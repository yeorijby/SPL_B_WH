// CvSto1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "CvSto1Dlg.h"
#include "EcsEnv.h"
#include "EcsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCvSto1Dlg dialog


CCvSto1Dlg::CCvSto1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCvSto1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCvSto1Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCvSto1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCvSto1Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCvSto1Dlg, CDialog)
	//{{AFX_MSG_MAP(CCvSto1Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCvSto1Dlg message handlers

#define	TRACK_INFO		m_pDoc->m_ConveyorTrackInfo

BOOL CCvSto1Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CJobItem* pJobItem;
	CString szTemp, strProdCode;

	for (int i=0; i<90; i++)
	{	
		int nTrackNum;

		if (i < 66)
			nTrackNum = i;
		else if (i < 82)
			nTrackNum = i+18;
		else
			nTrackNum = i+37;

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
				SET(IDC_BUTTON_CV1, szTemp);
				break;
			case 1:
				SET(IDC_BUTTON_CV2, szTemp);
				break;
			case 2:
				SET(IDC_BUTTON_CV3, szTemp);
				break;
			case 3:
				SET(IDC_BUTTON_CV4, szTemp);
				break;
			case 4:
				SET(IDC_BUTTON_CV5, szTemp);
				break;
			case 5:
				SET(IDC_BUTTON_CV6, szTemp);
				break;
			case 6:
				SET(IDC_BUTTON_CV7, szTemp);
				break;
			case 7:
				SET(IDC_BUTTON_CV8, szTemp);
				break;
			case 8:
				SET(IDC_BUTTON_CV9, szTemp);
				break;
			case 9:
				SET(IDC_BUTTON_CV10, szTemp);
				break;
			case 10:
				SET(IDC_BUTTON_CV11, szTemp);
				break;
			case 11:
				SET(IDC_BUTTON_CV12, szTemp);
				break;
			case 12:
				SET(IDC_BUTTON_CV13, szTemp);
				break;
			case 13:
				SET(IDC_BUTTON_CV14, szTemp);
				break;
			case 14:
				SET(IDC_BUTTON_CV15, szTemp);
				break;
			case 15:
				SET(IDC_BUTTON_CV16, szTemp);
				break;
			case 16:
				SET(IDC_BUTTON_CV17, szTemp);
				break;
			case 17:
				SET(IDC_BUTTON_CV18, szTemp);
				break;
			case 18:
				SET(IDC_BUTTON_CV19, szTemp);
				break;
			case 19:
				SET(IDC_BUTTON_CV20, szTemp);
				break;
			case 20:
				SET(IDC_BUTTON_CV21, szTemp);
				break;
			case 21:
				SET(IDC_BUTTON_CV22, szTemp);
				break;
			case 22:
				SET(IDC_BUTTON_CV23, szTemp);
				break;
			case 23:
				SET(IDC_BUTTON_CV24, szTemp);
				break;
			case 24:
				SET(IDC_BUTTON_CV25, szTemp);
				break;
			case 25:
				SET(IDC_BUTTON_CV26, szTemp);
				break;
			case 26:
				SET(IDC_BUTTON_CV27, szTemp);
				break;
			case 27:
				SET(IDC_BUTTON_CV28, szTemp);
				break;
			case 28:
				SET(IDC_BUTTON_CV29, szTemp);
				break;
			case 29:
				SET(IDC_BUTTON_CV30, szTemp);
				break;
			case 30:
				SET(IDC_BUTTON_CV31, szTemp);
				break;
			case 31:
				SET(IDC_BUTTON_CV32, szTemp);
				break;
			case 32:
				SET(IDC_BUTTON_CV33, szTemp);
				break;
			case 33:
				SET(IDC_BUTTON_CV34, szTemp);
				break;
			case 34:
				SET(IDC_BUTTON_CV35, szTemp);
				break;
			case 35:
				SET(IDC_BUTTON_CV36, szTemp);
				break;
			case 36:
				SET(IDC_BUTTON_CV37, szTemp);
				break;
			case 37:
				SET(IDC_BUTTON_CV38, szTemp);
				break;
			case 38:
				SET(IDC_BUTTON_CV39, szTemp);
				break;
			case 39:
				SET(IDC_BUTTON_CV40, szTemp);
				break;
			case 40:
				SET(IDC_BUTTON_CV41, szTemp);
				break;
			case 41:
				SET(IDC_BUTTON_CV42, szTemp);
				break;
			case 42:
				SET(IDC_BUTTON_CV43, szTemp);
				break;
			case 43:
				SET(IDC_BUTTON_CV44, szTemp);
				break;
			case 44:
				SET(IDC_BUTTON_CV45, szTemp);
				break;
			case 45:
				SET(IDC_BUTTON_CV46, szTemp);
				break;
			case 46:
				SET(IDC_BUTTON_CV47, szTemp);
				break;
			case 47:
				SET(IDC_BUTTON_CV48, szTemp);
				break;
			case 48:
				SET(IDC_BUTTON_CV49, szTemp);
				break;
			case 49:
				SET(IDC_BUTTON_CV50, szTemp);
				break;
			case 50:
				SET(IDC_BUTTON_CV51, szTemp);
				break;
			case 51:
				SET(IDC_BUTTON_CV52, szTemp);
				break;
			case 52:
				SET(IDC_BUTTON_CV53, szTemp);
				break;
			case 53:
				SET(IDC_BUTTON_CV54, szTemp);
				break;
			case 54:
				SET(IDC_BUTTON_CV55, szTemp);
				break;
			case 55:
				SET(IDC_BUTTON_CV56, szTemp);
				break;
			case 56:
				SET(IDC_BUTTON_CV57, szTemp);
				break;
			case 57:
				SET(IDC_BUTTON_CV58, szTemp);
				break;
			case 58:
				SET(IDC_BUTTON_CV59, szTemp);
				break;
			case 59:
				SET(IDC_BUTTON_CV60, szTemp);
				break;
			case 60:
				SET(IDC_BUTTON_CV61, szTemp);
				break;
			case 61:
				SET(IDC_BUTTON_CV62, szTemp);
				break;
			case 62:
				SET(IDC_BUTTON_CV63, szTemp);
				break;
			case 63:
				SET(IDC_BUTTON_CV64, szTemp);
				break;
			case 64:
				SET(IDC_BUTTON_CV65, szTemp);
				break;
			case 65:
				SET(IDC_BUTTON_CV66, szTemp);
				break;
			case 66:
				SET(IDC_BUTTON_CV85, szTemp);
				break;
			case 67:
				SET(IDC_BUTTON_CV86, szTemp);
				break;
			case 68:
				SET(IDC_BUTTON_CV87, szTemp);
				break;
			case 69:
				SET(IDC_BUTTON_CV88, szTemp);
				break;
			case 70:
				SET(IDC_BUTTON_CV89, szTemp);
				break;
			case 71:
				SET(IDC_BUTTON_CV90, szTemp);
				break;
			case 72:
				SET(IDC_BUTTON_CV91, szTemp);
				break;
			case 73:
				SET(IDC_BUTTON_CV92, szTemp);
				break;
			case 74:
				SET(IDC_BUTTON_CV93, szTemp);
				break;
			case 75:
				SET(IDC_BUTTON_CV94, szTemp);
				break;
			case 76:
				SET(IDC_BUTTON_CV95, szTemp);
				break;
			case 77:
				SET(IDC_BUTTON_CV96, szTemp);
				break;
			case 78:
				SET(IDC_BUTTON_CV97, szTemp);
				break;
			case 79:
				SET(IDC_BUTTON_CV98, szTemp);
				break;
			case 80:
				SET(IDC_BUTTON_CV99, szTemp);
				break;
			case 81:
				SET(IDC_BUTTON_CV100, szTemp);
				break;
			case 82:
				SET(IDC_BUTTON_CV119, szTemp);
				break;
			case 83:
				SET(IDC_BUTTON_CV120, szTemp);
				break;
			case 84:
				SET(IDC_BUTTON_CV121, szTemp);
				break;
			case 85:
				SET(IDC_BUTTON_CV122, szTemp);
				break;
			case 86:
				SET(IDC_BUTTON_CV123, szTemp);
				break;
			case 87:
				SET(IDC_BUTTON_CV124, szTemp);
				break;
			case 88:
				SET(IDC_BUTTON_CV125, szTemp);
				break;
			case 89:
				SET(IDC_BUTTON_CV126, szTemp);
				break;
			}
		}
	}
		
	return TRUE;  
}
