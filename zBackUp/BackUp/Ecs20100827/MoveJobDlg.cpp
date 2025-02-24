// JobDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ecs.h"
#include "MoveJob.h"
#include "MoveJobDlg.h"
#include "MoveJobItemDlg.h"
#include "EcsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJobDlg dialog


CMoveJobDlg::CMoveJobDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMoveJobDlg::IDD, pParent)
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

CMoveJobDlg::~CMoveJobDlg()
{
	if (m_pImageList != NULL) delete m_pImageList;
}


void CMoveJobDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJobDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMoveJobDlg, CDialog)
	//{{AFX_MSG_MAP(CJobDlg)
	ON_NOTIFY(NM_CLICK, IDC_TAB_JOB, OnClickTabJob)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_RETRY, OnButtonRetry)
	ON_BN_CLICKED(IDC_BUTTON_ARRIVE, OnButtonArrive)
	ON_BN_CLICKED(IDC_BUTTON_COMPLETE, OnButtonComplete)
	ON_BN_CLICKED(IDC_BUTTON_COUNT_RESET, OnButtonCountReset)
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

BOOL CMoveJobDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString strTemp;
	
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
	lvcolumn.cx = 100;
//	lvcolumn.cx = 80; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

/*	lvcolumn.pszText = "출발위치";
	lvcolumn.cx = 100; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "도착위치";
	lvcolumn.cx = 120; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);
*/
	lvcolumn.pszText = "제품코드";
	lvcolumn.cx = 80; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "진행상태";
	lvcolumn.cx = 150; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "BUFFER";
	lvcolumn.cx = 105; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "LAST";
	lvcolumn.cx = 50; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "제품명";
	lvcolumn.cx = 185; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "LOAD";
	lvcolumn.cx = 65; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "LINE";
	lvcolumn.cx = 45; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

/*	lvcolumn.pszText = "Batch No";
	lvcolumn.cx = 60; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	lvcolumn.pszText = "Pallet No";
	lvcolumn.cx = 50; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);
*/
	lvcolumn.pszText = "수량";
	lvcolumn.cx = 45; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

/*	lvcolumn.pszText = "우선순위";
	lvcolumn.cx = 80; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);
*/
	lvcolumn.pszText = "작업생성시간";
	lvcolumn.cx = 160; 
	pListCtrl->InsertColumn(nCol++, &lvcolumn);

	CTabCtrl* pTabCtrl = (CTabCtrl *)GetDlgItem(IDC_TAB_JOB);

	TC_ITEM TabCtrlItem;

	TabCtrlItem.mask = TCIF_TEXT;
    TabCtrlItem.pszText = "전체";
	pTabCtrl->InsertItem(0, &TabCtrlItem);
//    TabCtrlItem.pszText = "신규";
//	pTabCtrl->InsertItem(1, &TabCtrlItem);
//    TabCtrlItem.pszText = "진행";
//	pTabCtrl->InsertItem(2, &TabCtrlItem);
//    TabCtrlItem.pszText = "에러";
//	pTabCtrl->InsertItem(3, &TabCtrlItem);

	CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_TYPE);

	pComboBox->InsertString(0,"전체");
	pComboBox->InsertString(1,"Buffer #1");
	pComboBox->InsertString(2,"Buffer #2");
	pComboBox->InsertString(3,"Buffer #3");
	pComboBox->InsertString(4,"Buffer #4");
	pComboBox->InsertString(5,"");
	pComboBox->InsertString(6,"");
	pComboBox->InsertString(7,"");
	pComboBox->InsertString(8,"");
	pComboBox->InsertString(9,"");
	pComboBox->InsertString(10,"");
	pComboBox->InsertString(11,"");
	pComboBox->InsertString(12,"수동 LINE");


