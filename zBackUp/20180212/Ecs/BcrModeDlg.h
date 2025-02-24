#if !defined(AFX_BCRMODEDLG_H__CA0C5CA0_D76A_11D4_863C_00010290A450__INCLUDED_)
#define AFX_BCRMODEDLG_H__CA0C5CA0_D76A_11D4_863C_00010290A450__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BcrModeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBcrModeDlg dialog

#include "EcsDef.h"
#include <EcsEnv.h>

class CEcsDoc;

class CBcrModeDlg : public CDialog
{
// Construction
public:
	CBcrModeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBcrModeDlg)
	enum { IDD = IDD_BCR_MODE };
	BOOL	m_bAuto1;
	BOOL	m_bTest1;
	//}}AFX_DATA

// Attributes
public:
	int m_nID;
	CEcsDoc* m_pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBcrModeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBcrModeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSetup();
	afx_msg void OnCheckAuto1();
	afx_msg void OnCheckTest1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCRMODEDLG_H__CA0C5CA0_D76A_11D4_863C_00010290A450__INCLUDED_)
