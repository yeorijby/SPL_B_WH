// RgvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"

#include "EcsDoc.h"
#include "RgvDlg.h"

#include "RgvManualDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRgvDlg dialog


CRgvDlg::CRgvDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRgvDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRgvDlg)
	m_bRetrieve = FALSE;
	m_bStore = FALSE;
	//}}AFX_DATA_INIT
}


void CRgvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRgvDlg)
	DDX_Check(pDX, IDC_CHECK_RETRIEVE, m_bRetrieve);
	DDX_Check(pDX, IDC_CHECK_STORE, m_bStore);
	//}}AFX_DATA_MAP
/*	DDX_Control(pDX, IDC_BUTTON_COMPLETE, m_btnComplete);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_BUTTON_ESTOP, m_btnEStop);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_btnStop);
	DDX_Control(pDX, IDC_BUTTON_ACTIVE, m_btnActive);
	DDX_Control(pDX, IDC_BUTTON_RESET, m_btnReset);
	DDX_Control(pDX, IDC_BUTTON_CALL_TO_HOME, m_btnCallToHome);
	DDX_Control(pDX, IDC_BUTTON_MANUAL, m_btnManual);

	DDX_Control(pDX, IDC_STATIC_LUGG_NUM, m_stcLuggNum);
	DDX_Control(pDX, IDC_STATIC_JOB_TYPE, m_stcJobType);
	DDX_Control(pDX, IDC_STATIC_START_POS, m_stcStartPos);
	DDX_Control(pDX, IDC_STATIC_DEST_POS, m_stcDestPos);
	DDX_Control(pDX, IDC_STATIC_INTERNAL_LUGG_NUM, m_stcInternalLuggNum);

	DDX_Control(pDX, IDC_EDIT_RGV_NUM, m_edtRgvNum);
	DDX_Control(pDX, IDC_EDIT_LUGG_NUM, m_edtLuggNum);
	DDX_Control(pDX, IDC_EDIT_JOB_TYPE, m_edtJobType);
	DDX_Control(pDX, IDC_EDIT_START_POS, m_edtStartPos);
	DDX_Control(pDX, IDC_EDIT_DEST_POS, m_edtDestPos);

	DDX_Control(pDX, IDC_EDIT_RGV_MODE, m_edtMode);
	DDX_Control(pDX, IDC_EDIT_STATUS, m_edtStatus);

	DDX_Control(pDX, IDC_EDIT_INTERNAL_LUGG_NUM, m_edtInternalLuggNum);
	DDX_Control(pDX, IDC_EDIT_START_HOME_STAND, m_edtStartHomeStand);
	DDX_Control(pDX, IDC_EDIT_DEST_HOME_STAND, m_edtDestHomeStand);

	DDX_Control(pDX, IDC_EDIT_DIAGNOSIS, m_btnDiagnosis);
*/
}


BEGIN_MESSAGE_MAP(CRgvDlg, CDialog)
	//{{AFX_MSG_MAP(CRgvDlg)
	ON_BN_CLICKED(IDC_BUTTON_COMPLETE, OnButtonComplete)
	ON_BN_CLICKED(IDC_BUTTON_ESTOP, OnButtonEstop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_CALL_TO_HOME, OnButtonCallToHome)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL, OnButtonManual)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_BN_CLICKED(IDC_CHECK_STORE, OnCheckStore)
	ON_BN_CLICKED(IDC_CHECK_RETRIEVE, OnCheckRetrieve)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_ACTIVE, OnButtonActive)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////
// CRgvDlg message handlers

#define RGV_INFO	m_pDoc->m_pRgvInfo[m_nID]

