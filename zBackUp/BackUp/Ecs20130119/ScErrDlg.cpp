// ScErrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "ScErrDlg.h"
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScErrDlg dialog


CScErrDlg::CScErrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScErrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScErrDlg)
	m_date = _T("");
	//}}AFX_DATA_INIT
}


void CScErrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScErrDlg)
	DDX_Control(pDX, IDC_EDIT1, m_Editdate);
	DDX_Text(pDX, IDC_EDIT1, m_date);
	DDV_MaxChars(pDX, m_date, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScErrDlg, CDialog)
	//{{AFX_MSG_MAP(CScErrDlg)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_BN_CLICKED(ID_CLEAR2, OnClear2)
	ON_BN_CLICKED(ID_PRT, OnPrt)
	ON_BN_CLICKED(IDC_SC1, OnSc1)
	ON_BN_CLICKED(IDC_SC2, OnSc2)
	ON_BN_CLICKED(IDC_SC3, OnSc3)
	ON_BN_CLICKED(IDC_SC4, OnSc4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScErrDlg message handlers

BOOL CScErrDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//CVETRODoc* pDoc = (CVETRODoc*) GetParentFrame()->GetActiveDocument();
	CListBox*  pList = (CListBox*) GetDlgItem(IDC_LIST1);
	CButton*   pChk1 = (CButton*) GetDlgItem(IDC_SC1);
	
	char    Buff[9], Time[7];
	 		
	m_Editdate.LimitText(8);

    _strdate(Buff);
    sprintf(Time, "%c%c%c%c%c%c", Buff[6], Buff[7], Buff[0], Buff[1], Buff[3], Buff[4]);
    _strtime(Buff);
    sprintf(Time+6, "%c%c", Buff[0], Buff[1]);
    SetDlgItemText(IDC_EDIT1, Time);

	pChk1->SetCheck(1);
	
	pList->ResetContent();
	DispScErr(pList, Time, 10);
		
	return TRUE;
}

void CScErrDlg::OnChangeEdit1() 
{
	int  Temp;
	CString  tmpTime;

	Temp = (int)GetDlgItemText(IDC_EDIT1, tmpTime);
	            
	memcpy(chTime, tmpTime, 8);
	chTime[8] = NULL;
	
}

void CScErrDlg::OnClear2() 
{
	CButton*   pChk1 = (CButton*) GetDlgItem(IDC_SC1);
	CButton*   pChk2 = (CButton*) GetDlgItem(IDC_SC2);
	CButton*   pChk3 = (CButton*) GetDlgItem(IDC_SC3);
	CButton*   pChk4 = (CButton*) GetDlgItem(IDC_SC4);

	char SysBuff[30];
	int  i;

	memset(SysBuff, 0x00, 30);

	if ((i = pChk1->GetCheck()) == 1)
		strcpy(SysBuff, "DEL ..\\STC\\ERR_S10");
	if ((i = pChk2->GetCheck()) == 1)
		strcpy(SysBuff, "DEL ..\\STC\\ERR_S11");
	if ((i = pChk3->GetCheck()) == 1)
		strcpy(SysBuff, "DEL ..\\STC\\ERR_S12");
	if ((i = pChk4->GetCheck()) == 1)
		strcpy(SysBuff, "DEL ..\\STC\\ERR_S13");
	
	system(SysBuff);
	
}

void CScErrDlg::OnOK() 
{
	CDialog::OnOK();
}

