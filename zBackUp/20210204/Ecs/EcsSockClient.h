#if !defined(AFX_SOCKCLIENT_H__E90C1B01_861B_11D3_B48B_0800092D38F6__INCLUDED_)
#define AFX_SOCKCLIENT_H__E90C1B01_861B_11D3_B48B_0800092D38F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EcsSockClient.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEcsSockClient command target
class CEcsDoc;
class CEcsSockClient : public CAsyncSocket
{
	DECLARE_DYNAMIC(CEcsSockClient);
// Attributes
public:
	HWND m_hwndCvDlg;
	HWND m_hwndScDlg;
	HWND m_hwndJobDlg;
	HWND m_hwndRgvDlg;

	//^^ sc dlg info
	CString m_strLocation;
	CString m_strSecondLoc;
	char m_cWareHouse;
	int m_nStartPos;
	int m_nDestPos;
	int m_nStatus;
	int m_nJobType;

	BOOL m_bConnected;

// Operations
public:
	CEcsSockClient(CEcsDoc* pDoc);
	virtual ~CEcsSockClient();
//	void RequestCvTrackInfo(int nTrackNum);
//	void RequestScDlgInfo(int nScId);
//	void RequestRgvDlgInfo(int nRgvId);
//	void RequestWriteTrack(int nPlcNum, SConveyorMsg& sCvMsg);
//	void RequestScCommand(int nScNum, int nCommand);
//	void RequestRgvCommand(int nRgvNum, int nCommand);
//	void RequestAllJob();
//	void RequestRemoveAllJob();
//	void RequestInitStatistics();
//	void RequestJobCommand(int nCommand, int nTrackId, CJobItem* pJobItem);
	void UpdateCommCl(char Status);
	BOOL SendMsg(char* pTxBuff, int nSndMsgLen);
	void EcsClientSendData();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSockClient)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSockClient)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:

private:
	void Clear();
	void ParsingFrame(char *pFrame);
//	void ParsingMcStatus(char *pFrame);
	void GetStringReason(int nReason);


	CEcsDoc* m_pDoc;
	int m_nLastIpNo;


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKCLIENT_H__E90C1B01_861B_11D3_B48B_0800092D38F6__INCLUDED_)
