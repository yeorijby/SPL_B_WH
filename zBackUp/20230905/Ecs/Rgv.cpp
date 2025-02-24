
// Rgv.cpp : implementation of the CRgv class
//

#include "stdafx.h"
#include "Ecs.h"

#include "Rgv.h"
#include "Conveyor.h"

#include "Lib.h"

#define RGV_INFO		m_pRgvInfo	
#define	TRACK_INFO		m_pConveyorTrackInfo

CRgv::CRgv(int nNum, CEcsDoc* pDoc)
{ 
	m_nNum = nNum;
	m_pDoc = pDoc;
	m_strDevice = m_pDoc->m_pConfig->GetRgvDeviceName(nNum);

	m_pRgvInfo     = m_pDoc->m_pRgvInfo[nNum];
	m_pConveyorTrackInfo = m_pDoc->m_ConveyorTrackInfo;

	m_nCount = 0;

	m_pDoc->m_RgvThreadInfo[nNum].m_hCommDev = m_hCommDev;
}

int CRgv::ReadStatus()
{
	int nReadCnt=0;

	BYTE RxBuff[256];
	memset(RxBuff, NULL, sizeof(RxBuff));
	
	if ( Read(RxBuff, 100, 15, 'D', &nReadCnt) != TRUE) 
	{
		//if (RGV_INFO->m_wPrevErrCode == RGV_INFO->m_wErrCode)
		//	return FALSE;

		if (++m_nCount >= 5)
		{
			RGV_INFO->m_wErrCode = RGV_ERR_CODE_COMM_ERROR;
			RGV_INFO->m_ucStatus = RGV_STA_ERROR;
			RGV_INFO->m_bModified = TRUE;
		}
		return FALSE;
	}
	m_nCount = 0;

    BYTE ucMode          = RxBuff[8];  // '1' 자동 '2' 수동
    BYTE ucProdLoad      = RxBuff[6];  // '1' = 0x31 
    BYTE ucStatus        = RxBuff[12]; // '1': 대기중 '2': 동작중 '4': 에러

	BYTE ucHorizontalPos = CLib::HexStrToBYTE(RxBuff+15);
	BYTE ucFirstForkPos  = RxBuff[24];
    WORD wErrCode        = CLib::HexStrToWORD(RxBuff+25);
	BYTE ucActive		 = RxBuff[44];
	BYTE ucTransaction	 = RxBuff[48];

    BYTE ucJobType       = RxBuff[52];
    WORD wLuggNum        = CLib::HexStrToWORD(RxBuff+53);

	BYTE ucStartPos      = CLib::HexStrToBYTE(RxBuff+59);
	BYTE ucDestPos       = CLib::HexStrToBYTE(RxBuff+63);

	RGV_INFO->m_ucStartPos = ucStartPos;
	RGV_INFO->m_ucDestPos = ucDestPos;

	if (ucMode != RGV_INFO->m_ucMode)
	{
		RGV_INFO->m_ucMode = ucMode;            //자동 수동
		RGV_INFO->m_bModified = TRUE;
	}

	if (ucStatus != RGV_INFO->m_ucStatus)       //대기 이동 에러
	{
		RGV_INFO->m_ucStatus = ucStatus;
		RGV_INFO->m_bModified = TRUE;
	}

	if (ucProdLoad != RGV_INFO->m_ucProdLoad)
	{
		RGV_INFO->m_ucProdLoad = ucProdLoad;
		RGV_INFO->m_bModified = TRUE;
	}

	if (ucActive != RGV_INFO->m_ucActive)       //0:STOP 1:Active
	{
		RGV_INFO->m_ucActive = ucActive;
		RGV_INFO->m_bModified = TRUE;
	}

	if (wErrCode != RGV_INFO->m_wErrCode)
	{
		RGV_INFO->m_wErrCode = wErrCode;
		RGV_INFO->m_bModified = TRUE;
	}

	if (ucHorizontalPos != RGV_INFO->m_ucHorizontalPos)
	{
		RGV_INFO->m_ucHorizontalPos = ucHorizontalPos;
		RGV_INFO->m_bModified = TRUE;
	}

	if (wLuggNum != RGV_INFO->m_nLuggNum)
	{
		RGV_INFO->m_nLuggNum = wLuggNum;
		RGV_INFO->m_bModified = TRUE;
	}

	if (ucJobType != RGV_INFO->m_ucJobType)
	{
		RGV_INFO->m_ucJobType = ucJobType;
		RGV_INFO->m_bModified = TRUE;
	}

	if (ucTransaction != RGV_INFO->m_ucTransaction)
	{
		RGV_INFO->m_ucTransaction = ucTransaction;
		RGV_INFO->m_bModified = TRUE;
	}

	StatisticTroubleTime();

	return TRUE;
}
/*
void CRgv::InvokeCheck()
{

	if (RGV_INFO->m_bInvoke || RGV_INFO->m_ucMode != RGV_MODE_AUTO || RGV_INFO->m_ucActive != RGV_ACTIVE ||
		RGV_INFO->m_ucStatus == RGV_STA_MOVE || RGV_INFO->m_ucStatus == RGV_STA_ERROR)
		return;

	switch ( m_nNum )
	{
	case	RGV_1_NUM:
		switch (RGV_INFO->m_nNextRtn)
		{
		case	ROUTINE_STORE:
			if (RetrieveRoutine())
				break;

			if (StoreRoutine())
				break;

			if (StoreSiteRoutine())
				break;
			break;

		case	ROUTINE_SITE_STORE:
			if (StoreRoutine())
				break;

			if (StoreSiteRoutine())
				break;

			if (RetrieveRoutine())
				break;
			break;

		case	ROUTINE_RETRIEVE:
			if (StoreSiteRoutine())
				break;

			if (RetrieveRoutine())
				break;

			if (StoreRoutine())
				break;
			break;
		}
		break;
	case	RGV_2_NUM:
		switch (RGV_INFO->m_nNextRtn)
		{
		case	ROUTINE_STORE:
			if (RetrieveSiteRoutine())
				break;
			break;
		case	ROUTINE_SITE_RETRIEVE:
			if (RetrieveSiteRoutine())
				break;
			break;
		}
		break;
	}
}
*/

void CRgv::InvokeCheck()
{

	if (RGV_INFO->m_bInvoke || RGV_INFO->m_ucMode != RGV_MODE_AUTO || RGV_INFO->m_ucActive != RGV_ACTIVE ||
		RGV_INFO->m_ucStatus == RGV_STA_MOVE || RGV_INFO->m_ucStatus == RGV_STA_ERROR)
		return;

	switch ( m_nNum )
	{
	case	RGV_1_NUM:
		switch (RGV_INFO->m_nNextRtn)
		{
		case	ROUTINE_STORE:
			if (RetrieveRoutine())
				break;

		case	ROUTINE_SITE_STORE:
			if (RetrieveRoutine())
				break;
			break;

		case	ROUTINE_RETRIEVE:
			if (RetrieveRoutine())
				break;
			break;
		}
		break;
	case	RGV_2_NUM:
		switch (RGV_INFO->m_nNextRtn)
		{
		case	ROUTINE_STORE:
			if (RetrieveSiteRoutine())
				break;
			break;
		case	ROUTINE_SITE_RETRIEVE:
			if (RetrieveSiteRoutine())
				break;
			break;
		}
		break;
	}
}

