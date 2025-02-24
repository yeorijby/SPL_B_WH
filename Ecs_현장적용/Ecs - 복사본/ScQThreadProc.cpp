
#include "stdafx.h"
#include "Ecs.h"
#include "ScQ.h"
#include "Lib.h"

#define SC_NOTIFY(xArg) ::PostMessage(pStackerThreadInfo->m_hwndNotify, WM_USER_SC_NOTIFY, pStackerThreadInfo->m_nNum, xArg)

#define DOC		pStackerThreadInfo->m_pDoc
#define SOCKET	pStackerThreadInfo->m_pSocket
#define SC_NUM	pStackerThreadInfo->m_nNum
#define SC_INFO	pStackerThreadInfo->m_pStackerInfo

UINT ScQThreadProc(LPVOID pParam)
{

	SStackerThreadInfo* pStackerThreadInfo = (SStackerThreadInfo*)pParam;
	CScQ Sc(SC_NUM, DOC, SOCKET);

	while (TRUE)
	{
		if ( WaitForSingleObject(pStackerThreadInfo->m_hEventSendStacker, 600)
			== WAIT_OBJECT_0 )
		{
			if (pStackerThreadInfo->m_StackerMsg.bModified)
			{
				Sc.CommandProc(&pStackerThreadInfo->m_StackerMsg);
				pStackerThreadInfo->m_StackerMsg.bModified = FALSE;
			}
		}

		SC_NOTIFY(NOTIFY_SEND);

		if ( Sc.ReadStatus() != TRUE ) 
		{
			Sc.ErrorCheck();
			SC_NOTIFY(NOTIFY_ERROR);
		}
		else
		{
			if ( SC_INFO->m_ucStatus == SC_STA_ERROR )
			{
				Sc.ErrorCheck();
				Sc.ErrorRoutine();
			}
			else
			{
				if ( Sc.IsInvoke() )
				{
					Sc.CompleteCheck();
				}
				else
				{
					Sc.InvokeCheck();
				}
			}
			SC_NOTIFY(NOTIFY_REFRESH);
		}

		if ( WaitForSingleObject(pStackerThreadInfo->m_hEventKillStackerThread, 600) == WAIT_OBJECT_0 )
		{
			break;
		}
	}

//	Sc.Close();
	SetEvent(pStackerThreadInfo->m_hEventStackerThreadKilled);
	return 0;
}

#undef SC_NUM