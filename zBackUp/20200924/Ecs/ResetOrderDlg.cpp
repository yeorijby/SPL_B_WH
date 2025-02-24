// ResetOrderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "EcsDoc.h"
#include "ResetOrderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResetOrderDlg dialog


CResetOrderDlg::CResetOrderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResetOrderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResetOrderDlg)
	m_strCvOrder = _T("");
	m_strScOrder = _T("");
	//}}AFX_DATA_INIT
}


void CResetOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResetOrderDlg)
	DDX_Text(pDX, IDC_EDIT_CV_ORDER, m_strCvOrder);
	DDV_MaxChars(pDX, m_strCvOrder, 4);
	DDX_Text(pDX, IDC_EDIT_SC_ORDER, m_strScOrder);
	DDV_MaxChars(pDX, m_strScOrder, 4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResetOrderDlg, CDialog)
	//{{AFX_MSG_MAP(CResetOrderDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResetOrderDlg message handlers

BOOL CResetOrderDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString strTemp;
	
	strTemp.Format("%d", m_pDoc->m_pJob->m_nScOrderNo);
	SET(IDC_EDIT_SC_ORDER, strTemp);
	strTemp.Format("%d", m_pDoc->m_pJob->m_nCvOrderNo);
	SET(IDC_EDIT_CV_ORDER, strTemp);
	
	return TRUE;
}

void CResetOrderDlg::OnOK() 
{
	CString strTemp;
	int nScOrderNo, nCvOrderNo;

	GET(IDC_EDIT_SC_ORDER, strTemp);
	nScOrderNo = atoi(strTemp);
	if (m_pDoc->m_pJob->m_nScOrderNo != nScOrderNo)
	{
		m_pDoc->m_pJob->m_nScOrderNo = nScOrderNo;
		strTemp.Format("S/C 출고Order 변경 : %d", nScOrderNo);
		m_pDoc->m_pLog->Event(LOG_POS_SYSTEM, LOG_SYSTEM, strTemp);
	}

	GET(IDC_EDIT_CV_ORDER, strTemp);
	nCvOrderNo = atoi(strTemp);
	if (m_pDoc->m_pJob->m_nCvOrderNo != nCvOrderNo)
	{
		m_pDoc->m_pJob->ChangeStatusByOrder(m_pDoc->m_pJob->m_nCvOrderNo);
		m_pDoc->m_pJob->m_bEndTrnSta = TRUE;
		m_pDoc->m_pJob->m_nCvOrderNo = nCvOrderNo;
		strTemp.Format("C/V 출발Order 변경 : %d", nCvOrderNo);
		m_pDoc->m_pLog->Event(LOG_POS_SYSTEM, LOG_SYSTEM, strTemp);
	}
		
	CDialog::OnOK();
}
