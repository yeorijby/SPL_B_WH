// EcsDoc.h : interface of the CEcsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef	__ECSDOC_H__
#define	__ECSDOC_H__

#include "EcsDef.h"
#include "Host.h"
#include "Thread.h"
#include "Log.h"
#include "Job.h"
#include "MoveJob.h"
#include "Config.h"
#include "Statistic.h"
#include "ConveyorTrackInfo.h"
#include "StackerInfo.h"
#include "CvSocket.h"
#include "RgvInfo.h"
#include "EcsSockClient.h"

#include "ScSocket.h"

class CLogoDlg;

class CDisplayMsg
{
public:
	CDisplayMsg(CString strMsg, BOOL bNormalStatus);

	CString m_strMsg;
	BOOL m_bNormalStatus;
};

class CEcsDoc : public CDocument
{
protected: // create from serialization only
	CEcsDoc();
	DECLARE_DYNCREATE(CEcsDoc)

// Attributes
public:
#ifdef TEST_MODE
	int m_nSto;
	int m_nRet;
#endif

	HWND m_hwndView;
	CConfig* m_pConfig;
	CStatistic* m_pStatistic;
	CJob* m_pJob;
	CMoveJob* m_pMoveJob;
	CLog* m_pLog;
	CListenSk* m_pListenSk;
	CHostSv* m_pHostSv;
	CHostCl* m_pHostCl;
	CEcsSockClient* m_pEcsCl;

	CCvSocket *m_pConveyorSocket[CV_PLC_CNT];
	int m_nAlive;

	CTime m_timeFullReady[14];
	CTime m_timeStart[14];
	BOOL  m_bBufferSuspend[14];
	
	CPtrList m_MsgList;

	CWinThread* m_pHostThread;
	SHostThreadInfo m_HostThreadInfo;
	HANDLE m_hEventNotifyHost;
	HANDLE m_hEventKillHostThread;
	HANDLE m_hEventHostThreadKilled;

	//CConveyorTrackInfo m_ConveyorTrackInfo[1500];
	CConveyorTrackInfo m_ConveyorTrackInfo[2500];
	COpBoxInfo m_OpBoxInfo[OPBOX_CNT];
	CStackerInfo* m_pStackerInfo[SC_CNT];
	CRgvInfo* m_pRgvInfo[RGV_CNT];
	
	CWinThread* m_pConveyorThread[CV_PLC_CNT];
	SConveyorThreadInfo m_ConveyorThreadInfo[CV_PLC_CNT];
	int m_nConveyorEventCount[CV_PLC_CNT];
	HANDLE m_hEventSendConveyor[CV_PLC_CNT];
	HANDLE m_hEventKillConveyorThread[CV_PLC_CNT];
	HANDLE m_hEventConveyorThreadKilled[CV_PLC_CNT];


	CWinThread* m_pStackerThread[SC_CNT];
	SStackerThreadInfo m_StackerThreadInfo[SC_CNT];
	int m_nStackerEventCount[SC_CNT];
	HANDLE m_hEventSendStacker[SC_CNT];
	HANDLE m_hEventKillStackerThread[SC_CNT];
	HANDLE m_hEventStackerThreadKilled[SC_CNT];
	CScSocket* m_pStackerSocket[SC_CNT];

	CWinThread* m_pRgvThread[RGV_CNT];
	SRgvThreadInfo m_RgvThreadInfo[RGV_CNT];
	int m_nRgvEventCount[RGV_CNT];
	HANDLE m_hEventSendRgv[RGV_CNT];
	HANDLE m_hEventKillRgvThread[RGV_CNT];
	HANDLE m_hEventRgvThreadKilled[RGV_CNT];

	SConveyorMsg m_ConveyorMsg;

	BOOL m_bScSta[SC_CNT], m_bCvSta[CV_PLC_CNT];
	BOOL m_bCv1Alive;
	BOOL m_bBuzzer, m_bScJobHold[SC_CNT], m_bScEmerStop[SC_CNT];
	int  m_nDispLine;
	int  m_nRetCnt[2];

	BOOL m_bStoRetMode;
    BOOL m_bWriteTroubleCheck;
	BOOL m_bWriteLineTroubleCheck;
	BOOL m_bJobStopCheck;
	BOOL m_bBufferStopCheck;

	BOOL m_bWriteStackingCheck1;
	BOOL m_bWriteStackingCheck2;

	BOOL m_bSetLineCheck;
	BOOL m_bSetLineCheck2;
	BOOL m_bSetCountCheck;
	BOOL m_bSetTestCheck;
	int  m_nSetLine[10];
	int  m_nSetLineCount[10];
	BOOL m_bBufferLock[10];
	int  m_nSetLine2[14];
	int  m_nSetLineCount2[14];
	BOOL m_bBufferLock2[14];

	BOOL	m_bSafetyError[2];
	BOOL	m_bRtvCpError[2];

	BOOL	m_bStoSafetyError[6];
	BOOL	m_bRetSafetyError[6];

	BOOL	m_bAllScStoSuspend;
	BOOL	m_bAllScRetSuspend;

