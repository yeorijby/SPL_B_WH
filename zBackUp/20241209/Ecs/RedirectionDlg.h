#if !defined(AFX_REDIRECTIONDLG_H__EFDB3963_1A8D_11D1_829E_00A024CA879C__INCLUDED_)
#define AFX_REDIRECTIONDLG_H__EFDB3963_1A8D_11D1_829E_00A024CA879C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RedirectionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRedirectionDlg dialog

class CRedirectionDlg : public CDialog
{
// Construction
public:
	CRedirectionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRedirectionDlg)
	enum { IDD = IDD_NEW_LOCATION };
	CString	m_strLocation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRedirectionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRedirectionDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REDIRECTIONDLG_H__EFDB3963_1A8D_11D1_829E_00A024CA879C__INCLUDED_)
