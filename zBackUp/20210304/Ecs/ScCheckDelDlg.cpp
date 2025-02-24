// ScCheckDelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "ScCheckDelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScCheckDelDlg dialog

CScCheckDelDlg::CScCheckDelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScCheckDelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScCheckDelDlg)
	m_bFork1 = FALSE;
	m_bFork2 = FALSE;
	m_bFork12 = FALSE;
	//}}AFX_DATA_INIT
}


void CScCheckDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScCheckDelDlg)
	DDX_Check(pDX, IDC_FORK1, m_bFork1);
	DDX_Check(pDX, IDC_FORK2, m_bFork2);
	DDX_Check(pDX, IDC_FORK12, m_bFork12);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScCheckDelDlg, CDialog)
	//{{AFX_MSG_MAP(CScCheckDelDlg)
	ON_BN_CLICKED(IDC_FORK1, OnFork1)
	ON_BN_CLICKED(IDC_FORK2, OnFork2)
	ON_BN_CLICKED(IDC_FORK12, OnFork12)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScCheckDelDlg message handlers

void CScCheckDelDlg::OnFork1() 
{
	UpdateData(TRUE);
	if(m_bFork1 == TRUE)
	{
		m_nCheck = 1;
		((CButton*)GetDlgItem(IDC_FORK2))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_FORK12))->SetCheck(FALSE); 
	}
}

void CScCheckDelDlg::OnFork2() 
{
	UpdateData(TRUE);

	if(m_bFork2 == TRUE)
	{
		m_nCheck = 2;
		((CButton*)GetDlgItem(IDC_FORK1))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_FORK12))->SetCheck(FALSE); 

	}
}

void CScCheckDelDlg::OnFork12() 
{
	UpdateData(TRUE);

	if(m_bFork12 == TRUE)
	{
		m_nCheck = 3;
		((CButton*)GetDlgItem(IDC_FORK1))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_FORK2))->SetCheck(FALSE); 
	}
}

BOOL CScCheckDelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

		m_nCheck = 0;
	
	return TRUE;
}
