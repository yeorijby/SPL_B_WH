
#pragma once

#include "Melsec3E.h"

class CScQ : public CMelsecSc3E
{
public:
	CScQ(int nNum, CEcsDoc* pDoc, CScSocket *pSock);

public:
	CEcsDoc* m_pDoc;
	int m_nNum;
	CString m_strDevice;

	CStackerInfo *m_pStackerInfo;
	CConveyorTrackInfo *m_pConveyorTrackInfo;

	int  m_nCount;

protected:
	time_t	m_tJobStart;
	time_t	m_tJobEnd;
	time_t	m_tErrorStart;
	time_t	m_tErrorEnd;
	BOOL    m_bIsError;


public:

	virtual BOOL IsInvoke();
	BOOL StoreRoutine();
	BOOL RetrieveRoutine();
	BOOL RackToRackRoutine();
	BOOL ErrorRoutine();

	int  ReadStatus();
	int  CommandProc(SStackerMsg* pStackerMsg);
	int Store(int nLuggNum1, CString strLocation1, int nLuggNum2, CString strLocation2, int nHsNum, char bUseFork, int nSize);
	int Retrieve(int nLuggNum1, CString strLocation1, int nLuggNum2, CString strLocation2, int nHsNum, char bUseFork, int nSize);
	int HsToHs(int nLuggNum1, int nLuggNum2, int nHsNumFrom, int nHsNumTo, char bUseFork, int nSize);
	int RackToRack(int nLuggNum1, CString strLocFrom1, CString strLocTo1, int nLuggNum2, CString strLocFrom2, CString strLocTo2, char bUseFork, int nSize);
	int CallToHome();

	int Reset();
	int Active();
	int Stop();
	int Pause();

	void InvokeCheck();
	void ErrorCheck();
	void CompleteCheck();

	int Delete(BOOL bFirst = TRUE);
	int RcMode(BOOL bOnLine);

protected:
	BYTE GetSide(CString strLocation);
	BYTE GetBank(CString strLocation);
	BYTE GetBay(CString strLocation);
	BYTE GetLevel(CString strLocation);

protected:
	void StatisticWorkTime(CJobItem *pJobItem);
	void StatisticTroubleTime();

};

