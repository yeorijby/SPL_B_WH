// EcsSrial.cpp : implementation of the CEcsSrial class
//

#include "stdafx.h"
#include "Serial.h"

#include <EcsEnv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define VALID_CHECK	if (m_hCommDev == INVALID_HANDLE_VALUE) { m_strErrMsg.Format("Port is not opened.. ErrCode =[%d]", m_dwErrCode = (DWORD)ERR_PORT_NOT_OPEN);	return -1; }

////////////////////////////////////////////////////////////////////////////////
// CSerial

CSerial::CSerial()
{
	m_hCommDev    = INVALID_HANDLE_VALUE;
	m_Line		  = Dead;
	m_dwInQue     = 256;
	m_dwOutQue    = 256;
	m_dwErrCode   = TRUE;
	m_strErrMsg   = "";

	// Create events for overlapped I/O (thread operation)
	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (m_osWrite.hEvent == NULL) 
	{
		m_strErrMsg.Format("Initialize fail.. ErrCode =[%d]", m_dwErrCode = (DWORD)ERR_INIT_FAIL);
		return;
	}

	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;
	m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (m_osRead.hEvent == NULL) 
	{
		CloseHandle(m_osWrite.hEvent);
		m_osWrite.hEvent = NULL;
		m_strErrMsg.Format("Initialize fail.. ErrCode =[%d]", m_dwErrCode = (DWORD)ERR_INIT_FAIL);
	}
}

CSerial::~CSerial()
{
	if (m_osWrite.hEvent) CloseHandle(m_osWrite.hEvent);
	if (m_osRead.hEvent) CloseHandle(m_osRead.hEvent);
	if (m_hCommDev != INVALID_HANDLE_VALUE) Close();
}

void CSerial::SetConfig(LPSTR strComName, 
	  				DWORD dwBaudRate,
					BYTE byByteSize,
					BYTE byParity,
					BYTE byStopBits,
					BYTE byFlowCtrl)
{
	m_strCommName = strComName;

	m_dwBaudRate = dwBaudRate;
	m_byByteSize = byByteSize;
	m_byParity   = byParity;
	m_byStopBits = byStopBits;
	m_byFlowCtrl  = byFlowCtrl;

	m_CommTimeOuts.ReadIntervalTimeout         = 0xFFFFFFFF;
	m_CommTimeOuts.ReadTotalTimeoutMultiplier  = 0;
	m_CommTimeOuts.ReadTotalTimeoutConstant    = 500;
	m_CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	m_CommTimeOuts.WriteTotalTimeoutConstant   = 100;
}

BOOL CSerial::Setup(void)
{
	DCB	dcb;

	dcb.DCBlength = sizeof(DCB);

	::GetCommState(m_hCommDev, &dcb);

	dcb.BaudRate = m_dwBaudRate;

	dcb.ByteSize = m_byByteSize;
	dcb.Parity   = m_byParity;
	dcb.StopBits = m_byStopBits;

	dcb.fOutxDsrFlow = (BYTE) ((m_byFlowCtrl & FC_DTRDSR));
	dcb.fDtrControl  = dcb.fOutxDsrFlow ? DTR_CONTROL_HANDSHAKE: DTR_CONTROL_ENABLE;

	if (m_byFlowCtrl & FC_RTSCTS_H) 
		dcb.fOutxCtsFlow = TRUE;
	else 
		dcb.fOutxCtsFlow = FALSE;

	if (dcb.fOutxCtsFlow) 
		dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
	else 
	{
		if ((m_byFlowCtrl & FC_RTSCTS_T) == FC_RTSCTS_T) 
			dcb.fRtsControl = RTS_CONTROL_TOGGLE;
	    else 
			dcb.fRtsControl = RTS_CONTROL_ENABLE;
	}

	// Setup software flow control
	dcb.fInX     = dcb.fOutX = (BYTE) ((m_byFlowCtrl & FC_XONXOFF) != 0);
	dcb.XonChar  = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim   = 100;
	dcb.XoffLim  = 100;

	// Other various settings
	dcb.fBinary = TRUE ;
	dcb.fParity = TRUE ;
	dcb.EofChar = ASCII_CR;
	dcb.EvtChar = ASCII_CR;

	return SetCommState(m_hCommDev, &dcb);
}

