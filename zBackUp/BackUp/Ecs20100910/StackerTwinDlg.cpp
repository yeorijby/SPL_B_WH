// StackerTwinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "StackerTwinDlg.h"
#include "RedirectionDlg.h"
#include "EcsDoc.h"
#include "Lib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SC_INFO	m_pDoc->m_pStackerInfo[m_nID]

/////////////////////////////////////////////////////////////////////////////
// CStackerTwinDlg dialog


CStackerTwinDlg::CStackerTwinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStackerTwinDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStackerTwinDlg)
	m_bRetrieve = FALSE;
	m_bStore = FALSE;
	//}}AFX_DATA_INIT
}


void CStackerTwinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStackerTwinDlg)
	DDX_Check(pDX, IDC_CHECK_RETRIEVE, m_bRetrieve);
	DDX_Check(pDX, IDC_CHECK_STORE, m_bStore);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStackerTwinDlg, CDialog)
	//{{AFX_MSG_MAP(CStackerTwinDlg)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_CALL_TO_HOME, OnButtonCallToHome)
	ON_BN_CLICKED(IDC_BUTTON_COMPLETE, OnButtonComplete)
	ON_BN_CLICKED(IDC_BUTTON_NEW_LOCATION, OnButtonNewLocation)
	ON_BN_CLICKED(IDC_CHECK_RETRIEVE, OnCheckRetrieve)
	ON_BN_CLICKED(IDC_CHECK_STORE, OnCheckStore)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_ERROR_RESET, OnButtonErrorReset)
	ON_BN_CLICKED(IDC_BUTTON_ACTIVE, OnButtonActive)
	ON_BN_CLICKED(IDC_BUTTON_ESTOP, OnButtonEstop)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStackerTwinDlg message handlers

