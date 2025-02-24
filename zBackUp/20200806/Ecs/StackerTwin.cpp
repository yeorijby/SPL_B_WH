// StackerTwin.cpp: implementation of the CStackerTwin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ecs.h"
#include "StackerTwin.h"
#include "Lib.h"
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStacker::CStacker(int nNum, CEcsDoc* pDoc)
{ 
	m_nNum = nNum; 
	m_pDoc = pDoc; 

	m_bIsError = FALSE;
}

uchar CStacker::GetBank(CString strLocation)
{
	return atoi(strLocation.Mid(0, 2));
}

uchar CStacker::GetSide(CString strLocation)
{
	return ((atoi(strLocation.Mid(0, 2)) + 1) % 2) + 1;
}

uchar CStacker::GetBay(CString strLocation)
{
	return atoi(strLocation.Mid(2, 3));
}

uchar CStacker::GetLevel(CString strLocation)
{
	return atoi(strLocation.Mid(5, 2));
}

int CStacker::Store(int nLuggNum1, CString strLocation1, int nLuggNum2, CString strLocation2, int nHsNum, char bUseFork)
{
	BYTE	TxBuff[256];
	memset(TxBuff, '0', sizeof(TxBuff));

	char bLuggNum1[5];
	char bHsNum1[5];
	char bSide1[5];
	char bBay1[5];
	char bLevel1[5];
	char bHsNum2[5];
	char bLuggNum2[5];
	char bSide2[5];
	char bBay2[5];
	char bLevel2[5];

	sprintf(bLuggNum1, "%.4X", nLuggNum1);
	sprintf(bHsNum1, "%.4X", nHsNum);
	sprintf(bSide1, "%.4X", GetSide(strLocation1));
	sprintf(bBay1, "%.4X", GetBay(strLocation1));
	sprintf(bLevel1, "%.4X", GetLevel(strLocation1));

	if (nLuggNum2 != 0)
	{
		sprintf(bLuggNum2, "%.4X", nLuggNum2);
		sprintf(bSide2, "%.4X", GetSide(strLocation2));
		sprintf(bBay2, "%.4X", GetBay(strLocation2));
		sprintf(bLevel2, "%.4X", GetLevel(strLocation2));
		sprintf(bHsNum2, "%.4X", nHsNum);
	}
	else
	{
		strcpy(bHsNum2, "0000");
		strcpy(bLuggNum2, "0000");
		strcpy(bSide2, "0000");
		strcpy(bBay2, "0000");
		strcpy(bLevel2, "0000");
	}

	TxBuff[3] = '1';
    memcpy(TxBuff+4,  bLuggNum1, 4);
    memcpy(TxBuff+20, bHsNum1, 4);
    memcpy(TxBuff+24, bSide1, 4);
	memcpy(TxBuff+28, bBay1, 4);
	memcpy(TxBuff+32, bLevel1, 4);
	TxBuff[43] = bUseFork;			// 0 포크#1, 1 포크#1 #2, 2 포크#2
	memcpy(TxBuff+44, bLuggNum2, 4);
    memcpy(TxBuff+60, bHsNum2, 4);
    memcpy(TxBuff+64, bSide2, 4);
	memcpy(TxBuff+68, bBay2, 4);
	memcpy(TxBuff+72, bLevel2, 4);
	TxBuff[80] = NULL;

	return Write(TxBuff, 301, 20, 'D');			// D0301 20 WORDS
}

int CStacker::Retrieve(int nLuggNum1, CString strLocation1, int nLuggNum2, CString strLocation2, int nHsNum, char bUseFork)
{
	BYTE	TxBuff[256];
	memset(TxBuff, '0', sizeof(TxBuff));

	char bLuggNum1[5];
	char bHsNum1[5];
	char bHsNum2[5];
	char bSide1[5];
	char bBay1[5];
	char bLevel1[5];
	char bLuggNum2[5];
	char bSide2[5];
	char bBay2[5];
	char bLevel2[5];

	sprintf(bLuggNum1, "%.4X", nLuggNum1);
	sprintf(bHsNum1, "%.4X", nHsNum);
	sprintf(bSide1, "%.4X", GetSide(strLocation1));
	sprintf(bBay1, "%.4X", GetBay(strLocation1));
	sprintf(bLevel1, "%.4X", GetLevel(strLocation1));

	if (nLuggNum2 != 0)
	{
		sprintf(bLuggNum2, "%.4X", nLuggNum2);
		sprintf(bSide2, "%.4X", GetSide(strLocation2));
		sprintf(bBay2, "%.4X", GetBay(strLocation2));
		sprintf(bLevel2, "%.4X", GetLevel(strLocation2));
		sprintf(bHsNum2, "%.4X", nHsNum);
	}
	else
	{
		strcpy(bHsNum2, "0000");
		strcpy(bLuggNum2, "0000");
		strcpy(bSide2, "0000");
		strcpy(bBay2, "0000");
		strcpy(bLevel2, "0000");
	}

	TxBuff[3] = '2';
    memcpy(TxBuff+4,  bLuggNum1, 4);
    memcpy(TxBuff+8,  bSide1, 4);
	memcpy(TxBuff+12, bBay1, 4);
	memcpy(TxBuff+16, bLevel1, 4);
    memcpy(TxBuff+36, bHsNum1, 4);
	memcpy(TxBuff+44, bLuggNum2, 4);
    memcpy(TxBuff+48, bSide2, 4);
	memcpy(TxBuff+52, bBay2, 4);
	memcpy(TxBuff+56, bLevel2, 4);
    memcpy(TxBuff+76, bHsNum2, 4);
	TxBuff[43] = bUseFork;			// 0 포크#1, 1 포크#1 #2, 2 포크#2
	TxBuff[80] = NULL;

	return Write(TxBuff, 301, 20, 'D');			// D0301 20 WORDS
}

