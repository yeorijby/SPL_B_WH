// EcsSock.cpp : implementation of the CEcsSock class
//

#include "stdafx.h"
#include "ecs.h"

#include "Host.h"
#include "EcsDoc.h"
//#include "Plc.h"
#include "MainFrm.h"
#include "Lib.h"

#include <stddef.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CListenSk, CAsyncSocket)
IMPLEMENT_DYNAMIC(CHostSv, CAsyncSocket)
IMPLEMENT_DYNAMIC(CHostCl, CAsyncSocket)

CListenSk::CListenSk()
{
	m_pDoc = NULL;
}

CListenSk::CListenSk(CEcsDoc * pDoc)
{
	m_pDoc = pDoc;
	m_bConnected = FALSE;
}

CListenSk::~CListenSk()
{
}

void CListenSk::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (m_bConnected) {
		CHostSv *pHostSv = m_pDoc->m_pHostSv; 
		m_pDoc->m_pHostSv = NULL;
		m_bConnected = FALSE;
		pHostSv->ShutDown();
	    delete pHostSv;
	    m_pDoc->m_pHostSv = new CHostSv(m_pDoc);
		m_pDoc->m_pHostSv->UpdateCommSv(COMM_STA_RECEIVE);
		m_pDoc->m_pLog->Error(LOG_POS_SYSTEM, LOG_SYSTEM, "ECS서버와 IMS 클라이언트 재연결 성공..!");
//		AfxMessageBox("ECS HostSrv Program choice another channel");
	}
	else {
	    m_pDoc->m_pHostSv = new CHostSv(m_pDoc);
		m_pDoc->m_pHostSv->UpdateCommSv(COMM_STA_RECEIVE);
	}

	if (!Accept(*m_pDoc->m_pHostSv))
	{
		m_pDoc->m_pHostSv->UpdateCommSv(NOTIFY_ERROR);
		m_pDoc->m_pHostSv->ShutDown();
		delete m_pDoc->m_pHostSv;
		m_pDoc->m_pHostSv = NULL;
	}
	else
	{
		m_pDoc->m_pHostSv->UpdateCommSv(COMM_STA_RECEIVE);
		m_bConnected = TRUE;
		m_pDoc->m_pLog->Event(LOG_POS_SYSTEM, LOG_SYSTEM, "ECS서버와 IMS 클라이언트 연결 성공");
	}

	CAsyncSocket::OnAccept(nErrorCode);
}


CHostSv::CHostSv(CEcsDoc* pDoc)
{
	m_pDoc = pDoc;
}

void CHostSv::Clear()
{
	uchar RxBuff[1024];

	Receive(RxBuff, 1024);
}

void CHostSv::Answer(uchar ucMsgType, int nLuggNum, int nReasonCode)
{
	char TxBuff[64];
	char AckNak = (nReasonCode == MSG_NO_ERROR) ? 'A':'N';
	ucMsgType += (ucMsgType == CMD_UNPREDICT) ? 0 : 32; // make lower case character

	memset(TxBuff, 0x0, sizeof(TxBuff));
	sprintf(TxBuff, "ECS_MBX   %04d ", MSG_LENGTH_RESPONSE_DATA);
	sprintf(TxBuff + MSG_LENGTH_HEADER, "%c%c%c%02d%04d%.4s%c",
		STX, ucMsgType, AckNak, nReasonCode, nLuggNum, "    ", ETX);

	UpdateCommSv(COMM_STA_SEND);
	Send(TxBuff, MSG_LENGTH_RESPONSE_MSG);
}

void CHostSv::OnClose(int nErrorCode)
{

	UpdateCommSv(NOTIFY_ERROR);

	CString strLog;
	strLog.Format("ECS서버와 IMS클라이언트 연결 해제..! [%s]", CLib::GetSystemErrMsg(nErrorCode));

	LOG_EVENT(LOG_POS_SYSTEM, LOG_SYSTEM, strLog);
	m_pDoc->m_pListenSk->m_bConnected = FALSE;
	m_pDoc->m_pHostSv = NULL;
	ShutDown();
	delete this;

	CAsyncSocket::OnClose(nErrorCode);
}


void CHostSv::UpdateCommSv(char Status)
{
	::PostMessage(m_pDoc->m_hwndView, WM_USER_HOST_NOTIFY, 1, Status);
//	m_pDoc->UpdateHostComm(Status);
	return;

	CMainFrame* pWnd = (CMainFrame *)AfxGetMainWnd();
	pWnd->UpdateCommHostSv(Status);
}


void CHostSv::OnReceive(int nErrorCode)
{
	CAsyncSocket::OnReceive(nErrorCode);

	if (nErrorCode) {
		AfxMessageBox("The Windows Sockets implementation detected that the network subsystem failed.");
	}

	int nMsgLen = 0;
	char RxBuff[1024];
	CString strLog;

	DWORD dwLen = 0;
	DWORD nRealLen = 0;

	if(IOCtl( FIONREAD, &dwLen ) == FALSE)
	{
		strLog.Format("CHostCl::OnReceive.. 메시지 수신 에러 [%s]", CLib::GetSystemErrMsg());
		LOG_ERROR(LOG_POS_HOST, LOG_SYSTEM, strLog);
		Answer(CMD_UNPREDICT, 0, MSG_SOCKET_ERROR);
		return;
	}

	memset(RxBuff, 0x00, sizeof(RxBuff));
	if ((nRealLen = Receive(RxBuff, dwLen)) != dwLen)
	{
		strLog.Format("ECS서버 메시지 수신.. 수신 메시지 길이 이상.. LEN[%d]  REAL_LEN[%d]", dwLen, nRealLen);
		LOG_ERROR(LOG_POS_HOST, LOG_SYSTEM, strLog);
		Answer(CMD_UNPREDICT, 0, MSG_INVALID_HEADER_LENG);
		return;
	}

	if (RxBuff[MSG_LENGTH_HEADER] != STX)
	{
		Answer(CMD_UNPREDICT, 0, MSG_NO_STX);
		LOG_ERROR(LOG_POS_HOST, LOG_SYSTEM, "ECS서버 데이터 수신.. No STX 에러..!");
		return;
	}

/*	int nFrameLen = dwLen -1;
	if (RxBuff[nFrameLen] != ETX)
	{
		Answer(CMD_UNPREDICT, 0, MSG_NO_ETX);
		LOG_ERROR(LOG_POS_HOST, LOG_SYSTEM, "ECS서버 데이터 수신.. No ETX 에러..!");
		return;
	}
*/

	Parsing(RxBuff + MSG_LENGTH_HEADER);
	UpdateCommSv(NOTIFY_RECEIVE);
}

