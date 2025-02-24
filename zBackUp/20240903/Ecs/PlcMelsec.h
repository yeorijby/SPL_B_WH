// PLC Melsec Class

#ifndef __PLC_H__
#define __PLC_H__

#include "Serial.h"
#include "Thread.h"
#include "ConveyorTrackInfo.h"
#include "EcsDoc.h"


class CPlcMelsec : public CSerial
{
// constructor & destructor
public:
	CPlcMelsec() : CSerial() { m_byAddr = 0xFF; };

// Attributes
protected:
public:
	BYTE m_byAddr;

// operations
public:
	BOOL Connect(LPSTR strCommName,
  			     DWORD dwBaudRate = (DWORD)9600,
				 BYTE byByteSize = (BYTE)8,
				 BYTE byParity = NOPARITY,
				 BYTE byStopBits = ONESTOPBIT,
				 BYTE byFlowCtrl = 0);
	static void CheckSum(BYTE *pBuff, int nLen, BYTE *pSumA, BYTE *pSumB);
	BOOL ReadUptoLF(BYTE *pRxBuff, int nByteCnt, int *nReadCnt);
	BOOL ResponseRead(BYTE *pRxBuff, int nWordCnt, int *nReadCnt);
	BOOL Response();
	BOOL Read(BYTE *pRxBuff, int BaseAddr, int n, int Type,  int *nReadCnt);
	int  Write2Word(BYTE *pData, int nTrackNum);
	int  Write1Word(BYTE *pData, int nTrackNum);
	int  Write3Word(BYTE *pData, int nTrackNum);
	int  Write6Word(BYTE *pData, int nTrackNum);
	int  Write(BYTE *pTxBuff, int BaseAddr, int nWordCnt, int Type);
	int  AckResponse();
	int  NakResponse();
	void HexStr2Word(BYTE *bySrc, WORD *byDest);
	void HexStr1Word(BYTE *bySrc, BYTE *byDest);

// Overrides
};

#endif // __PLC_H__
