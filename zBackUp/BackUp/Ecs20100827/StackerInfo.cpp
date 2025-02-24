// StackerInfo.cpp : implementation of the CStackerInfo class
//

#include "stdafx.h"
#include "StackerInfo.h"
#include "EcsDoc.h"

IMPLEMENT_DYNCREATE(CInfo, CObject)
IMPLEMENT_DYNCREATE(CStackerInfo, CInfo)

CInfo::CInfo()
{
}

CInfo::CInfo(CEcsDoc* pDoc, CString strFileName)
{
	m_pDoc = pDoc;
	m_strFileName = strFileName;

	m_bModified = TRUE;
}

CInfo::~CInfo()
{
}

void CInfo::Serialize(CArchive& ar)
{
}

CStackerInfo::CStackerInfo(CEcsDoc* pDoc, CString strFileName) : CInfo(pDoc, strFileName) 
{ 
	m_bStoreSuspend = m_bRetrieveSuspend = FALSE; 
	m_bInvoke = FALSE;
	m_bSecondInvoke = FALSE;
	m_nPrevRtn = ROUTINE_STORE;
	m_nLuggNum = 0;
	m_nSecondLuggNum = 0;
	m_nInternalLuggNum = 0;
	m_nSecondInternalLuggNum = 0;
	m_ucMode = SC_MODE_REMOTE;
	m_ucStatus = m_ucPrevStatus =0;
	m_wErrCode = 0;
	m_wPrevErrCode = 0;
	m_wSaveErrCode = 0;
	m_nDirection = 0;
	m_nHorizontalPos = 0;
	m_bConfirmed = FALSE;
}

void CStackerInfo::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_bModified;
		ar << m_bStoreSuspend;
		ar << m_bRetrieveSuspend;
		ar << m_nLuggNum;
		ar << m_nSecondLuggNum;
		ar << m_ucMode;
		ar << m_ucStatus;
		ar << m_ucProdLoad;
		ar << m_ucSecondProdLoad;
		ar << m_wErrCode;
		ar << m_wPrevErrCode;
		ar << m_wSaveErrCode;
		ar << m_nHorizontalPos;
		ar << m_nVerticalPos;
		ar << m_ucTransaction;
		ar << m_ucInternalTransaction;
		ar << m_ucSecondTransaction;
		ar << m_ucJobType;
		ar << m_ucSecondJobType;
		ar << m_bInternalJobType;
		ar << m_bSecondInternalJobType;
		ar << m_nInternalLuggNum;
		ar << m_nSecondInternalLuggNum;
		ar << m_nPrevRtn;
		ar << m_bInvoke;
		ar << m_bSecondInvoke;
		ar << m_tJobStart;
		ar << m_tJobEnd;
		ar << m_tErrorStart;
		ar << m_tErrorEnd;
		ar << m_nDirection;
		ar << m_bConfirmed;
		ar << m_ucPrevStatus;
	}
	else
	{
		ar >> m_bModified;
		ar >> m_bStoreSuspend;
		ar >> m_bRetrieveSuspend;
		ar >> m_nLuggNum;
		ar >> m_nSecondLuggNum;
		ar >> m_ucMode;
		ar >> m_ucStatus;
		ar >> m_ucProdLoad;
		ar >> m_ucSecondProdLoad;
		ar >> m_wErrCode;
		ar >> m_wPrevErrCode;
		ar >> m_wSaveErrCode;
		ar >> m_nHorizontalPos;
		ar >> m_nVerticalPos;
		ar >> m_ucTransaction;
		ar >> m_ucInternalTransaction;
		ar >> m_ucSecondTransaction;
		ar >> m_ucJobType;
		ar >> m_ucSecondJobType;
		ar >> m_bInternalJobType;
		ar >> m_bSecondInternalJobType;
		ar >> m_nInternalLuggNum;
		ar >> m_nSecondInternalLuggNum;
		ar >> m_nPrevRtn;
		ar >> m_bInvoke;
		ar >> m_bSecondInvoke;
		ar >> m_tJobStart;
		ar >> m_tJobEnd;
		ar >> m_tErrorStart;
		ar >> m_tErrorEnd;
		ar >> m_nDirection;
		ar >> m_bConfirmed;
		ar >> m_ucPrevStatus;
	}
}

BOOL CInfo::Restore()
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
		strTemp.Format("CInfo::Restore.. File could not be opened e->m_cause=[%d]", e->m_cause);
		m_pDoc->m_pLog->Error(LOG_POS_SC, LOG_SYSTEM, strTemp);
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

BOOL CInfo::Backup()
{
	CFile* pFile;
	TRY
	{
		const char* pFileName = LPCTSTR(m_strFileName);
		pFile = new CFile(pFileName, CFile::modeCreate | CFile::modeWrite);
	}
	CATCH( CFileException, e )
	{
		CString strTemp;
		strTemp.Format("CInfo::Restore.. File could not be opened e->m_cause=[%d]", e->m_cause);
		m_pDoc->m_pLog->Error(LOG_POS_SC, LOG_SYSTEM, strTemp);
		return FALSE;
	}
	END_CATCH

	CArchive* pArchive = new CArchive(pFile, CArchive::store);

	Serialize(*pArchive);

	delete pArchive;
	delete pFile;

	return TRUE;
}
