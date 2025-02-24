
#ifndef __MELSEC3E_H__
#define __MELSEC3E_H__

#include "EcsDoc.h"

#define CMD_WORD_UNIT		0x00
#define CMD_BIT_UNIT		0x01

#define	DEVICE_CODE_SM		0x91
#define	DEVICE_CODE_SD		0xA9
#define	DEVICE_CODE_X		0x9C
#define	DEVICE_CODE_Y		0x9D
#define	DEVICE_CODE_M		0x90
#define	DEVICE_CODE_L		0x92
#define	DEVICE_CODE_F		0x93
#define	DEVICE_CODE_V		0x94
#define	DEVICE_CODE_B		0xA0
#define	DEVICE_CODE_D		0xA8
#define	DEVICE_CODE_W		0xB4
#define	DEVICE_CODE_TS		0xC1
#define	DEVICE_CODE_TC		0xC0
#define	DEVICE_CODE_TN		0xC2
#define	DEVICE_CODE_SS		0xC7
#define	DEVICE_CODE_SC		0xC6
#define	DEVICE_CODE_SN		0xC8
#define	DEVICE_CODE_CS		0xC4
#define	DEVICE_CODE_CC		0xC3
#define	DEVICE_CODE_CN		0xC5
#define	DEVICE_CODE_SB		0xA1
#define	DEVICE_CODE_SW		0xB5
#define	DEVICE_CODE_S		0x98
#define	DEVICE_CODE_DX		0xA2
#define	DEVICE_CODE_DY		0xA3
#define	DEVICE_CODE_Z		0xCC
#define	DEVICE_CODE_R		0xAF
#define	DEVICE_CODE_ZR		0xB0

#define BINARY_HEADER_LEN	11


class CMelsec3E
{

public:
	CMelsec3E(CCvSocket *pSock);

// Attributes
protected:
	CCvSocket *m_pSock;

	CString m_strErrMsg;


// operations
public:
	BOOL Read(int nUnitType, BYTE *pRxBuff, BYTE DeviceCode, int nStartAddr, WORD wReadLen);
	BOOL Write(int nUnitType, BYTE *pTxBuff, BYTE DeviceCode, int nStartAddr, WORD wWriteLen);

	BOOL RecvReadAck(int nUnitType, BYTE *pRxBuff, WORD wReadCnt);
	BOOL RecvWriteAck();

	int RecvFrame(BYTE *pRxBuff);

	WORD SwapToWord(BYTE *pSrc);
	DWORD SwapToDWord(BYTE *pSrc);

	int GetDataLength(int nUnitType, WORD wLen);

//	int  Write2Word(BYTE *pData, int nTrackNum);
//	int  Write1Word(BYTE *pData, int nTrackNum);

	void HexStr2Word(BYTE *bySrc, WORD *byDest);
	void HexStr1Word(BYTE *bySrc, BYTE *byDest);
	void HexStr1Byte(BYTE *bySrc, BYTE *byDest);
	void HexStr2Byte(BYTE *bySrc, BYTE *byDest);

};

#endif