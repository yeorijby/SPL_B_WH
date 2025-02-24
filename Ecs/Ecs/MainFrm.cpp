// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Ecs.h"

#include "MainFrm.h"
#include "EcsView.h"

#include <EcsEnv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	ID_INDICATOR_MODE,
	ID_INDICATOR_DATE,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
	int aaa;
	aaa = 0;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

//	m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT);
	
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

//	m_wndStatusBar.SetText(4, " Manual", TRUE);
//	m_wndStatusBar.SetText(5, " 97/04/04 16:35:00", TRUE);

//	m_wndToolBar.SetButtonInfo(0, ID_SYSTEM_CONFIG, TBBS_BUTTON, 1);
//	m_wndToolBar.SetButtonInfo(6, 2, TBBS_BUTTON, 1);
//	m_wndToolBar.SetButtonInfo(7, 2, TBBS_BUTTON, 1);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::DisplayMessage(CString strMsg)
{
	m_wndStatusBar.SetWindowText(strMsg);
}

void CMainFrame::UpdateCommHost(UINT unID, char Status)
{
	m_wndToolBar.SetButtonInfo(8 + unID - ID_COMM_HOST_CLIENT, unID, TBBS_BUTTON, GetIndex(Status));
}

void CMainFrame::UpdateCommHostCl(char Status)
{
	m_wndToolBar.SetButtonInfo(8, ID_COMM_HOST_CLIENT, TBBS_BUTTON, GetIndex(Status));
}

void CMainFrame::UpdateCommHostSv(char Status)
{
	m_wndToolBar.SetButtonInfo(9, ID_COMM_HOST_SERVER, TBBS_BUTTON, GetIndex(Status));
}

void CMainFrame::UpdateCommCv(UINT unID, char Status) 
{
	m_wndToolBar.SetButtonInfo(11 + unID - ID_COMM_CV_1, unID, TBBS_BUTTON, GetIndex(Status));
}

void CMainFrame::UpdateCommSc(UINT unID, char Status) 
{
	m_wndToolBar.SetButtonInfo(21 + unID - ID_COMM_SC_1, unID, TBBS_BUTTON, GetIndex(Status));
}

void CMainFrame::UpdateCommRgv(UINT unID, char Status) 
{
	m_wndToolBar.SetButtonInfo(28 + unID - ID_COMM_RGV_1, unID, TBBS_BUTTON, GetIndex(Status));
}

void CMainFrame::UpdateCommEcsCl(char Status)
{
	m_wndToolBar.SetButtonInfo(31, ID_COMM_NEW_ECS, TBBS_BUTTON, GetIndex(Status));
}

int CMainFrame::GetIndex(char Status) 
{
	switch (Status)
	{
	case	COMM_STA_SEND:
		return 8;
	case	COMM_STA_RECEIVE:
		return 9;
	case	COMM_STA_STOP:
		return 10;
	default:
		return 10;
	}
}

void CMainFrame::SetViewHandle(HWND hwnd)
{
	m_hwndView = hwnd;
}
