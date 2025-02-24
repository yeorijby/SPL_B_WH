#if !defined(AFX_BUFFERCONTROLLER_H__9524199C_56B5_4541_9731_334C6E48223B__INCLUDED_)
#define AFX_BUFFERCONTROLLER_H__9524199C_56B5_4541_9731_334C6E48223B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BufferController.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBufferController dialog
#include "Thread.h"

class CEcsDoc;

class CBufferController : public CDialog
{
// Construction
public:
	CBufferController(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBufferController)
	enum { IDD = IDD_CV_CTRL1 };
	BOOL	m_bSuspend;
	//}}AFX_DATA

// Attribute
public:
	CEcsDoc* m_pDoc;
	int m_nID;


	int m_nLuggNo[2][6];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBufferController)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBufferController)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUFFERCONTROLLER_H__9524199C_56B5_4541_9731_334C6E48223B__INCLUDED_)
