// LogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "Log.h"
#include "LogDlg.h"
#include <EcsEnv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogDlg dialog

CLogDlg::CLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogDlg::IDD, pParent)
{
	m_bCheck = FALSE;
	m_nType = LOG_TYPE_ALL;
	m_nPos = LOG_POS_ALL;
	m_pImageList = NULL;

	//{{AFX_DATA_INIT(CLogDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CLogDlg::~CLogDlg()
{
	if (m_pImageList != NULL) delete m_pImageList;
}

void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogDlg, CDialog)
	//{{AFX_MSG_MAP(CLogDlg)
	ON_BN_CLICKED(IDC_CHECK_LUGG_ID, OnCheckLuggId)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_FILE, OnButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_SAVEAS, OnButtonSaveas)
	ON_CBN_SELCHANGE(IDC_COMBO_POSITION, OnSelchangeComboPosition)
	ON_NOTIFY(HDN_ITEMCLICKA, 0, OnHeaderClicked) 
	ON_NOTIFY(HDN_ITEMCLICKW, 0, OnHeaderClicked)
	ON_WM_DRAWITEM()
	ON_NOTIFY(NM_CLICK, IDC_TAB_LOG, OnClickTabLog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogDlg message handlers

BOOL CLogDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CTime theTime = CTime::GetCurrentTime();
	m_nDay = theTime.GetDay();

	CString strTemp;
	strTemp.Format("%.2d/%.2d", theTime.GetMonth(), m_nDay);
	GetDlgItem(IDC_EDIT_DATE)->SetWindowText(strTemp);
	
	m_nFrom = theTime.GetHour();
	if (m_nFrom == 0) m_nFrom = 1;
	m_nTo = m_nFrom + 1;

	CSpinButtonCtrl* pSpinButtonCtrlFrom = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_FROM);
	pSpinButtonCtrlFrom->SetRange(23, 0);
	pSpinButtonCtrlFrom->SetPos(m_nFrom);
	pSpinButtonCtrlFrom->SetBuddy(GetDlgItem(IDC_EDIT_FROM));
	CSpinButtonCtrl* pSpinButtonCtrlTo = (CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_TO);
	pSpinButtonCtrlTo->SetRange(24, 1);
	pSpinButtonCtrlTo->SetPos(m_nTo);
	pSpinButtonCtrlTo->SetBuddy(GetDlgItem(IDC_EDIT_TO));

	SetRange();

	m_pImageList = new CImageList();		
	ASSERT(m_pImageList != NULL);    // no serious allocation failure checking

	CEcsApp* pApp = (CEcsApp *)AfxGetApp();
	m_pImageList->Create(16, 16, TRUE/*bMask*/,	1/*nInitial*/, 1/*nGrow*/);
	m_pImageList->Add(pApp->LoadIcon(IDI_ICON16));
//	m_pImageList->Add(pApp->LoadIcon(IDI_ICON_LOG));

	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_LOG);

	pListCtrl->SetImageList(m_pImageList, LVSIL_SMALL);

	LV_COLUMN		lvcolumn;

	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvcolumn.fmt = LVCFMT_LEFT;
	lvcolumn.pszText = "시간";
	lvcolumn.iSubItem = 0;
	lvcolumn.cx = 85;

	pListCtrl->InsertColumn(0, &lvcolumn);

	lvcolumn.pszText = "작업번호";
	lvcolumn.cx = 80; 
	pListCtrl->InsertColumn(1, &lvcolumn); 

	lvcolumn.pszText = "발생위치";
	lvcolumn.cx = 80; 
	pListCtrl->InsertColumn(2, &lvcolumn); 

	lvcolumn.pszText = "내용";
	lvcolumn.cx = 500; 
	pListCtrl->InsertColumn(3, &lvcolumn); 

	CTabCtrl* pTabCtrl = (CTabCtrl *)GetDlgItem(IDC_TAB_LOG);

	TC_ITEM TabCtrlItem;

	TabCtrlItem.mask = TCIF_TEXT;
    TabCtrlItem.pszText = "전체";
	pTabCtrl->InsertItem(0, &TabCtrlItem);
    TabCtrlItem.pszText = "작업";
	pTabCtrl->InsertItem(1, &TabCtrlItem);
    TabCtrlItem.pszText = "이벤트";
	pTabCtrl->InsertItem(2, &TabCtrlItem);
    TabCtrlItem.pszText = "에러";
	pTabCtrl->InsertItem(3, &TabCtrlItem);
    TabCtrlItem.pszText = "디버그";
	pTabCtrl->InsertItem(4, &TabCtrlItem);

	CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_POSITION);

	CLogEvent LogEvent;
	for (int i=0; i < LOG_POS_CNT; i++)
	{
		pComboBox->InsertString(i, LogEvent.GetPosition(i));
	}
	pComboBox->SetCurSel(0);

	Loading();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLogDlg::SetRange() 
{
	CString strTemp;
	strTemp.Format("%.2d", m_nFrom);
	GetDlgItem(IDC_EDIT_FROM)->SetWindowText(strTemp);
	strTemp.Format("%.2d", m_nTo);
	GetDlgItem(IDC_EDIT_TO)->SetWindowText(strTemp);
}

