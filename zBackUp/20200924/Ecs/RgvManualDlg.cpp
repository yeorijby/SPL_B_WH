// RgvManualDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"

#include "EcsDoc.h"
#include "RgvManualDlg.h"

#include "Lib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////
// CRgvManualDlg dialog


CRgvManualDlg::CRgvManualDlg(CEcsDoc *pDoc, int nID, int nWareHouse, CString strCaption, CWnd* pParent /*=NULL*/)
	: CDialog(CRgvManualDlg::IDD, pParent)
{
	m_pDoc = pDoc;

	m_nID = nID;
	m_nWareHouse = nWareHouse;
	m_strCaption = strCaption;

	//{{AFX_DATA_INIT(CRgvManualDlg)
	//}}AFX_DATA_INIT
}


void CRgvManualDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRgvManualDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRgvManualDlg, CDialog)
	//{{AFX_MSG_MAP(CRgvManualDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////
// CRgvManualDlg message handlers

BOOL CRgvManualDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetWindowText(m_strCaption);

	CComboBox* pComboStart = (CComboBox *)GetDlgItem(IDC_COMBO_RGV_START);
	CComboBox* pComboDest = (CComboBox *)GetDlgItem(IDC_COMBO_RGV_DEST);

	CString strTemp;

	int nCnt = (m_nID == 0) ? 23 : 13;

	for(int i = 0; i < nCnt; i++)
	{
		int nTrackNum = CLib::GetRgvStartHSTrack(m_nID, i);
		strTemp.Format("CV#%d-(%d)", nTrackNum+1, i+1);
		pComboStart->InsertString(i, strTemp);
	}
	pComboStart->SetCurSel(0);
		
	for( i = 0; i < nCnt; i++)
	{
		int nTrackNum = CLib::GetRgvDestHSTrack(m_nID, i);
		strTemp.Format("CV#%d-(%d)", nTrackNum+1, i+1);
		pComboDest->InsertString(i, strTemp);
	}
	pComboDest->SetCurSel(0);
	return TRUE;
}

void CRgvManualDlg::OnOK() 
{
	if (AfxMessageBox("RTV 수동작업 지시를 하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return ;

	UpdateData(TRUE);

	CComboBox* pComboStart = (CComboBox *)GetDlgItem(IDC_COMBO_RGV_START);
	CComboBox* pComboDest = (CComboBox *)GetDlgItem(IDC_COMBO_RGV_DEST);
	int nStartHS = pComboStart->GetCurSel();
	int nDestHS = pComboDest->GetCurSel();

	CString strStartTrack;
	CString strDestTrack;
	
	pComboStart->GetLBText(pComboStart->GetCurSel(), strStartTrack);
	pComboDest->GetLBText(pComboDest->GetCurSel(), strDestTrack);

	int nStartTrack = atoi( strStartTrack.Mid(3, strStartTrack.GetLength()) );
	int nDestTrack  = atoi( strDestTrack.Mid(3, strDestTrack.GetLength()) );

//	int nStartPos = GetRgvPosPerTrack(nStartTrack);
//	int nDestPos  = GetRgvPosPerTrack(nDestTrack);

	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.nStartHS = nStartTrack;
	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.nDestHS  = nDestTrack;
	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.nCommand  = RGV_CMD_MANUAL;
	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.bModified = TRUE;
	RGV_ACTION(m_nID);

	CDialog::OnOK();
}

int CRgvManualDlg::GetRgvPosPerTrack(int nTrackNum)
{
	switch (m_nID)
	{
	case	RGV_1_NUM:
		switch(nTrackNum)
		{
		case	122:			return  1;
		case	115:			return  2;
		case	128:			return  3;
		case	134:			return  4;
		case	140:			return  5;
		case	146:			return  6;
		case	151:			return  7;
		case	110:			return  8;
		case	107:			return  9;
		case	103:			return  10;
		}
		break;

	case	RGV_2_NUM:
		switch (nTrackNum)
		{
		case	208:		return  1;
		case	211:		return  2;
		case	217:		return  3;
		case	222:		return  4;
		case	228:		return  5;
		case	234:		return  6;
		case	239:		return  7;
		case	113:		return  8;
		case	109:		return  9;
		}
		break;

	}

	return 0;
}