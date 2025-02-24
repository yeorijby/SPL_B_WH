// Job.cpp : implementation of the CJob class
//

#include "stdafx.h"
#include "Job.h"
#include "EcsDoc.h"
#include "Ecs.h"
#include "Lib.h"

#define	LOG			m_pDoc->m_pLog

IMPLEMENT_DYNCREATE(CJob, CObject)

CCriticalSectionEx CJob::m_csJobAdd = CCriticalSectionEx();

CJob::CJob(CEcsDoc* pDoc) 
{ 
	m_pDoc = pDoc;
	//m_strFileName = "..\\Temp\\Job.Ecs";
	m_strFileName = "..\\Job\\Job.Ecs";
	m_bModified = FALSE;
	m_bIsOfflineJob = FALSE;
	m_bSwitchChg = FALSE;
	m_bButtonChg = FALSE;

	ResetResultCount();

	if (m_nScOrderNo < 0)   m_nScOrderNo = 0;
	if (m_nCvOrderNo < 0)   m_nCvOrderNo = 0;
	if (m_nPrevOrderNo < 0) m_nPrevOrderNo = 0;
	if (m_nOppOrderNo < 0)  m_nOppOrderNo = 0;
	for (int i=0; i<SC_CNT; i++)
	{
		if (ScHis[i].m_nJobStartTime < 0) ScHis[i].m_nJobStartTime = 0;
	    if (ScHis[i].m_nErrStartTime < 0) ScHis[i].m_nErrStartTime = 0;
		for (int j=0; j<3; j++) 
		{
			if (ScHis[i].TimeInfo[j].m_nTrnSta < 0) ScHis[i].TimeInfo[j].m_nTrnSta = 0;
		    if (ScHis[i].TimeInfo[j].m_nJobTime < 0) ScHis[i].TimeInfo[j].m_nJobTime = 0;
			if (ScHis[i].TimeInfo[j].m_nErrTime < 0) ScHis[i].TimeInfo[j].m_nErrTime = 0;
			if (ScHis[i].TimeInfo[j].m_nWorkCnt < 0) ScHis[i].TimeInfo[j].m_nWorkCnt = 0;
	        if (ScHis[i].TimeInfo[j].m_nAvgTime < 0) ScHis[i].TimeInfo[j].m_nAvgTime = 0;
			if (ScHis[i].TimeInfo[j].m_nLongTime < 0) ScHis[i].TimeInfo[j].m_nLongTime = 0;
		}
	}
}

CJob::~CJob()
{
	for (POSITION pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		delete m_JobList.GetNext(pos);
	}
	m_JobList.RemoveAll();

	for ( pos = m_MsgList.GetHeadPosition(); pos != NULL;)
	{
		delete m_MsgList.GetNext(pos);
	}
	m_MsgList.RemoveAll();

}

void CJob::Serialize(CArchive& ar)
{

	m_JobList.Serialize(ar);
	m_MsgList.Serialize(ar);

	if (ar.IsStoring())
	{
		for ( int i = 0; i < SC_CNT; i++ )
		{
			ar << m_nResultCount[i];
			ar << m_nScRetCount[i];
		}
		ar << m_nLuggNum;
		ar << m_bIsOfflineJob;
		ar << m_nEntryCnt;
		ar << m_nRetCnt;
		ar << m_nScOrderNo;
		ar << m_nScOrderCnt;
		ar << m_nCvOrderNo;
		ar << m_nCvOrderCnt;
		ar << m_nPrevOrderNo;
		ar << m_nBcrOrderNo;
		ar << m_nBcrOrderCnt;
		ar << m_nOppOrderNo;
		ar << m_bEndTrnSta;
		ar << m_bPrevSwitchSts;
		ar << m_bPrevButtonSts;
		ar << m_strShiftNo;
		ar << m_nSftNo;
		ar << m_nPreNo;

		ar << m_pDoc->m_n4GroupInternalBatch;
		ar << m_pDoc->m_n4GroupInternalPallet;

		ar << m_pDoc->m_n5GroupInternalBatch;
		ar << m_pDoc->m_n5GroupInternalPallet;

		ar << m_pDoc->m_n6GroupInternalBatch;
		ar << m_pDoc->m_n6GroupInternalPallet;

		ar << m_pDoc->m_n4goupBuffCouter;
		ar << m_pDoc->m_n5goupBuffCouter;
		ar << m_pDoc->m_n6goupBuffCouter;

		ar << m_pDoc->m_bWriteTroubleCheck;
		ar << m_pDoc->m_bJobStopCheck;

//		ar << m_pDoc->m_n4GroupCvCount;
//		ar << m_pDoc->m_n5GroupCvCount;
//		ar << m_pDoc->m_n6GroupCvCount;

//		ar << m_pDoc->m_b4groupCheck;
//		ar << m_pDoc->m_b5groupCheck;
//		ar << m_pDoc->m_b6groupCheck;

		for (i=0; i<SC_CNT; i++)
		{
			ar << ScHis[i].m_nJobStartTime;
		    ar << ScHis[i].m_nErrStartTime;
			for (int j=0; j<3; j++) 
			{
				ar << ScHis[i].TimeInfo[j].m_nTrnSta;
			    ar << ScHis[i].TimeInfo[j].m_nJobTime;
				ar << ScHis[i].TimeInfo[j].m_nErrTime;
				ar << ScHis[i].TimeInfo[j].m_nWorkCnt;
		        ar << ScHis[i].TimeInfo[j].m_nAvgTime;
				ar << ScHis[i].TimeInfo[j].m_nLongTime;
			}
		}
	}
	else
	{
		for ( int i = 0; i < SC_CNT; i++ )
		{
			ar >> m_nResultCount[i];
			ar >> m_nScRetCount[i];
		}
		ar >> m_nLuggNum;
		ar >> m_bIsOfflineJob;
		ar >> m_nEntryCnt;
		ar >> m_nRetCnt;
		ar >> m_nScOrderNo;
		ar >> m_nScOrderCnt;
		ar >> m_nCvOrderNo;
		ar >> m_nCvOrderCnt;
		ar >> m_nPrevOrderNo;
		ar >> m_nBcrOrderNo;
		ar >> m_nBcrOrderCnt;
		ar >> m_nOppOrderNo;
		ar >> m_bEndTrnSta;
		ar >> m_bPrevSwitchSts;
		ar >> m_bPrevButtonSts;
		ar >> m_strShiftNo;
		ar >> m_nSftNo;
		ar >> m_nPreNo;

		ar >> m_pDoc->m_n4GroupInternalBatch;
		ar >> m_pDoc->m_n4GroupInternalPallet;

		ar >> m_pDoc->m_n5GroupInternalBatch;
		ar >> m_pDoc->m_n5GroupInternalPallet;

		ar >> m_pDoc->m_n6GroupInternalBatch;
		ar >> m_pDoc->m_n6GroupInternalPallet;

		ar >> m_pDoc->m_n4goupBuffCouter;
		ar >> m_pDoc->m_n5goupBuffCouter;
		ar >> m_pDoc->m_n6goupBuffCouter;

		ar >> m_pDoc->m_bWriteTroubleCheck;

		ar >> m_pDoc->m_bJobStopCheck;

//		ar >> m_pDoc->m_n4GroupCvCount;
//		ar >> m_pDoc->m_n5GroupCvCount;
//		ar >> m_pDoc->m_n6GroupCvCount;

//		ar >> m_pDoc->m_b4groupCheck;
//		ar >> m_pDoc->m_b5groupCheck;
//		ar >> m_pDoc->m_b6groupCheck;

		if (m_nScOrderNo < 0)   m_nScOrderNo = 0;
		if (m_nCvOrderNo < 0)   m_nCvOrderNo = 0;
		if (m_nPrevOrderNo < 0) m_nPrevOrderNo = 0;
		if (m_nOppOrderNo < 0)  m_nOppOrderNo = 0;

		for (i=0; i<SC_CNT; i++)
		{
			ar >> ScHis[i].m_nJobStartTime;
		    ar >> ScHis[i].m_nErrStartTime;
			if (ScHis[i].m_nJobStartTime < 0) ScHis[i].m_nJobStartTime = 0;
		    if (ScHis[i].m_nErrStartTime < 0) ScHis[i].m_nErrStartTime = 0;
			for (int j=0; j<3; j++) 
			{
				ar >> ScHis[i].TimeInfo[j].m_nTrnSta;
			    ar >> ScHis[i].TimeInfo[j].m_nJobTime;
				ar >> ScHis[i].TimeInfo[j].m_nErrTime;
				ar >> ScHis[i].TimeInfo[j].m_nWorkCnt;
		        ar >> ScHis[i].TimeInfo[j].m_nAvgTime;
				ar >> ScHis[i].TimeInfo[j].m_nLongTime;

				if (ScHis[i].TimeInfo[j].m_nTrnSta < 0) ScHis[i].TimeInfo[j].m_nTrnSta = 0;
			    if (ScHis[i].TimeInfo[j].m_nJobTime < 0) ScHis[i].TimeInfo[j].m_nJobTime = 0;
				if (ScHis[i].TimeInfo[j].m_nErrTime < 0) ScHis[i].TimeInfo[j].m_nErrTime = 0;
				if (ScHis[i].TimeInfo[j].m_nWorkCnt < 0) ScHis[i].TimeInfo[j].m_nWorkCnt = 0;
		        if (ScHis[i].TimeInfo[j].m_nAvgTime < 0) ScHis[i].TimeInfo[j].m_nAvgTime = 0;
				if (ScHis[i].TimeInfo[j].m_nLongTime < 0) ScHis[i].TimeInfo[j].m_nLongTime = 0;
			}
		}
	}
}

