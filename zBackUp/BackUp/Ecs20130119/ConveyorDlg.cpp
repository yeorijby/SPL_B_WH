// ConveyorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "ConveyorDlg.h"
#include "EcsDoc.h"
#include "ManualDlg.h"
#include "Lib.h"
#include "PasswordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConveyorDlg dialog


CConveyorDlg::CConveyorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConveyorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConveyorDlg)
	m_strLuggNum = _T("");
	m_strBatchNum = _T("");
	//}}AFX_DATA_INIT
//	m_bCopied = FALSE;
}


void CConveyorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConveyorDlg)
	DDX_Text(pDX, IDC_EDIT_LUGG_NUM, m_strLuggNum);
	DDV_MaxChars(pDX, m_strLuggNum, 4);
	DDX_Text(pDX, IDC_EDIT_BATCH_NUM, m_strBatchNum);
	DDV_MaxChars(pDX, m_strBatchNum, 4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConveyorDlg, CDialog)
	//{{AFX_MSG_MAP(CConveyorDlg)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_STO, OnButtonManualSto)
	ON_CBN_SELCHANGE(IDC_COMBO_JOB_TYPE, OnSelchangeComboJobType)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, OnButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_COPY, OnButtonCopy)
	ON_BN_CLICKED(IDC_BUTTON_PASTE, OnButtonPaste)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_CUT, OnButtonCut)
	ON_BN_CLICKED(IDC_BUTTON_LAST_PALLET, OnButtonLastPallet)
	ON_BN_CLICKED(IDC_BUTTON_LAST_PALLET_RESET, OnButtonLastPalletReset)
	ON_BN_CLICKED(IDC_BUTTON_REWRITE, OnButtonRewrite)
	ON_BN_CLICKED(IDC_BUTTON_CV_STATUS, OnButtonCvStatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConveyorDlg message handlers

//#define CV_PLC_NUM		( m_nID < CV_1_TRACK_CNT  ? 0 : (m_nID < (CV_2_TRACK_CNT+CV_2_START_TRACK) ? 1 : (m_nID < (CV_3_TRACK_CNT+CV_3_START_TRACK) ? 2 : (m_nID < (CV_4_TRACK_CNT+CV_4_START_TRACK) ? 3 : (m_nID < (CV_5_TRACK_CNT+CV_5_START_TRACK) ? 4 : (m_nID < (CV_6_TRACK_CNT+CV_6_START_TRACK) ? 5 : 6))))))
#define	CV_PLC_NUM	CLib::GetPlcNumByTrack(m_nID)
#define TRACK_MSG	m_pDoc->m_ConveyorThreadInfo[CV_PLC_NUM].m_ConveyorMsg

void CConveyorDlg::OnButtonManualSto() 
{
	if (m_nID > CV_TRACKING_ED_STO)
	{
		AfxMessageBox("반자동 입고를 할 수 없는 구간입니다..");
		return;
	}
	if (m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLuggNum < 1 ||
		m_pDoc->m_ConveyorTrackInfo[m_nID].m_nJobType < 1)
	{
		AfxMessageBox("먼저 작업번호, 작업구분, 출발위치, 도착위치를 생성하십시요..");
		return;
	}

#ifdef OPT_PASSWORD_USE
	CPasswordDlg PasswordDlg;
	PasswordDlg.m_pDoc = m_pDoc;
	if (PasswordDlg.DoModal() != IDOK) return;
	if ( PasswordDlg.m_strPassword != m_pDoc->m_pConfig->m_strPassword )
	{
		AfxMessageBox("PASSWORD 확인 바람..");
		return;
	}
#endif

	CManualDlg ManualDlg;
	
	ManualDlg.m_pDoc = m_pDoc;
	ManualDlg.m_nTrackNum = m_nID;
	ManualDlg.m_nLuggNum  = m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLuggNum;
	ManualDlg.m_nJobType  = m_pDoc->m_ConveyorTrackInfo[m_nID].m_nJobType;
	ManualDlg.DoModal();
}

BOOL CConveyorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (!m_pDoc->m_ConveyorMsg.bCopy)
		GetDlgItem(IDC_BUTTON_PASTE)->EnableWindow(FALSE);

	CString strTemp;
	strTemp.Format(" #%d", m_nID + 1);
	GetDlgItem(IDC_EDIT_TRACK_NUM)->SetWindowText(strTemp);

	if(m_nID < CV_1_TRACK_CNT)
	{
		GetDlgItem(IDC_BUTTON_LAST_PALLET)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_LAST_PALLET_RESET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TRACK_LAST)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_REWRITE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_STARTNATION)->EnableWindow(FALSE);
	}

	if(m_nID < CV_7_START_TRACK)
		GetDlgItem(IDC_EDIT_LUGG_NUM2)->EnableWindow(FALSE);

	if(m_nID > CV_1_TRACK_CNT)
		GetDlgItem(IDC_COMBO_LINE)->EnableWindow(FALSE);

	if(m_nID >= CV_7_START_TRACK)
		GetDlgItem(IDC_COMBO_STARTNATION)->EnableWindow(FALSE);

    
//	if(m_nID != 329) 		GetDlgItem(IDC_BUTTON_REWRITE)->EnableWindow(FALSE);

	strTemp.Format("%04d", m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLuggNum);
	GetDlgItem(IDC_EDIT_LUGG_NUM)->SetWindowText(strTemp);

	strTemp.Format("%04d", m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLuggNum2);
	GetDlgItem(IDC_EDIT_LUGG_NUM2)->SetWindowText(strTemp);


	strTemp.Format("%d", m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLastPallet);
	GetDlgItem(IDC_EDIT_TRACK_LAST)->SetWindowText(strTemp);

	CJobItem JobItem;

	CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_JOB_TYPE);
