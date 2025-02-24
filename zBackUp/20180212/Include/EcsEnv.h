// Ecs common environment define section

#ifndef __ECSENV_H__
#define	__ECSENV_H__

#define ECS_ENV_FILE			".\EcsEnv.ini"

#define	STX				0x02
#define	ETX				0x03
#define	EOT				0x04
#define	ENQ				0x05
#define	ACK				0x06
#define	NAK				0x15
#define	CR				0x0d
#define	LF				0x0a

#define ADDR_PLC        0xff
#define ADDR_ECS        0x64

#define	MANIO_FILE		"..\\log\\OfflineJob.dat"

enum EMouseStatus { Up, Down };
enum EButtonStatus { Set, Release };
enum EDirection { Undecided, HorizontalLeft, HorizontalRight, VerticalTop, VerticalBottom };
enum EStackerType { SingleFork, TwinFork, DoubleReach };

#define BLACK					RGB(  0,  0,  0)
#define BLUE					RGB(  0,  0,255)
#define GREEN					RGB(  0,255,  0)
#define CYAN					RGB(  0,255,255)
#define RED						RGB(255,  0,  0)
#define MAGENTA					RGB(255,  0,255)
#define YELLOW					RGB(255,255,  0)
#define SITE					RGB(128,  0,255)
#define WHITE					RGB(255,255,255)
#define DARK_BLUE				RGB(  0,  0,128)
#define DARK_GREEN				RGB(  0,128,  0)
#define DARK_CYAN				RGB(  0,128,128)
#define DARK_RED				RGB(128,  0,  0)
#define DARK_MAGENTA			RGB(128,  0,128)
#define DARK_YELLOW				RGB(128,128,  0)
#define DARK_GRAY				RGB(128,128,128)
#define LIGHT_BLUE				RGB(  0,  0,192)
#define LIGHT_GREEN				RGB(  0,192,  0)
#define LIGHT_CYAN				RGB(  0,192,192)
#define LIGHT_RED				RGB(192,  0,  0)
#define LIGHT_MAGENTA			RGB(192,  0,192)
#define LIGHT_YELLOW			RGB(192,192,  0)
#define LIGHT_GRAY				RGB(192,192,192)
#define PALE_GRAY				RGB(220,220,220)

//#define DEF_RACK_COLOR			RGB(128, 192, 192)
#define DEF_CONVEYOR_COLOR		LIGHT_GRAY

#define	ID_MAIN_TIMER			100
#define	ID_LOGO_TIMER			101
#define	ID_JOB_TIMER			102
#define	ID_STACKER_TIMER		103
#define	ID_RGV_TIMER			104
#define ID_WRAPING_TIMER		105

typedef unsigned char			uchar;

#define	STX						0x02
#define	ETX						0x03

#define ERR_PORT_NOT_OPEN		-1
#define ERR_INIT_FAIL			-2

#define NOTIFY_REFRESH			1
#define NOTIFY_SEND				2
#define NOTIFY_RECEIVE 			3
#define NOTIFY_ERROR			4

#define COMM_STA_STOP			1
#define COMM_STA_SEND			2
#define COMM_STA_RECEIVE		3

#define CMD_STORE				0
#define CMD_RETRIEVE			1
#define CMD_BYPASS				2
#define CMD_RACK_TO_RACK		3

#define	JOB_DEST_POS_CNT		6

#define MAX_FRAME_LEN			100

#define BLOCK_LOWEST			0
#define BLOCK_LOW				1
#define BLOCK_HIGH				2
#define BLOCK_HIGHEST			3
#define BLOCK_CNT				4

#define TURN_NONE				2
#define TURN_LEFT				1
#define TURN_RIGHT				0
#define TURN_CNT				3

