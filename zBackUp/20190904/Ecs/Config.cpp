// Config.cpp : implementation of the CConfig class
//

#include "stdafx.h"
#include "Config.h"
#include "EcsDoc.h"

IMPLEMENT_DYNCREATE(CConfig, CObject)

CConfig::CConfig()
{
}

CConfig::CConfig(CEcsDoc* pDoc)
{
	m_pDoc = pDoc; 
	m_bConnect=0;
	m_bRetry=0;
	m_strHostAddr="";
	m_nHostPort=0;

	m_nEcsSvPort=8500;

	GetProfile();
}

CConfig::~CConfig()
{

}

void CConfig::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_strMainLogName;
		ar << m_strHostAddr;
		ar << m_nHostPort;

		ar << m_nEcsSvPort;
	}
	else
	{
		ar >> m_strMainLogName;
		ar >> m_strHostAddr;
		ar >> m_nHostPort;

		ar >> m_nEcsSvPort;
	}
}

BOOL CConfig::Restore()
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
		strTemp.Format("CConfig::Restore.. File could not be opened e->m_cause=[%d]", e->m_cause);
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

BOOL CConfig::Backup()
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
		strTemp.Format("CConfig::Backup.. File could not be opened e->m_cause=[%d]", e->m_cause);
		m_pDoc->m_pLog->Error(LOG_POS_SYSTEM, LOG_SYSTEM, strTemp);
		return FALSE;
	}
	END_CATCH

	CArchive* pArchive = new CArchive(pFile, CArchive::store);

	Serialize(*pArchive);

	delete pArchive;
	delete pFile;

	return TRUE;
}

void CConfig::Load(CListCtrl* pListCtrl) 
{
	char szText[256];
	LV_ITEM lvitem;
	lvitem.mask = LVIF_TEXT;

	pListCtrl->DeleteAllItems();

	for (int i = 0; i < SC_CNT-1; i++ )	//스테커 교체 시 수정 
	{
		char szSection[30];
		sprintf(szSection, "Stacker%d", i + 1);
		lvitem.iItem = i;
		lvitem.iSubItem = 0;
		sprintf(szText, "%s", szSection);
		lvitem.pszText = szText;
		pListCtrl->InsertItem(&lvitem);

		lvitem.iSubItem = 1;
		sprintf(szText, "%s", m_sScPort[i].szComName);
		lvitem.pszText = szText;
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem = 2;
		sprintf(szText, "%d", m_sScPort[i].nBaudRate);
		lvitem.pszText = szText;
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem = 3;
		sprintf(szText, "%d", m_sScPort[i].nParity);
		lvitem.pszText = szText;
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem = 4;
		sprintf(szText, "%d", m_sScPort[i].nStopBits);
		lvitem.pszText = szText;
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem = 5;
		sprintf(szText, "%d", m_sScPort[i].nBitsPerChar);
		lvitem.pszText = szText;
		pListCtrl->SetItem(&lvitem);
	}

	for (i = 0; i < RGV_CNT; i++)
	{
		char szSection[30];
		sprintf(szSection, "Rtv%d", i+1);
		lvitem.iItem = i+SC_CNT-1;
		lvitem.iSubItem = 0;
		sprintf(szText, "%s", szSection);
		lvitem.pszText = szText;
		pListCtrl->InsertItem(&lvitem);

		lvitem.iSubItem = 1;
		sprintf(szText, "%s", m_sRgvPort[i].szComName);
		lvitem.pszText = szText;
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem = 2;
		sprintf(szText, "%d", m_sRgvPort[i].nBaudRate);
		lvitem.pszText = szText;
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem = 3;
		sprintf(szText, "%d", m_sRgvPort[i].nParity);
		lvitem.pszText = szText;
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem = 4;
		sprintf(szText, "%d", m_sRgvPort[i].nStopBits);
		lvitem.pszText = szText;
		pListCtrl->SetItem(&lvitem);

		lvitem.iSubItem = 5;
		sprintf(szText, "%d", m_sRgvPort[i].nBitsPerChar);
		lvitem.pszText = szText;
		pListCtrl->SetItem(&lvitem);
	}
}

CString CConfig::GetRgvDeviceName(int nRgvNum)
{
	return m_sRgvPort[nRgvNum].strDevice;
}

