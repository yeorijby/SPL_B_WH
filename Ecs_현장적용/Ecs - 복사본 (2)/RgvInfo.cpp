


#include "stdafx.h"
#include "EcsDoc.h"
#include "RgvInfo.h"

IMPLEMENT_DYNCREATE(CRgvInfo, CStackerInfo)


CRgvInfo::CRgvInfo(CEcsDoc* pDoc, CString strFileName, int nNum) : CInfo(pDoc, strFileName) 
{ 
	m_nNum = nNum;

	m_bStoreSuspend = m_bRetrieveSuspend = FALSE; 

	m_nNextRtn = ROUTINE_STORE;
	m_nStoNextRtn = 0;
	m_nStoSiteNextRtn = 0;
	m_nRetNextRtn = 0;
	m_nRetSiteNextRtn = 0;

	m_ucMode = RGV_MODE_MANUAL;
	m_ucStatus = RGV_STA_WAIT;
	m_ucProdLoad = RGV_PROD_EMPTY;
	m_ucActive = RGV_STOP;

	m_wErrCode = 0;
	m_wPrevErrCode = 0;
	m_ucHorizontalPos = 0;

	m_ucHorizontalPosSave = 0;

	m_bInvoke = FALSE;
	m_nLuggNum = 0;
	m_nInternalLuggNum = 0;
	m_ucJobType = RGV_JOB_TYPE_ANY;
	m_ucInternalJobType = RGV_JOB_TYPE_RETRIEVE; //RGV_JOB_TYPE_ANY;
	m_ucTransaction = RGV_TRN_DOING;

	m_nInternalLuggNum2 = 0;
	m_ucInternalJobType2 = RGV_JOB_TYPE_RETRIEVE; 

	m_nDestTrack = 0;
	m_nStartTrack = 0;

	m_strDevice = m_pDoc->m_pConfig->GetRgvDeviceName(nNum);

	Restore();
}

CRgvInfo::~CRgvInfo()
{
//	Backup();
}

void CRgvInfo::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_bInvoke;

		ar << m_nLuggNum;
		ar << m_nInternalLuggNum;
		ar << m_ucJobType;
		ar << m_ucInternalJobType;

		ar << m_wErrCode;
		ar << m_wPrevErrCode;

		ar << m_nStartTrack;
		ar << m_nDestTrack;
		ar << m_ucStartPos;
		ar << m_ucDestPos;

		ar << m_bStoreSuspend;
		ar << m_bRetrieveSuspend;

		ar << m_tJobStart;
		ar << m_tJobEnd;
		ar << m_tErrorStart;
		ar << m_tErrorEnd;

		ar << m_pDoc->m_b4groupCheck;
		ar << m_pDoc->m_b5groupCheck;
		ar << m_pDoc->m_b6groupCheck;
		ar << m_pDoc->m_b7groupCheck;
		ar << m_pDoc->m_b8groupCheck;
		ar << m_pDoc->m_b9groupCheck;

		ar << m_pDoc->m_bAllScStoSuspend;
		ar << m_pDoc->m_bAllScRetSuspend;
	}
	else
	{
		ar >> m_bInvoke;

		ar >> m_nLuggNum;
		ar >> m_nInternalLuggNum;
		ar >> m_ucJobType;
		ar >> m_ucInternalJobType;

		ar >> m_wErrCode;
		ar >> m_wPrevErrCode;

		ar >> m_nStartTrack;
		ar >> m_nDestTrack;
		ar >> m_ucStartPos;
		ar >> m_ucDestPos;

		ar >> m_bStoreSuspend;
		ar >> m_bRetrieveSuspend;

		ar >> m_tJobStart;
		ar >> m_tJobEnd;
		ar >> m_tErrorStart;
		ar >> m_tErrorEnd;

		ar >> m_pDoc->m_b4groupCheck;
		ar >> m_pDoc->m_b5groupCheck;
		ar >> m_pDoc->m_b6groupCheck;
		ar >> m_pDoc->m_b7groupCheck;
		ar >> m_pDoc->m_b8groupCheck;
		ar >> m_pDoc->m_b9groupCheck;

		ar >> m_pDoc->m_bAllScStoSuspend;
		ar >> m_pDoc->m_bAllScRetSuspend;
	}
}

/*
void CRgvInfo::InvokeControl(CScControl *pRgv)
{
	if ( m_bModified == FALSE )	 return;
	pRgv->SetValue(m_ucHorizontalPos,
				   GetRailColor(),
				   GetForkColor(),
				   GetPostColor(),
				   LIGHT_GRAY,
				   DARK_GRAY);

	m_bModified = FALSE;
}
*/
void CRgvInfo::DisplayRgvStatusMsg()
{
	if (m_ucStatus == RGV_STA_ERROR)
	{
		CString strMsg;
		strMsg.Format("%s 에러.. 에러코드[%d] 내용[%s]", m_strDevice, m_wErrCode, GetRgvErrorString());
		m_pDoc->DisplayMessage(strMsg, FALSE);
	}
}

