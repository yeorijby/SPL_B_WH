#include "stdafx.h"
#include "Melsec3E.h"

#include "Lib.h"


CMelsec3E::CMelsec3E(CCvSocket *pSock)
{
	m_pSock = pSock;

	m_strErrMsg = "";
}

BOOL CMelsec3E::Read(int nUnitType, BYTE *pRxBuff, BYTE DeviceCode, int nStartAddr, WORD wReadLen)
{
	m_strErrMsg = "";

	BYTE TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));

    TxBuff[0]  = 0x50;  
	TxBuff[1]  = 0x00;	// Subheader	

	TxBuff[2]  = 0x00;	// Network No. (Self station)
	TxBuff[3]  = 0xFF;	// PC No.

    TxBuff[4]  = 0xFF;	
	TxBuff[5]  = 0x03;	// Specific value
	TxBuff[6]  = 0x00;	// Specific value 2

	TxBuff[7]  = 0x0C;  //0x0C
	TxBuff[8]  = 0x00;	// Request data length

	TxBuff[9]  = 0x08;  // 0x08;
	TxBuff[10] = 0x00;	// CPU monitoring timer (unit is 250ms)

	TxBuff[11] = 0x01;
	TxBuff[12] = 0x04;  //Command
	TxBuff[13] = nUnitType;
	TxBuff[14] = 0x00; 	// Subcommand

	TxBuff[15] = (nStartAddr & 0xFF);
	TxBuff[16] = (nStartAddr >> 8) & 0xFF;
	TxBuff[17] = (nStartAddr >> 16) & 0xFF;		// Head device (Start Address)

	TxBuff[18] = DeviceCode;					// Device code (Memory Type)

	TxBuff[19] = wReadLen & 0x00FF;				//WORD단위:읽을 워드수, BIT단위:읽을 비트수
	TxBuff[20] = (wReadLen >> 8) & 0x00FF;		// Number of device points

	Sleep(30);

	if( m_pSock->Send(TxBuff, 21) == SOCKET_ERROR )
	{
		m_strErrMsg.Format("Read.. 송신 에러 [%s]", CLib::GetSystemErrMsg());
		return FALSE;
	}

	return RecvReadAck(nUnitType, pRxBuff, wReadLen);
}

BOOL CMelsec3E::Write(int nUnitType, BYTE *pTxBuff, BYTE DeviceCode, int nStartAddr, WORD wWriteLen)
{
	m_strErrMsg = "";

	BYTE TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));
	WORD wReqLen = 12 + GetDataLength(nUnitType, wWriteLen);

    TxBuff[0]  = 0x50;  
	TxBuff[1]  = 0x00;	// Subheader	

	TxBuff[2]  = 0x00;	// Network No. (Self station)
	TxBuff[3]  = 0xFF;	// PC No.

    TxBuff[4]  = 0xFF;	
	TxBuff[5]  = 0x03;	// Specific value
	TxBuff[6]  = 0x00;	// Specific value 2

	TxBuff[7]  = wReqLen & 0x00FF;
	TxBuff[8]  = (wReqLen >> 8) & 0x00FF;  	// Request data length

	TxBuff[9]  = 0x08;  // 0x04;
	TxBuff[10] = 0x00;	// CPU monitoring timer (unit is 250ms)

	TxBuff[11] = 0x01;
	TxBuff[12] = 0x14;  //Command
	TxBuff[13] = nUnitType;
	TxBuff[14] = 0x00; 	// Subcommand

	TxBuff[15] = (nStartAddr & 0xFF);
	TxBuff[16] = (nStartAddr >> 8) & 0xFF;
	TxBuff[17] = (nStartAddr >> 16) & 0xFF;		// Head device (Start Address)

	TxBuff[18] = DeviceCode;					// Device code (Memory Type)

	TxBuff[19] = wWriteLen & 0x00FF;            //WORD단위:쓸 워드수, BIT단위:쓸 비트수
	TxBuff[20] = (wWriteLen >> 8) & 0x00FF;		// Number of device points

	memcpy(TxBuff+21, pTxBuff, GetDataLength(nUnitType, wWriteLen));
	int nLen = 21 + GetDataLength(nUnitType, wWriteLen);

	if( m_pSock->Send(TxBuff, nLen) == SOCKET_ERROR )
	{
		m_strErrMsg.Format("Write.. 송신 에러 [%s]", CLib::GetSystemErrMsg());
		return FALSE;
	}

	return RecvWriteAck();
}

