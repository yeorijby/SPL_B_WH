// JobDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "Job.h"
#include "JobDlg.h"
#include "JobItemDlg.h"
#include "EcsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJobDlg dialog


CJobDlg::CJobDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJobDlg::IDD, pParent)
{
	m_nType = JOB_TYPE_ALL;
	m_nStatus = JOB_STA_ALL;
	m_nCurSel = -1;
	m_bCheckAuto = TRUE;
	m_pImageList = NULL;

	//{{AFX_DATA_INIT(CJobDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CJobDlg::~CJobDlg()
{
	if (m_pImageList != NULL) delete m_pImageList;
}


void CJobDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJobDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJobDlg, CDialog)
	//{{AFX_MSG_MAP(CJobDlg)
	ON_NOTIFY(NM_CLICK, IDC_TAB_JOB, OnClickTabJob)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_RETRY, OnButtonRetry)
	ON_BN_CLICKED(IDC_BUTTON_COMPLETE, OnButtonComplete)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_JOB, OnItemchangedListJob)
	ON_BN_CLICKED(IDC_CHECK_AUTO, OnCheckAuto)
	ON_WM_TIMER()
	ON_WM_DRAWITEM()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_JOB, OnDblclkListJob)
	ON_NOTIFY(HDN_ITEMCLICKA, 0, OnHeaderClicked) 
	ON_NOTIFY(HDN_ITEMCLICKW, 0, OnHeaderClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJobDlg message handlers

BOOL CJobDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_pImageList = new CImageList();		
	ASSERT(m_pImageList != NULL);    // no serious allocation failure checking

	CEcsApp* pApp = (CEcsApp *)AfxGetApp();
	m_pImageList->Create(16, 16, TRUE/*bMask*/,	1/*nInitial*/, 1/*nGrow*/);
	m_pImageList->Add(pApp->LoadIcon(IDI_ICON5));

	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_JOB);

	pListCtrl->SetImageList(m_pImageList, LVSIL_SMALL);

	LV_COLUMN		lvcolumn;

	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvcolumn.fmt = LVCFMT_LEFT;
	lvcolumn.pszText = "작업번호";
	lvcolumn.iSubItem = 0;
	lvcolumn.cx = 80;

	int nCol = 0;
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "작업구분";
	lvcolumn.cx = 120;
//	lvcolumn.cx = 80; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "출발위치";
	lvcolumn.cx = 100; 
//	lvcolumn.cx = 80;
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "도착위치";
	lvcolumn.cx = 120; 
//	lvcolumn.cx = 80;
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "제품명";
	lvcolumn.cx = 160; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "진행상태";
	lvcolumn.cx = 250; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "Batch No";
	lvcolumn.cx = 80; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "Pallet No";
	lvcolumn.cx = 50; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "Lelvel No";
	lvcolumn.cx = 30; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "제품코드";
	lvcolumn.cx = 100; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "우선순위";
	lvcolumn.cx = 80; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "유통기간";
	lvcolumn.cx = 80; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "작업생성시간";
	lvcolumn.cx = 160; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	CTabCtrl* pTabCtrl = (CTabCtrl *)GetDlgItem(IDC_TAB_JOB);

	TC_ITEM TabCtrlItem;

	TabCtrlItem.mask = TCIF_TEXT;
    TabCtrlItem.pszText = "전체";
	pTabCtrl->InsertItem(0, &TabCtrlItem);
    TabCtrlItem.pszText = "신규";
	pTabCtrl->InsertItem(1, &TabCtrlItem);
    TabCtrlItem.pszText = "진행";
	pTabCtrl->InsertItem(2, &TabCtrlItem);
    TabCtrlItem.pszText = "에러";
	pTabCtrl->InsertItem(3, &TabCtrlItem);

	CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_TYPE);

/*	CJobItem JobItem;
	for (int i=0; i < (JOB_TYPE_CNT+SC_CNT); i++)
	{
		pComboBox->InsertString(i, JobItem.GetType(i));
	}
*/	
	pComboBox->InsertString(0,"전체");
	pComboBox->InsertString(1,"UNIT 입고");
	pComboBox->InsertString(2,"UNIT 출고");
	pComboBox->InsertString(3,"외주창고 이동");
	pComboBox->InsertString(4,"반자동 입고");
	pComboBox->InsertString(5,"반자동 출고");
	pComboBox->InsertString(6,"반자동 외주창고 이동");
	pComboBox->InsertString(7,"출하분류대#1");
	pComboBox->InsertString(8,"출하분류대#2");
	pComboBox->InsertString(9,"출하분류대#3");
	pComboBox->InsertString(10,"출하이동대");

	pComboBox->SetCurSel(0);

	Loading();

	m_bAscend = FALSE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CJobDlg::Loading() 
{
	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_JOB);
	CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_TYPE);
	m_nType = pComboBox->GetCurSel();

	switch(m_nType)
	{
	case 0:
	case 1:
	case 2:	break;
	case 3:	m_nType = 6;  break;
	case 4: m_nType = 7;  break;
	case 5: m_nType = 4;  break;
	case 6: m_nType = 10; break;

	case 7: m_nType = 13;  break;
	case 8: m_nType = 14;  break;
	case 9: m_nType = 15;  break;
	case 10: m_nType = 16;  break;
	}

	m_pDoc->m_pJob->Load(pListCtrl, m_nType, m_nStatus);

	CString strTemp;
	strTemp.Format(" %d Item(s)", pListCtrl->GetItemCount());
	GetDlgItem(IDC_EDIT_DISP)->SetWindowText(strTemp);

	m_nCurSel = LB_ERR;
}

