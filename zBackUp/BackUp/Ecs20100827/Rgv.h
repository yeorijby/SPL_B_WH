
#pragma once

#include "Melsec.h"

class CRgv : public CMelsec
{
public:
	CRgv() : CMelsec() {};
	CRgv(int nNum, CEcsDoc* pDoc);


public:
	CEcsDoc* m_pDoc;
	int m_nNum;
	int m_nWareHouse;

	CString m_strDevice;

	CRgvInfo *m_pRgvInfo;
	CConveyorTrackInfo *m_pConveyorTrackInfo;

	int m_nCount;

	time_t	m_tJobStart;
	time_t	m_tJobEnd;
	time_t	m_tErrorStart;
	time_t	m_tErrorEnd;
	BOOL    m_bIsError;

public:
	int  ReadStatus();
	void InvokeCheck();

	BOOL StoreRoutine();
	BOOL StoreRoutine(int nRank);

	BOOL StoreSiteRoutine();
	BOOL StoreSiteRoutine(int nRank);
	
	BOOL RetrieveRoutine();
	BOOL RetrieveRoutine(int nRank);

	BOOL RetrieveSiteRoutine();
	BOOL RetrieveSiteRoutine(int nRank);

	void CompleteCheck();
	void ErrorCheck();
	int  CommandProc(SRgvMsg* pRgvMsg);

	int  HsToHs(int nLuggNum, int nHsNumFrom, int nHsNumTo);

	int  CallToHome();

	int  EStop();
	int  Active();
	int  Stop();
	int  Reset();
	int  Delete();

	int  GetBank(CString strLocation);
	int  GetSide(CString strLocation);
	int  GetBay(CString strLocation);

	void StatisticWorkTime(CMoveJobItem *pMoveJobItem);
	void StatisticTroubleTime();

public:
//	void EnterBlcokingSection();
//	void LeaveBlcokingSection();
//	BOOL CanBlockingJobStartNow();
//	void ChangeBlockingRoutine();


public:
	int  GetRgvPosPerTrack(int nTrackNum);
	BOOL IsInvoke();

	CMoveJobItem* CheckStartStation(int nRank, int nStartTrack);

	BOOL IsRetPalletValid(CMoveJobItem *pMoveJobItem, int nRank, int nTrackNum);

	int GetSiteToSiteScCount();


	int GetLogID();

};


