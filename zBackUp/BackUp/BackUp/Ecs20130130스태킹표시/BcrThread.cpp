#include "stdafx.h"
#include "Ecs.h"
#include "EcsDoc.h"
#include "Serial.h"
#include "BcrComm.h"
#include "Thread.h"
#include "Log.h"

#define BCR_NOTIFY(xArg) ::PostMessage(pBcrInfo->m_hwndNotify, WM_USER_BCR_NOTIFY, pBcrInfo->m_nNum, xArg)
#define BCR_NUM		pBcrInfo->m_nNum

UINT BcrThreadProc(LPVOID pParam)
{
	SBcrThreadInfo* pBcrInfo = (SBcrThreadInfo*)pParam;

	CBcr Bcr(BCR_NUM, pBcrInfo->m_pDoc);
	if (!Bcr.Connect(pBcrInfo->m_szComName, 
					 pBcrInfo->m_nBaudRate,
					 pBcrInfo->m_nBitsPerChar,
					 pBcrInfo->m_nParity,
					 pBcrInfo->m_nStopBits))
	{
		BCR_NOTIFY(NOTIFY_ERROR);
#ifdef OPT_COMM_OPEN_ERROR_DISPLAY_USE
		MessageBox(GetFocus(), Bcr.m_strErrMsg, pBcrInfo->m_szComName, MB_ICONEXCLAMATION | MB_OK ) ;
#endif
		SetEvent(pBcrInfo->m_hEventBcrThreadKilled);
		return 0;
	}

	if (pBcrInfo->m_pDoc->m_pBcrInfo[BCR_NUM]->m_bStatus)
		BCR_NOTIFY(pBcrInfo->m_pDoc->m_pBcrInfo[BCR_NUM]->m_ucMode);
	else
		BCR_NOTIFY(NOTIFY_ERROR);

    while (TRUE) 
	{
		if (WaitForSingleObject(pBcrInfo->m_hEventSendBcr, 500) // Send notify
			== WAIT_OBJECT_0)
		{
			pBcrInfo->m_pDoc->m_nBcrEventCount[0]--;
		}

		if (pBcrInfo->m_pDoc->m_nBcrEventCount[0] > 0)
			SetEvent(pBcrInfo->m_hEventSendBcr);

		int nStatus = Bcr.ReadStatus();
		if (nStatus == FALSE)
		{
			pBcrInfo->m_pDoc->m_pBcrInfo[BCR_NUM]->m_bStatus = FALSE;
			BCR_NOTIFY(NOTIFY_ERROR);
		}
		else if (nStatus == TRUE)
			BCR_NOTIFY(pBcrInfo->m_pDoc->m_pBcrInfo[BCR_NUM]->m_ucMode);
				
		if (WaitForSingleObject(pBcrInfo->m_hEventKillBcrThread, 10) // Kill notify
			== WAIT_OBJECT_0)
		{
			break; // Terminate this thread by existing the proc.
		}
	}

	Bcr.Close();
	SetEvent(pBcrInfo->m_hEventBcrThreadKilled);
	
	return 0;
	
}
