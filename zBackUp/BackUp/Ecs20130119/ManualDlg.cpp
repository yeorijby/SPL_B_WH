// ManualDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "ManualDlg.h"
#include "EcsDoc.h"
#include "Lib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManualDlg dialog


CManualDlg::CManualDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManualDlg::IDD, pParent)
{
	m_nCmd = 0;
	m_nTrackNum = -1;
	m_bCheckHostNotify = FALSE;

	//{{AFX_DATA_INIT(CManualDlg)
	m_strLocationDest = _T("");
	m_strLocationStart = _T("");
	m_strQuantity = _T("");
	m_strLotNo = _T("");
	m_strProdCode = _T("");
	m_strLuggNum = _T("");
	//}}AFX_DATA_INIT
}


void CManualDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManualDlg)
	DDX_Text(pDX, IDC_EDIT_DEST, m_strLocationDest);
	DDV_MaxChars(pDX, m_strLocationDest, 7);
	DDX_Text(pDX, IDC_EDIT_START, m_strLocationStart);
	DDV_MaxChars(pDX, m_strLocationStart, 7);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CManualDlg, CDialog)
	//{{AFX_MSG_MAP(CManualDlg)
	ON_NOTIFY(NM_CLICK, IDC_TAB_MANUAL, OnClickTabManual)
	ON_BN_CLICKED(IDC_BUTTON_CONFIRM, OnButtonConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManualDlg message handlers

BOOL CManualDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CTabCtrl* pTabCtrl = (CTabCtrl *)GetDlgItem(IDC_TAB_MANUAL);

	TC_ITEM TabCtrlItem;

	TabCtrlItem.mask = TCIF_TEXT;
    TabCtrlItem.pszText = "입고지시";
	pTabCtrl->InsertItem(CMD_STORE, &TabCtrlItem);
    TabCtrlItem.pszText = "출고지시";
	pTabCtrl->InsertItem(CMD_RETRIEVE, &TabCtrlItem);
    TabCtrlItem.pszText = "이동지시";
	pTabCtrl->InsertItem(CMD_BYPASS, &TabCtrlItem);	
#ifdef OPT_RACK_TO_RACK_USE
    TabCtrlItem.pszText = "랙간 이동 지시";
	pTabCtrl->InsertItem(CMD_RACK_TO_RACK, &TabCtrlItem);
#endif

	CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_START);
	pComboBox->ResetContent();
	pComboBox->InsertString(0, "생산입고대");
//	pComboBox->InsertString(1, "Line#11 (CV#782)");
//	pComboBox->InsertString(2, "수동 입고대");
	pComboBox->SetCurSel(-1);

	GetDlgItem(IDC_COMBO_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_DEST)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DEST)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_LAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_MANUALINE)->EnableWindow(FALSE);


	return TRUE;  
}

void CManualDlg::OnClickTabManual(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTabCtrl* pTabCtrl = (CTabCtrl *)GetDlgItem(IDC_TAB_MANUAL);
	m_nCmd = pTabCtrl->GetCurSel(); 
	
	switch (m_nCmd)
	{
	case	CMD_STORE:
		{
		GetDlgItem(IDC_COMBO_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DEST)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DEST)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_LAST)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_MANUALINE)->EnableWindow(FALSE);

		CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_START);
	    pComboBox->ResetContent();
		pComboBox->InsertString(0, "생산입고대");
		pComboBox->SetCurSel(-1);
		}
		break;
	case	CMD_RETRIEVE:
		{
		GetDlgItem(IDC_COMBO_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DEST)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DEST)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_LAST)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_MANUALINE)->EnableWindow(FALSE);

		CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_DEST);
 	    pComboBox->ResetContent();
		pComboBox->InsertString(0, "상차시스템#1");
		pComboBox->InsertString(1, "상차시스템#2");
		pComboBox->InsertString(2, "상차시스템#3");
		pComboBox->SetCurSel(-1);
		}
		break;
	case	CMD_BYPASS:
		{
		GetDlgItem(IDC_COMBO_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DEST)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DEST)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_LAST)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_MANUALINE)->EnableWindow(TRUE);

		CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_START);
		pComboBox->ResetContent();
		pComboBox->InsertString(0, "생산입고대");
		pComboBox->InsertString(1, "Line#11 (CV#782)");
