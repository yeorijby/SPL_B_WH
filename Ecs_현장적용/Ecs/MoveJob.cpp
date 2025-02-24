// MoveJob.cpp : implementation of the CJob class
//

#include "stdafx.h"
#include "MoveJob.h"
#include "EcsDoc.h"
#include "Ecs.h"
#include "Lib.h"

#define	LOG			m_pDoc->m_pLog

IMPLEMENT_DYNCREATE(CMoveJob, CObject)

CCriticalSectionEx CMoveJob::m_csMoveJobAdd = CCriticalSectionEx();

CMoveJob::CMoveJob(CEcsDoc* pDoc) 
{ 
	m_pDoc = pDoc;
	m_strFileName = "..\\Job\\MoveJob.Ecs";
	m_bModified = FALSE;
	m_bIsOfflineJob = FALSE;

//	ResetResultCount();


}

CMoveJob::~CMoveJob()
{
	for (POSITION pos = m_MoveJobList.GetHeadPosition(); pos != NULL;)
	{
		delete m_MoveJobList.GetNext(pos);
	}
	m_MoveJobList.RemoveAll();

	for ( pos = m_MoveMsgList.GetHeadPosition(); pos != NULL;)
	{
		delete m_MoveMsgList.GetNext(pos);
	}
	m_MoveMsgList.RemoveAll();

}

void CMoveJob::Serialize(CArchive& ar)
{

	m_MoveJobList.Serialize(ar);
	m_MoveMsgList.Serialize(ar);

	if (ar.IsStoring())
	{

		ar << m_nLuggNum;

		for(int i=0; i<10; i++)
			ar << m_pDoc->m_nSetLine[i];

		for(i=0; i<10; i++)
			ar << m_pDoc->m_nSetLineCount[i];

		for(i=0; i<14; i++)
			ar << m_pDoc->m_nSetLine2[i];

		for(i=0; i<14; i++)
			ar << m_pDoc->m_nSetLineCount2[i];

		
	}
	else
	{

		ar >> m_nLuggNum;

		for(int i=0; i<10; i++)
			ar >> m_pDoc->m_nSetLine[i];

		for(i=0; i<10; i++)
			ar >> m_pDoc->m_nSetLineCount[i];

		for(i=0; i<14; i++)
			ar >> m_pDoc->m_nSetLine2[i];

		for(i=0; i<14; i++)
			ar >> m_pDoc->m_nSetLineCount2[i];

	}
}

// MoveJobItem Class
/////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CMoveJobItem, CObject, 0)

CMoveJobItem::CMoveJobItem(int nLuggNum, int nJobType, CString strLocation, int nBatchNo, int nPalletNo, int nLevelNo, int nStartPos, int nDestPos, int nPriority, CString strProductID, CString strSecondLoc, int nStatus, CString strGrade, CString strQuantity, int nHeight, int nLineNum, int nLastPallet)
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

	m_nLineNum = nLineNum;
	m_nLastPallet = nLastPallet;

	m_nDestTrack   = 0;
	m_nTwinJob = 0;

	m_tTimeStamp   = time(NULL);

	m_bFirstFork = TRUE;
	m_bLock = FALSE;
}

void CMoveJobItem::Serialize(CArchive& ar)
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

	    ar << m_nLineNum;
	    ar << m_nLastPallet;

		ar << m_tTimeStamp;

		ar << m_nTwinJob;
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

	    ar >> m_nLineNum;
	    ar >> m_nLastPallet;

		ar >> m_tTimeStamp;

		ar >> m_nTwinJob;
	}
}

CString CMoveJobItem::GetLuggNumString()
{
	CString strTemp;
	strTemp.Format("%.4d", m_nLuggNum);

	return strTemp;
}

CString CMoveJobItem::GetLuggNumString2()
{
	CString strTemp;
	strTemp.Format("%.4d", m_nErrCode);

	return strTemp;
}

CString CMoveJobItem::GetTimeStampString()
{
	CTime theTime(m_tTimeStamp);
	CString strTemp = theTime.Format( "%Y/%m/%d/ %H:%M:%S" );

	return strTemp;
}