/*
void CRgvInfo::WriteStatusForHMI()
{
	m_pDoc->m_ConveyorThreadInfo[m_nNum].m_ConveyorRgvMsg.nCommand  = CV_CMD_RGV;
	m_pDoc->m_ConveyorThreadInfo[m_nNum].m_ConveyorRgvMsg.ucMode = m_ucMode-0x30;
	m_pDoc->m_ConveyorThreadInfo[m_nNum].m_ConveyorRgvMsg.ucStatus = m_ucStatus-0x30;
	m_pDoc->m_ConveyorThreadInfo[m_nNum].m_ConveyorRgvMsg.ucActive = m_ucActive-0x30;
	m_pDoc->m_ConveyorThreadInfo[m_nNum].m_ConveyorRgvMsg.wErrCode = m_wErrCode;
	m_pDoc->m_ConveyorThreadInfo[m_nNum].m_ConveyorRgvMsg.bModified = TRUE;

	CV_ACTION(m_nNum);
}
*/
COLORREF CRgvInfo::GetForkColor()
{
	if (m_ucStatus == RGV_STA_ERROR)
		return RED;

	if (m_ucMode != RGV_MODE_AUTO ||
	    m_ucActive == RGV_STOP )
		return DARK_GRAY;

	if (!m_bInvoke) return LIGHT_GRAY;

	switch (m_ucInternalJobType)
	{
	case	RGV_JOB_TYPE_STORE:				return GREEN;
	case	RGV_JOB_TYPE_RETRIEVE:			return BLUE;
	case	RGV_JOB_TYPE_RACK_TO_RACK:  	return YELLOW;
	//case	JOB_TYPE_PICK_REPLENISH:		return m_pDoc->m_pConfig->m_clrCvAutoPickingColor;
	case	RGV_JOB_TYPE_SITE_TO_SITE:		return CYAN;
	case	RGV_JOB_TYPE_AISLE_TO_AISLE:	return LIGHT_CYAN;

	case	JOB_TYPE_MANUAL_STO:		return DARK_CYAN;
	case	JOB_TYPE_MANUAL_RET:		return LIGHT_RED;
	//case	JOB_TYPE_MANUAL_PICKING:	return m_pDoc->m_pConfig->m_clrCvSemiPickingColor;
	case	JOB_TYPE_MANUAL_STN_TO_STN:		return LIGHT_MAGENTA;

	case	RGV_JOB_TYPE_MANUAL:
	case	RGV_JOB_TYPE_CALL_TO_HOME:	return BLACK;
	}

	return LIGHT_GRAY;
}


COLORREF CRgvInfo::GetRailColor() 
{
	if (m_bStoreSuspend /*|| m_bRetrieveSuspend*/)		return RED;

	return m_bInvoke ? BLUE : BLACK;
}

COLORREF CRgvInfo::GetPostColor()
{
	return m_ucProdLoad ==  RGV_PROD_LOAD ? BLUE : DARK_GRAY;
}

CString CRgvInfo::GetRgvLuggNumString()
{
	CString strTemp;
	strTemp.Format("%d", m_nLuggNum);
	return strTemp;
}

CString CRgvInfo::GetEcsLuggNumString()
{
	CString strTemp;
	strTemp.Format("%d", m_nInternalLuggNum);
	return m_bInvoke ? strTemp : "";
}

CString CRgvInfo::GetEcsLuggNumString2()
{
	CString strTemp;
	strTemp.Format("%d", m_nInternalLuggNum2);
	return m_bInvoke ? strTemp : "";
}

CString CRgvInfo::GetRgvModeString()
{

	switch (m_ucMode)
	{
	case	RGV_MODE_OFFLINE:		return "OFF";
	case	RGV_MODE_AUTO:			return "자동";
	case	RGV_MODE_MANUAL:		return "수동";
	}

	CString strTemp;
	strTemp.Format("이상모드[%c]", m_ucMode);
	return strTemp;
}

CString CRgvInfo::GetActiveString()
{
	switch (m_ucActive)
	{
	case	RGV_ACTIVE:		return "ACTIVE";
	case	RGV_STOP:		return "STOP";
	}

	CString strTemp;
	strTemp.Format("이상 (%c)", m_ucActive);
	return strTemp;
}