BOOL CRgv::StoreRoutine()
{

	int nRank = RGV_INFO->m_nStoNextRtn;


	int nStoCnt = 1;

	for( int i=0; i<nStoCnt; i++)
	{
		if ( StoreRoutine(nRank) )		
		{
			nRank++;
			if (nRank >= nStoCnt)
				nRank = 0;

			RGV_INFO->m_nStoNextRtn = nRank;
			return TRUE;
		}
		nRank++;
		if (nRank >= nStoCnt)
			nRank = 0;
	}

	RGV_INFO->m_nStoNextRtn = nRank;
	//RGV_INFO->m_nStoNextRtn++;

	return FALSE;
}

BOOL CRgv::StoreRoutine(int nRank)
{
	int nDestTrack = 0, nScNum = 0;

	if (RGV_INFO->m_bStoreSuspend)	
		return FALSE;

	int nTrackNum = 702-1;

	if ( TRACK_INFO[nTrackNum].m_nLuggNum ==  0 ||
		!TRACK_INFO[nTrackNum].m_bStoHomeStandReady )
		return FALSE;

	CString strLog;
	CMoveJobItem *pMoveJobItem = MOVEJOB->Find(TRACK_INFO[nTrackNum].m_nLuggNum);
	if (pMoveJobItem == NULL)
	{
		strLog.Format("StoreRoutine.. %s 출발HS[CV#%d]에 도착한 작업번호를 찾을 수 없슴..", m_strDevice, nTrackNum+1);
		m_pDoc->DisplayMessage(strLog, FALSE);
		return FALSE;
	} 

	if(pMoveJobItem->GetPattern() != JOB_PATTERN_MOVE ) 
		return FALSE;

    if(pMoveJobItem->m_nStatus != JOB_STA_MOVE_CV_OPER_INVOKE) 
		return FALSE;

	nDestTrack = CLib::GetRgvStoDestHSTrack(m_nNum, pMoveJobItem->m_nLineNum);

	//내려놓을 자리를 순간적으로 체크하므로 RTV 완료 상태가 있으면 이동지시 안한다.
	CMoveJobItem *pCheckJobItem = MOVEJOB->FetchRgvJobByDestTrack(nDestTrack);
	if ( pCheckJobItem != NULL )		
		return FALSE;

	if (!TRACK_INFO[nDestTrack].m_bRetHomeStandReady)
	{
		if (TRACK_INFO[nDestTrack].m_nLuggNum ==  0)
			return FALSE;
	}

	if (TRACK_INFO[nDestTrack].m_bRetHomeStandReady)
	{
		if (TRACK_INFO[nDestTrack].m_nLuggNum !=  0)
			return FALSE;
	}

	if ( TRACK_INFO[nDestTrack].m_nLuggNum !=  0 || TRACK_INFO[nDestTrack].m_bStoHomeStandReady)
	{
		int nLuggNum1 = TRACK_INFO[nDestTrack].m_nLuggNum;

		CMoveJobItem *pDestJobItem1 = MOVEJOB->Find(nLuggNum1);
		if (pDestJobItem1 == NULL)
			return FALSE;

		nDestTrack = 746-1;

		if (TRACK_INFO[nDestTrack].m_bStoHomeStandReady )
			return FALSE;

		if (TRACK_INFO[nDestTrack].m_nLuggNum ==  0 && TRACK_INFO[nDestTrack].m_bRetHomeStandReady == FALSE)
			return FALSE;

		if (!TRACK_INFO[nDestTrack].m_bRetHomeStandReady )
			return FALSE;

		//702 보다 버퍼구간을 먼저 하기 위해...
		if (TRACK_INFO[nDestTrack].m_bRetHomeStandReady)
		{
			if (TRACK_INFO[nDestTrack].m_nLuggNum !=  0)
				return FALSE;
		}

		int nLuggNum2 = TRACK_INFO[nDestTrack].m_nLuggNum; 


		CMoveJobItem *pDestJobItem2 = MOVEJOB->Find(nLuggNum2);
		if (pDestJobItem2 != NULL)
		{
			if(pMoveJobItem->m_nLineNum != pDestJobItem2->m_nLineNum)
				return FALSE;

			if (pMoveJobItem->m_nLastPallet == 1)
				return FALSE;
		} 

		if (pMoveJobItem->m_nLastPallet == 1 && nLuggNum2 != 0)
				return FALSE;

	}
	else if ( (TRACK_INFO[nDestTrack].m_nLuggNum ==  0 || TRACK_INFO[nDestTrack].m_bRetHomeStandReady) && pMoveJobItem->m_nLastPallet == 1)
	{
		 nDestTrack = 746-1;

		if ( TRACK_INFO[nDestTrack].m_nLuggNum ==  0 ||
			 TRACK_INFO[nDestTrack].m_bRetHomeStandReady )
		{
			nDestTrack = CLib::GetRgvRetDestHSTrack(pMoveJobItem->m_nLineNum, m_nNum);
			
			if ( TRACK_INFO[nDestTrack].m_nLuggNum !=  0 ||
				!m_pDoc->m_ConveyorTrackInfo[nDestTrack].m_bRetHomeStandReady )
				return FALSE;
		}

		if ( TRACK_INFO[nDestTrack].m_nLuggNum !=  0 ||
			 TRACK_INFO[nDestTrack].m_bStoHomeStandReady )
		{

			CMoveJobItem *pDestJobItem = MOVEJOB->Find(TRACK_INFO[nDestTrack].m_nLuggNum);
			if (pDestJobItem != NULL)
			{
				if(pMoveJobItem->m_nLineNum != pDestJobItem->m_nLineNum)
				{
					nDestTrack = CLib::GetRgvRetDestHSTrack(pMoveJobItem->m_nLineNum, m_nNum);
			
					if ( TRACK_INFO[nDestTrack].m_nLuggNum !=  0 ||
						!m_pDoc->m_ConveyorTrackInfo[nDestTrack].m_bRetHomeStandReady )
						return FALSE;
				}

				if(pMoveJobItem->m_nLineNum == pDestJobItem->m_nLineNum)
						return FALSE;
			} 

//			nDestTrack = CLib::GetRgvRetDestHSTrack(pMoveJobItem->m_nLineNum, m_nNum);
//			
//			if ( TRACK_INFO[nDestTrack].m_nLuggNum !=  0 ||
//				!m_pDoc->m_ConveyorTrackInfo[nDestTrack].m_bRetHomeStandReady )
//				return FALSE;

		}
	}


	int nStartPos = GetRgvPosPerTrack(nTrackNum+1);
	int nDestPos  = GetRgvPosPerTrack(nDestTrack+1);

	if (HsToHs(pMoveJobItem->m_nLuggNum, nStartPos, nDestPos))
	{
		RGV_INFO->m_bInvoke = TRUE;
		RGV_INFO->m_nNextRtn = ROUTINE_STORE;

		RGV_INFO->m_nStartTrack = nTrackNum;
		RGV_INFO->m_nDestTrack = nDestTrack;

		RGV_INFO->m_nInternalLuggNum = pMoveJobItem->m_nLuggNum;

		if(pMoveJobItem->GetPattern() == JOB_PATTERN_MOVE) RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_SITE_TO_SITE;
		else if(pMoveJobItem->GetPattern() == JOB_PATTERN_STO) RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_STORE;
		else RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_RETRIEVE;

		time(&RGV_INFO->m_tJobStart);

		RGV_INFO->m_bModified = TRUE;
		RGV_INFO->Backup();

		pMoveJobItem->m_nStatus = JOB_STA_MOVE_RGV_OPER_INVOKE;
		MOVEJOB->Backup();

		strLog.Format("StoreRoutine.. %s 이동지시[CV#%d-CV#%d] 전송..", m_strDevice, nTrackNum+1, nDestTrack+1);
		LOG_JOB(LOG_POS_RGV, pMoveJobItem->m_nLuggNum, strLog);
		return TRUE;
	}
	else
	{
		strLog.Format("StoreRoutine.. %s 이동지시[CV#%d-CV#%d] 실패..[%s]", m_strDevice, nTrackNum+1, nDestTrack+1, m_strErrorMsg);
		LOG_ERROR(LOG_POS_RGV, pMoveJobItem->m_nLuggNum, strLog);
	}

	return FALSE;
}


