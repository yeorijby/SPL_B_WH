
#include "SxButton.h"
#include "EditEx.h"
#include "Label.h"

class CRgvDlg : public CDialog
{
public:
	CEcsDoc *m_pDoc;

	int m_nID;
	int m_nWareHouse;
	CString m_strCaption;

	int m_nTimerID;

// Construction
public:
	CRgvDlg(CWnd* pParent = NULL);   // standard constructor
	void SetSxButton();

// Dialog Data
	//{{AFX_DATA(CRgvDlg)
	enum { IDD = IDD_RGV_CTRL };
	BOOL	m_bRetrieve;
	BOOL	m_bStore;
	//}}AFX_DATA
/*	CSxButton	m_btnComplete;
	CSxButton	m_btnCancel;
	CSxButton   m_btnEStop;
	CSxButton   m_btnStop;
	CSxButton   m_btnActive;
	CSxButton   m_btnReset;
	CSxButton	m_btnCallToHome;
	CSxButton	m_btnManual;

	CLabel  m_stcLuggNum;
	CLabel  m_stcJobType;
	CLabel  m_stcStartPos;
	CLabel  m_stcDestPos;
	CLabel  m_stcInternalLuggNum;

	CEditEx     m_edtRgvNum;
	CEditEx     m_edtLuggNum;
	CEditEx     m_edtJobType;
	CEditEx     m_edtStartPos;
	CEditEx     m_edtDestPos;

	CEditEx     m_edtMode;
	CEditEx     m_edtStatus;

	CEditEx     m_edtInternalLuggNum;
	CEditEx     m_edtStartHomeStand;
	CEditEx     m_edtDestHomeStand;

	CEditEx		m_btnDiagnosis;
*/
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRgvDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void Refresh();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRgvDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonComplete();
	afx_msg void OnButtonEstop();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonCallToHome();
	afx_msg void OnButtonManual();
	afx_msg void OnButtonCancel();
	afx_msg void OnCheckStore();
	afx_msg void OnCheckRetrieve();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonActive();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