#define CMD_ORDER				'O'
#define CMD_ORDER_ANSWER		'o'
#define CMD_CANCEL				'D'
#define CMD_CANCEL_ANSWER		'd'
#define CMD_STATUS				'S'
#define CMD_STATUS_ANSWER		's'
#define CMD_CHANGE				'C'
#define CMD_CHANGE_ANSWER		'c'
#define CMD_ERROR				'E'
#define CMD_ERROR_ANSWER		'e'
#define CMD_COMPLETE			'F'
#define CMD_COMPLETE_ANSWER		'f'
#define	CMD_ALT_LOC				'R'
#define	CMD_ALT_LOC_ANSWER		'r'
#define	CMD_LOAD_ARRV			'A'
#define	CMD_LOAD_ARRV_ANSWER	'a'
#define	CMD_REQ_START			'I'
#define	CMD_REQ_START_ANSWER	'i'
#define	CMD_REQ_PAUSE			'P'
#define	CMD_REQ_PAUSE_ANSWER	'p'
#define	CMD_TIME_SET			'Y'
#define	CMD_TIME_SET_ANSWER		'y'
#define	CMD_THROUGHPUT			'U'
#define	CMD_THROUGHPUT_ANSWER	'u'
#define	CMD_OFFLINE_JOB			'J'
#define	CMD_OFFLINE_JOB_ANSWER	'j'
#define CMD_BCRJOB				'Q'
#define CMD_BCRJOB_ANSWER		'q'
#define CMD_BATCH				'K'
#define CMD_BATCH_ANSWER		'k'

#define	CMD_UNPREDICT			'X'

#define CMD_MODIFY				0
#define CMD_FINISH				2
#define CMD_RETRY				3
#define CMD_ARRIVE				6

#define	CMD_ON_OFFLINE_CHART	1
#define	CMD_ONLINE_CHART		2
#define	CMD_OFFLINE_CHART		3
#define	CMD_RATIO_CHART			4
#define	CMD_COUNT_CHART			5

#define CANCEL_REASON_INTERNAL	1
#define CANCEL_REASON_HARDWARE	2

#define	JOB_TYPE_ALL						0
#define	JOB_TYPE_UNIT_STO					1
#define	JOB_TYPE_UNIT_RET					2
#define	JOB_TYPE_PICK_REPLENISH				3
#define	JOB_TYPE_RACK_TO_RACK				4
#define	JOB_TYPE_AISLE_TO_AISLE				5
#define	JOB_TYPE_STN_TO_STN					6

#define	JOB_TYPE_MANUAL_STO					7
#define	JOB_TYPE_MANUAL_RET					8
#define	JOB_TYPE_MANUAL_RTR			        9
#define JOB_TYPE_MANUAL_STN_TO_STN 			10
#define	JOB_TYPE_CNT						11

#define	HOST			m_pDoc->m_pHostCl
#define LGV				m_pDoc->m_pLgvSocket
#define	JOB				m_pDoc->m_pJob
#define	MOVEJOB			m_pDoc->m_pMoveJob
#define	REPORT			m_pDoc->m_pReportJob
#define	ROUTING			m_pDoc->m_pJobRouting
#define CONFIG			m_pDoc->m_pConfig

#define STATISTIC		m_pDoc->m_pStatistic
#define LOG_JOB			m_pDoc->m_pLog->Job
#define LOG_DEBUG		m_pDoc->m_pLog->Debug
#define LOG_ERROR       m_pDoc->m_pLog->Error
#define LOG_EVENT       m_pDoc->m_pLog->Event

typedef struct _SORT_PARAMS
{
	HWND	hWnd;
	int		nCol;
	BOOL	bAscend;
}SORT_PARAMS, *PSORT_PARAMS;

/*
#define	JOB_TYPE_UNIT_STO					1
#define	JOB_TYPE_UNIT_RET					2
#define	JOB_TYPE_PICK_REPLENISH				3
#define	JOB_TYPE_RACK_TO_RACK				4
#define	JOB_TYPE_AISLE_TO_AISLE				5
#define	JOB_TYPE_SITE_TO_SITE				6
#define	JOB_TYPE_MANUAL_STO					7
#define	JOB_TYPE_MANUAL_RET					8
#define	JOB_TYPE_MANUAL_RTR					9
*/

#define	JOB_AISLE_1							10
#define	JOB_AISLE_2							11
#define	JOB_AISLE_3							12
#define	JOB_AISLE_4							13

