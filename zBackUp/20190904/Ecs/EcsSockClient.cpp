// EcsSockClient.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"

#include "EcsDoc.h"
#include "Log.h"
#include "MainFrm.h"
#include "EcsView.h"
#include "lib.h"

//#include "WvcSockDef.h"
#include "EcsSockClient.h"


#define SC_INFO			m_pDoc->m_pStackerInfo
#define RGV_INFO		m_pDoc->m_pRgvInfo
#define TRACK_INFO		m_pDoc->m_ConveyorTrackInfo
#define OPBOX_INFO		m_pDoc->m_OpBoxInfo
#define SC_INFO_CNT		13
#define RGV_INFO_CNT	10
#define OPBOX_INFO_CNT	2

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
IMPLEMENT_DYNAMIC(CEcsSockClient, CAsyncSocket)

/////////////////////////////////////////////////////////////////////////////
// CSockClient

CEcsSockClient::CEcsSockClient(CEcsDoc* pDoc)
{
	m_pDoc = pDoc;
	m_nLastIpNo = 0;
	m_cWareHouse = 0x20;
	m_strLocation = _T("");
	m_strSecondLoc = _T("");;
	m_nStartPos = 0;
	m_nDestPos = 0;

	m_hwndCvDlg = NULL;
	m_hwndScDlg = NULL;
	m_hwndJobDlg = NULL;
	m_hwndScDlg = NULL;

	m_bConnected = FALSE;
}

CEcsSockClient::~CEcsSockClient()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CEcsSockClient, CAsyncSocket)
	//{{AFX_MSG_MAP(CEcsSockClient)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CEcsSockClient member functions

void CEcsSockClient::OnReceive(int nErrorCode) 
{
	if (nErrorCode) {
		AfxMessageBox("The Windows Sockets implementation detected that the network subsystem failed.");
	}

	int nMsgLen = 0;
	char RxBuff[1024];

	memset(RxBuff, 0x00, sizeof(RxBuff));

	if (Receive(RxBuff, MSG_LENGTH_HEADER) != MSG_LENGTH_HEADER)
	{
		m_pDoc->m_pLog->Error(LOG_POS_ECS, LOG_SYSTEM, "Error.. Msg header lenth is too short.");
		UpdateCommCl(NOTIFY_ERROR);
		Clear();
		return;
	}

	RxBuff[MSG_LENGTH_HEADER - 1] = 0;
	nMsgLen = atoi( &RxBuff[10] );
	if(nMsgLen <= 0)
	{
		m_pDoc->m_pLog->Error(LOG_POS_ECS, LOG_SYSTEM, "Error.. Invalid MsgLen.");
		UpdateCommCl(NOTIFY_ERROR);
		Clear();
		return;
	}

	if (Receive(RxBuff + MSG_LENGTH_HEADER, nMsgLen) != nMsgLen)
	{
		m_pDoc->m_pLog->Error(LOG_POS_ECS, LOG_SYSTEM, "Error.. Msg lenth is not correct.");
		UpdateCommCl(NOTIFY_ERROR);
		Clear();
		return;
	}

	if (RxBuff[MSG_LENGTH_HEADER] != STX)
	{
		m_pDoc->m_pLog->Error(LOG_POS_ECS, LOG_SYSTEM, "Error.. There is no STX...");
		UpdateCommCl(NOTIFY_ERROR);
		Clear();
		return;
	}

	if (RxBuff[MSG_LENGTH_HEADER + nMsgLen -1] != ETX)
	{
		m_pDoc->m_pLog->Error(LOG_POS_ECS, LOG_SYSTEM, "Error.. There is no ETX...");
		UpdateCommCl(NOTIFY_ERROR);
		Clear();
		return;
	}

	UpdateCommCl(NOTIFY_RECEIVE);

	ParsingFrame(RxBuff);

	CAsyncSocket::OnReceive(nErrorCode);
}

void CEcsSockClient::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
//	::PostMessage(m_pDoc->m_hwndView, WM_USER_HOST_NOTIFY, ID_COMM_SRV, COMM_STA_STOP);
	UpdateCommCl(NOTIFY_ERROR);

	m_pDoc->m_pLog->Error(LOG_POS_ECS, LOG_SYSTEM, "Network or Ecs Server is down !");
	m_pDoc->m_pEcsCl = NULL;
	m_bConnected = FALSE;
	ShutDown();
	delete this;

	CAsyncSocket::OnClose(nErrorCode);
}

