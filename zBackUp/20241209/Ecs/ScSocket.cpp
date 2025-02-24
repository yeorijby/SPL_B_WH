
// ScSocket.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"

#include "EcsDoc.h"
#include "MainFrm.h"

#include "ScSocket.h"
#include "Lib.h"

//#include "ScThreadProc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////
// CScSocket

CScSocket::CScSocket(CEcsDoc *pDoc, int nNum, CString strDevice)
{
	m_pDoc       = pDoc;
	m_nScNum     = nNum;
	m_strDevice  = strDevice;
	m_bConnected = FALSE;

	m_bReceiving = FALSE;
	m_hEventRecv = CreateEvent(NULL, FALSE, FALSE, NULL); // manual reset, initially nonsignaled
}

CScSocket::~CScSocket()
{
	::CloseHandle(m_hEventRecv);
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CScSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CScSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

//////////////////////////////////////////
// CScSocket member functions

void CScSocket::OnConnect(int nErrorCode) 
{

	CString strLog;
	if (nErrorCode)
	{
		UpdateCommSc(NOTIFY_ERROR);

		strLog.Format("%s 서버에 접속 실패.. [%s]", m_strDevice, CLib::GetSystemErrMsg(nErrorCode));

		CMainFrame *pFrame  =  (CMainFrame*)AfxGetMainWnd();
		if ( pFrame  !=  NULL )
		{
			CEcsDoc *pDoc = (CEcsDoc*)pFrame->GetActiveDocument();
			if ( pDoc != NULL )
			{
				LOG_ERROR(LOG_POS_SC, LOG_SYSTEM, strLog);
				pDoc->m_pStackerSocket[m_nScNum] = NULL;
				ShutDown();
				delete this;
			}
		}
	}
	else
	{
		if (!m_bConnected)
		{
			UpdateCommSc(NOTIFY_SEND);

			strLog.Format("OnConnect.. %s 서버에 접속 성공..", m_strDevice);
			LOG_EVENT(LOG_POS_SC, LOG_SYSTEM, strLog);

			m_bConnected = TRUE;
			m_pDoc->m_StackerThreadInfo[m_nScNum].m_pSocket = this;

			//if(m_pDoc->m_pConfig->m_sScPort[m_nScNum].bChange)
				m_pDoc->m_pStackerThread[m_nScNum] = AfxBeginThread(ScQThreadProc, &(m_pDoc->m_StackerThreadInfo[m_nScNum]));
			//else
			//	m_pDoc->m_pStackerThread[m_nScNum] = AfxBeginThread(ScThreadProc, &(m_pDoc->m_StackerThreadInfo[m_nScNum]));
		}
		else
		{
			UpdateCommSc(NOTIFY_SEND);

			strLog.Format("OnConnect.. %s 서버에 재접속 요구 (SKIP) ..", m_strDevice);
			LOG_EVENT(LOG_POS_SC, LOG_SYSTEM, strLog);
		}
	}

	CAsyncSocket::OnConnect(nErrorCode);
}

void CScSocket::OnClose(int nErrorCode) 
{
	UpdateCommSc(NOTIFY_ERROR);

	CString strLog;
	strLog.Format("%s 서버와 연결 해제..! [%s]", m_strDevice, CLib::GetSystemErrMsg(nErrorCode));
	LOG_EVENT(LOG_POS_SC, LOG_SYSTEM, strLog);

	//ShutDown();

	SetEvent(m_pDoc->m_hEventKillStackerThread[m_nScNum]);
	WaitForSingleObject(m_pDoc->m_pStackerThread[m_nScNum]->m_hThread, INFINITE);

	m_bConnected = FALSE;
	m_pDoc->m_pStackerSocket[m_nScNum] = NULL;
	ShutDown();

	CAsyncSocket::OnClose(nErrorCode);
	delete this;
}

void CScSocket::UpdateCommSc(char Status)
{
	::PostMessage(m_pDoc->m_hwndView, WM_USER_SC_NOTIFY, m_nScNum, Status);
}

void CScSocket::OnReceive(int nErrorCode) 
{
	CAsyncSocket::OnReceive(nErrorCode);

	if (nErrorCode) 
		AfxMessageBox(CLib::GetSystemErrMsg());

	DWORD dwLen = 0;
	IOCtl( FIONREAD, &dwLen );

	if(!m_bReceiving)
	{
		CString strLog;

		BYTE RxBuff[1048];
		memset(RxBuff, 0x00, sizeof(RxBuff));

		Receive(RxBuff, dwLen);

		strLog.Format("OnReceive.. %s 수신 대기 시간 초과후 데이터 수신 데이터", m_strDevice);
		LOG_ERROR(LOG_POS_SC, LOG_SYSTEM, strLog);
		return;
	}

	if(dwLen)	
		SetEvent(m_hEventRecv);
}