void CHostSv::Parsing(char *pFrame)
{
	CString strLog;

	CString strFrame = pFrame;
	uchar ucMsgType = pFrame[1];
	int nResultCode = MSG_NO_ERROR;

	switch (ucMsgType)
	{
	case	CMD_ORDER:
		{
			CJobItem JobItem;
			CString strLocation, strSecondLoc, strProductID, strProductName, strPltQuantity, strNotNo;

			int nLuggNum = atoi(strFrame.Mid(3, 4));
			int nJobType = (int) (pFrame[2] & 0x0f);

			int nBatchNo = atoi(strFrame.Mid(7, 4));
			int nPalletNo = atoi(strFrame.Mid(11, 4));
			int nLevelNo = atoi(strFrame.Mid(15, 2));

			int	nStartPos = atoi(strFrame.Mid(17, 3));
			int nDestPos = atoi(strFrame.Mid(27, 3));
			
			int nPriority = atoi(strFrame.Mid(37, 3));

			int nLoadline = atoi(strFrame.Mid(40, 1));

			strProductID = strFrame.Mid(41, 20);
			strProductName = strFrame.Mid(61, 50);
			strProductID.TrimRight();

			//strProductName + 출고라인(2) + 마지막 파렛트(1) + ETX
	
			switch (JobItem.GetPattern(nJobType))
			{
			case	JOB_PATTERN_STO:
				strLocation = strFrame.Mid(30, 7);
				if (!JobItem.IsValidLocation(strLocation))
				{
					strLog.Format("Parsing.. 입고 Location 이상 [%s]", strLocation);
					LOG_ERROR(LOG_POS_HOST, nLuggNum, strLog);
					nResultCode = MSG_INVALID_LOC;
					break;
				}

				if (!CLib::IsValidHostStartPos(nStartPos))
				{
					strLog.Format("Parsing.. 입고 출발위치 이상 [%d]", nStartPos);
					LOG_ERROR(LOG_POS_HOST, nLuggNum, strLog);
					nResultCode = MSG_INVALID_STN_NO;
					break;
				}

				if(JOB->Find(nLuggNum) != NULL)
				{
					LOG_ERROR(LOG_POS_HOST, nLuggNum, "Parsing.. 사용중인 작업번호로 작업지시.. IMS 확인");
					nResultCode = MSG_LUGG_NO_DUPLICATED;
					break;
				}

				LOG_JOB(LOG_POS_HOST, nLuggNum, "Parsing.. 입고작업 지시 수신.. ");
																		 			
				if (!JOB->Add(nLuggNum, nJobType, strLocation, nBatchNo, nPalletNo, nLevelNo, nStartPos, nDestPos, nPriority,  
										strProductID, strSecondLoc, JOB_STA_NEW, strProductName, strPltQuantity, -1))
					nResultCode = MSG_INTERNAL_ERROR;

				break;

			case	JOB_PATTERN_RET:
				{
					int nPeriodNum = -1;
					strLocation = strFrame.Mid(20, 7);
					nPeriodNum = atoi(strFrame.Mid(114, 8));

					if (!JobItem.IsValidLocation(strLocation))
					{
						strLog.Format("Parsing.. 출고 Location 이상 [%s]", strLocation);
						LOG_ERROR(LOG_POS_HOST, nLuggNum, strLog);
						nResultCode = MSG_INVALID_LOC;
						break;
					}

					if (!CLib::IsValidHostDestPos(nDestPos))
					{
						strLog.Format("Parsing.. 출고 도착위치 이상 [%d]", nDestPos);
						LOG_ERROR(LOG_POS_HOST, nLuggNum, strLog);
						nResultCode = MSG_INVALID_STN_NO;
						break;
					}

					if (JOB->Find(nLuggNum) != NULL)
					{
						LOG_ERROR(LOG_POS_HOST, nLuggNum, "Parsing.. 사용중인 작업번호로 작업지시.. IMS 확인");
						nResultCode = MSG_LUGG_NO_DUPLICATED;
						break;
					}

					strLog.Format("Parsing.. 출고작업 지시 수신..Batch=[%d]..Pallet=[%d]..Level=[%d]", nBatchNo, nPalletNo, nLevelNo);
					LOG_JOB(LOG_POS_HOST, nLuggNum, strLog);
					
	/*				if(nDestPos == IMS_ECS_RET_STATION_201) 
					{
						++m_pDoc->m_n4groupInternalPalletCount;

						if(m_pDoc->m_n4groupInternalPalletCount == nPalletNo)
						{
							m_pDoc->m_n4groupInternalPalletCount = 0;
						}

						if(m_pDoc->m_n4groupInternalPalletCount == 1)
						{
							m_pDoc->m_n4GroupInternalBatch = nBatchNo;
						}
					}
					else if(nDestPos == IMS_ECS_RET_STATION_202) 
					{
						if(m_pDoc->m_n5groupInternalPalletCount == nPalletNo)
						{
							m_pDoc->m_n5groupInternalPalletCount = 0;
						}

						m_pDoc->m_n5GroupInternalBatch = nBatchNo;
						++m_pDoc->m_n5groupInternalPalletCount;
					}
					else if(nDestPos == IMS_ECS_RET_STATION_203)
					{
						if(m_pDoc->m_n6groupInternalPalletCount == nPalletNo)
						{
							m_pDoc->m_n6groupInternalPalletCount = 0;
						}

						m_pDoc->m_n6GroupInternalBatch = nBatchNo;
						++m_pDoc->m_n6groupInternalPalletCount;
					}
	*/
					if (!JOB->Add(nLuggNum, nJobType, strLocation, nBatchNo, nPalletNo, nLevelNo, nStartPos, nDestPos, nPriority, 
											strProductID, strSecondLoc, JOB_STA_NEW, strProductName, strPltQuantity, nPeriodNum))
						nResultCode = MSG_INTERNAL_ERROR;
				}
				break;

			case	JOB_PATTERN_CIRCULATION:
				strLocation = strFrame.Mid(20, 7);
				if (!JobItem.IsValidLocation(strLocation))
				{
					strLog.Format("Parsing.. Picking Location 이상 [%s]", strLocation);
					LOG_ERROR(LOG_POS_HOST, nLuggNum, strLog);
					nResultCode = MSG_INVALID_LOC;
					break;
				}

				if (!CLib::IsValidHostDestPos(nDestPos))
				{
					strLog.Format("Parsing.. Picking 도착위치 이상 [%d]", nDestPos);
					LOG_ERROR(LOG_POS_HOST, nLuggNum, strLog);
					nResultCode = MSG_INVALID_STN_NO;
					break;
				}

				if (JOB->Find(nLuggNum) != NULL)
				{
					LOG_ERROR(LOG_POS_HOST, nLuggNum, "Parsing.. 사용중인 작업번호로 작업지시.. IMS 확인");
					nResultCode = MSG_LUGG_NO_DUPLICATED;
					break;
				}

				LOG_JOB(LOG_POS_HOST, nLuggNum, "Parsing.. Picking 작업 지시 수신..");

				if (!JOB->Add(nLuggNum, nJobType, strLocation, nBatchNo, nPalletNo, nLevelNo, nStartPos, nDestPos, nPriority, 
										strProductID, strSecondLoc, JOB_STA_NEW, "", strPltQuantity, -1))
					nResultCode = MSG_INTERNAL_ERROR;

				break;

			case	JOB_PATTERN_RTR: 

				strLocation = strFrame.Mid(20, 7);
				if (!JobItem.IsValidLocation(strLocation))
				{
					strLog.Format("Parsing.. RTR 출발 Location 이상 [%s]", strLocation);
					LOG_ERROR(LOG_POS_HOST, nLuggNum, strLog);
					nResultCode = MSG_INVALID_LOC;
					break;
				}
				strSecondLoc = strFrame.Mid(30, 7);
				if (!JobItem.IsValidLocation(strSecondLoc))
				{
					strLog.Format("Parsing.. RTR 도착 Location 이상 [%s]", strSecondLoc);
					LOG_ERROR(LOG_POS_HOST, nLuggNum, strLog);
					nResultCode = MSG_INVALID_LOC;
					break;
				}
				if (JobItem.GetStackerNum(strLocation) != JobItem.GetStackerNum(strSecondLoc))
				{
					nResultCode = MSG_INVALID_LOC;
					break;
				}
				if (JOB->Find(nLuggNum) != NULL)
				{
					LOG_ERROR(LOG_POS_HOST, nLuggNum, "Parsing.. 사용중인 작업번호로 작업지시.. IMS 확인");
					nResultCode = MSG_LUGG_NO_DUPLICATED;
					break;
				}

				strLog.Format("Parsing.. 랙투랙 작업지시 수신.. 출발=[%s] 도착=[%s]", strLocation, strSecondLoc);
				LOG_JOB(LOG_POS_HOST, nLuggNum, strLog);

				if (!JOB->Add(nLuggNum, nJobType, strLocation, nBatchNo, nPalletNo, nLevelNo, nStartPos, nDestPos, nPriority, 
										strProductID, strSecondLoc, JOB_STA_NEW, "", strPltQuantity, -1))
					nResultCode = MSG_INTERNAL_ERROR;
				
				break;
			case	JOB_PATTERN_MOVE:
				{
					int nLineNum = atoi(strFrame.Mid(111, 2));
					int nLastPallet = atoi(strFrame.Mid(113, 1));
					int nPeriodNum = atoi(strFrame.Mid(114, 8));

					//추가 Column 
					strPltQuantity = strFrame.Mid(122, 8); //수량 strPltQuantity (0000125)
					strLocation = strFrame.Mid(130, 5); //생산라인 strLocation (H1234)
					strSecondLoc = strFrame.Mid(135, 8); //전표번호 strSecondLoc (12345678)

					if (!CLib::IsValidHostStartPos(nStartPos))
					{
						strLog.Format("Parsing.. 이동 출발위치 이상 [%d]", nStartPos);
						LOG_ERROR(LOG_POS_HOST, nLuggNum, strLog);
						nResultCode = MSG_INVALID_STN_NO;
						break;
					}

					if (!CLib::IsValidHostDestPos(nDestPos))
					{
						strLog.Format("Parsing.. 이동 도착위치 이상 [%d]", nDestPos);
						LOG_ERROR(LOG_POS_HOST, nLuggNum, strLog);
						nResultCode = MSG_INVALID_STN_NO;
						break;
					}

					if (MOVEJOB->Find(nLuggNum) != NULL)
					{
						LOG_ERROR(LOG_POS_HOST, nLuggNum, "Parsing.. 사용중인 작업번호로 작업지시.. IMS 확인");
						nResultCode = MSG_LUGG_NO_DUPLICATED;
						break;
					}

					strLog.Format("Parsing.. 이동 작업지시 수신.. 출발=[%d] 도착=[%d] 수량:%s 생산라인:%s 전표번호:%s", nStartPos, nDestPos, strPltQuantity, strLocation, strSecondLoc);
					LOG_JOB(LOG_POS_HOST, nLuggNum, strLog);

					if(nStartPos == 103)
						nLineNum = 12;

					if (!MOVEJOB->Add(nLuggNum, nJobType, strLocation, nBatchNo, nPalletNo, nLevelNo, nStartPos, nDestPos, nPeriodNum, 
											strProductID, strSecondLoc, JOB_STA_NEW, strProductName, strPltQuantity, nLoadline, nLineNum, nLastPallet))
						nResultCode = MSG_INTERNAL_ERROR;
				}
				
				break;

			default:
				strLog.Format("Parsing.. 정의되지 않은 작업구분 JobType=[%d].. IMS 확인 바람..", nJobType);
				LOG_ERROR(LOG_POS_HOST, nLuggNum, strLog);
				nResultCode = MSG_UNKNOWN_JOB_TYPE;
				break;
			}
			Answer(ucMsgType, nLuggNum, nResultCode);

//			if (nResultCode == MSG_NO_ERROR)
//				JOB->Invoke(nLuggNum);
		}
		break;

	case	CMD_CANCEL:
		{
			int nLuggNum = atoi(strFrame.Mid(3, 4));
			int nJobType = CLib::ConvertCustomToJobType((int) pFrame[2]);
			strLog.Format("Parsing.. 작업취소 수신.. JobType=[%d]", nJobType);
			LOG_EVENT(LOG_POS_HOST, nLuggNum, strLog);

			int nTrackNum = 0;// = CLib::GetTrackByStationNum(ECS_PICK_POS_1);
			if( m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_nLuggNum != nLuggNum )
			{
				Answer(ucMsgType, nLuggNum, MSG_ALREADY_INVOKED_JOB);
				LOG_ERROR(LOG_POS_HOST, nLuggNum, "Parsing.. 작업취소 불가 CV.. 작업중 ");
				break;
			}

			CJobItem * pJobItem = JOB->Find(nLuggNum);
			if (pJobItem == NULL) 
			{
				Answer(ucMsgType, nLuggNum, MSG_NO_EXIST_JOB);
				LOG_ERROR(LOG_POS_HOST, nLuggNum, "Parsing.. 유효하지 않은 작업번호.. ");
				break;
			}

			//	if (!((pJobItem->GetPattern() == JOB_PATTERN_STO && pJobItem->m_nStatus == JOB_STA_CV_OPER_REQUEST) ||
			//	(pJobItem->GetPattern() != JOB_PATTERN_STO && pJobItem->m_nStatus == JOB_STA_SC_OPER_REQUEST) ||
			//	pJobItem->m_nStatus == JOB_STA_NEW))
			//	{
			//		Answer(ucMsgType, nLuggNum, MSG_ALREADY_INVOKED_JOB);
			//		m_pDoc->m_pLog->Error(LOG_POS_HOST, nLuggNum, "Parsing.. This Job can't cancel.. Please check it's status");
			//		break;
			//	}
				
			#define TRACK_INFO	m_pDoc->m_ConveyorThreadInfo[0].m_ConveyorMsg
			if (JOB->Remove(nLuggNum))
			{
				TRACK_INFO.nTrackNum = nTrackNum;
				TRACK_INFO.nLuggNum  = 0;
				TRACK_INFO.nJobType  = 0;
				TRACK_INFO.nStartPos = 0;
				TRACK_INFO.nDestPos  = 0;

				TRACK_INFO.bModified = TRUE;
				CV_ACTION(0);

				Answer(ucMsgType, nLuggNum, RECEIVE_OK);
				LOG_EVENT(LOG_POS_HOST, nLuggNum, "Parsing.. 작업취소 & 응답 OK");
			}
			else
			{
				Answer(ucMsgType, nLuggNum, MSG_INTERNAL_ERROR);
				LOG_ERROR(LOG_POS_HOST, nLuggNum, "Parsing.. 작업취소 실패[작업리스트에서 삭제 실패]");
			}
		}

		break;

	case	CMD_CHANGE:
		{
			CJobItem JobItem;
			int nLuggNum = atoi(strFrame.Mid(3, 4));
			int nJobType = CLib::ConvertCustomToJobType((int) pFrame[2]);
			int	nStartPos = atoi(strFrame.Mid(7, 3));
			int nDestPos = atoi(strFrame.Mid(17, 3));
			int nPriority = atoi(strFrame.Mid(27, 3));

			strLog.Format("Parsing.. 변경작업 수신.. JobType=[%d]", nJobType);
			LOG_EVENT(LOG_POS_HOST, nLuggNum, strLog);

			CJobItem * pJobItem = JOB->Find(nLuggNum);
			if (pJobItem == NULL) 
			{
				Answer(ucMsgType, nLuggNum, MSG_NO_EXIST_JOB);
				LOG_ERROR(LOG_POS_HOST, nLuggNum, "Parsing.. 변경작업 유효하지 않은 작업번호.. ");
				break;
			}

			if (!((pJobItem->GetPattern() == JOB_PATTERN_STO && pJobItem->m_nStatus == JOB_STA_CV_OPER_REQUEST) ||
				  (pJobItem->GetPattern() != JOB_PATTERN_STO && pJobItem->m_nStatus == JOB_STA_SC_OPER_REQUEST) ||
				   pJobItem->m_nStatus == JOB_STA_NEW))
			{
				Answer(ucMsgType, nLuggNum, MSG_ALREADY_INVOKED_JOB);
				LOG_ERROR(LOG_POS_HOST, nLuggNum, "Parsing.. 해당 작업 변경 불가.. 작업상태를 확인");
				break;
			}

			pJobItem->m_nJobType = nJobType;
			pJobItem->m_nStartPos = nStartPos;
			pJobItem->m_nDestPos = nDestPos;
			pJobItem->m_nPriority = nPriority;

			int nPattern = JobItem.GetPattern(nJobType);
			if (nPattern == JOB_PATTERN_STO)
			{
				pJobItem->m_strLocation = strFrame.Mid(20, 7);
			}
			else if (nPattern == JOB_PATTERN_RET || nPattern == JOB_PATTERN_CIRCULATION)
			{
				pJobItem->m_strLocation = strFrame.Mid(10, 7);
			}
			else if (nPattern == JOB_PATTERN_RTR)
			{
				pJobItem->m_strLocation = strFrame.Mid(10, 7);
				pJobItem->m_strSecondLoc = strFrame.Mid(20, 7);
			}

			Answer(ucMsgType, nLuggNum, RECEIVE_OK);
			LOG_EVENT(LOG_POS_HOST, nLuggNum, "Parsing.. 작업변경 & 응답 OK");
		}
		break;

	case	CMD_ALT_LOC:
		{
			int nLuggNum = atoi(strFrame.Mid(3, 4));
			int nJobType = (int) (pFrame[2] & 0x0f);
			CString strLocation = strFrame.Mid(20, 7);
			CString strSecondLoc = strFrame.Mid(30, 7);
			int	nKind = atoi(strFrame.Mid(27, 1));

			int	nStatus = (nKind == 1) ? JOB_STA_DUAL_STO_RETRY : JOB_STA_EMPTY_RET_RETRY;
			if(nJobType == JOB_TYPE_RACK_TO_RACK)
				nStatus = (nKind == 1) ? JOB_STA_DUAL_RTR_RETRY : JOB_STA_EMPTY_RTR_RETRY;

			if (nStatus == JOB_STA_DUAL_STO_RETRY || nStatus == JOB_STA_DUAL_RTR_RETRY)
			{
				CJobItem* pJobItem = m_pDoc->m_pJob->Find(nLuggNum);
				if (pJobItem == NULL)
				{
					LOG_ERROR(LOG_POS_HOST, nLuggNum, "이중입고 재지정.. 작업번호를 찾을수 없슴");
					Answer(ucMsgType, nLuggNum, MSG_NO_EXIST_JOB);
					break;
				}
				if (pJobItem->m_nJobType != nJobType)
				{
					strLog.Format("작업구분이 일치 하지않음.. Org=[%s]  New=[%s]", 
  								   pJobItem->GetType(), pJobItem->GetType(nJobType));
					LOG_ERROR(LOG_POS_HOST, nLuggNum, strLog);
					Answer(ucMsgType, nLuggNum, MSG_INVALID_CONTENT);
					break;
				}

				if(nStatus == JOB_STA_DUAL_STO_RETRY)
					pJobItem->m_strLocation  = strLocation;
				else
					pJobItem->m_strSecondLoc = strSecondLoc;

				pJobItem->m_nStatus = nStatus;
				m_pDoc->m_pJob->m_bModified = TRUE;

				if (nStatus == JOB_STA_DUAL_STO_RETRY)
					LOG_JOB(LOG_POS_HOST, nLuggNum, "Parsing.. STO..이중입고 재지정 수신..");
				else
					LOG_JOB(LOG_POS_HOST, nLuggNum, "Parsing.. RTR..이중입고 재지정 수신..");

				Answer(ucMsgType, nLuggNum, RECEIVE_OK);
				break;
			}

			if (nStatus == JOB_STA_EMPTY_RET_RETRY || nStatus == JOB_STA_EMPTY_RTR_RETRY)
			{
				CJobItem* pJobItem = m_pDoc->m_pJob->Find(nLuggNum);
				if (pJobItem == NULL)
				{
					LOG_ERROR(LOG_POS_HOST, nLuggNum, "공출고 재지정.. 작업번호를 찾을수 없슴");
					Answer(ucMsgType, nLuggNum, MSG_NO_EXIST_JOB);
					break;
				}

				if (pJobItem->m_nJobType != nJobType)
				{
					strLog.Format("작업구분이 일치 하지않음.. Org=[%s]  New=[%s]",
								   pJobItem->GetType(), pJobItem->GetType(nJobType));
					Answer(ucMsgType, nLuggNum, MSG_INVALID_CONTENT);
					break;
				}

				pJobItem->m_strLocation = strLocation;
				pJobItem->m_nStatus = nStatus;
				m_pDoc->m_pJob->m_bModified = TRUE;

				if (nStatus == JOB_STA_EMPTY_RET_RETRY)
					LOG_JOB(LOG_POS_HOST, nLuggNum, "Parsing.. RET.. 공출고 재지정 수신..");
				else
					LOG_JOB(LOG_POS_HOST, nLuggNum, "Parsing.. RTR.. 공출고 재지정 수신..");

				Answer(ucMsgType, nLuggNum, RECEIVE_OK);
				break;
			}
		}
		break;
	
	case	CMD_REQ_START:
		m_pDoc->m_pConfig->m_bSysSuspend = FALSE;
		Answer(ucMsgType, 0, RECEIVE_OK);
		m_pDoc->m_pConfig->Backup();
		LOG_EVENT(LOG_POS_SYSTEM, LOG_SYSTEM, "Request to START Directive from IMS..");
		break;

	case	CMD_REQ_PAUSE:
		m_pDoc->m_pConfig->m_bSysSuspend = TRUE;
		Answer(ucMsgType, 0, RECEIVE_OK);
		m_pDoc->m_pConfig->Backup();
		LOG_EVENT(LOG_POS_SYSTEM, LOG_SYSTEM, "Request to PAUSE Directive from IMS..");
		break;

	case	CMD_TIME_SET:
		{
			char	ucDate[32], ucTime[32];
			SYSTEMTIME  lpSystemTime;
			CString strTmp1, strTmp2, strTmp3, strTmp4, strTmp5, strTmp6, strLog;
  
			GetLocalTime(&lpSystemTime);

			strTmp1.Format("%.4s", pFrame +2);	lpSystemTime.wYear  = atoi(strTmp1);
			strTmp2.Format("%.2s", pFrame +6);	lpSystemTime.wMonth = atoi(strTmp2);
			strTmp3.Format("%.2s", pFrame +8);	lpSystemTime.wDay   = atoi(strTmp3);

			strTmp4.Format("%.2s", pFrame+10);	lpSystemTime.wHour  = atoi(strTmp4);
			strTmp5.Format("%.2s", pFrame+12);	lpSystemTime.wMinute= atoi(strTmp5);
			strTmp6.Format("%.2s", pFrame+14);	lpSystemTime.wSecond= atoi(strTmp6);
			lpSystemTime.wMilliseconds = 0;

			CTime theTime( lpSystemTime.wYear, lpSystemTime.wMonth,  lpSystemTime.wDay,
						lpSystemTime.wHour, lpSystemTime.wMinute, lpSystemTime.wSecond);
			theTime.GetAsSystemTime(lpSystemTime);
			SetLocalTime(&lpSystemTime);

			sprintf(ucDate, "date %.4s-%.2s-%.2s", strTmp1, strTmp2, strTmp3);
			sprintf(ucTime, "time %.2s:%.2s:%.2s", strTmp4, strTmp5, strTmp6);

			strLog.Format("Date & Time SET Date:[%s] Time:[%s]", ucDate, ucTime);
			LOG_EVENT(LOG_POS_SYSTEM, LOG_SYSTEM, strLog);

//			system(ucDate);
//			system(ucTime);
			Answer(ucMsgType, 0, RECEIVE_OK);
		}
		break;
	
	default:
		strLog.Format("정의되지 않은 메시지 수신.. MsgType=[%c]", ucMsgType);
		Answer(ucMsgType, 0, MSG_UNKNOWN_MSG_TYPE);
		LOG_EVENT(LOG_POS_HOST, LOG_SYSTEM, strLog);
		break;
	}

//	UpdateCommSv(COMM_STA_RECEIVE);
}