#define JOB_STA_PROGRESS				-1
#define	JOB_STA_ALL						0
#define JOB_STA_NEW						1
#define JOB_STA_CV_NEW					2
#define JOB_STA_ERR						3
#define JOB_STA_SC_OPER_REQUEST			4
#define JOB_STA_SC_OPER_INVOKE			5
#define JOB_STA_CV_OPER_REQUEST			6
#define JOB_STA_CV_OPER_INVOKE			7
#define JOB_STA_CV_MOVE_RET_STATION		8
#define JOB_STA_COMPLETE_REQUEST		9
#define JOB_STA_COMPLETE				10
#define JOB_STA_ERR_DUAL_STO_REQUEST	11
#define JOB_STA_ERR_DUAL_STO			12
#define	JOB_STA_DUAL_STO_RETRY			13
#define JOB_STA_ERR_EMPTY_RET_REQUEST	14
#define JOB_STA_ERR_EMPTY_RET			15
#define	JOB_STA_EMPTY_RET_RETRY			16
#define	JOB_STA_DUAL_RTR_RETRY			17
#define	JOB_STA_EMPTY_RTR_RETRY			18
#define JOB_STA_REFUSE_COMPLETE			19
#define JOB_STA_REFUSE_ARRIVED			20
#define JOB_STA_REFUSE_CANCEL			21
#define	JOB_STA_REFUSE_ERROR			22
#define	JOB_STA_ERR_REPORT	    		23
#define JOB_STA_CNT						24


#define JOB_STA_MOVE_PROGRESS					-1
#define	JOB_STA_MOVE_ALL						0
#define JOB_STA_MOVE_NEW						1
#define JOB_STA_MOVE_CV_NEW						2
#define JOB_STA_MOVE_ERR						3
#define JOB_STA_MOVE_CV_OPER_REQUEST			4
#define JOB_STA_MOVE_CV_OPER_INVOKE				5
#define JOB_STA_MOVE_RGV_OPER_REQUEST			6
#define JOB_STA_MOVE_RGV_OPER_INVOKE			7
#define JOB_STA_MOVE_RGV_OPER_COMPLETE			8
#define JOB_STA_MOVE_COMPLETE_REQUEST			9
#define JOB_STA_MOVE_COMPLETE					10
#define JOB_STA_MOVE_REFUSE_COMPLETE			11
#define JOB_STA_MOVE_REFUSE_ARRIVED				12
#define JOB_STA_MOVE_REFUSE_CANCEL				13
#define	JOB_STA_MOVE_REFUSE_ERROR				14
#define JOB_STA_MOVE_CNT						15


//  Error Message Code
#define	RECEIVE_OK						0
#define	MSG_NO_ERROR					0
#define	MSG_NO_STX						1
#define	MSG_NO_ETX						2
#define	MSG_LUGG_NO_DUPLICATED			3
#define	MSG_NO_EXIST_JOB				4
#define	MSG_ECS_BUFFER_FULL				5
#define	MSG_INVALID_HEADER_LENG			6
#define	MSG_INVALID_MSG_LENG			7
#define	MSG_INVALID_LOC					8
#define	MSG_INVALID_STN_NO				9
#define	MSG_INVALID_LUGG_NO				10
#define	MSG_UNKNOWN_JOB_TYPE			11
#define	MSG_INHIBITED_LOC				12
#define	MSG_INVALID_MAILBOX_NAME		13
#define	MSG_ALREADY_INVOKED_JOB			14
#define	MSG_INVALID_CONTENT				15	
#define	MSG_UNKNOWN_MSG_TYPE			16	
#define	MSG_IMPROPER_HANDSHAKE			17
#define	MSG_NO_RESPONSE					18
#define	MSG_SOCKET_ERROR				19
#define	MSG_INTERNAL_ERROR				99

