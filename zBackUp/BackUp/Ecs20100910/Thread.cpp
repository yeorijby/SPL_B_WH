#include "stdafx.h"
#include "Ecs.h"
#include "EcsDoc.h"
#include "Serial.h"
#include "Plc.h"
#include "Thread.h"

#define CV_NOTIFY(xArg) ::PostMessage(pConveyorInfo->m_hwndNotify, WM_USER_CV_NOTIFY, pConveyorInfo->m_nNum, xArg)

UINT ConveyorThreadProc(LPVOID pParam)
{
	CConveyorThreadInfo* pConveyorInfo = (CConveyorThreadInfo*)pParam;

	CPlc Plc;
	if (!Plc.Connect("COM1"))
		MessageBox(GetFocus(), Plc.m_strErrMsg, "PLC ERROR", MB_ICONEXCLAMATION | MB_OK ) ;
//	else
//		CV_NOTIFY(100);

    while (TRUE) {

		BOOL bWriteJobExist = FALSE;
		if (WaitForSingleObject(pConveyorInfo->m_hEventSendConveyor, 10) // Send notify
			== WAIT_OBJECT_0)
		{
			bWriteJobExist = TRUE;
		}

		unsigned char Buff[256];
		if (!Plc.Send(Buff, 5)) CV_NOTIFY(-2);
//		CV_NOTIFY(NOTIFY_REFRESH);
		
		if (WaitForSingleObject(pConveyorInfo->m_hEventKillConveyorThread, 10) // Kill notify
			== WAIT_OBJECT_0)
		{
			break; // Terminate this thread by existing the proc.
		}
	}

	Plc.Close();
	SetEvent(pConveyorInfo->m_hEventConveyorThreadKilled);
	return 0;
}

UINT StackerThreadProc(LPVOID pParam)
{
	CStackerThreadInfo* pStackerInfo = (CStackerThreadInfo*)pParam;
	int nCnt = 0;

    while (TRUE) {
		
		if (WaitForSingleObject(pStackerInfo->m_hEventSendStacker, 0)
			== WAIT_OBJECT_0)
		{
//			AfxMessageBox("EventSendStacker");
		}

		nCnt++;
		if (nCnt == 0)
		{
			::PostMessage(pStackerInfo->m_hwndNotify,
				WM_USER_SC_READ_DONE, pStackerInfo->m_nNum, 0);
		}

		if (WaitForSingleObject(pStackerInfo->m_hEventKillStackerThread, 0)
			== WAIT_OBJECT_0)
		{
			CString strTemp;
			strTemp.Format("EventKillStackerThread, ScNum=[%d], Count=[%d]", 
				pStackerInfo->m_nNum, nCnt);
//			AfxMessageBox(strTemp);
			break; // Terminate this thread by existing the proc.
		}

		Sleep(50);
	}

	SetEvent(pStackerInfo->m_hEventStackerThreadKilled);
	return 0;
}
