// ScQ.cpp : implementation of the CSc class
//

#include "stdafx.h"

#include "Ecs.h"
#include "ScQ.h"

#include "Lib.h"

#define SC_INFO			m_pStackerInfo
#define	TRACK_INFO		m_pConveyorTrackInfo
#define	JOB				m_pDoc->m_pJob
#define	LOG				m_pDoc->m_pLog
#define	HOST			m_pDoc->m_pHostCl
#define STATISTIC		m_pDoc->m_pStatistic


CScQ::CScQ(int nNum, CEcsDoc* pDoc, CScSocket *pSock) : CMelsecSc3E(pSock)
{ 
	m_nNum = nNum;
	m_pDoc = pDoc;
	m_strDevice = m_pDoc->m_pConfig->GetScDeviceName(nNum);

	m_pStackerInfo = m_pDoc->m_pStackerInfo[nNum];
	m_pConveyorTrackInfo = m_pDoc->m_ConveyorTrackInfo;

	m_nCount = 0;
	m_bIsError = FALSE;

	time(&m_tJobStart);
	time(&m_tErrorStart);
}

int CScQ::ReadStatus()
{
	BYTE RxBuff[256];
	memset(RxBuff, NULL, sizeof(RxBuff));

	//if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 99, 31) == FALSE )
	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 95, 35) == FALSE )
	{
		if (SC_INFO->m_wPrevErrCode == SC_INFO->m_wErrCode)
			return FALSE;

		if (++m_nCount >= 3)
		{
			SC_INFO->m_wErrCode = SC_ERR_CODE_COMM_ERROR;
			SC_INFO->m_ucStatus = SC_STA_ERROR;
			SC_INFO->m_bModified = TRUE;
		}
		return FALSE;
	}
	m_nCount = 0;

    BYTE ucRcMode        = RxBuff[0]+0x30;  // 지상반 = Stacker Remote Controler
	BYTE ucScMode		 = RxBuff[2+8]+0x30;  // 기상반 = StackerCrane
    BYTE ucStatus        = RxBuff[4+8]+0x30;  // '1': 대기중 '2': 동작중 '4': 에러
//  BYTE ucProdLoad      = (RxBuff[3] & 0x01)+0x30;		// '1' = 0x31 
//	BYTE ucSecondProdLoad = (RxBuff[3] & 0x02)+0x30;	// '1' = 0x31 
	BYTE ucProdLoad      = RxBuff[3+8]+0x30;		// Fork#1 '1', Fork#2 '2', Fork#1, #2 '3'  

	BYTE ucHorizontalPos = RxBuff[6+8];
	BYTE ucVerticalPos   = RxBuff[8+8];

	BYTE ucFirstForkPos   = RxBuff[10+8];
	BYTE ucSecondForkPos  = RxBuff[11+8];

    WORD wErrCode = SwapToWord(RxBuff+12+8);
	BYTE ucFirstForkErrStatus	 = RxBuff[14+8];
	BYTE ucSecondForkErrStatus	 = RxBuff[15+8];
	
	WORD wForkJob = SwapToWord(RxBuff+16+8);

	BYTE ucActive		 = RxBuff[20+8]+0x30;
	BYTE ucTransaction	 = RxBuff[22+8]+0x30;

    BYTE ucJobType = RxBuff[24+8];
    WORD wLuggNum = SwapToWord(RxBuff+26+8);
    WORD wLuggNum2 = SwapToWord(RxBuff+46+8);

	if (ucRcMode != SC_INFO->m_ucRcMode)
	{
		SC_INFO->m_ucRcMode = ucRcMode;            
		SC_INFO->m_bModified = TRUE;
	}

	if (ucScMode != SC_INFO->m_ucScMode)
	{
		SC_INFO->m_ucScMode = ucScMode;           
		SC_INFO->m_bModified = TRUE;
	}

	if (ucStatus != SC_INFO->m_ucStatus)		  
	{
		m_pDoc->m_pStackerInfo[m_nNum]->m_ucPrevStatus = m_pDoc->m_pStackerInfo[m_nNum]->m_ucStatus;
		SC_INFO->m_ucStatus = ucStatus;
		SC_INFO->m_bModified = TRUE;
	}

	if (ucHorizontalPos != SC_INFO->m_nHorizontalPos)
	{
		SC_INFO->m_nHorizontalPos = ucHorizontalPos;
		SC_INFO->m_bModified = TRUE;
	}

	if (ucFirstForkPos != SC_INFO->m_ucFirstForkPos) // 필요없음
	{
		SC_INFO->m_ucFirstForkPos = ucFirstForkPos;
		
	}

	if (wErrCode != SC_INFO->m_wErrCode)
	{
		SC_INFO->m_wErrCode = wErrCode;
		SC_INFO->m_wPrevErrCode = 0;
		SC_INFO->m_bModified = TRUE;
	}

	if (ucFirstForkErrStatus != SC_INFO->m_ucFirstForkErrStatus) // 필요함
	{
		SC_INFO->m_ucFirstForkErrStatus = ucFirstForkErrStatus;
		SC_INFO->m_bModified = TRUE;
	}

	if (wForkJob != SC_INFO->m_wForkJob) // 필요없음
	{
		SC_INFO->m_wForkJob = wForkJob;
		
	}

	if (ucActive != SC_INFO->m_ucActive) // 필요함
	{
		SC_INFO->m_ucActive = ucActive;
		SC_INFO->m_bModified = TRUE;
	}

	if (ucTransaction != m_pDoc->m_pStackerInfo[m_nNum]->m_ucTransaction)
	{
		m_pDoc->m_pStackerInfo[m_nNum]->m_ucTransaction = ucTransaction;
		SC_INFO->m_bModified = TRUE;
	}

	if (ucJobType != SC_INFO->m_ucJobType)
	{
		SC_INFO->m_ucJobType = ucJobType;
		SC_INFO->m_bModified = TRUE;
	}

	if (wLuggNum != SC_INFO->m_nLuggNum)
	{
		SC_INFO->m_nLuggNum = wLuggNum;
	}

	if (wLuggNum2 != SC_INFO->m_nSecondLuggNum)
	{
		SC_INFO->m_nSecondLuggNum = wLuggNum2;
	}

	if ( SC_INFO->m_ucActive != SC_ACTIVE ||
		SC_INFO->m_ucRcMode != SC_MODE_ONLINE_NEW ||
		SC_INFO->m_ucScMode != SC_MODE_AUTO )
		SC_INFO->m_ucMode = SC_MODE_MANUAL_NEW;
	else
		SC_INFO->m_ucMode = SC_MODE_AUTO;

	StatisticTroubleTime();
	
	return TRUE;
}

void CScQ::InvokeCheck()
{
	if (SC_INFO->m_bInvoke)							
		return;
	if (SC_INFO->m_ucRcMode != SC_MODE_ONLINE_NEW)	
		return;
	if (SC_INFO->m_ucActive != SC_ACTIVE)			
		return;
	if (SC_INFO->m_ucScMode != SC_MODE_AUTO)		
		return;
	if (SC_INFO->m_ucStatus == SC_STA_MOVE)			
		return;
	if (SC_INFO->m_ucStatus == SC_STA_ERROR)		
		return;
	
	static int nCount[SC_CNT] = { 0, 0, 0, 0, 0, 0 };
	
	switch (SC_INFO->m_nPrevRtn)
	{
	case	ROUTINE_STORE:
		if (RetrieveRoutine())
		{
			nCount[m_nNum] = 0;
			break;
		}
		if (StoreRoutine())
		{
			nCount[m_nNum] = 0;
			break;
		}
		if (RackToRackRoutine())
		{
			nCount[m_nNum] = 0;
			break;
		}

	case	ROUTINE_RETRIEVE:
		if (StoreRoutine())
		{
			nCount[m_nNum] = 0;
			break;
		}
		if (RetrieveRoutine())
		{
			nCount[m_nNum] = 0;
			break;
		}
		if (RackToRackRoutine())
		{
			nCount[m_nNum] = 0;
			break;
		}
	case	ROUTINE_RACK_TO_RACK:
		if (RetrieveRoutine())
		{
			nCount[m_nNum] = 0;
			break;
		}
		if (StoreRoutine())
		{
			nCount[m_nNum] = 0;
			break;
		}
		if (RackToRackRoutine())
		{
			nCount[m_nNum] = 0;
			break;
		}
	default:
		SC_INFO->m_nPrevRtn = ROUTINE_STORE;
		break;
	}

/*	if (nCount[m_nNum] ++ > 900 && SC_INFO->m_ucHorizontalPos > 1)
	{
		nCount[m_nNum] = 0;
		if (SC_INFO->m_bStoreSuspend)		return;

		CallToHome();

		SC_INFO->m_bInvoke = TRUE;
		SC_INFO->m_nInternalLuggNum = 0;
		SC_INFO->m_bInternalJobType = SC_JOB_TYPE_CALL_TO_HOME;

		CString strLog;
		strLog.Format("Stacker Idle.. %s 홈복귀 지시..", m_strDevice);
		LOG_EVENT(LOG_POS_SC, LOG_SYSTEM, strLog);
	}
*/
}


