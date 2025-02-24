// Cv.cpp : implementation of the CCv class
//

#include "stdafx.h"
#include "Ecs.h"

#include "Conveyor.h"
#include "Lib.h"

#define SC_INFO			m_pDoc->m_pStackerInfo[m_nNum]	
#define	TRACK_INFO		m_pDoc->m_ConveyorTrackInfo
#define	JOB				m_pDoc->m_pJob
#define	LOG				m_pDoc->m_pLog
#define	HOST			m_pDoc->m_pHostCl

CConveyor::CConveyor(int nNum, CEcsDoc* pDoc,  CCvSocket *pSock) : CMelsec3E(pSock) 
{ 
	m_nNum = nNum; 
	m_pDoc = pDoc; 
	m_nArrivedLuggNum1 = 0;
	m_nArrivedLuggNum2 = 0;
	m_nArrivedLuggNum3 = 0;
	m_nArrivedLuggNum4 = 0;

	m_nLineCountLuggNum = 0;

	m_nCvNextRtn = 0;

	for(int i = 0; i<3; i++)
	{
		m_nArrivedRemoveCheckNum[i] = 0;
	}
	m_nStoPrevLuggNum = 0;
}
/*
int CConveyor::ReadStatus()
{
	int nResult, nReadCnt=0, nReadWordCnt, nStartTrack;
	BYTE RxBuff[512];

	memset(RxBuff, 0x0, sizeof(RxBuff));
	nStartTrack = 1;
	nReadWordCnt = 40;	// Max Read Count: 64
	if ((nResult = Read(RxBuff, nStartTrack * 2, nReadWordCnt, 'D', &nReadCnt)) != TRUE) 
	{
		//m_pDoc->m_ConveyorExtraInfo[m_nNum].m_bLive = FALSE;
		return nResult;
	}

	for (int i=0; i<nReadCnt; i++)
	{
		if (RxBuff[i] > 0x80)	RxBuff[i] ^= 0x80;
	}

	ParsingFrame(RxBuff+5, nStartTrack, nReadWordCnt/2);

	Sleep(100L);
	nStartTrack = 21;
	nReadWordCnt = 36;	// Max Read Count: 64
	if ((nResult = Read(RxBuff, nStartTrack * 2, nReadWordCnt, 'D', &nReadCnt)) != TRUE) 
	{
		//m_pDoc->m_ConveyorExtraInfo[m_nNum].m_bLive = FALSE;
		return nResult;
	}

	for (i=0; i<nReadCnt; i++)
	{
		if (RxBuff[i] > 0x80)	RxBuff[i] ^= 0x80;
	}

	ParsingFrame(RxBuff+5, nStartTrack, nReadWordCnt/2);

	Sleep(100L);
	memset(RxBuff, 0x0, sizeof(RxBuff));
	nStartTrack = 39;
	nReadWordCnt = 60;	// Max Read Count: 64
	if ((nResult = Read(RxBuff, nStartTrack * 2, nReadWordCnt, 'D', &nReadCnt)) != TRUE) 
	{
		//m_pDoc->m_ConveyorExtraInfo[m_nNum].m_bLive = FALSE;
		return nResult;
	}

	for ( i=0; i<nReadCnt; i++)
	{
		if (RxBuff[i] > 0x80)	RxBuff[i] ^= 0x80;
	}

	ParsingFrame2(RxBuff+5, nStartTrack, nReadWordCnt/3);

	Sleep(100L);
	memset(RxBuff, 0x0, sizeof(RxBuff));
	nStartTrack = 59;
	nReadWordCnt = 57;	// Max Read Count: 64
	if ((nResult = Read(RxBuff, nStartTrack * 2 + 20, nReadWordCnt, 'D', &nReadCnt)) != TRUE) 
	{
		//m_pDoc->m_ConveyorExtraInfo[m_nNum].m_bLive = FALSE;
		return nResult;
	}

	for ( i=0; i<nReadCnt; i++)
	{
		if (RxBuff[i] > 0x80)	RxBuff[i] ^= 0x80;
	}

	ParsingFrame2(RxBuff+5, nStartTrack, nReadWordCnt/3);

	Sleep(100L);
	memset(RxBuff, 0x0, sizeof(RxBuff));
	nReadCnt = 0;
	nStartTrack = 300;
	nReadWordCnt = 39;
	if ((nResult = Read(RxBuff, nStartTrack, nReadWordCnt, 'D', &nReadCnt)) != TRUE)
	{
		//m_pDoc->m_ConveyorExtraInfo[m_nNum].m_bLive = FALSE;
		return nResult;
	}

	for (i=0; i<nReadCnt; i++)
	{
		if (RxBuff[i] > 0x80)	RxBuff[i] ^= 0x80;
	}

	//m_pDoc->m_ConveyorExtraInfo[m_nNum].m_bLive = TRUE;

	ParsingExtraFrame(RxBuff + 5);

	return TRUE;
}
*/
int CConveyor::ReadStatus1()
{
	CString strLog;

	//BYTE RxBuff[4096];
	BYTE RxBuff[10000];
	memset(RxBuff, 0x0, sizeof(RxBuff));

	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 2, CV_1_TRACK_CNT*2) == FALSE )
	{
		strLog.Format("ReadStatus1.. CV#%d 트랙정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingFrameE(RxBuff);

	//if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 160, 16) == FALSE )
	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 160, 21) == FALSE )
	{
		strLog.Format("ReadStatus1.. CV#%d 상태정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingExtraFrame1(RxBuff);

	return TRUE;
}

int CConveyor::ReadStatus2()
{
	CString strLog;

	//BYTE RxBuff[4096];
	BYTE RxBuff[10000];
	memset(RxBuff, 0x0, sizeof(RxBuff));

	//if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 10, 70*10) == FALSE )
	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 10, 76*10) == FALSE )
	{
		strLog.Format("ReadStatus2.. CV#%d 트랙정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	//ParsingFrame2(RxBuff, 901-1, 70);
	ParsingFrame2(RxBuff, 901-1, 76);

	//if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 710, 76*10) == FALSE )
	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 770, 76*10) == FALSE )
	{
		strLog.Format("ReadStatus2.. CV#%d 트랙정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	//ParsingFrame2(RxBuff, 971-1, 76);
	ParsingFrame2(RxBuff, 977-1, 76);

	return TRUE;
}


/* int CConveyor::ReadStatus2()
{
	CString strLog;

	BYTE RxBuff[4096];
	memset(RxBuff, 0x0, sizeof(RxBuff));

	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 150, 30) == FALSE )
	{
		strLog.Format("ReadStatus2.. Line CV#%d 트랙정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingExtraFrame2(RxBuff);

	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 180, 5) == FALSE )
	{
		strLog.Format("ReadStatus2.. Line CV #%d-1 상태정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingExtraFrame2_1(RxBuff);

	return TRUE;
} */

int CConveyor::ReadStatus3()
{
	CString strLog;

	//BYTE RxBuff[4096];
	BYTE RxBuff[10000];
	memset(RxBuff, 0x0, sizeof(RxBuff));

	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 302, CV_3_TRACK_CNT*2) == FALSE )
	{
		strLog.Format("ReadStatus3.. CV#%d 트랙정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingFrameE(RxBuff);

	//if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 420, 13) == FALSE )
	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 420, 16) == FALSE )
	{
		strLog.Format("ReadStatus3.. CV#%d 상태정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingExtraFrame3(RxBuff);

	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 400, 4) == FALSE )
	{
		strLog.Format("ReadStatus3.. CV#%d Count 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingCount(RxBuff);

	return TRUE;
}

int CConveyor::ReadStatus4()
{
	CString strLog;

	//BYTE RxBuff[4096];
	BYTE RxBuff[10000];
	memset(RxBuff, 0x0, sizeof(RxBuff));

	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 2, CV_4_TRACK_CNT*2) == FALSE )
	{
		strLog.Format("ReadStatus4.. CV#%d 트랙정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingFrameE(RxBuff);

	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 200, 18) == FALSE )
	{
		strLog.Format("ReadStatus4.. CV#%d 상태정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingExtraFrame4(RxBuff);

	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 218, 2) == FALSE )
	{
		strLog.Format("ReadStatus4.. CV#%d 버퍼구간 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingBufferLine4(RxBuff);

	return TRUE;
}

int CConveyor::ReadStatus5()
{
	CString strLog;

	//BYTE RxBuff[4096];
	BYTE RxBuff[10000];
	memset(RxBuff, 0x0, sizeof(RxBuff));

	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 2, CV_5_TRACK_CNT*2) == FALSE )
	{
		strLog.Format("ReadStatus5.. CV#%d 트랙정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingFrameE(RxBuff);

	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 200, 18) == FALSE )
	{
		strLog.Format("ReadStatus5.. CV#%d 상태정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingExtraFrame5(RxBuff);

	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 218, 2) == FALSE )
	{
		strLog.Format("ReadStatus5.. CV#%d 버퍼구간 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingBufferLine5(RxBuff);

	return TRUE;
}

int CConveyor::ReadStatus6()
{
	CString strLog;

	//BYTE RxBuff[4096];
	BYTE RxBuff[10000];
	memset(RxBuff, 0x0, sizeof(RxBuff));

	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 2, CV_6_TRACK_CNT*2) == FALSE )
	{
		strLog.Format("ReadStatus6.. CV#%d 트랙정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingFrameE(RxBuff);

	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 200, 18) == FALSE )
	{
		strLog.Format("ReadStatus6.. CV#%d 상태정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingExtraFrame6(RxBuff);

	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 218, 2) == FALSE )
	{
		strLog.Format("ReadStatus6.. CV#%d 버퍼구간 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingBufferLine6(RxBuff);

	return TRUE;
}

int CConveyor::ReadStatus7()
{
	CString strLog, strBuff;

	//BYTE RxBuff[4096];
	BYTE RxBuff[10000];

	memset(RxBuff, 0x0, sizeof(RxBuff));
	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 10, 960) == FALSE )
	{
		strLog.Format("ReadStatus7.. CV#%d 상태정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingFrame7(RxBuff, 700, 96);

	//if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 970, 260) == FALSE )
	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 970, 410) == FALSE )
	{
		strLog.Format("ReadStatus7.. CV#%d 상태정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	//ParsingFrame7(RxBuff, 796, 26);
	ParsingFrame7(RxBuff, 796, 41);


	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 2, 2) == FALSE )
	{
		strLog.Format("ReadStatus7.. CV#%d 기타 설비 상태정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingStatus7(RxBuff);


	return TRUE;
}

int CConveyor::ReadStatus8()
{
	CString strLog, strBuff;

	//BYTE RxBuff[4096];
	BYTE RxBuff[10000];

	memset(RxBuff, 0x0, sizeof(RxBuff));
	//if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 10, 960) == FALSE )
	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 10, 300) == FALSE ) //PLC가 틀린 것이라 한번에 읽어 오는 길이가가 작다. (720Word) 싸구려를 쓴것임. 
	{
		strLog.Format("ReadStatus8.. CV#%d 상태정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingFrame8(RxBuff, 2000, CV_8_TRACK_CNT);


	if( Read(CMD_WORD_UNIT, RxBuff, DEVICE_CODE_D, 3, 2) == FALSE )
	{
		strLog.Format("ReadStatus8.. CV#%d 기타 설비 상태정보 수신 실패.. [%s]", m_nNum+1, m_strErrMsg);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}
	ParsingStatus8(RxBuff);		

	return TRUE;
}

void CConveyor::ParsingFrame(BYTE * pRxBuff, int nFromTrackNum, int nCnt)
{
	int	nTrackNum = nFromTrackNum - 1;
    for ( int i = 0; i < nCnt; i++ )
	{
		CString	strFrame;
		strFrame.Format("%.8s", pRxBuff + i * 8);
		int nLuggNum  = atoi(strFrame.Mid(0, 4));
		int nJobType  = atoi(strFrame.Mid(4, 2));
		int nDestPos  = atoi(strFrame.Mid(6, 2));

		if (TRACK_INFO[nTrackNum].m_nLuggNum != nLuggNum)
		{
			TRACK_INFO[nTrackNum].m_nLuggNum  = nLuggNum;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nJobType != nJobType)
		{
			TRACK_INFO[nTrackNum].m_nJobType  = nJobType;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nDestPos != nDestPos)
		{
			TRACK_INFO[nTrackNum].m_nDestPos = nDestPos;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}		
		nTrackNum ++;
    }
}

void CConveyor::ParsingFrameE(BYTE *pRxBuff)
{
	int nTrackNum = CLib::GetStartTrackNumPerCvPlc(m_nNum);

    for ( int i = 0; i < CLib::GetTrackCntPerCvPlc(m_nNum); i++ ) 
	{
		CString	strFrame;
		strFrame.Format("%.8s", pRxBuff + i * 8);

	    int nLuggNum    = pRxBuff[1 + i*4] * 100 + pRxBuff[i*4];
        int nDestPos    = pRxBuff[2 + i*4] & 0x0f;
        int nStartPos   = (pRxBuff[2 + i*4] >> 4) & 0x0f;
        int nJobType    = (pRxBuff[3 + i*4] >> 4) & 0x0f;
		int nLastPallet = pRxBuff[3 + i*4] & 0x0f;

		if (TRACK_INFO[nTrackNum].m_nLuggNum != nLuggNum)
		{
			TRACK_INFO[nTrackNum].m_nLuggNum  = nLuggNum;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;

			if(nTrackNum == 9-1 && nLuggNum != 0 && m_pDoc->m_pHostCl != NULL)
				m_pDoc->m_pHostCl->Status(TRUE);
		}

		if (TRACK_INFO[nTrackNum].m_nJobType != nJobType)
		{
			TRACK_INFO[nTrackNum].m_nJobType  = nJobType;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nStartPos != nStartPos)
		{
			TRACK_INFO[nTrackNum].m_nStartPos  = nStartPos;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nDestPos != nDestPos)
		{
			TRACK_INFO[nTrackNum].m_nDestPos = nDestPos;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nLastPallet != nLastPallet)
		{
			TRACK_INFO[nTrackNum].m_nLastPallet = nLastPallet;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		nTrackNum ++;
    }
	
//	if(m_nNum == 2)
//		m_pDoc->m_n4GroupInCount   = pRxBuff[33] * 100 + pRxBuff[32]; // D216
}

void CConveyor::ParsingFrame2(BYTE *pRxBuff, int nFromTrackNum, int nCnt)
{
	int	nTrackNum = nFromTrackNum;
 
	for ( int i = 0; i < nCnt; i++ ) 
	{
        int nLuggNum    = pRxBuff[1 + i*20] * 100 + pRxBuff[i*20];
		int nStartPos   = pRxBuff[2 + i*20] & 0xFF;
        int nJobType    = pRxBuff[3 + i*20] & 0xFF;
        int nDestPos    = pRxBuff[4 + i*20] & 0xFF;
	    int nComplete   = pRxBuff[5 + i*20] & 0xFF;

		WORD wPlcCount = SwapToWord(pRxBuff + 6 + i*20);
		if (TRACK_INFO[nTrackNum].m_wPlcCount != wPlcCount)
		{
			TRACK_INFO[nTrackNum].m_wPlcCount = wPlcCount;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		WORD wStackLevel = SwapToWord(pRxBuff + 10 + i*20);
		if (TRACK_INFO[nTrackNum].m_wStackLevel != wStackLevel)
		{
			TRACK_INFO[nTrackNum].m_wStackLevel = wStackLevel;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

        //int nSize       = (pRxBuff[4 + i*20] >> 4) & 0xff;
		//int nComplete   = pRxBuff[5 + i*20] & 0xFF;

 		if (TRACK_INFO[nTrackNum].m_nLuggNum != nLuggNum)
		{
			TRACK_INFO[nTrackNum].m_nLuggNum  = nLuggNum;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;

			if(nTrackNum == 902-1 && nLuggNum != 0 && m_pDoc->m_pHostCl != NULL)
				m_pDoc->m_pHostCl->Status(TRUE);
		}


		if (TRACK_INFO[nTrackNum].m_nStartPos != nStartPos)
		{
			TRACK_INFO[nTrackNum].m_nStartPos  = nStartPos;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nJobType != nJobType)
		{
			TRACK_INFO[nTrackNum].m_nJobType  = nJobType;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nDestPos != nDestPos)
		{
			TRACK_INFO[nTrackNum].m_nDestPos = nDestPos;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nComplete != nComplete)
		{
			TRACK_INFO[nTrackNum].m_nComplete = nComplete;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		WORD wErrcode = SwapToWord(pRxBuff + 12 + i*20);
		if (TRACK_INFO[nTrackNum].m_wErrorCode != wErrcode)
		{
			TRACK_INFO[nTrackNum].m_wErrorCode = wErrcode;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}
	
		WORD wWordA = SwapToWord(pRxBuff + 14 + i*20);

		BOOL bStatus = CLib::IsSet(wWordA, 0);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bStoStationReady)
		{
			TRACK_INFO[nTrackNum].m_bStoStationReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;

			if(m_pDoc->m_pHostCl != NULL)
				m_pDoc->m_pHostCl->Status(TRUE);
		}

		bStatus = CLib::IsSet(wWordA, 5);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bPickingStationReady)
		{
			TRACK_INFO[nTrackNum].m_bPickingStationReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;

		/*	if(nTrackNum == 901-1 && nDestPos == 12 && bStatus == TRUE)
			{
				if(WriteTrackInfo2(nTrackNum, 0, 0, 0, 0) == TRUE)
					LOG_JOB(LOG_POS_CV, 0, "ParsingFrame2.. 도착지 12번 CV#901 Data 삭제 성공..");
				else
					LOG_ERROR(LOG_POS_CV, 0, "ParsingFrame2.. 도착지 12번 CV#901 Data 삭제 실패..");
			} */
		}
		
		wWordA = SwapToWord(pRxBuff + 16 + i*20);

		bStatus = CLib::IsSet(wWordA, 0);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bOpMode)
		{
			TRACK_INFO[nTrackNum].m_bOpMode = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 1);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bPltSensor)
		{
			TRACK_INFO[nTrackNum].m_bPltSensor = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		nTrackNum++;
    }
}

void CConveyor::ParsingFrame7(BYTE *pRxBuff, int nFromTrackNum, int nCnt)
{
	int	nTrackNum = nFromTrackNum;
 
	for ( int i = 0; i < nCnt; i++ ) 
	{
        int nLuggNum    = pRxBuff[1 + i*20] * 100 + pRxBuff[i*20];
        int nDestPos    = pRxBuff[2 + i*20] & 0xFF;
		int nStartPos   = pRxBuff[3 + i*20] & 0xFF;
        int nJobType    = pRxBuff[4 + i*20] & 0x0f;
        int nSize       = (pRxBuff[4 + i*20] >> 4) & 0xff;
		int nComplete   = pRxBuff[5 + i*20] & 0xFF;

        int nLuggNum2    = pRxBuff[7 + i*20] * 100 + pRxBuff[6 + i*20];

 		if (TRACK_INFO[nTrackNum].m_nLuggNum != nLuggNum)
		{
			TRACK_INFO[nTrackNum].m_nLuggNum  = nLuggNum;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

 		if (TRACK_INFO[nTrackNum].m_nLuggNum2 != nLuggNum2)
		{
			TRACK_INFO[nTrackNum].m_nLuggNum2  = nLuggNum2;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nStartPos != nStartPos)
		{
			TRACK_INFO[nTrackNum].m_nStartPos  = nStartPos;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nDestPos != nDestPos)
		{
			TRACK_INFO[nTrackNum].m_nDestPos = nDestPos;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nComplete != nComplete)
		{
			TRACK_INFO[nTrackNum].m_nComplete  = nComplete;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nSize != nSize)
		{
			TRACK_INFO[nTrackNum].m_nSize = nSize;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nJobType != nJobType)
		{
			TRACK_INFO[nTrackNum].m_nJobType  = nJobType;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		WORD wPlcCount = SwapToWord(pRxBuff + 10 + i*20);
		if (TRACK_INFO[nTrackNum].m_wPlcCount != wPlcCount)
		{
			TRACK_INFO[nTrackNum].m_wPlcCount = wPlcCount;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		WORD wErrcode = SwapToWord(pRxBuff + 12 + i*20);
		if (TRACK_INFO[nTrackNum].m_wErrorCode != wErrcode)
		{
			TRACK_INFO[nTrackNum].m_wErrorCode = wErrcode;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}
	
		WORD wWordA = SwapToWord(pRxBuff + 14 + i*20);

		BOOL bStatus = CLib::IsSet(wWordA, 0);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bPickingStationReady)
		{
			TRACK_INFO[nTrackNum].m_bPickingStationReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if(!bStatus)
		{
				bStatus = CLib::IsSet(wWordA, 1);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bPickingStationReady)
			{
				TRACK_INFO[nTrackNum].m_bPickingStationReady = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE;
			}
		}

		bStatus = CLib::IsSet(wWordA, 2);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bStoStationReady)
		{
			TRACK_INFO[nTrackNum].m_bStoStationReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;

			if(nTrackNum == 793-1 && bStatus == TRUE && m_pDoc->m_pHostCl != NULL)
				m_pDoc->m_pHostCl->Status(TRUE);
		}
		
		bStatus = CLib::IsSet(wWordA, 3);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bRetStationReady)
		{
			TRACK_INFO[nTrackNum].m_bRetStationReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 4);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bStoHomeStandReady)
		{
			TRACK_INFO[nTrackNum].m_bStoHomeStandReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 5);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bRetHomeStandReady)
		{
			TRACK_INFO[nTrackNum].m_bRetHomeStandReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 6);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bOpMode)
		{
			TRACK_INFO[nTrackNum].m_bOpMode = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

/*
		bStatus = CLib::IsSet(wWordA, 8);
		if(m_pDoc->m_pRgvInfo[0]->m_bRetrieveSuspend && m_nNum == CV_1_PLC && nTrackNum == 100)//rtv비상정지
		{
			if (bStatus ^ m_pDoc->m_bSafetyError[0])
			{
				m_pDoc->m_bSafetyError[0] = bStatus;
				RgvEmergencyStop(bStatus, RGV_1_NUM);
			}
		}
		if(m_pDoc->m_pRgvInfo[1]->m_bRetrieveSuspend && m_nNum == CV_2_PLC && nTrackNum == 200)//rtv비상정지
		{
			if (bStatus ^ m_pDoc->m_bSafetyError[1])
			{
				m_pDoc->m_bSafetyError[1] = bStatus;
				RgvEmergencyStop(bStatus, RGV_2_NUM);
			}
		}
*/
		////////조진영대리를 위하여..
		bStatus = CLib::IsSet(wWordA,10);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bWrapSignalIn1)
		{
			TRACK_INFO[nTrackNum].m_bWrapSignalIn1 = bStatus;
		}

		bStatus = CLib::IsSet(wWordA,11);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bWrapSignalIn2)
		{
			TRACK_INFO[nTrackNum].m_bWrapSignalIn2 = bStatus;
		}

		bStatus = CLib::IsSet(wWordA,12);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bWrapSignalIn3)
		{
			TRACK_INFO[nTrackNum].m_bWrapSignalIn3 = bStatus;
		}

		bStatus = CLib::IsSet(wWordA,13);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bWrapSignalIn4)
		{
			TRACK_INFO[nTrackNum].m_bWrapSignalIn4 = bStatus;
		}
		////////

		wWordA = SwapToWord(pRxBuff + 16 + i*20);
		bStatus = CLib::IsSet(wWordA, 0);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bPltSensor)
		{
			TRACK_INFO[nTrackNum].m_bPltSensor = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 2);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bHomeStandUp)
		{
			TRACK_INFO[nTrackNum].m_bHomeStandUp = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}
		bStatus = CLib::IsSet(wWordA, 4);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bDiverterUp)
		{
			TRACK_INFO[nTrackNum].m_bDiverterUp = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 6);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bRgvInterLock)
		{
			TRACK_INFO[nTrackNum].m_bRgvInterLock = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 7);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bScInterLock)
		{
			TRACK_INFO[nTrackNum].m_bScInterLock = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}
		
		bStatus = CLib::IsSet(wWordA, 8);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bDoorOpen)
		{
			TRACK_INFO[nTrackNum].m_bDoorOpen = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		
		wWordA = SwapToWord(pRxBuff + 18 + i*20);
		bStatus = CLib::IsSet(wWordA, 0);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_nMotorRun1)
		{
			TRACK_INFO[nTrackNum].m_nMotorRun1 = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 1);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_nMotorRun2)
		{
			TRACK_INFO[nTrackNum].m_nMotorRun2 = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 2);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bDoorOpenRequest)
		{
			TRACK_INFO[nTrackNum].m_bDoorOpenRequest = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 3);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bDoorCloseRequest)
		{
			TRACK_INFO[nTrackNum].m_bDoorCloseRequest = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 4);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bRgvInterLockOut)
		{
			TRACK_INFO[nTrackNum].m_bRgvInterLockOut = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 5);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bScInterLockOut)
		{
			TRACK_INFO[nTrackNum].m_bScInterLockOut = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		////////조진영대리를 위하여..
		bStatus = CLib::IsSet(wWordA,10);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bWrapSignalOut1)
		{
			TRACK_INFO[nTrackNum].m_bWrapSignalOut1 = bStatus;
		}

		bStatus = CLib::IsSet(wWordA,11);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bWrapSignalOut2)
		{
			TRACK_INFO[nTrackNum].m_bWrapSignalOut2 = bStatus;
		}

		bStatus = CLib::IsSet(wWordA,12);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bWrapSignalOut3)
		{
			TRACK_INFO[nTrackNum].m_bWrapSignalOut3 = bStatus;
		}

		bStatus = CLib::IsSet(wWordA,13);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bWrapSignalOut4)
		{
			TRACK_INFO[nTrackNum].m_bWrapSignalOut4 = bStatus;
		}
		////////

		nTrackNum++;
    }
}