int CStacker::HsToHs(int nLuggNum1, int nLuggNum2, int nHsNumFrom, int nHsNumTo, char bUseFork)
{

	BYTE	TxBuff[256];
	memset(TxBuff, '0', sizeof(TxBuff));

	char bLuggNum1[5];
	char bLuggNum2[5];
	char bHsFrom[5];
	char bHsTo[5];

	sprintf(bLuggNum1, "%.4X", nLuggNum1);
	sprintf(bLuggNum2, "%.4X", nLuggNum2);
	sprintf(bHsFrom, "%.4X", nHsNumFrom);
	sprintf(bHsTo, "%.4X", nHsNumTo);

	TxBuff[3] = '3';
    memcpy(TxBuff+4,  bLuggNum1, 4);
    memcpy(TxBuff+20, bHsFrom, 4);
	memcpy(TxBuff+36, bHsTo, 4);
	memcpy(TxBuff+44, bLuggNum2, 4);
    memcpy(TxBuff+60, bHsFrom, 4);
	memcpy(TxBuff+76, bHsTo, 4);
	TxBuff[43] = bUseFork;			// 0 포크#1, 1 포크#1 #2, 2 포크#2
	TxBuff[80] = NULL;

	return Write(TxBuff, 301, 20, 'D');			// D0301 20 WORDS
}

int CStacker::RackToRack(int nLuggNum1, CString strLocFrom1, CString strLocTo1, int nLuggNum2, CString strLocFrom2, CString strLocTo2, char bUseFork)
{
	BYTE	TxBuff[256];
	memset(TxBuff, '0', sizeof(TxBuff));

	char bLuggNum1[5];
	char bSideFrom1[5];
	char bBayFrom1[5];
	char bLevelFrom1[5];
	char bSideTo1[5];
	char bBayTo1[5];
	char bLevelTo1[5];
	char bLuggNum2[5];
	char bSideFrom2[5];
	char bBayFrom2[5];
	char bLevelFrom2[5];
	char bSideTo2[5];
	char bBayTo2[5];
	char bLevelTo2[5];

	sprintf(bLuggNum1, "%.4X", nLuggNum1);
	sprintf(bSideFrom1, "%.4X", GetSide(strLocFrom1));
	sprintf(bBayFrom1, "%.4X", GetBay(strLocFrom1));
	sprintf(bLevelFrom1, "%.4X", GetLevel(strLocFrom1));
	sprintf(bSideTo1, "%.4X", GetSide(strLocTo1));
	sprintf(bBayTo1, "%.4X", GetBay(strLocTo1));
	sprintf(bLevelTo1, "%.4X", GetLevel(strLocTo1));

	if (nLuggNum2 != 0)
	{
		sprintf(bLuggNum2, "%.4X", nLuggNum2);
		sprintf(bSideFrom2, "%.4X", GetSide(strLocFrom2));
		sprintf(bBayFrom2, "%.4X", GetBay(strLocFrom2));
		sprintf(bLevelFrom2, "%.4X", GetLevel(strLocFrom2));
		sprintf(bSideTo2, "%.4X", GetSide(strLocTo2));
		sprintf(bBayTo2, "%.4X", GetBay(strLocTo2));
		sprintf(bLevelTo2, "%.4X", GetLevel(strLocTo2));
	}
	else
	{
		strcpy(bLuggNum2, "0000");
		strcpy(bSideFrom2, "0000");
		strcpy(bBayFrom2, "0000");
		strcpy(bLevelFrom2, "0000");
		strcpy(bSideTo2, "0000");
		strcpy(bBayTo2, "0000");
		strcpy(bLevelTo2, "0000");
	}

	TxBuff[3] = '4';
    memcpy(TxBuff+4,  bLuggNum1, 4);
    memcpy(TxBuff+8,  bSideFrom1, 4);
	memcpy(TxBuff+12, bBayFrom1, 4);
	memcpy(TxBuff+16, bLevelFrom1, 4);
    memcpy(TxBuff+24, bSideTo1, 4);
	memcpy(TxBuff+28, bBayTo1, 4);
	memcpy(TxBuff+32, bLevelTo1, 4);
	memcpy(TxBuff+44, bLuggNum2, 4);
    memcpy(TxBuff+48, bSideFrom2, 4);
	memcpy(TxBuff+52, bBayFrom2, 4);
	memcpy(TxBuff+56, bLevelFrom2, 4);
    memcpy(TxBuff+64, bSideTo2, 4);
	memcpy(TxBuff+68, bBayTo2, 4);
	memcpy(TxBuff+72, bLevelTo2, 4);
	TxBuff[43] = '0';			// 0 포크#1, 1 포크#1 #2, 2 포크#2
	TxBuff[80] = NULL;

	return Write(TxBuff, 301, 20, 'D');			// D0301 20 WORDS
}

