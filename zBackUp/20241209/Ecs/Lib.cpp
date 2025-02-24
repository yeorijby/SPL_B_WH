// Gloval Library..
#include "stdafx.h"

#include "EcsDef.h"
#include <EcsEnv.h>
#include "Lib.h"

int CLib::GetScStoHSTrack(int nScNum, BYTE bFirstFork)
{
	int nTrackNum = 0;

	switch ( nScNum )
	{
	case	0:
		if (bFirstFork)
			nTrackNum = 15;
		else
			nTrackNum = 14;
		break;
	case	1:
		if (bFirstFork)
			nTrackNum = 20;
		else
			nTrackNum = 19;
		break;
	case	2:
		if (bFirstFork)
			nTrackNum = 25;
		else
			nTrackNum = 24;
		break;
	case	3:
		if (bFirstFork)
			nTrackNum = 30;
		else
			nTrackNum = 29;
		break;
	case	4:
		if (bFirstFork)
			nTrackNum = 35;
		else
			nTrackNum = 34;
		break;
	case	5:
		if (bFirstFork)
			nTrackNum = 40;
		else
			nTrackNum = 39;
		break;
	}

	return (nTrackNum - 1);
}

int CLib::GetScStoHSTrack(int nPlcNum, int nSequenceNum, BYTE bFirstFork)
{
	switch ( nPlcNum )
	{
	case	CV_1_PLC:
		return GetScStoHSTrack(nSequenceNum, bFirstFork);
	case	CV_2_PLC:
		break;
	}

	return -1;
}

int CLib::GetScRetHSTrack(int nScNum, BYTE bFirstFork)
{
	int nTrackNum = 0;

	switch ( nScNum )
	{
	case	0:
		if (bFirstFork)
			nTrackNum = 301;
		else
			nTrackNum = 302;
		break;
	case	1:
		if (bFirstFork)
			nTrackNum = 306;
		else
			nTrackNum = 307;
		break;
	case	2:
		if (bFirstFork)
			nTrackNum = 311;
		else
			nTrackNum = 312;
		break;
	case	3:
		if (bFirstFork)
			nTrackNum = 316;
		else
			nTrackNum = 317;
		break;
	case	4:
		if (bFirstFork)
			nTrackNum = 321;
		else
			nTrackNum = 322;
		break;
	case	5:
		if (bFirstFork)
			nTrackNum = 326;
		else
			nTrackNum = 327;
		break;
	}

	return (nTrackNum - 1);
}

int CLib::GetScRetHSTrack(int nPlcNum, int nSequenceNum, BYTE bFirstFork)
{
	switch ( nPlcNum )
	{
	case	CV_1_PLC:
		break;
	case	CV_2_PLC:
		break;
	case	CV_3_PLC:
		return GetScRetHSTrack(nSequenceNum, bFirstFork);
	}

	return -1;
}

int CLib::GetStoHSTrack(int nScNum)
{
	int nTrackNum = 0;
	switch (nScNum)
	{
	case 0:
			nTrackNum = 14;
			break;
	case 1:
			nTrackNum = 21;
			break;
	case 2:
			nTrackNum = 28;
			break;
	default:
			break;
	}

	return (nTrackNum - 1);
}

int CLib::GetStoHSTrack(int nPlcNum, int nSequenceNum)
{
	int nTrackNum = 0;

	switch ( nPlcNum )
	{
	case	CV_1_PLC:
		switch ( nSequenceNum )
		{
		case	0:
			nTrackNum = 14;
			break;
		case	1:
			nTrackNum = 21;
			break;
		case	2:
			nTrackNum = 28;
			break;
		}
		break;
	case	CV_2_PLC:
		break;
	}

	return (nTrackNum - 1);
}

CString CLib::GetLinearStartStationName(int nSequenceNum)
{

	switch (nSequenceNum)
	{
	case	0:
		return CString("생산입고대");
	case	1:
		return CString("외주입고대");
	default:
		CString strTemp;
		strTemp.Format("DEF(%d)", nSequenceNum);
		return strTemp;
	}
}

CString CLib::GetLinearEndStationName(int nSequenceNum)
{

	switch (nSequenceNum)
	{
	case	0:
		return CString("출하분류대#1");
	case	1:
		return CString("출하분류대#2");
	case	2:
		return CString("출하분류대#3");
	case	3:
		return CString("출하이동대");
	default:
		CString strTemp;
		strTemp.Format("DEF(%d)", nSequenceNum);
		return strTemp;
	}
}

CString CLib::GetLinearStationSpecialName(int nSequenceNum)
{

	switch (nSequenceNum)
	{
	case	0:
		return CString("실Pallet");
	case	1:
		return CString("공Pallet");
	default:
		CString strTemp;
		strTemp.Format("DEF(%d)", nSequenceNum);
		return strTemp;
	}
}

CString CLib::GetLinearTurnName(int nSequenceNum)
{

	switch (nSequenceNum)
	{
	case	0:
		return CString("정보없음");
	case	1:
		return CString("좌측");
	case	2:
		return CString("우측");
	default:
		CString strTemp;
		strTemp.Format("DEF(%d)", nSequenceNum);
		return strTemp;
	}
}

int CLib::GetStartNumToCombo(int nSequenceNum)
{

	switch (nSequenceNum)
	{
	case	1:
		return 0;
	case	2:
		return 1;
	case	3:
		return 2;
	case	4:
		return 3;
	case	5:
		return 4;
	case	6:
		return 5;
	case	8:
		return 6;
	case	9:
		return 7;
	case	10:
		return 8;
	default:
		return 100;
	}
}

int CLib::GetEndNumToCombo(int nSequenceNum)
{

	switch (nSequenceNum)
	{
	case	1:
		return 0;
	case	2:
		return 1;
	case	3:
		return 2;
	case	4:
		return 3;
	case	9:
		return 4;
	case	10:
		return 5;
	case	11:
		return 6;
	case	12:
		return 7;
	case	13:
		return 9;
	case	14:
		return 8;
	case	15:
		return 10;
	default:
		return 100;
	}
}

int CLib::GetComboToStartNum(int nSequenceNum)
{

	switch (nSequenceNum)
	{
	case	0:
		return 1;
	case	1:
		return 2;
	case	2:
		return 3;
	case	3:
		return 4;
	case	4:
		return 5;
	case	5:
		return 6;
	case	6:
		return 8;
	case	7:
		return 9;
	case	8:
		return 10;
	default:
		return 0;
	}
}

int CLib::GetComboToEndNum(int nSequenceNum)
{

	switch (nSequenceNum)
	{
	case	0:
		return 1;
	case	1:
		return 2;
	case	2:
		return 3;
	case	3:
		return 4;
	case	4:
		return 9;
	case	5:
		return 10;
	case	6:
		return 11;
	case	7:
		return 12;
	case	8:
		return 14;
	case	9:
		return 13;
	case	10:
		return 15;
	default:
		return 0;
	}
}

int CLib::GetLinearTurnNo(int nSequenceNum)
{

	switch (nSequenceNum)
	{
	case	0:
		return 0;
	case	1:
		return 1;
	case	2:
		return 2;
	default:
		return 0;
	}
}

int CLib::GetLinearStationNum(int nSequenceNum)
{
	int nStationNum = -1;

	switch ( nSequenceNum )
	{
	case	0:
		nStationNum = ECS_STO_POS_1; // 8
		break;
	case	1:
		nStationNum = ECS_STO_POS_2; // 9
		break;
	case	2:
		nStationNum = ECS_STO_POS_3; // 10
		break;
	}
	return nStationNum;
}

int CLib::GetLinearStoStnNumPerCvPlc(int nPlcNum, int nSequenceNum)
{
	int nStationNum = -1;

	switch ( nPlcNum )
	{
	case	CV_1_PLC:
		switch ( nSequenceNum )
		{
		case	0:
			nStationNum = IMS_ECS_STO_STATION_100;
			break;
		case	1:
			nStationNum = IMS_ECS_STO_STATION_101;
			break;
		}
		break;
	case	CV_2_PLC:
		break;
	case	CV_3_PLC:
		switch ( nSequenceNum )
		{
		case	0:
			nStationNum = IMS_ECS_RET_STATION_201;
			break;
		case	1:
			nStationNum = IMS_ECS_RET_STATION_202;
			break;
		case	2:
			nStationNum = IMS_ECS_RET_STATION_203;
			break;
		}
		break;
	}

	return nStationNum;
}

int CLib::GetLinearRetStnNumPerCvPlc(int nPlcNum, int nSequenceNum)
{
	int nStationNum = -1;

	switch ( nPlcNum )
	{
	case	CV_1_PLC:
		nStationNum = IMS_ECS_RET_STATION_200;
		break;
	case	CV_2_PLC:
		break;
	}

	return nStationNum;
}

