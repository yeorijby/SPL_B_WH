

#ifndef __MELSEC_H__
#define __MELSEC_H__

#include "Serial.h"
#include "EcsDoc.h"
#include <EcsEnv.h>

class CMelsec : public CSerial
{
public:
	CMelsec();

// Attributes
protected:
public:
	BYTE m_byAddr;
	CString m_strErrorMsg;

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
	BOOL ResponseWrite();

	BOOL Read(BYTE *pRxBuff, int BaseAddr, int nWordCnt, int Type,  int *nReadCnt);
	BOOL Write(BYTE *pTxBuff, int BaseAddr, int nWordCnt, int Type);

	int  AckResponse();
	int  NakResponse();


// Overrides
};

#endif // __PLC_H__