BOOL CRgvDlg::OnInitDialog() 
{
	m_bStore    = RGV_INFO->m_bStoreSuspend;
	m_bRetrieve = RGV_INFO->m_bRetrieveSuspend;

	CDialog::OnInitDialog();

//	SetSxButton();
//	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);

	CString strTemp;
//	SET(IDC_EDIT_RGV_NUM, m_strCaption);

	strTemp.Format(" #%d", m_nID+1);
	SET(IDC_EDIT_RGV_NUM, strTemp);


	Refresh();

	m_nTimerID = SetTimer(ID_RGV_TIMER, 1000, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRgvDlg::SetSxButton()
{
//	m_btnComplete.SetIcon(IDI_ICON_LEDOFF, 16, 16);
//	m_btnComplete.SetImagePos( CPoint ( 6, SXBUTTON_CENTER ));
//	m_btnComplete.SetTextPos( CPoint( 30, SXBUTTON_CENTER ));

//	m_btnEStop.SetIcon(IDI_ICON_LEDOFF, 16, 16);
//	m_btnEStop.SetImagePos( CPoint ( 6, SXBUTTON_CENTER ));
//	m_btnEStop.SetTextPos( CPoint( 30, SXBUTTON_CENTER ));

//	m_btnStop.SetIcon(IDI_ICON_LEDOFF, 16, 16);
//	m_btnStop.SetImagePos( CPoint ( 6, SXBUTTON_CENTER ));
//	m_btnStop.SetTextPos( CPoint( 30, SXBUTTON_CENTER ));

//	m_btnActive.SetIcon(IDI_ICON_LEDON, 16, 16);
//	m_btnActive.SetImagePos( CPoint ( 6, SXBUTTON_CENTER ));
//	m_btnActive.SetTextPos( CPoint( 30, SXBUTTON_CENTER ));

//	m_btnReset.SetIcon(IDI_ICON_RETURN, 16, 16);
//	m_btnReset.SetImagePos( CPoint ( 6, SXBUTTON_CENTER ));
//	m_btnReset.SetTextPos( CPoint( 30, SXBUTTON_CENTER ));

//	m_btnCallToHome.SetIcon(IDI_ICON_HOME, 16, 16);	
//	m_btnCallToHome.SetImagePos( CPoint ( 6, SXBUTTON_CENTER ));
//	m_btnCallToHome.SetTextPos( CPoint( 30, SXBUTTON_CENTER ));

//	m_btnManual.SetIcon(IDI_BTN_MANUAL, 16, 16);
//	m_btnManual.SetImagePos( CPoint ( 6, SXBUTTON_CENTER ));
//	m_btnManual.SetTextPos( CPoint( 30, SXBUTTON_CENTER ));

/*	LOGFONT logLogFont = {16, 0, 0, 0, FW_ULTRABOLD, FALSE, FALSE, FALSE, 1, 0, 0, 0, 0, _T("�߰��")};
	m_edtRgvNum.SetEditExFont(&logLogFont);
	m_edtRgvNum.SetBkColor(RGB(223, 223, 223));

	m_edtLuggNum.SetBkColor(RGB(255, 174, 136));
	m_edtJobType.SetBkColor(RGB(225, 255, 225));
	m_edtStartPos.SetBkColor(RGB(225, 255, 225));
	m_edtDestPos.SetBkColor(RGB(225, 255, 225));

	m_edtLuggNum.SetTextColor(RGB(0, 0, 255));
	m_edtJobType.SetTextColor(RGB(0, 0, 255));
	m_edtStartPos.SetTextColor(RGB(0, 0, 255));
	m_edtDestPos.SetTextColor(RGB(0, 0, 255));

	logLogFont.lfHeight = 14; logLogFont.lfWeight = FW_MEDIUM;
	m_edtLuggNum.SetEditExFont(&logLogFont);
	m_edtJobType.SetEditExFont(&logLogFont);
	m_edtStartPos.SetEditExFont(&logLogFont);
	m_edtDestPos.SetEditExFont(&logLogFont);

	m_edtMode.SetBkColor(RGB(178, 178, 178));
	m_edtStatus.SetBkColor(RGB(178, 178, 178));

	m_edtInternalLuggNum.SetEditExFont(&logLogFont);
	m_edtInternalLuggNum.SetTextColor(RGB(0, 0, 255));
	m_edtInternalLuggNum.SetBkColor(RGB(223, 223, 223));
	m_edtStartHomeStand.SetBkColor(RGB(178, 178, 178));
	m_edtDestHomeStand.SetBkColor(RGB(178, 178, 178));

	m_btnDiagnosis.SetBkColor(RGB(255, 255, 223));
	m_btnDiagnosis.SetTextColor(RGB(0, 0, 0));

	CFont *pFont = GetFont();
	pFont->GetLogFont(&logLogFont);

	m_stcLuggNum.SetFontName(logLogFont.lfFaceName);
	m_stcJobType.SetFontName(logLogFont.lfFaceName);
	m_stcStartPos.SetFontName(logLogFont.lfFaceName);
	m_stcDestPos.SetFontName(logLogFont.lfFaceName);
	m_stcInternalLuggNum.SetFontName(logLogFont.lfFaceName);

	m_stcLuggNum.SetFontSize(logLogFont.lfHeight);
	m_stcJobType.SetFontSize(logLogFont.lfHeight);
	m_stcStartPos.SetFontSize(logLogFont.lfHeight);
	m_stcDestPos.SetFontSize(logLogFont.lfHeight);
	m_stcInternalLuggNum.SetFontSize(logLogFont.lfHeight);

	m_stcLuggNum.SetTextColor(RGB(170, 0, 170));
	m_stcJobType.SetTextColor(RGB(170, 0, 170));
	m_stcStartPos.SetTextColor(RGB(170, 0, 170));
	m_stcDestPos.SetTextColor(RGB(170, 0, 170));
	m_stcInternalLuggNum.SetTextColor(RGB(161, 81, 0));
*/
}

void CRgvDlg::Refresh()
{
	SET(IDC_EDIT_RTV_LUGG_NUM, RGV_INFO->GetRgvLuggNumString());
	SET(IDC_EDIT_JOB_TYPE, RGV_INFO->GetRgvJobTypeString());
	CMoveJobItem* pMoveJobItem = MOVEJOB->Find(RGV_INFO->m_nInternalLuggNum);
	if (pMoveJobItem != NULL)
	{
		SET(IDC_EDIT_START_POS, pMoveJobItem->GetStartPos());
		SET(IDC_EDIT_DEST_POS, pMoveJobItem->GetDestPos());
	}

	SET(IDC_EDIT_RGV_MODE, RGV_INFO->GetRgvModeString());
	SET(IDC_EDIT_RGV_ACTIVE, RGV_INFO->GetActiveString());
	SET(IDC_EDIT_COMPLETE, RGV_INFO->GetCompleteString());
	SET(IDC_EDIT_PRODLOAD, RGV_INFO->GetProdLoadString());

	SET(IDC_EDIT_HORIZONTAL_POS, RGV_INFO->GetHorizontalPosString());
	SET(IDC_EDIT_STATUS, RGV_INFO->GetRgvStatusString());

	SET(IDC_EDIT_INTERNAL_LUGG_NUM, RGV_INFO->GetEcsLuggNumString());
	SET(IDC_EDIT_INTERNAL_LUGG_NUM2, RGV_INFO->GetEcsLuggNumString2());

	CString strTemp;
	strTemp.Format("%d", RGV_INFO->m_nStoNextRtn);
	SET(IDC_EDIT_RGV_RANK, strTemp);

	if (pMoveJobItem != NULL)
	{
		//SET(IDC_EDIT_RGV_LOCATION, pJobItem->m_strLocation);
		SET(IDC_EDIT_START_TRACK, RGV_INFO->GetStartTrackString());
		SET(IDC_EDIT_DEST_TRACK, RGV_INFO->GetDestTrackString());

		SET(IDC_EDIT_JOB_PROGRESS, pMoveJobItem->GetStatus());
		
		SET(IDC_EDIT_ITMCD, pMoveJobItem->m_strProductID);
		SET(IDC_EDIT_ITMNM, pMoveJobItem->m_strGrade);
	}
}

#define	TRACK_INFO		m_pDoc->m_ConveyorTrackInfo

void CRgvDlg::OnTimer(UINT nIDEvent) 
{
	CDialog::OnTimer(nIDEvent);

	Refresh();
//	m_btnDiagnosis.SetTextColor(RGB(255, 0, 0));

	CString strDiagnosis;
	if (RGV_INFO->m_ucStatus == RGV_STA_ERROR || RGV_INFO->m_wErrCode > 0)
	{
		CString strTemp;
	    //m_btnDiagnosis.SetTextColor(RGB(255, 0, 0));
		strTemp.Format("�����߻�.. �ڵ�=[%#d].. %s", RGV_INFO->m_wErrCode, RGV_INFO->GetRgvErrorString());


		if(m_pDoc->m_pRgvInfo[0]->m_wErrCode == RGV_ERR_CODE_COMM_ERROR && m_pDoc->m_bRtvCpError[0] == TRUE)
			strTemp.Format("�ڵ�=[%d].. %s", 999, "RTV#1 [RTV#1 ���� CP19 OFF]. ��ŵ���");

		if(m_pDoc->m_pRgvInfo[1]->m_wErrCode == RGV_ERR_CODE_COMM_ERROR && m_pDoc->m_bRtvCpError[1] == TRUE)
			strTemp.Format("�ڵ�=[%d].. %s", 999, "RTV#2 [RTV#2 ���� CP20 OFF]. ��ŵ���");

		SET(IDC_EDIT_DIAGNOSIS, strTemp);
		return;
	}

    if (RGV_INFO->m_ucMode != RGV_MODE_AUTO)
	{
        SET(IDC_EDIT_DIAGNOSIS, "RTV�� ���� �ڵ���� � ���°� �ƴմϴ�.! Ȯ���Ͻʽÿ�..");
        return;
    }

	if (RGV_INFO->m_ucActive == RGV_STOP) {
        SET(IDC_EDIT_DIAGNOSIS, "RTV ����� STOP ����.  Ȯ���Ͻʽÿ�..");
        return;
    }

    if (RGV_INFO->m_bInvoke) 
	{
        if (RGV_INFO->m_ucStatus == RGV_STA_WAIT || RGV_INFO->m_ucStatus == RGV_STA_IDLE)
		{
	        SET(IDC_EDIT_DIAGNOSIS, "�۾� ���¸� Ȯ�� �� �Ϸ� �Ǵ� �����Ͻʽÿ�..");
            return;
        }
        if (RGV_INFO->m_ucStatus == RGV_STA_MOVE)
		{
			//m_btnDiagnosis.SetTextColor(RGB(128, 0, 255));
	        SET(IDC_EDIT_DIAGNOSIS, "RTV �۾���.. ��� ��ٸ��ʽÿ�..");
            return;
        }
    } 
	else 
	{
        if (RGV_INFO->m_ucProdLoad == RGV_PROD_LOAD)
		{
	        SET(IDC_EDIT_DIAGNOSIS, "RTV�� ȭ���� ����.. �������� ó��..");
            return;
        }

        if (RGV_INFO->m_ucStatus == RGV_STA_MOVE)
		{
			//m_btnDiagnosis.SetTextColor(RGB(128, 0, 255));
	        SET(IDC_EDIT_DIAGNOSIS, "RTV �̵���.. ��/��� �۾��� �����ϴ�..");
            return;
        }

		static BOOL bStoreCheck = TRUE;
        if (RGV_INFO->m_ucStatus == RGV_STA_WAIT || RGV_INFO->m_ucStatus == RGV_STA_IDLE)
		{
			if (bStoreCheck)
			{
				bStoreCheck = FALSE;
				if (RGV_INFO->m_bStoreSuspend)
				{
			        SET(IDC_EDIT_DIAGNOSIS, "RTV �۾� �Ͻ� ���� ���..");
					return;
				}

		        SET(IDC_EDIT_DIAGNOSIS, "������۾� �����..");
                return;
            } 
			else 
			{
				bStoreCheck = TRUE;
				if (RGV_INFO->m_bRetrieveSuspend)
				{
			        SET(IDC_EDIT_DIAGNOSIS, "Door Open �� ȭ���������� ���� �� ��� ���� ���..");
					return;
				}

		        SET(IDC_EDIT_DIAGNOSIS, "��� ���� ��� ����..");
                return;
            }
		}
	}

	SET(IDC_EDIT_DIAGNOSIS, "�� ��Ȳ�� �Ǵ��� �� ����..");
}

void CRgvDlg::OnButtonManual() 
{
	CRgvManualDlg ManualDlg(m_pDoc, m_nID, m_nWareHouse, m_strCaption);
	ManualDlg.DoModal();
}

void CRgvDlg::OnCheckStore() 
{
	RGV_INFO->m_bStoreSuspend = !RGV_INFO->m_bStoreSuspend;
	RGV_INFO->m_bModified = TRUE;	
}

void CRgvDlg::OnCheckRetrieve() 
{
	RGV_INFO->m_bRetrieveSuspend = !RGV_INFO->m_bRetrieveSuspend;
	RGV_INFO->m_bModified = TRUE;	
}

void CRgvDlg::OnButtonComplete() 
{
	if (!m_pDoc->m_pRgvInfo[m_nID]->m_bInvoke) 
	{
		AfxMessageBox("RTV ���� Ȯ�� �ٶ�..\n���� RGV�� ���� ���� �۾��� �����ϴ�!");
		return;
	}

	if ( RGV_INFO->m_ucStatus != RGV_STA_WAIT && RGV_INFO->m_ucStatus != RGV_STA_IDLE) 
	{
		AfxMessageBox("RTV ���� Ȯ�� �ٶ�..\n���� RGV�� ��� ���°� �ƴմϴ�.. !");
		return;
	}

	if ( RGV_INFO->m_ucProdLoad == RGV_PROD_LOAD )
	{
		AfxMessageBox("RTV ���� Ȯ�� �ٶ�..  ���� RGV�� ȭ���� ����� ���� �Դϴ�.. !");
		return;
	}

	if (AfxMessageBox("�� �۾��� ���� �Ϸ� �Ͻðڽ��ϱ�?\n\n���� : RTV�� ȭ���� ������ġ�� �������� ��ġ��Ű�� �����Ϸ� �Ͻʽÿ�",	MB_OKCANCEL) == IDCANCEL)
		return ;

/*	int nTrackNum = m_pDoc->m_pRgvInfo[m_nID]->m_nDestTrack;
	if (m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_bRetHomeStandReady)
	{
		AfxMessageBox("RTV�� ȭ���� ������ġ�� �������� ��ġ ��Ű�� �����Ϸ� �Ͻʽÿ�");
		return;
	}
*/
	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.nCommand = RGV_CMD_COMPLETE;
	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.bModified = TRUE;
	RGV_ACTION(m_nID);
}

void CRgvDlg::OnButtonCancel() 
{
	if (AfxMessageBox("�� �۾��� ���� �Ͻðڽ��ϱ�?", MB_OKCANCEL) == IDCANCEL)
		return ;

//	if ( RGV_INFO->m_ucStatus != RGV_STA_WAIT && RGV_INFO->m_ucStatus != RGV_STA_IDLE) 
//	{
//		AfxMessageBox("RTV ���� Ȯ�� �ٶ�..\n���� RGV�� ��� ���°� �ƴմϴ�.. !");
//		return;
//	}

	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.nCommand = RGV_CMD_CANCEL;
	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.bModified = TRUE;
	RGV_ACTION(m_nID);
}

void CRgvDlg::OnButtonEstop() 
{
	if (AfxMessageBox("������� ���ø� �����ڽ��ϱ�?", MB_OKCANCEL) == IDCANCEL)
		return ;

	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.nCommand = RGV_CMD_ESTOP;
	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.bModified = TRUE;
	RGV_ACTION(m_nID);	
}

void CRgvDlg::OnButtonStop() 
{
	if (AfxMessageBox("���� ���ø� �����ڽ��ϱ�?", MB_OKCANCEL) == IDCANCEL)
		return ;

	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.nCommand = RGV_CMD_STOP;
	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.bModified = TRUE;
	RGV_ACTION(m_nID);	
}

void CRgvDlg::OnButtonActive() 
{
	if (AfxMessageBox("Active ���ø� �����ڽ��ϱ�?\n\n���忡 ����� ������ Ȯ����..", MB_OKCANCEL) == IDCANCEL)
		return ;

	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.nCommand = RGV_CMD_ACTIVE;
	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.bModified = TRUE;
	RGV_ACTION(m_nID);	
}

void CRgvDlg::OnButtonReset() 
{
	if(m_pDoc->m_pRgvInfo[m_nID]->m_wErrCode == 3 || m_pDoc->m_pRgvInfo[m_nID]->m_wErrCode == 5)
	{
		//if(m_pDoc->m_bSafetyError[m_nID])
		if(m_pDoc->m_bSafetyError[0] || m_pDoc->m_bSafetyError[1])
		{
			AfxMessageBox("Door�� ���� �ֽ��ϴ�! RTV ��������ÿ� Door�� ���� ������ ���� ������ �ȵ˴ϴ�!");
				return ;
		}
	}

	if (AfxMessageBox("���� ���� ���ø� �����ڽ��ϱ�?", MB_OKCANCEL) == IDCANCEL)
		return ;

	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.nCommand = RGV_CMD_RESET;
	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.bModified = TRUE;
	RGV_ACTION(m_nID);	
}

void CRgvDlg::OnButtonCallToHome() 
{
	if (RGV_INFO->m_bInvoke) 
	{
		AfxMessageBox("RTV ���� Ȯ�� �ٶ�..\nRTV�� �۾��� ���� ���Դϴ�!");
		return;
	}

	if (RGV_INFO->m_ucStatus == RGV_STA_ERROR) 
	{
		AfxMessageBox("RTV ���� Ȯ�� �ٶ�..\nRTV�� Error �����Դϴ�..! ���� ���� ��ġ �Ͻʽÿ�");
		return;
	}


	if ( RGV_INFO->m_ucStatus != RGV_STA_WAIT && RGV_INFO->m_ucStatus != RGV_STA_IDLE) 
	{
		AfxMessageBox("RTV ���� Ȯ�� �ٶ�..\n���� RTV�� ��� ���°� �ƴմϴ�.. ������ ������!");
		return;
	}

	if (AfxMessageBox("Ȩ���� ���ø� �����ڽ��ϱ�?", MB_OKCANCEL) == IDCANCEL)
		return ;

	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.nCommand = RGV_CMD_CALL_TO_HOME;
	m_pDoc->m_RgvThreadInfo[m_nID].m_RgvMsg.bModified = TRUE;
	RGV_ACTION(m_nID);
}

void CRgvDlg::OnOK() 
{
	KillTimer(m_nTimerID);
	
	CDialog::OnOK();
}

