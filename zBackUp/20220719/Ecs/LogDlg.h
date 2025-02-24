// LogDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogDlg dialog

class CLogDlg : public CDialog
{
// Construction
public:
	CLogDlg(CWnd* pParent = NULL);   // standard constructor
	~CLogDlg();
	LPCTSTR MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset);
	void PrintTitle(CDC* pDC, int nPageNum);

	CImageList* m_pImageList;
	CLog* m_pLog;
	BOOL m_bCheck;
	int m_nType;
	int m_nPos;
	int	m_nLuggNum;
	int m_nFrom;
	int m_nTo;
	int m_nDay;
	BOOL m_bAscend;


// Dialog Data
	//{{AFX_DATA(CLogDlg)
	enum { IDD = IDD_LOG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetRange();
	BOOL GetRange();

	// Generated message map functions
	//{{AFX_MSG(CLogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void Loading();
	afx_msg void OnClickLogTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckLuggId();
	afx_msg void OnButtonSearch();
	afx_msg void OnButtonFile();
	afx_msg void OnButtonPrint();
	afx_msg void OnButtonRefresh();
	afx_msg void OnButtonSaveas();
	afx_msg void OnSelchangeComboPosition();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnClickTabLog(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHeaderClicked(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
