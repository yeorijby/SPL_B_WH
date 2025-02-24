#if !defined(AFX_CVSTO1DLG_H__9594E1C0_DF5A_11D4_863C_00010290A450__INCLUDED_)
#define AFX_CVSTO1DLG_H__9594E1C0_DF5A_11D4_863C_00010290A450__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CvSto1Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCvSto1Dlg dialog

class CEcsDoc;

class CCvSto1Dlg : public CDialog
{
// Construction
public:
	CCvSto1Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCvSto1Dlg)
	enum { IDD = IDD_CV_STORE1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attribute
public:
	CEcsDoc* m_pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCvSto1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCvSto1Dlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CVSTO1DLG_H__9594E1C0_DF5A_11D4_863C_00010290A450__INCLUDED_)