// JobItem Class
/////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CJobItem, CObject, 0)

CJobItem::CJobItem(int nLuggNum, int nJobType, CString strLocation, int nBatchNo, int nPalletNo, int nLevelNo, int nStartPos, int nDestPos, int nPriority, CString strProductID, CString strSecondLoc, int nStatus, CString strGrade, CString strQuantity, int nHeight)
{
	m_nLuggNum     = nLuggNum;
	m_nJobType     = nJobType;
	m_strGrade     = strGrade;
	m_strProductID = strProductID;
	m_strQuantity  = strQuantity;
	m_nStartPos    = nStartPos;
	m_nDestPos     = nDestPos;
	m_strLocation  = strLocation;
	m_strSecondLoc = strSecondLoc;
	m_nHeight	   = nHeight;
	m_nPriority    = nPriority;
	m_nStatus      = nStatus;
	m_nErrCode     = JOB_ERR_NONE;

	m_nBatchNo = nBatchNo;
	m_nPalletNo = nPalletNo; 
	m_nLevelNo = nLevelNo;

	m_nDestTrack   = 0;

	m_tTimeStamp   = time(NULL);

	m_bFirstFork = TRUE;
	m_bLock = FALSE;
}

void CJobItem::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_nLuggNum;
		ar << m_nJobType;
		ar << m_strGrade;
		ar << m_strQuantity;
		ar << m_strProductID;
		ar << m_strLocation;
		ar << m_strSecondLoc;
		ar << m_nStartPos;
		ar << m_nDestPos;
		ar << m_nHeight;
		ar << m_nPriority;
		ar << m_nStatus;
		ar << m_nErrCode;
		ar << m_bFirstFork;

		ar << m_nBatchNo;
		ar << m_nPalletNo;
		ar << m_nLevelNo;

		ar << m_tTimeStamp;
	}
	else
	{
		ar >> m_nLuggNum;
		ar >> m_nJobType;
		ar >> m_strGrade;
		ar >> m_strQuantity;
		ar >> m_strProductID;
		ar >> m_strLocation;
		ar >> m_strSecondLoc;
		ar >> m_nStartPos;
		ar >> m_nDestPos;
		ar >> m_nHeight;
		ar >> m_nPriority;
		ar >> m_nStatus;
		ar >> m_nErrCode;
		ar >> m_bFirstFork;

		ar >> m_nBatchNo;
		ar >> m_nPalletNo;
		ar >> m_nLevelNo;

		ar >> m_tTimeStamp;
	}
}

CString CJobItem::GetLuggNumString()
{
	CString strTemp;
	strTemp.Format("%.4d", m_nLuggNum);

	return strTemp;
}

CString CJobItem::GetTimeStampString()
{
	CTime theTime(m_tTimeStamp);
	CString strTemp = theTime.Format( "%Y/%m/%d/ %H:%M:%S" );

	return strTemp;
}

CString CJobItem::GetBatchNoString()
{
	CString strTemp;
	strTemp.Format("%.4d", m_nBatchNo);

	return strTemp;
}

CString CJobItem::GetPriorityString()
{
	CString strTemp;
	strTemp.Format("%d", m_nPriority);

	return strTemp;
}

CString CJobItem::GetType()
{
	return GetType(m_nJobType);
}

CString CJobItem::GetType(int nType)
{
	return CLib::ConvertJobTypeToString(nType);
}

CString CJobItem::GetStartPos()
{
	return GetStartPos(m_strLocation, m_nStartPos, m_nJobType);
}

CString CJobItem::GetStartPos(CString strLocation, int nStartPos, int nJobType)
{
	switch ( nJobType )
	{
	case	JOB_TYPE_UNIT_RET:
	case	JOB_TYPE_MANUAL_RET:
	case  JOB_TYPE_RACK_TO_RACK:
		return CLib::ConvertLocationToCustom(strLocation);
	}

	if (GetStackerNum() < SC_1_CNT)
	{
		switch (nStartPos)
		{
		case	IMS_ECS_STO_STATION_100:
			return CString("생산입고대");
		case	IMS_ECS_STO_STATION_101:
			return CString("외주입고대");

		case	111:
			return CString("1:페스츄리2호 1번라인");
		case	112:
			return CString("2:페스츄리2호 2번라인");
		case	113:
			return CString("3:페스츄리3호");
		case	114:
			return CString("4:페스츄리수동");
		case	115:
			return CString("5:찹쌀도넛1호");
		case	116:
			return CString("6:찹쌀도넛2호");
		case	117:
			return CString("7:식빵");
		case	118:
			return CString("8:찰도넛(모찌)");
		case	119:
			return CString("9:1층 냉동샌드위치");
		case	120:
			return CString("10:성형과자1호");
		case	121:
			return CString("11:성형과자2호");
		case	122:
			return CString("12:성형과자4호");
		case	123:
			return CString("13:성형과자3호");
		case	124:
			return CString("14:1층 머랭");
		case	125:
			return CString("15:성형바게트 15라인");
		case	126:
			return CString("16:성형바게트 16라인");
		case	127:
			return CString("17:파베이크 17라인");
		case	128:
			return CString("18:파베이크 18라인");

		default:
			CString strTemp;
			strTemp.Format("DEF(%d)", nStartPos);
			return strTemp;
		}
	}

	CString strTemp;
	strTemp.Format("DEF(%d)", nStartPos);
	return strTemp;
}

CString CJobItem::GetDestPos()
{
	return GetDestPos(m_strLocation, m_strSecondLoc, m_nDestPos, m_nJobType);
}