BOOL CRgv::StoreSiteRoutine()
{

	int nRank = RGV_INFO->m_nStoSiteNextRtn;


	int nStoSiteCnt = 10;

	for( int i=0; i<nStoSiteCnt; i++)
	{
		if ( StoreSiteRoutine(nRank) )		
		{
			nRank++;
			if (nRank >= nStoSiteCnt)
				nRank = 0;

			RGV_INFO->m_nStoSiteNextRtn = nRank;
			return TRUE;
		}
		nRank++;
		if (nRank >= nStoSiteCnt)
			nRank = 0;
	}

	RGV_INFO->m_nStoSiteNextRtn = nRank;

	return FALSE;
}

BOOL CRgv::StoreSiteRoutine(int nRank)
{
	int nDestTrack = 0, nScNum = 0;

	if (RGV_INFO->m_bStoreSuspend)	
		return FALSE;

	int nTrackNum = CLib::GetRgvStoStartHSTrack(m_nNum, nRank);

	if ( TRACK_INFO[nTrackNum].m_nLuggNum ==  0 ||
		!TRACK_INFO[nTrackNum].m_bStoHomeStandReady )
		return FALSE;

	CString strLog;
	CMoveJobItem *pMoveJobItem = MOVEJOB->Find(TRACK_INFO[nTrackNum].m_nLuggNum);
	if (pMoveJobItem == NULL)
	{
		strLog.Format("StoreSiteRoutine.. %s 출발HS[CV#%d]에 도착한 작업번호를 찾을 수 없슴..", m_strDevice, nTrackNum+1);
		m_pDoc->DisplayMessage(strLog, FALSE);
		return FALSE;
	} 

	if(pMoveJobItem->GetPattern() != JOB_PATTERN_MOVE ) 
		return FALSE;

    if(pMoveJobItem->m_nStatus != JOB_STA_MOVE_CV_OPER_INVOKE) 
		return FALSE;


	if(pMoveJobItem->m_nLastPallet == 1)
	{
		int nDestTrack = CLib::GetRgvRetDestHSTrack(pMoveJobItem->m_nLineNum, m_nNum);
		
		if ( TRACK_INFO[nDestTrack].m_nLuggNum !=  0 ||
			!m_pDoc->m_ConveyorTrackInfo[nDestTrack].m_bRetHomeStandReady )
			return FALSE;

		int nStartPos = GetRgvPosPerTrack(nTrackNum+1);
		int nDestPos  = GetRgvPosPerTrack(nDestTrack+1);

		if (HsToHs(pMoveJobItem->m_nLuggNum, nStartPos, nDestPos))
		{
			RGV_INFO->m_bInvoke = TRUE;
			RGV_INFO->m_nNextRtn = ROUTINE_SITE_STORE;

			RGV_INFO->m_nStartTrack = nTrackNum;
			RGV_INFO->m_nDestTrack = nDestTrack;

			RGV_INFO->m_nInternalLuggNum = pMoveJobItem->m_nLuggNum;

			if(pMoveJobItem->GetPattern() == JOB_PATTERN_MOVE) RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_SITE_TO_SITE;
			else if(pMoveJobItem->GetPattern() == JOB_PATTERN_STO) RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_STORE;
			else RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_RETRIEVE;

			RGV_INFO->m_bModified = TRUE;
			RGV_INFO->Backup();

			//pMoveJobItem->Lock();

			pMoveJobItem->m_nStatus = JOB_STA_MOVE_RGV_OPER_INVOKE;
			MOVEJOB->Backup();

			strLog.Format("StoreSiteRoutine.. %s 마지막으로 강제 설정 이동지시[CV#%d-CV#%d] 전송..", m_strDevice, nTrackNum+1, nDestTrack+1);
			LOG_JOB(LOG_POS_RGV, pMoveJobItem->m_nLuggNum, strLog);

			return TRUE;
		}
		else
		{
			strLog.Format("RetrieveRoutine.. %s 마지막으로 강제 설정 이동지시[CV#%d-CV#%d] 실패..[%s]", m_strDevice, nTrackNum+1, nDestTrack+1, m_strErrorMsg);
			LOG_ERROR(LOG_POS_RGV, pMoveJobItem->m_nLuggNum, strLog);
		}
	}
	else
	{
		nDestTrack = 746-1;
		//nDestTrack = CLib::GetRgvStoDestHSTrack(m_nNum, pMoveJobItem->m_nLineNum);

		if ( TRACK_INFO[nDestTrack].m_nLuggNum ==  0 ||
			 !TRACK_INFO[nDestTrack].m_bRetHomeStandReady )
			 return FALSE;

		if ( TRACK_INFO[nDestTrack].m_nLuggNum !=  0 ||
			 TRACK_INFO[nDestTrack].m_bRetHomeStandReady )
		{

			CMoveJobItem *pDestJobItem = MOVEJOB->Find(TRACK_INFO[nDestTrack].m_nLuggNum);
			if (pDestJobItem == NULL)
			{
				strLog.Format("StoreRoutine.. %s 출발HS[CV#%d]에 도착한 작업번호를 찾을 수 없슴..", m_strDevice, nTrackNum+1);
				m_pDoc->DisplayMessage(strLog, FALSE);
				return FALSE;
			} 

			if(pMoveJobItem->m_nLineNum != pDestJobItem->m_nLineNum)
				return FALSE;
		}

		int nStartPos = GetRgvPosPerTrack(nTrackNum+1);
		int nDestPos  = GetRgvPosPerTrack(nDestTrack+1);

		if (HsToHs(pMoveJobItem->m_nLuggNum, nStartPos, nDestPos))
		{
			RGV_INFO->m_bInvoke = TRUE;
			RGV_INFO->m_nNextRtn = ROUTINE_SITE_STORE;

			RGV_INFO->m_nStartTrack = nTrackNum;
			RGV_INFO->m_nDestTrack = nDestTrack;

			RGV_INFO->m_nInternalLuggNum = pMoveJobItem->m_nLuggNum;

			if(pMoveJobItem->GetPattern() == JOB_PATTERN_MOVE) RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_SITE_TO_SITE;
			else if(pMoveJobItem->GetPattern() == JOB_PATTERN_STO) RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_STORE;
			else RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_RETRIEVE;

			time(&RGV_INFO->m_tJobStart);

			RGV_INFO->m_bModified = TRUE;
			RGV_INFO->Backup();

			pMoveJobItem->m_nStatus = JOB_STA_MOVE_RGV_OPER_INVOKE;
			MOVEJOB->Backup();

			strLog.Format("StoreSiteRoutine.. %s 이동지시[CV#%d-CV#%d] 전송..", m_strDevice, nTrackNum+1, nDestTrack+1);
			LOG_JOB(LOG_POS_RGV, pMoveJobItem->m_nLuggNum, strLog);
			return TRUE;
		}
		else
		{
			strLog.Format("StoreSiteRoutine.. %s 이동지시[CV#%d-CV#%d] 실패..[%s]", m_strDevice, nTrackNum+1, nDestTrack+1, m_strErrorMsg);
			LOG_ERROR(LOG_POS_RGV, pMoveJobItem->m_nLuggNum, strLog);
		}
	}

	return FALSE;
}


