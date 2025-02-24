#include "stdafx.h"
#include "Ecs.h"
#include "EcsDoc.h"
#include "Serial.h"
#include "Conveyor.h"
#include "Thread.h"
#include "Log.h"

#define CV_NOTIFY(xArg)  ::PostMessage(pConveyorInfo->m_hwndNotify, WM_USER_CV_NOTIFY, pConveyorInfo->m_nNum, xArg)
#define CV_NUM		pConveyorInfo->m_nNum
#define CV_SOCKET   pConveyorInfo->m_pSocket

UINT ConveyorThreadProc(LPVOID pParam)
{
	SConveyorThreadInfo* pConveyorInfo = (SConveyorThreadInfo*)pParam;
	
	CConveyor Conveyor(CV_NUM, pConveyorInfo->m_pDoc, CV_SOCKET);

/*	if (CV_NUM != 0)
	{
		SetEvent(pConveyorInfo->m_hEventConveyorThreadKilled);
		return 0;
	}
*/			
	pConveyorInfo->m_ConveyorMsg.bModified = FALSE;

    while (TRUE) 
	{
		if (WaitForSingleObject(pConveyorInfo->m_hEventSendConveyor, 200) // Send notify
			== WAIT_OBJECT_0)
		{
			
			if (pConveyorInfo->m_ConveyorMsg.bModified && pConveyorInfo->m_ConveyorMsg.nTrackNum < 700)
			{
				CV_NOTIFY(NOTIFY_SEND);

				if (Conveyor.WriteTrackInfo(pConveyorInfo->m_ConveyorMsg.nTrackNum, 
										pConveyorInfo->m_ConveyorMsg.nLuggNum, 
										pConveyorInfo->m_ConveyorMsg.nJobType, 
										pConveyorInfo->m_ConveyorMsg.nStartPos,
										pConveyorInfo->m_ConveyorMsg.nDestPos,
										pConveyorInfo->m_ConveyorMsg.nLastPallet) != TRUE)
						CV_NOTIFY(NOTIFY_ERROR);
				else
				{
					pConveyorInfo->m_ConveyorMsg.bModified = FALSE;
					CV_NOTIFY(NOTIFY_RECEIVE);
				}
			}
			else if(pConveyorInfo->m_ConveyorMsg.bModified && (pConveyorInfo->m_ConveyorMsg.nTrackNum >= 900 && pConveyorInfo->m_ConveyorMsg.nTrackNum < 2000))
			{
				CV_NOTIFY(NOTIFY_SEND);

				if (Conveyor.WriteTrackInfo2(pConveyorInfo->m_ConveyorMsg.nTrackNum, 
									  pConveyorInfo->m_ConveyorMsg.nLuggNum,	
									  pConveyorInfo->m_ConveyorMsg.nStartPos, 
									  pConveyorInfo->m_ConveyorMsg.nDestPos, 
									  pConveyorInfo->m_ConveyorMsg.nJobType) != TRUE)

					CV_NOTIFY(NOTIFY_ERROR);
				else
				{
					pConveyorInfo->m_ConveyorMsg.bModified = FALSE;
					CV_NOTIFY(NOTIFY_RECEIVE);
				}
			}
			else if (pConveyorInfo->m_ConveyorMsg.bModified && pConveyorInfo->m_ConveyorMsg.nTrackNum >= 700)
			{
				CV_NOTIFY(NOTIFY_SEND);

				if (Conveyor.WriteTrackInfo7(pConveyorInfo->m_ConveyorMsg.nTrackNum, 
									  pConveyorInfo->m_ConveyorMsg.nLuggNum,	
									  pConveyorInfo->m_ConveyorMsg.nLuggNum2,
									  pConveyorInfo->m_ConveyorMsg.nStartPos, 
									  pConveyorInfo->m_ConveyorMsg.nDestPos, 
									  pConveyorInfo->m_ConveyorMsg.nJobType,
									  pConveyorInfo->m_ConveyorMsg.nComplete,
									  pConveyorInfo->m_ConveyorMsg.nSize) != TRUE)

					CV_NOTIFY(NOTIFY_ERROR);
				else
				{
					pConveyorInfo->m_ConveyorMsg.bModified = FALSE;
					CV_NOTIFY(NOTIFY_RECEIVE);
				}
			}
			else
			{
				switch(CV_NUM)
				{
				case CV_1_PLC:
					break;
				case CV_3_PLC:
					{
						Conveyor.RetInvokeCheck();
						Conveyor.RetInvokeCheck2();
					}
					break;

				}
			}

			if(pConveyorInfo->m_pDoc->m_bInResetCheck)
			{
				if(Conveyor.WriteInCounterReset(pConveyorInfo->m_pDoc->m_nInCountReset) != TRUE) CV_NOTIFY(NOTIFY_ERROR);
				else
				{
					pConveyorInfo->m_pDoc->m_bInResetCheck = FALSE;
					CV_NOTIFY(NOTIFY_RECEIVE);
				}

			}

			if ( pConveyorInfo->m_ConveyorTroubleMsg.bModified )
			{
				CV_NOTIFY(NOTIFY_SEND);
				if ( Conveyor.WriteTroubleInfo(pConveyorInfo->m_ConveyorTroubleMsg.nAddressNum,
					                    pConveyorInfo->m_ConveyorTroubleMsg.wAddressData) != TRUE)
					CV_NOTIFY(NOTIFY_ERROR);
				else
				{
					pConveyorInfo->m_ConveyorTroubleMsg.bModified = FALSE;
					CV_NOTIFY(NOTIFY_RECEIVE);
				}
			}

			if (pConveyorInfo->m_PlcCountMsg.bModified)
			{
				CV_NOTIFY(NOTIFY_SEND);

				if (Conveyor.WritePlcCountInfo(pConveyorInfo->m_PlcCountMsg.nTrackNum, 
									  pConveyorInfo->m_PlcCountMsg.nPlcCount) != TRUE)

					CV_NOTIFY(NOTIFY_ERROR);
				else
				{
					pConveyorInfo->m_PlcCountMsg.bModified = FALSE;
					CV_NOTIFY(NOTIFY_RECEIVE);
				}
			}

			

			pConveyorInfo->m_pDoc->m_nConveyorEventCount[0]--;
		}

		if (pConveyorInfo->m_pDoc->m_nConveyorEventCount[0] > 0)
			SetEvent(pConveyorInfo->m_hEventSendConveyor);

		CV_NOTIFY(NOTIFY_SEND);
		
		switch(CV_NUM)
		{
		case	CV_1_PLC:
			if (Conveyor.ReadStatus1() != TRUE) 
				CV_NOTIFY(NOTIFY_ERROR);

			else
			{
				Conveyor.StoInvokeCheck();
				Conveyor.StoInvokeCheck7();

				Conveyor.RemoveCvData1Group();

				CV_NOTIFY(NOTIFY_REFRESH);
			}
			break;

		case	CV_2_PLC:
			if (Conveyor.ReadStatus2() != TRUE) 
				CV_NOTIFY(NOTIFY_ERROR);
			else
			{
				Conveyor.StoInvokeCheck2();
				Conveyor.StoMoveInvokeCheck2();

				//Conveyor.CvDataChange2GroupTo1Group();

				CV_NOTIFY(NOTIFY_REFRESH);
			}
			break;

		case	CV_3_PLC:
			if (Conveyor.ReadStatus3() != TRUE) 
				CV_NOTIFY(NOTIFY_ERROR);
			else
			{
				Conveyor.RetInvokeCheck();
				Conveyor.RetInvokeCheck2();
				Conveyor.ArriveCountCheck();
				Conveyor.ArriveDataCopy();

				Conveyor.RemoveCvData3Group();
				Conveyor.RemoveCvData3GroupTo8Group();

				CV_NOTIFY(NOTIFY_REFRESH);
			}
			break;
		case	CV_4_PLC:
			if (Conveyor.ReadStatus4() != TRUE) 
				CV_NOTIFY(NOTIFY_ERROR);
			else
			{
				Conveyor.CvDataChange3GroupTo4Group();
				Conveyor.RemoveCvData4Group();
				Conveyor.ArriveRemoveCheck4Group();

				CV_NOTIFY(NOTIFY_REFRESH);
			}
			break;
		case	CV_5_PLC:
			if (Conveyor.ReadStatus5() != TRUE) 
				CV_NOTIFY(NOTIFY_ERROR);
			else
			{
				Conveyor.CvDataChange4GroupTo5Group();
				Conveyor.RemoveCvData5Group();
				Conveyor.ArriveRemoveCheck5Group();

				CV_NOTIFY(NOTIFY_REFRESH);
			}
			break;
		case	CV_6_PLC:
			if (Conveyor.ReadStatus6() != TRUE) 
				CV_NOTIFY(NOTIFY_ERROR);
			else
			{
				Conveyor.CvDataChange5GroupTo6Group();
				Conveyor.ArriveRemoveCheck6Group();

				CV_NOTIFY(NOTIFY_REFRESH);
			}
			break;
		case	CV_7_PLC:
			if (Conveyor.ReadStatus7() != TRUE) 
				CV_NOTIFY(NOTIFY_ERROR);
			else
			{
				Conveyor.RgvCompleteCheck3();
				Conveyor.RgvCompleteCheck4();

				Conveyor.InvokeCheck();

				Conveyor.ArrivedCheck1();
				Conveyor.ArrivedCheck2();

				//Conveyor.StoManualInvokeCheck7();
				Conveyor.SiteInvokeCheck7();
				Conveyor.ManualInvokeCheck7();

				Conveyor.CvDataChange1GroupTo7Group();
				Conveyor.CvDataChange8GroupTo7Group();

				Conveyor.LineCountCheck();

				Conveyor.RemoveCvData7Group();

				CV_NOTIFY(NOTIFY_REFRESH);
			}
			break;
		case	CV_8_PLC:
			if (Conveyor.ReadStatus8() != TRUE) 
				CV_NOTIFY(NOTIFY_ERROR);
			else
			{
				Conveyor.CvDataChange7GroupTo8Group();
				Conveyor.CvDataChange3GroupTo8Group();

				Conveyor.ArrivedCheck3();

				Conveyor.RemoveCvData8Group();
				//Conveyor.RemoveCvData8GroupTo3Group();

				CV_NOTIFY(NOTIFY_REFRESH);
			}
			break;
		}

		
		if (WaitForSingleObject(pConveyorInfo->m_hEventKillConveyorThread, 500) // Kill notify
			== WAIT_OBJECT_0)
		{
			break;
		}
	}

//	Conveyor.Close();
	SetEvent(pConveyorInfo->m_hEventConveyorThreadKilled);
	return 0;
}