CString CMoveJobItem::GetBatchNoString()
{
	CString strTemp;
	strTemp.Format("%.4d", m_nBatchNo);

	return strTemp;
}

CString CMoveJobItem::GetPriorityString()
{
	CString strTemp;
	strTemp.Format("%d", m_nPriority);

	return strTemp;
}

CString CMoveJobItem::GetType()
{
	return GetType(m_nJobType);
}

CString CMoveJobItem::GetType(int nType)
{
	return CLib::ConvertJobTypeToString(nType);
}

CString CMoveJobItem::GetStartPos()
{
	return GetStartPos(m_strLocation, m_nStartPos, m_nJobType);
}

CString CMoveJobItem::GetStartPos(CString strLocation, int nStartPos, int nJobType)
{
	switch ( nJobType )
	{
	case	JOB_TYPE_UNIT_RET:
	case	JOB_TYPE_MANUAL_RET:
	case  JOB_TYPE_RACK_TO_RACK:
		return CLib::ConvertLocationToCustom(strLocation);
	}

//	if (GetStackerNum() < SC_1_CNT)
	{
		switch (nStartPos)
		{
		case	IMS_ECS_STO_STATION_100:
			return CString("�����԰��");
		case	IMS_ECS_STO_STATION_101:
			return CString("Line#11 (CV#782)");
		case	IMS_ECS_STO_STATION_103:
			return CString("�����ڵ��԰��");

		case	111:
			return CString("1:�佺��2ȣ 1������");
		case	112:
			return CString("2:�佺��2ȣ 2������");
		case	113:
			return CString("3:�佺��3ȣ");
		case	114:
			return CString("4:�佺�򸮼���");
		case	115:
			return CString("5:���ҵ���1ȣ");
		case	116:
			return CString("6:���ҵ���2ȣ");
		case	117:
			return CString("7:�Ļ�");
		case	118:
			return CString("8:������(����)");
		case	119:
			return CString("9:1�� �õ�������ġ");
		case	120:
			return CString("10:��������1ȣ");
		case	121:
			return CString("11:��������2ȣ");
		case	122:
			return CString("12:��������4ȣ");
		case	123:
			return CString("13:��������3ȣ");
		case	124:
			return CString("14:1�� �ӷ�");
		case	125:
			return CString("15:�����ٰ�Ʈ 15����");
		case	126:
			return CString("16:�����ٰ�Ʈ 16����");
		case	127:
			return CString("17:�ĺ���ũ 17����");
		case	128:
			return CString("18:�ĺ���ũ 18����");

		default:
			CString strTemp;
			//strTemp.Format("DEF(%d)", nStartPos);
			strTemp.Format("��� ���� �̵�");
			return strTemp;
		}
	}

	CString strTemp;
	strTemp.Format("DEF(%d)", nStartPos);
	return strTemp;
}

CString CMoveJobItem::GetDestPos()
{
	return GetDestPos(m_nLineNum);
}

CString CMoveJobItem::GetDestPos(int nLineNum)
{

	switch (nLineNum)
	{
	case	1:
		return CString("Buffer#1");
	case	2:
		return CString("Buffer#2");
	case	3:
		return CString("Buffer#3");
	case	4:
		return CString("Buffer#4");
	case	11:
		return CString("LINE#11");
	case	12:
		return CString("���� LINE#12");
	case	15:
		return CString("Buffer#15");

	default:
		CString strTemp;
		strTemp.Format("DEF(%d)", nLineNum);
		return strTemp;
	}

	CString strTemp;
	strTemp.Format("DEF(%d)", nLineNum);
	return strTemp;
}

CString CMoveJobItem::GetDestPos2()
{
	return GetDestPos2(m_nDestPos);
}

CString CMoveJobItem::GetDestPos2(int nDestPos)
{

	switch (nDestPos)
	{
	case	IMS_ECS_RET_STATION_251:
		return CString("��������");
	case	IMS_ECS_RET_STATION_255:
		return CString("�����̵���");
	case	IMS_ECS_RET_STATION_204:
		return CString("���Ϻз���");

	default:
		CString strTemp;
		strTemp.Format("DEF(%d)", nDestPos);
		return strTemp;
	}

	CString strTemp;
	strTemp.Format("DEF(%d)", nDestPos);
	return strTemp;
}