void CConveyor::ParsingFrame8(BYTE *pRxBuff, int nFromTrackNum, int nCnt)
{
	int	nTrackNum = nFromTrackNum;
 
	for ( int i = 0; i < nCnt; i++ ) 
	{
        int nLuggNum    = pRxBuff[1 + i*20] * 100 + pRxBuff[i*20];
        int nDestPos    = pRxBuff[2 + i*20] & 0xFF;
		int nStartPos   = pRxBuff[3 + i*20] & 0xFF;
        int nJobType    = pRxBuff[4 + i*20] & 0x0f;
        int nSize       = (pRxBuff[4 + i*20] >> 4) & 0xff;
		int nComplete   = pRxBuff[5 + i*20] & 0xFF;

        int nLuggNum2    = pRxBuff[7 + i*20] * 100 + pRxBuff[6 + i*20];

 		if (TRACK_INFO[nTrackNum].m_nLuggNum != nLuggNum)
		{
			TRACK_INFO[nTrackNum].m_nLuggNum  = nLuggNum;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

 		if (TRACK_INFO[nTrackNum].m_nLuggNum2 != nLuggNum2)
		{
			TRACK_INFO[nTrackNum].m_nLuggNum2  = nLuggNum2;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nStartPos != nStartPos)
		{
			TRACK_INFO[nTrackNum].m_nStartPos  = nStartPos;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nDestPos != nDestPos)
		{
			TRACK_INFO[nTrackNum].m_nDestPos = nDestPos;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nComplete != nComplete)
		{
			TRACK_INFO[nTrackNum].m_nComplete  = nComplete;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nSize != nSize)
		{
			TRACK_INFO[nTrackNum].m_nSize = nSize;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if (TRACK_INFO[nTrackNum].m_nJobType != nJobType)
		{
			TRACK_INFO[nTrackNum].m_nJobType  = nJobType;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		WORD wPlcCount = SwapToWord(pRxBuff + 10 + i*20);
		if (TRACK_INFO[nTrackNum].m_wPlcCount != wPlcCount)
		{
			TRACK_INFO[nTrackNum].m_wPlcCount = wPlcCount;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		WORD wErrcode = SwapToWord(pRxBuff + 12 + i*20);
		if (TRACK_INFO[nTrackNum].m_wErrorCode != wErrcode)
		{
			TRACK_INFO[nTrackNum].m_wErrorCode = wErrcode;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}
	
		WORD wWordA = SwapToWord(pRxBuff + 14 + i*20);

		BOOL bStatus = CLib::IsSet(wWordA, 0);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bPickingStationReady)
		{
			TRACK_INFO[nTrackNum].m_bPickingStationReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		if(!bStatus)
		{
				bStatus = CLib::IsSet(wWordA, 1);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bPickingStationReady)
			{
				TRACK_INFO[nTrackNum].m_bPickingStationReady = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE;
			}
		}

		bStatus = CLib::IsSet(wWordA, 2);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bStoStationReady)
		{
			TRACK_INFO[nTrackNum].m_bStoStationReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}
		
		bStatus = CLib::IsSet(wWordA, 3);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bRetStationReady)
		{
			TRACK_INFO[nTrackNum].m_bRetStationReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 4);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bStoHomeStandReady)
		{
			TRACK_INFO[nTrackNum].m_bStoHomeStandReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 5);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bRetHomeStandReady)
		{
			TRACK_INFO[nTrackNum].m_bRetHomeStandReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 6);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bOpMode)
		{
			TRACK_INFO[nTrackNum].m_bOpMode = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		wWordA = SwapToWord(pRxBuff + 16 + i*20);
		bStatus = CLib::IsSet(wWordA, 0);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bPltSensor)
		{
			TRACK_INFO[nTrackNum].m_bPltSensor = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 2);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bHomeStandUp)
		{
			TRACK_INFO[nTrackNum].m_bHomeStandUp = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}
		bStatus = CLib::IsSet(wWordA, 4);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bDiverterUp)
		{
			TRACK_INFO[nTrackNum].m_bDiverterUp = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 6);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bRgvInterLock)
		{
			TRACK_INFO[nTrackNum].m_bRgvInterLock = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 7);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bScInterLock)
		{
			TRACK_INFO[nTrackNum].m_bScInterLock = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}
		
		bStatus = CLib::IsSet(wWordA, 8);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bDoorOpen)
		{
			TRACK_INFO[nTrackNum].m_bDoorOpen = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		
		wWordA = SwapToWord(pRxBuff + 18 + i*20);
		bStatus = CLib::IsSet(wWordA, 0);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_nMotorRun1)
		{
			TRACK_INFO[nTrackNum].m_nMotorRun1 = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 1);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_nMotorRun2)
		{
			TRACK_INFO[nTrackNum].m_nMotorRun2 = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 2);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bDoorOpenRequest)
		{
			TRACK_INFO[nTrackNum].m_bDoorOpenRequest = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 3);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bDoorCloseRequest)
		{
			TRACK_INFO[nTrackNum].m_bDoorCloseRequest = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 4);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bRgvInterLockOut)
		{
			TRACK_INFO[nTrackNum].m_bRgvInterLockOut = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordA, 5);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bScInterLockOut)
		{
			TRACK_INFO[nTrackNum].m_bScInterLockOut = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

		nTrackNum++;
    }
}

void CConveyor::ParsingStatus7(BYTE *pRxBuff)
{
	WORD wWordA = SwapToWord(pRxBuff);

	//Fence Open시 RTV 비상정지
	BOOL bStatus = CLib::IsSet(wWordA, 0);
	if(m_pDoc->m_pRgvInfo[0]->m_bRetrieveSuspend)
	{
		if (bStatus ^ m_pDoc->m_bSafetyError[0])
		{
			m_pDoc->m_bSafetyError[0] = bStatus;
			RgvEmergencyStop(bStatus, RGV_1_NUM);
			//Sleep(900L);
			Sleep(400L);
			RgvEmergencyStop(bStatus, RGV_2_NUM);
		}
	}

	bStatus = CLib::IsSet(wWordA, 1);
	if(m_pDoc->m_pRgvInfo[1]->m_bRetrieveSuspend)
	{
		if (bStatus ^ m_pDoc->m_bSafetyError[1])
		{
			m_pDoc->m_bSafetyError[1] = bStatus;
			RgvEmergencyStop(bStatus, RGV_2_NUM);
			//Sleep(900L);
			Sleep(400L);
			RgvEmergencyStop(bStatus, RGV_1_NUM);
		}
	}

	bStatus = CLib::IsSet(wWordA, 10);
	if (bStatus ^ m_pDoc->m_bRtvCpError[0])
	{
		m_pDoc->m_bRtvCpError[0] = bStatus;
	}

	bStatus = CLib::IsSet(wWordA, 11);
	if (bStatus ^ m_pDoc->m_bRtvCpError[1])
	{
		m_pDoc->m_bRtvCpError[1] = bStatus;
	}
}

void CConveyor::ParsingStatus8(BYTE *pRxBuff)
{
	CString strLog;

	WORD wWordA = SwapToWord(pRxBuff);

	BOOL bStatus = CLib::IsSet(wWordA, 0);

	if (bStatus ^ m_pDoc->m_bAlarmError)
	{
		m_pDoc->m_bAlarmError = bStatus;

		m_pDoc->m_ConveyorThreadInfo[CV_7_PLC].m_PlcCountMsg.nTrackNum = 3;
		m_pDoc->m_ConveyorThreadInfo[CV_7_PLC].m_PlcCountMsg.nPlcCount = m_pDoc->m_bAlarmError;
		m_pDoc->m_ConveyorThreadInfo[CV_7_PLC].m_PlcCountMsg.bModified = TRUE;
		CV_ACTION(CV_7_PLC);

		strLog.Format("ParsingStatus8.. 이동라인 PLC#8 CV Error 발생 PLC#7로 Alarm 신호 보냄..[%d]..", m_pDoc->m_bAlarmError);
		LOG_EVENT(LOG_POS_CV, 0, strLog);

	}

}

void CConveyor::ParsingExtraFrame1(BYTE * pRxBuff)
{
	WORD wWordA = SwapToWord(pRxBuff); //입고대 D160 

	for (int i = 0; i < 2; i++ )
	{
		int	nStationNum = CLib::GetLinearStoStnNumPerCvPlc(m_nNum, i);
		int nTrackNum = CLib::GetTrackByStationNum(nStationNum);
		if(i==1)
			nTrackNum = 9-1;

		BOOL bStatus = CLib::IsSet(wWordA, i);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bStoStationReady)
		{
			TRACK_INFO[nTrackNum].m_bStoStationReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}
	}

/*	BOOL bStatus = CLib::IsSet(wWordA, 5); //외주창고 입출고 Mode
	if (bStatus ^ m_pDoc->m_bStoRetMode)
	{
		m_pDoc->m_bStoRetMode = bStatus;
	} */

	BOOL bStatus = CLib::IsSet(wWordA, 7);
	if (bStatus ^ TRACK_INFO[9-1].m_bPickingStationReady)
	{
		TRACK_INFO[9-1].m_bPickingStationReady = bStatus;
		TRACK_INFO[9-1].m_bModified = TRUE;

		if(bStatus)
		{
			int nJobType = TRACK_INFO[901-1].m_nJobType;

			if(nJobType == 5)
				nJobType = 0;

			if (WriteTrackInfo(9-1, TRACK_INFO[901-1].m_nLuggNum, nJobType, TRACK_INFO[901-1].m_nComplete, TRACK_INFO[901-1].m_nDestPos))
			{
				m_pDoc->m_ConveyorThreadInfo[CV_2_PLC].m_ConveyorMsg.nTrackNum = 901-1;
				m_pDoc->m_ConveyorThreadInfo[CV_2_PLC].m_ConveyorMsg.nLuggNum = 0; 
				m_pDoc->m_ConveyorThreadInfo[CV_2_PLC].m_ConveyorMsg.nJobType = 0;
				m_pDoc->m_ConveyorThreadInfo[CV_2_PLC].m_ConveyorMsg.nStartPos = 0;
				m_pDoc->m_ConveyorThreadInfo[CV_2_PLC].m_ConveyorMsg.nDestPos = 0;
				m_pDoc->m_ConveyorThreadInfo[CV_2_PLC].m_ConveyorMsg.nComplete = 0;
				m_pDoc->m_ConveyorThreadInfo[CV_2_PLC].m_ConveyorMsg.bModified = TRUE;
				CV_ACTION(CV_2_PLC);

				LOG_JOB(LOG_POS_CV, TRACK_INFO[901-1].m_nLuggNum, "ParsingExtraFrame1.. CV#901->CV#9 Data 쓰기 성공..");
			}
			else
			{
				LOG_ERROR(LOG_POS_CV, TRACK_INFO[901-1].m_nLuggNum, "ParsingExtraFrame1.. CV#901->CV#9 Data 쓰기 실패..");
			}
		}
	}

	wWordA = SwapToWord(pRxBuff+2); //출고대 D161
	for ( i = 0; i < 1; i++ )
	{
		int	nStationNum = CLib::GetLinearRetStnNumPerCvPlc(m_nNum, i);
		int nTrackNum = CLib::GetTrackByStationNum(nStationNum);
		BOOL bStatus = CLib::IsSet(wWordA, i);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bRetStationReady)
		{
			TRACK_INFO[nTrackNum].m_bRetStationReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}
	}

	int j = 0;
	wWordA = SwapToWord(pRxBuff+4); //입고 Fork#1 H/S D162
	for ( i = 0, j = 0; i < CLib::GetScCntPerCvPlc(m_nNum); i++ )
	{
		int	nTrackNum = CLib::GetScStoHSTrack(m_nNum, i, TRUE);
		BOOL bStatus = CLib::IsSet(wWordA, j++);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bStoHomeStandReady)
		{
			TRACK_INFO[nTrackNum].m_bStoHomeStandReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

	}
	for ( i = 0, j = 6; i < CLib::GetScCntPerCvPlc(m_nNum); i++ )//입고 Fork#2 H/S D162
	{
		int nTrackNum = CLib::GetScStoHSTrack(m_nNum, i, FALSE);
		bStatus = CLib::IsSet(wWordA, j++);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bStoHomeStandReady)
		{
			TRACK_INFO[nTrackNum].m_bStoHomeStandReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}			
	}

	wWordA = SwapToWord(pRxBuff+8); //D164
	WORD wWordB = SwapToWord(pRxBuff+10); //D165
	for (i = 0; i < CLib::GetOpBoxCntPerCvPlc(m_nNum); i++)
	{
		int nOpBoxNum = i;

		BOOL bStatus = !CLib::IsSet(wWordA, i);
		if (bStatus ^ m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bNormalStatus)
		{
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bNormalStatus = bStatus;
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordB, i);
		if (bStatus ^ m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bAutoMode)
		{
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bAutoMode = bStatus;
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bModified = TRUE;
		}
	}

	for ( j = 0; j < 5; j++ ) 
	{
		wWordA = SwapToWord(pRxBuff + 12 + j*2); //D166 ~ D170
		wWordB = SwapToWord(pRxBuff + 22 + j*2); //D171 ~ D175

        for ( int i = 0; i < 16; i++ ) 
		{
            int nTrackNum = i + j * 16;

            if (nTrackNum >= CLib::GetTrackCntPerCvPlc(m_nNum)+2) break;

			BOOL bStatus = CLib::IsSet(wWordA, i);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bOverTimeErr)
			{
				TRACK_INFO[nTrackNum].m_bOverTimeErr = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE;
			}

			bStatus = CLib::IsSet(wWordB, i);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bOverLoadErr)
			{
				TRACK_INFO[nTrackNum].m_bOverLoadErr = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE; 
			}
        }
	}

	//입고 펜스 오픈 SC 비상정지 
	wWordA = SwapToWord(pRxBuff+40); //D180
	for( i = 0; i < 6; i++ ) 
	{
		BOOL bStatus = !CLib::IsSet(wWordA, i);
		
		if(bStatus ^ m_pDoc->m_bStoSafetyError[i])
		{
			m_pDoc->m_bStoSafetyError[i] = bStatus;

			if(m_pDoc->m_bStoSafetyError[i] == FALSE && m_pDoc->m_pConfig->m_bDebug)
			{
				//m_pDoc->m_StackerThreadInfo[i].m_StackerMsg.nCommand = SC_CMD_ESTOP;
				m_pDoc->m_StackerThreadInfo[i].m_StackerMsg.nCommand = SC_CMD_PAUSE;

				m_pDoc->m_StackerThreadInfo[i].m_StackerMsg.bModified = TRUE;

				SC_ACTION(i);
			}

		}
	}
}

void CConveyor::ParsingExtraFrame2(BYTE * pRxBuff)
{
	WORD wWordA, wWordB, wWordC;

	for (int j = 0; j < 8; j++ ) 
	{
		wWordA = SwapToWord(pRxBuff + j*2); //D150 ~ D157
		wWordB = SwapToWord(pRxBuff + 20 + j*2); //D160 ~ D167
		wWordC = SwapToWord(pRxBuff + 40 + j*2); //D170 ~ D177

        for ( int i = 0; i < 16; i++ ) 
		{
            int nTrackNum = i + j * 16;

			nTrackNum = nTrackNum+900;			

            if (nTrackNum >= 1019) break;

			BOOL bStatus = CLib::IsSet(wWordA, i);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bOverTimeErr)
			{
				TRACK_INFO[nTrackNum].m_bOverTimeErr = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE;
			}
			
			bStatus = CLib::IsSet(wWordB, i);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bPltSensor)
			{
				TRACK_INFO[nTrackNum].m_bPltSensor = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE;
			}

			bStatus = CLib::IsSet(wWordC, i);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bOverLoadErr)
			{
				TRACK_INFO[nTrackNum].m_bOverLoadErr = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE; 
			}
        }
	}
}