BOOL CMelsec3E::RecvReadAck(int nUnitType, BYTE *pRxBuff, WORD wReadLen)
{
	int nRecvLen = 0;
	//BYTE RxBuff[4096];
	BYTE RxBuff[10000];
	memset(RxBuff, 0x00, sizeof(RxBuff));

	if((nRecvLen = RecvFrame(RxBuff)) == FALSE)		return FALSE;

	if(RxBuff[0] != 0xD0 || RxBuff[1] != 0x00)                //Subheader
	{
		m_strErrMsg.Format("RecvReadAck.. Subheader 이상..");
		return FALSE;
	}
	if(RxBuff[2] != 0x00 || RxBuff[3] != 0xFF)                // Network NO, PC NO
	{
		m_strErrMsg.Format("RecvReadAck.. Network or PC NO 이상..");
		return FALSE;
	}
	if(RxBuff[4] != 0xFF || RxBuff[5] != 0x03 || RxBuff[6] != 0x00)   // Specific value
	{
		m_strErrMsg.Format("RecvReadAck.. Specific Value 이상..");
		return FALSE;
	}

	WORD wErrNo = SwapToWord(RxBuff+9);
	if(wErrNo)
	{
		m_strErrMsg.Format("RecvReadAck.. 응답 수신.. 오류코드[%d]", wErrNo);
		return FALSE;
	}

	int nTotalLen = BINARY_HEADER_LEN + GetDataLength(nUnitType, wReadLen);
	if(nTotalLen != nRecvLen)
	{
		m_strErrMsg.Format("RecvReadAck.. 응답 프레임 길이 이상[전체%d - 수신%d]", nTotalLen, nRecvLen);
		return FALSE;
	}

	memcpy(pRxBuff, RxBuff+BINARY_HEADER_LEN, GetDataLength(nUnitType, wReadLen));

	//m_strErrMsg.Format("수신 데이타.. [%s]", pRxBuff);

	return TRUE;
}

BOOL CMelsec3E::RecvWriteAck()
{
	BYTE RxBuff[1024];
	int nRecvLen;

	memset(RxBuff, 0x00, sizeof(RxBuff));
	if((nRecvLen = RecvFrame(RxBuff)) == FALSE)
		return FALSE;

	if(RxBuff[0] != 0xD0 || RxBuff[1] != 0x00)                //Subheader
	{
		m_strErrMsg.Format("RecvReadAck.. Subheader 이상..");
		return FALSE;
	}
	if(RxBuff[2] != 0x00 || RxBuff[3] != 0xFF)                // Network NO, PC NO
	{
		m_strErrMsg.Format("RecvWriteAck.. Network or PC NO 이상..");
		return FALSE;
	}
	if(RxBuff[4] != 0xFF || RxBuff[5] != 0x03 || RxBuff[6] != 0x00)   // Specific value
	{
		m_strErrMsg.Format("RecvWriteAck.. Specific Value 이상..");
		return FALSE;
	}

	WORD wErrNo = SwapToWord(RxBuff+9);
	if(wErrNo)
	{
		m_strErrMsg.Format("RecvWriteAck.. 응답 수신.. 오류코드[%d]", wErrNo);
		return FALSE;
	}

	return TRUE;
}