int CMoveJobItem::GetPattern()
{
	return GetPattern(m_nJobType);
}

int CMoveJobItem::GetPattern(int nJobType)
{
	return CLib::ConvertJobTypeToPattern(nJobType);
}

BOOL CMoveJobItem::IsError()
{
	return IsError(m_nStatus);
}

BOOL CMoveJobItem::IsError(int nStatus)
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

BOOL CMoveJobItem::IsOffLineJob()
{
	if( m_nJobType == JOB_TYPE_MANUAL_STO || m_nJobType == JOB_TYPE_RACK_TO_RACK || m_nJobType == JOB_TYPE_MANUAL_STN_TO_STN )
		return TRUE;

	return FALSE;
}

CString CMoveJobItem::GetStatus()
{
	return GetStatus(m_nStatus);
}

CString CMoveJobItem::GetStatus(int nStatus)
{
	switch (nStatus)
	{
	case	JOB_STA_MOVE_ALL:					
		return CString("��ü");
	case	JOB_STA_MOVE_NEW:					
		return CString("�ű�");
	case	JOB_STA_MOVE_CV_NEW:					
		return CString("C/V �ű� �۾�");
	case	JOB_STA_MOVE_ERR:					
		return CString("����");


	case	JOB_STA_MOVE_CV_OPER_REQUEST:		
		return CString("C/V ���� ���");
	case	JOB_STA_MOVE_CV_OPER_INVOKE:			
		return CString("C/V ������");
	case	JOB_STA_MOVE_CV_BUFFER_OPER_INVOKE:			
		return CString("BUFFER ���� ������");
	case	JOB_STA_MOVE_CV_PALLET_OPER_INVOKE:			
		return CString("PALLET ���� ������");

	case	JOB_STA_MOVE_RGV_OPER_REQUEST:		
		return CString("RTV ���� ���");
	case	JOB_STA_MOVE_RGV_OPER_INVOKE:		
		return CString("RTV ������");
	case	JOB_STA_MOVE_RGV_OPER_COMPLETE:		
		return CString("RTV �۾� �Ϸ�");


	case	JOB_STA_MOVE_COMPLETE_REQUEST:		
		return CString("�Ϸ� ���� ��û");
	case	JOB_STA_MOVE_COMPLETE:				
		return CString("�Ϸ� ���� ���");



	case	JOB_STA_MOVE_REFUSE_COMPLETE:		
		return CString("�Ϸ� ���� �̻�");
	case	JOB_STA_MOVE_REFUSE_ARRIVED:			
		return CString("���� ���� �̻�");
	case	JOB_STA_MOVE_REFUSE_CANCEL:			
		return CString("��� ���� �̻�");

	case	JOB_STA_MOVE_REFUSE_ERROR:			
		return CString("���� ���� �̻�");



	default:
		CString strTemp;
		strTemp.Format("DEF(%d)", nStatus);
		return strTemp;
	}

}

CString CMoveJobItem::GetHeight()
{
	return GetHeight(m_nHeight);
}

CString CMoveJobItem::GetHeight(int nHeight)
{
	switch (nHeight)
	{
	case	-1:
	case	TURN_NONE:
		return CString("��������");
	case	TURN_LEFT:
		return CString("B Line");
	case	TURN_RIGHT:
		return CString("A Line");
	default:
		CString strTemp;
		strTemp.Format("DEF(%d)", nHeight);
		return strTemp;
	}
}

int CMoveJobItem::GetBlock()
{
	return GetBlock(m_strLocation);
}

int CMoveJobItem::GetSecondBlock()
{
	return GetBlock(m_strSecondLoc);
}

int CMoveJobItem::GetBlock(CString strLocation)
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

int CMoveJobItem::GetStackerNum()
{
	return GetStackerNum(m_strLocation);
}

int CMoveJobItem::GetStackerNum(CString strLocation)
{
	return CLib::GetStackerNum(strLocation);
}

int CMoveJobItem::GetBank()
{
	return GetBank(m_strLocation);
}

int CMoveJobItem::GetBank(CString strLocation)
{
	return CLib::GetBank(strLocation);
}