int CStacker::CallToHome(int nLuggNum)
{
	BYTE	TxBuff[256];
	memset(TxBuff, '0', sizeof(TxBuff));

	char bLuggNum[5];
	sprintf(bLuggNum, "%.4X", nLuggNum);

	TxBuff[3] = '5';
	TxBuff[43] = '0';			// 0 포크#1, 1 포크#1 #2, 2 포크#2
	TxBuff[80] = NULL;

	return Write(TxBuff, 301, 20, 'D');			// D0301 20 WORDS
}

int CStacker::ErrorReset()
{
	BYTE	TxBuff[256];
	memset(TxBuff, '0', sizeof(TxBuff));

	TxBuff[0] = '1';
	TxBuff[1] = NULL;
//	TxBuff[2] = '0';
//	TxBuff[3] = NULL;

	return Write(TxBuff, 565, 1, 'M');
}

int CStacker::Active()
{
	BYTE	TxBuff[256];
	memset(TxBuff, '0', sizeof(TxBuff));

	TxBuff[0] = '1';
	TxBuff[1] = NULL;
//	TxBuff[2] = '0';
//	TxBuff[3] = NULL;

	return Write(TxBuff, 563, 1, 'M');
}

int CStacker::Estop()
{
	BYTE	TxBuff[256];
	memset(TxBuff, '0', sizeof(TxBuff));

	TxBuff[0] = '1';
	TxBuff[1] = NULL;
//	TxBuff[2] = '0';
//	TxBuff[3] = NULL;

	return Write(TxBuff, 562, 1, 'M');
}

int CStacker::Stop()
{
	BYTE	TxBuff[256];
	memset(TxBuff, '0', sizeof(TxBuff));

	TxBuff[0] = '1';
	TxBuff[1] = NULL;
//	TxBuff[2] = '0';
//	TxBuff[3] = NULL;

	return Write(TxBuff, 564, 1, 'M');
}

#define SC_INFO			m_pDoc->m_pStackerInfo[m_nNum]	
#define	TRACK_INFO		m_pDoc->m_ConveyorTrackInfo
#define	JOB				m_pDoc->m_pJob
#define	LOG				m_pDoc->m_pLog
#define	HOST			m_pDoc->m_pHostCl
#define STATISTIC		m_pDoc->m_pStatistic

