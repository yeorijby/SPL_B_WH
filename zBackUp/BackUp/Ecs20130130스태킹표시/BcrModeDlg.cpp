// BcrModeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "BcrModeDlg.h"
#include "EcsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBcrModeDlg dialog


CBcrModeDlg::CBcrModeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBcrModeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBcrModeDlg)
	m_bAuto1 = FALSE;
	m_bTest1 = FALSE;
	//}}AFX_DATA_INIT
}


void CBcrModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBcrModeDlg)
	DDX_Check(pDX, IDC_CHECK_AUTO1, m_bAuto1);
	DDX_Check(pDX, IDC_CHECK_TEST1, m_bTest1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBcrModeDlg, CDialog)
	//{{AFX_MSG_MAP(CBcrModeDlg)
	ON_BN_CLICKED(IDC_BUTTON_SETUP, OnButtonSetup)
	ON_BN_CLICKED(IDC_CHECK_AUTO1, OnCheckAuto1)
	ON_BN_CLICKED(IDC_CHECK_TEST1, OnCheckTest1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBcrModeDlg message handlers

BOOL CBcrModeDlg::OnInitDialog() 
{

	if (m_pDoc->m_pBcrInfo[0]->m_ucMode == BCR_MODE_AUTO)
	{
		m_bAuto1 = TRUE;
		m_bTest1 = FALSE;
	}
	else
	{
		m_bAuto1 = FALSE;
		m_bTest1 = TRUE;
	}
	
	CDialog::OnInitDialog();

	return TRUE;  
}

void CBcrModeDlg::OnButtonSetup() 
{
	int nModeChk[BCR_CNT] = {0}; //@@

	if (m_bAuto1)
	{
		if (m_pDoc->m_pBcrInfo[0]->m_ucMode == BCR_MODE_MANUAL)
			nModeChk[0] = 1;
		m_pDoc->m_pBcrInfo[0]->m_ucMode = BCR_MODE_AUTO;
	}
	else
		m_pDoc->m_pBcrInfo[0]->m_ucMode = BCR_MODE_MANUAL;
	if (m_bAuto1)
	{
		if (m_pDoc->m_pBcrInfo[0]->m_ucMode == BCR_MODE_MANUAL)
			nModeChk[0] = 1;
		m_pDoc->m_pBcrInfo[0]->m_ucMode = BCR_MODE_AUTO;
	}
	else
		m_pDoc->m_pBcrInfo[0]->m_ucMode = BCR_MODE_MANUAL;
		
	for (int i=0; i<BCR_CNT; i++)
	{
		m_pDoc->m_pBcrInfo[i]->m_bModified = TRUE;
		m_pDoc->m_pBcrInfo[i]->Backup();
		if (m_pDoc->m_pBcrInfo[i]->m_ucMode == BCR_MODE_AUTO)
		{
			if (m_pDoc->m_pBcrInfo[i]->m_bStatus)
				::PostMessage(m_pDoc->m_BcrThreadInfo[i].m_hwndNotify, WM_USER_BCR_NOTIFY, i, m_pDoc->m_pBcrInfo[i]->m_ucMode);
			else
				::PostMessage(m_pDoc->m_BcrThreadInfo[i].m_hwndNotify, WM_USER_BCR_NOTIFY, i, NOTIFY_ERROR);
		}
		else
			::PostMessage(m_pDoc->m_BcrThreadInfo[i].m_hwndNotify, WM_USER_BCR_NOTIFY, i, m_pDoc->m_pBcrInfo[i]->m_ucMode);

		//if (nModeChk[i] == 1)
		//	m_pDoc->m_pJob->RemoveBcrJob(i+1);
	}

	AfxMessageBox("BCR Mode 설정 완료");
	
}

void CBcrModeDlg::OnCheckAuto1() 
{
	if (m_bAuto1)
	{
		m_bAuto1 = FALSE;
		m_bTest1 = TRUE;
	}
	else
	{
		m_bAuto1 = TRUE;
		m_bTest1 = FALSE;
	}

	CDialog::OnInitDialog();
	
}

void CBcrModeDlg::OnCheckTest1() 
{
	if (m_bTest1)
	{
		m_bAuto1 = TRUE;
		m_bTest1 = FALSE;
	}
	else
	{
		m_bAuto1 = FALSE;
		m_bTest1 = TRUE;
	}

	CDialog::OnInitDialog();
	
}