CString CJobItem::GetDestPos(CString strLocation, CString strSecondLoc, int nDestPos, int nType)
{
	switch ( nType )
	{
	case	JOB_TYPE_UNIT_STO:
	case	JOB_TYPE_MANUAL_STO:
		return CLib::ConvertLocationToCustom(strLocation);
	default:
		break;
	}

	switch (nDestPos)
	{
//	case	IMS_ECS_RET_STATION_200:
//		return CString("출하분류대");
	case	IMS_ECS_RET_STATION_201:
		return CString("출하분류대#1");
	case	IMS_ECS_RET_STATION_202:
		return CString("출하분류대#2");
	case	IMS_ECS_RET_STATION_203:
		return CString("출하분류대#3");
	case	IMS_ECS_RET_STATION_204:
		return CString("출하분류대");
	case	IMS_ECS_RET_STATION_251:
		return CString("외주출고대");
	case	IMS_ECS_RET_STATION_255:
		return CString("출하이동대");
	default:
		CString strTemp;
		strTemp.Format("DEF(%d)", nDestPos);
		return strTemp;
	}

/*	if(GetStackerNum() < SC_1_CNT)
	{
		switch (nDestPos)
		{
		case	ECS_POS_HS_1:
			return CString("S/C#1 H/S");
		case	ECS_POS_HS_2:
			return CString("S/C#2 H/S");
		case	ECS_POS_HS_3:
			return CString("S/C#3 H/S");
		case	ECS_POS_HS_4:
			return CString("S/C#4 H/S");
		case	ECS_POS_HS_5:
			return CString("S/C#5 H/S");
		case	ECS_POS_HS_6:
			return CString("S/C#6 H/S");
		case	IMS_ECS_RET_STATION_200:
			return CString("외주출고대");
		case	IMS_ECS_RET_STATION_201:
			return CString("출하분류대#1");
		case	IMS_ECS_RET_STATION_202:
			return CString("출하분류대#2");
		case	IMS_ECS_RET_STATION_203:
			return CString("출하분류대#3");
		default:
			CString strTemp;
			strTemp.Format("DEF(%d)", nDestPos);
			return strTemp;
		}
	}
*/

	CString strTemp;
	strTemp.Format("DEF(%d)", nDestPos);
	return strTemp;
}

int CJobItem::GetPattern()
{
	return GetPattern(m_nJobType);
}

int CJobItem::GetPattern(int nJobType)
{
	return CLib::ConvertJobTypeToPattern(nJobType);
}

BOOL CJobItem::IsError()
{
	return IsError(m_nStatus);
}

BOOL CJobItem::IsError(int nStatus)
{
	switch (nStatus)
	{
	case	JOB_STA_ERR:
	case	JOB_STA_REFUSE_COMPLETE:
	case	JOB_STA_REFUSE_CANCEL:
	case	JOB_STA_REFUSE_ARRIVED:
	case	JOB_STA_REFUSE_ERROR:
		return TRUE;
	default:
		return FALSE;
	}
}

BOOL CJobItem::IsOffLineJob()
{
	if( m_nJobType == JOB_TYPE_MANUAL_STO || m_nJobType == JOB_TYPE_RACK_TO_RACK || m_nJobType == JOB_TYPE_MANUAL_STN_TO_STN )
		return TRUE;

	return FALSE;
}

CString CJobItem::GetStatus()
{
	return GetStatus(m_nStatus);
}

CString CJobItem::GetStatus(int nStatus)
{
	switch (nStatus)
	{
	case	JOB_STA_ALL:					// 0
		return CString("전체");
	case	JOB_STA_NEW:					// 1
		return CString("신규");
	case	JOB_STA_CV_NEW:					// 2
		return CString("C/V 신규 작업");
	case	JOB_STA_ERR:					// 3
		return CString("에러");

	case	JOB_STA_SC_OPER_REQUEST:		// 5
		return CString("S/C 작업 대기");
	case	JOB_STA_SC_OPER_INVOKE:			// 6
		return CString("S/C 작업중");
	case	JOB_STA_CV_OPER_REQUEST:		// 7
		return CString("C/V 구동 대기");
	case	JOB_STA_CV_OPER_INVOKE:			// 8
		return CString("C/V 구동중");

/*	case	JOB_STA_RGV_OPER_REQUEST:		// 9
		return CString("RTV 구동 지시");
	case	JOB_STA_RGV_OPER_INVOKE:		// 10
		return CString("RTV 구동중");
	case	JOB_STA_RGV_OPER_COMPLETE:		// 11
		return CString("RTV 작업 완료");
*/

	case	JOB_STA_COMPLETE_REQUEST:		// 12
		return CString("완료 승인 요청");
	case	JOB_STA_COMPLETE:				// 13
		return CString("완료 응답 대기");


	case	JOB_STA_ERR_DUAL_STO_REQUEST:	// 18
		return CString("이중입고 보고요청");
	case	JOB_STA_ERR_DUAL_STO:			// 19
		return CString("이중입고 에러");
	case	JOB_STA_DUAL_STO_RETRY:			// 20
		return CString("이중입고 재지정");
	case	JOB_STA_ERR_EMPTY_RET_REQUEST:	// 21
		return CString("공출고 보고요청");
	case	JOB_STA_ERR_EMPTY_RET:			// 22
		return CString("공출고 에러");
	case	JOB_STA_EMPTY_RET_RETRY:		// 23
		return CString("공출고 재지정");
	case	JOB_STA_DUAL_RTR_RETRY:			// 24
		return CString("랙투랙 이중입고 재지정");
	case	JOB_STA_EMPTY_RTR_RETRY:		// 25
		return CString("랙투랙 공출고 재지정");

	case	JOB_STA_REFUSE_COMPLETE:		// 26
		return CString("완료 보고 이상");
	case	JOB_STA_REFUSE_ARRIVED:			// 27
		return CString("도착 보고 이상");
	case	JOB_STA_REFUSE_CANCEL:			// 28
		return CString("취소 보고 이상");

	case	JOB_STA_REFUSE_ERROR:			// 30
		return CString("에러 보고 이상");
	case	JOB_STA_ERR_REPORT:				// 31
		return CString("에러 보고");
	case    JOB_STA_CV_MOVE_RET_STATION:
		return CString("CV#330 -> 출하 분류대로 이동중");

	default:
		CString strTemp;
		strTemp.Format("DEF(%d)", nStatus);
		return strTemp;
	}

}

CString CJobItem::GetHeight()
{
	return GetHeight(m_nHeight);
}

CString CJobItem::GetHeight(int nHeight)
{
	switch (nHeight)
	{
	case	-1:
	case	TURN_NONE:
		return CString("정보없음");
	case	TURN_LEFT:
		return CString("좌측");
	case	TURN_RIGHT:
		return CString("우측");
	default:
		CString strTemp;
		strTemp.Format("DEF(%d)", nHeight);
		return strTemp;
	}
}

int CJobItem::GetBlock()
{
	return GetBlock(m_strLocation);
}

int CJobItem::GetSecondBlock()
{
	return GetBlock(m_strSecondLoc);
}

int CJobItem::GetBlock(CString strLocation)
{
	int nLevel = atoi(strLocation.Mid(5, 2));

	if (nLevel <= 3)
		return BLOCK_HIGHEST;
	else if (nLevel <= 7)
		return BLOCK_HIGH;
	else if (nLevel >= 13)
		return BLOCK_LOW;
	else
		return BLOCK_LOWEST;
}

int CJobItem::GetStackerNum()
{
	return GetStackerNum(m_strLocation);
}

int CJobItem::GetStackerNum(CString strLocation)
{
	return CLib::GetStackerNum(strLocation);
}

int CJobItem::GetBank()
{
	return GetBank(m_strLocation);
}

int CJobItem::GetBank(CString strLocation)
{
	return CLib::GetBank(strLocation);
}

int CJobItem::GetBay()
{
	return GetBay(m_strLocation);
}

int CJobItem::GetBay(CString strLocation)
{
	return CLib::GetBay(strLocation);
}

int CJobItem::GetLevel()
{
	return GetLevel(m_strLocation);
}

int CJobItem::GetLevel(CString strLocation)
{
	return CLib::GetLevel(strLocation);
}

CString CJobItem::GetErrInfo()
{
	return GetErrInfo(m_nErrCode);
}

CString CJobItem::GetErrInfo(int nErrCode)
{
	if (nErrCode > 0)
	{
		CString strErrInfo;
		strErrInfo.Format("%d", nErrCode);
		return strErrInfo;
	}

	switch (nErrCode)
	{
	case	JOB_ERR_NONE:
		return CString("");
	default:
		return CString("");
	}
}

BOOL CJobItem::IsValidLocation()
{
	return IsValidLocation(m_strLocation);
}

BOOL CJobItem::IsValidLocation(CString strLocation)
{
	return CLib::IsValidLocation(strLocation);
}