BOOL CScQ::StoreRoutine()
{
	int nLuggNum2=0;
	CString strLocation2="";
	char bUseFork;
	CJobItem* pJobItem2=NULL;
	CString strLog;

	if (SC_INFO->m_bStoreSuspend)
		return FALSE;

	int nTrackNum1 = CLib::GetScStoHSTrack(m_nNum, TRUE);
	if (!m_pDoc->m_ConveyorTrackInfo[nTrackNum1].m_bStoHomeStandReady)
		return FALSE;
	if (m_pDoc->m_ConveyorTrackInfo[nTrackNum1].m_nLuggNum == 0)
		return FALSE;
	CJobItem* pJobItem1 = m_pDoc->m_pJob->Find(m_pDoc->m_ConveyorTrackInfo[nTrackNum1].m_nLuggNum);
	if (pJobItem1 == NULL)
	{
		CString strTemp;
		strTemp.Format("S/C#%d H/S#1에 도착한 Crate[%04d]의 작업정보가 없습니다.", m_nNum+1, m_pDoc->m_ConveyorTrackInfo[nTrackNum1].m_nLuggNum);
		m_pDoc->DisplayMessage(strTemp, FALSE);
		m_pDoc->m_pLog->Error(LOG_POS_SC, m_pDoc->m_ConveyorTrackInfo[nTrackNum1].m_nLuggNum, strTemp);
		return FALSE;
	}
	if (pJobItem1->m_nStatus != JOB_STA_CV_OPER_INVOKE)
	{
		CString strTemp;
		strTemp.Format("S/C#%d H/S#1에 도착한 Crate[%04d]의 작업상태가 맞지 않습니다.", m_nNum+1, m_pDoc->m_ConveyorTrackInfo[nTrackNum1].m_nLuggNum);
		m_pDoc->DisplayMessage(strTemp, FALSE);
		m_pDoc->m_pLog->Error(LOG_POS_SC, pJobItem1->m_nLuggNum, strTemp);
		return FALSE;
	}
	if (pJobItem1->GetStackerNum() != m_nNum)
	{
		CString strTemp;
		strTemp.Format("S/C#%d H/S#1에 도착한 Crate[%04d]의 S/C번호가 맞지 않습니다.", m_nNum+1, m_pDoc->m_ConveyorTrackInfo[nTrackNum1].m_nLuggNum);
		m_pDoc->DisplayMessage(strTemp, FALSE);
		m_pDoc->m_pLog->Error(LOG_POS_SC, pJobItem1->m_nLuggNum, strTemp);
		return FALSE;
	}
	
	int nTrackNum2 = CLib::GetScStoHSTrack(m_nNum, FALSE);
	if (!m_pDoc->m_ConveyorTrackInfo[nTrackNum2].m_bStoHomeStandReady)
	{
		nLuggNum2 = 0;
		strLocation2 = "";
		bUseFork = '0';
	}
	else
	{
		if (m_pDoc->m_ConveyorTrackInfo[nTrackNum2].m_nLuggNum == 0)
			return FALSE;

		pJobItem2 = m_pDoc->m_pJob->Find(m_pDoc->m_ConveyorTrackInfo[nTrackNum2].m_nLuggNum);
		if (pJobItem2 == NULL)
		{
			CString strTemp;
			strTemp.Format("S/C#%d H/S#2에 도착한 Crate[%04d]의 작업정보가 없습니다.", m_nNum+10, m_pDoc->m_ConveyorTrackInfo[nTrackNum2].m_nLuggNum);
			m_pDoc->DisplayMessage(strTemp, FALSE);
		    m_pDoc->m_pLog->Error(LOG_POS_SC, m_pDoc->m_ConveyorTrackInfo[nTrackNum2].m_nLuggNum, strTemp);
			return FALSE;
		}
		if (pJobItem2->m_nStatus != JOB_STA_CV_OPER_INVOKE)
		{
			CString strTemp;
			strTemp.Format("S/C#%d H/S#2에 도착한 Crate[%04d]의 작업상태가 맞지 않습니다.", m_nNum+10, m_pDoc->m_ConveyorTrackInfo[nTrackNum2].m_nLuggNum);
			m_pDoc->DisplayMessage(strTemp, FALSE);
		    m_pDoc->m_pLog->Error(LOG_POS_SC, pJobItem2->m_nLuggNum, strTemp);
			return FALSE;
		}
		if (pJobItem2->GetStackerNum() != m_nNum)
		{
			CString strTemp;
			strTemp.Format("S/C#%d H/S#2에 도착한 Crate[%04d]의 S/C번호가 맞지 않습니다.", m_nNum+10, m_pDoc->m_ConveyorTrackInfo[nTrackNum2].m_nLuggNum);
			m_pDoc->DisplayMessage(strTemp, FALSE);
		    m_pDoc->m_pLog->Error(LOG_POS_SC, pJobItem2->m_nLuggNum, strTemp);
			return FALSE;
		}

		int nBay = atoi(pJobItem2->m_strLocation.Mid(2,3));

//		if (nBay == BAY_1_CNT)
//		{
//			nLuggNum2 = 0;
//			strLocation2 = "";
//			bUseFork = '0';
//			pJobItem2 = NULL;
//		}
//		else
		{
		nLuggNum2 = pJobItem2->m_nLuggNum;
		strLocation2 = pJobItem2->m_strLocation;
		bUseFork = '1';
		}
	}

	if (Store(pJobItem1->m_nLuggNum, pJobItem1->m_strLocation, nLuggNum2, strLocation2, SC_DEFAULT_HS_STORE, bUseFork, 0) == TRUE)
	{
		SC_INFO->m_bInvoke = TRUE;
		SC_INFO->m_nInternalLuggNum = pJobItem1->m_nLuggNum;
		SC_INFO->m_bInternalJobType = SC_JOB_TYPE_STORE;
		time(&SC_INFO->m_tJobStart);
//		ScJobStart();	
	
		pJobItem1->m_bFirstFork = TRUE;
		pJobItem1->m_nStatus = JOB_STA_SC_OPER_INVOKE;

		if(pJobItem2 == NULL)
		{
			strLog.Format("StoreRoutine.. SC#%d 포크#1 입고지시 전송.. SINGLE 작업", m_nNum+1);
		}
		else
		{
			strLog.Format("StoreRoutine.. SC#%d 포크#1 입고지시 전송.. TWIN 작업.. 작번[포크#1:%d-포크#2:%d]",
			               m_nNum+1, pJobItem1->m_nLuggNum, pJobItem2->m_nLuggNum);
		}
		LOG->Job(LOG_POS_SC, pJobItem1->m_nLuggNum, strLog);

		if (pJobItem2 != NULL)
		{
			SC_INFO->m_bSecondInvoke = TRUE;
			SC_INFO->m_nSecondInternalLuggNum = pJobItem2->m_nLuggNum;
			SC_INFO->m_bSecondInternalJobType = SC_JOB_TYPE_STORE;
	
			pJobItem2->m_bFirstFork = FALSE;
			pJobItem2->m_nStatus = JOB_STA_SC_OPER_INVOKE;

			strLog.Format("StoreRoutine.. SC#%d 포크#2 입고지시 전송.. TWIN 작업.. 작번[포크#1:%d-포크#2:%d]",
				           m_nNum+1, pJobItem1->m_nLuggNum, pJobItem2->m_nLuggNum);
			LOG->Job(LOG_POS_SC, pJobItem2->m_nLuggNum, strLog);
		}

		SC_INFO->m_bModified = TRUE;
		SC_INFO->m_nPrevRtn = ROUTINE_STORE;
		SC_INFO->Backup();

		JOB->Backup();
		return TRUE;
	}
	else
	{
		strLog.Format("StoreRoutine.. SC#%d 입고지시 전송 실패!!!", m_nNum + 1); 
		m_pDoc->m_pLog->Error(LOG_POS_SC, pJobItem1->m_nLuggNum, strLog);
		return FALSE;	
	}

	return FALSE;
}