int CLib::GetTrackByStationNum(int nStationNum)
{
	int nTrackNum = 0;

	switch ( nStationNum )
	{
	case	IMS_ECS_STO_STATION_100:
		//nTrackNum = 8;
		nTrackNum = 9;
		break;
	case	IMS_ECS_STO_STATION_101:
		nTrackNum = 71;
		break;
	case	IMS_ECS_RET_STATION_200:
		nTrackNum = 71;
		break;
	case	IMS_ECS_RET_STATION_201:
		nTrackNum = 402;
		break;
	case	IMS_ECS_RET_STATION_202:
		nTrackNum = 502;
		break;
	case	IMS_ECS_RET_STATION_203:
		nTrackNum = 602;
		break;
	}

	return (nTrackNum - 1);
}

int CLib::GetTrackByBcrStationNum(int nStationNum)
{
	int nTrackNum = 0;

	switch ( nStationNum )
	{
	case	0:
		nTrackNum = 43;
		break;
	case	1:
		nTrackNum = 51;
		break;
	case	2:
		nTrackNum = 85;
		break;
	case	3:
		nTrackNum = 119;
		break;
	case	4:
		nTrackNum = 59;
		break;
	case	5:
		nTrackNum = 93;
		break;
	case	6:
		nTrackNum = 84;
		break;
	case	7:
		nTrackNum = 118;
		break;
	}

	return (nTrackNum - 1);
}

int CLib::GetTrackByChkNum(int nStationNum)
{
	int nTrackNum = 0;

	switch ( nStationNum )
	{
	case	0:
		nTrackNum = 204;
		break;
	case	1:
		nTrackNum = 210;
		break;
	case	2:
		nTrackNum = 219;
		break;
	case	3:
		nTrackNum = 234;
		break;
	}

	return (nTrackNum - 1);
}

BOOL CLib::IsSet(BYTE Byte, int nPos)
{
    BYTE   BitFormat;

    BitFormat = (BYTE)Power(2, nPos);
    return ((Byte & BitFormat) == BitFormat) ? TRUE : FALSE;
}

BOOL CLib::IsSet(WORD Word, int nPos)
{
    WORD   BitFormat;

    BitFormat = (WORD)Power(2, nPos);
    return ((Word & BitFormat) == BitFormat) ? TRUE : FALSE;
}

int CLib::Power(int x, int y)
{
    int     i, z = x;

    if (y == 0) return 1;

    for (i = 0; i < y - 1; i++) z *= x;

    return z;
}

int CLib::HexToInt(BYTE bHex)
{
	char szBuff[10];

	sprintf(szBuff, "%2x", bHex);
	return atoi(szBuff);
}

void CLib::ConvertAscToHex(char* pOrg, char* pDest)
{
	sprintf(pDest, "Rx:");
	for (int i = 0; i < MAX_FRAME_LEN; i++)
	{
		if (pOrg[i] == NULL) break;
		sprintf(pDest + 3 + i * 3, " %.2x", pOrg[i]);
	}
}

//
//	Number Limit  -  1000000000 이하 Double Value
//
BOOL CLib::ConvertFloatStrToCustom(CString strFloat, char *pDest, int nIntLen, int nPrecision)
{
	char	Format[16], DecPoint[32];

	int		nCount = 0;
	BOOL	bFound = FALSE;

	if(strFloat.IsEmpty())
	{
		sprintf(Format, "%%0%dd", nIntLen + nPrecision);
		sprintf(pDest, Format, 0);
		return TRUE;
	}

	for ( int i=0; i < strFloat.GetLength(); i++ ) {
		if (strFloat[i] == '.')	{
			bFound = TRUE;	nCount = i+1;
			break;
		}
	}

	if ( nCount - 1 > nIntLen )	return FALSE;

	if (bFound) {
		int nFrontVal = atoi(strFloat.Mid(0, nCount));
		int nRange = strFloat.GetLength() - nCount;
		if (nRange > nPrecision)	nRange = nPrecision;

		sprintf(Format, "%%0%dd%%s", nIntLen);

		int rd = sprintf(DecPoint, "%s", strFloat.Mid(nCount, nRange));
		if (rd < nPrecision) {
			for ( i = rd; i < nPrecision; i++)
				DecPoint[i] = '0';
			DecPoint[i]=0;
		}
		sprintf(pDest, Format, nFrontVal, DecPoint);
	}
	else {
		if ( strFloat.GetLength() > nIntLen )	return FALSE;
		int nFrontVal = atoi(strFloat.Mid(0, strFloat.GetLength()));
		sprintf(Format, "%%0%dd%%0%dd", nIntLen, nPrecision);
		sprintf(pDest, Format, nFrontVal, 0);
	}

	return TRUE;
}

int	CLib::ConvertHexStr2HexValue(char *strHex, int nLen)
{
	char	byCh=0;
	int		nHexVal=0, nVal;

	for(int i=0; i<nLen; i++)
	{
		byCh = strHex[i];
		if(byCh == 0x20)	continue;
		if(byCh >= 0x30 && byCh <= 0x39)
		{
			nVal = byCh - 0x30;
			nHexVal += (Power(16, (nLen - i - 1)) * nVal);
			continue;
		}
		else if(byCh >= 0x41 && byCh <= 0x46)
		{
			nVal = byCh - 0x37;
			nHexVal += (Power(16, (nLen - i - 1)) * nVal);
			continue;
		}
		else if(byCh >= 0x61 && byCh <= 0x66)
		{
			nVal = byCh - 0x57;
			nHexVal += (Power(16, (nLen - i - 1)) * nVal);
			continue;
		}
		else
		{
			nHexVal=0;
			break;
		}
	}
	return nHexVal;
}

BYTE CLib::HexStrToBYTE(BYTE *bySrc)
{
	BYTE byDest = 0;
	for(int i = 0; i < 2; i++)
	{
		if( bySrc[i] >= '0' && bySrc[i] <= '9')
			byDest |= bySrc[i] - '0';
		else
			byDest |= bySrc[i] - 'A' + 10;
		if(i == 0)		byDest <<= 4;
	}

	return byDest;
}

WORD CLib::HexStrToWORD(BYTE *bySrc)
{
	WORD wDest = 0;
	for (int i=0; i<4; i++)
	{
		if (bySrc[i] >= '0' && bySrc[i] <= '9')
			wDest |= bySrc[i] - '0';
		else
			wDest |= bySrc[i] - 'A' + 10;
		if(i!=3) wDest <<= 4;
	}

	return wDest;
}

int CLib::GetStoStnCntPerCvPlc(int nPlcNum)
{
	switch ( nPlcNum )
	{
	case	CV_1_PLC:
		return ECS_STO_STN_CNT;
	case	CV_2_PLC:
		return 1;
	default:
		return 1;
	}
}

int CLib::GetRetStnCntPerCvPlc(int nPlcNum)
{
	switch ( nPlcNum )
	{
	case	CV_1_PLC:
		return ECS_RET_STN_CNT;
	case	CV_2_PLC:
		return 1;
	default:
		return 1;
	}
}

int CLib::GetRetChkCntPerCvPlc(int nPlcNum)
{
	switch ( nPlcNum )
	{
	case	CV_2_PLC:
		return ECS_RET_CHK_CNT;
	default:
		return 1;
	}
}

int CLib::GetScCntPerCvPlc(int nPlcNum)
{
	switch ( nPlcNum )
	{
	case	CV_1_PLC:
		return SC_1_CNT;
	case	CV_2_PLC:
		return SC_1_CNT;
	case	CV_3_PLC:
		return SC_1_CNT;
	default:
		return 1;
	}
}

int CLib::GetOpBoxCntPerCvPlc(int nPlcNum)
{
	switch ( nPlcNum )
	{
	case	CV_1_PLC:
		return OPBOX_1_CNT;
	case	CV_2_PLC:
		return OPBOX_2_CNT;
	case	CV_3_PLC:
		return OPBOX_3_CNT;
	case	CV_4_PLC:
		return OPBOX_4_CNT;
	case	CV_5_PLC:
		return OPBOX_5_CNT;
	case	CV_6_PLC:
		return OPBOX_6_CNT;
	default:
		return 1;
	}
}

int CLib::GetStoHSCntPerCvPlc(int nPlcNum)
{
	switch ( nPlcNum )
	{
	case	CV_1_PLC:
		return STO_HS_1_CNT;
	case	CV_2_PLC:
		return STO_HS_2_CNT;
	default:
		return 1;
	}
}

int CLib::GetRetHSCntPerCvPlc(int nPlcNum)
{
	switch ( nPlcNum )
	{
	case	CV_1_PLC:
		return RET_HS_1_CNT;
	case	CV_2_PLC:
		return RET_HS_2_CNT;
	default:
		return 1;
	}
}

