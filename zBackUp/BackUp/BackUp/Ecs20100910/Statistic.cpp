// Statistic.cpp : implementation of the CStatistic class
//

#include "stdafx.h"
#include "Statistic.h"
#include "EcsDoc.h"
#include "Lib.h"
#include <time.h>
#include <stdlib.h>

IMPLEMENT_DYNCREATE(CStatistic, CObject)

CStatistic::CStatistic()
{
}

CStatistic::CStatistic(CEcsDoc* pDoc, CString strDir, CString strStcFileName, CString strErrFileName)
{
	m_pDoc = pDoc; 
	m_strDir = strDir;
	m_strStcFileName = strStcFileName;
	m_strErrFileName = strErrFileName;
	ExpiredFileRemove();
	Restore();
}

CStatistic::~CStatistic()
{
	Backup();
}

void CStatistic::Serialize(CArchive& ar)
{
}

void CStatistic::Backup()
{
	CTime theTime = CTime::GetCurrentTime();
	CString strFileName, strTemp;
	struct tm	*pStartTm;

	int	nToday=theTime.GetDay();
	pStartTm = localtime(&m_sSTC[0].tBeginTime);
	if(pStartTm->tm_mday == nToday)
	{
		WriteProfile();
		WriteErrCodeFile();
		return;
	}
	
	ExpiredFileRemove();
	Restore();
	return;
}

void CStatistic::Restore()
{
	char szSection[256];
	time_t	tBeginTm;

	CTime theTime = CTime::GetCurrentTime();
	CString strStcFileName, strErrFileName, strTemp;

	strTemp.Format("%.2d", theTime.GetDay());
	strStcFileName = m_strDir + m_strStcFileName + strTemp + ".info";
	strErrFileName = m_strDir + m_strErrFileName + strTemp + ".dat";

	tBeginTm = (time_t) GetPrivateProfileInt("EcsBegin", "BeginTime", 0, strStcFileName);
	if(tBeginTm==0)		tBeginTm = InitProfile();

	for ( int i = 0; i < SC_CNT; i++ )
	{
		sprintf(szSection, "Stacker%d", i + 1);
		m_sSTC[i].tBeginTime = tBeginTm;
		m_sSTC[i].tOnlineWorkTime     = (time_t) GetPrivateProfileInt(szSection, "OnlineWorkTime", 0, strStcFileName);
		m_sSTC[i].tOfflineWorkTime    = (time_t) GetPrivateProfileInt(szSection, "OfflineWorkTime", 0, strStcFileName);
		m_sSTC[i].tOnlineTroubleTime  = (time_t) GetPrivateProfileInt(szSection, "OnlineTroubleTime", 0, strStcFileName);
		m_sSTC[i].tOfflineTroubleTime = (time_t) GetPrivateProfileInt(szSection, "OfflineTroubleTime", 0, strStcFileName);
		m_sSTC[i].nOnlineJobSum       = GetPrivateProfileInt(szSection, "OnlineJobSum", 0, strStcFileName);
		m_sSTC[i].nOfflineJobSum      = GetPrivateProfileInt(szSection, "OfflineJobSum", 0, strStcFileName);
		m_sSTC[i].nErrorSum           = GetPrivateProfileInt(szSection, "ErrorSum", 0, strStcFileName);
	}

	CFile ErrCodeFile;
	CFileException e;

	if ( !ErrCodeFile.Open(LPCTSTR(strErrFileName), CFile::modeRead, &e) )
	{
		memset(m_sCode, 0x00, sizeof(m_sCode)-1);
		if( ErrCodeFile.Open(LPCTSTR(strErrFileName), CFile::modeCreate | CFile::modeWrite, &e) )
		{
			ErrCodeFile.Write(m_sCode, sizeof(m_sCode));
			ErrCodeFile.Close();
		}
		return;
	}

	ErrCodeFile.Read(m_sCode, sizeof(m_sCode));
	ErrCodeFile.Close();
}

void CStatistic::ExpiredFileRemove()
{
	CTime theTime = CTime::GetCurrentTime();
	CString strExpiredStcFile, strExpiredErrFile, strTemp;
	CTimeSpan theTimeSpan(1, 0, 0, 0);


	for(int i = 0; i < 4; i++)
	{
		theTime += theTimeSpan;
		strTemp.Format("%.2d", theTime.GetDay());
		strExpiredStcFile = m_strDir + m_strStcFileName + strTemp + ".info";
		strExpiredErrFile = m_strDir + m_strErrFileName + strTemp + ".dat";

		const char* pExpiredStcFileName = LPCTSTR(strExpiredStcFile);
		TRY
		{
			CFile::Remove(pExpiredStcFileName);
		}
		CATCH( CFileException, e )
		{
			#ifdef _DEBUG
				afxDump << "File " << pExpiredStcFileName << " cannot be removed\n";
			#endif
		}
		END_CATCH

		const char* pExpiredErrFileName = LPCTSTR(strExpiredErrFile);
		TRY
		{
			CFile::Remove(pExpiredErrFileName);
		}
		CATCH( CFileException, e )
		{
			#ifdef _DEBUG
				afxDump << "File " << pExpiredErrFileName << " cannot be removed\n";
			#endif
		}
		END_CATCH
	}

}