BOOL CScQ::RetrieveRoutine()
{
	char bUseFork;

	if (SC_INFO->m_bRetrieveSuspend)	return FALSE;

	int	nTrackNum = CLib::GetScRetHSTrack(m_nNum, TRUE);
	/*
	if ( m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_nLuggNum != 0  ||
		!m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_bRetHomeStandReady )
		return FALSE;
	*/
	if (!m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_bRetHomeStandReady)  //2018.10.14 요청으로 레디신호만 보기로 함 
		return FALSE;


	//if ( SC_INFO->m_bCvTransaction )	return FALSE;

	int nSecondLuggNum = 0;
	CString strSecondLoc = "";

	int	nSecondTrackNum = CLib::GetScRetHSTrack(m_nNum, FALSE);
	/*
	if ( TRACK_INFO[nSecondTrackNum].m_nLuggNum != 0 ||
		!TRACK_INFO[nSecondTrackNum].m_bRetHomeStandReady )
		return FALSE;
	*/

	if (!TRACK_INFO[nSecondTrackNum].m_bRetHomeStandReady)	//2018.10.14 요청으로 레디신호만 보기로 함 
		return FALSE;


	//if(m_nNum != 3) return FALSE;

	CJobItem* pJobItem = NULL;
	CJobItem* pSecondJobItem = NULL;
	
	BOOL bResult = JOB->FetchByJobRetrieve(m_nNum, &pJobItem, &pSecondJobItem);
	if (pJobItem == NULL && pSecondJobItem == NULL)		
		return FALSE;

	bUseFork = '0';
	int nLuggNum = pJobItem->m_nLuggNum;

	//@@ Batch별 출고 조정.
	//bResult = AdjustableRetrieve(pJobItem, pSecondJobItem);
	//if(!bResult) return FALSE;
	//@@

	//@@같은 출하 분류대로 여러개의 Batch로 출하지시가 내려왔을때 Batch가 높은게 나중에 출하한다...
	bResult = JOB->FetchLowBatchRetrive(pJobItem, m_nNum);
	if(!bResult) 
		return FALSE;

	BOOL bBatchResult = TRUE;

	if (pSecondJobItem != NULL)
	{
		bBatchResult = JOB->FetchLowBatchRetrive(pSecondJobItem,m_nNum);

		if(!bBatchResult) 
		{
			nSecondLuggNum = 0;
			strSecondLoc   = "";
			bUseFork = '0';
		}
		else
		{
			nSecondLuggNum = pSecondJobItem->m_nLuggNum;
			strSecondLoc   = pSecondJobItem->m_strLocation;
			bUseFork = '1';
		}
	}

/*	//@@상차시스템에 버퍼 FULL 이면 출고 안함.
	if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_201 && m_pDoc->m_b4groupCheck == TRUE)
	{
		if(m_pDoc->m_n4GroupInCount > m_pDoc->m_n4goupBuffCouter)  return FALSE;
	}
	else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_202 && m_pDoc->m_b5groupCheck == TRUE)
	{
		if(m_pDoc->m_n5GroupInCount > m_pDoc->m_n5goupBuffCouter)  return FALSE;
	}
	else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_203 && m_pDoc->m_b6groupCheck == TRUE)
	{
		if(m_pDoc->m_n6GroupInCount > m_pDoc->m_n6goupBuffCouter)  return FALSE;
	}

	if (pSecondJobItem != NULL)
	{
		if(pSecondJobItem->m_nDestPos == IMS_ECS_RET_STATION_201 && m_pDoc->m_b4groupCheck == TRUE)
		{
			if(m_pDoc->m_n4GroupInCount > 	m_pDoc->m_n4goupBuffCouter)  return FALSE;
		}
		else if(pSecondJobItem->m_nDestPos == IMS_ECS_RET_STATION_202 && m_pDoc->m_b5groupCheck == TRUE)
		{
			if(m_pDoc->m_n5GroupInCount > 	m_pDoc->m_n5goupBuffCouter)  return FALSE;
		}
		else if(pSecondJobItem->m_nDestPos == IMS_ECS_RET_STATION_203 && m_pDoc->m_b6groupCheck == TRUE)
		{
			if(m_pDoc->m_n6GroupInCount > 	m_pDoc->m_n6goupBuffCouter)  return FALSE;
		}
	}
	//@@
*/
	//@@ 단수가 낮은게 제일 늦게 출고.
/*	if(pJobItem->m_nLevelNo > 0 && pJobItem->m_nLevelNo != 6) 
	{
		bResult = JOB->FetchLowLevelRetrive(pJobItem);
		if(!bResult) return FALSE;
	}
*/
	if (pSecondJobItem != NULL)
	{
/*		if(pSecondJobItem->m_nLevelNo > 0 && pSecondJobItem->m_nLevelNo != 6) 
		{
			bResult = JOB->FetchLowLevelRetrive(pSecondJobItem);
			if(!bResult) 
			{
				nSecondLuggNum = 0;
				strSecondLoc   = "";
				bUseFork = '0';
			}
			else
			{
				//단수가 낮은 버켓은 하나씩 출고 되므로 이 루틴 까지 오리이까!
				if(!bBatchResult)
				{
					nSecondLuggNum = 0;
					strSecondLoc   = "";
					bUseFork = '0';
				}
				else
				{
					nSecondLuggNum = pSecondJobItem->m_nLuggNum;
					strSecondLoc   = pSecondJobItem->m_strLocation;
					bUseFork = '1';
				}
			}
		}
		else
*/
		{
			if(!bBatchResult)
			{
				nSecondLuggNum = 0;
				strSecondLoc   = "";
				bUseFork = '0';
			}
			else
			{
				nSecondLuggNum = pSecondJobItem->m_nLuggNum;
				strSecondLoc   = pSecondJobItem->m_strLocation;
				bUseFork = '1';
			}
		}
	}
	//@@

	CString strLog;

	if (Retrieve(pJobItem->m_nLuggNum, pJobItem->m_strLocation, nSecondLuggNum, strSecondLoc, 2, bUseFork, 0) == TRUE)
	{
		SC_INFO->m_bInvoke = TRUE;
		SC_INFO->m_nInternalLuggNum = pJobItem->m_nLuggNum;
		SC_INFO->m_bInternalJobType = SC_JOB_TYPE_RETRIEVE;
		time(&SC_INFO->m_tJobStart);
		//ScJobStart();

		pJobItem->m_bFirstFork = TRUE;
		pJobItem->m_nStatus = JOB_STA_SC_OPER_INVOKE;
	
		if(pSecondJobItem == NULL)
			strLog.Format("RetrieveRoutine.. SC#%d 포크#1 출고지시 전송.. SINGLE 작업", m_nNum+1);
		else
			strLog.Format("RetrieveRoutine.. SC#%d 포크#1 출고지시 전송.. TWIN 작업.. 작번[포크#1:%d-포크#2:%d]",
			               m_nNum+1, pJobItem->m_nLuggNum, pSecondJobItem->m_nLuggNum);
		LOG->Job(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);


		if (pSecondJobItem != NULL)
		{
/*			if(pSecondJobItem->m_nLevelNo > 0 && pSecondJobItem->m_nLevelNo != 6) 
			{
				if(nSecondLuggNum != 0 && strSecondLoc != "" && bUseFork == '1')
				{
					SC_INFO->m_bSecondInvoke = TRUE;
					SC_INFO->m_nSecondInternalLuggNum = pSecondJobItem->m_nLuggNum;
					SC_INFO->m_bSecondInternalJobType = SC_JOB_TYPE_RETRIEVE;

					pSecondJobItem->m_bFirstFork = FALSE;
					pSecondJobItem->m_nStatus = JOB_STA_SC_OPER_INVOKE;

					strLog.Format("RetrieveRoutine.. SC#%d 포크#2 출고지시 전송.. TWIN 작업.. 작번[포크#1:%d-포크#2:%d]",
			               m_nNum+1, pJobItem->m_nLuggNum, pSecondJobItem->m_nLuggNum);
					LOG->Job(LOG_POS_SC, pSecondJobItem->m_nLuggNum, strLog);
				}
			}
			else
*/
			{
				if(nSecondLuggNum != 0 && strSecondLoc != "" && bUseFork == '1')
				{
					SC_INFO->m_bSecondInvoke = TRUE;
					SC_INFO->m_nSecondInternalLuggNum = pSecondJobItem->m_nLuggNum;
					SC_INFO->m_bSecondInternalJobType = SC_JOB_TYPE_RETRIEVE;

					pSecondJobItem->m_bFirstFork = FALSE;
					pSecondJobItem->m_nStatus = JOB_STA_SC_OPER_INVOKE;

					strLog.Format("RetrieveRoutine.. SC#%d 포크#2 출고지시 전송.. TWIN 작업.. 작번[포크#1:%d-포크#2:%d]",
							m_nNum+1, pJobItem->m_nLuggNum, pSecondJobItem->m_nLuggNum);
					LOG->Job(LOG_POS_SC, pSecondJobItem->m_nLuggNum, strLog);
				}
			}
		}

		SC_INFO->m_bModified = TRUE;
		SC_INFO->m_nPrevRtn = ROUTINE_RETRIEVE;
		SC_INFO->Backup();
		
		JOB->Backup();
		return TRUE;
	}
	else
	{
		strLog.Format("RetrieveRoutine.. SC#%d 출고지시 전송 실패!!!", m_nNum + 1); 
		m_pDoc->m_pLog->Error(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);

		return FALSE;

	}

	return FALSE;
}

