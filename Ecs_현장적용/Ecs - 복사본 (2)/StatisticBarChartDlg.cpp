// StatisticBarChartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "Statistic.h"
#include "StatisticBarChartDlg.h"
#include "vcplot.h"
#include "vcaxis.h"
#include "vcaxistitle.h"
#include <EcsEnv.h>
#include <atlbase.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatisticBarChartDlg dialog


CStatisticBarChartDlg::CStatisticBarChartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatisticBarChartDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatisticBarChartDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStatisticBarChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatisticBarChartDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_MSCHART1, m_pMSChart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatisticBarChartDlg, CDialog)
	//{{AFX_MSG_MAP(CStatisticBarChartDlg)
	ON_BN_CLICKED(IDC_RADIO_2DAREA, OnRadio2darea)
	ON_BN_CLICKED(IDC_RADIO_2DBAR, OnRadio2dbar)
	ON_BN_CLICKED(IDC_RADIO_2DLINE, OnRadio2dline)
	ON_BN_CLICKED(IDC_RADIO_2DPIE, OnRadio2dpie)
	ON_BN_CLICKED(IDC_RADIO_2DSTEP, OnRadio2dstep)
	ON_BN_CLICKED(IDC_RADIO_2DXY, OnRadio2dxy)
	ON_BN_CLICKED(IDC_RADIO_3DAREA, OnRadio3darea)
	ON_BN_CLICKED(IDC_RADIO_3DBAR, OnRadio3dbar)
	ON_BN_CLICKED(IDC_RADIO_3DLINE, OnRadio3dline)
	ON_BN_CLICKED(IDC_RADIO_3STEP, OnRadio3step)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatisticBarChartDlg message handlers