int CMoveJobItem::GetBay()
{
	return GetBay(m_strLocation);
}

int CMoveJobItem::GetBay(CString strLocation)
{
	return CLib::GetBay(strLocation);
}

int CMoveJobItem::GetLevel()
{
	return GetLevel(m_strLocation);
}

int CMoveJobItem::GetLevel(CString strLocation)
{
	return CLib::GetLevel(strLocation);
}

CString CMoveJobItem::GetErrInfo()
{
	return GetErrInfo(m_nErrCode);
}

CString CMoveJobItem::GetErrInfo(int nErrCode)
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

BOOL CMoveJobItem::IsValidLocation()
{
	return IsValidLocation(m_strLocation);
}

BOOL CMoveJobItem::IsValidLocation(CString strLocation)
{
	return CLib::IsValidLocation(strLocation);
}

BOOL CMoveJobItem::IsManualJob()
{
	if ( m_nJobType == JOB_TYPE_MANUAL_STO ||
	     m_nJobType == JOB_TYPE_MANUAL_RET ||
		 m_nJobType == JOB_TYPE_MANUAL_RTR ||
		 m_nJobType == JOB_TYPE_MANUAL_STN_TO_STN )
		 return TRUE;
	return FALSE;
}

BOOL CMoveJob::Load(CListCtrl* pListCtrl, int nJobType, int nStatus)
{
	POSITION pos;
	CMoveJobItem* pMoveJobItem;
	LV_ITEM lvitem;
	char szBuff[256];
	int i = 0;


	pListCtrl->DeleteAllItems();

	lvitem.iItem = 0;
	for (pos = m_MoveJobList.GetHeadPosition(); pos != NULL;)
	{
		pMoveJobItem = (CMoveJobItem *)m_MoveJobList.GetNext(pos);

		int nGroup = 0;

		if(nJobType < 13) {
			if (nJobType != JOB_TYPE_ALL && nJobType != pMoveJobItem->m_nLineNum)
				continue;
		}
		else
		{
			if (nJobType != JOB_TYPE_ALL && nJobType != nGroup)  
				continue;

//			if (pJobItem->GetStackerNum() != (nJobType - JOB_TYPE_CNT))
//				continue;
		}
		if (nStatus != JOB_STA_ALL)
		{
			if (nStatus == JOB_STA_PROGRESS && (pMoveJobItem->m_nStatus == JOB_STA_NEW || pMoveJobItem->m_nStatus == JOB_STA_ERR))
				continue;
			if (nStatus == JOB_STA_NEW && nStatus != pMoveJobItem->m_nStatus)
				continue;
			if (nStatus == JOB_STA_ERR && !pMoveJobItem->IsError())
				continue;
		}

		lvitem.mask = LVIF_TEXT | LVIF_IMAGE;
		lvitem.iSubItem = 0;
		sprintf(szBuff, "%.4d", pMoveJobItem->m_nLuggNum);
		lvitem.pszText = szBuff;
		lvitem.iImage = 0;
		pListCtrl->InsertItem(&lvitem);

		lvitem.mask = LVIF_TEXT;
		lvitem.iSubItem++;
		sprintf(szBuff, "%.4d", pMoveJobItem->m_nErrCode);
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		strcpy(szBuff, LPCTSTR(pMoveJobItem->GetStartPos()));
		pListCtrl->SetItem(&lvitem);


		lvitem.iSubItem++;
		strcpy(szBuff, LPCTSTR(pMoveJobItem->m_strProductID));
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		strcpy(szBuff, LPCTSTR(pMoveJobItem->GetStatus()));
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		sprintf(szBuff, LPCTSTR(pMoveJobItem->GetDestPos()));
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		sprintf(szBuff, "%d", pMoveJobItem->m_nLastPallet);
		if(pMoveJobItem->m_nLastPallet == 1)
			sprintf(szBuff, "%.2d", pMoveJobItem->m_nLastPallet);
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		strcpy(szBuff, LPCTSTR(pMoveJobItem->m_strGrade));
		pListCtrl->SetItem(&lvitem);


		lvitem.iSubItem++;
		sprintf(szBuff, LPCTSTR(pMoveJobItem->GetDestPos2()));
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		strcpy(szBuff, LPCTSTR(pMoveJobItem->GetHeight()));
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		sprintf(szBuff, "%d", pMoveJobItem->m_nBatchNo);
		pListCtrl->SetItem(&lvitem);

/*		lvitem.iSubItem++;
		sprintf(szBuff, "%d", pMoveJobItem->m_nBatchNo);
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		sprintf(szBuff, "%d", pMoveJobItem->m_nPalletNo);
		pListCtrl->SetItem(&lvitem);
*/
		lvitem.iSubItem++;
		sprintf(szBuff, "%d", pMoveJobItem->m_nLevelNo);
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		sprintf(szBuff, "%d", pMoveJobItem->m_nPriority);
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem++;
		strcpy(szBuff, LPCTSTR(pMoveJobItem->GetTimeStampString()));
		pListCtrl->SetItem(&lvitem);

		lvitem.iItem++;

	}
	
	m_bModified = FALSE;

	return TRUE;
}

