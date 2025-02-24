// StatisticErrCodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "StatisticErrCodeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatisticErrCodeDlg dialog


CStatisticErrCodeDlg::CStatisticErrCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatisticErrCodeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatisticErrCodeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStatisticErrCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatisticErrCodeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatisticErrCodeDlg, CDialog)
	//{{AFX_MSG_MAP(CStatisticErrCodeDlg)
	ON_BN_CLICKED(IDC_BUTTON_FILE, OnButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_SAVEAS, OnButtonSaveas)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_BN_CLICKED(IDC_CHECK_ERRCODE, OnCheckErrcode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatisticErrCodeDlg message handlers

BOOL CStatisticErrCodeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CTime theTime = CTime::GetCurrentTime();
	m_nDay = theTime.GetDay();

	CString strTemp;
	strTemp.Format("%.2d/%.2d", theTime.GetMonth(), m_nDay);
	GetDlgItem(IDC_EDIT_DATE)->SetWindowText(strTemp);
	
	m_pImageList = new CImageList();
	ASSERT(m_pImageList != NULL);    // no serious allocation failure checking

	CEcsApp* pApp = (CEcsApp *)AfxGetApp();
	m_pImageList->Create(16, 16, TRUE/*bMask*/,	1/*nInitial*/, 1/*nGrow*/);
	m_pImageList->Add(pApp->LoadIcon(IDI_ICON2));

	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_ERRCODE);

	pListCtrl->SetImageList(m_pImageList, LVSIL_SMALL);

	LV_COLUMN		lvcolumn;

	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvcolumn.fmt = LVCFMT_LEFT;
	lvcolumn.pszText = "발생위치";
	lvcolumn.iSubItem = 0;
	lvcolumn.cx = 85;

	pListCtrl->InsertColumn(0, &lvcolumn);

	lvcolumn.pszText = "에러코드";
	lvcolumn.cx = 70; 
	pListCtrl->InsertColumn(1, &lvcolumn); 

	lvcolumn.pszText = "발생건수";
	lvcolumn.cx = 50; 
	pListCtrl->InsertColumn(2, &lvcolumn); 

	lvcolumn.pszText = "내용";
	lvcolumn.cx = 500; 
	pListCtrl->InsertColumn(3, &lvcolumn); 

	CTabCtrl* pTabCtrl = (CTabCtrl *)GetDlgItem(IDC_TAB_SCNUM);

	TC_ITEM TabCtrlItem;

	TabCtrlItem.mask = TCIF_TEXT;
    TabCtrlItem.pszText = "전체";
	pTabCtrl->InsertItem(0, &TabCtrlItem);
    TabCtrlItem.pszText = "Stacker #1";
	pTabCtrl->InsertItem(1, &TabCtrlItem);
    TabCtrlItem.pszText = "Stacker #2";
	pTabCtrl->InsertItem(2, &TabCtrlItem);
    TabCtrlItem.pszText = "Stacker #3";
	pTabCtrl->InsertItem(3, &TabCtrlItem);
    TabCtrlItem.pszText = "Stacker #4";
	pTabCtrl->InsertItem(4, &TabCtrlItem);
    TabCtrlItem.pszText = "Stacker #5";
	pTabCtrl->InsertItem(5, &TabCtrlItem);
    TabCtrlItem.pszText = "Stacker #6";
	pTabCtrl->InsertItem(6, &TabCtrlItem);
    TabCtrlItem.pszText = "Stacker #7";
	pTabCtrl->InsertItem(7, &TabCtrlItem);

//	Loading();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStatisticErrCodeDlg::OnButtonFile() 
{
	// TODO: Add your control notification handler code here
	
}

void CStatisticErrCodeDlg::OnButtonPrint() 
{
	// TODO: Add your control notification handler code here
	
}

void CStatisticErrCodeDlg::OnButtonRefresh() 
{
	// TODO: Add your control notification handler code here
	
}

void CStatisticErrCodeDlg::OnButtonSaveas() 
{
	// TODO: Add your control notification handler code here
	
}

void CStatisticErrCodeDlg::OnButtonSearch() 
{
	// TODO: Add your control notification handler code here
	
}

void CStatisticErrCodeDlg::OnCheckErrcode() 
{
	// TODO: Add your control notification handler code here
	
}
