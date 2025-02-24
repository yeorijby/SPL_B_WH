#include "stdafx.h"
#include "Ecs.h"
#include "EcsDoc.h"
#include "Serial.h"
#include "Thread.h"
#include "StackerTwin.h"

#define SC_NOTIFY(xArg) ::PostMessage(pStackerInfo->m_hwndNotify, WM_USER_SC_NOTIFY, pStackerInfo->m_nNum, xArg)

#define SC_NUM	pStackerInfo->m_nNum
#define DOC		pStackerInfo->m_pDoc
#define SC_INFO	pStackerInfo->m_pStackerInfo

UINT StackerThreadProc(LPVOID pParam)
{
	SStackerThreadInfo* pStackerInfo = (SStackerThreadInfo *)pParam;
	CStacker Stacker(SC_NUM, DOC);

	if (!Stacker.Connect(pStackerInfo->m_szComName, 
						 pStackerInfo->m_nBaudRate,
						 pStackerInfo->m_nBitsPerChar,
						 pStackerInfo->m_nParity,
						 pStackerInfo->m_nStopBits))
	{
		SC_NOTIFY(NOTIFY_ERROR);
#ifdef OPT_COMM_OPEN_ERROR_DISPLAY_USE
		MessageBox(GetFocus(), pStacker->m_strErrMsg, pStackerInfo->m_szComName, MB_ICONEXCLAMATION | MB_OK ) ;
#endif
		SetEvent(pStackerInfo->m_hEventStackerThreadKilled);

		return 0;
	}
	
/*	if (SC_NUM != 1)
	{
		SetEvent(pStackerInfo->m_hEventStackerThreadKilled);

		return 0;
	}
*/			
    while (TRUE)
	{
		if ( WaitForSingleObject(pStackerInfo->m_hEventSendStacker, 200)
			== WAIT_OBJECT_0 )		
		{
			Stacker.CommandProc(&pStackerInfo->m_StackerMsg);
			if ( !Stacker.IsInvoke() )
			{
				Stacker.InvokeCheck();
			}
			DOC->m_nStackerEventCount[SC_NUM]--;
		}

		if ( DOC->m_nStackerEventCount[SC_NUM] > 0 )
			SetEvent(pStackerInfo->m_hEventSendStacker);

		SC_NOTIFY(NOTIFY_SEND);

//		Stacker.ScDiagnosis();

		if ( Stacker.ReadStatus() != TRUE ) 
		{
			Stacker.ErrorCheck();
			SC_NOTIFY(NOTIFY_ERROR);
		}
		else
		{
			if ( SC_INFO->m_ucStatus == SC_STA_ERROR )
			{
				Stacker.ErrorCheck();
				Stacker.ErrorRoutine();
			}
			else
			{
				if ( Stacker.IsInvoke() )
				{
					Stacker.CompleteCheck();
				}
				else
				{
					Stacker.InvokeCheck();
				}
			}
			SC_NOTIFY(NOTIFY_REFRESH);
		}

		if ( WaitForSingleObject(pStackerInfo->m_hEventKillStackerThread, 500)
			== WAIT_OBJECT_0 )
		{
			break; // Terminate this thread by existing the proc.
		}
		
	}

	Stacker.Close();

	SetEvent(pStackerInfo->m_hEventStackerThreadKilled);
	return 0;
}

#undef SC_NUM