BOOL CJobItem::IsManualJob()
{
	if ( m_nJobType == JOB_TYPE_MANUAL_STO ||
	     m_nJobType == JOB_TYPE_MANUAL_RET ||
		 m_nJobType == JOB_TYPE_MANUAL_RTR ||
		 m_nJobType == JOB_TYPE_MANUAL_STN_TO_STN )
		 return TRUE;
	return FALSE;
}

BOOL CJob::Load(CListCtrl* pListCtrl, int nJobType, int nStatus)
{
	POSITION pos;
	CJobItem* pJobItem;
	LV_ITEM lvitem;
	char szBuff[256];
	int i = 0;


	pListCtrl->DeleteAllItems();

	lvitem.iItem = 0;
	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		int nGroup = 0;
		if(pJobItem->m_nJobType == JOB_TYPE_UNIT_RET || pJobItem->m_nJobType == JOB_TYPE_MANUAL_RET || 
			pJobItem->m_nJobType == JOB_TYPE_RACK_TO_RACK)
		{
			switch(pJobItem->m_nDestPos)
			{
				case	IMS_ECS_RET_STATION_201:	nGroup = 13; break;
				case	IMS_ECS_RET_STATION_202:	nGroup = 14; break;
				case	IMS_ECS_RET_STATION_203:	nGroup = 15; break;
				case	IMS_ECS_RET_STATION_255:	nGroup = 16; break;
			}
		}

		if(nJobType < JOB_TYPE_CNT) {
			if (nJobType != JOB_TYPE_ALL && nJobType != pJobItem->m_nJobType)
				continue;
		}
		else
		{
			if (nJobType != JOB_TYPE_ALL && nJobType != nGroup)  continue;

//			if (pJobItem->GetStackerNum() != (nJobType - JOB_TYPE_CNT))
//				continue;
		}
		if (nStatus != JOB_STA_ALL)
		{
			if (nStatus == JOB_STA_PROGRESS && (pJobItem->m_nStatus == JOB_STA_NEW || pJobItem->m_nStatus == JOB_STA_ERR))
				continue;
			if (nStatus == JOB_STA_NEW && nStatus != pJobItem->m_nStatus)
				continue;
			if (nStatus == JOB_STA_ERR && !pJobItem->IsError())
				continue;
		}

		lvitem.mask = LVIF_TEXT | LVIF_IMAGE;
		lvitem.iSubItem = 0;
		sprintf(szBuff, "%.4d", pJobItem->m_nLuggNum);
		lvitem.pszText = szBuff;
		lvitem.iImage = 0;
		pListCtrl->InsertItem(&lvitem);

		lvitem.mask = LVIF_TEXT;
		lvitem.iSubItem++;
		strcpy(szBuff, LPCTSTR(pJobItem->GetType()));
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		strcpy(szBuff, LPCTSTR(pJobItem->GetStartPos()));
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		strcpy(szBuff, LPCTSTR(pJobItem->GetDestPos()));
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		strcpy(szBuff, LPCTSTR(pJobItem->m_strGrade));
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		strcpy(szBuff, LPCTSTR(pJobItem->GetStatus()));
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		sprintf(szBuff, "%d", pJobItem->m_nBatchNo);
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		sprintf(szBuff, "%d", pJobItem->m_nPalletNo);
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		sprintf(szBuff, "%d", pJobItem->m_nLevelNo);
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		strcpy(szBuff, LPCTSTR(pJobItem->m_strProductID));
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		sprintf(szBuff, "%d", pJobItem->m_nPriority);
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		sprintf(szBuff, "%d", pJobItem->m_nHeight);
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		strcpy(szBuff, LPCTSTR(pJobItem->GetTimeStampString()));
		pListCtrl->SetItem(&lvitem);

		lvitem.iItem++;

	}
	
	m_bModified = FALSE;

	return TRUE;
}

BOOL CJob::Add(int nLuggNum, int nJobType, CString strLocation, int nBatchNo, int nPallet, int nLevelNo, int nStartPos, int nDestPos, int nPriority, CString strProductID, CString strSecondLoc, int nStatus, CString strGrade, CString strQuantity, int nHeight)
{
	CJobItem* pJobItem = new CJobItem(nLuggNum, nJobType, strLocation, nBatchNo, nPallet, nLevelNo, nStartPos, nDestPos, nPriority, strProductID, strSecondLoc, nStatus, strGrade, strQuantity, nHeight);

	return AddSort(pJobItem);
}

BOOL CJob::Add(CJobItem* pJobItem)
{
	return AddSort(pJobItem);
}

BOOL CJob::AddSort(CJobItem* pJobItem)
{
	POSITION pos;

//	m_csJobAdd.Lock();

	CString strLog;
	strLog.Format("Add.. JobType=[%s], From=[%s], To=[%s], 제품명=[%s], 제품코드=[%s]", pJobItem->GetType(), pJobItem->GetStartPos(), pJobItem->GetDestPos(),
															pJobItem->m_strGrade, pJobItem->m_strProductID);
	m_pDoc->m_pLog->Job(LOG_POS_SYSTEM, pJobItem->m_nLuggNum, strLog);
	
	pos = m_JobList.AddTail(pJobItem);

	m_bModified = TRUE;

	if (pJobItem->m_nStatus == JOB_STA_NEW)		Invoke(pJobItem);
 	Backup();

//	m_csJobAdd.Unlock();

	return (pos != NULL) ? TRUE : FALSE;
}

BOOL CJob::Remove(int nLuggNum)
{
	CJobItem* pJobItem = Find(nLuggNum);
	if (pJobItem == NULL)
		return FALSE;
	return Remove(pJobItem);
}

BOOL CJob::Remove(CJobItem* pJobItem)
{
//	m_csJobAdd.Lock();

	POSITION pos = m_JobList.Find(pJobItem);
	if (pos == NULL) return FALSE;

	CString strLog;
	strLog.Format("Job::Remove.. JobType=[%s], From=[%s], To=[%s]", pJobItem->GetType(), pJobItem->GetStartPos(), pJobItem->GetDestPos());
	LOG->Job(LOG_POS_SYSTEM, pJobItem->m_nLuggNum, strLog);

	m_JobList.RemoveAt(pos);
	delete pJobItem;

	m_bModified = TRUE;
//	Backup();

//	m_csJobAdd.Unlock();
	return TRUE;
}

BOOL CJob::Restore()
{
	CFile* pFile;
	TRY
	{
		const char* pFileName = LPCTSTR(m_strFileName);
		pFile = new CFile(pFileName, CFile::modeRead);
	}
	CATCH( CFileException, e )
	{
		CString strTemp;
		strTemp.Format("CJob::Restore.. File could not be opened e->m_cause=[%d]", e->m_cause);
		m_pDoc->m_pLog->Error(LOG_POS_SYSTEM, LOG_SYSTEM, strTemp);
		return FALSE;
	}
	END_CATCH
	CArchive* pArchive = new CArchive(pFile, CArchive::load);

	if (pFile->GetLength() > 0)
		Serialize(*pArchive);

	delete pArchive;
	delete pFile;

	return TRUE;
}

