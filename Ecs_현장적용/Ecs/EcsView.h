// EcsView.h : interface of the CEcsView class
//
/////////////////////////////////////////////////////////////////////////////

#include "EcsDef.h"
#include "ConveyorDlg.h"
#include "ToolTipWnd.h"
#include "EcsDoc.h"
//#include "Label.h"

//class CEditEx;
class CEcsView : public CFormView
{
protected: // create from serialization only
	CEcsView();
	DECLARE_DYNCREATE(CEcsView)

public:
	//{{AFX_DATA(CEcsView)
	enum{ IDD = IDD_ECS_FORM_KOR };

	BOOL	m_b4Check;
	BOOL	m_b5Check;
	BOOL	m_b6Check;
	BOOL	m_b7Check;
	BOOL	m_b8Check;
	BOOL	m_b9Check;

	BOOL    m_bTroubleCheck;
	BOOL    m_bLineTroubleCheck;
	BOOL    m_bStopCheck;
	BOOL    m_bBufferStopCheck;
	BOOL    m_bLineCheck;
	BOOL    m_bLineCheck2;
	BOOL    m_bCountCheck;
	BOOL    m_bTestCheck;

	BOOL    m_bStackingCheck1;
	BOOL    m_bStackingCheck2;

	BOOL    m_bPriorityCheck;
	BOOL    m_bLineEmergencyCheck;

	BOOL    m_bAllSEmergenCheck;
	BOOL	m_bAllScStoSuspend;
	BOOL	m_bAllScRetSuspend;
//	enum{ IDD = IDD_ECS_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
/*	CEditEx	 m_edt4GroupInCount;
	CEditEx	 m_edt4GroupOutCount;
	CEditEx	 m_edt5GroupInCount;
	CEditEx	 m_edt5GroupOutCount;
	CEditEx	 m_edt6GroupInCount;
	CEditEx	 m_edt6GroupOutCount;
*/
// Attributes
public:
	CEcsDoc* GetDocument();

	CConveyorDlg m_ConveyorDlg;

	int	m_nMainTimerID;
	CToolTipWnd m_bttWnd;
	COLORREF GetCvColor(BOOL bOverTime, BOOL bOverLoad,BOOL bBuffTrouble,  int nJobType, BOOL bOpMode, BOOL bPltSensor=FALSE);
	BOOL IsReportingStatusTrack(int nTrack);

	BOOL TestMethod(BOOL *bCheck);

	// Operations
public:
	LRESULT OnJobNotify(WPARAM wParam, LPARAM lParam);
	LRESULT OnCvNotify(WPARAM wParam, LPARAM lParam);
	LRESULT OnScNotify(WPARAM wParam, LPARAM lParam);
	LRESULT OnHostNotify(WPARAM wParam, LPARAM lParam);
	LRESULT OnRgvNotify(WPARAM wParam, LPARAM lParam);
	LRESULT OnEcsNotify(WPARAM wParam, LPARAM lParam);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEcsView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	char ConvertNotifyToStatus(int nNotify);

	void 	GetConvertHorizontalPos(int nRgvNum, int nHorizontal);
//	void CountFont();
	virtual ~CEcsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEcsView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLBtnClickOpbox(short nID);
	afx_msg void OnLBtnClickStacker(short nID);
	afx_msg void OnLBtnClickConveyor(short nID);
	afx_msg void OnLBtnClickRgv(short nID);
	afx_msg void OnCheckBufferFull1();
	afx_msg void OnCheckBufferFull2();
	afx_msg void OnCheckBufferFull3();
	afx_msg void OnCheckTrouble();
	afx_msg void OnCheckStop();
	afx_msg void OnCheckSetLine();
	afx_msg void OnCheckSetLine2();
	afx_msg void OnCheckChangeCount();
	afx_msg void OnCheckTest();
	afx_msg void OnButtonSignal();
	afx_msg void OnCheckSetPriority();
	afx_msg void OnCheckLineEmergency();
	afx_msg void OnCheckStacking1();
	afx_msg void OnCheckStacking2();
	afx_msg void OnCheckBufferFull4();
	afx_msg void OnCheckBufferFull5();
	afx_msg void OnCheckBufferFull6();
	afx_msg void OnButtonResetIncount();
	afx_msg void OnCheckBufferStop();
	afx_msg void OnCheckStackEmergency();
	afx_msg void OnCheckScStoSuspend();
	afx_msg void OnCheckScRetSuspend();
	afx_msg void OnCheckLineTrouble();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in EcsView.cpp
inline CEcsDoc* CEcsView::GetDocument()
   { return (CEcsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