void CConveyor::ParsingExtraFrame2_1(BYTE * pRxBuff)
{
	WORD wWordA = SwapToWord(pRxBuff); //D180
	WORD wWordB = SwapToWord(pRxBuff+2); //D181

	WORD wWordD = SwapToWord(pRxBuff+6); //D183
	WORD wWordE = SwapToWord(pRxBuff+8); //D184

	for (int i = 0; i < CLib::GetOpBoxCntPerCvPlc(m_nNum); i++)
	{
		int nOpBoxNum = i + OPBOX_1_CNT;

		BOOL bStatus = !CLib::IsSet(wWordA, i);
		if (bStatus ^ m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bNormalStatus)
		{
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bNormalStatus = bStatus;
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordB, i);
		if (bStatus ^ m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bAutoMode)
		{
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bAutoMode = bStatus;
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bModified = TRUE;
		}
	}

	

	for (i = 0; i < 5; i++)
	{
		int nStackerNum = i + 1049;

		BOOL bStatus = CLib::IsSet(wWordD, i);
		if (bStatus ^ TRACK_INFO[nStackerNum].m_bOpMode)
		{
			TRACK_INFO[nStackerNum].m_bOpMode = bStatus;
			TRACK_INFO[nStackerNum].m_bModified = TRUE;
		}
	}

	for (i = 0; i < 5; i++)
	{
		int nStackerNum = i + 1049;

		BOOL bStatus = CLib::IsSet(wWordE, i);
		if (bStatus ^ TRACK_INFO[nStackerNum].m_bError)
		{
			TRACK_INFO[nStackerNum].m_bError = bStatus;
			TRACK_INFO[nStackerNum].m_bModified = TRUE;
		}
	}

/*	for ( j = 0; j < 5; j++ ) 
	{
		wWordA = SwapToWord(pRxBuff + 12 + j*2); //D166 ~ D170
		wWordB = SwapToWord(pRxBuff + 22 + j*2); //D171 ~ D175

        for ( int i = 0; i < 16; i++ ) 
		{
            int nTrackNum = i + j * 16;

            if (nTrackNum >= CLib::GetTrackCntPerCvPlc(m_nNum)) break;

			BOOL bStatus = CLib::IsSet(wWordA, i);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bOverTimeErr)
			{
				TRACK_INFO[nTrackNum].m_bOverTimeErr = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE;
			}

			bStatus = CLib::IsSet(wWordB, i);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bOverLoadErr)
			{
				TRACK_INFO[nTrackNum].m_bOverLoadErr = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE; 
			}
        }
	}
*/
}

void CConveyor::ParsingExtraFrame3(BYTE * pRxBuff)
{

	int i, j;
	WORD wWordA = SwapToWord(pRxBuff+6); //출고 Fork#2 H/S D423 전
	for (i = 0, j = 0; i < CLib::GetScCntPerCvPlc(m_nNum); i++ )
	{
		int	nTrackNum = CLib::GetScRetHSTrack(m_nNum, i, TRUE);
		BOOL bStatus = CLib::IsSet(wWordA, j++);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bRetHomeStandReady)
		{
			TRACK_INFO[nTrackNum].m_bRetHomeStandReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

	}
	for ( i = 0, j = 6; i < CLib::GetScCntPerCvPlc(m_nNum); i++ )//출고 Fork#1 H/S D423 후
	{
		int nTrackNum = CLib::GetScRetHSTrack(m_nNum, i, FALSE);
		BOOL bStatus = CLib::IsSet(wWordA, j++);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bRetHomeStandReady)
		{
			TRACK_INFO[nTrackNum].m_bRetHomeStandReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}			
	}

	wWordA = SwapToWord(pRxBuff+8); //D424
	WORD wWordB = SwapToWord(pRxBuff+10); //D425
	for (i = 0; i < CLib::GetOpBoxCntPerCvPlc(m_nNum); i++)
	{
		int nOpBoxNum = i + OPBOX_1_CNT + OPBOX_2_CNT;

		BOOL bStatus = !CLib::IsSet(wWordA, i);
		if (bStatus ^ m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bNormalStatus)
		{
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bNormalStatus = bStatus;
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordB, i);
		if (bStatus ^ m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bAutoMode)
		{
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bAutoMode = bStatus;
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bModified = TRUE;
		}
	}

	for ( j = 0; j < 4; j++ ) 
	{
		wWordA = SwapToWord(pRxBuff + 12 + j*2); //D426 ~ D429
		wWordB = SwapToWord(pRxBuff + 20 + j*2); //D430 ~ D433

        for ( int i = 0; i < 16; i++ ) 
		{
            int nTrackNum = i + j * 16;

			nTrackNum = nTrackNum + CV_3_START_TRACK;

            if (nTrackNum >= CLib::GetTrackCntPerCvPlc(m_nNum)+CV_3_START_TRACK) break;

			BOOL bStatus = CLib::IsSet(wWordA, i);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bOverTimeErr)
			{
				TRACK_INFO[nTrackNum].m_bOverTimeErr = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE;
			}

			bStatus = CLib::IsSet(wWordB, i);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bOverLoadErr)
			{
				TRACK_INFO[nTrackNum].m_bOverLoadErr = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE; 
			}
        }
	}

	//출고 펜스 오픈 SC 비상정지 
	wWordA = SwapToWord(pRxBuff+30); //D435
	for( i = 0; i < 6; i++ ) 
	{
		BOOL bStatus = !CLib::IsSet(wWordA, i);

		if(bStatus ^ m_pDoc->m_bRetSafetyError[i])
		{
			m_pDoc->m_bRetSafetyError[i] = bStatus;
			
			if(m_pDoc->m_bRetSafetyError[i] == FALSE && m_pDoc->m_pConfig->m_bDebug)
			{
				//m_pDoc->m_StackerThreadInfo[i].m_StackerMsg.nCommand = SC_CMD_ESTOP;
				m_pDoc->m_StackerThreadInfo[i].m_StackerMsg.nCommand = SC_CMD_PAUSE;
				SC_ACTION(i);
			}
			
		}
	}
}

void CConveyor::ParsingCount(BYTE * pRxBuff)
{

	if(pRxBuff[1] > 0)
	{
		m_pDoc->m_n4GroupInCount   = (pRxBuff[1] * 256) + pRxBuff[0]; // D400
	}
	else if(pRxBuff[1] == 0)
	{
		m_pDoc->m_n4GroupInCount   = pRxBuff[1] + pRxBuff[0]; // D400
	}

	if(pRxBuff[3] > 0)
	{
		m_pDoc->m_n5GroupInCount   = (pRxBuff[3] * 256) + pRxBuff[2]; // D401
	}
	else if(pRxBuff[3] == 0)
	{
		m_pDoc->m_n5GroupInCount   = pRxBuff[3] + pRxBuff[2]; // D401
	}

	if(pRxBuff[5] > 0)
	{
		m_pDoc->m_n6GroupInCount   = (pRxBuff[5] * 256) + pRxBuff[4]; // D402
	}
	else if(pRxBuff[5] == 0)
	{
		m_pDoc->m_n6GroupInCount   = pRxBuff[5] + pRxBuff[4]; // D402
	}

	if(pRxBuff[7] > 0)
	{
		m_pDoc->m_n7GroupInCount   = (pRxBuff[7] * 256) + pRxBuff[6]; // D403
	}
	else if(pRxBuff[7] == 0)
	{
		m_pDoc->m_n7GroupInCount   = pRxBuff[7] + pRxBuff[6]; // D403
	}

}

void CConveyor::ParsingExtraFrame4(BYTE * pRxBuff)
{
	int i, j;

	WORD wWordA = SwapToWord(pRxBuff); //입고대 D200
	for (i = 0, j = 0; i < 1; i++ )
	{
		int	nTrackNum = 401 -1;
		BOOL bStatus = CLib::IsSet(wWordA, j++);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bStoHomeStandReady)
		{
			TRACK_INFO[nTrackNum].m_bStoHomeStandReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

	}
	     wWordA = SwapToWord(pRxBuff+4); //D202
	WORD wWordB = SwapToWord(pRxBuff+6); //D203
	for (i = 0; i < CLib::GetOpBoxCntPerCvPlc(m_nNum); i++)
	{
		int nOpBoxNum = i + OPBOX_1_CNT + OPBOX_2_CNT + OPBOX_3_CNT;

		BOOL bStatus = !CLib::IsSet(wWordA, i);
		if (bStatus ^ m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bNormalStatus)
		{
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bNormalStatus = bStatus;
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordB, i);
		if (bStatus ^ m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bAutoMode)
		{
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bAutoMode = bStatus;
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bModified = TRUE;
		}
	}

	for (j = 0; j < 6; j++ ) 
	{
		wWordA = SwapToWord(pRxBuff + 8 + j*2); //D204 ~ D209
		wWordB = SwapToWord(pRxBuff + 20 + j*2); //D210 ~ D215

        for ( int i = 0; i < 16; i++ ) 
		{
            int nTrackNum = i + j * 16;

			nTrackNum = nTrackNum + CV_4_START_TRACK;

			//if(nTrackNum == 486 || nTrackNum == 487){

            if (nTrackNum >= (CLib::GetTrackCntPerCvPlc(m_nNum)+CV_4_START_TRACK+2)) break;

			BOOL bStatus = CLib::IsSet(wWordA, i);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bOverTimeErr)
			{
				TRACK_INFO[nTrackNum].m_bOverTimeErr = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE;
			}

			bStatus = CLib::IsSet(wWordB, i);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bOverLoadErr)
			{
				TRACK_INFO[nTrackNum].m_bOverLoadErr = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE; 
			}
			//}
        }
	}

//	m_pDoc->m_n4GroupInCount   = pRxBuff[33] * 100 + pRxBuff[32]; // D216
    m_pDoc->m_n4GroupOutCount  = pRxBuff[35] * 100 + pRxBuff[34]; // D217

	m_pDoc->m_n4GroupInternalCount = m_pDoc->m_n4GroupInCount - (m_pDoc->m_n4GroupOutCount*2);
}

void CConveyor::ParsingExtraFrame5(BYTE * pRxBuff)
{
	int i, j;

	WORD wWordA = SwapToWord(pRxBuff); //입고대 D200
	for (i = 0, j = 0; i < 1; i++ )
	{
		int	nTrackNum = 501 -1;
		BOOL bStatus = CLib::IsSet(wWordA, j++);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bStoHomeStandReady)
		{
			TRACK_INFO[nTrackNum].m_bStoHomeStandReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

	}

		 wWordA = SwapToWord(pRxBuff+4); //D202
	WORD wWordB = SwapToWord(pRxBuff+6); //D203
	for ( i = 0; i < CLib::GetOpBoxCntPerCvPlc(m_nNum); i++)
	{
		int nOpBoxNum = i + OPBOX_1_CNT + OPBOX_2_CNT + OPBOX_3_CNT + OPBOX_4_CNT;

		BOOL bStatus = !CLib::IsSet(wWordA, i);
		if (bStatus ^ m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bNormalStatus)
		{
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bNormalStatus = bStatus;
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordB, i);
		if (bStatus ^ m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bAutoMode)
		{
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bAutoMode = bStatus;
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bModified = TRUE;
		}
	}

	for ( j = 0; j < 6; j++ ) 
	{
		wWordA = SwapToWord(pRxBuff + 8 + j*2); //D204 ~ D209
		wWordB = SwapToWord(pRxBuff + 20 + j*2); //D210 ~ D215

        for ( int i = 0; i < 16; i++ ) 
		{
            int nTrackNum = i + j * 16;

			nTrackNum = nTrackNum + CV_5_START_TRACK;

            if (nTrackNum >= (CLib::GetTrackCntPerCvPlc(m_nNum)+CV_5_START_TRACK+2)) break;

			BOOL bStatus = CLib::IsSet(wWordA, i);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bOverTimeErr)
			{
				TRACK_INFO[nTrackNum].m_bOverTimeErr = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE;
			}

			bStatus = CLib::IsSet(wWordB, i);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bOverLoadErr)
			{
				TRACK_INFO[nTrackNum].m_bOverLoadErr = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE; 
			}
        }
	}

//	m_pDoc->m_n5GroupInCount   = pRxBuff[33] * 100 + pRxBuff[32]; // D216
    m_pDoc->m_n5GroupOutCount  = pRxBuff[35] * 100 + pRxBuff[34]; // D217

	m_pDoc->m_n5GroupInternalCount = m_pDoc->m_n5GroupInCount - (m_pDoc->m_n5GroupOutCount*2);
}

void CConveyor::ParsingExtraFrame6(BYTE * pRxBuff)
{
	int i, j;

	WORD wWordA = SwapToWord(pRxBuff); //입고대 D200
	for (i = 0, j = 0; i < 1; i++ )
	{
		int	nTrackNum = 601 -1;
		BOOL bStatus = CLib::IsSet(wWordA, j++);
		if (bStatus ^ TRACK_INFO[nTrackNum].m_bStoHomeStandReady)
		{
			TRACK_INFO[nTrackNum].m_bStoHomeStandReady = bStatus;
			TRACK_INFO[nTrackNum].m_bModified = TRUE;
		}

	}

		 wWordA = SwapToWord(pRxBuff+4); //D202
	WORD wWordB = SwapToWord(pRxBuff+6); //D203
	for ( i = 0; i < CLib::GetOpBoxCntPerCvPlc(m_nNum); i++)
	{
		int nOpBoxNum = i + OPBOX_1_CNT + OPBOX_2_CNT + OPBOX_3_CNT + OPBOX_4_CNT + OPBOX_5_CNT;

		BOOL bStatus = !CLib::IsSet(wWordA, i);
		if (bStatus ^ m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bNormalStatus)
		{
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bNormalStatus = bStatus;
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bModified = TRUE;
		}

		bStatus = CLib::IsSet(wWordB, i);
		if (bStatus ^ m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bAutoMode)
		{
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bAutoMode = bStatus;
			m_pDoc->m_OpBoxInfo[nOpBoxNum].m_bModified = TRUE;
		}
	}

	for (j = 0; j < 6; j++ ) 
	{
		wWordA = SwapToWord(pRxBuff + 8 + j*2); //D204 ~ D209
		wWordB = SwapToWord(pRxBuff + 20 + j*2); //D210 ~ D215

        for ( int i = 0; i < 16; i++ ) 
		{
            int nTrackNum = i + j * 16;

			nTrackNum = nTrackNum + CV_6_START_TRACK;

            if (nTrackNum >= (CLib::GetTrackCntPerCvPlc(m_nNum)+CV_6_START_TRACK+2)) break;

			BOOL bStatus = CLib::IsSet(wWordA, i);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bOverTimeErr)
			{
				TRACK_INFO[nTrackNum].m_bOverTimeErr = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE;
			}

			bStatus = CLib::IsSet(wWordB, i);
			if (bStatus ^ TRACK_INFO[nTrackNum].m_bOverLoadErr)
			{
				TRACK_INFO[nTrackNum].m_bOverLoadErr = bStatus;
				TRACK_INFO[nTrackNum].m_bModified = TRUE; 
			}
        }
	}

//	m_pDoc->m_n6GroupInCount   = pRxBuff[33] * 100 + pRxBuff[32]; // D216
    m_pDoc->m_n6GroupOutCount  = pRxBuff[35] * 100 + pRxBuff[34]; // D217

	m_pDoc->m_n6GroupInternalCount = m_pDoc->m_n6GroupInCount - (m_pDoc->m_n6GroupOutCount*2);
}

void CConveyor::ParsingBufferLine4(BYTE * pRxBuff)
{
	WORD wWordA = SwapToWord(pRxBuff); //D218
	WORD wWordB = SwapToWord(pRxBuff+2); //D219
	for (int i = 0; i < 6; i++)
	{
		switch(i)
		{
			case 0:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10; j++)
				{
					int nTrackNum = 460;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
			case 1:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10;j++)
				{
					int nTrackNum = 450;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
			case 2:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10;j++)
				{
					int nTrackNum = 440;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
			case 3:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10;j++)
				{
					int nTrackNum = 430;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
			case 4:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10;j++)
				{
					int nTrackNum = 420;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
			case 5:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10;j++)
				{
					int nTrackNum = 410;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
		}

	}

	for (i = 0; i < 6; i++)
	{
		BOOL bStatus = CLib::IsSet(wWordB, i);
		if (bStatus ^ m_pDoc->m_b4groupBuffIn[i])
		{
			m_pDoc->m_b4groupBuffIn[i] = bStatus;
		}
	}
}

void CConveyor::ParsingBufferLine5(BYTE * pRxBuff)
{
	WORD wWordA = SwapToWord(pRxBuff); //D218
	WORD wWordB = SwapToWord(pRxBuff+2); //D219
	for (int i = 0; i < 6; i++)
	{
		switch(i)
		{
			case 0:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10; j++)
				{
					int nTrackNum = 560;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
			case 1:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10;j++)
				{
					int nTrackNum = 550;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
			case 2:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10;j++)
				{
					int nTrackNum = 540;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
			case 3:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10;j++)
				{
					int nTrackNum = 530;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
			case 4:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10;j++)
				{
					int nTrackNum = 520;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
			case 5:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10;j++)
				{
					int nTrackNum = 510;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
		}

	}

	for (i = 0; i < 6; i++)
	{
		BOOL bStatus = CLib::IsSet(wWordB, i);
		if (bStatus ^ m_pDoc->m_b5groupBuffIn[i])
		{
			m_pDoc->m_b5groupBuffIn[i] = bStatus;
		}
	}
}

void CConveyor::ParsingBufferLine6(BYTE * pRxBuff)
{
	WORD wWordA = SwapToWord(pRxBuff); //D218
	WORD wWordB = SwapToWord(pRxBuff+2); //D219
	for (int i = 0; i < 6; i++)
	{
		switch(i)
		{
			case 0:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10; j++)
				{
					int nTrackNum = 660;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
			case 1:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10;j++)
				{
					int nTrackNum = 650;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
			case 2:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10;j++)
				{
					int nTrackNum = 640;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
			case 3:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10;j++)
				{
					int nTrackNum = 630;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
			case 4:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10;j++)
				{
					int nTrackNum = 620;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
			case 5:
			{
				BOOL bStatus = CLib::IsSet(wWordA, i);
				for(int j = 0; j < 10;j++)
				{
					int nTrackNum = 610;
					if (bStatus ^ TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble)
					{
						TRACK_INFO[j+nTrackNum-1].m_bBuffTrouble = bStatus;
						TRACK_INFO[j+nTrackNum-1].m_bModified = TRUE; 
					}
				}
			}
			break;
		}

	}

	for (i = 0; i < 6; i++)
	{
		BOOL bStatus = CLib::IsSet(wWordB, i);
		if (bStatus ^ m_pDoc->m_b6groupBuffIn[i])
		{
			m_pDoc->m_b6groupBuffIn[i] = bStatus;
		}
	}
}

void CConveyor::ArrivedCheck1()
{
	CString strLog, strTemp="출고: ";

	for (int i=0; i<1; i++)
	{
		int nTrackNum = 817 - 1;
		int nCurLuggNum = TRACK_INFO[nTrackNum].m_nLuggNum;

		if ( nCurLuggNum == 0 ) m_nArrivedLuggNum1 = 0;
		if ( nCurLuggNum == m_nArrivedLuggNum1 )			continue;

		CMoveJobItem *pMoveJobItem = MOVEJOB->Find(nCurLuggNum);

		if ( pMoveJobItem == NULL )								
			continue;

		if (pMoveJobItem->GetPattern() == JOB_PATTERN_STO)		
			continue;

		if (pMoveJobItem->m_nJobType == JOB_TYPE_STN_TO_STN)
		{
			m_pDoc->m_pLog->Job(LOG_POS_SYSTEM, nCurLuggNum, "Job Complete.. 외주 출고대 도착..");
			
			pMoveJobItem->m_nStatus = JOB_STA_COMPLETE;

			m_pDoc->m_strCodeNum = "";
			m_pDoc->m_nPeriodNum = 0;
			m_pDoc->m_strProdName = "";
			m_pDoc->m_strQuantity = ""; //수량 
			m_pDoc->m_strLineNum = "";  //생산라인 
			m_pDoc->m_strCheckNum = ""; //전표번호 

			m_pDoc->m_strCodeNum = pMoveJobItem->m_strProductID;
			m_pDoc->m_nPeriodNum = pMoveJobItem->m_nPriority;
			m_pDoc->m_strProdName = pMoveJobItem->m_strGrade;
			m_pDoc->m_strQuantity = pMoveJobItem->m_strQuantity; //수량 
			m_pDoc->m_strLineNum = pMoveJobItem->m_strLocation;  //생산라인 
			m_pDoc->m_strCheckNum = pMoveJobItem->m_strSecondLoc; //전표번호 

			if(pMoveJobItem->m_nLineNum == 11)
			{
				m_pDoc->m_strCodeNum = "";
				m_pDoc->m_nPeriodNum = 0;
				m_pDoc->m_strProdName = "";
				m_pDoc->m_strQuantity = ""; //수량 
				m_pDoc->m_strLineNum = "";  //생산라인 
				m_pDoc->m_strCheckNum = ""; //전표번호 


				m_pDoc->m_strCodeNum = pMoveJobItem->m_strProductID;
				m_pDoc->m_nPeriodNum = pMoveJobItem->m_nHeight;

				pMoveJobItem->m_strGrade.TrimRight();
				strTemp += pMoveJobItem->m_strGrade;
				m_pDoc->m_strProdName = strTemp;
			}


			if(m_pDoc->m_pHostCl != NULL) 
			{
				//if(pMoveJobItem->m_nBatchNo != 11)
				if(pMoveJobItem->m_nLineNum != 11)
				{
					if(TRACK_INFO[nTrackNum].m_nLuggNum !=0 && TRACK_INFO[nTrackNum].m_nLuggNum2 == 0)
						m_pDoc->m_pHostCl->Arrived(nCurLuggNum);

					if(TRACK_INFO[nTrackNum].m_nLuggNum !=0 && TRACK_INFO[nTrackNum].m_nLuggNum2 != 0)
						m_pDoc->m_pHostCl->Arrived2(nCurLuggNum, TRACK_INFO[nTrackNum].m_nLuggNum2);
				}

				//Sleep(500);
				MOVEJOB->Remove(pMoveJobItem);

				if(TRACK_INFO[nTrackNum].m_nLuggNum2 !=0 )
					MOVEJOB->Remove(TRACK_INFO[nTrackNum].m_nLuggNum2);
			}

			if ( m_pDoc->m_pEcsCl != NULL)
				m_pDoc->m_pEcsCl->EcsClientSendData();

			m_nArrivedLuggNum1 = nCurLuggNum;
		}
		else if(pMoveJobItem->m_nJobType == JOB_TYPE_MANUAL_STN_TO_STN)
		{

			m_pDoc->m_strCodeNum = "";
			m_pDoc->m_nPeriodNum = 0;
			m_pDoc->m_strProdName = "";

			m_pDoc->m_strQuantity = ""; //수량 
			m_pDoc->m_strLineNum = "";  //생산라인 
			m_pDoc->m_strCheckNum = ""; //전표번호 

			if (m_pDoc->m_pEcsCl != NULL)
				m_pDoc->m_pEcsCl->EcsClientSendData();

			m_pDoc->m_pLog->Job(LOG_POS_SYSTEM, nCurLuggNum, "수동 Job Complete..외주 출고대 도착..");
			//m_pDoc->m_pJob->m_nResultCount[pJobItem->GetStackerNum()]++;
			//::PostMessage(m_pDoc->m_hwndView, WM_USER_JOB_NOTIFY, JOB_RESULT_DRAW, 0);
			MOVEJOB->Remove(pMoveJobItem);

				if(TRACK_INFO[nTrackNum].m_nLuggNum2 !=0 )
					MOVEJOB->Remove(TRACK_INFO[nTrackNum].m_nLuggNum2);

			m_nArrivedLuggNum1 = nCurLuggNum;
		}
	}
}

