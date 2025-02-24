// ScInhibitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "ScInhibitDlg.h"
#include "EcsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScInhibitDlg dialog


CScInhibitDlg::CScInhibitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScInhibitDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScInhibitDlg)
	m_bRetrieve1 = FALSE;
	m_bRetrieve2 = FALSE;
	m_bRetrieve3 = FALSE;
	m_bRetrieve4 = FALSE;
	m_bStore1 = FALSE;
	m_bStore2 = FALSE;
	m_bStore3 = FALSE;
	m_bStore4 = FALSE;
	//}}AFX_DATA_INIT
}


void CScInhibitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScInhibitDlg)
	DDX_Check(pDX, IDC_CHECK_RETRIEVE1, m_bRetrieve1);
	DDX_Check(pDX, IDC_CHECK_RETRIEVE2, m_bRetrieve2);
	DDX_Check(pDX, IDC_CHECK_RETRIEVE3, m_bRetrieve3);
	DDX_Check(pDX, IDC_CHECK_RETRIEVE4, m_bRetrieve4);
	DDX_Check(pDX, IDC_CHECK_STORE1, m_bStore1);
	DDX_Check(pDX, IDC_CHECK_STORE2, m_bStore2);
	DDX_Check(pDX, IDC_CHECK_STORE3, m_bStore3);
	DDX_Check(pDX, IDC_CHECK_STORE4, m_bStore4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScInhibitDlg, CDialog)
	//{{AFX_MSG_MAP(CScInhibitDlg)
	ON_BN_CLICKED(IDC_CHECK_STORE1, OnCheckStore1)
	ON_BN_CLICKED(IDC_CHECK_STORE2, OnCheckStore2)
	ON_BN_CLICKED(IDC_CHECK_STORE3, OnCheckStore3)
	ON_BN_CLICKED(IDC_CHECK_STORE4, OnCheckStore4)
	ON_BN_CLICKED(IDC_CHECK_RETRIEVE1, OnCheckRetrieve1)
	ON_BN_CLICKED(IDC_CHECK_RETRIEVE2, OnCheckRetrieve2)
	ON_BN_CLICKED(IDC_CHECK_RETRIEVE3, OnCheckRetrieve3)
	ON_BN_CLICKED(IDC_CHECK_RETRIEVE4, OnCheckRetrieve4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScInhibitDlg message handlers

BOOL CScInhibitDlg::OnInitDialog() 
{
	
	m_bStore1 = m_pDoc->m_pStackerInfo[0]->m_bStoreSuspend;
	m_bStore2 = m_pDoc->m_pStackerInfo[1]->m_bStoreSuspend;
	m_bStore3 = m_pDoc->m_pStackerInfo[2]->m_bStoreSuspend;
	m_bStore4 = m_pDoc->m_pStackerInfo[3]->m_bStoreSuspend;
	m_bRetrieve1 = m_pDoc->m_pStackerInfo[0]->m_bRetrieveSuspend;
	m_bRetrieve2 = m_pDoc->m_pStackerInfo[1]->m_bRetrieveSuspend;
	m_bRetrieve3 = m_pDoc->m_pStackerInfo[2]->m_bRetrieveSuspend;
	m_bRetrieve4 = m_pDoc->m_pStackerInfo[3]->m_bRetrieveSuspend;
	
	CDialog::OnInitDialog();

	return TRUE;
}

void CScInhibitDlg::OnCheckStore1() 
{
	m_pDoc->m_pStackerInfo[0]->m_bStoreSuspend = !m_pDoc->m_pStackerInfo[0]->m_bStoreSuspend;
	m_pDoc->m_pStackerInfo[0]->m_bModified = TRUE;

}

void CScInhibitDlg::OnCheckStore2() 
{
	m_pDoc->m_pStackerInfo[1]->m_bStoreSuspend = !m_pDoc->m_pStackerInfo[1]->m_bStoreSuspend;
	m_pDoc->m_pStackerInfo[1]->m_bModified = TRUE;
	
}

void CScInhibitDlg::OnCheckStore3() 
{
	m_pDoc->m_pStackerInfo[2]->m_bStoreSuspend = !m_pDoc->m_pStackerInfo[2]->m_bStoreSuspend;
	m_pDoc->m_pStackerInfo[2]->m_bModified = TRUE;
	
}

void CScInhibitDlg::OnCheckStore4() 
{
	m_pDoc->m_pStackerInfo[3]->m_bStoreSuspend = !m_pDoc->m_pStackerInfo[3]->m_bStoreSuspend;
	m_pDoc->m_pStackerInfo[3]->m_bModified = TRUE;
	
}

void CScInhibitDlg::OnCheckRetrieve1() 
{
	m_pDoc->m_pStackerInfo[0]->m_bRetrieveSuspend = !m_pDoc->m_pStackerInfo[0]->m_bRetrieveSuspend;
	m_pDoc->m_pStackerInfo[0]->m_bModified = TRUE;
	
}

void CScInhibitDlg::OnCheckRetrieve2() 
{
	m_pDoc->m_pStackerInfo[1]->m_bRetrieveSuspend = !m_pDoc->m_pStackerInfo[1]->m_bRetrieveSuspend;
	m_pDoc->m_pStackerInfo[1]->m_bModified = TRUE;
	
}

void CScInhibitDlg::OnCheckRetrieve3() 
{
	m_pDoc->m_pStackerInfo[2]->m_bRetrieveSuspend = !m_pDoc->m_pStackerInfo[2]->m_bRetrieveSuspend;
	m_pDoc->m_pStackerInfo[2]->m_bModified = TRUE;
	
}

void CScInhibitDlg::OnCheckRetrieve4() 
{
	m_pDoc->m_pStackerInfo[3]->m_bRetrieveSuspend = !m_pDoc->m_pStackerInfo[3]->m_bRetrieveSuspend;
	m_pDoc->m_pStackerInfo[3]->m_bModified = TRUE;
	
}
