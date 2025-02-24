// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "ConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
	m_nPort = 0;
	m_strAddr = _T("");
	m_bConnect = FALSE;
	m_bRetry = FALSE;
	m_bJob = FALSE;
	m_bEvent = FALSE;
	m_bError = FALSE;
	m_bDebug = FALSE;
	m_bBeep = FALSE;

	m_nEcsSvPort = 0;

	m_nCvPort1 = 0;
	m_nCvPort2 = 0;
	m_nCvPort3 = 0;
	m_nCvPort4 = 0;
	m_nCvPort5 = 0;
	m_nCvPort6 = 0;
	m_nCvPort7 = 0;
	m_nCvPort8 = 0;
	m_bCvConnect1 = FALSE;
	m_bCvConnect2 = FALSE;
	m_bCvConnect3 = FALSE;
	m_bCvConnect4 = FALSE;
	m_bCvConnect5 = FALSE;
	m_bCvConnect6 = FALSE;
	m_bCvConnect7 = FALSE;
	m_bCvConnect8 = FALSE;
	m_bCvRetry1 = FALSE;
	m_bCvRetry2 = FALSE;
	m_bCvRetry3 = FALSE;
	m_bCvRetry4 = FALSE;
	m_bCvRetry5 = FALSE;
	m_bCvRetry6 = FALSE;
	m_bCvRetry7 = FALSE;
	m_bCvRetry8 = FALSE;

//	m_strClientLocation = _T("");
//	m_strOrderFile = _T("");
	//}}AFX_DATA_INIT
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)

	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDV_MinMaxInt(pDX, m_nPort, 1, 10000);
	DDX_Text(pDX, IDC_EDIT_ADDR, m_strAddr);
	DDV_MaxChars(pDX, m_strAddr, 15);
	DDX_Check(pDX, IDC_CHECK_CONNECT, m_bConnect);
	DDX_Check(pDX, IDC_CHECK_RETRY, m_bRetry);

	DDX_Check(pDX, IDC_CHECK_JOB, m_bJob);
	DDX_Check(pDX, IDC_CHECK_EVENT, m_bEvent);
	DDX_Check(pDX, IDC_CHECK_ERROR, m_bError);
	DDX_Check(pDX, IDC_CHECK_DEBUG, m_bDebug);
	DDX_Check(pDX, IDC_CHECK_BEEP, m_bBeep);

	DDX_Text(pDX, IDC_EDIT_CV_PORT1, m_nCvPort1);
	DDX_Text(pDX, IDC_EDIT_CV_PORT2, m_nCvPort2);
	DDX_Text(pDX, IDC_EDIT_CV_PORT3, m_nCvPort3);
	DDX_Text(pDX, IDC_EDIT_CV_PORT4, m_nCvPort4);
	DDX_Text(pDX, IDC_EDIT_CV_PORT5, m_nCvPort5);
	DDX_Text(pDX, IDC_EDIT_CV_PORT6, m_nCvPort6);
	DDX_Text(pDX, IDC_EDIT_CV_PORT7, m_nCvPort7);
	DDX_Text(pDX, IDC_EDIT_CV_PORT8, m_nCvPort8);
	DDX_Text(pDX, IDC_EDIT_ECS_PORT, m_nEcsPort);
	DDX_Check(pDX, IDC_CHECK_CV_CONNECT1, m_bCvConnect1);
	DDX_Check(pDX, IDC_CHECK_CV_CONNECT2, m_bCvConnect2);
	DDX_Check(pDX, IDC_CHECK_CV_CONNECT3, m_bCvConnect3);
	DDX_Check(pDX, IDC_CHECK_CV_CONNECT4, m_bCvConnect4);
	DDX_Check(pDX, IDC_CHECK_CV_CONNECT5, m_bCvConnect5);
	DDX_Check(pDX, IDC_CHECK_CV_CONNECT6, m_bCvConnect6);
	DDX_Check(pDX, IDC_CHECK_CV_CONNECT7, m_bCvConnect7);
	DDX_Check(pDX, IDC_CHECK_CV_CONNECT8, m_bCvConnect8);
	DDX_Check(pDX, IDC_CHECK_ECS_CONNECT, m_bEcsConnect);
	DDX_Check(pDX, IDC_CHECK_CV_RETRY1, m_bCvRetry1);
	DDX_Check(pDX, IDC_CHECK_CV_RETRY2, m_bCvRetry2);
	DDX_Check(pDX, IDC_CHECK_CV_RETRY3, m_bCvRetry3);
	DDX_Check(pDX, IDC_CHECK_CV_RETRY4, m_bCvRetry4);
	DDX_Check(pDX, IDC_CHECK_CV_RETRY5, m_bCvRetry5);
	DDX_Check(pDX, IDC_CHECK_CV_RETRY6, m_bCvRetry6);
	DDX_Check(pDX, IDC_CHECK_CV_RETRY7, m_bCvRetry7);
	DDX_Check(pDX, IDC_CHECK_CV_RETRY8, m_bCvRetry8);
	DDX_Check(pDX, IDC_CHECK_ECS_RETRY, m_bEcsRetry);