/*	for (int i=0; i < JOB_TYPE_CNT; i++)
		pComboBox->InsertString(i, JobItem.GetType(i));
*/
	pComboBox->InsertString(0, "UNIT 입고");
	pComboBox->InsertString(1, "UNIT 출고");
	pComboBox->InsertString(2, "외주창고 이동");
	pComboBox->InsertString(3, "반자동 입고");
	pComboBox->InsertString(4, "반자동 출고");
	pComboBox->InsertString(5, "마지막 Pallet");

	int nJobType = m_pDoc->m_ConveyorTrackInfo[m_nID].m_nJobType;

	switch(nJobType)
	{
	case  1:  pComboBox->SetCurSel(0); break;
	case  2:  pComboBox->SetCurSel(1); break;
	case  6:  pComboBox->SetCurSel(2); break;
	case  10:  pComboBox->SetCurSel(3); break;
	//case  7:  pComboBox->SetCurSel(3); break;
	case  4:  pComboBox->SetCurSel(4); break;
	case  5:  pComboBox->SetCurSel(5); break;
	}

	pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_LINE);
	if(m_nID < 100)
	{
		pComboBox->InsertString(0, "A Line");
		pComboBox->InsertString(1, "B Line");

		pComboBox->SetCurSel(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nStartPos);
	}

	pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_STARTNATION);
	if(m_nID < 100)
	{
		pComboBox->InsertString(0, "생산입고대");
		//pComboBox->InsertString(1, "외주입고대");

		pComboBox->SetCurSel(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nStartPos-1);
	}
	else if(m_nID < 700)
	{
		pComboBox->InsertString(0, "S/C#1 H/S");
		pComboBox->InsertString(1, "S/C#2 H/S");
		pComboBox->InsertString(2, "S/C#3 H/S");
		pComboBox->InsertString(3, "S/C#4 H/S");
		pComboBox->InsertString(4, "S/C#5 H/S");
		pComboBox->InsertString(5, "S/C#6 H/S");

		pComboBox->SetCurSel(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nStartPos-1);
	}
	else
	{
		pComboBox->InsertString(0, "생산입고대");
		pComboBox->InsertString(1, "수동입고대");

		pComboBox->SetCurSel(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nStartPos-1);
	}

	pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_DESTINATION);
		
	if(m_nID < 100)
	{
		pComboBox->InsertString(0, "S/C#1 H/S");
		pComboBox->InsertString(1, "S/C#2 H/S");
		pComboBox->InsertString(2, "S/C#3 H/S");
		pComboBox->InsertString(3, "S/C#4 H/S");
		pComboBox->InsertString(4, "S/C#5 H/S");
		pComboBox->InsertString(5, "S/C#6 H/S");
		pComboBox->InsertString(6, "외주출고대");
		pComboBox->InsertString(7, "Buffer #1");
		pComboBox->InsertString(8, "Buffer #2");
		pComboBox->InsertString(9, "Buffer #3");
		pComboBox->InsertString(10, "Buffer #4");

		pComboBox->SetCurSel(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nDestPos-1);

/*		CMoveJobItem* pMoveJobItem = m_pDoc->m_pMoveJob->Find(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLuggNum);

		if (pMoveJobItem != NULL)
		{
			if(pMoveJobItem->GetPattern() == JOB_PATTERN_MOVE)
			{
				pComboBox->InsertString(0, "Buffer #1");
				pComboBox->InsertString(1, "Buffer #2");
				pComboBox->InsertString(2, "Buffer #3");
				pComboBox->InsertString(3, "Buffer #4");

				pComboBox->SetCurSel(pMoveJobItem->m_nLineNum-1);
			}
		}
*/
	}
	else if(m_nID < 700)
	{
		pComboBox->InsertString(0, "출하분류대#1");
		pComboBox->InsertString(1, "출하분류대#2");
		pComboBox->InsertString(2, "출하분류대#3");

		pComboBox->SetCurSel(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nDestPos-1);
	}
	else if(m_nID != 745 && m_nID < 789)
	{
		pComboBox->InsertString(0, "LINE #1");
		pComboBox->InsertString(1, "LINE #2");
		pComboBox->InsertString(2, "LINE #3");
		pComboBox->InsertString(3, "LINE #4");
		pComboBox->InsertString(4, "LINE #5");
		pComboBox->InsertString(5, "LINE #6");
		pComboBox->InsertString(6, "LINE #7");
		pComboBox->InsertString(7, "LINE #8");
		pComboBox->InsertString(8, "LINE #9");
		pComboBox->InsertString(9, "LINE #10");
		pComboBox->InsertString(10, "LINE #11");

		pComboBox->SetCurSel(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nDestPos-1);
	}
	else if(m_nID >= 789 && m_nID <= 807)
	{
		pComboBox->InsertString(0, "A LINE");
		pComboBox->InsertString(1, "B LINE");

		pComboBox->SetCurSel(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nDestPos-21);
	}
	else if(m_nID == 745 || (m_nID >= 823 && m_nID <= 836))
	{

		strTemp="";
		CMoveJobItem* pMoveJobItem = m_pDoc->m_pMoveJob->Find(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLuggNum);
		if (pMoveJobItem != NULL)	
		{
			strTemp.Format("Buffer#%d->", pMoveJobItem->m_nLineNum);
		}
		strTemp.Format("%sStacking", strTemp);

		pComboBox->InsertString(0, "Buffer #1");
		pComboBox->InsertString(1, "Buffer #2");
		pComboBox->InsertString(2, "Buffer #3");
		pComboBox->InsertString(3, strTemp);
		pComboBox->InsertString(4, "Buffer #4");

		pComboBox->SetCurSel(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nDestPos-8);
	}
	else
	{
		pComboBox->InsertString(0, "파렛트창고 입고대");
		pComboBox->InsertString(1, "수동 랩핑대");
		pComboBox->InsertString(2, "파렛트분배(P/D)");
		pComboBox->InsertString(3, "P/D 대기대");

		pComboBox->SetCurSel(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nDestPos-3);
	}


	if(m_nID < 712 || m_nID > 807)
	{
		GetDlgItem(IDC_COMBO_RTV_STATUS)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CV_STATUS)->EnableWindow(FALSE); 
	}

	CComboBox* pComboBoxStatus = (CComboBox *)GetDlgItem(IDC_COMBO_RTV_STATUS);
	pComboBoxStatus->InsertString(0, "RTV 구동 대기");
	pComboBoxStatus->InsertString(1, "C/V 구동중");
	pComboBoxStatus->SetCurSel(-1);

	CMoveJobItem* pMoveJobItem = m_pDoc->m_pMoveJob->Find(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLuggNum);
	if (pMoveJobItem != NULL)
	{
		if(pMoveJobItem->m_nStatus == JOB_STA_MOVE_RGV_OPER_REQUEST)
			pComboBoxStatus->SetCurSel(0);

		if(pMoveJobItem->m_nStatus == JOB_STA_MOVE_CV_OPER_INVOKE)
			pComboBoxStatus->SetCurSel(1);
	}

	if(m_nID >= 700)
	{
		strTemp = (m_pDoc->m_ConveyorTrackInfo[m_nID].m_bOpMode == TRUE) ? "자동" : "수동"; 
		SET(IDC_EDIT_OP_MODE, strTemp);
		strTemp = (m_pDoc->m_ConveyorTrackInfo[m_nID].m_bPltSensor == TRUE) ? "있음" : "없음"; 
		SET(IDC_EDIT_PLT_SENSOR, strTemp);

		strTemp = (m_pDoc->m_ConveyorTrackInfo[m_nID].m_nComplete == 1) ? "1" : "0"; 
		SET(IDC_EDIT_PLT_LAST, strTemp);
	}
	else
	{
		SET(IDC_EDIT_OP_MODE, "");
		SET(IDC_EDIT_PLT_SENSOR, "");
	}

	strTemp = (m_pDoc->m_ConveyorTrackInfo[m_nID].m_bStoHomeStandReady == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_STO_HS, strTemp);

	strTemp = (m_pDoc->m_ConveyorTrackInfo[m_nID].m_bRetHomeStandReady == TRUE) ? "ON" : "OFF"; 
	SET(IDC_EDIT_RET_HS, strTemp);

	CJobItem* pJobItem = m_pDoc->m_pJob->Find(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLuggNum);

	if (pJobItem != NULL)
	{
		strTemp.Format("%d", pJobItem->m_nBatchNo);
		GetDlgItem(IDC_EDIT_BATCH_NUM)->SetWindowText(strTemp);

		strTemp.Format("%d", pJobItem->m_nPalletNo);
		GetDlgItem(IDC_EDIT_PALLET_NUM)->SetWindowText(strTemp);

		strTemp.Format("%d", pJobItem->m_nLevelNo);
		GetDlgItem(IDC_EDIT_LEVEL_NUM)->SetWindowText(strTemp);

		SET(IDC_EDIT_LOC, CLib::ConvertLocationToCustom(pJobItem->m_strLocation));
		SET(IDC_EDIT_PRODUCT, pJobItem->m_strProductID);
		SET(IDC_EDIT_PRODUCT_NAME,pJobItem->m_strGrade);
	}

	if(m_nID < 100 || m_nID >= 700)
	{
		CMoveJobItem* pMoveJobItem = m_pDoc->m_pMoveJob->Find(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLuggNum);

		if (pMoveJobItem != NULL)
		{
			//strTemp.Format("%d", pMoveJobItem->m_nBatchNo);
			//GetDlgItem(IDC_EDIT_BATCH_NUM)->SetWindowText(strTemp);

			strTemp.Format("%d", pMoveJobItem->m_nPalletNo);
			GetDlgItem(IDC_EDIT_PALLET_NUM)->SetWindowText(strTemp);

			strTemp.Format("%d", pMoveJobItem->m_nLevelNo);
			GetDlgItem(IDC_EDIT_LEVEL_NUM)->SetWindowText(strTemp);

			SET(IDC_EDIT_LOC, CLib::ConvertLocationToCustom(pMoveJobItem->m_strLocation));
			SET(IDC_EDIT_PRODUCT, pMoveJobItem->m_strProductID);
			SET(IDC_EDIT_PRODUCT_NAME,pMoveJobItem->m_strGrade);
		}
	}
	
	if (m_pDoc->m_ConveyorTrackInfo[m_nID].m_bOverTimeErr)
		SET(IDC_EDIT_CV_STATUS, " OverTime Error");
	else if (m_pDoc->m_ConveyorTrackInfo[m_nID].m_bOverLoadErr)
		SET(IDC_EDIT_CV_STATUS, " OverLoad Error");
	else if(m_pDoc->m_ConveyorTrackInfo[m_nID].m_bBuffTrouble)
		SET(IDC_EDIT_CV_STATUS, " 버퍼Line 수동 및 고장");
	else
		SET(IDC_EDIT_CV_STATUS, " Normal");

	strTemp.Format("%s Code:[%d번] ", CLib::GetCvErrorCode(m_pDoc->m_ConveyorTrackInfo[m_nID].m_wErrorCode), m_pDoc->m_ConveyorTrackInfo[m_nID].m_wErrorCode);
	//strTemp = CLib::GetCvErrorCode(m_pDoc->m_ConveyorTrackInfo[m_nID].m_wErrorCode);
	if(m_pDoc->m_ConveyorTrackInfo[m_nID].m_wErrorCode == 0)
	   strTemp = "";

	SET(IDC_EDIT_ERROR_CODE, strTemp);

	return TRUE;  
}

