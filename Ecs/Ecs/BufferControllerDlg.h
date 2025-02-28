#if !defined(AFX_BUFFERCONTROLLERDLG_H__9524199C_56B5_4541_9731_334C6E48223B__INCLUDED_)
#define AFX_BUFFERCONTROLLERDLG_H__9524199C_56B5_4541_9731_334C6E48223B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BufferControllerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBufferControllerDlg dialog
#include "Thread.h"

class CEcsDoc;

class CBufferControllerDlg : public CDialog
{
// Construction
public:
	CBufferControllerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBufferControllerDlg)
	enum { IDD = IDD_CV_CTRL1 };
	BOOL	m_bSuspend;
	BOOL	m_bReady;
	//}}AFX_DATA

// Attribute
public:
	CEcsDoc* m_pDoc;
	int m_nID;


	int m_nLuggNo[2][6];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBufferControllerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBufferControllerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckSuspend();
	afx_msg void OnCheckReady();			// 일단은 읽어만 오는 걸로 하자 
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUFFERCONTROLLERDLG_H__9524199C_56B5_4541_9731_334C6E48223B__INCLUDED_)
