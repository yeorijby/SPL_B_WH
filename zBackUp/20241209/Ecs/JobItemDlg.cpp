// JobItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "Job.h"
#include "JobItemDlg.h"
#include "EcsDoc.h"
#include "Lib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJobItemDlg dialog


CJobItemDlg::CJobItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJobItemDlg::IDD, pParent)
{
	m_pJobItem = NULL;

	//{{AFX_DATA_INIT(CJobItemDlg)
	m_bNoNotify = FALSE;
	m_strLocationDest = _T("");
	m_strLocationStart = _T("");
	//}}AFX_DATA_INIT
}


void CJobItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJobItemDlg)
	DDX_Text(pDX, IDC_EDIT_DEST_LOC, m_strLocationDest);
	DDV_MaxChars(pDX, m_strLocationDest, 7);
	DDX_Text(pDX, IDC_EDIT_START_LOC, m_strLocationStart);
	DDV_MaxChars(pDX, m_strLocationStart, 7);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJobItemDlg, CDialog)
	//{{AFX_MSG_MAP(CJobItemDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJobItemDlg message handlers

BOOL CJobItemDlg::OnInitDialog() 
{
	if (m_pJobItem == NULL) 
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
	
	GetDlgItem(IDC_EDIT_LUGG_NUM)->SetWindowText(m_pJobItem->GetLuggNumString());
	GetDlgItem(IDC_EDIT_TYPE)->SetWindowText(m_pJobItem->GetType());
	GetDlgItem(IDC_EDIT_BATCHNO)->SetWindowText(m_pJobItem->GetBatchNoString());
	GetDlgItem(IDC_EDIT_PRIORITY)->SetWindowText(m_pJobItem->GetPriorityString());
	GetDlgItem(IDC_EDIT_ERR_INFO)->SetWindowText(m_pJobItem->GetErrInfo());

	CComboBox* pComboBoxStatus = (CComboBox *)GetDlgItem(IDC_COMBO_STATUS);
	for (int i=1; i<JOB_STA_CNT; i++)
		pComboBoxStatus->InsertString(i - 1, m_pJobItem->GetStatus(i));
	pComboBoxStatus->SetCurSel(m_pJobItem->m_nStatus - 1);

	CComboBox* pComboBoxStartPos = (CComboBox *)GetDlgItem(IDC_COMBO_START_POS);
	for (i=0; i<2; i++)
		pComboBoxStartPos->InsertString(i, CLib::GetLinearStartStationName(i));
	
	CComboBox* pComboBoxDestPos = (CComboBox *)GetDlgItem(IDC_COMBO_DEST_POS);
	for (i=0; i<4; i++)
	{
		pComboBoxDestPos->InsertString(i, CLib::GetLinearEndStationName(i));
	}
	
	switch ( m_pJobItem->m_nJobType )
	{
	case	JOB_TYPE_UNIT_STO:
	case	JOB_TYPE_MANUAL_STO:
		GetDlgItem(IDC_COMBO_START_POS)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DEST_POS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_START_LOC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DEST_LOC)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT_DEST_LOC)->SetWindowText(m_pJobItem->m_strLocation);
		pComboBoxStartPos->SetCurSel(m_pJobItem->m_nStartPos == IMS_ECS_STO_STATION_100 ? 0 : 1);
		break;
	case	JOB_TYPE_UNIT_RET:
	case	JOB_TYPE_MANUAL_RET:
	case	JOB_TYPE_RACK_TO_RACK: 
		GetDlgItem(IDC_COMBO_START_POS)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DEST_POS)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_START_LOC)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DEST_LOC)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_START_LOC)->SetWindowText(m_pJobItem->m_strLocation);
		pComboBoxDestPos->SetCurSel(m_pJobItem->m_nDestPos == IMS_ECS_RET_STATION_201 ? 0 : (m_pJobItem->m_nDestPos == IMS_ECS_RET_STATION_202 ? 1 : 2));

		if(m_pJobItem->m_nDestPos == IMS_ECS_RET_STATION_255)
			pComboBoxDestPos->SetCurSel(3);

		break;

	case	JOB_TYPE_STN_TO_STN:
	case	JOB_TYPE_MANUAL_STN_TO_STN:
		GetDlgItem(IDC_COMBO_START_POS)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DEST_POS)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_START_LOC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DEST_LOC)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_DEST_LOC)->SetWindowText(m_pJobItem->m_strLocation);
		pComboBoxStartPos->SetCurSel(m_pJobItem->m_nStartPos == IMS_ECS_STO_STATION_100 ? 0 : 1);

		GetDlgItem(IDC_EDIT_START_LOC)->SetWindowText(m_pJobItem->m_strLocation);
		pComboBoxDestPos->SetCurSel(m_pJobItem->m_nDestPos == IMS_ECS_RET_STATION_200 ? 3 : 0);
		break;
	}

	if ( m_nCmd != CMD_MODIFY )
	{
		GetDlgItem(IDC_EDIT_BATCHNO)->EnableWindow(FALSE);
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

void CJobItemDlg::OnOK() 
{
	CString strGrade, strQuantity, strLocation, strSecondLoc, strPriority;
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
		switch ( m_pJobItem->m_nJobType )
		{
		case	JOB_TYPE_UNIT_STO:
		case	JOB_TYPE_MANUAL_STO:
		case	JOB_TYPE_STN_TO_STN:
		case	JOB_TYPE_MANUAL_STN_TO_STN:
			GET(IDC_EDIT_DEST_LOC, strLocation);
			if (strLocation.GetLength() < 7)
			{
				AfxMessageBox("Location은 7자리 숫자로 입력하여야 합니다.");
				return;
			}
			m_pJobItem->m_strLocation = strLocation;
			{
				CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_START_POS);
				m_pJobItem->m_nStartPos = pComboBox->GetCurSel() == 0 ? IMS_ECS_STO_STATION_100 : IMS_ECS_STO_STATION_101 ;
			}
			break;
		case	JOB_TYPE_UNIT_RET:
		case	JOB_TYPE_MANUAL_RET:
		case	JOB_TYPE_RACK_TO_RACK:
			GET(IDC_EDIT_START_LOC, strLocation);
			if (strLocation.GetLength() < 7)
			{
				AfxMessageBox("Location은 7자리 숫자로 입력하여야 합니다.");
				return;
			}
			m_pJobItem->m_strLocation = strLocation;
			{
				CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_DEST_POS);
				m_pJobItem->m_nDestPos = pComboBox->GetCurSel() == 0 ? IMS_ECS_RET_STATION_201 : (pComboBox->GetCurSel() == 1 ? IMS_ECS_RET_STATION_202 : IMS_ECS_RET_STATION_203) ;

				if(pComboBox->GetCurSel() == 3)
					m_pJobItem->m_nDestPos = IMS_ECS_RET_STATION_255;
			}
			break;
		}

		GET(IDC_EDIT_PRIORITY, strPriority);
		m_pJobItem->m_nPriority = atoi(strPriority);
		
		m_pJobItem->m_nStatus = pComboBoxStatus->GetCurSel() + 1;
		break;
	case	CMD_CANCEL:
		m_pDoc->m_pLog->Event(LOG_POS_HOST, m_pJobItem->m_nLuggNum, "강제 삭제 IMS에 보고 하지 않음!..");
		m_pDoc->m_pJob->Remove(m_pJobItem);
		break;
	case	CMD_RETRY:
		m_pJobItem->m_nStatus = pComboBoxStatus->GetCurSel() + 1;
		break;
	case	CMD_COMPLETE:
		if (m_pJobItem->m_nJobType == JOB_TYPE_MANUAL_STO ||
			m_pJobItem->m_nJobType == JOB_TYPE_MANUAL_RET || 
			m_pJobItem->m_nJobType == JOB_TYPE_RACK_TO_RACK || m_pJobItem->m_nJobType == JOB_TYPE_MANUAL_STN_TO_STN)
		{
			m_pDoc->m_pJob->m_nResultCount[m_pJobItem->GetStackerNum()]++;
			::PostMessage(m_pDoc->m_hwndView, WM_USER_JOB_NOTIFY, JOB_RESULT_DRAW, 0);
		
			m_pDoc->m_pLog->Event(LOG_POS_HOST, m_pJobItem->m_nLuggNum, "반자동 작업 강제 완료 IMS에 보고 하지 않음!..");
			m_pDoc->m_pJob->Remove(m_pJobItem);
			break;
		}

		if(m_pJobItem->m_nJobType == JOB_TYPE_UNIT_STO || m_pJobItem->m_nJobType == JOB_TYPE_UNIT_RET)
		{
			m_pDoc->m_pLog->Event(LOG_POS_HOST, m_pJobItem->m_nLuggNum, "강제 완료 보고..IMS");

			m_pJobItem->m_nStatus = JOB_STA_COMPLETE_REQUEST;

			if (m_pDoc->m_pHostCl != NULL)
				m_pDoc->m_pHostCl->Complete(m_pJobItem->m_nLuggNum);
		}
		else if(m_pJobItem->m_nJobType == JOB_TYPE_STN_TO_STN)
		{
			m_pDoc->m_pLog->Event(LOG_POS_HOST, m_pJobItem->m_nLuggNum, "강제 도착 보고..IMS");

			m_pJobItem->m_nStatus = JOB_STA_COMPLETE;

			//if (m_pDoc->m_pHostCl != NULL)
			//	m_pDoc->m_pHostCl->Arrived(m_pJobItem->m_nLuggNum);
		}

#ifdef OPT_HOST_SAP_INTERFACE_USE
		m_pDoc->m_pSapHost->Complete(m_pJobItem->m_nLuggNum);
#endif
		break;
	}

	m_pDoc->m_pJob->Backup();

	CDialog::OnOK();
}