void CConveyorDlg::OnSelchangeComboJobType() 
{
	
}

//#define CV_PLC_NUM		( m_nID < CV_1_TRACK_CNT  ? 0 : (m_nID < (CV_2_TRACK_CNT+CV_2_START_TRACK) ? 1 : 2))
//#define CV_PLC_NUM		( m_nID < CV_1_TRACK_CNT  ? 0 : (m_nID < (CV_2_TRACK_CNT+CV_2_START_TRACK) ? 1 : (m_nID < (CV_3_TRACK_CNT+CV_3_START_TRACK) ? 2 : 3)))


void CConveyorDlg::OnButtonWrite() 
{
/*
	CString strTemp;
	if( m_pDoc->m_pConveyorSocket[CV_PLC_NUM] == NULL )
	{
		strTemp.Format("PLC#%d 서버와 연결이 안된 상태 입니다.. 잠시후 다시 시도 하세요", CV_PLC_NUM+1);
		AfxMessageBox(strTemp);
		return;
	}

	if (TRACK_INFO.bModified)
	{
		AfxMessageBox("이전 지시작업을 실행 중입니다. 잠시 후에 다시 시도하십시요...");
		return;
	}
*/
	//int nTemp = CV_PLC_NUM;

    CMoveJobItem* pMoveJobItem=NULL;
	if (AfxMessageBox("트랙정보를 변경하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return ;

	GetDisplayTrackInfo();

	TRACK_MSG.nTrackNum = m_nID;
	TRACK_MSG.nLuggNum  = m_pDoc->m_ConveyorMsg.nLuggNum;
	TRACK_MSG.nLuggNum2  = m_pDoc->m_ConveyorMsg.nLuggNum2;
	TRACK_MSG.nJobType  = m_pDoc->m_ConveyorMsg.nJobType;
	TRACK_MSG.nStartPos  = m_pDoc->m_ConveyorMsg.nStartPos;
	TRACK_MSG.nDestPos  = m_pDoc->m_ConveyorMsg.nDestPos;
	TRACK_MSG.nLastPallet  = 0;
	TRACK_MSG.nComplete = 0;
	TRACK_MSG.nSize = 0;


/*	if(m_nID < 100)
	{
		pMoveJobItem = m_pDoc->m_pMoveJob->Find(m_pDoc->m_ConveyorMsg.nLuggNum);
		if (pMoveJobItem != NULL)
		{
			CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_DESTINATION);
			pMoveJobItem->m_nLineNum = pComboBox->GetCurSel()+1;

			TRACK_MSG.nDestPos  = pComboBox->GetCurSel()+8;
		}
	}
	else if(m_nID >= 700 && m_nID < 789)
	{
		pMoveJobItem = m_pDoc->m_pMoveJob->Find(m_pDoc->m_ConveyorMsg.nLuggNum);
		if (pMoveJobItem != NULL)
		{
			CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_DESTINATION);
			//pMoveJobItem->m_nLineNum = pComboBox->GetCurSel();
		}

		pMoveJobItem = m_pDoc->m_pMoveJob->Find(m_pDoc->m_ConveyorMsg.nLuggNum2);
		if (pMoveJobItem != NULL)
		{
			CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_DESTINATION);
			//pMoveJobItem->m_nLineNum = pComboBox->GetCurSel();
		}
	}
*/
	TRACK_MSG.bModified = TRUE;

	int nTest = CV_PLC_NUM;

   BOOL bTest = m_pDoc->m_ConveyorThreadInfo[CV_PLC_NUM].m_ConveyorMsg.bModified;

	CV_ACTION(CV_PLC_NUM);

	CString strLog;
	strLog.Format("CConveyorDlg::OnButtonWrite.. TrackNum=[%d], Lugg1=[%d], Lugg2=[%d], Start =[%d], Dest=[%d]",
		TRACK_MSG.nTrackNum + 1, TRACK_MSG.nLuggNum, TRACK_MSG.nLuggNum2, TRACK_MSG.nStartPos, TRACK_MSG.nDestPos);
	m_pDoc->m_pLog->Event(LOG_POS_CV, TRACK_MSG.nLuggNum, strLog);
}

void CConveyorDlg::OnButtonPaste() 
{
	CMoveJobItem* pMoveJobItem=NULL;

	if (AfxMessageBox("복사된 트랙정보를 붙여넣으시겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return ;

	TRACK_MSG.nTrackNum = m_nID;
	TRACK_MSG.nLuggNum  = m_pDoc->m_ConveyorMsg.nLuggNum;
	TRACK_MSG.nLuggNum2  = m_pDoc->m_ConveyorMsg.nLuggNum2;
	TRACK_MSG.nJobType  = m_pDoc->m_ConveyorMsg.nJobType;
	TRACK_MSG.nStartPos  = m_pDoc->m_ConveyorMsg.nStartPos;
	TRACK_MSG.nDestPos  = m_pDoc->m_ConveyorMsg.nDestPos;
	TRACK_MSG.nLastPallet  = m_pDoc->m_ConveyorMsg.nLastPallet;
	TRACK_MSG.nComplete = m_pDoc->m_ConveyorMsg.nComplete;
	TRACK_MSG.nSize = 0;
	
	CString strTemp;
	strTemp.Format("%d", TRACK_MSG.nLuggNum);
	SET(IDC_EDIT_LUGG_NUM, strTemp);

	strTemp.Format("%d", TRACK_MSG.nLuggNum2);
	SET(IDC_EDIT_LUGG_NUM2, strTemp);

	int nJobType = TRACK_MSG.nJobType;

/*	if(m_nID < 100)
	{
		pMoveJobItem = m_pDoc->m_pMoveJob->Find(m_pDoc->m_ConveyorMsg.nLuggNum);
		if (pMoveJobItem != NULL)
			TRACK_MSG.nDestPos  = 7;
	}
	else if(m_nID >= 700 && m_nID < 789)
	{
		pMoveJobItem = m_pDoc->m_pMoveJob->Find(m_pDoc->m_ConveyorMsg.nLuggNum);
		if (pMoveJobItem != NULL)
		{
			int nCurSel = pMoveJobItem->m_nLineNum;
			CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_DESTINATION);
			pComboBox->SetCurSel(nCurSel);
		}

		pMoveJobItem = m_pDoc->m_pMoveJob->Find(m_pDoc->m_ConveyorMsg.nLuggNum2);
		if (pMoveJobItem != NULL)
		{
			int nCurSel = pMoveJobItem->m_nLineNum;
			CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_DESTINATION);
			pComboBox->SetCurSel(nCurSel);
		}
	}
*/

	CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_JOB_TYPE);
	switch(nJobType)
	{
	case  1:  pComboBox->SetCurSel(0); break;
	case  2:  pComboBox->SetCurSel(1); break;
	case  6:  pComboBox->SetCurSel(2); break;
	case  7:  pComboBox->SetCurSel(3); break;
	case  8:  pComboBox->SetCurSel(4); break;
	case  5:  pComboBox->SetCurSel(5); break;
	}

	pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_STARTNATION);
	pComboBox->SetCurSel(TRACK_MSG.nStartPos - 1);

	pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_DESTINATION);
	pComboBox->SetCurSel(TRACK_MSG.nDestPos - 1);
	
	if (m_nID > CV_TRACKING_ED_STO)
	{
		strTemp.Format("%d", TRACK_MSG.nBatchNum);
		SET(IDC_EDIT_BATCH_NUM, strTemp);
	}

	TRACK_MSG.bModified = TRUE;

	CV_ACTION(CV_PLC_NUM);

	//m_bCopied = FALSE;
	m_pDoc->m_ConveyorMsg.bCopy = FALSE;
	GetDlgItem(IDC_BUTTON_PASTE)->EnableWindow(FALSE);
}

void CConveyorDlg::OnButtonDelete() 
{
/*
	CString strTemp;
	if( m_pDoc->m_pConveyorSocket[CV_PLC_NUM] == NULL )
	{
		strTemp.Format("PLC#%d 서버와 연결이 안된 상태 입니다.. 잠시후 다시 시도 하세요", CV_PLC_NUM+1);
		AfxMessageBox(strTemp);
		return;
	}

	if (TRACK_INFO.bModified)
	{
		AfxMessageBox("이전 지시작업을 실행 중입니다. 잠시 후에 다시 시도하십시요...");
		return;
	}
*/
	if (AfxMessageBox("트랙정보를 삭제하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return ;

	TRACK_MSG.nTrackNum = m_nID;
	TRACK_MSG.nLuggNum  = 0;
	TRACK_MSG.nLuggNum2 = 0;
	TRACK_MSG.nJobType  = 0;
	TRACK_MSG.nStartPos = 0;
	TRACK_MSG.nDestPos  = 0;
	TRACK_MSG.nLastPallet = 0;
	TRACK_MSG.nComplete = 0;
	TRACK_MSG.nSize = 0;

	CString strTemp;
	strTemp.Format("%d", TRACK_MSG.nLuggNum);
	SET(IDC_EDIT_LUGG_NUM, strTemp);

	strTemp.Format("%d", TRACK_MSG.nLuggNum2);
	SET(IDC_EDIT_LUGG_NUM2, strTemp);
	
	CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_JOB_TYPE);
	pComboBox->SetCurSel(/*TRACK_MSG.nJobType*/-1);

	pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_STARTNATION);
	pComboBox->SetCurSel(/*TRACK_MSG.nStartPos*/ - 1);

	pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_DESTINATION);
	pComboBox->SetCurSel(/*TRACK_MSG.nDestPos*/ - 1);
	
	TRACK_MSG.bModified = TRUE;

	CV_ACTION(CV_PLC_NUM);

}