CHostCl::CHostCl(CEcsDoc* pDoc)
{
	m_pDoc = pDoc;
}

void CHostCl::Clear()
{
	uchar RxBuff[1024];

	Receive(RxBuff, 1024);
}

CString CHostCl::GetStringReason(int nReasonCode)
{
	return CLib::ConvertReasonToString(nReasonCode);
}

void CHostCl::Status(int nRegularCycle)
{
#define	CV_TRACK_INFO					m_pDoc->m_ConveyorTrackInfo
#define SC_INFO						    m_pDoc->m_pStackerInfo[i]

#define	SC_STATUS_NORMAL_WAIT			0
#define	SC_STATUS_STORING				1
#define	SC_STATUS_RETRIEVING			2
#define	SC_STATUS_RACK_TO_RACK			3
#define	SC_STATUS_NO_ONLINE				4
#define	SC_STATUS_ERROR					5
#define	SC_STATUS_SUSPEND_STO			6
#define	SC_STATUS_SUSPEND_RET			7
#define	SC_STATUS_SUSPEND_ALL			8

#define ECS_STATION_CNT					4

	int nCvStatus = 1, nScStatus = 1, nStoHSStatus = 1, nRetHSStatus = 1;

	char TxBuff[512];
	static	char	PrevBuff[512] = {0};
	memset(TxBuff, 0x0, sizeof(TxBuff));
	sprintf(TxBuff, "ECS_MBX   %04d ", MSG_LENGTH_STATUS_DATA);
	TxBuff[MSG_LENGTH_HEADER] = STX;
	TxBuff[MSG_LENGTH_HEADER+1] = CMD_STATUS;

	for (int i = 0; i < SC_CNT; i++)
	{
		if (!SC_INFO->m_bInvoke && !SC_INFO->m_bSecondInvoke &&	 SC_INFO->m_ucMode == SC_MODE_AUTO)  //PLC 타입
			nScStatus = SC_STATUS_NORMAL_WAIT;

		if (SC_INFO->m_bInvoke)
		{
			if (SC_INFO->m_bInternalJobType == SC_JOB_TYPE_RACK_TO_RACK)
				nScStatus = SC_STATUS_RACK_TO_RACK;
			else if (SC_INFO->m_bInternalJobType == SC_JOB_TYPE_RETRIEVE)
				nScStatus = SC_STATUS_RETRIEVING;
			else
				nScStatus = SC_STATUS_STORING;
		}

		if (SC_INFO->m_ucMode != SC_MODE_AUTO)   //Plc Type
			nScStatus = SC_STATUS_NO_ONLINE;
		if (SC_INFO->m_bStoreSuspend)
			nScStatus = SC_STATUS_SUSPEND_STO;
		if (SC_INFO->m_bRetrieveSuspend)
			nScStatus = SC_STATUS_SUSPEND_RET;
		if (SC_INFO->m_bStoreSuspend && SC_INFO->m_bRetrieveSuspend)
			nScStatus = SC_STATUS_SUSPEND_ALL;
		if (SC_INFO->m_ucStatus == SC_STA_ERROR)
			nScStatus = SC_STATUS_ERROR;

		//TEST
		//if(i == 0 || i == 1) { nScStatus = SC_STATUS_NORMAL_WAIT; /*SC_INFO->m_nInternalLuggNum = 1075;*/}
		
		//nScStatus = SC_STATUS_NORMAL_WAIT;
		sprintf(TxBuff + MSG_LENGTH_HEADER + 2 + (11 * i), "%02d%d%04d%04d",
			i+1, nScStatus, SC_INFO->m_nInternalLuggNum, SC_INFO->m_nSecondInternalLuggNum);
	}

	{
		//sprintf(TxBuff + MSG_LENGTH_HEADER + 2 + (11 * SC_CNT), "%d",
		//			CV_TRACK_INFO[9-1].m_bStoStationReady);

		sprintf(TxBuff + MSG_LENGTH_HEADER + 2 + (11 * SC_CNT), "%d",
					1/*CV_TRACK_INFO[8-1].m_bStoStationReady*/);

		//sprintf(TxBuff + MSG_LENGTH_HEADER + 2 + (11 * SC_CNT) + 1, "%d",
		//			CV_TRACK_INFO[71-1].m_bStoStationReady);
		sprintf(TxBuff + MSG_LENGTH_HEADER + 2 + (11 * SC_CNT) + 1, "%d",
					CV_TRACK_INFO[793-1].m_bStoStationReady);

		sprintf(TxBuff + MSG_LENGTH_HEADER + 2 + (11 * SC_CNT) + 2, "%d",
					CV_TRACK_INFO[71-1].m_bRetStationReady);

		sprintf(TxBuff + MSG_LENGTH_HEADER + 2 + (11 * SC_CNT) + 3, "%d",
					!m_pDoc->m_bStoRetMode);
	}	

	TxBuff[MSG_LENGTH_HEADER + 2 + (11 * SC_CNT) + ECS_STATION_CNT] = ETX;

	int rt=memcmp(PrevBuff, TxBuff, MSG_LENGTH_STATUS_MSG);
	if( nRegularCycle || rt )
	{
			int a = strlen(TxBuff);
			int b = MSG_LENGTH_STATUS_MSG;
		if(	SendMsg(TxBuff, MSG_LENGTH_STATUS_MSG) == FALSE )
		{
			CString strLog;
			strLog.Format("상태 보고 송신 실패.. 에러=[%s]", CLib::GetSystemErrMsg());
			LOG_ERROR(LOG_POS_HOST, LOG_SYSTEM, strLog);
			return;
		}
		memcpy(PrevBuff, TxBuff, MSG_LENGTH_STATUS_MSG);
	}
}