void CEcsSockClient::OnConnect(int nErrorCode) 
{
	CString strLog;
	CString strLocalIP, strPeerIP;
	UINT nPort;

	if (nErrorCode)
	{
		if (m_pDoc->m_nAlive != 1)
		{
			m_pDoc->m_pEcsCl = NULL;
			ShutDown();
			delete this;
		}
//		::PostMessage(m_pDoc->m_hwndView, WM_USER_LGV_NOTIFY, ID_COMM_LGV, COMM_STA_STOP);
		UpdateCommCl(NOTIFY_ERROR);
		m_bConnected = FALSE;

		strLog.Format("신규 (Pallet 창고) ECS(Server)에 접속 실패.. [%s]", CLib::GetSystemErrMsg(nErrorCode));
//		m_pDoc->m_pLog->Error(LOG_POS_ECS, LOG_SYSTEM, strLog);

		// 2001. 10. 03 
		// PGM 종료시 CEcsView::OnTimer - ConnectEcsServer로 인해서 CEcsDoc 객체 소멸후
		// OnConnect 호출되면 에러
		CMainFrame *pFrame = (CMainFrame *) AfxGetMainWnd();
		if(pFrame != NULL)
		{
			CEcsDoc * pDoc = (CEcsDoc *) pFrame->GetActiveDocument();
			if(pDoc != NULL)
			{
				if(pDoc->m_pLog != NULL)
					pDoc->m_pLog->Error(LOG_POS_ECS, LOG_SYSTEM, strLog);

				pDoc->m_pEcsCl = NULL;
				ShutDown();
				delete this;
			}
		}
	}
	else
	{
		m_pDoc->m_pEcsCl = this;
		if (GetSockName(strLocalIP, nPort))
			m_nLastIpNo = atoi(strLocalIP.Right(3));

		GetPeerName(strPeerIP, nPort);
//		::PostMessage(m_pDoc->m_hwndView, WM_USER_LGV_NOTIFY, ID_COMM_LGV, COMM_STA_RECEIVE);
		UpdateCommCl(NOTIFY_SEND);
		m_bConnected = TRUE;
		strLog.Format("신규 (Pallet 창고) ECS(Server)에 접속 성공.. (EcsCl)");
		m_pDoc->m_pLog->Event(LOG_POS_ECS, LOG_SYSTEM, strLog);
	}
	
	CAsyncSocket::OnConnect(nErrorCode);
}

void CEcsSockClient::Clear()
{
	char RxBuff[1024];

	Receive(RxBuff, 1024); 	
}

void CEcsSockClient::EcsClientSendData()
{

	char TxBuff[256];
	int nSeqNo = 0;
	memset(TxBuff, 0x0, sizeof(TxBuff));

	sprintf(TxBuff, "%c%20s%08d%50s%c", 
		STX, m_pDoc->m_strCodeNum, m_pDoc->m_nPeriodNum, m_pDoc->m_strProdName, ETX);

	CString strLog;
	if(SendMsg(TxBuff, 80) == FALSE)
	{
		strLog.Format("EcsClientSendData 송신 실패.. 에러=[%s]", CLib::GetSystemErrMsg());
		LOG_ERROR(LOG_POS_HOST, 0, strLog);
		return;
	}

//	m_pDoc->m_strCodeNum = "";
//	m_pDoc->m_strProdName = "";
//	m_pDoc->m_nPeriodNum = 0;

	strLog.Format("EcsClientSendData 송신.. 성공..");
	LOG_JOB(LOG_POS_HOST, 0, strLog);

}


BOOL CEcsSockClient::SendMsg(char* pTxBuff, int nSndMsgLen)
{
	UpdateCommCl(NOTIFY_SEND);
	return (Send(pTxBuff, nSndMsgLen) == nSndMsgLen) ? TRUE : FALSE;
}

void CEcsSockClient::ParsingFrame(char *pFrame)
{

	CString strLog;
	CString strFrame = pFrame;
	uchar ucMsgType = pFrame[1];
	uchar ucAckNak  = pFrame[2];
	int nReason = MSG_NO_ERROR;


	return;
}
void CEcsSockClient::UpdateCommCl(char Status)
{

	::PostMessage(m_pDoc->m_hwndView, WM_USER_ECS_NOTIFY, 0, Status);
//	m_pDoc->UpdateHostComm(Status);
	return;

	CMainFrame* pWnd = (CMainFrame *)AfxGetMainWnd();
	pWnd->UpdateCommEcsCl(Status);
}