int CStacker::ReadStatus()
{
	int nResult, nReadCnt=0;
	BYTE RxBuff[256];
	static int nCount[SC_CNT];

//	time_t	tLapsTime;

	memset(RxBuff, 0x0, sizeof(RxBuff));
	
	if ((nResult = Read(RxBuff, 99, 32, 'D', &nReadCnt)) != TRUE) 
	{
		if (++nCount[m_nNum] == 5)
		{
			SC_INFO->m_wErrCode = SC_ERR_CODE_COMM_ERROR;
			SC_INFO->m_ucStatus = SC_STA_ERROR;
			SC_INFO->m_bModified = TRUE;
		}
		return nResult;
	}

	for (int i=0; i<nReadCnt; i++)
	{
		if (RxBuff[i] > 0x80)	RxBuff[i] ^= 0x80;
	}

	nCount[m_nNum] = 0;

    BYTE ucRcMode        = RxBuff[8];  // 지상반 = Stacker Remote Controler
	BYTE ucScMode		 = RxBuff[12]; // 기상반 = StackerCrane
    BYTE ucStatus        = RxBuff[16]; // '1': 대기중 '2': 동작중 '4': 에러

	BYTE ucProadLoad	 = RxBuff[13];  //'1': Fork#1 Yes  '2':Fork#2 Yes

	BYTE nHorizontalPos;
	HexStr1Word(RxBuff+19, &nHorizontalPos);
	BYTE nVerticalPos;
	HexStr1Word(RxBuff+23, &nVerticalPos);

	BYTE ucSecondForkPos  = RxBuff[26];
	BYTE ucFirstForkPos   = RxBuff[28];

    WORD wErrCode;
	HexStr2Word(RxBuff+29, &wErrCode);
	BYTE ucSecondForkErrStatus	 = RxBuff[34];
	BYTE ucFirstForkErrStatus	 = RxBuff[36];

	WORD wForkJob;
	HexStr2Word(RxBuff+37, &wForkJob);

	BYTE ucActive		 = RxBuff[48];
	BYTE ucTransaction	 = RxBuff[52];

    BYTE ucJobType;
	HexStr1Word(RxBuff+55, &ucJobType);
    WORD wLuggNum1;
	HexStr2Word(RxBuff+57, &wLuggNum1);
	WORD wLuggNum2;
	HexStr2Word(RxBuff+97, &wLuggNum2);

	SC_INFO->m_ucRcMode = ucRcMode;            //자동 반자동 수동
	SC_INFO->m_bModified = TRUE;

	if (ucScMode != SC_INFO->m_ucScMode)
	{
		SC_INFO->m_ucScMode = ucScMode;            //자동 반자동 수동
		SC_INFO->m_bModified = TRUE;
	}

	if (ucStatus != SC_INFO->m_ucStatus)		   //대기 이동 에러
	{
		m_pDoc->m_pStackerInfo[m_nNum]->m_ucPrevStatus = m_pDoc->m_pStackerInfo[m_nNum]->m_ucStatus;
		SC_INFO->m_ucStatus = ucStatus;
		SC_INFO->m_bModified = TRUE;
	}

	if (nHorizontalPos != SC_INFO->m_nHorizontalPos)
	{
		SC_INFO->m_nHorizontalPos = nHorizontalPos;
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

	if (wLuggNum1 != SC_INFO->m_nLuggNum)
	{
		SC_INFO->m_nLuggNum = wLuggNum1;
	}

	if (wLuggNum2 != SC_INFO->m_nSecondLuggNum)
	{
		SC_INFO->m_nSecondLuggNum = wLuggNum2;
	}

	if ( SC_INFO->m_ucActive != SC_ACTIVE ||
		 SC_INFO->m_ucRcMode != SC_MODE_REMOTE ||
		 SC_INFO->m_ucScMode != SC_MODE_AUTO )
		SC_INFO->m_ucMode = SC_MODE_MANUAL;
	else
		SC_INFO->m_ucMode = SC_MODE_AUTO;

	if( m_bIsError && ucStatus != SC_STA_ERROR)// && SC_INFO->m_nInternalLuggNum != 0)
	{
		time(&SC_INFO->m_tErrorEnd);
		if(SC_INFO->m_nInternalLuggNum > 9000 || SC_INFO->m_nInternalLuggNum <= 0)
		{
			time_t tLapsTime = (time_t) difftime(SC_INFO->m_tErrorEnd, SC_INFO->m_tErrorStart);
			STATISTIC->m_sSTC[m_nNum].tOfflineTroubleTime += tLapsTime;
			m_bIsError = FALSE;
		}
		else
		{
			time_t tLapsTime = (time_t) difftime(SC_INFO->m_tErrorEnd, SC_INFO->m_tErrorStart);
			STATISTIC->m_sSTC[m_nNum].tOnlineTroubleTime += tLapsTime;
			m_bIsError = FALSE;
		}

		ScErrorLog(0, SC_INFO->m_wSaveErrCode);
	}

	return TRUE;
}

/*
void CStacker::CompleteCheck()
{
	if ( SC_INFO->m_bInvoke == FALSE && SC_INFO->m_bSecondInvoke == TRUE &&
		(SC_INFO->m_ucStatus == SC_STA_WAIT || SC_INFO->m_ucStatus == SC_STA_IDLE) &&
		 SC_INFO->m_nLuggNum == SC_INFO->m_nSecondInternalLuggNum &&
		 SC_INFO->m_ucTransaction == SC_TRN_COMPLETE_FORK1)
	{
		SC_INFO->m_nSecondLuggNum = SC_INFO->m_nLuggNum;
		
		CString strLog;
		strLog.Format("CompleteCheck.. SC#%d 완료보고 이상..", m_nNum+1);
		LOG->Debug(LOG_POS_SC, SC_INFO->m_nSecondInternalLuggNum, strLog);
	}

	//출고 TWIN작업인 경우 출고HS#2에 우선적 출고지시
	if ( SC_INFO->m_bSecondInvoke && (SC_INFO->m_ucStatus == SC_STA_WAIT || SC_INFO->m_ucStatus == SC_STA_IDLE) &&
		 SC_INFO->m_nSecondLuggNum == SC_INFO->m_nSecondInternalLuggNum &&
		(SC_INFO->m_ucTransaction == SC_TRN_COMPLETE_FORK2 || SC_INFO->m_ucTransaction == SC_TRN_COMPLETE_FORK12))
	{
		SC_INFO->m_bSecondInvoke = FALSE;

		CString strLog;

		CJobItem* pJobItem = JOB->Find(SC_INFO->m_nSecondInternalLuggNum);
		if (pJobItem == NULL)
		{
			strLog.Format("CompleteCheck.. SC#%d 포크#2 작업번호를 찾을 수 없음..", m_nNum+1);
			LOG->Error(LOG_POS_SC, SC_INFO->m_nSecondInternalLuggNum, strLog);
			return;
		}

		if ( SC_INFO->m_bSecondInternalJobType == SC_JOB_TYPE_RETRIEVE )
		{
			strLog.Format("CompleteCheck.. SC#%d.. 포크#2 출고 작업완료..", m_nNum+1);
			LOG->Job(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);

			pJobItem->m_bFirstFork = FALSE;
			pJobItem->m_nStatus = JOB_STA_CV_OPER_REQUEST;
			CV_ACTION(CV_1_PLC);

			SC_INFO->m_nSecondInternalLuggNum = 0;
			SC_INFO->m_bModified = TRUE;
			SC_INFO->Backup();
			return;
		}

		strLog.Format("CompleteCheck.. SC#%d.. 포크#2 입고 작업완료..", m_nNum+1);
		LOG->Job(LOG_POS_SC, SC_INFO->m_nSecondInternalLuggNum, strLog);

		JOB->Complete(SC_INFO->m_nSecondInternalLuggNum, SC_JOB_TYPE_STORE);
		JOB->Backup();

		SC_INFO->m_nSecondInternalLuggNum = 0;
		SC_INFO->m_bModified = TRUE;
		SC_INFO->Backup();
	}

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

		//StatisticWorkTime(pJobItem);

		if ( SC_INFO->m_bInternalJobType == SC_JOB_TYPE_RETRIEVE )
		{
			strLog.Format("CompleteCheck.. SC#%d.. 포크#1 출고 작업완료..", m_nNum+1);
			LOG->Job(LOG_POS_SC, pJobItem->m_nLuggNum, strLog);

			pJobItem->m_bFirstFork = TRUE;
			pJobItem->m_nStatus = JOB_STA_CV_OPER_REQUEST;

			SC_INFO->m_bCvTransaction = TRUE;
			CV_ACTION(CV_1_PLC);

			SC_INFO->m_nInternalLuggNum = 0;
			SC_INFO->m_bModified = TRUE;
			SC_INFO->Backup();
			return;
		}

		strLog.Format("CompleteCheck.. SC#%d.. 포크#1 입고 작업완료..", m_nNum+1);
		LOG->Job(LOG_POS_SC, SC_INFO->m_nInternalLuggNum, strLog);

		JOB->Complete(SC_INFO->m_nInternalLuggNum, SC_JOB_TYPE_STORE);
		JOB->Backup();

		SC_INFO->m_nInternalLuggNum = 0;
		SC_INFO->m_bModified = TRUE;
		SC_INFO->Backup();
	}
}
*/

void CStacker::CompleteCheck()
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

void CStacker::InvokeCheck()
{
	if (SC_INFO->m_bInvoke || SC_INFO->m_ucMode != SC_MODE_AUTO || 
		SC_INFO->m_ucStatus == SC_STA_MOVE || SC_INFO->m_ucStatus == SC_STA_ERROR)
		return;
	
	//if (SC_INFO->m_bInvoke || SC_INFO->m_ucRcMode != SC_MODE_REMOTE || SC_INFO->m_ucScMode == SC_MODE_MANUAL ||
	//	SC_INFO->m_ucActive != SC_ACTIVE || SC_INFO->m_ucStatus == SC_STA_MOVE || SC_INFO->m_ucStatus == SC_STA_ERROR)
	//	return;

	static int nCount = 0;

	switch (SC_INFO->m_nPrevRtn)
	{
	case	ROUTINE_STORE:
		if (RetrieveRoutine())
		{
			nCount = 0;
			break;
		}
		if (StoreRoutine())
		{
			nCount = 0;
			break;
		}
	case	ROUTINE_RETRIEVE:
		if (StoreRoutine())
		{
			nCount = 0;
			break;
		}
		if (RetrieveRoutine())
		{
			nCount = 0;
			break;
		}
	default:
		SC_INFO->m_nPrevRtn = ROUTINE_STORE;
		break;
	}

	if (nCount++ > 100 && SC_INFO->m_nHorizontalPos != 0) 
	{
//		CallToHome(0, SC_DEFAULT_HS_RETRIEVE);
		nCount = 0;
	}
}

BOOL CStacker::ErrorRoutine()
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

		if (Store(pJobItem->m_nLuggNum, strLocation, nSecondLuggNum, strSecondLoc, 1, bUseFork) == TRUE)
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

		if (Store(nLuggNum, strLocation, pSecondJobItem->m_nLuggNum, strSecondLocation, 1, bUseFork) == TRUE)
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

BOOL CStacker::StoreRoutine()
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

	if (Store(pJobItem1->m_nLuggNum, pJobItem1->m_strLocation, nLuggNum2, strLocation2, SC_DEFAULT_HS_STORE, bUseFork) == TRUE)
	{
		SC_INFO->m_bInvoke = TRUE;
		SC_INFO->m_nInternalLuggNum = pJobItem1->m_nLuggNum;
		SC_INFO->m_bInternalJobType = SC_JOB_TYPE_STORE;
		time(&SC_INFO->m_tJobStart);
		ScJobStart();	
	
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

BOOL CStacker::RetrieveRoutine()
{
	char bUseFork;

	if (SC_INFO->m_bRetrieveSuspend)	return FALSE;

	int	nTrackNum = CLib::GetScRetHSTrack(m_nNum, TRUE);
	if ( m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_nLuggNum != 0  ||
		!m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_bRetHomeStandReady )
		return FALSE;

	//if ( SC_INFO->m_bCvTransaction )	return FALSE;

	int nSecondLuggNum = 0;
	CString strSecondLoc = "";

	int	nSecondTrackNum = CLib::GetScRetHSTrack(m_nNum, FALSE);
	if ( TRACK_INFO[nSecondTrackNum].m_nLuggNum != 0 ||
		!TRACK_INFO[nSecondTrackNum].m_bRetHomeStandReady )
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

	if (Retrieve(pJobItem->m_nLuggNum, pJobItem->m_strLocation, nSecondLuggNum, strSecondLoc, 2, bUseFork) == TRUE)
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

BOOL CStacker::AdjustableRetrieve(CJobItem *pJobItem, CJobItem *pSecondJobItem)
{
	int nInternalCount = 5;

	if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_201)
	{
		if(m_pDoc->m_n4GroupInternalBatch == 0 && m_pDoc->m_n4groupInternalPalletCount == 0)
			return TRUE;

		if(pJobItem->m_nBatchNo != m_pDoc->m_n4GroupInternalBatch && 
			m_pDoc->m_n4groupInternalPalletCount > nInternalCount) return FALSE;
	}
	else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_202)
	{
		if(m_pDoc->m_n5GroupInternalBatch == 0 && m_pDoc->m_n5groupInternalPalletCount == 0)
			return TRUE;

		if(pJobItem->m_nBatchNo != m_pDoc->m_n5GroupInternalBatch && 
			m_pDoc->m_n5groupInternalPalletCount > nInternalCount) return FALSE;
	}
	else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_203)
	{
		if(m_pDoc->m_n6GroupInternalBatch == 0 && m_pDoc->m_n6groupInternalPalletCount == 0)
			return TRUE;

		if(pJobItem->m_nBatchNo != m_pDoc->m_n6GroupInternalBatch && 
			m_pDoc->m_n6groupInternalPalletCount < nInternalCount) return FALSE;
	}

	if (pSecondJobItem != NULL)
	{
		if(pSecondJobItem->m_nDestPos == IMS_ECS_RET_STATION_201)
		{
			if(m_pDoc->m_n4GroupInternalBatch == 0 && m_pDoc->m_n4groupInternalPalletCount == 0)
				return TRUE;

			if(pSecondJobItem->m_nBatchNo != m_pDoc->m_n4GroupInternalBatch && 
				m_pDoc->m_n4groupInternalPalletCount > nInternalCount)  return FALSE;
		}
		else if(pSecondJobItem->m_nDestPos == IMS_ECS_RET_STATION_202)
		{
			if(m_pDoc->m_n5GroupInternalBatch == 0 && m_pDoc->m_n5groupInternalPalletCount == 0)
				return TRUE;

			if(pSecondJobItem->m_nBatchNo != m_pDoc->m_n5GroupInternalBatch && 
				m_pDoc->m_n5groupInternalPalletCount > nInternalCount)  return FALSE;
		}
		else if(pSecondJobItem->m_nDestPos == IMS_ECS_RET_STATION_203)
		{
			if(m_pDoc->m_n6GroupInternalBatch == 0 && m_pDoc->m_n6groupInternalPalletCount == 0)
				return TRUE;

			if(pSecondJobItem->m_nBatchNo != m_pDoc->m_n6GroupInternalBatch && 
				m_pDoc->m_n6groupInternalPalletCount < nInternalCount)  return FALSE;
		}
	}

	return TRUE;
}