BOOL CMoveJob::Add(int nLuggNum, int nJobType, CString strLocation, int nBatchNo, int nPallet, int nLevelNo, int nStartPos, int nDestPos, int nPriority, CString strProductID, CString strSecondLoc, int nStatus, CString strGrade, CString strQuantity, int nHeight, int nLineNum, int nLastPallet)
{
	CMoveJobItem* pMoveJobItem = new CMoveJobItem(nLuggNum, nJobType, strLocation, nBatchNo, nPallet, nLevelNo, nStartPos, nDestPos, nPriority, strProductID, strSecondLoc, nStatus, strGrade, strQuantity, nHeight, nLineNum, nLastPallet);

	return AddSort(pMoveJobItem);
}

BOOL CMoveJob::Add(CMoveJobItem* CMoveJobItem)
{
	return AddSort(CMoveJobItem);
}

BOOL CMoveJob::AddSort(CMoveJobItem* pMoveJobItem)
{
	POSITION pos;

//	m_csMoveJobAdd.Lock();

	CString strLog;
	strLog.Format("MoveAdd.. JobType=[%s], From=[%s], To=[%s], ��ǰ��=[%s], ��ǰ�ڵ�=[%s]", pMoveJobItem->GetType(), pMoveJobItem->GetStartPos(), pMoveJobItem->GetDestPos(),
															pMoveJobItem->m_strGrade, pMoveJobItem->m_strProductID);
	m_pDoc->m_pLog->Job(LOG_POS_SYSTEM, pMoveJobItem->m_nLuggNum, strLog);
	
	pos = m_MoveJobList.AddTail(pMoveJobItem);

	m_bModified = TRUE;

	if (pMoveJobItem->m_nStatus == JOB_STA_NEW)		
		Invoke(pMoveJobItem);

 	//Backup();

//	m_csMoveJobAdd.Unlock();

	return (pos != NULL) ? TRUE : FALSE;
}

int CMoveJob::GetSeqLuggNum()
{
	if (m_nLuggNum >= 999 || m_nLuggNum < 1)
        m_nLuggNum = 0;
    return ++ m_nLuggNum;
}

int CMoveJob::MoveGetSeqLuggNum()
{
	if (m_nLuggNum >= 9998 || m_nLuggNum < 9001)
        m_nLuggNum = 9000;
    return ++ m_nLuggNum;
}

BOOL CMoveJob::Remove(int nLuggNum)
{
	CMoveJobItem* pMoveJobItem = Find(nLuggNum);
	if (pMoveJobItem == NULL)
		return FALSE;
	return Remove(pMoveJobItem);
}

BOOL CMoveJob::Remove(CMoveJobItem* pMoveJobItem)
{
//	m_csMoveJobAdd.Lock();

	POSITION pos = m_MoveJobList.Find(pMoveJobItem);
	if (pos == NULL) 
	{
//		m_csMoveJobAdd.Unlock();
		return FALSE;
	}

	CString strLog;
	strLog.Format("MoveJob::Remove.. JobType=[%s], From=[%s], To=[%s]", pMoveJobItem->GetType(), pMoveJobItem->GetStartPos(), pMoveJobItem->GetDestPos());
	LOG->Job(LOG_POS_SYSTEM, pMoveJobItem->m_nLuggNum, strLog);

	m_MoveJobList.RemoveAt(pos);
	delete pMoveJobItem;

	m_bModified = TRUE;
//	Backup();
//	m_csMoveJobAdd.Unlock();

	return TRUE;
}