#define	MSG_LENGTH_HEADER				15
#define	MSG_LENGTH_RESPONSE_DATA		14
#define	MSG_LENGTH_RESPONSE_MSG			(MSG_LENGTH_HEADER + MSG_LENGTH_RESPONSE_DATA)
#define	MSG_LENGTH_COMPLETE_DATA		10
#define	MSG_LENGTH_COMPLETE_MSG			(MSG_LENGTH_HEADER + MSG_LENGTH_COMPLETE_DATA)
#define	MSG_LENGTH_ARRIVAL_DATA			16
#define	MSG_LENGTH_ARRIVAL_MSG			(MSG_LENGTH_HEADER + MSG_LENGTH_ARRIVAL_DATA)
#define	MSG_LENGTH_ERROR_DATA			23
#define	MSG_LENGTH_ERROR_MSG			(MSG_LENGTH_HEADER + MSG_LENGTH_ERROR_DATA)
#define	MSG_LENGTH_CANCEL_DATA			8
#define	MSG_LENGTH_CANCEL_MSG			(MSG_LENGTH_HEADER + MSG_LENGTH_CANCEL_DATA)

//  STX(1) + MsgType(1) + (7 * SC_CNT) + ECS_STN_CNT(4) + ETX(1)
#define	MSG_LENGTH_STATUS_DATA			73
#define	MSG_LENGTH_STATUS_MSG			(MSG_LENGTH_HEADER + MSG_LENGTH_STATUS_DATA)

//  STX(1) + MsgType(1) + Date(8) + Time(6) +(27 * SC_CNT) + ETX(1)
#define	MSG_LENGTH_THROUGHPUT_DATA		75
#define	MSG_LENGTH_THROUGHPUT_MSG		(MSG_LENGTH_HEADER + MSG_LENGTH_THROUGHPUT_DATA)
//	Lugg(4) + JobClass(1) + Loc1(7) + Loc2(7) + Product(20) + Qty(15) + Date(8) + Time(6) + TxFlag(2) + CRLF(2)
#define	MSG_LENGTH_OFFJOB_DATA			72
#define	MSG_LENGTH_OFFJOB_MSG			(MSG_LENGTH_HEADER + MSG_LENGTH_OFFJOB_DATA)

#define	MSG_LENGTH_BCRJOB_DATA			27
#define	MSG_LENGTH_BCRJOB_MSG			(MSG_LENGTH_HEADER + MSG_LENGTH_BCRJOB_DATA)

#define	JOB_PATTERN_STO					0
#define	JOB_PATTERN_RET					1
#define	JOB_PATTERN_RTR					2
#define	JOB_PATTERN_CIRCULATION			3
#define	JOB_PATTERN_MOVE				4
#define JOB_PATTERN_SITE				5
#define	JOB_PATTERN_CNT					6


#define	STO_JOB							0
#define	RET_JOB							1
#define	SRET_JOB						2

#define	JOB_SORT_ASC					1
#define	JOB_SORT_DESC					2

#define JOB_PRI_DEF						100

#define JOB_ERR_NONE					0

#define CV_TRACK_NORMAL					0
#define CV_TRACK_ERROR					1

#define OPBOX_MODE_AUTO					1
#define OPBOX_MODE_MANUAL				2
#define OPBOX_STA_EMERGENCY				3
#define OPBOX_STA_NORMAL				4

#define BCR_MODE_ERROR					0
#define BCR_MODE_AUTO					1
#define BCR_MODE_MANUAL					2

#define	SC_JOB_TYPE_ANY					'0'
#define SC_JOB_TYPE_STORE				'1'
#define SC_JOB_TYPE_RETRIEVE			'2'
#define SC_JOB_TYPE_RACK_TO_RACK		'3'
#define SC_JOB_TYPE_HS_TO_HS			'4'
#define SC_JOB_TYPE_CALL_TO_HOME		'5'
#define SC_JOB_TYPE_SITE_TO_SITE		'6'
#define SC_JOB_TYPE_MANUAL				'9'

#ifdef OPT_SC_PLC_TYPE_USE

#define SC_MODE_AUTO					'1'
#define SC_MODE_SEMI_AUTO				'2'
#define SC_MODE_MANUAL					'3'

#define SC_MODE_ONLINE					'2'
#define SC_MODE_REMOTE					'1'
#define SC_MODE_OFFLINE					'4'

#define SC_TRN_COMPLETE					'1'
#define SC_TRN_DOING					'0'

#define SC_PROD_LOAD					'1'
#define SC_PROD_EMPTY					'0'

