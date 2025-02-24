
#ifndef _CV_H_
#define _CV_H_

#include "Melsec3E.h"

class CEcsDoc;

class CConveyor : public CMelsec3E
{
// constructor & destructor
public:
//  Conveyor() : CMelsec3E() {};
	CConveyor(int nNum, CEcsDoc* pDoc,  CCvSocket *pSock);

// Attributes
public:
	CEcsDoc* m_pDoc;
	int m_nNum;
	int m_nArrivedLuggNum1;
	int m_nArrivedLuggNum2;
	int m_nArrivedLuggNum3;
	int m_nArrivedLuggNum4;
	int m_nArrivedCheckLuggNum;
	int m_nArrivedRemoveCheckNum[3];
	int m_nLineCountLuggNum;

	int m_nCvNextRtn;

	int m_nStoPrevLuggNum;
	
// operations
public:

	void ParsingFrame(BYTE * pRxBuff, int nFromTrackNum, int nCnt);
	void ParsingFrameE(BYTE * pRxBuff);
    void ParsingFrame2(BYTE *pRxBuff, int nFromTrackNum, int nCnt);
    void ParsingFrame7(BYTE *pRxBuff, int nFromTrackNum, int nCnt);
    void ParsingFrame8(BYTE *pRxBuff, int nFromTrackNum, int nCnt);

	BOOL RetrieveStationCheck(CEcsDoc* pDoc);

    void ArrivedCheck1();
    void ArrivedCheck2();
    void ArrivedCheck3();
	void ArriveCountCheck();
	void ArriveDataCopy();
	void LineCountCheck();

	void ArriveRemoveCheck4Group();
	void ArriveRemoveCheck5Group();
	void ArriveRemoveCheck6Group();

	void CvDataChange2GroupTo1Group();
	void CvDataChange3GroupTo4Group();
	void CvDataChange4GroupTo5Group();
	void CvDataChange5GroupTo6Group();
	void CvDataChange1GroupTo7Group();
	void CvDataChange8GroupTo7Group();
	void CvDataChange7GroupTo8Group();
	void CvDataChange3GroupTo8Group();

	void RemoveCvData3Group();
	void RemoveCvData3GroupTo8Group();
	void RemoveCvData4Group();
	void RemoveCvData5Group();
	void RemoveCvData1Group();
	void RemoveCvData7Group();
	void RemoveCvData8Group();
	//void RemoveCvData8GroupTo3Group();

	int  WriteTrackInfo(int nTrackNum, int nLuggNum, int nJobType, int nStartPos, int nDestPos, int nLastPallet = 0);
	int  WriteTrackInfo2(int nTrackNum, int nLuggNum, int nStartPos, int nDestPos, int nJobType = 0, int nComplete=0);
    int  WriteTrackInfo7(int nTrackNum, int nLuggNum, int nLuggNum2, int nStartPos, int nDestPos, int nJobType, int nComplete=0, int nSize=0);

	int  WriteInCounterReset(int nStartAddr);
    int  WriteTroubleInfo(int nAddressNum, WORD wAddressData);
	int  WritePlcCountInfo(int nTrackNum, int nPlcCount);

	void StoInvokeCheck();
	void StoInvokeCheck2();
	void StoMoveInvokeCheck2();
	void StoInvokeCheck7();
	void StoManualInvokeCheck7();
	void ManualInvokeCheck7();
	void SiteInvokeCheck7();

	void ParsingStatus7(BYTE *pRxBuff);
	void ParsingStatus8(BYTE *pRxBuff);

	BOOL RetInvokeCheck();
	BOOL RetInvokeCheck2();

	void RgvCompleteCheck1();
	void RgvCompleteCheck2();
	void RgvCompleteCheck3();
	void RgvCompleteCheck4();

	int  ReadStatus1();
	int  ReadStatus2();
	int  ReadStatus3();
	int  ReadStatus4();
	int  ReadStatus5();
	int  ReadStatus6();
	int  ReadStatus7();
	int  ReadStatus8();

	void ParsingExtraFrame1(BYTE * pRxBuff);
	void ParsingExtraFrame2(BYTE * pRxBuff);
	void ParsingExtraFrame2_1(BYTE * pRxBuff);
	void ParsingExtraFrame3(BYTE * pRxBuff);
	void ParsingExtraFrame4(BYTE * pRxBuff);
	void ParsingExtraFrame5(BYTE * pRxBuff);
	void ParsingExtraFrame6(BYTE * pRxBuff);

	void ParsingBufferLine4(BYTE * pRxBuff);
	void ParsingBufferLine5(BYTE * pRxBuff);
	void ParsingBufferLine6(BYTE * pRxBuff);

	void ParsingCount(BYTE * pRxBuff);

	BOOL InvokeCheck();
    BOOL CvRtvInvokeCheck(int nRank);

	void RgvEmergencyStop(BOOL bStop, int nRgvNum);

// Overrides
};

#endif _CV_H_