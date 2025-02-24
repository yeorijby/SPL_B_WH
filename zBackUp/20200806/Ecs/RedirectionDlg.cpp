// RedirectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "RedirectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRedirectionDlg dialog


CRedirectionDlg::CRedirectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRedirectionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRedirectionDlg)
	m_strLocation = _T("");
	//}}AFX_DATA_INIT
}


void CRedirectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRedirectionDlg)
	DDX_Text(pDX, IDC_EDIT_LOCATION, m_strLocation);
	DDV_MaxChars(pDX, m_strLocation, 7);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRedirectionDlg, CDialog)
	//{{AFX_MSG_MAP(CRedirectionDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRedirectionDlg message handlers
