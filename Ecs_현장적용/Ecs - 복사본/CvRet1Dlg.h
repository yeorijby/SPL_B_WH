#if !defined(AFX_CVRET1DLG_H__BCCC33C0_E166_11D4_863C_00010290A450__INCLUDED_)
#define AFX_CVRET1DLG_H__BCCC33C0_E166_11D4_863C_00010290A450__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CvRet1Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCvRet1Dlg dialog

class CEcsDoc;

class CCvRet1Dlg : public CDialog
{
// Construction
public:
	CCvRet1Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCvRet1Dlg)
	enum { IDD = IDD_CV_RETRIEVE1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attribute
public:
	CEcsDoc* m_pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCvRet1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCvRet1Dlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CVRET1DLG_H__BCCC33C0_E166_11D4_863C_00010290A450__INCLUDED_)
