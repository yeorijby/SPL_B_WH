// ManualDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CManualDlg dialog

#ifndef __MANUALDLG_H__
#define __MANUALDLG_H__

class CEcsDoc;
class CManualDlg : public CDialog
{
// Construction
public:
	CManualDlg(CWnd* pParent = NULL);   // standard constructor

	CEcsDoc* m_pDoc;
	int m_nTrackNum;
	int m_nLuggNum;
	int m_nJobType;
	int m_nCmd;
	BOOL m_bCheckHostNotify;
	void Recording(int nJobClass, int nLuggNum, CString strSrcLoc = "0000000", CString strDestLoc = "0000000", CString strProductCode = "", CString strLotNo = "", CString strQty = "");

// Dialog Data
	//{{AFX_DATA(CManualDlg)
	enum { IDD = IDD_MANUAL };
	CString	m_strLocationDest;
	CString	m_strLocationStart;
	CString	m_strQuantity;
	CString	m_strLotNo;
	CString	m_strProdCode;
	CString	m_strLuggNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManualDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CManualDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickTabManual(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonConfirm();
	afx_msg void OnCheckHostNotify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // __MANUALDLG_H__