void CJobDlg::OnClickTabJob(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTabCtrl* pTabCtrl = (CTabCtrl *)GetDlgItem(IDC_TAB_JOB);
	if ((m_nStatus = pTabCtrl->GetCurSel()) == 2)
		m_nStatus = JOB_STA_PROGRESS; 

	Loading();

	*pResult = 0;
}

void CJobDlg::OnButtonAdd() 
{
	m_pDoc->OnManual();	

	if (m_pDoc->m_pJob->IsModified())
	{
		Loading();
	}
}

void CJobDlg::OnButtonRefresh() 
{
	Loading();
}

void CJobDlg::OnSelchangeComboType() 
{
	Loading();
}

void CJobDlg::JobItemDetail(int nCmd) 
{
	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_JOB);

	if (m_nCurSel == LB_ERR)
		MessageBox("No item is currently selected !");

	int nLuggNum = atoi(pListCtrl->GetItemText(m_nCurSel, 0));

	CJobItemDlg JobItemDlg;
	CJobItem* pJobItem = m_pDoc->m_pJob->Find(nLuggNum);
	if (pJobItem == NULL)
		return;

	JobItemDlg.m_pJobItem = pJobItem;
	JobItemDlg.m_nCmd = nCmd;
	JobItemDlg.m_pDoc = m_pDoc;
	if (JobItemDlg.DoModal() == IDOK)
	{
		if (nCmd == CMD_RETRY)
		{
			if (pJobItem->m_nStatus == JOB_STA_SC_OPER_REQUEST)
			{
				int nScNum = pJobItem->GetStackerNum();
				m_pDoc->m_StackerThreadInfo[nScNum].m_StackerMsg.nCommand = SC_CMD_INVOKE;
				m_pDoc->m_StackerThreadInfo[nScNum].m_StackerMsg.nLuggNum = nLuggNum;
				CString strTemp;
				strTemp.Format("ScNum=[%d] Retry.. Stacker Operation Request..", nScNum + 1);
				m_pDoc->m_pLog->Event(LOG_POS_SYSTEM, nLuggNum, strTemp);
				SetEvent(m_pDoc->m_hEventSendStacker[nScNum]);
			}
		}
		Loading();
	}
}

void CJobDlg::OnButtonModify() 
{
	JobItemDetail(CMD_MODIFY);
}

void CJobDlg::OnButtonCancel() 
{
	//JobItemDetail(CMD_CANCEL);

	int nChk = 0;

	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_JOB);

	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox("No item is currently selected !");
		return;
	}
	else
	{
		int nSelect = pListCtrl->GetSelectedCount();

		CString strTemp;
		strTemp.Format("%d개 작업을 삭제하시겠습니까?",nSelect);

		if (AfxMessageBox(strTemp, MB_OKCANCEL) == IDCANCEL)
			return ;

		while (pos)
		{
			int nItem = pListCtrl->GetNextSelectedItem(pos);
			int nLuggNum = atoi(pListCtrl->GetItemText(nItem, 0));
			CJobItem* pJobItem = m_pDoc->m_pJob->Find(nLuggNum);

			if (pJobItem == NULL)
				continue;
			
			m_pDoc->m_pJob->Remove(pJobItem);
			strTemp.Format("작업자가 작업을 강제 삭제하였습니다!");
			m_pDoc->m_pLog->Event(LOG_POS_SYSTEM, nLuggNum, strTemp);

			nChk++;
     	}
	}

	if (nChk > 0)
		Loading();

	/*
	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_JOB);

	int nCount = pListCtrl->GetItemCount();
	int nChk = 0;
	int nSelChk;

	int aaa = pListCtrl->GetSelectedCount();

	for (int i=0; i<aaa; i++) {
		
		nSelChk = pListCtrl->GetCheck(i);

		if (nSelChk == 1) 
		{
			int nLuggNum = atoi(pListCtrl->GetItemText(i, 0));
			CJobItem* pJobItem = m_pDoc->m_pJob->Find(nLuggNum);

			if (pJobItem == NULL)
				continue;
			
			m_pDoc->m_pJob->Remove(pJobItem);
			nChk++;
			
		}
    }

	if (nChk > 0)
		Loading();
	*/
}

