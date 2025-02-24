// ColorViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "ColorViewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorViewDlg dialog


CColorViewDlg::CColorViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorViewDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CColorViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorViewDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CColorViewDlg, CDialog)
	//{{AFX_MSG_MAP(CColorViewDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorViewDlg message handlers