/*	pComboBox->InsertString(0,"전체");
	pComboBox->InsertString(1,"LINE #1");
	pComboBox->InsertString(2,"LINE #2");
	pComboBox->InsertString(3,"LINE #3");
	pComboBox->InsertString(4,"LINE #4");
	pComboBox->InsertString(5,"LINE #5");
	pComboBox->InsertString(6,"LINE #6");
	pComboBox->InsertString(7,"LINE #7");
	pComboBox->InsertString(8,"LINE #8");
	pComboBox->InsertString(9,"LINE #9");
	pComboBox->InsertString(10,"LINE #10");
	pComboBox->InsertString(11,"LINE #11");
	pComboBox->InsertString(12,"수동 LINE");
*/
	pComboBox->SetCurSel(0);

	strTemp.Format("%d", m_pDoc->m_nSetLine[0]);
	SET(IDC_EDIT_JOB_SET_LINE1, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[1]);
	SET(IDC_EDIT_JOB_SET_LINE2, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[2]);
	SET(IDC_EDIT_JOB_SET_LINE3, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[3]);
	SET(IDC_EDIT_JOB_SET_LINE4, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[4]);
	SET(IDC_EDIT_JOB_SET_LINE5, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[5]);
	SET(IDC_EDIT_JOB_SET_LINE6, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[6]);
	SET(IDC_EDIT_JOB_SET_LINE7, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[7]);
	SET(IDC_EDIT_JOB_SET_LINE8, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[8]);
	SET(IDC_EDIT_JOB_SET_LINE9, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[9]);
	SET(IDC_EDIT_JOB_SET_LINE10, strTemp );



	strTemp.Format("%d", m_pDoc->m_nSetLineCount[0]);
	SET(IDC_EDIT_COUNT_SET_LINE1, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[1]);
	SET(IDC_EDIT_COUNT_SET_LINE2, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[2]);
	SET(IDC_EDIT_COUNT_SET_LINE3, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[3]);
	SET(IDC_EDIT_COUNT_SET_LINE4, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[4]);
	SET(IDC_EDIT_COUNT_SET_LINE5, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[5]);
	SET(IDC_EDIT_COUNT_SET_LINE6, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[6]);
	SET(IDC_EDIT_COUNT_SET_LINE7, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[7]);
	SET(IDC_EDIT_COUNT_SET_LINE8, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[8]);
	SET(IDC_EDIT_COUNT_SET_LINE9, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[9]);
	SET(IDC_EDIT_COUNT_SET_LINE10, strTemp );



	Loading();

	m_bAscend = FALSE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMoveJobDlg::Loading() 
{
	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_JOB);
	CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO_TYPE);
	m_nType = pComboBox->GetCurSel();

	m_pDoc->m_pMoveJob->Load(pListCtrl, m_nType, m_nStatus);

	CString strTemp;
	strTemp.Format(" %d Item(s)", pListCtrl->GetItemCount());
	GetDlgItem(IDC_EDIT_DISP)->SetWindowText(strTemp);

	m_nCurSel = LB_ERR;
}

void CMoveJobDlg::OnClickTabJob(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTabCtrl* pTabCtrl = (CTabCtrl *)GetDlgItem(IDC_TAB_JOB);
	if ((m_nStatus = pTabCtrl->GetCurSel()) == 2)
		m_nStatus = JOB_STA_PROGRESS; 

	Loading();

	*pResult = 0;
}

void CMoveJobDlg::OnButtonAdd() 
{
	m_pDoc->OnManual();	

	if (m_pDoc->m_pJob->IsModified())
	{
		Loading();
	}
}

void CMoveJobDlg::OnButtonRefresh() 
{
	Loading();
}

void CMoveJobDlg::OnSelchangeComboType() 
{
	Loading();
}

void CMoveJobDlg::JobItemDetail(int nCmd) 
{
	CListCtrl* pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST_JOB);

	if (m_nCurSel == LB_ERR)
		MessageBox("No item is currently selected !");

	int nLuggNum = atoi(pListCtrl->GetItemText(m_nCurSel, 0));

	CMoveJobItemDlg MoveJobItemDlg;
	CMoveJobItem* pMoveJobItem = m_pDoc->m_pMoveJob->Find(nLuggNum);
	if (pMoveJobItem == NULL)
		return;

	MoveJobItemDlg.m_pMoveJobItem = pMoveJobItem;
	MoveJobItemDlg.m_nCmd = nCmd;
	MoveJobItemDlg.m_pDoc = m_pDoc;
	if (MoveJobItemDlg.DoModal() == IDOK)
	{
		Loading();
	}
}

void CMoveJobDlg::OnButtonModify() 
{
	JobItemDetail(CMD_MODIFY);
}