//	    pComboBox->InsertString(2, "수동 입고대");
		pComboBox->SetCurSel(-1);

		pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_DEST);
		pComboBox->ResetContent();
		pComboBox->InsertString(0, "Buffer #1");
		pComboBox->InsertString(1, "Buffer #2");
		pComboBox->InsertString(2, "Buffer #3");
		pComboBox->InsertString(3, "Buffer #4");

		pComboBox->SetCurSel(-1);

		pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_MANUALINE);
		pComboBox->ResetContent();
		pComboBox->InsertString(0, "A Line");
		pComboBox->InsertString(1, "B Line");

		pComboBox->SetCurSel(-1);

		}
		break;
	case	CMD_RACK_TO_RACK:
		{
		GetDlgItem(IDC_COMBO_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DEST)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DEST)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_LAST)->EnableWindow(FALSE);
		}
		break;
	}

	*pResult = 0;
}

#define CV_PLC_NUM	( m_nTrackNum < CV_1_TRACK_CNT + CV_3_TRACK_CNT) ? 0 : 2
#define TRACK_INFO	m_pDoc->m_ConveyorThreadInfo[CV_PLC_NUM].m_ConveyorMsg

void CManualDlg::OnButtonConfirm() 
{
	int nPosition, nLuggNum, nDest;
	CComboBox* pComboBox;
	CComboBox* pComboBox1;
	CJobItem JobItem;
	CString strSrcLoc = "0000000", strDestLoc = "0000000", strTemp, strLast;
	CString strProductID = "", strLotNo = "", strQty;
	CJobItem* pJobItem;

	CTabCtrl* pTabCtrl = (CTabCtrl *)GetDlgItem(IDC_TAB_MANUAL);
	m_nCmd = pTabCtrl->GetCurSel();

	switch (m_nCmd)
	{
	case	CMD_STORE:
		pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_START);
		nPosition = pComboBox->GetCurSel();
		GetDlgItem(IDC_EDIT_DEST)->GetWindowText(strDestLoc);
		if (strDestLoc.GetLength() < 7)
		{
			AfxMessageBox("Location은 7자리 숫자로 입력하여야 합니다.");
			return;
		}
		if (!JobItem.IsValidLocation(strDestLoc))
		{
			AfxMessageBox("Location을 확인하십시오");
			return;
		}
		if ( nPosition > 1 )
		{
			AfxMessageBox("출발위치를 확인하십시오");
			return;
		}

		//nPosition = (nPosition == 0) ? IMS_ECS_STO_STATION_100 : IMS_ECS_STO_STATION_101;
		nPosition = IMS_ECS_STO_STATION_100;

		nLuggNum = m_pDoc->m_pJob->GetSeqLuggNum();
				
		if ( m_nTrackNum == -1 )
		{
			m_pDoc->m_pJob->Add(nLuggNum, JOB_TYPE_MANUAL_STO, 
				strDestLoc, 0, 0, 0,nPosition, CLib::GetStackerNum(strDestLoc) + 1, 100, strProductID);
		}
		else
		{
			m_pDoc->m_pJob->Add(nLuggNum, JOB_TYPE_MANUAL_STO, 
				strDestLoc, 0, 0, 0, nPosition, CLib::GetStackerNum(strDestLoc) + 1, 100, strProductID, "", JOB_STA_CV_OPER_INVOKE);
		}
		strTemp = "반자동 입고 지시 완료!";
		m_pDoc->m_pLog->Event(LOG_POS_SYSTEM, nLuggNum, strTemp);
		AfxMessageBox(strTemp);
		//CV_ACTION(0);
		GetDlgItem(IDC_EDIT_DEST)->SetWindowText("");
		break;
	case	CMD_RETRIEVE:
		pComboBox1 = (CComboBox *)GetDlgItem(IDC_COMBO_DEST);
		nDest = pComboBox1->GetCurSel();
		GetDlgItem(IDC_EDIT_START)->GetWindowText(strSrcLoc);
		if (strSrcLoc.GetLength() < 7)
		{
			AfxMessageBox("Location은 7자리 숫자로 입력하여야 합니다.");
			return;
		}

		if (!JobItem.IsValidLocation(strSrcLoc))
		{
			AfxMessageBox("Location을 확인하십시오");
			return;
		}
		if ( nDest > 2 )
		{
			AfxMessageBox("도착위치를 확인하십시오");
			return;
		}

		switch(nDest)
		{
		case 0:	nPosition = IMS_ECS_RET_STATION_201; break;
		case 1: nPosition = IMS_ECS_RET_STATION_202; break;
		case 2: nPosition = IMS_ECS_RET_STATION_203; break;
		}

		nLuggNum = m_pDoc->m_pJob->GetSeqLuggNum();

		m_pDoc->m_pJob->Add(nLuggNum, JOB_TYPE_RACK_TO_RACK,
			strSrcLoc, 0, 0, 0, CLib::GetStackerNum(strSrcLoc) + 1, nPosition, 100, strProductID, "", JOB_STA_SC_OPER_REQUEST, "", "", 0);
		strTemp = "반자동 출고 지시 완료!";
		m_pDoc->m_pLog->Event(LOG_POS_SYSTEM, nLuggNum, strTemp);
		AfxMessageBox(strTemp);
		GetDlgItem(IDC_EDIT_START)->SetWindowText("");
		break;
	case	CMD_BYPASS:
		{
		pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_START);
		nPosition = pComboBox->GetCurSel();

		pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_MANUALINE);
		int nLoadLine = pComboBox->GetCurSel();
		
		GetDlgItem(IDC_EDIT_LAST)->GetWindowText(strLast);

		int nLast = atoi(strLast);

		if ( nPosition != 0 && nPosition != 1 && nPosition != 2 )
		{
			AfxMessageBox("출발위치를 확인하십시오");
			return;
		}

		int nStartPosition = (nPosition == 0) ? IMS_ECS_STO_STATION_100 : ((nPosition == 1) ? IMS_ECS_STO_STATION_101 : IMS_ECS_STO_STATION_102);

		pComboBox1 = (CComboBox *)GetDlgItem(IDC_COMBO_DEST);
		int nDestLine = pComboBox1->GetCurSel()+1;

		int nDestPosition = 0;

		nLuggNum = m_pDoc->m_pMoveJob->MoveGetSeqLuggNum();

		m_pDoc->m_pMoveJob->Add(nLuggNum, JOB_TYPE_MANUAL_STN_TO_STN,
			strSrcLoc, 0, 0, 0, nStartPosition, nDestPosition, 100, strProductID, "", 0, "", "", nLoadLine, nDestLine, nLast);
		strTemp = "반자동 이동 지시 완료!";
		m_pDoc->m_pLog->Event(LOG_POS_SYSTEM, nLuggNum, strTemp);
		AfxMessageBox(strTemp);
		GetDlgItem(IDC_EDIT_START)->SetWindowText("");
		}
		break;
	case	CMD_RACK_TO_RACK:
		nPosition = 0;
		GetDlgItem(IDC_EDIT_START)->GetWindowText(strSrcLoc);
		if (!JobItem.IsValidLocation(strSrcLoc))
		{
			AfxMessageBox("Start Location is not valid");
			return;
		}
		GetDlgItem(IDC_EDIT_DEST)->GetWindowText(strDestLoc);
		if ( strSrcLoc.GetLength() < 7 || strDestLoc.GetLength() < 7 )
		{
			AfxMessageBox("Location은 7자리 숫자로 입력하여야 합니다.");
			return;
		}
		if (!JobItem.IsValidLocation(strDestLoc))
		{
			AfxMessageBox("Second Location is not valid");
			return;
		}
		if ( JobItem.GetStackerNum(strSrcLoc) != JobItem.GetStackerNum(strDestLoc) )
		{
			AfxMessageBox("Stacker Number is different");
			return;
		}

		GetDlgItem(IDC_EDIT_LUGG_NUM)->GetWindowText(strTemp);
		nLuggNum = atoi(strTemp.Mid(0,4));

		//m_pDoc->m_pJob->Add(nLuggNum, JOB_TYPE_MANUAL_RTR, 
		//	strSrcLoc, 0, 0, nPosition, nPosition, JOB_PRI_DEF, strProductID, strDestLoc);
		strTemp = "Manual Rack to Rack.. Ok!";
		m_pDoc->m_pLog->Event(LOG_POS_SYSTEM, nLuggNum, strTemp);
		AfxMessageBox(strTemp);
		GetDlgItem(IDC_EDIT_START)->SetWindowText("");
		GetDlgItem(IDC_EDIT_DEST)->SetWindowText("");
		break;
	}

	if ( m_nTrackNum == -1 )
	{
		if(m_nCmd == CMD_BYPASS)
			m_pDoc->m_pMoveJob->Invoke(nLuggNum);
		else
			m_pDoc->m_pJob->Invoke(nLuggNum);
		return;
	}

	if (m_nCmd != CMD_STORE )
		return;

	pJobItem = m_pDoc->m_pJob->Find(nLuggNum);
	if ( pJobItem == NULL ) return;

	int nStartPos, nDestPos;
	nStartPos = pJobItem->m_nStartPos;
	nDestPos = pJobItem->m_nDestPos;

	TRACK_INFO.nTrackNum = m_nTrackNum;
	TRACK_INFO.nLuggNum  = nLuggNum;
	TRACK_INFO.nJobType  = pJobItem->m_nJobType;
	TRACK_INFO.nDestPos  = nDestPos;

	TRACK_INFO.bModified = TRUE;
	CV_ACTION(CV_PLC_NUM);

	CString strLog;
	strLog.Format("CManualDlg::OnButtonConfirm.. TrackNum=[%d], Lugg=[%d], Dest=[%d]",
		TRACK_INFO.nTrackNum + 1, TRACK_INFO.nLuggNum, TRACK_INFO.nDestPos);
	m_pDoc->m_pLog->Event(LOG_POS_CV, TRACK_INFO.nLuggNum, strLog);
}