void CConveyorDlg::OnButtonCut() 
{
	CMoveJobItem* pMoveJobItem=NULL;
/*
	CString strTemp;
	if( m_pDoc->m_pConveyorSocket[CV_PLC_NUM] == NULL )
	{
		strTemp.Format("PLC#%d 서버와 연결이 안된 상태 입니다.. 잠시후 다시 시도 하세요", CV_PLC_NUM+1);
		AfxMessageBox(strTemp);
		return;
	}

	if (TRACK_INFO.bModified)
	{
		AfxMessageBox("이전 지시작업을 실행 중입니다. 잠시 후에 다시 시도하십시요...");
		return;
	}
*/
	if (AfxMessageBox("트랙정보를 복사후 삭제하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return ;

	GetDisplayTrackInfo();
	
	TRACK_MSG.nTrackNum    = m_nID;
	TRACK_MSG.nLuggNum     = 0;
	TRACK_MSG.nLuggNum2    = 0;
	TRACK_MSG.nJobType     = 0;
	TRACK_MSG.nStartPos    = 0;
	TRACK_MSG.nDestPos     = 0;
	TRACK_MSG.nLastPallet  = 0;
	TRACK_MSG.nComplete = 0;
	TRACK_MSG.nSize     = 0;
	
	CString strTemp;
	strTemp.Format("%d", TRACK_MSG.nLuggNum);
	SET(IDC_EDIT_LUGG_NUM, strTemp);

	strTemp.Format("%d", TRACK_MSG.nLuggNum2);
	SET(IDC_EDIT_LUGG_NUM2, strTemp);
	
	CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_JOB_TYPE);
	pComboBox->SetCurSel(/*TRACK_MSG.nJobType*/-1);

	pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_STARTNATION);
	pComboBox->SetCurSel(/*TRACK_MSG.nStartPos*/ - 1);

	pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_DESTINATION);
	pComboBox->SetCurSel(/*TRACK_MSG.nDestPos*/ - 1);