BOOL CRgv::RetrieveRoutine()
{
	int nRank = RGV_INFO->m_nRetNextRtn;

	//int nRetCnt = 1;
	int nRetCnt = 2;

	for(int i=0; i<nRetCnt; i++)
	{
		if ( RetrieveRoutine(nRank) )
		{
			nRank++;
			if (nRank >= nRetCnt)
				nRank = 0;

			RGV_INFO->m_nRetNextRtn = nRank;
			return TRUE;
		}
		nRank++;
		if (nRank >= nRetCnt)
			nRank = 0;
	}

	RGV_INFO->m_nRetNextRtn = nRank;

	return FALSE;
}

BOOL CRgv::RetrieveRoutine(int nRank)
{
	CString strLog;
	int nTrackNum=0;
    CMoveJobItem *pMoveJobItem2=NULL;


	if (RGV_INFO->m_bStoreSuspend)		
		return FALSE;

	if(nRank == 0)
		nTrackNum = 746-1;
	else
		nTrackNum = 2005-1;

	if (!TRACK_INFO[nTrackNum].m_bStoHomeStandReady)
		return FALSE;

	CMoveJobItem *pMoveJobItem = MOVEJOB->Find(TRACK_INFO[nTrackNum].m_nLuggNum);
	if (pMoveJobItem == NULL)
	{
		strLog.Format("RetrieveRoutine.. %s 출발HS[CV#%d]에 도착한 작업번호를 찻을수 없슴..", m_strDevice, nTrackNum+1);
		m_pDoc->DisplayMessage(strLog, FALSE);
		return FALSE;
	}

	if(TRACK_INFO[nTrackNum].m_nLuggNum2 != 0)
	{
		pMoveJobItem2 = MOVEJOB->Find(TRACK_INFO[nTrackNum].m_nLuggNum2);
		if (pMoveJobItem2 == NULL)
		{
			strLog.Format("RetrieveRoutine.. %s 출발HS[CV#%d]에 도착한 작업번호를 찻을수 없슴..", m_strDevice, nTrackNum+1);
			m_pDoc->DisplayMessage(strLog, FALSE);
			return FALSE;
		}
	}

	if(pMoveJobItem->GetPattern() != JOB_PATTERN_MOVE) 
		return FALSE;

	if (pMoveJobItem->m_nStatus != JOB_STA_MOVE_CV_OPER_INVOKE)	
		return FALSE;

	if (pMoveJobItem2 != NULL)
	{
		if(pMoveJobItem->m_nLineNum != pMoveJobItem2->m_nLineNum)
			return FALSE;

		if(pMoveJobItem2->GetPattern() != JOB_PATTERN_MOVE) 
			return FALSE;

		if(pMoveJobItem2->m_nStatus != JOB_STA_MOVE_CV_OPER_INVOKE)	
			return FALSE;
	}

	int nDestTrack=0;

	switch(pMoveJobItem->m_nBatchNo)
	{
	case	1:	nDestTrack = 713-1;	break;
	case	2:	nDestTrack = 720-1;	break;
	case	3:	nDestTrack = 727-1;	break;
	case	4:	nDestTrack = 734-1;	break;
	case	5:	nDestTrack = 740-1;	break;
	case	6:	nDestTrack = 747-1;	break;
	case	7:	nDestTrack = 754-1;	break;
	case	8:	nDestTrack = 761-1;	break;
	case	9:	nDestTrack = 768-1;	break;
	case	10:	nDestTrack = 775-1;	break;
	case	11:	nDestTrack = 782-1;	break;
	}

	//내려놓을 자리를 순간적으로 체크하므로 RTV 완료 상태가 있으면 이동지시 안한다.
	CMoveJobItem *pCheckJobItem = MOVEJOB->FetchRgvJobByDestTrack(nDestTrack);
	if ( pCheckJobItem != NULL )		
		return FALSE;
	
	if ( TRACK_INFO[nDestTrack].m_nLuggNum !=  0 ||
		!m_pDoc->m_ConveyorTrackInfo[nDestTrack].m_bRetHomeStandReady )
		return FALSE;

	int nStartPos = GetRgvPosPerTrack(nTrackNum+1);
	int nDestPos  = GetRgvPosPerTrack(nDestTrack+1);

	if (HsToHs(pMoveJobItem->m_nLuggNum, nStartPos, nDestPos))
	{
		RGV_INFO->m_bInvoke = TRUE;
		RGV_INFO->m_nNextRtn = ROUTINE_RETRIEVE;

		RGV_INFO->m_nStartTrack = nTrackNum;
		RGV_INFO->m_nDestTrack = nDestTrack;

		RGV_INFO->m_nInternalLuggNum = pMoveJobItem->m_nLuggNum;

		if(TRACK_INFO[nTrackNum].m_nLuggNum2 != 0)
			RGV_INFO->m_nInternalLuggNum2 = pMoveJobItem2->m_nLuggNum;

		if(pMoveJobItem->GetPattern() == JOB_PATTERN_MOVE) RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_SITE_TO_SITE;
		else if(pMoveJobItem->GetPattern() == JOB_PATTERN_STO) RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_STORE;
		else RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_RETRIEVE;

		RGV_INFO->m_bModified = TRUE;
		RGV_INFO->Backup();

		//pMoveJobItem->Lock();

		pMoveJobItem->m_nStatus = JOB_STA_MOVE_RGV_OPER_INVOKE;
		MOVEJOB->Backup();

		strLog.Format("RetrieveRoutine.. %s 이동지시[CV#%d-CV#%d] 전송..", m_strDevice, nTrackNum+1, nDestTrack+1);
		LOG_JOB(LOG_POS_RGV, pMoveJobItem->m_nLuggNum, strLog);

		if(TRACK_INFO[nTrackNum].m_nLuggNum2 != 0)
		{
			strLog.Format("RetrieveRoutine.. %s 이동지시[CV#%d-CV#%d] 전송..", m_strDevice, nTrackNum+1, nDestTrack+1);
			LOG_JOB(LOG_POS_RGV, pMoveJobItem2->m_nLuggNum, strLog);
		}

		return TRUE;
	}
	else
	{
		strLog.Format("RetrieveRoutine.. %s 이동지시[CV#%d-CV#%d] 실패..[%s]", m_strDevice, nTrackNum+1, nDestTrack+1, m_strErrorMsg);
		LOG_ERROR(LOG_POS_RGV, pMoveJobItem->m_nLuggNum, strLog);

		if(TRACK_INFO[nTrackNum].m_nLuggNum2 != 0)
		{
			strLog.Format("RetrieveRoutine.. %s 이동지시[CV#%d-CV#%d] 실패..[%s]", m_strDevice, nTrackNum+1, nDestTrack+1, m_strErrorMsg);
			LOG_ERROR(LOG_POS_RGV, pMoveJobItem2->m_nLuggNum, strLog);
		}
	}

	return FALSE;
}

