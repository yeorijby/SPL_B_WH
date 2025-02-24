// Ecs.h : main header file for the ECS application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#define WM_USER_CV_IN_PROGRESS		(WM_USER + 1)
#define WM_USER_SC_IN_PROGRESS		(WM_USER + 2)
#define WM_USER_CV_READ_DONE		(WM_USER + 3)
#define WM_USER_SC_READ_DONE		(WM_USER + 4)
#define WM_USER_CV_NOTIFY			(WM_USER + 5)
#define WM_USER_SC_NOTIFY			(WM_USER + 6)
#define WM_USER_RGV_NOTIFY			(WM_USER + 7)
#define WM_USER_BCR_NOTIFY			(WM_USER + 8)
#define WM_USER_HOST_NOTIFY			(WM_USER + 9)
#define WM_USER_JOB_NOTIFY			(WM_USER + 10)
#define WM_USER_ECS_NOTIFY			(WM_USER + 11)

/////////////////////////////////////////////////////////////////////////////
// CEcsApp:
// See Ecs.cpp for the implementation of this class
//

class CEcsApp : public CWinApp
{
public:
	CEcsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEcsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEcsApp)
	afx_msg void OnAppAbout();
	afx_msg void OnHelpIndex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