/*	if(m_nID < 100)
	{
		pMoveJobItem = m_pDoc->m_pMoveJob->Find(m_pDoc->m_ConveyorMsg.nLuggNum);
		if (pMoveJobItem != NULL)
			TRACK_MSG.nDestPos  = 7;
	}
	else if(m_nID >= 700 && m_nID < 789)
	{
		pMoveJobItem = m_pDoc->m_pMoveJob->Find(m_pDoc->m_ConveyorMsg.nLuggNum);
		if (pMoveJobItem != NULL)
		{
			CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_DESTINATION);
			pMoveJobItem->m_nLineNum = m_pDoc->m_ConveyorMsg.nDestPos-1;
		}

		pMoveJobItem = m_pDoc->m_pMoveJob->Find(m_pDoc->m_ConveyorMsg.nLuggNum2);
		if (pMoveJobItem != NULL)
		{
			CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_DESTINATION);
			pMoveJobItem->m_nLineNum = m_pDoc->m_ConveyorMsg.nDestPos-1;
		}
	}
*/
	TRACK_MSG.bModified = TRUE;

	CV_ACTION(CV_PLC_NUM);

	//m_bCopied = TRUE;
	m_pDoc->m_ConveyorMsg.bCopy = TRUE;
	GetDlgItem(IDC_BUTTON_PASTE)->EnableWindow(TRUE);
}