void CHostCl::Throughput()
{
	char TxBuff[512];
	memset(TxBuff, 0x0, sizeof(TxBuff));
	sprintf(TxBuff, "ECS_MBX   %04d ", MSG_LENGTH_THROUGHPUT_DATA);
	TxBuff[MSG_LENGTH_HEADER] = STX;
	TxBuff[MSG_LENGTH_HEADER+1] = CMD_THROUGHPUT;

	CTime t(m_pDoc->m_pStatistic->m_sSTC[0].tBeginTime);
	CString strDate = t.Format("%Y%m%d");
	CString strTime = t.Format("%H%M%S");

	//sprintf(TxBuff + MSG_LENGTH_HEADER + 2, "%.8s%.6s", strDate, strTime);

	int nJobHour,  nJobMin=0;
	int nErrHour,  nErrMin=0;
	int nAvgHour,  nAvgMin=0;
	int nLongHour, nLongMin=0;

	for (int i = 0; i < SC_CNT; i++)
	{
		/*
		sprintf( TxBuff + MSG_LENGTH_HEADER + 2 + 14 + (27 * i), "%02d%03d%03d%03d%04d%04d%04d%04d",
			i+1,
			m_pDoc->m_pStatistic->m_sSTC[i].nOnlineJobSum,
			m_pDoc->m_pStatistic->m_sSTC[i].nOfflineJobSum,
			m_pDoc->m_pStatistic->m_sSTC[i].nErrorSum,
			m_pDoc->m_pStatistic->m_sSTC[i].nOnlineJobSum,
			m_pDoc->m_pStatistic->m_sSTC[i].tOnlineWorkTime/60,
			m_pDoc->m_pStatistic->m_sSTC[i].tOfflineWorkTime/60,
			m_pDoc->m_pStatistic->m_sSTC[i].tOnlineTroubleTime/60,
			m_pDoc->m_pStatistic->m_sSTC[i].tOfflineTroubleTime/60 );*/

		nJobHour  = m_pDoc->m_pJob->ScHis[i].TimeInfo[m_pDoc->m_pJob->m_nSftNo].m_nJobTime / 3600;
		nJobMin   = (m_pDoc->m_pJob->ScHis[i].TimeInfo[m_pDoc->m_pJob->m_nSftNo].m_nJobTime % 3600)/60;
		nErrHour  = m_pDoc->m_pJob->ScHis[i].TimeInfo[m_pDoc->m_pJob->m_nSftNo].m_nErrTime / 3600;
		nErrMin   = (m_pDoc->m_pJob->ScHis[i].TimeInfo[m_pDoc->m_pJob->m_nSftNo].m_nErrTime % 3600)/60;
		nAvgHour  = m_pDoc->m_pJob->ScHis[i].TimeInfo[m_pDoc->m_pJob->m_nSftNo].m_nAvgTime / 60;
		nAvgMin   = m_pDoc->m_pJob->ScHis[i].TimeInfo[m_pDoc->m_pJob->m_nSftNo].m_nAvgTime % 60;
		nLongHour = m_pDoc->m_pJob->ScHis[i].TimeInfo[m_pDoc->m_pJob->m_nSftNo].m_nLongTime / 60;
		nLongMin  = m_pDoc->m_pJob->ScHis[i].TimeInfo[m_pDoc->m_pJob->m_nSftNo].m_nLongTime % 60;

		sprintf( TxBuff + MSG_LENGTH_HEADER + 2 + (18 * i), "%02d%02d%02d%02d%02d%02d%02d%02d%02d",
			i+10,
			nJobHour,
			nJobMin,
			nErrHour,
			nErrMin,
			nAvgHour,
			nAvgMin,
			nLongHour,
			nLongMin );
	}

	TxBuff[MSG_LENGTH_HEADER + 2 + (18 * SC_CNT)] = ETX;

	SendMsg(TxBuff, MSG_LENGTH_THROUGHPUT_MSG);
}

