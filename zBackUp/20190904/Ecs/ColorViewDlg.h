#if !defined(AFX_COLORVIEWDLG_H__81650680_EC31_11D2_B136_080009B90446__INCLUDED_)
#define AFX_COLORVIEWDLG_H__81650680_EC31_11D2_B136_080009B90446__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorViewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorViewDlg dialog

class CColorViewDlg : public CDialog
{
// Construction
public:
	CColorViewDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CColorViewDlg)
	enum { IDD = IDD_COLOR_VIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CColorViewDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORVIEWDLG_H__81650680_EC31_11D2_B136_080009B90446__INCLUDED_)