void CConveyorDlg::OnButtonCvStatus() 
{
	CString strLog;

	if (AfxMessageBox("CV 진행 상태를 변경 하시겠습니까? ", MB_OKCANCEL) == IDCANCEL)
		return ;

	CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_RTV_STATUS);
	int nPosition = pComboBox->GetCurSel()+1;

	static int nRtvTrack1[] = {718, 717, 716, 715, 714, 713};
	static int nRtvTrack2[] = {725, 724, 723, 722, 721, 720};
	static int nRtvTrack3[] = {732, 731, 730, 729, 728, 727};
	static int nRtvTrack4[] = {739, 738, 737, 736, 735, 734};
	static int nRtvTrack5[] = {745, 744, 743, 742, 741, 740};
	static int nRtvTrack6[] = {752, 751, 750, 749, 748, 747};
	static int nRtvTrack7[] = {759, 758, 757, 756, 755, 754};
	static int nRtvTrack8[] = {766, 765, 764, 763, 762, 761};
	static int nRtvTrack9[] = {773, 772, 771, 770, 769, 768};
	static int nRtvTrack10[] = {780, 779, 778, 777, 776, 775};
	static int nRtvTrack11[] = {787, 786, 785, 784, 783, 782};

	static int nRtvTrack12[] = {808, 807, 802, 803, 804, 805, 806};
	static int nRtvTrack13[] = {808, 807, 797, 798, 799, 800, 801};


	CMoveJobItem *pMoveJobItem = MOVEJOB->Find(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLuggNum);
	if (pMoveJobItem == NULL)
	{
		strLog.Format("CV에 해당하는 작업정보가 없습니다! 작업번호=[%d]", m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLuggNum);
		if (AfxMessageBox(strLog, MB_OKCANCEL) == IDCANCEL)
			return ;
	}

	for(int i=0; i<6; i++)
	{
		switch(m_nID+1)
		{
		case	718:
		case	717:
		case	716:
		case	715:
		case	714:
		case	713:
			{
				if(nPosition == 1)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack1[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack1[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

				if(nPosition == 2)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack1[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack1[i]-1].m_nLuggNum2, JOB_STA_MOVE_CV_OPER_INVOKE);
			}
			break;
		case	725:
		case	724:
		case	723:
		case	722:
		case	721:
		case	720:
			{
				if(nPosition == 1)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack2[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack2[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

				if(nPosition == 2)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack2[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack2[i]-1].m_nLuggNum2, JOB_STA_MOVE_CV_OPER_INVOKE);
			}
			break;
		case	732:
		case	731:
		case	730:
		case	729:
		case	728:
		case	727:
			{
				if(nPosition == 1)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack3[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack3[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

				if(nPosition == 2)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack3[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack3[i]-1].m_nLuggNum2, JOB_STA_MOVE_CV_OPER_INVOKE);
			}
			break;
		case	739:
		case	738:
		case	737:
		case	736:
		case	735:
		case	734:
			{
				if(nPosition == 1)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack4[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack4[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

				if(nPosition == 2)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack4[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack4[i]-1].m_nLuggNum2, JOB_STA_MOVE_CV_OPER_INVOKE);
			}
			break;
		case	745:
		case	744:
		case	743:
		case	742:
		case	741:
		case	740:
			{
				if(nPosition == 1)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack5[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack5[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

				if(nPosition == 2)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack5[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack5[i]-1].m_nLuggNum2, JOB_STA_MOVE_CV_OPER_INVOKE);
			}
			break;
		case	752:
		case	751:
		case	750:
		case	749:
		case	748:
		case	747:
			{
				if(nPosition == 1)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack6[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack6[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

				if(nPosition == 2)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack6[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack6[i]-1].m_nLuggNum2, JOB_STA_MOVE_CV_OPER_INVOKE);
			}
			break;
		case	759:
		case	758:
		case	757:
		case	756:
		case	755:
		case	754:
			{
				if(nPosition == 1)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack7[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack7[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

				if(nPosition == 2)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack7[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack7[i]-1].m_nLuggNum2, JOB_STA_MOVE_CV_OPER_INVOKE);
			}
			break;
		case	766:
		case	765:
		case	764:
		case	763:
		case	762:
		case	761:
			{
				if(nPosition == 1)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack8[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack8[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

				if(nPosition == 2)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack8[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack8[i]-1].m_nLuggNum2, JOB_STA_MOVE_CV_OPER_INVOKE);
			}
			break;
		case	773:
		case	772:
		case	771:
		case	770:
		case	769:
		case	768:
			{
				if(nPosition == 1)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack9[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack9[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

				if(nPosition == 2)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack9[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack9[i]-1].m_nLuggNum2, JOB_STA_MOVE_CV_OPER_INVOKE);
			}
			break;
		case	780:
		case	779:
		case	778:
		case	777:
		case	776:
		case	775:
			{
				if(nPosition == 1)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack10[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack10[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

				if(nPosition == 2)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack10[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack10[i]-1].m_nLuggNum2, JOB_STA_MOVE_CV_OPER_INVOKE);
			}
			break;
		case	787:
		case	786:
		case	785:
		case	784:
		case	783:
		case	782:
			{
				if(nPosition == 1)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack11[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack11[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

				if(nPosition == 2)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack11[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack11[i]-1].m_nLuggNum2, JOB_STA_MOVE_CV_OPER_INVOKE);
			}
			break;
/*		case	808:
		case	807:
		case	802:
		case	803:
		case	804:
		case	805:
		case	797:
		case	798:
		case	799:
		case	800:
			{
				if(nPosition == 1 && m_pDoc->m_ConveyorTrackInfo[nRtvTrack12[i]-1].m_nDestPos == 21)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack12[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack12[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

				if(nPosition == 2 && m_pDoc->m_ConveyorTrackInfo[nRtvTrack12[i]-1].m_nDestPos == 21)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack12[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack12[i]-1].m_nLuggNum2, JOB_STA_MOVE_CV_OPER_INVOKE);

				if(nPosition == 1 && m_pDoc->m_ConveyorTrackInfo[nRtvTrack13[i]-1].m_nDestPos == 22)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack13[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack13[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

				if(nPosition == 2 && m_pDoc->m_ConveyorTrackInfo[nRtvTrack13[i]-1].m_nDestPos == 22)
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack13[i]-1].m_nLuggNum, m_pDoc->m_ConveyorTrackInfo[nRtvTrack13[i]-1].m_nLuggNum2, JOB_STA_MOVE_CV_OPER_INVOKE);
			}
			break;
*/
		}
	}

	for( i=0; i<7; i++)
	{
		switch(m_nID+1)
		{
		case	808:
		case	807:
		case	802:
		case	803:
		case	804:
		case	806:
		case	805:
		case	797:
		case	798:
		case	799:
		case	800:
		case	801:
			{
				if(nPosition == 1 && m_pDoc->m_ConveyorTrackInfo[nRtvTrack12[i]-1].m_nDestPos == 21)
				{
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack12[i]-1].m_nLuggNum, 
						                m_pDoc->m_ConveyorTrackInfo[nRtvTrack12[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

					if(i == 6 && m_pDoc->m_ConveyorTrackInfo[795-1].m_nDestPos == 21 && m_pDoc->m_ConveyorTrackInfo[795-1].m_nComplete == 1)
						MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[795-1].m_nLuggNum, 0, JOB_STA_MOVE_RGV_OPER_REQUEST);
				
				}

				if(nPosition == 2 && m_pDoc->m_ConveyorTrackInfo[nRtvTrack12[i]-1].m_nDestPos == 21)
				{
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack12[i]-1].m_nLuggNum, 
					                    m_pDoc->m_ConveyorTrackInfo[nRtvTrack12[i]-1].m_nLuggNum2, JOB_STA_MOVE_CV_OPER_INVOKE);

					if(i == 6 && m_pDoc->m_ConveyorTrackInfo[795-1].m_nDestPos == 21 && m_pDoc->m_ConveyorTrackInfo[795-1].m_nComplete == 1)
						MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[795-1].m_nLuggNum, 0, JOB_STA_MOVE_CV_OPER_INVOKE);
				}

				if(nPosition == 1 && m_pDoc->m_ConveyorTrackInfo[nRtvTrack13[i]-1].m_nDestPos == 22)
				{
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack13[i]-1].m_nLuggNum, 
					                    m_pDoc->m_ConveyorTrackInfo[nRtvTrack13[i]-1].m_nLuggNum2, JOB_STA_MOVE_RGV_OPER_REQUEST);

					if(i == 6 && m_pDoc->m_ConveyorTrackInfo[795-1].m_nDestPos == 22 && m_pDoc->m_ConveyorTrackInfo[795-1].m_nComplete == 1)
						MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[795-1].m_nLuggNum, 0, JOB_STA_MOVE_RGV_OPER_REQUEST);
				}

				if(nPosition == 2 && m_pDoc->m_ConveyorTrackInfo[nRtvTrack13[i]-1].m_nDestPos == 22)
				{
					MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[nRtvTrack13[i]-1].m_nLuggNum, 
					                    m_pDoc->m_ConveyorTrackInfo[nRtvTrack13[i]-1].m_nLuggNum2, JOB_STA_MOVE_CV_OPER_INVOKE);

					if(i == 6 && m_pDoc->m_ConveyorTrackInfo[795-1].m_nDestPos == 22 && m_pDoc->m_ConveyorTrackInfo[795-1].m_nComplete == 1)
						MOVEJOB->FindChange(m_pDoc->m_ConveyorTrackInfo[795-1].m_nLuggNum, 0, JOB_STA_MOVE_CV_OPER_INVOKE);
				}
			}
			break;
		}
	}

}

#undef TRACK_INFO

void CConveyorDlg::OnButtonCopy() 
{
/*
	CString strTemp;
	if( m_pDoc->m_pConveyorSocket[CV_PLC_NUM] == NULL )
	{
		strTemp.Format("PLC#%d 서버와 연결이 안된 상태 입니다.. 잠시후 다시 시도 하세요", CV_PLC_NUM+1);
		AfxMessageBox(strTemp);
		return;
	}
*/
	GetDisplayTrackInfo();

	//m_bCopied = TRUE;
	m_pDoc->m_ConveyorMsg.bCopy = TRUE;
	GetDlgItem(IDC_BUTTON_PASTE)->EnableWindow(TRUE);
}

void CConveyorDlg::GetDisplayTrackInfo() 
{
	CString strTemp;
	GET(IDC_EDIT_LUGG_NUM, strTemp);
	m_pDoc->m_ConveyorMsg.nLuggNum = atoi(strTemp);

	GET(IDC_EDIT_LUGG_NUM2, strTemp);
	m_pDoc->m_ConveyorMsg.nLuggNum2 = atoi(strTemp);
	
	CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_JOB_TYPE);
	int nJobType = pComboBox->GetCurSel()+1;
	switch(nJobType)
	{
	case 1: m_pDoc->m_ConveyorMsg.nJobType = 1; break;
	case 2: m_pDoc->m_ConveyorMsg.nJobType = 2; break;
	case 3: m_pDoc->m_ConveyorMsg.nJobType = 6; break;
	case 4: m_pDoc->m_ConveyorMsg.nJobType = 10; break;
	//case 4: m_pDoc->m_ConveyorMsg.nJobType = 7; break;
	case 5: m_pDoc->m_ConveyorMsg.nJobType = 4; break;
	case 6: m_pDoc->m_ConveyorMsg.nJobType = 5; break;
	}

	pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_STARTNATION);

/*	int nJobType = pComboBox->GetCurSel() + 1;
	m_pDoc->m_ConveyorMsg.nStartPos = (nJobType == 3) ? 6 : nJobType;
*/
	m_pDoc->m_ConveyorMsg.nStartPos = pComboBox->GetCurSel() + 1;

	if(m_nID < 100)
	{
		pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_LINE);
		m_pDoc->m_ConveyorMsg.nStartPos = pComboBox->GetCurSel();
	}

	pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_DESTINATION);
	m_pDoc->m_ConveyorMsg.nDestPos = pComboBox->GetCurSel() + 1;

    m_pDoc->m_ConveyorMsg.nLastPallet = m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLastPallet;

	if(m_nID >= 700)
		m_pDoc->m_ConveyorMsg.nComplete = m_pDoc->m_ConveyorTrackInfo[m_nID].m_nComplete;

	CJobItem* pJobItem = m_pDoc->m_pJob->Find(m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLuggNum);
	if (pJobItem != NULL)
	{
		if(m_pDoc->m_ConveyorMsg.nDestPos == 1)
			pJobItem->m_nDestPos = IMS_ECS_RET_STATION_201;
		else if(m_pDoc->m_ConveyorMsg.nDestPos == 2)
			pJobItem->m_nDestPos = IMS_ECS_RET_STATION_202;
		else if(m_pDoc->m_ConveyorMsg.nDestPos == 3)
			pJobItem->m_nDestPos = IMS_ECS_RET_STATION_203;
	}	

	if(m_nID > 789)
	   m_pDoc->m_ConveyorMsg.nDestPos = pComboBox->GetCurSel() + 3;

	if(m_nID >= 809-1 && m_nID <= 817)
	{
//	   if(nJobType == 3 || nJobType == 4)
		   m_pDoc->m_ConveyorMsg.nDestPos = 7; // 파렛트 대기대는 목적지 7번이다.
	}

	if(m_nID >= 789 && m_nID <= 807)
		m_pDoc->m_ConveyorMsg.nDestPos = pComboBox->GetCurSel()+21;

	if(m_nID == 745 || (m_nID >= 823 && m_nID <= 836))
		m_pDoc->m_ConveyorMsg.nDestPos = pComboBox->GetCurSel()+8;

}

