// Log.cpp : implementation of the CLog class
//

#include "stdafx.h"
#include "Log.h"
#include "EcsDoc.h"

CLog::CLog(CEcsDoc* pDoc, CString strLogDir, CString strLogName)
{
	m_pDoc = pDoc;
	m_strLogDir = strLogDir;
	m_strLogName = strLogName;
	m_strLogFile = m_strLogDir + m_strLogName;
	//ExpiredFileRemove();
}

CLog::~CLog()
{
}

BOOL CLog::Start()
{
	const char* pFileName = LPCTSTR(m_strLogName);
	TRY
	{
		CFile * pFileOut = new CFile(pFileName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << "File could not be opened " << e->m_cause << "\n";
		#endif
		return FALSE;
	}
	END_CATCH

//    pFileOut->SeekToEnd();

//	pArchiveOut = new CArchive(m_pFileOut, CArchive::store);

	return	TRUE;
}

void CLog::Event(int nLogPos, int nLuggNum, CString strContent)
{
	if (!m_pDoc->m_pConfig->m_bEvent) return;

	Write(LOG_TYPE_EVENT, nLogPos, nLuggNum, strContent);
}

void CLog::Job(int nLogPos, int nLuggNum, CString strContent)
{
	if (!m_pDoc->m_pConfig->m_bJob) return;

	Write(LOG_TYPE_JOB, nLogPos, nLuggNum, strContent);
}

void CLog::Debug(int nLogPos, int nLuggNum, CString strContent)
{
	if (!m_pDoc->m_pConfig->m_bDebug) return;

	Write(LOG_TYPE_DEBUG, nLogPos, nLuggNum, strContent);
}

void CLog::Error(int nLogPos, int nLuggNum, CString strContent)
{
	if (!m_pDoc->m_pConfig->m_bError) return;

	Write(LOG_TYPE_ERROR, nLogPos, nLuggNum, strContent);
}

void CLog::Write(int nType, int nLogPos, int nLuggNum, CString strContent)
{
	CTime theTime = CTime::GetCurrentTime();
	CTimeSpan theTimeSpan(1, 0, 0, 0);

	CString strExpiredLogFile, strTemp;
	strTemp.Format("%.2d", theTime.GetDay());
	//m_strLogFile = m_strLogDir + m_strLogName + strTemp + ".elg";
	CString strLogFile = m_strLogFile + strTemp + ".elg";

	for (int i=0; i<4; i++)
	{
		theTime += theTimeSpan;
		strTemp.Format("%.2d", theTime.GetDay());
		strExpiredLogFile = m_strLogDir + m_strLogName + strTemp + ".elg";

		const char* pExpiredFileName = LPCTSTR(strExpiredLogFile);
		TRY
		{
			CFile::Remove(pExpiredFileName);
		}
		CATCH( CFileException, e )
		{
			#ifdef _DEBUG
				afxDump << "File " << pExpiredFileName << " cannot be removed\n";
			#endif
		}
		END_CATCH
	}
	
	CFile * pFileOut;

	//const char* pFileName = LPCTSTR(m_strLogFile);
	const char* pFileName = LPCTSTR(strLogFile);
	TRY
	{
		pFileOut = new CFile(pFileName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << "File could not be opened " << e->m_cause << "\n";
		#endif
		return;
	}
	END_CATCH

    pFileOut->SeekToEnd();

	CArchive * pArchiveOut = new CArchive(pFileOut, CArchive::store);

	//m_pDoc->DisplayMessage(strContent);

	CLogEvent LogEvent(nType, nLogPos, nLuggNum, strContent);
	LogEvent.Serialize(*pArchiveOut);

	delete pArchiveOut;
	delete pFileOut;
}

void CLog::ExpiredFileRemove()
{
	CTime theTime = CTime::GetCurrentTime();
	CString strExpiredLogFile, strTemp;
	CTimeSpan theTimeSpan(1, 0, 0, 0);

	for (int i=0; i<4; i++)
	{
		theTime += theTimeSpan;
		strTemp.Format("%.2d", theTime.GetDay());
		strExpiredLogFile = m_strLogDir + m_strLogName + strTemp + ".elg";

		const char* pExpiredFileName = LPCTSTR(strExpiredLogFile);
		TRY
		{
			CFile::Remove(pExpiredFileName);
		}
		CATCH( CFileException, e )
		{
			#ifdef _DEBUG
				afxDump << "File " << pExpiredFileName << " cannot be removed\n";
			#endif
		}
		END_CATCH
	}

}

// LogEvent Class
/////////////////////////////////////////////////////////////////////////
//IMPLEMENT_DYNCREATE(CLogEvent, CObject)
IMPLEMENT_SERIAL(CLogEvent, CObject, 0)

CLogEvent::CLogEvent(int nType, int nLogPos, int nLuggNum, CString strContent)
{
	char	szTime[32];

    _strtime(szTime);
	m_strTime.Format("%s", szTime);

	m_nPos       = nLogPos;
	m_nType      = nType;
	m_nLuggNum   = nLuggNum;
	m_strContent = strContent;
}

void CLogEvent::Serialize(CArchive& ar)
{
	DWORD dwTemp;

	if (ar.IsStoring())
	{
		ar << m_strTime;
		ar << (DWORD)m_nType;
		ar << (DWORD)m_nPos;
		ar << (DWORD)m_nLuggNum;
		ar << m_strContent;
	}
	else
	{
		ar >> m_strTime;
		ar >> dwTemp;
		m_nType = dwTemp;
		ar >> dwTemp;
		m_nPos = dwTemp;
		ar >> dwTemp;
		m_nLuggNum = dwTemp;
		ar >> m_strContent;
	}
}

CString CLogEvent::GetPosition()
{
	return GetPosition(m_nPos);
}

CString CLogEvent::GetPosition(int nPos)
{
	switch (nPos)
	{
	case	LOG_POS_ALL:
		return CString("ALL");
	case	LOG_POS_SYSTEM:
		return CString("SYS");
	case	LOG_POS_SC:
		return CString("SC");
	case	LOG_POS_CV:
		return CString("CV");
	case	LOG_POS_RGV:
		return CString("RTV");
	case	LOG_POS_HOST:
		return CString("HOST");
	case	LOG_POS_ECS:
		return CString("ECS");
	default:
		return CString("DEF");
	}
}

BOOL CLog::Load(CListCtrl* pListCtrl, int nDay, int nType, int nPos, int nLuggNum, int nFrom, int nTo)
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	CString strTemp;
	strTemp.Format("%.2d", nDay);
	CString strLogFile = m_strLogDir + m_strLogName + strTemp + ".elg";

	CFile * pFileIn;
	const char* pFileName = LPCTSTR(strLogFile);
	TRY
	{
		pFileIn = new CFile(pFileName, CFile::modeRead);
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << "File could not be opened " << e->m_cause << "\n";
		#endif
		return FALSE;
	}
	END_CATCH

	DWORD dwFileLength = pFileIn->GetLength(), dwCurrentPos = 0;
	CArchive * pArchiveIn = new CArchive(pFileIn, CArchive::load);

	CLogEvent LogEvent;
	LV_ITEM lvitem;
	char szBuff[256];
	lvitem.mask = LVIF_TEXT;

	pListCtrl->DeleteAllItems();

	for (int i = 0;;)
	{
		if (dwFileLength <= dwCurrentPos) break;

		TRY
		{
			LogEvent.Serialize(*pArchiveIn);
		}
		CATCH( CFileException, e )
		{
			CString strTemp;
			strTemp.Format("Something wrong while serializing, Cause=[");
			strTemp += e->m_cause + "]";
			AfxMessageBox(strTemp);
			break;
		}
		END_CATCH

		dwCurrentPos += LogEvent.m_strContent.GetLength() + 22;

		if (LogEvent.m_strTime.IsEmpty()) continue;

		int nHour = atoi(LogEvent.m_strTime.Mid(0, 2));
		if ((nLuggNum != 0 && nLuggNum != LogEvent.m_nLuggNum) || 
			(nType != LOG_TYPE_ALL && nType != LogEvent.m_nType) ||
			(nPos != LOG_POS_ALL && nPos != LogEvent.m_nPos) ||
			nHour < nFrom || nHour >= nTo) continue;

		lvitem.iItem = i++;
		lvitem.iSubItem = 0;
		strcpy(szBuff, LPCTSTR(LogEvent.m_strTime));
		lvitem.pszText = szBuff;
		pListCtrl->InsertItem(&lvitem);

		lvitem.iSubItem = 1;
		if (LogEvent.m_nLuggNum == LOG_SYSTEM)
			sprintf(lvitem.pszText, "");
		else
			sprintf(lvitem.pszText, "%.4d", LogEvent.m_nLuggNum);
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem = 2;
		strcpy(szBuff, LPCTSTR(LogEvent.GetPosition()));
		lvitem.pszText = szBuff;
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem = 3;
		strcpy(szBuff, LPCTSTR(LogEvent.m_strContent));
		lvitem.pszText = szBuff;
		pListCtrl->SetItem(&lvitem);

		if (i > LOG_DISP_MAX) break;
	}

	delete pArchiveIn;
	delete pFileIn;

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));

	return TRUE;
}

