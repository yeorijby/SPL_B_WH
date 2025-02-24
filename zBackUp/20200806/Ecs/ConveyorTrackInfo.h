// CvTrackInfo.h : Defines the class behaviors for the application.

#ifndef __CVTRACKINFO_H__
#define __CVTRACKINFO_H__

class CConveyorTrackInfo
{
// constructor & destructor
public:
	CConveyorTrackInfo();
	~CConveyorTrackInfo();

// Attributes
	BOOL m_bModified;

	int m_nLuggNum;
	int m_nLuggNum2;
	int m_nJobType;
	int m_nStartPos;
	int	m_nDestPos;
	int m_nHeight;
	int m_nBatchNum;

	int m_nLastPallet;

	BOOL m_bOverTimeErr;
	BOOL m_bOverLoadErr;
	BOOL m_bSensorOn;
	BOOL m_bSensorFull;
	BOOL m_bHomeStandReady;
	BOOL m_bBuffTrouble;

	BOOL m_bConfirmed;

	BOOL m_bStoStationReady;
	BOOL m_bRetStationReady;
	BOOL m_bPickingStationReady;
	BOOL m_bStoHomeStandReady;
	BOOL m_bRetHomeStandReady;
	BOOL m_bHeightErr;

	BOOL m_bOpMode;
	int  m_nComplete;
    int  m_nSize;
	BOOL m_bHomeStandUp;
	BOOL m_bPltSensor;
	BOOL m_bSizeCheck;
	BOOL m_bError;
	
	int  m_nMotorRun1;
	int  m_nMotorRun2;
	WORD m_wErrorCode;
	WORD m_wStatus;

	WORD m_wPlcCount;

	BOOL m_bDiverterUp;
	BOOL m_bDoorOpen;
	BOOL m_bRgvInterLock;
	BOOL m_bScInterLock;
	BOOL m_bDoorCloseRequest;
	BOOL m_bDoorOpenRequest;
	BOOL m_bRgvInterLockOut;
	BOOL m_bScInterLockOut;

	BOOL m_bWrapSignalIn1;
	BOOL m_bWrapSignalIn2;
	BOOL m_bWrapSignalIn3;
	BOOL m_bWrapSignalIn4;

	BOOL m_bWrapSignalOut1;
	BOOL m_bWrapSignalOut2;
	BOOL m_bWrapSignalOut3;
	BOOL m_bWrapSignalOut4;


// operations
public:

// Implementation
public:
	BOOL m_bCinfirmed;
};

class COpBoxInfo 
{
// constructor & destructor
public:
	COpBoxInfo();
	~COpBoxInfo();

// Attributes
	BOOL m_bModified;
	BOOL m_bAutoMode;
	BOOL m_bNormalStatus;

// operations
public:

// Implementation
public:
};

/*
class CBcrInfo 
{
// constructor & destructor
public:
	CBcrInfo();
	~CBcrInfo();

// Attributes
	uchar m_ucMode;
	BOOL  m_bModified;
	BOOL  m_bStatus;
	
// operations
public:

// Implementation
public:
};
*/

#endif // __CVTRACKINFO_H__
