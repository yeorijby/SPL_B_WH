// EcsDoc.cpp : implementation of the CEcsDoc class
//

#include "stdafx.h"
#include "Ecs.h"

#include "EcsDoc.h"
#include "Log.h"
#include "LogDlg.h"
#include "ManualDlg.h"
#include "JobDlg.h"
#include "MoveJobDlg.h"
#include "ConfigDlg.h"
#include "MainFrm.h"
#include "Statistic.h"
#include "StatisticAvailDlg.h"
#include "StatisticThroughputDlg.h"
#include "StatisticErrCodeDlg.h"
#include "ScErrDlg.h"
#include "PasswordDlg.h"
#include "ColorViewDlg.h"
#include "ScInhibitDlg.h"
#include "Lib.h"

#include "LogoDlg.h"

#ifdef _WIN32
#ifndef _UNICODE
#include <strstrea.h>
#endif
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define THREAD_RUN
/////////////////////////////////////////////////////////////////////////////
// CEcsDoc

IMPLEMENT_DYNCREATE(CEcsDoc, CDocument)

BEGIN_MESSAGE_MAP(CEcsDoc, CDocument)
	//{{AFX_MSG_MAP(CEcsDoc)
	ON_COMMAND(ID_LOGGING, OnLogging)
	ON_COMMAND(ID_MANUAL, OnManual)
	ON_COMMAND(ID_JOB, OnJob)
	ON_COMMAND(ID_MOVE_JOB, OnMoveJob)
	ON_COMMAND(ID_SYSTEM_CONFIG, OnConfig)
	ON_COMMAND(ID_LOGO, OnLogo)
//	ON_COMMAND(ID_SYSTEM_RESET_RESULT_COUNT, OnSystemResetResultCount)
//	ON_COMMAND(ID_SYSTEM_REMOVE_ALL_JOB, OnSystemRemoveAllJob)
	ON_COMMAND(ID_STATISTICS_AVAIL, OnStatisticsAvail)
	ON_COMMAND(ID_STATISTICS_THROUGHPUT, OnStatisticsThroughput)
	ON_COMMAND(ID_STATISTICS_ERRCODE, OnStatisticsErrcode)
//	ON_COMMAND(ID_SC_ERRLOG, OnScErrLog)
//	ON_COMMAND(ID_SYSTEM_RESET_STATISTIC_INFO, OnSystemResetStatisticInfo)
//	ON_COMMAND(ID_COLOR_VIEW, OnColorView)
	ON_COMMAND(ID_COMM_HOST_CLIENT, OnCommHostClient)
	ON_COMMAND(ID_COMM_HOST_SERVER, OnCommHostServer)
	ON_COMMAND(ID_COMM_CV_1, OnCommCv1)
	ON_COMMAND(ID_COMM_CV_2, OnCommCv2)
	ON_COMMAND(ID_COMM_CV_3, OnCommCv3)
	ON_COMMAND(ID_COMM_CV_4, OnCommCv4)
	ON_COMMAND(ID_COMM_CV_5, OnCommCv5)
	ON_COMMAND(ID_COMM_CV_6, OnCommCv6)
	ON_COMMAND(ID_COMM_CV_7, OnCommCv7)
	ON_COMMAND(ID_COMM_CV_8, OnCommCv8)
	ON_COMMAND(ID_COMM_CV_9, OnCommCv9)
	ON_COMMAND(ID_COMM_SC_1, OnCommSc1)
	ON_COMMAND(ID_COMM_SC_2, OnCommSc2)
	ON_COMMAND(ID_COMM_SC_3, OnCommSc3)
	ON_COMMAND(ID_COMM_SC_4, OnCommSc4)
	ON_COMMAND(ID_COMM_SC_5, OnCommSc5)
	ON_COMMAND(ID_COMM_SC_6, OnCommSc6)
	ON_COMMAND(ID_COMM_RGV_1, OnCommRgv1)
	ON_COMMAND(ID_COMM_RGV_2, OnCommRgv2)
	ON_COMMAND(ID_COMM_NEW_ECS, OnCommNewEcs)
//	ON_COMMAND(ID_SC_INHIBIT, OnScInhibit)

	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_DATE, OnUpdateDateTime)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_MODE, OnUpdateMode)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEcsDoc construction/destruction

