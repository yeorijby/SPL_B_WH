// ConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

#include "Config.h"

class CConfigDlg : public CDialog
{
// Construction
public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_CONFIG_STD };
	int		m_nEcsSvPort;

	int		m_nPort;
	CString	m_strAddr;
	BOOL	m_bConnect;
	BOOL	m_bRetry;
	BOOL	m_bJob;
	BOOL	m_bEvent;
	BOOL	m_bError;
	BOOL	m_bDebug;
	BOOL	m_bBeep;

	UINT	m_nCvPort1;
	UINT	m_nCvPort2;
	UINT	m_nCvPort3;
	UINT	m_nCvPort4;
	UINT	m_nCvPort5;
	UINT	m_nCvPort6;
	UINT	m_nCvPort7;
	UINT	m_nCvPort8;
	UINT	m_nEcsPort;
	BOOL	m_bCvConnect1;
	BOOL	m_bCvConnect2;
	BOOL	m_bCvConnect3;
	BOOL	m_bCvConnect4;
	BOOL	m_bCvConnect5;
	BOOL	m_bCvConnect6;
	BOOL	m_bCvConnect7;
	BOOL	m_bCvConnect8;
	BOOL	m_bEcsConnect;
	BOOL	m_bCvRetry1;
	BOOL	m_bCvRetry2;
	BOOL	m_bCvRetry3;
	BOOL	m_bCvRetry4;
	BOOL	m_bCvRetry5;
	BOOL	m_bCvRetry6;
	BOOL	m_bCvRetry7;
	BOOL	m_bCvRetry8;
	BOOL	m_bEcsRetry;

	UINT	m_nScPort1;
	BOOL	m_bScConnect1;
	BOOL	m_bScRetry1;

	UINT	m_nScPort2;
	BOOL	m_bScConnect2;
	BOOL	m_bScRetry2;

	UINT	m_nScPort3;
	BOOL	m_bScConnect3;
	BOOL	m_bScRetry3;

	UINT	m_nScPort4;
	BOOL	m_bScConnect4;
	BOOL	m_bScRetry4;

	UINT	m_nScPort5;
	BOOL	m_bScConnect5;
	BOOL	m_bScRetry5;

	UINT	m_nScPort6;
	BOOL	m_bScConnect6;
	BOOL	m_bScRetry6;

//	CString	m_strClientLocation;
//	CString	m_strOrderFile;
	//}}AFX_DATA

// Attributes
	CConfig* m_pConfig;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