BOOL CScQ::RackToRackRoutine()
{
	char bUseFork;

	CJobItem* pJobItem = JOB->FetchByJobPattern(JOB_PATTERN_RTR, m_nNum);
	if (pJobItem == NULL)		return FALSE;

	int nSecondLuggNum = 0;
	CString strSecondLocFrom = "", strSecondLocTo = "";
	bUseFork = '0';

	CJobItem* pSecondJobItem = JOB->FetchByJobPattern(JOB_PATTERN_RTR, m_nNum, pJobItem->m_nLuggNum);
	if (pSecondJobItem != NULL)
	{
		nSecondLuggNum = pSecondJobItem->m_nLuggNum;
		strSecondLocFrom = pSecondJobItem->m_strLocation;
		strSecondLocTo = pSecondJobItem->m_strSecondLoc;
		bUseFork = '1';
	}

	CString strLog;
	if (RackToRack(pJobItem->m_nLuggNum, pJobItem->m_strLocation, pJobItem->m_strSecondLoc,
		           nSecondLuggNum, strSecondLocFrom, strSecondLocTo, bUseFork, 0) == TRUE)
	{
		SC_INFO->m_bInvoke = TRUE;
		SC_INFO->m_nInternalLuggNum = pJobItem->m_nLuggNum;
		SC_INFO->m_bInternalJobType = SC_JOB_TYPE_RACK_TO_RACK;
		time(&SC_INFO->m_tJobStart);
		
		pJobItem->m_bFirstFork = TRUE;
		pJobItem->m_nStatus = JOB_STA_SC_OPER_INVOKE;

		if(pSecondJobItem == NULL)
			strLog.Format("RackToRackRoutine.. SC#%d 포크#1 랙투랙 지시전송.. SINGLE 작업", m_nNum+1);
		else
			strLog.Format("RackToRackRoutine.. SC#%d 포크#1 랙투랙 지시전송.. TWIN 작업.. 작번[포크#1:%d-포크#2:%d]",
			               m_nNum+1, pJobItem->m_nLuggNum, pSecondJobItem->m_nLuggNum);
		LOG->Job(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);

		if (pSecondJobItem != NULL)
		{
			SC_INFO->m_bSecondInvoke = TRUE;
			SC_INFO->m_nSecondInternalLuggNum = pSecondJobItem->m_nLuggNum;
			SC_INFO->m_bSecondInternalJobType = SC_JOB_TYPE_RACK_TO_RACK;

			pSecondJobItem->m_bFirstFork = FALSE;
			pSecondJobItem->m_nStatus = JOB_STA_SC_OPER_INVOKE;

			strLog.Format("RackToRackRoutine.. SC#%d 포크#2 랙투랙 지시전송.. TWIN 작업.. 작번[포크#1:%d-포크#2:%d]",
			               m_nNum+1, pJobItem->m_nLuggNum, pSecondJobItem->m_nLuggNum);
			LOG->Job(LOG_POS_SC, pSecondJobItem->m_nLuggNum, strLog);
		}

		SC_INFO->m_bModified = TRUE;
		SC_INFO->m_nPrevRtn = ROUTINE_RACK_TO_RACK;
		SC_INFO->Backup();

		JOB->Backup();
		return TRUE;
	}

	return FALSE;
}

void CScQ::CompleteCheck()
{
	CString strLog;
	int nCount;
	static int nChk[SC_CNT] = {0,0,0,0,0,0};

	if ((m_pDoc->m_pStackerInfo[m_nNum]->m_ucStatus == SC_STA_WAIT || m_pDoc->m_pStackerInfo[m_nNum]->m_ucStatus == SC_STA_IDLE) &&
		 m_pDoc->m_pStackerInfo[m_nNum]->m_ucActive &&
		(m_pDoc->m_pStackerInfo[m_nNum]->m_ucTransaction == SC_TRN_COMPLETE_FORK1 ||
		 m_pDoc->m_pStackerInfo[m_nNum]->m_ucTransaction == SC_TRN_COMPLETE_FORK2 ||
		 m_pDoc->m_pStackerInfo[m_nNum]->m_ucTransaction == SC_TRN_COMPLETE_FORK12))
	{
/*		if ( (m_pDoc->m_pStackerInfo[m_nNum]->m_ucPrevStatus != SC_STA_ERROR && SC_INFO->m_ucPrevStatus != SC_STA_MOVE) &&
			m_pDoc->m_pStackerInfo[m_nNum]->m_nLuggNum == m_pDoc->m_pStackerInfo[m_nNum]->m_nInternalLuggNum)
		{
			if (nChk[m_nNum] == 0)
			{
				strLog.Format("CompleteCheck.. SC#%d SC가 동작하지 않고 작업완료 보고.. 이상..", m_nNum+1);
				LOG->Error(LOG_POS_SC, SC_INFO->m_nSecondInternalLuggNum, strLog);
				nChk[m_nNum] = 1;
			}
			return;
		}
*/
		nChk[m_nNum] = 0;
		SC_INFO->m_ucPrevStatus = SC_STA_IDLE;
		nCount = 0;

		if ( m_pDoc->m_pStackerInfo[m_nNum]->m_bInvoke &&	(m_pDoc->m_pStackerInfo[m_nNum]->m_ucStatus == SC_STA_WAIT || m_pDoc->m_pStackerInfo[m_nNum]->m_ucStatus == SC_STA_IDLE) &&
			 m_pDoc->m_pStackerInfo[m_nNum]->m_nLuggNum == m_pDoc->m_pStackerInfo[m_nNum]->m_nInternalLuggNum &&
			(m_pDoc->m_pStackerInfo[m_nNum]->m_ucTransaction == SC_TRN_COMPLETE_FORK1 || m_pDoc->m_pStackerInfo[m_nNum]->m_ucTransaction == SC_TRN_COMPLETE_FORK12))
		{
			SC_INFO->m_bInvoke = FALSE;

			CString strLog;

			CJobItem* pJobItem = JOB->Find(SC_INFO->m_nInternalLuggNum);
			if (pJobItem == NULL)
			{
				strLog.Format("CompleteCheck.. SC#%d 포크#1 작업번호를 찾을 수 없음..", m_nNum+1);
				LOG->Error(LOG_POS_SC, SC_INFO->m_nInternalLuggNum, strLog);
				return;
			}

			StatisticWorkTime(pJobItem);

			if ( SC_INFO->m_bInternalJobType == SC_JOB_TYPE_RETRIEVE )
			{
				strLog.Format("CompleteCheck.. SC#%d.. 포크#1 출고 작업완료..", m_nNum+1);
				LOG->Job(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);

				pJobItem->m_bFirstFork = TRUE;
				pJobItem->m_nStatus = JOB_STA_CV_OPER_REQUEST;

				JOB->Complete(SC_INFO->m_nInternalLuggNum, SC_JOB_TYPE_RETRIEVE);
				SC_INFO->m_bCvTransaction = TRUE;
				CV_ACTION(CV_3_PLC);

				SC_INFO->m_nInternalLuggNum = 0;
				SC_INFO->m_bModified = TRUE;
				SC_INFO->Backup();
				nCount++;
				//return;
			}
			else if ( m_pDoc->m_pStackerInfo[m_nNum]->m_bInternalJobType == SC_JOB_TYPE_STORE )
			{
				strLog.Format("CompleteCheck.. SC#%d.. 포크#1 입고 작업완료..", m_nNum+1);
				LOG->Job(LOG_POS_SC, SC_INFO->m_nInternalLuggNum, strLog);

				JOB->Complete(SC_INFO->m_nInternalLuggNum, SC_JOB_TYPE_STORE);
				Sleep(500);
				JOB->Backup();

				SC_INFO->m_nInternalLuggNum = 0;
				SC_INFO->m_bModified = TRUE;
				SC_INFO->Backup();
				nCount++;
			}
		}
	
		if ( SC_INFO->m_bSecondInvoke && (SC_INFO->m_ucStatus == SC_STA_WAIT || SC_INFO->m_ucStatus == SC_STA_IDLE) &&
			 SC_INFO->m_nSecondLuggNum == SC_INFO->m_nSecondInternalLuggNum &&
			(SC_INFO->m_ucTransaction == SC_TRN_COMPLETE_FORK2 || SC_INFO->m_ucTransaction == SC_TRN_COMPLETE_FORK12))
		{
			SC_INFO->m_bSecondInvoke = FALSE;

			CJobItem* pJobItem = JOB->Find(SC_INFO->m_nSecondInternalLuggNum);
			if (pJobItem == NULL)
			{
				strLog.Format("CompleteCheck.. SC#%d 포크#2 작업번호를 찾을 수 없음..", m_nNum+1);
				LOG->Error(LOG_POS_SC, SC_INFO->m_nSecondInternalLuggNum, strLog);
				return;
			}

			StatisticWorkTime(pJobItem);

			if ( SC_INFO->m_bSecondInternalJobType == SC_JOB_TYPE_RETRIEVE )
			{
				strLog.Format("CompleteCheck.. SC#%d.. 포크#2 출고 작업완료..", m_nNum+1);
				LOG->Job(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);

				pJobItem->m_bFirstFork = FALSE;
				pJobItem->m_nStatus = JOB_STA_CV_OPER_REQUEST;
				JOB->Complete(SC_INFO->m_nSecondInternalLuggNum, SC_JOB_TYPE_RETRIEVE);
				CV_ACTION(CV_3_PLC);

				SC_INFO->m_nSecondInternalLuggNum = 0;
				SC_INFO->m_bModified = TRUE;
				SC_INFO->Backup();
				nCount++;
				//return;
			}
			else if ( SC_INFO->m_bSecondInternalJobType == SC_JOB_TYPE_STORE )
			{

				strLog.Format("CompleteCheck.. SC#%d.. 포크#2 입고 작업완료..", m_nNum+1);
				LOG->Job(LOG_POS_SC, SC_INFO->m_nSecondInternalLuggNum, strLog);

				JOB->Complete(SC_INFO->m_nSecondInternalLuggNum, SC_JOB_TYPE_STORE);
				Sleep(500);
				JOB->Backup();

				SC_INFO->m_nSecondInternalLuggNum = 0;
				SC_INFO->m_bModified = TRUE;
				SC_INFO->Backup();
				nCount++;
			}
		}
//		if (nCount > 0)
//			ScJobAdd(nCount);
	}
}

