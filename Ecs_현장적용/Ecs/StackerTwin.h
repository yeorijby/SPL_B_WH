// StackerTwin.h: interface for the CStackerTwin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STACKERTWIN_H__9DD18703_72FA_11D1_970A_006097933291__INCLUDED_)
#define AFX_STACKERTWIN_H__9DD18703_72FA_11D1_970A_006097933291__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PlcMelsec.h"

class CStacker : public CPlcMelsec
{

public:
	CStacker() : CPlcMelsec() {};
	CStacker(int nNum, CEcsDoc* pDoc);

// Attributes
protected:
public:
	CEcsDoc* m_pDoc;
	int m_nNum;
	BOOL	m_bIsError;

// operations
public:
	virtual BOOL IsInvoke();
	virtual BOOL StoreRoutine();
	virtual BOOL RetrieveRoutine();
	virtual BOOL RackToRackRoutine();
	virtual BOOL ErrorRoutine();
	uchar GetSide(CString strLocation);
	uchar GetBank(CString strLocation);
	uchar GetBay(CString strLocation);
	uchar GetLevel(CString strLocation);
	virtual int ReadStatus();
	virtual int CommandProc(SStackerMsg* pStackerMsg);
	virtual int Store(int nLuggNum1, CString strLocation1, int nLuggNum2, CString strLocation2, int nHsNum, char bUseFork);
	virtual int Retrieve(int nLuggNum1, CString strLocation1, int nLuggNum2, CString strLocation2, int nHsNum, char bUseFork);
	virtual int HsToHs(int nLuggNum1, int nLuggNum2, int nHsNumFrom, int nHsNumTo, char bUseFork);
	virtual int RackToRack(int nLuggNum1, CString strLocFrom1, CString strLocTo1, int nLuggNum2, CString strLocFrom2, CString strLocTo2, char bUseFork);
	virtual int CallToHome(int nLuggNum);

	virtual int ErrorReset();
	virtual int Active();
	virtual int Estop();
	virtual int Stop();

	virtual void InvokeCheck();
	virtual void ErrorCheck();
	virtual void CompleteCheck();

	void  StatisticWorkTime(CJobItem *pJobItem);

	void  ScDiagnosis();
	void  ScJobStart();
	void  ScJobAdd(int Count);

	void  ScErrorLog(int nMode, WORD wErrCode);


	BOOL AdjustableRetrieve(CJobItem *pJobItem, CJobItem *pSecondJobItem);

// Overrides
};

#endif // !defined(AFX_STACKERTWIN_H__9DD18703_72FA_11D1_970A_006097933291__INCLUDED_)
