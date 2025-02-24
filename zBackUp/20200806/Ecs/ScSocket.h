
#pragma once

class CScSocket : public CAsyncSocket
{
public:
	CScSocket(CEcsDoc *pDoc, int nNum, CString strDevice);
	virtual ~CScSocket();

public:
	CEcsDoc  *m_pDoc;
	int      m_nScNum;
	CString  m_strDevice;
	BOOL	 m_bConnected;

public:
	BOOL     m_bReceiving;
	HANDLE   m_hEventRecv;


public:
	void UpdateCommSc(char Status);


// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScSocket)
	public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CScSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