BOOL CScQ::ErrorRoutine()
{
	CString strLog;
	char    bUseFork;

	//포크#1 이중입고
	if ( SC_INFO->m_bInvoke && SC_INFO->m_ucStatus == SC_STA_ERROR &&
		 SC_INFO->m_wErrCode == SC_ERR_CODE_DUAL_STORE )
	{
		CJobItem* pJobItem = JOB->FetchByStatus(JOB_STA_DUAL_STO_RETRY, m_nNum);
		if (pJobItem == NULL)
		{
			pJobItem = JOB->FetchByStatus(JOB_STA_DUAL_RTR_RETRY, m_nNum);
			if (pJobItem == NULL)	return FALSE;
		}

		CString strLocation = pJobItem->GetPattern() == JOB_PATTERN_RTR ? pJobItem->m_strSecondLoc : pJobItem->m_strLocation;

		int nSecondLuggNum = 0;
		CString strSecondLoc = "";
		bUseFork = '0';

		// 1. 포크#1, 포크#2 화물 있고 포크#1에 이중입고시 
		// 2. 포크#1, 화물 있고 포크#2 화물 없을때 포크#1에 이중입고시
		//    - 이런경우도 동일하게 아래처럼 포크#2의 작업지시도 함께 줘야 하는지 아니면 완료비트 보고
		//    - 포크#2의 작업은 안내려야 하는지 확인
		if ( SC_INFO->m_bSecondInvoke && SC_INFO->m_nSecondInternalLuggNum )
		{
			CJobItem* pSecondJobItem = JOB->Find(SC_INFO->m_nSecondInternalLuggNum);
			if (pSecondJobItem != NULL)
			{
				nSecondLuggNum = pSecondJobItem->m_nLuggNum;
				strSecondLoc = pSecondJobItem->m_strLocation;
				bUseFork = '1';
			}
		}

		if (Store(pJobItem->m_nLuggNum, strLocation, nSecondLuggNum, strSecondLoc, 1, bUseFork, 0) == TRUE)
		{
			SC_INFO->m_bInvoke = TRUE;
			SC_INFO->m_nInternalLuggNum = pJobItem->m_nLuggNum;
			pJobItem->m_nStatus = JOB_STA_SC_OPER_INVOKE;

			strLog.Format("ErrorRoutine.. SC#%d 포크#1 이중입고 재지정 전송..", m_nNum+1);
			LOG->Job(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);
		}
		else
		{
			strLog.Format("ErrorRoutine.. SC#%d 포크#1 이중입고 재지정 전송 실패..", m_nNum+1);
			LOG->Error(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);
			
			Sleep(3000);
			ReadStatus();
			if (SC_INFO->m_ucStatus != SC_STA_ERROR)
			{
				SC_INFO->m_bInvoke = TRUE;
				SC_INFO->m_nInternalLuggNum = pJobItem->m_nLuggNum;
				pJobItem->m_nStatus = JOB_STA_SC_OPER_INVOKE;

				strLog.Format("ErrorRoutine.. SC#%d 포크#1 이중입고 재지정 전송2..", m_nNum+1);
				LOG->Error(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);
			}
		}
	}

	//포크#2 이중입고
	if ( SC_INFO->m_bSecondInvoke && SC_INFO->m_ucStatus == SC_STA_ERROR &&
		 SC_INFO->m_wErrCode == SC_ERR_CODE_DUAL_SECOND_STORE )
	{
		CJobItem* pSecondJobItem = JOB->FetchByStatus(JOB_STA_DUAL_STO_RETRY, m_nNum);
		if (pSecondJobItem == NULL)
		{
			pSecondJobItem = JOB->FetchByStatus(JOB_STA_DUAL_RTR_RETRY, m_nNum);
			if (pSecondJobItem == NULL)	return FALSE;
		}

		CString strSecondLocation = pSecondJobItem->GetPattern() == JOB_PATTERN_RTR ? pSecondJobItem->m_strSecondLoc : pSecondJobItem->m_strLocation;

		int nLuggNum = 0;
		CString strLocation = "";
		bUseFork = '1';

		// 1. 포크#1, 포크#2 화물 있고 포크#2 먼저 작업 하다가 포크#2에 이중입고시 
		// 2. 포크#1, 화물 없고 포크#2 화물 있을때 포크#2에 이중입고시
		//    - 이런경우도 동일하게 아래처럼 포크#1의 작업지시도 함께 조야 하는지 아니면 완료비트 보고
		//    - 포크#1의 작업은 안내려야 하는지 확인
		if ( SC_INFO->m_bInvoke && SC_INFO->m_nInternalLuggNum )
		{
			CJobItem* pJobItem = JOB->Find(SC_INFO->m_nInternalLuggNum);
			if (pJobItem != NULL)
			{
				nLuggNum = pJobItem->m_nLuggNum;
				strLocation = pJobItem->m_strLocation;
			}
		}

		if (Store(nLuggNum, strLocation, pSecondJobItem->m_nLuggNum, strSecondLocation, 1, bUseFork, 0) == TRUE)
		{
			SC_INFO->m_bSecondInvoke = TRUE;
			SC_INFO->m_nSecondInternalLuggNum = pSecondJobItem->m_nLuggNum;
			pSecondJobItem->m_nStatus = JOB_STA_SC_OPER_INVOKE;

			strLog.Format("ErrorRoutine.. SC#%d 포크#2 이중입고 재지정 전송..", m_nNum+1);
			LOG->Job(LOG_POS_SC, pSecondJobItem->m_nLuggNum, strLog);
		}
		else
		{
			strLog.Format("ErrorRoutine.. SC#%d 포크#2 이중입고 재지정 전송 실패..", m_nNum+1);
			LOG->Error(LOG_POS_SC, pSecondJobItem->m_nLuggNum, strLog);

			Sleep(3000);
			ReadStatus();
			if (SC_INFO->m_ucStatus != SC_STA_ERROR)
			{
				SC_INFO->m_bSecondInvoke = TRUE;
				SC_INFO->m_nSecondInternalLuggNum = pSecondJobItem->m_nLuggNum;
				pSecondJobItem->m_nStatus = JOB_STA_SC_OPER_INVOKE;

				strLog.Format("ErrorRoutine.. SC#%d 포크#2 이중입고 재지정 전송2..", m_nNum+1);
				LOG->Error(LOG_POS_SC, pSecondJobItem->m_nLuggNum, strLog);
			}
		}
	}

	return TRUE;
}

