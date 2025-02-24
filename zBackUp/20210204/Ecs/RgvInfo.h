
#pragma once

#include "Info.h"
//#include "StackerInfo.h"
#include "EcsDef.h"


class CRgvInfo : public CInfo
{
protected:
	DECLARE_DYNCREATE(CRgvInfo)

// constructor & destructor
public:
	CRgvInfo() {};
	CRgvInfo(CEcsDoc* pDoc, CString strFileName, int nNum);
	~CRgvInfo();

public:
	int   m_nNum;

	int   m_nNextRtn;
	int   m_nStoNextRtn;
	int   m_nStoSiteNextRtn;
	int   m_nRetNextRtn;
	int   m_nRetSiteNextRtn;

	BOOL  m_bStoreSuspend;
	BOOL  m_bRetrieveSuspend;

	BYTE  m_ucMode;
	BYTE  m_ucStatus;
	BYTE  m_ucActive;

	WORD  m_wErrCode;
	WORD  m_wPrevErrCode;
	BYTE  m_ucHorizontalPos;
	
	BYTE  m_ucHorizontalPosSave;

	BOOL  m_bInvoke;
	int   m_nLuggNum;
	BYTE  m_ucJobType;
	BYTE  m_ucProdLoad;
	BYTE  m_ucTransaction;

	int   m_nInternalLuggNum;
	BYTE  m_ucInternalJobType;

	int   m_nInternalLuggNum2;
	BYTE  m_ucInternalJobType2;

	int   m_nStartTrack;
	int   m_nDestTrack;
	BYTE  m_ucStartPos;
	BYTE  m_ucDestPos;

	time_t	m_tJobStart;
	time_t	m_tJobEnd;
	time_t	m_tErrorStart;
	time_t	m_tErrorEnd;

	CString m_strDevice;

public:
	BOOL Restore();
	BOOL Backup();

public:
	CString GetRgvModeString();
	CString GetActiveString();
	CString GetHorizontalPosString();
	CString GetProdLoadString();
	CString GetCompleteString();

	CString GetRgvLuggNumString();
	CString GetEcsLuggNumString();
	CString GetRgvStatusString();

	CString GetEcsLuggNumString2();

	CString GetRgvJobTypeString();

	CString GetStartTrackString();
	CString GetDestTrackString();

	CString GetRgvErrorString();

	int GetID();


public:
//	void InvokeControl(CScControl *pRgv);
	COLORREF GetForkColor();
	COLORREF GetRailColor();
	COLORREF GetPostColor();

	void DisplayRgvStatusMsg();

//	void WriteStatusForHMI();


public:


// Implementation
public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};



