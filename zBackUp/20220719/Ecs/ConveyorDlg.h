// ConveyorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConveyorDlg dialog
#include "Thread.h"

class CEcsDoc;

class CConveyorDlg : public CDialog
{
// Construction
public:
	CConveyorDlg(CWnd* pParent = NULL);   // standard constructor

// Attribute
public:
	CEcsDoc* m_pDoc;
	int m_nID;
//	BOOL m_bCopied;
//	SConveyorMsg m_ConveyorMsg;

// Dialog Data
	//{{AFX_DATA(CConveyorDlg)
	enum { IDD = IDD_CV_CTRL };
	CString m_strLuggNum;
	CString	m_strBatchNum;
	//}}AFX_DATA


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
	void GetDisplayTrackInfo();

	// Generated message map functions
	//{{AFX_MSG(CConveyorDlg)
	afx_msg void OnButtonManualSto();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboJobType();
	afx_msg void OnButtonWrite();
	afx_msg void OnButtonCopy();
	afx_msg void OnButtonPaste();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonCut();
	afx_msg void OnButtonLastPallet();
	afx_msg void OnButtonLastPalletReset();
	afx_msg void OnButtonRewrite();
	afx_msg void OnButtonCvStatus();
	afx_msg void OnButtonPlcCount();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