void CConveyor::ArrivedCheck2()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		int nTrackNum = 816 - 1;
		int nCurLuggNum = TRACK_INFO[nTrackNum].m_nLuggNum;

		if ( nCurLuggNum == 0 ) m_nArrivedLuggNum2 = 0;
		if ( nCurLuggNum == m_nArrivedLuggNum2 )			continue;

		CMoveJobItem *pMoveJobItem = MOVEJOB->Find(nCurLuggNum);

		if ( pMoveJobItem == NULL )								
			continue;

		if (pMoveJobItem->GetPattern() == JOB_PATTERN_STO)		
			continue;

		if (pMoveJobItem->m_nJobType == JOB_TYPE_STN_TO_STN)
		{
			m_pDoc->m_pLog->Job(LOG_POS_SYSTEM, nCurLuggNum, "Job Complete.. 외주 출고대 도착..");
			
			pMoveJobItem->m_nStatus = JOB_STA_COMPLETE;

			if(m_pDoc->m_pHostCl != NULL) 
			{
				//if(pMoveJobItem->m_nBatchNo != 11)
				if(pMoveJobItem->m_nLineNum != 11)
				{
					if(TRACK_INFO[nTrackNum].m_nLuggNum !=0 && TRACK_INFO[nTrackNum].m_nLuggNum2 == 0)
						m_pDoc->m_pHostCl->Arrived(nCurLuggNum);

					if(TRACK_INFO[nTrackNum].m_nLuggNum !=0 && TRACK_INFO[nTrackNum].m_nLuggNum2 != 0)
						m_pDoc->m_pHostCl->Arrived2(nCurLuggNum, TRACK_INFO[nTrackNum].m_nLuggNum2);
				}

				//Sleep(500);
				MOVEJOB->Remove(pMoveJobItem);

				if(TRACK_INFO[nTrackNum].m_nLuggNum2 !=0 )
					MOVEJOB->Remove(TRACK_INFO[nTrackNum].m_nLuggNum2);
			}

			m_nArrivedLuggNum2 = nCurLuggNum;
		}
		else if(pMoveJobItem->m_nJobType == JOB_TYPE_MANUAL_STN_TO_STN)
		{
			m_pDoc->m_pLog->Job(LOG_POS_SYSTEM, nCurLuggNum, "수동 Job Complete..외주 출고대 도착..");
			//m_pDoc->m_pJob->m_nResultCount[pJobItem->GetStackerNum()]++;
			//::PostMessage(m_pDoc->m_hwndView, WM_USER_JOB_NOTIFY, JOB_RESULT_DRAW, 0);
			MOVEJOB->Remove(pMoveJobItem);

				if(TRACK_INFO[nTrackNum].m_nLuggNum2 !=0 )
					MOVEJOB->Remove(TRACK_INFO[nTrackNum].m_nLuggNum2);

			m_nArrivedLuggNum2 = nCurLuggNum;
		}
	}
}

void CConveyor::ArrivedCheck3()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		//int nTrackNum = 2023 - 1;
		int nTrackNum = 2024 - 1;
		int nCurLuggNum = TRACK_INFO[nTrackNum].m_nLuggNum;

		if ( nCurLuggNum == 0 ) m_nArrivedLuggNum3 = 0;
		if ( nCurLuggNum == m_nArrivedLuggNum3 )			
			continue;

		if(TRACK_INFO[nTrackNum].m_nDestPos != 14)
			continue;

		CMoveJobItem *pMoveJobItem = MOVEJOB->Find(nCurLuggNum);
		if(pMoveJobItem == NULL)								
			continue;

		if(pMoveJobItem->GetPattern() == JOB_PATTERN_STO)		
			continue;

		if(pMoveJobItem->m_nLineNum != 4)
			continue;

		if(pMoveJobItem->m_nJobType == JOB_TYPE_STN_TO_STN)
		{
			m_pDoc->m_pLog->Job(LOG_POS_SYSTEM, nCurLuggNum, "Job Complete.. 비상시.. 출하분류대 도착..");
			
			pMoveJobItem->m_nStatus = JOB_STA_COMPLETE;

			if(m_pDoc->m_pHostCl != NULL) 
			{
				if(TRACK_INFO[nTrackNum].m_nLuggNum !=0 )
					m_pDoc->m_pHostCl->Arrived(nCurLuggNum);

				//Sleep(500);

				MOVEJOB->Remove(pMoveJobItem);
			}

			m_nArrivedLuggNum3 = nCurLuggNum;
		}
		else if(pMoveJobItem->m_nJobType == JOB_TYPE_MANUAL_STN_TO_STN)
		{
			m_pDoc->m_pLog->Job(LOG_POS_SYSTEM, nCurLuggNum, "수동 Job Complete..비상시.. 출하분류대 도착..");

			MOVEJOB->Remove(pMoveJobItem);

			m_nArrivedLuggNum3 = nCurLuggNum;
		}
	}
}

void CConveyor::LineCountCheck()
{
	CString strLog;
	int nLineQuantity=0;

	for (int i=0; i<1; i++)
	{

		int nTrackNum = 824 - 1;
		int nCurLuggNum = TRACK_INFO[nTrackNum].m_nLuggNum;

		if ( nCurLuggNum == 0 ) m_nLineCountLuggNum = 0;
		if ( nCurLuggNum == m_nLineCountLuggNum )			
			continue;

		CMoveJobItem *pMoveJobItem = MOVEJOB->Find(nCurLuggNum);

		if (pMoveJobItem == NULL)								
			continue;

		if (pMoveJobItem->GetPattern() == JOB_PATTERN_STO)		
			continue;


		for(int i=0; i<10; i++)
		{
			if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[i])
				nLineQuantity++;
				continue;
		}

		if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[0] && m_pDoc->m_nSetLineCount[0] < 12 && nLineQuantity > 1)
		{
			m_pDoc->m_nSetLineCount[0]++;
			pMoveJobItem->m_nBatchNo = 1;

			strLog.Format("LineCountCheck.. 카운트 체크.. Buffer=[%d], Line=[%d], Count=[%d] ..", pMoveJobItem->m_nLineNum, pMoveJobItem->m_nBatchNo, m_pDoc->m_nSetLineCount[0]);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			if(pMoveJobItem->m_nLastPallet == 1)
			{
				for(int i=0; i<10; i++)
				{
					if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[i])
						m_pDoc->m_nSetLineCount[i] = 0;
				}
			}
		}
		else if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[1] && m_pDoc->m_nSetLineCount[1] < 12 && nLineQuantity > 1)
		{
			m_pDoc->m_nSetLineCount[1]++;
			pMoveJobItem->m_nBatchNo = 2;

			strLog.Format("LineCountCheck.. 카운트 체크.. Buffer=[%d], Line=[%d], Count=[%d] ..", pMoveJobItem->m_nLineNum, pMoveJobItem->m_nBatchNo, m_pDoc->m_nSetLineCount[1]);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			if(pMoveJobItem->m_nLastPallet == 1)
			{
				for(int i=0; i<10; i++)
				{
					if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[i])
						m_pDoc->m_nSetLineCount[i] = 0;
				}
			}
		}
		else if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[2] && m_pDoc->m_nSetLineCount[2] < 12 && nLineQuantity > 1)
		{
			m_pDoc->m_nSetLineCount[2]++;
			pMoveJobItem->m_nBatchNo = 3;

			strLog.Format("LineCountCheck.. 카운트 체크.. Buffer=[%d], Line=[%d], Count=[%d] ..", pMoveJobItem->m_nLineNum, pMoveJobItem->m_nBatchNo, m_pDoc->m_nSetLineCount[2]);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			if(pMoveJobItem->m_nLastPallet == 1)
			{
				for(int i=0; i<10; i++)
				{
					if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[i])
						m_pDoc->m_nSetLineCount[i] = 0;
				}
			}
		}
		else if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[3] && m_pDoc->m_nSetLineCount[3] < 12 && nLineQuantity > 1)
		{
			m_pDoc->m_nSetLineCount[3]++;
			pMoveJobItem->m_nBatchNo = 4;

			strLog.Format("LineCountCheck.. 카운트 체크.. Buffer=[%d], Line=[%d], Count=[%d] ..", pMoveJobItem->m_nLineNum, pMoveJobItem->m_nBatchNo, m_pDoc->m_nSetLineCount[3]);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			if(pMoveJobItem->m_nLastPallet == 1)
			{
				for(int i=0; i<10; i++)
				{
					if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[i])
						m_pDoc->m_nSetLineCount[i] = 0;
				}
			}
		}
		else if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[4] && m_pDoc->m_nSetLineCount[4] < 12 && nLineQuantity > 1)
		{
			m_pDoc->m_nSetLineCount[4]++;
			pMoveJobItem->m_nBatchNo = 5;

			strLog.Format("LineCountCheck.. 카운트 체크.. Buffer=[%d], Line=[%d], Count=[%d] ..", pMoveJobItem->m_nLineNum, pMoveJobItem->m_nBatchNo, m_pDoc->m_nSetLineCount[4]);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			if(pMoveJobItem->m_nLastPallet == 1)
			{
				for(int i=0; i<10; i++)
				{
					if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[i])
						m_pDoc->m_nSetLineCount[i] = 0;
				}
			}
		}
		else if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[5] && m_pDoc->m_nSetLineCount[5] < 12 && nLineQuantity > 1)
		{
			m_pDoc->m_nSetLineCount[5]++;
			pMoveJobItem->m_nBatchNo = 6;

			strLog.Format("LineCountCheck.. 카운트 체크.. Buffer=[%d], Line=[%d], Count=[%d] ..", pMoveJobItem->m_nLineNum, pMoveJobItem->m_nBatchNo, m_pDoc->m_nSetLineCount[5]);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			if(pMoveJobItem->m_nLastPallet == 1)
			{
				for(int i=0; i<10; i++)
				{
					if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[i])
						m_pDoc->m_nSetLineCount[i] = 0;
				}
			}
		}
		else if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[6] && m_pDoc->m_nSetLineCount[6] < 12 && nLineQuantity > 1)
		{
			m_pDoc->m_nSetLineCount[6]++;
			pMoveJobItem->m_nBatchNo = 7;

			strLog.Format("LineCountCheck.. 카운트 체크.. Buffer=[%d], Line=[%d], Count=[%d] ..", pMoveJobItem->m_nLineNum, pMoveJobItem->m_nBatchNo, m_pDoc->m_nSetLineCount[6]);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			if(pMoveJobItem->m_nLastPallet == 1)
			{
				for(int i=0; i<10; i++)
				{
					if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[i])
						m_pDoc->m_nSetLineCount[i] = 0;
				}
			}
		}
		else if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[7] && m_pDoc->m_nSetLineCount[7] < 12 && nLineQuantity > 1)
		{
			m_pDoc->m_nSetLineCount[7]++;
			pMoveJobItem->m_nBatchNo = 8;

			strLog.Format("LineCountCheck.. 카운트 체크.. Buffer=[%d], Line=[%d], Count=[%d] ..", pMoveJobItem->m_nLineNum, pMoveJobItem->m_nBatchNo, m_pDoc->m_nSetLineCount[7]);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			if(pMoveJobItem->m_nLastPallet == 1)
			{
				for(int i=0; i<10; i++)
				{
					if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[i])
						m_pDoc->m_nSetLineCount[i] = 0;
				}
			}
		}
		else if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[8] && m_pDoc->m_nSetLineCount[8] < 12 && nLineQuantity > 1)
		{
			m_pDoc->m_nSetLineCount[8]++;
			pMoveJobItem->m_nBatchNo = 9;

			strLog.Format("LineCountCheck.. 카운트 체크.. Buffer=[%d], Line=[%d], Count=[%d] ..", pMoveJobItem->m_nLineNum, pMoveJobItem->m_nBatchNo, m_pDoc->m_nSetLineCount[8]);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			if(pMoveJobItem->m_nLastPallet == 1)
			{
				for(int i=0; i<10; i++)
				{
					if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[i])
						m_pDoc->m_nSetLineCount[i] = 0;
				}
			}
		}
		else if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[9] && m_pDoc->m_nSetLineCount[9] < 12 && nLineQuantity > 1)
		{
			m_pDoc->m_nSetLineCount[9]++;
			pMoveJobItem->m_nBatchNo = 10;

			strLog.Format("LineCountCheck.. 카운트 체크.. Buffer=[%d], Line=[%d], Count=[%d] ..", pMoveJobItem->m_nLineNum, pMoveJobItem->m_nBatchNo, m_pDoc->m_nSetLineCount[9]);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			if(pMoveJobItem->m_nLastPallet == 1)
			{
				for(int i=0; i<10; i++)
				{
					if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[i])
						m_pDoc->m_nSetLineCount[i] = 0;
				}
			}
		}
		else
		{

			if(nLineQuantity > 1)
			{
				for(int i=0; i<10; i++)
				{
					if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[i] && m_pDoc->m_nSetLineCount[i] >= 12)
						m_pDoc->m_nSetLineCount[i] = 0;
				}

				for(i=0; i<10; i++)
				{
					if(pMoveJobItem->m_nLineNum != m_pDoc->m_nSetLine[i])
						continue;

					if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[i])
					{
						m_pDoc->m_nSetLineCount[i]++;
						pMoveJobItem->m_nBatchNo = i+1;

						strLog.Format("LineCountCheck.. 카운트 체크.. Buffer=[%d], Line=[%d], Count=[%d] ..", pMoveJobItem->m_nLineNum, pMoveJobItem->m_nBatchNo, m_pDoc->m_nSetLineCount[i]);
						LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);
					goto Exit;
					}

				}

			}
			else if(nLineQuantity == 1)
			{
				for(int i=0; i<10; i++)
				{
					if(pMoveJobItem->m_nLineNum != m_pDoc->m_nSetLine[i])
						continue;

					if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[i])
					{
						m_pDoc->m_nSetLineCount[i]++;
						pMoveJobItem->m_nBatchNo = i+1;

						strLog.Format("LineCountCheck.. 카운트 체크.. Buffer=[%d], Line=[%d], Count=[%d] ..", pMoveJobItem->m_nLineNum, pMoveJobItem->m_nBatchNo, m_pDoc->m_nSetLineCount[i]);
						LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

						if(pMoveJobItem->m_nLastPallet == 1)
							m_pDoc->m_nSetLineCount[i] = 0;
					}
				}

			}

		}
Exit:

		m_nLineCountLuggNum = nCurLuggNum;
	}
}


void CConveyor::ArriveRemoveCheck4Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		int nTrackNum = 402 -1;
		int nCurLuggNum = TRACK_INFO[nTrackNum].m_nLuggNum;

		if ( nCurLuggNum == 0 ) m_nArrivedRemoveCheckNum[0] = 0;
		if ( nCurLuggNum == m_nArrivedRemoveCheckNum[0] )			continue;

		CJobItem *pJobItem = JOB->Find(nCurLuggNum);
		if ( pJobItem == NULL )								continue;

		if (pJobItem->GetPattern() == JOB_PATTERN_STO)		continue;

		if (pJobItem->m_nJobType == JOB_TYPE_UNIT_RET)
		{
			strLog.Format("Unit 출고 도착 완료..출하분류대#1 도착..트랙[%d]..", nTrackNum+1);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			m_pDoc->m_pJob->Remove(pJobItem);

			m_nArrivedRemoveCheckNum[0] = nCurLuggNum;
		}
		else if(pJobItem->m_nJobType == JOB_TYPE_RACK_TO_RACK)
		{
			strLog.Format("반자동 출고 도착 완료..출하분류대#1 도착..트랙[%d]..", nTrackNum+1);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			m_pDoc->m_pJob->Remove(pJobItem);

			m_nArrivedRemoveCheckNum[0] = nCurLuggNum;
		}
	}
}

void CConveyor::ArriveRemoveCheck5Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		int nTrackNum = 502 - 1;
		int nCurLuggNum = TRACK_INFO[nTrackNum].m_nLuggNum;

		if ( nCurLuggNum == 0 ) m_nArrivedRemoveCheckNum[1] = 0;
		if ( nCurLuggNum == m_nArrivedRemoveCheckNum[1] )			continue;

		CJobItem *pJobItem = JOB->Find(nCurLuggNum);
		if ( pJobItem == NULL )								continue;

		if (pJobItem->GetPattern() == JOB_PATTERN_STO)		continue;

		if (pJobItem->m_nJobType == JOB_TYPE_UNIT_RET)
		{
			strLog.Format("Unit 출고 도착 완료..출하분류대#2 도착..트랙[%d]..", nTrackNum+1);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			m_pDoc->m_pJob->Remove(pJobItem);

			m_nArrivedRemoveCheckNum[1] = nCurLuggNum;
		}
		else if(pJobItem->m_nJobType == JOB_TYPE_RACK_TO_RACK)
		{
			strLog.Format("반자동 출고 도착 완료..출하분류대#2 도착..트랙[%d]..", nTrackNum+1);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			m_pDoc->m_pJob->Remove(pJobItem);

			m_nArrivedRemoveCheckNum[1] = nCurLuggNum;
		}
	}
}

void CConveyor::ArriveRemoveCheck6Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		int nTrackNum = 602 -1;
		int nCurLuggNum = TRACK_INFO[nTrackNum].m_nLuggNum;

		if ( nCurLuggNum == 0 ) m_nArrivedRemoveCheckNum[2] = 0;
		if ( nCurLuggNum == m_nArrivedRemoveCheckNum[2] )			continue;

		CJobItem *pJobItem = JOB->Find(nCurLuggNum);
		if ( pJobItem == NULL )								continue;

		if (pJobItem->GetPattern() == JOB_PATTERN_STO)		continue;

		if (pJobItem->m_nJobType == JOB_TYPE_UNIT_RET)
		{
			strLog.Format("Unit 출고 도착 완료..출하분류대#3 도착..트랙[%d]..", nTrackNum+1);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			m_pDoc->m_pJob->Remove(pJobItem);

			m_nArrivedRemoveCheckNum[2] = nCurLuggNum;
		}
		else if(pJobItem->m_nJobType == JOB_TYPE_RACK_TO_RACK)
		{
			strLog.Format("반자동 출고 도착 완료..출하분류대#3 도착..트랙[%d]..", nTrackNum+1);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			m_pDoc->m_pJob->Remove(pJobItem);

			m_nArrivedRemoveCheckNum[2] = nCurLuggNum;
		}
	}
}