BOOL CLogDlg::GetRange() 
{
	CString strMsg = "Range is not correct!, check the range items";
	CString strTemp;
	GetDlgItem(IDC_EDIT_FROM)->GetWindowText(strTemp);
	if ((m_nFrom = atoi(strTemp)) < 0 || m_nFrom > 23)
	{
		MessageBox(strMsg);
		return FALSE;
	}
	GetDlgItem(IDC_EDIT_TO)->GetWindowText(strTemp);
	if ((m_nTo = atoi(strTemp)) < 1 || m_nTo > 24)
	{
		MessageBox(strMsg);
		return FALSE;
	}

	if (m_nFrom >= m_nTo)
	{
		MessageBox(strMsg);
		return FALSE;
	}
	return TRUE;
}

void CLogDlg::Loading() 
{
	if (!GetRange()) return;

	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_LOG);
	CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_POSITION);
	m_nPos = pComboBox->GetCurSel();

	if (m_bCheck)
		m_pLog->Load(pListCtrl, m_nDay, m_nType, m_nPos, m_nLuggNum, m_nFrom, m_nTo);
	else
		m_pLog->Load(pListCtrl, m_nDay, m_nType, m_nPos, 0, m_nFrom, m_nTo);
}

void CLogDlg::OnClickLogTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTabCtrl* pTabCtrl = (CTabCtrl *)GetDlgItem(IDC_TAB_LOG);
	m_nType = pTabCtrl->GetCurSel(); 

	Loading();

	*pResult = 0;
}

void CLogDlg::OnCheckLuggId() 
{
	if (m_bCheck) 
		m_bCheck = FALSE;
	else
		m_bCheck = TRUE;

	GetDlgItem( IDC_BUTTON_SEARCH )->EnableWindow( m_bCheck );
	GetDlgItem( IDC_EDIT_LUGG_ID )->EnableWindow( m_bCheck );
}

void CLogDlg::OnButtonSearch() 
{
	CString strLuggNum;
	GetDlgItem(IDC_EDIT_LUGG_ID)->GetWindowText(strLuggNum);
	m_nLuggNum = atoi(strLuggNum);

	Loading();
}

void CLogDlg::OnButtonFile() 
{
/*	char	szOldDir[128];
	GetCurrentDirectory(sizeof(szOldDir), szOldDir);
	SetCurrentDirectory(m_pLog->m_strLogDir);

	CFileDialog FileDlg(TRUE, NULL, "*.elg", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		" ECS Log Files (*.elg) | *.elg ||");
*/
	char	szOldDir[128];
	char	szNewDir[512];

	GetCurrentDirectory(sizeof(szOldDir), szOldDir);
	SetCurrentDirectory(m_pLog->m_strLogDir);
	GetCurrentDirectory(sizeof(szNewDir), szNewDir);

	CFileDialog FileDlg(TRUE, NULL, "*.elg", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		" ECS Log Files (*.elg) | *.elg ||");

	FileDlg.m_ofn.lpstrInitialDir = szNewDir;
	FileDlg.m_ofn.lpstrTitle = "ECS 작업기록 파일";

	if (FileDlg.DoModal() == IDOK) 
	{
		CString strFileTitle = FileDlg.GetFileTitle();
		m_nDay = atoi(strFileTitle.Mid(4, 2));
		CTime theTime = CTime::GetCurrentTime();
		CString strTemp;
		int nMonth = theTime.GetMonth();
		if (m_nDay > theTime.GetDay())
		{
			if (nMonth == 1)
				strTemp.Format("%.2d/%.2d", 12, m_nDay);
			else
				strTemp.Format("%.2d/%.2d", nMonth - 1, m_nDay);
		}
		else
		{
			strTemp.Format("%.2d/%.2d", theTime.GetMonth(), m_nDay);
		}

		GetDlgItem(IDC_EDIT_DATE)->SetWindowText(strTemp);
		Loading();
	}
	SetCurrentDirectory(szOldDir);
}