BOOL CJob::Backup()
{
	static int nChk2 = 0;

	if (nChk2 == 1)
		return FALSE;

	nChk2 = 1;

	CFile* pFile;
	CString strFileName;
	strFileName = m_strFileName;

	TRY
	{
		const char* pFileName = LPCTSTR(strFileName);
		pFile = new CFile(pFileName, CFile::modeCreate | CFile::modeWrite);
	}
	CATCH( CFileException, e )
	{
		CString strTemp;
		strTemp.Format("CJob::Backup.. 작업정보 파일 열기 실패 [%s]", CLib::GetSystemErrMsg(e->m_cause));
		LOG_ERROR(LOG_POS_SYSTEM, LOG_SYSTEM, strTemp);
		nChk2 = 0;
		return FALSE;
	}
	END_CATCH

	CArchive* pArchive = new CArchive(pFile, CArchive::store);

	Serialize(*pArchive);
		
	delete pArchive;
	delete pFile;

	nChk2 = 0;

	::PostMessage(m_pDoc->m_hwndView, WM_USER_JOB_NOTIFY, JOB_PROGRESS_DRAW, 0);

	return TRUE;
/*	CFile* pFile;
	TRY
	{
		const char* pFileName = LPCTSTR(m_strFileName);
		pFile = new CFile(pFileName, CFile::modeCreate | CFile::modeWrite);
	}
	CATCH( CFileException, e )
	{
		CString strTemp;
		strTemp.Format("CJob::Backup.. File could not be opened e->m_cause=[%d]", e->m_cause);
		m_pDoc->m_pLog->Error(LOG_POS_SYSTEM, LOG_SYSTEM, strTemp);
		return FALSE;
	}
	END_CATCH

	CArchive* pArchive = new CArchive(pFile, CArchive::store);

	Serialize(*pArchive);

	delete pArchive;
	delete pFile;

	::PostMessage(m_pDoc->m_hwndView, WM_USER_JOB_NOTIFY, JOB_PROGRESS_DRAW, 0);

	return TRUE;
*/
}

CJobItem* CJob::Find(int nLuggNum)
{
	POSITION pos;
	CJobItem* pJobItem;

//	m_csJobAdd.Lock();

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		if (pJobItem->m_nLuggNum == nLuggNum)
		{
//			m_csJobAdd.Unlock();
			return pJobItem;
		}
	}

//	m_csJobAdd.Unlock();
	return NULL;
}

CJobItem* CJob::FetchByStatus(int nStatus, int nScNum)
{
	POSITION pos;
	CJobItem* pJobItem;

//	m_csJobAdd.Lock();

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		if (nScNum != -1 && pJobItem->GetStackerNum() != nScNum)
			continue;

		if (pJobItem->m_nStatus == nStatus)
		{
//			m_csJobAdd.Unlock();
			return pJobItem;
		}
	}

	return NULL;
}

CJobItem* CJob::FetchByComple(int nStatus)
{
	POSITION pos;
	CJobItem* pJobItem;

//	m_csJobAdd.Lock();

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		if (pJobItem->m_nStatus == nStatus)
		{
//			m_csJobAdd.Unlock();
			return pJobItem;
		}
	}

	return NULL;
}

CJobItem* CJob::FetchCvJob(int nScNum, BOOL bFirstFork)
{
	POSITION pos;
	CJobItem* pJobItem;

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		if (nScNum != -1 && pJobItem->GetStackerNum() != nScNum)
			continue;

		if (pJobItem->m_nStatus != JOB_STA_CV_OPER_REQUEST) 
			continue;
		if (pJobItem->m_bFirstFork != bFirstFork) 
			continue;

		if (pJobItem->GetPattern() != JOB_PATTERN_RET) 
			continue;
		
		return pJobItem;
	}

	return NULL;
}

CJobItem* CJob::FetchCvJobByScNum(int nScNum, BOOL bFirstFork)
{
	POSITION pos;
	CJobItem* pJobItem;

//	m_csJobAdd.Lock();

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		if (nScNum != -1 && pJobItem->GetStackerNum() != nScNum)	
			continue;

		if (pJobItem->m_nStatus != JOB_STA_CV_OPER_REQUEST) 
			continue;
		if (pJobItem->m_bFirstFork != bFirstFork) 
			continue;

		if (pJobItem->GetPattern() == JOB_PATTERN_RET)
		{
//			m_csJobAdd.Unlock();
			return pJobItem;
		}
	}

//	m_csJobAdd.Unlock();

	return NULL;
}

CJobItem* CJob::FetchCvJobByJobPattern(int nJobPattern, int nScNum)
{
	POSITION pos;
	CJobItem* pJobItem;

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		if (nScNum != -1 && pJobItem->GetStackerNum() != nScNum)
			continue;

		if (pJobItem->m_nStatus != JOB_STA_CV_OPER_REQUEST) continue;

		if (pJobItem->GetPattern() == nJobPattern)
			return pJobItem;
	}

	return NULL;
}

CJobItem* CJob::FetchCvJobByStationNum(int nStatus, int nStationNum)
{
	POSITION pos;
	CJobItem* pJobItem;

//	m_csJobAdd.Lock();

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		if (nStationNum != -1 && pJobItem->m_nStartPos != nStationNum)
			continue;

		if (pJobItem->m_nStatus != nStatus) 
			continue;

		if (pJobItem->GetPattern() == JOB_PATTERN_STO)
		{
//			m_csJobAdd.Unlock();
			return pJobItem;
		}
	}

//	m_csJobAdd.Unlock();

	return NULL;
}

CJobItem* CJob::FetchCvJobByLocation(CString strLocation, int nLuggNum)
{
	POSITION pos;
	CJobItem* pJobItem;

//	m_csJobAdd.Lock();

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		if(pJobItem->m_nLuggNum == nLuggNum)
			continue;

		if(pJobItem->GetPattern() != JOB_PATTERN_STO) 
			continue;

		if (pJobItem->m_strLocation == strLocation)
		{
//			m_csJobAdd.Unlock();
			return pJobItem;
		}
	}

//	m_csJobAdd.Unlock();

	return NULL;
}

CJobItem* CJob::FetchCvJobByStationNum2(int nJobType, int nStationNum)
{
	POSITION pos;
	CJobItem* pJobItem;

//	m_csJobAdd.Lock();

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		if (nStationNum != -1 && pJobItem->m_nStartPos != nStationNum)
			continue;

		if (pJobItem->m_nStatus != JOB_STA_CV_OPER_REQUEST) continue;

		if (pJobItem->m_nJobType == JOB_TYPE_MANUAL_STO)
		{
//			m_csJobAdd.Unlock();
			return pJobItem;
		}
	}

//	m_csJobAdd.Unlock();

	return NULL;
}

CJobItem* CJob::FetchCvJobByLuggNum(int nLuggNum)
{
	POSITION pos;
	CJobItem* pJobItem;

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		if (pJobItem->m_nStatus != JOB_STA_CV_OPER_REQUEST) 
			continue;

		if (pJobItem->GetPattern() != JOB_PATTERN_STO)
			continue;

		if (pJobItem->m_nLuggNum != nLuggNum)
			continue;

		return pJobItem;
	}

	return NULL;
}

void CJob::ChangeStatusByOrder(int nBatchNum)
{
	POSITION pos;
	CJobItem* pJobItem;

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		if (pJobItem->GetPattern() != JOB_PATTERN_RET)
			continue;

		if (pJobItem->m_nBatchNo != nBatchNum) 
			continue;

		if (pJobItem->m_nStatus != JOB_STA_CV_OPER_INVOKE) 
			continue;

		//pJobItem->m_nStatus = JOB_STA_CV_MOVE_ST; 
		Remove(pJobItem); //@@
	}

}

CJobItem* CJob::FetchByJobType(int nJobType, int nScNum, int nExceptLuggNum)
{
	POSITION pos;
	CJobItem* pJobItem;

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		if (nScNum != -1 && pJobItem->GetStackerNum() != nScNum)
			continue;

		if ( nExceptLuggNum == 0 && pJobItem->m_nLuggNum == nExceptLuggNum )
			continue;

		if (pJobItem->m_nJobType == nJobType)
			return pJobItem;
	}

	return NULL;
}

CJobItem* CJob::FetchByJobPattern(int nJobPattern, int nScNum, int nExceptLuggNum)
{
	POSITION pos;
	CJobItem* pJobItem;
	CJobItem* pFetchJobItem = NULL;
	int nPriority = -1;

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		if (pJobItem->GetPattern() != nJobPattern || pJobItem->GetStackerNum() != nScNum) 
			continue;

		if ( nExceptLuggNum != 0 && pJobItem->m_nLuggNum == nExceptLuggNum )
			continue;

		if (pJobItem->m_nStatus != JOB_STA_SC_OPER_REQUEST)
			continue;

		if (pJobItem->m_nPriority > nPriority)
		{
			pFetchJobItem = pJobItem;
			nPriority = pFetchJobItem->m_nPriority;
		}
	}

	return pFetchJobItem;
}