void CConveyor::ArriveCountCheck()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		int nTrackNum = 330 - 1;
		int nCurLuggNum = TRACK_INFO[nTrackNum].m_nLuggNum;

		if ( nCurLuggNum == 0 ) m_nArrivedCheckLuggNum = 0;
		if ( nCurLuggNum == m_nArrivedCheckLuggNum )			continue;

		CJobItem *pJobItem = JOB->Find(nCurLuggNum);
		if ( pJobItem == NULL )								continue;

		if (pJobItem->GetPattern() == JOB_PATTERN_STO)		continue;

		if (pJobItem->m_nDestPos == IMS_ECS_RET_STATION_201)
		{
			pJobItem->m_nStatus = JOB_STA_CV_MOVE_RET_STATION;

			m_pDoc->m_n4GroupInternalBatch = pJobItem->m_nBatchNo;
			m_pDoc->m_n4GroupInternalPallet = pJobItem->m_nPalletNo;
			
			//int n4GroupCount = ++m_pDoc->m_n4GroupCvCount;

			strLog.Format("Change Status.. Counter..트랙[%d].. Counter[%d]..출하분류대#1..", nTrackNum+1, m_pDoc->m_n4GroupInCount);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			if(pJobItem->m_nPalletNo == m_pDoc->m_n4GroupInCount)
			{
				int nStartPos = CLib::ConvertCustomToPosition(pJobItem->m_nStartPos);
				int nDestPos = CV_RET_STATION_4GROUP;

				if (WriteTrackInfo(nTrackNum, nCurLuggNum, JOB_TYPE_AISLE_TO_AISLE, nStartPos, nDestPos, 1) == TRUE)
				{
					//m_pDoc->m_n4GroupCvCount = 0;

					strLog.Format("CvLastPalletWrite.. 마지막 팔렛으로 쓰기 성공..! 트랙[%d]..BatchNum[%d] 도착지[%s]", nTrackNum+1, pJobItem->m_nBatchNo, pJobItem->GetDestPos());
					LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);

					JOB->Backup();
				}
				else
				{
					strLog.Format("CvLastPalletWrite.. 마지막 팔렛으로 쓰기 실패..! 트랙[%d]..BatchNum[%d] 도착지[%s]", nTrackNum+1, pJobItem->m_nBatchNo, pJobItem->GetDestPos());
					LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);
					continue;
				}
			}
			else
			{
				int nStartPos = CLib::ConvertCustomToPosition(pJobItem->m_nStartPos);
				int nDestPos = CV_RET_STATION_4GROUP;

				if (WriteTrackInfo(nTrackNum, nCurLuggNum, pJobItem->m_nJobType, nStartPos, nDestPos, 2) == TRUE)
				{
					//m_pDoc->m_n4GroupCvCount = 0;

					strLog.Format("CvPalletWrite.. 재지시 쓰기 성공..! 트랙[%d]..BatchNum[%d] 도착지[%s]", nTrackNum+1, pJobItem->m_nBatchNo, pJobItem->GetDestPos());
					LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);

					JOB->Backup();
				}
				else
				{
					strLog.Format("CvPalletWrite.. 재지시 쓰기 실패..! 트랙[%d]..BatchNum[%d] 도착지[%s]", nTrackNum+1, pJobItem->m_nBatchNo, pJobItem->GetDestPos());
					LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);
					continue;
				}
			}

			m_nArrivedCheckLuggNum = nCurLuggNum;
		}
		else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_202)
		{
			pJobItem->m_nStatus = JOB_STA_CV_MOVE_RET_STATION;

			m_pDoc->m_n5GroupInternalBatch = pJobItem->m_nBatchNo;
			m_pDoc->m_n5GroupInternalPallet = pJobItem->m_nPalletNo;
		
			//int n5GroupCount = ++m_pDoc->m_n5GroupCvCount;

			strLog.Format("Change Status.. Counter..트랙[%d].. Counter[%d]..출하분류대#2..", nTrackNum+1, m_pDoc->m_n5GroupInCount);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			if(pJobItem->m_nPalletNo == m_pDoc->m_n5GroupInCount)
			{
				int nStartPos = CLib::ConvertCustomToPosition(pJobItem->m_nStartPos);
				int nDestPos = CV_RET_STATION_5GROUP;

				if (WriteTrackInfo(nTrackNum, nCurLuggNum, JOB_TYPE_AISLE_TO_AISLE, nStartPos, nDestPos, 1) == TRUE)
				{
					//m_pDoc->m_n5GroupCvCount = 0;

					strLog.Format("CvLastPalletWrite.. 마지막 팔렛으로 쓰기 성공..! 트랙[%d]..BatchNum[%d] 도착지[%s]", nTrackNum+1, pJobItem->m_nBatchNo, pJobItem->GetDestPos());
					LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);

					JOB->Backup();
				}
				else
				{
					strLog.Format("CvLastPalletWrite.. 마지막 팔렛으로 쓰기 실패..! 트랙[%d]..BatchNum[%d] 도착지[%s]", nTrackNum+1, pJobItem->m_nBatchNo, pJobItem->GetDestPos());
					LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);
					continue;
				}
			}
			else
			{
				int nStartPos = CLib::ConvertCustomToPosition(pJobItem->m_nStartPos);
				int nDestPos = CV_RET_STATION_5GROUP;

				if (WriteTrackInfo(nTrackNum, nCurLuggNum, pJobItem->m_nJobType, nStartPos, nDestPos, 2) == TRUE)
				{
					//m_pDoc->m_n4GroupCvCount = 0;

					strLog.Format("CvPalletWrite.. 재지시 쓰기 성공..! 트랙[%d]..BatchNum[%d] 도착지[%s]", nTrackNum+1, pJobItem->m_nBatchNo, pJobItem->GetDestPos());
					LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);

					JOB->Backup();
				}
				else
				{
					strLog.Format("CvPalletWrite.. 재지시 쓰기 실패..! 트랙[%d]..BatchNum[%d] 도착지[%s]", nTrackNum+1, pJobItem->m_nBatchNo, pJobItem->GetDestPos());
					LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);
					continue;
				}
			}

			m_nArrivedCheckLuggNum = nCurLuggNum;
		}
		else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_203)
		{
			pJobItem->m_nStatus = JOB_STA_CV_MOVE_RET_STATION;

			m_pDoc->m_n6GroupInternalBatch = pJobItem->m_nBatchNo;
			m_pDoc->m_n6GroupInternalPallet = pJobItem->m_nPalletNo;

			//int n6GroupCount = ++m_pDoc->m_n6GroupCvCount;

			strLog.Format("Change Status.. Counter..트랙[%d].. Counter[%d]..출하분류대#3..", nTrackNum+1, m_pDoc->m_n6GroupInCount);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			if(pJobItem->m_nPalletNo == m_pDoc->m_n6GroupInCount)
			{
				int nStartPos = CLib::ConvertCustomToPosition(pJobItem->m_nStartPos);
				int nDestPos = CV_RET_STATION_6GROUP;

				if (WriteTrackInfo(nTrackNum, nCurLuggNum, JOB_TYPE_AISLE_TO_AISLE, nStartPos, nDestPos, 1) == TRUE)
				{
					//m_pDoc->m_n6GroupCvCount = 0;

					strLog.Format("CvLastPalletWrite.. 마지막 팔렛으로 쓰기 성공..! 트랙[%d]..BatchNum[%d] 도착지[%s]", nTrackNum+1, pJobItem->m_nBatchNo, pJobItem->GetDestPos());
					LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);

					JOB->Backup();
				}
				else
				{
					strLog.Format("CvLastPalletWrite.. 마지막 팔렛으로 쓰기 실패..! 트랙[%d]..BatchNum[%d] 도착지[%s]", nTrackNum+1, pJobItem->m_nBatchNo, pJobItem->GetDestPos());
					LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);
					continue;
				}
			}
			else
			{
				int nStartPos = CLib::ConvertCustomToPosition(pJobItem->m_nStartPos);
				int nDestPos = CV_RET_STATION_6GROUP;

				if (WriteTrackInfo(nTrackNum, nCurLuggNum, pJobItem->m_nJobType, nStartPos, nDestPos, 2) == TRUE)
				{
					//m_pDoc->m_n4GroupCvCount = 0;

					strLog.Format("CvPalletWrite.. 재지시 쓰기 성공..! 트랙[%d]..BatchNum[%d] 도착지[%s]", nTrackNum+1, pJobItem->m_nBatchNo, pJobItem->GetDestPos());
					LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);

					JOB->Backup();
				}
				else
				{
					strLog.Format("CvPalletWrite.. 재지시 쓰기 실패..! 트랙[%d]..BatchNum[%d] 도착지[%s]", nTrackNum+1, pJobItem->m_nBatchNo, pJobItem->GetDestPos());
					LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);
					continue;
				}
			}

			m_nArrivedCheckLuggNum = nCurLuggNum;
		}
		else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_255)
		{
			m_pDoc->m_n7GroupInternalBatch = pJobItem->m_nBatchNo;
			m_pDoc->m_n7GroupInternalPallet = pJobItem->m_nPalletNo;

			strLog.Format("Change Status.. Counter..트랙[%d].. Counter[%d]..출하이동대..", nTrackNum+1, m_pDoc->m_n7GroupInCount);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			if(pJobItem->m_nPalletNo == m_pDoc->m_n7GroupInCount)
			{
				int nStartPos = CLib::ConvertCustomToPosition(pJobItem->m_nStartPos);
				int nDestPos = 4;

				if (WriteTrackInfo(nTrackNum, nCurLuggNum, JOB_TYPE_AISLE_TO_AISLE, nStartPos, nDestPos, 1) == TRUE)
				{
					strLog.Format("CvLastPalletWrite.. 마지막 팔렛으로 쓰기 성공..! 트랙[%d]..BatchNum[%d] 도착지[%s]", nTrackNum+1, pJobItem->m_nBatchNo, pJobItem->GetDestPos());
					LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);

					JOB->Backup();
				}
				else
				{
					strLog.Format("CvLastPalletWrite.. 마지막 팔렛으로 쓰기 실패..! 트랙[%d]..BatchNum[%d] 도착지[%s]", nTrackNum+1, pJobItem->m_nBatchNo, pJobItem->GetDestPos());
					LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);
					continue;
				}
			}
			else
			{
				int nStartPos = CLib::ConvertCustomToPosition(pJobItem->m_nStartPos);
				int nDestPos = 4;

				if (WriteTrackInfo(nTrackNum, nCurLuggNum, pJobItem->m_nJobType, nStartPos, nDestPos, 2) == TRUE)
				{
					strLog.Format("CvPalletWrite.. 재지시 쓰기 성공..! 트랙[%d]..BatchNum[%d] 도착지[%s]", nTrackNum+1, pJobItem->m_nBatchNo, pJobItem->GetDestPos());
					LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);

					JOB->Backup();
				}
				else
				{
					strLog.Format("CvPalletWrite.. 재지시 쓰기 실패..! 트랙[%d]..BatchNum[%d] 도착지[%s]", nTrackNum+1, pJobItem->m_nBatchNo, pJobItem->GetDestPos());
					LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);
					continue;
				}
			}

			m_nArrivedCheckLuggNum = nCurLuggNum;
		}
	}
}

void CConveyor::ArriveDataCopy()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		int nTrackNum = 348 -1;
		int nCurLuggNum = TRACK_INFO[nTrackNum].m_nLuggNum;

		if( nCurLuggNum == 0 ) 
			m_nArrivedLuggNum4 = 0;

		if( nCurLuggNum == m_nArrivedLuggNum4 )			
			continue;

		CJobItem *pJobItem = JOB->Find(nCurLuggNum);
		if( pJobItem == NULL )								
			continue;

		if(pJobItem->GetPattern() == JOB_PATTERN_STO)		
			continue;

		if(MOVEJOB->Find(nCurLuggNum) != NULL)
			continue;

		int nBatchNo=11, nLineNum=11, nLastPallet=0;

		if(TRACK_INFO[nTrackNum].m_nLastPallet == 1)
			nLastPallet = 1;

		if(!MOVEJOB->Add(pJobItem->m_nLuggNum, JOB_TYPE_STN_TO_STN, pJobItem->m_strLocation, nBatchNo, pJobItem->m_nPalletNo, pJobItem->m_nLevelNo, pJobItem->m_nStartPos, pJobItem->m_nDestPos, pJobItem->m_nHeight, 
								pJobItem->m_strProductID, pJobItem->m_strSecondLoc, JOB_STA_MOVE_CV_OPER_INVOKE, pJobItem->m_strGrade, "", pJobItem->m_nHeight, nLineNum, nLastPallet))
			continue;


		if (pJobItem->m_nJobType == JOB_TYPE_UNIT_RET)
		{
			strLog.Format("ArriveDataCopy.. 출고 이동대 시작 Conveyor 도착.. 이동작업 정보 생성.. 트랙[%d]..", nTrackNum+1);
			LOG_JOB(LOG_POS_CV, nCurLuggNum, strLog);

			m_pDoc->m_pJob->Remove(pJobItem);

			m_nArrivedLuggNum4 = nCurLuggNum;
		}

	}
}

void CConveyor::CvDataChange2GroupTo1Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		int nFrontTrackNum = 9 - 1;
		int nRearTrackNum  = 901 -1;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum )  continue;

		if(!m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_bPickingStationReady && !m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_bPickingStationReady )  continue;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == 0 && m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_bPickingStationReady) 
		{
			int nLuggNum, nJobType, nStartPos, nDestPos;

			nLuggNum = TRACK_INFO[nFrontTrackNum].m_nLuggNum  = TRACK_INFO[nRearTrackNum].m_nLuggNum;
			nJobType = TRACK_INFO[nFrontTrackNum].m_nJobType  = TRACK_INFO[nRearTrackNum].m_nJobType;
			nStartPos = TRACK_INFO[nFrontTrackNum].m_nStartPos = TRACK_INFO[nRearTrackNum].m_nStartPos;
			nDestPos = TRACK_INFO[nFrontTrackNum].m_nDestPos  = TRACK_INFO[nRearTrackNum].m_nDestPos;

			if (WriteTrackInfo2(nFrontTrackNum, nLuggNum, nStartPos, nDestPos, nJobType))
			{
				strLog.Format("CvDataChange2GroupTo1Group.. 트랙[%d]->트랙[%d] 쓰기 성공..!", nRearTrackNum+1, nFrontTrackNum+1);
				LOG_JOB(LOG_POS_CV, nLuggNum, strLog);
			}
			else
			{
				strLog.Format("CvDataChange2GroupTo1Group.. 트랙[%d]->트랙[%d] 쓰기 실패..!", nRearTrackNum+1, nFrontTrackNum+1);
				LOG_ERROR(LOG_POS_CV, nLuggNum, strLog);
			}
		}
	}	
}

void CConveyor::CvDataChange3GroupTo4Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		int nFrontTrackNum = 401 - 1;
		int nRearTrackNum  = 336 -1;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum )  continue;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == 0 && m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_bStoHomeStandReady) 
		{
			int nLuggNum, nJobType, nStartPos, nDestPos, nLastPallet;

			nLuggNum = TRACK_INFO[nFrontTrackNum].m_nLuggNum  = TRACK_INFO[nRearTrackNum].m_nLuggNum;
			nJobType = TRACK_INFO[nFrontTrackNum].m_nJobType  = TRACK_INFO[nRearTrackNum].m_nJobType;
			nStartPos = TRACK_INFO[nFrontTrackNum].m_nStartPos = TRACK_INFO[nRearTrackNum].m_nStartPos;
			nDestPos = TRACK_INFO[nFrontTrackNum].m_nDestPos  = TRACK_INFO[nRearTrackNum].m_nDestPos;
			nLastPallet = TRACK_INFO[nFrontTrackNum].m_nLastPallet  = TRACK_INFO[nRearTrackNum].m_nLastPallet;

			if (WriteTrackInfo(nFrontTrackNum, nLuggNum, nJobType, nStartPos, nDestPos, nLastPallet))
			{
				strLog.Format("DataChange3GroupTo4Group.. 트랙[%d]->트랙[%d] 쓰기 성공..!", nRearTrackNum+1, nFrontTrackNum+1);
				LOG_JOB(LOG_POS_CV, nLuggNum, strLog);
			}
			else
			{
				strLog.Format("DataChange3GroupTo4Group.. 트랙[%d]->트랙[%d] 쓰기 실패..!", nRearTrackNum+1, nFrontTrackNum+1);
				LOG_ERROR(LOG_POS_CV, nLuggNum, strLog);
			}
		}
	}	
}

void CConveyor::CvDataChange4GroupTo5Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		int nFrontTrackNum = 501 - 1;
		int nRearTrackNum  = 486 -1;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum )  continue;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == 0 && m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_bStoHomeStandReady) 
		{
			int nLuggNum, nJobType, nStartPos, nDestPos, nLastPallet;

			nLuggNum = TRACK_INFO[nFrontTrackNum].m_nLuggNum  = TRACK_INFO[nRearTrackNum].m_nLuggNum;
			nJobType = TRACK_INFO[nFrontTrackNum].m_nJobType  = TRACK_INFO[nRearTrackNum].m_nJobType;
			nStartPos = TRACK_INFO[nFrontTrackNum].m_nStartPos = TRACK_INFO[nRearTrackNum].m_nStartPos;
			nDestPos = TRACK_INFO[nFrontTrackNum].m_nDestPos  = TRACK_INFO[nRearTrackNum].m_nDestPos;
			nLastPallet = TRACK_INFO[nFrontTrackNum].m_nLastPallet  = TRACK_INFO[nRearTrackNum].m_nLastPallet;

			if (WriteTrackInfo(nFrontTrackNum, nLuggNum, nJobType, nStartPos, nDestPos, nLastPallet))
			{
				strLog.Format("DataChange4GroupTo5Group.. 트랙[%d]->트랙[%d] 쓰기 성공..!", nRearTrackNum+1, nFrontTrackNum+1);
				LOG_JOB(LOG_POS_CV, nLuggNum, strLog);
			}
			else
			{
				strLog.Format("DataChange4GroupTo5Group.. 트랙[%d]->트랙[%d] 쓰기 실패..!", nRearTrackNum+1, nFrontTrackNum+1);
				LOG_ERROR(LOG_POS_CV, nLuggNum, strLog);
			}
		}
	}	
}
void CConveyor::CvDataChange5GroupTo6Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		int nFrontTrackNum = 601 - 1;
		int nRearTrackNum  = 586 -1;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum )  continue;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == 0 && m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_bStoHomeStandReady) 
		{
			int nLuggNum, nJobType, nStartPos, nDestPos, nLastPallet;

			nLuggNum = TRACK_INFO[nFrontTrackNum].m_nLuggNum  = TRACK_INFO[nRearTrackNum].m_nLuggNum;
			nJobType = TRACK_INFO[nFrontTrackNum].m_nJobType  = TRACK_INFO[nRearTrackNum].m_nJobType;
			nStartPos = TRACK_INFO[nFrontTrackNum].m_nStartPos = TRACK_INFO[nRearTrackNum].m_nStartPos;
			nDestPos = TRACK_INFO[nFrontTrackNum].m_nDestPos  = TRACK_INFO[nRearTrackNum].m_nDestPos;
			nLastPallet = TRACK_INFO[nFrontTrackNum].m_nLastPallet  = TRACK_INFO[nRearTrackNum].m_nLastPallet;

			if (WriteTrackInfo(nFrontTrackNum, nLuggNum, nJobType, nStartPos, nDestPos, nLastPallet))
			{
				strLog.Format("DataChange5GroupTo6Group.. 트랙[%d]->트랙[%d] 쓰기 성공..!", nRearTrackNum+1, nFrontTrackNum+1);
				LOG_JOB(LOG_POS_CV, nLuggNum, strLog);
			}
			else
			{
				strLog.Format("DataChange5GroupTo6Group.. 트랙[%d]->트랙[%d] 쓰기 실패..!", nRearTrackNum+1, nFrontTrackNum+1);
				LOG_ERROR(LOG_POS_CV, nLuggNum, strLog);
			}
		}
	}	
}

void CConveyor::CvDataChange1GroupTo7Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		int nFrontTrackNum = 824 - 1;
		int nRearTrackNum  = 56 -1;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum )  continue;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == 0 && m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_bStoStationReady) 
		{
			int nLuggNum, nJobType, nStartPos, nDestPos, nComplete, nSize=0;

			nLuggNum = TRACK_INFO[nFrontTrackNum].m_nLuggNum  = TRACK_INFO[nRearTrackNum].m_nLuggNum;
			nJobType = TRACK_INFO[nFrontTrackNum].m_nJobType  = TRACK_INFO[nRearTrackNum].m_nJobType;
			nStartPos = TRACK_INFO[nFrontTrackNum].m_nStartPos = TRACK_INFO[nRearTrackNum].m_nStartPos;
			nDestPos = TRACK_INFO[nFrontTrackNum].m_nDestPos  = TRACK_INFO[nRearTrackNum].m_nDestPos;
			nComplete = TRACK_INFO[nFrontTrackNum].m_nComplete  = TRACK_INFO[nRearTrackNum].m_nLastPallet;

			CMoveJobItem* pMoveJobItem = m_pDoc->m_pMoveJob->Find(TRACK_INFO[nRearTrackNum].m_nLuggNum);
			if (pMoveJobItem != NULL)
			{
				nDestPos = TRACK_INFO[nFrontTrackNum].m_nDestPos = pMoveJobItem->m_nLineNum+7;

				//if(m_pDoc->m_bWriteStackingCheck1 == TRUE)
				//	nDestPos = 13;

				if(pMoveJobItem->m_nLineNum == 4 && m_pDoc->m_bWriteStackingCheck1 == FALSE)
					nDestPos = 12;

				if(pMoveJobItem->m_nLineNum == 4 && pMoveJobItem->m_nDestPos == IMS_ECS_RET_STATION_204)
					nDestPos = 14;
			}

			if (WriteTrackInfo7(nFrontTrackNum, nLuggNum, 0, nStartPos, nDestPos, nJobType, nComplete, nSize))
			{
				strLog.Format("CvDataChange1GroupTo7Group.. 트랙[%d]->트랙[%d] 쓰기 성공..!", nRearTrackNum+1, nFrontTrackNum+1);
				LOG_JOB(LOG_POS_CV, nLuggNum, strLog);

			}
			else
			{
				strLog.Format("CvDataChange1GroupTo7Group.. 트랙[%d]->트랙[%d] 쓰기 실패..!", nRearTrackNum+1, nFrontTrackNum+1);
				LOG_ERROR(LOG_POS_CV, nLuggNum, strLog);
			}
		}
	}	
}