CString CLib::ConvertJobTypeToString(int nType)
{
	switch (nType)
	{
	case	JOB_TYPE_ALL:
		return CString("전체");
	case	JOB_TYPE_UNIT_STO:
		return CString("UNIT 입고");
	case	JOB_TYPE_UNIT_RET:
		return CString("UNIT 출고");
	case    JOB_TYPE_STN_TO_STN:
		return CString("생산 이동");
	case    JOB_TYPE_MANUAL_STN_TO_STN:
		return CString("수동 이동");
	case	JOB_TYPE_MANUAL_STO:
		return CString("반자동 입고");
	case	JOB_TYPE_MANUAL_RET:
	case	JOB_TYPE_RACK_TO_RACK:
		return CString("반자동 출고");	
	default:
		CString strTemp;
		strTemp.Format("DEF(%d)", nType);
		return strTemp;
	}

}

int CLib::ConvertJobTypeToCustom(int nType)
{
/*
	switch (nType)
	{
	case	JOB_TYPE_UNIT_STO:
		return SSE_JOB_TYPE_NORMAL_STO;
	case	JOB_TYPE_UNIT_RET:
		return SSE_JOB_TYPE_NORMAL_RET;
	case	JOB_TYPE_PICK_REPLENISH:
		return SSE_JOB_TYPE_PICKING_RET;
	case	JOB_TYPE_MANUAL_STO:
		return SSE_JOB_TYPE_MANUAL_STO;
	case	JOB_TYPE_MANUAL_RET:
		return SSE_JOB_TYPE_MANUAL_RET;
	default:
		return nType;
	}
*/
	return	nType;
}

int CLib::ConvertCustomToJobType(int nType)
{
/*
	switch (nType)
	{
	case	0:
		return -1;
	case	SSE_JOB_TYPE_NORMAL_STO:
		return JOB_TYPE_UNIT_STO;
	case	SSE_JOB_TYPE_NORMAL_RET:
		return JOB_TYPE_UNIT_RET;
	case	SSE_JOB_TYPE_PICKING_RET:
		return JOB_TYPE_PICK_REPLENISH;
	case	SSE_JOB_TYPE_MANUAL_STO:
		return JOB_TYPE_MANUAL_STO;
	case	SSE_JOB_TYPE_MANUAL_RET:
		return JOB_TYPE_MANUAL_RET;
	default:
		return nType;
	}
*/
	return nType;
}

int CLib::ConvertJobTypeToPattern(int nJobType)
{
	switch (nJobType)
	{
	case	JOB_TYPE_UNIT_STO:
	case	JOB_TYPE_MANUAL_STO:
		return JOB_PATTERN_STO;
	case	JOB_TYPE_UNIT_RET:
	case	JOB_TYPE_MANUAL_RET:
	case	JOB_TYPE_RACK_TO_RACK:
		return JOB_PATTERN_RET;
	case    JOB_TYPE_STN_TO_STN:
	case    JOB_TYPE_MANUAL_STN_TO_STN:
		return JOB_PATTERN_MOVE;
	default:
		return -1;
	}
}

int CLib::ConvertJobTypeToPattern2(int nJobType)
{
	switch (nJobType)
	{
	case	JOB_TYPE_UNIT_STO:
	case	JOB_TYPE_MANUAL_STO:
		return STO_JOB;
	case	JOB_TYPE_UNIT_RET:
		return RET_JOB;
	case	JOB_TYPE_MANUAL_RET:
		return SRET_JOB;
	default:
		return -1;
	}
}

BOOL CLib::IsValidLocation(CString strLocation)
{
	if (strLocation.IsEmpty())	return FALSE;

	int nBank = atoi(strLocation.Mid(0, 2));
	int nBay = atoi(strLocation.Mid(2, 3));
	int nLevel = atoi(strLocation.Mid(5, 2));

	if ( nBank > BANK_CNT || 
		 nBay > BAY_1_CNT ||
		 nLevel > LEVEL_1_CNT ) 
		return FALSE;

	return TRUE;
}

int CLib::GetStackerNum(CString strLocation)
{
	return (atoi(strLocation.Mid(0, 2)) + 1) / 2 - 1;
}


int CLib::ExtractInt(BYTE * pbFrame, int nLen)
{
	char szTemp[5];
	strncpy(szTemp, (char *)pbFrame, nLen);
	
	return atoi(szTemp);
}

CString CLib::ExtractString(BYTE * pbFrame, int nLen)
{
	CString strTemp;
	strTemp.Format("%nLen*s", pbFrame);
	
	return strTemp;
}

BOOL CLib::IsValidStartPos(BYTE bStartPos, int nScNum)
{
	if ( nScNum < SC_1_CNT )
	{
		switch (bStartPos)
		{
		case	ECS_POS_HS_1:
		case	ECS_POS_HS_2:
		case	ECS_POS_HS_3:
		case	ECS_POS_HS_4:
		case	ECS_STO_POS_1:
		case	ECS_STO_POS_2:
		case	ECS_STO_POS_3:		return TRUE;
		default:					return FALSE;
		}
	}

	return FALSE;
}

BOOL CLib::IsValidDestPos(BYTE bDestPos, int nScNum)
{
	if ( nScNum < SC_1_CNT )
	{
		switch (bDestPos)
		{
		case	ECS_POS_HS_1:
		case	ECS_POS_HS_2:
		case	ECS_POS_HS_3:
		case	ECS_POS_HS_4:
		case	ECS_RET_POS_1:
		case	ECS_RET_POS_2:		return TRUE;
		default:					return FALSE;
		}
	}

	return FALSE;
}

CString CLib::ConvertLocationToCustom(CString strLocation)
{
	if (strLocation.IsEmpty())	return CString(strLocation);

	CString strTemp = strLocation.Mid(0, 2);
	strTemp += "-";
	strTemp += strLocation.Mid(2, 3);
	strTemp += "-";
	strTemp += strLocation.Mid(5, 2);
	return	strTemp;
}

int CLib::GetPlcNumByTrack(int nTrackNum)
{
	if (nTrackNum < CV_1_TRACK_CNT)
		return CV_1_PLC;
	else if (nTrackNum < CV_3_TRACK_CNT+CV_3_START_TRACK)
		return CV_3_PLC;
	else if (nTrackNum < CV_4_TRACK_CNT+CV_4_START_TRACK)
		return CV_4_PLC;
	else if (nTrackNum < CV_5_TRACK_CNT+CV_5_START_TRACK)
		return CV_5_PLC;
	else if (nTrackNum < CV_6_TRACK_CNT+CV_6_START_TRACK)
		return CV_6_PLC;
	else if (nTrackNum < CV_7_TRACK_CNT+CV_7_START_TRACK)
		return CV_7_PLC;
	else if (nTrackNum < CV_2_TRACK_CNT+CV_2_START_TRACK)
		return CV_2_PLC;
	else if (nTrackNum < CV_8_TRACK_CNT+CV_8_START_TRACK)
		return CV_8_PLC;
	else if (nTrackNum < CV_9_TRACK_CNT+CV_9_START_TRACK)
		return CV_9_PLC;

	return 0;
}


CString CLib::ConvertReasonToString(int nType)
{
	switch (nType)
	{
	case	RECEIVE_OK:
		return "정상수신";
	case	MSG_NO_STX:
		return "NO STX";
	case	MSG_NO_ETX:
		return "NO ETX";
	case	MSG_LUGG_NO_DUPLICATED:
		return "Luggage 번호 중복";
	case	MSG_NO_EXIST_JOB:
		return "NO Exist Job";
	case	MSG_ECS_BUFFER_FULL:
		return "Buffer Full";
	case	MSG_INVALID_HEADER_LENG:
		return "Invalid Header Length";
	case	MSG_INVALID_MSG_LENG:
		return "Invalid Msg Length";
	case	MSG_INVALID_LOC:
		return "Invalid Location";
	case	MSG_INVALID_STN_NO:
		return "Invalid Stn. No";
	case	MSG_INVALID_LUGG_NO:
		return "Invalid Luggage No";
	case	MSG_UNKNOWN_JOB_TYPE:
		return "Unknown JobType";
	case	MSG_INHIBITED_LOC:
		return "Inhibited Location";
	case	MSG_INVALID_MAILBOX_NAME:
		return "Invalid MailBox Name";
	case	MSG_ALREADY_INVOKED_JOB:
		return "Already Invoked Job";
	case	MSG_INVALID_CONTENT:
		return "Invalid Contents";
	case	MSG_UNKNOWN_MSG_TYPE:
		return "Unknown Msg Type";
	case	MSG_IMPROPER_HANDSHAKE:
		return "Improper Handshake";
	case	MSG_NO_RESPONSE:
		return "No Response from IMS";
	case	MSG_INTERNAL_ERROR:
		return "Internal Error";
	case	MSG_SOCKET_ERROR:
		return "Socket Error";
	default:
		CString strTemp;
		strTemp.Format("Unknown Reason(%d)", nType);
		return strTemp;
	}
}

