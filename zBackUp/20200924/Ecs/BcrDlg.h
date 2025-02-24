#if !defined(AFX_BCRDLG_H__7F3486F2_D5ED_11D3_BA7F_005004C01131__INCLUDED_)
#define AFX_BCRDLG_H__7F3486F2_D5ED_11D3_BA7F_005004C01131__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BcrDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBcrDlg dialog

class CEcsDoc;

class CBcrDlg : public CDialog
{
// Construction
public:
	CBcrDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBcrDlg)
	enum { IDD = IDD_BCR_CTRL };
	CString	m_strData;
	//}}AFX_DATA

// Attributes
	int m_nID;
	CEcsDoc* m_pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBcrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBcrDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCreate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCRDLG_H__7F3486F2_D5ED_11D3_BA7F_005004C01131__INCLUDED_)