//	DDX_Text(pDX, IDC_EDIT_CLIENT_LOCATION, m_strClientLocation);
//	DDX_Text(pDX, IDC_EDIT_ORDER_FILE, m_strOrderFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

BOOL CConfigDlg::OnInitDialog() 
{
#ifdef OPT_HOST_NETWORK_INTERFACE_USE
	m_strAddr  = m_pConfig->m_strHostAddr;
	m_nPort    = m_pConfig->m_nHostPort;
	m_bConnect = m_pConfig->m_bConnect;
	m_bRetry   = m_pConfig->m_bRetry;
#endif

#ifdef OPT_HOST_SAP_INTERFACE_USE
	m_strOrderFile = m_pConfig->m_strOrderFile;
	m_strClientLocation = m_pConfig->m_strClientLocation;
#endif

	m_nEcsSvPort    = m_pConfig->m_nEcsSvPort;

	m_bJob     = m_pConfig->m_bJob;
	m_bEvent   = m_pConfig->m_bEvent;
	m_bError   = m_pConfig->m_bError;
	m_bDebug   = m_pConfig->m_bDebug;
	m_bBeep    = m_pConfig->m_bBeep;

	m_nCvPort1 = m_pConfig->m_sCvPort[0].nPort;
	m_nCvPort2 = m_pConfig->m_sCvPort[1].nPort;
	m_nCvPort3 = m_pConfig->m_sCvPort[2].nPort;
	m_nCvPort4 = m_pConfig->m_sCvPort[3].nPort;
	m_nCvPort5 = m_pConfig->m_sCvPort[4].nPort;
	m_nCvPort6 = m_pConfig->m_sCvPort[5].nPort;
	m_nCvPort7 = m_pConfig->m_sCvPort[6].nPort;
	m_nCvPort8 = m_pConfig->m_sCvPort[7].nPort;
	m_nEcsPort = m_pConfig->m_nEcsPort;

	m_bCvConnect1 = m_pConfig->m_sCvPort[0].bConnect;
	m_bCvConnect2 = m_pConfig->m_sCvPort[1].bConnect;
	m_bCvConnect3 = m_pConfig->m_sCvPort[2].bConnect;
	m_bCvConnect4 = m_pConfig->m_sCvPort[3].bConnect;
	m_bCvConnect5 = m_pConfig->m_sCvPort[4].bConnect;
	m_bCvConnect6 = m_pConfig->m_sCvPort[5].bConnect;
	m_bCvConnect7 = m_pConfig->m_sCvPort[6].bConnect;
	m_bCvConnect8 = m_pConfig->m_sCvPort[7].bConnect;
	m_bEcsConnect = m_pConfig->m_bEcsConnect;

	m_bCvRetry1 = m_pConfig->m_sCvPort[0].bRetry;
	m_bCvRetry2 = m_pConfig->m_sCvPort[1].bRetry;
	m_bCvRetry3 = m_pConfig->m_sCvPort[2].bRetry;
	m_bCvRetry4 = m_pConfig->m_sCvPort[3].bRetry;
	m_bCvRetry5 = m_pConfig->m_sCvPort[4].bRetry;
	m_bCvRetry6 = m_pConfig->m_sCvPort[5].bRetry;
	m_bCvRetry7 = m_pConfig->m_sCvPort[6].bRetry;
	m_bCvRetry8 = m_pConfig->m_sCvPort[7].bRetry;
	m_bEcsRetry = m_pConfig->m_bEcsRetry;

	CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT_CV_ADDR1, m_pConfig->m_sCvPort[0].strAddress);
	SetDlgItemText(IDC_EDIT_CV_ADDR2, m_pConfig->m_sCvPort[1].strAddress);
	SetDlgItemText(IDC_EDIT_CV_ADDR3, m_pConfig->m_sCvPort[2].strAddress);
	SetDlgItemText(IDC_EDIT_CV_ADDR4, m_pConfig->m_sCvPort[3].strAddress);
	SetDlgItemText(IDC_EDIT_CV_ADDR5, m_pConfig->m_sCvPort[4].strAddress);
	SetDlgItemText(IDC_EDIT_CV_ADDR6, m_pConfig->m_sCvPort[5].strAddress);
	SetDlgItemText(IDC_EDIT_CV_ADDR7, m_pConfig->m_sCvPort[6].strAddress);
	SetDlgItemText(IDC_EDIT_CV_ADDR8, m_pConfig->m_sCvPort[7].strAddress);

	SetDlgItemText(IDC_EDIT_ECS_ADDR, m_pConfig->m_strEcsAddr);
	
	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_COMM);

	LV_COLUMN lvcolumn;
	char szText[256];

	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvcolumn.fmt = LVCFMT_LEFT;
	sprintf(szText, "%s", "Thread");
	lvcolumn.pszText = szText;
	lvcolumn.iSubItem = 0;
	lvcolumn.cx = 80;

	pListCtrl->InsertColumn(0, &lvcolumn);

	sprintf(szText, "%s", "ComName");
	lvcolumn.pszText = szText;
	lvcolumn.cx = 90; 
	pListCtrl->InsertColumn(1, &lvcolumn); 

	sprintf(szText, "%s", "BaudRate");
	lvcolumn.pszText = szText;
	lvcolumn.cx = 80; 
	pListCtrl->InsertColumn(2, &lvcolumn); 

	sprintf(szText, "%s", "Parity");
	lvcolumn.pszText = szText;
	lvcolumn.cx = 80; 
	pListCtrl->InsertColumn(3, &lvcolumn); 
	
	sprintf(szText, "%s", "StopBits");
	lvcolumn.pszText = szText;
	lvcolumn.cx = 80; 
	pListCtrl->InsertColumn(4, &lvcolumn); 
	
	sprintf(szText, "%s", "BitsPerChar");
	lvcolumn.pszText = szText;
	lvcolumn.cx = 80; 
	pListCtrl->InsertColumn(5, &lvcolumn); 

	m_pConfig->Load(pListCtrl);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigDlg::OnButtonSave() 
{
	CString strAddr;

	if (AfxMessageBox("시스템 환경을 변경하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return ;

	if (!UpdateData(TRUE))
	{
		TRACE0("UpdateData failed during dialog termination.\n");
		// the UpdateData routine will set focus to correct item
		return;
	}

#ifdef OPT_HOST_NETWORK_INTERFACE_USE
	m_pConfig->m_strHostAddr = m_strAddr;
	m_pConfig->m_nHostPort   = m_nPort;
	m_pConfig->m_bConnect    = m_bConnect;
	m_pConfig->m_bRetry      = m_bRetry;
#endif

#ifdef OPT_HOST_SAP_INTERFACE_USE
	m_pConfig->m_strOrderFile = m_strOrderFile;
	m_pConfig->m_strClientLocation = m_strClientLocation;
#endif

	m_pConfig->m_nEcsSvPort  = m_nEcsSvPort;

	m_pConfig->m_bJob        = m_bJob;
	m_pConfig->m_bEvent      = m_bEvent;
	m_pConfig->m_bError      = m_bError;
	m_pConfig->m_bDebug      = m_bDebug;
	m_pConfig->m_bBeep       = m_bBeep;

	GetDlgItemText(IDC_EDIT_CV_ADDR1, strAddr);			
	m_pConfig->m_sCvPort[0].strAddress = strAddr;
	GetDlgItemText(IDC_EDIT_CV_ADDR2, strAddr);			
	m_pConfig->m_sCvPort[1].strAddress = strAddr;
	GetDlgItemText(IDC_EDIT_CV_ADDR3, strAddr);			
	m_pConfig->m_sCvPort[2].strAddress = strAddr;
	GetDlgItemText(IDC_EDIT_CV_ADDR4, strAddr);			
	m_pConfig->m_sCvPort[3].strAddress = strAddr;
	GetDlgItemText(IDC_EDIT_CV_ADDR5, strAddr);			
	m_pConfig->m_sCvPort[4].strAddress = strAddr;
	GetDlgItemText(IDC_EDIT_CV_ADDR6, strAddr);			
	m_pConfig->m_sCvPort[5].strAddress = strAddr;
	GetDlgItemText(IDC_EDIT_CV_ADDR7, strAddr);			
	m_pConfig->m_sCvPort[6].strAddress = strAddr;
	GetDlgItemText(IDC_EDIT_CV_ADDR8, strAddr);			
	m_pConfig->m_sCvPort[7].strAddress = strAddr;

	GetDlgItemText(IDC_EDIT_ECS_ADDR, strAddr);			
	m_pConfig->m_strEcsAddr		= strAddr;

	m_pConfig->m_sCvPort[0].nPort = m_nCvPort1;
	m_pConfig->m_sCvPort[1].nPort = m_nCvPort2;
	m_pConfig->m_sCvPort[2].nPort = m_nCvPort3;
	m_pConfig->m_sCvPort[3].nPort = m_nCvPort4;
	m_pConfig->m_sCvPort[4].nPort = m_nCvPort5;
	m_pConfig->m_sCvPort[5].nPort = m_nCvPort6;
	m_pConfig->m_sCvPort[6].nPort = m_nCvPort7;
	m_pConfig->m_sCvPort[7].nPort = m_nCvPort8;

	m_pConfig->m_nEcsPort	= m_nEcsPort;

	m_pConfig->m_sCvPort[0].bConnect	= m_bCvConnect1;
	m_pConfig->m_sCvPort[1].bConnect	= m_bCvConnect2;
	m_pConfig->m_sCvPort[2].bConnect	= m_bCvConnect3;
	m_pConfig->m_sCvPort[3].bConnect	= m_bCvConnect4;
	m_pConfig->m_sCvPort[4].bConnect	= m_bCvConnect5;
	m_pConfig->m_sCvPort[5].bConnect	= m_bCvConnect6;
	m_pConfig->m_sCvPort[6].bConnect	= m_bCvConnect7;
	m_pConfig->m_sCvPort[7].bConnect	= m_bCvConnect8;

	m_pConfig->m_bEcsConnect	= m_bEcsConnect;

	m_pConfig->m_sCvPort[0].bRetry = m_bCvRetry1;
	m_pConfig->m_sCvPort[1].bRetry = m_bCvRetry2;
	m_pConfig->m_sCvPort[2].bRetry = m_bCvRetry3;
	m_pConfig->m_sCvPort[3].bRetry = m_bCvRetry4;
	m_pConfig->m_sCvPort[4].bRetry = m_bCvRetry5;
	m_pConfig->m_sCvPort[5].bRetry = m_bCvRetry6;
	m_pConfig->m_sCvPort[6].bRetry = m_bCvRetry7;
	m_pConfig->m_sCvPort[7].bRetry = m_bCvRetry8;

	m_pConfig->m_bEcsRetry	 = m_bEcsRetry;

	m_pConfig->WriteProfile();

	OnOK();
}
