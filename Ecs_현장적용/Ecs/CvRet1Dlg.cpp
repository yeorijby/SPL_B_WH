// CvRet1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "CvRet1Dlg.h"
#include "EcsEnv.h"
#include "EcsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCvRet1Dlg dialog


CCvRet1Dlg::CCvRet1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCvRet1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCvRet1Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCvRet1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCvRet1Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCvRet1Dlg, CDialog)
	//{{AFX_MSG_MAP(CCvRet1Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCvRet1Dlg message handlers

#define	TRACK_INFO		m_pDoc->m_ConveyorTrackInfo

BOOL CCvRet1Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CJobItem* pJobItem;
	CString szTemp, strProdCode;

	for (int i=0; i<50; i++)
	{
		int nTrackNum;

		if (i < 38)
			nTrackNum = i+200; // ~ 238
		else if (i < 40)
			nTrackNum = i+209; // 248, 249
		else if (i < 44)
			nTrackNum = i+238; // 279, 280, 281, 282
		else if (i < 47)
			nTrackNum = i+37;  // 82, 83, 84
		else
			nTrackNum = i+68;  // 116, 117, 118

		if (TRACK_INFO[nTrackNum].m_nLuggNum != 0)
		{
			pJobItem = m_pDoc->m_pJob->Find(TRACK_INFO[nTrackNum].m_nLuggNum);

			if (pJobItem != NULL)
				strProdCode = pJobItem->m_strProductID;
			else
				strProdCode = " ";
			szTemp.Format("%04d%c%s", TRACK_INFO[nTrackNum].m_nLuggNum, ASCII_CR, strProdCode);

			switch (i)
			{
			case 0:
				SET(IDC_BUTTON_CV201, szTemp);
				break;
			case 1:
				SET(IDC_BUTTON_CV202, szTemp);
				break;
			case 2:
				SET(IDC_BUTTON_CV203, szTemp);
				break;
			case 3:
				SET(IDC_BUTTON_CV204, szTemp);
				break;
			case 4:
				SET(IDC_BUTTON_CV205, szTemp);
				break;
			case 5:
				SET(IDC_BUTTON_CV206, szTemp);
				break;
			case 6:
				SET(IDC_BUTTON_CV207, szTemp);
				break;
			case 7:
				SET(IDC_BUTTON_CV208, szTemp);
				break;
			case 8:
				SET(IDC_BUTTON_CV209, szTemp);
				break;
			case 9:
				SET(IDC_BUTTON_CV210, szTemp);
				break;
			case 10:
				SET(IDC_BUTTON_CV211, szTemp);
				break;
			case 11:
				SET(IDC_BUTTON_CV212, szTemp);
				break;
			case 12:
				SET(IDC_BUTTON_CV213, szTemp);
				break;
			case 13:
				SET(IDC_BUTTON_CV214, szTemp);
				break;
			case 14:
				SET(IDC_BUTTON_CV215, szTemp);
				break;
			case 15:
				SET(IDC_BUTTON_CV216, szTemp);
				break;
			case 16:
				SET(IDC_BUTTON_CV217, szTemp);
				break;
			case 17:
				SET(IDC_BUTTON_CV218, szTemp);
				break;
			case 18:
				SET(IDC_BUTTON_CV219, szTemp);
				break;
			case 19:
				SET(IDC_BUTTON_CV220, szTemp);
				break;
			case 20:
				SET(IDC_BUTTON_CV221, szTemp);
				break;
			case 21:
				SET(IDC_BUTTON_CV222, szTemp);
				break;
			case 22:
				SET(IDC_BUTTON_CV223, szTemp);
				break;
			case 23:
				SET(IDC_BUTTON_CV224, szTemp);
				break;
			case 24:
				SET(IDC_BUTTON_CV225, szTemp);
				break;
			case 25:
				SET(IDC_BUTTON_CV226, szTemp);
				break;
			case 26:
				SET(IDC_BUTTON_CV227, szTemp);
				break;
			case 27:
				SET(IDC_BUTTON_CV228, szTemp);
				break;
			case 28:
				SET(IDC_BUTTON_CV229, szTemp);
				break;
			case 29:
				SET(IDC_BUTTON_CV230, szTemp);
				break;
			case 30:
				SET(IDC_BUTTON_CV231, szTemp);
				break;
			case 31:
				SET(IDC_BUTTON_CV232, szTemp);
				break;
			case 32:
				SET(IDC_BUTTON_CV233, szTemp);
				break;
			case 33:
				SET(IDC_BUTTON_CV234, szTemp);
				break;
			case 34:
				SET(IDC_BUTTON_CV235, szTemp);
				break;
			case 35:
				SET(IDC_BUTTON_CV236, szTemp);
				break;
			case 36:
				SET(IDC_BUTTON_CV237, szTemp);
				break;
			case 37:
				SET(IDC_BUTTON_CV238, szTemp);
				break;
			case 38:
				SET(IDC_BUTTON_CV248, szTemp);
				break;
			case 39:
				SET(IDC_BUTTON_CV249, szTemp);
				break;
			case 40:
				SET(IDC_BUTTON_CV279, szTemp);
				break;
			case 41:
				SET(IDC_BUTTON_CV280, szTemp);
				break;
			case 42:
				SET(IDC_BUTTON_CV281, szTemp);
				break;
			case 43:
				SET(IDC_BUTTON_CV282, szTemp);
				break;
			case 44:
				SET(IDC_BUTTON_CV82, szTemp);
				break;
			case 45:
				SET(IDC_BUTTON_CV83, szTemp);
				break;
			case 46:
				SET(IDC_BUTTON_CV84, szTemp);
				break;
			case 47:
				SET(IDC_BUTTON_CV116, szTemp);
				break;
			case 48:
				SET(IDC_BUTTON_CV117, szTemp);
				break;
			case 49:
				SET(IDC_BUTTON_CV118, szTemp);
				break;
			}
		}
	}
	
	return TRUE;
}