void CHostCl::Complete()
{
	CJobItem* pJobItem = JOB->FetchByStatus(JOB_STA_COMPLETE_REQUEST);
	if (pJobItem == NULL) return;
		
	Complete(pJobItem->m_nLuggNum);
}


void CHostCl::Complete(int nLuggNum, int nScJobType)
{
	CJobItem* pJobItem = JOB->Find(nLuggNum);
	if (pJobItem == NULL)
	{
		LOG_ERROR(LOG_POS_HOST, nLuggNum, "CHostCl::Complete.. 작업번호를 찾을수 없슴..");
		return;
	}

	int nStep = 1;
	if (pJobItem->m_nStatus != JOB_STA_COMPLETE)
		nStep = 0;

	char TxBuff[256];
	memset(TxBuff, 0x0, sizeof(TxBuff));

	if(nScJobType == SC_JOB_TYPE_ANY)
	{
		switch (pJobItem->GetPattern())
		{
		case	JOB_PATTERN_STO:
		case	JOB_PATTERN_CIRCULATION:
		case	JOB_PATTERN_RTR:
//		case	JOB_PATTERN_AISLE:
			nScJobType = SC_JOB_TYPE_STORE;
			break;
		case	JOB_PATTERN_RET:
			nScJobType = SC_JOB_TYPE_RETRIEVE;
			break;
		case	JOB_PATTERN_MOVE:
			nScJobType = SC_JOB_TYPE_SITE_TO_SITE;
			break;
		}
	}

	pJobItem = JOB->Find(nLuggNum);
	if(pJobItem == NULL) return;


	sprintf(TxBuff, "ECS_MBX   %04d ", MSG_LENGTH_COMPLETE_DATA);

	sprintf(TxBuff + MSG_LENGTH_HEADER, "%c%c%d%04d%c%d%c",	
		STX, CMD_COMPLETE, pJobItem->m_nJobType, nLuggNum, nScJobType, nStep, ETX);

	CString strLog;
	if(	SendMsg(TxBuff, MSG_LENGTH_COMPLETE_MSG) == TRUE)
	{
		if (  pJobItem->m_nJobType == JOB_TYPE_UNIT_STO || nScJobType == SC_JOB_TYPE_STORE )
		{
			strLog.Format("작업완료 보고.. JobType=[%s]  ScJobType=[%c] ", pJobItem->GetType(), nScJobType);
			LOG_JOB(LOG_POS_HOST, nLuggNum, strLog);

			m_pDoc->m_pJob->m_nResultCount[pJobItem->GetStackerNum()]++;
			::PostMessage(m_pDoc->m_hwndView, WM_USER_JOB_NOTIFY, JOB_RESULT_DRAW, 0);
			JOB->Remove(pJobItem);
			return;
		}
	}
	else
	{
		strLog.Format("작업완료 보고 송신 실패.. JobType=[%s] 에러=[%s]", pJobItem->GetType(), CLib::GetSystemErrMsg());
		LOG_ERROR(LOG_POS_HOST, nLuggNum, strLog);
		return;
	}

//	if (  pJobItem->m_nJobType == JOB_TYPE_UNIT_STO || nScJobType == SC_JOB_TYPE_STORE )
//		pJobItem->m_nStatus = JOB_STA_COMPLETE;

//	else if (  pJobItem->m_nJobType == JOB_TYPE_UNIT_RET ||
//		      (pJobItem->m_nJobType == JOB_TYPE_PICK_REPLENISH &&
//	 		   nScJobType == SC_JOB_TYPE_RETRIEVE) )
//		pJobItem->m_nStatus = JOB_STA_COMPLETE;

	strLog.Format("작업완료 보고.. JobType=[%s]  ScJobType=[%c] ", pJobItem->GetType(), nScJobType);
	LOG_JOB(LOG_POS_HOST, nLuggNum, strLog);

}

void CHostCl::BcrJob()
{
	/*
	CBcrBuff* pBcrBuff = m_pDoc->m_pJob->FindBcrBuff();
	if (pBcrBuff == NULL) return;
	if (m_pDoc->m_pBcrInfo[pBcrBuff->m_nBcrNum-1]->m_ucMode == BCR_MODE_MANUAL)
		return;
		
	char TxBuff[256];
	memset(TxBuff, 0x0, sizeof(TxBuff));

	sprintf(TxBuff, "ECS_MBX   %04d ", MSG_LENGTH_BCRJOB_DATA);
	sprintf(TxBuff + MSG_LENGTH_HEADER, "%c%c%03d%-20s%c%c",
		STX, CMD_BCRJOB, pBcrBuff->m_nBcrNum-1, pBcrBuff->m_strBcrData, 0x20, ETX);
	SendMsg(TxBuff, MSG_LENGTH_BCRJOB_MSG);
	CString strLog;
	strLog.Format("SendMsg Bcr Data.. BcrNo=[%d]  BcrData=[%s]", pBcrBuff->m_nBcrNum, pBcrBuff->m_strBcrData);
	m_pDoc->m_pLog->Job(LOG_POS_HOST, 0, strLog);

	m_pDoc->m_pJob->RemoveBcrJob(pBcrBuff);
	//pBcrBuff->m_nStatus = 2;
	*/
}

void CHostCl::Arrived(int nLuggNum)
{
	CMoveJobItem* pMoveJobItem = MOVEJOB->Find(nLuggNum);
	if (pMoveJobItem == NULL)
	{
		LOG_ERROR(LOG_POS_HOST, nLuggNum, "CHostCl::Arrived.. 작업번호를 찾을수 없슴..");
		return;
	}


	char TxBuff[256];
	int nSeqNo = 0;
	memset(TxBuff, 0x0, sizeof(TxBuff));
	sprintf(TxBuff, "ECS_MBX   %04d ", MSG_LENGTH_ARRIVAL_DATA);
	sprintf(TxBuff + MSG_LENGTH_HEADER, "%c%c%03d%d%04d%.4s%d%c",
		STX, CMD_LOAD_ARRV, pMoveJobItem->m_nDestPos, pMoveJobItem->m_nJobType, nLuggNum, "    ", nSeqNo, ETX);

	CString strLog;
	if(SendMsg(TxBuff, MSG_LENGTH_ARRIVAL_MSG) == FALSE)
	{
		strLog.Format("도착완료 보고 송신 실패.. 에러=[%s]", CLib::GetSystemErrMsg());
		LOG_ERROR(LOG_POS_HOST, nLuggNum, strLog);
		return;
	}

	strLog.Format("도착완료 보고.. JobType=[%s] Station=[%d]", pMoveJobItem->GetType(), pMoveJobItem->m_nDestPos);
	LOG_JOB(LOG_POS_HOST, nLuggNum, strLog);

}