void CConveyor::CvDataChange8GroupTo7Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		//int nFrontTrackNum = 701 - 1;
		//int nRearTrackNum  = 60 -1;

		int nFrontTrackNum = 837 - 1;
		int nRearTrackNum  = 2001 -1;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum )  
			continue;

		if(m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nDestPos != 11 && m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nDestPos != 12)
			continue;

/*		if(m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nComplete == 0)
		{
			if(m_pDoc->m_ConveyorTrackInfo[2002-1].m_nDestPos == 0)
			continue;
		}
*/

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == 0 && m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_bStoStationReady) 
		{
			int nLuggNum, nJobType, nStartPos, nDestPos, nComplete, nSize=0;

			nLuggNum = TRACK_INFO[nFrontTrackNum].m_nLuggNum  = TRACK_INFO[nRearTrackNum].m_nLuggNum;
			nJobType = TRACK_INFO[nFrontTrackNum].m_nJobType  = TRACK_INFO[nRearTrackNum].m_nJobType;
			nStartPos = TRACK_INFO[nFrontTrackNum].m_nStartPos = TRACK_INFO[nRearTrackNum].m_nStartPos;
			nDestPos = TRACK_INFO[nFrontTrackNum].m_nDestPos  = TRACK_INFO[nRearTrackNum].m_nDestPos;
			nComplete = TRACK_INFO[nFrontTrackNum].m_nComplete  = TRACK_INFO[nRearTrackNum].m_nComplete;

			nDestPos = 12;

			if(WriteTrackInfo7(nFrontTrackNum, nLuggNum, 0, nStartPos, nDestPos, nJobType, nComplete, nSize))
			{
				strLog.Format("CvDataChange8GroupTo7Group.. 트랙[%d]->트랙[%d] 쓰기 성공..!", nRearTrackNum+1, nFrontTrackNum+1);
				LOG_JOB(LOG_POS_CV, nLuggNum, strLog);

			}
			else
			{
				strLog.Format("CvDataChange8GroupTo7Group.. 트랙[%d]->트랙[%d] 쓰기 실패..!", nRearTrackNum+1, nFrontTrackNum+1);
				LOG_ERROR(LOG_POS_CV, nLuggNum, strLog);
			}

		}
	}	
}

void CConveyor::CvDataChange7GroupTo8Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{

		int nFrontTrackNum = 2001 - 1;
		int nRearTrackNum  = 837 -1;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum )  
			continue;

		if(m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nDestPos != 13 &&  m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nDestPos != 14)  
			continue;

		//if(m_pDoc->m_bWriteStackingCheck1 == FALSE)
		//	continue;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == 0 && m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_bStoStationReady) 
		{
			int nLuggNum, nJobType, nStartPos, nDestPos, nComplete, nSize=0;

			nLuggNum = TRACK_INFO[nFrontTrackNum].m_nLuggNum  = TRACK_INFO[nRearTrackNum].m_nLuggNum;
			nJobType = TRACK_INFO[nFrontTrackNum].m_nJobType  = TRACK_INFO[nRearTrackNum].m_nJobType;
			nStartPos = TRACK_INFO[nFrontTrackNum].m_nStartPos = TRACK_INFO[nRearTrackNum].m_nStartPos;
			nDestPos = TRACK_INFO[nFrontTrackNum].m_nDestPos  = TRACK_INFO[nRearTrackNum].m_nDestPos;
			nComplete = TRACK_INFO[nFrontTrackNum].m_nComplete  = TRACK_INFO[nRearTrackNum].m_nComplete;

			//nDestPos = 13;
			if(m_pDoc->m_bWriteStackingCheck2 == TRUE)
				nDestPos = 14;

			if (WriteTrackInfo7(nFrontTrackNum, nLuggNum, 0, nStartPos, nDestPos, nJobType, nComplete, nSize))
			{
				strLog.Format("CvDataChange7GroupTo8Group.. 트랙[%d]->트랙[%d] 쓰기 성공..!", nRearTrackNum+1, nFrontTrackNum+1);
				LOG_JOB(LOG_POS_CV, nLuggNum, strLog);

			}
			else
			{
				strLog.Format("CvDataChange7GroupTo8Group.. 트랙[%d]->트랙[%d] 쓰기 실패..!", nRearTrackNum+1, nFrontTrackNum+1);
				LOG_ERROR(LOG_POS_CV, nLuggNum, strLog);
			}

		}
	}	
}

void CConveyor::CvDataChange3GroupTo8Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		//int nFrontTrackNum = 2023 - 1;
		int nFrontTrackNum = 2024 - 1;
		int nRearTrackNum  = 348 -1;

		if(m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nDestPos != 4)  
			continue;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum )  
			continue;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == 0 && m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_bStoStationReady) 
		{
			int nLuggNum, nJobType, nStartPos, nDestPos, nComplete, nSize=0;

			nLuggNum = TRACK_INFO[nFrontTrackNum].m_nLuggNum  = TRACK_INFO[nRearTrackNum].m_nLuggNum;
			nJobType = TRACK_INFO[nFrontTrackNum].m_nJobType  = TRACK_INFO[nRearTrackNum].m_nJobType;
			nStartPos = TRACK_INFO[nFrontTrackNum].m_nStartPos = TRACK_INFO[nRearTrackNum].m_nStartPos;
			nDestPos = TRACK_INFO[nFrontTrackNum].m_nDestPos  = TRACK_INFO[nRearTrackNum].m_nDestPos;
			nComplete = TRACK_INFO[nFrontTrackNum].m_nComplete  = TRACK_INFO[nRearTrackNum].m_nLastPallet;

			nStartPos = 2;
			nDestPos = 13;

			if(m_pDoc->m_bWriteStackingCheck2 == TRUE)
				nDestPos = 12;

			if (WriteTrackInfo7(nFrontTrackNum, nLuggNum, 0, nStartPos, nDestPos, nJobType, nComplete, nSize))
			{
				strLog.Format("CvDataChange3GroupTo8Group.. 트랙[%d]->트랙[%d] 쓰기 성공..!", nRearTrackNum+1, nFrontTrackNum+1);
				LOG_JOB(LOG_POS_CV, nLuggNum, strLog);
			}
			else
			{
				strLog.Format("CvDataChange3GroupTo8Group.. 트랙[%d]->트랙[%d] 쓰기 실패..!", nRearTrackNum+1, nFrontTrackNum+1);
				LOG_ERROR(LOG_POS_CV, nLuggNum, strLog);
			}
		}
	}	
}

void CConveyor::RemoveCvData3Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		int nFrontTrackNum = 401 - 1;
		int nRearTrackNum = 336 -1;
		int nLuggNum = m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == 0 &&
		   m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum == 0)		continue;
		
		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum )  
		{
			if (WriteTrackInfo(nRearTrackNum, 0, 0, 0, 0, 0))
			{
				strLog.Format("RemoveCvData3Group.. 트랙[%d] 데이타 삭제 성공..!", nRearTrackNum+1);
				LOG_JOB(LOG_POS_CV, nLuggNum, strLog);
			}
			else
			{
				strLog.Format("RemoveCvData3Group.. 트랙[%d] 데이타 삭제 실패..!", nRearTrackNum+1);
				LOG_ERROR(LOG_POS_CV, nLuggNum, strLog);
			}
		}
	}	
}

void CConveyor::RemoveCvData3GroupTo8Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		//int nFrontTrackNum = 2023 - 1;
		int nFrontTrackNum = 2024 - 1;
		int nRearTrackNum = 348 -1;
		int nLuggNum = m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == 0 &&
		   m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum == 0)		
		   continue;

		if(m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nDestPos != 4)		
		   continue;
		
		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum )  
		{
			if(WriteTrackInfo(nRearTrackNum, 0, 0, 0, 0, 0))
			{
				strLog.Format("RemoveCvData3GroupTo8Group.. 트랙[%d] 데이타 삭제 성공..!", nRearTrackNum+1);
				LOG_JOB(LOG_POS_CV, nLuggNum, strLog);
			}
			else
			{
				strLog.Format("RemoveCvData3GroupTo8Group.. 트랙[%d] 데이타 삭제 실패..!", nRearTrackNum+1);
				LOG_ERROR(LOG_POS_CV, nLuggNum, strLog);
			}
		}
	}	
}

void CConveyor::RemoveCvData4Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		int nFrontTrackNum = 501 - 1;
		int nRearTrackNum = 486 -1;
		int nLuggNum = m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == 0 &&
		   m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum == 0)		continue;
		
		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum )  
		{
			if (WriteTrackInfo(nRearTrackNum, 0, 0, 0, 0, 0))
			{
				strLog.Format("RemoveCvData4Group.. 트랙[%d] 데이타 삭제 성공..!", nRearTrackNum+1);
				LOG_JOB(LOG_POS_CV, nLuggNum, strLog);
			}
			else
			{
				strLog.Format("RemoveCvData4Group.. 트랙[%d] 데이타 삭제 실패..!", nRearTrackNum+1);
				LOG_ERROR(LOG_POS_CV, nLuggNum, strLog);
			}
		}
	}	
}

void CConveyor::RemoveCvData5Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		int nFrontTrackNum = 601 - 1;
		int nRearTrackNum = 586 -1;
		int nLuggNum = m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == 0 &&
		   m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum == 0)		continue;
		
		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum )  
		{
			if (WriteTrackInfo(nRearTrackNum, 0, 0, 0, 0, 0))
			{
				strLog.Format("RemoveCvData5Group.. 트랙[%d] 데이타 삭제 성공..!", nRearTrackNum+1);
				LOG_JOB(LOG_POS_CV, nLuggNum, strLog);
			}
			else
			{
				strLog.Format("RemoveCvData5Group.. 트랙[%d] 데이타 삭제 실패..!", nRearTrackNum+1);
				LOG_ERROR(LOG_POS_CV, nLuggNum, strLog);
			}
		}
	}	
}

void CConveyor::RemoveCvData1Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		//int nFrontTrackNum = 701 - 1;
		//int nRearTrackNum = 60 -1;

		int nFrontTrackNum = 824 - 1;
		int nRearTrackNum = 56 -1;

		int nLuggNum = m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == 0 &&
		   m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum == 0)		
		   continue;
		
		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum )  
		{
			if (WriteTrackInfo(nRearTrackNum, 0, 0, 0, 0, 0))
			{
				strLog.Format("RemoveCvData1Group.. 트랙[%d] 데이타 삭제 성공..!", nRearTrackNum+1);
				LOG_JOB(LOG_POS_CV, nLuggNum, strLog);
			}
			else
			{
				strLog.Format("RemoveCvData1Group.. 트랙[%d] 데이타 삭제 실패..!", nRearTrackNum+1);
				LOG_ERROR(LOG_POS_CV, nLuggNum, strLog);
			}
		}
	}	
}

void CConveyor::RemoveCvData7Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{
		//int nFrontTrackNum = 701 - 1;
		//int nRearTrackNum = 60 -1;

		int nFrontTrackNum = 2001 - 1;
		int nRearTrackNum = 837 -1;

		int nLuggNum = m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == 0 &&
		   m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum == 0)		
		   continue;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_bStoStationReady)
		   continue;

		if(m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nDestPos != 13 && m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nDestPos != 14)
		   continue;
		
		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum )  
		{
			if (WriteTrackInfo7(nRearTrackNum, 0, 0, 0, 0, 0))
			{
				strLog.Format("RemoveCvData7Group.. 트랙[%d] 데이타 삭제 성공..!", nRearTrackNum+1);
				LOG_JOB(LOG_POS_CV, nLuggNum, strLog);
			}
			else
			{
				strLog.Format("RemoveCvData7Group.. 트랙[%d] 데이타 삭제 실패..!", nRearTrackNum+1);
				LOG_ERROR(LOG_POS_CV, nLuggNum, strLog);
			}
		}
	}	
}

void CConveyor::RemoveCvData8Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{

		int nFrontTrackNum = 837 - 1;
		int nRearTrackNum = 2001 -1;

		int nLuggNum = m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == 0 &&
		   m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum == 0)		
		   continue;

		if(m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nDestPos != 11 && m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nDestPos != 12)
		   continue;
		
		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum )  
		{
			if (WriteTrackInfo7(nRearTrackNum, 0, 0, 0, 0, 0))
			{
				strLog.Format("RemoveCvData8Group.. 트랙[%d] 데이타 삭제 성공..!", nRearTrackNum+1);
				LOG_JOB(LOG_POS_CV, nLuggNum, strLog);
			}
			else
			{
				strLog.Format("RemoveCvData8Group.. 트랙[%d] 데이타 삭제 실패..!", nRearTrackNum+1);
				LOG_ERROR(LOG_POS_CV, nLuggNum, strLog);
			}
		}
	}	
}

/*
void CConveyor::RemoveCvData8GroupTo3Group()
{
	CString strLog;

	for (int i=0; i<1; i++)
	{

		int nFrontTrackNum = 348 - 1;
		int nRearTrackNum = 2023 -1;

		int nLuggNum = m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum;

		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == 0 &&
		   m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum == 0)		
		   continue;

		if(m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nDestPos != 14)
		   continue;
		
		if(m_pDoc->m_ConveyorTrackInfo[nFrontTrackNum].m_nLuggNum == m_pDoc->m_ConveyorTrackInfo[nRearTrackNum].m_nLuggNum )  
		{
			if (WriteTrackInfo(nRearTrackNum, 0, 0, 0, 0, 0))
			{
				strLog.Format("RemoveCvData8GroupTo3Group.. 트랙[%d] 데이타 삭제 성공..!", nRearTrackNum+1);
				LOG_JOB(LOG_POS_CV, nLuggNum, strLog);
			}
			else
			{
				strLog.Format("RemoveCvData8GroupTo3Group.. 트랙[%d] 데이타 삭제 실패..!", nRearTrackNum+1);
				LOG_ERROR(LOG_POS_CV, nLuggNum, strLog);
			}
		}
	}	
}
*/

void CConveyor::StoInvokeCheck()
{
	CString strLog;

	for( int i = 0; i < 1; i++ )
	{
		int	nStationNum = CLib::GetLinearStoStnNumPerCvPlc(m_nNum, i);
		int nTrackNum = CLib::GetTrackByStationNum(nStationNum);
 
		//if (TRACK_INFO[nTrackNum].m_nLuggNum != 0 ||
		if(!TRACK_INFO[nTrackNum].m_bStoStationReady) 
			continue;

		CJobItem *pJobItem = JOB->FetchCvJobByStationNum(JOB_STA_CV_OPER_REQUEST, nStationNum);
		if(pJobItem == NULL)		
			continue;

		//if(m_nStoPrevLuggNum == pJobItem->m_nLuggNum)
		//	continue;

		m_pDoc->m_strDualCheck = "";

		if(pJobItem->GetPattern() == JOB_PATTERN_STO)
		{
			CJobItem *pDualItem = JOB->FetchCvJobByLocation(pJobItem->m_strLocation, pJobItem->m_nLuggNum);
			if(pDualItem != NULL)
			{
				strLog.Format("중복셀: %d, %d", pJobItem->m_nLuggNum, pDualItem->m_nLuggNum);
				m_pDoc->m_strDualCheck = strLog;
				continue;
			}
		}

		//int nStartPos = (nStationNum == IMS_ECS_STO_STATION_100) ? CV_POS_HS_1 : CV_POS_HS_2;
		int nStartPos = 0;
		int nDestPos  = CLib::ConvertCustomToPosition(pJobItem->m_nDestPos);

		if (WriteTrackInfo(nTrackNum, pJobItem->m_nLuggNum, pJobItem->m_nJobType, nStartPos, nDestPos))
		{
			//m_nStoPrevLuggNum = pJobItem->m_nLuggNum;
			strLog.Format("StoInvokeCheck.. 트랙[%d].. %s.. 입고지시..", nTrackNum+1, pJobItem->GetStartPos());
			LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);

			pJobItem->m_nStatus = JOB_STA_CV_OPER_INVOKE;
			JOB->Backup();
		}
		else
		{
			strLog.Format("StoInvokeCheck1.. 트랙[%d] %s .. 입고지시 에러[%s]..", nTrackNum+1, pJobItem->GetStartPos(), m_strErrMsg);
			LOG_ERROR(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);
		}
	}
}

void CConveyor::StoInvokeCheck2()
{
	CString strLog;
	int nTrackNumber[]  = {904, 910, 919, 1013, 1030, 1018, 926, 1032, 933, 939, 945, 952, 960, 1034, 1036, 966, 1038, 973};
	int nCvStationNum[] = {111, 112, 113,  114,  115,  116, 117,  118, 119, 120, 121, 122, 123,  124,  125, 126,  127, 128};

	for ( int i = 0; i < 18; i++ )
	{
		int nStartPos=0, nDestPos=0, nComplete=0;
		int	nStationNum = nCvStationNum[i];
		int nTrackNum = nTrackNumber[i]-1;

		if(TRACK_INFO[nTrackNum].m_nLuggNum != 0 ||
		 !TRACK_INFO[nTrackNum].m_bStoStationReady) 
			continue;

		CJobItem *pJobItem = JOB->FetchCvJobByStationNum(JOB_STA_CV_OPER_REQUEST, nStationNum);
		if(pJobItem == NULL)		
			continue;

		nStartPos = i+3;
		nDestPos  = CLib::ConvertCustomToPosition(pJobItem->m_nDestPos);


		if(WriteTrackInfo2(nTrackNum, pJobItem->m_nLuggNum, nStartPos, nDestPos, pJobItem->m_nJobType, nComplete) == TRUE)
		{
			pJobItem->m_nStatus = JOB_STA_CV_OPER_INVOKE;
			JOB->Backup();

			strLog.Format("StoInvokeCheck2.. 트랙[%d] %s 입고지시..", nTrackNum+1, pJobItem->GetStartPos());
			LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);
		}
		else
		{
			strLog.Format("StoInvokeCheck2.. 트랙[%d] %s 입고지시 에러..", nTrackNum+1, pJobItem->GetStartPos());
			LOG_ERROR(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);
		}
	}

	//비상운영 모드
	for ( i = 0; i < 18; i++ )
	{
		int nStartPos=0, nDestPos=0;
		int nTrackNum = nTrackNumber[i]-1;

		nStartPos = i+3;
		nDestPos = 12;

		if(TRACK_INFO[nTrackNum].m_nLuggNum == 0 && TRACK_INFO[nTrackNum].m_bStoStationReady == TRUE &&
		   m_pDoc->m_bAllStackerEmergency == TRUE) 
		{
			if(WriteTrackInfo2(nTrackNum, 0, nStartPos, nDestPos, 0, 0) == TRUE)
			{
				strLog.Format("StoInvokeCheck2.. 트랙[%d] 비상운영 이동 지시..", nTrackNum+1);
				LOG_JOB(LOG_POS_CV, 0, strLog);
			}
			else
			{
				strLog.Format("StoInvokeCheck2.. 트랙[%d] 비상운영 이동 지시 에러..", nTrackNum+1);
				LOG_ERROR(LOG_POS_CV, 0, strLog);
			}
		}
	}
}

void CConveyor::StoMoveInvokeCheck2()
{
	CString strLog;
	int nTrackNumber[]  = {904, 910, 919, 1013, 1030, 1018, 926, 1032, 933, 939, 945, 952, 960, 1034, 1036, 966, 1038, 973};
	int nCvStationNum[] = {111, 112, 113,  114,  115,  116, 117,  118, 119, 120, 121, 122, 123,  124,  125, 126,  127, 128};

	for ( int i = 0; i < 18; i++ )
	{
		int nStartPos=0, nDestPos=0, nJobType=0, nComplete=1;
		int	nStationNum = nCvStationNum[i];
		int nTrackNum = nTrackNumber[i]-1;

		if(TRACK_INFO[nTrackNum].m_nLuggNum != 0 ||
		 !TRACK_INFO[nTrackNum].m_bStoStationReady) 
			continue;

		CMoveJobItem *pMoveJobItem = MOVEJOB->FetchCvJobByStationNum(JOB_STA_MOVE_CV_OPER_REQUEST, nCvStationNum[i]);
		if ( pMoveJobItem == NULL )		
			continue;

		
		//nLastPallet = pMoveJobItem->m_nLastPallet;

		nStartPos = i+3;
		nJobType = 6;
		nComplete = pMoveJobItem->m_nHeight;

		switch(pMoveJobItem->m_nLineNum)
		{
		case	1:	nDestPos = 8;	break;
		case	2:	nDestPos = 9;	break;
		case	3:	nDestPos = 10;	break;
		case	4:	nDestPos = 11;	break;
		}

		if(pMoveJobItem->m_nLastPallet == 1)
			nJobType = 5;

		if(WriteTrackInfo2(nTrackNum, pMoveJobItem->m_nLuggNum, nStartPos, nDestPos, nJobType, nComplete) == TRUE)
		{
			pMoveJobItem->m_nStatus = JOB_STA_MOVE_CV_OPER_INVOKE;
			MOVEJOB->Backup();

			strLog.Format("StoMoveInvokeCheck2.. 트랙[%d].. %s.. 이동 지시..", nTrackNum+1, pMoveJobItem->GetStartPos());
			LOG_JOB(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);
		}
		else
		{
			strLog.Format("StoMoveInvokeCheck2.. 트랙[%d].. %s.. 이동 지시 에러..", nTrackNum+1, pMoveJobItem->GetStartPos());
			LOG_JOB(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);
		}
	}
}