BOOL CJob::FetchLowLevelRetrive(CJobItem* pJobItem)
{
	POSITION pos;
	CJobItem* pNewJobItem;

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pNewJobItem = (CJobItem *)m_JobList.GetNext(pos);

		int	nPattern = pNewJobItem->GetPattern();
		if (nPattern != JOB_PATTERN_RET)
			continue;

//		if (pNewJobItem->m_nPriority != 100)
//			continue;
		int nLugg = pNewJobItem->m_nLuggNum;

		if(pJobItem->m_nBatchNo == pNewJobItem->m_nBatchNo)
		{
			if(pNewJobItem->m_nLevelNo > 0 && pNewJobItem->m_nLevelNo == 6)
			{
				if (pNewJobItem->m_nStatus == JOB_STA_CV_OPER_INVOKE  || 
					pNewJobItem->m_nStatus == JOB_STA_SC_OPER_REQUEST || 
					pNewJobItem->m_nStatus == JOB_STA_SC_OPER_INVOKE)

					return FALSE;
			}

			if(pNewJobItem->m_nLevelNo > 0 && pNewJobItem->m_nLevelNo != 6) continue;
		}
	}

	return TRUE;
}

BOOL  CJob::FetchLowBatchRetrive(CJobItem* pJobItem, int nScNum)
{
	POSITION pos;
	CJobItem* pNewJobItem;

//	m_csJobAdd.Lock();

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pNewJobItem = (CJobItem *)m_JobList.GetNext(pos);

		int	nPattern = pNewJobItem->GetPattern();
		if (nPattern != JOB_PATTERN_RET)
			continue;

		if (pJobItem->GetStackerNum() != nScNum) 
			continue;
//		if (pNewJobItem->m_nStatus != JOB_STA_SC_OPER_REQUEST)
//			continue;
		int lugg = pJobItem->m_nLuggNum;

		int nLugg = pNewJobItem->m_nLuggNum;

		if(pJobItem->m_nDestPos == pNewJobItem->m_nDestPos && pJobItem->m_nBatchNo > pNewJobItem->m_nBatchNo)
		{
			if (pNewJobItem->m_nStatus == JOB_STA_CV_OPER_INVOKE  || 
				pNewJobItem->m_nStatus == JOB_STA_SC_OPER_REQUEST || 
				pNewJobItem->m_nStatus == JOB_STA_SC_OPER_INVOKE)
				{
//					m_csJobAdd.Unlock();
					return FALSE;
				}
		}
	}

//	m_csJobAdd.Unlock();
	return TRUE;
}

/*
CJobItem* CJob::FetchByJobRetrieve(int nScNum, int nExceptLuggNum)
{
	POSITION pos;
	CJobItem* pJobItem;
	CJobItem* pFetchJobItem = NULL;
	int nPriority = -1;

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		//if ( pJobItem->m_ucTypeWH != ucTypeWH )	continue;

		if ( (pJobItem->GetPattern() != JOB_PATTERN_RET &&
			  pJobItem->GetPattern() != JOB_PATTERN_CIRCULATION ) ||
			  pJobItem->GetStackerNum() != nScNum ) 
			continue;

		if ( nExceptLuggNum != 0 && pJobItem->m_nLuggNum == nExceptLuggNum )
			continue;

		if (pJobItem->m_nStatus != JOB_STA_SC_OPER_REQUEST)
			continue;

		if (pJobItem->m_nPriority > nPriority)
		{
			nPriority = pJobItem->m_nPriority;
			pFetchJobItem = pJobItem;
		}
	}

	return pFetchJobItem;
}
*/

BOOL CJob::FetchByJobRetrieve(int nScNum, CJobItem** pFetchJobItem1, CJobItem** pFetchJobItem2)
{
	POSITION pos;
	CJobItem* pJobItem;
	int nBank1, nBay1, nLevel1 = 0;
	int nBank2, nBay2, nLevel2 = 0;

//	m_csJobAdd.Lock();

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

        int	nPattern = pJobItem->GetPattern();
		if (nPattern != JOB_PATTERN_RET || pJobItem->GetStackerNum() != nScNum)
			continue;
		if (pJobItem->m_nPriority != 100)
			continue;
		if (pJobItem->m_nStatus != JOB_STA_SC_OPER_REQUEST)
			continue;

		//Test확인
		if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_201 && m_pDoc->m_b4groupCheck == TRUE)
		{
			if(m_pDoc->m_n4GroupInCount > m_pDoc->m_n4goupBuffCouter)  continue;
		}
		else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_202 && m_pDoc->m_b5groupCheck == TRUE)
		{
			if(m_pDoc->m_n5GroupInCount > m_pDoc->m_n5goupBuffCouter)  continue;
		}
		else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_203 && m_pDoc->m_b6groupCheck == TRUE)
		{
			if(m_pDoc->m_n6GroupInCount > m_pDoc->m_n6goupBuffCouter)  continue;
		}
		else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_255 && m_pDoc->m_b7groupCheck == TRUE)
			continue;
		//

		int nLuggNum = pJobItem->m_nLuggNum;
				
		(*pFetchJobItem1) = pJobItem;

		nBank1  = CLib::GetBank(pJobItem->m_strLocation);
		nBay1   = CLib::GetBay(pJobItem->m_strLocation);
		nLevel1 = CLib::GetLevel(pJobItem->m_strLocation);
		break; // Fork#1 작업을 찾는다.ㅣ
	}

	if ((*pFetchJobItem1) != NULL) {
		for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
		{
			pJobItem = (CJobItem *)m_JobList.GetNext(pos);

			int	nPattern = pJobItem->GetPattern();
			if (nPattern != JOB_PATTERN_RET || pJobItem->GetStackerNum() != nScNum)
				continue;
			if (pJobItem->m_nPriority != 100)
				continue;
			if (pJobItem->m_nStatus != JOB_STA_SC_OPER_REQUEST)
				continue;
			if (pJobItem == (*pFetchJobItem1))
				continue;

			//Test확인
			if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_201 && m_pDoc->m_b4groupCheck == TRUE)
			{
				if(m_pDoc->m_n4GroupInCount > m_pDoc->m_n4goupBuffCouter)  continue;
			}
			else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_202 && m_pDoc->m_b5groupCheck == TRUE)
			{
				if(m_pDoc->m_n5GroupInCount > m_pDoc->m_n5goupBuffCouter)  continue;
			}
			else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_203 && m_pDoc->m_b6groupCheck == TRUE)
			{
				if(m_pDoc->m_n6GroupInCount > m_pDoc->m_n6goupBuffCouter)  continue;
			}
			else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_255 && m_pDoc->m_b7groupCheck == TRUE)
				continue;
			//

			int nLuggNum = pJobItem->m_nLuggNum;

			nBank2  = CLib::GetBank(pJobItem->m_strLocation);
			nBay2   = CLib::GetBay(pJobItem->m_strLocation);
			nLevel2 = CLib::GetLevel(pJobItem->m_strLocation);

			if (nBank1 != nBank2 || nLevel1 != nLevel2) 
				continue;

			if (nBay1 != nBay2 - 1 && nBay1 != nBay2 + 1) 
				continue;
			
/*			if (nBay1 == nBay2 - 1) {
				(*pFetchJobItem2) = (*pFetchJobItem1);
				(*pFetchJobItem1) = pJobItem;
			}
			else */ if (nBay1 == nBay2 + 1) {
				(*pFetchJobItem2) = pJobItem;
			}