void CManualDlg::Recording(int nJobClass, int nLuggNum, CString strSrcLoc, CString strDestLoc, CString strProductCode, CString strLotNo, CString strQty)
{
	CFile * pFileOut;

	const char* pFileName = MANIO_FILE;
	TRY
	{
		pFileOut = new CFile(pFileName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << "File could not be opened " << e->m_cause << "\n";
		#endif
		return;
	}
	END_CATCH

    pFileOut->SeekToEnd();

	CTime theTime   = CTime::GetCurrentTime();
	CString strDate = theTime.Format("%Y%m%d");
	CString strTime = theTime.Format("%H%M%S");

	char	cProductID[64];
	char	Buffer[512];
	memset(cProductID, 0x20, sizeof(cProductID));
	memset(Buffer, 0x0, sizeof(Buffer));
	sprintf(cProductID, strProductCode.Left(strProductCode.GetLength()));
	cProductID[strProductCode.GetLength()] = 0x20;
	sprintf(cProductID + 6, strLotNo.Left(strLotNo.GetLength()));
	cProductID[6 + strLotNo.GetLength()] = 0x20;

	sprintf(Buffer, "%04d%d%7s%7s%.20s%15s%8s%6s:0\r\n",
		nLuggNum,
		nJobClass,
		strSrcLoc,
		strDestLoc,
		cProductID,
		strQty,
		strDate,
		strTime	);
	pFileOut->Write(Buffer, strlen(Buffer));
	pFileOut->Close();

	m_pDoc->m_pJob->m_bIsOfflineJob = TRUE;

}
