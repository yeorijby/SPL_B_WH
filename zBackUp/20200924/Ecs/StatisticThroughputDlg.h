#if !defined(AFX_STATISTICTHROUGHPUTDLG_H__B1D7F6E2_72AC_11D2_B757_00A024826C1A__INCLUDED_)
#define AFX_STATISTICTHROUGHPUTDLG_H__B1D7F6E2_72AC_11D2_B757_00A024826C1A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StatisticThroughputDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatisticThroughputDlg dialog
class CEcsDoc;

class CStatisticThroughputDlg : public CDialog
{
// Construction
public:
	CStatisticThroughputDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatisticThroughputDlg)
	enum { IDD = IDD_STATISTICS_THROUGHPUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Attributes
public:
	CEcsDoc* m_pDoc;
	BOOL	m_bSelected;
	int		m_nDay;
	CString m_strDir;
	CString m_strFileName;
	struct	SStatisticInfo	m_sStcInfo[SC_CNT];

	void Refresh(struct SStatisticInfo *STATICS, BOOL bToday=TRUE);
	void Loading();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatisticThroughputDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStatisticThroughputDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonFile();
	afx_msg void OnButtonRefresh();
	afx_msg void OnButtonOfflineChart();
	afx_msg void OnButtonOnlineChart();
	afx_msg void OnButtonRatioChart();
	afx_msg void OnButtonSumCount();
	afx_msg void OnButtonOnofflineChart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATISTICTHROUGHPUTDLG_H__B1D7F6E2_72AC_11D2_B757_00A024826C1A__INCLUDED_)
