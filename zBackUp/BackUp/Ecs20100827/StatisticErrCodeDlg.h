#if !defined(AFX_STATISTICERRCODEDLG_H__D22B30A1_9658_11D2_94DF_080009A4CC9D__INCLUDED_)
#define AFX_STATISTICERRCODEDLG_H__D22B30A1_9658_11D2_94DF_080009A4CC9D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StatisticErrCodeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatisticErrCodeDlg dialog
class CEcsDoc;

class CStatisticErrCodeDlg : public CDialog
{
// Construction
public:
	CStatisticErrCodeDlg(CWnd* pParent = NULL);   // standard constructor
	~CStatisticErrCodeDlg();
	LPCTSTR MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset);
	void PrintTitle(CDC* pDC, int nPageNum);

	CEcsDoc* m_pDoc;
	CImageList* m_pImageList;
	BOOL	m_bCheck;
	int		m_nScNum;
	int		m_nErrorCode;
	int		m_nDay;
	BOOL    m_bAscend;

	void Loading();

// Dialog Data
	//{{AFX_DATA(CStatisticErrCodeDlg)
	enum { IDD = IDD_STATISTICS_ERRCODE };
	CString	m_strErrorCode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatisticErrCodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStatisticErrCodeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickTabScNum(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonFile();
	afx_msg void OnButtonPrint();
	afx_msg void OnButtonRefresh();
	afx_msg void OnButtonSaveas();
	afx_msg void OnButtonSearch();
	afx_msg void OnCheckErrcode();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnHeaderClicked(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATISTICERRCODEDLG_H__D22B30A1_9658_11D2_94DF_080009A4CC9D__INCLUDED_)
