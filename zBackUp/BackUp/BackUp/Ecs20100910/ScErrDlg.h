#if !defined(AFX_SCERRDLG_H__5A82E645_E511_43C0_BD53_D0DC69DE3E00__INCLUDED_)
#define AFX_SCERRDLG_H__5A82E645_E511_43C0_BD53_D0DC69DE3E00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScErrDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScErrDlg dialog

class CScErrDlg : public CDialog
{
// Construction
public:
	CScErrDlg(CWnd* pParent = NULL);   // standard constructor
	void DispScErr(CListBox*, char *, int);
	void PrintTitle(CDC* pDC, int nPageNum);
	int  ReadLogInfo(int, char *);

// Dialog Data
	//{{AFX_DATA(CScErrDlg)
	enum { IDD = IDD_SC_ERR };
	CEdit	m_Editdate;
	CString	m_date;
	//}}AFX_DATA

	char   chTime[9];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScErrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScErrDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit1();
	afx_msg void OnClear2();
	virtual void OnOK();
	afx_msg void OnPrt();
	afx_msg void OnSc1();
	afx_msg void OnSc2();
	afx_msg void OnSc3();
	afx_msg void OnSc4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCERRDLG_H__5A82E645_E511_43C0_BD53_D0DC69DE3E00__INCLUDED_)