BOOL CConveyorDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (int) pMsg->wParam == VK_ESCAPE )
	       return TRUE;
		
	return CDialog::PreTranslateMessage(pMsg);
}

void CConveyorDlg::OnButtonLastPallet() 
{
	CString strLog;

	if (AfxMessageBox("마지막 Pallet으로 설정 하시겠습니까? ", MB_OKCANCEL) == IDCANCEL)
		return ;

	GetDisplayTrackInfo();

	if(m_nID < 100)
	{
		TRACK_MSG.nTrackNum    = m_nID;
		TRACK_MSG.nLuggNum     = m_pDoc->m_ConveyorMsg.nLuggNum;
		TRACK_MSG.nJobType     = 5;
		TRACK_MSG.nStartPos    = m_pDoc->m_ConveyorMsg.nStartPos;
		TRACK_MSG.nDestPos     = m_pDoc->m_ConveyorMsg.nDestPos;
		m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLastPallet = TRACK_MSG.nLastPallet  = 1;

		CMoveJobItem* pMoveJobItem = MOVEJOB->Find(m_pDoc->m_ConveyorMsg.nLuggNum);
		if(pMoveJobItem != NULL)
			pMoveJobItem->m_nLastPallet = 1;

	}
	else if(m_nID < 700)
	{
		TRACK_MSG.nTrackNum    = m_nID;
		TRACK_MSG.nLuggNum     = m_pDoc->m_ConveyorMsg.nLuggNum;
		TRACK_MSG.nJobType     = 5;
		TRACK_MSG.nStartPos    = m_pDoc->m_ConveyorMsg.nStartPos;
		TRACK_MSG.nDestPos     = m_pDoc->m_ConveyorMsg.nDestPos;
		m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLastPallet = TRACK_MSG.nLastPallet  = 1;
	}
	else
	{
		TRACK_MSG.nTrackNum    = m_nID;
		TRACK_MSG.nLuggNum     = m_pDoc->m_ConveyorMsg.nLuggNum;
		TRACK_MSG.nLuggNum2     = m_pDoc->m_ConveyorMsg.nLuggNum2;
		TRACK_MSG.nJobType     = 5;
		TRACK_MSG.nStartPos    = m_pDoc->m_ConveyorMsg.nStartPos;
		TRACK_MSG.nDestPos     = m_pDoc->m_ConveyorMsg.nDestPos;
		m_pDoc->m_ConveyorTrackInfo[m_nID].m_nComplete = TRACK_MSG.nComplete  = 1;
		TRACK_MSG.nSize     = 0;

		CMoveJobItem* pMoveJobItem = MOVEJOB->Find(m_pDoc->m_ConveyorMsg.nLuggNum);
		if(pMoveJobItem != NULL)
		{
			pMoveJobItem->m_nLastPallet = 1;

			for(int i=0; i<10; i++)
			{
				if(pMoveJobItem->m_nLineNum != m_pDoc->m_nSetLine[i])
					continue;

				if(pMoveJobItem->m_nLineNum == m_pDoc->m_nSetLine[i])
				{
					if(pMoveJobItem->m_nLastPallet == 1)
						m_pDoc->m_nSetLineCount[i] = 0;

					//strLog.Format("OnButtonLastPallet.. 작업자가 수동으로 마지막 카운트 설정 카운트 초기화 함.. Buffer=[%d], Line=[%d], Count=[%d] ..", pMoveJobItem->m_nLineNum, pMoveJobItem->m_nBatchNo, m_pDoc->m_nSetLineCount[i]);
					//LOG_JOB(LOG_POS_CV, TRACK_MSG.nLuggNum, strLog);

				}
			}
		}


	}
	TRACK_MSG.bModified = TRUE;

	CV_ACTION(CV_PLC_NUM);

	strLog.Format("CConveyorDlg::OnButtonLastPallet.. 마지막 팔렛으로 설정..TrackNum=[%d], LastPallet=[%d], Lugg=[%d], Start =[%d], Dest=[%d]",
		TRACK_MSG.nTrackNum + 1, TRACK_MSG.nLastPallet, TRACK_MSG.nLuggNum, TRACK_MSG.nStartPos, TRACK_MSG.nDestPos, TRACK_MSG.nLuggNum);
	m_pDoc->m_pLog->Event(LOG_POS_CV, TRACK_MSG.nLuggNum, strLog);
	
}

