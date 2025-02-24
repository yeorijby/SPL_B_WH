// EcsView.cpp : implementation of the CEcsView class
//

#include "stdafx.h"
#include "Ecs.h"

#include "EcsDoc.h"
#include "EcsView.h"
#include "MainFrm.h"

#include "control.h"
#include "StackerTwinDlg.h"
#include "OpBoxDlg.h"
#include "ResetOrderDlg.h"
#include "RgvDlg.h"
#include "CommonDlg.h"
#include "CvLineDlg.h"

#include "EcsDef.h"
#include <EcsEnv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEcsView

IMPLEMENT_DYNCREATE(CEcsView, CFormView)

BEGIN_MESSAGE_MAP(CEcsView, CFormView)
	ON_MESSAGE(WM_USER_CV_NOTIFY, OnCvNotify)
	ON_MESSAGE(WM_USER_SC_NOTIFY, OnScNotify)
	ON_MESSAGE(WM_USER_RGV_NOTIFY, OnRgvNotify)
	ON_MESSAGE(WM_USER_JOB_NOTIFY, OnJobNotify)
	ON_MESSAGE(WM_USER_HOST_NOTIFY, OnHostNotify)
	ON_MESSAGE(WM_USER_ECS_NOTIFY, OnEcsNotify)
	//{{AFX_MSG_MAP(CEcsView)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_CHECK_BUFFER_FULL_1, OnCheckBufferFull1)
	ON_BN_CLICKED(IDC_CHECK_BUFFER_FULL_2, OnCheckBufferFull2)
	ON_BN_CLICKED(IDC_CHECK_BUFFER_FULL_3, OnCheckBufferFull3)
	ON_BN_CLICKED(IDC_CHECK_TROUBLE, OnCheckTrouble)
	ON_BN_CLICKED(IDC_CHECK_STOP, OnCheckStop)
	ON_BN_CLICKED(IDC_CHECK_SET_LINE, OnCheckSetLine)
	ON_BN_CLICKED(IDC_CHECK_SET_LINE2, OnCheckSetLine2)
	ON_BN_CLICKED(IDC_CHECK_SET_CHANGE_COUNT, OnCheckChangeCount)
	ON_BN_CLICKED(IDC_CHECK_SET_TEST, OnCheckTest)
	ON_BN_CLICKED(IDC_BUTTON_SIGNAL, OnButtonSignal)
	ON_BN_CLICKED(IDC_CHECK_SET_PRIORITY, OnCheckSetPriority)
	ON_BN_CLICKED(IDC_CHECK_LINE_EMERGENCY, OnCheckLineEmergency)
	ON_BN_CLICKED(IDC_CHECK_STACKING1, OnCheckStacking1)
	ON_BN_CLICKED(IDC_CHECK_STACKING2, OnCheckStacking2)
	ON_BN_CLICKED(IDC_CHECK_BUFFER_FULL_4, OnCheckBufferFull4)
	ON_BN_CLICKED(IDC_CHECK_BUFFER_FULL_5, OnCheckBufferFull5)
	ON_BN_CLICKED(IDC_CHECK_BUFFER_FULL_6, OnCheckBufferFull6)
	ON_BN_CLICKED(IDC_BUTTON_RESET_INCOUNT, OnButtonResetIncount)
	ON_BN_CLICKED(IDC_CHECK_BUFFER_STOP, OnCheckBufferStop)
	ON_BN_CLICKED(IDC_CHECK_STACK_EMERGENCY, OnCheckStackEmergency)
	ON_BN_CLICKED(IDC_CHECK_SC_STO_SUSPEND, OnCheckScStoSuspend)
	ON_BN_CLICKED(IDC_CHECK_SC_RET_SUSPEND, OnCheckScRetSuspend)
	ON_BN_CLICKED(IDC_CHECK_LINE_TROUBLE, OnCheckLineTrouble)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEcsView construction/destruction

CEcsView::CEcsView()
	: CFormView(CEcsView::IDD)
{
	//{{AFX_DATA_INIT(CEcsView)
	m_b4Check = FALSE;
	m_b5Check = FALSE;
	m_b6Check = FALSE;
	m_b7Check = FALSE;
	m_b8Check = FALSE;
	m_b9Check = FALSE;

    m_bTroubleCheck = FALSE;
    m_bLineTroubleCheck = FALSE;
    m_bStopCheck = FALSE;
    m_bBufferStopCheck = FALSE;
	m_bLineCheck = FALSE;
	m_bLineCheck2 = FALSE;
	m_bCountCheck = FALSE;
	m_bPriorityCheck = FALSE;
	m_bLineEmergencyCheck = FALSE;

	m_bStackingCheck1 = FALSE;
	m_bStackingCheck2 = FALSE;

	m_bAllSEmergenCheck = FALSE;
	m_bAllScStoSuspend = FALSE;
	m_bAllScRetSuspend = FALSE;

	m_bTestCheck = TRUE;

		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here
}

CEcsView::~CEcsView()
{

}

void CEcsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEcsView)
	DDX_Check(pDX, IDC_CHECK_BUFFER_FULL_1, m_b4Check);
	DDX_Check(pDX, IDC_CHECK_BUFFER_FULL_2, m_b5Check);
	DDX_Check(pDX, IDC_CHECK_BUFFER_FULL_3, m_b6Check);
	DDX_Check(pDX, IDC_CHECK_BUFFER_FULL_4, m_b7Check);
	DDX_Check(pDX, IDC_CHECK_BUFFER_FULL_5, m_b8Check);
	DDX_Check(pDX, IDC_CHECK_BUFFER_FULL_6, m_b9Check);

	DDX_Check(pDX, IDC_CHECK_TROUBLE, m_bTroubleCheck);
	DDX_Check(pDX, IDC_CHECK_LINE_TROUBLE, m_bLineTroubleCheck);
	DDX_Check(pDX, IDC_CHECK_STOP, m_bStopCheck);
	DDX_Check(pDX, IDC_CHECK_BUFFER_STOP, m_bBufferStopCheck);
	
	DDX_Check(pDX, IDC_CHECK_SET_LINE, m_bLineCheck);
	DDX_Check(pDX, IDC_CHECK_SET_LINE2, m_bLineCheck2);
	DDX_Check(pDX, IDC_CHECK_SET_CHANGE_COUNT, m_bCountCheck);
	DDX_Check(pDX, IDC_CHECK_SET_TEST, m_bTestCheck);

	DDX_Check(pDX, IDC_CHECK_SET_PRIORITY, m_bPriorityCheck);
	DDX_Check(pDX, IDC_CHECK_LINE_EMERGENCY, m_bLineEmergencyCheck);

	DDX_Check(pDX, IDC_CHECK_STACKING1, m_bStackingCheck1);
	DDX_Check(pDX, IDC_CHECK_STACKING2, m_bStackingCheck2);

	DDX_Check(pDX, IDC_CHECK_STACK_EMERGENCY, m_bAllSEmergenCheck);
	DDX_Check(pDX, IDC_CHECK_SC_STO_SUSPEND, m_bAllScStoSuspend);
	DDX_Check(pDX, IDC_CHECK_SC_RET_SUSPEND, m_bAllScRetSuspend);
	
	
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
/*	DDX_Control(pDX, IDC_EDIT_4GRUP_IN,  m_edt4GroupInCount);
	DDX_Control(pDX, IDC_EDIT_4GRUP_OUT, m_edt4GroupOutCount);
	DDX_Control(pDX, IDC_EDIT_5GRUP_IN,  m_edt5GroupInCount);
	DDX_Control(pDX, IDC_EDIT_5GRUP_OUT, m_edt5GroupOutCount);
	DDX_Control(pDX, IDC_EDIT_6GRUP_IN,  m_edt6GroupInCount);
	DDX_Control(pDX, IDC_EDIT_6GRUP_OUT, m_edt6GroupOutCount);
*/
}

BOOL CEcsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEcsView diagnostics

#ifdef _DEBUG
void CEcsView::AssertValid() const
{
	CFormView::AssertValid();
}

void CEcsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CEcsDoc* CEcsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEcsDoc)));
	return (CEcsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEcsView message handlers

void CEcsView::OnTimer(UINT nIDEvent) 
{
	CEcsDoc* pDoc = GetDocument();
	CEcsApp* pWnd = (CEcsApp *)AfxGetApp();
	//TEST

/*	CString strTemp="출하: ", strTemp2="";
	pDoc->m_strCodeNum = "56712343";
	pDoc->m_nPeriodNum = 20130213;
	strTemp2 = "소보루빵도포물[리뉴얼]                                                            "; 
	//strTemp2.TrimRight();
	strTemp2.TrimLeft();
	strTemp += strTemp2;
	pDoc->m_strProdName = strTemp;
	if(pDoc->m_pEcsCl != NULL)
		pDoc->m_pEcsCl->EcsClientSendData();
*/

	//////////////////////////////////
/*
	BOOL bLineCheck=FALSE;
	static int nLineCount=0;

	static int m_nRetSiteNextRtn=0;
	int nRank=m_nRetSiteNextRtn;

	if(m_nRetSiteNextRtn > 12)
		nRank=m_nRetSiteNextRtn=0;

	for(int i=m_nRetSiteNextRtn; i<m_nRetSiteNextRtn+12; i++)
	{
		if(i >= 12)
			nRank = i-12;

		if ( TestMethod(&bLineCheck) )
		{
			nLineCount++;
			if(nLineCount == 6)
			{
				nLineCount=0;
				m_nRetSiteNextRtn++;
				return;
			}
		}

		nRank++;
	}
*/
   //////////////////////////////////

	CGmsBtnControl* pFullBuffer1 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_BUFF_1);
	if ( pFullBuffer1 != NULL )
	{
		pFullBuffer1->SetEnabledBtnColor(pDoc->m_b4groupCheck ? CYAN : YELLOW);
	}

	CGmsBtnControl* pFullBuffer2 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_BUFF_2);
	if ( pFullBuffer2 != NULL )
	{
		pFullBuffer2->SetEnabledBtnColor(pDoc->m_b5groupCheck ? CYAN : YELLOW);
	}

	CGmsBtnControl* pFullBuffer3 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_BUFF_3);
	if ( pFullBuffer3 != NULL )
	{
		pFullBuffer3->SetEnabledBtnColor(pDoc->m_b6groupCheck ? CYAN : YELLOW);
	}
	////4Group
	CGmsBtnControl* p4GBufferLineIn_1 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_4IN_BUFF_1);
	if ( p4GBufferLineIn_1 != NULL )
	{
		p4GBufferLineIn_1->SetEnabledBtnColor(pDoc->m_b4groupBuffIn[0] ? LIGHT_GREEN : PALE_GRAY);
	}

	CGmsBtnControl* p4GBufferLineIn_2 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_4IN_BUFF_2);
	if ( p4GBufferLineIn_2 != NULL )
	{
		p4GBufferLineIn_2->SetEnabledBtnColor(pDoc->m_b4groupBuffIn[1] ? LIGHT_GREEN : PALE_GRAY);
	}

	CGmsBtnControl* p4GBufferLineIn_3 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_4IN_BUFF_3);
	if ( p4GBufferLineIn_3 != NULL )
	{
		p4GBufferLineIn_3->SetEnabledBtnColor(pDoc->m_b4groupBuffIn[2] ? LIGHT_GREEN : PALE_GRAY);
	}

	CGmsBtnControl* p4GBufferLineIn_4 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_4IN_BUFF_4);
	if ( p4GBufferLineIn_4 != NULL )
	{
		p4GBufferLineIn_4->SetEnabledBtnColor(pDoc->m_b4groupBuffIn[3] ? LIGHT_GREEN : PALE_GRAY);
	}

	CGmsBtnControl* p4GBufferLineIn_5 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_4IN_BUFF_5);
	if ( p4GBufferLineIn_5 != NULL )
	{
		p4GBufferLineIn_5->SetEnabledBtnColor(pDoc->m_b4groupBuffIn[4] ? LIGHT_GREEN : PALE_GRAY);
	}

	CGmsBtnControl* p4GBufferLineIn_6 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_4IN_BUFF_6);
	if ( p4GBufferLineIn_6 != NULL )
	{
		p4GBufferLineIn_6->SetEnabledBtnColor(pDoc->m_b4groupBuffIn[5] ? LIGHT_GREEN : PALE_GRAY);
	}

	////5Group
	CGmsBtnControl* p5GBufferLineIn_1 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_5IN_BUFF_1);
	if ( p5GBufferLineIn_1 != NULL )
	{
		p5GBufferLineIn_1->SetEnabledBtnColor(pDoc->m_b5groupBuffIn[0] ? LIGHT_GREEN : PALE_GRAY);
	}

	CGmsBtnControl* p5GBufferLineIn_2 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_5IN_BUFF_2);
	if ( p5GBufferLineIn_2 != NULL )
	{
		p5GBufferLineIn_2->SetEnabledBtnColor(pDoc->m_b5groupBuffIn[1] ? LIGHT_GREEN : PALE_GRAY);
	}

	CGmsBtnControl* p5GBufferLineIn_3 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_5IN_BUFF_3);
	if ( p5GBufferLineIn_3 != NULL )
	{
		p5GBufferLineIn_3->SetEnabledBtnColor(pDoc->m_b5groupBuffIn[2] ? LIGHT_GREEN : PALE_GRAY);
	}

	CGmsBtnControl* p5GBufferLineIn_4 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_5IN_BUFF_4);
	if ( p5GBufferLineIn_4 != NULL )
	{
		p5GBufferLineIn_4->SetEnabledBtnColor(pDoc->m_b5groupBuffIn[3] ? LIGHT_GREEN : PALE_GRAY);
	}

	CGmsBtnControl* p5GBufferLineIn_5 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_5IN_BUFF_5);
	if ( p5GBufferLineIn_5 != NULL )
	{
		p5GBufferLineIn_5->SetEnabledBtnColor(pDoc->m_b5groupBuffIn[4] ? LIGHT_GREEN : PALE_GRAY);
	}

	CGmsBtnControl* p5GBufferLineIn_6 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_5IN_BUFF_6);
	if ( p5GBufferLineIn_6 != NULL )
	{
		p5GBufferLineIn_6->SetEnabledBtnColor(pDoc->m_b5groupBuffIn[5] ? LIGHT_GREEN : PALE_GRAY);
	}

	////6Group
	CGmsBtnControl* p6GBufferLineIn_1 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_6IN_BUFF_1);
	if ( p6GBufferLineIn_1 != NULL )
	{
		p6GBufferLineIn_1->SetEnabledBtnColor(pDoc->m_b6groupBuffIn[0] ? LIGHT_GREEN : PALE_GRAY);
	}

	CGmsBtnControl* p6GBufferLineIn_2 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_6IN_BUFF_2);
	if ( p6GBufferLineIn_2 != NULL )
	{
		p6GBufferLineIn_2->SetEnabledBtnColor(pDoc->m_b6groupBuffIn[1] ? LIGHT_GREEN : PALE_GRAY);
	}

	CGmsBtnControl* p6GBufferLineIn_3 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_6IN_BUFF_3);
	if ( p6GBufferLineIn_3 != NULL )
	{
		p6GBufferLineIn_3->SetEnabledBtnColor(pDoc->m_b6groupBuffIn[2] ? LIGHT_GREEN : PALE_GRAY);
	}

	CGmsBtnControl* p6GBufferLineIn_4 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_6IN_BUFF_4);
	if ( p6GBufferLineIn_4 != NULL )
	{
		p6GBufferLineIn_4->SetEnabledBtnColor(pDoc->m_b6groupBuffIn[3] ? LIGHT_GREEN : PALE_GRAY);
	}

	CGmsBtnControl* p6GBufferLineIn_5 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_6IN_BUFF_5);
	if ( p6GBufferLineIn_5 != NULL )
	{
		p6GBufferLineIn_5->SetEnabledBtnColor(pDoc->m_b6groupBuffIn[4] ? LIGHT_GREEN : PALE_GRAY);
	}

	CGmsBtnControl* p6GBufferLineIn_6 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_6IN_BUFF_6);
	if ( p6GBufferLineIn_6 != NULL )
	{
		p6GBufferLineIn_6->SetEnabledBtnColor(pDoc->m_b6groupBuffIn[5] ? LIGHT_GREEN : PALE_GRAY);
	}