BOOL CLib::IsValidLuggNum(int nLuggNum)
{
	return ( nLuggNum > 0 && nLuggNum < 10000 ) ? TRUE : FALSE;
}

BOOL CLib::IsValidCustomJobType(int nJobType)
{
	switch (nJobType)
	{
	case	JOB_TYPE_UNIT_STO:
	case	JOB_TYPE_UNIT_RET:
//	case	JOB_TYPE_PICK_REPLENISH:
//	case	JOB_TYPE_RACK_TO_RACK:
//	case	JOB_TYPE_AISLE_TO_AISLE:
//	case	JOB_TYPE_SITE_TO_SITE:
		return TRUE;
	default:
		return FALSE;
	}
}

int CLib::ConvertCustomToPosition(int nPosition)
{
	switch ( nPosition )
	{
	case	ECS_POS_HS_1:
		return CV_POS_HS_1;
	case	ECS_POS_HS_2:
		return CV_POS_HS_2;
	case	ECS_POS_HS_3:
		return CV_POS_HS_3;
	case	ECS_POS_HS_4:
		return CV_POS_HS_4;
	case	ECS_POS_HS_5:
		return CV_POS_HS_5;
	case	ECS_POS_HS_6:
		return CV_POS_HS_6;
	case IMS_ECS_RET_STATION_200:
		return CV_RET_STATION_2;

	default:
		return 0;
	}

}

int CLib::ConvertPositionToCustom(int nType, int nPosition)
{
	if (nType == 1)
	{
		switch ( nPosition )
		{
		case	CNV_POS_HS_1:
		case	CNV_POS_HS_2:
		case	CNV_POS_HS_3:
		case	CNV_POS_HS_4:
			return nPosition;
		case	CNV_STO_POS_1:
			return ECS_STO_POS_1;
		case	CNV_STO_POS_2:
			return ECS_STO_POS_2;
		case	CNV_STO_POS_3:
			return ECS_STO_POS_3;
		default:
			return 0;
		}
	}
	else
		switch ( nPosition )
		{
		case	CNV_POS_HS_1:
		case	CNV_POS_HS_2:
		case	CNV_POS_HS_3:
		case	CNV_POS_HS_4:
			return nPosition;
		case	CNV_RET_POS_1:
			return ECS_RET_POS_1;
		case	CNV_RET_POS_2:
			return ECS_RET_POS_2;
		default:
			return 0;
		}
	{
	}
}

CString CLib::BatchStatusToString(BYTE bMode)
{
	switch (bMode)
	{
	case	0:
		return "NONE";
	case	1:
		return "S/C작업중";
	case	2:
		return "대기C/V도착";
	case	3:
		return "대기C/V출발";
	case	4:
		return "4,3호기 사이";
	case	5:
		return "3,2호기 사이";
	case	6:
		return "2,1호기 사이";
	case	7:
		return "Turn C/V";
	default:
		CString strTemp;
		strTemp.Format("Unknown (%c)", bMode);
		return strTemp;
	}
}

int CLib::GetBank(CString strLocation)
{
	return (atoi(strLocation.Mid(0, 2)));
}

int CLib::GetBay(CString strLocation)
{
	return atoi(strLocation.Mid(2, 3));
}

int CLib::GetLevel(CString strLocation)
{
	return atoi(strLocation.Mid(5, 2));
}

CString CLib::ConvertStackerMode(unsigned char ucMode)
{
	switch (ucMode)
	{
	case	SC_MODE_REMOTE:
		return "자동";
	case	SC_MODE_ONLINE:
		return "수동";
	case	SC_MODE_OFFLINE:
		return "OFF";
	default:
		CString strTemp;
		strTemp.Format("Unknown (%c)", ucMode);
		return strTemp;
	}
}

CString CLib::StackerJobTypeToString(BYTE bJobType)
{
	switch (bJobType)
	{
	case	SC_JOB_TYPE_STORE:
		return "입고";
	case	SC_JOB_TYPE_RETRIEVE:
		return "출고";
	case	SC_JOB_TYPE_RACK_TO_RACK:
		return "RACK TO RACK";
	case	SC_JOB_TYPE_CALL_TO_HOME:
		return "홈 복귀";
	case	SC_JOB_TYPE_MANUAL:
		return "수동지시 작업";
	default:
		CString strTemp;
		strTemp.Format("Unknown (%c)", bJobType);
		return strTemp;
	}
}

CString CLib::StackerModeToString(BYTE bMode)
{
	switch (bMode)
	{
	case	SC_MODE_REMOTE:
		return "자동";
	case	SC_MODE_ONLINE:
		return "수동";
	case	SC_MODE_OFFLINE:
		return "OFF";
	default:
		CString strTemp;
		strTemp.Format("Unknown (%c)", bMode);
		return strTemp;
	}
}

CString CLib::StackerRcModeToString(unsigned char ucMode)
{
	switch (ucMode)
	{
	case	SC_MODE_REMOTE:
		return "자동";
	case	SC_MODE_ONLINE:
		return "수동";
	case	SC_MODE_OFFLINE:
		return "OFF";
	}

	CString strTemp;
	strTemp.Format("이상 (%c)", ucMode);
	return strTemp;
}

CString CLib::StackerRcModeToString_New(unsigned char ucMode)
{
	switch (ucMode)
	{
	case	SC_MODE_REMOTE_NEW:
		return "수동";
	case	SC_MODE_ONLINE_NEW:
		return "자동";
	case	SC_MODE_OFFLINE:
		return "OFF";
	}
	
	CString strTemp;
	strTemp.Format("이상 (%c)", ucMode);
	return strTemp;
}

CString CLib::StackerScModeToString(unsigned char ucMode)
{
	switch (ucMode)
	{
	case	SC_MODE_AUTO:
		return "자동";
	case	SC_MODE_MANUAL_NEW:
	case	SC_MODE_MANUAL:
		return "수동";
	}

	CString strTemp;
	strTemp.Format("이상 (%c)", ucMode);
	return strTemp;
}

CString CLib::StackerActiveToString(unsigned char ucActive)
{
	switch (ucActive)
	{
	case	SC_ACTIVE:
		return "ACTIVE";
	case	SC_STOP:
		return "STOP";
	}

	CString strTemp;
	strTemp.Format("이상 (%c)", ucActive);
	return strTemp;
}

CString CLib::StackerStatusToString(WORD bStatus)
{
	switch (bStatus)
	{
	case	SC_STA_WAIT:
		return "대기(Wait)";
	case	SC_STA_IDLE:
		return "대기(Idle)";
	case	SC_STA_MOVE:
		return "이동";
	case	SC_STA_ERROR:
		return "에러";
	default:
		CString strTemp;
		strTemp.Format("Unknown (%d)", bStatus);
		return strTemp;
	}
}

#ifdef OPT_SC_SHINHUNG_USE
CString CLib::StackerPhaseToString(BYTE ucPhase)
{
	switch (ucPhase)
	{
	case	1:
		return "홈 이동 중.. (Simple Moving)";
	case	2:
		return "입고 H/S로 이동 중.. (Simple Moving)";
	case	3:
		return "출고 H/S로 이동 중.. (Simple Moving)";
	case	4:
		return "랙으로 이동 중.. (Simple Moving)";
	case	5:
		return "Rack에서 크레인으로 적재 중.. (Loading)";
	case	6:
		return "크레인에서 Rack으로 이재 중.. (Unloading)";
	case	7:
		return "입고 H/S에서 크레인으로 적재 중.. (Loading)";
	case	8:
		return "크레인에서 출고 H/S로 이재 중.. (UnLoading)";
	default:
		CString strTemp;
		strTemp.Format("Unknown (%x)", ucPhase);
		return strTemp;
	}
}
#endif

