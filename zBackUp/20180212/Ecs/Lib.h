// Gloval Library Header
#include "EcsDef.h"
#include <EcsEnv.h>
#ifndef __LIB_H__
#define __LIB_H__

class CLib
{
public:
	static CString GetStackerErrorInfo(int nErrorCode);
	static int GetBank(CString strLocation);
	static int GetBay(CString strLocation);
	static int GetLevel(CString strLocation);
	static int ConvertCustomToPosition(int nPosition);
	static int ConvertPositionToCustom(int nType, int nPosition);
	static CString ConvertLocationToCustom(CString strLocation);
	static BOOL ConvertFloatStrToCustom(CString strFloat, char *pDest, int nTotalLen, int nPrecision);
	static BOOL IsValidCustomJobType(int nJobType);
	static BOOL IsValidLuggNum(int nLuggNum);
	static CString BatchStatusToString(BYTE bMode);
	static CString StackerStatusToString(WORD bStatus);
	static CString StackerModeToString(BYTE bMode);
	static CString StackerJobTypeToString(BYTE bJobType);
	static BOOL IsValidDestPos(BYTE bDestPos, int nScNum);
	static BOOL IsValidStartPos(BYTE bStartPos, int nScNum);
	static CString ExtractString(BYTE * pbFrame, int nLen);
	static int ExtractInt(BYTE* pbFrame, int nLen);
	static int GetStackerNum(CString strLocation);
	static BOOL IsValidLocation(CString strLocation);
	static CString CLib::ConvertReasonToString(int nType);

	static int GetPlcNumByTrack(int nTrackNum);

	static CString GetSystemErrMsg(int nErrNo=0);
	static CString GetLinearStartStationName(int nSequenceNum);
	static CString GetLinearEndStationName(int nSequenceNum);
	static CString GetLinearStationSpecialName(int nSequenceNum);
	static CString GetLinearTurnName(int nSequenceNum);
	static int GetStartNumToCombo(int nSequenceNum);
	static int GetEndNumToCombo(int nSequenceNum);
	static int GetComboToStartNum(int nSequenceNum);
	static int GetComboToEndNum(int nSequenceNum);
	static int GetLinearTurnNo(int nSequenceNum);
	static int GetLinearStationNum(int nSequenceNum); // 6,7,8
	static int GetLinearStoStnNumPerCvPlc(int nPlcNum, int nSequenceNum);
	static int GetLinearRetStnNumPerCvPlc(int nPlcNum, int nSequenceNum);
	static int GetTrackByStationNum(int nStationNum);
	static int GetTrackByBcrStationNum(int nStationNum);
	static int GetTrackByChkNum(int nStationNum);
	static int GetScStoHSTrack(int nScNum, BYTE bFirstFork);
	static int GetScStoHSTrack(int nPlcNum, int nSequenceNum, BYTE bFirstFork);

	static int GetScRetHSTrack(int nScNum, BYTE bFirstFork);
	static int GetScRetHSTrack(int nPlcNum, int nSequenceNum, BYTE bFirstFork);
	
	static int GetStoHSTrack(int nScNum);
	static int GetStoHSTrack(int nPlcNum, int nSequenceNum);
	
	static BOOL IsSet(BYTE Byte, int nPos);
	static BOOL IsSet(WORD Word, int nPos);
	static int Power(int x, int y);
	static int HexToInt(BYTE bHex);
	static void ConvertAscToHex(char* pOrg, char* pDest);
	static int ConvertHexStr2HexValue(char *strHex, int nLen);
	static BYTE HexStrToBYTE(BYTE *bySrc);
	static WORD HexStrToWORD(BYTE *bySrc);
	static CString ConvertStackerMode(unsigned char ucMode);

	static int GetStoStnCntPerCvPlc(int nPlcNum);
	static int GetRetStnCntPerCvPlc(int nPlcNum);
	static int GetRetChkCntPerCvPlc(int nPlcNum);
	static int GetScCntPerCvPlc(int nPlcNum);
	static int GetTrackCntPerCvPlc(int nPlcNum);
	static int GetOpBoxCntPerCvPlc(int nPlcNum);
	static int GetStoHSCntPerCvPlc(int nPlcNum);
	static int GetRetHSCntPerCvPlc(int nPlcNum);

	static CString ConvertJobTypeToString(int nType);
	static int ConvertJobTypeToCustom(int nType);
	static int ConvertCustomToJobType(int nType);
	static int ConvertJobTypeToPattern(int nJobType);
	static int ConvertJobTypeToPattern2(int nJobType);

	static CString StackerRcModeToString(uchar ucMode);
	static CString StackerScModeToString(uchar ucMode);
	static CString StackerActiveToString(uchar ucActive);

	static BOOL CLib::IsValidHostStartPos(int bStartPos);
	static BOOL CLib::IsValidHostDestPos(int bDestPos);

	static int CLib::GetStartTrackNumPerCvPlc(int nPlcNum);

    static CString GetRgvErrorCode(int nErrorCode);
    static int GetRgvStoStartHSTrack(int nRgvNum, int nSequenceNum);
    static int GetRgvRetStartHSTrack(int nRgvNum, int nSequenceNum);
    static int GetRgvRetStartHSTrack2(int nRgvNum, int nSequenceNum);
    static int GetRgvDestHSTrack(int nRgvNum, int nSequenceNum);
    static int GetRgvStoDestHSTrack(int nRgvNum, int nLineNum);
    static int GetRgvRetDestHSTrack(int nStationNum, int nRgvNum);
	static int GetRgvStartHSTrack(int nRgvNum, int nSequenceNum);

//^^^^^^^^^^^^^ RGV Ãâ¹ßH/S °¹¼ö ^^^^^^^^^^^^^^//
    static int GetStartStnCntPerRgv(int nRgvNo);
    static int GetDestStnCntPerRgv(int nRgvNo);
    static int GetStoStnCntPerRgv(int nRgvNo);
    static int GetRetStnCntPerRgv(int nRgvNo);
	static CString GetCvErrorCode(int nErrorCode);


#ifdef OPT_SC_SHINHUNG_USE
	static CString StackerPhaseToString(BYTE ucPhase);
#endif
};

#endif // __LIB_H__