CEcsDoc::CEcsDoc()
{
#ifdef TEST_MODE
	m_nSto = 0;
	m_nRet = 1000;
#endif
	m_nAlive = 1;

	m_pListenSk = NULL;
	m_pHostCl   = NULL;
	m_pHostSv   = NULL;
	m_pEcsCl	= NULL;

	m_pLog      = NULL;
	m_pConfig   = NULL;
	m_pJob      = NULL;

	for ( int i = 0; i < SC_CNT; i++ )
	{
		m_pStackerSocket[i] = NULL;
		m_pStackerThread[i] = NULL;
		m_nStackerEventCount[i] = 0;
		m_bScSta[i] = TRUE;
		m_bScJobHold[i] = FALSE;
		m_bScEmerStop[i] = FALSE;
	}

	for ( i = 0; i < CV_PLC_CNT; i++ )
	{
		m_pConveyorSocket[i] = NULL;
		m_pConveyorThread[i] = NULL;
		m_nConveyorEventCount[i] = 0;
		m_bCvSta[i] = TRUE;
	}

	for ( i = 0; i < RGV_CNT; i++ )
	{
		m_pRgvThread[i] = NULL;
		m_pRgvInfo[i] = NULL;
		m_nRgvEventCount[i] = 0;
	}

	for( i = 0; i < 6; i++)
	{
		m_b4groupBuffIn[i] = FALSE;
	}

	for( i = 0; i < 6; i++)
	{
		m_b5groupBuffIn[i] = FALSE;
	}

	for( i = 0; i < 6; i++)
	{
		m_b6groupBuffIn[i] = FALSE;
	}

	for ( i = 0; i < 2; i++)
	{
		m_bSafetyError[i] = FALSE;
	}

	for ( i = 0; i < 2; i++)
	{
		m_bRtvCpError[i] = FALSE;
	}
	

	m_ConveyorMsg.bCopy = FALSE;

	m_bBuzzer = FALSE;
	m_nDispLine = 1;
	m_bCv1Alive = FALSE;

	m_nRetCnt[0] = 1;
	m_nRetCnt[1] = 1;

	m_bStoRetMode = FALSE;

	m_n4GroupInCount = 0;
	m_n4GroupOutCount = 0;
	m_n5GroupInCount = 0;
	m_n5GroupOutCount = 0;
	m_n6GroupInCount = 0;
	m_n6GroupOutCount = 0;

	m_n7GroupInCount = 0;

	m_n4GroupInternalCount = 0;
	m_n5GroupInternalCount = 0;
	m_n6GroupInternalCount = 0;

	m_n4GroupCvCount = 0;
	m_n5GroupCvCount = 0;
	m_n6GroupCvCount = 0;

	m_n4GroupInternalBatch = 0;
	m_n5GroupInternalBatch = 0;
	m_n6GroupInternalBatch = 0;
	m_n7GroupInternalBatch = 0;

	m_n4groupInternalPalletCount = 0;
	m_n5groupInternalPalletCount = 0;
	m_n6groupInternalPalletCount = 0;
	m_n7groupInternalPalletCount = 0;

	m_n4GroupInternalPallet = 0;
	m_n5GroupInternalPallet = 0;
	m_n6GroupInternalPallet = 0;
	m_n7GroupInternalPallet = 0;

	m_b4groupCheck = 0;
	m_b5groupCheck = 0;
	m_b6groupCheck = 0;	
	m_b7groupCheck = 0;	
	m_b8groupCheck = 0;	
	m_b9groupCheck = 0;	

	m_n4goupBuffCouter = 0;
	m_n5goupBuffCouter = 0;
	m_n6goupBuffCouter = 0;

	m_nInCountReset = 0;

	m_bInResetCheck = FALSE;

	m_bWriteTroubleCheck = FALSE;
	m_bWriteLineTroubleCheck = FALSE;
	m_bJobStopCheck = FALSE;
	m_bBufferStopCheck = FALSE;

	m_bWriteStackingCheck1=FALSE;
	m_bWriteStackingCheck2=FALSE;

	m_bSetLineCheck = FALSE;
	m_bSetLineCheck2 = FALSE;

	m_bSetCountCheck = FALSE;
	m_bSetTestCheck = TRUE;

	m_bAllScStoSuspend = FALSE;
	m_bAllScRetSuspend = FALSE;

	for( i = 0; i < 10; i++)
	{
		m_nSetLine[i] = 0;
	}

	for( i = 0; i < 10; i++)
	{
		m_nSetLineCount[i] = 0;
	}

	for( i = 0; i < 10; i++)
	{
		m_bBufferLock[i] = FALSE;
	}	

	for( i = 0; i < 14; i++)
	{
		m_nSetLine2[i] = 0;
	}

	for( i = 0; i < 14; i++)
	{
		m_nSetLineCount2[i] = 0;
	}

	for( i = 0; i < 14; i++)
	{
		m_bBufferLock2[i] = FALSE;

		m_bLineGoing[i] = FALSE;
	}	

	m_bPriorityDocCheck = FALSE;
	m_strDualCheck = "";
	m_bAlarmError = FALSE;

	for( i = 0; i < 6; i++)
	{
		m_bStoSafetyError[i] = FALSE;
		m_bRetSafetyError[i] = FALSE;
	}

	m_strCodeNum	= "";
	m_nPeriodNum	= 0;
	m_strProdName	= "";
	m_strQuantity = "";
	m_strLineNum = "";
	m_strCheckNum = "";

	m_strCodeNum2	= "";
	m_nPeriodNum2	= 0;
	m_strProdName2	= "";
	m_strQuantity2 = "";
	m_strLineNum2 = "";
	m_strCheckNum2 = "";

	m_bAllStackerEmergency = FALSE;

	m_nLineModeAB = 0;
}