void CHostCl::Arrived2(int nLuggNum, int nLuggNum2)
{
	CMoveJobItem* pMoveJobItem = MOVEJOB->Find(nLuggNum);
	if (pMoveJobItem == NULL)
	{
		LOG_ERROR(LOG_POS_HOST, nLuggNum, "CHostCl::Arrived.. 작업번호를 찾을수 없슴..");
		return;
	}

	CMoveJobItem* pMoveJobItem2 = MOVEJOB->Find(nLuggNum2);
	if (pMoveJobItem2 == NULL)
	{
		LOG_ERROR(LOG_POS_HOST, nLuggNum2, "CHostCl::Arrived.. 작업번호를 찾을수 없슴..");
		return;
	}

	char TxBuff[256];
	int nSeqNo = 0;
	memset(TxBuff, 0x0, sizeof(TxBuff));
	sprintf(TxBuff, "ECS_MBX   %04d ", MSG_LENGTH_ARRIVAL_DATA);
	sprintf(TxBuff + MSG_LENGTH_HEADER, "%c%c%03d%d%04d%04d%d%c",
		STX, CMD_LOAD_ARRV, pMoveJobItem->m_nDestPos, pMoveJobItem->m_nJobType, nLuggNum, nLuggNum2, nSeqNo, ETX);

	CString strLog;
	if(SendMsg(TxBuff, MSG_LENGTH_ARRIVAL_MSG) == FALSE)
	{
		strLog.Format("도착완료 보고 송신 실패.. 에러=[%s]", CLib::GetSystemErrMsg());
		LOG_ERROR(LOG_POS_HOST, nLuggNum, strLog);

		strLog.Format("도착완료 보고 송신 실패.. 에러=[%s]", CLib::GetSystemErrMsg());
		LOG_ERROR(LOG_POS_HOST, nLuggNum2, strLog);
		return;
	}

	strLog.Format("도착완료 보고.. JobType=[%s] Station=[%d]", pMoveJobItem->GetType(), pMoveJobItem->m_nDestPos);
	LOG_JOB(LOG_POS_HOST, nLuggNum, strLog);

	strLog.Format("도착완료 보고.. JobType=[%s] Station=[%d]", pMoveJobItem2->GetType(), pMoveJobItem2->m_nDestPos);
	LOG_JOB(LOG_POS_HOST, nLuggNum2, strLog);

}

void CHostCl::OfflineJob()
{

	CFile* pFile;
	TRY
	{
		const char* pFileName = LPCTSTR(MANIO_FILE);
		pFile = new CFile(pFileName, CFile::modeReadWrite);
	}
	CATCH( CFileException, e )
	{
		CString strTemp;
		strTemp.Format("CHostCl::OfflineJob.. File could not be opened e->m_cause=[%d]", e->m_cause);
		m_pDoc->m_pLog->Error(LOG_POS_SC, LOG_SYSTEM, strTemp);
		m_pDoc->m_pJob->m_bIsOfflineJob = FALSE;
		return;
	}
	END_CATCH

	pFile->SeekToBegin();

//	static int nLuggNum = 9001;
	char	Buffer[256];
	int		nReadLen = 4 + 1 + 7 + 7 + 20 + 15 + 8 + 6 + 2 + 2;
	int		nFileLen = pFile->GetLength();
	char	TxBuff[256];

	memset(TxBuff, 0x0, sizeof(TxBuff));

	while(TRUE) {
		memset(Buffer, 0x0, sizeof(Buffer));
		int nBytesRead = pFile->Read(Buffer, nReadLen);
		nFileLen -= nBytesRead;
		if (nBytesRead < nReadLen) {
			pFile->Close();
			if (nFileLen <= 0) {
				CFile::Remove(MANIO_FILE);
				m_pDoc->m_pJob->m_bIsOfflineJob = FALSE;
			}
			break;
		}

		if (Buffer[nReadLen - 4] != ':') {
			AfxMessageBox("Check the File -> log\\OfflineJob.dat !!");
			m_pDoc->m_pJob->m_bIsOfflineJob = FALSE;
			break;
		}

		if (Buffer[nReadLen - 3] == 0x30)	// 미전송
		{
//			if(++ nLuggNum > 9999)	nLuggNum = 9001;
			CString	strFrame;
			strFrame.Format("%s", Buffer);
			int nLuggNum = atoi(strFrame.Left(4));
			sprintf(TxBuff, "ECS_MBX   %04d ", MSG_LENGTH_OFFJOB_DATA);
			sprintf(TxBuff + MSG_LENGTH_HEADER, "%c%c%.68s%c",
				STX, CMD_OFFLINE_JOB, Buffer, ETX);

			SendMsg(TxBuff, MSG_LENGTH_OFFJOB_MSG);
			CString strLog;
			strLog.Format("Offline Job..  JobClass=[%c], SrcLoc=[%.7s] DestLoc=[%.7s]", Buffer[4], &Buffer[5], &Buffer[12]);
			m_pDoc->m_pLog->Job(LOG_POS_HOST, nLuggNum, strLog);
			pFile->Seek(-3L, CFile::current);
			pFile->Write("1", 1);
			pFile->Close();
			break;
		}
		else continue;
	}

	delete pFile;
}

void CHostCl::Cancel(int nLuggNum)
{
	CJobItem* pJobItem = m_pDoc->m_pJob->Find(nLuggNum);
	if (pJobItem == NULL)
	{
		m_pDoc->m_pLog->Error(LOG_POS_HOST, nLuggNum, "Luggage Number does not exist..");
		return;
	}

	char TxBuff[256];
	memset(TxBuff, 0x0, sizeof(TxBuff));
	sprintf(TxBuff, "ECS_MBX   %04d ", MSG_LENGTH_CANCEL_DATA);
	sprintf(TxBuff + MSG_LENGTH_HEADER, "%c%c%d%04d%c",
		STX, CMD_CANCEL, pJobItem->m_nJobType, nLuggNum, ETX);

	SendMsg(TxBuff, MSG_LENGTH_CANCEL_MSG);
	CString strLog;
	strLog.Format("SendMsg Cancel.. JobType=[%s]", pJobItem->GetType());
	m_pDoc->m_pLog->Event(LOG_POS_HOST, nLuggNum, strLog);

}

void CHostCl::Error(int nDevKind, int nDevNo, int nErrKind, int nErrCode, int nLuggNum, CString strLocation )
{
	CJobItem *pJobItem;
	if (nLuggNum && nErrKind)
	{
		pJobItem = JOB->Find(nLuggNum);
		if (pJobItem == NULL)
		{
			LOG_ERROR(LOG_POS_HOST, nLuggNum, "CHostCl::Error.. 작업번호를 찾을수 없슴..");
			return;
		}
	}

	int	nBank, nBay, nLevel;
	if ( strLocation.IsEmpty() )
	{
		nBank = nBay = nLevel = 0;
	}
	else
	{
		nBank  = CLib::GetBank(strLocation);
		nBay   = CLib::GetBay(strLocation);
		nLevel = CLib::GetLevel(strLocation);
	}

	pJobItem = JOB->Find(nLuggNum);
	if(pJobItem == NULL) return;
		
	char TxBuff[256];
	memset(TxBuff, 0x0, sizeof(TxBuff));
	sprintf(TxBuff, "ECS_MBX   %04d ", MSG_LENGTH_ERROR_DATA);
	sprintf(TxBuff + MSG_LENGTH_HEADER, "%c%c%d%03d%d%04d%04d%02d%03d%02d%c",
		STX, CMD_ERROR, nDevKind, nDevNo, nErrKind, nErrCode, nLuggNum, nBank, nBay, nLevel, ETX);

	CString strLog;
	if(	SendMsg(TxBuff, MSG_LENGTH_ERROR_MSG) == FALSE )
	{
		strLog.Format("에러 보고 송신 실패.. 에러=[%s]", CLib::GetSystemErrMsg());
		LOG_ERROR(LOG_POS_HOST, nLuggNum, strLog);
		return;
	}

	strLog.Format("에러 보고.. DevKind=[%d] DevNo=[%d] ErrKind=[%d] LuggNum=[%d]", nDevKind, nDevNo, nErrKind, nLuggNum);
	LOG_EVENT(LOG_POS_HOST, nLuggNum, strLog);
}

void CHostCl::PutOffTrans()
{

	CMsg	*pMsg;
	CString strLog;

	POSITION	posPrev;
	if (m_pDoc->m_pJob->m_MsgList.GetCount() == 0)	return;
	for (POSITION pos = m_pDoc->m_pJob->m_MsgList.GetHeadPosition(); pos != NULL;)
	{
		posPrev = pos;
		pMsg = (CMsg *)m_pDoc->m_pJob->m_MsgList.GetNext(pos);

		if (pMsg != NULL && !pMsg->m_bNew)	continue;

		switch (pMsg->m_MsgType)
		{
		case	CMD_COMPLETE:
			Complete(pMsg->m_nLuggNum, pMsg->m_nScJobType);
			strLog.Format("PutOff Complete.. ScJobType=[%c]", pMsg->m_nScJobType);
			m_pDoc->m_pLog->Job(LOG_POS_HOST, pMsg->m_nLuggNum, strLog);
			break;
		case	CMD_ERROR:
			Error(pMsg->m_nDevKind, pMsg->m_nDevNo, pMsg->m_nErrKind, pMsg->m_nErrCode, pMsg->m_nLuggNum, pMsg->m_strLocation);
			strLog.Format("PutOff Error.. DevKind=[%d] DevNo=[%d] ErrCode=[%d]", pMsg->m_nDevKind, pMsg->m_nDevNo, pMsg->m_nErrCode);
			m_pDoc->m_pLog->Job(LOG_POS_HOST, pMsg->m_nLuggNum, strLog);
			break;
		case	CMD_CANCEL:
			Cancel(pMsg->m_nLuggNum);
			m_pDoc->m_pLog->Job(LOG_POS_HOST, pMsg->m_nLuggNum, "PutOff Cancel.. ");
			break;
		case	CMD_LOAD_ARRV:
			//Arrived(pMsg->m_nLuggNum);
			m_pDoc->m_pLog->Job(LOG_POS_HOST, pMsg->m_nLuggNum, "PutOff Arrive.. ");
			break;
		default:
			strLog.Format("PutOffTrans.. MsgType=[%c], DevKind=[%d]", pMsg->m_MsgType, pMsg->m_nDevKind);
			m_pDoc->m_pLog->Error(LOG_POS_HOST, pMsg->m_nLuggNum, strLog);
			break;
		}

		m_pDoc->m_pJob->m_MsgList.RemoveAt(posPrev);
		delete pMsg;
	}

	m_pDoc->m_pJob->Backup();
}