BOOL CSerial::Open(void)
{
	if (m_dwErrCode == ERR_INIT_FAIL) return FALSE;

	if (m_Line == Live) Close();

	m_hCommDev = CreateFile(m_strCommName, GENERIC_READ | GENERIC_WRITE,
							0,			// exclusive access
							NULL,		// no security attrs
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, // overlapped I/O
							NULL);

	if (m_hCommDev == INVALID_HANDLE_VALUE) {
		m_strErrMsg.Format("Device file create fail.. ErrCode =[%d]", m_dwErrCode = ::GetLastError());
		return FALSE;
	}

	if (!::SetCommMask(m_hCommDev, EV_RXCHAR)) // Get any early notifications
	{
		m_strErrMsg.Format("SetCommMask routine fail.. ErrCode =[%d]", m_dwErrCode = ::GetLastError());
		return FALSE;
	}

	if (m_dwInQue <= 0 && m_dwOutQue <= 0) {
		m_strErrMsg.Format("IN & OUT Queue size is negative.. ErrCode =[Internal]");
		return FALSE;
	}

	if (!::SetupComm(m_hCommDev, m_dwInQue, m_dwOutQue)) // Setup device buffers
	{
		m_strErrMsg.Format("SetupComm routine fail.. ErrCode =[%d]", m_dwErrCode = ::GetLastError());
		return FALSE;
	}

	if (!PurgeComm())  return FALSE; // purge any information in the buffer

	if (!::SetCommTimeouts(m_hCommDev, &m_CommTimeOuts)) // Set up for overlapped I/O
	{
		m_strErrMsg.Format("SetCommTimeouts routine fail.. ErrCode =[%d]", m_dwErrCode = ::GetLastError());
		return FALSE;
	}

	if (Setup())
	{
		m_Line = Live;
		if (!::EscapeCommFunction(m_hCommDev, SETDTR)) // Assert DTR
		{
			m_strErrMsg.Format("EscapeCommFunction routine fail.. ErrCode =[%d]", m_dwErrCode = ::GetLastError());
			return FALSE;
		}
		return TRUE;
	}
	else 
	{
		m_strErrMsg.Format("SetCommState routine fail.. ErrCode =[%d]", m_dwErrCode = ::GetLastError());
		CloseHandle(m_hCommDev);
		return FALSE;
	}
}

void CSerial::Close(void)
{
	SetCommMask(0);					// Disable event notification
	EscapeCommFunction(CLRDTR);		// Drop DTR
	PurgeComm();					// Purge any outstanding reads/writes

	if (m_hCommDev != INVALID_HANDLE_VALUE) 
	{
		CloseHandle(m_hCommDev);	// Close device handle
		m_hCommDev = INVALID_HANDLE_VALUE;
	}
}

BOOL CSerial::ClearCommError(void)
{
	VALID_CHECK;

	if (::ClearCommError(m_hCommDev, &m_CommError, &m_Comstat)) return TRUE;

	m_strErrMsg.Format("GetOverlappedResult routine fail.. ErrCode =[%d]", m_dwErrCode = ::GetLastError());
	return FALSE;
}

BOOL CSerial::EscapeCommFunction(DWORD dwFunc)
{
	VALID_CHECK;

	if (::EscapeCommFunction(m_hCommDev, dwFunc)) return TRUE;

	m_strErrMsg.Format("EscapeCommFunction routine fail.. ErrCode =[%d]", m_dwErrCode = ::GetLastError());
	return FALSE;
}

BOOL CSerial::PurgeComm(DWORD dwAction) // Purge any information in the buffer
{
	VALID_CHECK;

	if (::PurgeComm(m_hCommDev, dwAction)) return TRUE;
	else {
		m_strErrMsg.Format("PurgeComm routine fail.. ErrCode =[%d]", ::GetLastError());
		return FALSE;
	}
}

BOOL CSerial::SetCommMask(DWORD dwEvtMask)
{
	VALID_CHECK;

	if (::SetCommMask(m_hCommDev, dwEvtMask)) return TRUE;

	m_strErrMsg.Format("GetCommTimeouts routine fail.. ErrCode =[%d]", m_dwErrCode = ::GetLastError());
	return FALSE;
}