//			m_csJobAdd.Unlock();
			return TRUE; // 동시에(양방향) 작업을 할 Fork#2 작업을 찾는다.
		}
	}

	if ((*pFetchJobItem1) != NULL && (*pFetchJobItem2) == NULL) {
		for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
		{
			pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		    int	nPattern = pJobItem->GetPattern();
			if (nPattern != JOB_PATTERN_RET || pJobItem->GetStackerNum() != nScNum)
				continue;
			if (pJobItem->m_nPriority != 100)
				continue;
			if (pJobItem->m_nStatus != JOB_STA_SC_OPER_REQUEST)
				continue;
			if (pJobItem == (*pFetchJobItem1))
				continue;

			//Test확인
			if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_201 && m_pDoc->m_b4groupCheck == TRUE)
			{
				if(m_pDoc->m_n4GroupInCount > m_pDoc->m_n4goupBuffCouter)  continue;
			}
			else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_202 && m_pDoc->m_b5groupCheck == TRUE)
			{
				if(m_pDoc->m_n5GroupInCount > m_pDoc->m_n5goupBuffCouter)  continue;
			}
			else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_203 && m_pDoc->m_b6groupCheck == TRUE)
			{
				if(m_pDoc->m_n6GroupInCount > m_pDoc->m_n6goupBuffCouter)  continue;
			}
			else if(pJobItem->m_nDestPos == IMS_ECS_RET_STATION_255 && m_pDoc->m_b7groupCheck == TRUE)
				continue;
			//

			int nLuggNum = pJobItem->m_nLuggNum;
					
			(*pFetchJobItem2) = pJobItem;
			break; // 동시에 할 작업이 없으면 따로 떨어져 있는 작업을 찾는다.
		}
	}

	if ((*pFetchJobItem1) != NULL && (*pFetchJobItem2) != NULL)
	{
//	  m_csJobAdd.Unlock();
	  return TRUE;
	}


	if ((*pFetchJobItem1) != NULL && (*pFetchJobItem2) == NULL) 
	{
		for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
		{
			pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		    int	nPattern = pJobItem->GetPattern();
			if (nPattern != JOB_PATTERN_RET || pJobItem->GetStackerNum() != nScNum)
				continue;
			if (pJobItem->m_nPriority != 100)
				continue;
			if (pJobItem->m_nStatus != JOB_STA_SC_OPER_REQUEST)
				continue;
			if (m_nScOrderNo != pJobItem->m_nBatchNo && pJobItem->m_nJobType == JOB_TYPE_UNIT_RET) 
				continue;

			if (pJobItem == (*pFetchJobItem1))
				continue;
		
			(*pFetchJobItem2) = pJobItem;
			break; // Fork#1 작업이 있고 Fork#2작업을 찾을때 우선순위와 BatchNo를 신경 쓴다.
		}
	}
	    
	if ((*pFetchJobItem1) != NULL)
	{
//	  m_csJobAdd.Unlock();
	  return TRUE;
	}
	
    if ((*pFetchJobItem1) == NULL) {
		for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
		{
			pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		    int	nPattern = pJobItem->GetPattern();
			if (nPattern != JOB_PATTERN_RET || pJobItem->GetStackerNum() != nScNum)
				continue;
			if (pJobItem->m_nPriority != 100)
				continue;
			if (pJobItem->m_nStatus != JOB_STA_SC_OPER_REQUEST)
				continue;
			if (m_nScOrderNo != pJobItem->m_nBatchNo && pJobItem->m_nJobType == JOB_TYPE_UNIT_RET) 
				continue;
					
			(*pFetchJobItem1) = pJobItem;
			break;
		}
	}
	
	if ((*pFetchJobItem1) != NULL && (*pFetchJobItem1) == (*pFetchJobItem2)) {
        (*pFetchJobItem2) = NULL;
		{
//		  m_csJobAdd.Unlock();
		  return TRUE;
		}
    }

    if ((*pFetchJobItem1) == NULL)  
	{
//	  m_csJobAdd.Unlock();
	  return FALSE;
	}

    if ((*pFetchJobItem1) != NULL)  
	{
//	  m_csJobAdd.Unlock();
	  return TRUE;
	}

//	m_csJobAdd.Unlock();
	return TRUE;
}

int CJob::FetchCvJobByDestNum(int nStationNum)
{
	POSITION pos;
	CJobItem* pJobItem;

	for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
	{
		pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		if (pJobItem->GetPattern() != JOB_PATTERN_RET &&
			pJobItem->GetPattern() != JOB_PATTERN_MOVE)
			continue;

		if (pJobItem->m_nDestPos != nStationNum)
			continue;

		return 1;
	}

	return 0;
}

BOOL CJob::Invoke(int nLuggNum)
{
	CString strLog;
	CJobItem* pJobItem;

	if (nLuggNum == 0)
	{
		pJobItem = FetchByStatus(JOB_STA_NEW);
		if (pJobItem == NULL)
			return FALSE;
	} 
	else
	{
		pJobItem = Find(nLuggNum);
		if (pJobItem == NULL)
		{
			m_pDoc->m_pLog->Error(LOG_POS_SYSTEM, nLuggNum, "Can't find this luggage number.. can't invoke..");
			return FALSE;
		}
	}
	Invoke(pJobItem);

	return TRUE;
}

BOOL CJob::Invoke(CJobItem* pJobItem)
{
	CString strLog;

	switch (pJobItem->GetPattern())
	{
	case	JOB_PATTERN_STO:
		if (pJobItem->m_nStatus == JOB_STA_DUAL_STO_RETRY)
		{
			pJobItem->m_nStatus = JOB_STA_SC_OPER_REQUEST;
			//Backup();
			SC_ACTION(pJobItem->GetStackerNum());
			strLog.Format("Invoke.. Stacker #%d 재입고 구동 요구..", pJobItem->GetStackerNum() + 1);
			m_pDoc->m_pLog->Job(LOG_POS_SYSTEM, pJobItem->m_nLuggNum, strLog);
			return TRUE;
		}
		pJobItem->m_nStatus = JOB_STA_CV_OPER_REQUEST;
		//Backup();

		CV_ACTION(CV_1_PLC);
		m_pDoc->m_pLog->Job(LOG_POS_SYSTEM, pJobItem->m_nLuggNum, "Invoke.. Conveyor 구동 요구..");
		return TRUE;
	case	JOB_PATTERN_MOVE:
		pJobItem->m_nStatus = JOB_STA_CV_OPER_REQUEST;
		//Backup();

		CV_ACTION(CV_1_PLC);
		m_pDoc->m_pLog->Job(LOG_POS_SYSTEM, pJobItem->m_nLuggNum, "Invoke.. Conveyor 구동 요구..");
		return TRUE;
	case	JOB_PATTERN_CIRCULATION:
	case	JOB_PATTERN_RTR:
		pJobItem->m_nStatus = JOB_STA_SC_OPER_REQUEST;
//		Backup();	98.11.25 for the performance

		SC_ACTION(pJobItem->GetStackerNum());
		strLog.Format("Invoke.. Stacker #%d 랙투랙 구동 요구..", pJobItem->GetStackerNum() + 1);
		m_pDoc->m_pLog->Job(LOG_POS_SYSTEM, pJobItem->m_nLuggNum, strLog);
		return TRUE;
	case	JOB_PATTERN_RET:
		pJobItem->m_nStatus = JOB_STA_SC_OPER_REQUEST;
//		Backup();	98.11.25 for the performance

		SC_ACTION(pJobItem->GetStackerNum());
		strLog.Format("Invoke.. Stacker #%d 출고 구동 요구..", pJobItem->GetStackerNum() + 1);
		m_pDoc->m_pLog->Job(LOG_POS_SYSTEM, pJobItem->m_nLuggNum, strLog);
		return TRUE;
	}

	return FALSE;
}

