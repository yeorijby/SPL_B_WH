// StatisticAvailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "EcsDoc.h"
#include "StatisticAvailDlg.h"
#include "Statistic.h"
#include "StatisticBarChartDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatisticAvailDlg dialog


CStatisticAvailDlg::CStatisticAvailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatisticAvailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatisticAvailDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStatisticAvailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatisticAvailDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatisticAvailDlg, CDialog)
	//{{AFX_MSG_MAP(CStatisticAvailDlg)
	ON_BN_CLICKED(IDC_BUTTON_FILE, OnButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_ONLINE_CHART, OnButtonOnlineChart)
	ON_BN_CLICKED(IDC_BUTTON_OFFLINE_CHART, OnButtonOfflineChart)
	ON_BN_CLICKED(IDC_BUTTON_RATIO_CHART, OnButtonRatioChart)
	ON_BN_CLICKED(IDC_BUTTON_SUM_COUNT, OnButtonSumCount)
	ON_BN_CLICKED(IDC_BUTTON_ONOFFLINE_CHART, OnButtonOnofflineChart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatisticAvailDlg message handlers

BOOL CStatisticAvailDlg::OnInitDialog() 
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

void CStatisticAvailDlg::Refresh(struct SStatisticInfo *STATICS,  BOOL bToday)
{
	char	szBuff[124], tmpBuff[64];
	time_t	tCurTime;
	double  dOnlineWork=0, dOfflineWork=0, dOnlineTrouble=0, dOfflineTrouble=0;
	double	dAverage;
	struct  tm *StartTm;

	time(&tCurTime);
	StartTm = localtime(&STATICS[0].tBeginTime);
	//CurTm   = localtime(&tCurTime);
	_strtime(tmpBuff);

	int idx=sprintf(szBuff, "일별 가동/고장률 집계정보 (%d/%d/%d %02d:%02d ~ )",
			1900+StartTm->tm_year, StartTm->tm_mon+1, StartTm->tm_mday,
			StartTm->tm_hour, StartTm->tm_min);
	if(bToday)	sprintf(&szBuff[idx-1], "%.5s)", tmpBuff);
	else		tCurTime = STATICS[0].tBeginTime + (24 - StartTm->tm_hour) * 3600;

	SET(IDC_TITLE, szBuff);

	for(int i=0; i<SC_CNT; i++) 
	{
		switch (i)
		{
		case 0:
			sprintf(szBuff, "%d", STATICS[i].tOnlineWorkTime/60);
			SET(IDC_ONLINE_WORK1, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOfflineWorkTime/60);
			SET(IDC_OFFLINE_WORK1, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOnlineTroubleTime/60);
			SET(IDC_ONLINE_STOP1, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOfflineTroubleTime/60);
			SET(IDC_OFFLINE_STOP1, szBuff);
			dAverage = (STATICS[i].tOnlineWorkTime + STATICS[i].tOfflineWorkTime) * 100;
			dAverage /= (tCurTime - STATICS[i].tBeginTime);
			sprintf(szBuff, "%.2f", dAverage);
			SET(IDC_WORK_RATIO1, szBuff);
			dAverage = (STATICS[i].tOnlineTroubleTime + STATICS[i].tOfflineTroubleTime) * 100;
			dAverage /= (tCurTime - STATICS[i].tBeginTime);
			sprintf(szBuff, "%.2f", dAverage);
			SET(IDC_STOP_RATIO1, szBuff);
			break;
		case 1:
			sprintf(szBuff, "%d", STATICS[i].tOnlineWorkTime/60);
			SET(IDC_ONLINE_WORK2, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOfflineWorkTime/60);
			SET(IDC_OFFLINE_WORK2, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOnlineTroubleTime/60);
			SET(IDC_ONLINE_STOP2, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOfflineTroubleTime/60);
			SET(IDC_OFFLINE_STOP2, szBuff);
			dAverage = (STATICS[i].tOnlineWorkTime + STATICS[i].tOfflineWorkTime) * 100;
			dAverage /= (tCurTime - STATICS[i].tBeginTime);
			sprintf(szBuff, "%.2f", dAverage);
			SET(IDC_WORK_RATIO2, szBuff);
			dAverage = (STATICS[i].tOnlineTroubleTime + STATICS[i].tOfflineTroubleTime) * 100;
			dAverage /= (tCurTime - STATICS[i].tBeginTime);
			sprintf(szBuff, "%.2f", dAverage);
			SET(IDC_STOP_RATIO2, szBuff);
			break;
		case 2:
			sprintf(szBuff, "%d", STATICS[i].tOnlineWorkTime/60);
			SET(IDC_ONLINE_WORK3, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOfflineWorkTime/60);
			SET(IDC_OFFLINE_WORK3, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOnlineTroubleTime/60);
			SET(IDC_ONLINE_STOP3, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOfflineTroubleTime/60);
			SET(IDC_OFFLINE_STOP3, szBuff);
			dAverage = (STATICS[i].tOnlineWorkTime + STATICS[i].tOfflineWorkTime) * 100;
			dAverage /= (tCurTime - STATICS[i].tBeginTime);
			sprintf(szBuff, "%.2f", dAverage);
			SET(IDC_WORK_RATIO3, szBuff);
			dAverage = (STATICS[i].tOnlineTroubleTime + STATICS[i].tOfflineTroubleTime) * 100;
			dAverage /= (tCurTime - STATICS[i].tBeginTime);
			sprintf(szBuff, "%.2f", dAverage);
			SET(IDC_STOP_RATIO3, szBuff);
			break;
		case 3:
			sprintf(szBuff, "%d", STATICS[i].tOnlineWorkTime/60);
			SET(IDC_ONLINE_WORK4, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOfflineWorkTime/60);
			SET(IDC_OFFLINE_WORK4, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOnlineTroubleTime/60);
			SET(IDC_ONLINE_STOP4, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOfflineTroubleTime/60);
			SET(IDC_OFFLINE_STOP4, szBuff);
			dAverage = (STATICS[i].tOnlineWorkTime + STATICS[i].tOfflineWorkTime) * 100;
			dAverage /= (tCurTime - STATICS[i].tBeginTime);
			sprintf(szBuff, "%.2f", dAverage);
			SET(IDC_WORK_RATIO4, szBuff);
			dAverage = (STATICS[i].tOnlineTroubleTime + STATICS[i].tOfflineTroubleTime) * 100;
			dAverage /= (tCurTime - STATICS[i].tBeginTime);
			sprintf(szBuff, "%.2f", dAverage);
			SET(IDC_STOP_RATIO4, szBuff);
			break;
		case 4:
			sprintf(szBuff, "%d", STATICS[i].tOnlineWorkTime/60);
			SET(IDC_ONLINE_WORK5, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOfflineWorkTime/60);
			SET(IDC_OFFLINE_WORK5, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOnlineTroubleTime/60);
			SET(IDC_ONLINE_STOP5, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOfflineTroubleTime/60);
			SET(IDC_OFFLINE_STOP5, szBuff);
			dAverage = (STATICS[i].tOnlineWorkTime + STATICS[i].tOfflineWorkTime) * 100;
			dAverage /= (tCurTime - STATICS[i].tBeginTime);
			sprintf(szBuff, "%.2f", dAverage);
			SET(IDC_WORK_RATIO5, szBuff);
			dAverage = (STATICS[i].tOnlineTroubleTime + STATICS[i].tOfflineTroubleTime) * 100;
			dAverage /= (tCurTime - STATICS[i].tBeginTime);
			sprintf(szBuff, "%.2f", dAverage);
			SET(IDC_STOP_RATIO5, szBuff);
			break;
		case 5:
			sprintf(szBuff, "%d", STATICS[i].tOnlineWorkTime/60);
			SET(IDC_ONLINE_WORK6, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOfflineWorkTime/60);
			SET(IDC_OFFLINE_WORK6, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOnlineTroubleTime/60);
			SET(IDC_ONLINE_STOP6, szBuff);
			sprintf(szBuff, "%d", STATICS[i].tOfflineTroubleTime/60);
			SET(IDC_OFFLINE_STOP6, szBuff);
			dAverage = (STATICS[i].tOnlineWorkTime + STATICS[i].tOfflineWorkTime) * 100;
			dAverage /= (tCurTime - STATICS[i].tBeginTime);
			sprintf(szBuff, "%.2f", dAverage);
			SET(IDC_WORK_RATIO6, szBuff);
			dAverage = (STATICS[i].tOnlineTroubleTime + STATICS[i].tOfflineTroubleTime) * 100;
			dAverage /= (tCurTime - STATICS[i].tBeginTime);
			sprintf(szBuff, "%.2f", dAverage);
			SET(IDC_STOP_RATIO6, szBuff);
			break;
		}
	}

	for(i=0; i<SC_CNT; i++)
	{
		dOnlineWork += STATICS[i].tOnlineWorkTime;
		dOfflineWork += STATICS[i].tOfflineWorkTime;
		dOnlineTrouble += STATICS[i].tOnlineTroubleTime;
		dOfflineTrouble += STATICS[i].tOfflineTroubleTime;
	}

	dAverage = (dOnlineWork / 60) / SC_CNT;
	sprintf(szBuff, "%.2f", dAverage);
	SET(IDC_ONLINE_WORK_AVERAGE, szBuff);
	dAverage = (dOfflineWork / 60) / SC_CNT;
	sprintf(szBuff, "%.2f", dAverage);
	SET(IDC_OFFLINE_WORK_AVERAGE, szBuff);
	dAverage = (dOnlineTrouble / 60) / SC_CNT;
	sprintf(szBuff, "%.2f", dAverage);
	SET(IDC_ONLINE_STOP_AVERAGE, szBuff);
	dAverage = (dOfflineTrouble / 60) / SC_CNT;
	sprintf(szBuff, "%.2f", dAverage);
	SET(IDC_OFFLINE_STOP_AVERAGE, szBuff);

	dAverage = (dOnlineWork + dOfflineWork) * 100;
	dAverage /= ((tCurTime - STATICS[0].tBeginTime) * SC_CNT);
	sprintf(szBuff, "%.2f", dAverage);
	SET(IDC_WORK_RATIO_AVERAGE, szBuff);

	dAverage = (dOnlineTrouble + dOfflineTrouble) * 100;
	dAverage /=	((tCurTime - STATICS[0].tBeginTime) * SC_CNT);
	sprintf(szBuff, "%.2f", dAverage);
	SET(IDC_STOP_RATIO_AVERAGE, szBuff);
}

void CStatisticAvailDlg::OnButtonFile() 
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

	CFileDialog FileDlg(TRUE, NULL, "*.info", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		" ECS Statistics Files (*.info) | *.info ||");

	FileDlg.m_ofn.lpstrInitialDir = szNewDir;
	FileDlg.m_ofn.lpstrTitle = "ECS 통계정보 파일";

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

void CStatisticAvailDlg::Loading()
{
	char szSection[256];
	time_t	tBeginTm;
//	struct	SStatisticInfo	StcInfo[SC_CNT];

	CTime theTime = CTime::GetCurrentTime();
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

void CStatisticAvailDlg::OnButtonRefresh() 
{
	// TODO: Add your control notification handler code here
	CTime theTime = CTime::GetCurrentTime();
	m_nDay = theTime.GetDay();
	CString strTemp;
	strTemp.Format("%.2d/%.2d", theTime.GetMonth(), m_nDay);
	GetDlgItem(IDC_EDIT_DATE)->SetWindowText(strTemp);

	m_bSelected = FALSE;
	Refresh(m_pDoc->m_pStatistic->m_sSTC);
}

void CStatisticAvailDlg::OnButtonOnlineChart() 
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

void CStatisticAvailDlg::OnButtonOfflineChart() 
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

void CStatisticAvailDlg::OnButtonRatioChart() 
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

void CStatisticAvailDlg::OnButtonSumCount() 
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

void CStatisticAvailDlg::OnButtonOnofflineChart() 
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