BOOL CSerial::WaitCommEvent(LPDWORD lpfdwEvtMask, LPOVERLAPPED lpo)
{
	VALID_CHECK;

	if (::WaitCommEvent(m_hCommDev, lpfdwEvtMask, lpo)) return TRUE;

	m_strErrMsg.Format("WaitCommEvent routine fail.. ErrCode =[%d]", m_dwErrCode = ::GetLastError());
	return FALSE;
}

BOOL CSerial::GetOverlappedResult(LPOVERLAPPED lpOverlapped, LPDWORD lpNumber, BOOL bWait)	
{
	if (::GetOverlappedResult(m_hCommDev, lpOverlapped, lpNumber, bWait)) return TRUE;

	m_strErrMsg.Format("GetOverlappedResult routine fail.. ErrCode =[%d]", m_dwErrCode = ::GetLastError());
	return FALSE;
}

BOOL CSerial::Recv(BYTE* pRxBuff, DWORD nLen)
{
	//VALID_CHECK;
	
	if (nLen <= 0) return -1;

	DWORD	dwCnt = nLen;
	int		nOffset = 0, nRetryCnt = 0;

	BYTE szAAA[200];
	memset(szAAA, 0x00, 200);

	while (nLen > 0)
	{
		if (!ReadFile(m_hCommDev, pRxBuff + nOffset, dwCnt, &dwCnt, &m_osRead)) 
		//if (!ReadFile(m_hCommDev, szAAA + nOffset, dwCnt, &dwCnt, &m_osRead)) 
		{
			m_strErrMsg.Format("ReadFile routine fail.. ErrCode =[%d]", m_dwErrCode = ::GetLastError());
			if (m_dwErrCode == ERROR_IO_PENDING) 
			{
				while (!GetOverlappedResult(&m_osRead, &dwCnt, TRUE)) 
				{
					if(m_dwErrCode == ERROR_IO_INCOMPLETE) continue;
					else ClearCommError();
				}
			}
			else
			{
				ClearCommError();
				return -1;
			}
		}
		if (dwCnt < nLen)
		{
			nOffset += dwCnt;
			Sleep(50);
		}
		nLen -= dwCnt;
		if (nRetryCnt++ > 3) 
		{
			PurgeComm();
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CSerial::RecvBcr(BYTE* pRxBuff, DWORD nLen)
{
	VALID_CHECK;
	
	if (nLen <= 0) return -1;

	DWORD	dwCnt = nLen;
	int		nOffset = 0, nRetryCnt = 0;

	while (nLen > 0)
	{
		if (!ReadFile(m_hCommDev, pRxBuff + nOffset, dwCnt, &dwCnt, &m_osRead)) 
		{
			m_strErrMsg.Format("ReadFile routine fail.. ErrCode =[%d]", m_dwErrCode = ::GetLastError());
			if (m_dwErrCode == ERROR_IO_PENDING) 
			{
				while (!GetOverlappedResult(&m_osRead, &dwCnt, TRUE)) 
				{
					if(m_dwErrCode == ERROR_IO_INCOMPLETE) continue;
					else ClearCommError();
				}
			}
			else
			{
				ClearCommError();
				return -1;
			}
		}
		if (dwCnt < nLen)
		{
			nOffset += dwCnt;
			Sleep(50);
		}
		nLen -= dwCnt;
		if (nRetryCnt++ > 3) 
		{
//			PurgeComm();
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CSerial::Send(BYTE* pTxBuff, DWORD nLen)
{
	VALID_CHECK;
	
	if (nLen <= 0) return FALSE;

	DWORD dwCnt = nLen;

	if (!WriteFile(m_hCommDev, pTxBuff, dwCnt, &dwCnt, &m_osWrite)) 
	{
		while (!GetOverlappedResult(&m_osWrite, &dwCnt, TRUE)) 
		{
			if(m_dwErrCode == ERROR_IO_INCOMPLETE) continue;
			else 
			{
				ClearCommError();
				return FALSE;
			}
		}
	}

	return (dwCnt == nLen) ? TRUE : FALSE;
}