CString CLib::GetStackerErrorInfo(int nErrorCode)
{
	switch ( nErrorCode )
	{
	// SFA - MELSEC INVERTER TYPE 크레인
	case	0:		return "정상";
	case	1:		return "주행비상정지";
	case	2:		return "승강비상정지";
	case	3:		return "강제비상정지(기상반 버튼 눌림)";
	case	4:		return "승강체인이상";
	case	5:		return "지상반비상정지(DOOR OPEN)";

	case	11:		return "주행카운트 한계이상(전진시)";
	case	12:		return "주행카운트 한계이상(후진시)";
	case	13:		return "주행이동 목적방향에러";

	case	14:		return "주행1차완료후 정위치 이상";
	case	15:		return "주행2차완료후 정위치 이상";
	case	16:		return "포킹중 주행 정위치 이상";

	case	18:		return "주행 감속후 주행오버타임";
	case	19:		return "주행위치 보정실패";
	case	20:		return "수동포킹시 주행 정위치 이상";
	case	21:		return "주행위치보정 카운터오버";
	case	22:		return "주행최초구동 이상";
	case	23:		return "주행고속컷위치 이상";
	case	24:		return "주행엔코더 한계 이상";
	case	30:		return "승강카운트이상";
	case	31:		return "승강카운트이상 센서이상(상승시)";
	case	32:		return "승강카운트이상 센서이상(하강시)";

	case	33:		return "승강이동 목적방향에러";
	case	34:		return "승강1차완료후 정위치 이상";
	case	35:		return "승강2차완료후 정위치 이상";

	case	36:		return "승강 정위치 이상";

	case	38:		return "승강감속후 승강 오버타임";
	case	39:		return "승강위치보정실패";
	case	40:		return "수동포킹시 승강 정위치 이상";

	case	41:		return "승강 위치보정 카운트오버";
	case	42:		return "승강최초구동 이상";

	case	43:		return "포킹UP/DN완료전 승강정위치이상";
	case	44:		return "포킹UP/DN완료후 승강정위치이상";
	case	45:		return "포킹UP/DN 오버타임";
	case	46:		return "포킹UP/DN시 승강ZONE 이상";
	case	47:		return "포킹UP/DN후 승강ZONE 이상";

	case	50:		return "SC 최초기동시 포크#1 이상";
	case	51:		return "SC 최초기동시 포크#2 이상";
	case	52:		return "화물 오버사이즈 에러";
	case	53:		return "화물 붕괴에러";
	case	54:		return "이중입고 포크#1";
	case	55:		return "이중입고 포크#2";
	case	56:		return "입고장애(더블)";
	case	57:		return "출고장애(더블)";

	case	58:		return "공출고 에러 포크#1";
	case	59:		return "공출고 에러 포크#2";
	case	60:		return "출고실패 포크#1(작업대)";
	case	61:		return "출고실패 포크#2(작업대)";
	case	62:		return "입고실패 포크#1(작업대)";
	case	63:		return "입고실패 포크#2(작업대)";
	case	64:		return "입고실패 포크#1(랙)";
	case	65:		return "입고실패 포크#2(랙)";

	case	70:		return "SC이동시 포크센터이상";
	case	71:		return "ACTIVE최초 포크센터이상";
	case	72:		return "포크말단 화물 돌출";
	case    74:		return "포크센터이상(학습시)";
	case	75:		return "포크센터이상(홈복귀시)";
	case	76:		return "포크센터이상(주행이동)";
	case	77:		return "포크센터이상(승강이동)";
	case	78:		return "수동주행시 포크센터이상";
	case	79:		return "수동승강시 포크센터이상";

	case	80:		return "포크감속후 오버타임";
	case	81:		return "포크구동 오버타임";
	case	82:		return "포크최초 구동이상";
	case	83:		return "좌측랙포스트 센서이상";
	case	84:		return "우측랙포스트 센서이상";
	case	87:		return "포크#1 홈복귀실패";
	case	88:		return "포크#2 홈복귀실패";
	case	89:		return "DRIVE ALARM(포크#1)";

	case	90:		return "DRIVE ALARM(포크#2)";
	case	91:		return "주행 모터 과부하";
	case	92:		return "승강 모터 과부하";
	case	93:		return "포크 모터 과부하";
	case	94:		return "제동저향 과열";
	case	96:		return "드라이브이상(주행)";
	case	97:		return "드라이브이상(승강)";
	case    98:		return "위치결정 유닛이상";
	case	99:		return "아나로글출력 유닛이상";

	case	101:		return "작업실행시 전체학습 미완료";
	case	102:		return "작업실행시 주행학습 미완료";
	case	103:		return "작업실행시 승강학습 미완료";
	case	104:		return "승강학습 에러";
	case	105:		return "승강학습 카운트 에러";
	case	106:		return "승강학습 엔드홈 이상";
	case	107:		return "주행학습 카운트 에러";
	case    108:		return "주행학습 에러";
	case	109:		return "주행학습 에러(좌측 랙포스트센서)";
	case	110:		return "주행학습 에러(우측 랙포스트센서)";
	case	111:		return "주행학습데이터 에러(랙포스트 보정한계 오버)";
	case	112:		return "주행학습 엔드홈 이상";
	case	113:		return "포크학습 오버타임";
	case	114:		return "작업대학습 주행 오버타임";
	case	115:		return "작업대학습 주행학습 에러";
	case	116:		return "작업대학습 승강오버(타임/카운트)";
	case    117:		return "작업대학습 승강학습 에러";
	case	118:		return "브레이크학습 이상 (주행)";
	case	119:		return "브레이크학습 이상 (승강)";
	case	120:		return "작업대학습 트러스 이상";
	case	121:		return "작업데이터 연산에러";
	case	122:		return "이동순위 연산에러";
	case    123:		return "승강출력 연산에러";
	case	124:		return "주행출력 연산에러";
	case	125:		return "목적지 연산에러(열/행/단/작업대)";
	case	126:		return "주행승강 감속거리 연산에러";
	case	127:		return "포크최대출력 연산에러";
	case	128:		return "목적지 연산에러(행보정값)";
	case    129:		return "주행감속거리,등속 연산에러";
	case	130:		return "승강감속거리, 등속 연산에러";


	case	131:	return "입고작업대 상태이상";
	case	132:	return "출고작업대 상태이상";
	case	133:	return "출고작업대 화물이상";
	case	141:	return "수신데이터 이상(포크#1)";
	case	142:	return "수신데이터 이상(포크#2)";
	case	143:	return "수신데이터 작업대 용도이상";
	case	144:	return "수신데이터 OVERWRITE";
	case	145:	return "수신데이터 재지정시 에러";
	case	146:	return "수신데이터 재지정시 재지정요구에러";
	case	147:	return "수신데이터 금지셀 지정에러";
	case	148:	return "수신데이터 지상반 모드에러";
	case	149:	return "주행위치결정 UNIT시동번호 이상";
	case	150:	return "승강위치결정 UNIT시동번호 이상";

	case	151:	return "시스템파라미터이상";
	case	152:	return "주행 파라미터이상";
	case	153:	return "승강 파라미터이상";
	case	154:	return "포크 파라미터이상";
	case	155:	return "작업대 파라미터이상";

	case	161:	return "주행엔코더 회전방향 이상";
	case	162:	return "주행엔코더 가산데이터 미달";
	case	163:	return "주행엔코더 가산데이터 오버";
	case	164:	return "주행엔코더 입력데이터 이상";
	case	166:	return "승강엔코더 회전 방향";
	case	167:	return "승강엔코더 가산데이터 미달";
	case	168:	return "승강엔코더 가산데이터 오버";
	case	169:	return "승강엔코더 입력데이터 이상";

	case	171:	return "계산기 통신두절";
	case	172:	return "계산기 유닛 이상";
	case	173:	return "통신 체크섬 에러";
	case	174:	return "통신 CASE 에러";

	case	200:	return "통신 프레임 에러";
	case	201:	return "금지셀 에러";
	case	202:	return "유효성 에러";
	case	203:	return "작업대 데이터 이상";
	case	204:	return "체크섬 에러";
	case	205:	return "통신유닛에러";
	case	206:	return "최대열행단 에러";
	case	207:	return "작업입력 에러";
	case	208:	return "SC 지/기상반 통신 두절";
	case    209:	return "지상반 OFFLINE MODE 에러";

	case	SC_ERR_CODE_COMM_ERROR:		return	"지상반 응답없슴. 통신두절";
	
	default:
		return "기타 에러[SC메뉴얼참조]";
	}
}

