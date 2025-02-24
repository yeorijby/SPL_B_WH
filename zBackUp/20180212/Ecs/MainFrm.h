// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	HWND m_hwndView;

// Operations
public:
	void DisplayMessage(CString strMsg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetViewHandle(HWND hwnd);
	int GetIndex(char Status);
	void UpdateCommHost(UINT unID, char Status);
	void UpdateCommHostCl(char Status);
	void UpdateCommHostSv(char Status);
	void UpdateCommCv(UINT unID, char Status);
	void UpdateCommSc(UINT unID, char Status);
	void UpdateCommRgv(UINT unID, char Status);
	void UpdateCommEcsCl(char Status);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