void CStackerTwinDlg::Refresh()
{
	CString strTemp;
	strTemp.Format(" #%d ", m_nID + 1);
	SET(IDC_EDIT_SC_NUM, strTemp);
	
	SET(IDC_EDIT_SC_MODE, CLib::StackerModeToString(m_pDoc->m_pStackerInfo[m_nID]->m_ucMode));
	SET(IDC_EDIT_SC_RC_MODE, CLib::StackerRcModeToString(SC_INFO->m_ucRcMode));
	SET(IDC_EDIT_SC_SC_MODE, CLib::StackerScModeToString(SC_INFO->m_ucScMode));
	SET(IDC_EDIT_SC_ACTIVE, CLib::StackerActiveToString(SC_INFO->m_ucActive));
	strTemp.Format("%d", SC_INFO->m_nHorizontalPos);
	SET(IDC_EDIT_HORIZONTAL_POS, strTemp);

	strTemp.Format("%.4d", SC_INFO->m_nLuggNum);
	SET(IDC_EDIT_LUGG_NUM_1, strTemp);

	strTemp.Format("%.4d", SC_INFO->m_nSecondLuggNum);
	SET(IDC_EDIT_LUGG_NUM_2, strTemp);

	SET(IDC_EDIT_JOB_TYPE, CLib::StackerJobTypeToString(SC_INFO->m_bInternalJobType));
	SET(IDC_EDIT_JOB_TYPE_2, CLib::StackerJobTypeToString(SC_INFO->m_bSecondInternalJobType));

	CJobItem* pJobItem = m_pDoc->m_pJob->Find(SC_INFO->m_nInternalLuggNum);
	if (pJobItem != NULL)
	{
		SET(IDC_EDIT_START_POS, pJobItem->GetStartPos());
		SET(IDC_EDIT_DEST_POS, pJobItem->GetDestPos());

		strTemp.Format("%d", pJobItem->m_nBatchNo);
		GetDlgItem(IDC_EDIT_BATCH_NUM)->SetWindowText(strTemp);

		strTemp.Format("%d", pJobItem->m_nPalletNo);
		GetDlgItem(IDC_EDIT_PALLET_NUM)->SetWindowText(strTemp);

		strTemp.Format("%d", pJobItem->m_nLevelNo);
		GetDlgItem(IDC_EDIT_LEVEL_NUM)->SetWindowText(strTemp);

		SET(IDC_EDIT_PROD_CODE, pJobItem->m_strProductID);
		SET(IDC_EDIT_PROD_CODE_NAME,pJobItem->m_strGrade);
	}

	pJobItem = m_pDoc->m_pJob->Find(SC_INFO->m_nSecondInternalLuggNum);
	if (pJobItem != NULL)
	{
		SET(IDC_EDIT_START_POS_2, pJobItem->GetStartPos());
		SET(IDC_EDIT_DEST_POS_2, pJobItem->GetDestPos());

		strTemp.Format("%d", pJobItem->m_nBatchNo);
		GetDlgItem(IDC_EDIT_BATCH_NUM_2)->SetWindowText(strTemp);

		strTemp.Format("%d", pJobItem->m_nPalletNo);
		GetDlgItem(IDC_EDIT_PALLET_NUM_2)->SetWindowText(strTemp);

		strTemp.Format("%d", pJobItem->m_nLevelNo);
		GetDlgItem(IDC_EDIT_LEVEL_NUM_2)->SetWindowText(strTemp);

		SET(IDC_EDIT_PROD_CODE3, pJobItem->m_strProductID);
		SET(IDC_EDIT_PROD_CODE_NAME_2,pJobItem->m_strGrade);
	}

	if (SC_INFO->m_ucStatus == SC_STA_ERROR)
		strTemp.Format("%s, [%s]", CLib::StackerStatusToString(SC_INFO->m_ucStatus), CLib::GetStackerErrorInfo(SC_INFO->m_wErrCode));
	else
		strTemp = CLib::StackerStatusToString(SC_INFO->m_ucStatus);
	SET(IDC_EDIT_STATUS, strTemp);
	SET(IDC_EDIT_STATUS_2, strTemp);

	if (SC_INFO->m_ucStatus == SC_STA_ERROR)
	{
		strTemp.Format("%d", SC_INFO->m_wErrCode);
		SET(IDC_EDIT_ERROR_CODE, strTemp);
		strTemp.Format("%s", CLib::GetStackerErrorInfo(SC_INFO->m_wErrCode));
		SET(IDC_EDIT_ERROR_CONTEXT, strTemp);
	}

	strTemp.Format("%.4d", SC_INFO->m_nInternalLuggNum);
	SET(IDC_EDIT_INTERNAL_LUGG_NUM, strTemp);
	strTemp.Format("%.4d", SC_INFO->m_nSecondInternalLuggNum);
	SET(IDC_EDIT_INTERNAL_LUGG_NUM_2, strTemp);

    int nTrackNum = CLib::GetScStoHSTrack(m_nID, TRUE);
	if (m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_bStoHomeStandReady)
		strTemp = "STO=[On] ";
	else
		strTemp = "STO=[Off] ";

    nTrackNum = CLib::GetScRetHSTrack(m_nID, TRUE);
	if (m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_bRetHomeStandReady)
		strTemp += "RET=[On]";
	else
		strTemp += "RET=[Off]";

	SET(IDC_EDIT_HOME_STAND, strTemp);

    nTrackNum = CLib::GetScStoHSTrack(m_nID, FALSE);
	if (m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_bStoHomeStandReady)
		strTemp = "STO=[On] ";
	else
		strTemp = "STO=[Off] ";

    nTrackNum = CLib::GetScRetHSTrack(m_nID, FALSE);
	if (m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_bRetHomeStandReady)
		strTemp += "RET=[On]";
	else
		strTemp += "RET=[Off]";

	SET(IDC_EDIT_HOME_STAND_2, strTemp);

/*	pJobItem = m_pDoc->m_pJob->Find(SC_INFO->m_nInternalLuggNum);
	if (pJobItem != NULL)
	{
		strTemp.Format("%.4d", pJobItem->m_nBatchNo);
		SET(IDC_EDIT_BATCH_NUM, strTemp);
		SET(IDC_EDIT_PROD_CODE, pJobItem->m_strProductID);
	}
	pJobItem = m_pDoc->m_pJob->Find(SC_INFO->m_nSecondInternalLuggNum);
	if (pJobItem != NULL)
	{
		//SET(IDC_EDIT_JOB_PROGRESS_2, pJobItem->GetStatus());
		strTemp.Format("%.4d", pJobItem->m_nBatchNo);
		SET(IDC_EDIT_BATCH_NUM_2, strTemp);
		SET(IDC_EDIT_PROD_CODE_2, pJobItem->m_strProductID);
	}
*/
	if (SC_INFO->m_bInvoke)
		SET(IDC_EDIT_JOB_PROGRESS, "진행중");
	else
		SET(IDC_EDIT_JOB_PROGRESS, "완료");
	if (SC_INFO->m_bSecondInvoke)
		SET(IDC_EDIT_JOB_PROGRESS_2, "진행중");
	else
		SET(IDC_EDIT_JOB_PROGRESS_2, "완료");
}