#define SC_STA_WAIT						'0'
#define SC_STA_IDLE						'1'
#define SC_STA_MOVE						'2'
#define SC_STA_ERROR					'3'
#define SC_STA_ESTOP					'4'
#define SC_STA_MANUAL					'5'

#define SC_DEFAULT_HS_STORE				1
#define SC_DEFAULT_HS_RETRIEVE			2

#define SC_ERR_CODE_DUAL_STORE				63
#define SC_ERR_CODE_DUAL_SECOND_STORE		64
#define SC_ERR_CODE_EMPTY_RETRIEVE			61
#define SC_ERR_CODE_EMPTY_SECOND_RETRIEVE	62
#define SC_ERR_CODE_COMM_ERROR				99
 
#endif

#ifdef OPT_SC_MELSEC_TYPE_USE

#define SC_MODE_OFFLINE					'0'
#define SC_MODE_REMOTE					'1'
#define SC_MODE_ONLINE					'2'

#define SC_MODE_AUTO					'1'
#define SC_MODE_MANUAL					'2'

#define SC_FORK_POS_CENTER				'0'
#define SC_FORK_POS_LEFT				'1'
#define SC_FORK_POS_RIGHT				'2'

#define SC_DUAL_STO_READY				'3'
#define SC_EMPTY_RET_READY				'5'

#define SC_STOP							'0'
#define SC_ACTIVE						'1'

#define SC_TRN_DOING					'0'
#define SC_TRN_COMPLETE_FORK1			'1'
#define SC_TRN_COMPLETE_FORK2			'2'
#define SC_TRN_COMPLETE_FORK12			'3'

#define SC_PROD_LOAD					'1'
#define SC_PROD_EMPTY					'0'

#define SC_STA_WAIT						'0'
#define SC_STA_IDLE						'1'
#define SC_STA_MOVE						'2'
#define SC_STA_ERROR					'4'
#define SC_STA_ESTOP					'5'
#define SC_STA_MANUAL					'6'

#define SC_DEFAULT_HS_STORE				1
#define SC_DEFAULT_HS_RETRIEVE			2

#define SC_ERR_STATUS_DUAL_STORE_NOREADY		'2'
#define SC_ERR_STATUS_EMPTY_RETRIEVE_NOREADY	'4'
#define SC_ERR_STATUS_DUAL_STORE_READY			'3'
#define SC_ERR_STATUS_EMPTY_RETRIEVE_READY		'5'

#define SC_ERR_CODE_DUAL_STORE				54
#define SC_ERR_CODE_DUAL_SECOND_STORE		55
#define SC_ERR_CODE_EMPTY_RETRIEVE			58
#define SC_ERR_CODE_EMPTY_SECOND_RETRIEVE	59
#define SC_ERR_CODE_COMM_ERROR				999

#define SC_JOB_TYPE_MANUAL                  '9'
 
#endif

#ifdef OPT_SC_BOARD_TYPE_USE

#define SC_MODE_AUTO					'1'
#define SC_MODE_SEMI_AUTO				'2'
#define SC_MODE_MANUAL					'3'

#define SC_MODE_ONLINE					'2'
#define SC_MODE_REMOTE					'1'
#define SC_MODE_OFFLINE					'4'

#define SC_TRN_COMPLETE					0x55
#define SC_TRN_DOING					0

#define SC_PROD_LOAD					'1'
#define SC_PROD_EMPTY					'0'

#define SC_STA_WAIT						3		// empty
#define SC_STA_IDLE						0		// initial state
#define SC_STA_MOVE						0xaa	// working
#define SC_STA_ESTOP					'4'
#define SC_STA_MANUAL					'5'
#define SC_STA_ERROR					0xee

#define SC_DEFAULT_HS_STORE				1
#define SC_DEFAULT_HS_RETRIEVE			2

#define SC_ERR_CODE_DUAL_STORE				0x8003
#define SC_ERR_CODE_DUAL_SECOND_STORE		0x8009
#define SC_ERR_CODE_EMPTY_RETRIEVE			0x8001
#define SC_ERR_CODE_EMPTY_SECOND_RETRIEVE	0x8006
#define	SC_ERR_CODE_EMTPY_RETRIEVE_ALL		0x8013
#define SC_ERR_CODE_COMM_ERROR				99
 