/*
BOOL CRgv::RetrieveSiteRoutine()
{
	BOOL bLinelastCheck=FALSE;
	static int nLineCount=0;
	int nStationCnt=12;
	int nRank = RGV_INFO->m_nRetSiteNextRtn;

	if(RGV_INFO->m_nRetSiteNextRtn > nStationCnt)
		nRank = RGV_INFO->m_nRetSiteNextRtn = 0;


	for(int i = RGV_INFO->m_nRetSiteNextRtn; i< RGV_INFO->m_nRetSiteNextRtn + nStationCnt; i++)
	{
		if(i >= nStationCnt)
			nRank = i-nStationCnt;

		if ( RetrieveSiteRoutine(nRank, &bLinelastCheck) )
		{
			nLineCount++;

			if(nLineCount == 6 || bLinelastCheck == TRUE)
			{
				nLineCount=0;
				RGV_INFO->m_nRetSiteNextRtn++;
				return TRUE;
			}
		}

		nRank++;
	}

	return FALSE;
}
*/


BOOL CRgv::RetrieveSiteRoutine()
{
	int nRank = RGV_INFO->m_nRetSiteNextRtn;

	int nRetSiteCnt = 12;

	for(int i=0; i<nRetSiteCnt; i++)
	{
		if ( RetrieveSiteRoutine(nRank) )
		{
			nRank++;
			if (nRank >= nRetSiteCnt)
				nRank = 0;

			RGV_INFO->m_nRetSiteNextRtn = nRank;
			return TRUE;
		}
		nRank++;
		if (nRank >= nRetSiteCnt)
			nRank = 0;
	}

	RGV_INFO->m_nRetSiteNextRtn = nRank;

	return FALSE;
}


BOOL CRgv::RetrieveSiteRoutine(int nRank)
{
	CString strLog;
	CMoveJobItem *pMoveJobItem2=NULL;

	if (RGV_INFO->m_bStoreSuspend)		
		return FALSE;

	int nTrackNum = CLib::GetRgvRetStartHSTrack2(m_nNum, nRank);

	if ( TRACK_INFO[nTrackNum].m_nLuggNum ==  0 || 
		!TRACK_INFO[nTrackNum].m_bStoHomeStandReady )
		return FALSE;

	if(nTrackNum == 787-1)
	{
		if(m_pDoc->m_bJobStopCheck)	
			return FALSE;
	}
	else if(nTrackNum != 808-1)
	{
		if(m_pDoc->m_bBufferStopCheck)
			return FALSE;
	}

	CMoveJobItem *pMoveJobItem = MOVEJOB->Find(TRACK_INFO[nTrackNum].m_nLuggNum);
	if (pMoveJobItem == NULL)
	{
		strLog.Format("RetrieveSiteRoutine.. %s 출발HS[CV#%d]에 도착한 작업번호를 찻을수 없슴..", m_strDevice, nTrackNum+1);
		m_pDoc->DisplayMessage(strLog, FALSE);
		return FALSE;
	}

	if(TRACK_INFO[nTrackNum].m_nLuggNum2 != 0)
	{
		pMoveJobItem2 = MOVEJOB->Find(TRACK_INFO[nTrackNum].m_nLuggNum2);
		if (pMoveJobItem2 == NULL)
		{
			strLog.Format("RetrieveRoutine.. %s 출발HS[CV#%d]에 도착한 작업번호를 찻을수 없슴..", m_strDevice, nTrackNum+1);
			m_pDoc->DisplayMessage(strLog, FALSE);
			return FALSE;
		}
	}

	if(pMoveJobItem->GetPattern() != JOB_PATTERN_MOVE) 
		return FALSE;

	if(TRACK_INFO[nTrackNum].m_nLuggNum2 != 0 && pMoveJobItem2 != NULL)
	{
		if(pMoveJobItem2->GetPattern() != JOB_PATTERN_MOVE) 
			return FALSE;
	}

	if (pMoveJobItem->m_nStatus != JOB_STA_MOVE_RGV_OPER_REQUEST)	
		return FALSE;

	if(TRACK_INFO[nTrackNum].m_nLuggNum2 != 0 && pMoveJobItem2 != NULL)
	{
		if(pMoveJobItem2->m_nStatus != JOB_STA_MOVE_RGV_OPER_REQUEST) 
			return FALSE;
	}

	int nDestTrack = 809-1;

	if(m_pDoc->m_bPriorityDocCheck)
    {
		if ( TRACK_INFO[nDestTrack].m_nLuggNum !=  0 ||
			!m_pDoc->m_ConveyorTrackInfo[nDestTrack].m_bRetHomeStandReady )
			return FALSE;
    }
/*	
	if ( TRACK_INFO[nDestTrack].m_nLuggNum !=  0 ||
		!m_pDoc->m_ConveyorTrackInfo[nDestTrack].m_bRetHomeStandReady )
		return FALSE;
*/
	int nStartPos = GetRgvPosPerTrack(nTrackNum+1);
	int nDestPos  = GetRgvPosPerTrack(nDestTrack+1);

	if (HsToHs(pMoveJobItem->m_nLuggNum, nStartPos, nDestPos))
	{
		RGV_INFO->m_bInvoke = TRUE;
		RGV_INFO->m_nNextRtn = ROUTINE_SITE_RETRIEVE;

		RGV_INFO->m_nStartTrack = nTrackNum;
		RGV_INFO->m_nDestTrack = nDestTrack;

		RGV_INFO->m_nInternalLuggNum = pMoveJobItem->m_nLuggNum;

		if(TRACK_INFO[nTrackNum].m_nLuggNum2 != 0 && pMoveJobItem2 != NULL)
		{
			RGV_INFO->m_nInternalLuggNum2 = pMoveJobItem2->m_nLuggNum;
			pMoveJobItem2->m_nStatus = JOB_STA_MOVE_RGV_OPER_INVOKE;
			pMoveJobItem2->m_nBatchNo = 0;
		}

		if(pMoveJobItem->GetPattern() == JOB_PATTERN_MOVE) RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_SITE_TO_SITE;
		else if(pMoveJobItem->GetPattern() == JOB_PATTERN_STO) RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_STORE;
		else RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_RETRIEVE;

		RGV_INFO->m_bModified = TRUE;
		RGV_INFO->Backup();

		//pMoveJobItem->Lock();

		pMoveJobItem->m_nStatus = JOB_STA_MOVE_RGV_OPER_INVOKE;
		pMoveJobItem->m_nBatchNo = 0;
		MOVEJOB->Backup();

		strLog.Format("RetrieveSiteRoutine.. %s 이동지시[CV#%d-CV#%d] 전송..", m_strDevice, nTrackNum+1, nDestTrack+1);
		LOG_JOB(LOG_POS_RGV, pMoveJobItem->m_nLuggNum, strLog);

		if(TRACK_INFO[nTrackNum].m_nLuggNum2 != 0 && pMoveJobItem2 != NULL)
		{
			strLog.Format("RetrieveSiteRoutine.. %s 이동지시[CV#%d-CV#%d] 전송..", m_strDevice, nTrackNum+1, nDestTrack+1);
			LOG_JOB(LOG_POS_RGV, pMoveJobItem2->m_nLuggNum, strLog);
		}

		return TRUE;
	}
	else
	{
		strLog.Format("RetrieveSiteRoutine.. %s 이동지시[CV#%d-CV#%d] 실패..[%s]", m_strDevice, nTrackNum+1, nDestTrack+1, m_strErrorMsg);
		LOG_ERROR(LOG_POS_RGV, pMoveJobItem->m_nLuggNum, strLog);

		if(TRACK_INFO[nTrackNum].m_nLuggNum2 != 0)
		{
			strLog.Format("RetrieveSiteRoutine.. %s 이동지시[CV#%d-CV#%d] 실패..[%s]", m_strDevice, nTrackNum+1, nDestTrack+1, m_strErrorMsg);
			LOG_ERROR(LOG_POS_RGV, pMoveJobItem2->m_nLuggNum, strLog);
		}
	}

	return FALSE;
}