int CMelsec3E::RecvFrame(BYTE *pRxBuff)
{
	DWORD dwLen = 0, nRealLen, nTotalLen = 0;

	m_pSock->m_bReceiving = TRUE;

	if(WaitForSingleObject(m_pSock->m_hEventRecv, 2000) == WAIT_TIMEOUT)
	{
		if(WaitForSingleObject(m_pSock->m_hEventRecv, 2000) == WAIT_TIMEOUT)
		{
			m_strErrMsg.Format("RecvFrame.. 수신 대기시간 초과 에러");
			return FALSE;
		}
	}

	if(m_pSock->IOCtl( FIONREAD, &dwLen ) == FALSE)
	{
		m_strErrMsg.Format("RecvFrame.. IOCtl 에러 [%s]", CLib::GetSystemErrMsg());
		return FALSE;
	}

	if ((nRealLen = m_pSock->Receive(pRxBuff, dwLen)) != dwLen)
	{
		m_strErrMsg.Format("RecvFrame.. Receive에러 [%s]", CLib::GetSystemErrMsg());
		return FALSE;
	}

	nTotalLen = nRealLen;

	if (dwLen < BINARY_HEADER_LEN)
	{
		if(WaitForSingleObject(m_pSock->m_hEventRecv, 2000) == WAIT_TIMEOUT)
		{
			m_strErrMsg.Format("RecvFrame.. 수신 대기시간 초과 에러#2 [dwLen=%d]", dwLen);
			return FALSE;
		}

		if(m_pSock->IOCtl( FIONREAD, &dwLen ) == FALSE)
		{
			m_strErrMsg.Format("RecvFrame.. IOCtl 에러#2 [%s]", CLib::GetSystemErrMsg());
			return FALSE;
		}

		if ((nRealLen = m_pSock->Receive(pRxBuff+nRealLen, dwLen)) != dwLen)
		{
			m_strErrMsg.Format("RecvFrame.. Receive에러#2 [%s]", CLib::GetSystemErrMsg());
			return FALSE;
		}

		nTotalLen += nRealLen;

		if(nRealLen <= BINARY_HEADER_LEN)
		{
			m_strErrMsg.Format("RecvFrame.. 수신 데이터 길이[%d] 이상", nRealLen);
			return FALSE;
		}
	}

	m_pSock->m_bReceiving = FALSE;

	return nTotalLen;
}

WORD CMelsec3E::SwapToWord(BYTE *pSrc)
{
	return (WORD)(pSrc[1] << 8) | pSrc[0];
}

DWORD CMelsec3E::SwapToDWord(BYTE *pSrc)
{
	return (DWORD)(pSrc[3] << 24) | (pSrc[2] << 16) | (pSrc[1] << 8) | pSrc[0];
}


int CMelsec3E::GetDataLength(int nUnitType, WORD wLen)
{
	return (nUnitType == CMD_WORD_UNIT) ? (wLen*2) : ((wLen/2)+(wLen%2));
}
/*
int CMelsec3E::Write2Word(BYTE *pData, int nTrackNum)
{
    BYTE	TxBuff[256], SumA, SumB;
    char    szAddr[32];

	memset(TxBuff, 0x0, sizeof(TxBuff));
    sprintf(szAddr, "D%.4d", nTrackNum*2 + 2);

    TxBuff[0]  = ENQ;
    memcpy(TxBuff+1, "00FFWW0", 7);
    memcpy(TxBuff+8, szAddr, 5);

    TxBuff[13] = 0x30;
	TxBuff[14] = 0x32;		// Range : 2 Word Write
	memcpy(TxBuff+15, pData, 8);

    CheckSum(TxBuff, 23, &SumA, &SumB);
    TxBuff[23] = SumA;
    TxBuff[24] = SumB;
    TxBuff[25] = CR;
    TxBuff[26] = LF;

	if(!Send(TxBuff, 27)) return FALSE;
	Sleep(200L);

	return Response();
}

int CMelsec3E::Write1Word(BYTE *pData, int nTrackNum)
{
    BYTE	TxBuff[256], SumA, SumB;
    char    szAddr[32];

	memset(TxBuff, 0x0, sizeof(TxBuff));
    sprintf(szAddr, "D%.4d", nTrackNum);

    TxBuff[0]  = ENQ;
    memcpy(TxBuff+1, "00FFWW0", 7);
    memcpy(TxBuff+8, szAddr, 5);

    TxBuff[13] = 0x30;
	TxBuff[14] = 0x31;		// Range : 1 Word Write
	memcpy(TxBuff+15, pData, 4);

    CheckSum(TxBuff, 19, &SumA, &SumB);
    TxBuff[19] = SumA;
    TxBuff[20] = SumB;
    TxBuff[21] = CR;
    TxBuff[22] = LF;

	Send(TxBuff, 23);
	Sleep(200L);
	return Response();
}
*/
void CMelsec3E::HexStr2Word(BYTE *bySrc, WORD *byDest)
{
	*byDest = 0;
	for (int i=0; i<4; i++)
	{
		if (bySrc[i] >= '0' && bySrc[i] <= '9')
			(*byDest) |= bySrc[i] - '0';
		else
			(*byDest) |= bySrc[i] - 'A' + 10;
		if(i!=3) (*byDest) <<= 4;
	}
}