BOOL CStacker::RackToRackRoutine()
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
		           nSecondLuggNum, strSecondLocFrom, strSecondLocTo, bUseFork) == TRUE)
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

void CStacker::ErrorCheck()
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
				   CLib::GetStackerErrorInfoQ(SC_INFO->m_wErrCode));
	LOG->Error(LOG_POS_SC, LOG_SYSTEM, strLog);

	time(&SC_INFO->m_tErrorStart); m_bIsError=TRUE;
	m_pDoc->m_pStatistic->m_sSTC[m_nNum].nErrorSum ++;
	m_pDoc->m_pStatistic->RegistErrCode(m_nNum, SC_INFO->m_wErrCode);
	ScErrorLog(1, SC_INFO->m_wErrCode);

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

int CStacker::CommandProc(SStackerMsg* pStackerMsg)
{
	switch (pStackerMsg->nCommand)
	{
		case	SC_CMD_INVOKE:
//			pDoc->m_pLog->Event(LOG_POS_SC, pStackerMsg->nLuggNum, "Invoke Request Message receive..");
			InvokeCheck();
			break;
		case	SC_CMD_COMPLETE:
			LOG->Event(LOG_POS_SC, LOG_SYSTEM, "CommandProc.. 완료..");
			SC_INFO->m_ucPrevStatus  = SC_STA_MOVE;
			SC_INFO->m_ucTransaction = SC_TRN_COMPLETE_FORK12;
			if (SC_INFO->m_bInvoke && SC_INFO->m_nLuggNum == 0)
				SC_INFO->m_nLuggNum = SC_INFO->m_nInternalLuggNum;
			if (SC_INFO->m_bSecondInvoke && SC_INFO->m_nSecondLuggNum == 0)
				SC_INFO->m_nSecondLuggNum = SC_INFO->m_nSecondInternalLuggNum;
			CompleteCheck();
//			Delete();
			break;
		case	SC_CMD_RESTART:
			break;
		case	SC_CMD_CANCEL:
			LOG->Event(LOG_POS_SC, SC_INFO->m_nInternalLuggNum, "CommandProc.. 현작업 데이터 삭제");
			SC_INFO->m_bInvoke = FALSE;
			SC_INFO->m_nInternalLuggNum = 0;
			SC_INFO->m_bSecondInvoke = FALSE;
			SC_INFO->m_nSecondInternalLuggNum = 0;
			SC_INFO->m_bModified = TRUE;
			break;
		case	SC_CMD_CALL_TO_HOME:
			LOG->Event(LOG_POS_SC, LOG_SYSTEM, "CommandProc.. 홈복귀..");
			CallToHome(0);
			break;
		case	SC_CMD_NEW_LOCATION:
			LOG->Event(LOG_POS_SC, LOG_SYSTEM, "CommandProc.. 이중입고 재지정..");
			ErrorRoutine();
			break;

		case	SC_CMD_ERROR_RESET:
			LOG->Event(LOG_POS_SC, LOG_SYSTEM, "CommandProc.. 에러 Reset..");
			ErrorReset();
			break;
		case	SC_CMD_ACTIVE:
			LOG->Event(LOG_POS_SC, LOG_SYSTEM, "CommandProc.. Active..");
			Active();
			break;
		case	SC_CMD_ESTOP:
			LOG->Event(LOG_POS_SC, LOG_SYSTEM, "CommandProc.. 비상정지..");
			Estop();
			break;
		case	SC_CMD_PAUSE:
			LOG->Event(LOG_POS_SC, LOG_SYSTEM, "CommandProc.. 정지..");
			Stop();
			break;
	}
	
	pStackerMsg->nCommand = SC_CMD_INVOKE;
	SC_INFO->m_bModified = TRUE;
	SC_INFO->Backup();
	
	return TRUE;
}