void CRgv::ErrorCheck()
{
	if (RGV_INFO->m_ucStatus != RGV_STA_ERROR)
	{
		RGV_INFO->m_wPrevErrCode = 0;
		return;
	}

	if (RGV_INFO->m_wPrevErrCode == RGV_INFO->m_wErrCode)
		return;

	time(&RGV_INFO->m_tErrorStart); m_bIsError=TRUE;
	STATISTIC->m_sSTC[m_nNum].nErrorSum ++;
	STATISTIC->RegistErrCode(m_nNum, RGV_INFO->m_wErrCode);
	m_pDoc->m_pStatistic->Backup();

	RGV_INFO->m_wPrevErrCode = RGV_INFO->m_wErrCode;
	if(RGV_INFO->m_wErrCode == 0)	return;

	CString strLog;
	strLog.Format("ErrorCheck.. %s 에러.. 모드=[%s], 정보=[%d : %s]", m_strDevice,
				   RGV_INFO->GetRgvModeString(), RGV_INFO->m_wErrCode, RGV_INFO->GetRgvErrorString());

	if (HOST != NULL)
		HOST->Error(4, m_nNum+1, 0, RGV_INFO->m_wErrCode, 0000);

	if (RGV_INFO->m_nInternalLuggNum == 0 || RGV_INFO->m_nInternalLuggNum == 9999)
	{
		LOG_ERROR(LOG_POS_RGV, LOG_SYSTEM, strLog);
		return;
	}

	CMoveJobItem* pMoveJobItem = MOVEJOB->Find(RGV_INFO->m_nInternalLuggNum);
	if (pMoveJobItem == NULL)
	{
		strLog.Format("ErrorCheck.. %s 이미 완료 또는 삭제 되었슴.. 에러는 무시..", m_strDevice);
		LOG_ERROR(LOG_POS_RGV, RGV_INFO->m_nInternalLuggNum, strLog);
		return;
	}

	LOG_ERROR(LOG_POS_RGV, pMoveJobItem->m_nLuggNum, strLog);
}

void CRgv::CompleteCheck()
{
	if (!RGV_INFO->m_bInvoke)		
		return;

	if ( (m_pRgvInfo->m_ucStatus == RGV_STA_WAIT || m_pRgvInfo->m_ucStatus == RGV_STA_IDLE) &&
		  m_pRgvInfo->m_ucProdLoad == RGV_PROD_EMPTY && m_pRgvInfo->m_ucTransaction == RGV_TRN_COMPLETE &&
		  m_pRgvInfo->m_nLuggNum == m_pRgvInfo->m_nInternalLuggNum )
	{
		RGV_INFO->m_bInvoke = FALSE;
		RGV_INFO->m_bModified = TRUE;

		if(	RGV_INFO->m_ucInternalJobType == RGV_JOB_TYPE_MANUAL ||
			RGV_INFO->m_ucInternalJobType == RGV_JOB_TYPE_CALL_TO_HOME)
		{
			RGV_INFO->m_nInternalLuggNum = 0;
			RGV_INFO->Backup();
			return;
		}

		CString strLog;
		CMoveJobItem* pMoveJobItem = MOVEJOB->Find(RGV_INFO->m_nInternalLuggNum);
		if (pMoveJobItem == NULL)
		{
			strLog.Format("CompleteCheck.. %s 작업번호를 찾을 수 없슴..", m_strDevice, RGV_INFO->m_nLuggNum);
			LOG_ERROR(LOG_POS_RGV, RGV_INFO->m_nInternalLuggNum, strLog);
			return;
		}

//		StatisticWorkTime(pMoveJobItem);

		pMoveJobItem->m_nDestTrack = RGV_INFO->m_nDestTrack;
		pMoveJobItem->m_nStatus = JOB_STA_MOVE_RGV_OPER_COMPLETE;
		MOVEJOB->Backup();

		strLog.Format("CompleteCheck.. %s 이동 작업완료.. ", m_strDevice);
		LOG_JOB(LOG_POS_RGV, RGV_INFO->m_nInternalLuggNum, strLog);

		CMoveJobItem* pMoveJobItem2 = MOVEJOB->Find(RGV_INFO->m_nInternalLuggNum2);
		if (pMoveJobItem2 != NULL)
		{
			pMoveJobItem->m_nTwinJob = 2;
			pMoveJobItem2->m_nTwinJob = 2;

			pMoveJobItem2->m_nDestTrack = RGV_INFO->m_nDestTrack;
			pMoveJobItem2->m_nStatus = JOB_STA_MOVE_RGV_OPER_COMPLETE;
			MOVEJOB->Backup();

			strLog.Format("CompleteCheck.. %s 이동 작업완료.. ", m_strDevice);
			LOG_JOB(LOG_POS_RGV, RGV_INFO->m_nInternalLuggNum2, strLog);
		}

		RGV_INFO->m_nInternalLuggNum  = 0;
		RGV_INFO->m_nInternalLuggNum2 = 0;
		RGV_INFO->Backup();
	}
}