void CLogDlg::OnButtonPrint() 
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
    lpdi.lpszDocName = "EcsLog";
    lpdi.lpszOutput = NULL;

	pDC->StartDoc(&lpdi);
	pDC->StartPage();

    CString strTemp;
	char Buff[1024];
	GET(IDC_EDIT_DATE, strTemp);
	sprintf(Buff, "Logging file dated %s........", strTemp);
	pDC->TextOut(10, 100, Buff, strlen(Buff));

	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_LOG);

	for (int i = 0, nLine, nPageNum = 1; i < pListCtrl->GetItemCount(); i++)
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

		sprintf(Buff, "%s %-4s %-5s %s", 
			pListCtrl->GetItemText(i, 0), 
			pListCtrl->GetItemText(i, 1), 
			pListCtrl->GetItemText(i, 2), 
			pListCtrl->GetItemText(i, 3));
		pDC->TextOut(10, 500 + nLine++ * 100, Buff, strlen(Buff));
	}

	pDC->EndPage();
	pDC->EndDoc();
	DeleteDC(hdc);

	AfxMessageBox("Log print OK..");
}

void CLogDlg::PrintTitle(CDC* pDC, int nPageNum)
{
	char Buff[1024];

	sprintf(Buff, "Time     Lugg Pos   Content........................................< Page %d >", nPageNum);
	pDC->TextOut(10, 300, Buff, strlen(Buff));
	sprintf(Buff, "======== ==== ===== =======================================================>>>");
	pDC->TextOut(10, 400, Buff, strlen(Buff));
}

void CLogDlg::OnButtonRefresh() 
{
	Loading();
}

void CLogDlg::OnButtonSaveas() 
{
	char	szOldDir[128];
	GetCurrentDirectory(sizeof(szOldDir), szOldDir);
	SetCurrentDirectory(m_pLog->m_strLogDir);

	CFileDialog FileDlg(FALSE, NULL, "*.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		" ECS Log Files - Text Format (*.txt) | *.txt ||");

	if (FileDlg.DoModal() != IDOK)
		return;

	CString strFile = FileDlg.GetPathName();
	CString strTemp;

	CFile* pFile;
	TRY
	{
		const char* pFileName = LPCTSTR(strFile);
		pFile = new CFile(pFileName, CFile::modeCreate | CFile::modeWrite);
	}
	CATCH( CFileException, e )
	{
		strTemp.Format("CLogDlg::OnButtonSaveas.. File could not be opened e->m_cause=[%d]", e->m_cause);
		AfxMessageBox(strTemp);
		return;
	}
	END_CATCH

	char Buff[1024];

	GET(IDC_EDIT_DATE, strTemp);
	sprintf(Buff, "Logging file dated %s........\r\n\r\n", strTemp);
	pFile->Write(Buff, strlen(Buff));
	sprintf(Buff, "Time     Lugg Pos   Content..\r\n");
	pFile->Write(Buff, strlen(Buff));
	sprintf(Buff, "======== ==== ===== =========>>>\r\n");
	pFile->Write(Buff, strlen(Buff));

	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_LOG);

	for (int i = 0; i < pListCtrl->GetItemCount(); i++)
	{
		sprintf(Buff, "%s %-4s %-5s %s\r\n", 
			pListCtrl->GetItemText(i, 0), 
			pListCtrl->GetItemText(i, 1), 
			pListCtrl->GetItemText(i, 2), 
			pListCtrl->GetItemText(i, 3));
		pFile->Write(Buff, strlen(Buff));
	}
	delete pFile;
	SetCurrentDirectory(szOldDir);
}

