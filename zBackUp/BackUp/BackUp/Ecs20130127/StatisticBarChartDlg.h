#if !defined(AFX_STATISTICBARCHARTDLG_H__8AFBD39A_8C1F_11D2_94DF_080009A4CC9D__INCLUDED_)
#define AFX_STATISTICBARCHARTDLG_H__8AFBD39A_8C1F_11D2_94DF_080009A4CC9D__INCLUDED_

#include "mschart1.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StatisticBarChartDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatisticBarChartDlg dialog

class CStatisticBarChartDlg : public CDialog
{
// Construction
public:
	CStatisticBarChartDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatisticBarChartDlg)
	enum { IDD = IDD_STATISTICS_BAR };
	CMSChart	m_pMSChart;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatisticBarChartDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Attribute
public:
	int		m_nCMD;
	BOOL	m_bToday;
	struct	SStatisticInfo	m_sStcInfo[SC_CNT];
	void	InitChart();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStatisticBarChartDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio2darea();
	afx_msg void OnRadio2dbar();
	afx_msg void OnRadio2dline();
	afx_msg void OnRadio2dpie();
	afx_msg void OnRadio2dstep();
	afx_msg void OnRadio2dxy();
	afx_msg void OnRadio3darea();
	afx_msg void OnRadio3dbar();
	afx_msg void OnRadio3dline();
	afx_msg void OnRadio3step();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATISTICBARCHARTDLG_H__8AFBD39A_8C1F_11D2_94DF_080009A4CC9D__INCLUDED_)