void CStacker::StatisticWorkTime(CJobItem *pJobItem)
{
	if(pJobItem == NULL)	return;

	if ( pJobItem->IsOffLineJob() )
	{
		time(&SC_INFO->m_tJobEnd);
		time_t tLapsTime = (time_t) difftime(SC_INFO->m_tJobEnd, SC_INFO->m_tJobStart);
		STATISTIC->m_sSTC[m_nNum].tOfflineWorkTime += tLapsTime;
		STATISTIC->m_sSTC[m_nNum].nOfflineJobSum ++;
	}
	else
	{
		time(&SC_INFO->m_tJobEnd);
		time_t tLapsTime = (time_t) difftime(SC_INFO->m_tJobEnd, SC_INFO->m_tJobStart);
		STATISTIC->m_sSTC[m_nNum].tOnlineWorkTime += tLapsTime;
		STATISTIC->m_sSTC[m_nNum].nOnlineJobSum ++;
	}
}

BOOL CStacker::IsInvoke()
{
	if( SC_INFO->m_bInvoke || SC_INFO->m_bSecondInvoke)
		return TRUE;
	return FALSE;
}

void CStacker::ScDiagnosis()
{
	int   nHour, nMin, nSec;
	int   nErrTime;
	
	if (m_pDoc->m_pJob == NULL) return;

	CTime theTime   = CTime::GetCurrentTime();
	CString strTime = theTime.Format("%H%M%S");

    nHour = atoi(strTime.Mid(0,2));
	nMin  = atoi(strTime.Mid(2,2));
	nSec  = atoi(strTime.Mid(4,2));

	if (nHour >= 7 && nHour < 15) 
	{
		nHour = nHour - 7;
	}
	else if (nHour >= 15 && nHour < 23) 
	{
		nHour = nHour - 15;
	}
	else 
	{
		if (nHour >= 23) 
			nHour = nHour - 23;
		else                
			nHour = nHour + 1;
	}
	
	if (JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nTrnSta == 0) 
	{
		JOB->ScHis[m_nNum].TimeInfo[JOB->m_nPreNo].m_nTrnSta = 0;
		JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nTrnSta = 1;
		JOB->ScHis[m_nNum].m_nJobStartTime = 0;
		JOB->ScHis[m_nNum].m_nErrStartTime = 0;
		JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nJobTime = 0;
        JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nErrTime = 0;
        JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nWorkCnt = 0;
		JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nAvgTime = 0;
		JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nLongTime = 0;
	}

	if (SC_INFO->m_ucStatus == SC_STA_ERROR) 
	{
		if (JOB->ScHis[m_nNum].m_nErrStartTime == 0) 
		{
			JOB->ScHis[m_nNum].m_nErrStartTime = (nHour * 60 + nMin)*60 + nSec;
		}
		else if (JOB->ScHis[m_nNum].m_nErrStartTime > 0)
		{
			nErrTime = (nHour * 60 + nMin)*60 + nSec;
			if (JOB->ScHis[m_nNum].m_nErrStartTime < nErrTime) 
			{
			    JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nErrTime =
						JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nErrTime +
				        nErrTime - JOB->ScHis[m_nNum].m_nErrStartTime;
				JOB->ScHis[m_nNum].m_nErrStartTime = nErrTime;
			}
			else if (JOB->ScHis[m_nNum].m_nErrStartTime > nErrTime)
			{
				JOB->ScHis[m_nNum].m_nErrStartTime = 0;
				JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nErrTime = 0;
			}
		}
		else 
		{
			JOB->ScHis[m_nNum].m_nErrStartTime = 0;
			JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nErrTime = 0;
		}

		if (JOB->ScHis[m_nNum].m_nJobStartTime != 0) 
		{
			JOB->ScHis[m_nNum].m_nJobStartTime = 0;
		}
	}
	else 
	{
		if (JOB->ScHis[m_nNum].m_nErrStartTime > 0) 
		{
			nErrTime = (nHour * 60 + nMin)*60 + nSec;
			if (JOB->ScHis[m_nNum].m_nErrStartTime < nErrTime) 
			{
			    JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nErrTime =
					    JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nErrTime +
					    nErrTime - JOB->ScHis[m_nNum].m_nErrStartTime;
			}
			JOB->ScHis[m_nNum].m_nErrStartTime = 0;
		}
		else if (JOB->ScHis[m_nNum].m_nErrStartTime < 0) 
		{
			JOB->ScHis[m_nNum].m_nErrStartTime = 0;
			JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nErrTime = 0;
		}
	}

	if (JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nErrTime < 0) 
	{
		JOB->ScHis[m_nNum].m_nErrStartTime = 0;
		JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nErrTime = 0;
	}

	if (JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nJobTime > 0 &&
		JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nWorkCnt > 0) 
	{
	    JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nAvgTime =
		        JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nJobTime /
		        JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nWorkCnt;
	}
	else if (JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nJobTime > 0 &&
		     JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nWorkCnt <= 0) 
	{
		JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nJobTime = 0;
		JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nWorkCnt = 0;
		JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nAvgTime = 0;
	}
	else
	{
		JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nJobTime = 0;
		JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nWorkCnt = 0;
		JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nAvgTime = 0;
	}
}