void CScQ::ErrorCheck()
{	
	if (SC_INFO->m_ucStatus != SC_STA_ERROR)
	{
		SC_INFO->m_wPrevErrCode = 0;
		return;
	}

	if (SC_INFO->m_wPrevErrCode == SC_INFO->m_wErrCode)
		return;

	SC_INFO->m_wPrevErrCode = SC_INFO->m_wErrCode;
	if(SC_INFO->m_wErrCode == 0)	return;

	CString strLog;
	strLog.Format("ErrorCheck.. SC#%d 에러.. SC모드=[%s], 코드=[%d], 정보=[%s]", m_nNum+1, 
				   CLib::StackerModeToString(SC_INFO->m_ucMode),
				   SC_INFO->m_wErrCode,
				   CLib::GetStackerErrorInfo(SC_INFO->m_wErrCode));
	LOG->Error(LOG_POS_SC, LOG_SYSTEM, strLog);

	time(&SC_INFO->m_tErrorStart); m_bIsError=TRUE;
	m_pDoc->m_pStatistic->m_sSTC[m_nNum].nErrorSum ++;
	m_pDoc->m_pStatistic->RegistErrCode(m_nNum, SC_INFO->m_wErrCode);
//	ScErrorLog(1, SC_INFO->m_wErrCode);

	if (SC_INFO->m_nInternalLuggNum == 0 && SC_INFO->m_nSecondInternalLuggNum == 0)
		return;

	int nChk = 0;

	if ( SC_INFO->m_bInvoke )
	{
		if(SC_INFO->m_nInternalLuggNum == 0)		return;

		CJobItem* pJobItem = JOB->Find(SC_INFO->m_nInternalLuggNum);
		if (pJobItem == NULL)
		{
			strLog.Format("ErrorCheck.. SC#%d. 포크#1 이미 완료되었거나 삭제 되었슴.. 에러는 무시..", m_nNum+1);
			LOG->Error(LOG_POS_SC, SC_INFO->m_nInternalLuggNum, strLog);
		}

		CString strLocation;
		switch (SC_INFO->m_wErrCode)
		{
		case	SC_ERR_CODE_EMPTY_RETRIEVE:
			if (pJobItem == NULL)	break;
			if (pJobItem->GetPattern() == JOB_PATTERN_STO)
			{
				strLog.Format("ErrorCheck.. SC#%d 포크#1 입고중 공출고 에러 SC 로직에러 SC체크..", m_nNum+1);
				LOG->Error(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);
				return;
			}
			pJobItem->m_nStatus = JOB_STA_ERR_EMPTY_RET;

			strLog.Format("ErrorCheck.. SC#%d, 포크#1 공출고 에러..", m_nNum+1);
			LOG->Error(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);

			//공출고 에러는 다음 작업진행
			/*아니면 풀기
			SC_INFO->m_bInvoke = FALSE;
			SC_INFO->m_nPrevRtn = ROUTINE_RETRIEVE;
			SC_INFO->m_nInternalLuggNum = 0;
			SC_INFO->m_bModified = TRUE;
			*/
			
			//if ( pJobItem->IsOffLineJob() )		return;
			//JOB->InCreaseErrorCount();
			break;

		case	SC_ERR_CODE_DUAL_STORE:
			if (pJobItem == NULL)	break;
			if (pJobItem->GetPattern() == JOB_PATTERN_RET)
			{
				strLog.Format("ErrorCheck.. SC#%d 포크#1 출고중 이중입고 에러 SC 로직에러 SC체크..", m_nNum+1);
				LOG->Error(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);
				return;
			}
			pJobItem->m_nStatus = JOB_STA_ERR_DUAL_STO;
	
			strLog.Format("ErrorCheck.. SC#%d,  포크#1 이중입고 에러..", m_nNum+1);
			LOG->Error(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);

			//if ( pJobItem->IsOffLineJob() )		return;
			//JOB->InCreaseErrorCount();
			break;

		default:
			if (pJobItem == NULL)	break;
			strLog.Format("ErrorCheck.. SC#%d 포크#1 기타에러.. ErrKind[설비에러]", m_nNum+1);
			LOG->Event(LOG_POS_SC, SC_INFO->m_nInternalLuggNum, strLog);
			if (HOST != NULL) HOST->Error(DEVICE_CLASS_SC, m_nNum+1, MECHANIC_ERROR, SC_INFO->m_wErrCode);
			nChk = 1;
			break;
		}
	}

	if ( SC_INFO->m_bSecondInvoke )
	{
		if(SC_INFO->m_nSecondInternalLuggNum == 0)		return;

		CJobItem* pJobItem = JOB->Find(SC_INFO->m_nSecondInternalLuggNum);
		if (pJobItem == NULL)
		{
			strLog.Format("ErrorCheck.. SC#%d. 포크#2 이미 완료되었거나 삭제 되었슴.. 에러는 무시..", m_nNum+1);
			LOG->Error(LOG_POS_SC, SC_INFO->m_nSecondInternalLuggNum, strLog);
		}

		CString strLocation;
		switch (SC_INFO->m_wErrCode)
		{
		case	SC_ERR_CODE_EMPTY_SECOND_RETRIEVE:
			if (pJobItem == NULL)	break;
			if (pJobItem->GetPattern() == JOB_PATTERN_STO)
			{
				strLog.Format("ErrorCheck.. SC#%d 포크#1 입고중 공출고 에러 SC 로직에러 SC체크..", m_nNum+1);
				LOG->Error(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);
				return;
			}
			pJobItem->m_nStatus = JOB_STA_ERR_EMPTY_RET;

			strLog.Format("ErrorCheck.. SC#%d, 포크#2 공출고 에러..", m_nNum+1);
			LOG->Error(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);

			//공출고 에러는 다음 작업진행
			/*아니면 풀기
			SC_INFO->m_bSecondInvoke = FALSE;
			SC_INFO->m_nPrevRtn = ROUTINE_RETRIEVE;
			SC_INFO->m_nSecondInternalLuggNum = 0;
			SC_INFO->m_bModified = TRUE;
			*/
			
			//if ( pJobItem->IsOffLineJob() )		return;
			//JOB->InCreaseErrorCount();
			break;

		case	SC_ERR_CODE_DUAL_SECOND_STORE:
			if (pJobItem == NULL)	break;
			if (pJobItem->GetPattern() == JOB_PATTERN_RET)
			{
				strLog.Format("ErrorCheck.. SC#%d 포크#1 출고중 이중입고 에러 SC 로직에러 SC체크..", m_nNum+1);
				LOG->Error(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);
				return;
			}
			pJobItem->m_nStatus = JOB_STA_ERR_DUAL_STO;
	
			strLog.Format("ErrorCheck.. SC#%d,  포크#2 이중입고 에러..", m_nNum+1);
			LOG->Error(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);

			//if ( pJobItem->IsOffLineJob() )		return;
			//JOB->InCreaseErrorCount();
			break;

		default:
			if (pJobItem == NULL)	break;
			strLog.Format("ErrorCheck.. SC#%d 포크#2 기타에러.. ErrKind[설비에러]", m_nNum+1);
			LOG->Event(LOG_POS_SC, SC_INFO->m_nInternalLuggNum, strLog);
			if (nChk == 0)
			{
				if (HOST != NULL) HOST->Error(DEVICE_CLASS_SC, m_nNum+1, MECHANIC_ERROR, SC_INFO->m_wErrCode);
			}
			break;
		}
	}
}