BOOL CMoveJob::Restore()
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
		strTemp.Format("CMoveJob::Restore.. File could not be opened e->m_cause=[%d]", e->m_cause);
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

BOOL CMoveJob::Backup()
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
		strTemp.Format("CMoveJob::Backup.. �۾����� ���� ���� ���� [%s]", CLib::GetSystemErrMsg(e->m_cause));
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

	//::PostMessage(m_pDoc->m_hwndView, WM_USER_JOB_NOTIFY, JOB_PROGRESS_DRAW, 0);

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

CMoveJobItem* CMoveJob::Find(int nLuggNum)
{
	POSITION pos;
	CMoveJobItem* pMoveJobItem;

//	m_csMoveJobAdd.Lock();

	for (pos = m_MoveJobList.GetHeadPosition(); pos != NULL;)
	{
		pMoveJobItem = (CMoveJobItem *)m_MoveJobList.GetNext(pos);

		if (pMoveJobItem->m_nLuggNum == nLuggNum)
		{
//			m_csMoveJobAdd.Unlock();
			return pMoveJobItem;
		}
	}		
//	m_csMoveJobAdd.Unlock();

	return NULL;
}

void CMoveJob::FindChange(int nLuggNum1, int nLuggNum2, int nStatus)
{
	POSITION pos;
	CMoveJobItem* pMoveJobItem;

//	m_csMoveJobAdd.Lock();

	for (pos = m_MoveJobList.GetHeadPosition(); pos != NULL;)
	{
		pMoveJobItem = (CMoveJobItem *)m_MoveJobList.GetNext(pos);

		if (pMoveJobItem->m_nLuggNum == nLuggNum1)
		{
			pMoveJobItem->m_nStatus = nStatus;
			continue;
		}

		if (pMoveJobItem->m_nLuggNum == nLuggNum2)
		{
			pMoveJobItem->m_nStatus = nStatus;
			continue;
		}
	}

//	m_csMoveJobAdd.Unlock();

}

CMoveJobItem* CMoveJob::FetchCvJobByStationNum(int nStatus, int nStationNum)
{
	POSITION pos;
	CMoveJobItem* pMoveJobItem;

//	m_csMoveJobAdd.Lock();

	for (pos = m_MoveJobList.GetHeadPosition(); pos != NULL;)
	{
		pMoveJobItem = (CMoveJobItem *)m_MoveJobList.GetNext(pos);

		if (nStationNum != -1 && pMoveJobItem->m_nStartPos != nStationNum)
			continue;

		if (pMoveJobItem->m_nStatus != nStatus) 
			continue;

		if (pMoveJobItem->GetPattern() == JOB_PATTERN_MOVE)
		{
//			m_csMoveJobAdd.Unlock();
			return pMoveJobItem;
		}
	}

//	m_csMoveJobAdd.Unlock();

	return NULL;
}

CMoveJobItem* CMoveJob::FetchByStatus(int nStatus, int nScNum)
{
	POSITION pos;
	CMoveJobItem* pMoveJobItem;

//	m_csMoveJobAdd.Lock();

	for (pos = m_MoveJobList.GetHeadPosition(); pos != NULL;)
	{
		pMoveJobItem = (CMoveJobItem *)m_MoveJobList.GetNext(pos);

		if (nScNum != -1 && pMoveJobItem->GetStackerNum() != nScNum)
			continue;

		if (pMoveJobItem->m_nStatus == nStatus)
		{
//			m_csMoveJobAdd.Unlock();
			return pMoveJobItem;
		}
	}
//	m_csMoveJobAdd.Unlock();

	return NULL;
}

