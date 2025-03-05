// BufferDestSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ecs.h"
#include "BufferDestSettingDlg.h"
#include "EcsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBufferDestSettingDlg dialog


CBufferDestSettingDlg::CBufferDestSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBufferDestSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBufferDestSettingDlg)

	//}}AFX_DATA_INIT

}


void CBufferDestSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBufferDestSettingDlg)
	DDX_Control(pDX, IDC_SLIDER2, m_Slider);
	DDX_Text(pDX, IDC_EDIT_DEST1_TO, m_nDest1To);
	DDV_MinMaxInt(pDX, m_nDest1To, 1, 13);
	DDX_Text(pDX, IDC_EDIT_DEST2_FROM, m_nDest2From);
	DDV_MinMaxInt(pDX, m_nDest2From, 2, 14);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBufferDestSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CBufferDestSettingDlg)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	//NM_CUSTOMDRAW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1, IDC_RADIO2, OnRangeRadioGroup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBufferDestSettingDlg message handlers

BOOL CBufferDestSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString strTemp;
	strTemp.Format(" #%d", m_nID + 1);
	GetDlgItem(IDC_EDIT_TRACK_NUM)->SetWindowText(strTemp);

	GetDlgItem(IDC_EDIT_DEST1_FROM)->SetWindowText(_T("1"));
	GetDlgItem(IDC_EDIT_DEST1_TO)->SetWindowText(_T("1"));

	GetDlgItem(IDC_EDIT_DEST2_FROM)->SetWindowText(_T("2"));
	GetDlgItem(IDC_EDIT_DEST2_TO)->SetWindowText(_T("14"));

	m_Slider.SetRange(1, 13);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBufferDestSettingDlg::OnRangeRadioGroup(UINT uID)
{
	int nDest = 0;
	CString strTemp;
	switch (uID)
	{
	case IDC_RADIO1:
		strTemp = _T("[15] TR# 174 :");
		nDest = 15;
		break;
	case IDC_RADIO2:
		strTemp = _T("[16] TR# 176 :");
		nDest = 16;
		break;
	default:
		AfxMessageBox(_T("목적지를 선택해주세요"));
		return;
	}
	SetDlgItemText(IDC_STATIC_WRAP_DEST, strTemp);
	m_pDoc->m_nBufferDest1 = nDest;

}

void CBufferDestSettingDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// 슬라이더의 위치를 검사한다. 
	nPos = m_Slider.GetPos();

	m_nDest1To = nPos;
	m_nDest2From = ++nPos;

	UpdateData(FALSE);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CBufferDestSettingDlg::OnButtonSave()
{
	UpdateData(TRUE);

	m_pDoc->m_nBufferDest1To = m_nDest1To;
}
