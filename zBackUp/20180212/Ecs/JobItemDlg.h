// JobItemDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CJobItemDlg dialog

class CJobItem;
class CEcsDoc;

class CJobItemDlg : public CDialog
{
// Construction
public:
	CJobItemDlg(CWnd* pParent = NULL);   // standard constructor

// Attribute
public:
	CEcsDoc* m_pDoc;
	CJobItem* m_pJobItem;
	int m_nCmd;

// Dialog Data
	//{{AFX_DATA(CJobItemDlg)
	enum { IDD = IDD_JOB_ITEM };
	BOOL	m_bNoNotify;
	CString	m_strLocationDest;
	CString	m_strLocationStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJobItemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CJobItemDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