BOOL CHostCl::SendMsg(char* pTxBuff, int nSndMsgLen)
{
	UpdateCommCl(NOTIFY_SEND);
	return (Send(pTxBuff, nSndMsgLen) == nSndMsgLen) ? TRUE : FALSE;
}

/*
void CHostCl::SendMsg(char* pTxBuff, int nSndMsgLen)
{
	UpdateCommCl(COMM_STA_SEND);
	Send(pTxBuff, nSndMsgLen);
}
*/
//^^suri

void CHostCl::OnReceive(int nErrorCode)
{
	CAsyncSocket::OnReceive(nErrorCode);

	if (nErrorCode) {
		AfxMessageBox("The Windows Sockets implementation (HostCl) detected that the network subsystem failed.");
	}

	int nMsgLen = 0;
	char RxBuff[1024];
	CString strLog;

	DWORD dwLen = 0;
	DWORD nRealLen = 0;

	if(IOCtl( FIONREAD, &dwLen ) == FALSE)
	{
		strLog.Format("CHostCl::OnReceive.. 메시지 수신 에러 [%s]", CLib::GetSystemErrMsg());
		LOG_ERROR(LOG_POS_HOST, LOG_SYSTEM, strLog);
		UpdateCommCl(NOTIFY_ERROR);
		return;
	}

	memset(RxBuff, 0x00, sizeof(RxBuff));
	if ((nRealLen = Receive(RxBuff, dwLen)) != dwLen)
	{
		strLog.Format("ECS클라이언트 메시지 수신.. 수신 메시지 길이 이상.. LEN[%d]  REAL_LEN[%d]", dwLen, nRealLen);
		LOG_ERROR(LOG_POS_HOST, LOG_SYSTEM, strLog);
		UpdateCommCl(NOTIFY_ERROR);
		return;
	}

	if (RxBuff[MSG_LENGTH_HEADER] != STX)
	{
		LOG_ERROR(LOG_POS_HOST, LOG_SYSTEM, "ECS클라이언트 데이터 수신.. No STX 에러..!");
		UpdateCommCl(NOTIFY_ERROR);
		return;
	}

	int nFrameLen = dwLen -1;
	if (RxBuff[nFrameLen] != ETX)
	{
		LOG_ERROR(LOG_POS_HOST, LOG_SYSTEM, "ECS클라이언트 데이터 수신.. No ETX 에러..!");
		UpdateCommCl(NOTIFY_ERROR);
		return;
	}

	Parsing(RxBuff + MSG_LENGTH_HEADER);
	UpdateCommCl(NOTIFY_RECEIVE);

/*	CAsyncSocket::OnReceive(nErrorCode);

	if (nErrorCode) {
		AfxMessageBox("The Windows Sockets implementation (HostCl) detected that the network subsystem failed.");
	}

	int nMsgLen = 0;
	char RxBuff[1024];

	memset(RxBuff, 0x00, sizeof(RxBuff));
	if (Receive(RxBuff, MSG_LENGTH_HEADER) != MSG_LENGTH_HEADER)
	{
		m_pDoc->m_pLog->HOST_ERROR("Error(HostCl).. Msg header lenth is too short.");
		UpdateCommCl(COMM_STA_STOP);
		return;
	}

	RxBuff[MSG_LENGTH_HEADER - 1] = 0;
	nMsgLen = atoi( &RxBuff[10] );
	if(nMsgLen <= 0)
	{
		m_pDoc->m_pLog->HOST_ERROR("Error(HostCl).. Invalid MsgLen.");
		UpdateCommCl(COMM_STA_STOP);
		return;
	}

	if (Receive(RxBuff + MSG_LENGTH_HEADER, nMsgLen) != nMsgLen)
	{
		m_pDoc->m_pLog->HOST_ERROR("Error(HostCl).. Msg lenth is not correct.");
		UpdateCommCl(COMM_STA_STOP);
		return;
	}

	if (RxBuff[MSG_LENGTH_HEADER] != STX)
	{
		m_pDoc->m_pLog->HOST_ERROR("Error(HostCl).. There is no STX...");
		UpdateCommCl(COMM_STA_STOP);
		return;
	}

	if (RxBuff[MSG_LENGTH_HEADER + nMsgLen -1] != ETX)
	{
		m_pDoc->m_pLog->HOST_ERROR("Error(HostCl).. There is no ETX...");
		UpdateCommCl(COMM_STA_STOP);
		return;
	}

	Parsing(RxBuff + MSG_LENGTH_HEADER);
	UpdateCommCl(COMM_STA_RECEIVE);
*/
}

