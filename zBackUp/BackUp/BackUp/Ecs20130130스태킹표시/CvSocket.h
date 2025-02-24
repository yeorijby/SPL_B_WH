
#ifndef __CVSOCK_H__
#define __CVSOCK_H__

class CCvSocket : public CAsyncSocket
{
public:
	CCvSocket(CEcsDoc *pDoc, int nCvNum);
	virtual ~CCvSocket();

public:
	int m_nCvNum;
	CEcsDoc *m_pDoc;
	BOOL	 m_bConnected;

	HANDLE m_hEventRecv;

	BOOL m_bReceiving;

public:
	void UpdateCommCv(char Status);


// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCvSocket)
	public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CCvSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

#endif