int CScQ::CommandProc(SStackerMsg* pStackerMsg)
{
	CString strLog;

	switch (pStackerMsg->nCommand)
	{
	case	SC_CMD_COMPLETE:
		{
		strLog.Format("CSc::CommandProc.. %s 강제완료..", m_strDevice);
		LOG_EVENT(LOG_POS_SC, SC_INFO->m_nInternalLuggNum, strLog);

			SC_INFO->m_ucPrevStatus  = SC_STA_MOVE;
			SC_INFO->m_ucTransaction = SC_TRN_COMPLETE_FORK12;
			if (SC_INFO->m_bInvoke && SC_INFO->m_nLuggNum == 0)
				SC_INFO->m_nLuggNum = SC_INFO->m_nInternalLuggNum;
			if (SC_INFO->m_bSecondInvoke && SC_INFO->m_nSecondLuggNum == 0)
				SC_INFO->m_nSecondLuggNum = SC_INFO->m_nSecondInternalLuggNum;
			CompleteCheck();
		}
		break;

	case	SC_CMD_CANCEL:
		{
		// 16 포크#1,  32 포크#2,   64 포크#1, #2 ALL DELETE
		if(pStackerMsg->nDeleteFork == 16)
		{
			SC_INFO->m_bInvoke = FALSE;
			SC_INFO->m_nInternalLuggNum = 0;
		}
		else if(pStackerMsg->nDeleteFork == 32)
		{
			SC_INFO->m_bSecondInvoke = FALSE;
			SC_INFO->m_nSecondInternalLuggNum = 0;
		}
		else if(pStackerMsg->nDeleteFork == 64)
		{
			SC_INFO->m_bInvoke = FALSE;
			SC_INFO->m_bSecondInvoke = FALSE;
			SC_INFO->m_nInternalLuggNum = 0;
			SC_INFO->m_nSecondInternalLuggNum = 0;
		}

		Delete(pStackerMsg->nDeleteFork);
		strLog.Format("CSc::CommandProc.. %s 현작업 데이터 삭제", m_strDevice);
		LOG_EVENT(LOG_POS_SC, SC_INFO->m_nInternalLuggNum, strLog);
		}
		break;

	case	SC_CMD_CALL_TO_HOME:
		{
		if ( CallToHome() )
		{
			SC_INFO->m_bInvoke = TRUE;
			SC_INFO->m_nInternalLuggNum = 0;
			SC_INFO->m_bInternalJobType = SC_JOB_TYPE_CALL_TO_HOME;
			strLog.Format("CSc::CommandProc.. %s 홈복귀 지시..", m_strDevice);
		}
		else
			strLog.Format("CSc::CommandProc.. %s 홈복귀 지시 실패..", m_strDevice);
		LOG_EVENT(LOG_POS_SC, LOG_SYSTEM, strLog);
		}
		break;

	case	SC_CMD_NEW_LOCATION:
		{
		strLog.Format("CSc::CommandProc.. %s 이중입고 재지정 지시..", m_strDevice);
		LOG_EVENT(LOG_POS_SC, LOG_SYSTEM, strLog);
		ErrorRoutine();
		}
		break;
	case	SC_CMD_ERROR_RESET:
		{
		LOG->Event(LOG_POS_SC, LOG_SYSTEM, "CommandProc.. 에러 Reset..");
		Reset();
		}
		break;
	case	SC_CMD_ACTIVE:
		{
		LOG->Event(LOG_POS_SC, LOG_SYSTEM, "CommandProc.. Active..");
		Active();
		}
		break;
	case	SC_CMD_ESTOP:
		{
		LOG->Event(LOG_POS_SC, LOG_SYSTEM, "CommandProc.. 비상정지..");
			//Estop();
			Stop();
		}
		break;
	case	SC_CMD_PAUSE:
		{
		LOG->Event(LOG_POS_SC, LOG_SYSTEM, "CommandProc.. 정지..");
		Pause();
		}
		break;
	}

	SC_INFO->m_bModified = TRUE;
	SC_INFO->Backup();
	
	return TRUE;
}


int CScQ::Store(int nLuggNum1, CString strLocation1, int nLuggNum2, CString strLocation2, int nHsNum, char bUseFork, int nSize)
{
	BYTE	TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));
	int nUseFork;

	TxBuff[0] = 1;									// D171 - Store - DualStore

	if(nLuggNum1 != 0)
	{
		TxBuff[2] = nLuggNum1 & 0xFF;				// D172 LOW 
		TxBuff[3] = (nLuggNum1 >> 8) & 0xFF;		// D172 HIGH

		TxBuff[10] = (BYTE)nHsNum;					// D176 Start Home Stand  LOW

		TxBuff[12] = GetSide(strLocation1);			// D177 Bank   LOW
		TxBuff[14] = GetBay(strLocation1);			// D178 Bay    LOW
		TxBuff[16] = GetLevel(strLocation1);		// D179 Level  LOW
	}

	switch(bUseFork)
	{
	case	'0':
		nUseFork = 0;
		break;
	case	'1':
		nUseFork = 1;
		break;
	case	'2':
		nUseFork = 2;
		break;
	}

	TxBuff[20] = nUseFork;							// D181 (0 - USE FORK#1) (1 - USE FORK#1, #2) (2 - USE FORK#2) --- LOW

	if (nLuggNum2 != 0)
	{
		TxBuff[22] = nLuggNum2 & 0xFF;				// D182 LOW 
		TxBuff[23] = (nLuggNum2 >> 8) & 0xFF;		// D182 HIGH

	    TxBuff[30] = (BYTE)nHsNum;					// D186 Start Home Stand  LOW

		TxBuff[32] = GetSide(strLocation2);			// D187 Bank   LOW
		TxBuff[34] = GetBay(strLocation2);			// D188 Bay    LOW
		TxBuff[36] = GetLevel(strLocation2);		// D189 Level  LOW
	}

	TxBuff[40] = 1;									// D191 WRITE COMPLETE DEFAULT SETTING  -HIGH
//	TxBuff[42] = nSize;						        // D192 Gen   - HIGH
	TxBuff[42] = (BYTE)nSize;						// D192 Gen   - HIGH

	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  171, 22);

}

int CScQ::Retrieve(int nLuggNum1, CString strLocation1, int nLuggNum2, CString strLocation2, int nHsNum, char bUseFork, int nSize)
{
	BYTE	TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));
	int nUseFork;

	TxBuff[0] = 2;									// D171 - Retrieve

	if(nLuggNum1 != 0)
	{
		TxBuff[2] = nLuggNum1 & 0xFF;				// D172 LOW 
		TxBuff[3] = (nLuggNum1 >> 8) & 0xFF;		// D172 HIGH

		TxBuff[4] = GetSide(strLocation1);			// D173 Bank   LOW
		TxBuff[6] = GetBay(strLocation1);			// D174 Bay    LOW
		TxBuff[8] = GetLevel(strLocation1);			// D175 Level  LOW

		TxBuff[18] = (BYTE)nHsNum;					// D176 Dest Home Stand  LOW
	}

	switch(bUseFork)
	{
	case	'0':
		nUseFork = 0;
		break;
	case	'1':
		nUseFork = 1;
		break;
	case	'2':
		nUseFork = 2;
		break;
	}

	TxBuff[20] = nUseFork;							// D181 (0 - USE FORK#1) (1 - USE FORK#1, #2) (2 - USE FORK#2) --- LO

	if (nLuggNum2 != 0)
	{
		TxBuff[22] = nLuggNum2 & 0xFF;				// D182 LOW 
		TxBuff[23] = (nLuggNum2 >> 8) & 0xFF;		// D182 HIGH

		TxBuff[24] = GetSide(strLocation2);			// D183 Bank   LOW
		TxBuff[26] = GetBay(strLocation2);			// D184 Bay    LOW
		TxBuff[28] = GetLevel(strLocation2);		// D185 Level  LOW

	    TxBuff[38] = (BYTE)nHsNum;					// D190 Dest Home Stand  LOW
	}

	TxBuff[40] = 1;									// D191 WRITE COMPLETE DEFAULT SETTING  -LOW