CString CLib::GetStackerErrorInfoQ(int nErrorCode)
{
	switch ( nErrorCode )
	{
	// SFA - MELSEC INVERTER TYPE 크레인
	case	1:		return "주행비상정지";
	case	2:		return "승강비상정지";
	case	3:		return "강제비상정지(기상반 버튼 눌림)";
	case	4:		return "승강체인이상";
	case	5:		return "지상반비상정지(DOOR OPEN)";

	case	11:		return "주행카운트 한계이상(전진시)";
	case	12:		return "주행카운트 한계이상(후진시)";
	case	13:		return "주행이동 목적방향에러";

	case	14:		return "주행1차완료후 정위치 이상";
	case	15:		return "주행2차완료후 정위치 이상";
	case	16:		return "포킹중 주행 정위치 이상";

	case	18:		return "주행 감속후 주행오버타임";
	case	19:		return "주행위치 보정실패";
	case	20:		return "수동포킹시 주행 정위치 이상";
	case	21:		return "주행위치보정 카운터오버";
	case	22:		return "주행최초구동 이상";
	case	30:		return "승강카운트이상";
	case	31:
	case	32:		return "승강카운트이상 센서이상";

	case	33:		return "승강이동 목적방향에러";
	case	34:		return "승강1차완료후 정위치 이상";
	case	35:		return "승강2차완료후 정위치 이상";

	case	36:		return "승강 정위치 이상";

	case	38:		return "승강감속후 승강 오버타임";
	case	39:		return "승강위치보정실패";
	case	40:		return "수동포킹시 승강 정위치 이상";

	case	41:		return "승강 위치보정 카운트오버";
	case	42:		return "승강최초구동 이상";

	case	43:		return "포킹UP/DN완료전 승강정위치이상";
	case	44:		return "포킹UP/DN완료후 승강정위치이상";
	case	45:		return "포킹UP/DN 오버타임";
	case	46:		return "포킹UP/DN시 승강ZONE 이상";
	case	47:		return "포킹UP/DN후 승강ZONE 이상";

	case	50:		return "SC 최초기동시 포크#1 이상";
	case	51:		return "SC 최초기동시 포크#2 이상";
	case	52:		return "화물 오버사이즈 에러";
	case	53:		return "화물 붕괴에러";
	case	54:		return "이중입고 포크#1";
	case	55:		return "이중입고 포크#1";
	case	56:		return "입고장애(더블)";
	case	57:		return "출고장애(더블)";

	case	58:		return "공출고 에러 포크#1";
	case	59:		return "공출고 에러 포크#2";
	case	60:		return "출고실패 포크#1(작업대)";
	case	61:		return "출고실패 포크#2(작업대)";
	case	62:		return "입고실패 포크#1(작업대)";
	case	63:		return "입고실패 포크#2(작업대)";
	case	64:		return "입고실패 포크#1(랙)";
	case	65:		return "입고실패 포크#2(랙)";

	case	70:		return "SC이동시 포크센터이상";
	case	71:		return "ACTIVE최초 포크센터이상";
	case	72:		return "포크말단 화물 돌출";
	case	75:		return "포크센터이상(홈복귀시)";
	case	76:		return "포크센터이상(주행이동)";
	case	77:		return "포크센터이상(승강이동)";
	case	78:		return "수동주행시 포크센터이상";
	case	79:		return "수동승강시 포크센터이상";

	case	80:		return "포크감속후 오버타임";
	case	81:		return "포크구동 오버타임";
	case	82:		return "포크최초 구동이상";
	case	83:		return "좌측랙포스트 센서이상";
	case	84:		return "우측랙포스트 센서이상";
	case	87:		return "포크#1 홈복귀실패";
	case	88:		return "포크#2 홈복귀실패";
	case	89:		return "DRIVE ALARM(포크#1)";

	case	90:		return "DRIVE ALARM(포크#2)";
	case	91:		return "주행 모터 과부하";
	case	92:		return "승강 모터 과부하";
	case	93:		return "포크 모터 과부하";
	case	94:		return "제동저향 과열";
	case	96:		return "드라이브이상(주행)";
	case	97:		return "드라이브이상(승강)";

	case	131:	return "입고작업대 상태이상";
	case	132:	return "출고작업대 상태이상";
	case	133:	return "출고작업대 화물이상";
	case	141:	return "수신데이터 이상(포크#1)";
	case	142:	return "수신데이터 이상(포크#2)";
	case	143:	return "수신데이터 작업대 용도이상";
	case	144:	return "수신데이터 OVERWRITE";
	case	145:	return "수신데이터 재지정시 에러";
	case	146:	return "수신데이터 재지정시 재지정요구에러";
	case	147:	return "수신데이터 금지셀 지정에러";
	case	148:	return "수신데이터 지상반 모드에러";
	case	149:	return "주행위치결정 UNIT시동번호 이상";
	case	150:	return "승강위치결정 UNIT시동번호 이상";

	case	151:	return "시스템파라미터이상";
	case	152:	return "주행 파라미터이상";
	case	153:	return "승강 파라미터이상";
	case	154:	return "포크 파라미터이상";
	case	155:	return "작업대 파라미터이상";

	case	161:	return "주행엔코더 회전방향 이상";
	case	162:	return "주행엔코더 가산데이터 미달";
	case	163:	return "주행엔코더 가산데이터 오버";
	case	164:	return "주행엔코더 입력데이터 이상";
	case	166:	return "승강엔코더 회전 방향";
	case	167:	return "승강엔코더 가산데이터 미달";
	case	168:	return "승강엔코더 가산데이터 오버";
	case	169:	return "승강엔코더 입력데이터 이상";

	case	171:	return "계산기 통신두절";
	case	172:	return "계산기 유닛 이상";
	case	173:	return "통신 체크섬 이레";
	case	174:	return "통신 CASE에러";

	case	200:		return "통신 프레임 에러";
	case	201:		return "금지셀 에러";
	case	202:		return "유효성 에러";
	case	203:		return "작업대 데이터 이상";
	case	204:		return "체크섬 에러";
	case	205:		return "통신유닛에러";
	case	206:		return "최대열행단 에러";
	case	207:		return "작업입력 에러";
	case	208:		return "SC 지/기상반 통신 두절";

	case	SC_ERR_CODE_COMM_ERROR:		return	"지상반 응답없슴. 통신두절";
	
	default:
		return "기타 에러[SC메뉴얼참조]";
	}
}

CString CLib::GetSystemErrMsg(int nErrNo)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
	    FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
	    NULL,
		nErrNo ? nErrNo : ::GetLastError(),
	    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
	    0,
		NULL 
	);

	CString str;
	str.Format("%s", (LPCTSTR)lpMsgBuf);
	LocalFree( lpMsgBuf );

	str.TrimRight();

	return str; 
}

BOOL CLib::IsValidHostStartPos(int bStartPos)
{
	if(bStartPos == 100 || bStartPos == 101  || bStartPos == 103)
		return TRUE;

	if(bStartPos >= 111 && bStartPos <= 128)
		return TRUE;

	return FALSE;
}

BOOL CLib::IsValidHostDestPos(int bDestPos)
{

	if (bDestPos == 200 || bDestPos == 201 || bDestPos == 202 || bDestPos == 203 || 
		bDestPos == 204 || bDestPos == 251 || bDestPos == 255 || bDestPos == 1)
		return TRUE;

	return FALSE;
}

int CLib::GetStartTrackNumPerCvPlc(int nPlcNum)
{
	int nTrackNum = 0;

	switch ( nPlcNum )
	{
	case	CV_1_PLC:	nTrackNum = CV_1_START_TRACK;	break;
	case	CV_2_PLC:	nTrackNum = CV_2_START_TRACK;	break;
	case	CV_3_PLC:	nTrackNum = CV_3_START_TRACK;	break;
	case	CV_4_PLC:	nTrackNum = CV_4_START_TRACK;	break;
	case	CV_5_PLC:	nTrackNum = CV_5_START_TRACK;	break;
	case	CV_6_PLC:	nTrackNum = CV_6_START_TRACK;	break;
	}

	return (nTrackNum);
}

int CLib::GetTrackCntPerCvPlc(int nPlcNum)
{
	switch ( nPlcNum )
	{
	case	CV_1_PLC:
		return CV_1_TRACK_CNT;
	case	CV_2_PLC:
		return CV_2_TRACK_CNT;
	case	CV_3_PLC:
		return CV_3_TRACK_CNT;
	case	CV_4_PLC:
		return CV_4_TRACK_CNT;
	case	CV_5_PLC:
		return CV_5_TRACK_CNT;
	case	CV_6_PLC:
		return CV_6_TRACK_CNT;
	default:
		return 1;
	}

}


