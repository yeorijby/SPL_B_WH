// CvLineDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCvLineDlg dialog
#include "Thread.h"

#include "SxButton.h"
#include "EditEx.h"

class CEcsDoc;

class CCvLineDlg : public CDialog
{
// Construction
public:
	CCvLineDlg(CWnd* pParent = NULL);   // standard constructor

// Attribute
public:
	CEcsDoc* m_pDoc;
	int m_nID;

	int m_nTimerID;

// Dialog Data
	//{{AFX_DATA(CConveyorDlg)
	enum { IDD = IDD_CVLINE_CTRL };


	//}}AFX_DATA


//	CSxButton	m_btnManualSto;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConveyorDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CConveyorDlg)
	virtual BOOL OnInitDialog();

	virtual void OnCancel();	
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