int CRgv::CommandProc(SRgvMsg* pRgvMsg)
{
	CString strLog;
	switch (pRgvMsg->nCommand)
	{
	case	RGV_CMD_COMPLETE:
		strLog.Format("CRgv::CommandProc.. %s 강제완료..", m_strDevice);
		LOG_EVENT(LOG_POS_RGV, RGV_INFO->m_nInternalLuggNum, strLog);

		RGV_INFO->m_nLuggNum = RGV_INFO->m_nInternalLuggNum;
		RGV_INFO->m_ucTransaction = RGV_TRN_COMPLETE;
		CompleteCheck();
		Delete();
		break;

	case	RGV_CMD_CANCEL:
		if ( Delete() )
		{
			strLog.Format("CRgv::CommandProc.. %s 현작업 데이터 삭제", m_strDevice);
			LOG_EVENT(LOG_POS_RGV, RGV_INFO->m_nInternalLuggNum, strLog);

			RGV_INFO->m_bInvoke = FALSE;
			RGV_INFO->m_nInternalLuggNum  = 0;
			RGV_INFO->m_nInternalLuggNum2 = 0;
		}
		else
		{
			strLog.Format("CRgv::CommandProc.. %s 현작업 데이터 삭제 실패", m_strDevice);
			LOG_EVENT(LOG_POS_RGV, RGV_INFO->m_nInternalLuggNum, strLog);
		}
		break;

	case	RGV_CMD_ACTIVE:
		if ( Active() )
			strLog.Format("CRgv::CommandProc.. %s ACTIVE 지시", m_strDevice);
		else
			strLog.Format("CRgv::CommandProc.. %s ACTIVE 지시 실패", m_strDevice);
		LOG_EVENT(LOG_POS_RGV, LOG_SYSTEM, strLog);
		break;

	case	RGV_CMD_ESTOP:
		if ( EStop() )
			strLog.Format("CRgv::CommandProc.. %s 비상정지 지시", m_strDevice);
		else
			strLog.Format("CRgv::CommandProc.. %s 비상정지 지시.. 실패..", m_strDevice);
		LOG_ERROR(LOG_POS_RGV, LOG_SYSTEM, strLog);
		break;

	case	RGV_CMD_STOP:
		if ( Stop() )
			strLog.Format("CRgv::CommandProc.. %s 정지 지시", m_strDevice);
		else
			strLog.Format("CRgv::CommandProc.. %s 정지 지시.. 실패..", m_strDevice);
		LOG_ERROR(LOG_POS_RGV, LOG_SYSTEM, strLog);
		break;


	case	RGV_CMD_RESET:
		if ( Reset() )
			strLog.Format("CRgv::CommandProc.. %s 에러 리셋 지시", m_strDevice);
		else
			strLog.Format("CRgv::CommandProc.. %s 에러 리세 지시 실패", m_strDevice);
		LOG_EVENT(LOG_POS_RGV, LOG_SYSTEM, strLog);
		break;

	case	RGV_CMD_CALL_TO_HOME:
		LOG_EVENT(LOG_POS_RGV, LOG_SYSTEM, "CRgv::CommandProc.. RGV 홈복귀지시..");
		if (CallToHome())
		{
			RGV_INFO->m_bInvoke = TRUE;
			RGV_INFO->m_nInternalLuggNum = LOG_SYSTEM;
			RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_CALL_TO_HOME;
		}
		break;

	case	RGV_CMD_MANUAL:
		if ( HsToHs(LOG_SYSTEM, GetRgvPosPerTrack(pRgvMsg->nStartHS), GetRgvPosPerTrack(pRgvMsg->nDestHS)) )
		{
			RGV_INFO->m_bInvoke = TRUE;
			RGV_INFO->m_nInternalLuggNum = LOG_SYSTEM;
			RGV_INFO->m_ucInternalJobType = RGV_JOB_TYPE_MANUAL;
			strLog.Format("CRgv::CommandProc.. %s 수동 이동지시[CV#%d-CV#%d]..", m_strDevice, 
				           pRgvMsg->nStartHS, pRgvMsg->nDestHS);
		}
		else
		{
			strLog.Format("CRgv::CommandProc.. %s 수동 이동지시[CV#%d-CV#%d] 실패..",
				           m_strDevice, pRgvMsg->nStartHS, pRgvMsg->nDestHS );
		}
		LOG_EVENT(LOG_POS_RGV, LOG_SYSTEM, strLog);

		break;
	}
	
	RGV_INFO->m_bModified = TRUE;
	RGV_INFO->Backup();

	return TRUE;
}

BOOL CRgv::IsInvoke()
{
	return RGV_INFO->m_bInvoke;
}

int CRgv::HsToHs(int nLuggNum, int nHsNumFrom, int nHsNumTo)
{
	BYTE	TxBuff[256];
	memset(TxBuff, 0x30, sizeof(TxBuff));

	char bLuggNum[5];
	char bFromHS[5];
	char bToHS[5];

	sprintf(bLuggNum, "%.4X", nLuggNum);
	sprintf(bFromHS, "%.4X", nHsNumFrom);
	sprintf(bToHS, "%.4X", nHsNumTo);

	TxBuff[3] = '3';                 // 직출고
    memcpy(TxBuff+4, bLuggNum, 4);
    memcpy(TxBuff+8, bFromHS, 4);
	memcpy(TxBuff+12, bToHS, 4);
	TxBuff[16] = NULL;

	return Write(TxBuff, 171, 4, 'D');
}

int CRgv::CallToHome()
{
	BYTE	TxBuff[256];
	memset(TxBuff, '0', sizeof(TxBuff));

	char bLuggNum[5];
	char bFromHS[5];
	char bToHS[5];

	sprintf(bLuggNum, "%.4X", LOG_SYSTEM);
	sprintf(bFromHS, "%.4X", 1);
	sprintf(bToHS, "%.4X", 1);

	TxBuff[3] = '5';

	memcpy(TxBuff+4, bLuggNum, 4);
    memcpy(TxBuff+8, bFromHS, 4);
	memcpy(TxBuff+12, bToHS, 4);
	TxBuff[16] = NULL;

	return Write(TxBuff, 171, 4, 'D');
}

int CRgv::EStop()
{
	BYTE	TxBuff[256];
	memset(TxBuff, '0', sizeof(TxBuff));

	TxBuff[3] = '1';
	TxBuff[4] = NULL;

	return Write(TxBuff, 199, 1, 'D');
}

int CRgv::Active()
{
	BYTE	TxBuff[256];
	memset(TxBuff, '0', sizeof(TxBuff));

	TxBuff[3] = '2';
	TxBuff[4] = NULL;

	return Write(TxBuff, 199, 1, 'D');
}

int CRgv::Stop()
{
	BYTE	TxBuff[256];
	memset(TxBuff, '0', sizeof(TxBuff));

	TxBuff[3] = '4';
	TxBuff[4] = NULL;

	return Write(TxBuff, 199, 1, 'D');
}

int CRgv::Reset()         // ERROR RESET
{
	BYTE	TxBuff[256];
	memset(TxBuff, '0', sizeof(TxBuff));

	TxBuff[3] = '8';
	TxBuff[4] = NULL;

	return Write(TxBuff, 199, 1, 'D');
}

int CRgv::Delete()       // DATA DELETE
{
	BYTE	TxBuff[256];
	memset(TxBuff, '0', sizeof(TxBuff));

	TxBuff[2] = '1';
	TxBuff[4] = NULL;

	return Write(TxBuff, 199, 1, 'D');
}

int CRgv::GetBank(CString strLocation)
{
	return atoi(strLocation.Mid(0, 2));
}

int CRgv::GetSide(CString strLocation)
{
	return ((atoi(strLocation.Mid(0, 2)) + 1) % 2) + 1;
}

int CRgv::GetBay(CString strLocation)
{
	return atoi(strLocation.Mid(2, 3));
}

CMoveJobItem* CRgv::CheckStartStation(int nRank, int nStartTrack)
{
	CString strLog;

	for( ; nRank<CLib::GetStartStnCntPerRgv(m_nNum); nRank++ )
	{
		if ( TRACK_INFO[nStartTrack].m_nLuggNum ==  0 ||
			!TRACK_INFO[nStartTrack].m_bStoHomeStandReady )
			continue;
		CMoveJobItem *pMoveJobItem = MOVEJOB->Find(TRACK_INFO[nStartTrack].m_nLuggNum);
		if (pMoveJobItem == NULL)

		{
			strLog.Format("%s 출발HS[CV#%d]에 도착한 작업번호를 찻을수 없슴..", m_strDevice, nStartTrack+1);
			m_pDoc->DisplayMessage(strLog, FALSE);
			continue;
		}

		if (pMoveJobItem->m_nStatus != JOB_STA_MOVE_CV_OPER_INVOKE)
			continue;

		return pMoveJobItem;
	}
	RGV_INFO->m_nRetNextRtn = 0;

	return NULL;
}


