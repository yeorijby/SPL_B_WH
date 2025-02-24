// Config.h : Defines the class behaviors for the application.

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "EcsDef.h"

#define ECS_INI_FILE		"..\\Bin\\Ecs.ini"
/*
struct SPort 
{
	char	szComName[30];
	int		nBaudRate;
	int		nParity;
	int		nStopBits;
	int		nBitsPerChar;
};
*/

struct SPort 
{

	char	szComName[30];
	int		nBaudRate;
	int		nParity;
	int		nStopBits;
	int		nBitsPerChar;

	DWORD	dwReadTimeOut;

	CString strDevice;
	CString strAddress;
	int     nPort;
	BOOL	bConnect;
	BOOL	bRetry;
};

class CEcsDoc;
class CConfig : public CObject
{
protected:
	DECLARE_DYNCREATE(CConfig)

// constructor & destructor
public:
	CConfig();
	CConfig(CEcsDoc* pDoc);
	~CConfig();

// Attributes
protected:
	CString	m_strMainLogName;
public:
	CEcsDoc* m_pDoc;
	CString	m_strFileName;
	CString m_strPassword;
	BOOL	m_bConnect;
	BOOL	m_bRetry;
	BOOL	m_bJob;
	BOOL	m_bEvent;
	BOOL	m_bError;
	BOOL	m_bDebug;
	BOOL	m_bBeep;
	BOOL	m_bSysSuspend;
	SPort	m_sCvPort[CV_PLC_CNT];
	SPort	m_sScPort[SC_CNT];
	SPort	m_sRgvPort[RGV_CNT];

	CString m_strCvAddr[CV_PLC_CNT];
	int     m_nCvPort[CV_PLC_CNT];
	BOOL    m_bCvConnect[CV_PLC_CNT];
	BOOL    m_bCvRetry[CV_PLC_CNT];

	CString m_strEcsAddr;
	int     m_nEcsPort;
	BOOL    m_bEcsConnect;
	BOOL    m_bEcsRetry;
	
// OPT_HOST_NETWORK_INTERFACE_USE
	CString	m_strHostAddr;
	int		m_nHostPort;

	UINT	m_nEcsSvPort;

// OPT_SAP_NETWORK_INTERFACE_USE
	CString	m_strOrderFile;
	CString	m_strClientLocation;

// operations
public:
	BOOL Restore();
	BOOL Backup();
	void Load(CListCtrl* pListCtrl);
	void GetProfile();
	void WriteProfile();

	CString GetRgvDeviceName(int nRgvNum);

// Implementation
public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

#endif // __CONFIG_H__
