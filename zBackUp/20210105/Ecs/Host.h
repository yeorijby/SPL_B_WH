// Host.h : Defines the class behaviors for the application.

#ifndef _ECSSOCK
#define _ECSSOCK

#include "EcsDef.h"
#include <EcsEnv.h>

class CEcsDoc;

class CListenSk : public CAsyncSocket
{
	DECLARE_DYNAMIC(CListenSk);

// Attributes
public:
	CEcsDoc* m_pDoc;
	BOOL	m_bConnected;

// Operations
public:
	CListenSk();
	CListenSk(CEcsDoc * pDoc);
	virtual ~CListenSk();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSk)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSk)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:

};

class CHostSv : public CAsyncSocket
{
	DECLARE_DYNAMIC(CHostSv);

// Construction
public:
	CHostSv(CEcsDoc* pDoc);

// Attributes
public:
	CEcsDoc* m_pDoc;

// Operations
public:
	void UpdateCommSv(char Status);
	void Clear();
	void Parsing(char *pFrame);
	void Answer(uchar ucMsgType, int nLuggNum, int nReasonCode);
// Implementation
protected:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

class CHostCl : public CAsyncSocket
{
	DECLARE_DYNAMIC(CHostCl);

// Construction
public:
	CHostCl(CEcsDoc* pDoc);

// Attributes
public:
	CEcsDoc* m_pDoc;

// Operations
public:
	void UpdateCommCl(char Status);
	void Cancel(int nLuggNum);
	void Complete(int nLuggNum, int nScJobType = SC_JOB_TYPE_ANY);
	void Arrived(int nLuggNum);
	void Arrived2(int nLuggNum, int nLuggNum2);
	void Clear();
	void Complete();
	void Error(int nDevKind, int nDevNo, int nErrKind=0, int nErrCode=0, int nLuggNum=0, CString strLocation="");
	void Status(int nRegularCycle=0);
	void Throughput();
	void OfflineJob();
	void PutOffTrans();
	void BcrJob();

//	void SendMsg(char *pTxBuff, int nSndMsgLen);
	BOOL SendMsg(char* pTxBuff, int nSndMsgLen);

	void Parsing(char *pFrame);
	CString GetStringReason(int nReasonCode);
//	void ReadData();

// Implementation
protected:
	virtual void OnConnect(int nErrorCode);
	//^^suri
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


#endif // _ECSSOCK
