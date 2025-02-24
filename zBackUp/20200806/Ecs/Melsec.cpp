// CPlc.cpp : implementation of the CConfig class
//

#include "stdafx.h"
#include "Melsec.h"
#include "Lib.h"

CMelsec::CMelsec() : CSerial()
{
	m_byAddr = 0xFF;
	m_strErrorMsg = "";
}

BOOL CMelsec::Connect(LPSTR strComName, 
		   DWORD dwBaudRate,
		   BYTE byByteSize,
		   BYTE byParity,
		   BYTE byStopBits,
		   BYTE byFlowCtrl)
{
	SetConfig(strComName, dwBaudRate, byByteSize, byParity, byStopBits, byFlowCtrl);
	return Open();
}

void CMelsec::CheckSum(BYTE *pBuff, int nLen, BYTE *pSumA, BYTE *pSumB)
{
    int     SumA, SumB, Check = 0;

    for (int i=1; i<nLen; i++) Check += pBuff[i] & 0x00ff;

    SumA = Check & 0x00ff;
    SumA = SumA >> 4;
    SumB = Check & 0x000f;

    if (SumA <= 0x09)
        SumA = SumA + 0x30;
    else {
        SumA = SumA - 0x09;
        SumA = SumA + 0x40;
    }
    if (SumB <= 0x09)
        SumB = SumB + 0x30;
    else {
        SumB = SumB - 0x09;
        SumB = SumB + 0x40;
    }

    *pSumA = (BYTE) SumA;
    *pSumB = (BYTE) SumB;
}

BOOL CMelsec::ReadUptoLF(BYTE *pRxBuff, int nByteCnt, int *nReadCnt)
{
	BYTE	DummyBuf[1024];
	memset(DummyBuf, 0x00, sizeof(DummyBuf));

	if (Recv(pRxBuff, nByteCnt) == TRUE) {
		*nReadCnt = nByteCnt;
		return	TRUE;
	}

	*nReadCnt = 0;
	Recv(DummyBuf, 1024);
	return FALSE;
}

BOOL CMelsec::ResponseRead(BYTE *pRxBuff, int nWordCnt, int *nReadCnt)
{
	BOOL bAck = TRUE;
	BYTE   SumA, SumB;

//	MELSEC PLC 책자 참조 2002. 2. 27
	int    nLen = (nWordCnt * 4) + 10; // SumA+SumB+ETX+CR+LF
//	int    nLen = (nWordCnt * 4) + 8;  // '2'
//	int    nLen = (nWordCnt * 4) + 6;  // '1' CheckSum 확인 안하는 옵션

	if (!ReadUptoLF(pRxBuff, nLen, nReadCnt))
		return FALSE;

	if (pRxBuff[0] != STX)			bAck = FALSE;
	if (pRxBuff[nLen-1] != LF)		bAck = FALSE;
	if (pRxBuff[nLen-2] != CR)		bAck = FALSE;

	CheckSum(pRxBuff, nLen-4, &SumA, &SumB);
	if (pRxBuff[nLen-4] != SumA)	bAck = FALSE;
	if (pRxBuff[nLen-3] != SumB)	bAck = FALSE;

	if (pRxBuff[nLen-5] != ETX)		bAck = FALSE;


	bAck ? AckResponse() : NakResponse();
	return bAck;

/*	int     nLen;
	BYTE   SumA, SumB;
	int		nByteCnt = (nWordCnt * 4) + 10;

		if (ReadUptoLF(pRxBuff, nByteCnt, nReadCnt)) {
	switch (pRxBuff[0]) {
		case    STX :
			nLen = *nReadCnt;
			CheckSum(pRxBuff, nLen-4, &SumA, &SumB);
			if (pRxBuff[nLen-4] != SumA || pRxBuff[nLen-3] != SumB) {
				NakResponse();
				return FALSE;
			} else {
				AckResponse();
				return TRUE;
			}
//		case    ACK :
//			return TRUE;
			break;
		default :
			NakResponse();
			return FALSE;
		}
	}

	return FALSE;
*/
}

BOOL CMelsec::ResponseWrite()
{
	BYTE	RxBuff[256];
	int     nReadCnt=0;

	memset(RxBuff, 0x0, sizeof(RxBuff));
	if (!ReadUptoLF(RxBuff, 5, &nReadCnt))
	{
		m_strErrorMsg.Format("CMelsec::ResponseWrite 에러 [%s]", RxBuff);
		return FALSE;
	}

	if (nReadCnt !=  5)
	{
		m_strErrorMsg.Format("CMelsec::ResponseWrite 에러 수신데이터[%s] 길이이상", RxBuff);
		return FALSE;
	}
	
	if (RxBuff[0] != NAK)
		return TRUE;

//  쓰레기 데이터
//	if (RxBuff[0] != ACK)
	{
		m_strErrorMsg.Format("CMelsec::ResponseWrite 에러 수신데이터[%s] NAK 응답", RxBuff);
		return FALSE;
	}

	return FALSE;
}

