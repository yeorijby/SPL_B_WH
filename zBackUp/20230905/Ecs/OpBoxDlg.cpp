// OpBoxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "EcsDoc.h"
#include "OpBoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpBoxDlg dialog


COpBoxDlg::COpBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpBoxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpBoxDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COpBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpBoxDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpBoxDlg, CDialog)
	//{{AFX_MSG_MAP(COpBoxDlg)
	ON_BN_CLICKED(IDC_BUTTON_OUT_RESET, OnButtonOutReset)
	ON_BN_CLICKED(IDC_BUTTON__IN_RESET, OnButtonInReset)
	ON_BN_CLICKED(IDC_BUTTON_FIRST_IN, OnButtonFirstIn)
	ON_BN_CLICKED(IDC_BUTTON_COUNTER_SET, OnButtonCounterSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpBoxDlg message handlers

#define CV_PLC_NUM		( m_nID == 22  ? 3 : (m_nID == 24 ? 4 : 5))
#define TRACK_MSG	m_pDoc->m_ConveyorThreadInfo[CV_PLC_NUM].m_ConveyorMsg

BOOL COpBoxDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString strTemp;
	int	nOpNum;

	nOpNum = m_nID + 1;
	switch (nOpNum)
	{
	case 1 :
		strTemp.Format("1-1");
		break;
	case 2 :
		strTemp.Format("1-2");
		break;
	case 3 :
		strTemp.Format("1-3");
		break;
	case 4 :
		strTemp.Format("1-4");
		break;
	case 5 :
		strTemp.Format("1-5");
		break;
	case 6 :
		strTemp.Format("2-1");
		break;
	case 7 :
		strTemp.Format("2-2");
		break;
	case 8 :
		strTemp.Format("2-3");
		break;
	case 9 :
		strTemp.Format("2-4");
		break;
	case 10 :
		strTemp.Format("2-5");
		break;
	case 11 :
		strTemp.Format("2-6");
		break;
	case 12 :
		strTemp.Format("2-7");
		break;
	case 13 :
		strTemp.Format("2-8");
		break;
	case 14 :
		strTemp.Format("2-9");
		break;
	case 15 :
		strTemp.Format("2-10");
		break;
	case 16 :
		strTemp.Format("2-11");
		break;
	case 17 :
		strTemp.Format("2-12");
		break;
	case 18 :
		strTemp.Format("2-13");
		break;
	case 19 :
		strTemp.Format("3-1");
		break;
	case 20 :
		strTemp.Format("3-2");
		break;
	case 21 :
		strTemp.Format("3-3");
		break;
	case 22 :
		strTemp.Format("4-1");
		break;
	case 23 :
		strTemp.Format("4-2");
		break;
	case 24 :
		strTemp.Format("5-1");
		break;
	case 25 :
		strTemp.Format("5-2");
		break;
	case 26 :
		strTemp.Format("6-1");
		break;
	case 27 :
		strTemp.Format("6-2");
		break;
	}
	SET(IDC_EDIT_NUM, strTemp);
	
	if (m_pDoc->m_OpBoxInfo[m_nID].m_bAutoMode)
		strTemp.Format(" 자동");
	else
		strTemp.Format(" 수동");
	SET(IDC_EDIT_MODE, strTemp);

	if (m_pDoc->m_OpBoxInfo[m_nID].m_bNormalStatus)
		strTemp.Format(" 정상");
	else
		strTemp.Format(" 비상정지");
	SET(IDC_EDIT_STATUS, strTemp);

	if(m_nID != 22 && m_nID != 24 && m_nID != 26)
	{
		GetDlgItem(IDC_BUTTON__IN_RESET)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OUT_RESET)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_FIRST_IN)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_BUFF_COUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_COUNTER_SET)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_BUFF)->EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COpBoxDlg::OnButtonOutReset() 
{
	if (AfxMessageBox("Out Counter를 초기화 하시겠습니까? ", MB_OKCANCEL) == IDCANCEL)
		return ;


	if(m_nID == 22)
	TRACK_MSG.nTrackNum    = 507;
	else if(m_nID == 24)
	TRACK_MSG.nTrackNum    = 607;
	else if(m_nID == 26)
	TRACK_MSG.nTrackNum    = 707;

	TRACK_MSG.nLuggNum     = 0;
	TRACK_MSG.nJobType     = 0;
	TRACK_MSG.nStartPos    = 0;
	TRACK_MSG.nDestPos     = 0;
	TRACK_MSG.nLastPallet =  0;

	TRACK_MSG.bModified = TRUE;

	CV_ACTION(CV_PLC_NUM);

	CString strLog;
	strLog.Format("CConveyorDlg::OnButtonOutReset.. %dGroup Out Count 초기화..", m_nID == 22 ? 4 : (m_nID == 24 ? 5 : 6));
	m_pDoc->m_pLog->Event(LOG_POS_CV, 0000, strLog);
}

