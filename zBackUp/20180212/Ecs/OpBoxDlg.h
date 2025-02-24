// OpBoxDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpBoxDlg dialog

class CEcsDoc;

class COpBoxDlg : public CDialog
{
// Construction
public:
	COpBoxDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COpBoxDlg)
	enum { IDD = IDD_OPBOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
	int m_nID;
	CEcsDoc* m_pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpBoxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COpBoxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonOutReset();
	afx_msg void OnButtonInReset();
	afx_msg void OnButtonFirstIn();
	afx_msg void OnButtonCounterSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