/*	CGmsBtnControl* pStacking1 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_STACKING1);
	if ( pStacking1 != NULL )
	{
		pStacking1->SetEnabledBtnColor(pDoc->m_bWriteStackingCheck1 ? CYAN : YELLOW);
	}

	CGmsBtnControl* pStacking2 = (CGmsBtnControl*)GetDlgItem(IDC_GMSBTNCTRL_STACKING2);
	if ( pStacking2 != NULL )
	{
		pStacking2->SetEnabledBtnColor(pDoc->m_bWriteStackingCheck2 ? CYAN : YELLOW);
	}
*/
	static int nCount = 1;

	char  sz4GroupBatch[32], 
		  sz4GroupPallet[32], 
		  sz5GroupBatch[32], 
		  sz5GroupPallet[32],
		  sz6GroupBatch[32],
		  sz6GroupPallet[32],
		  sz7GroupBatch[32],
		  sz7GroupPallet[32],

		  sz4GroupInCount[32], 
		  sz4GroupOutCount[32], 
		  sz5GroupInCount[32], 
		  sz5GroupOutCount[32],
		  sz6GroupInCount[32],

		  sz7GroupInCount[32],

		  sz6GroupOutCount[32],
		  sz4GroupInternalCount[32],
		  sz5GroupInternalCount[32],
		  sz6GroupInternalCount[32];

	pDoc->DisplayMessage();

	sprintf(sz4GroupBatch, "%d", pDoc->m_n4GroupInternalBatch);
	SET(IDC_EDIT_4GRUP_BATCHNUM, sz4GroupBatch );
	sprintf(sz4GroupPallet, "%d", pDoc->m_n4GroupInternalPallet);
	SET(IDC_EDIT_4GRUP_PALLETNUM, sz4GroupPallet );

	sprintf(sz5GroupBatch, "%d", pDoc->m_n5GroupInternalBatch);
	SET(IDC_EDIT_5GRUP_BATCHNUM, sz5GroupBatch );
	sprintf(sz5GroupPallet, "%d", pDoc->m_n5GroupInternalPallet);
	SET(IDC_EDIT_5GRUP_PALLETNUM, sz5GroupPallet );

	sprintf(sz6GroupBatch, "%d", pDoc->m_n6GroupInternalBatch);
	SET(IDC_EDIT_6GRUP_BATCHNUM, sz6GroupBatch );
	sprintf(sz6GroupPallet, "%d", pDoc->m_n6GroupInternalPallet);
	SET(IDC_EDIT_6GRUP_PALLETNUM, sz6GroupPallet );

	sprintf(sz7GroupBatch, "%d", pDoc->m_n7GroupInternalBatch);
	SET(IDC_EDIT_7GRUP_BATCHNUM, sz7GroupBatch );
	sprintf(sz7GroupPallet, "%d", pDoc->m_n7GroupInternalPallet);
	SET(IDC_EDIT_7GRUP_PALLETNUM, sz7GroupPallet );

	sprintf(sz4GroupInCount, "%d", pDoc->m_n4GroupInCount);
	SET(IDC_EDIT_4GRUP_IN, sz4GroupInCount );
	sprintf(sz4GroupOutCount, "%d", pDoc->m_n4GroupOutCount);
	SET(IDC_EDIT_4GRUP_OUT, sz4GroupOutCount );

	sprintf(sz5GroupInCount, "%d", pDoc->m_n5GroupInCount);
	SET(IDC_EDIT_5GRUP_IN, sz5GroupInCount );
	sprintf(sz5GroupOutCount, "%d", pDoc->m_n5GroupOutCount);
	SET(IDC_EDIT_5GRUP_OUT, sz5GroupOutCount );

	sprintf(sz6GroupInCount, "%d", pDoc->m_n6GroupInCount);
	SET(IDC_EDIT_6GRUP_IN, sz6GroupInCount );
	sprintf(sz6GroupOutCount, "%d", pDoc->m_n6GroupOutCount);
	SET(IDC_EDIT_6GRUP_OUT, sz6GroupOutCount );

	sprintf(sz7GroupInCount, "%d", pDoc->m_n7GroupInCount);
	SET(IDC_EDIT_7GRUP_IN, sz7GroupInCount );

	sprintf(sz4GroupInternalCount, "%d", pDoc->m_n4goupBuffCouter);
	SET(IDC_EDIT_4GRUP_INTERNALCOUNT, sz4GroupInternalCount );

	sprintf(sz5GroupInternalCount, "%d", pDoc->m_n5goupBuffCouter);
	SET(IDC_EDIT_5GRUP_INTERNALCOUNT, sz5GroupInternalCount );

	sprintf(sz6GroupInternalCount, "%d", pDoc->m_n6goupBuffCouter);
	SET(IDC_EDIT_6GRUP_INTERNALCOUNT, sz6GroupInternalCount );

	CString strTem;

	strTem.Format("%s", pDoc->m_strCodeNum);
	SET(IDC_EDIT_CODE, strTem );

	//strTem.Format("%s", pDoc->m_strDualCheck);
	strTem.Format("%d%s", pDoc->m_nLineModeAB , pDoc->m_strDualCheck);
	SET(IDC_EDIT1_DUALCELL, strTem );

	strTem.Format("%s", pDoc->m_strCodeNum2);
	SET(IDC_EDIT_CODE2, strTem );

	static int nCvLuggNum = -1;
	static int nScLuggNum1 = -1;
	static int nScLuggNum2 = -1;
	static int nScLuggNum3 = -1;
	static int nScLuggNum4 = -1;
	static int nRtvLuggNum1 = -1;
	static int nRtvLuggNum2 = -1;
	static int nRtvLuggNum3 = -1;
	static int nRtvLuggNum4 = -1;

	if (nCvLuggNum != pDoc->m_ConveyorTrackInfo[702-1].m_nLuggNum)
	{
		nCvLuggNum = pDoc->m_ConveyorTrackInfo[702-1].m_nLuggNum;

		CMoveJobItem *pMoveJobItem = pDoc->m_pMoveJob->Find(nCvLuggNum);
		if ( pMoveJobItem != NULL )
		{
			strTem.Format("%d", pMoveJobItem->m_nLineNum);
			SET(IDC_EDIT_CV_LINE, strTem );
		}
		else
			SET(IDC_EDIT_CV_LINE, "" );
	}

	if (nScLuggNum1 != pDoc->m_ConveyorTrackInfo[746-1].m_nLuggNum)
	{
		nScLuggNum1 = pDoc->m_ConveyorTrackInfo[746-1].m_nLuggNum;

		CMoveJobItem *pMoveJobItem = pDoc->m_pMoveJob->Find(nScLuggNum1);
		if ( pMoveJobItem != NULL )
		{
			strTem.Format("%d", pMoveJobItem->m_nLineNum);
			SET(IDC_EDIT_SC_LINE1, strTem );
		}
		else
			SET(IDC_EDIT_SC_LINE1, "" );
	}

	if (nScLuggNum2 != pDoc->m_ConveyorTrackInfo[746-1].m_nLuggNum2)
	{
		nScLuggNum2 = pDoc->m_ConveyorTrackInfo[746-1].m_nLuggNum2;

		CMoveJobItem *pMoveJobItem = pDoc->m_pMoveJob->Find(nScLuggNum2);
		if ( pMoveJobItem != NULL )
		{
			strTem.Format("%d", pMoveJobItem->m_nLineNum);
			SET(IDC_EDIT_SC_LINE2, strTem );
		}
		else
			SET(IDC_EDIT_SC_LINE2, "" );
	}


	if (nScLuggNum3 != pDoc->m_ConveyorTrackInfo[2005-1].m_nLuggNum)
	{
		nScLuggNum3 = pDoc->m_ConveyorTrackInfo[2005-1].m_nLuggNum;

		CMoveJobItem *pMoveJobItem = pDoc->m_pMoveJob->Find(nScLuggNum3);
		if ( pMoveJobItem != NULL )
		{
			strTem.Format("%d", pMoveJobItem->m_nLineNum);
			SET(IDC_EDIT_SC_LINE3, strTem );
		}
		else
			SET(IDC_EDIT_SC_LINE3, "" );
	}

	if (nScLuggNum4 != pDoc->m_ConveyorTrackInfo[2005-1].m_nLuggNum2)
	{
		nScLuggNum4 = pDoc->m_ConveyorTrackInfo[2005-1].m_nLuggNum2;

		CMoveJobItem *pMoveJobItem = pDoc->m_pMoveJob->Find(nScLuggNum4);
		if ( pMoveJobItem != NULL )
		{
			strTem.Format("%d", pMoveJobItem->m_nLineNum);
			SET(IDC_EDIT_SC_LINE4, strTem );
		}
		else
			SET(IDC_EDIT_SC_LINE4, "" );
	}

	if (nRtvLuggNum1 != pDoc->m_pRgvInfo[0]->m_nInternalLuggNum )
	{
		nRtvLuggNum1 = pDoc->m_pRgvInfo[0]->m_nInternalLuggNum;

		CMoveJobItem *pMoveJobItem = pDoc->m_pMoveJob->Find(nRtvLuggNum1);
		if ( pMoveJobItem != NULL )
		{
			strTem.Format("%d", pMoveJobItem->m_nLineNum);
			SET(IDC_EDIT_RTV_LINE1, strTem );
		}
		else
			SET(IDC_EDIT_RTV_LINE1, "" );
	}

	if (nRtvLuggNum2 != pDoc->m_pRgvInfo[0]->m_nInternalLuggNum2 )
	{
		nRtvLuggNum2 = pDoc->m_pRgvInfo[0]->m_nInternalLuggNum2;

		CMoveJobItem *pMoveJobItem = pDoc->m_pMoveJob->Find(nRtvLuggNum2);
		if ( pMoveJobItem != NULL )
		{
			strTem.Format("%d", pMoveJobItem->m_nLineNum);
			SET(IDC_EDIT_RTV_LINE2, strTem );
		}
		else
			SET(IDC_EDIT_RTV_LINE2, "" );
	}


	if (nRtvLuggNum3 != pDoc->m_pRgvInfo[1]->m_nInternalLuggNum )
	{
		nRtvLuggNum3 = pDoc->m_pRgvInfo[1]->m_nInternalLuggNum;

		CMoveJobItem *pMoveJobItem = pDoc->m_pMoveJob->Find(nRtvLuggNum3);
		if ( pMoveJobItem != NULL )
		{
			strTem.Format("%d", pMoveJobItem->m_nLineNum);
			SET(IDC_EDIT_RTV_LINE3, strTem );
		}
		else
			SET(IDC_EDIT_RTV_LINE3, "" );
	}

	if (nRtvLuggNum4 != pDoc->m_pRgvInfo[1]->m_nInternalLuggNum2 )
	{
		nRtvLuggNum4 = pDoc->m_pRgvInfo[1]->m_nInternalLuggNum2;

		CMoveJobItem *pMoveJobItem = pDoc->m_pMoveJob->Find(nRtvLuggNum4);
		if ( pMoveJobItem != NULL )
		{
			strTem.Format("%d", pMoveJobItem->m_nLineNum);
			SET(IDC_EDIT_RTV_LINE4, strTem );
		}
		else
			SET(IDC_EDIT_RTV_LINE4, "" );
	}

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[904-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[904-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER1, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[910-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[910-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER2, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[919-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[919-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER3, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[1013-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[1013-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER4, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[1030-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[1030-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER5, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[1018-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[1018-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER6, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[926-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[926-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER7, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[1032-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[1032-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER8, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[933-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[933-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER9, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[939-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[939-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER10, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[945-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[945-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER11, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[952-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[952-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER12, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[960-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[960-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER13, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[1034-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[1034-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER14, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[1036-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[1036-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER15, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[966-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[966-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER16, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[1038-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[1038-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER17, strTem );

	strTem.Format("%d/%d", pDoc->m_ConveyorTrackInfo[973-1].m_wStackLevel, pDoc->m_ConveyorTrackInfo[973-1].m_wPlcCount);
	SET(IDC_EDIT1_LINE_COUNTER18, strTem );


	static int nLine1 = -1;
	static int nLine2 = -1;
	static int nLine3 = -1;
	static int nLine4 = -1;
	static int nLine5 = -1;
	static int nLine6 = -1;
	static int nLine7 = -1;
	static int nLine8 = -1;
	static int nLine9 = -1;
	static int nLine10 = -1;

	if (nLine1 != pDoc->m_nSetLine[0] )
	{
		nLine1 = pDoc->m_nSetLine[0];

		strTem.Format("%d", pDoc->m_nSetLine[0]);
		SET(IDC_EDIT_SET_LINE1, strTem );
	}

	if (nLine2 != pDoc->m_nSetLine[1] )
	{
		nLine2 = pDoc->m_nSetLine[1];

		strTem.Format("%d", pDoc->m_nSetLine[1]);
		SET(IDC_EDIT_SET_LINE2, strTem );
	}

	if (nLine3 != pDoc->m_nSetLine[2] )
	{
		nLine3 = pDoc->m_nSetLine[2];

		strTem.Format("%d", pDoc->m_nSetLine[2]);
		SET(IDC_EDIT_SET_LINE3, strTem );
	}

	if (nLine4 != pDoc->m_nSetLine[3] )
	{
		nLine4 = pDoc->m_nSetLine[3];

		strTem.Format("%d", pDoc->m_nSetLine[3]);
		SET(IDC_EDIT_SET_LINE4, strTem );
	}

	if (nLine5 != pDoc->m_nSetLine[4] )
	{
		nLine5 = pDoc->m_nSetLine[4];

		strTem.Format("%d", pDoc->m_nSetLine[4]);
		SET(IDC_EDIT_SET_LINE5, strTem );
	}

	if (nLine6 != pDoc->m_nSetLine[5] )
	{
		nLine6 = pDoc->m_nSetLine[5];

		strTem.Format("%d", pDoc->m_nSetLine[5]);
		SET(IDC_EDIT_SET_LINE6, strTem );
	}

	if (nLine7 != pDoc->m_nSetLine[6] )
	{
		nLine7 = pDoc->m_nSetLine[6];

		strTem.Format("%d", pDoc->m_nSetLine[6]);
		SET(IDC_EDIT_SET_LINE7, strTem );
	}

	if (nLine8 != pDoc->m_nSetLine[7] )
	{
		nLine8 = pDoc->m_nSetLine[7];

		strTem.Format("%d", pDoc->m_nSetLine[7]);
		SET(IDC_EDIT_SET_LINE8, strTem );
	}

	if (nLine9 != pDoc->m_nSetLine[8] )
	{
		nLine9 = pDoc->m_nSetLine[8];

		strTem.Format("%d", pDoc->m_nSetLine[8]);
		SET(IDC_EDIT_SET_LINE9, strTem );
	}

	if (nLine10 != pDoc->m_nSetLine[9] )
	{
		nLine10 = pDoc->m_nSetLine[9];

		strTem.Format("%d", pDoc->m_nSetLine[9]);
		SET(IDC_EDIT_SET_LINE10, strTem );
	}


	static int nLine109 = -1;
	static int nLine110 = -1;
	static int nLine111 = -1;
	static int nLine112 = -1;
	static int nLine113 = -1;
	static int nLine114 = -1;

	if (nLine109 != pDoc->m_nSetLine2[8] )
	{
		nLine109 = pDoc->m_nSetLine2[8];

		strTem.Format("%d", pDoc->m_nSetLine2[8]);
		SET(IDC_EDIT_SET_LINE109, strTem );
	}

	if (nLine110 != pDoc->m_nSetLine2[9] )
	{
		nLine110 = pDoc->m_nSetLine2[9];

		strTem.Format("%d", pDoc->m_nSetLine2[9]);
		SET(IDC_EDIT_SET_LINE110, strTem );
	}

	if (nLine111 != pDoc->m_nSetLine2[10] )
	{
		nLine111 = pDoc->m_nSetLine2[10];

		strTem.Format("%d", pDoc->m_nSetLine2[10]);
		SET(IDC_EDIT_SET_LINE111, strTem );
	}

	if (nLine112 != pDoc->m_nSetLine2[11] )
	{
		nLine112 = pDoc->m_nSetLine2[11];

		strTem.Format("%d", pDoc->m_nSetLine2[11]);
		SET(IDC_EDIT_SET_LINE112, strTem );
	}

	if (nLine113 != pDoc->m_nSetLine2[12] )
	{
		nLine113 = pDoc->m_nSetLine2[12];

		strTem.Format("%d", pDoc->m_nSetLine2[12]);
		SET(IDC_EDIT_SET_LINE113, strTem );
	}

	if (nLine114 != pDoc->m_nSetLine2[13] )
	{
		nLine114 = pDoc->m_nSetLine2[13];

		strTem.Format("%d", pDoc->m_nSetLine2[13]);
		SET(IDC_EDIT_SET_LINE114, strTem );
	}

	static int nCount109 = -1;
	static int nCount110 = -1;
	static int nCount111 = -1;
	static int nCount112 = -1;
	static int nCount113 = -1;
	static int nCount114 = -1;

	if (nCount109 != pDoc->m_nSetLineCount2[8] )
	{
		nCount109 = pDoc->m_nSetLineCount2[8];

		strTem.Format("%d", pDoc->m_nSetLineCount2[8]);
		SET(IDC_EDIT_SET_COUNT109, strTem );
	}

	if (nCount110 != pDoc->m_nSetLineCount2[9] )
	{
		nCount110 = pDoc->m_nSetLineCount2[9];

		strTem.Format("%d", pDoc->m_nSetLineCount2[9]);
		SET(IDC_EDIT_SET_COUNT110, strTem );
	}

	if (nCount111 != pDoc->m_nSetLineCount2[10] )
	{
		nCount111 = pDoc->m_nSetLineCount2[10];

		strTem.Format("%d", pDoc->m_nSetLineCount2[10]);
		SET(IDC_EDIT_SET_COUNT111, strTem );
	}

	if (nCount112 != pDoc->m_nSetLineCount2[11] )
	{
		nCount112 = pDoc->m_nSetLineCount2[11];

		strTem.Format("%d", pDoc->m_nSetLineCount2[11]);
		SET(IDC_EDIT_SET_COUNT112, strTem );
	}

	if (nCount113 != pDoc->m_nSetLineCount2[12] )
	{
		nCount113 = pDoc->m_nSetLineCount2[12];

		strTem.Format("%d", pDoc->m_nSetLineCount2[12]);
		SET(IDC_EDIT_SET_COUNT113, strTem );
	}

	if (nCount114 != pDoc->m_nSetLineCount2[13] )
	{
		nCount114 = pDoc->m_nSetLineCount2[13];

		strTem.Format("%d", pDoc->m_nSetLineCount2[13]);
		SET(IDC_EDIT_SET_COUNT114, strTem );
	}

	if(pDoc->m_b4groupCheck == TRUE)
	   m_b4Check = TRUE;
	if(pDoc->m_b4groupCheck == FALSE)
	   m_b4Check = FALSE;

	if(pDoc->m_b5groupCheck == TRUE)
	   m_b5Check = TRUE;
	if(pDoc->m_b5groupCheck == FALSE)
	   m_b5Check = FALSE;

	if(pDoc->m_b6groupCheck == TRUE)
	   m_b6Check = TRUE;
	if(pDoc->m_b6groupCheck == FALSE)
	   m_b6Check = FALSE;

	if(pDoc->m_b7groupCheck == TRUE)
	   m_b7Check = TRUE;
	if(pDoc->m_b7groupCheck == FALSE)
	   m_b7Check = FALSE;
	
	if(pDoc->m_b8groupCheck == TRUE)
	   m_b8Check = TRUE;
	if(pDoc->m_b8groupCheck == FALSE)
	   m_b8Check = FALSE;
	
	if(pDoc->m_b9groupCheck == TRUE)
	   m_b9Check = TRUE;
	if(pDoc->m_b9groupCheck == FALSE)
	   m_b9Check = FALSE;
	
	if(pDoc->m_bJobStopCheck == TRUE)
	   m_bStopCheck = TRUE;

	if(pDoc->m_bBufferStopCheck == FALSE)
	   m_bBufferStopCheck = FALSE;

	if(pDoc->m_bBufferStopCheck == TRUE)
	   m_bBufferStopCheck = TRUE;

	if(pDoc->m_bJobStopCheck == FALSE)
	   m_bStopCheck = FALSE;



	if(pDoc->m_bWriteTroubleCheck == FALSE)
	{
		m_bTroubleCheck = FALSE;
		UpdateData(FALSE);
	}

	if(pDoc->m_bWriteTroubleCheck == TRUE)
	{
		m_bTroubleCheck = TRUE;
		UpdateData(FALSE);
	}

	if(pDoc->m_bWriteLineTroubleCheck == FALSE)
	{
		m_bLineTroubleCheck = FALSE;
		UpdateData(FALSE);
	}

	if(pDoc->m_bWriteLineTroubleCheck == TRUE)
	{
		m_bLineTroubleCheck = TRUE;
		UpdateData(FALSE);
	}

	if(pDoc->m_bWriteStackingCheck1 == FALSE)
	{
		m_bStackingCheck1 = FALSE;
		UpdateData(FALSE);
	}

	if(pDoc->m_bWriteStackingCheck1 == TRUE)
	{
		m_bStackingCheck1 = TRUE;
		UpdateData(FALSE);
	}

	if(pDoc->m_bWriteStackingCheck2 == FALSE)
	{
		m_bStackingCheck2 = FALSE;
		UpdateData(FALSE);
	}

	if(pDoc->m_bWriteStackingCheck2 == TRUE)
	{
		m_bStackingCheck2 = TRUE;
		UpdateData(FALSE);
	}

	if(pDoc->m_bPriorityDocCheck == TRUE)
	   m_bPriorityCheck = TRUE;

	if(pDoc->m_bPriorityDocCheck == FALSE)
	   m_bPriorityCheck = FALSE;

	if(pDoc->m_bSetLineCheck == FALSE)
	{
		m_bLineCheck = FALSE;

		GetDlgItem(IDC_EDIT_SET_LINE1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_LINE2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_LINE3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_LINE4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_LINE5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_LINE6)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_LINE7)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_LINE8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_LINE9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_LINE10)->EnableWindow(FALSE);

		UpdateData(FALSE);
	}

	if(pDoc->m_bSetLineCheck == TRUE)
	{
		m_bLineCheck = TRUE;

		GetDlgItem(IDC_EDIT_SET_LINE1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_LINE2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_LINE3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_LINE4)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_LINE5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_LINE6)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_LINE7)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_LINE8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_LINE9)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_LINE10)->EnableWindow(TRUE);

		UpdateData(FALSE);
	}

	if(pDoc->m_bSetLineCheck2 == FALSE)
	{
		m_bLineCheck2 = FALSE;

		GetDlgItem(IDC_EDIT_SET_LINE109)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_LINE110)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_LINE111)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_LINE112)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_LINE113)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_LINE114)->EnableWindow(FALSE);

		UpdateData(FALSE);
	}
	if(pDoc->m_bSWStart == TRUE)
	{
		OnCheckSetLine2();
		pDoc->m_bSWStart = FALSE;
	}


	if(pDoc->m_bSetLineCheck2 == TRUE)
	{
		m_bLineCheck2 = TRUE;

		GetDlgItem(IDC_EDIT_SET_LINE109)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_LINE110)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_LINE111)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_LINE112)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_LINE113)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_LINE114)->EnableWindow(TRUE);

		UpdateData(FALSE);
	}

	if(pDoc->m_bSetCountCheck == FALSE)
	{
		m_bCountCheck = FALSE;

		GetDlgItem(IDC_EDIT_SET_COUNT109)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_COUNT110)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_COUNT111)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_COUNT112)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_COUNT113)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SET_COUNT114)->EnableWindow(FALSE);

		UpdateData(FALSE);
	}

	if(pDoc->m_bSetCountCheck == TRUE)
	{
		m_bCountCheck = TRUE;

		GetDlgItem(IDC_EDIT_SET_COUNT109)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_COUNT110)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_COUNT111)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_COUNT112)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_COUNT113)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SET_COUNT114)->EnableWindow(TRUE);

		UpdateData(FALSE);
	}


	if(pDoc->m_bSetTestCheck == FALSE) //임시방편
	{
		m_bTestCheck = FALSE;

		UpdateData(FALSE);
	}

	if(pDoc->m_bSetTestCheck == TRUE) //임시방편
	{
		m_bTestCheck = TRUE;

		UpdateData(FALSE);
	}




	if(pDoc->m_bAllStackerEmergency == FALSE)
	{
		m_bAllSEmergenCheck = FALSE;
		UpdateData(FALSE);
	}

	if(pDoc->m_bAllStackerEmergency == TRUE)
	{
		m_bAllSEmergenCheck = TRUE;
		UpdateData(FALSE);
	}


	if (nCount % 10 == 0)				// 10초마다 ECS server로 접속시도
	{
		if ( pDoc->m_pEcsCl == NULL && pDoc->m_pConfig->m_bEcsRetry)
			pDoc->ConnectEcsServer();
	}

	if (nCount % 10 == 0 && pDoc->m_pHostCl != NULL)
	{
		pDoc->m_pHostCl->Status(TRUE);
	}

	if (nCount % 10 == 0)
	{
		if ( pDoc->m_pHostCl == NULL &&	pDoc->m_pConfig->m_bRetry )
			pDoc->ConnectServer();

		for(int i = 0; i<CV_PLC_CNT; i++)
		{
			//if ( pDoc->m_pConveyorSocket[i] == NULL && pDoc->m_pConfig->m_bCvRetry[i] )
			if ( pDoc->m_pConveyorSocket[i] == NULL && pDoc->m_pConfig->m_sCvPort[i].bRetry )
				pDoc->ConnectCvServer(i);
		}

		for( i = 0; i<SC_CNT; i++)
		{
			if ( pDoc->m_pStackerSocket[i] == NULL && pDoc->m_pConfig->m_sScPort[i].bRetry) 
				pDoc->ConnectScServer(i);
		}

	}

	static int nLineGoing[14] = {-1,-1,-1,-1,-1,-1,-1-1,-1,-1,-1,-1,-1,-1};
	for (int i = 8; i < 14; i++)
	{
		if(nLineGoing[i] != pDoc->m_bLineGoing[i])
		{
			CCvControl* pCv = (CCvControl *)GetDlgItem(IDC_CVCTRLGOING9 + i-8);
			if(pCv == NULL)
				continue; 

			if(pDoc->m_bLineGoing[i])
				pCv->SetValue(BLUE, 0, 0, 0, 0, 0, 0);

			if(!pDoc->m_bLineGoing[i])
				pCv->SetValue(LIGHT_GRAY, 0, 0, 0, 0, 0, 0);

			nLineGoing[i] = pDoc->m_bLineGoing[i];
		}
	}

/*	if (pWnd->m_pMainWnd != NULL) 
	{
		unsigned char ucValue;   
		CString      strTitle[2];

		pWnd->m_pMainWnd->GetWindowText(strTitle[0]);

		ucValue = strTitle[0].GetAt(0);

		if ((ucValue >> 7) >0)	
			strTitle[1] = strTitle[0].Right(strTitle[0].GetLength()-2) + strTitle[0].Left(2);  
		else					
			strTitle[1] = strTitle[0].Right(strTitle[0].GetLength()-1) + strTitle[0].Left(1);  

		::AfxGetApp()->m_pMainWnd->SetWindowText(strTitle[1]);
	}
*/
	static int nError = 0;
	if (++nError % 10 == 0 && pDoc->m_pHostCl != NULL) {
		CJobItem* pJobItem = pDoc->m_pJob->FetchByStatus(JOB_STA_ERR_DUAL_STO);
		if ( pJobItem != NULL)
			pDoc->m_pHostCl->Error(DEVICE_CLASS_SC, pJobItem->GetStackerNum(pJobItem->m_strLocation)+1, SC_DUAL_STORE, 54, pJobItem->m_nLuggNum,
					pJobItem->m_strLocation);
		pJobItem = pDoc->m_pJob->FetchByStatus(JOB_STA_ERR_EMPTY_RET);
		if ( pJobItem != NULL)
			pDoc->m_pHostCl->Error(DEVICE_CLASS_SC, pJobItem->GetStackerNum(pJobItem->m_strLocation)+1, SC_EMPTY_RETRIEVE, 58, pJobItem->m_nLuggNum,
				pJobItem->m_strLocation);
		nError = 0;
	}

	if (++nCount % 300 == 0)
	{
		pDoc->m_pStatistic->Backup();

		nCount = 0;
	}

	CFormView::OnTimer(nIDEvent);
}

BEGIN_EVENTSINK_MAP(CEcsView, CFormView)
    //{{AFX_EVENTSINK_MAP(CEcsView)
	ON_EVENT(CEcsView, IDC_CVCTRL1, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL3, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL4, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL5, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL6, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL7, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL8, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL9, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL10, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL11, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL12, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL13, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL14, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL15, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL16, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL17, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL18, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL19, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL20, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL21, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL22, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL23, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL24, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL25, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL26, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL27, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL28, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL29, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL30, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL31, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL32, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL33, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL34, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL35, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL36, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL37, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL38, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL39, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL40, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL41, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL42, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL43, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL44, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL45, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL46, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL47, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL48, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL49, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL50, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL51, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL52, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL53, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL57, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL58, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL59, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL61, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL62, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL63, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL64, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL65, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL66, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL67, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL68, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL69, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL70, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL71, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL72, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL73, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL74, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL75, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL76, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)

	ON_EVENT(CEcsView, IDC_CVCTRL301, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL302, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL303, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL304, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL305, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL306, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL307, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL308, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL309, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL310, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL311, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL312, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL313, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL314, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL315, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL316, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL317, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL318, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL319, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL320, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL321, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL322, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL323, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL324, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL325, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL326, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL327, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL328, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL329, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL330, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL331, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL332, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL333, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL334, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL335, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL336, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL337, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL338, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL339, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL340, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL341, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL342, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL343, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL344, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL345, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL346, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL347, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL348, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL349, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)

	ON_EVENT(CEcsView, IDC_CVCTRL401, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL402, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL403, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL404, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL405, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL406, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL407, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL408, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL409, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL410, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL411, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL412, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL413, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL414, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL415, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL416, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL417, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL418, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL419, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL420, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL421, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL422, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL423, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL424, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL425, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL426, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL427, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL428, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL429, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL430, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL431, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL432, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL433, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL434, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL435, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL436, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL437, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL438, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL439, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL440, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL441, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL442, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL443, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL444, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL445, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL446, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL447, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL448, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL449, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL450, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL451, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL452, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL453, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL454, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL455, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL456, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL457, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL458, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL459, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL460, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL461, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL462, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL463, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL464, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL465, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL466, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL467, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL468, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL469, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL470, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL471, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL472, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL473, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL474, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL475, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL476, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL477, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL478, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL479, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL480, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL481, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL482, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL483, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL484, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL485, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL486, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL487, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL488, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)

	ON_EVENT(CEcsView, IDC_CVCTRL501, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL502, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL503, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL504, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL505, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL506, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL507, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL508, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL509, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL510, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL511, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL512, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL513, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL514, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL515, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL516, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL517, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL518, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL519, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL520, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL521, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL522, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL523, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL524, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL525, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL526, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL527, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL528, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL529, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL530, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL531, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL532, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL533, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL534, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL535, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL536, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL537, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL538, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL539, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL540, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL541, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL542, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL543, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL544, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL545, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL546, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL547, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL548, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL549, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL550, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL551, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL552, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL553, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL554, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL555, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL556, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL557, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL558, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL559, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL560, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL561, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL562, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL563, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL564, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL565, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL566, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL567, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL568, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL569, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL570, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL571, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL572, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL573, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL574, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL575, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL576, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL577, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL578, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL579, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL580, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL581, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL582, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL583, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL584, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL585, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL586, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL587, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL588, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)

	ON_EVENT(CEcsView, IDC_CVCTRL601, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL602, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL603, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL604, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL605, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL606, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL607, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL608, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL609, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL610, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL611, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL612, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL613, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL614, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL615, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL616, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL617, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL618, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL619, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL620, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL621, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL622, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL623, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL624, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL625, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL626, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL627, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL628, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL629, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL630, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL631, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL632, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL633, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL634, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL635, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL636, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL637, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL638, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL639, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL640, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL641, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL642, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL643, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL644, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL645, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL646, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL647, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL648, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL649, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL650, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL651, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL652, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL653, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL654, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL655, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL656, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL657, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL658, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL659, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL660, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL661, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL662, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL663, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL664, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL665, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL666, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL667, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL668, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL669, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL670, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL671, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL672, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL673, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL674, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL675, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL676, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL677, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL678, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL679, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL680, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL681, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL682, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL683, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL684, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)


	ON_EVENT(CEcsView, IDC_CVCTRL701, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL702, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL703, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL704, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL705, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL706, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL707, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL708, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL709, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL710, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL711, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL712, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL713, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL714, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL715, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL716, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL717, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL718, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL719, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL720, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL721, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL722, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL723, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL724, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL725, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL726, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL727, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL728, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL729, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL730, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL731, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL732, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL733, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL734, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL735, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL736, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL737, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL738, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL739, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL740, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL741, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL742, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL743, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL744, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL745, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL747, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL748, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL749, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL750, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL751, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL752, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL753, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL754, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL755, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL756, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL757, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL758, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL759, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL760, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL761, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL762, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL763, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL764, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL765, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL766, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL767, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL768, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL769, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL770, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL771, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL772, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL773, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL774, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL775, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL776, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL777, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL778, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL779, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL780, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL781, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL782, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL783, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL784, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL785, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL786, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL787, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL788, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL789, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL790, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL791, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL792, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL793, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL794, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL795, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL796, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL797, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL798, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL799, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL800, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL801, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL802, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL803, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL804, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL805, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL806, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL807, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL808, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL809, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL810, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL811, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL812, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL813, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL814, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL815, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL816, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL817, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL818, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL819, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL820, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL821, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL822, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL823, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)

	ON_EVENT(CEcsView, IDC_CVCTRL901, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL902, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL903, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL904, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL905, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL906, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL907, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL908, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL909, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL910, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL911, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL912, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL913, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL915, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL916, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL917, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL918, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL919, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL920, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL921, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL922, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL923, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL924, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL925, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL926, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL927, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL928, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL929, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL930, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL931, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL932, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL933, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL934, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL935, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL937, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL938, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL939, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL940, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL941, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL942, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL943, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL944, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL945, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL946, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL947, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL948, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL949, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL950, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL951, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL952, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL953, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL954, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL955, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL957, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL958, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL959, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL960, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL961, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL962, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL963, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL964, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL965, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL966, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL967, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL968, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL969, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL970, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL971, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL972, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL973, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL974, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL975, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL976, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL977, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1000, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1001, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1002, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1003, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL1010, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL1011, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL1012, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1013, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1014, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL1015, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL1016, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL1017, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1018, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL1019, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1021, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1022, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1023, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1024, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1030, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL1031, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1032, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL1033, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1034, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL1035, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1036, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL1037, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1038, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	//ON_EVENT(CEcsView, IDC_CVCTRL1039, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1040, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1041, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1042, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1043, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1044, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1045, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1046, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1047, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1048, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1049, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1050, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL1051, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2008, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2009, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2010, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2011, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2012, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2013, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2014, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2015, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2016, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2017, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2018, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2019, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2020, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2021, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2022, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2023, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2024, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)

	ON_EVENT(CEcsView, IDC_CVCTRL2101, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2102, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2103, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2104, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2105, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2106, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2107, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2108, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2109, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2110, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2111, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2112, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2113, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2114, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2200, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2201, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2202, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2203, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2204, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2205, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2206, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2207, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2208, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2210, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2211, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2212, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2213, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2214, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2215, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2216, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2217, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2218, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2220, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2221, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2222, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2223, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2224, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2225, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2226, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2227, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2228, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2230, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2231, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2232, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2233, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2234, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2235, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2236, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2237, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2238, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2240, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2241, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2242, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2243, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2244, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2245, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2246, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2247, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2248, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2250, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2251, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2252, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2253, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2254, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2255, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2256, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2257, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2258, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2268, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2269, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2270, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2271, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2272, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2273, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2280, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2281, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2282, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2283, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2284, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2285, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2286, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2287, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2288, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2289, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2300, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2301, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)
	ON_EVENT(CEcsView, IDC_CVCTRL2302, 1 /* LBtnClick */, OnLBtnClickConveyor, VTS_I2)


	ON_EVENT(CEcsView, IDC_STACKER_1, 1 /* LBtnClick */, OnLBtnClickStacker, VTS_I2)
	ON_EVENT(CEcsView, IDC_STACKER_2, 1 /* LBtnClick */, OnLBtnClickStacker, VTS_I2)
	ON_EVENT(CEcsView, IDC_STACKER_3, 1 /* LBtnClick */, OnLBtnClickStacker, VTS_I2)
	ON_EVENT(CEcsView, IDC_STACKER_4, 1 /* LBtnClick */, OnLBtnClickStacker, VTS_I2)
	ON_EVENT(CEcsView, IDC_STACKER_5, 1 /* LBtnClick */, OnLBtnClickStacker, VTS_I2)
	ON_EVENT(CEcsView, IDC_STACKER_6, 1 /* LBtnClick */, OnLBtnClickStacker, VTS_I2)

	ON_EVENT(CEcsView, IDC_RTVCTRL1, 1 /* LBtnClick */, OnLBtnClickRgv, VTS_I2)
	ON_EVENT(CEcsView, IDC_RTVCTRL2, 1 /* LBtnClick */, OnLBtnClickRgv, VTS_I2)

	ON_EVENT(CEcsView, IDC_OPBOXCTRL1, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL2, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL3, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL4, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL5, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL6, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL7, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL8, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL9, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL10, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL11, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL12, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL13, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL14, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL15, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL16, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL17, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL18, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL19, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL20, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL21, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL22, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL23, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL24, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL25, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL26, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)
	ON_EVENT(CEcsView, IDC_OPBOXCTRL27, 1 /* LBtnClick */, OnLBtnClickOpbox, VTS_I2)

	//ON_EVENT(CEcsView, IDC_BCR_2, 1 /* LBtnClick */, OnLBtnClickBcr, VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

LRESULT CEcsView::OnCvNotify(WPARAM wParam, LPARAM lParam)
{
	CMainFrame* pWnd = (CMainFrame *)AfxGetMainWnd();
	CEcsDoc* pDoc = GetDocument();
	static BOOL bSent = FALSE;
	static int	nPrevErrTrack = -1;

	CString strBttName;

	if (lParam == NOTIFY_REFRESH)
	{
		bSent = FALSE;
		BOOL bRefreshStatus = FALSE;
		CCvControl* pCv;

		for (int i = 0; i < CV_1_TRACK_CNT+2 && wParam == CV_1_PLC; i++)
		{
			if (pDoc->m_ConveyorTrackInfo[i].m_bModified)
			{
				int nStatus = CV_TRACK_NORMAL;
				if (pDoc->m_ConveyorTrackInfo[i].m_bOverLoadErr ||
					pDoc->m_ConveyorTrackInfo[i].m_bOverTimeErr)
				{
					nStatus = CV_TRACK_ERROR;
				}
				pCv = (CCvControl *)GetDlgItem(IDC_CVCTRL1 + i);
				if(pCv == NULL)
					continue;
				
				//Test
				//if(pDoc->m_ConveyorTrackInfo[i].m_nDestPos == 7)
				//	 pDoc->m_ConveyorTrackInfo[i].m_nJobType = 6;

				BOOL bOverTime = pDoc->m_ConveyorTrackInfo[i].m_bOverTimeErr;
				BOOL bOverLoad = pDoc->m_ConveyorTrackInfo[i].m_bOverLoadErr;
				BOOL bBuffTrouble = pDoc->m_ConveyorTrackInfo[i].m_bBuffTrouble;

				int  nJobType  = pDoc->m_ConveyorTrackInfo[i].m_nJobType;

				BOOL  bPltSensor = FALSE;

				BOOL  bStoStationReady = pDoc->m_ConveyorTrackInfo[i].m_bStoStationReady;

			/*	if(i == 9-1)
				{
					bPltSensor = pDoc->m_ConveyorTrackInfo[i].m_bStoStationReady;
					bStoStationReady = FALSE;
				} */

				if(nJobType == 0 && pDoc->m_ConveyorTrackInfo[i].m_nDestPos == 12)
					nJobType = 4;

				pCv->SetValue(GetCvColor(bOverTime, bOverLoad, bBuffTrouble, (unsigned long)nJobType, TRUE, bPltSensor),
					  pDoc->m_ConveyorTrackInfo[i].m_bHeightErr,
					  //pDoc->m_ConveyorTrackInfo[i].m_bStoStationReady,
					  bStoStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bPickingStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoHomeStandReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetHomeStandReady);

				pDoc->m_ConveyorTrackInfo[i].m_bModified = FALSE;

				if (bOverTime || bOverLoad) pDoc->DisplayMessage("Cv Error", FALSE);

				bRefreshStatus = IsReportingStatusTrack(i + 1);
			}
		}

		for (i = CV_2_START_TRACK;i < CV_2_START_TRACK + CV_2_TRACK_CNT && wParam == CV_2_PLC; i++)
		{
			if (pDoc->m_ConveyorTrackInfo[i].m_bModified)
			{
				pCv = (CCvControl *)GetDlgItem(IDC_CVCTRL901 + i - CV_2_START_TRACK);

				if(pCv == NULL)
					continue;

				BOOL bOverTime = pDoc->m_ConveyorTrackInfo[i].m_bOverTimeErr;
				BOOL bOverLoad = pDoc->m_ConveyorTrackInfo[i].m_bOverLoadErr;

				int  nJobType  = pDoc->m_ConveyorTrackInfo[i].m_nJobType;
				BOOL  bPltSensor = pDoc->m_ConveyorTrackInfo[i].m_bPltSensor;
				BOOL  bOpMode  = pDoc->m_ConveyorTrackInfo[i].m_bOpMode;
				
				if(nJobType == 0 && pDoc->m_ConveyorTrackInfo[i].m_nDestPos == 12)
				//if(pDoc->m_ConveyorTrackInfo[i].m_nDestPos == 12)
					nJobType = 4;

			

				if(pDoc->m_ConveyorTrackInfo[i].m_wErrorCode != 0)
					bOverTime = TRUE;

				
				pCv->SetValue(GetCvColor(bOverTime, bOverLoad, FALSE, (unsigned long)nJobType, bOpMode, bPltSensor),
					  pDoc->m_ConveyorTrackInfo[i].m_bHeightErr,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bPickingStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoHomeStandReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetHomeStandReady);

				pDoc->m_ConveyorTrackInfo[i].m_bModified = FALSE;

				if (bOverTime || bOverLoad) pDoc->DisplayMessage("Cv Error", FALSE);

				//bRefreshStatus = IsReportingStatusTrack(i + 1);
			}

		}

		for (i = CV_3_START_TRACK;i < CV_3_START_TRACK + CV_3_TRACK_CNT && wParam == CV_3_PLC; i++)
		{
			if (pDoc->m_ConveyorTrackInfo[i].m_bModified)
			{
				int nStatus = CV_TRACK_NORMAL;
				if (pDoc->m_ConveyorTrackInfo[i].m_bOverLoadErr ||
					pDoc->m_ConveyorTrackInfo[i].m_bOverTimeErr)
				{
					nStatus = CV_TRACK_ERROR;
				}
				pCv = (CCvControl *)GetDlgItem(IDC_CVCTRL301 + i - CV_3_START_TRACK);
				if(pCv == NULL)
					continue;

				BOOL bOverTime = pDoc->m_ConveyorTrackInfo[i].m_bOverTimeErr;
				BOOL bOverLoad = pDoc->m_ConveyorTrackInfo[i].m_bOverLoadErr;
				BOOL bBuffTrouble = pDoc->m_ConveyorTrackInfo[i].m_bBuffTrouble;

				if(i == 330-1)
				{
					if(pDoc->m_ConveyorTrackInfo[347-1].m_bOverLoadErr)
						bOverLoad = TRUE;
				}


				int  nJobType  = pDoc->m_ConveyorTrackInfo[i].m_nJobType;

				pCv->SetValue(GetCvColor(bOverTime, bOverLoad, bBuffTrouble, (unsigned long)nJobType, TRUE),
					  pDoc->m_ConveyorTrackInfo[i].m_bHeightErr,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bPickingStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoHomeStandReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetHomeStandReady);

				pDoc->m_ConveyorTrackInfo[i].m_bModified = FALSE;

				//if (i != 305 && i != 306 && (bOverTime || bOverLoad)) pDoc->DisplayMessage("Cv Error", FALSE);

			//	bRefreshStatus = IsReportingStatusTrack(i + 1);
			}

		}

		for (i = CV_4_START_TRACK;i < CV_4_START_TRACK + CV_4_TRACK_CNT+2 && wParam == CV_4_PLC; i++)
		{
			if (pDoc->m_ConveyorTrackInfo[i].m_bModified)
			{
				int nStatus = CV_TRACK_NORMAL;
				if (pDoc->m_ConveyorTrackInfo[i].m_bOverLoadErr ||
					pDoc->m_ConveyorTrackInfo[i].m_bOverTimeErr)
				{
					nStatus = CV_TRACK_ERROR;
				}
				pCv = (CCvControl *)GetDlgItem(IDC_CVCTRL401 + i - CV_4_START_TRACK);
				if(pCv == NULL)
					continue;

				//if(i == 486 || i == 487){
				BOOL bOverTime = pDoc->m_ConveyorTrackInfo[i].m_bOverTimeErr;
				BOOL bOverLoad = pDoc->m_ConveyorTrackInfo[i].m_bOverLoadErr;
				BOOL bBuffTrouble = pDoc->m_ConveyorTrackInfo[i].m_bBuffTrouble;

				int  nJobType  = pDoc->m_ConveyorTrackInfo[i].m_nJobType;

				pCv->SetValue(GetCvColor(bOverTime, bOverLoad, bBuffTrouble, (unsigned long)nJobType, TRUE),
					  pDoc->m_ConveyorTrackInfo[i].m_bHeightErr,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bPickingStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoHomeStandReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetHomeStandReady);

				pDoc->m_ConveyorTrackInfo[i].m_bModified = FALSE;

				if (bOverTime || bOverLoad) pDoc->DisplayMessage("Cv Error", FALSE);
				//}
				//bRefreshStatus = IsReportingStatusTrack(i + 1);
			}

		}

		for (i = CV_5_START_TRACK;i < CV_5_START_TRACK + CV_5_TRACK_CNT+2 && wParam == CV_5_PLC; i++)
		{
			if (pDoc->m_ConveyorTrackInfo[i].m_bModified)
			{
				int nStatus = CV_TRACK_NORMAL;
				if (pDoc->m_ConveyorTrackInfo[i].m_bOverLoadErr ||
					pDoc->m_ConveyorTrackInfo[i].m_bOverTimeErr)
				{
					nStatus = CV_TRACK_ERROR;
				}
				pCv = (CCvControl *)GetDlgItem(IDC_CVCTRL501 + i - CV_5_START_TRACK);
				if(pCv == NULL)
					continue;

				BOOL bOverTime = pDoc->m_ConveyorTrackInfo[i].m_bOverTimeErr;
				BOOL bOverLoad = pDoc->m_ConveyorTrackInfo[i].m_bOverLoadErr;
				BOOL bBuffTrouble = pDoc->m_ConveyorTrackInfo[i].m_bBuffTrouble;

				int  nJobType  = pDoc->m_ConveyorTrackInfo[i].m_nJobType;

				pCv->SetValue(GetCvColor(bOverTime, bOverLoad, bBuffTrouble, (unsigned long)nJobType, TRUE),
					  pDoc->m_ConveyorTrackInfo[i].m_bHeightErr,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bPickingStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoHomeStandReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetHomeStandReady);

				pDoc->m_ConveyorTrackInfo[i].m_bModified = FALSE;

				if (bOverTime || bOverLoad) pDoc->DisplayMessage("Cv Error", FALSE);

				//bRefreshStatus = IsReportingStatusTrack(i + 1);
			}

		}

		for (i = CV_6_START_TRACK;i < CV_6_START_TRACK + CV_6_TRACK_CNT+2 && wParam == CV_6_PLC; i++)
		{
			if (pDoc->m_ConveyorTrackInfo[i].m_bModified)
			{
				int nStatus = CV_TRACK_NORMAL;
				if (pDoc->m_ConveyorTrackInfo[i].m_bOverLoadErr ||
					pDoc->m_ConveyorTrackInfo[i].m_bOverTimeErr)
				{
					nStatus = CV_TRACK_ERROR;
				}
				pCv = (CCvControl *)GetDlgItem(IDC_CVCTRL601 + i - CV_6_START_TRACK);
				if(pCv == NULL)
					continue;

				BOOL bOverTime = pDoc->m_ConveyorTrackInfo[i].m_bOverTimeErr;
				BOOL bOverLoad = pDoc->m_ConveyorTrackInfo[i].m_bOverLoadErr;
				BOOL bBuffTrouble = pDoc->m_ConveyorTrackInfo[i].m_bBuffTrouble;

				int  nJobType  = pDoc->m_ConveyorTrackInfo[i].m_nJobType;

				pCv->SetValue(GetCvColor(bOverTime, bOverLoad, bBuffTrouble, (unsigned long)nJobType, TRUE),
					  pDoc->m_ConveyorTrackInfo[i].m_bHeightErr,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bPickingStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoHomeStandReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetHomeStandReady);

				pDoc->m_ConveyorTrackInfo[i].m_bModified = FALSE;

				if (bOverTime || bOverLoad) pDoc->DisplayMessage("Cv Error", FALSE);

				//bRefreshStatus = IsReportingStatusTrack(i + 1);
			}

		}

		for (i = CV_7_START_TRACK;i < CV_7_START_TRACK + CV_7_TRACK_CNT && wParam == CV_7_PLC; i++)
		{
			if (pDoc->m_ConveyorTrackInfo[i].m_bModified)
			{
				int nStatus = CV_TRACK_NORMAL;

				int  nErrorCode = pDoc->m_ConveyorTrackInfo[i].m_wErrorCode;
				if (nErrorCode > 0) nStatus = CV_TRACK_ERROR;

				pCv = (CCvControl *)GetDlgItem(IDC_CVCTRL701 + i - CV_7_START_TRACK);
				if(pCv == NULL)
					continue;

				BOOL bOverTime = pDoc->m_ConveyorTrackInfo[i].m_bOverTimeErr;
				BOOL bOverLoad = pDoc->m_ConveyorTrackInfo[i].m_bOverLoadErr;
				BOOL bBuffTrouble = pDoc->m_ConveyorTrackInfo[i].m_bBuffTrouble;

				int  nJobType  = pDoc->m_ConveyorTrackInfo[i].m_nJobType;
				BOOL  bOpMode  = pDoc->m_ConveyorTrackInfo[i].m_bOpMode;
				int nDestPos = pDoc->m_ConveyorTrackInfo[i].m_nDestPos;
				
				if(pDoc->m_ConveyorTrackInfo[i].m_nDestPos == 22)
					nJobType = JOB_TYPE_PICK_REPLENISH;

				if(pDoc->m_ConveyorTrackInfo[i].m_nDestPos == 21)
					nJobType = JOB_TYPE_STN_TO_STN;

				if(i > 817 && i < 822)
				{
					if(pDoc->m_ConveyorTrackInfo[i].m_nDestPos == 5 || pDoc->m_ConveyorTrackInfo[i].m_nDestPos == 6)
						nJobType = 2;
				}


				if(pDoc->m_ConveyorTrackInfo[i].m_nComplete == 1)
					nJobType = 5;


				pCv->SetValue(GetCvColor(nStatus, nStatus, bBuffTrouble, (unsigned long)nJobType, bOpMode),
					  pDoc->m_ConveyorTrackInfo[i].m_bHeightErr,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bPickingStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoHomeStandReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetHomeStandReady);

				pDoc->m_ConveyorTrackInfo[i].m_bModified = FALSE;

				if (bOverTime || bOverLoad) pDoc->DisplayMessage("Cv Error", FALSE);

				//bRefreshStatus = IsReportingStatusTrack(i + 1);
			}

		}

		/* 250124 LJM 주석
		*/
		for (i = CV_8_START_TRACK;i < CV_8_START_TRACK + CV_8_TRACK_CNT && wParam == CV_8_PLC; i++)
		{
			if (pDoc->m_ConveyorTrackInfo[i].m_bModified)
			{
				int nStatus = CV_TRACK_NORMAL;

				int  nErrorCode = pDoc->m_ConveyorTrackInfo[i].m_wErrorCode;
				if (nErrorCode > 0) nStatus = CV_TRACK_ERROR;

				pCv = (CCvControl *)GetDlgItem(7601 + i - CV_8_START_TRACK);
				if(pCv == NULL)
					continue;

				BOOL bOverTime = pDoc->m_ConveyorTrackInfo[i].m_bOverTimeErr;
				BOOL bOverLoad = pDoc->m_ConveyorTrackInfo[i].m_bOverLoadErr;
				BOOL bBuffTrouble = pDoc->m_ConveyorTrackInfo[i].m_bBuffTrouble;

				int  nJobType  = pDoc->m_ConveyorTrackInfo[i].m_nJobType;
				BOOL  bOpMode  = pDoc->m_ConveyorTrackInfo[i].m_bOpMode;
				int nDestPos = pDoc->m_ConveyorTrackInfo[i].m_nDestPos;
				

				if(pDoc->m_ConveyorTrackInfo[i].m_nComplete == 1)
					nJobType = 5;


				pCv->SetValue(GetCvColor(nStatus, nStatus, bBuffTrouble, (unsigned long)nJobType, bOpMode),
					  pDoc->m_ConveyorTrackInfo[i].m_bHeightErr,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bPickingStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoHomeStandReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetHomeStandReady);

				pDoc->m_ConveyorTrackInfo[i].m_bModified = FALSE;

				if (bOverTime || bOverLoad) pDoc->DisplayMessage("Cv Error", FALSE);

				//bRefreshStatus = IsReportingStatusTrack(i + 1);
			}
		}

		for (i = CV_9_START_TRACK;i < CV_9_START_TRACK + CV_9_TRACK_CNT && wParam == CV_9_PLC; i++)
		{
			if (pDoc->m_ConveyorTrackInfo[i].m_bModified)
			{
				int nStatus = CV_TRACK_NORMAL;

				int  nErrorCode = pDoc->m_ConveyorTrackInfo[i].m_wErrorCode;
				if (nErrorCode > 0) nStatus = CV_TRACK_ERROR;

				pCv = (CCvControl *)GetDlgItem(7701 + i - CV_9_START_TRACK);
				if(pCv == NULL)
					continue;

				BOOL bOverTime = pDoc->m_ConveyorTrackInfo[i].m_bOverTimeErr;
				BOOL bOverLoad = pDoc->m_ConveyorTrackInfo[i].m_bOverLoadErr;
				BOOL bBuffTrouble = pDoc->m_ConveyorTrackInfo[i].m_bBuffTrouble;

				int  nJobType  = pDoc->m_ConveyorTrackInfo[i].m_nJobType;
				BOOL  bOpMode  = pDoc->m_ConveyorTrackInfo[i].m_bOpMode;
				int nDestPos = pDoc->m_ConveyorTrackInfo[i].m_nDestPos;
				

				if(pDoc->m_ConveyorTrackInfo[i].m_nComplete == 1)
					nJobType = 5;


				pCv->SetValue(GetCvColor(nStatus, nStatus, bBuffTrouble, (unsigned long)nJobType, bOpMode),
					  pDoc->m_ConveyorTrackInfo[i].m_bHeightErr,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bPickingStationReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bStoHomeStandReady,
					  pDoc->m_ConveyorTrackInfo[i].m_bRetHomeStandReady);

				pDoc->m_ConveyorTrackInfo[i].m_bModified = FALSE;

				if (bOverTime || bOverLoad) pDoc->DisplayMessage("Cv Error", FALSE);

				//bRefreshStatus = IsReportingStatusTrack(i + 1);
			}
		}

		COpBoxControl* pOpBox;
		for (i = 0; i < OPBOX_CNT; i++)
		{
			if(i>4 && i<18)
				continue;

			if (pDoc->m_OpBoxInfo[i].m_bModified)
			{
				pOpBox = (COpBoxControl *)GetDlgItem(IDC_OPBOXCTRL1 + i);

				BOOL bAutoMode = pDoc->m_OpBoxInfo[i].m_bAutoMode ? 1 : 0;
				BOOL bNormalStatus = !pDoc->m_OpBoxInfo[i].m_bNormalStatus;

				pOpBox->SetValueEx(bAutoMode, bNormalStatus);
				pDoc->m_OpBoxInfo[i].m_bModified = FALSE;

				bRefreshStatus = TRUE;
			}
		}
		if (bRefreshStatus && pDoc->m_pHostCl != NULL) pDoc->m_pHostCl->Status(TRUE);
	}

	if (lParam == NOTIFY_ERROR) pDoc->DisplayMessage("No response from Conveyor PLC", FALSE);

	pWnd->UpdateCommCv(wParam + ID_COMM_CV_1, ConvertNotifyToStatus(lParam));

	return 0;
}
COLORREF CEcsView::GetCvColor(BOOL bOverTime, BOOL bOverLoad, BOOL bBuffTrouble, int nJobType, BOOL bOpMode, BOOL bPltSensor)
{
	if (bOverTime || bOverLoad)
		return RED;

	if(bBuffTrouble)
		return YELLOW;

	//if(bPltSensor)
	//	return DARK_GRAY;

	switch (nJobType)
	{
	case	JOB_TYPE_UNIT_STO:				return GREEN;			// UNIT 입고
	case	JOB_TYPE_UNIT_RET:				return BLUE;			// UNIT 출고
	case	99:                             //정지 
	case	JOB_TYPE_PICK_REPLENISH:		return YELLOW;			// 피킹출고/보충입고
	case	JOB_TYPE_STN_TO_STN:			return CYAN;			// 이동
	case	JOB_TYPE_AISLE_TO_AISLE:		return MAGENTA;			//마지막 팔렛트

	case	JOB_TYPE_MANUAL_STO:			return DARK_GREEN;		// 반자동 입고
	case	JOB_TYPE_RACK_TO_RACK:			return BLACK;		    // 반자동 출고
	case    JOB_TYPE_MANUAL_STN_TO_STN:		return DARK_YELLOW;     // 반자동 이동

	default	: 
		{
		if(!bOpMode) 
			return DARK_GRAY;
		else if(bPltSensor)
			return DARK_GRAY;
		else 
			return LIGHT_GRAY;		
		}
		break;
	}

	if(!bOpMode) 
	 return DARK_GRAY;

	return LIGHT_GRAY;
}

BOOL CEcsView::IsReportingStatusTrack(int nTrack)
{
	switch ( nTrack )
	{
	case	9:	
	case	71:		
	case	793:	return TRUE;
	}

	return FALSE;
}

LRESULT CEcsView::OnScNotify(WPARAM wParam, LPARAM lParam) 
{
	CMainFrame* pWnd = (CMainFrame *)AfxGetMainWnd();

	int i = wParam;
	CEcsDoc* pDoc = GetDocument();
		
	CStackerControl* pSc;

	if (pDoc->m_pStackerInfo[i]->m_bModified)
	{
		int nStatus = pDoc->m_pStackerInfo[i]->m_ucStatus;
		if (nStatus != SC_STA_ERROR &&
			pDoc->m_pStackerInfo[i]->m_ucMode != SC_MODE_REMOTE)
			nStatus = SC_STA_MANUAL;

		BOOL bEstop = FALSE;
		if (pDoc->m_pStackerInfo[i]->m_bStoreSuspend ||
			pDoc->m_pStackerInfo[i]->m_bRetrieveSuspend)
			bEstop = TRUE;

		if (nStatus == SC_STA_ERROR)
			int i = 0;

		BOOL bProdLoad = (pDoc->m_pStackerInfo[i]->m_ucProdLoad == SC_PROD_LOAD) ? TRUE : FALSE;
		pSc = (CStackerControl *)GetDlgItem(IDC_STACKER_1 + i);
		short	sHorizPos = pDoc->m_pStackerInfo[i]->m_nHorizontalPos;
		if (sHorizPos > BAY_CNT)	sHorizPos = BAY_CNT;

		BOOL bInvoke = pDoc->m_pStackerInfo[i]->m_bSecondInvoke ? TRUE : FALSE;
			 bInvoke = pDoc->m_pStackerInfo[i]->m_bInvoke ? TRUE : FALSE;

		pSc->SetValue(sHorizPos, 
			pDoc->m_pStackerInfo[i]->m_bSecondInternalJobType, 
			bEstop,
			pDoc->m_pStackerInfo[i]->m_bSecondInvoke,
			bProdLoad, 
			nStatus, 
			pDoc->m_pStackerInfo[i]->m_bInternalJobType, 
			pDoc->m_pStackerInfo[i]->m_bInvoke);

		pDoc->m_pStackerInfo[i]->m_bModified = FALSE;

		if (lParam == NOTIFY_REFRESH && pDoc->m_pHostCl != NULL) pDoc->m_pHostCl->Status();
	}

	if (pDoc->m_pStackerInfo[i]->m_ucStatus == SC_STA_ERROR)
	{
		CString strMsg;
		strMsg.Format("Stacker #%d error.. ErrCode=[%d] Please check this..", i + 1, pDoc->m_pStackerInfo[i]->m_wErrCode);
		pDoc->DisplayMessage(strMsg, FALSE);
		pDoc->m_bScSta[i] = FALSE;
	}
	else
		pDoc->m_bScSta[i] = TRUE;

	pWnd->UpdateCommSc(wParam + ID_COMM_SC_1, ConvertNotifyToStatus(lParam));

	return 0;
}

LRESULT CEcsView::OnRgvNotify(WPARAM wParam, LPARAM lParam) 
{
	CMainFrame* pWnd = (CMainFrame *)AfxGetMainWnd();

	int i = wParam;
	CEcsDoc* pDoc = GetDocument();
		
	CScControl* pRgv;

	if (pDoc->m_pRgvInfo[i]->m_bModified)
	{
		BOOL bProdLoad = (pDoc->m_pRgvInfo[i]->m_ucProdLoad == '1') ? TRUE : FALSE;
		pRgv = (CScControl *)GetDlgItem(IDC_RTVCTRL1 + i);

		GetConvertHorizontalPos(i, pDoc->m_pRgvInfo[i]->m_ucHorizontalPos);

		//if(pDoc->m_bRtvCpError[0] == TRUE)
		//	pDoc->m_pRgvInfo[0]->m_ucStatus = RGV_STA_ERROR;

		pRgv->SetValue(	pDoc->m_pRgvInfo[i]->m_ucHorizontalPosSave, 
						pDoc->m_pRgvInfo[i]->GetForkColor() , 
						LIGHT_GRAY,
						pDoc->m_pRgvInfo[i]->GetRailColor(), 
						bProdLoad, 
						DARK_GRAY);

		pDoc->m_pRgvInfo[i]->m_bModified = FALSE;
	}

	if (pDoc->m_pRgvInfo[i]->m_ucStatus == SC_STA_ERROR)
	{
		CString strMsg;
			strMsg.Format("Rtv #%d error.. ErrCode=[%d] Please check this..", i + 1, pDoc->m_pRgvInfo[i]->m_wErrCode);
		pDoc->DisplayMessage(strMsg, FALSE);
	}

//	if (lParam == NOTIFY_REFRESH && pDoc->m_pHostCl != NULL) pDoc->m_pHostCl->Status(TRUE);

	pWnd->UpdateCommRgv(wParam + ID_COMM_RGV_1, ConvertNotifyToStatus(lParam));

	return 0;
}

void CEcsView::GetConvertHorizontalPos(int nRgvNum, int nHorizontal)
{
	CEcsDoc* pDoc = GetDocument();

 	switch(nRgvNum)
	{
	case	RGV_1_NUM:
		switch ( pDoc->m_pRgvInfo[0]->m_ucHorizontalPos )
		{
		case	0:		
		case	1:		pDoc->m_pRgvInfo[RGV_1_NUM]->m_ucHorizontalPosSave = 0;		break;
		case	2:		pDoc->m_pRgvInfo[RGV_1_NUM]->m_ucHorizontalPosSave = 1;		break;
		case	3:		pDoc->m_pRgvInfo[RGV_1_NUM]->m_ucHorizontalPosSave = 2;		break;
		case	4:		pDoc->m_pRgvInfo[RGV_1_NUM]->m_ucHorizontalPosSave = 3;		break;
		case	5:		pDoc->m_pRgvInfo[RGV_1_NUM]->m_ucHorizontalPosSave = 4;		break;
		case	6:		pDoc->m_pRgvInfo[RGV_1_NUM]->m_ucHorizontalPosSave = 5;		break;
		case	7:		pDoc->m_pRgvInfo[RGV_1_NUM]->m_ucHorizontalPosSave = 6;		break;
		case	8:		pDoc->m_pRgvInfo[RGV_1_NUM]->m_ucHorizontalPosSave = 7;		break;
		case	9:		pDoc->m_pRgvInfo[RGV_1_NUM]->m_ucHorizontalPosSave = 8;		break;
		case	10:		pDoc->m_pRgvInfo[RGV_1_NUM]->m_ucHorizontalPosSave = 9;		break;
		case	11:		pDoc->m_pRgvInfo[RGV_1_NUM]->m_ucHorizontalPosSave = 10;	break;
		case	12:		pDoc->m_pRgvInfo[RGV_1_NUM]->m_ucHorizontalPosSave = 11;	break;
		default	: 
			pDoc->m_pRgvInfo[RGV_1_NUM]->m_ucHorizontalPosSave = 0;		break;
		}
		break;
	case	RGV_2_NUM:
		switch ( pDoc->m_pRgvInfo[1]->m_ucHorizontalPos )
		{
		case	0:		
		case	1:		pDoc->m_pRgvInfo[RGV_2_NUM]->m_ucHorizontalPosSave = 0;		break;
		case	2:		pDoc->m_pRgvInfo[RGV_2_NUM]->m_ucHorizontalPosSave = 1;		break;
		case	3:		pDoc->m_pRgvInfo[RGV_2_NUM]->m_ucHorizontalPosSave = 2;		break;
		case	4:		pDoc->m_pRgvInfo[RGV_2_NUM]->m_ucHorizontalPosSave = 3;		break;
		case	5:		pDoc->m_pRgvInfo[RGV_2_NUM]->m_ucHorizontalPosSave = 4;		break;
		case	6:		pDoc->m_pRgvInfo[RGV_2_NUM]->m_ucHorizontalPosSave = 5;		break;
		case	7:		
		case	8:		pDoc->m_pRgvInfo[RGV_2_NUM]->m_ucHorizontalPosSave = 6;		break;
		case	9:		pDoc->m_pRgvInfo[RGV_2_NUM]->m_ucHorizontalPosSave = 7;		break;
		case	10:		
		case	11:		pDoc->m_pRgvInfo[RGV_2_NUM]->m_ucHorizontalPosSave = 8;	    break;
		case	12:		pDoc->m_pRgvInfo[RGV_2_NUM]->m_ucHorizontalPosSave = 9;	    break;
		case	13:		pDoc->m_pRgvInfo[RGV_2_NUM]->m_ucHorizontalPosSave = 10;	break;
		default	: 
			pDoc->m_pRgvInfo[RGV_2_NUM]->m_ucHorizontalPosSave = 0;		break;
		}
		break;
	}
}

LRESULT CEcsView::OnHostNotify(WPARAM wParam, LPARAM lParam) 
{
	CMainFrame* pWnd = (CMainFrame *)AfxGetMainWnd();

	pWnd->UpdateCommHost(wParam + ID_COMM_HOST_CLIENT, ConvertNotifyToStatus(lParam));

	return 0;
}

LRESULT CEcsView::OnEcsNotify(WPARAM wParam, LPARAM lParam) 
{
	CMainFrame* pWnd = (CMainFrame *)AfxGetMainWnd();

	pWnd->UpdateCommEcsCl(ConvertNotifyToStatus(lParam));

	return 0;
}

int CEcsView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	int nTimerID = SetTimer(ID_MAIN_TIMER, 1000, NULL); 

	return 0;
}

void CEcsView::OnLBtnClickRgv(short nID) 
{
	CEcsDoc* pDoc = GetDocument();
	CRgvDlg RgvDlg;

	RgvDlg.m_nID = nID;
	RgvDlg.m_pDoc = GetDocument();
//	RgvDlg.m_pDoc = pDoc; 
	RgvDlg.DoModal();
}

void CEcsView::OnLBtnClickOpbox(short nID) 
{
	COpBoxDlg OpBoxDlg;

	OpBoxDlg.m_nID = nID;
	OpBoxDlg.m_pDoc = GetDocument();
	OpBoxDlg.DoModal();
}

void CEcsView::OnLBtnClickStacker(short nID) 
{

	CStackerTwinDlg StackerDlg;

	StackerDlg.m_nID = nID;
	StackerDlg.m_pDoc = GetDocument();
	StackerDlg.DoModal();

}

void CEcsView::OnLBtnClickConveyor(short nID) 
{
//	CConveyorDlg ConveyorDlg;
	CCvLineDlg CvLineDlg;

	if(nID == 486 || nID == 487 || nID == 586 || 
	   nID == 587 || nID == 682 || nID == 683 || nID == 74 || nID == 75) return;


	//if(nID < 900 || nID >= 2000)
	{
		m_ConveyorDlg.m_nID = nID;
		m_ConveyorDlg.m_pDoc = GetDocument();

		if (m_ConveyorDlg.m_hWnd == NULL) 
		{
			m_ConveyorDlg.Create(IDD_CV_CTRL);
		 
			CRect MainRect;
			CRect Rect;
			CRect PosRect;

			::AfxGetApp()->GetMainWnd()->GetWindowRect(&MainRect);   
			m_ConveyorDlg.GetWindowRect(&Rect); 

			PosRect.left = ((MainRect.right  - MainRect.left) - Rect.Width())  / 2; 
			PosRect.top  = ((MainRect.bottom - MainRect.top)  - Rect.Height()) / 2; 
			m_ConveyorDlg.SetWindowPos(&wndTop, PosRect.left, PosRect.top, 
										Rect.Width(), Rect.Height(), 
										SWP_SHOWWINDOW);

		} 
		else 
		{
			if (!m_ConveyorDlg.IsWindowVisible()) m_ConveyorDlg.ShowWindow(SW_SHOWNORMAL);
			m_ConveyorDlg.SendMessage(WM_INITDIALOG);   
		}
	}
	//else
	//{
	//	CvLineDlg.m_nID = nID;
	//	CvLineDlg.m_pDoc = GetDocument();
	//	CvLineDlg.DoModal();
	//}
}

void CEcsView::OnInitialUpdate() 
{
	CEcsDoc* pDoc = GetDocument();

	CMainFrame* pWnd = (CMainFrame *)AfxGetMainWnd();

	pWnd->SetViewHandle(m_hWnd);

	m_bTroubleCheck = pDoc->m_bWriteTroubleCheck;
	m_bLineTroubleCheck = pDoc->m_bWriteLineTroubleCheck;

	m_bStackingCheck1 = pDoc->m_bWriteStackingCheck1;
	m_bStackingCheck2 = pDoc->m_bWriteStackingCheck2;

	m_bStopCheck = pDoc->m_bJobStopCheck;

	m_bBufferStopCheck = pDoc->m_bBufferStopCheck;

	m_bLineCheck = pDoc->m_bSetLineCheck;
	m_bLineCheck2 = pDoc->m_bSetLineCheck2;
	m_bCountCheck = pDoc->m_bSetCountCheck;

	m_bTestCheck = pDoc->m_bSetTestCheck; //임시방편

	m_bPriorityCheck = pDoc->m_bPriorityDocCheck;

	m_bAllSEmergenCheck = pDoc->m_bAllStackerEmergency;
	
	m_bAllScStoSuspend = pDoc->m_bAllScStoSuspend;
	m_bAllScRetSuspend = pDoc->m_bAllScRetSuspend;

	CFormView::OnInitialUpdate();

	m_b4Check = pDoc->m_b4groupCheck;
	m_b5Check = pDoc->m_b5groupCheck;
	m_b6Check = pDoc->m_b6groupCheck;
	m_b7Check = pDoc->m_b7groupCheck;
	m_b8Check = pDoc->m_b8groupCheck;
	m_b9Check = pDoc->m_b9groupCheck;

	UpdateData(FALSE);

	CEcsGraphControl *pJobProgress;//, *pJobResult;
	
	pJobProgress = (CEcsGraphControl *)GetDlgItem(IDC_JOB_PROGRESS_GRAPH); 
//	pJobResult = (CEcsGraphControl *)GetDlgItem(IDC_JOB_RESULT_GRAPH); 
	
	CString strLabel = "#1  #2   #3   #4    #5    #6";
	pJobProgress->SetProperty(SC_CNT, strLabel);
//	pJobResult->SetProperty(SC_CNT, strLabel);

	::PostMessage(m_hWnd, WM_USER_JOB_NOTIFY, JOB_PROGRESS_DRAW, 0);
//	::PostMessage(m_hWnd, WM_USER_JOB_NOTIFY, JOB_RESULT_DRAW, 0);

	CString strBttName;
	m_bttWnd.Create(this);
	m_bttWnd.SetWidth(400);
	m_bttWnd.SetBkColor(YELLOW);
	m_bttWnd.SetFrameColor(RGB(131,0,250));

/*	CRackControl* pRack;
	for ( int i = IDC_RACK_1; i <= IDC_RACK_12; i++ )
	{
		pRack = (CRackControl *)GetDlgItem(i);
		if (pRack == NULL) continue;
		pRack->SetProperty(i - IDC_RACK_1, HorizontalLeft, BAY_CNT, FORK_SIZE);
		
	}
*/
	CStackerControl* pSc;
	for (int i = IDC_STACKER_1; i < IDC_STACKER_1 + SC_CNT; i++ )
	{
		pSc = (CStackerControl *)GetDlgItem(i);
		if ( pSc == NULL ) continue;

		int nScNum = i - IDC_STACKER_1;
		pSc->SetProperty(nScNum , HorizontalLeft, TwinFork, FORK_SIZE, BAY_CNT, MAX_DISPLAY_POS);

		strBttName.Format("S/C #%d", i - IDC_STACKER_1  + 1);
		m_bttWnd.AddTool(GetDlgItem(i), strBttName);
	}

	CScControl* pRtv;
	for (i = IDC_RTVCTRL1; i < IDC_RTVCTRL1 + RGV_CNT; i++ )
	{
		pRtv = (CScControl *)GetDlgItem(i);
		if ( pRtv == NULL ) continue;

		pRtv->SetID(i - IDC_RTVCTRL1);

		strBttName.Format("RTV #%d", i - IDC_RTVCTRL1  + 1);
		m_bttWnd.AddTool(GetDlgItem(i), strBttName);
	}


	CCvControl* pCv;
	for (i = IDC_CVCTRL1; i < IDC_CVCTRL1 + CV_1_TRACK_CNT+2; i++)
	{
		pCv = (CCvControl *)GetDlgItem(i);
		if (pCv == NULL) continue;

		pCv->SetID(i - IDC_CVCTRL1);

		int nTrackNum = i - IDC_CVCTRL1 + 1;
		//if (nTrackNum == 9)
		if (nTrackNum == 8)
		{
			strBttName.Format("C/V Track #%d\n생산입고대", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
		else if(nTrackNum == 71)
		{
			strBttName.Format("C/V Track #%d\n외주입고대", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
		else if(nTrackNum == 75)
		{
			strBttName.Format("입고 DOOR #1");
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
		else if(nTrackNum == 76)
		{
			strBttName.Format("입고 DOOR #2");
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
		else
		{
			strBttName.Format("C/V Track #%d", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
	}
		
	for (i = IDC_CVCTRL301; i < IDC_CVCTRL301 + CV_3_TRACK_CNT; i++)
	{
		pCv = (CCvControl *)GetDlgItem(i);
		if (pCv == NULL) continue;

		pCv->SetID(i+300 - IDC_CVCTRL301);

		int nTrackNum = i - IDC_CVCTRL301 + 301;

		strBttName.Format("C/V Track #%d", nTrackNum);
		m_bttWnd.AddTool(GetDlgItem(i), strBttName);
	}

	for (i = IDC_CVCTRL401; i < IDC_CVCTRL401 + CV_4_TRACK_CNT+2; i++)
	{
		pCv = (CCvControl *)GetDlgItem(i);
		if (pCv == NULL) continue;

		pCv->SetID(i+400 - IDC_CVCTRL401);

		int nTrackNum = i - IDC_CVCTRL401 + 401;

		if (nTrackNum == 487)
		{
			strBttName.Format("출하대#1 DOOR #1", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
		else if(nTrackNum == 488)
		{
			strBttName.Format("출하대#1 DOOR #2", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
		else
		{
			strBttName.Format("C/V Track #%d", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
	}

	for (i = IDC_CVCTRL501; i < IDC_CVCTRL501 + CV_5_TRACK_CNT+2; i++)
	{
		pCv = (CCvControl *)GetDlgItem(i);
		if (pCv == NULL) continue;

		pCv->SetID(i+500 - IDC_CVCTRL501);

		int nTrackNum = i - IDC_CVCTRL501 + 501;

		if (nTrackNum == 587)
		{
			strBttName.Format("출하대#2 DOOR #1", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
		else if(nTrackNum == 588)
		{
			strBttName.Format("출하대#2 DOOR #2", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
		else
		{
			strBttName.Format("C/V Track #%d", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
	}

	for (i = IDC_CVCTRL601; i < IDC_CVCTRL601 + CV_6_TRACK_CNT+2; i++)
	{
		pCv = (CCvControl *)GetDlgItem(i);
		if (pCv == NULL) continue;

		pCv->SetID(i+600 - IDC_CVCTRL601);

		int nTrackNum = i - IDC_CVCTRL601 + 601;

		if (nTrackNum == 683)
		{
			strBttName.Format("출하대#3 DOOR #1", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
		else if(nTrackNum == 684)
		{
			strBttName.Format("출하대#3 DOOR #2", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
		else
		{
			strBttName.Format("C/V Track #%d", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
	}

	for (i = IDC_CVCTRL701; i < IDC_CVCTRL701 + CV_7_TRACK_CNT; i++)
	{
		pCv = (CCvControl *)GetDlgItem(i);
		if (pCv == NULL) continue;

		pCv->SetID(i+700 - IDC_CVCTRL701);

		int nTrackNum = i - IDC_CVCTRL701 + 701;

		if(nTrackNum == 746)
		{
			strBttName.Format("Stacking#1", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
		else
		{
			strBttName.Format("C/V Track #%d", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
	}

	for (i = IDC_CVCTRL901; i < IDC_CVCTRL901 + CV_2_TRACK_CNT; i++)
	{
		pCv = (CCvControl *)GetDlgItem(i);
		if (pCv == NULL) continue;

		pCv->SetID(i+900 - IDC_CVCTRL901);

		int nTrackNum = i - IDC_CVCTRL901 + 901;

//		if (nTrackNum == 1050 || nTrackNum == 1051 || nTrackNum == 1052 || nTrackNum == 1053 || nTrackNum == 1054)
//		{
//			strBttName.Format("SPL Stacker #%d", nTrackNum-1049);
//			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
//		}
//		else
		{
			strBttName.Format("C/V Track #%d", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
	}

	/* 250124 LJM 주석
		*/
	for (i = 7601; i < 7601 + CV_8_TRACK_CNT; i++)
	{
		pCv = (CCvControl *)GetDlgItem(i);
		if (pCv == NULL) continue;

		pCv->SetID(i+2000 - 7601);

		int nTrackNum = i - 7601 + 2001;

		if(nTrackNum == 2005)
		{
			strBttName.Format("Stacking#2", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
		else
		{
			strBttName.Format("C/V Track #%d", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
	}

	for (i = 7701; i < 7701 + CV_9_TRACK_CNT; i++)
	{
		pCv = (CCvControl *)GetDlgItem(i);
		if (pCv == NULL) continue;

		pCv->SetID(i+2100 - 7701);

		int nTrackNum = i - 7701 + 2101;

		if(nTrackNum == 2202 || nTrackNum == 2212 || nTrackNum == 2222 || nTrackNum == 2232 || nTrackNum == 2242 || nTrackNum == 2252)
		{
			strBttName.Format("Stacking CV#%d", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
		else
		{
			strBttName.Format("C/V Track #%d", nTrackNum);
			m_bttWnd.AddTool(GetDlgItem(i), strBttName);
		}
	}

	COpBoxControl* pOpBox;
	for (i = IDC_OPBOXCTRL1; i <= IDC_OPBOXCTRL1 + OPBOX_CNT; i++)
	{
		pOpBox = (COpBoxControl *)GetDlgItem(i);
		if (pOpBox == NULL) continue;

		pOpBox->SetID(i - IDC_OPBOXCTRL1);

		int nOpBoxNum = i - IDC_OPBOXCTRL1 + 1;

		switch (nOpBoxNum)
		{
		case 1 :
			strBttName.Format("OP-Box #1-1");
			break;
		case 2 :
			strBttName.Format("OP-Box #1-2");
			break;
		case 3 :
			strBttName.Format("OP-Box #1-3");
			break;
		case 4 :
			strBttName.Format("OP-Box #1-4");
			break;
		case 5 :
			strBttName.Format("OP-Box #1-5");
			break;
		case 6 :
			strBttName.Format("OP-Box #2-1");
			break;
		case 7 :
			strBttName.Format("OP-Box #2-2");
			break;
		case 8 :
			strBttName.Format("OP-Box #2-3");
			break;
		case 9 :
			strBttName.Format("OP-Box #2-4");
			break;
		case 10 :
			strBttName.Format("OP-Box #2-5");
			break;
		case 11 :
			strBttName.Format("OP-Box #2-6");
			break;
		case 12 :
			strBttName.Format("OP-Box #2-7");
			break;
		case 13 :
			strBttName.Format("OP-Box #2-8");
			break;
		case 14 :
			strBttName.Format("OP-Box #2-9");
			break;
		case 15 :
			strBttName.Format("OP-Box #2-10");
			break;
		case 16 :
			strBttName.Format("OP-Box #2-11");
			break;
		case 17 :
			strBttName.Format("OP-Box #2-12");
			break;
		case 18 :
			strBttName.Format("OP-Box #2-13");
			break;
		case 19 :
			strBttName.Format("OP-Box #3-1");
			break;
		case 20 :
			strBttName.Format("OP-Box #3-2");
			break;
		case 21 :
			strBttName.Format("OP-Box #3-3");
			break;
		case 22 :
			strBttName.Format("OP-Box #4-1");
			break;
		case 23 :
			strBttName.Format("OP-Box #4-2");
			break;
		case 24 :
			strBttName.Format("OP-Box #5-1");
			break;
		case 25 :
			strBttName.Format("OP-Box #5-2");
			break;
		case 26 :
			strBttName.Format("OP-Box #6-1");
			break;
		case 27 :
			strBttName.Format("OP-Box #6-2");
			break;
		}

		m_bttWnd.AddTool(GetDlgItem(i), strBttName);
	}

	LOGFONT LogFont;
	CFont font;
//	font.CreateFont (100, 100, 100, 100, 900, FALSE, 100, 100, 1, 100, 100, 100, 100, _T("System") );
	font.CreateFont (10, 0, 0, 0, 100, FALSE, 0, 0, 1, 0, 0, 0, 0, _T("System") );
	font.GetLogFont(&LogFont);

	for( CWnd* pChildWnd = GetWindow(GW_CHILD); pChildWnd != NULL; pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT))
	{
		CRuntimeClass *prt = pChildWnd->GetRuntimeClass();
		pChildWnd->SetFont(&font);

		//IsKindof가 안먹히는지 .. 테스트 할것
//		if( CString("CEditEx") == prt->m_lpszClassName )
//			((CEditEx*)pChildWnd)->SetTextColor(RGB(0, 0, 255));
	}

}

char CEcsView::ConvertNotifyToStatus(int nNotify) 
{
	switch (nNotify)
	{
	case	NOTIFY_SEND:
		return COMM_STA_SEND;
	case	NOTIFY_RECEIVE:
	case	NOTIFY_REFRESH:
		return COMM_STA_RECEIVE;
	case	NOTIFY_ERROR:
	default:
		return COMM_STA_STOP;
	}
}

LRESULT CEcsView::OnJobNotify(WPARAM wParam, LPARAM lParam) 
{
	CEcsDoc* pDoc = GetDocument();

	if ( wParam == JOB_PROGRESS_DRAW )
	{
		CEcsGraphControl *pJobProgress = (CEcsGraphControl *)GetDlgItem(IDC_JOB_PROGRESS_GRAPH); 
		
		for ( int i = 0; i < SC_CNT; i++ )
		{
			pJobProgress->SetValue(i, pDoc->m_pJob->GetJobCount(i)+5, pDoc->m_pJob->GetJobCount(i));
		}
		pJobProgress->Draw();
	}
/*
	else
	{
		CEcsGraphControl *pJobResult = (CEcsGraphControl *)GetDlgItem(IDC_JOB_RESULT_GRAPH); 
		
		for ( int i = 0; i < SC_CNT; i++ )
		{
			pJobResult->SetValue(i, pDoc->m_pJob->GetResultCount(i)/10, pDoc->m_pJob->GetResultCount(i));
		}
		pJobResult->Draw();
	}
*/
	return 0;
}

BOOL CEcsView::PreTranslateMessage(MSG* pMsg) 
{
	m_bttWnd.RelayEvent(pMsg);
		
	return CFormView::PreTranslateMessage(pMsg);
}

/*
void CEcsView::OnButtonOrder() 
{
	CResetOrderDlg ResetOrderDlg;

	ResetOrderDlg.m_pDoc = GetDocument();
	ResetOrderDlg.DoModal();
	
}
*/
/*
void CEcsView::CountFont()
{
	LOGFONT LogFont;
	CFont font;
	font.CreateFont (10, 0, 0, 0, 100, FALSE, 0, 0, 1, 0, 0, 0, 0, _T("System") );
	font.GetLogFont(&LogFont);

//	m_edt4GroupInCount.SetEditExFont(24);
//	m_edt4GroupInCount.SetBkColor(RGB(255, 255, 223));
//	m_edt4GroupInCount.SetTextColor(RGB(0, 0, 255));
	m_edt4GroupInCount.SetBkColor(RGB(0, 0, 64));
	m_edt4GroupInCount.SetTextColor(RGB(0, 255, 0));
	m_edt4GroupInCount.SetFont(&font);

//	m_edt4GroupOutCount.SetEditExFont(24);
//	m_edt4GroupOutCount.SetBkColor(RGB(255, 255, 223));
//	m_edt4GroupOutCount.SetTextColor(RGB(0, 0, 255));
	m_edt4GroupOutCount.SetBkColor(RGB(0, 0, 64));
	m_edt4GroupOutCount.SetTextColor(RGB(0, 255, 0));
	m_edt4GroupOutCount.SetFont(&font);

//	m_edt5GroupInCount.SetEditExFont(24);
//	m_edt5GroupInCount.SetBkColor(RGB(255, 255, 223));
//	m_edt5GroupInCount.SetTextColor(RGB(0, 0, 255));
	m_edt5GroupInCount.SetBkColor(RGB(0, 0, 64));
	m_edt5GroupInCount.SetTextColor(RGB(0, 255, 0));
	m_edt5GroupInCount.SetFont(&font);

//	m_edt5GroupOutCount.SetEditExFont(24);
//	m_edt5GroupOutCount.SetBkColor(RGB(255, 255, 223));
//	m_edt5GroupOutCount.SetTextColor(RGB(0, 0, 255));
	m_edt5GroupOutCount.SetBkColor(RGB(0, 0, 64));
	m_edt5GroupOutCount.SetTextColor(RGB(0, 255, 0));
	m_edt5GroupOutCount.SetFont(&font);

//	m_edt6GroupInCount.SetEditExFont(24);
//	m_edt6GroupInCount.SetBkColor(RGB(255, 255, 223));
//	m_edt6GroupInCount.SetTextColor(RGB(0, 0, 255));
	m_edt6GroupInCount.SetBkColor(RGB(0, 0, 64));
	m_edt6GroupInCount.SetTextColor(RGB(0, 255, 0));
	m_edt6GroupInCount.SetFont(&font);

//	m_edt6GroupOutCount.SetEditExFont(24);
//	m_edt6GroupOutCount.SetBkColor(RGB(255, 255, 223));
//	m_edt6GroupOutCount.SetTextColor(RGB(0, 0, 255));
	m_edt6GroupOutCount.SetBkColor(RGB(0, 0, 64));
	m_edt6GroupOutCount.SetTextColor(RGB(0, 255, 0));
	m_edt6GroupOutCount.SetFont(&font);
}
*/


void CEcsView::OnCheckBufferFull1() 
{
	CEcsDoc* pDoc = GetDocument();

//	if (AfxMessageBox("출하분류대#1에 만차기능을 해제 하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
//	return;
	pDoc->m_b4groupCheck = !pDoc->m_b4groupCheck;
}

void CEcsView::OnCheckBufferFull2() 
{
	CEcsDoc* pDoc = GetDocument();

//	if (AfxMessageBox("출하분류대#2에 만차기능을 해제 하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
//	return;
	pDoc->m_b5groupCheck = !pDoc->m_b5groupCheck;
}

void CEcsView::OnCheckBufferFull3() 
{
	CEcsDoc* pDoc = GetDocument();

//	if (AfxMessageBox("출하분류대#3에 만차기능을 해제 하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
//	return;	
	pDoc->m_b6groupCheck = !pDoc->m_b6groupCheck;
}

void CEcsView::OnCheckBufferFull4() 
{
	CEcsDoc* pDoc = GetDocument();

//	if (AfxMessageBox("출하이동대에 만차기능을 해제 하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
//	return;	
	pDoc->m_b7groupCheck = !pDoc->m_b7groupCheck;
}

void CEcsView::OnCheckBufferFull5() 
{
	CEcsDoc* pDoc = GetDocument();
	pDoc->m_b8groupCheck = !pDoc->m_b8groupCheck;
}

void CEcsView::OnCheckBufferFull6() 
{
	CEcsDoc* pDoc = GetDocument();
	pDoc->m_b9groupCheck = !pDoc->m_b9groupCheck;
}

#define TRACK_TROUBLE_MSG	pDoc->m_ConveyorThreadInfo[CV_7_PLC].m_ConveyorTroubleMsg


void CEcsView::OnCheckTrouble() 
{
	CString strLog;
	int nLineMode=0;
	CEcsDoc* pDoc = GetDocument();

	UpdateData(TRUE);

	pDoc->m_bWriteTroubleCheck = !pDoc->m_bWriteTroubleCheck;

	if(pDoc->m_bWriteTroubleCheck == TRUE)
	{
		if (AfxMessageBox("비상 LINE 상태로 바꾸시겠습니가?", MB_OKCANCEL) == IDCANCEL)
		{
			pDoc->m_bWriteTroubleCheck = FALSE;
			return;	
		}
	}

	if(pDoc->m_bWriteTroubleCheck == FALSE)
	{
		if (AfxMessageBox("정상 LINE 상태로 바꾸시겠습니가?", MB_OKCANCEL) == IDCANCEL)
		{
			pDoc->m_bWriteTroubleCheck = TRUE;
			return;	
		}
	}

	if(pDoc->m_bWriteTroubleCheck == TRUE)
		nLineMode = 1;
	else
		nLineMode = 2;


	pDoc->m_ConveyorThreadInfo[CV_7_PLC].m_PlcCountMsg.nTrackNum = 808-1;

	pDoc->m_ConveyorThreadInfo[CV_7_PLC].m_PlcCountMsg.nPlcCount = nLineMode;

	pDoc->m_ConveyorThreadInfo[CV_7_PLC].m_PlcCountMsg.bModified = TRUE;

    pDoc->m_nConveyorEventCount[CV_7_PLC]++; SetEvent(pDoc->m_hEventSendConveyor[CV_7_PLC]);


	strLog.Format("외주 창고 비상라인 모드 변경 [%d]", nLineMode);
	pDoc->m_pLog->Event(LOG_POS_CV, 9999, strLog);

/*	CEcsDoc* pDoc = GetDocument();

	UpdateData(TRUE);

	pDoc->m_bWriteTroubleCheck = !pDoc->m_bWriteTroubleCheck;

	if(pDoc->m_bWriteTroubleCheck == TRUE)
	{
		if (AfxMessageBox("생산 이동 창고의 비상 LINE 상태로 바꾸시겠습니가?", MB_OKCANCEL) == IDCANCEL)
		{
			pDoc->m_bWriteTroubleCheck = FALSE;
			return;	
		}
	}

	if(pDoc->m_bWriteTroubleCheck == TRUE)
	{
		TRACK_TROUBLE_MSG.nAddressNum = 5;
		TRACK_TROUBLE_MSG.wAddressData = 1;
		TRACK_TROUBLE_MSG.bModified = TRUE;

		pDoc->m_nConveyorEventCount[CV_7_PLC]++; SetEvent(pDoc->m_hEventSendConveyor[CV_7_PLC]);

	}
	else
	{
		TRACK_TROUBLE_MSG.nAddressNum = 5;
		TRACK_TROUBLE_MSG.wAddressData = 0;
		TRACK_TROUBLE_MSG.bModified = TRUE;

		pDoc->m_nConveyorEventCount[CV_7_PLC]++; SetEvent(pDoc->m_hEventSendConveyor[CV_7_PLC]);

	}	
*/
}

BOOL CEcsView::TestMethod(BOOL *bCheck)
{

	*bCheck = TRUE;
	return TRUE;
}

void CEcsView::OnCheckStop() 
{
	CEcsDoc* pDoc = GetDocument();
	pDoc->m_bJobStopCheck = !pDoc->m_bJobStopCheck;
}

void CEcsView::OnCheckSetLine() 
{
	CString strTemp;
	CEcsDoc* pDoc = GetDocument();
	pDoc->m_bSetLineCheck = !pDoc->m_bSetLineCheck;

	if(pDoc->m_bSetLineCheck == FALSE)
	{
		GET(IDC_EDIT_SET_LINE1, strTemp);
		pDoc->m_nSetLine[0] = atoi(strTemp);

		GET(IDC_EDIT_SET_LINE2, strTemp);
		pDoc->m_nSetLine[1] = atoi(strTemp);

		GET(IDC_EDIT_SET_LINE3, strTemp);
		pDoc->m_nSetLine[2] = atoi(strTemp);

		GET(IDC_EDIT_SET_LINE4, strTemp);
		pDoc->m_nSetLine[3] = atoi(strTemp);

		GET(IDC_EDIT_SET_LINE5, strTemp);
		pDoc->m_nSetLine[4] = atoi(strTemp);

		GET(IDC_EDIT_SET_LINE6, strTemp);
		pDoc->m_nSetLine[5] = atoi(strTemp);

		GET(IDC_EDIT_SET_LINE7, strTemp);
		pDoc->m_nSetLine[6] = atoi(strTemp);

		GET(IDC_EDIT_SET_LINE8, strTemp);
		pDoc->m_nSetLine[7] = atoi(strTemp);

		GET(IDC_EDIT_SET_LINE9, strTemp);
		pDoc->m_nSetLine[8] = atoi(strTemp);

		GET(IDC_EDIT_SET_LINE10, strTemp);
		pDoc->m_nSetLine[9] = atoi(strTemp);
	}
}

void CEcsView::OnCheckSetLine2() 
{
	CString strTemp;
	CEcsDoc* pDoc = GetDocument();
	pDoc->m_bSetLineCheck2 = !pDoc->m_bSetLineCheck2;

	if(pDoc->m_bSetLineCheck2 == FALSE)
	{
		GET(IDC_EDIT_SET_LINE109, strTemp);
		pDoc->m_ConveyorThreadInfo[CV_9_PLC].m_ConveyorTroubleMsg.nD[8] = atoi(strTemp);
		//pDoc->m_nSetLine2[8] = atoi(strTemp);

		GET(IDC_EDIT_SET_LINE110, strTemp);
		pDoc->m_ConveyorThreadInfo[CV_9_PLC].m_ConveyorTroubleMsg.nD[9] = atoi(strTemp);
		//pDoc->m_nSetLine2[9] = atoi(strTemp);

		GET(IDC_EDIT_SET_LINE111, strTemp);
		pDoc->m_ConveyorThreadInfo[CV_9_PLC].m_ConveyorTroubleMsg.nD[10] = atoi(strTemp);
		//pDoc->m_nSetLine2[10] = atoi(strTemp);

		GET(IDC_EDIT_SET_LINE112, strTemp);
		pDoc->m_ConveyorThreadInfo[CV_9_PLC].m_ConveyorTroubleMsg.nD[11] = atoi(strTemp);
		//pDoc->m_nSetLine2[11] = atoi(strTemp);

		GET(IDC_EDIT_SET_LINE113, strTemp);
		pDoc->m_ConveyorThreadInfo[CV_9_PLC].m_ConveyorTroubleMsg.nD[12] = atoi(strTemp);
		//pDoc->m_nSetLine2[12] = atoi(strTemp);

		GET(IDC_EDIT_SET_LINE114, strTemp);
		pDoc->m_ConveyorThreadInfo[CV_9_PLC].m_ConveyorTroubleMsg.nD[13] = atoi(strTemp);
		//pDoc->m_nSetLine2[13] = atoi(strTemp);

		pDoc->m_ConveyorThreadInfo[CV_9_PLC].m_ConveyorTroubleMsg.bModified = TRUE;

		pDoc->m_nConveyorEventCount[CV_9_PLC]++; SetEvent(pDoc->m_hEventSendConveyor[CV_9_PLC]);
	}
}

void CEcsView::OnCheckChangeCount() 
{
	CString strTemp;
	CEcsDoc* pDoc = GetDocument();
	pDoc->m_bSetCountCheck = !pDoc->m_bSetCountCheck;

	if(pDoc->m_bSetCountCheck == FALSE)
	{
		GET(IDC_EDIT_SET_COUNT109, strTemp);
		pDoc->m_nSetLineCount2[8] = atoi(strTemp);

		GET(IDC_EDIT_SET_COUNT110, strTemp);
		pDoc->m_nSetLineCount2[9] = atoi(strTemp);

		GET(IDC_EDIT_SET_COUNT111, strTemp);
		pDoc->m_nSetLineCount2[10] = atoi(strTemp);

		GET(IDC_EDIT_SET_COUNT112, strTemp);
		pDoc->m_nSetLineCount2[11] = atoi(strTemp);

		GET(IDC_EDIT_SET_COUNT113, strTemp);
		pDoc->m_nSetLineCount2[12] = atoi(strTemp);

		GET(IDC_EDIT_SET_COUNT114, strTemp);
		pDoc->m_nSetLineCount2[13] = atoi(strTemp);
	}
}

void CEcsView::OnCheckTest() //임시방편
{
	CString strTemp;
	CEcsDoc* pDoc = GetDocument();
	pDoc->m_bSetTestCheck = !pDoc->m_bSetTestCheck;

	if(pDoc->m_bSetTestCheck == FALSE)
	{
		if (AfxMessageBox("기존 LINE 상태로 바꾸시겠습니가?", MB_OKCANCEL) == IDCANCEL)
		{
			pDoc->m_bSetTestCheck = TRUE;
			return;	
		}
	}

	if(pDoc->m_bSetTestCheck == TRUE)
	{
		if (AfxMessageBox("신규 LINE 상태로 바꾸시겠습니가?", MB_OKCANCEL) == IDCANCEL)
		{
			pDoc->m_bSetTestCheck = FALSE;
			return;	
		}
	}


}

void CEcsView::OnButtonSignal() 
{
	CCommonDlg CommonDlg;

	CommonDlg.m_pDoc = GetDocument();
	CommonDlg.DoModal();
}

void CEcsView::OnCheckSetPriority() 
{
	CEcsDoc* pDoc = GetDocument();
	pDoc->m_bPriorityDocCheck = !pDoc->m_bPriorityDocCheck;	
}

void CEcsView::OnCheckLineEmergency() 
{
	CEcsDoc* pDoc = GetDocument();
	CString strLog;
	int nLineMode=0;

	UpdateData(TRUE);
    
	m_bLineEmergencyCheck = m_bLineEmergencyCheck;


	AfxMessageBox("비상 상태를 변경 하시겠습니까? ");

	if(m_bLineEmergencyCheck == TRUE)
		nLineMode = 1;
	else
		nLineMode = 2;


	pDoc->m_ConveyorThreadInfo[CV_7_PLC].m_PlcCountMsg.nTrackNum = 808-1;

	pDoc->m_ConveyorThreadInfo[CV_7_PLC].m_PlcCountMsg.nPlcCount = nLineMode;

	pDoc->m_ConveyorThreadInfo[CV_7_PLC].m_PlcCountMsg.bModified = TRUE;

    pDoc->m_nConveyorEventCount[CV_7_PLC]++; SetEvent(pDoc->m_hEventSendConveyor[CV_7_PLC]);


	strLog.Format("외주 창고 비상라인 모드 변경 [%d]", nLineMode);
	pDoc->m_pLog->Event(LOG_POS_CV, 9999, strLog);

	
}

void CEcsView::OnCheckStacking1() 
{
	CString strLog;
	int nStatusMode=0;
	CEcsDoc* pDoc = GetDocument();

	UpdateData(TRUE);

	pDoc->m_bWriteStackingCheck1 = !pDoc->m_bWriteStackingCheck1;

	if(pDoc->m_bWriteStackingCheck1 == TRUE)
	{
		if (AfxMessageBox("Stacking#1 고장 상태로 바꾸시겠습니가?", MB_OKCANCEL) == IDCANCEL)
		{
			pDoc->m_bWriteStackingCheck1 = FALSE;
			return;	
		}
	}

	if(pDoc->m_bWriteStackingCheck1 == FALSE)
	{
		if (AfxMessageBox("Stacking#1 정상 상태로 바꾸시겠습니가?", MB_OKCANCEL) == IDCANCEL)
		{
			pDoc->m_bWriteStackingCheck1 = TRUE;
			return;	
		}
	}

	if(pDoc->m_bWriteStackingCheck1 == TRUE)
		nStatusMode = 1;
	else
		nStatusMode = 2;


	pDoc->m_ConveyorThreadInfo[CV_7_PLC].m_PlcCountMsg.nTrackNum = 746-1;
	pDoc->m_ConveyorThreadInfo[CV_7_PLC].m_PlcCountMsg.nPlcCount = nStatusMode;
	pDoc->m_ConveyorThreadInfo[CV_7_PLC].m_PlcCountMsg.bModified = TRUE;
    pDoc->m_nConveyorEventCount[CV_7_PLC]++; SetEvent(pDoc->m_hEventSendConveyor[CV_7_PLC]);

	strLog.Format("Stacking#1 고장 모드 변경 [%d]", nStatusMode);
	pDoc->m_pLog->Event(LOG_POS_CV, 9999, strLog);
}

void CEcsView::OnCheckStacking2() 
{
	CString strLog;
	int nStatusMode=0;
	CEcsDoc* pDoc = GetDocument();

	UpdateData(TRUE);

	pDoc->m_bWriteStackingCheck2 = !pDoc->m_bWriteStackingCheck2;

	if(pDoc->m_bWriteStackingCheck2 == TRUE)
	{
		if (AfxMessageBox("Stacking#2 고장 상태로 바꾸시겠습니가?", MB_OKCANCEL) == IDCANCEL)
		{
			pDoc->m_bWriteStackingCheck2 = FALSE;
			return;	
		}
	}

	if(pDoc->m_bWriteStackingCheck2 == FALSE)
	{
		if (AfxMessageBox("Stacking#2 정상 상태로 바꾸시겠습니가?", MB_OKCANCEL) == IDCANCEL)
		{
			pDoc->m_bWriteStackingCheck2 = TRUE;
			return;	
		}
	}

	if(pDoc->m_bWriteStackingCheck2 == TRUE)
		nStatusMode = 1;
	else
		nStatusMode = 2;


	pDoc->m_ConveyorThreadInfo[CV_8_PLC].m_PlcCountMsg.nTrackNum = 2005-1;
	pDoc->m_ConveyorThreadInfo[CV_8_PLC].m_PlcCountMsg.nPlcCount = nStatusMode;
	pDoc->m_ConveyorThreadInfo[CV_8_PLC].m_PlcCountMsg.bModified = TRUE;
    pDoc->m_nConveyorEventCount[CV_8_PLC]++; SetEvent(pDoc->m_hEventSendConveyor[CV_8_PLC]);

	Sleep(500);

	pDoc->m_ConveyorThreadInfo[CV_7_PLC].m_PlcCountMsg.nTrackNum = 745-1;
	pDoc->m_ConveyorThreadInfo[CV_7_PLC].m_PlcCountMsg.nPlcCount = nStatusMode;
	pDoc->m_ConveyorThreadInfo[CV_7_PLC].m_PlcCountMsg.bModified = TRUE;
    pDoc->m_nConveyorEventCount[CV_7_PLC]++; SetEvent(pDoc->m_hEventSendConveyor[CV_7_PLC]);


	strLog.Format("Stacking#2 고장 모드 변경 [%d]", nStatusMode);
	pDoc->m_pLog->Event(LOG_POS_CV, 9999, strLog);
}



void CEcsView::OnButtonResetIncount() 
{
	CString strLog;
	CEcsDoc* pDoc = GetDocument();

	if (AfxMessageBox("In Counter를 초기화 하시겠습니까? ", MB_OKCANCEL) == IDCANCEL)
		return ;

	pDoc->m_nInCountReset = 403;

	pDoc->m_bInResetCheck = TRUE;

    pDoc->m_nConveyorEventCount[CV_3_PLC]++; SetEvent(pDoc->m_hEventSendConveyor[CV_3_PLC]);

	strLog.Format("OnButtonResetIncount.. 출하이동대 In Count 초기화..");
	pDoc->m_pLog->Event(LOG_POS_SYSTEM, 0000, strLog);
}

void CEcsView::OnCheckBufferStop() 
{
	CEcsDoc* pDoc = GetDocument();
	pDoc->m_bBufferStopCheck = !pDoc->m_bBufferStopCheck;
}

void CEcsView::OnCheckStackEmergency() 
{
	CString strLog;
	CEcsDoc* pDoc = GetDocument();

	UpdateData(TRUE);

	pDoc->m_bAllStackerEmergency = !pDoc->m_bAllStackerEmergency;

	if(pDoc->m_bAllStackerEmergency == TRUE)
	{
		if (AfxMessageBox("비상운영 모드로 바꾸시겠습니까?\nIMS에서 작업정보 받지 않고 PLC DATA(검정색)만 생성되어\n생산입고대로 이동합니다!", MB_OKCANCEL) == IDCANCEL)
		{
			pDoc->m_bAllStackerEmergency = FALSE;
			return;	
		}
	}

	if(pDoc->m_bAllStackerEmergency == FALSE)
	{
		if (AfxMessageBox("정상 상태로 바꾸시겠습니까?", MB_OKCANCEL) == IDCANCEL)
		{
			pDoc->m_bAllStackerEmergency = TRUE;
			return;	
		}
	}

	strLog.Format("생산 입고 라인 비상운영 모드 변경 상태[%d]", pDoc->m_bAllStackerEmergency);
	pDoc->m_pLog->Event(LOG_POS_SYSTEM, 0, strLog);
}

void CEcsView::OnCheckScStoSuspend() 
{
	CString strLog;
	CEcsDoc* pDoc = GetDocument();

	if(m_bAllScStoSuspend == TRUE)
	{
		if (AfxMessageBox("SC 전체 입고금지를 해제하시겠습니까?", MB_OKCANCEL) == IDOK)
		{
			m_bAllScStoSuspend = FALSE;
			pDoc->m_bAllScStoSuspend = FALSE;
			for (int i = 0; i < 6; i++)
			{
				pDoc->m_pStackerInfo[i]->m_bStoreSuspend = FALSE;
				pDoc->m_pStackerInfo[i]->m_bModified = TRUE;
			}
			return;	
		}
	}

	if(m_bAllScStoSuspend == FALSE)
	{
		if (AfxMessageBox("SC 전체 입고금지 하시겠습니까?", MB_OKCANCEL) == IDOK)
		{
			m_bAllScStoSuspend = TRUE;
			pDoc->m_bAllScStoSuspend = TRUE;
			for (int i = 0; i < 6; i++)
			{
				pDoc->m_pStackerInfo[i]->m_bStoreSuspend = TRUE;
				pDoc->m_pStackerInfo[i]->m_bModified = TRUE;
			}
			return;	
		}
	}

	strLog.Format("SC 입고금지 상태 변경 상태[%d]", m_bAllScStoSuspend);
	pDoc->m_pLog->Event(LOG_POS_SYSTEM, 0, strLog);

	UpdateData(TRUE);
}

void CEcsView::OnCheckScRetSuspend() 
{
	CString strLog;
	CEcsDoc* pDoc = GetDocument();

	if(m_bAllScRetSuspend == TRUE)
	{
		if (AfxMessageBox("SC 전체 출고금지를 해제하시겠습니까?", MB_OKCANCEL) == IDOK)
		{
			m_bAllScRetSuspend = FALSE;
			pDoc->m_bAllScRetSuspend = FALSE;
			for (int i = 0; i < 6; i++)
			{
				pDoc->m_pStackerInfo[i]->m_bRetrieveSuspend = FALSE;
				pDoc->m_pStackerInfo[i]->m_bModified = TRUE;
			}
			return;	
		}
	}

	if(m_bAllScRetSuspend == FALSE)
	{
		if (AfxMessageBox("SC 전체 출고금지 하시겠습니까?", MB_OKCANCEL) == IDOK)
		{
			m_bAllScRetSuspend = TRUE;
			pDoc->m_bAllScRetSuspend = TRUE;
			for (int i = 0; i < 6; i++)
			{
				pDoc->m_pStackerInfo[i]->m_bRetrieveSuspend = TRUE;
				pDoc->m_pStackerInfo[i]->m_bModified = TRUE;
			}
			return;	
		}
	}

	strLog.Format("SC 출고금지 상태 변경 상태[%d]", m_bAllScRetSuspend);
	pDoc->m_pLog->Event(LOG_POS_SYSTEM, 0, strLog);

	UpdateData(TRUE);
}

void CEcsView::OnCheckLineTrouble() 
{
	CString strLog;
	int nLineMode=0;
	CEcsDoc* pDoc = GetDocument();

	UpdateData(TRUE);

	pDoc->m_bWriteLineTroubleCheck = !pDoc->m_bWriteLineTroubleCheck;

	if(pDoc->m_bWriteLineTroubleCheck == TRUE)
	{
		if (AfxMessageBox("고장 상태로 바꾸시겠습니가?", MB_OKCANCEL) == IDCANCEL)
		{
			pDoc->m_bWriteLineTroubleCheck = FALSE;
			return;	
		}
	}

	if(pDoc->m_bWriteLineTroubleCheck == FALSE)
	{
		if (AfxMessageBox("정상 상태로 바꾸시겠습니가?", MB_OKCANCEL) == IDCANCEL)
		{
			pDoc->m_bWriteLineTroubleCheck = TRUE;
			return;	
		}
	}

	if(pDoc->m_bWriteLineTroubleCheck == TRUE)
		nLineMode = 1;
	else
		nLineMode = 0;


	pDoc->m_ConveyorThreadInfo[CV_1_PLC].m_PlcCountMsg.nTrackNum = 181;

	pDoc->m_ConveyorThreadInfo[CV_1_PLC].m_PlcCountMsg.nPlcCount = nLineMode;

	pDoc->m_ConveyorThreadInfo[CV_1_PLC].m_PlcCountMsg.bModified = TRUE;

    pDoc->m_nConveyorEventCount[CV_1_PLC]++; SetEvent(pDoc->m_hEventSendConveyor[CV_1_PLC]);


	strLog.Format("냉동창고 입고,이동 고장 라인 모드 변경 [%d]", nLineMode);
	pDoc->m_pLog->Event(LOG_POS_CV, 9997, strLog);	
}
