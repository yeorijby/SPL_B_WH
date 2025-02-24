#if !defined(AFX_SCINHIBITDLG_H__DC515100_D688_11D4_863C_00010290A450__INCLUDED_)
#define AFX_SCINHIBITDLG_H__DC515100_D688_11D4_863C_00010290A450__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScInhibitDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScInhibitDlg dialog

#include "EcsDef.h"
#include <EcsEnv.h>

class CEcsDoc;

class CScInhibitDlg : public CDialog
{
// Construction
public:
	CScInhibitDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScInhibitDlg)
	enum { IDD = IDD_SC_INHIBIT };
	BOOL	m_bRetrieve1;
	BOOL	m_bRetrieve2;
	BOOL	m_bRetrieve3;
	BOOL	m_bRetrieve4;
	BOOL	m_bStore1;
	BOOL	m_bStore2;
	BOOL	m_bStore3;
	BOOL	m_bStore4;
	//}}AFX_DATA

// Attributes
public:
	int m_nID;
	CEcsDoc* m_pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScInhibitDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScInhibitDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckStore1();
	afx_msg void OnCheckStore2();
	afx_msg void OnCheckStore3();
	afx_msg void OnCheckStore4();
	afx_msg void OnCheckRetrieve1();
	afx_msg void OnCheckRetrieve2();
	afx_msg void OnCheckRetrieve3();
	afx_msg void OnCheckRetrieve4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCINHIBITDLG_H__DC515100_D688_11D4_863C_00010290A450__INCLUDED_)