void CConveyor::StoInvokeCheck7()
{
	CString strLog;

	for ( int i = 0; i < 1; i++ )
	{
		int nTrackNum = 9-1;
		//int nTrackNum = 8-1;

		//if ( TRACK_INFO[nTrackNum].m_nLuggNum != 0 ||
		if(!TRACK_INFO[nTrackNum].m_bStoStationReady) 
				continue;

		CMoveJobItem *pMoveJobItem = MOVEJOB->FetchCvJobByStationNum(JOB_STA_MOVE_CV_OPER_REQUEST, IMS_ECS_STO_STATION_100);
		if ( pMoveJobItem == NULL )		
			continue;

		int nStartPos = pMoveJobItem->m_nHeight;
		//int nJobType = pMoveJobItem->m_nJobType;
		int nJobType = 6;
		int nLastPallet = pMoveJobItem->m_nLastPallet;
		int nDestPos  = 0;

		switch(pMoveJobItem->m_nLineNum)
		{
		case	1:	nDestPos = 8;	break;
		case	2:	nDestPos = 9;	break;
		case	3:	nDestPos = 10;	break;
		case	4:	nDestPos = 11;	break;
		}

		if(pMoveJobItem->m_nLastPallet == 1)
			nJobType = 5;

		if (WriteTrackInfo(nTrackNum, pMoveJobItem->m_nLuggNum, nJobType, nStartPos, nDestPos, nLastPallet))
		{
			strLog.Format("StoInvokeCheck7.. 트랙[%d].. %s.. 이동 지시..", nTrackNum+1, pMoveJobItem->GetStartPos());
			LOG_JOB(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);

			pMoveJobItem->m_nStatus = JOB_STA_MOVE_CV_OPER_INVOKE;
			MOVEJOB->Backup();
		}
		else
		{
			strLog.Format("StoInvokeCheck7.. 트랙[%d] %s .. 이동 지시 에러[%s]..", nTrackNum+1, pMoveJobItem->GetStartPos(), m_strErrMsg);
			LOG_ERROR(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);
		}
	}
}

void CConveyor::StoManualInvokeCheck7()
{
	CString strLog;
	for ( int i = 0; i < 1; i++ )
	{
		int nTrackNum = 793-1;

		if ( TRACK_INFO[nTrackNum].m_nLuggNum != 0 ||
			!TRACK_INFO[nTrackNum].m_bStoStationReady) continue;

		int nLuggNum = m_pDoc->m_pMoveJob->GetSeqLuggNum();

		m_pDoc->m_pMoveJob->Add(nLuggNum, JOB_TYPE_MANUAL_STN_TO_STN,
			"", 0, 0, 0, 101, 251, 100, "", "", 0, "", "", 0, 12, TRACK_INFO[nTrackNum].m_nComplete);

		m_pDoc->m_pLog->Event(LOG_POS_SYSTEM, nLuggNum, "Add.. StoManualInvokeCheck7.. 수동 입고대 이동 작업 생성...!");

		Sleep(500);

		CMoveJobItem *pMoveJobItem = MOVEJOB->Find(nLuggNum);
		if ( pMoveJobItem == NULL )		
			continue;

		int nStartPos=2;
		int nDestPos  = TRACK_INFO[nTrackNum].m_nDestPos;
		int nComplete = TRACK_INFO[nTrackNum].m_nComplete;
		int nSize=0, nJobType=3;
		//int nSize=0, nJobType=6;

		if(nComplete == 1)
			nJobType = 5;

		if (WriteTrackInfo7(nTrackNum, pMoveJobItem->m_nLuggNum, 0, nStartPos, nDestPos, nJobType, nComplete, nSize))
		{
			pMoveJobItem->m_nStatus = JOB_STA_MOVE_CV_OPER_INVOKE;

			strLog.Format("StoManualInvokeCheck7.. 트랙[%d].. %s.. 수동 이동 지시..", nTrackNum+1, "수동 입고대");
			LOG_JOB(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);
		
			MOVEJOB->Backup();
		}
		else
		{
			strLog.Format("StoManualInvokeCheck7.. 트랙[%d].. %s.. 수동 이동 지시 실패..", nTrackNum+1, "수동 입고대");
			LOG_ERROR(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);
		}
	}
}

void CConveyor::SiteInvokeCheck7()
{
	CString strLog;
	for ( int i = 0; i < 1; i++ )
	{
		int nTrackNum = 793-1;

		if ( TRACK_INFO[nTrackNum].m_nLuggNum != 0 ||
			!TRACK_INFO[nTrackNum].m_bStoStationReady) continue;

		CMoveJobItem *pMoveJobItem = MOVEJOB->FetchCvJobByStationNum(JOB_STA_MOVE_CV_OPER_REQUEST, IMS_ECS_STO_STATION_103);
		if ( pMoveJobItem == NULL )		
			continue;


		int nStartPos=2;
		int nDestPos  = TRACK_INFO[nTrackNum].m_nDestPos;
		int nComplete = TRACK_INFO[nTrackNum].m_nComplete;
		int nSize=0, nJobType=3;
		//int nSize=0, nJobType=6;

		if(nComplete == 1)
			nJobType = 5;

		if (WriteTrackInfo7(nTrackNum, pMoveJobItem->m_nLuggNum, 0, nStartPos, nDestPos, nJobType, nComplete, nSize))
		{
			pMoveJobItem->m_nStatus = JOB_STA_MOVE_CV_OPER_INVOKE;

			strLog.Format("SiteInvokeCheck7.. 트랙[%d].. %s.. 자동 이동 지시..", nTrackNum+1, "버켓자동입고대");
			LOG_JOB(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);
		
			MOVEJOB->Backup();
		}
		else
		{
			strLog.Format("SiteInvokeCheck7.. 트랙[%d].. %s.. 자동 이동 지시 실패..", nTrackNum+1, "버켓자동입고대");
			LOG_ERROR(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);
		}
	}
}

void CConveyor::ManualInvokeCheck7()
{
	CString strLog;
	for ( int i = 0; i < 1; i++ )
	{
		int nTrackNum = 782-1;

		if ( TRACK_INFO[nTrackNum].m_nLuggNum != 0 ||
			 TRACK_INFO[nTrackNum].m_bRetHomeStandReady) 
			continue;

		CMoveJobItem *pMoveJobItem = MOVEJOB->FetchCvJobByStationNum(JOB_STA_MOVE_CV_OPER_REQUEST, 101);
		if ( pMoveJobItem == NULL )		
			continue;

		int nStartPos=2;
		int nDestPos  = 7;
		int nComplete = pMoveJobItem->m_nLastPallet;
		int nSize=0, nJobType=6;

		if(pMoveJobItem->m_nLastPallet == 1)
			nJobType = 5;

		if (WriteTrackInfo7(nTrackNum, pMoveJobItem->m_nLuggNum, 0, nStartPos, nDestPos, nJobType, nComplete, nSize))
		{
			pMoveJobItem->m_nStatus = JOB_STA_MOVE_CV_OPER_INVOKE;

			strLog.Format("ManualInvokeCheck7.. 트랙[%d].. %s.. Line#11 반자동 이동 지시..", nTrackNum+1, "Line#11");
			LOG_JOB(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);
		
			MOVEJOB->Backup();
		}
		else
		{
			strLog.Format("ManualInvokeCheck7.. 트랙[%d].. %s.. Line#11 반자동 이동 지시 실패..", nTrackNum+1, "Line#11");
			LOG_ERROR(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);
		}
	}
}

BOOL CConveyor::RetInvokeCheck()
{
	for (int i = 0; i < 6; i++ )
	{
		int nScNum = i;
		int nTrackNum = CLib::GetScRetHSTrack(nScNum, FALSE); //Fork#1 후

		// 화물이 있어도 출고대 준비로 상태가 올라옴 무시
		if ( TRACK_INFO[nTrackNum].m_nLuggNum != 0 ||
		   TRACK_INFO[nTrackNum].m_bRetHomeStandReady) continue;

		//if( m_pDoc->m_pStackerInfo[m_nNum]->m_bCvTransaction == FALSE )	continue;

		CJobItem *pJobItem = JOB->FetchCvJobByScNum(nScNum, TRUE);
		if ( pJobItem == NULL )
		{
			SC_INFO->m_bCvTransaction = FALSE;
			continue;
		}

//		CJobItem *pSecondJobItem = JOB->FetchCvJobByScNum(nScNum, FALSE);
//		if(pSecondJobItem != NULL)		continue;

		CString strLog;

		int nStartPos = CLib::ConvertCustomToPosition(pJobItem->m_nStartPos);
		int nDestPos = 0;

		if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_201)	nDestPos = CV_RET_STATION_4GROUP;
		else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_202)	nDestPos = CV_RET_STATION_5GROUP;
		else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_203)	nDestPos = CV_RET_STATION_6GROUP;
		else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_255)	nDestPos = 4;
		else 0;

		if (WriteTrackInfo(nTrackNum, pJobItem->m_nLuggNum, pJobItem->m_nJobType, nStartPos, nDestPos) == TRUE)
		{
			SC_INFO->m_bCvTransaction = FALSE;
			TRACK_INFO[nTrackNum].m_bRetHomeStandReady = FALSE;

			strLog.Format("RetInvokeCheck.. 포크#1 CV 출고지시.. 트랙[%d] 도착지[%s]", nTrackNum+1, pJobItem->GetDestPos());
			LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);

			pJobItem->m_nStatus = JOB_STA_CV_OPER_INVOKE;
			JOB->Backup();
			continue;
		}
		else
		{
			strLog.Format("RetInvokeCheck.. 포크#1 CV 출고지시 에러.. 트랙[%d]", nTrackNum+1);
			LOG_ERROR(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);
			continue;
		}
	}

	return TRUE;
}

BOOL CConveyor::RetInvokeCheck2()
{
	for ( int i = 0; i < 6; i++ )
	{
		int nScNum = i;
		int nTrackNum = CLib::GetScRetHSTrack(nScNum, TRUE); //Fork#2 전

		if ( TRACK_INFO[nTrackNum].m_nLuggNum != 0 ||
			 TRACK_INFO[nTrackNum].m_bRetHomeStandReady) continue;
		
		CJobItem *pJobItem = JOB->FetchCvJobByScNum(nScNum, FALSE);
		if ( pJobItem == NULL )			continue;
		
		CString strLog;

		int nStartPos = CLib::ConvertCustomToPosition(pJobItem->m_nStartPos);
		int nDestPos = 0;

		if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_201)	nDestPos = CV_RET_STATION_4GROUP;
		else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_202)	nDestPos = CV_RET_STATION_5GROUP;
		else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_203)	nDestPos = CV_RET_STATION_6GROUP;
		else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_255)	nDestPos = 4;
		else 0;


		if (WriteTrackInfo(nTrackNum, pJobItem->m_nLuggNum, pJobItem->m_nJobType, nStartPos, nDestPos) == TRUE)
		{
			strLog.Format("RetInvokeCheck2.. 포크#2 CV 출고지시.. 트랙[%d] 도착지[%s]", nTrackNum+1, pJobItem->GetDestPos());
			LOG_JOB(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);

			pJobItem->m_nStatus = JOB_STA_CV_OPER_INVOKE;
			JOB->Backup();
			continue;
		}
		else
		{
			strLog.Format("RetInvokeCheck2.. 포크#2 CV 출고지시 에러.. 트랙[%d]", nTrackNum+1);
			LOG_ERROR(LOG_POS_CV, pJobItem->m_nLuggNum, strLog);
			continue;
		}
	}
	return TRUE;
}

void CConveyor::RgvCompleteCheck1()
{
	static int nTrackStation1[] = {711, 712, 719, 726, 733, 753, 760, 767, 774, 781};

	CString strLog;

	for ( int i = 0; i < 10; i++ )
	{
		int nTrackNum = nTrackStation1[i]-1;

		if ( TRACK_INFO[nTrackNum].m_nLuggNum != 0 ||
			 TRACK_INFO[nTrackNum].m_bRetHomeStandReady )	
			 continue;

		CMoveJobItem *pMoveJobItem = MOVEJOB->FetchRgvJobByDestTrack(nTrackNum);
		if ( pMoveJobItem == NULL )		
			continue;

		int nStartPos=1;
		int nDestPos = pMoveJobItem->m_nLineNum+1;
		int nComplete = pMoveJobItem->m_nLastPallet;
		int nSize=0;


		if (WriteTrackInfo7(nTrackNum, pMoveJobItem->m_nLuggNum, 0, nStartPos, nDestPos, pMoveJobItem->m_nJobType, nComplete, nSize))
		{
			pMoveJobItem->m_nStatus = JOB_STA_MOVE_CV_OPER_INVOKE;

			strLog.Format("RgvCompleteCheck1.. RTV#%d 작업완료[CV#%d].. 도착지[%s] CV 이동지시..",
				           1, nTrackNum+1, pMoveJobItem->GetDestPos());

			LOG_JOB(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);
		
			MOVEJOB->Backup();
		}
		else
		{
			strLog.Format("RgvCompleteCheck1.. RTV#%d 작업완료[CV#%d].. 도착지[%s] CV 이동지시 에러", 
				           1, nTrackNum+1, pMoveJobItem->GetDestPos());

			LOG_ERROR(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);
		}
	}
}

void CConveyor::RgvCompleteCheck2()
{
	static int nTrackStation2[] = {746};

	CString strLog;
	int nLuggNum1=0, nLuggNum2=0;

	for ( int i = 0; i < 1; i++ )
	{
		int nTrackNum = nTrackStation2[i]-1;

		if (TRACK_INFO[nTrackNum].m_bRetHomeStandReady)	
			 continue;

		CMoveJobItem *pMoveJobItem = MOVEJOB->FetchRgvJobByDestTrack(nTrackNum);
		if ( pMoveJobItem == NULL )		
			continue;

		int nStartPos=1;
		int nDestPos = pMoveJobItem->m_nLineNum+1;
		int nComplete=0;
		int nSize=0, nJobType=6;

		if(TRACK_INFO[nTrackNum].m_nComplete == 0 && pMoveJobItem->m_nLastPallet == 1)
		{
			nComplete = 1;
			nJobType = 5;
		}

		if(TRACK_INFO[nTrackNum].m_nComplete == 1 && pMoveJobItem->m_nLastPallet == 0)
		{
			nComplete = 1;
			nJobType = 5;
		}

		nLuggNum1 = pMoveJobItem->m_nLuggNum;

		if(m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_nLuggNum != 0 &&
		   m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_nLuggNum2 == 0)
		{
				nLuggNum1 = m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_nLuggNum;
				nLuggNum2 = pMoveJobItem->m_nLuggNum;
		}


		if (WriteTrackInfo7(nTrackNum, nLuggNum1, nLuggNum2, nStartPos, nDestPos, nJobType, nComplete, nSize))
		{
			pMoveJobItem->m_nStatus = JOB_STA_MOVE_CV_OPER_INVOKE;

			strLog.Format("RgvCompleteCheck2.. RTV#%d 작업완료[CV#%d].. 도착지[%s] CV 이동지시..",
				           1, nTrackNum+1, pMoveJobItem->GetDestPos());

			LOG_JOB(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);
		
			MOVEJOB->Backup();
		}
		else
		{
			strLog.Format("RgvCompleteCheck2.. RTV#%d 작업완료[CV#%d].. 도착지[%s] CV 이동지시 에러", 
				           1, nTrackNum+1, pMoveJobItem->GetDestPos());

			LOG_ERROR(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);
		}
	}
}

void CConveyor::RgvCompleteCheck3()
{
	static int nTrackStation3[] = {713, 720, 727, 734, 740, 747, 754, 761, 768, 775, 782};
	CString strLog;
	int nLuggNum1=0, nLuggNum2=0;

	for ( int i = 0; i < 11; i++ )
	{
		int nTrackNum = nTrackStation3[i]-1;

		if ( TRACK_INFO[nTrackNum].m_nLuggNum != 0 ||
			 TRACK_INFO[nTrackNum].m_bRetHomeStandReady )	
			 continue;

		CMoveJobItem* pMoveJobItem = NULL;
		CMoveJobItem* pMoveJobItem2 = NULL;
		
		//BOOL bResult = MOVEJOB->FetchRgvJobRetrieve(nTrackNum, &pMoveJobItem, &pMoveJobItem2);
		//if (pMoveJobItem == NULL && pMoveJobItem2 == NULL)		
		//	 continue;

		pMoveJobItem = MOVEJOB->FetchRgvJobByDestTrack(nTrackNum);
		if (pMoveJobItem == NULL)	
			continue;

		//Sleep(500L);

		int nStartPos = 1;
		int nDestPos = pMoveJobItem->m_nBatchNo;
		int nComplete = 0;
		int nSize=0, nJobType=0;

		if(pMoveJobItem->m_nTwinJob == 2)
		{
			pMoveJobItem2 = MOVEJOB->FetchRgvJobByDestTrack2(nTrackNum, pMoveJobItem->m_nLuggNum);
			if (pMoveJobItem2 == NULL)	
				continue;

			nLuggNum1 = pMoveJobItem->m_nLuggNum;
			nComplete = pMoveJobItem->m_nLastPallet;
			nJobType = pMoveJobItem->m_nJobType;

			nLuggNum2 = pMoveJobItem2->m_nLuggNum;
			nComplete = pMoveJobItem2->m_nLastPallet;
			nJobType = pMoveJobItem2->m_nJobType;

			if(pMoveJobItem->m_nLastPallet == 1)
			{
			   nComplete = 1;
			   nJobType = 5;
			}

			if(pMoveJobItem2->m_nLastPallet == 1)
			{
			   nComplete = 1;
			   nJobType = 5;
			}

			if(nTrackStation3[i] == 782)
				nJobType = 2;

			if (WriteTrackInfo7(nTrackNum, nLuggNum1, nLuggNum2, nStartPos, nDestPos, nJobType, nComplete, nSize))
			{
				pMoveJobItem->m_nStatus = JOB_STA_MOVE_CV_OPER_INVOKE;

				strLog.Format("RgvCompleteCheck3.. RTV#%d 작업완료[CV#%d].. 도착지[%s] CV 이동지시..", 1, nTrackNum+1, pMoveJobItem->GetDestPos());
				LOG_JOB(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);

				pMoveJobItem2->m_nStatus = JOB_STA_MOVE_CV_OPER_INVOKE;

				strLog.Format("RgvCompleteCheck3.. RTV#%d 작업완료[CV#%d].. 도착지[%s] CV 이동지시..", 1, nTrackNum+1, pMoveJobItem2->GetDestPos());
				LOG_JOB(LOG_POS_CV, pMoveJobItem2->m_nLuggNum, strLog);

				MOVEJOB->Backup();

				return;
			}
			else
			{
				strLog.Format("RgvCompleteCheck3.. RTV#%d 작업완료[CV#%d].. 도착지[%s] CV 이동지시 에러", 1, nTrackNum+1, pMoveJobItem->GetDestPos());
				LOG_ERROR(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);


				strLog.Format("RgvCompleteCheck3.. RTV#%d 작업완료[CV#%d].. 도착지[%s] CV 이동지시 에러", 1, nTrackNum+1, pMoveJobItem2->GetDestPos());
					LOG_ERROR(LOG_POS_CV, pMoveJobItem2->m_nLuggNum, strLog);

				return;
			}
		}

		nLuggNum1 = pMoveJobItem->m_nLuggNum;
		nComplete = pMoveJobItem->m_nLastPallet;
		nJobType = pMoveJobItem->m_nJobType;

		if(nTrackStation3[i] == 782)
			nJobType = 2;


		if(pMoveJobItem->m_nLastPallet == 1)
		{
		   nComplete = 1;
		   nJobType = 5;
		}

		if (WriteTrackInfo7(nTrackNum, nLuggNum1, nLuggNum2, nStartPos, nDestPos, nJobType, nComplete, nSize))
		{
			pMoveJobItem->m_nStatus = JOB_STA_MOVE_CV_OPER_INVOKE;

			strLog.Format("RgvCompleteCheck4.. RTV#%d 작업완료[CV#%d].. 도착지[%s] CV 이동지시..",
							   1, nTrackNum+1, pMoveJobItem->GetDestPos());
			LOG_JOB(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);

			MOVEJOB->Backup();
		}
		else
		{
			strLog.Format("RgvCompleteCheck4.. RTV#%d 작업완료[CV#%d].. 도착지[%s] CV 이동지시 에러", 
							   1, nTrackNum+1, pMoveJobItem->GetDestPos());
			LOG_ERROR(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);

		}

	}
}

