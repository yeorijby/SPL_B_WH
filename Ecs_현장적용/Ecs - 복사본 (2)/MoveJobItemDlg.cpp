// MoveJobItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "MoveJob.h"
#include "MoveJobItemDlg.h"
#include "EcsDoc.h"
#include "Lib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMoveJobItemDlg dialog


CMoveJobItemDlg::CMoveJobItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMoveJobItemDlg::IDD, pParent)
{
	m_pMoveJobItem = NULL;

	//{{AFX_DATA_INIT(CJobItemDlg)
	m_bNoNotify = FALSE;
	m_strLocationDest = _T("");
	m_strLocationStart = _T("");
	//}}AFX_DATA_INIT
}


void CMoveJobItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJobItemDlg)
	DDX_Text(pDX, IDC_EDIT_DEST_LOC, m_strLocationDest);
	DDV_MaxChars(pDX, m_strLocationDest, 7);
	DDX_Text(pDX, IDC_EDIT_START_LOC, m_strLocationStart);
	DDV_MaxChars(pDX, m_strLocationStart, 7);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMoveJobItemDlg, CDialog)
	//{{AFX_MSG_MAP(CMoveJobItemDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJobItemDlg message handlers

BOOL CMoveJobItemDlg::OnInitDialog() 
{
	CString strTemp;

	if (m_pMoveJobItem == NULL) 
		CDialog::OnCancel();                                                     
	
	switch (m_nCmd)
	{
	case	CMD_MODIFY:
//		m_bNoNotify = TRUE;
		GetDlgItem(IDOK)->SetWindowText("수정");
		break;
	case	CMD_CANCEL:
//		m_bNoNotify = TRUE;
		GetDlgItem(IDOK)->SetWindowText("취소(삭제)");
		break;
	case	CMD_RETRY:
		GetDlgItem(IDOK)->SetWindowText("재시도");
		break;
	case	CMD_COMPLETE:
		GetDlgItem(IDOK)->SetWindowText("완료");
		break;
	}

	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_EDIT_LUGG_NUM)->SetWindowText(m_pMoveJobItem->GetLuggNumString());
	GetDlgItem(IDC_EDIT_LUGG_NUM2)->SetWindowText(m_pMoveJobItem->GetLuggNumString2());
	GetDlgItem(IDC_EDIT_TYPE)->SetWindowText(m_pMoveJobItem->GetType());
	//GetDlgItem(IDC_EDIT_BATCHNO)->SetWindowText(m_pMoveJobItem->GetBatchNoString());
	GetDlgItem(IDC_EDIT_PRIORITY)->SetWindowText(m_pMoveJobItem->GetPriorityString());
	GetDlgItem(IDC_EDIT_ERR_INFO)->SetWindowText(m_pMoveJobItem->GetErrInfo());

	CComboBox* pComboBoxStatus = (CComboBox *)GetDlgItem(IDC_COMBO_STATUS);
	for (int i=1; i<JOB_STA_MOVE_CNT; i++)
		pComboBoxStatus->InsertString(i - 1, m_pMoveJobItem->GetStatus(i));
	pComboBoxStatus->SetCurSel(m_pMoveJobItem->m_nStatus - 1);

	CComboBox* pComboBoxStartPos = (CComboBox *)GetDlgItem(IDC_COMBO_START_POS);
	pComboBoxStartPos->InsertString(0, "생산 입고대");
	pComboBoxStartPos->InsertString(1, "Line#11 (CV#782)");
	pComboBoxStartPos->InsertString(2, "수동 입고대");
	//pComboBoxStartPos->InsertString(2, "버켓 자동 입고대");

	pComboBoxStartPos->SetCurSel(-1);
	
	CComboBox* pComboBoxDestPos = (CComboBox *)GetDlgItem(IDC_COMBO_DEST_POS);
	pComboBoxDestPos->InsertString(0, "Buffer#1");
	pComboBoxDestPos->InsertString(1, "Buffer#2");
	pComboBoxDestPos->InsertString(2, "Buffer#3");
	pComboBoxDestPos->InsertString(3, "Buffer#4");
	pComboBoxDestPos->InsertString(4, "Line#11");
	pComboBoxDestPos->InsertString(5, "Buffer#15");
	pComboBoxDestPos->SetCurSel(-1);

	strTemp.Format("%d", m_pMoveJobItem->m_nBatchNo);
	SET(IDC_EDIT_LINE_SEQ, strTemp );

	switch ( m_pMoveJobItem->m_nJobType )
	{
	case	JOB_TYPE_STN_TO_STN:
	case	JOB_TYPE_MANUAL_STN_TO_STN:
		GetDlgItem(IDC_COMBO_START_POS)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DEST_POS)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_START_LOC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DEST_LOC)->EnableWindow(FALSE);

		pComboBoxStartPos->SetCurSel(m_pMoveJobItem->m_nStartPos == IMS_ECS_STO_STATION_100 ? 0 : (m_pMoveJobItem->m_nStartPos == IMS_ECS_STO_STATION_101 ? 1 : 2));
		pComboBoxDestPos->SetCurSel(m_pMoveJobItem->m_nLineNum-1);
		if(m_pMoveJobItem->m_nLineNum == 11)
			pComboBoxDestPos->SetCurSel(4);
		if(m_pMoveJobItem->m_nLineNum == 15)
			pComboBoxDestPos->SetCurSel(5);

		break;
	}

	if ( m_nCmd != CMD_MODIFY )
	{
		//GetDlgItem(IDC_EDIT_BATCHNO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRIORITY)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_STATUS)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_START_POS)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DEST_POS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_START_LOC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DEST_LOC)->EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMoveJobItemDlg::OnOK() 
{
	CString strGrade, strQuantity, strLocation, strSecondLoc, strPriority, strLineSeq;
	CComboBox* pComboBoxStatus = (CComboBox *)GetDlgItem(IDC_COMBO_STATUS);

	if (!UpdateData(TRUE))
	{
		TRACE0("UpdateData failed during dialog termination.\n");
		// the UpdateData routine will set focus to correct item
		return;
	}

	switch (m_nCmd)
	{
	case	CMD_MODIFY:
		switch ( m_pMoveJobItem->m_nJobType )
		{
		case	JOB_TYPE_STN_TO_STN:
		case	JOB_TYPE_MANUAL_STN_TO_STN:

			CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_START_POS);
			m_pMoveJobItem->m_nStartPos = pComboBox->GetCurSel()+100;

			//if(m_pMoveJobItem->m_nStartPos == 102)
			//	m_pMoveJobItem->m_nStartPos = 103;

	
			pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_DEST_POS);
			m_pMoveJobItem->m_nLineNum = pComboBox->GetCurSel()+1;

			if(pComboBox->GetCurSel()+1 == 5)
				m_pMoveJobItem->m_nLineNum = 11;

			if(pComboBox->GetCurSel()+1 == 6)
				m_pMoveJobItem->m_nLineNum = 15;

			GET(IDC_EDIT_LINE_SEQ, strLineSeq);
			m_pMoveJobItem->m_nBatchNo = atoi(strLineSeq);

			break;

		}

		GET(IDC_EDIT_PRIORITY, strPriority);
		m_pMoveJobItem->m_nPriority = atoi(strPriority);
		
		m_pMoveJobItem->m_nStatus = pComboBoxStatus->GetCurSel() + 1;
		break;
	case	CMD_CANCEL:
		m_pDoc->m_pLog->Event(LOG_POS_HOST, m_pMoveJobItem->m_nLuggNum, "강제 삭제 IMS에 보고 하지 않음!..");
		m_pDoc->m_pMoveJob->Remove(m_pMoveJobItem);
		break;
	case	CMD_RETRY:
		m_pMoveJobItem->m_nStatus = pComboBoxStatus->GetCurSel() + 1;
		break;
	case	CMD_ARRIVE:
		if (m_pMoveJobItem->m_nJobType == JOB_TYPE_MANUAL_STN_TO_STN)
		{
			//m_pDoc->m_pMoveJob->m_nResultCount[m_pJobItem->GetStackerNum()]++;
			::PostMessage(m_pDoc->m_hwndView, WM_USER_JOB_NOTIFY, JOB_RESULT_DRAW, 0);
		
			m_pDoc->m_pLog->Event(LOG_POS_HOST, m_pMoveJobItem->m_nLuggNum, "반자동 작업 강제 완료 IMS에 보고 하지 않음!..");
			m_pDoc->m_pMoveJob->Remove(m_pMoveJobItem);
			break;
		}

		if(m_pMoveJobItem->m_nJobType == JOB_TYPE_STN_TO_STN)
		{
			m_pDoc->m_pLog->Event(LOG_POS_HOST, m_pMoveJobItem->m_nLuggNum, "강제 도착 보고..IMS");

			m_pMoveJobItem->m_nStatus = JOB_STA_COMPLETE;

			if (m_pDoc->m_pHostCl != NULL)
				m_pDoc->m_pHostCl->Arrived(m_pMoveJobItem->m_nLuggNum);
		}

		break;
	case	CMD_COMPLETE:
		if (m_pMoveJobItem->m_nJobType == JOB_TYPE_MANUAL_STO ||
			m_pMoveJobItem->m_nJobType == JOB_TYPE_MANUAL_RET || 
			m_pMoveJobItem->m_nJobType == JOB_TYPE_RACK_TO_RACK || m_pMoveJobItem->m_nJobType == JOB_TYPE_MANUAL_STN_TO_STN)
		{
			//m_pDoc->m_pMoveJob->m_nResultCount[m_pJobItem->GetStackerNum()]++;
			::PostMessage(m_pDoc->m_hwndView, WM_USER_JOB_NOTIFY, JOB_RESULT_DRAW, 0);
		
			m_pDoc->m_pLog->Event(LOG_POS_HOST, m_pMoveJobItem->m_nLuggNum, "반자동 작업 강제 완료 IMS에 보고 하지 않음!..");
			m_pDoc->m_pMoveJob->Remove(m_pMoveJobItem);
			break;
		}

		if(m_pMoveJobItem->m_nJobType == JOB_TYPE_STN_TO_STN)
		{
			m_pDoc->m_pLog->Event(LOG_POS_HOST, m_pMoveJobItem->m_nLuggNum, "강제 도착 보고..IMS");

			m_pMoveJobItem->m_nStatus = JOB_STA_COMPLETE;

			if (m_pDoc->m_pHostCl != NULL)
				m_pDoc->m_pHostCl->Arrived(m_pMoveJobItem->m_nLuggNum);
		}

#ifdef OPT_HOST_SAP_INTERFACE_USE
		m_pDoc->m_pSapHost->Complete(m_pJobItem->m_nLuggNum);
#endif
		break;
	}

	m_pDoc->m_pMoveJob->Backup();

	CDialog::OnOK();
}
