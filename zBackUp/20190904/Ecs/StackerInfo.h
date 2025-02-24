// ScInfo.h : Defines the class behaviors for the application.

#ifndef __SCINFO_H__
#define __SCINFO_H__

#include "Info.h"
#include "EcsDef.h"
#include <EcsEnv.h>

/*
class CEcsDoc;

class CInfo : public CObject
{
protected:
	DECLARE_DYNCREATE(CInfo)

// constructor & destructor
public:
	CInfo();
	CInfo(CEcsDoc* pDoc, CString strFileName);
	~CInfo();

// Attributes
	CEcsDoc* m_pDoc;
	CString m_strFileName;
	BOOL m_bModified;

// operations
public:
	BOOL Backup();
	BOOL Restore();

// Implementation
public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};
*/

class CStackerInfo : public CInfo
{
protected:
	DECLARE_DYNCREATE(CStackerInfo)

// constructor & destructor
public:
	CStackerInfo() {};
	CStackerInfo(CEcsDoc* pDoc, CString strFileName);
	~CStackerInfo() {};

// Attributes
	BOOL m_bStoreSuspend;
	BOOL m_bRetrieveSuspend;

	BYTE m_bInternalJobType;
	BYTE m_bSecondInternalJobType;

	uchar m_ucMode;
	uchar m_ucStatus;
	WORD  m_wErrCode;
	WORD  m_wPrevErrCode;
	WORD  m_wSaveErrCode;
	int   m_nHorizontalPos;
	int   m_nVerticalPos;
	uchar m_ucHorizontalPos;
	uchar m_ucVerticalPos;


	uchar  m_ucGen;
	uchar m_ucActive;
	uchar m_ucRcMode;
	uchar m_ucScMode;
	uchar m_ucPrevStatus;
	uchar m_ucFirstForkErrStatus;
	WORD  m_wForkJob;

	uchar m_ucJobType;
	uchar m_ucSecondJobType;
	int m_nLuggNum;
	int m_nSecondLuggNum;
	uchar m_ucProdLoad;
	uchar m_ucSecondProdLoad;
	uchar m_ucTransaction;
	uchar m_ucInternalTransaction;
	uchar m_ucSecondTransaction;

	int m_nInternalLuggNum;
	int m_nSecondInternalLuggNum;
	CString m_strLocationFrom;
	CString m_strSecondLocationFrom;
	CString m_strLocationTo;
	CString m_strSecondLocationTo;
	int m_nPrevRtn;
	int	m_nDirection;
	BOOL m_bConfirmed;

	time_t	m_tJobStart;
	time_t	m_tJobEnd;
	time_t	m_tErrorStart;
	time_t	m_tErrorEnd;

	BOOL m_bCvTransaction;

	BOOL m_bInvoke;
	BOOL m_bSecondInvoke;

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	int m_ucFirstForkPos;
/*	int m_nSecondForkPos;
	BOOL m_bSemiAutoJob;
	BOOL m_bRcpJob;
	BOOL m_bPowerBit;
	BOOL m_bLocMiss;
	WORD m_wErrCodeDetail;
	BYTE m_ucPhase;
	BYTE m_ucSensorSta;
	BOOL m_bHomeBit;
	BOOL m_bCenterBit;
	WORD m_wRejectCode;
*/
// operations
public:

// Implementation
public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

#endif // __SCINFO_H__
