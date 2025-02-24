// LogoDlg.cpp : implementation file
//

#include "stdafx.h"
#include <EcsEnv.h>
#include "Ecs.h"
#include "LogoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogoDlg dialog


CLogoDlg::CLogoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
//	ASSERT(m_pParent != NULL);

//	m_pParent = pParent;
//	m_nID = CLogoDlg::IDD;
}


void CLogoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogoDlg, CDialog)
	//{{AFX_MSG_MAP(CLogoDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogoDlg message handlers

void CLogoDlg::Close()
{
	OnOK();
}

BOOL CLogoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(m_bInitial)
		m_nTimerID = SetTimer(ID_LOGO_TIMER, 1000, NULL); 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLogoDlg::OnTimer(UINT nIDEvent) 
{
	CDialog::OnTimer(nIDEvent);

	m_bInitial = FALSE;
	KillTimer(m_nTimerID);
	OnOK();
}