void CConveyor::RgvCompleteCheck4()
{
	static int nTrackStation4[] = {809};
	CString strLog;
	int nLuggNum1=0, nLuggNum2=0;

	for ( int i = 0; i < 1; i++ )
	{
		int nTrackNum = nTrackStation4[i]-1;

		if ( TRACK_INFO[nTrackNum].m_nLuggNum != 0 ||
			 TRACK_INFO[nTrackNum].m_bRetHomeStandReady )	
			 continue;

		CMoveJobItem* pMoveJobItem = NULL;
		CMoveJobItem* pMoveJobItem2 = NULL;

		int nStartPos = 1;
		int nDestPos = 7;
		int nComplete = 0;
		int nSize=0, nJobType=0;
		
		//BOOL bResult = MOVEJOB->FetchRgvJobRetrieve(nTrackNum, &pMoveJobItem, &pMoveJobItem2);
		//if (pMoveJobItem == NULL && pMoveJobItem2 == NULL)		
		//	 continue;

		pMoveJobItem = MOVEJOB->FetchRgvJobByDestTrack(nTrackNum);
		if (pMoveJobItem == NULL)	
			continue;

		//Sleep(500L);

		if(pMoveJobItem->m_nTwinJob == 2)
		{
			pMoveJobItem2 = MOVEJOB->FetchRgvJobByDestTrack2(nTrackNum, pMoveJobItem->m_nLuggNum);
			if (pMoveJobItem2 == NULL)	
				continue;

			nLuggNum1 = pMoveJobItem->m_nLuggNum;
			nComplete = pMoveJobItem->m_nLastPallet;
			nJobType = pMoveJobItem->m_nJobType;

			//if(nJobType == JOB_TYPE_MANUAL_STN_TO_STN)
			//	nDestPos = 3;

			nLuggNum2 = pMoveJobItem2->m_nLuggNum;
			nComplete = pMoveJobItem2->m_nLastPallet;
			nJobType = pMoveJobItem2->m_nJobType;

			//if(nJobType == JOB_TYPE_MANUAL_STN_TO_STN)
			//	nDestPos = 3;

			if(pMoveJobItem->m_nLineNum == 11 || pMoveJobItem2->m_nLineNum == 11)
				nJobType = 2;

			if(pMoveJobItem->m_nLastPallet == 1)
			{
				nComplete = 1;
				nJobType = 5;
				nDestPos = 4;

			}

			if(pMoveJobItem2->m_nLastPallet == 1)
			{
				nComplete = 1;
				nJobType = 5;
				nDestPos = 4;
			}

			if (WriteTrackInfo7(nTrackNum, nLuggNum1, nLuggNum2, nStartPos, nDestPos, nJobType, nComplete, nSize))
			{
				pMoveJobItem->m_nStatus = JOB_STA_MOVE_CV_OPER_INVOKE;

				strLog.Format("RgvCompleteCheck4.. RTV#%d 작업완료[CV#%d].. 도착지[%s] CV 이동지시..", 2, nTrackNum+1, pMoveJobItem->GetDestPos());
				LOG_JOB(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);

				pMoveJobItem2->m_nStatus = JOB_STA_MOVE_CV_OPER_INVOKE;

				strLog.Format("RgvCompleteCheck4.. RTV#%d 작업완료[CV#%d].. 도착지[%s] CV 이동지시..", 2, nTrackNum+1, pMoveJobItem2->GetDestPos());
				LOG_JOB(LOG_POS_CV, pMoveJobItem2->m_nLuggNum, strLog);

				MOVEJOB->Backup();

				return;
			}
			else
			{
				strLog.Format("RgvCompleteCheck4.. RTV#%d 작업완료[CV#%d].. 도착지[%s] CV 이동지시 에러", 2, nTrackNum+1, pMoveJobItem->GetDestPos());
				LOG_ERROR(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);


				strLog.Format("RgvCompleteCheck4.. RTV#%d 작업완료[CV#%d].. 도착지[%s] CV 이동지시 에러", 2, nTrackNum+1, pMoveJobItem2->GetDestPos());
					LOG_ERROR(LOG_POS_CV, pMoveJobItem2->m_nLuggNum, strLog);

				return;
			}
		}

		nLuggNum1 = pMoveJobItem->m_nLuggNum;
		nComplete = pMoveJobItem->m_nLastPallet;
		nJobType = pMoveJobItem->m_nJobType;

		//if(nJobType == JOB_TYPE_MANUAL_STN_TO_STN)
		//	nDestPos = 3;

		if(pMoveJobItem->m_nLineNum == 11)
			nJobType = 2;

		if(pMoveJobItem->m_nLastPallet == 1)
		{
			nComplete = 1;
			nJobType = 5;
			nDestPos = 4;

			//if(pMoveJobItem->m_nLevelNo != 5)
			//  nDestPos = 4;
		}

		if (WriteTrackInfo7(nTrackNum, nLuggNum1, nLuggNum2, nStartPos, nDestPos, nJobType, nComplete, nSize))
		{
			pMoveJobItem->m_nStatus = JOB_STA_MOVE_CV_OPER_INVOKE;

			strLog.Format("RgvCompleteCheck4.. RTV#%d 작업완료[CV#%d].. 도착지[%s] CV 이동지시..",
							   2, nTrackNum+1, pMoveJobItem->GetDestPos());
			LOG_JOB(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);

			MOVEJOB->Backup();
		}
		else
		{
			strLog.Format("RgvCompleteCheck4.. RTV#%d 작업완료[CV#%d].. 도착지[%s] CV 이동지시 에러", 
							   2, nTrackNum+1, pMoveJobItem->GetDestPos());
			LOG_ERROR(LOG_POS_CV, pMoveJobItem->m_nLuggNum, strLog);

		}
	}
}

/*
BOOL CConveyor::InvokeCheck()
{
	int nCvRtvCnt = 12;
    int nRank = m_nCvNextRtn;

	if(m_nCvNextRtn > nCvRtvCnt)
		nRank = m_nCvNextRtn = 0;

	for( int i = m_nCvNextRtn; i<m_nCvNextRtn + nCvRtvCnt; i++)
	{ 
		if(i >= nCvRtvCnt)
			nRank = i-nCvRtvCnt;

		if ( CvRtvInvokeCheck(nRank) )		
		{
			m_nCvNextRtn++;
			return TRUE;
		}
		nRank++;
	}

	return FALSE;
}
*/


BOOL CConveyor::InvokeCheck()
{
    int nRank = m_nCvNextRtn;
	int nCvRtvCnt = 12;

	for( int i=0; i<nCvRtvCnt; i++)
	{
		if ( CvRtvInvokeCheck(nRank) )		
		{
			nRank++;
			if (nRank >= nCvRtvCnt)
				nRank = 0;

			m_nCvNextRtn = nRank;
			return TRUE;
		}
		nRank++;
		if (nRank >= nCvRtvCnt)
			nRank = 0;
	}

	m_nCvNextRtn = nRank;

	return FALSE;
}


BOOL CConveyor::CvRtvInvokeCheck(int nRank)
{
	static int nRtvTrack1[] = {718, 717, 716, 715, 714, 713};
	static int nRtvTrack2[] = {725, 724, 723, 722, 721, 720};
	static int nRtvTrack3[] = {732, 731, 730, 729, 728, 727};
	static int nRtvTrack4[] = {739, 738, 737, 736, 735, 734};
	static int nRtvTrack5[] = {745, 744, 743, 742, 741, 740};
	static int nRtvTrack6[] = {752, 751, 750, 749, 748, 747};
	static int nRtvTrack7[] = {759, 758, 757, 756, 755, 754};
	static int nRtvTrack8[] = {766, 765, 764, 763, 762, 761};
	static int nRtvTrack9[] = {773, 772, 771, 770, 769, 768};
	static int nRtvTrack10[] = {780, 779, 778, 777, 776, 775};
	static int nRtvTrack11[] = {787, 786, 785, 784, 783, 782};
	static int nRtvTrack12[] = {808, 807, 802, 803, 804, 805, 806};
	//static int nRtvTrack13[] = {808, 807, 797, 798, 799, 800, 801};
	static int nRtvTrack13[] = {808, 807, 802, 804, 805, 806};

//	int nTrackNum = CLib::GetRgvRetStartHSTrack(RGV_2_NUM, nRank);
	int nTrackNum = CLib::GetRgvRetStartHSTrack2(RGV_2_NUM, nRank);

	if ( TRACK_INFO[nTrackNum].m_nLuggNum ==  0 ||
		!TRACK_INFO[nTrackNum].m_bStoHomeStandReady )
		return FALSE;

	if (m_pDoc->m_pRgvInfo[1]->m_bInvoke || m_pDoc->m_pRgvInfo[1]->m_ucMode != RGV_MODE_AUTO || m_pDoc->m_pRgvInfo[1]->m_ucActive != RGV_ACTIVE ||
		m_pDoc->m_pRgvInfo[1]->m_ucStatus == RGV_STA_MOVE || m_pDoc->m_pRgvInfo[1]->m_ucStatus == RGV_STA_ERROR)
		return FALSE;

	if (m_pDoc->m_pRgvInfo[1]->m_bStoreSuspend)	
		return FALSE;
	

	CString strLog;
	CMoveJobItem *pMoveJobItem = MOVEJOB->FetchCvRgvInvokeCheck(TRACK_INFO[nTrackNum].m_nLuggNum);
	if (pMoveJobItem != NULL)
		return FALSE;

	//for(int i=0; i<7; i++)
	for(int i=0; i<6; i++)
	{
		switch(nTrackNum+1)
		{
		case	808:
			{
			/*	if(TRACK_INFO[808-1].m_nDestPos == 21)//A Line
				{
					MOVEJOB->FindChange(TRACK_INFO[nRtvTrack12[i]-1].m_nLuggNum, TRACK_INFO[nRtvTrack12[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

					if(i == 6 && TRACK_INFO[795-1].m_nDestPos == 21 && TRACK_INFO[795-1].m_nComplete == 1)
						MOVEJOB->FindChange(TRACK_INFO[795-1].m_nLuggNum, 0, JOB_STA_MOVE_RGV_OPER_REQUEST);

					//if(i == 6 && TRACK_INFO[796-1].m_nDestPos == 21 && TRACK_INFO[796-1].m_nComplete == 1)
					if(i == 6 && TRACK_INFO[796-1].m_nDestPos == 21)
						MOVEJOB->FindChange(TRACK_INFO[796-1].m_nLuggNum, 0, JOB_STA_MOVE_RGV_OPER_REQUEST);

				}
			*/
				if(TRACK_INFO[808-1].m_nDestPos == 22)//B Line
				{
					MOVEJOB->FindChange(TRACK_INFO[nRtvTrack13[i]-1].m_nLuggNum, TRACK_INFO[nRtvTrack13[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

					//if(i == 6 && TRACK_INFO[795-1].m_nDestPos == 22 && TRACK_INFO[795-1].m_nComplete == 1)
					//	MOVEJOB->FindChange(TRACK_INFO[795-1].m_nLuggNum, 0, JOB_STA_MOVE_RGV_OPER_REQUEST);

					//if(i == 6 && TRACK_INFO[796-1].m_nDestPos == 22)
					//	MOVEJOB->FindChange(TRACK_INFO[796-1].m_nLuggNum, 0, JOB_STA_MOVE_RGV_OPER_REQUEST);

				}

			}
			break;
		}
	}

//	if (m_pDoc->m_bJobStopCheck)	
//		return FALSE;

	for(i=0; i<6; i++)
	{
		switch(nTrackNum+1)
		{
		case	718:
			{
				if(!m_pDoc->m_bBufferStopCheck)
					MOVEJOB->FindChange(TRACK_INFO[nRtvTrack1[i]-1].m_nLuggNum, TRACK_INFO[nRtvTrack1[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);
			}
			break;
		case	725:
			{
				if(!m_pDoc->m_bBufferStopCheck)
					MOVEJOB->FindChange(TRACK_INFO[nRtvTrack2[i]-1].m_nLuggNum, TRACK_INFO[nRtvTrack2[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);
			}
			break;
		case	732:
			{
				if(!m_pDoc->m_bBufferStopCheck)
					MOVEJOB->FindChange(TRACK_INFO[nRtvTrack3[i]-1].m_nLuggNum, TRACK_INFO[nRtvTrack3[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);
			}
			break;
		case	739:
			{
				if(!m_pDoc->m_bBufferStopCheck)
					MOVEJOB->FindChange(TRACK_INFO[nRtvTrack4[i]-1].m_nLuggNum, TRACK_INFO[nRtvTrack4[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);
			}
			break;


		case	745:
			{
				if(!m_pDoc->m_bBufferStopCheck)
					MOVEJOB->FindChange(TRACK_INFO[nRtvTrack5[i]-1].m_nLuggNum, TRACK_INFO[nRtvTrack5[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);
			}
			break;
		case	752:
			{
				if(!m_pDoc->m_bBufferStopCheck)
					MOVEJOB->FindChange(TRACK_INFO[nRtvTrack6[i]-1].m_nLuggNum, TRACK_INFO[nRtvTrack6[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);
			}
			break;
		case	759:
			{
				if(!m_pDoc->m_bBufferStopCheck)
					MOVEJOB->FindChange(TRACK_INFO[nRtvTrack7[i]-1].m_nLuggNum, TRACK_INFO[nRtvTrack7[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);
			}
			break;
		case	766:
			{
				if(!m_pDoc->m_bBufferStopCheck)
					MOVEJOB->FindChange(TRACK_INFO[nRtvTrack8[i]-1].m_nLuggNum, TRACK_INFO[nRtvTrack8[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);
			}
			break;

		case	773:
			{
				if(!m_pDoc->m_bBufferStopCheck)
					MOVEJOB->FindChange(TRACK_INFO[nRtvTrack9[i]-1].m_nLuggNum, TRACK_INFO[nRtvTrack9[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);
			}
			break;
		case	780:
			{
				if(!m_pDoc->m_bBufferStopCheck)
					MOVEJOB->FindChange(TRACK_INFO[nRtvTrack10[i]-1].m_nLuggNum, TRACK_INFO[nRtvTrack10[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);
			}
			break;
		case	787:
			{
				if(!m_pDoc->m_bJobStopCheck)	
					MOVEJOB->FindChange(TRACK_INFO[nRtvTrack11[i]-1].m_nLuggNum, TRACK_INFO[nRtvTrack11[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);
			}
			break;
/*		case	808:
			{
				if(TRACK_INFO[808-1].m_nDestPos == 21)
					MOVEJOB->FindChange(TRACK_INFO[nRtvTrack12[i]-1].m_nLuggNum, TRACK_INFO[nRtvTrack12[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

				if(TRACK_INFO[808-1].m_nDestPos == 22)
					MOVEJOB->FindChange(TRACK_INFO[nRtvTrack13[i]-1].m_nLuggNum, TRACK_INFO[nRtvTrack13[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

			}
			break;
*/
		}
	}

	return FALSE;
}


void CConveyor::RgvEmergencyStop(BOOL bStop, int nRgvNum)
{
	CString strLog;

	if ( bStop )
	{
		CString strRgvName = m_pDoc->m_pConfig->GetRgvDeviceName(nRgvNum);
		strLog.Format("RtvEmergencyStop.. Fence Open.. %s 비상정지 지시..", strRgvName);
		LOG_JOB(LOG_POS_CV, LOG_SYSTEM, strLog);

		m_pDoc->m_RgvThreadInfo[nRgvNum].m_RgvMsg.nCommand = RGV_CMD_ESTOP;
		m_pDoc->m_RgvThreadInfo[nRgvNum].m_RgvMsg.bModified = TRUE;
		RGV_ACTION(nRgvNum);	
	}
}

BOOL CConveyor::RetrieveStationCheck(CEcsDoc* pDoc)
{
	return TRUE;
}

#undef	TRACK_INFO

int  CConveyor::WriteTrackInfo(int nTrackNum, int nLuggNum, int nJobType, int nStartPos, int nDestPos, int nLastPallet)
{
	BYTE	TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));

	TxBuff[0] = (BYTE)(nLuggNum % 100);
	TxBuff[1] = (BYTE)(nLuggNum / 100);
    TxBuff[2] = (BYTE)(((nStartPos & 0x0F) << 4 | (nDestPos & 0x0F)));
	TxBuff[3] = (BYTE)(((nJobType & 0x0F) << 4 | (nLastPallet & 0x0F)));

	int nStartAddr = 0, nNewTrackNum = 0, nOldTrackNum = 0;

	switch(m_nNum)
	{
	case CV_1_PLC:
		{
			nStartAddr = (2 + nTrackNum * 2);
		}
		break;
	case CV_2_PLC:	
		break;
	case CV_3_PLC:
		{
			nOldTrackNum = nTrackNum - 300;
			nNewTrackNum = 2 + nOldTrackNum * 2;
			nStartAddr = nNewTrackNum + 300;
		}
		break;
	case CV_4_PLC:
		{
			nNewTrackNum = nTrackNum - 400;
			nStartAddr = (2 + nNewTrackNum * 2);	
		}
		break;
	case CV_5_PLC:
		{
			nNewTrackNum = nTrackNum - 500;
			nStartAddr = (2 + nNewTrackNum * 2);	
		}
		break;
	case CV_6_PLC:
		{
			nNewTrackNum = nTrackNum - 600;
			nStartAddr = (2 + nNewTrackNum * 2);	
		}
		break;
	}

	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  nStartAddr, 2);
}

int  CConveyor::WriteInCounterReset(int nStartAddr)
{
	BYTE	TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));

	TxBuff[0] = 0;
	TxBuff[1] = 0;

	m_pDoc->m_bInResetCheck = FALSE;

	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  nStartAddr, 1);
}

int CConveyor::WriteTrackInfo2(int nTrackNum, int nLuggNum, int nStartPos, int nDestPos, int nJobType, int nComplete)
{
	BYTE	TxBuff[256];
	int     nStartAddr;

	CString strStartAddr, strTempAddr;
	memset(TxBuff, 0x00, sizeof(TxBuff));

	TxBuff[0] = (BYTE)(nLuggNum % 100);
	TxBuff[1] = (BYTE)(nLuggNum / 100);

    TxBuff[2] = (BYTE)(nStartPos & 0xFF);
	TxBuff[3] = (BYTE)(nJobType & 0xFF);

	TxBuff[4] = (BYTE)(nDestPos & 0xFF);
	TxBuff[5] = (BYTE)(nComplete & 0xFF);

	//TxBuff[4] = (BYTE)((nSize & 0xFF) << 4 | (nJobType & 0xFF));

	nStartAddr = ((nTrackNum+1-900) * 10);

	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  nStartAddr, 3);	
}

int CConveyor::WriteTrackInfo7(int nTrackNum, int nLuggNum, int nLuggNum2, int nStartPos, int nDestPos, int nJobType, int nComplete, int nSize)
{
	BYTE	TxBuff[256];
//  char    szDestPos[3], szStartPos[3];
	int     nStartAddr;

	CString strStartAddr, strTempAddr;
	memset(TxBuff, 0x00, sizeof(TxBuff));

	TxBuff[0] = (BYTE)(nLuggNum % 100);
	TxBuff[1] = (BYTE)(nLuggNum / 100);

    TxBuff[2] = (BYTE)(nDestPos & 0xFF);
//    sprintf(szDestPos, "%.1X", nDestPos);
//    memcpy(TxBuff+2, szDestPos, 1);

	TxBuff[3] = (BYTE)(nStartPos & 0xFF);
//    sprintf(szStartPos, "%.1X", nStartPos);
//    memcpy(TxBuff+3, szStartPos, 1);

	TxBuff[4] = (BYTE)((nSize & 0xFF) << 4 | (nJobType & 0xFF));
	TxBuff[5] = (BYTE)(nComplete & 0xFF);

	TxBuff[6] = (BYTE)(nLuggNum2 % 100);
	TxBuff[7] = (BYTE)(nLuggNum2 / 100);

//	sprintf((char *)TxBuff, "%.04d%2d%2x%2d%1d%1d%", nLuggNum, nStartPos, nDestPos, nComplete, nSize, nJobType);

	nStartAddr = ((nTrackNum+1-700) * 10);

	if(	nTrackNum >= 2000)
		nStartAddr = ((nTrackNum+1-2000) * 10);

	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  nStartAddr, 4);	
}

int CConveyor::WriteTroubleInfo(int nAddressNum, WORD wAddressData)
{
	BYTE	TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));

    TxBuff[0] = (BYTE)(wAddressData & 0x00FF);
	TxBuff[1] = (BYTE)(wAddressData & 0xFF00) >> 8;

	int nStartAddr = nAddressNum;

	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  nStartAddr, 1);
}

int CConveyor::WritePlcCountInfo(int nTrackNum, int nPlcCount)
{
	BYTE	TxBuff[256];
	int     nStartAddr=0;

	memset(TxBuff, 0x00, sizeof(TxBuff));

	if(nPlcCount == 0)
		nPlcCount = 7;

    TxBuff[0] = (BYTE)(nPlcCount & 0xFF);


	switch(m_nNum)
	{
	case CV_7_PLC:
		{
			if(nTrackNum == 809-1)
				nStartAddr = 1094;
			else if(nTrackNum == 799-1)
				nStartAddr = 994;
			else if(nTrackNum == 808-1)
				nStartAddr = 1084;

			else if(nTrackNum == 833-1)
				nStartAddr = 1334;
			else if(nTrackNum == 837-1)
				nStartAddr = 1374;

			else if(nTrackNum == 746-1)
				nStartAddr = 464;
			else if(nTrackNum == 745-1)
			{
				nStartAddr = 464;
				TxBuff[1] = (BYTE)(nPlcCount & 0xFF);
			}

		}
		break;
	case CV_8_PLC:
		{
			if(nTrackNum == 2005-1)
				nStartAddr = 54;
		}
		break;
	}

	if(nTrackNum == 3)
	{
		nStartAddr = nTrackNum;

		if(nPlcCount == 7)
			nPlcCount = 0;

		TxBuff[0] = (BYTE)(nPlcCount & 0xFF);
	}

	return Write(CMD_WORD_UNIT, TxBuff, DEVICE_CODE_D,  nStartAddr, 1);	
}