CMoveJobItem* CMoveJob::FetchRgvJobByDestTrack(int nTrackNum)
{
	CMoveJobItem* pMoveJobItem;

//	m_csMoveJobAdd.Lock();

	for (POSITION pos = m_MoveJobList.GetHeadPosition(); pos != NULL;)
	{
		pMoveJobItem = (CMoveJobItem *)m_MoveJobList.GetNext(pos);

		if (pMoveJobItem->m_nStatus != JOB_STA_MOVE_RGV_OPER_COMPLETE)	
			continue;

		if (pMoveJobItem->m_nDestTrack == nTrackNum)
		{
//			m_csMoveJobAdd.Unlock();
			return pMoveJobItem;
		}
	}

//	m_csMoveJobAdd.Unlock();
	return NULL;
}

CMoveJobItem* CMoveJob::FetchRgvJobByDestTrack2(int nTrackNum, int nLuggNum)
{
	CMoveJobItem* pMoveJobItem;

//	m_csMoveJobAdd.Lock();

	for (POSITION pos = m_MoveJobList.GetHeadPosition(); pos != NULL;)
	{
		pMoveJobItem = (CMoveJobItem *)m_MoveJobList.GetNext(pos);

		if(pMoveJobItem->m_nStatus != JOB_STA_MOVE_RGV_OPER_COMPLETE)	
			continue;

		if(pMoveJobItem->m_nLuggNum == nLuggNum)
			continue;

		if(pMoveJobItem->m_nTwinJob != 2)
			continue;

		if (pMoveJobItem->m_nDestTrack == nTrackNum)
		{
//			m_csMoveJobAdd.Unlock();
			return pMoveJobItem;
		}
	}

//	m_csMoveJobAdd.Unlock();
	return NULL;
}


CMoveJobItem* CMoveJob::FetchCvRgvInvokeCheck(int nLuggNum)
{
	CMoveJobItem* pMoveJobItem;

//	m_csMoveJobAdd.Lock();

	for (POSITION pos = m_MoveJobList.GetHeadPosition(); pos != NULL;)
	{
		pMoveJobItem = (CMoveJobItem *)m_MoveJobList.GetNext(pos);

		//if(nLuggNum == pMoveJobItem->m_nLuggNum && pMoveJobItem->m_nStatus == JOB_STA_MOVE_RGV_OPER_REQUEST)
		//    return pMoveJobItem;

		if (pMoveJobItem->m_nStatus == JOB_STA_MOVE_RGV_OPER_REQUEST)	
		{
//			m_csMoveJobAdd.Unlock();
			return pMoveJobItem;
		}
	}

//	m_csMoveJobAdd.Unlock();

	return NULL;
}

BOOL CMoveJob::Invoke(int nLuggNum)
{
	CString strLog;
	CMoveJobItem* pMoveJobItem;

	if (nLuggNum == 0)
	{
		pMoveJobItem = FetchByStatus(JOB_STA_NEW);
		if (pMoveJobItem == NULL)
			return FALSE;
	} 
	else
	{
		pMoveJobItem = Find(nLuggNum);
		if (pMoveJobItem == NULL)
		{
			m_pDoc->m_pLog->Error(LOG_POS_SYSTEM, nLuggNum, "Can't find this luggage number.. can't invoke..");
			return FALSE;
		}
	}
	Invoke(pMoveJobItem);

	return TRUE;
}

BOOL CMoveJob::Invoke(CMoveJobItem* pMoveJobItem)
{
	CString strLog;

	switch (pMoveJobItem->GetPattern())
	{

	case	JOB_PATTERN_MOVE:
		pMoveJobItem->m_nStatus = JOB_STA_MOVE_CV_OPER_REQUEST;
		//Backup();

		//CV_ACTION(CV_1_PLC);
		m_pDoc->m_pLog->Job(LOG_POS_SYSTEM, pMoveJobItem->m_nLuggNum, "Invoke.. Conveyor ���� �䱸..");
		return TRUE;
	}

	return FALSE;
}