void CLogDlg::OnSelchangeComboPosition() 
{
	Loading();
}

// offsets for first and other columns
#define OFFSET_FIRST	2
#define OFFSET_OTHER	6

void CLogDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_LOG);
	
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rcItem(lpDrawItemStruct->rcItem);
	UINT uiFlags = ILD_TRANSPARENT;
	CImageList* pImageList;
	int nItem = lpDrawItemStruct->itemID;
	BOOL bFocus = (GetFocus() == this);
	COLORREF clrTextSave, clrBkSave;
	COLORREF clrImage = ::GetSysColor(COLOR_WINDOW);
	static _TCHAR szBuff[MAX_PATH];
	LPCTSTR pszText;

// get item data

	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvi.iItem = nItem;
	lvi.iSubItem = 0;
	lvi.pszText = szBuff;
	lvi.cchTextMax = sizeof(szBuff);
	lvi.stateMask = 0xFFFF;		// get all state flags
	pListCtrl->GetItem(&lvi);

	BOOL bSelected = bFocus || lvi.state & LVIS_SELECTED;

// set colors if item is selected

	CRect rcAllLabels;
	pListCtrl->GetItemRect(nItem, rcAllLabels, LVIR_BOUNDS);

	CRect rcLabel;
	pListCtrl->GetItemRect(nItem, rcLabel, LVIR_LABEL);

	rcAllLabels.left = rcLabel.left;
	if (rcAllLabels.right < 800)
		rcAllLabels.right = 800;

	if (bSelected)
	{
		clrTextSave = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		clrBkSave = pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));

		pDC->FillRect(rcAllLabels, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
	}
	else
		pDC->FillRect(rcAllLabels, &CBrush(::GetSysColor(COLOR_WINDOW)));

// set color and mask for the icon

	if (lvi.state & LVIS_CUT)
	{
		clrImage = ::GetSysColor(COLOR_WINDOW);
		uiFlags |= ILD_BLEND50;
	}
	else if (bSelected)
	{
		clrImage = ::GetSysColor(COLOR_HIGHLIGHT);
		uiFlags |= ILD_BLEND50;
	}

// draw state icon

/*	UINT nStateImageMask = lvi.state & LVIS_STATEIMAGEMASK;
	if (nStateImageMask)
	{
		int nImage = (nStateImageMask>>12) - 1;
		pImageList = pListCtrl->GetImageList(LVSIL_STATE);
		if (pImageList)
		{
			pImageList->Draw(pDC, nImage,
				CPoint(rcItem.left, rcItem.top), ILD_TRANSPARENT);
		}
	}
*/
// draw normal and overlay icon

	CRect rcIcon;
	pListCtrl->GetItemRect(nItem, rcIcon, LVIR_ICON);

	pImageList = pListCtrl->GetImageList(LVSIL_SMALL);
	if (pImageList)
	{
		UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
		if (rcItem.left<rcItem.right-1)
		{
			ImageList_DrawEx(pImageList->m_hImageList, lvi.iImage,
					pDC->m_hDC,rcIcon.left,rcIcon.top, 16, 16,
					::GetSysColor(COLOR_WINDOW), clrImage, uiFlags | nOvlImageMask);
		}
	}

// draw item label

	pListCtrl->GetItemRect(nItem, rcItem, LVIR_LABEL);
//	rcItem.right -= 16;

	pszText = MakeShortString(pDC, szBuff,
				rcItem.right-rcItem.left, 2*OFFSET_FIRST);

	rcLabel = rcItem;
	rcLabel.left += OFFSET_FIRST;
	rcLabel.right -= OFFSET_FIRST;

	pDC->DrawText(pszText,-1,rcLabel,DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);

