
#include "stdafx.h"
#include "Ecs.h"

#include "EcsDoc.h"

#include "Thread.h"
#include "Rgv.h"

#define RGV_NOTIFY(xArg) ::PostMessage(pThreadInfo->m_hwndNotify, WM_USER_RGV_NOTIFY, pThreadInfo->m_nNum, xArg)

#define RGV_NUM		pThreadInfo->m_nNum
#define DEVICE		pThreadInfo->m_strDevice
#define DOC			pThreadInfo->m_pDoc
#define RGV_INFO	pThreadInfo->m_pRgvInfo

UINT RgvThreadProc(LPVOID pParam)
{
	SRgvThreadInfo* pThreadInfo = (SRgvThreadInfo *)pParam;

	CRgv Rgv(RGV_NUM, DOC); 
//	if (!Rgv.Connect(pThreadInfo->Port.szComName, pThreadInfo->Port.dwReadTimeOut))
	if (!Rgv.Connect(pThreadInfo->Port.szComName, 
		             pThreadInfo->Port.nBaudRate, 
					 pThreadInfo->Port.nBitsPerChar, 
					 pThreadInfo->Port.nParity,//NOPARITY, 
					 pThreadInfo->Port.nStopBits,//ONESTOPBIT, 
						   0))
	{
		RGV_INFO->m_wErrCode = RGV_ERR_CODE_COMM_ERROR;
		RGV_INFO->m_ucStatus = RGV_STA_ERROR;
		RGV_NOTIFY(NOTIFY_ERROR);
		DOC->m_pRgvThread[RGV_NUM] = NULL;

		SetEvent(pThreadInfo->m_hEventRgvThreadKilled);
		return 0;
	}

	while (TRUE)
	{
		if ( WaitForSingleObject(pThreadInfo->m_hEventSendRgv, 100) == WAIT_OBJECT_0 )
		{
			if (pThreadInfo->m_RgvMsg.bModified)
			{
				Rgv.CommandProc(&pThreadInfo->m_RgvMsg);
				pThreadInfo->m_RgvMsg.bModified = FALSE;
			}
		}

		RGV_NOTIFY(NOTIFY_SEND);

		if ( Rgv.ReadStatus() != TRUE ) 
		{
			Rgv.ErrorCheck();
			RGV_NOTIFY(NOTIFY_ERROR);
		}
		else
		{
			if ( RGV_INFO->m_ucStatus == RGV_STA_ERROR )
				Rgv.ErrorCheck();

			else
			{
				if ( Rgv.IsInvoke() )
					Rgv.CompleteCheck();

				else
					Rgv.InvokeCheck();
			}

			RGV_NOTIFY(NOTIFY_REFRESH);
		}

		if ( WaitForSingleObject(pThreadInfo->m_hEventKillRgvThread, 200) == WAIT_OBJECT_0 )
		{
			break;
		}
	}

	return 0;
}

#undef RGV_NUM