CString CConfig::GetScDeviceName(int nScNum)
{
	return m_sScPort[nScNum].strDevice;
}

void CConfig::GetProfile() 
{
	char szSection[256];
	char szBuff[256];

#ifdef OPT_HOST_NETWORK_INTERFACE_USE
	GetPrivateProfileString("Host", "Address", "", szBuff, 16, ECS_INI_FILE);
	m_strHostAddr = szBuff;
	m_nHostPort = GetPrivateProfileInt("Host", "Port", 700, ECS_INI_FILE);
	m_bConnect = (BOOL)GetPrivateProfileInt("Host", "Connect", 1, ECS_INI_FILE);
	m_bRetry = (BOOL)GetPrivateProfileInt("Host", "Retry", 1, ECS_INI_FILE);
#endif

#ifdef OPT_HOST_SAP_INTERFACE_USE
	GetPrivateProfileString("SapHost", "OrderFile", "", szBuff, 100, ECS_INI_FILE);
	m_strOrderFile = szBuff;
	GetPrivateProfileString("SapHost", "ClientLocation", "", szBuff, 100, ECS_INI_FILE);
	m_strClientLocation = szBuff;
#endif

	m_nEcsSvPort = GetPrivateProfileInt("EcsSv", "Port", 700, ECS_INI_FILE);
	m_bConnect = (BOOL)GetPrivateProfileInt("EcsSv", "Connect", 1, ECS_INI_FILE);
	m_bRetry = (BOOL)GetPrivateProfileInt("EcsSv", "Retry", 1, ECS_INI_FILE);


	GetPrivateProfileString("Password", "Password", "", szBuff, 100, ECS_INI_FILE);
	m_strPassword = szBuff;

	m_bJob   = (BOOL)GetPrivateProfileInt("Main", "Job", 1, ECS_INI_FILE);
	m_bEvent = (BOOL)GetPrivateProfileInt("Main", "Event", 1, ECS_INI_FILE);
	m_bError = (BOOL)GetPrivateProfileInt("Main", "Error", 1, ECS_INI_FILE);
	m_bDebug = (BOOL)GetPrivateProfileInt("Main", "Debug", 1, ECS_INI_FILE);
	m_bBeep  = (BOOL)GetPrivateProfileInt("Main", "Beep", 1, ECS_INI_FILE);

	for ( int i = 0; i < CV_PLC_CNT; i++ )
	{
		sprintf(szSection, "Conveyor%d", i + 1);
		GetPrivateProfileString(szSection, "Address", "", szBuff, 256, ECS_INI_FILE);
		m_sCvPort[i].strAddress = szBuff;
		m_sCvPort[i].nPort = GetPrivateProfileInt(szSection, "Port", 7000, ECS_INI_FILE);
		m_sCvPort[i].bConnect  = (UINT)GetPrivateProfileInt(szSection, "Connect", 1, ECS_INI_FILE);
		m_sCvPort[i].bRetry    = (UINT)GetPrivateProfileInt(szSection, "Retry", 1, ECS_INI_FILE);
		m_sCvPort[i].dwReadTimeOut = GetPrivateProfileInt(szSection, "ReadTimeOut", 2000, ECS_INI_FILE);

//		m_strCvAddr[i] = szBuff;
//		m_nCvPort[i] = GetPrivateProfileInt(szSection, "Port", 7000, ECS_INI_FILE);
//		m_bCvConnect[i]  = (UINT)GetPrivateProfileInt(szSection, "Connect", 1, ECS_INI_FILE);
//		m_bCvRetry[i]    = (UINT)GetPrivateProfileInt(szSection, "Retry", 1, ECS_INI_FILE);

	}


	for (i = 0; i < SC_CNT-1; i++ )
	{
		sprintf(szSection, "Stacker%d", i + 1);
		GetPrivateProfileString(szSection, "ComName", "", m_sScPort[i].szComName, 30, ECS_INI_FILE);
		m_sScPort[i].nBaudRate = GetPrivateProfileInt(szSection, "BaudRate", 2400, ECS_INI_FILE);
		m_sScPort[i].nParity = GetPrivateProfileInt(szSection, "Parity", 0, ECS_INI_FILE);
		m_sScPort[i].nStopBits = GetPrivateProfileInt(szSection, "StopBits", 0, ECS_INI_FILE);
		m_sScPort[i].nBitsPerChar = GetPrivateProfileInt(szSection, "BitsPerChar", 8, ECS_INI_FILE);
	}

		sprintf(szSection, "Stacker%d", 6);
		m_sScPort[i].strDevice = szSection;
		GetPrivateProfileString(szSection, "Address", "", szBuff, 256, ECS_INI_FILE);
		m_sScPort[5].strAddress = szBuff;
		m_sScPort[5].nPort = GetPrivateProfileInt(szSection, "Port", 7000, ECS_INI_FILE);
		m_sScPort[5].bConnect  = (UINT)GetPrivateProfileInt(szSection, "Connect", 1, ECS_INI_FILE);
		m_sScPort[5].bRetry    = (UINT)GetPrivateProfileInt(szSection, "Retry", 1, ECS_INI_FILE);
		m_sScPort[5].dwReadTimeOut = GetPrivateProfileInt(szSection, "ReadTimeOut", 2000, ECS_INI_FILE);


	for (i = 0; i < RGV_CNT; i++ )
	{
		sprintf(szSection, "Rtv%d", i + 1);
		m_sRgvPort[i].strDevice = szSection;
		GetPrivateProfileString(szSection, "ComName", "", m_sRgvPort[i].szComName, 30, ECS_INI_FILE);
		m_sRgvPort[i].nBaudRate = GetPrivateProfileInt(szSection, "BaudRate", 2400, ECS_INI_FILE);
		m_sRgvPort[i].nParity = GetPrivateProfileInt(szSection, "Parity", 0, ECS_INI_FILE);
		m_sRgvPort[i].nStopBits = GetPrivateProfileInt(szSection, "StopBits", 0, ECS_INI_FILE);
		m_sRgvPort[i].nBitsPerChar = GetPrivateProfileInt(szSection, "BitsPerChar", 8, ECS_INI_FILE);
		m_sRgvPort[i].dwReadTimeOut = GetPrivateProfileInt(szSection, "ReadTimeOut", 2000, ECS_INI_FILE);
	}

	GetPrivateProfileString("Ecs", "Address", "", szBuff, 256, ECS_INI_FILE);
	m_strEcsAddr	= szBuff;
	m_nEcsPort		=		GetPrivateProfileInt("Ecs", "Port", 7000, ECS_INI_FILE);
	m_bEcsConnect	= (UINT)GetPrivateProfileInt("Ecs", "Connect", 1, ECS_INI_FILE);
	m_bEcsRetry		= (UINT)GetPrivateProfileInt("Ecs", "Retry", 1, ECS_INI_FILE);


	m_nEcsSvPort = GetPrivateProfileInt("EcsSv", "Port", 700, ECS_INI_FILE);

}

