// ConveyorTrackInfo.cpp : implementation of the CConveyorTrackInfo class
//

#include "stdafx.h"
#include "ConveyorTrackInfo.h"

CConveyorTrackInfo::CConveyorTrackInfo()
{
	m_nLuggNum = 0;
	m_nLuggNum2 = 0;
	m_nJobType = -1;
	m_nStartPos = -1;
	m_nDestPos  = -1;
	m_nHeight = -1;
	m_nBatchNum = -1;
	m_bOverTimeErr = FALSE;
	m_bOverLoadErr = FALSE;
	m_bSensorOn = FALSE;
	m_bSensorFull = FALSE;
	m_bHomeStandReady = FALSE;
	m_bConfirmed = FALSE;

	m_nLastPallet = 0;

	m_bBuffTrouble = FALSE;

	m_bStoStationReady = FALSE;
	m_bRetStationReady = FALSE;
	m_bPickingStationReady = FALSE;
	m_bStoHomeStandReady = FALSE;
	m_bRetHomeStandReady = FALSE;
	m_bHeightErr = FALSE;

	m_nSize = 0;
	m_nComplete = 0;
	m_bOpMode = FALSE;
	m_bRgvInterLockOut = FALSE;
	m_bScInterLockOut = FALSE;
	m_bHomeStandUp = FALSE;
	m_bError = FALSE;

	m_nMotorRun1 = 0;
	m_nMotorRun2 = 0;
	m_wErrorCode = 0;

	m_wPlcCount = 0;
	m_wStackLevel = 0;

	m_bPltSensor = FALSE;
	m_bDiverterUp = FALSE;
	m_bDoorOpen = FALSE;
	m_bRgvInterLock = FALSE;
	m_bScInterLock = FALSE;
	m_bDoorCloseRequest = FALSE;
	m_bDoorOpenRequest = FALSE;
	m_bSizeCheck = FALSE;

	m_bWrapSignalIn1 = FALSE;
	m_bWrapSignalIn2 = FALSE;
	m_bWrapSignalIn3 = FALSE;
	m_bWrapSignalIn4 = FALSE;

	m_bWrapSignalOut1 = FALSE;
	m_bWrapSignalOut2 = FALSE;
	m_bWrapSignalOut3 = FALSE;
	m_bWrapSignalOut4 = FALSE;
}

CConveyorTrackInfo::~CConveyorTrackInfo()
{
}

COpBoxInfo::COpBoxInfo()
{
	m_bAutoMode = FALSE;
	m_bNormalStatus = FALSE;
}

COpBoxInfo::~COpBoxInfo()
{
}

/*
CBcrInfo::CBcrInfo()
{
	m_bStatus = FALSE;
}

CBcrInfo::~CBcrInfo()
{
}
*/