void CMelsec3E::HexStr1Word(BYTE *bySrc, BYTE *byDest)
{
	*byDest = 0;
	for (int i=0; i<2; i++)
	{
		if (bySrc[i] >= '0' && bySrc[i] <= '9')
			(*byDest) |= bySrc[i] - '0';
		else
			(*byDest) |= bySrc[i] - 'A' + 10;
		if(i!=1) (*byDest) <<= 4;
	}
}

void CMelsec3E::HexStr1Byte(BYTE *bySrc, BYTE *byDest)
{
	*byDest = 0;
	for (int i=0; i<1; i++)
	{
		if (bySrc[i] >= '0' && bySrc[i] <= '9')
			(*byDest) |= bySrc[i] - '0';
		else
			(*byDest) |= bySrc[i] - 'A' + 10;
	}
}

void CMelsec3E::HexStr2Byte(BYTE *bySrc, BYTE *byDest)
{
	*byDest = 0;
	for (int i=0; i<2; i++)
	{
		if (bySrc[i] >= '0' && bySrc[i] <= '9')
			(*byDest) |= bySrc[i] - '0';
		else
			(*byDest) |= bySrc[i] - 'A' + 10;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//

CMelsecSc3E::CMelsecSc3E(CScSocket *pSock)
{
	m_pSock = pSock;

	m_strErrMsg = "";
}

BOOL CMelsecSc3E::Read(int nUnitType, BYTE *pRxBuff, BYTE DeviceCode, int nStartAddr, WORD wReadLen)
{
	m_strErrMsg = "";

	BYTE TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));

    TxBuff[0]  = 0x50;  
	TxBuff[1]  = 0x00;	// Subheader	

	TxBuff[2]  = 0x00;	// Network No. (Self station)
	TxBuff[3]  = 0xFF;	// PC No.

    TxBuff[4]  = 0xFF;	
	TxBuff[5]  = 0x03;	// Specific value
	TxBuff[6]  = 0x00;	// Specific value 2

	TxBuff[7]  = 0x0C;
	TxBuff[8]  = 0x00;	// Request data length

	TxBuff[9]  = 0x08;  // 0x04;
	TxBuff[10] = 0x00;	// CPU monitoring timer (unit is 250ms)

	TxBuff[11] = 0x01;
	TxBuff[12] = 0x04;  //Command
	TxBuff[13] = nUnitType;
	TxBuff[14] = 0x00; 	// Subcommand

	TxBuff[15] = (nStartAddr & 0xFF);
	TxBuff[16] = (nStartAddr >> 8) & 0xFF;
	TxBuff[17] = (nStartAddr >> 16) & 0xFF;		// Head device (Start Address)

	TxBuff[18] = DeviceCode;					// Device code (Memory Type)

	TxBuff[19] = wReadLen & 0x00FF;				//WORD단위:읽을 워드수, BIT단위:읽을 비트수
	TxBuff[20] = (wReadLen >> 8) & 0x00FF;		// Number of device points

	Sleep(30);

	if(m_pSock->Send(TxBuff, 21) == SOCKET_ERROR )
	{
		m_strErrMsg.Format("Read.. 송신 에러 [%s]", CLib::GetSystemErrMsg());
		return FALSE;
	}

	return RecvReadAck(nUnitType, pRxBuff, wReadLen);
}