	int m_n4GroupInCount;
	int m_n4GroupOutCount;
	int m_n5GroupInCount;
	int m_n5GroupOutCount;
	int m_n6GroupInCount;
	int m_n6GroupOutCount;
	int m_n7GroupInCount;

	int m_n4GroupInternalCount;
	int m_n5GroupInternalCount;
	int m_n6GroupInternalCount;

	int m_n4GroupCvCount;
	int m_n5GroupCvCount;
	int m_n6GroupCvCount;

	int m_n4GroupInternalBatch;
	int m_n5GroupInternalBatch;
	int m_n6GroupInternalBatch;
	int m_n7GroupInternalBatch;

	int m_n4GroupInternalPallet;
	int m_n5GroupInternalPallet;
	int m_n6GroupInternalPallet;
	int m_n7GroupInternalPallet;

	int m_n4groupInternalPalletCount;
	int m_n5groupInternalPalletCount;
	int m_n6groupInternalPalletCount;
	int m_n7groupInternalPalletCount;

	BOOL m_b4groupCheck;
	BOOL m_b5groupCheck;
	BOOL m_b6groupCheck;
	BOOL m_b7groupCheck;
	BOOL m_b8groupCheck;
	BOOL m_b9groupCheck;
	
	BOOL m_b4groupBuffIn[6];
	BOOL m_b5groupBuffIn[6];
	BOOL m_b6groupBuffIn[6];

	int m_n4goupBuffCouter;
	int m_n5goupBuffCouter;
	int m_n6goupBuffCouter;

	int m_nInCountReset;
	BOOL m_bInResetCheck;

	CString m_strDualCheck;
    BOOL m_bPriorityDocCheck;
	BOOL m_bAlarmError; 

	CString m_strCodeNum;
	int m_nPeriodNum;
	CString m_strProdName;
	CString m_strQuantity;
	CString m_strLineNum;
	CString m_strCheckNum;

	CString m_strCodeNum2;
	int m_nPeriodNum2;
	CString m_strProdName2;
	CString m_strQuantity2;
	CString m_strLineNum2;
	CString m_strCheckNum2;

	BOOL m_bAllStackerEmergency;

	int m_nLineModeAB;

	BOOL m_bLineGoing[14];

	BOOL m_bSWStart;
	
// Operations
public:
	BOOL Initialize();
	void ConnectServer();
	void ConnectEcsServer();
	BOOL ConnectSocket(LPCTSTR lpszAddress, UINT nPort);
	BOOL ConnectEcsSocket(LPCTSTR lpszAddress, UINT nPort);
	void ProcessPendingRead();
	void SendMsg(CString& strText);
	void ReceiveMsg();
	BOOL Backup();
	BOOL Restore();
	void DisplayMessage();
	void DisplayMessage(CString strMsg, BOOL bNormalStatus = TRUE);
	void EventLog(int nLuggNum, CString strContent);

	BOOL ConnectCvSocket(int nCvNum, LPCTSTR lpszAddress, UINT nPort);
	void ConnectCvServer(int nCvNum);
	BOOL ConnectScSocket(int nScNum, LPCTSTR lpszAddress, UINT nPort, CString strDevice);
	void ConnectScServer(int nScNum);

	BOOL MoveBackup();
	BOOL MoveRestore();

//	void UpdateHostCommCl(char Status);
//	void UpdateHostCommSv(char Status);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEcsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEcsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
public:
	void CvAction(int nPlcNum);
	void ScAction(int nScNum);
	//{{AFX_MSG(CEcsDoc)
	afx_msg void OnLogging();
	afx_msg void OnManual();
	afx_msg void OnJob();
	afx_msg void OnMoveJob();
	afx_msg void OnConfig();
	afx_msg void OnLogo();
	afx_msg void OnSystemResetResultCount();
//	afx_msg void OnSystemRemoveAllJob();
	afx_msg void OnStatisticsAvail();
	afx_msg void OnStatisticsThroughput();
	afx_msg void OnStatisticsErrcode();
//	afx_msg void OnScErrLog();
//	afx_msg void OnSystemResetStatisticInfo();
//	afx_msg void OnColorView();
	afx_msg void OnCommHostClient();
	afx_msg void OnCommHostServer();
	afx_msg void OnCommCv1();
	afx_msg void OnCommCv2();
	afx_msg void OnCommCv3();
	afx_msg void OnCommCv4();
	afx_msg void OnCommCv5();
	afx_msg void OnCommCv6();
	afx_msg void OnCommCv7();
	afx_msg void OnCommCv8();
	afx_msg void OnCommCv9();
	afx_msg void OnCommSc1();
	afx_msg void OnCommSc2();
	afx_msg void OnCommSc3();
	afx_msg void OnCommSc4();
	afx_msg void OnCommSc5();
	afx_msg void OnCommSc6();
	afx_msg void OnCommRgv1();
	afx_msg void OnCommRgv2();
	afx_msg void OnCommNewEcs();
//	afx_msg void OnScInhibit();
	//}}AFX_MSG
	afx_msg void OnUpdateDateTime(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMode(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif // __ECSDOC_H__