BOOL CStatisticBarChartDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitChart();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStatisticBarChartDlg::InitChart()
{
	char	szBuff[124], tmpBuff[64];
	int		i, j, nJobSum=0, nErrorSum=0;
	time_t	tCurTime;
	double  dOnOfflineWork=0, dOnOfflineTrouble=0, dOnlineWork=0, dOfflineWork=0, dOnlineTrouble=0, dOfflineTrouble=0;
	double	dAverage;
	struct  tm *StartTm;
	VARIANT	index;

	StartTm = localtime(&m_sStcInfo[0].tBeginTime);

	if(m_bToday)	time(&tCurTime);
	else			tCurTime = m_sStcInfo[0].tBeginTime + (24 - StartTm->tm_hour) * 3600;


	switch (m_nCMD)
	{
	case	CMD_ON_OFFLINE_CHART:
		sprintf(szBuff, "< 가동시간/장애시간 > OnLine+OffLine");
		m_pMSChart.SetTextLengthType((long) strlen(szBuff));
		m_pMSChart.SetTitleText(LPCTSTR (szBuff));
		sprintf(tmpBuff, "사용시간/분 ");

		for (i=0; i<2; i++)
		{
			for (j=0; j<SC_CNT; j++)
			{
				m_pMSChart.SetColumn(i+1);
				m_pMSChart.SetRow(j+1);
				if(i==0)	sprintf(szBuff, "%.d", (m_sStcInfo[j].tOnlineWorkTime + m_sStcInfo[j].tOfflineWorkTime)/60);
				else		sprintf(szBuff, "%.d", (m_sStcInfo[j].tOnlineTroubleTime + m_sStcInfo[j].tOfflineTroubleTime)/60);
				m_pMSChart.SetData(LPCSTR (szBuff));
			}
		}

		for(i=0; i<SC_CNT; i++)
		{
			dOnOfflineWork += m_sStcInfo[i].tOnlineWorkTime;
			dOnOfflineWork += m_sStcInfo[i].tOfflineWorkTime;
			dOnOfflineTrouble += m_sStcInfo[i].tOnlineTroubleTime;
			dOnOfflineTrouble += m_sStcInfo[i].tOfflineTroubleTime;
		}

		dAverage = (dOnOfflineWork / 60) / SC_CNT;
		sprintf(szBuff, "%.2f", dAverage);
		m_pMSChart.SetColumn(1);
		m_pMSChart.SetRow(SC_CNT+1);
		m_pMSChart.SetData(LPCSTR (szBuff));

		dAverage = (dOnOfflineTrouble / 60) / SC_CNT;
		sprintf(szBuff, "%.2f", dAverage);
		m_pMSChart.SetColumn(2);
		m_pMSChart.SetRow(SC_CNT+1);
		m_pMSChart.SetData(LPCSTR (szBuff));
		break;
	case	CMD_ONLINE_CHART:
		sprintf(szBuff, "< 가동시간/장애시간 > On-Line");
		m_pMSChart.SetTextLengthType((long) strlen(szBuff));
		m_pMSChart.SetTitleText(LPCTSTR (szBuff));
		sprintf(tmpBuff, "사용시간/분 ");
/*
		m_sStcInfo[0].tOnlineWorkTime = 60000;
		m_sStcInfo[0].tOnlineTroubleTime = 20000;
		m_sStcInfo[1].tOnlineWorkTime = 80000;
		m_sStcInfo[1].tOnlineTroubleTime = 0;
		m_sStcInfo[2].tOnlineWorkTime = 70000;
		m_sStcInfo[2].tOnlineTroubleTime = 10000;
		m_sStcInfo[3].tOnlineWorkTime = 50000;
		m_sStcInfo[3].tOnlineTroubleTime = 30000;
*/
		for (i=0; i<2; i++)
		{
			for (j=0; j<SC_CNT; j++)
			{
				m_pMSChart.SetColumn(i+1);
				m_pMSChart.SetRow(j+1);
				if(i==0)	sprintf(szBuff, "%.d", m_sStcInfo[j].tOnlineWorkTime/60);
				else		sprintf(szBuff, "%.d", m_sStcInfo[j].tOnlineTroubleTime/60);
				m_pMSChart.SetData(LPCSTR (szBuff));
			}
		}

		for(i=0; i<SC_CNT; i++)
		{
			dOnlineWork += m_sStcInfo[i].tOnlineWorkTime;
			dOnlineTrouble += m_sStcInfo[i].tOnlineTroubleTime;
		}

		dAverage = (dOnlineWork / 60) / SC_CNT;
		sprintf(szBuff, "%.2f", dAverage);
		m_pMSChart.SetColumn(1);
		m_pMSChart.SetRow(SC_CNT+1);
		m_pMSChart.SetData(LPCSTR (szBuff));

		dAverage = (dOnlineTrouble / 60) / SC_CNT;
		sprintf(szBuff, "%.2f", dAverage);
		m_pMSChart.SetColumn(2);
		m_pMSChart.SetRow(SC_CNT+1);
		m_pMSChart.SetData(LPCSTR (szBuff));
		break;
	case	CMD_OFFLINE_CHART:
		sprintf(szBuff, "< 가동시간/장애시간 > Off-Line");
		m_pMSChart.SetTextLengthType((long) strlen(szBuff));
		m_pMSChart.SetTitleText(LPCTSTR (szBuff));
		sprintf(tmpBuff, "사용시간/분 ");

		for (i=0; i<2; i++)
		{
			for (j=0; j<SC_CNT; j++)
			{
				m_pMSChart.SetColumn(i+1);
				m_pMSChart.SetRow(j+1);
				if(i==0)	sprintf(szBuff, "%.d", m_sStcInfo[j].tOfflineWorkTime/60);
				else		sprintf(szBuff, "%.d", m_sStcInfo[j].tOfflineTroubleTime/60);
				m_pMSChart.SetData(LPCSTR (szBuff));
			}
		}

		for(i=0; i<SC_CNT; i++)
		{
			dOfflineWork += m_sStcInfo[i].tOfflineWorkTime;
			dOfflineTrouble += m_sStcInfo[i].tOfflineTroubleTime;
		}

		dAverage = (dOfflineWork / 60) / SC_CNT;
		sprintf(szBuff, "%.2f", dAverage);
		m_pMSChart.SetColumn(1);
		m_pMSChart.SetRow(SC_CNT+1);
		m_pMSChart.SetData(LPCSTR (szBuff));

		dAverage = (dOfflineTrouble / 60) / SC_CNT;
		sprintf(szBuff, "%.2f", dAverage);
		m_pMSChart.SetColumn(2);
		m_pMSChart.SetRow(SC_CNT+1);
		m_pMSChart.SetData(LPCSTR (szBuff));
		break;
	case	CMD_RATIO_CHART:
		sprintf(szBuff, "< 가동률/장애률 >");
		m_pMSChart.SetTextLengthType((long) strlen(szBuff));
		m_pMSChart.SetTitleText(LPCTSTR (szBuff));
		sprintf(tmpBuff, "백분률/%% ");

		for(i=0; i<2; i++)
		{
			for (j=0; j<SC_CNT; j++)
			{
				m_pMSChart.SetColumn(i+1);
				m_pMSChart.SetRow(j+1);
				if(i==0)
				{
					dAverage = (m_sStcInfo[j].tOnlineWorkTime + m_sStcInfo[j].tOfflineWorkTime) * 100;
					dAverage /= (tCurTime - m_sStcInfo[j].tBeginTime);
				}
				else
				{
					dAverage = (m_sStcInfo[j].tOnlineTroubleTime + m_sStcInfo[j].tOfflineTroubleTime) * 100;
					dAverage /= (tCurTime - m_sStcInfo[j].tBeginTime);
				}
				sprintf(szBuff, "%.2f", dAverage);
				m_pMSChart.SetData(LPCSTR (szBuff));
			}
		}

		for(i=0; i<SC_CNT; i++)
		{
			dOnlineWork += m_sStcInfo[i].tOnlineWorkTime;
			dOfflineWork += m_sStcInfo[i].tOfflineWorkTime;
			dOnlineTrouble += m_sStcInfo[i].tOnlineTroubleTime;
			dOfflineTrouble += m_sStcInfo[i].tOfflineTroubleTime;
		}

		dAverage = (dOnlineWork + dOfflineWork) * 100;
		dAverage /= ((tCurTime - m_sStcInfo[0].tBeginTime) * SC_CNT);
		sprintf(szBuff, "%.2f", dAverage);
		m_pMSChart.SetColumn(1);
		m_pMSChart.SetRow(SC_CNT+1);
		m_pMSChart.SetData(LPCSTR (szBuff));

		dAverage = (dOnlineTrouble + dOfflineTrouble) * 100;
		dAverage /=	((tCurTime - m_sStcInfo[0].tBeginTime) * SC_CNT);
		sprintf(szBuff, "%.2f", dAverage);
		m_pMSChart.SetColumn(2);
		m_pMSChart.SetRow(SC_CNT+1);
		m_pMSChart.SetData(LPCSTR (szBuff));
		m_pMSChart.SetChartType(14L);	// 2D Pie

		break;
	case	CMD_COUNT_CHART:
		sprintf(szBuff, "< 물량처리건수/장애건수 >");
		m_pMSChart.SetTextLengthType((long) strlen(szBuff));
		m_pMSChart.SetTitleText(LPCTSTR (szBuff));
		sprintf(tmpBuff, "건수/건 ");
		for(i=0; i<2; i++)
		{
			for (j=0; j<SC_CNT; j++)
			{
				m_pMSChart.SetColumn(i+1);
				m_pMSChart.SetRow(j+1);
				if(i==0)	sprintf(szBuff, "%d", m_sStcInfo[j].nOnlineJobSum + m_sStcInfo[j].nOfflineJobSum);
				else		sprintf(szBuff, "%d", m_sStcInfo[j].nErrorSum);
				m_pMSChart.SetData(LPCSTR (szBuff));
			}
		}

		for(i=0; i<SC_CNT; i++)
		{
			nJobSum += m_sStcInfo[i].nOnlineJobSum;
			nJobSum += m_sStcInfo[i].nOfflineJobSum;
			nErrorSum += m_sStcInfo[i].nErrorSum;
		}

		dAverage = nJobSum /SC_CNT;
		sprintf(szBuff, "%.2f", dAverage);
		m_pMSChart.SetColumn(1);
		m_pMSChart.SetRow(SC_CNT+1);
		m_pMSChart.SetData(LPCSTR (szBuff));

		dAverage = nErrorSum /SC_CNT;
		sprintf(szBuff, "%.2f", dAverage);
		m_pMSChart.SetColumn(2);
		m_pMSChart.SetRow(SC_CNT+1);
		m_pMSChart.SetData(LPCSTR (szBuff));
		break;
	}

	index.lVal=1;
	m_pMSChart.GetPlot().GetAxis(1, index).GetAxisTitle().SetText(LPCTSTR (tmpBuff));

}

void CStatisticBarChartDlg::OnRadio2darea() 
{
	m_pMSChart.SetChartType(5L);

}

void CStatisticBarChartDlg::OnRadio2dbar() 
{
	m_pMSChart.SetChartType(1L);
	
}

void CStatisticBarChartDlg::OnRadio2dline() 
{
	m_pMSChart.SetChartType(3L);
	
}

void CStatisticBarChartDlg::OnRadio2dpie() 
{
	m_pMSChart.SetChartType(14L);
	
}

void CStatisticBarChartDlg::OnRadio2dstep() 
{
	m_pMSChart.SetChartType(7L);
	
}

void CStatisticBarChartDlg::OnRadio2dxy() 
{
	m_pMSChart.SetChartType(16L);
	
}

void CStatisticBarChartDlg::OnRadio3darea() 
{
	m_pMSChart.SetChartType(4L);
	
}

void CStatisticBarChartDlg::OnRadio3dbar() 
{
	m_pMSChart.SetChartType(0L);
	
}

void CStatisticBarChartDlg::OnRadio3dline() 
{
	m_pMSChart.SetChartType(2L);
	
}

void CStatisticBarChartDlg::OnRadio3step() 
{
	m_pMSChart.SetChartType(6L);
	
}