BOOL CJob::Complete(int nLuggNum, int nScJobType)
{
	CJobItem* pJobItem = Find(nLuggNum);

	if (pJobItem == NULL)
	{
		m_pDoc->m_pLog->Error(LOG_POS_SYSTEM, nLuggNum, "CJob::Complete.. 작업번호를 찾을수 없슴..");
		return FALSE;
	}

	if ( nScJobType == SC_JOB_TYPE_STORE || nScJobType == SC_JOB_TYPE_RACK_TO_RACK )
	{
		switch (pJobItem->m_nJobType) 
		{
		case	JOB_TYPE_UNIT_STO:
		case	JOB_TYPE_MANUAL_STO:
			pJobItem->m_nStatus = JOB_STA_COMPLETE_REQUEST;
			m_pDoc->m_pLog->Job(LOG_POS_SYSTEM, nLuggNum, "입고 작업완료..");
			break;
		}
	}
	else	// SC_JOB_TYPE_RETRIEVE
	{
		switch (pJobItem->m_nJobType) 
		{
		case	JOB_TYPE_UNIT_RET:
		case	JOB_TYPE_MANUAL_RET:
		case	JOB_TYPE_RACK_TO_RACK:
			m_pDoc->m_pLog->Job(LOG_POS_SYSTEM, nLuggNum, "출고 작업완료..");
			break;
		}
	}

	if ( pJobItem->m_nJobType == JOB_TYPE_MANUAL_RET || pJobItem->m_nJobType == JOB_TYPE_RACK_TO_RACK)
		return TRUE;
	else if ( pJobItem->m_nJobType == JOB_TYPE_MANUAL_STO )
	{
		m_nResultCount[pJobItem->GetStackerNum()]++;
		::PostMessage(m_pDoc->m_hwndView, WM_USER_JOB_NOTIFY, JOB_RESULT_DRAW, 0);
		Remove(pJobItem);
		return TRUE;
	}

#ifdef OPT_HOST_SAP_INTERFACE_USE
		m_pDoc->m_pSapHost->Complete(pJobItem->m_nLuggNum);
#endif
#ifdef OPT_HOST_NETWORK_INTERFACE_USE
	if (m_pDoc->m_pHostCl != NULL)
		m_pDoc->m_pHostCl->Complete(nLuggNum, nScJobType);
	//else
	//	PutOffMsg(CMD_COMPLETE, nLuggNum, nScJobType);
#endif

	return TRUE;
}


void CJob::PutOffMsg(char cMsgType, int nLuggNum, int nScJobType, int nDevKind, int nDevNo, int nErrKind, int nErrCode, CString strLocation )
{
	POSITION pos, posPrev;
	CMsg *pMsg;

	if (m_MsgList.GetCount() > 100)
	{
		for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
		{
			posPrev = pos;
			pMsg = (CMsg *)m_MsgList.GetNext(pos);
			if (pMsg->m_MsgType == CMD_COMPLETE ||
				(pMsg->m_MsgType == CMD_ERROR && pMsg->m_nDevKind == DEVICE_CLASS_SC && pMsg->m_nErrKind != MECHANIC_ERROR))
				continue;
			m_MsgList.RemoveAt(posPrev);
			delete pMsg;
			break;
		}
	}

	pMsg = new CMsg(cMsgType, nLuggNum, nScJobType, nDevKind, nDevNo, nErrKind, nErrCode, strLocation);
	m_MsgList.AddTail(pMsg);
}

int CJob::GetNewLuggNum()
{
	POSITION pos;
	CJobItem* pJobItem;
	
	for (int nLuggNum = 9001; nLuggNum < 9999; nLuggNum++)
	{
		int nCnt = 0;
		for (pos = m_JobList.GetHeadPosition(); pos != NULL;)
		{
			pJobItem = (CJobItem *)m_JobList.GetNext(pos);

			if (pJobItem->m_nLuggNum == nLuggNum)
				nCnt++;
		}
		if (nCnt == 0)
			return nLuggNum;
	}
	return FALSE;
}

int CJob::GetSeqLuggNum()
{
	if (m_nLuggNum >= 9998 || m_nLuggNum < 9001)
        m_nLuggNum = 9000;
    return ++ m_nLuggNum;
}

/* BcrCode
int CJob::GetNewSeqNo()
{
	POSITION pos;
	CBcrBuff* pBcrBuff;
	
	for (int nSeqNo = 1; nSeqNo < 9999; nSeqNo++)
	{
		int nCnt = 0;
		for (pos = m_BcrBuff.GetHeadPosition(); pos != NULL;)
		{
			pBcrBuff = (CBcrBuff *)m_BcrBuff.GetNext(pos);

			if (pBcrBuff->m_nSeqNo == nSeqNo)
				nCnt++;
		}
		if (nCnt == 0)
			return nSeqNo;
	}
	return FALSE;
}
*/

int CJob::GetJobCount(int nScNum)
{
	int nJobCount = 0;

	for ( POSITION pos = m_JobList.GetHeadPosition(); pos != NULL; )
	{
		CJobItem *pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		if ( nScNum != -1 && pJobItem->GetStackerNum() != nScNum )
			continue;

		nJobCount++;
	}

	return nJobCount;
}

int CJob::GetResultCount(int nScNum)
{
	int nResultCount = 0;

	if ( nScNum != -1 )
		return m_nResultCount[nScNum];

	for ( int i = 0; i < SC_CNT; i++ )
	{
		nResultCount += m_nResultCount[i];
	}

	return nResultCount;
}

void CJob::RemoveAllJob()
{
	for ( POSITION pos = m_JobList.GetHeadPosition(); pos != NULL; )
	{
		CJobItem *pJobItem = (CJobItem *)m_JobList.GetNext(pos);

		CString strLog;
		strLog.Format("Job::RemoveAllJob.. JobType=[%s], From=[%s], To=[%s]", pJobItem->GetType(), pJobItem->GetStartPos(), pJobItem->GetDestPos());
		LOG->Job(LOG_POS_SYSTEM, pJobItem->m_nLuggNum, strLog);

		delete pJobItem;
	}
	
	m_JobList.RemoveAll();

	for ( pos = m_MsgList.GetHeadPosition(); pos != NULL; )
	{
		CMsg *pMsg = (CMsg *)m_MsgList.GetNext(pos);

		CString strLog;
		strLog.Format("Job::RemoveAllJob.. MsgType=[%c], DevNo=[%d], JobType=[%d], ErrCode=[%d]", 
			pMsg->m_MsgType, pMsg->m_nDevNo, pMsg->m_nScJobType, pMsg->m_nErrCode);
		LOG->Job(LOG_POS_SYSTEM, pMsg->m_nLuggNum, strLog);

		delete pMsg;
	}
	
	m_MsgList.RemoveAll();

	/* BcrCode
	for ( pos = m_BcrBuff.GetHeadPosition(); pos != NULL; )
	{
		CBcrBuff *pBcrBuff = (CBcrBuff *)m_BcrBuff.GetNext(pos);
		delete pBcrBuff;
	}
	*/
	
	m_BcrBuff.RemoveAll();

	m_bModified = TRUE;
	Backup();
}

void CJob::ResetResultCount()
{
	for ( int i = 0; i < SC_CNT; i++ )
		m_nResultCount[i] = 0;

	if ( m_pDoc != NULL )
		::PostMessage(m_pDoc->m_hwndView, WM_USER_JOB_NOTIFY, JOB_RESULT_DRAW, 0);
}


// Msg Class
/////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CMsg, CObject, 0)

CMsg::CMsg()
{
	m_bNew = TRUE;
}

CMsg::CMsg(char cMsgType, int nLuggNum, int nScJobType, int nDevKind, int nDevNo, int nErrKind, int nErrCode, CString strLocation )
{
	m_MsgType = cMsgType;
	m_nLuggNum = nLuggNum;
	m_nScJobType = nScJobType;
	m_nDevKind = nDevKind;
	m_nDevNo = nDevNo;
	m_nErrKind = nErrKind;
	m_nErrCode = nErrCode;
	m_strLocation = strLocation;
	m_bNew = TRUE;
}

void CMsg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_bNew;
		ar << m_MsgType;
		ar << m_nLuggNum;
		ar << m_nScJobType;
		ar << m_nDevKind;
		ar << m_nDevNo;
		ar << m_nErrKind;
		ar << m_nErrCode;
		ar << m_strLocation;
	}
	else
	{
		ar >> m_bNew;
		ar >> m_MsgType;
		ar >> m_nLuggNum;
		ar >> m_nScJobType;
		ar >> m_nDevKind;
		ar >> m_nDevNo;
		ar >> m_nErrKind;
		ar >> m_nErrCode;
		ar >> m_strLocation;
	}
}
