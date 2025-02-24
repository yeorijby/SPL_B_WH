// Define Thread

#ifndef __THREAD_H__
#define __THREAD_H__

#include "Config.h"
#include "ConveyorTrackInfo.h"
#include "StackerInfo.h"
#include "CvSocket.h"
#include "RgvInfo.h"
#include "ScSocket.h"

struct SConveyorMsg 
{
	int nTrackNum;
	int nLuggNum;
	int nLuggNum2;
	int nJobType;
	int nStartPos;
	int	nDestPos;
	int nBatchNum;
	int nPalletNum;
	int nLevelNum;

	int nComplete;
	int nSize;

	int nPlcCount;

	int nLastPallet;

	BOOL bCopy;
	BOOL bModified;
};

struct STroubleMsg 
{
public:
	STroubleMsg() {bModified = FALSE;};
public:
	int  nAddressNum;
	WORD wAddressData;

	int  nD[14];

	BOOL bModified;
};

struct SHostThreadInfo
{
	char m_szComName[60];

	CEcsDoc* m_pDoc;

	HWND m_hwndNotify;

	HANDLE m_hEventNotify;
	HANDLE m_hEventKillThread;
	HANDLE m_hEventThreadKilled;
};

struct SConveyorThreadInfo
{
	int m_nNum;
	char m_szComName[60];
	int	 m_nBaudRate;
	int	 m_nParity;
	int	 m_nStopBits;
	int	 m_nBitsPerChar;

	SPort	Port;
	DWORD m_dwReadTimeOut;

	CEcsDoc* m_pDoc;
	CCvSocket* m_pSocket;
	CConveyorTrackInfo* m_pConveyorTrackInfo;
	
	SConveyorMsg m_ConveyorMsg;
	STroubleMsg m_ConveyorTroubleMsg;
	STroubleMsg m_ConveyorOutMsg;

	SConveyorMsg m_PlcCountMsg;

	HWND m_hwndNotify;

	HANDLE m_hEventSendConveyor;
	HANDLE m_hEventKillConveyorThread;
	HANDLE m_hEventConveyorThreadKilled;
};

UINT ConveyorThreadProc(LPVOID pParam);

struct SBcrThreadInfo
{
	int m_nNum;
	char m_szComName[60];
	int	 m_nBaudRate;
	int	 m_nParity;
	int	 m_nStopBits;
	int	 m_nBitsPerChar;

	CEcsDoc* m_pDoc;
		
	HWND m_hwndNotify;

	HANDLE m_hEventSendBcr;
	HANDLE m_hEventKillBcrThread;
	HANDLE m_hEventBcrThreadKilled;
};

UINT BcrThreadProc(LPVOID pParam);

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^ suri
struct SClReadThreadInfo
{
	CEcsDoc* m_pDoc;
		
	HANDLE m_hEventKillClReadThread;
	HANDLE m_hEventClReadThreadKilled;
};

UINT ClReadThreadProc(LPVOID pParam);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


#define SC_CMD_INVOKE		 1
#define SC_CMD_COMPLETE		 2
#define SC_CMD_CANCEL		 3
#define SC_CMD_ESTOP		 4
#define SC_CMD_RESTART		 5
#define SC_CMD_CALL_TO_HOME	 6
#define SC_CMD_NEW_LOCATION	 7
#define	SC_CMD_RETRY    	 8
#define	SC_CMD_MANUAL		 10
#define	SC_CMD_STO_LOADING	 11
#define	SC_CMD_STO_UNLOADING 12
#define	SC_CMD_RET_LOADING 	 13
#define	SC_CMD_RET_UNLOADING 14
#define SC_CMD_ERROR_RESET   15
#define SC_CMD_ACTIVE		 16
#define SC_CMD_PAUSE		 17

#define SC_CMD_RESET		 18
#define SC_CMD_STOP			 19

struct SStackerMsg 
{
	int nCommand;
	int nLuggNum;
	int nJobType;
	CString strStartLoc;
	CString strDestLoc;
	int nDeleteFork;

	int nHsNum;
	int nCmdType;
	int nStartHS;
	int nDestHS;
	int nGen;

	BOOL bModified;
};

struct SStackerThreadInfo
{
	int m_nNum;
	char m_szComName[60];
	int	 m_nBaudRate;
	int	 m_nParity;
	int	 m_nStopBits;
	int	 m_nBitsPerChar;

	CEcsDoc* m_pDoc;
	CScSocket* m_pSocket;
	CStackerInfo* m_pStackerInfo;
	SStackerMsg m_StackerMsg;

	HWND m_hwndNotify;

	HANDLE m_hEventSendStacker;
	HANDLE m_hEventKillStackerThread;
	HANDLE m_hEventStackerThreadKilled;
};
UINT StackerThreadProc(LPVOID pParam);
UINT ScQThreadProc(LPVOID pParam);


#define RGV_CMD_INVOKE			1
#define RGV_CMD_COMPLETE		2
#define RGV_CMD_CANCEL			3
#define RGV_CMD_RESET			4
#define RGV_CMD_STOP			5
#define RGV_CMD_ESTOP			6
#define RGV_CMD_ACTIVE			7
#define RGV_CMD_CALL_TO_HOME	8
#define RGV_CMD_MANUAL			9
#define RGV_CMD_STO_SUSPEND		10
#define RGV_CMD_RET_SUSPEND		11

struct SRgvMsg 
{
	int nCommand;
	int nLuggNum;
	int nStartHS;
	int nDestHS;
	CString strStartHS;
	CString strDestHS;

	BOOL bModified;
};

struct SRgvThreadInfo
{
	int m_nNum;
	SPort	Port;
	char m_szComName[60];
	DWORD m_dwReadTimeOut;

	CEcsDoc* m_pDoc;
	CRgvInfo* m_pRgvInfo;
	CConveyorTrackInfo *m_pConveyorTrackInfo;

	SRgvMsg m_RgvMsg;

	HWND m_hwndNotify;

	HANDLE m_hEventSendRgv;
	HANDLE m_hEventKillRgvThread;
	HANDLE m_hEventRgvThreadKilled;

	HANDLE m_hCommDev;
};
UINT RgvThreadProc(LPVOID pParam);


#endif // __THREAD_H__