CEcsDoc::~CEcsDoc()
{

	m_nAlive = 0;

#ifdef THREAD_RUN

	CString strLog;
	DWORD dwExitCode;

	m_pStatistic->Backup();

	for ( int i = 0; i < SC_CNT; i++ )
	{
		if ( m_pStackerThread[i] != NULL &&
			GetExitCodeThread(m_pStackerThread[i]->m_hThread, &dwExitCode) &&
			dwExitCode == STILL_ACTIVE )
		{
			SetEvent(m_hEventKillStackerThread[i]);
			WaitForSingleObject(m_hEventStackerThreadKilled[i], INFINITE);
			strLog.Format("Stacker #%d Thread Terminated..", i + 1);
			m_pLog->Event(LOG_POS_SC, LOG_SYSTEM, strLog);
		}

		if (m_pStackerSocket[i] != NULL)	
			delete m_pStackerSocket[i];

 		m_pStackerInfo[i]->Backup();
		delete m_pStackerInfo[i];
	}

	for ( i = 0; i < CV_PLC_CNT; i++ )
	{
		if ( m_pConveyorThread[i] != NULL &&
			GetExitCodeThread(m_pConveyorThread[i]->m_hThread, &dwExitCode) &&
			dwExitCode == STILL_ACTIVE )
		{
			SetEvent(m_hEventKillConveyorThread[i]);
			WaitForSingleObject(m_hEventConveyorThreadKilled[i], INFINITE);
			strLog.Format("Conveyor #%d Thread Terminated..", i + 1);
			m_pLog->Event(LOG_POS_CV, LOG_SYSTEM, strLog);
		}

		m_pConveyorSocket[i] = NULL;
		if (m_pConveyorSocket[i] != NULL)
		{	
			delete m_pConveyorSocket[i];
//			m_pConveyorSocket[i] = NULL;
		}

	}

	for (i = 0; i < RGV_CNT; i++ )
	{
		if ( m_pRgvThread[i] != NULL &&
			GetExitCodeThread(m_pRgvThread[i]->m_hThread, &dwExitCode) &&
			dwExitCode == STILL_ACTIVE )
		{
			SetEvent(m_hEventKillRgvThread[i]);
			WaitForSingleObject(m_hEventRgvThreadKilled[i], 500);
			strLog.Format("Rtv #%d Thread Terminated..", i + 1);
			m_pLog->Event(LOG_POS_RGV, LOG_SYSTEM, strLog);
		}

		m_pRgvInfo[i]->Backup();
		if (m_pRgvInfo[i] != NULL)	 
		delete m_pRgvInfo[i];
	}

#endif // THREAD_RUN

	if (m_pListenSk != NULL)
		delete m_pListenSk;

	if (m_pHostSv != NULL)
		delete m_pHostSv;

	if (m_pHostCl != NULL)
		delete m_pHostCl;


	
	if (m_pConfig != NULL)
		delete m_pConfig;

	if (m_pStatistic != NULL)
		delete m_pStatistic;
	
	if (m_pJob != NULL)
		delete m_pJob;

	if (m_pMoveJob != NULL)
		delete m_pMoveJob;

	m_pLog->Event(LOG_POS_SYSTEM, LOG_SYSTEM, "Equipment Control System Terminated..");
	
	if (m_pLog != NULL)
		delete m_pLog;

	for (POSITION pos = m_MsgList.GetHeadPosition(); pos != NULL;)
	{
		delete m_MsgList.GetNext(pos);
	}
	m_MsgList.RemoveAll();

	if (m_pEcsCl != NULL)
		delete m_pEcsCl;

}

BOOL CEcsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return Initialize();
}

/////////////////////////////////////////////////////////////////////////////
// CEcsDoc serialization

void CEcsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEcsDoc diagnostics

#ifdef _DEBUG
void CEcsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEcsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEcsDoc commands