#endif

#ifdef OPT_SC_DONGJIN_USE

#define SC_MODE_REMOTE					'C'
#define SC_MODE_OFFLINE					'B'
#define SC_MODE_ONLINE					'C'

#define SC_TRN_COMPLETE					'1'
#define SC_TRN_DOING					'0'

#define SC_PROD_LOAD					'1'
#define SC_PROD_EMPTY					'0'

#define SC_STA_WAIT						'0'
#define SC_STA_IDLE						'1'
#define SC_STA_MOVE						'2'
#define SC_STA_ERROR					'3'
#define SC_STA_ESTOP					'4'
#define SC_STA_MANUAL					'5'

#define SC_ERR_CODE_DUAL_STORE			41
#define SC_ERR_CODE_EMPTY_RETRIEVE		42
#define SC_ERR_CODE_DATA_ERROR			51
#define SC_ERR_CODE_COMM_ERROR			99

#define SC_DEFAULT_HS_STORE				1
#define SC_DEFAULT_HS_RETRIEVE			2

#endif

#ifdef OPT_SC_SHINHUNG_USE

#define SC_FORK_POS_CENTER				0
#define SC_FORK_POS_RIGHT				1
#define SC_FORK_POS_LEFT				2

#define SC_MODE_MANUAL					'0'
#define SC_MODE_SEMI_AUTO				'1'
#define SC_MODE_AUTO					'2'
#define SC_MODE_REMOTE					'3'

#define SC_TRN_COMPLETE					'1'
#define SC_TRN_DOING					'0'

#define SC_PROD_LOAD					'1'
#define SC_PROD_EMPTY					'0'

#define SC_STA_WAIT						'0'
#define SC_STA_IDLE						'1'
#define SC_STA_MOVE						'2'
#define SC_STA_ERROR					'3'
#define SC_STA_ESTOP					'4'
#define SC_STA_MANUAL					'5'

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^ s/c에 write할때의 값, 2이면 출고 h/s에 화물을 뺌
#define SC_DEFAULT_HS_STORE				1
#define SC_DEFAULT_HS_RETRIEVE			1
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#define SC_ERR_CODE_EMPTY_RETRIEVE			1501
#define SC_ERR_CODE_DUAL_STORE				1101
#define SC_ERR_CODE_DUAL_SECOND_STORE		64
#define SC_ERR_CODE_EMPTY_SECOND_RETRIEVE	62
#define SC_ERR_CODE_COMM_ERROR				99
 
#endif

#define ROUTINE_STORE					1
#define ROUTINE_SITE_STORE				2
#define ROUTINE_RETRIEVE				3
#define ROUTINE_SITE_RETRIEVE			4
#define ROUTINE_RACK_TO_RACK			5
#define ROUTINE_CALL_TO_HOME			6
#define ROUTINE_STO_LOADING				7
#define ROUTINE_RET_LOADING				8
#define ROUTINE_RTR_LOADING				9

#define	DEVICE_CLASS_SC					1
#define	DEVICE_CLASS_CV					2
#define	DEVICE_CLASS_AGV				3
#define	DEVICE_CLASS_RGV				4
#define	DEVICE_CLASS_ROBOT				5
#define	DEVICE_CLASS_BCR				6

#define	MECHANIC_ERROR					0
#define	SC_DUAL_STORE					1
#define	SC_BLOCKED_STORE				2
#define	SC_EMPTY_RETRIEVE				3
#define	SC_BLOCKED_RETRIEVE				4

#define	CV_OVERTIME_ERROR				2
#define	CV_OVERLOAD_ERROR				3

#define SET(xArg, yArg)	GetDlgItem(xArg)->SetWindowText(yArg)
#define GET(xArg, yArg)	GetDlgItem(xArg)->GetWindowText(yArg)

#define SYS_JOB(xArg)		Job(LOG_POS_SYSTEM, LOG_SYSTEM, xArg)
#define SYS_EVENT(xArg)		Event(LOG_POS_SYSTEM, LOG_SYSTEM, xArg)
#define SYS_ERROR(xArg)		Error(LOG_POS_SYSTEM, LOG_SYSTEM, xArg)