time_t CStatistic::InitProfile() 
{
	CString	strStcFileName, strTemp;
	CTime theTime = CTime::GetCurrentTime();
	strTemp.Format("%.2d", theTime.GetDay());
	strStcFileName = m_strDir + m_strStcFileName + strTemp + ".info";
	CFile * pFileOut;
	char szBuff[256];
	time_t	start;

	time( &start );
	const char* pStcFileName = LPCTSTR(strStcFileName);
	TRY
	{
		pFileOut = new CFile(pStcFileName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << "File could not be opened " << e->m_cause << "\n";
		#endif
		return	start;
	}
	END_CATCH

	delete pFileOut;

	for ( int i=0; i<SC_CNT; i++ )
	{
		m_sSTC[i].tBeginTime = start;
		m_sSTC[i].tOnlineWorkTime = 0;
		m_sSTC[i].tOfflineWorkTime = 0;
		m_sSTC[i].tOnlineTroubleTime = 0;
		m_sSTC[i].tOfflineTroubleTime = 0;
		m_sSTC[i].nOnlineJobSum = 0;
		m_sSTC[i].nOfflineJobSum = 0;
		m_sSTC[i].nErrorSum = 0;
	}
	sprintf(szBuff, "%ld", start);
	BOOL rt=WritePrivateProfileString("EcsBegin", "BeginTime", szBuff, strStcFileName);
	WriteProfile();
	return	start;
}

void CStatistic::WriteProfile() 
{
	char szSection[256];
	char szBuff[256];

	CTime theTime = CTime::GetCurrentTime();
	CString strFileName, strTemp;

	strTemp.Format("%.2d", theTime.GetDay());
	strFileName = m_strDir + m_strStcFileName + strTemp + ".info";

	for ( int i = 0; i < SC_CNT; i++ )
	{
		sprintf(szSection, "Stacker%d", i + 1);
		sprintf(szBuff, "%ld", m_sSTC[i].tOnlineWorkTime);
		WritePrivateProfileString(szSection, "OnlineWorkTime", szBuff, strFileName);
		sprintf(szBuff, "%ld", m_sSTC[i].tOfflineWorkTime);
		WritePrivateProfileString(szSection, "OfflineWorkTime", szBuff, strFileName);
		sprintf(szBuff, "%ld", m_sSTC[i].tOnlineTroubleTime);
		WritePrivateProfileString(szSection, "OnlineTroubleTime", szBuff, strFileName);
		sprintf(szBuff, "%ld", m_sSTC[i].tOfflineTroubleTime);
		WritePrivateProfileString(szSection, "OfflineTroubleTime", szBuff, strFileName);
		sprintf(szBuff, "%d", m_sSTC[i].nOnlineJobSum);
		WritePrivateProfileString(szSection, "OnlineJobSum", szBuff, strFileName);
		sprintf(szBuff, "%d", m_sSTC[i].nOfflineJobSum);
		WritePrivateProfileString(szSection, "OfflineJobSum", szBuff, strFileName);
		sprintf(szBuff, "%d", m_sSTC[i].nErrorSum);
		WritePrivateProfileString(szSection, "ErrorSum", szBuff, strFileName);
	}
}

void CStatistic::WriteErrCodeFile() 
{
	CTime theTime = CTime::GetCurrentTime();
	CString strErrFileName, strTemp;
	CFile	ErrCodeFile;
	CFileException e;


	strTemp.Format("%.2d", theTime.GetDay());
	strErrFileName = m_strDir + m_strErrFileName + strTemp + ".dat";

	if( ErrCodeFile.Open(LPCTSTR(strErrFileName), CFile::modeCreate | CFile::modeWrite, &e) )
	{
		ErrCodeFile.Write(m_sCode, sizeof(m_sCode));
		ErrCodeFile.Close();
	}
}

void CStatistic::RegistErrCode(int nScNum, int nErrCode)
{
	if(nScNum < 0 || nScNum >= SC_CNT)	return;

	for(int i=0; i<SC_ERROR_KIND_CNT; i++)
	{
		if(m_sCode[nScNum][i].nErrorCode == 0 && m_sCode[nScNum][i].nCount == 0)
		{
			m_sCode[nScNum][i].nScNum = nScNum + 1;
			m_sCode[nScNum][i].nErrorCode = nErrCode;
			m_sCode[nScNum][i].nCount = 1;
			return;
		}

		if(m_sCode[nScNum][i].nErrorCode &&
				m_sCode[nScNum][i].nErrorCode == nErrCode)
		{
			m_sCode[nScNum][i].nCount++;
			return;
		}

		if(m_sCode[nScNum][i].nErrorCode &&
				m_sCode[nScNum][i].nErrorCode != nErrCode)	continue;
	}

	return;
}

void CStatistic::ResetStatisticInfo()
{
	CFile ErrCodeFile;
	CFileException e;

	InitProfile();
	CTime theTime = CTime::GetCurrentTime();
	CString strErrFileName, strTemp;
	strTemp.Format("%.2d", theTime.GetDay());
	strErrFileName = m_strDir + m_strErrFileName + strTemp + ".dat";
	memset(m_sCode, 0x00, sizeof(m_sCode));
	if( ErrCodeFile.Open(LPCTSTR(strErrFileName), CFile::modeCreate | CFile::modeWrite, &e) )
	{
		ErrCodeFile.Write(m_sCode, sizeof(m_sCode));
		ErrCodeFile.Close();
	}
}

void CStatistic::Load(CListCtrl *pListCtrl, int nDay, int nScNum, int nErrCode)
{
	int cdecl NjcCompare(const void *e1, const void *e2);
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	SStatisticErrorCnt	sStcErr[SC_CNT][SC_ERROR_KIND_CNT];
	CString strTemp;
	strTemp.Format("%.2d", nDay);
	CString strErrFileName = m_strDir + m_strErrFileName + strTemp + ".dat";

	CFile ErrCodeFile;
	CFileException e;

	if ( !ErrCodeFile.Open(LPCTSTR(strErrFileName), CFile::modeRead, &e) )
	{
		strTemp.Format("Something wrong while serializing, Cause=[");
		strTemp += e.m_cause + "]";
		AfxMessageBox(strTemp);
		return;
	}

	memset(sStcErr, 0x00, sizeof(sStcErr));
	ErrCodeFile.Read(sStcErr, sizeof(sStcErr));
	ErrCodeFile.Close();

	if (nScNum < 0 || nScNum > SC_CNT)	return;
	if(nScNum)
		qsort(sStcErr[nScNum-1], (size_t) SC_ERROR_KIND_CNT, (size_t) sizeof(struct SStatisticErrorCnt), NjcCompare);
	else
		qsort(sStcErr[0], (size_t) (SC_ERROR_KIND_CNT * SC_CNT), (size_t) sizeof(struct SStatisticErrorCnt), NjcCompare);

	LV_ITEM lvitem;
	char szBuff[256];
	lvitem.mask = LVIF_TEXT;

	pListCtrl->DeleteAllItems();

	for(int i=0, nNum=0; nNum < SC_CNT; nNum++)
		for(int	nKind=0; nKind < SC_ERROR_KIND_CNT; nKind++)
		{
			if (nScNum != 0 && sStcErr[nNum][nKind].nScNum != nScNum)	continue;
			if (nErrCode != 0 && sStcErr[nNum][nKind].nErrorCode != nErrCode)	continue;
			if (sStcErr[nNum][nKind].nCount==0 || sStcErr[nNum][nKind].nErrorCode==0)	continue;

			lvitem.iItem = i++;
			lvitem.iSubItem = 0;
			sprintf(szBuff, "S/C #%d", sStcErr[nNum][nKind].nScNum);
			lvitem.pszText = szBuff;
			pListCtrl->InsertItem(&lvitem);

			lvitem.iSubItem = 1;
			sprintf(szBuff, "%d", sStcErr[nNum][nKind].nErrorCode);
			lvitem.pszText = szBuff;
			pListCtrl->SetItem(&lvitem);

			lvitem.iSubItem = 2;
			sprintf(szBuff, "    %d", sStcErr[nNum][nKind].nCount);
			lvitem.pszText = szBuff;
			pListCtrl->SetItem(&lvitem);

			lvitem.iSubItem = 3;
			sprintf(szBuff, "%s", CLib::GetStackerErrorInfo(sStcErr[nNum][nKind].nErrorCode));
			lvitem.pszText = szBuff;
			pListCtrl->SetItem(&lvitem);
		}

	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

int cdecl NjcCompare(const void *elem1, const void *elem2)
{
	struct SStatisticErrorCnt *e1, *e2;
	e1 = (SStatisticErrorCnt *) elem1;
	e2 = (SStatisticErrorCnt *) elem2;

	if(e1->nCount < e2->nCount)							return  1;
	else if(e1->nCount == e2->nCount)
	{
		if(e1->nScNum > e2->nScNum)						return  1;
		else if(e1->nScNum == e2->nScNum)
		{
			if(e1->nErrorCode > e2->nErrorCode)			return  1;
			else if(e1->nErrorCode == e2->nErrorCode)	return  0;
			else										return -1;
		}
		else											return -1;
	}
	else												return -1;
}
