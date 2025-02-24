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
		return CString("�����԰��");
	case	1:
		return CString("�����԰��");
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
		return CString("���Ϻз���#1");
	case	1:
		return CString("���Ϻз���#2");
	case	2:
		return CString("���Ϻз���#3");
	case	3:
		return CString("�����̵���");
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
		return CString("��Pallet");
	case	1:
		return CString("��Pallet");
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
		return CString("��������");
	case	1:
		return CString("����");
	case	2:
		return CString("����");
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
//	Number Limit  -  1000000000 ���� Double Value
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
		return CString("��ü");
	case	JOB_TYPE_UNIT_STO:
		return CString("UNIT �԰�");
	case	JOB_TYPE_UNIT_RET:
		return CString("UNIT ���");
	case    JOB_TYPE_STN_TO_STN:
		return CString("���� �̵�");
	case    JOB_TYPE_MANUAL_STN_TO_STN:
		return CString("���� �̵�");
	case	JOB_TYPE_MANUAL_STO:
		return CString("���ڵ� �԰�");
	case	JOB_TYPE_MANUAL_RET:
	case	JOB_TYPE_RACK_TO_RACK:
		return CString("���ڵ� ���");	
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
		return "�������";
	case	MSG_NO_STX:
		return "NO STX";
	case	MSG_NO_ETX:
		return "NO ETX";
	case	MSG_LUGG_NO_DUPLICATED:
		return "Luggage ��ȣ �ߺ�";
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
		return "S/C�۾���";
	case	2:
		return "���C/V����";
	case	3:
		return "���C/V���";
	case	4:
		return "4,3ȣ�� ����";
	case	5:
		return "3,2ȣ�� ����";
	case	6:
		return "2,1ȣ�� ����";
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
		return "�ڵ�";
	case	SC_MODE_ONLINE:
		return "����";
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
		return "�԰�";
	case	SC_JOB_TYPE_RETRIEVE:
		return "���";
	case	SC_JOB_TYPE_RACK_TO_RACK:
		return "RACK TO RACK";
	case	SC_JOB_TYPE_CALL_TO_HOME:
		return "Ȩ ����";
	case	SC_JOB_TYPE_MANUAL:
		return "�������� �۾�";
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
		return "�ڵ�";
	case	SC_MODE_ONLINE:
		return "����";
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
		return "�ڵ�";
	case	SC_MODE_ONLINE:
		return "����";
	case	SC_MODE_OFFLINE:
		return "OFF";
	}

	CString strTemp;
	strTemp.Format("�̻� (%c)", ucMode);
	return strTemp;
}

CString CLib::StackerRcModeToString_New(unsigned char ucMode)
{
	switch (ucMode)
	{
	case	SC_MODE_REMOTE_NEW:
		return "����";
	case	SC_MODE_ONLINE_NEW:
		return "�ڵ�";
	case	SC_MODE_OFFLINE:
		return "OFF";
	}
	
	CString strTemp;
	strTemp.Format("�̻� (%c)", ucMode);
	return strTemp;
}

CString CLib::StackerScModeToString(unsigned char ucMode)
{
	switch (ucMode)
	{
	case	SC_MODE_AUTO:
		return "�ڵ�";
	case	SC_MODE_MANUAL_NEW:
	case	SC_MODE_MANUAL:
		return "����";
	}

	CString strTemp;
	strTemp.Format("�̻� (%c)", ucMode);
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
	strTemp.Format("�̻� (%c)", ucActive);
	return strTemp;
}