BOOL CMoveJob::FetchRgvJobRetrieve(int nTrackNum, CMoveJobItem** pFetchJobItem1, CMoveJobItem** pFetchJobItem2)
{
	POSITION pos;
	CMoveJobItem* pMoveJobItem;
	int nLuggNum1=0, nLuggNum2=0;

//	m_csMoveJobAdd.Lock();

	for (pos = m_MoveJobList.GetHeadPosition(); pos != NULL;)
	{
		pMoveJobItem = (CMoveJobItem *)m_MoveJobList.GetNext(pos);

		if (pMoveJobItem->m_nStatus != JOB_STA_MOVE_RGV_OPER_COMPLETE)	
			continue;

		if (pMoveJobItem->m_nDestTrack != nTrackNum)
			continue;

		nLuggNum1 = pMoveJobItem->m_nLuggNum;

		(*pFetchJobItem1) = pMoveJobItem;
		break;
	}

	for (pos = m_MoveJobList.GetHeadPosition(); pos != NULL;)
	{
		pMoveJobItem = (CMoveJobItem *)m_MoveJobList.GetNext(pos);

		if (pMoveJobItem->m_nStatus != JOB_STA_MOVE_RGV_OPER_COMPLETE)	
			continue;

		if (pMoveJobItem->m_nDestTrack != nTrackNum)
			continue;

		if(nLuggNum1 == pMoveJobItem->m_nLuggNum)
			continue;

		(*pFetchJobItem2) = pMoveJobItem;
		break;
	}


	if ((*pFetchJobItem1) == NULL && (*pFetchJobItem2) == NULL)
	{
//		m_csMoveJobAdd.Unlock();
		return FALSE;
	}

//	m_csMoveJobAdd.Unlock();

	return TRUE;
}

BOOL CMoveJob::BufferCvCountLock(int nSetLine, int nLineSeq)
{
	CMoveJobItem* pMoveJobItem;

	for ( POSITION pos = m_MoveJobList.GetHeadPosition(); pos != NULL; )
	{
		pMoveJobItem = (CMoveJobItem *)m_MoveJobList.GetNext(pos);

		if(pMoveJobItem->GetPattern() != JOB_PATTERN_MOVE )
			continue;

		if(pMoveJobItem->m_nLineNum != nSetLine)
			continue;

		if(pMoveJobItem->m_nBatchNo == nLineSeq)
			return TRUE;
	}

	return FALSE;
}

int CMoveJob::BufferLineCountCheck(int nSetLine, int nLineSeq, int nLuggNum)
{
	CMoveJobItem* pMoveJobItem;
	int nJobCount = 0;

	for ( POSITION pos = m_MoveJobList.GetHeadPosition(); pos != NULL; )
	{
		pMoveJobItem = (CMoveJobItem *)m_MoveJobList.GetNext(pos);

		if(pMoveJobItem->GetPattern() != JOB_PATTERN_MOVE )
			continue;

		if(pMoveJobItem->m_nLineNum != nSetLine)
			continue;

		if(pMoveJobItem->m_nBatchNo != nLineSeq)
			continue;

		if(pMoveJobItem->m_nStatus != JOB_STA_MOVE_CV_OPER_INVOKE)
			continue;

		if(pMoveJobItem->m_nLuggNum == nLuggNum)
			continue;

		//if(pMoveJobItem->m_bLock == FALSE)
		//	continue;

		//if(pMoveJobItem->m_nLastPallet == 1)
		//	return 16;

		nJobCount++;
	}

	return nJobCount;
}

CMoveJobItem* CMoveJob::BufferLineLastCheck(int nSetLine, int nLineSeq, CString strCodNum)
{
	CMoveJobItem* pMoveJobItem;

//	m_csMoveJobAdd.Lock();

	for(POSITION pos = m_MoveJobList.GetHeadPosition(); pos != NULL;)
	{
		pMoveJobItem = (CMoveJobItem *)m_MoveJobList.GetNext(pos);

		if(pMoveJobItem->GetPattern() != JOB_PATTERN_MOVE )
			continue;

		if(pMoveJobItem->m_nLineNum != nSetLine)
			continue;

		if(pMoveJobItem->m_nBatchNo != nLineSeq)
			continue;

		if(pMoveJobItem->m_nStatus != JOB_STA_MOVE_CV_BUFFER_OPER_INVOKE)
			continue;

		if(pMoveJobItem->m_strProductID != strCodNum)	
		{
//			m_csMoveJobAdd.Unlock();
			return pMoveJobItem;
		}
	}

//	m_csMoveJobAdd.Unlock();

	return NULL;
}