BOOL CMelsecSc3E::Write(int nUnitType, BYTE *pTxBuff, BYTE DeviceCode, int nStartAddr, WORD wWriteLen)
{
	m_strErrMsg = "";

	BYTE TxBuff[256];
	memset(TxBuff, 0x00, sizeof(TxBuff));
	WORD wReqLen = 12 + GetDataLength(nUnitType, wWriteLen);

    TxBuff[0]  = 0x50;  
	TxBuff[1]  = 0x00;	// Subheader	

	TxBuff[2]  = 0x00;	// Network No. (Self station)
	TxBuff[3]  = 0xFF;	// PC No.

    TxBuff[4]  = 0xFF;	
	TxBuff[5]  = 0x03;	// Specific value
	TxBuff[6]  = 0x00;	// Specific value 2

	TxBuff[7]  = wReqLen & 0x00FF;
	TxBuff[8]  = (wReqLen >> 8) & 0x00FF;  	// Request data length

	TxBuff[9]  = 0x08;  // 0x04;
	TxBuff[10] = 0x00;	// CPU monitoring timer (unit is 250ms)

	TxBuff[11] = 0x01;
	TxBuff[12] = 0x14;  //Command
	TxBuff[13] = nUnitType;
	TxBuff[14] = 0x00; 	// Subcommand

	TxBuff[15] = (nStartAddr & 0xFF);
	TxBuff[16] = (nStartAddr >> 8) & 0xFF;
	TxBuff[17] = (nStartAddr >> 16) & 0xFF;		// Head device (Start Address)

	TxBuff[18] = DeviceCode;					// Device code (Memory Type)

	TxBuff[19] = wWriteLen & 0x00FF;            //WORD단위:쓸 워드수, BIT단위:쓸 비트수
	TxBuff[20] = (wWriteLen >> 8) & 0x00FF;		// Number of device points

	memcpy(TxBuff+21, pTxBuff, GetDataLength(nUnitType, wWriteLen));
	int nLen = 21 + GetDataLength(nUnitType, wWriteLen);

	if( m_pSock->Send(TxBuff, nLen) == SOCKET_ERROR )
	{
		m_strErrMsg.Format("Write.. 송신 에러 [%s]", CLib::GetSystemErrMsg());
		return FALSE;
	}

	return RecvWriteAck();
}

BOOL CMelsecSc3E::RecvReadAck(int nUnitType, BYTE *pRxBuff, WORD wReadLen)
{
	int nRecvLen = 0;
	BYTE RxBuff[4096];
	memset(RxBuff, 0x00, sizeof(RxBuff));

	if((nRecvLen = RecvFrame(RxBuff)) == FALSE)		return FALSE;

	if(RxBuff[0] != 0xD0 || RxBuff[1] != 0x00)                //Subheader
	{
		m_strErrMsg.Format("RecvReadAck.. Subheader 이상..");
		return FALSE;
	}
	if(RxBuff[2] != 0x00 || RxBuff[3] != 0xFF)                // Network NO, PC NO
	{
		m_strErrMsg.Format("RecvReadAck.. Network or PC NO 이상..");
		return FALSE;
	}
	if(RxBuff[4] != 0xFF || RxBuff[5] != 0x03 || RxBuff[6] != 0x00)   // Specific value
	{
		m_strErrMsg.Format("RecvReadAck.. Specific Value 이상..");
		return FALSE;
	}

	WORD wErrNo = SwapToWord(RxBuff+9);
	if(wErrNo)
	{
		m_strErrMsg.Format("RecvReadAck.. 응답 수신.. 오류코드[%d]", wErrNo);
		return FALSE;
	}

	int nTotalLen = BINARY_HEADER_LEN + GetDataLength(nUnitType, wReadLen);
	if(nTotalLen != nRecvLen)
	{
		m_strErrMsg.Format("RecvReadAck.. 응답 프레임 길이 이상[전체%d - 수신%d]", nTotalLen, nRecvLen);
		return FALSE;
	}

	memcpy(pRxBuff, RxBuff+BINARY_HEADER_LEN, GetDataLength(nUnitType, wReadLen));

	return TRUE;
}