BOOL CStackerTwinDlg::OnInitDialog() 
{
	m_bStore = SC_INFO->m_bStoreSuspend;
	m_bRetrieve = SC_INFO->m_bRetrieveSuspend;

	CDialog::OnInitDialog();
	
	Refresh();

	m_nTimerID = SetTimer(ID_STACKER_TIMER, 1000, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStackerTwinDlg::OnTimer(UINT nIDEvent) 
{
	CDialog::OnTimer(nIDEvent);

	Refresh();

	CString strDiagnosis;

	//if (!SC_INFO->m_bOperatingMode)
	//{
	//	SET(IDC_EDIT_DIAGNOSIS, "소프트웨어 비상정지");
	//	return;
	//}

	if (SC_INFO->m_ucStatus == SC_STA_ERROR || SC_INFO->m_wErrCode > 0)
	{
		CString strTemp;
		strTemp.Format("에러발생.. 코드=[%#d].. 설비 담당자를 부르시오..", SC_INFO->m_wErrCode);
		SET(IDC_EDIT_DIAGNOSIS, strTemp);
		return;
	}

	if (SC_INFO->m_ucMode != SC_MODE_AUTO) {
        SET(IDC_EDIT_DIAGNOSIS, "S/C 모드(REMOTE 또는 OFF-LINE)를 확인하십시오..");
        return;
    }
	
    if (SC_INFO->m_bInvoke) 
	{
        if (SC_INFO->m_ucStatus == SC_STA_WAIT || SC_INFO->m_ucStatus == SC_STA_IDLE)
		{
	        SET(IDC_EDIT_DIAGNOSIS, "작업 상태를 확인후 완료 또는 삭제하십시오..");
            return;
        }
        if (SC_INFO->m_ucStatus == SC_STA_MOVE)
		{
	        SET(IDC_EDIT_DIAGNOSIS, "작업중.. 잠시 기다리십시오..");
            return;
        }
    } 
	else 
	{
		/*
        if (SC_INFO->m_ucProdLoad == SC_PROD_LOAD)
		{
	        SET(IDC_EDIT_DIAGNOSIS, "S/C에 화물이 있음.. 조치하십시오..");
            return;
        }
		*/

        if (SC_INFO->m_ucStatus == SC_STA_MOVE) {
	        SET(IDC_EDIT_DIAGNOSIS, "S/C 이동중.. 그러나 현재 작업이 없습니다..");
            return;
        }

		static BOOL bStoreCheck = TRUE;
        if (SC_INFO->m_ucStatus == SC_STA_WAIT || SC_INFO->m_ucStatus == SC_STA_IDLE)
		{
			if (bStoreCheck)
			{
				bStoreCheck = FALSE;
				if (SC_INFO->m_bStoreSuspend)
				{
			        SET(IDC_EDIT_DIAGNOSIS, "입고 일시 정지 모드..");
					return;
				}

                int nTrackNum = CLib::GetScStoHSTrack(m_nID, TRUE);

				if (m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_nLuggNum != 0)
				{
					if (m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_bHomeStandReady)
				        SET(IDC_EDIT_DIAGNOSIS, "입고대 화물 도착.. Location 이상.. 확인 바람..");
					else
				        SET(IDC_EDIT_DIAGNOSIS, "입고대 화물 도착.. 그러나 준비가 않됨.. 입고대 확인 바람..");
					return;
				}
		        SET(IDC_EDIT_DIAGNOSIS, "입고작업 대기중..");
                return;
            } 
			else 
			{
				bStoreCheck = TRUE;
				if (SC_INFO->m_bRetrieveSuspend)
				{
			        SET(IDC_EDIT_DIAGNOSIS, "출고 일시 정지 모드..");
					return;
				}

                int nTrackNum = CLib::GetScRetHSTrack(m_nID, TRUE);
				if (m_pDoc->m_pJob->FetchByJobPattern(JOB_PATTERN_RET, m_nID) != NULL &&
					!m_pDoc->m_ConveyorTrackInfo[nTrackNum].m_bHomeStandReady)
				{
			        SET(IDC_EDIT_DIAGNOSIS, "출고작업 있음.. 출고대 준비가 않됨.. 확인 바람..");
					return;
				}

		        SET(IDC_EDIT_DIAGNOSIS, "출고작업 대기중..");
                return;
            }
		}
	}

	SET(IDC_EDIT_DIAGNOSIS, "현 상황를 판단할 수 없음..");
}

void CStackerTwinDlg::OnButtonCallToHome() 
{
	if (SC_INFO->m_bInvoke || SC_INFO->m_ucStatus == SC_STA_MOVE || 
		SC_INFO->m_ucStatus == SC_STA_ERROR)// || SC_INFO->m_ucMode != SC_MODE_ONLINE) 
	{
		AfxMessageBox("S/C 상태 확인 바람..\n현재는 이 작업을 수행할 수 없습니다!");
		return;
	}

	//if (SC_INFO->m_ucHorizontalPos == 0)
	//{
	//	AfxMessageBox("Stacker already return back to Home !");
	//	return;
	//}

	if (AfxMessageBox("홈복귀 작업을 하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return ;

	m_pDoc->m_StackerThreadInfo[m_nID].m_StackerMsg.nCommand = SC_CMD_CALL_TO_HOME;
	SC_ACTION(m_nID);
}

void CStackerTwinDlg::OnButtonComplete() 
{
	if (AfxMessageBox("현 작업을 강제 완료하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return ;

	m_pDoc->m_StackerThreadInfo[m_nID].m_StackerMsg.nCommand = SC_CMD_COMPLETE;
	SC_ACTION(m_nID);
}

void CStackerTwinDlg::OnButtonNewLocation() 
{
	WORD wErrCode = SC_INFO->m_wErrCode;

	if (wErrCode != SC_ERR_CODE_DUAL_STORE  &&
		wErrCode != SC_ERR_CODE_DUAL_SECOND_STORE)
	{
		AfxMessageBox("이 기능은 이중입고 에러상황에서만 사용할 수 있습니다..");
		return;
	}

	CJobItem *pJobItem;
	if(wErrCode == SC_ERR_CODE_DUAL_STORE)
		pJobItem = m_pDoc->m_pJob->Find(SC_INFO->m_nInternalLuggNum);
	else
		pJobItem = m_pDoc->m_pJob->Find(SC_INFO->m_nSecondInternalLuggNum);

	if (pJobItem == NULL)
	{
		AfxMessageBox("작업번호를 찾을 수 없습니다.. ");
		return;
	}

	CRedirectionDlg RedirectionDlg;

	if (RedirectionDlg.DoModal() != IDOK) return;

	if (!pJobItem->IsValidLocation(RedirectionDlg.m_strLocation))
	{
		AfxMessageBox("Location 오류 !\nLocation 확인 바람..");
		return;
	}

	if (pJobItem->GetStackerNum() != pJobItem->GetStackerNum(RedirectionDlg.m_strLocation))
	{
		AfxMessageBox("같은 호기내의 Location을 입력해야 합니다!\nLocation 확인 바람..");
		return;
	}

	int	nPattern = pJobItem->GetPattern();
	if (nPattern == JOB_PATTERN_STO || nPattern == JOB_PATTERN_CIRCULATION)
	{
		pJobItem->m_strLocation = RedirectionDlg.m_strLocation;
		pJobItem->m_nStatus = JOB_STA_DUAL_STO_RETRY;
	}
	else
	{
		pJobItem->m_strSecondLoc = RedirectionDlg.m_strLocation;
		pJobItem->m_nStatus = JOB_STA_DUAL_RTR_RETRY;
	}

	m_pDoc->m_StackerThreadInfo[m_nID].m_StackerMsg.nCommand = SC_CMD_NEW_LOCATION;
	SC_ACTION(m_nID);
}

void CStackerTwinDlg::OnButtonReset() 
{
	if (AfxMessageBox("현 작업을 삭제하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return ;

	//m_pDoc->m_StackerThreadInfo[m_nID].m_StackerMsg.nCommand = SC_CMD_RESET;
	SC_ACTION(m_nID);
}

void CStackerTwinDlg::OnCheckRetrieve() 
{
	SC_INFO->m_bRetrieveSuspend = !SC_INFO->m_bRetrieveSuspend;
	SC_INFO->m_bModified = TRUE;
}

void CStackerTwinDlg::OnCheckStore() 
{
	SC_INFO->m_bStoreSuspend = !SC_INFO->m_bStoreSuspend;
	SC_INFO->m_bModified = TRUE;
}

void CStackerTwinDlg::OnButtonDelete() 
{
	if (AfxMessageBox("현 작업을 삭제 하시겠습니까?\n 만약 S/C에 작업 데이터가 있으면 S/C에서 수동으로 삭제 하십시요", MB_OKCANCEL) == IDCANCEL)
		return ;

	m_pDoc->m_StackerThreadInfo[m_nID].m_StackerMsg.nCommand = SC_CMD_CANCEL;
	SC_ACTION(m_nID);
	
}
void CStackerTwinDlg::OnButtonErrorReset() 
{
	if (AfxMessageBox("에러를 초기화 하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return ;

	m_pDoc->m_StackerThreadInfo[m_nID].m_StackerMsg.nCommand = SC_CMD_ERROR_RESET;
	SC_ACTION(m_nID);
	
}

void CStackerTwinDlg::OnButtonActive() 
{
	if (AfxMessageBox("Active 하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return ;

	m_pDoc->m_StackerThreadInfo[m_nID].m_StackerMsg.nCommand = SC_CMD_ACTIVE;
	SC_ACTION(m_nID);
}

void CStackerTwinDlg::OnButtonEstop() 
{
	if (AfxMessageBox("비상정지를 설정 하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return ;

	m_pDoc->m_StackerThreadInfo[m_nID].m_StackerMsg.nCommand = SC_CMD_ESTOP;
	SC_ACTION(m_nID);
}

void CStackerTwinDlg::OnButtonStop() 
{
	if (AfxMessageBox("정지를 설정 하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return ;

	m_pDoc->m_StackerThreadInfo[m_nID].m_StackerMsg.nCommand = SC_CMD_PAUSE;
	SC_ACTION(m_nID);
}
