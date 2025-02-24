// JobDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CJobDlg dialog
#ifndef __JOBDLG_H__
#define __JOBDLG_H__

class CJobDlg : public CDialog
{
// Construction
public:
	CJobDlg(CWnd* pParent = NULL);   // standard constructor
	~CJobDlg();

	CEcsDoc* m_pDoc;

// Dialog Data
	//{{AFX_DATA(CJobDlg)
	enum { IDD = IDD_JOB };
	//}}AFX_DATA

public:
	CImageList* m_pImageList;
	int m_nType;
	int m_nStatus;
	int m_nCurSel;
	BOOL m_bCheckAuto;
	BOOL m_bAscend;

// Operation
public:
	void Loading();
	void JobItemDetail(int nCmd); 
	void RepaintSelectedItems();
	LPCTSTR MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJobDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CJobDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickTabJob(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonRefresh();
	afx_msg void OnSelchangeComboType();
	afx_msg void OnButtonModify();
	afx_msg void OnButtonCancel();
	afx_msg void OnButtonRetry();
	afx_msg void OnButtonComplete();
	afx_msg void OnItemchangedListJob(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckAuto();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void OnOK();
	afx_msg void OnDblclkListJob(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHeaderClicked(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // __JOBDLG_H__