//	TxBuff[42] = nSize;						        // D192 Gen   - LOW
	TxBuff[42] = (BYTE)nSize;						// D192 Gen   - LOW

	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  171, 22);
}

int CScQ::HsToHs(int nLuggNum1, int nLuggNum2, int nHsNumFrom, int nHsNumTo, char bUseFork, int nSize)
{
	BYTE	TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));
	int nUseFork;

	TxBuff[0] = 3;								    // D171 - Store - DualStore

	if(nLuggNum1 != 0)
	{
		TxBuff[2] = nLuggNum1 & 0xFF;				// D172 LOW 
		TxBuff[3] = (nLuggNum1 >> 8) & 0xFF;		// D172 HIGH

		TxBuff[10] = (BYTE)nHsNumFrom;				// D176 Start Home Stand  LOW
		TxBuff[18] = (BYTE)nHsNumTo;				// D176 Dest Home Stand  LOW
	}

	switch(bUseFork)
	{
	case	'0':
		nUseFork = 0;
		break;
	case	'1':
		nUseFork = 1;
		break;
	case	'2':
		nUseFork = 2;
		break;
	}

	TxBuff[20] = nUseFork;							// D181 (0 - USE FORK#1) (1 - USE FORK#1, #2) (2 - USE FORK#2) --- LO

	if (nLuggNum2 != 0)
	{
		TxBuff[22] = nLuggNum2 & 0xFF;				// D182 LOW 
		TxBuff[23] = (nLuggNum2 >> 8) & 0xFF;		// D182 HIGH

		TxBuff[30] = (BYTE)nHsNumFrom;				// D186 Start Home Stand  LOW
		TxBuff[38] = (BYTE)nHsNumTo;				// D190 Dest Home Stand  LOW
	}

	TxBuff[40] = 1;									// D191 WRITE COMPLETE DEFAULT SETTING  -LOW
//	TxBuff[42] = nSize;						        // D192 Gen   - LOW
	TxBuff[42] = (BYTE)nSize;						// D192 Gen   - LOW
	
	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  171, 22);
}

int CScQ::RackToRack(int nLuggNum1, CString strLocFrom1, CString strLocTo1, int nLuggNum2, CString strLocFrom2, CString strLocTo2, char bUseFork, int nSize)
{
	BYTE	TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));
	int nUseFork;

	TxBuff[0] = 4;                             // D171 - Rack To Rack

	if(nLuggNum1 != 0)
	{
		TxBuff[2] = nLuggNum1 & 0xFF;		       // D172 LOW 
		TxBuff[3] = (nLuggNum1 >> 8) & 0xFF;       // D172 HIGH

		TxBuff[4] = GetSide(strLocFrom1);          // D173 Bank   LOW
		TxBuff[6] = GetBay(strLocFrom1);           // D174 Bay    LOW
		TxBuff[8] = GetLevel(strLocFrom1);         // D175 Level  LOW

		TxBuff[12] = GetSide(strLocTo1);           // D177 Bank   LOW
		TxBuff[14] = GetBay(strLocTo1);            // D178 Bay    LOW
		TxBuff[16] = GetLevel(strLocTo1);		   // D179 Level  LOW
	}

	switch(bUseFork)
	{
	case	'0':
		nUseFork = 0;
		break;
	case	'1':
		nUseFork = 1;
		break;
	case	'2':
		nUseFork = 2;
		break;
	}

	TxBuff[20] = nUseFork;						  // D181 (0 - USE FORK#1) (1 - USE FORK#1, #2) (2 - USE FORK#2) --- LO

	if (nLuggNum2 != 0)
	{
		TxBuff[22] = nLuggNum2 & 0xFF;			  // D182 LOW 
		TxBuff[23] = (nLuggNum2 >> 8) & 0xFF;     // D182 HIGH

		TxBuff[24] = GetSide(strLocFrom2);        // D183 Bank   LOW
		TxBuff[26] = GetBay(strLocFrom2);         // D184 Bay    LOW
		TxBuff[28] = GetLevel(strLocFrom2);       // D185 Level  LOW

		TxBuff[32] = GetSide(strLocTo2);          // D187 Bank   LOW
		TxBuff[34] = GetBay(strLocTo2);           // D188 Bay    LOW
		TxBuff[36] = GetLevel(strLocTo2);         // D189 Level  LOW
	}

	TxBuff[40] = 1;						          // D191 WRITE COMPLETE DEFAULT SETTING  -LOW
//	TxBuff[42] = nSize;						      // D192 Gen   - LOW
	TxBuff[42] = (BYTE)nSize;                     // D192 Gen   - LOW

	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  171, 22);
}

int CScQ::CallToHome()
{
	BYTE	TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));

	TxBuff[0] = 5;								// D171 - CallToHome
	TxBuff[40] = 1;								// D191 WRITE COMPLETE DEFAULT SETTING  -LOW

	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  171, 21);
}

int CScQ::Active()
{
	BYTE	TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));


	TxBuff[0] = 2;    
//	TxBuff[0] = '1';  
	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  199, 1);
}

int CScQ::Stop()								// SLOW STOP        지상반 데이터 유지
{
	BYTE	TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));

//	TxBuff[0] = 4; 
	TxBuff[0] = 1;  
	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  199, 1);
}

int CScQ::Pause()								// SLOW STOP        지상반 데이터 유지
{
	BYTE	TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));
	
	//	TxBuff[0] = 4; 
	TxBuff[0] = 4;  
	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  199, 1);
}


int CScQ::Reset()							// ERROR RESET
{
	BYTE	TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));

	TxBuff[0] = 8;                     
	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  199, 1);
}

int CScQ::Delete(BOOL bFirst)				// DATA DELETE
{
	BYTE	TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));

//  TxBuff[0] = 1;
	TxBuff[0] = bFirst;							// 16 포크#1,  32 포크#2,   64 포크#1, #2 ALL DELETE
	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  199, 1);
}

int CScQ::RcMode(BOOL bOnLine)				// 지상반
{
	BYTE	TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));

	TxBuff[0] = bOnLine ? 128 : 256;            // 64 : ON-LINE 128 : OFF LINE
	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  199, 1);
}

BOOL CScQ::IsInvoke()
{
	if( SC_INFO->m_bInvoke || SC_INFO->m_bSecondInvoke)
		return TRUE;
	return FALSE;
}

BYTE CScQ::GetBank(CString strLocation)
{
	return atoi(strLocation.Mid(0, 2));
}

BYTE CScQ::GetSide(CString strLocation)
{
	return ((atoi(strLocation.Mid(0, 2)) + 1) % 2) + 1;
}

BYTE CScQ::GetBay(CString strLocation)
{
	return atoi(strLocation.Mid(2, 3));
}

BYTE CScQ::GetLevel(CString strLocation)
{
	return atoi(strLocation.Mid(5, 2));
}


void CScQ::StatisticWorkTime(CJobItem *pJobItem)
{
	if(pJobItem == NULL)	return;

	if ( pJobItem->IsManualJob() )
	{
		time(&m_tJobEnd);
		time_t tLapsTime = (time_t) difftime(m_tJobEnd, m_tJobStart);
		STATISTIC->m_sSTC[m_nNum].tOfflineWorkTime += tLapsTime;
		STATISTIC->m_sSTC[m_nNum].nOfflineJobSum ++;
	}
	else
	{
		time(&m_tJobEnd);
		time_t tLapsTime = (time_t) difftime(m_tJobEnd, m_tJobStart);
		STATISTIC->m_sSTC[m_nNum].tOnlineWorkTime += tLapsTime;
		STATISTIC->m_sSTC[m_nNum].nOnlineJobSum ++;
	}
}

void CScQ::StatisticTroubleTime()
{

	if( m_bIsError && SC_INFO->m_ucStatus != SC_STA_ERROR && SC_INFO->m_nInternalLuggNum != 0)
	{
		time(&m_tErrorEnd);
		if(SC_INFO->m_nInternalLuggNum >= 9000)
		{
			time_t tLapsTime = (time_t) difftime(m_tErrorEnd, m_tErrorStart);
			STATISTIC->m_sSTC[m_nNum].tOfflineTroubleTime += tLapsTime;
			m_bIsError = FALSE;
		}
		else
		{
			time_t tLapsTime = (time_t) difftime(m_tErrorEnd, m_tErrorStart);
			STATISTIC->m_sSTC[m_nNum].tOnlineTroubleTime += tLapsTime;
			m_bIsError = FALSE;
		}

		STATISTIC->Backup();
	}
}