void CJobDlg::OnButtonRetry() 
{
	JobItemDetail(CMD_RETRY);
}

void CJobDlg::OnButtonComplete() 
{
	JobItemDetail(CMD_COMPLETE);
}

void CJobDlg::OnItemchangedListJob(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if (!(pNMListView->uNewState & LVIS_SELECTED))
		return;

	m_nCurSel = pNMListView->iItem ;	

//	RepaintSelectedItems();

	*pResult = 0;
}

void CJobDlg::OnCheckAuto() 
{
	static int nTimerID;

	if (m_bCheckAuto) 
	{
		m_bCheckAuto = FALSE;
		nTimerID = SetTimer(ID_JOB_TIMER, 1000, NULL);
	}
	else
	{
		m_bCheckAuto = TRUE;
		KillTimer(nTimerID);
	}

	GetDlgItem(IDC_BUTTON_REFRESH)->EnableWindow(m_bCheckAuto);
	GetDlgItem(IDC_BUTTON_CANCEL)->EnableWindow(m_bCheckAuto);
	GetDlgItem(IDC_BUTTON_COMPLETE)->EnableWindow(m_bCheckAuto);
	GetDlgItem(IDC_BUTTON_MODIFY)->EnableWindow(m_bCheckAuto);
//	GetDlgItem(IDC_BUTTON_RETRY)->EnableWindow(m_bCheckAuto);
}

void CJobDlg::OnTimer(UINT nIDEvent) 
{
	if (m_pDoc->m_pJob->IsModified())
	{
		Loading();
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CJobDlg::OnDblclkListJob(NMHDR* pNMHDR, LRESULT* pResult) 
{
	JobItemDetail(CMD_MODIFY);
	
	*pResult = 0;
}

void CJobDlg::RepaintSelectedItems()
{
	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_JOB);

	CRect rcItem, rcLabel;

// invalidate focused item so it can repaint properly

	int nItem = pListCtrl->GetNextItem(-1, LVNI_FOCUSED);

	if(nItem != -1)
	{
		pListCtrl->GetItemRect(nItem, rcItem, LVIR_BOUNDS);
		pListCtrl->GetItemRect(nItem, rcLabel, LVIR_LABEL);
		rcItem.left = rcLabel.left;

		InvalidateRect(rcItem, FALSE);
	}

// if selected items should not be preserved, invalidate them

	if(!(GetStyle() & LVS_SHOWSELALWAYS))
	{
		for(nItem = pListCtrl->GetNextItem(-1, LVNI_SELECTED);
			nItem != -1; nItem = pListCtrl->GetNextItem(nItem, LVNI_SELECTED))
		{
			pListCtrl->GetItemRect(nItem, rcItem, LVIR_BOUNDS);
			pListCtrl->GetItemRect(nItem, rcLabel, LVIR_LABEL);
			rcItem.left = rcLabel.left;

			InvalidateRect(rcItem, FALSE);
		}
	}

// update changes 

	UpdateWindow();
}

// offsets for first and other columns
#define OFFSET_FIRST	2
#define OFFSET_OTHER	6

void CJobDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{

	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_JOB);

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
//	BOOL bSelected = (bFocus || (GetStyle() & LVS_SHOWSELALWAYS)) && lvi.state & LVIS_SELECTED;
//	bSelected = bSelected || (lvi.state & LVIS_DROPHILITED);

// set colors if item is selected

	CRect rcAllLabels;
	pListCtrl->GetItemRect(nItem, rcAllLabels, LVIR_BOUNDS);

	CRect rcLabel;
	pListCtrl->GetItemRect(nItem, rcLabel, LVIR_LABEL);

	rcAllLabels.left = rcLabel.left;
	if (rcAllLabels.right < 800)
//	if (m_bClientWidthSel && rcAllLabels.right<m_cxClient)
		rcAllLabels.right = 800;
//		rcAllLabels.right = m_cxClient;

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
		//if (nRetLen == 0)
		//	continue;

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

LPCTSTR CJobDlg::MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset)
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

void CJobDlg::OnOK() 
{
	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_JOB);
	pListCtrl->DeleteAllItems();

	delete m_pImageList;
	m_pImageList = NULL;
	
	CDialog::OnOK();
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

void CJobDlg::OnHeaderClicked(NMHDR* pNMHDR, LRESULT* pResult)
{
	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_JOB);

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