CString CLib::GetRgvErrorCode(int nErrorCode)
{
	switch ( nErrorCode )
	{
	// SFA - MELSEC INVERTER TYPE 크레인
	case	1:		return "주행비상정지";
	case	2:      return "안전 범퍼 충돌 Error";
	case	3:		return "강제비상정지(EMG 버튼 눌림)";
	case	4:      return "Area Sensor 동작";
	case	5:		return "온라인 비상정지[ECS에서 비상정지 지시]";

	case	11:		return "주행카운트 한계이상(전진시)";
	case	12:		return "주행카운트 한계이상(후진시)";
	case	13:		return "주행이동 목적방향에러";

	case	14:		return "주행1차완료후 정위치 이상";
	case	15:		return "주행2차완료후 정위치 이상";
	case	16:		return "포킹중 주행 정위치 이상";

	case	18:		return "주행 감속후 주행오버타임";
	case	19:		return "주행위치 보정실패";

	case	21:		return "주행위치보정 카운터오버";
	case	22:		return "주행최초구동 이상";

	case	23:		return "CV 구동 에러";
	case	26:		return "CV 구동 타임 에러";

	case	50:		return "RTV 최초기동시 CV#1 하물이상";

	case	52:		return "화물 오버사이즈 에러";
	case	53:		return "화물 붕괴에러";
	case	56:		return "홈 감지 Sensor Error";

	case	70:		return "RTV 이동 시 CV 센터이상";
	case	71:		return "ACTIVE최초 CV 센터이상";

	case	74:		return "CV 센터이상(학습시)";
	case	75:		return "CV 센터이상(홈복귀시)";
	case	76:		return "CV 센터이상(주행이동)";

	case	78:		return "수동주행시 CV 센터이상";

	case	80:		return "CV감속후 오버타임";
	case	81:		return "CV구동 오버타임";
	case	82:		return "CV최초 구동이상";

	case	91:		return "주행 모터 과부하";

	case	93:		return "CV 모터 과부하";
	case	94:		return "제동저향 과열";
	case	95:		return "BREAK FUSE OFF";

	case	99:		return "아나로그출력 유닛이상";

	case	101:	return "작업실행시 전체학습 미완료";

	case	124:	return "주행출력 연산에러";
	case	125:	return "목적지 연산에러";
	case	126:	return "주행감석 감속거리 연산에러";

	case	127:	return "CV 출력 연산에러";
	case	128:	return "목적지 연산에러";
	case	129:	return "주행감속거리 등속 연산에러";

	case	151:	return "시스템파라미터이상";
	case	152:	return "주행 파라미터이상";
	case	154:	return "CV 파라미터이상";

	case	161:	return "주행엔코더 회전방향 이상";
	case	162:	return "주행엔코더 가산데이터 미달";
	case	163:	return "주행엔코더 가산데이터 오버";
	case	164:	return "주행엔코더 입력데이터 이상";

	case	RGV_ERR_CODE_COMM_ERROR:		return	"지상반 응답없슴. 통신두절";
	}

	return "기타 에러[RGV 메뉴얼참조]";

}

int CLib::GetRgvStoStartHSTrack(int nRgvNum, int nSequenceNum)
{
	int nTrackNum = 0;

	switch ( nRgvNum )
	{
	case	RGV_1_NUM:
		switch ( nSequenceNum )
		{
		case	0:	nTrackNum = 711;		break;
		case	1:	nTrackNum = 712;		break;
		case	2:	nTrackNum = 719;		break;
		case	3:	nTrackNum = 726;		break;
		case	4:	nTrackNum = 733;		break;
		case	5:	nTrackNum = 753;		break;
		case	6:	nTrackNum = 760;		break;
		case	7:	nTrackNum = 767;		break;
		case	8:	nTrackNum = 774;		break;
		case	9:	nTrackNum = 781;		break;
		case	10:	nTrackNum = 746;		break;
		}
		break;
	case	RGV_2_NUM:
		switch ( nSequenceNum )
		{
		case	0:	nTrackNum = 113;		break;
		case	1:	nTrackNum = 109;		break;
		}
		break;
	}

	return (nTrackNum - 1);
}

int CLib::GetRgvRetStartHSTrack(int nRgvNum, int nSequenceNum)
{
	int nTrackNum = 0;

	switch ( nRgvNum )
	{
	case	RGV_2_NUM:
		switch ( nSequenceNum )
		{
		case	0:	nTrackNum = 718;		break;
		case	1:	nTrackNum = 725;		break;
		case	2:	nTrackNum = 732;		break;
		case	3:	nTrackNum = 739;		break;
		case	4:	nTrackNum = 745;		break;
		case	5:	nTrackNum = 752;		break;
		case	6:	nTrackNum = 759;		break;
		case	7:	nTrackNum = 766;		break;
		case	8:	nTrackNum = 773;		break;
		case	9:	nTrackNum = 780;		break;
		case	10:	nTrackNum = 787;		break;
		case	11:	nTrackNum = 808;		break;

		}
		break;
	}

	return (nTrackNum - 1);
}

int CLib::GetRgvRetStartHSTrack2(int nRgvNum, int nSequenceNum)
{
	int nTrackNum = 0;

	switch ( nRgvNum )
	{
	case	RGV_2_NUM:
		switch ( nSequenceNum )
		{
		case	0:	nTrackNum = 808;		break;
		case	1:	nTrackNum = 787;		break;
		case	2:	nTrackNum = 780;		break;
		case	3:	nTrackNum = 773;		break;
		case	4:	nTrackNum = 766;		break;
		case	5:	nTrackNum = 759;		break;
		case	6:	nTrackNum = 752;		break;
		case	7:	nTrackNum = 745;		break;
		case	8:	nTrackNum = 739;		break;
		case	9:	nTrackNum = 732;		break;
		case	10:	nTrackNum = 725;		break;
		case	11:	nTrackNum = 718;		break;
		}
		break;
	}

	return (nTrackNum - 1);
}

int CLib::GetRgvDestHSTrack(int nRgvNum, int nSequenceNum)
{
	int nTrackNum = 0;

	switch ( nRgvNum )
	{
	case	RGV_1_NUM:
		switch ( nSequenceNum )
		{
		case	0:	nTrackNum = 782;		break;
		case	1:	nTrackNum = 775;		break;
		case	2:	nTrackNum = 768;		break;
		case	3:	nTrackNum = 761;		break;
		case	4:	nTrackNum = 754;		break;
		case	5:	nTrackNum = 747;		break;
		case	6:	nTrackNum = 740;		break;
		case	7:	nTrackNum = 734;		break;
		case	8:	nTrackNum = 727;		break;
		case	9:	nTrackNum = 720;		break;
		case	10:	nTrackNum = 713;		break;
		case	11:	nTrackNum = 711;		break;
		case	12:	nTrackNum = 702;		break;
		case	13:	nTrackNum = 712;		break;
		case	14:	nTrackNum = 719;		break;
		case	15:	nTrackNum = 726;		break;
		case	16:	nTrackNum = 733;		break;
		case	17:	nTrackNum = 746;		break;
		case	18:	nTrackNum = 753;		break;
		case	19:	nTrackNum = 760;		break;
		case	20:	nTrackNum = 767;		break;
		case	21:	nTrackNum = 774;		break;
		case	22:	nTrackNum = 781;		break;
		}
		break;
	case	RGV_2_NUM:
		switch ( nSequenceNum )
		{
		case	0:	nTrackNum = 808;	    break;
		case	1:	nTrackNum = 809;	    break;
		case	2:	nTrackNum = 718;		break;
		case	3:	nTrackNum = 725;		break;
		case	4:	nTrackNum = 732;		break;
		case	5:	nTrackNum = 739;		break;
		case	6:	nTrackNum = 745;		break;
		case	7:	nTrackNum = 752;		break;
		case	8:	nTrackNum = 759;		break;
		case	9:	nTrackNum = 766;		break;
		case	10:	nTrackNum = 773;		break;
		case	11:	nTrackNum = 780;		break;
		case	12:	nTrackNum = 787;		break;
		}
		break;
	}

	return (nTrackNum - 1);
}


int CLib::GetRgvStoDestHSTrack(int nRgvNum, int nLineNum)
{
	int nTrackNum = 0;


	switch ( nRgvNum )
	{
	case	RGV_1_NUM:
		switch ( nLineNum )
		{
		case	1:	nTrackNum = 711;		break;
		case	2:	nTrackNum = 712;		break;
		case	3:	nTrackNum = 719;		break;
		case	4:	nTrackNum = 726;		break;
		case	5:	nTrackNum = 733;		break;
		case	6:	nTrackNum = 753;		break;
		case	7:	nTrackNum = 760;		break;
		case	8:	nTrackNum = 767;		break;
		case	9:	nTrackNum = 774;		break;
		case	10:	nTrackNum = 781;		break;
		//case	11:	nTrackNum = 746;		break;
		}
		break;
	case	RGV_2_NUM:
		nTrackNum = 1;		break;
	}

	return nTrackNum - 1;
}

int CLib::GetRgvRetDestHSTrack(int nLineNum, int nRgvNum)
{
	int nTrackNum = 0;

	switch ( nRgvNum )
	{
	case	RGV_1_NUM:
		switch ( nLineNum )
		{
		case	1:		nTrackNum = 713;	break;
		case	2:		nTrackNum = 720;	break;
		case	3:		nTrackNum = 727;	break;
		case	4:		nTrackNum = 734;	break;
		case	5:		nTrackNum = 740;	break;
		case	6:		nTrackNum = 747;	break;
		case	7:		nTrackNum = 754;	break;
		case	8:		nTrackNum = 761;	break;
		case	9:		nTrackNum = 768;	break;
		case	10:		nTrackNum = 775;	break;

		}
		break;
	}

	return nTrackNum - 1;
}