BOOL CEcsDoc::ConnectSocket(LPCTSTR lpszAddress, UINT nPort)
{
	// Host Socket
	if (m_pHostCl != NULL)
	{
		m_pLog->Error(LOG_POS_SYSTEM, LOG_SYSTEM, "이미 IMS 서버와 접속 되어 있슴.. !");
		return TRUE;
	}

	CHostCl *pHostCl = new CHostCl(this);

	if (!pHostCl->Create())
	{
		pHostCl->ShutDown();
		delete pHostCl;
		m_pHostCl = NULL;
		AfxMessageBox(IDS_CREATEFAILED);
		return FALSE;
	}
	pHostCl->Connect(lpszAddress, nPort);


/*
	m_pTempCl = new CHostCl(this);

	if (!m_pTempCl->Create())
	{
		m_pTempCl->ShutDown();
		delete m_pTempCl;
		m_pTempCl = NULL;
		AfxMessageBox(IDS_CREATEFAILED);
		return FALSE;
	}

	m_pTempCl->Connect(lpszAddress, nPort);
*/
	return TRUE;
}
BOOL CEcsDoc::ConnectEcsSocket(LPCTSTR lpszAddress, UINT nPort)
{
	// ECS Socket
	if (m_pEcsCl != NULL)
	{
		m_pLog->Error(LOG_POS_SYSTEM, LOG_SYSTEM, "이미 신규 ECS와 접속 되어 있슴.. !");
		return TRUE;
	}

	m_pEcsCl = new CEcsSockClient(this);

	if (!m_pEcsCl->Create())
	{
		m_pEcsCl->ShutDown();
		delete m_pEcsCl;
		m_pEcsCl = NULL;
		AfxMessageBox(IDS_CREATEFAILED);
		return FALSE;
	}
	m_pEcsCl->Connect(lpszAddress, nPort);

//	delete pEcsCl;
	return TRUE;
}

void CEcsDoc::ProcessPendingRead() 
{
	/*
	do
	{
		ReceiveMsg();
		if (m_pHost == NULL)
			return;
	}
	while(!m_pArchiveIn->IsBufferEmpty());
	*/
}

void CEcsDoc::SendMsg(CString& strText)
{
}

void CEcsDoc::ReceiveMsg()
{
}

void CEcsDoc::DeleteContents() 
{
	if (m_pHostSv != NULL)
	{
		BYTE Buffer[50];
		m_pHostSv->ShutDown();

		while(m_pHostSv->Receive(Buffer, 50) > 0);
	}

	delete m_pHostSv;
	m_pHostSv = NULL;

	CDocument::DeleteContents();
}

void CEcsDoc::OnUpdateDateTime(CCmdUI* pCmdUI) 
{
	CTime theTime = CTime::GetCurrentTime();

	CString strDateTime = theTime.Format( "%X, %Y/%m/%d %A" );

	pCmdUI->Enable(TRUE);
	pCmdUI->SetText(strDateTime);
}

void CEcsDoc::OnUpdateMode(CCmdUI* pCmdUI) 
{
	CString strMode;

#ifdef OPT_HOST_NETWORK_INTERFACE_USE
	if (m_pHostCl == NULL)
		strMode = "PendingCL";
	else if (m_pHostSv == NULL)
		strMode = "PendingSV";
	else
		strMode = "Connected";
#endif

#ifdef OPT_HOST_SAP_INTERFACE
		strMode = "Connected";
#endif

	pCmdUI->Enable(TRUE);
	pCmdUI->SetText(strMode);
}

void CEcsDoc::ConnectServer()
{
	ConnectSocket(m_pConfig->m_strHostAddr, m_pConfig->m_nHostPort);
}
void CEcsDoc::ConnectEcsServer()
{
	ConnectEcsSocket(m_pConfig->m_strEcsAddr, m_pConfig->m_nEcsPort);
}

