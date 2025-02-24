// BcrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "EcsDoc.h"
#include "BcrDlg.h"
#include "BcrModeDlg.h"
#include "Lib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBcrDlg dialog


CBcrDlg::CBcrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBcrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBcrDlg)
	m_strData = _T("");
	//}}AFX_DATA_INIT
}


void CBcrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBcrDlg)
	DDX_Text(pDX, IDC_EDIT_DATA, m_strData);
	DDV_MaxChars(pDX, m_strData, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBcrDlg, CDialog)
	//{{AFX_MSG_MAP(CBcrDlg)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, OnButtonCreate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBcrDlg message handlers

BOOL CBcrDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString strTemp;
	int	nBcrNum;

	nBcrNum = m_nID + 1;

	strTemp.Format(" #%d", nBcrNum);
	SET(IDC_EDIT_BCRNO, strTemp);
	
	if (m_pDoc->m_pBcrInfo[m_nID]->m_ucMode == BCR_MODE_AUTO)
		strTemp.Format(" 운영 Mode");
	else
		strTemp.Format(" Test Mode");
	SET(IDC_EDIT_BCRMODE, strTemp);

	if (m_pDoc->m_pBcrInfo[m_nID]->m_bStatus)
		strTemp.Format(" Normal");
	else
		strTemp.Format(" Error ");
	SET(IDC_EDIT_BCRSTS, strTemp);

	SET(IDC_EDIT_DATA, m_pDoc->m_szBcrData[m_nID]);

	if (m_pDoc->m_pBcrInfo[m_nID]->m_nProSta == 1)
		strTemp.Format(" Reading");
	else if (m_pDoc->m_pBcrInfo[m_nID]->m_nProSta == 2)
		strTemp.Format(" 처리   ");
	else if (m_pDoc->m_pBcrInfo[m_nID]->m_nProSta == 9)
		strTemp.Format(" Error  ");
	else
		strTemp.Format("        ");
	SET(IDC_EDIT_PRO_STA, strTemp);

	return TRUE;

}

void CBcrDlg::OnButtonCreate() 
{
	CString strTemp;

	GET(IDC_EDIT_DATA, strTemp);
	
	m_pDoc->m_szBcrData[m_nID] = strTemp;
	m_pDoc->m_pBcrInfo[m_nID]->m_strBcrData = strTemp;
	m_pDoc->m_pBcrInfo[m_nID]->m_nProSta = 1;

	//m_pDoc->m_pJob->AddBcrBuff(nSeqNo, 1, strTemp, 2);
	
}