CString CLib::StackerStatusToString(WORD bStatus)
{
	switch (bStatus)
	{
	case	SC_STA_WAIT:
		return "���(Wait)";
	case	SC_STA_IDLE:
		return "���(Idle)";
	case	SC_STA_MOVE:
		return "�̵�";
	case	SC_STA_ERROR:
		return "����";
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
		return "Ȩ �̵� ��.. (Simple Moving)";
	case	2:
		return "�԰� H/S�� �̵� ��.. (Simple Moving)";
	case	3:
		return "��� H/S�� �̵� ��.. (Simple Moving)";
	case	4:
		return "������ �̵� ��.. (Simple Moving)";
	case	5:
		return "Rack���� ũ�������� ���� ��.. (Loading)";
	case	6:
		return "ũ���ο��� Rack���� ���� ��.. (Unloading)";
	case	7:
		return "�԰� H/S���� ũ�������� ���� ��.. (Loading)";
	case	8:
		return "ũ���ο��� ��� H/S�� ���� ��.. (UnLoading)";
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
	// SFA - MELSEC INVERTER TYPE ũ����
	case	0:		return "����";
	case	1:		return "����������";
	case	2:		return "�°��������";
	case	3:		return "�����������(���� ��ư ����)";
	case	4:		return "�°�ü���̻�";
	case	5:		return "����ݺ������(DOOR OPEN)";

	case	11:		return "����ī��Ʈ �Ѱ��̻�(������)";
	case	12:		return "����ī��Ʈ �Ѱ��̻�(������)";
	case	13:		return "�����̵� �������⿡��";

	case	14:		return "����1���Ϸ��� ����ġ �̻�";
	case	15:		return "����2���Ϸ��� ����ġ �̻�";
	case	16:		return "��ŷ�� ���� ����ġ �̻�";

	case	18:		return "���� ������ �������Ÿ��";
	case	19:		return "������ġ ��������";
	case	20:		return "������ŷ�� ���� ����ġ �̻�";
	case	21:		return "������ġ���� ī���Ϳ���";
	case	22:		return "�������ʱ��� �̻�";
	case	23:		return "����������ġ �̻�";
	case	24:		return "���࿣�ڴ� �Ѱ� �̻�";
	case	30:		return "�°�ī��Ʈ�̻�";
	case	31:		return "�°�ī��Ʈ�̻� �����̻�(��½�)";
	case	32:		return "�°�ī��Ʈ�̻� �����̻�(�ϰ���)";

	case	33:		return "�°��̵� �������⿡��";
	case	34:		return "�°�1���Ϸ��� ����ġ �̻�";
	case	35:		return "�°�2���Ϸ��� ����ġ �̻�";

	case	36:		return "�°� ����ġ �̻�";

	case	38:		return "�°������� �°� ����Ÿ��";
	case	39:		return "�°���ġ��������";
	case	40:		return "������ŷ�� �°� ����ġ �̻�";

	case	41:		return "�°� ��ġ���� ī��Ʈ����";
	case	42:		return "�°����ʱ��� �̻�";

	case	43:		return "��ŷUP/DN�Ϸ��� �°�����ġ�̻�";
	case	44:		return "��ŷUP/DN�Ϸ��� �°�����ġ�̻�";
	case	45:		return "��ŷUP/DN ����Ÿ��";
	case	46:		return "��ŷUP/DN�� �°�ZONE �̻�";
	case	47:		return "��ŷUP/DN�� �°�ZONE �̻�";

	case	50:		return "SC ���ʱ⵿�� ��ũ#1 �̻�";
	case	51:		return "SC ���ʱ⵿�� ��ũ#2 �̻�";
	case	52:		return "ȭ�� ���������� ����";
	case	53:		return "ȭ�� �ر�����";
	case	54:		return "�����԰� ��ũ#1";
	case	55:		return "�����԰� ��ũ#2";
	case	56:		return "�԰����(����)";
	case	57:		return "������(����)";

	case	58:		return "����� ���� ��ũ#1";
	case	59:		return "����� ���� ��ũ#2";
	case	60:		return "������ ��ũ#1(�۾���)";
	case	61:		return "������ ��ũ#2(�۾���)";
	case	62:		return "�԰���� ��ũ#1(�۾���)";
	case	63:		return "�԰���� ��ũ#2(�۾���)";
	case	64:		return "�԰���� ��ũ#1(��)";
	case	65:		return "�԰���� ��ũ#2(��)";

	case	70:		return "SC�̵��� ��ũ�����̻�";
	case	71:		return "ACTIVE���� ��ũ�����̻�";
	case	72:		return "��ũ���� ȭ�� ����";
	case    74:		return "��ũ�����̻�(�н���)";
	case	75:		return "��ũ�����̻�(Ȩ���ͽ�)";
	case	76:		return "��ũ�����̻�(�����̵�)";
	case	77:		return "��ũ�����̻�(�°��̵�)";
	case	78:		return "��������� ��ũ�����̻�";
	case	79:		return "�����°��� ��ũ�����̻�";

	case	80:		return "��ũ������ ����Ÿ��";
	case	81:		return "��ũ���� ����Ÿ��";
	case	82:		return "��ũ���� �����̻�";
	case	83:		return "����������Ʈ �����̻�";
	case	84:		return "����������Ʈ �����̻�";
	case	87:		return "��ũ#1 Ȩ���ͽ���";
	case	88:		return "��ũ#2 Ȩ���ͽ���";
	case	89:		return "DRIVE ALARM(��ũ#1)";

	case	90:		return "DRIVE ALARM(��ũ#2)";
	case	91:		return "���� ���� ������";
	case	92:		return "�°� ���� ������";
	case	93:		return "��ũ ���� ������";
	case	94:		return "�������� ����";
	case	96:		return "����̺��̻�(����)";
	case	97:		return "����̺��̻�(�°�)";
	case    98:		return "��ġ���� �����̻�";
	case	99:		return "�Ƴ��α���� �����̻�";

	case	101:		return "�۾������ ��ü�н� �̿Ϸ�";
	case	102:		return "�۾������ �����н� �̿Ϸ�";
	case	103:		return "�۾������ �°��н� �̿Ϸ�";
	case	104:		return "�°��н� ����";
	case	105:		return "�°��н� ī��Ʈ ����";
	case	106:		return "�°��н� ����Ȩ �̻�";
	case	107:		return "�����н� ī��Ʈ ����";
	case    108:		return "�����н� ����";
	case	109:		return "�����н� ����(���� ������Ʈ����)";
	case	110:		return "�����н� ����(���� ������Ʈ����)";
	case	111:		return "�����н������� ����(������Ʈ �����Ѱ� ����)";
	case	112:		return "�����н� ����Ȩ �̻�";
	case	113:		return "��ũ�н� ����Ÿ��";
	case	114:		return "�۾����н� ���� ����Ÿ��";
	case	115:		return "�۾����н� �����н� ����";
	case	116:		return "�۾����н� �°�����(Ÿ��/ī��Ʈ)";
	case    117:		return "�۾����н� �°��н� ����";
	case	118:		return "�극��ũ�н� �̻� (����)";
	case	119:		return "�극��ũ�н� �̻� (�°�)";
	case	120:		return "�۾����н� Ʈ���� �̻�";
	case	121:		return "�۾������� ���꿡��";
	case	122:		return "�̵����� ���꿡��";
	case    123:		return "�°���� ���꿡��";
	case	124:		return "������� ���꿡��";
	case	125:		return "������ ���꿡��(��/��/��/�۾���)";
	case	126:		return "����°� ���ӰŸ� ���꿡��";
	case	127:		return "��ũ�ִ���� ���꿡��";
	case	128:		return "������ ���꿡��(�ຸ����)";
	case    129:		return "���న�ӰŸ�,��� ���꿡��";
	case	130:		return "�°����ӰŸ�, ��� ���꿡��";


	case	131:	return "�԰��۾��� �����̻�";
	case	132:	return "����۾��� �����̻�";
	case	133:	return "����۾��� ȭ���̻�";
	case	141:	return "���ŵ����� �̻�(��ũ#1)";
	case	142:	return "���ŵ����� �̻�(��ũ#2)";
	case	143:	return "���ŵ����� �۾��� �뵵�̻�";
	case	144:	return "���ŵ����� OVERWRITE";
	case	145:	return "���ŵ����� �������� ����";
	case	146:	return "���ŵ����� �������� �������䱸����";
	case	147:	return "���ŵ����� ������ ��������";
	case	148:	return "���ŵ����� ����� ��忡��";
	case	149:	return "������ġ���� UNIT�õ���ȣ �̻�";
	case	150:	return "�°���ġ���� UNIT�õ���ȣ �̻�";

	case	151:	return "�ý����Ķ�����̻�";
	case	152:	return "���� �Ķ�����̻�";
	case	153:	return "�°� �Ķ�����̻�";
	case	154:	return "��ũ �Ķ�����̻�";
	case	155:	return "�۾��� �Ķ�����̻�";

	case	161:	return "���࿣�ڴ� ȸ������ �̻�";
	case	162:	return "���࿣�ڴ� ���굥���� �̴�";
	case	163:	return "���࿣�ڴ� ���굥���� ����";
	case	164:	return "���࿣�ڴ� �Էµ����� �̻�";
	case	166:	return "�°����ڴ� ȸ�� ����";
	case	167:	return "�°����ڴ� ���굥���� �̴�";
	case	168:	return "�°����ڴ� ���굥���� ����";
	case	169:	return "�°����ڴ� �Էµ����� �̻�";

	case	171:	return "���� ��ŵ���";
	case	172:	return "���� ���� �̻�";
	case	173:	return "��� üũ�� ����";
	case	174:	return "��� CASE ����";

	case	200:	return "��� ������ ����";
	case	201:	return "������ ����";
	case	202:	return "��ȿ�� ����";
	case	203:	return "�۾��� ������ �̻�";
	case	204:	return "üũ�� ����";
	case	205:	return "������ֿ���";
	case	206:	return "�ִ뿭��� ����";
	case	207:	return "�۾��Է� ����";
	case	208:	return "SC ��/���� ��� ����";
	case    209:	return "����� OFFLINE MODE ����";

	case	SC_ERR_CODE_COMM_ERROR:		return	"����� �������. ��ŵ���";
	
	default:
		return "��Ÿ ����[SC�޴�������]";
	}
}