BOOL CEcsDoc::Initialize()
{
/*	CLogoDlg LogoDlg;
	LogoDlg.m_bInitial = TRUE;
	LogoDlg.DoModal();
*/

	m_pConfig = new CConfig(this);

	m_pStatistic = new CStatistic(this, CString("..\\stc\\"), CString("Statistics"), CString("ErrorCode"));

	m_pLog = new CLog(this, CString("..\\log\\"), CString("Main"));

	m_pLog->Event(LOG_POS_SYSTEM, LOG_SYSTEM, "Equipment Control System Ver 2.2 Start..");

	m_pJob = new CJob(this);

	m_pMoveJob = new CMoveJob(this);

	Restore();
	MoveRestore();

#ifdef OPT_HOST_NETWORK_INTERFACE_USE

	m_pListenSk = new CListenSk(this);
	//if (m_pListenSk->Create(m_pConfig->m_nHostPort))
	if (m_pListenSk->Create(5000))
		m_pListenSk->Listen();

	if (m_pConfig->m_bConnect)
		ConnectServer();
#endif

#ifdef OPT_HOST_SAP_INTERFACE_USE
	m_pSapHost = new CSapHost(this);
#endif

	POSITION pos = GetFirstViewPosition();
	ASSERT(pos != NULL);
	CView* pView = GetNextView(pos);
	ASSERT(pView != NULL);

	m_hwndView = pView->m_hWnd;

#ifdef THREAD_RUN

#ifdef OPT_HOST_NETWORK_INTERFACE
	m_hEventHostNotify = CreateEvent(NULL, FALSE, FALSE, NULL); // auto reset, initially reset
	m_hEventKillHostThread = CreateEvent(NULL, FALSE, FALSE, NULL); // auto reset, initially reset
	m_hEventHostThreadKilled = CreateEvent(NULL, FALSE, FALSE, NULL); // auto reset, initially reset

	m_HostThreadInfo.m_hEventNotify = m_hEventHostNotify;
	m_HostThreadInfo.m_hEventKillThread = m_hEventKillHostThread;
	m_HostThreadInfo.m_hEventThreadKilled = m_hEventHostThreadKilled;

	strcpy(m_HostThreadInfo.m_szComName, m_pConfig->m_sDispPort.szComName);

#endif

	if (m_pConfig->m_bEcsConnect)
		ConnectEcsServer();

	for (int i = 0; i < SC_CNT; i++)
	{
		CString strFileName;
		strFileName.Format("..\\Temp\\ScInfo%d.Ecs", i + 1);
		m_pStackerInfo[i] = new CStackerInfo(this, strFileName);
		m_pStackerInfo[i]->Restore();
		m_pStackerInfo[i]->m_bModified = TRUE;

		m_hEventSendStacker[i] = CreateEvent(NULL, FALSE, FALSE, NULL); // auto reset, initially reset
		m_hEventKillStackerThread[i] = CreateEvent(NULL, FALSE, FALSE, NULL); // auto reset, initially reset
		m_hEventStackerThreadKilled[i] = CreateEvent(NULL, FALSE, FALSE, NULL); // auto reset, initially reset

		m_StackerThreadInfo[i].m_hEventSendStacker = m_hEventSendStacker[i];
		m_StackerThreadInfo[i].m_hEventKillStackerThread = m_hEventKillStackerThread[i];
		m_StackerThreadInfo[i].m_hEventStackerThreadKilled = m_hEventStackerThreadKilled[i];

		m_StackerThreadInfo[i].m_nNum = i;
		//필요 없음 
		strcpy(m_StackerThreadInfo[i].m_szComName, m_pConfig->m_sScPort[i].szComName);
		m_StackerThreadInfo[i].m_nBaudRate = m_pConfig->m_sScPort[i].nBaudRate;
	    m_StackerThreadInfo[i].m_nParity = m_pConfig->m_sScPort[i].nParity;
		m_StackerThreadInfo[i].m_nStopBits = m_pConfig->m_sScPort[i].nStopBits;
		m_StackerThreadInfo[i].m_nBitsPerChar = m_pConfig->m_sScPort[i].nBitsPerChar;

		m_StackerThreadInfo[i].m_pDoc = this;
		m_StackerThreadInfo[i].m_pStackerInfo = m_pStackerInfo[i];

		m_StackerThreadInfo[i].m_hwndNotify = pView->m_hWnd;

		if(m_pConfig->m_sScPort[i].bConnect)
			ConnectScServer(i);
	}


	for ( i = 0; i < CV_PLC_CNT; i++ )
	{
		m_hEventSendConveyor[i] = CreateEvent(NULL, FALSE, FALSE, NULL); // auto reset, initially reset
		m_hEventKillConveyorThread[i] = CreateEvent(NULL, FALSE, FALSE, NULL); // auto reset, initially reset
		m_hEventConveyorThreadKilled[i] = CreateEvent(NULL, FALSE, FALSE, NULL); // auto reset, initially reset

		m_ConveyorThreadInfo[i].m_hEventSendConveyor = m_hEventSendConveyor[i];
		m_ConveyorThreadInfo[i].m_hEventKillConveyorThread = m_hEventKillConveyorThread[i];
		m_ConveyorThreadInfo[i].m_hEventConveyorThreadKilled = m_hEventConveyorThreadKilled[i];

		m_ConveyorThreadInfo[i].m_nNum = i;
		m_ConveyorThreadInfo[i].m_dwReadTimeOut = m_pConfig->m_sCvPort[i].dwReadTimeOut;


		m_ConveyorThreadInfo[i].m_pDoc = this;
		m_ConveyorThreadInfo[i].m_pConveyorTrackInfo = m_ConveyorTrackInfo;

		m_ConveyorThreadInfo[i].m_hwndNotify = pView->m_hWnd;

		//if (m_pConfig->m_bCvConnect[i])
		if (m_pConfig->m_sCvPort[i].bConnect)
			ConnectCvServer(i);

//		m_pConveyorThread[i] = AfxBeginThread(ConveyorThreadProc, &m_ConveyorThreadInfo[i]);
	}

	for ( i = 0; i < RGV_CNT; i++ )
	{
		CString strFileName;
		strFileName.Format("..\\Temp\\RtvInfo%d.Ecs", i + 1);
		m_pRgvInfo[i] = new CRgvInfo(this, strFileName, i);
		m_pRgvInfo[i]->Restore();
		m_pRgvInfo[i]->m_bModified = TRUE;

		m_hEventSendRgv[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		m_hEventKillRgvThread[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		m_hEventRgvThreadKilled[i] = CreateEvent(NULL, FALSE, FALSE, NULL);

		m_RgvThreadInfo[i].m_hEventSendRgv = m_hEventSendRgv[i];
		m_RgvThreadInfo[i].m_hEventKillRgvThread = m_hEventKillRgvThread[i];
		m_RgvThreadInfo[i].m_hEventRgvThreadKilled = m_hEventRgvThreadKilled[i];

		m_RgvThreadInfo[i].m_nNum = i;
//		strcpy(m_RgvThreadInfo[i].m_szComName, m_pConfig->m_sRgvPort[i].szComName);
		strcpy(m_RgvThreadInfo[i].Port.szComName, m_pConfig->m_sRgvPort[i].szComName);
		m_RgvThreadInfo[i].Port.nBaudRate = m_pConfig->m_sRgvPort[i].nBaudRate;
		m_RgvThreadInfo[i].Port.nParity   = m_pConfig->m_sRgvPort[i].nParity;
		m_RgvThreadInfo[i].Port.nStopBits = m_pConfig->m_sRgvPort[i].nStopBits;
		m_RgvThreadInfo[i].Port.nBitsPerChar = m_pConfig->m_sRgvPort[i].nBitsPerChar;
		m_RgvThreadInfo[i].Port.dwReadTimeOut = m_pConfig->m_sRgvPort[i].dwReadTimeOut;

		m_RgvThreadInfo[i].m_pDoc = this;
		m_RgvThreadInfo[i].m_pRgvInfo = m_pRgvInfo[i];
		m_RgvThreadInfo[i].m_pConveyorTrackInfo = m_ConveyorTrackInfo;

		m_RgvThreadInfo[i].m_hwndNotify = m_hwndView;

		m_pRgvThread[i] = AfxBeginThread(RgvThreadProc, &m_RgvThreadInfo[i]);

	}

#endif // THREAD_RUN

	return TRUE;
}

BOOL CEcsDoc::ConnectCvSocket(int nCvNum, LPCTSTR lpszAddress, UINT nPort)
{
	CString strLog;

	if (m_pConveyorSocket[nCvNum] != NULL)
	{
		strLog.Format("이미 CV#%d서버와 접속 되어 있슴.. !", nCvNum+1);
		m_pLog->Error(LOG_POS_CV, LOG_SYSTEM, strLog);
		return TRUE;
	}

	m_pConveyorSocket[nCvNum] = new CCvSocket(this, nCvNum);

	if (!m_pConveyorSocket[nCvNum]->Create())
	{
		m_pConveyorSocket[nCvNum]->ShutDown();
		delete m_pConveyorSocket[nCvNum];
		m_pConveyorSocket[nCvNum] = NULL;

		strLog.Format("%s 소켓 생성 실패.. 에러[%s]!",  CLib::GetSystemErrMsg());
		m_pLog->Error(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}

	m_pConveyorSocket[nCvNum]->Connect(lpszAddress, nPort);
	return TRUE;

/*	CCvSocket *pCvSocket = new CCvSocket(this, nCvNum);

	if (!pCvSocket->Create())
	{
		pCvSocket->ShutDown();
		delete pCvSocket;
		m_pConveyorSocket[nCvNum] = NULL;

		strLog.Format("CV#%d 소켓 생성 실패.. 에러[%s]!", nCvNum+1, CLib::GetSystemErrMsg());
		m_pLog->Error(LOG_POS_CV, LOG_SYSTEM, strLog);
		return FALSE;
	}

	pCvSocket->Connect(lpszAddress, nPort);

	return TRUE;
*/
}

void CEcsDoc::ConnectCvServer(int nCvNum)
{
	ConnectCvSocket(nCvNum, m_pConfig->m_sCvPort[nCvNum].strAddress, m_pConfig->m_sCvPort[nCvNum].nPort);
//	ConnectCvSocket(nCvNum, m_pConfig->m_strCvAddr[nCvNum], m_pConfig->m_nCvPort[nCvNum]);
}


void CEcsDoc::ConnectScServer(int nScNum)
{
	ConnectScSocket(nScNum, m_pConfig->m_sScPort[nScNum].strAddress, m_pConfig->m_sScPort[nScNum].nPort, m_pConfig->m_sScPort[nScNum].strDevice);
}

BOOL CEcsDoc::ConnectScSocket(int nScNum, LPCTSTR lpszAddress, UINT nPort, CString strDevice)
{
	CString strLog;

	if (m_pStackerSocket[nScNum] != NULL)
		return TRUE;

	m_pStackerSocket[nScNum] = new CScSocket(this, nScNum, strDevice);

	if (!m_pStackerSocket[nScNum]->Create())
	{
		m_pStackerSocket[nScNum]->ShutDown();
		delete m_pStackerSocket[nScNum];
		m_pStackerSocket[nScNum] = NULL;

		strLog.Format("%s 소켓 생성 실패.. 에러[%s]!", strDevice, CLib::GetSystemErrMsg());
		m_pLog->Error(LOG_POS_SC, LOG_SYSTEM, strLog);
		return FALSE;
	}

	m_pStackerSocket[nScNum]->Connect(lpszAddress, nPort);
	return TRUE;
}

void CEcsDoc::OnLogging() 
{
	CLogDlg LogDlg;

	LogDlg.m_pLog = m_pLog;
	LogDlg.DoModal();
}

void CEcsDoc::OnManual() 
{
#ifdef OPT_PASSWORD_USE
	CPasswordDlg PasswordDlg;

	PasswordDlg.m_pDoc = this;
	if (PasswordDlg.DoModal() != IDOK) return;
	if ( PasswordDlg.m_strPassword != m_pConfig->m_strPassword )
	{
		AfxMessageBox("PASSWORD 확인 바람..");
		return;
	}
#endif
	CManualDlg ManualDlg;

	ManualDlg.m_pDoc = this;
	ManualDlg.DoModal();
}

void CEcsDoc::OnJob() 
{
	CJobDlg JobDlg;

	JobDlg.m_pDoc = this;
	JobDlg.DoModal();
}

void CEcsDoc::OnMoveJob() 
{
	CMoveJobDlg MoveJobDlg;

	MoveJobDlg.m_pDoc = this;
	MoveJobDlg.DoModal();
}

void CEcsDoc::OnConfig() 
{
	CConfigDlg ConfigDlg;

	ConfigDlg.m_pConfig = m_pConfig;
	ConfigDlg.DoModal();
}

void CEcsDoc::OnLogo()
{
	CLogoDlg LogoDlg;
	LogoDlg.m_bInitial = FALSE;
	LogoDlg.DoModal();
}

void CEcsDoc::OnStatisticsAvail() 
{
	CStatisticAvailDlg StatisticAvailDlg;

	StatisticAvailDlg.m_pDoc = this;
	StatisticAvailDlg.m_strDir = m_pStatistic->m_strDir;
	StatisticAvailDlg.m_strFileName = m_pStatistic->m_strStcFileName;

	StatisticAvailDlg.DoModal();
}

void CEcsDoc::OnStatisticsThroughput() 
{
	CStatisticThroughputDlg StatisticThroughputDlg;

	StatisticThroughputDlg.m_pDoc = this;
	StatisticThroughputDlg.m_strDir = m_pStatistic->m_strDir;
	StatisticThroughputDlg.m_strFileName = m_pStatistic->m_strStcFileName;
	StatisticThroughputDlg.DoModal();
}

BOOL CEcsDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	if (AfxMessageBox("종료하겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return FALSE;
	
	Backup();
	MoveBackup();

	return CDocument::CanCloseFrame(pFrame);
}

BOOL CEcsDoc::Restore()
{
	return m_pJob->Restore();
}

BOOL CEcsDoc::Backup()
{
	return m_pJob->Backup();
}

BOOL CEcsDoc::MoveRestore()
{
	return m_pMoveJob->Restore();
}

BOOL CEcsDoc::MoveBackup()
{
	return m_pMoveJob->Backup();
}

void CEcsDoc::DisplayMessage()
{
	if (m_MsgList.GetCount() <= 0)
		return;

	CMainFrame* pWnd = (CMainFrame *)AfxGetMainWnd();

	POSITION pos = m_MsgList.GetHeadPosition();
	CDisplayMsg* pMsg = (CDisplayMsg *)m_MsgList.GetAt(pos);
	pWnd->DisplayMessage(pMsg->m_strMsg);

	if (m_pConfig->m_bBeep && !pMsg->m_bNormalStatus) Beep(800, 300);

	m_MsgList.RemoveHead();
	delete pMsg;
}

void CEcsDoc::DisplayMessage(CString strMsg, BOOL bNormalStatus)
{
	if (m_MsgList.GetCount() > 5)
		return;

	CDisplayMsg* pMsg = new CDisplayMsg(strMsg, bNormalStatus);
	m_MsgList.AddTail(pMsg);
}

CDisplayMsg::CDisplayMsg(CString strMsg, BOOL bNormalStatus)
{
	m_strMsg = strMsg;
	m_bNormalStatus = bNormalStatus;
}

void CEcsDoc::EventLog(int nLuggNum, CString strContent)
{
	m_pLog->Event(LOG_POS_SYSTEM, nLuggNum, strContent);
}

void CEcsDoc::CvAction(int nPlcNum)
{
	m_nConveyorEventCount[nPlcNum]++; 
	SetEvent(m_hEventSendConveyor[nPlcNum]);
}

void CEcsDoc::ScAction(int nScNum)
{
	m_nStackerEventCount[nScNum]++; 
	SetEvent(m_hEventSendStacker);
}

//void CEcsDoc::UpdateHostCommCl(char Status)
//{
//	CMainFrame* pWnd = (CMainFrame *)AfxGetMainWnd();
//	pWnd->UpdateCommHostCl(Status);
//}

//void CEcsDoc::UpdateHostCommSv(char Status)
//{
//	CMainFrame* pWnd = (CMainFrame *)AfxGetMainWnd();
//	pWnd->UpdateCommHostSv(Status);
//}
/*
void CEcsDoc::OnSystemResetResultCount() 
{
	
#ifdef OPT_PASSWORD_USE
	CPasswordDlg PasswordDlg;
	PasswordDlg.m_pDoc = this;
	if (PasswordDlg.DoModal() != IDOK) return;
	if ( PasswordDlg.m_strPassword != m_pConfig->m_strPassword )
	{
		AfxMessageBox("PASSWORD 확인 바람..");
		return;
	}
#endif
	if (AfxMessageBox("작업실적 누계를 초기화하겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return;

	m_pJob->ResetResultCount();	
}
*/

/*
void CEcsDoc::OnSystemRemoveAllJob() 
{
//	AfxMessageBox("현시스템에서는 사용할 수 없는 기능입니다!!!");
//	return;

#ifdef OPT_PASSWORD_USE
	CPasswordDlg PasswordDlg;
	PasswordDlg.m_pDoc = this;
	if (PasswordDlg.DoModal() != IDOK) return;
	if ( PasswordDlg.m_strPassword != m_pConfig->m_strPassword )
	{
		AfxMessageBox("PASSWORD 확인 바람..");
		return;
	}
#endif
	if (AfxMessageBox("현재 진행중인 모든 작업을 삭제(취소)하겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return;

	m_pJob->RemoveAllJob();
}
*/


void CEcsDoc::OnStatisticsErrcode() 
{
	CStatisticErrCodeDlg StatisticErrCodeDlg;

	StatisticErrCodeDlg.m_pDoc = this;
	StatisticErrCodeDlg.DoModal();	
}
/*
void CEcsDoc::OnScErrLog() 
{
	CScErrDlg ScErrDlg;

	//StatisticErrCodeDlg.m_pDoc = this;
	ScErrDlg.DoModal();	
}
*/
/*
void CEcsDoc::OnSystemResetStatisticInfo() 
{
#ifdef OPT_PASSWORD_USE
	CPasswordDlg PasswordDlg;
	PasswordDlg.m_pDoc = this;
	if (PasswordDlg.DoModal() != IDOK) return;
	if ( PasswordDlg.m_strPassword != m_pConfig->m_strPassword )
	{
		AfxMessageBox("PASSWORD 확인 바람..");
		return;
	}
#endif
	if (AfxMessageBox("통계자료(가동률,물량처리,에러코드)를 초기화 하겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return;

	m_pStatistic->ResetStatisticInfo();
}
*/
/*
void CEcsDoc::OnColorView() 
{
	CColorViewDlg ColorViewDlg;
	ColorViewDlg.DoModal();	
}
*/

/*
void CEcsDoc::OnScInhibit() 
{
	CScInhibitDlg ScInhibitDlg;

	ScInhibitDlg.m_pDoc = this;
	ScInhibitDlg.DoModal();
	
}
*/

void CEcsDoc::OnCommHostClient() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "IMS Server/ECS Client", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommHostServer() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "IMS Client/ECS Server", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommCv1() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "Conveyor PLC #1", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommCv2() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "Conveyor PLC #2", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommCv3() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "Conveyor PLC #3", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommCv4() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "Conveyor PLC #4", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommCv5() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "Conveyor PLC #5", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommCv6() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "Conveyor PLC #6", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommCv7() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "Conveyor PLC #7", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommCv8() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "Conveyor PLC #8", MB_ICONEXCLAMATION | MB_OK ) ;
}


void CEcsDoc::OnCommCv9() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "Conveyor PLC #9", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommSc1() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "Stacker #1", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommSc2() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "Stacker #2", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommSc3() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "Stacker #3", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommSc4() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "Stacker #4", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommSc5() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "Stacker #5", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommSc6() 
{
	MessageBox(GetFocus(), "Communication Status.\nPlease look at the tool bar.", "Stacker #6", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommRgv1() 
{
	MessageBox(GetFocus(), "RTV#1 통신 상태.", "RTV#1 ", MB_ICONEXCLAMATION | MB_OK ) ;
}

void CEcsDoc::OnCommRgv2() 
{
	MessageBox(GetFocus(), "RTV#2 통신 상태.", "RTV#2 ", MB_ICONEXCLAMATION | MB_OK ) ;
}
void CEcsDoc::OnCommNewEcs() 
{
	MessageBox(GetFocus(), "신규 ECS 통신 상태.", "신규 ECS ", MB_ICONEXCLAMATION | MB_OK ) ;
}