BOOL CMelsec::Read(BYTE *pRxBuff, int BaseAddr, int nWordCnt, int Type,  int *nReadCnt)
{
   BYTE    SumA, SumB, TxBuff[256];
    char    szStartAddr[6], szRange[3];

    if(Type == 'D')
        sprintf(szStartAddr, "D%.4d", BaseAddr);
    else
        sprintf(szStartAddr, "M%.4d", BaseAddr);

    sprintf(szRange, "%.2X", nWordCnt);

	memset(TxBuff, 0x0, sizeof(TxBuff));

    TxBuff[0]  = ENQ;
    if (Type == 'D')
        memcpy(TxBuff+1, "00FFWR0", 7);
    else
        memcpy(TxBuff+1, "00FFBR0", 7);

    memcpy(TxBuff+8, szStartAddr, 5);
    memcpy(TxBuff+13, szRange, 2);

    CheckSum(TxBuff, 15, &SumA, &SumB);
    TxBuff[15] = SumA;
    TxBuff[16] = SumB;
	TxBuff[17] = CR;
	TxBuff[18] = LF;

    Send(TxBuff, 19);
	return	ResponseRead(pRxBuff, nWordCnt, nReadCnt);
}

int CMelsec::Write(BYTE *pTxBuff, int BaseAddr, int nWordCnt, int Type)
{
    BYTE	TxBuff[256], SumA, SumB;
    char    szStartAddr[6], szRange[6];
	m_strErrorMsg = "";

	memset(TxBuff, 0x0, sizeof(TxBuff));

    if(Type == 'D')
        sprintf(szStartAddr, "D%.4d", BaseAddr);
    else
        sprintf(szStartAddr, "M%.4d", BaseAddr);

    sprintf(szRange, "%.2X", nWordCnt);

    TxBuff[0]  = ENQ;
    if (Type == 'D')
        memcpy(TxBuff+1, "00FFWW0", 7);
    else
        memcpy(TxBuff+1, "00FFBW0", 7);

    memcpy(TxBuff+8, szStartAddr, 5);
    memcpy(TxBuff+13, szRange, 2);

    if (Type == 'D')
	{
		memcpy(TxBuff+15, pTxBuff, nWordCnt * 4);
	    CheckSum(TxBuff, 15+nWordCnt*4, &SumA, &SumB);
		TxBuff[15 + nWordCnt*4] = SumA;
	    TxBuff[15 + 1 + nWordCnt*4] = SumB;
		TxBuff[15 + 2 + nWordCnt*4] = CR;
	    TxBuff[15 + 3 + nWordCnt*4] = LF;
		
		if( Send(TxBuff, 15 + 4 + nWordCnt*4) == FALSE)
		{
			m_strErrorMsg.Format("CMelsec::Write 에러=[%s]", CLib::GetSystemErrMsg());
			return FALSE;
		}
	}
	else
	{
		memcpy(TxBuff+15, pTxBuff, nWordCnt);
	    CheckSum(TxBuff, 15+nWordCnt, &SumA, &SumB);
		TxBuff[15 + nWordCnt] = SumA;
	    TxBuff[15 + 1 + nWordCnt] = SumB;
		TxBuff[15 + 2 + nWordCnt] = CR;
	    TxBuff[15 + 3 + nWordCnt] = LF;

		if( Send(TxBuff, 15 + 4 + nWordCnt) == FALSE)
		{
			m_strErrorMsg.Format("CMelsec::Write 에러=[%s]", CLib::GetSystemErrMsg());
			return FALSE;
		}
	}

	return ResponseWrite();
}


int CMelsec::AckResponse()
{
	BYTE	TxBuff[256];
	memset(TxBuff, 0x0, sizeof(TxBuff));

	TxBuff[0] = ACK;
	memcpy(TxBuff+1, "00FF", 4);
	TxBuff[5] = CR;
	TxBuff[6] = LF;

	Send(TxBuff, 7);
	return TRUE;
}

int CMelsec::NakResponse()
{
	BYTE	TxBuff[1024];
	memset(TxBuff, 0x0, sizeof(TxBuff));

	TxBuff[0] = NAK;
	memcpy(TxBuff+1, "00FF", 4);
	TxBuff[5] = CR;
	TxBuff[6] = LF;

	Send(TxBuff, 7);
	Recv(TxBuff, 1024);
	return TRUE;
}