void CStacker::ScJobStart()
{
	int   nHour, nMin, nSec;
			
	CTime theTime   = CTime::GetCurrentTime();
	CString strTime = theTime.Format("%H%M%S");

    nHour = atoi(strTime.Mid(0,2));
	nMin  = atoi(strTime.Mid(2,2));
	nSec  = atoi(strTime.Mid(4,2));

	if (nHour >= 7 && nHour < 15) 
	{
		nHour = nHour - 7;
	}
	else if (nHour >= 15 && nHour < 23) 
	{
		nHour = nHour - 15;
	}
	else 
	{
		if (nHour >= 23) 
			nHour = nHour - 23;
		else                
			nHour = nHour + 1;
	}

	JOB->ScHis[m_nNum].m_nJobStartTime = (nHour*60 + nMin)*60 + nSec;
}

void CStacker::ScJobAdd(int Count)
{
	int   nHour, nMin, nSec;
	int   nJobTime1, nJobTime2;
		
	CTime theTime   = CTime::GetCurrentTime();
	CString strTime = theTime.Format("%H%M%S");

    nHour = atoi(strTime.Mid(0,2));
	nMin  = atoi(strTime.Mid(2,2));
	nSec  = atoi(strTime.Mid(4,2));

	if (nHour >= 7 && nHour < 15) 
	{
		nHour = nHour - 7;
	}
	else if (nHour >= 15 && nHour < 23) 
	{
		nHour = nHour - 15;
	}
	else 
	{
		if (nHour >= 23) 
			nHour = nHour - 23;
		else                
			nHour = nHour + 1;
	}
	
	if (JOB->ScHis[m_nNum].m_nJobStartTime > 0) 
	{
		nJobTime1 = (nHour*60 + nMin)*60 + nSec;
		if (JOB->ScHis[m_nNum].m_nJobStartTime < nJobTime1) 
		{
		    JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nJobTime =
			  	    JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nJobTime +
			        nJobTime1 - JOB->ScHis[m_nNum].m_nJobStartTime;
			JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nWorkCnt = 
					JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nWorkCnt+Count;
			nJobTime2 = nJobTime1 - JOB->ScHis[m_nNum].m_nJobStartTime;
			if (JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nLongTime < nJobTime2) 
			{
				JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nLongTime = nJobTime2;
			}
		}
		else if (JOB->ScHis[m_nNum].m_nJobStartTime > nJobTime1) 
		{
			JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nJobTime = 0;
			JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nLongTime = 0;
		}
	}
	if (JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nJobTime < 0) 
	{
		JOB->ScHis[m_nNum].m_nJobStartTime = 0;
		JOB->ScHis[m_nNum].TimeInfo[JOB->m_nSftNo].m_nJobTime = 0;
	}

	JOB->ScHis[m_nNum].m_nJobStartTime = 0;
}