BOOL CRgv::IsRetPalletValid(CMoveJobItem *pMoveJobItem, int nRank, int nTrackNum)
{
	CString strMsg;

	if ( m_nNum == RGV_1_NUM )
	{
		if ( nRank == 0 )
			return TRUE;

		if ( pMoveJobItem->GetPattern() != JOB_PATTERN_RET)
		{
			strMsg.Format("작업번호[%d].. %s RTV 출발HS[CV#%d] 도착화물 작업패턴[%s] 이상",
						   pMoveJobItem->m_nLuggNum, m_strDevice, nTrackNum+1, pMoveJobItem->GetType());
			m_pDoc->DisplayMessage(strMsg, FALSE);
			return FALSE;
		}

		if ( nRank-1 != pMoveJobItem->GetStackerNum() )
		{
			strMsg.Format("작업번호[%d].. %s RTV 출발HS[CV#%d] 도착화물 출발지[SC#%d - LOC-%s] 이상",
				           pMoveJobItem->m_nLuggNum, m_strDevice, nTrackNum+1, pMoveJobItem->GetStackerNum()+1, pMoveJobItem->m_strLocation);
			m_pDoc->DisplayMessage(strMsg, FALSE);
			return FALSE;
		}
	}
	else
	{
		if ( pMoveJobItem->GetPattern() != JOB_PATTERN_RET)
		{
			strMsg.Format("작업번호[%d].. %s RTV 출발HS[CV#%d] 도착화물 작업패턴[%s] 이상",
						   pMoveJobItem->m_nLuggNum, m_strDevice, nTrackNum+1, pMoveJobItem->GetType());
			m_pDoc->DisplayMessage(strMsg, FALSE);
			return FALSE;
		}

		if ( nRank != pMoveJobItem->GetStackerNum() )
		{
			strMsg.Format("작업번호[%d].. %s RTV 출발HS[CV#%d] 도착화물 출발지[SC#%d - LOC-%s] 이상",
				           pMoveJobItem->m_nLuggNum, m_strDevice, nTrackNum+1, pMoveJobItem->GetStackerNum()+1, pMoveJobItem->m_strLocation);
			m_pDoc->DisplayMessage(strMsg, FALSE);
			return FALSE;
		}
	}

	return TRUE;
}

int CRgv::GetRgvPosPerTrack(int nTrackNum)
{
	switch (m_nNum)
	{
	case	RGV_1_NUM:
		switch(nTrackNum)
		{
		case	782:			return  1;
		case	775:			return  2;
		case	768:			return  3;
		case	761:			return  4;
		case	754:			return  5;
		case	747:			return  6;
		case	740:			return  7;
		case	734:			return  8;
		case	727:			return  9;
		case	720:			return  10;
		case	713:			return  11;
		case	711:			return  12;
		case	702:			return  13;
		case	712:			return  14;
		case	719:			return  15;
		case	726:			return  16;
		case	733:			return  17;
		case	746:			return  18;
		case	753:			return  19;
		case	760:			return  20;
		case	2005:			return  21;
		//case	767:			return  21;
		case	774:			return  22;
		case	781:			return  23;
		}
		break;
	case	RGV_2_NUM:
		switch (nTrackNum)
		{
		case	808:		return  1;
		case	809:		return  2;
		case	718:		return  3;
		case	725:		return  4;
		case	732:		return  5;
		case	739:		return  6;
		case	745:		return  7;
		case	752:		return  8;
		case	759:		return  9;
		case	766:		return  10;
		case	773:		return  11;
		case	780:		return  12;
		case	787:		return  13;
		}
		break;
	
	}

	return 0;
}

void CRgv::StatisticWorkTime(CMoveJobItem *pMoveJobItem)
{
	if(pMoveJobItem == NULL)	return;

	if ( pMoveJobItem->IsManualJob() )
	{
		time(&RGV_INFO->m_tJobEnd);
		time_t tLapsTime = (time_t) difftime(RGV_INFO->m_tJobEnd, RGV_INFO->m_tJobStart);
		STATISTIC->m_sSTC[m_nNum+SC_CNT].tOfflineWorkTime += tLapsTime;
		STATISTIC->m_sSTC[m_nNum+SC_CNT].nOfflineJobSum ++;
	}
	else
	{
		time(&RGV_INFO->m_tJobEnd);
		time_t tLapsTime = (time_t) difftime(RGV_INFO->m_tJobEnd, RGV_INFO->m_tJobStart);
		STATISTIC->m_sSTC[m_nNum+SC_CNT].tOnlineWorkTime += tLapsTime;
		STATISTIC->m_sSTC[m_nNum+SC_CNT].nOnlineJobSum ++;

		STATISTIC->m_sSTC[m_nNum+SC_CNT].tTempOnlineWorkTime += tLapsTime;
		STATISTIC->m_sSTC[m_nNum+SC_CNT].nTempOnlineJobSum ++;
	}
}

void CRgv::StatisticTroubleTime()
{
	if( m_bIsError && RGV_INFO->m_ucStatus != RGV_STA_ERROR && RGV_INFO->m_nInternalLuggNum != 0)
	{
		time(&RGV_INFO->m_tErrorEnd);
		if(RGV_INFO->m_nInternalLuggNum >= 9000)
		{
			time_t tLapsTime = (time_t) difftime(RGV_INFO->m_tErrorEnd, RGV_INFO->m_tErrorStart);
			STATISTIC->m_sSTC[m_nNum+SC_CNT].tOfflineTroubleTime += tLapsTime;
			m_bIsError = FALSE;
		}
		else
		{
			time_t tLapsTime = (time_t) difftime(RGV_INFO->m_tErrorEnd, RGV_INFO->m_tErrorStart);
			STATISTIC->m_sSTC[m_nNum+SC_CNT].tOnlineTroubleTime += tLapsTime;
			m_bIsError = FALSE;

		    STATISTIC->m_sSTC[m_nNum+SC_CNT].tTempOnlineTroubleTime += tLapsTime;
		}

		STATISTIC->Backup();
	}
}

/*
void CRgv::EnterBlcokingSection()
{
	if ( m_nNum == RGV_1_NUM )
	{
		CCv::m_csLockSyncThread1.Lock();
	}

	if ( m_nNum == RGV_3_NUM )
	{
		CCv::m_csLockSyncThread2.Lock();
	}
}

void CRgv::LeaveBlcokingSection()
{
	if ( m_nNum == RGV_1_NUM )
	{
		CCv::m_csLockSyncThread1.Unlock();
	}

	if ( m_nNum == RGV_3_NUM )
	{
		CCv::m_csLockSyncThread2.Unlock();
	}
}

BOOL CRgv::CanBlockingJobStartNow()
{
	if ( m_nNum == RGV_1_NUM )
		return JOB->CanWip2LockJobStartNow(ROUTINE_RETRIEVE);

	if ( m_nNum == RGV_3_NUM )
		return JOB->CanWip3LockJobStartNow(ROUTINE_RETRIEVE);

	return FALSE;
}

void CRgv::ChangeBlockingRoutine()
{
	if ( m_nNum == RGV_1_NUM )
		JOB->m_nWip2NextRtn = ROUTINE_STORE;

	if ( m_nNum == RGV_3_NUM )
		JOB->m_nWip3NextRtn = ROUTINE_STORE;
}

*/