// draw labels for extra columns

	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH;
				   
	for(int nColumn = 1; pListCtrl->GetColumn(nColumn, &lvc); nColumn++)
	{
		rcItem.left = rcItem.right;
		rcItem.right += lvc.cx;

		int nRetLen = pListCtrl->GetItemText(nItem, nColumn,
						szBuff, sizeof(szBuff));
		if (nRetLen == 0)
			continue;

		pszText = MakeShortString(pDC, szBuff,
			rcItem.right - rcItem.left, 2*OFFSET_OTHER);

		UINT nJustify = DT_LEFT;

		if(pszText == szBuff)
		{
			switch(lvc.fmt & LVCFMT_JUSTIFYMASK)
			{
			case LVCFMT_RIGHT:
				nJustify = DT_RIGHT;
				break;
			case LVCFMT_CENTER:
				nJustify = DT_CENTER;
				break;
			default:
				break;
			}
		}

		rcLabel = rcItem;
		rcLabel.left += OFFSET_OTHER;
		rcLabel.right -= OFFSET_OTHER;

		pDC->DrawText(pszText, -1, rcLabel,
			nJustify | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
	}

// draw focus rectangle if item has focus

	if (lvi.state & LVIS_FOCUSED && bFocus)
		pDC->DrawFocusRect(rcAllLabels);

// set original colors if item was selected

	if (bSelected)
	{
        pDC->SetTextColor(clrTextSave);
		pDC->SetBkColor(clrBkSave);
	}
	
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

LPCTSTR CLogDlg::MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset)
{
	static const _TCHAR szThreeDots[] = _T("...");

	int nStringLen = lstrlen(lpszLong);

	if(nStringLen == 0 ||
		(pDC->GetTextExtent(lpszLong, nStringLen).cx + nOffset) <= nColumnLen)
	{
		return(lpszLong);
	}

	static _TCHAR szShort[MAX_PATH];

	lstrcpy(szShort,lpszLong);
	int nAddLen = pDC->GetTextExtent(szThreeDots,sizeof(szThreeDots)).cx;

	for(int i = nStringLen-1; i > 0; i--)
	{
		szShort[i] = 0;
		if((pDC->GetTextExtent(szShort, i).cx + nOffset + nAddLen)
			<= nColumnLen)
		{
			break;
		}
	}

	lstrcat(szShort, szThreeDots);
	return(szShort);
}

void CLogDlg::OnOK() 
{
	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_LOG);
	pListCtrl->DeleteAllItems();

	delete m_pImageList;
	m_pImageList = NULL;
	
	CDialog::OnOK();
}

void CLogDlg::OnClickTabLog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTabCtrl* pTabCtrl = (CTabCtrl *)GetDlgItem(IDC_TAB_LOG);
	m_nType = pTabCtrl->GetCurSel(); 

	Loading();
	
	*pResult = 0;
}

static int CALLBACK SortTextItems(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	SORT_PARAMS *pSortParams = (SORT_PARAMS *)lParamSort;
	
	CListCtrl *pListCtrl = (CListCtrl *)CWnd::FromHandle(pSortParams->hWnd);
	BOOL	bAscend = pSortParams->bAscend;
	int nCol = pSortParams->nCol;

	CString strItem1 = pListCtrl->GetItemText(lParam1, nCol);
	CString	strItem2 = pListCtrl->GetItemText(lParam2, nCol);

	if(bAscend)
		return strItem1.Compare(strItem2);
	else
		return strItem2.Compare(strItem1);
}

void CLogDlg::OnHeaderClicked(NMHDR* pNMHDR, LRESULT* pResult)
{
	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_LOG);

	NM_LISTVIEW* pNMList = (NM_LISTVIEW*)pNMHDR;

	int nColumn = pNMList->iItem;
	
	for(int i=0; i<pListCtrl->GetItemCount(); i++)
	{
		pListCtrl->SetItemData(i, i);
	}

	m_bAscend = !m_bAscend;
	
	SORT_PARAMS sort_params;
	sort_params.hWnd = pListCtrl->GetSafeHwnd();
	sort_params.nCol = nColumn;
	sort_params.bAscend = m_bAscend;
	
    pListCtrl->SortItems(&SortTextItems, (LPARAM)&sort_params );
    
    *pResult = 0;
}
