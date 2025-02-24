// StatisticThroughputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "EcsDoc.h"
#include "StatisticThroughputDlg.h"
#include "Statistic.h"
#include "StatisticBarChartDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatisticThroughputDlg dialog


CStatisticThroughputDlg::CStatisticThroughputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatisticThroughputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatisticThroughputDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStatisticThroughputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatisticThroughputDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatisticThroughputDlg, CDialog)
	//{{AFX_MSG_MAP(CStatisticThroughputDlg)
	ON_BN_CLICKED(IDC_BUTTON_FILE, OnButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_OFFLINE_CHART, OnButtonOfflineChart)
	ON_BN_CLICKED(IDC_BUTTON_ONLINE_CHART, OnButtonOnlineChart)
	ON_BN_CLICKED(IDC_BUTTON_RATIO_CHART, OnButtonRatioChart)
	ON_BN_CLICKED(IDC_BUTTON_SUM_COUNT, OnButtonSumCount)
	ON_BN_CLICKED(IDC_BUTTON_ONOFFLINE_CHART, OnButtonOnofflineChart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatisticThroughputDlg message handlers

BOOL CStatisticThroughputDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CTime theTime = CTime::GetCurrentTime();
	m_nDay = theTime.GetDay();
	CString strTemp;
	strTemp.Format("%.2d/%.2d", theTime.GetMonth(), m_nDay);
	GetDlgItem(IDC_EDIT_DATE)->SetWindowText(strTemp);

	m_bSelected = FALSE;
	memset(m_sStcInfo, 0x0, sizeof(m_sStcInfo));
	Refresh(m_pDoc->m_pStatistic->m_sSTC);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStatisticThroughputDlg::Refresh(struct SStatisticInfo *STATICS, BOOL bToday)
{
	char	szBuff[124], tmpBuff[64];
	time_t	tCurTime;
	int		nOnlineJob=0, nOfflineJob=0, nErrorSum=0;
	struct  tm *StartTm;

	time(&tCurTime);
	StartTm = localtime(&STATICS[0].tBeginTime);
	//CurTm   = localtime(&tCurTime);
	_strtime(tmpBuff);

	int idx=sprintf(szBuff, "일별 물량처리/장애발생 빈도 (%d/%d/%d %02d:%02d ~ )",
			1900+StartTm->tm_year, StartTm->tm_mon+1, StartTm->tm_mday,
			StartTm->tm_hour, StartTm->tm_min);
	if(bToday)	sprintf(&szBuff[idx-1], "%.5s)", tmpBuff);

	SET(IDC_TITLE, szBuff);

	for(int i=0; i<SC_CNT; i++) 
	{
		switch (i)
		{
		case 0:
			sprintf(szBuff, "%d", STATICS[i].nOnlineJobSum);
			SET(IDC_ONLINE_JOB1, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nOfflineJobSum);
			SET(IDC_OFFLINE_JOB1, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nOnlineJobSum + STATICS[i].nOfflineJobSum);
			SET(IDC_JOB_SUM1, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nErrorSum);
			SET(IDC_ERROR_SUM1, szBuff);
			break;
		case 1:
			sprintf(szBuff, "%d", STATICS[i].nOnlineJobSum);
			SET(IDC_ONLINE_JOB2, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nOfflineJobSum);
			SET(IDC_OFFLINE_JOB2, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nOnlineJobSum + STATICS[i].nOfflineJobSum);
			SET(IDC_JOB_SUM2, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nErrorSum);
			SET(IDC_ERROR_SUM2, szBuff);
			break;
		case 2:
			sprintf(szBuff, "%d", STATICS[i].nOnlineJobSum);
			SET(IDC_ONLINE_JOB3, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nOfflineJobSum);
			SET(IDC_OFFLINE_JOB3, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nOnlineJobSum + STATICS[i].nOfflineJobSum);
			SET(IDC_JOB_SUM3, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nErrorSum);
			SET(IDC_ERROR_SUM3, szBuff);
			break;
		case 3:
			sprintf(szBuff, "%d", STATICS[i].nOnlineJobSum);
			SET(IDC_ONLINE_JOB4, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nOfflineJobSum);
			SET(IDC_OFFLINE_JOB4, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nOnlineJobSum + STATICS[i].nOfflineJobSum);
			SET(IDC_JOB_SUM4, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nErrorSum);
			SET(IDC_ERROR_SUM4, szBuff);
			break;
		case 4:
			sprintf(szBuff, "%d", STATICS[i].nOnlineJobSum);
			SET(IDC_ONLINE_JOB5, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nOfflineJobSum);
			SET(IDC_OFFLINE_JOB5, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nOnlineJobSum + STATICS[i].nOfflineJobSum);
			SET(IDC_JOB_SUM5, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nErrorSum);
			SET(IDC_ERROR_SUM5, szBuff);
			break;
		case 5:
			sprintf(szBuff, "%d", STATICS[i].nOnlineJobSum);
			SET(IDC_ONLINE_JOB6, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nOfflineJobSum);
			SET(IDC_OFFLINE_JOB6, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nOnlineJobSum + STATICS[i].nOfflineJobSum);
			SET(IDC_JOB_SUM6, szBuff);
			sprintf(szBuff, "%d", STATICS[i].nErrorSum);
			SET(IDC_ERROR_SUM6, szBuff);
			break;
		}
	}

	for(i=0; i<SC_CNT; i++)
	{
		nOnlineJob  += STATICS[i].nOnlineJobSum;
		nOfflineJob += STATICS[i].nOfflineJobSum;
		nErrorSum   += STATICS[i].nErrorSum;
	}

	sprintf(szBuff, "%d", nOnlineJob);
	SET(IDC_ONLINE_JOB_AVERAGE, szBuff);
	sprintf(szBuff, "%d", nOfflineJob);
	SET(IDC_OFFLINE_JOB_AVERAGE, szBuff);
	sprintf(szBuff, "%d", nOnlineJob + nOfflineJob);
	SET(IDC_JOB_SUM_AVERAGE, szBuff);
	sprintf(szBuff, "%d", nErrorSum);
	SET(IDC_ERROR_SUM_AVERAGE, szBuff);
}

void CStatisticThroughputDlg::Loading()
{
	char szSection[256];
	time_t	tBeginTm;
//	struct	SStatisticInfo	StcInfo[SC_CNT];

	CString strFileName, strTemp;

	strTemp.Format("%.2d", m_nDay);
	strFileName = m_strDir + m_strFileName + strTemp + ".info";

	tBeginTm = (time_t) GetPrivateProfileInt("EcsBegin", "BeginTime", 0, strFileName);
	memset(m_sStcInfo, 0x0, sizeof(m_sStcInfo));
	for ( int i = 0; i < SC_CNT; i++ )
	{
		sprintf(szSection, "Stacker%d", i + 1);
		m_sStcInfo[i].tBeginTime = tBeginTm;
		m_sStcInfo[i].tOnlineWorkTime     = (time_t) GetPrivateProfileInt(szSection, "OnlineWorkTime", 0, strFileName);
		m_sStcInfo[i].tOfflineWorkTime    = (time_t) GetPrivateProfileInt(szSection, "OfflineWorkTime", 0, strFileName);
		m_sStcInfo[i].tOnlineTroubleTime  = (time_t) GetPrivateProfileInt(szSection, "OnlineTroubleTime", 0, strFileName);
		m_sStcInfo[i].tOfflineTroubleTime = (time_t) GetPrivateProfileInt(szSection, "OfflineTroubleTime", 0, strFileName);
		m_sStcInfo[i].nOnlineJobSum       = GetPrivateProfileInt(szSection, "OnlineJobSum", 0, strFileName);
		m_sStcInfo[i].nOfflineJobSum      = GetPrivateProfileInt(szSection, "OfflineJobSum", 0, strFileName);
		m_sStcInfo[i].nErrorSum           = GetPrivateProfileInt(szSection, "ErrorSum", 0, strFileName);
	}

	m_bSelected = TRUE;
	Refresh(m_sStcInfo, FALSE);
}

void CStatisticThroughputDlg::OnButtonFile() 
{
	// TODO: Add your control notification handler code here
/*	char	szOldDir[128];
	GetCurrentDirectory(sizeof(szOldDir), szOldDir);
	SetCurrentDirectory(m_pDoc->m_pStatistic->m_strDir);

	CFileDialog FileDlg(TRUE, NULL, "*.info", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		" ECS Statistics Files (*.info) | *.info ||");
*/
	char	szOldDir[128];
	char	szNewDir[512];

	GetCurrentDirectory(sizeof(szOldDir), szOldDir);
	SetCurrentDirectory(m_pDoc->m_pStatistic->m_strDir);
	GetCurrentDirectory(sizeof(szNewDir), szNewDir);

	CFileDialog FileDlg(TRUE, NULL, "*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		" ECS Statistics Error Files (*.dat) | *.dat ||");

	FileDlg.m_ofn.lpstrInitialDir = szNewDir;
	FileDlg.m_ofn.lpstrTitle = "ECS 물량처리정보 파일";

	if (FileDlg.DoModal() == IDOK) 
	{
		CString strFileTitle = FileDlg.GetFileTitle();
		m_nDay = atoi(strFileTitle.Mid(10, 2));
		CTime theTime = CTime::GetCurrentTime();
		CString strTemp;
		int nMonth = theTime.GetMonth();
		if (m_nDay > theTime.GetDay())
		{
			if (nMonth == 1)
				strTemp.Format("%.2d/%.2d", 12, m_nDay);
			else
				strTemp.Format("%.2d/%.2d", nMonth - 1, m_nDay);
		}
		else
		{
			strTemp.Format("%.2d/%.2d", theTime.GetMonth(), m_nDay);
		}

		GetDlgItem(IDC_EDIT_DATE)->SetWindowText(strTemp);
		Loading();
	}
	SetCurrentDirectory(szOldDir);
}

void CStatisticThroughputDlg::OnButtonRefresh()
{
	CTime theTime = CTime::GetCurrentTime();
	m_nDay = theTime.GetDay();
	CString strTemp;
	strTemp.Format("%.2d/%.2d", theTime.GetMonth(), m_nDay);
	GetDlgItem(IDC_EDIT_DATE)->SetWindowText(strTemp);

	m_bSelected = FALSE;
	Refresh(m_pDoc->m_pStatistic->m_sSTC);
}

void CStatisticThroughputDlg::OnButtonOfflineChart() 
{
	// TODO: Add your control notification handler code here
	struct	SStatisticInfo * pStcInfo;
	CStatisticBarChartDlg StatisticBarChartDlg;
	StatisticBarChartDlg.m_nCMD = CMD_OFFLINE_CHART;
	StatisticBarChartDlg.m_bToday = !m_bSelected;
	if(m_bSelected)	pStcInfo = m_sStcInfo;
	else			pStcInfo = m_pDoc->m_pStatistic->m_sSTC;
	for(int i=0; i<SC_CNT; i++)
		StatisticBarChartDlg.m_sStcInfo[i] = pStcInfo[i];
	StatisticBarChartDlg.DoModal();	
}

void CStatisticThroughputDlg::OnButtonOnlineChart() 
{
	// TODO: Add your control notification handler code here
	struct	SStatisticInfo * pStcInfo;
	CStatisticBarChartDlg StatisticBarChartDlg;
	StatisticBarChartDlg.m_nCMD = CMD_ONLINE_CHART;
	StatisticBarChartDlg.m_bToday = !m_bSelected;
	if(m_bSelected)	pStcInfo = m_sStcInfo;
	else			pStcInfo = m_pDoc->m_pStatistic->m_sSTC;
	for(int i=0; i<SC_CNT; i++)
		StatisticBarChartDlg.m_sStcInfo[i] = pStcInfo[i];
	StatisticBarChartDlg.DoModal();	
	
}

void CStatisticThroughputDlg::OnButtonRatioChart() 
{
	// TODO: Add your control notification handler code here
	struct	SStatisticInfo * pStcInfo;
	CStatisticBarChartDlg StatisticBarChartDlg;
	StatisticBarChartDlg.m_nCMD = CMD_RATIO_CHART;
	StatisticBarChartDlg.m_bToday = !m_bSelected;
	if(m_bSelected)	pStcInfo = m_sStcInfo;
	else			pStcInfo = m_pDoc->m_pStatistic->m_sSTC;
	for(int i=0; i<SC_CNT; i++)
		StatisticBarChartDlg.m_sStcInfo[i] = pStcInfo[i];
	StatisticBarChartDlg.DoModal();		
}

void CStatisticThroughputDlg::OnButtonSumCount() 
{
	// TODO: Add your control notification handler code here
	struct	SStatisticInfo * pStcInfo;
	CStatisticBarChartDlg StatisticBarChartDlg;
	StatisticBarChartDlg.m_nCMD = CMD_COUNT_CHART;
	StatisticBarChartDlg.m_bToday = !m_bSelected;
	if(m_bSelected)	pStcInfo = m_sStcInfo;
	else			pStcInfo = m_pDoc->m_pStatistic->m_sSTC;
	for(int i=0; i<SC_CNT; i++)
		StatisticBarChartDlg.m_sStcInfo[i] = pStcInfo[i];
	StatisticBarChartDlg.DoModal();
	
}

void CStatisticThroughputDlg::OnButtonOnofflineChart() 
{
	// TODO: Add your control notification handler code here
	struct	SStatisticInfo * pStcInfo;
	CStatisticBarChartDlg StatisticBarChartDlg;
	StatisticBarChartDlg.m_nCMD = CMD_ON_OFFLINE_CHART;
	StatisticBarChartDlg.m_bToday = !m_bSelected;
	if(m_bSelected)	pStcInfo = m_sStcInfo;
	else			pStcInfo = m_pDoc->m_pStatistic->m_sSTC;
	for(int i=0; i<SC_CNT; i++)
			StatisticBarChartDlg.m_sStcInfo[i] = pStcInfo[i];
	StatisticBarChartDlg.DoModal();	
	
}
