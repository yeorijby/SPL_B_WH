// Job.h : Defines the class behaviors for the application.
#ifndef __JOB_H__
#define __JOB_H__

#include <afxmt.h>
#include "EcsDef.h"
#include <EcsEnv.h>

class CCriticalSectionEx : public CCriticalSection
{
public:
	CCriticalSectionEx() {};
	CCriticalSectionEx(const CCriticalSectionEx& cs) {};
};

class CJobItem : public CObject
{
protected:
	DECLARE_SERIAL(CJobItem)

// constructor & destructor
public:
	CJobItem() { m_bLock = FALSE; };
	CJobItem(int nLuggNum, int nJobType, CString strLocation, int nBatchNo, int nPalletNo, int nLevelNo, int nStartPos, int nDestPos, int nPriority = 100, CString strProductID = "", CString strSecondLoc = "", int nStatus = JOB_STA_NEW, CString strGrade = "", CString strQuantity = "", int nHeight = -1);

// Attributes
public:
	int	m_nLuggNum;
	int m_nJobType;
	CString m_strLocation;
	CString m_strSecondLoc;

	int	m_nStartPos;
	int	m_nDestPos;
	int	m_nPriority;
	int m_nStatus;
	int m_nErrCode;

	int m_nBatchNo;
	int m_nPalletNo; 
	int m_nLevelNo;

	int m_nDestTrack;

	time_t m_tTimeStamp;

	CString	m_strGrade;
	CString	m_strQuantity;
	CString m_strProductID;
	int m_nHeight;  
	BOOL m_bLock;
	BOOL m_bFirstFork;

// Operation
public:
	CString GetLuggNumString();
	CString GetBatchNoString();
	CString GetTimeStampString();
	CString GetPriorityString();
	CString GetType();
	CString GetType(int nType);
	int GetPattern();
	int GetPattern(int nType);
	CString GetStartPos();
	CString GetStartPos(CString strLocation,  int nStartPos, int nType);
	CString GetDestPos();
	CString GetDestPos(CString strLocation,  CString strSecondLoc, int nDestPos, int nType);
	CString GetStatus();
	CString GetStatus(int nStatus);
	CString GetHeight();
	CString GetHeight(int nHeight);
	int GetBlock();
	int GetSecondBlock();
	int GetBlock(CString strLocation);
	int GetStackerNum();
	int GetStackerNum(CString strLocation);
	int GetBank();
	int GetBank(CString strLocation);
	int GetBay();
	int GetBay(CString strLocation);
	int GetLevel();
	int GetLevel(CString strLocation);
	CString GetErrInfo();
	CString GetErrInfo(int nErrCode);
	BOOL IsError();
	BOOL IsError(int nStatus);
	BOOL IsValidLocation();
	BOOL IsValidLocation(CString strLocation);
	BOOL IsLocking() { return (m_bLock) ? TRUE : FALSE; };
	void Lock() { m_bLock = TRUE; };
	void Release() { m_bLock = FALSE; };
	BOOL IsOffLineJob();
	BOOL	IsManualJob();

// Implementation
public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

#define	JOB_PROGRESS_DRAW		1
#define	JOB_RESULT_DRAW			2

class CEcsDoc;
class CJob : public CObject
{
protected:
	DECLARE_DYNCREATE(CJob)

	static CCriticalSectionEx m_csJobAdd;
 
// constructor & destructor
public:
	CJob() {};
	CJob(CEcsDoc* pDoc);
	~CJob();

// Attributes
protected:

public:
	CEcsDoc* m_pDoc;
	CObList m_JobList;
	CObList m_MsgList;
	CObList m_BcrBuff;
	CString	m_strFileName;
	BOOL m_bModified;
	BOOL m_bIsOfflineJob;
	int m_nResultCount[SC_CNT];
	int m_nScRetCount[SC_CNT];
	int	m_nLuggNum;
	int m_nEntryCnt;
	int m_nRetCnt;
	int m_nScOrderNo;
	int m_nScOrderCnt;
	int m_nCvOrderNo;
	int m_nCvOrderCnt;

	int  m_nPrevOrderNo;
	int  m_nBcrOrderNo;
	int  m_nOppOrderNo;
	int  m_nBcrOrderCnt;

	BOOL m_bSwitchSts;
	BOOL m_bPrevSwitchSts;
	BOOL m_bSwitchChg;

	BOOL m_bButtonSts;
	BOOL m_bPrevButtonSts;
	BOOL m_bButtonChg;

	int  m_nCrateSts;
	BOOL m_bEmptyDest;
	BOOL m_bFullDest;

	BOOL m_bEndTrnSta;
	
	CString m_strShiftNo;
	int     m_nSftNo;
	int     m_nPreNo;