void CConveyorDlg::OnButtonLastPalletReset() 
{
	if (AfxMessageBox("(주의)마지막 Pallet 설정을 해제 하시겠습니까? ", MB_OKCANCEL) == IDCANCEL)
		return ;

	GetDisplayTrackInfo();

	TRACK_MSG.nTrackNum    = m_nID;
	TRACK_MSG.nLuggNum     = m_pDoc->m_ConveyorMsg.nLuggNum;
	TRACK_MSG.nJobType     = m_pDoc->m_ConveyorMsg.nJobType;
	TRACK_MSG.nStartPos    = m_pDoc->m_ConveyorMsg.nStartPos;
	TRACK_MSG.nDestPos     = m_pDoc->m_ConveyorMsg.nDestPos;
	m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLastPallet = TRACK_MSG.nLastPallet  = 0;

	TRACK_MSG.bModified = TRUE;

	CV_ACTION(CV_PLC_NUM);

	CString strLog;
	strLog.Format("CConveyorDlg::OnButtonLastPalletReset.. 초기화..TrackNum=[%d], LastPallet=[%d], Lugg=[%d], Start =[%d], Dest=[%d]",
		TRACK_MSG.nTrackNum + 1, TRACK_MSG.nLastPallet, TRACK_MSG.nLuggNum, TRACK_MSG.nStartPos, TRACK_MSG.nDestPos, TRACK_MSG.nLuggNum);
	m_pDoc->m_pLog->Event(LOG_POS_CV, TRACK_MSG.nLuggNum, strLog);
}

void CConveyorDlg::OnButtonRewrite() 
{
	if (AfxMessageBox("지금의 데이타상의 정보대로 재지시를 하시겠습니까? ", MB_OKCANCEL) == IDCANCEL)
		return ;

	GetDisplayTrackInfo();

	TRACK_MSG.nTrackNum    = m_nID;
	TRACK_MSG.nLuggNum     = m_pDoc->m_ConveyorMsg.nLuggNum;
	TRACK_MSG.nJobType     = m_pDoc->m_ConveyorMsg.nJobType;
	TRACK_MSG.nStartPos    = m_pDoc->m_ConveyorMsg.nStartPos;
	TRACK_MSG.nDestPos     = m_pDoc->m_ConveyorMsg.nDestPos;
	m_pDoc->m_ConveyorTrackInfo[m_nID].m_nLastPallet = TRACK_MSG.nLastPallet  = 2;

	TRACK_MSG.bModified = TRUE;

	CV_ACTION(CV_PLC_NUM);

	CString strLog;
	strLog.Format("CConveyorDlg::OnButtonRewrite.. 강제 재지시 쓰기..TrackNum=[%d], LastPallet=[%d], Lugg=[%d], Start =[%d], Dest=[%d]",
		TRACK_MSG.nTrackNum + 1, TRACK_MSG.nLastPallet, TRACK_MSG.nLuggNum, TRACK_MSG.nStartPos, TRACK_MSG.nDestPos, TRACK_MSG.nLuggNum);
	m_pDoc->m_pLog->Event(LOG_POS_CV, TRACK_MSG.nLuggNum, strLog);
}