void CConfig::WriteProfile() 
{
	char szSection[256];
	char szBuff[256];

	sprintf(szBuff, "%s", (LPCTSTR)m_strHostAddr);			WritePrivateProfileString("Host", "Address", szBuff, ECS_INI_FILE);
	sprintf(szBuff, "%d", m_nHostPort);						WritePrivateProfileString("Host", "Port", szBuff, ECS_INI_FILE);
	sprintf(szBuff, "%d", m_bConnect);						WritePrivateProfileString("Host", "Connect", szBuff, ECS_INI_FILE);
	sprintf(szBuff, "%d", m_bRetry);						WritePrivateProfileString("Host", "Retry", szBuff, ECS_INI_FILE);
		
	sprintf(szBuff, "%s", (LPCTSTR)m_strOrderFile);			WritePrivateProfileString("SapHost", "OrderFile", szBuff, ECS_INI_FILE);
	sprintf(szBuff, "%s", (LPCTSTR)m_strClientLocation);	WritePrivateProfileString("SapHost", "ClientLocation", szBuff, ECS_INI_FILE);

	sprintf(szBuff, "%d", m_bJob);							WritePrivateProfileString("Main", "Job", szBuff, ECS_INI_FILE);
	sprintf(szBuff, "%d", m_bEvent);						WritePrivateProfileString("Main", "Event", szBuff, ECS_INI_FILE);
	sprintf(szBuff, "%d", m_bError);						WritePrivateProfileString("Main", "Error", szBuff, ECS_INI_FILE);
	sprintf(szBuff, "%d", m_bDebug);						WritePrivateProfileString("Main", "Debug", szBuff, ECS_INI_FILE);
	sprintf(szBuff, "%d", m_bBeep);							WritePrivateProfileString("Main", "Beep", szBuff, ECS_INI_FILE);

	for ( int i = 0; i < CV_PLC_CNT; i++ )
	{
		sprintf(szSection, "Conveyor%d", i + 1);
		WritePrivateProfileString(szSection, "Address", (LPTSTR)(LPCTSTR)m_sCvPort[i].strAddress,  ECS_INI_FILE);

		sprintf(szBuff, "%d", m_sCvPort[i].nPort);
		WritePrivateProfileString(szSection, "Port", szBuff,  ECS_INI_FILE);

		sprintf(szBuff, "%d", m_sCvPort[i].bConnect);
		WritePrivateProfileString(szSection, "Connect", szBuff, ECS_INI_FILE);
		
		sprintf(szBuff, "%d", m_sCvPort[i].bRetry);
		WritePrivateProfileString(szSection, "Retry", szBuff, ECS_INI_FILE);

//		sprintf(szSection, "Conveyor%d", i + 1);			WritePrivateProfileString(szSection, "Address", (LPTSTR)(LPCTSTR)m_strCvAddr[i],  ECS_INI_FILE);
//		sprintf(szBuff, "%d", m_nCvPort[i]);				WritePrivateProfileString(szSection, "Port", szBuff,  ECS_INI_FILE);
//		sprintf(szBuff, "%d", m_bCvConnect[i]);				WritePrivateProfileString(szSection, "Connect", szBuff, ECS_INI_FILE);
//		sprintf(szBuff, "%d", m_bCvRetry[i]);				WritePrivateProfileString(szSection, "Retry", szBuff, ECS_INI_FILE);
	}		

	for (i = 0; i < SC_CNT-1; i++ )
	{
		sprintf(szSection, "Stacker%d", i + 1);				WritePrivateProfileString(szSection, "ComName", m_sScPort[i].szComName, ECS_INI_FILE);
		sprintf(szBuff, "%d", m_sScPort[i].nBaudRate);		WritePrivateProfileString(szSection, "BaudRate", szBuff, ECS_INI_FILE);
		sprintf(szBuff, "%d", m_sScPort[i].nParity);		WritePrivateProfileString(szSection, "Parity", szBuff, ECS_INI_FILE);
		sprintf(szBuff, "%d", m_sScPort[i].nStopBits);		WritePrivateProfileString(szSection, "StopBits", szBuff, ECS_INI_FILE);
		sprintf(szBuff, "%d", m_sScPort[i].nBitsPerChar);	WritePrivateProfileString(szSection, "BitsPerChar", szBuff, ECS_INI_FILE);
	}

		sprintf(szSection, "Stacker%d", 6);
		WritePrivateProfileString(szSection, "Address", (LPTSTR)(LPCTSTR)m_sScPort[5].strAddress,  ECS_INI_FILE);
		sprintf(szBuff, "%d", m_sScPort[5].nPort);
		WritePrivateProfileString(szSection, "Port", szBuff,  ECS_INI_FILE);
		sprintf(szBuff, "%d", m_sScPort[5].bConnect);
		WritePrivateProfileString(szSection, "Connect", szBuff, ECS_INI_FILE);
		sprintf(szBuff, "%d", m_sScPort[5].bRetry);
		WritePrivateProfileString(szSection, "Retry", szBuff, ECS_INI_FILE);


	sprintf(szBuff, "%s", (LPCTSTR)m_strEcsAddr);			WritePrivateProfileString("Ecs", "Address", szBuff, ECS_INI_FILE);
	sprintf(szBuff, "%d", m_nEcsPort);						WritePrivateProfileString("Ecs", "Port",	szBuff, ECS_INI_FILE);
	sprintf(szBuff, "%d", m_bEcsConnect);					WritePrivateProfileString("Ecs", "Connect", szBuff, ECS_INI_FILE);
	sprintf(szBuff, "%d", m_bEcsRetry);						WritePrivateProfileString("Ecs", "Retry",	szBuff, ECS_INI_FILE);
		
	sprintf(szBuff, "%d", m_nEcsSvPort);					WritePrivateProfileString("EcsSv", "Port", szBuff, ECS_INI_FILE);


}