	struct sc_history {
	    int    m_nJobStartTime;
		int    m_nErrStartTime;
        struct time_info {
			int     m_nTrnSta;
            int     m_nJobTime;
            int     m_nErrTime;
            int     m_nWorkCnt;
		    int     m_nAvgTime;
		    int     m_nLongTime;
		} TimeInfo[3];
	};

	struct  sc_history  ScHis[SC_CNT];
	
// operations
public:
	CJobItem* FetchByJobPattern(int nJobPattern, int nScNum, int nExceptLuggNum = 0);
	BOOL FetchByJobRetrieve(int nScNum, CJobItem**, CJobItem**);

	BOOL FetchLowLevelRetrive(CJobItem* pJobItem);
	BOOL FetchLowBatchRetrive(CJobItem* pJobItem, int nScNum);

	//CJobItem* FetchByJobRetrieve(int nScNum, int nExceptLuggNum = 0);
	CJobItem* FetchCvJobByJobPattern(int nJobPattern, int nScNum);
	CJobItem* FetchCvJobByStationNum(int nStatus, int nStationNum);
	CJobItem* FetchCvJobByStationNum2(int nJobType, int nStationNum);
	CJobItem* FetchCvJobByLuggNum(int nLuggNum);
	CJobItem* FetchCvJob(int nScNum, BOOL bFirstFork = TRUE);

	CJobItem* CJob::FetchCvJobByScNum(int nScNum, BOOL bFirstFork);

	void ChangeStatusByOrder(int nBatchNum);
	int  FetchCvJobByDestNum(int nStationNum);
	BOOL Invoke(int nLuggNum = 0);
	BOOL Invoke(CJobItem* pJobItem);
	BOOL Add(CJobItem* pJobItem);
	BOOL Add(int nLuggNum, int nJobType, CString strLocation, int nBatchNo, int nPalletNo, int nLevelNo, int nStartPos, int nDestPos, int nPriority = 100, CString strProductID = "", CString strSecondLoc = "", int nStatus = JOB_STA_NEW, CString strGrade = "", CString strQuantity = "", int nHeight = 0);
	BOOL AddSort(CJobItem* pJobItem);
	BOOL Remove(CJobItem* pJobItem);
	BOOL Remove(int nLuggNum);
	BOOL Load(CListCtrl* pListCtrl, int nJob, int nStatus);
	BOOL Restore();
	BOOL Backup();
	CJobItem* Find(int nLuggNum);
	CJobItem* FetchByStatus(int nStatus, int nScNum = -1);

	CJobItem* CJob::FetchByComple(int nStatus);

	CJobItem* FetchByJobType(int nJobType, int nScNum = -1, int nExceptLuggNum = 0);
	BOOL IsModified() { return m_bModified; };
	int GetNewLuggNum();
	int GetSeqLuggNum();
	//int GetNewSeqNo();
	BOOL Complete(int nLuggNum, int nScJobType = SC_JOB_TYPE_ANY);
	void PutOffMsg(char cMsgType, int nLuggNum=0, int nScJobType=SC_JOB_TYPE_ANY, int nDevKind=0, int nDevNo=0, int nErrKind=0, int nErrCode=0, CString strLocation="" );

	void ResetResultCount();
	void RemoveAllJob();
	int GetResultCount(int nScNum = -1);
	int GetJobCount(int nScNum = -1);

	/* BcrCode
	BOOL AddBcrBuff(CBcrBuff* pBcrBuff);
	BOOL AddBcrBuff(int nSeqNo, int nBcrNum, CString strBcrData, int nStatus);
	BOOL AddBcr(CBcrBuff* pBcrBuff);
	CBcrBuff* FindBcrBuff(int nBcrNum, int nStatus);
	CBcrBuff* FindBcrBuff(int nSeqNo);
	CBcrBuff* FindBcrBuff();
	void RemoveAllBcrJob();
	BOOL RemoveBcrJob(int nBcrNum);
	BOOL RemoveBcrJob(CBcrBuff* pBcrBuff);
	BOOL LoadBcrBuff(CListCtrl* pListCtrl, int nBcrNum);
	*/

// Implementation
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

class CMsg : public CObject
{
protected:
	DECLARE_SERIAL(CMsg);
// Construction
public:
	CMsg();
	CMsg(char cMsgType, int nLuggNum, int nScJobType, int nDevKind, int nDevNo, int nErrKind, int nErrCode, CString strLocation );

// Attributes
public:
	BOOL m_bNew;
	char m_MsgType;
	int  m_nLuggNum;
	int  m_nScJobType;
	int	 m_nDevKind;
	int  m_nDevNo;
	int  m_nErrKind;
	int  m_nErrCode;
	CString m_strLocation;

// Operations

// Implementation
public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

#endif // __JOB_H__