BOOL CMelsecSc3E::RecvWriteAck()
{
	BYTE RxBuff[1024];
	int nRecvLen;

	memset(RxBuff, 0x00, sizeof(RxBuff));
	if((nRecvLen = RecvFrame(RxBuff)) == FALSE)
		return FALSE;

	if(RxBuff[0] != 0xD0 || RxBuff[1] != 0x00)                //Subheader
	{
		m_strErrMsg.Format("RecvReadAck.. Subheader 이상..");
		return FALSE;
	}
	if(RxBuff[2] != 0x00 || RxBuff[3] != 0xFF)                // Network NO, PC NO
	{
		m_strErrMsg.Format("RecvWriteAck.. Network or PC NO 이상..");
		return FALSE;
	}
	if(RxBuff[4] != 0xFF || RxBuff[5] != 0x03 || RxBuff[6] != 0x00)   // Specific value
	{
		m_strErrMsg.Format("RecvWriteAck.. Specific Value 이상..");
		return FALSE;
	}

	WORD wErrNo = SwapToWord(RxBuff+9);
	if(wErrNo)
	{
		m_strErrMsg.Format("RecvWriteAck.. 응답 수신.. 오류코드[%d]", wErrNo);
		return FALSE;
	}

	return TRUE;
}

int CMelsecSc3E::RecvFrame(BYTE *pRxBuff)
{
	DWORD dwLen = 0, nRealLen, nTotalLen = 0;

	m_pSock->m_bReceiving = TRUE;

	if(WaitForSingleObject(m_pSock->m_hEventRecv, 2000) == WAIT_TIMEOUT)
	{
		if(WaitForSingleObject(m_pSock->m_hEventRecv, 2000) == WAIT_TIMEOUT)
		{
			m_strErrMsg.Format("RecvFrame.. 수신 대기시간 초과 에러");
			return FALSE;
		}
	}

	if(m_pSock->IOCtl( FIONREAD, &dwLen ) == FALSE)
	{
		m_strErrMsg.Format("RecvFrame.. IOCtl 에러 [%s]", CLib::GetSystemErrMsg());
		return FALSE;
	}

	if ((nRealLen = m_pSock->Receive(pRxBuff, dwLen)) != dwLen)
	{
		m_strErrMsg.Format("RecvFrame.. Receive에러 [%s]", CLib::GetSystemErrMsg());
		return FALSE;
	}

	nTotalLen = nRealLen;

	if (dwLen < BINARY_HEADER_LEN)
	{
		if(WaitForSingleObject(m_pSock->m_hEventRecv, 2000) == WAIT_TIMEOUT)
		{
			m_strErrMsg.Format("RecvFrame.. 수신 대기시간 초과 에러#2 [dwLen=%d]", dwLen);
			return FALSE;
		}

		if(m_pSock->IOCtl( FIONREAD, &dwLen ) == FALSE)
		{
			m_strErrMsg.Format("RecvFrame.. IOCtl 에러#2 [%s]", CLib::GetSystemErrMsg());
			return FALSE;
		}

		if ((nRealLen = m_pSock->Receive(pRxBuff+nRealLen, dwLen)) != dwLen)
		{
			m_strErrMsg.Format("RecvFrame.. Receive에러#2 [%s]", CLib::GetSystemErrMsg());
			return FALSE;
		}

		nTotalLen += nRealLen;

		if(nRealLen <= BINARY_HEADER_LEN)
		{
			m_strErrMsg.Format("RecvFrame.. 수신 데이터 길이[%d] 이상", nRealLen);
			return FALSE;
		}
	}

	m_pSock->m_bReceiving = FALSE;

	return nTotalLen;
}

WORD CMelsecSc3E::SwapToWord(BYTE *pSrc)
{
	return (WORD)(pSrc[1] << 8) | pSrc[0];
}

DWORD CMelsecSc3E::SwapToDWord(BYTE *pSrc)
{
	return (DWORD)(pSrc[3] << 24) | (pSrc[2] << 16) | (pSrc[1] << 8) | pSrc[0];
}


int CMelsecSc3E::GetDataLength(int nUnitType, WORD wLen)
{
	return (nUnitType == CMD_WORD_UNIT) ? (wLen*2) : ((wLen/2)+(wLen%2));
}