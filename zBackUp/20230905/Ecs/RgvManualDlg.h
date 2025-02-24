

class CRgvManualDlg : public CDialog
{

public:
	CRgvManualDlg(CEcsDoc *pDoc, int nID, int nWareHouse, CString strCaption, CWnd* pParent = NULL);

	int  GetRgvPosPerTrack(int nTrackNum);


private:
	CEcsDoc *m_pDoc;

	int m_nID;
	int m_nWareHouse;
	CString m_strCaption;


// Dialog Data
	//{{AFX_DATA(CRgvManualDlg)
	enum { IDD = IDD_RGV_MANUAL };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRgvManualDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRgvManualDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

