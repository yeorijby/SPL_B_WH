// CommonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "CommonDlg.h"
#include "EcsDoc.h"
#include "Lib.h"
#include "Host.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConveyorDlg dialog


CCommonDlg::CCommonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConveyorDlg)

	//}}AFX_DATA_INIT
}


void CCommonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConveyorDlg)

	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CCommonDlg, CDialog)
	//{{AFX_MSG_MAP(CCommonDlg)
	
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPojanggiDlg message handlers

#define TRACK_MSG	m_pDoc->m_ConveyorThreadInfo[CV_PLC_NUM].m_ConveyorMsg

BOOL CCommonDlg::OnInitDialog() 
{

	CDialog::OnInitDialog();

/*	CString strTemp;

	strTemp = (m_pDoc->m_ConveyorTrackInfo[823-1].m_bWrapSignalIn1 == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_IN1, strTemp);

	strTemp = (m_pDoc->m_ConveyorTrackInfo[823-1].m_bWrapSignalIn2 == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_IN2, strTemp);

	strTemp = (m_pDoc->m_ConveyorTrackInfo[823-1].m_bWrapSignalIn3 == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_IN3, strTemp);

	strTemp = (m_pDoc->m_ConveyorTrackInfo[823-1].m_bWrapSignalIn4 == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_IN4, strTemp);


	strTemp = (m_pDoc->m_ConveyorTrackInfo[823-1].m_bWrapSignalOut1 == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_OUT1, strTemp);

	strTemp = (m_pDoc->m_ConveyorTrackInfo[823-1].m_bWrapSignalOut2 == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_OUT2, strTemp);

	strTemp = (m_pDoc->m_ConveyorTrackInfo[823-1].m_bWrapSignalOut3 == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_OUT3, strTemp);

	strTemp = (m_pDoc->m_ConveyorTrackInfo[823-1].m_bWrapSignalOut4 == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_OUT4, strTemp);
*/
	m_nTimerID = SetTimer(ID_WRAPING_TIMER, 1000, NULL);

	return TRUE;
}

#undef CV_PLC_NUM
#undef TRACK_MSG


BOOL CCommonDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (int) pMsg->wParam == VK_ESCAPE )
	       return TRUE;
		
	return CDialog::PreTranslateMessage(pMsg);
}

void CCommonDlg::OnCancel() 
{

	KillTimer(m_nTimerID);

	CDialog::OnCancel();
}


void CCommonDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
//	SetSubClassingItem();

	CString strTemp;

	strTemp = (m_pDoc->m_ConveyorTrackInfo[823-1].m_bWrapSignalIn1 == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_IN1, strTemp);

	strTemp = (m_pDoc->m_ConveyorTrackInfo[823-1].m_bWrapSignalIn2 == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_IN2, strTemp);

	strTemp = (m_pDoc->m_ConveyorTrackInfo[823-1].m_bWrapSignalIn3 == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_IN3, strTemp);

	strTemp = (m_pDoc->m_ConveyorTrackInfo[823-1].m_bWrapSignalIn4 == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_IN4, strTemp);


	strTemp = (m_pDoc->m_ConveyorTrackInfo[823-1].m_bWrapSignalOut1 == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_OUT1, strTemp);

	strTemp = (m_pDoc->m_ConveyorTrackInfo[823-1].m_bWrapSignalOut2 == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_OUT2, strTemp);

	strTemp = (m_pDoc->m_ConveyorTrackInfo[823-1].m_bWrapSignalOut3 == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_OUT3, strTemp);

	strTemp = (m_pDoc->m_ConveyorTrackInfo[823-1].m_bWrapSignalOut4 == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_OUT4, strTemp);

	CDialog::OnTimer(nIDEvent);
}


