// LogoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogoDlg dialog

class CLogoDlg : public CDialog
{
// Construction
public:
	CLogoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLogoDlg)
	enum { IDD = IDD_LOGO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Attributes
protected:
	int		m_nTimerID;
	CWnd*	m_pParent;
	int		m_nID;

// Implementation
public:
	BOOL	m_bInitial;
	void Close();

protected:
	// Generated message map functions
	//{{AFX_MSG(CLogoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
