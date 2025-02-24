#include "stdafx.h"
#include "BcrComm.h"
#include "Lib.h"
#include "Ecs.h"

CBcr::CBcr(int nNum, CEcsDoc* pDoc) : CSerial() 
{ 
	m_nNum = nNum; 
	m_pDoc = pDoc; 
}

BOOL CBcr::Connect(LPSTR strComName,
		   DWORD dwBaudRate,
		   BYTE byByteSize,
		   BYTE byParity,
		   BYTE byStopBits,
		   BYTE byFlowCtrl)
{
	SetConfig(strComName, dwBaudRate, byByteSize, byParity, byStopBits, byFlowCtrl);
	return Open();
}

int CBcr::ReadStatus()
{
	BYTE	RxBuff[256];
	BYTE	DummyBuf[1024];
	int     nReadCnt=0;

	memset(RxBuff, 0x0, sizeof(RxBuff));

	int i=0;

	if (RecvBcr(RxBuff, 1) != TRUE)
	{
		return 2;
	}

	if (RxBuff[0] != STX)
		return 2;

	while (TRUE)
	{
		i++;
		if (RecvBcr(RxBuff+i, 1) != TRUE)
			return 2;

		if (RxBuff[i] == ETX)
			break;
	
		if (i > 6)
		{
			RecvBcr(DummyBuf, 1024);
			
			//char strBcrData[100];
			//memcpy(strBcrData, RxBuff+1, i-1);
			//strBcrData[i-1] = NULL;
			//m_pDoc->m_szBcrData[m_nNum].Format("%s", strBcrData);
			m_pDoc->m_szBcrData[m_nNum] = "?????";
			ParsingFrame2();

			CString strBuff;
			strBuff.Format("Error.. Wrong Data.. BcrNo=[%d]", m_nNum+1);
//			m_pDoc->m_pLog->Error(LOG_POS_BCR, LOG_SYSTEM, strBuff);

			return FALSE;
		}

	}

	if (RxBuff[1] == '?')
	{
		CString strBuff;
		strBuff.Format("Error.. NO Read.. BcrNo=[%d]", m_nNum+1);
//		m_pDoc->m_pLog->Error(LOG_POS_BCR, LOG_SYSTEM, strBuff);

		//char strBcrData[100];
		//memcpy(strBcrData, RxBuff+1, i-1);
		//strBcrData[i-1] = NULL;
		//m_pDoc->m_szBcrData[m_nNum].Format("%s", strBcrData);
		m_pDoc->m_szBcrData[m_nNum] = "?????";
		ParsingFrame2();

		return FALSE;
	}
	else if (i == 1)
	{
		m_pDoc->m_szBcrData[m_nNum] = "SizeErr";
		ParsingFrame2();

		CString strBuff;
		strBuff.Format("Error.. Wrong Data Size.. BcrNo=[%d]", m_nNum+1);
//		m_pDoc->m_pLog->Error(LOG_POS_BCR, LOG_SYSTEM, strBuff);

		return FALSE;
	}
	else if (i != 6)
	{
		//char strBcrData[100];
		//memcpy(strBcrData, RxBuff+1, i-1);
		//strBcrData[i-1] = NULL;
		//m_pDoc->m_szBcrData[m_nNum].Format("%s", strBcrData);

		m_pDoc->m_szBcrData[m_nNum] = "?????";
		ParsingFrame2();

		CString strBuff;
		strBuff.Format("Error.. Wrong Data Size.. BcrNo=[%d]", m_nNum+1);
//		m_pDoc->m_pLog->Error(LOG_POS_BCR, LOG_SYSTEM, strBuff);

		return FALSE;
	}
	else
	{
		ParsingFrame(RxBuff+1, i+1);
		return TRUE;
	}

	return TRUE;
}

void CBcr::ParsingFrame(BYTE * pRxBuff, int nLen)
{

	char strBcrData[20];
	CString strData;

	memcpy(strBcrData, pRxBuff, nLen-2);
	strBcrData[nLen-2] = NULL;
	strData.Format("%s", strBcrData);

	/* BcrCode
	nSeqNo = m_pDoc->m_pJob->GetNewSeqNo();
	*/

	m_pDoc->m_szBcrData[m_nNum] = strData;

	/* BcrCode
	if (m_nNum == 1)
		m_pDoc->m_pJob->AddBcrBuff(nSeqNo, m_nNum+1, strData, 1); // 출고용
	else
		m_pDoc->m_pJob->AddBcrBuff(nSeqNo, m_nNum+1, strData, 2); // 입고용
	*/

	m_pDoc->m_pBcrInfo[m_nNum]->m_strBcrData = strData;
	m_pDoc->m_pBcrInfo[m_nNum]->m_nProSta = 1;
	m_pDoc->m_pBcrInfo[m_nNum]->m_bStatus = TRUE;

	CString strBuff;
	strBuff.Format("BCR Data Receive.. BcrNo:%d, (%s)", m_nNum+1, strData);
//	m_pDoc->m_pLog->Job(LOG_POS_BCR, LOG_SYSTEM, strBuff);

}

void CBcr::ParsingFrame2()
{

	CString strData;

	/* BcrCode
	nSeqNo = m_pDoc->m_pJob->GetNewSeqNo();
	*/

	strData = "?????";

	m_pDoc->m_szBcrData[m_nNum] = strData;
	m_pDoc->m_pBcrInfo[m_nNum]->m_strBcrData = strData;
	m_pDoc->m_pBcrInfo[m_nNum]->m_nProSta = 1;

	/* BcrCode
	if (m_nNum == 1)
		m_pDoc->m_pJob->AddBcrBuff(nSeqNo, m_nNum+1, strData, 1); // 출고용
	else
		m_pDoc->m_pJob->AddBcrBuff(nSeqNo, m_nNum+1, strData, 2); // 입고용
	*/

}