CString CLib::GetStackerErrorInfoQ(int nErrorCode)
{
	switch ( nErrorCode )
	{
	// SFA - MELSEC INVERTER TYPE ũ����
	case	1:		return "����������";
	case	2:		return "�°��������";
	case	3:		return "�����������(���� ��ư ����)";
	case	4:		return "�°�ü���̻�";
	case	5:		return "����ݺ������(DOOR OPEN)";

	case	11:		return "����ī��Ʈ �Ѱ��̻�(������)";
	case	12:		return "����ī��Ʈ �Ѱ��̻�(������)";
	case	13:		return "�����̵� �������⿡��";

	case	14:		return "����1���Ϸ��� ����ġ �̻�";
	case	15:		return "����2���Ϸ��� ����ġ �̻�";
	case	16:		return "��ŷ�� ���� ����ġ �̻�";

	case	18:		return "���� ������ �������Ÿ��";
	case	19:		return "������ġ ��������";
	case	20:		return "������ŷ�� ���� ����ġ �̻�";
	case	21:		return "������ġ���� ī���Ϳ���";
	case	22:		return "�������ʱ��� �̻�";
	case	30:		return "�°�ī��Ʈ�̻�";
	case	31:
	case	32:		return "�°�ī��Ʈ�̻� �����̻�";

	case	33:		return "�°��̵� �������⿡��";
	case	34:		return "�°�1���Ϸ��� ����ġ �̻�";
	case	35:		return "�°�2���Ϸ��� ����ġ �̻�";

	case	36:		return "�°� ����ġ �̻�";

	case	38:		return "�°������� �°� ����Ÿ��";
	case	39:		return "�°���ġ��������";
	case	40:		return "������ŷ�� �°� ����ġ �̻�";

	case	41:		return "�°� ��ġ���� ī��Ʈ����";
	case	42:		return "�°����ʱ��� �̻�";

	case	43:		return "��ŷUP/DN�Ϸ��� �°�����ġ�̻�";
	case	44:		return "��ŷUP/DN�Ϸ��� �°�����ġ�̻�";
	case	45:		return "��ŷUP/DN ����Ÿ��";
	case	46:		return "��ŷUP/DN�� �°�ZONE �̻�";
	case	47:		return "��ŷUP/DN�� �°�ZONE �̻�";

	case	50:		return "SC ���ʱ⵿�� ��ũ#1 �̻�";
	case	51:		return "SC ���ʱ⵿�� ��ũ#2 �̻�";
	case	52:		return "ȭ�� ���������� ����";
	case	53:		return "ȭ�� �ر�����";
	case	54:		return "�����԰� ��ũ#1";
	case	55:		return "�����԰� ��ũ#1";
	case	56:		return "�԰����(����)";
	case	57:		return "������(����)";

	case	58:		return "����� ���� ��ũ#1";
	case	59:		return "����� ���� ��ũ#2";
	case	60:		return "������ ��ũ#1(�۾���)";
	case	61:		return "������ ��ũ#2(�۾���)";
	case	62:		return "�԰���� ��ũ#1(�۾���)";
	case	63:		return "�԰���� ��ũ#2(�۾���)";
	case	64:		return "�԰���� ��ũ#1(��)";
	case	65:		return "�԰���� ��ũ#2(��)";

	case	70:		return "SC�̵��� ��ũ�����̻�";
	case	71:		return "ACTIVE���� ��ũ�����̻�";
	case	72:		return "��ũ���� ȭ�� ����";
	case	75:		return "��ũ�����̻�(Ȩ���ͽ�)";
	case	76:		return "��ũ�����̻�(�����̵�)";
	case	77:		return "��ũ�����̻�(�°��̵�)";
	case	78:		return "��������� ��ũ�����̻�";
	case	79:		return "�����°��� ��ũ�����̻�";

	case	80:		return "��ũ������ ����Ÿ��";
	case	81:		return "��ũ���� ����Ÿ��";
	case	82:		return "��ũ���� �����̻�";
	case	83:		return "����������Ʈ �����̻�";
	case	84:		return "����������Ʈ �����̻�";
	case	87:		return "��ũ#1 Ȩ���ͽ���";
	case	88:		return "��ũ#2 Ȩ���ͽ���";
	case	89:		return "DRIVE ALARM(��ũ#1)";

	case	90:		return "DRIVE ALARM(��ũ#2)";
	case	91:		return "���� ���� ������";
	case	92:		return "�°� ���� ������";
	case	93:		return "��ũ ���� ������";
	case	94:		return "�������� ����";
	case	96:		return "����̺��̻�(����)";
	case	97:		return "����̺��̻�(�°�)";

	case	131:	return "�԰��۾��� �����̻�";
	case	132:	return "����۾��� �����̻�";
	case	133:	return "����۾��� ȭ���̻�";
	case	141:	return "���ŵ����� �̻�(��ũ#1)";
	case	142:	return "���ŵ����� �̻�(��ũ#2)";
	case	143:	return "���ŵ����� �۾��� �뵵�̻�";
	case	144:	return "���ŵ����� OVERWRITE";
	case	145:	return "���ŵ����� �������� ����";
	case	146:	return "���ŵ����� �������� �������䱸����";
	case	147:	return "���ŵ����� ������ ��������";
	case	148:	return "���ŵ����� ����� ��忡��";
	case	149:	return "������ġ���� UNIT�õ���ȣ �̻�";
	case	150:	return "�°���ġ���� UNIT�õ���ȣ �̻�";

	case	151:	return "�ý����Ķ�����̻�";
	case	152:	return "���� �Ķ�����̻�";
	case	153:	return "�°� �Ķ�����̻�";
	case	154:	return "��ũ �Ķ�����̻�";
	case	155:	return "�۾��� �Ķ�����̻�";

	case	161:	return "���࿣�ڴ� ȸ������ �̻�";
	case	162:	return "���࿣�ڴ� ���굥���� �̴�";
	case	163:	return "���࿣�ڴ� ���굥���� ����";
	case	164:	return "���࿣�ڴ� �Էµ����� �̻�";
	case	166:	return "�°����ڴ� ȸ�� ����";
	case	167:	return "�°����ڴ� ���굥���� �̴�";
	case	168:	return "�°����ڴ� ���굥���� ����";
	case	169:	return "�°����ڴ� �Էµ����� �̻�";

	case	171:	return "���� ��ŵ���";
	case	172:	return "���� ���� �̻�";
	case	173:	return "��� üũ�� �̷�";
	case	174:	return "��� CASE����";

	case	200:		return "��� ������ ����";
	case	201:		return "������ ����";
	case	202:		return "��ȿ�� ����";
	case	203:		return "�۾��� ������ �̻�";
	case	204:		return "üũ�� ����";
	case	205:		return "������ֿ���";
	case	206:		return "�ִ뿭��� ����";
	case	207:		return "�۾��Է� ����";
	case	208:		return "SC ��/���� ��� ����";

	case	SC_ERR_CODE_COMM_ERROR:		return	"����� �������. ��ŵ���";
	
	default:
		return "��Ÿ ����[SC�޴�������]";
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
	// SFA - MELSEC INVERTER TYPE ũ����
	case	1:		return "����������";
	case	2:      return "���� ���� �浹 Error";
	case	3:		return "�����������(EMG ��ư ����)";
	case	4:      return "Area Sensor ����";
	case	5:		return "�¶��� �������[ECS���� ������� ����]";

	case	11:		return "����ī��Ʈ �Ѱ��̻�(������)";
	case	12:		return "����ī��Ʈ �Ѱ��̻�(������)";
	case	13:		return "�����̵� �������⿡��";

	case	14:		return "����1���Ϸ��� ����ġ �̻�";
	case	15:		return "����2���Ϸ��� ����ġ �̻�";
	case	16:		return "��ŷ�� ���� ����ġ �̻�";

	case	18:		return "���� ������ �������Ÿ��";
	case	19:		return "������ġ ��������";

	case	21:		return "������ġ���� ī���Ϳ���";
	case	22:		return "�������ʱ��� �̻�";

	case	23:		return "CV ���� ����";
	case	26:		return "CV ���� Ÿ�� ����";

	case	50:		return "RTV ���ʱ⵿�� CV#1 �Ϲ��̻�";

	case	52:		return "ȭ�� ���������� ����";
	case	53:		return "ȭ�� �ر�����";
	case	56:		return "Ȩ ���� Sensor Error";

	case	70:		return "RTV �̵� �� CV �����̻�";
	case	71:		return "ACTIVE���� CV �����̻�";

	case	74:		return "CV �����̻�(�н���)";
	case	75:		return "CV �����̻�(Ȩ���ͽ�)";
	case	76:		return "CV �����̻�(�����̵�)";

	case	78:		return "��������� CV �����̻�";

	case	80:		return "CV������ ����Ÿ��";
	case	81:		return "CV���� ����Ÿ��";
	case	82:		return "CV���� �����̻�";

	case	91:		return "���� ���� ������";

	case	93:		return "CV ���� ������";
	case	94:		return "�������� ����";
	case	95:		return "BREAK FUSE OFF";

	case	99:		return "�Ƴ��α���� �����̻�";

	case	101:	return "�۾������ ��ü�н� �̿Ϸ�";

	case	124:	return "������� ���꿡��";
	case	125:	return "������ ���꿡��";
	case	126:	return "���న�� ���ӰŸ� ���꿡��";

	case	127:	return "CV ��� ���꿡��";
	case	128:	return "������ ���꿡��";
	case	129:	return "���న�ӰŸ� ��� ���꿡��";

	case	151:	return "�ý����Ķ�����̻�";
	case	152:	return "���� �Ķ�����̻�";
	case	154:	return "CV �Ķ�����̻�";

	case	161:	return "���࿣�ڴ� ȸ������ �̻�";
	case	162:	return "���࿣�ڴ� ���굥���� �̴�";
	case	163:	return "���࿣�ڴ� ���굥���� ����";
	case	164:	return "���࿣�ڴ� �Էµ����� �̻�";

	case	RGV_ERR_CODE_COMM_ERROR:		return	"����� �������. ��ŵ���";
	}

	return "��Ÿ ����[RGV �޴�������]";

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

//^^^^^^^^^^^^^ RGV ���H/S ���� ^^^^^^^^^^^^^^//
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
	case	1:				return "�������(Main)";
	case	2:				return "�������(�ش�OP BOX)";
	case	3:				return "�������(Remote:Ecs)";
	case	4:				return "����ġ Error";
	case	5:				return "ȭ���ر� Error(Lift)";
	case	6:				return "Oversize Error(Lift)";
	case	7:				return "Interlock ���� Error";
	case	8:				return "Door OPEN/CLOSE ���� Sensor �ȵ�";
	case	9:				return "�������� ���� Error(Lift)";
	case	10:				return "���� Data �̻� Error";

	case	11:				return "Inverter Error";
	case	12:				return "Eocr Trip Error";
	case	13:				return "����ġ Sensor Error";
	case	14:				return "ȭ�� Overtime Error";
	case	15:				return "����Over���� Error";
	case	16:				return "����Over���� Error";
	case	17:				return "Diverter���Area���� Sensor Error";
	case	18:				return "Diverter�ϰ�Area���� Sensor Error";
	case	19:				return "H/S��½� Area���� Sensor Error";
	case	20:				return "H/S�ϰ��� Area���� Sensor Error";
		
	case	21:				return "SC��ι��� ȭ���ر����� Error";
	case	22:				return "Traverser ����ġ Error";
	case	23:				return "Traverser Ȯ�� Sensor Error";
	case	24:				return "Lifter Ȯ�� Sensor Error";
	case	25:				return "Traverser Sensor ���� Error";
	case	26:				return "H/S,Div' ���Limits Over���� Error";
	case	27:				return "������ ��� Over Time";
	case	28:				return "������ �ϰ� Over Time";
		
	case	31:				return "���� Sensor Check ���� Error";
	case	32:				return "���� Sensor Check ���� Error";
	case	33:				return "��ܺ� Sensor Check ���� Error";
	case	34:				return "���� Sensor Check ���� Error";
	case	35:				return "���� Sensor Check ���� Error";
	case	36:				return "";
	case	37:				return "������ �̻�";
				
	case	41:				return "�ް���/���漭 ��Ŭ���� Over Time";
	case	42:				return "�ް���/���漭 Stopper#1 Over Time";
	case	43:				return "�ް���/���漭 Stopper#2 Over Time";
	case	44:				return "�ް���/���漭 Up(Motor) Over Time";
	case	45:				return "�ް���/���漭 Down(Motor) Over Time";
	case	46:				return "�ް���/���漭 ���͸� ���� Over Time";
	case	47:				return "�ް���/���漭 ���͸� ���� Over Time";
	case	48:				return "�ް���/���漭 �� Pallet �̵� Over Time";

	case	51:				return "�ȷ�Ÿ���� ��ũ(Ŭ����) ������ ���� S/W���۾ȵǾ� Over Time";
	case	52:				return "�ȷ�Ÿ���� ��ũ(Ŭ����) ������ ���� S/W���۾ȵǾ� Over Time";
	case	53:				return "�ȷ�Ÿ������ Pallet akrdma Up ������ Up ��½� ���� S/W ���۾ȵ�";
	case	54:				return "�ȷ�Ÿ������ Pallet akrdma Down ������ Down ��½� ���� S/W ���۾ȵ�";
	case	55:				return "�ȷ�Ÿ���� �̼� �Ǹ��� ���� Over Time";
	case	56:				return "�ȷ�Ÿ���� �̼� �Ǹ��� ���� Over Time";
	case	57:				return "�ȷ�Ÿ���� ö��(����)�� ������ ����ġ �������� ���۾���";
	case	58:				return "�ȷ�Ÿ���� ö��(����)�� ������ ����ġ �������� �ļյ�";
	case	59:				return "�ȷ�Ÿ���� ö��(����)�� ������ ����ġ �������� Ǯ��";
	case	60:				return "Stocker Up/Down �����ȵ�";			// ������ �߰� (090821)

	// ������ �߰� (090821)
	case	61:				return "Stacker Up ���";
	case	62:				return "Stacker Down ���";
	case	63:				return "Stacker 10�� Over ����";
	case	64:				return "Stacker 5�� Over ����";

	case	71:				return "Diverter Up ���";
	case	72:				return "Diverter Down ���";
	case	73:				return "Over Time Error";
	case	74:				return "Data �ְ� Sensor ���� �ʵ�";
	case	75:				return "Diverter ���� Sensor ���� �ʵ�";
	case	76:				return "5�� Over ����";
	case	77:				return "Stacker Up Down Sensor ���� �ʵ�";

	case	100:			return "������ �ӽ� Error";					// ������ �߰� (090821)


	// ������ �߰� (090821)
	case	101:			return "Stacker �潺 ���� ����";
	case	102:			return "CP 11�� OFF";
	case	103:			return "CP 12�� OFF";
	case	104:			return "CP 13�� OFF";
	case	105:			return "CP 14�� OFF";
	case	106:			return "CP 15�� OFF";
	case	107:			return "CP 16�� OFF";
	case	108:			return "CP 17�� OFF";
	case	109:			return "CP 18�� OFF";
	case	110:			return "CP 19�� OFF";
	case	111:			return "CP 20�� OFF";

	default:				
		CString strTemp;
		strTemp.Format("ERROR CODE=[%d]..�������ڿ��� ���ǹٶ�..", nErrorCode);
		return strTemp;
	}

	return "";
}