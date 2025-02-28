// BufferControllerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ecs.h"
#include "BufferControllerDlg.h"
#include "EcsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBufferControllerDlg dialog


CBufferControllerDlg::CBufferControllerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBufferControllerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBufferControllerDlg)
	m_bSuspend = FALSE;
	m_bReady = FALSE;
	//}}AFX_DATA_INIT

	for (int i = 0 ; i < 2 ; i++)
	{
		for(int j = 0 ; j < 6 ; j++)
		{
			m_nLuggNo[2][6] = 0;
		}
	}
}


void CBufferControllerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBufferControllerDlg)
	DDX_Check(pDX, IDC_CHK_SUSPEND, m_bSuspend);
	DDX_Check(pDX, IDC_CHK_READY, m_bReady);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBufferControllerDlg, CDialog)
	//{{AFX_MSG_MAP(CBufferControllerDlg)
	ON_BN_CLICKED(IDC_CHK_SUSPEND, OnCheckSuspend)
	ON_BN_CLICKED(IDC_CHK_READY, OnCheckReady)			// 일단은 읽어만 오는 걸로 하자!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBufferControllerDlg message handlers

BOOL CBufferControllerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString strTemp;//, strTemp1, strTemp2, strTemp3, strTemp4, strTemp5, strTemp6;
	strTemp.Format(" #%d", m_nID + 1);
	GetDlgItem(IDC_EDIT_TRACK_NUM)->SetWindowText(strTemp);

//	CTime theTime = CTime::GetCurrentTime();

	int nTemp = 28;			// -6개 
	int nTempTemp = nTemp + (m_nID * 10) + 2100;

	int nTemp1 = nTempTemp - 0;
	int nTemp2 = nTempTemp - 1;
	int nTemp3 = nTempTemp - 2;
	int nTemp4 = nTempTemp - 3;
	int nTemp5 = nTempTemp - 4;
	int nTemp6 = nTempTemp - 5;

	int nTempTempTemp[6] = {nTemp1,nTemp2,nTemp3,nTemp4,nTemp5,nTemp6};


	strTemp.Format(" #%d", nTemp1);		GetDlgItem(IDC_STATIC_1ST)->SetWindowText(strTemp);
	strTemp.Format(" #%d", nTemp2);		GetDlgItem(IDC_STATIC_2ND)->SetWindowText(strTemp);
	strTemp.Format(" #%d", nTemp3);		GetDlgItem(IDC_STATIC_3RD)->SetWindowText(strTemp);
	strTemp.Format(" #%d", nTemp4);		GetDlgItem(IDC_STATIC_4TH)->SetWindowText(strTemp);
	strTemp.Format(" #%d", nTemp5);		GetDlgItem(IDC_STATIC_5TH)->SetWindowText(strTemp);
	strTemp.Format(" #%d", nTemp6);		GetDlgItem(IDC_STATIC_6TH)->SetWindowText(strTemp);

	
	for (int i = 0 ; i < 6 ; i++)
	{
		int nTrackNo = nTempTempTemp[i];

		strTemp.Format("%04d", m_pDoc->m_ConveyorTrackInfo[nTrackNo].m_nLuggNum);
		GetDlgItem(IDC_EDIT_LUGG_NUM6 - i)->SetWindowText(strTemp);									// 배열을 잘못 세팅해서 큰거에서 빼기해줘야함 
	
		strTemp.Format("%04d", m_pDoc->m_ConveyorTrackInfo[nTrackNo].m_nLuggNum2);
		GetDlgItem(IDC_EDIT_LUGG_NUM12 - i)->SetWindowText(strTemp);								// 배열을 잘못 세팅해서 큰거에서 빼기해줘야함 
		
		strTemp = (m_pDoc->m_ConveyorTrackInfo[nTrackNo].m_bPltSensor == TRUE) ? "있음" : "없음"; 
		SET(IDC_EDIT_PLT_SENSOR6 - i, strTemp);														// 배열을 잘못 세팅해서 큰거에서 빼기해줘야함 
	}


	// 일단은 표시하자		- NULL로 세팅을 해야 함! 
	CString strTime;
	strTime = (m_pDoc != NULL && m_pDoc->m_timeFullReady[m_nID] != NULL) ? m_pDoc->m_timeFullReady[m_nID].Format("%Y/%m/%d/ %H:%M:%S") : "";
	GetDlgItem(IDC_EDIT_READY_TIME)->SetWindowText(strTime);
	strTime = (m_pDoc != NULL && m_pDoc->m_timeStart[m_nID] != NULL) ? m_pDoc->m_timeStart[m_nID].Format("%Y/%m/%d/ %H:%M:%S") : "";
	GetDlgItem(IDC_EDIT_START_TIME)->SetWindowText(strTime);


	m_bSuspend = m_pDoc->m_bBufferSuspend[m_nID];
	m_bReady = m_pDoc->m_bBufferReady[m_nID];
	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBufferControllerDlg::OnCheckSuspend() 
{
	m_pDoc->m_bBufferSuspend[m_nID] = !m_pDoc->m_bBufferSuspend[m_nID];

	m_bSuspend = m_pDoc->m_bBufferSuspend[m_nID];
	UpdateData(FALSE);
}

// 일단 이거는 읽어오는 걸로만 하자!

void CBufferControllerDlg::OnCheckReady() 
{
	m_pDoc->m_bBufferReady[m_nID] = !m_pDoc->m_bBufferReady[m_nID];

	m_bReady = m_pDoc->m_bBufferReady[m_nID];
	UpdateData(FALSE);
}
//*/