int CLib::GetRgvStartHSTrack(int nRgvNum, int nSequenceNum)
{
	int nTrackNum = 0;

	switch ( nRgvNum )
	{
	case	RGV_1_NUM:
		switch ( nSequenceNum )
		{
		case	0:	nTrackNum = 782;		break;
		case	1:	nTrackNum = 775;		break;
		case	2:	nTrackNum = 768;		break;
		case	3:	nTrackNum = 761;		break;
		case	4:	nTrackNum = 754;		break;
		case	5:	nTrackNum = 747;		break;
		case	6:	nTrackNum = 740;		break;
		case	7:	nTrackNum = 734;		break;
		case	8:	nTrackNum = 727;		break;
		case	9:	nTrackNum = 720;		break;
		case	10:	nTrackNum = 713;		break;
		case	11:	nTrackNum = 711;		break;
		case	12:	nTrackNum = 702;		break;
		case	13:	nTrackNum = 712;		break;
		case	14:	nTrackNum = 719;		break;
		case	15:	nTrackNum = 726;		break;
		case	16:	nTrackNum = 733;		break;
		case	17:	nTrackNum = 746;		break;
		case	18:	nTrackNum = 753;		break;
		case	19:	nTrackNum = 760;		break;
		case	20:	nTrackNum = 767;		break;
		case	21:	nTrackNum = 774;		break;
		case	22:	nTrackNum = 781;		break;
		}
		break;
	case	RGV_2_NUM:
		switch ( nSequenceNum )
		{
		case	0:	nTrackNum = 808;	    break;
		case	1:	nTrackNum = 809;	    break;
		case	2:	nTrackNum = 718;		break;
		case	3:	nTrackNum = 725;		break;
		case	4:	nTrackNum = 732;		break;
		case	5:	nTrackNum = 739;		break;
		case	6:	nTrackNum = 745;		break;
		case	7:	nTrackNum = 752;		break;
		case	8:	nTrackNum = 759;		break;
		case	9:	nTrackNum = 766;		break;
		case	10:	nTrackNum = 773;		break;
		case	11:	nTrackNum = 780;		break;
		case	12:	nTrackNum = 787;		break;
		}
		break;
	}

	return (nTrackNum - 1);
}

//^^^^^^^^^^^^^ RGV 출발H/S 갯수 ^^^^^^^^^^^^^^//
int CLib::GetStartStnCntPerRgv(int nRgvNo)
{
	switch ( nRgvNo )
	{
	case	RGV_1_NUM:		return RGV_LOADING_HS_1_CNT;
	case	RGV_2_NUM:		return RGV_LOADING_HS_2_CNT;
	}

	return 0;
}

int CLib::GetDestStnCntPerRgv(int nRgvNo)
{
	switch ( nRgvNo )
	{
	case	RGV_1_NUM:		return RGV_UNLOADING_HS_1_CNT;
	case	RGV_2_NUM:		return RGV_UNLOADING_HS_2_CNT;
	}

	return 0;
}

int CLib::GetStoStnCntPerRgv(int nRgvNo)
{
	switch ( nRgvNo )
	{
	case	RGV_1_NUM:		return RGV_STO_LOADING_HS_1_CNT;
	case	RGV_2_NUM:		return RGV_STO_LOADING_HS_2_CNT;
	}

	return 0;
}

int CLib::GetRetStnCntPerRgv(int nRgvNo)
{
	switch ( nRgvNo )
	{
	case	RGV_1_NUM:		return RGV_RET_LOADING_HS_1_CNT;
	case	RGV_2_NUM:		return RGV_RET_LOADING_HS_2_CNT;
	}

	return 0;
}

CString CLib::GetCvErrorCode(int nErrorCode)
{
	switch ( nErrorCode )
	{
	case	0:				return "";
	case	1:				return "비상정지(Main)";
	case	2:				return "비상정지(해당OP BOX)";
	case	3:				return "비상정지(Remote:Ecs)";
	case	4:				return "정위치 Error";
	case	5:				return "화물붕괴 Error(Lift)";
	case	6:				return "Oversize Error(Lift)";
	case	7:				return "Interlock 지연 Error";
	case	8:				return "Door OPEN/CLOSE 센서 Sensor 안됨";
	case	9:				return "제동저항 과열 Error(Lift)";
	case	10:				return "수신 Data 이상 Error";

	case	11:				return "Inverter Error";
	case	12:				return "Eocr Trip Error";
	case	13:				return "정위치 Sensor Error";
	case	14:				return "화물 Overtime Error";
	case	15:				return "전진Over감지 Error";
	case	16:				return "후진Over감지 Error";
	case	17:				return "Diverter상승Area감지 Sensor Error";
	case	18:				return "Diverter하강Area감지 Sensor Error";
	case	19:				return "H/S상승시 Area감지 Sensor Error";
	case	20:				return "H/S하강시 Area감지 Sensor Error";
		
	case	21:				return "SC통로방향 화물붕괴감지 Error";
	case	22:				return "Traverser 정위치 Error";
	case	23:				return "Traverser 확인 Sensor Error";
	case	24:				return "Lifter 확인 Sensor Error";
	case	25:				return "Traverser Sensor 조합 Error";
	case	26:				return "H/S,Div' 비상Limits Over감지 Error";
	case	27:				return "스토퍼 상승 Over Time";
	case	28:				return "스토퍼 하강 Over Time";
		
	case	31:				return "전진 Sensor Check 감지 Error";
	case	32:				return "후진 Sensor Check 감지 Error";
	case	33:				return "상단부 Sensor Check 감지 Error";
	case	34:				return "우측 Sensor Check 감지 Error";
	case	35:				return "좌측 Sensor Check 감지 Error";
	case	36:				return "";
	case	37:				return "목적지 이상";
				
	case	41:				return "메가진/디스펜서 언클렘프 Over Time";
	case	42:				return "메가진/디스펜서 Stopper#1 Over Time";
	case	43:				return "메가진/디스펜서 Stopper#2 Over Time";
	case	44:				return "메가진/디스펜서 Up(Motor) Over Time";
	case	45:				return "메가진/디스펜서 Down(Motor) Over Time";
	case	46:				return "메가진/디스펜서 센터링 전진 Over Time";
	case	47:				return "메가진/디스펜서 센터링 후진 Over Time";
	case	48:				return "메가진/디스펜서 내 Pallet 이동 Over Time";

	case	51:				return "팔레타이져 포크(클렘프) 전진시 리드 S/W동작안되어 Over Time";
	case	52:				return "팔레타이져 포크(클렘프) 후진시 리드 S/W동작안되어 Over Time";
	case	53:				return "팔레타이져내 Pallet akrdma Up 스토퍼 Up 출력시 리드 S/W 동작안됨";
	case	54:				return "팔레타이져내 Pallet akrdma Down 스토퍼 Down 출력시 리드 S/W 동작안됨";
	case	55:				return "팔레타이져 이송 실린더 전진 Over Time";
	case	56:				return "팔레타이져 이송 실린더 후진 Over Time";
	case	57:				return "팔레타이져 철판(은색)이 동작중 정위치 근접센서 동작안함";
	case	58:				return "팔레타이져 철판(은색)이 동작중 정위치 근접센서 파손됨";
	case	59:				return "팔레타이져 철판(은색)이 동작중 정위치 근접센서 풀림";
	case	60:				return "Stocker Up/Down 감지안됨";			// 정복열 추가 (090821)

	// 정복열 추가 (090821)
	case	61:				return "Stacker Up 비상";
	case	62:				return "Stacker Down 비상";
	case	63:				return "Stacker 10단 Over 감지";
	case	64:				return "Stacker 5단 Over 감지";

	case	71:				return "Diverter Up 비상";
	case	72:				return "Diverter Down 비상";
	case	73:				return "Over Time Error";
	case	74:				return "Data 있고 Sensor 감지 않됨";
	case	75:				return "Diverter 리드 Sensor 감지 않됨";
	case	76:				return "5단 Over 감지";
	case	77:				return "Stacker Up Down Sensor 감지 않됨";

	case	100:			return "웨이핑 머신 Error";					// 정복열 추가 (090821)


	// 정복열 추가 (090821)
	case	101:			return "Stacker 펜스 도어 열림";
	case	102:			return "CP 11번 OFF";
	case	103:			return "CP 12번 OFF";
	case	104:			return "CP 13번 OFF";
	case	105:			return "CP 14번 OFF";
	case	106:			return "CP 15번 OFF";
	case	107:			return "CP 16번 OFF";
	case	108:			return "CP 17번 OFF";
	case	109:			return "CP 18번 OFF";
	case	110:			return "CP 19번 OFF";
	case	111:			return "CP 20번 OFF";

	default:				
		CString strTemp;
		strTemp.Format("ERROR CODE=[%d]..설비담당자에게 문의바람..", nErrorCode);
		return strTemp;
	}

	return "";
}