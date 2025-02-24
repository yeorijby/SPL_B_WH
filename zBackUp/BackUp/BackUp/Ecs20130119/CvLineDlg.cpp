// CvLineDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "CvLineDlg.h"
#include "EcsDoc.h"
#include "Lib.h"
#include "Host.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCvLineDlg dialog


CCvLineDlg::CCvLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCvLineDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConveyorDlg)

	//}}AFX_DATA_INIT
}


void CCvLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConveyorDlg)

	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CCvLineDlg, CDialog)
	//{{AFX_MSG_MAP(CCommonDlg)
	
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPojanggiDlg message handlers

#define TRACK_MSG	m_pDoc->m_ConveyorThreadInfo[CV_PLC_NUM].m_ConveyorMsg

BOOL CCvLineDlg::OnInitDialog() 
{

	CDialog::OnInitDialog();

	CString strTemp;
	strTemp.Format(" SFA CV#%d", m_nID + 1);
	GetDlgItem(IDC_EDIT_TRACK_NUM)->SetWindowText(strTemp);

	if(m_nID >= 1049)
	{
		strTemp.Format(" SPL Stacker#%d", m_nID - 1048);
		GetDlgItem(IDC_EDIT_TRACK_NUM)->SetWindowText(strTemp);

		GetDlgItem(IDC_EDIT_PLT_SENSOR)->EnableWindow(FALSE);
	}

	m_nTimerID = SetTimer(ID_WRAPING_TIMER, 1000, NULL);

	return TRUE;
}

#undef CV_PLC_NUM
#undef TRACK_MSG


BOOL CCvLineDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (int) pMsg->wParam == VK_ESCAPE )
	       return TRUE;
		
	return CDialog::PreTranslateMessage(pMsg);
}

void CCvLineDlg::OnCancel() 
{

	KillTimer(m_nTimerID);

	CDialog::OnCancel();
}


void CCvLineDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
//	SetSubClassingItem();

	CString strTemp;

	strTemp = (m_pDoc->m_ConveyorTrackInfo[m_nID].m_bPltSensor == TRUE) ? "있음" : "없음"; 
	SET(IDC_EDIT_PLT_SENSOR, strTemp);

	if (m_pDoc->m_ConveyorTrackInfo[m_nID].m_bOverTimeErr)
		SET(IDC_EDIT_ERROR_CODE, " OverTime Error");
	else if (m_pDoc->m_ConveyorTrackInfo[m_nID].m_bOverLoadErr)
		SET(IDC_EDIT_ERROR_CODE, " OverLoad Error");
	else
		SET(IDC_EDIT_ERROR_CODE, " 정상(Normal)");

	if(m_nID >= 1049)
	{
		if (m_pDoc->m_ConveyorTrackInfo[m_nID].m_bOpMode)
			SET(IDC_EDIT_ERROR_CODE, " 정상(Normal)");
		else if (m_pDoc->m_ConveyorTrackInfo[m_nID].m_bError)
			SET(IDC_EDIT_ERROR_CODE, " Error(Alarm)");
		else
			SET(IDC_EDIT_ERROR_CODE, " 정상(Normal)");

		SET(IDC_EDIT_PLT_SENSOR, "");
	}


	CDialog::OnTimer(nIDEvent);
}