/*
/*
void CHostCl::ReadData()
{
	int nMsgLen = 0;
	char RxBuff[1024];

	memset(RxBuff, 0x00, sizeof(RxBuff));

	nMsgLen = Receive(RxBuff, MSG_LENGTH_HEADER);
	if (nMsgLen <= 0)
		return;
	if (nMsgLen != MSG_LENGTH_HEADER)
	{
		m_pDoc->m_pLog->HOST_ERROR("Error(HostCl).. Msg header lenth is too short.");
		UpdateCommCl(COMM_STA_STOP);
		return;
	}

	RxBuff[MSG_LENGTH_HEADER - 1] = 0;
	nMsgLen = atoi( &RxBuff[10] );
	if(nMsgLen <= 0)
	{
		m_pDoc->m_pLog->HOST_ERROR("Error(HostCl).. Invalid MsgLen.");
		UpdateCommCl(COMM_STA_STOP);
		return;
	}

	if (Receive(RxBuff + MSG_LENGTH_HEADER, nMsgLen) != nMsgLen)
	{
		m_pDoc->m_pLog->HOST_ERROR("Error(HostCl).. Msg lenth is not correct.");
		UpdateCommCl(COMM_STA_STOP);
		return;
	}

	if (RxBuff[MSG_LENGTH_HEADER] != STX)
	{
		m_pDoc->m_pLog->HOST_ERROR("Error(HostCl).. There is no STX...");
		UpdateCommCl(COMM_STA_STOP);
		return;
	}

	if (RxBuff[MSG_LENGTH_HEADER + nMsgLen -1] != ETX)
	{
		m_pDoc->m_pLog->HOST_ERROR("Error(HostCl).. There is no ETX...");
		UpdateCommCl(COMM_STA_STOP);
		return;
	}

	Parsing(RxBuff + MSG_LENGTH_HEADER);
	UpdateCommCl(COMM_STA_RECEIVE);
}
*/
void CHostCl::Parsing(char *pFrame)
{
	CString strLog;

	CString strFrame = pFrame;
	uchar ucMsgType  = pFrame[1];
	uchar ucAckNak   = pFrame[2];
	int nReason      = atoi(strFrame.Mid(3, 2));
	int nLuggNum     = atoi(strFrame.Mid(5, 4));
	int nLuggNum2     = atoi(strFrame.Mid(9, 4));

	switch (ucMsgType)
	{
	case	CMD_COMPLETE_ANSWER:
		{
			CJobItem* pJobItem = m_pDoc->m_pJob->Find(nLuggNum);
			if (pJobItem == NULL)
			{
				//m_pDoc->m_pLog->Error(LOG_POS_HOST, nLuggNum, "CHostCl::Parsing.. 작업완료 에러..  작업번호가 존재 하지 않음.");
				return;
			}

			if ( nReason || ucAckNak != 'A')
			{
				CString strLog;
				strLog.Format("CHostCl::Parsing.. 완료 실패.. Reason=[%s:%d]", GetStringReason(nReason), nReason);
				pJobItem->m_nErrCode = pJobItem->m_nStatus = JOB_STA_REFUSE_COMPLETE;
				return;
			}

			m_pDoc->m_pJob->m_nResultCount[pJobItem->GetStackerNum()]++;
			::PostMessage(m_pDoc->m_hwndView, WM_USER_JOB_NOTIFY, JOB_RESULT_DRAW, 0);

//			int nJobType = CLib::ConvertJobTypeToPattern2(pJobItem->m_nJobType);
			int nJobType = pJobItem->m_nJobType;
			CString strLog;
			strLog.Format("CHostCl::Parsing.. 완료 응답 수신.. Lugg=[%d],JobType=[%d],Sts=[%d]", nLuggNum, nJobType, pJobItem->m_nStatus);
			m_pDoc->m_pLog->Job(LOG_POS_HOST, nLuggNum, strLog);

			if ( pJobItem->m_nStatus == JOB_STA_COMPLETE )
			{
				m_pDoc->m_pJob->m_nResultCount[pJobItem->GetStackerNum()]++;
				::PostMessage(m_pDoc->m_hwndView, WM_USER_JOB_NOTIFY, JOB_RESULT_DRAW, 0);
				JOB->Remove(pJobItem);
			}
			return;
		}
		break;
	case	CMD_LOAD_ARRV_ANSWER:
		{
			CMoveJobItem* pMoveJobItem2=NULL;
			CMoveJobItem* pMoveJobItem = m_pDoc->m_pMoveJob->Find(nLuggNum);
			if (pMoveJobItem == NULL)
			{
				m_pDoc->m_pLog->Error(LOG_POS_HOST, nLuggNum, "CHostCl::Parsing.. 도착완료 에러..  작업번호가 존재 하지 않음.");
				return;
			}

			if(nLuggNum2 != 0)
			{
				pMoveJobItem2 = m_pDoc->m_pMoveJob->Find(nLuggNum2);
				if (pMoveJobItem2 == NULL)
				{
					m_pDoc->m_pLog->Error(LOG_POS_HOST, nLuggNum2, "CHostCl::Parsing.. 도착완료 에러..  작업번호가 존재 하지 않음.");
					return;
				}
			}

			if ( nReason || ucAckNak != 'A')
			{
				CString strLog;
				strLog.Format("CHostCl::Parsing.. 도착 실패.. Reason=[%s:%d]", GetStringReason(nReason), nReason);
				m_pDoc->m_pLog->Error(LOG_POS_HOST, nLuggNum, strLog);
				pMoveJobItem->m_nErrCode = pMoveJobItem->m_nStatus = JOB_STA_REFUSE_ARRIVED;
				if(nLuggNum2 != 0)
				 pMoveJobItem2->m_nErrCode = pMoveJobItem2->m_nStatus = JOB_STA_REFUSE_ARRIVED;
				return;
			}

			CString strLog;
			strLog.Format("CHostCl::Parsing.. 도착 완료 응답 수신.. Lugg=[%d],JobType=[%d],Sts=[%d]", nLuggNum, pMoveJobItem->m_nJobType, pMoveJobItem->m_nStatus);
			m_pDoc->m_pLog->Job(LOG_POS_HOST, nLuggNum, strLog);

			if(nLuggNum2 != 0)
			{
				strLog.Format("CHostCl::Parsing.. 도착 완료 응답 수신.. Lugg=[%d],JobType=[%d],Sts=[%d]", nLuggNum2, pMoveJobItem2->m_nJobType, pMoveJobItem2->m_nStatus);
				m_pDoc->m_pLog->Job(LOG_POS_HOST, nLuggNum2, strLog);
			}

/*			if ( pMoveJobItem->m_nJobType == JOB_TYPE_STN_TO_STN )
			{
				m_pDoc->m_pJob->m_nResultCount[pJobItem->GetStackerNum()]++;
				::PostMessage(m_pDoc->m_hwndView, WM_USER_JOB_NOTIFY, JOB_RESULT_DRAW, 0);
			}
*/
			//if ( pJobItem->m_nJobType == JOB_TYPE_UNIT_RET || pJobItem->m_nJobType == JOB_TYPE_SITE_TO_SITE )
			//2005.03.23
			//if ( pJobItem->m_nJobType == JOB_TYPE_STN_TO_STN)
			//	m_pDoc->m_pJob->Remove(pJobItem);
		}
		break;
	case	CMD_CHANGE_ANSWER:
		break;
	case	CMD_CANCEL_ANSWER:
		{
			CJobItem* pJobItem = m_pDoc->m_pJob->Find(nLuggNum);
			if (pJobItem == NULL)
			{
				m_pDoc->m_pLog->Error(LOG_POS_HOST, nLuggNum, "Cancel Error..  No exist luggage number.");
				return;
			}

			if ( nReason || ucAckNak != 'A')
			{
				CString strLog;
				strLog.Format("Cancel Failed.. Reason=[%s:%d]", GetStringReason(nReason), nReason);
				m_pDoc->m_pLog->Error(LOG_POS_HOST, nLuggNum, strLog);
				pJobItem->m_nErrCode = pJobItem->m_nStatus = JOB_STA_REFUSE_CANCEL;
				return;
			}

//			m_pDoc->m_pJob->Remove(pJobItem);
		}
		break;
	case	CMD_OFFLINE_JOB_ANSWER:
		{
			if ( (nReason || ucAckNak != 'A') && nLuggNum )
			{
				CString strLog;
				strLog.Format("Offline Job Failed.. Reason=[%s:%d]", GetStringReason(nReason), nReason);
				m_pDoc->m_pLog->Error(LOG_POS_HOST, nLuggNum, strLog);
			}
		}
		break;
	case	CMD_ERROR_ANSWER:
		{
			if ( (nReason || ucAckNak != 'A') && nLuggNum )
			{
				CJobItem* pJobItem = m_pDoc->m_pJob->Find(nLuggNum);
				if (pJobItem == NULL)	return;
				if ( pJobItem->m_nStatus != JOB_STA_ERR_EMPTY_RET &&
						pJobItem->m_nStatus != JOB_STA_ERR_DUAL_STO )	return;

				strLog.Format("CHostCl::Parsing.. 에러보고 실패.. Reason=[%s:%d] ", GetStringReason(nReason), nReason);
				m_pDoc->m_pLog->Error(LOG_POS_HOST, nLuggNum, strLog);
				pJobItem->m_nErrCode = pJobItem->m_nStatus = JOB_STA_REFUSE_ERROR;
			}
			else
			{
				CJobItem* pJobItem = m_pDoc->m_pJob->Find(nLuggNum);
				if (pJobItem == NULL)	return;
				pJobItem->m_nStatus = JOB_STA_ERR_REPORT;
			}
		}
		break;
	case	CMD_STATUS_ANSWER:
		{
			if ( nReason || ucAckNak != 'A')
			{
				CString strLog;
				strLog.Format("Status Failed.. Reason=[%s:%d]", GetStringReason(nReason), nReason);
				m_pDoc->m_pLog->HOST_DEBUG(strLog);
			}
		}
		break;
	case	CMD_THROUGHPUT_ANSWER:
		{
			if ( nReason || ucAckNak != 'A')
			{
				CString strLog;
				strLog.Format("Throughput Failed.. Reason=[%s:%d]", GetStringReason(nReason), nReason);
				m_pDoc->m_pLog->HOST_DEBUG(strLog);
			}
		}
		break;
	case	CMD_BCRJOB_ANSWER:
		{
			if ( nReason || ucAckNak != 'A')
			{
				CString strLog;
				strLog.Format("BCR Job Failed.. Reason=[%s:%d]", GetStringReason(nReason), nReason);
				m_pDoc->m_pLog->HOST_DEBUG(strLog);
				return;
			}

			//m_pDoc->m_pJob->Remove(pJobItem);
		}
		break;
	default:
		{
			CString strLog;
			strLog.Format("Parsing Error(HostCl).. Unknown MsgType=[%c]", ucMsgType);
			m_pDoc->m_pLog->HOST_DEBUG(strLog);
		}
		break;
	}
}

void CHostCl::OnConnect(int nErrorCode)
{
	if (nErrorCode)
	{
		if (m_pDoc->m_nAlive != 1)
		{
			ShutDown();
			delete this;
			return;
		}

		UpdateCommCl(NOTIFY_ERROR);

		CString strLog;
		strLog.Format("IMS 서버에 접속 실패.. [%s]", CLib::GetSystemErrMsg(nErrorCode));

		// 2001. 10. 03
		// PGM 종료시 CEcsView::OnTimer - ConnectServer로 인해 CEcsDoc객체 소멸후
		// OnConnect호출되면 에러
		CMainFrame *pFrame  =  (CMainFrame*)AfxGetMainWnd();
		if(pFrame != NULL)
		{
			CEcsDoc *pDoc = (CEcsDoc*)pFrame->GetActiveDocument();
			if(pDoc != NULL)
			{
				//if (pDoc->m_pLog != NULL)
				//	LOG_ERROR(LOG_POS_SYSTEM, LOG_SYSTEM, strLog);
				pDoc->m_pHostCl = NULL;
				ShutDown();
				delete this;
			}
		}
	}
	else
	{
		m_pDoc->m_pHostCl = this;
		UpdateCommCl(NOTIFY_SEND);
		m_pDoc->m_pLog->Event(LOG_POS_SYSTEM, LOG_SYSTEM, "IMS 서버에 접속 성공.. (HostCl)");
	}

	/*
	if (nErrorCode)
	{
		UpdateCommCl(NOTIFY_ERROR);
//		m_pDoc->m_pLog->Error(LOG_POS_SYSTEM, LOG_SYSTEM, "Connect Failed !(HostCl)");
		m_pDoc->m_pHostCl = NULL;
		ShutDown();
		delete this;
	}
	else
	{
		m_pDoc->m_pHostCl = this;
		UpdateCommCl(COMM_STA_SEND);
		m_pDoc->m_pLog->Event(LOG_POS_SYSTEM, LOG_SYSTEM, "Connected to IMS Server.. (HostCl)");
	}
	*/

	CAsyncSocket::OnConnect(nErrorCode);
}

void CHostCl::OnClose(int nErrorCode)
{
	UpdateCommCl(NOTIFY_ERROR);

	CString strLog;
	strLog.Format("ECS클라이언트와 IMS서버 연결 해제..! [%s]", CLib::GetSystemErrMsg(nErrorCode));

	LOG_EVENT(LOG_POS_SYSTEM, LOG_SYSTEM, strLog);
	m_pDoc->m_pHostCl = NULL;
	ShutDown();
	delete this;
	//delete m_pDoc->m_pHostCl;

	CAsyncSocket::OnClose(nErrorCode);
}

void CHostCl::UpdateCommCl(char Status)
{

	::PostMessage(m_pDoc->m_hwndView, WM_USER_HOST_NOTIFY, 0, Status);
//	m_pDoc->UpdateHostComm(Status);
	return;

	CMainFrame* pWnd = (CMainFrame *)AfxGetMainWnd();
	pWnd->UpdateCommHostCl(Status);
}
