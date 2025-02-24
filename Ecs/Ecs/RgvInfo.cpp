


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
		strMsg.Format("%s ����.. �����ڵ�[%d] ����[%s]", m_strDevice, m_wErrCode, GetRgvErrorString());
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
	case	RGV_MODE_AUTO:			return "�ڵ�";
	case	RGV_MODE_MANUAL:		return "����";
	}

	CString strTemp;
	strTemp.Format("�̻���[%c]", m_ucMode);
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
	strTemp.Format("�̻� (%c)", m_ucActive);
	return strTemp;
}

CString CRgvInfo::GetProdLoadString()
{
	switch(m_ucProdLoad)
	{
	case	RGV_PROD_EMPTY:		return "ȭ����";
	case	RGV_PROD_LOAD:		return "ȭ����";
	}

	return "";
}

CString CRgvInfo::GetCompleteString()
{
	switch ( m_ucTransaction )
	{
	case	RGV_TRN_DOING:		return "�۾���";
	case	RGV_TRN_COMPLETE:	return "�Ϸ�";
	}

	return "";
}

CString CRgvInfo::GetRgvStatusString()
{
	switch (m_ucStatus)
	{
	case	RGV_STA_WAIT:		return "���(Wait)";
	case	RGV_STA_IDLE:		return "���(Idle)";
	case	RGV_STA_MOVE:		return "�̵�";
	case	RGV_STA_ERROR:		return "����";
	}

	CString strTemp;
	strTemp.Format("�̻����[%c]", m_ucStatus);
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
	case	RGV_JOB_TYPE_CALL_TO_HOME:		return "Ȩ ����";
	case	RGV_JOB_TYPE_MANUAL:			return "�����۾�";

	case	RGV_JOB_TYPE_STORE:			return CString("UNIT �԰�");
	case	RGV_JOB_TYPE_RETRIEVE:			return CString("UNIT ���");
	case	RGV_JOB_TYPE_RACK_TO_RACK:		return CString("������");
	case	RGV_JOB_TYPE_SITE_TO_SITE:		return CString("�۾��� �̵�");
	case	RGV_JOB_TYPE_AISLE_TO_AISLE:	return CString("â�� �̵�");

	case	JOB_TYPE_MANUAL_STO:		return CString("���ڵ� �԰�");
	case	JOB_TYPE_MANUAL_RET:		return CString("���ڵ� ���");
	case	JOB_TYPE_MANUAL_RTR:		return CString("���ڵ� ������");
	case	JOB_TYPE_MANUAL_STN_TO_STN:		return CString("���ڵ� �۾��� �̵�");

	}
	
	CString strTemp;
	strTemp.Format("�۾�����[%d] �̻�", m_ucInternalJobType);
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
	case	96:		return "����̺��̻�(����)";

	case	99:		return "�Ƴ��α���� �����̻�";

	case	101:	return "�۾������ ��ü�н� �̿Ϸ�";

	case	124:	return "������� ���꿡��";
	case	125:	return "������ ���꿡��";
	case	126:	return "���న�� ���ӰŸ� ���꿡��";

	case	127:	return "CV ��� ���꿡��";
	case	128:	return "������ ���꿡��";
	case	129:	return "���న�ӰŸ� ��� ���꿡��";

	case	151:	return "�ý����Ķ�����̻�";
	case	152:	return "���� �Ķ�����̻�";	case	154:	return "CV �Ķ�����̻�";

	case	161:	return "���࿣�ڴ� ȸ������ �̻�";
	case	162:	return "���࿣�ڴ� ���굥���� �̴�";
	case	163:	return "���࿣�ڴ� ���굥���� ����";
	case	164:	return "���࿣�ڴ� �Էµ����� �̻�";

	case	RGV_ERR_CODE_COMM_ERROR:
		return	"����� �������. ��ŵ���";
	}

	return "��Ÿ ����[RGV �޴�������]";

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