#define HOST_JOB(xArg)		Job(LOG_POS_HOST, LOG_SYSTEM, xArg)
#define HOST_EVENT(xArg)	Event(LOG_POS_HOST, LOG_SYSTEM, xArg)
#define HOST_ERROR(xArg)	Error(LOG_POS_HOST, LOG_SYSTEM, xArg)
#define HOST_DEBUG(xArg)	Debug(LOG_POS_HOST, LOG_SYSTEM, xArg)

#define CV_ACTION(xArg)		m_pDoc->m_nConveyorEventCount[xArg]++; SetEvent(m_pDoc->m_hEventSendConveyor[xArg])
#define DISP_ACTION			m_pDoc->m_nDisplayEventCount++; SetEvent(m_pDoc->m_hEventSendDisplay)
#define SC_ACTION(xArg)		m_pDoc->m_nStackerEventCount[xArg]++; SetEvent(m_pDoc->m_hEventSendStacker[xArg])
#define RGV_ACTION(xArg)	m_pDoc->m_nRgvEventCount[xArg]++; SetEvent(m_pDoc->m_hEventSendRgv[xArg])

#define	RGV_JOB_TYPE_ANY				'0'
#define	RGV_JOB_TYPE_STORE				'1'
#define	RGV_JOB_TYPE_RETRIEVE			'2'
#define RGV_JOB_TYPE_RACK_TO_RACK		'3'
#define RGV_JOB_TYPE_HS_TO_HS			'4'
#define	RGV_JOB_TYPE_SITE_TO_SITE		'5'
#define	RGV_JOB_TYPE_CALL_TO_HOME		'6'
#define RGV_JOB_TYPE_AISLE_TO_AISLE		'7'
#define	RGV_JOB_TYPE_MANUAL				'9'
#ifdef OPT_RGV_PLC_TYPE_USE // 위에 주석이 진짜임 이것은 임시 방편

#define RGV_STOP						'0'
#define RGV_ACTIVE						'1'

#define RGV_MODE_OFFLINE				'0'
#define RGV_MODE_AUTO					'1'
#define RGV_MODE_MANUAL					'2'

#define RGV_MODE_SEMI_AUTO				'3'

#define RGV_PROD_LOAD					'1'
#define RGV_PROD_EMPTY					'0'

#define RGV_STA_WAIT					'0'
#define RGV_STA_IDLE					'1'
#define RGV_STA_MOVE					'2'
#define RGV_STA_ERROR					'4'

#define RGV_STA_ESTOP					'0'
#define RGV_STA_MANUAL					'1'

#define RGV_TRN_DOING					'0'
#define RGV_TRN_COMPLETE				'3'

#define RGV_PROD_LOAD					'1'
#define RGV_PROD_EMPTY					'0'

#define RGV_DEFAULT_HS_STORE			1
#define RGV_DEFAULT_HS_RETRIEVE			2

#define RGV_ERR_CODE_DUAL_STORE				63
#define RGV_ERR_CODE_DUAL_SECOND_STORE		64
#define RGV_ERR_CODE_EMPTY_RETRIEVE			61
#define RGV_ERR_CODE_EMPTY_SECOND_RETRIEVE	62
#define RGV_ERR_CODE_COMM_ERROR				999
 
#endif


#ifdef OPT_RGV_MELSEC_INVERTER_TYPE_USE
#define RGV_MODE_OFFLINE				'0'
#define RGV_MODE_AUTO					'1'
#define RGV_MODE_MANUAL					'2'

#define RGV_STA_WAIT					'0'
#define RGV_STA_IDLE					'1'
#define RGV_STA_MOVE					'2'
#define RGV_STA_ERROR					'4'

#define RGV_STOP						'0'
#define RGV_ACTIVE						'1'

#define RGV_TRN_DOING					'0'
#define RGV_TRN_COMPLETE				'3'

#define RGV_PROD_LOAD					'1'
#define RGV_PROD_EMPTY					'0'

#define RGV_ERR_CODE_COMM_ERROR			999

#endif

#endif // __ECSENV_H__ 
