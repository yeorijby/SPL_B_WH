
#include "stdafx.h"
#include "PlcMelsec.h"
#include "Lib.h"
#include "Ecs.h"

BOOL CPlcMelsec::Connect(LPSTR strComName,
		   DWORD dwBaudRate,
		   BYTE byByteSize,
		   BYTE byParity,
		   BYTE byStopBits,
		   BYTE byFlowCtrl)
{
	SetConfig(strComName, dwBaudRate, byByteSize, byParity, byStopBits, byFlowCtrl);
	return Open();
}

void CPlcMelsec::CheckSum(BYTE *pBuff, int nLen, BYTE *pSumA, BYTE *pSumB)
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

BOOL CPlcMelsec::ReadUptoLF(BYTE *pRxBuff, int nByteCnt, int *nReadCnt)
{
	BYTE	DummyBuf[1024];

	if (Recv(pRxBuff, nByteCnt) == TRUE) {
		*nReadCnt = nByteCnt;
		return	TRUE;
	}

	*nReadCnt = 0;
	Recv(DummyBuf, 1024);
	return FALSE;
}


BOOL CPlcMelsec::ResponseRead(BYTE *pRxBuff, int nWordCnt, int *nReadCnt)
{
	int     nLen;
	BYTE   SumA, SumB;
	int		nByteCnt = (nWordCnt * 4) + 10;
	//int		nByteCnt = (nWordCnt * 4) + 6;

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
}

BOOL CPlcMelsec::Response()
{
	BYTE	RxBuff[256];
	BYTE	DummyBuf[1024];
	int     nReadCnt=0;

	memset(RxBuff, 0x0, sizeof(RxBuff));
	if (!ReadUptoLF(RxBuff, 7, &nReadCnt))
	{
		return FALSE;
	}
	if (nReadCnt !=  7)
	{
		return FALSE;
	}
	if (RxBuff[0] != ACK)
	{
		Recv(DummyBuf, 1024);
		return TRUE;
	}

	return TRUE;
}

BOOL CPlcMelsec::Read(BYTE *pRxBuff, int BaseAddr, int nWordCnt, int Type,  int *nReadCnt)
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
	Sleep(300L);
	return	ResponseRead(pRxBuff, nWordCnt, nReadCnt);
}

int CPlcMelsec::Write2Word(BYTE *pData, int nTrackNum)
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

	Send(TxBuff, 27);
	Sleep(200L);
	return Response();
}

int CPlcMelsec::Write3Word(BYTE *pData, int nTrackNum)
{
    BYTE	TxBuff[256], SumA, SumB;
    char    szAddr[32];

	memset(TxBuff, 0x0, sizeof(TxBuff));
	if (nTrackNum < 70)
		sprintf(szAddr, "D%.4d", (nTrackNum-38)*3 + 78);
	else if (nTrackNum < 104)
		sprintf(szAddr, "D%.4d", (nTrackNum-102)*3 + 189);
	else
		sprintf(szAddr, "D%.4d", (nTrackNum-110)*3 + 174);

    TxBuff[0]  = ENQ;
    memcpy(TxBuff+1, "00FFWW0", 7);
    memcpy(TxBuff+8, szAddr, 5);

    TxBuff[13] = 0x30;
	TxBuff[14] = 0x33;		// Range : 3 Word Write
	memcpy(TxBuff+15, pData, 12);

    CheckSum(TxBuff, 27, &SumA, &SumB);
    TxBuff[27] = SumA;
    TxBuff[28] = SumB;
    TxBuff[29] = CR;
    TxBuff[30] = LF;

	Send(TxBuff, 31);
	Sleep(200L);
	return Response();
}

int CPlcMelsec::Write6Word(BYTE *pData, int nTrackNum)
{
    BYTE	TxBuff[256], SumA, SumB;
    char    szAddr[32];

	memset(TxBuff, 0x0, sizeof(TxBuff));
    sprintf(szAddr, "D%.4d", (nTrackNum-38)*3 + 78);

    TxBuff[0]  = ENQ;
    memcpy(TxBuff+1, "00FFWW0", 7);
    memcpy(TxBuff+8, szAddr, 5);

    TxBuff[13] = 0x30;
	TxBuff[14] = 0x36;		// Range : 2 Word Write
	memcpy(TxBuff+15, pData, 24);

    CheckSum(TxBuff, 39, &SumA, &SumB);
    TxBuff[39] = SumA;
    TxBuff[40] = SumB;
    TxBuff[41] = CR;
    TxBuff[42] = LF;

	Send(TxBuff, 43);
	Sleep(200L);
	return Response();
}

int CPlcMelsec::Write1Word(BYTE *pData, int nTrackNum)
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

int CPlcMelsec::Write(BYTE *pTxBuff, int BaseAddr, int nWordCnt, int Type)
{
    BYTE	TxBuff[256], SumA, SumB;
    char    szStartAddr[6], szRange[6];

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
			return FALSE;
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
			return FALSE;
	}

	Sleep(500L);
	return Response();
}

int CPlcMelsec::AckResponse()
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

int CPlcMelsec::NakResponse()
{
	BYTE	TxBuff[1024];

	memset(TxBuff, 0x0, sizeof(TxBuff));
	TxBuff[0] = NAK;
	memcpy(TxBuff+1, "00FF", 4);
	TxBuff[5] = CR;
	TxBuff[6] = LF;

	Send(TxBuff, 7);
	Sleep(300L);
	Recv(TxBuff, 1024);
	return TRUE;
}

void CPlcMelsec::HexStr2Word(BYTE *bySrc, WORD *byDest)
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

void CPlcMelsec::HexStr1Word(BYTE *bySrc, BYTE *byDest)
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