void CStacker::ScErrorLog(int nMode, WORD wErrCode)
{
    char    FileName[20], Buff[9];
    char    PrtBuff[80];
    int     Log;

	if (nMode == 1) 
	{
		SC_INFO->m_wSaveErrCode = wErrCode;
        sprintf(FileName, "..\\STC\\ERR_S%d", m_nNum+10);
        Log = open(FileName, O_WRONLY | O_CREAT | O_APPEND, S_IWRITE);
        if (Log <= -1) 
		{
            close(Log);
            return;
        }

        memset(PrtBuff, 0x20, sizeof(PrtBuff));
        _strdate(Buff);
        sprintf(PrtBuff, "%c%c%c%c%c%c", Buff[6], Buff[7], Buff[0], Buff[1], Buff[3], Buff[4]);
        _strtime(Buff);

        memcpy(PrtBuff+6, Buff, 8);
        sprintf(PrtBuff+14, "%d  ON ", wErrCode);
        write(Log, PrtBuff, 80);
        close(Log);
    }
    else
	{
		sprintf(FileName, "..\\STC\\ERR_S%d", m_nNum+10);
        Log = open(FileName, O_WRONLY | O_CREAT | O_APPEND, S_IWRITE);
        if (Log <= -1) 
		{
            close(Log);
            return;
        }

        memset(PrtBuff, 0x20, sizeof(PrtBuff));
        _strdate(Buff);
        sprintf(PrtBuff, "%c%c%c%c%c%c", Buff[6], Buff[7], Buff[0], Buff[1], Buff[3], Buff[4]);
        _strtime(Buff);

        memcpy(PrtBuff+6, Buff, 8);
        sprintf(PrtBuff+14, "%d  OFF", wErrCode);
        write(Log, PrtBuff, 80);
        close(Log);
	}
}