void CMoveJobDlg::OnButtonCancel() 
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
			CMoveJobItem* pMoveJobItem = m_pDoc->m_pMoveJob->Find(nLuggNum);

			if (pMoveJobItem == NULL)
				continue;

			for(int i=0; i<10; i++)
			{
				if(pMoveJobItem->m_nBatchNo == 0)
					continue;

				if(pMoveJobItem->m_nBatchNo == i+1)
					m_pDoc->m_nSetLineCount[i]--;
			}
			
			m_pDoc->m_pMoveJob->Remove(pMoveJobItem);
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

void CMoveJobDlg::OnButtonRetry() 
{
	JobItemDetail(CMD_RETRY);
}

void CMoveJobDlg::OnButtonArrive() 
{
	JobItemDetail(CMD_ARRIVE);
}

void CMoveJobDlg::OnButtonComplete() 
{
	JobItemDetail(CMD_COMPLETE);
}

void CMoveJobDlg::OnButtonCountReset() 
{
	if (AfxMessageBox("Line 카운트를 모두 초기화 하시겠습니까?", MB_OKCANCEL) == IDCANCEL)
		return ;

	for(int i=0; i<10; i++)
		m_pDoc->m_nSetLineCount[i] = 0;

	static int nTimerID;

	nTimerID = SetTimer(ID_JOB_TIMER, 1000, NULL);

}


void CMoveJobDlg::OnItemchangedListJob(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if (!(pNMListView->uNewState & LVIS_SELECTED))
		return;

	m_nCurSel = pNMListView->iItem ;	

//	RepaintSelectedItems();

	*pResult = 0;
}

void CMoveJobDlg::OnCheckAuto() 
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

void CMoveJobDlg::OnTimer(UINT nIDEvent) 
{
	if (m_pDoc->m_pMoveJob->IsModified())
	{
		Loading();
	}

	CString strTemp;

	strTemp.Format("%d", m_pDoc->m_nSetLine[0]);
	SET(IDC_EDIT_JOB_SET_LINE1, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[1]);
	SET(IDC_EDIT_JOB_SET_LINE2, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[2]);
	SET(IDC_EDIT_JOB_SET_LINE3, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[3]);
	SET(IDC_EDIT_JOB_SET_LINE4, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[4]);
	SET(IDC_EDIT_JOB_SET_LINE5, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[5]);
	SET(IDC_EDIT_JOB_SET_LINE6, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[6]);
	SET(IDC_EDIT_JOB_SET_LINE7, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[7]);
	SET(IDC_EDIT_JOB_SET_LINE8, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[8]);
	SET(IDC_EDIT_JOB_SET_LINE9, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLine[9]);
	SET(IDC_EDIT_JOB_SET_LINE10, strTemp );



	strTemp.Format("%d", m_pDoc->m_nSetLineCount[0]);
	SET(IDC_EDIT_COUNT_SET_LINE1, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[1]);
	SET(IDC_EDIT_COUNT_SET_LINE2, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[2]);
	SET(IDC_EDIT_COUNT_SET_LINE3, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[3]);
	SET(IDC_EDIT_COUNT_SET_LINE4, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[4]);
	SET(IDC_EDIT_COUNT_SET_LINE5, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[5]);
	SET(IDC_EDIT_COUNT_SET_LINE6, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[6]);
	SET(IDC_EDIT_COUNT_SET_LINE7, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[7]);
	SET(IDC_EDIT_COUNT_SET_LINE8, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[8]);
	SET(IDC_EDIT_COUNT_SET_LINE9, strTemp );

	strTemp.Format("%d", m_pDoc->m_nSetLineCount[9]);
	SET(IDC_EDIT_COUNT_SET_LINE10, strTemp );
	
	CDialog::OnTimer(nIDEvent);
}

void CMoveJobDlg::OnDblclkListJob(NMHDR* pNMHDR, LRESULT* pResult) 
{
	JobItemDetail(CMD_MODIFY);
	
	*pResult = 0;
}

void CMoveJobDlg::RepaintSelectedItems()
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

void CMoveJobDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
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

LPCTSTR CMoveJobDlg::MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset)
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

void CMoveJobDlg::OnOK() 
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

void CMoveJobDlg::OnHeaderClicked(NMHDR* pNMHDR, LRESULT* pResult)
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
