#if !defined(AFX_STACKERTWINDLG_H__66FAEBFF_4F7B_45A6_A528_8CD4E731F85E__INCLUDED_)
#define AFX_STACKERTWINDLG_H__66FAEBFF_4F7B_45A6_A528_8CD4E731F85E__INCLUDED_

#include "EcsDef.h"
#include <EcsEnv.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StackerTwinDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStackerTwinDlg dialog

class CEcsDoc;

class CStackerTwinDlg : public CDialog
{
// Construction
public:
	CStackerTwinDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStackerTwinDlg)
	enum { IDD = IDD_SC_TWIN_CTRL };
	BOOL	m_bRetrieve;
	BOOL	m_bStore;
	//}}AFX_DATA

// Attributes
public:
	void Refresh();
	int m_nID;
	int m_nTimerID;
	CEcsDoc* m_pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStackerTwinDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStackerTwinDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonCallToHome();
	afx_msg void OnButtonComplete();
	afx_msg void OnButtonNewLocation();
	afx_msg void OnButtonReset();
	afx_msg void OnCheckRetrieve();
	afx_msg void OnCheckStore();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonErrorReset();
	afx_msg void OnButtonActive();
	afx_msg void OnButtonEstop();
	afx_msg void OnButtonStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STACKERTWINDLG_H__66FAEBFF_4F7B_45A6_A528_8CD4E731F85E__INCLUDED_)