CString CRgvInfo::GetProdLoadString()
{
	switch(m_ucProdLoad)
	{
	case	RGV_PROD_EMPTY:		return "화물무";
	case	RGV_PROD_LOAD:		return "화물유";
	}

	return "";
}

CString CRgvInfo::GetCompleteString()
{
	switch ( m_ucTransaction )
	{
	case	RGV_TRN_DOING:		return "작업중";
	case	RGV_TRN_COMPLETE:	return "완료";
	}

	return "";
}

CString CRgvInfo::GetRgvStatusString()
{
	switch (m_ucStatus)
	{
	case	RGV_STA_WAIT:		return "대기(Wait)";
	case	RGV_STA_IDLE:		return "대기(Idle)";
	case	RGV_STA_MOVE:		return "이동";
	case	RGV_STA_ERROR:		return "에러";
	}

	CString strTemp;
	strTemp.Format("이상상태[%c]", m_ucStatus);
	return strTemp;
}

int CRgvInfo::GetID()
{
	return RGV_CNT > m_nNum ? m_nNum : m_nNum-RGV_CNT;
}

CString CRgvInfo::GetRgvJobTypeString()
{
	switch (m_ucInternalJobType)
	{
	case	RGV_JOB_TYPE_ANY:				return "";
	case	RGV_JOB_TYPE_CALL_TO_HOME:		return "홈 복귀";
	case	RGV_JOB_TYPE_MANUAL:			return "수동작업";

	case	RGV_JOB_TYPE_STORE:			return CString("UNIT 입고");
	case	RGV_JOB_TYPE_RETRIEVE:			return CString("UNIT 출고");
	case	RGV_JOB_TYPE_RACK_TO_RACK:		return CString("랙투랙");
	case	RGV_JOB_TYPE_SITE_TO_SITE:		return CString("작업대 이동");
	case	RGV_JOB_TYPE_AISLE_TO_AISLE:	return CString("창고간 이동");

	case	JOB_TYPE_MANUAL_STO:		return CString("반자동 입고");
	case	JOB_TYPE_MANUAL_RET:		return CString("반자동 출고");
	case	JOB_TYPE_MANUAL_RTR:		return CString("반자동 랙투랙");
	case	JOB_TYPE_MANUAL_STN_TO_STN:		return CString("반자동 작업대 이동");

	}
	
	CString strTemp;
	strTemp.Format("작업구분[%d] 이상", m_ucInternalJobType);
	return strTemp;

}

CString CRgvInfo::GetStartTrackString()
{
	CString strTemp;
	strTemp.Format("CV#%d", m_nStartTrack+1);
	return strTemp;
}

CString CRgvInfo::GetDestTrackString()
{
	CString strTemp;
	strTemp.Format("CV#%d", m_nDestTrack+1);
	return strTemp;
}

CString CRgvInfo::GetHorizontalPosString()
{
	CString strTemp;
	strTemp.Format("%d", m_ucHorizontalPos);
	return strTemp;
}

CString CRgvInfo::GetRgvErrorString()
{
	switch ( m_wErrCode )
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
	case	96:		return "드라이브이상(주행)";

	case	99:		return "아나로그출력 유닛이상";

	case	101:	return "작업실행시 전체학습 미완료";

	case	124:	return "주행출력 연산에러";
	case	125:	return "목적지 연산에러";
	case	126:	return "주행감석 감속거리 연산에러";

	case	127:	return "CV 출력 연산에러";
	case	128:	return "목적지 연산에러";
	case	129:	return "주행감속거리 등속 연산에러";

	case	151:	return "시스템파라미터이상";
	case	152:	return "주행 파라미터이상";	case	154:	return "CV 파라미터이상";

	case	161:	return "주행엔코더 회전방향 이상";
	case	162:	return "주행엔코더 가산데이터 미달";
	case	163:	return "주행엔코더 가산데이터 오버";
	case	164:	return "주행엔코더 입력데이터 이상";

	case	RGV_ERR_CODE_COMM_ERROR:
		return	"지상반 응답없슴. 통신두절";
	}

	return "기타 에러[RGV 메뉴얼참조]";

}

BOOL CRgvInfo::Restore()
{
	if(!CInfo::Restore())
	{
		LOG_ERROR(LOG_POS_RGV, LOG_SYSTEM, CString("CRgvInfo::Restore.. RTV ") + m_strErrMsg);
		return FALSE;
	}

	return TRUE;
}

BOOL CRgvInfo::Backup()
{
	if(!CInfo::Backup())
	{
		LOG_ERROR(LOG_POS_RGV, LOG_SYSTEM, CString("CRgvInfo::Backup.. RTV ") + m_strErrMsg);
		return FALSE;
	}

	return TRUE;
}