void COpBoxDlg::OnButtonInReset() 
{
	if (AfxMessageBox("In Counter를 초기화 하시겠습니까? ", MB_OKCANCEL) == IDCANCEL)
		return ;

	CString strLog;

	if(m_nID == 22)
	m_pDoc->m_nInCountReset = 400;
	else if(m_nID == 24)
	m_pDoc->m_nInCountReset = 401;
	else if(m_nID == 26)
	m_pDoc->m_nInCountReset = 402;

	m_pDoc->m_bInResetCheck = TRUE;

	CV_ACTION(CV_3_PLC);

	strLog.Format("CConveyorDlg::OnButtonInReset.. %dGroup In Count 초기화..", m_nID == 22 ? 4 : (m_nID == 24 ? 5 : 6));
	m_pDoc->m_pLog->Event(LOG_POS_CV, 0000, strLog);
}

void COpBoxDlg::OnButtonFirstIn() 
{
	if (AfxMessageBox("첫번째 버퍼 진입으로 설정 하시겠습니까? ", MB_OKCANCEL) == IDCANCEL)
		return ;


	if(m_nID == 22)
	TRACK_MSG.nTrackNum    = 494;
	else if(m_nID == 24)
	TRACK_MSG.nTrackNum    = 594;
	else if(m_nID == 26)
	TRACK_MSG.nTrackNum    = 694;

	TRACK_MSG.nLuggNum     = 0;
	TRACK_MSG.nJobType     = 0;
	TRACK_MSG.nStartPos    = 0;
	TRACK_MSG.nDestPos     = 0;
	TRACK_MSG.nLastPallet =  0;

	TRACK_MSG.bModified = TRUE;

	CV_ACTION(CV_PLC_NUM);

	CString strLog;
	strLog.Format("CConveyorDlg::OnButtonFirstIn.. %dGroup 첫번째 버퍼 진입으로 설정..", m_nID == 22 ? 4 : (m_nID == 24 ? 5 : 6));
	m_pDoc->m_pLog->Event(LOG_POS_CV, 0000, strLog);	
}

void COpBoxDlg::OnButtonCounterSet() 
{

	CString strTemp;
	GET(IDC_EDIT_BUFF_COUNT, strTemp);

	if(m_nID == 22)
	m_pDoc->m_n4goupBuffCouter = atoi(strTemp);
	else if(m_nID == 24)
	m_pDoc->m_n5goupBuffCouter = atoi(strTemp);
	else if(m_nID == 26)
	m_pDoc->m_n6goupBuffCouter = atoi(strTemp);

	CString strLog;
	strLog.Format("CConveyorDlg::OnButtonCounterSet.. %dGroup 버퍼 수량 설정..", m_nID == 22 ? 4 : (m_nID == 24 ? 5 : 6));
	m_pDoc->m_pLog->Event(LOG_POS_CV, 0000, strLog);

}