void CScErrDlg::OnPrt() 
{
	CPrintDialog PrintDlg(TRUE);

	if (PrintDlg.DoModal() != IDOK)
		return;

	HDC hdc = PrintDlg.CreatePrinterDC();
	if (hdc == NULL)
	{
		AfxMessageBox("Can't print.. because printer device is not working correctly");
		return;
	}

	CDC* pDC = CDC::FromHandle(hdc);

	DOCINFO lpdi;
	lpdi.cbSize = sizeof(DOCINFO);
    lpdi.lpszDocName = "EcsErr";
    lpdi.lpszOutput = NULL;

	pDC->StartDoc(&lpdi);
	pDC->StartPage();

    CString strTemp;
	char Buff[1024];
	strcpy(Buff, "S/C Error Code Reporting........");
	pDC->TextOut(10, 100, Buff, strlen(Buff));

	CListBox* pListCtrl = (CListBox *)GetDlgItem(IDC_LIST1);
	int nCount = pListCtrl->GetCount();

	for (int i = 0, nLine, nPageNum = 1; i < nCount; i++)
	{
		if (i % 62 == 0)
		{
			nLine = 0;
			if (nPageNum != 1)
			{
				pDC->EndPage();
				pDC->StartPage();
			}
			PrintTitle(pDC, nPageNum);
			nPageNum++;
		}

		char szBuff[200];
		
		pListCtrl->GetText(i, szBuff);

		pDC->TextOut(10, 500 + nLine++ * 100, szBuff, strlen(szBuff));
	}

	pDC->EndPage();
	pDC->EndDoc();
	DeleteDC(hdc);

	AfxMessageBox("S/C Error Report Print OK..");
	
}

void CScErrDlg::OnSc1() 
{
	CListBox*  pList = (CListBox*) GetDlgItem(IDC_LIST1);

	DispScErr(pList, chTime, 10);
	
}

void CScErrDlg::OnSc2() 
{
	CListBox*  pList = (CListBox*) GetDlgItem(IDC_LIST1);

	DispScErr(pList, chTime, 11);
	
}

void CScErrDlg::OnSc3() 
{
	CListBox*  pList = (CListBox*) GetDlgItem(IDC_LIST1);

	DispScErr(pList, chTime, 12);
	
}

void CScErrDlg::OnSc4() 
{
	CListBox*  pList = (CListBox*) GetDlgItem(IDC_LIST1);

	DispScErr(pList, chTime, 13);
	
}

void CScErrDlg::PrintTitle(CDC* pDC, int nPageNum)
{
	char Buff[1024];

	sprintf(Buff, "a1      a2        a3    < Page %d >", nPageNum);
	pDC->TextOut(10, 300, Buff, strlen(Buff));
	sprintf(Buff, "======  ========  ====          >>>");
	pDC->TextOut(10, 400, Buff, strlen(Buff));
}

void CScErrDlg::DispScErr(CListBox *pList, char *Time, int ScNo)
{
    char    szBuff1[104], szBuff[80], FileName[20], szText[30];
    int     i, LineCnt = 0, log;
	CString szTemp1, szTemp2;

	pList->ResetContent();
    sprintf(FileName, "..\\STC\\ERR_S%d", ScNo);
        
    szTemp1.Format("%.8s", Time);
    log = open(FileName, O_RDONLY);
    if (log <= -1) {
		pList->AddString("File not found !!");
        return;
    }

    if (lseek(log, 0L, SEEK_END) < 0) return;

    for (i=0; LineCnt<1000; i++) {
        memset(szBuff, 0x20, sizeof(szBuff));
        memset(szBuff1, 0x20, sizeof(szBuff1));
        if (i == 0) {
            if (lseek(log, -80L, SEEK_CUR) < 0) break;
        } else if (lseek(log, -160L, SEEK_CUR) <0) break;
        if (ReadLogInfo(log, szBuff)) {
			szTemp2.Format("%.8s", szBuff);
            memcpy(szBuff1, szBuff, 6);
            memcpy(szBuff1+8, szBuff+6, 8);
            memcpy(szBuff1+18, szBuff+14, 4);
			memcpy(szBuff1+22, szBuff+18, 5);
            if (szTemp1 < szTemp2) continue;
            LineCnt++;
			pList->AddString(szBuff1);
            
        } else break;
    }
    if (LineCnt == 0) {
        strcpy(szText, " No Logging Data..");
	    pList->AddString(szText);
    }
    close(log);
}

int CScErrDlg::ReadLogInfo(int log, char *pBuff)
{
	int   rd;

	rd = read(log, pBuff, 80);
	if (rd != -1) return(TRUE);
    return(FALSE);
}


