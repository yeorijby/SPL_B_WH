// MoveJob.h : Defines the class behaviors for the application.
#ifndef __MOVEJOB_H__
#define __MOVEJOB_H__


#include <afxmt.h>
#include "EcsDef.h"
#include <EcsEnv.h>
#include "Job.h"

/*
class CCriticalSectionEx : public CCriticalSection
{
public:
	CCriticalSectionEx() {};
	CCriticalSectionEx(const CCriticalSectionEx& cs) {};
};
*/

class CMoveJobItem : public CObject
{
protected:
	DECLARE_SERIAL(CMoveJobItem)

// constructor & destructor
public:
	CMoveJobItem() { m_bLock = FALSE; };
	CMoveJobItem(int nLuggNum, int nJobType, CString strLocation, int nBatchNo, int nPalletNo, int nLevelNo, int nStartPos, int nDestPos, int nPriority = 100, CString strProductID = "", CString strSecondLoc = "", int nStatus = JOB_STA_NEW, CString strGrade = "", CString strQuantity = "", int nHeight = -1, int nLineNum = 0, int nLastPallet = 0);

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

	int m_nLineNum;
	int m_nLastPallet;

	int m_nTwinJob;

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
	CString GetDestPos(int nLineNum);
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

//#define	JOB_PROGRESS_DRAW		1
//#define	JOB_RESULT_DRAW			2

class CEcsDoc;
class CMoveJob : public CObject
{
protected:
	DECLARE_DYNCREATE(CMoveJob)

	static CCriticalSectionEx m_csMoveJobAdd;
 
// constructor & destructor
public:
	CMoveJob() {};
	CMoveJob(CEcsDoc* pDoc);
	~CMoveJob();

// Attributes
protected:

public:
	CEcsDoc* m_pDoc;
	CObList m_MoveJobList;
	CObList m_MoveMsgList;
	CString	m_strFileName;
	BOOL m_bModified;
	BOOL m_bIsOfflineJob;
	int m_nResultCount[SC_CNT];
	int m_nScRetCount[SC_CNT];
	int	m_nLuggNum;
	int m_nEntryCnt;
	int m_nRetCnt;

	
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

	BOOL Invoke(int nLuggNum = 0);
	BOOL Invoke(CMoveJobItem* pMoveJobItem);
	BOOL Add(CMoveJobItem* pMoveJobItem);
	BOOL Add(int nLuggNum, int nJobType, CString strLocation, int nBatchNo, int nPalletNo, int nLevelNo, int nStartPos, int nDestPos, int nPriority = 100, CString strProductID = "", CString strSecondLoc = "", int nStatus = JOB_STA_NEW, CString strGrade = "", CString strQuantity = "", int nHeight = 0, int nLineNum =0, int nLastPallet = 0);
	BOOL AddSort(CMoveJobItem* pMoveJobItem);
	BOOL Remove(CMoveJobItem* pMoveJobItem);
	BOOL Remove(int nLuggNum);
	BOOL Load(CListCtrl* pListCtrl, int nJob, int nStatus);
	BOOL Restore();
	BOOL Backup();
	int GetSeqLuggNum();
	int MoveGetSeqLuggNum();
	CMoveJobItem* Find(int nLuggNum);
	void FindChange(int nLuggNum1, int nLuggNum2, int nStatus);
	CMoveJobItem* FetchByStatus(int nStatus, int nScNum = -1);
    CMoveJobItem* FetchRgvJobByDestTrack(int nTrackNum);
	CMoveJobItem* FetchRgvJobByDestTrack2(int nTrackNum, int nLuggNum);
	CMoveJobItem* FetchCvRgvInvokeCheck(int nLuggNum);
    CMoveJobItem* FetchCvJobByStationNum(int nStatus, int nStationNum);

	BOOL FetchRgvJobRetrieve(int nTrackNum, CMoveJobItem** pFetchJobItem1, CMoveJobItem** pFetchJobItem2);
	int	 RtvCvCountCheck(int nSetLine, int nLineSeq);
	BOOL BufferCvCountLock(int nSetLine, int nLineSeq);

	BOOL IsModified() { return m_bModified; };

// Implementation
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

#endif // __MOVEJOB_H__
