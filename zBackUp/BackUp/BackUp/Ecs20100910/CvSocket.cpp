// CvSocket.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"

#include "EcsDoc.h"
#include "MainFrm.h"

#include "CvSocket.h"
#include "Lib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////
// CCvSocket

CCvSocket::CCvSocket(CEcsDoc *pDoc, int nCvNum)
{
	m_pDoc = pDoc;
	m_nCvNum = nCvNum;
	m_hEventRecv = CreateEvent(NULL, FALSE, FALSE, NULL); // manual reset, initially nonsignaled

	m_bConnected = FALSE;
	m_bReceiving = FALSE;

}

CCvSocket::~CCvSocket()
{
	::CloseHandle(m_hEventRecv);
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CCvSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CCvSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

//////////////////////////////////////////
// CCvSocket member functions

void CCvSocket::OnConnect(int nErrorCode) 
{
	CString strLog;
	if (nErrorCode)
	{
		UpdateCommCv(NOTIFY_ERROR);

		strLog.Format("CV#%d 서버에 접속 실패.. [%s]", m_nCvNum+1, CLib::GetSystemErrMsg(nErrorCode));

		CMainFrame *pFrame  =  (CMainFrame*)AfxGetMainWnd();
		if ( pFrame  !=  NULL )
		{
			CEcsDoc *pDoc = (CEcsDoc*)pFrame->GetActiveDocument();
			if ( pDoc != NULL )
			{
				LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
				pDoc->m_pConveyorSocket[m_nCvNum] = NULL;
				ShutDown();
				delete this;
			}
		}
	}
	else
	{
		m_pDoc->m_pConveyorSocket[m_nCvNum] = this;
		UpdateCommCv(NOTIFY_SEND);

		strLog.Format("OnConnect.. CV#%d 서버에 접속 성공..", m_nCvNum+1);
		LOG_EVENT(LOG_POS_CV, LOG_SYSTEM, strLog);

		m_bConnected = TRUE;

		m_pDoc->m_ConveyorThreadInfo[m_nCvNum].m_pSocket = this;
		m_pDoc->m_pConveyorThread[m_nCvNum] = AfxBeginThread(ConveyorThreadProc, &(m_pDoc->m_ConveyorThreadInfo[m_nCvNum]));
	}

	CAsyncSocket::OnConnect(nErrorCode);
}

void CCvSocket::OnClose(int nErrorCode) 
{
	UpdateCommCv(NOTIFY_ERROR);

	CString strLog;
	strLog.Format("CV#%d CV서버와 연결 해제..! [%s]", m_nCvNum+1, CLib::GetSystemErrMsg(nErrorCode));
	LOG_EVENT(LOG_POS_CV, LOG_SYSTEM, strLog);

	ShutDown();

	SetEvent(m_pDoc->m_hEventKillConveyorThread[m_nCvNum]);
	WaitForSingleObject(m_pDoc->m_pConveyorThread[m_nCvNum]->m_hThread, INFINITE);

	m_bConnected = FALSE;

	m_pDoc->m_pConveyorSocket[m_nCvNum] = NULL;
	
	CAsyncSocket::OnClose(nErrorCode);
	delete this;
}

void CCvSocket::UpdateCommCv(char Status)
{
	::PostMessage(m_pDoc->m_hwndView, WM_USER_CV_NOTIFY, m_nCvNum, Status);
}

void CCvSocket::OnReceive(int nErrorCode) 
{
	CAsyncSocket::OnReceive(nErrorCode);

	if (nErrorCode) 
		AfxMessageBox(CLib::GetSystemErrMsg());

	DWORD dwLen = 0;
	IOCtl( FIONREAD, &dwLen );

	if(!m_bReceiving)
	{
		CString strLog;

		BYTE RxBuff[4096];
		memset(RxBuff, 0x00, sizeof(RxBuff));

		Receive(RxBuff, dwLen);

		//strLog.Format("OnReceive.. CV#%d 수신 대기 시간 초과후 데이터 수신 데이터[%s]", m_nCvNum+1, RxBuff);
		strLog.Format("OnReceive.. CV#%d 수신 대기 시간 초과후 데이터 수신 데이터", m_nCvNum+1);
		LOG_ERROR(LOG_POS_CV, LOG_SYSTEM, strLog);
		return;
	}

	if(dwLen)	
		SetEvent(m_hEventRecv);
}
