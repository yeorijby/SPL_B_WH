#if !defined(AFX_RESETORDERDLG_H__18A83CBD_8853_4627_930E_92CFDBE21144__INCLUDED_)
#define AFX_RESETORDERDLG_H__18A83CBD_8853_4627_930E_92CFDBE21144__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResetOrderDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResetOrderDlg dialog

class CEcsDoc;

class CResetOrderDlg : public CDialog
{
// Construction
public:
	CResetOrderDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResetOrderDlg)
	enum { IDD = IDD_RESET_ORDER };
	CString	m_strCvOrder;
	CString	m_strScOrder;
	//}}AFX_DATA

// Attributes
public:
	CEcsDoc* m_pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResetOrderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResetOrderDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESETORDERDLG_H__18A83CBD_8853_4627_930E_92CFDBE21144__INCLUDED_)
