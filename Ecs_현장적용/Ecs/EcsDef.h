// Global Define Value for Samsung Electronics

#ifndef __GLX_DEFINE_H__
#define __GLX_DEFINE_H__

//#define OPT_HOST_SAP_INTERFACE_USE
//#define OPT_SC_BOARD_TYPE_USE
//#define OPT_HOST_SERIAL_INTERFACE_USE
//#define OPT_COMM_OPEN_ERROR_DISPLAY_USE
//#define OPT_RACK_TO_RACK_USE
#define OPT_HOST_NETWORK_INTERFACE_USE
//#define OPT_SC_PLC_TYPE_USE
#define OPT_SC_MELSEC_TYPE_USE
#define	OPT_PASSWORD_USE

//#define OPT_RGV_PLC_TYPE_USE
#define OPT_RGV_MELSEC_INVERTER_TYPE_USE


#define TEST_MODE

#define SC_1_CNT				6
#define	BANK_1_CNT				12
#define	BAY_1_CNT				117
#define	LEVEL_1_CNT				8
#define FORK_1_SIZE				9
#define MAX_DISPLAY_1_POS		117

#define SC_2_CNT				0
#define	BANK_2_CNT				0
#define	BAY_2_CNT				0
#define	LEVEL_2_CNT				0
#define FORK_2_SIZE				0
#define MAX_DISPLAY_2_POS		0

#define OPBOX_1_CNT				5
#define OPBOX_2_CNT				13
#define OPBOX_3_CNT				3
#define OPBOX_4_CNT				2
#define OPBOX_5_CNT				2
#define OPBOX_6_CNT				2

#define STO_HS_1_CNT			6
#define STO_HS_2_CNT			0

#define RET_HS_1_CNT			12
#define RET_HS_2_CNT			4

#define SC_CNT					(SC_1_CNT + SC_2_CNT)
#define	BANK_CNT				(BANK_1_CNT + BANK_2_CNT)
#define	BAY_CNT					117
#define	LEVEL_CNT				8
#define FORK_SIZE				9
#define MAX_DISPLAY_POS			117

#define RGV_1_NUM				0
#define RGV_2_NUM				1
#define RGV_CNT					2

#define CV_1_TRACK_CNT			74  //126
#define CV_2_TRACK_CNT			151 //146 //140 //160 //73
#define CV_3_TRACK_CNT			49
#define CV_4_TRACK_CNT			86
#define CV_5_TRACK_CNT			86
#define CV_6_TRACK_CNT			82
#define CV_7_TRACK_CNT			137 //122
#define CV_8_TRACK_CNT			24 //23
#define CV_9_TRACK_CNT			220 
#define CV_TRACK_CNT			(CV_1_TRACK_CNT + CV_2_TRACK_CNT + CV_3_TRACK_CNT + CV_4_TRACK_CNT + CV_5_TRACK_CNT + CV_6_TRACK_CNT + CV_7_TRACK_CNT + CV_8_TRACK_CNT + CV_9_TRACK_CNT)

#define CV_1_START_TRACK				0
#define CV_2_START_TRACK				900
#define CV_3_START_TRACK				300
#define CV_4_START_TRACK				400
#define CV_5_START_TRACK				500
#define CV_6_START_TRACK				600
#define CV_7_START_TRACK				700
#define CV_8_START_TRACK				2000
#define CV_9_START_TRACK				2100

#define CV_TRACKING_ST_STO		0
#define CV_TRACKING_ED_STO		37
#define CV_TRACKING_ST_RET1		38
#define CV_TRACKING_ED_RET1		69
#define CV_TRACKING_ST_RET2		110
#define CV_TRACKING_ED_RET2		114
#define CV_TRACKING_PT_RET		103
#define CV_NONTRACKING_ST1		70
#define CV_NONTRACKING_ED1		101
#define CV_NONTRACKING_ST2		104
#define CV_NONTRACKING_ED2		109

#define OPBOX_CNT				(OPBOX_1_CNT + OPBOX_2_CNT + OPBOX_3_CNT + OPBOX_4_CNT + OPBOX_5_CNT + OPBOX_6_CNT)

#define STO_HS_CNT				6
#define RET_HS_CNT				6

#define CV_1_PLC				0
#define	CV_2_PLC				1
#define	CV_3_PLC				2
#define CV_4_PLC				3
#define	CV_5_PLC				4
#define	CV_6_PLC				5
#define	CV_7_PLC				6
#define	CV_8_PLC				7
#define	CV_9_PLC				8
#define CV_PLC_CNT				9

#define	SC_ERROR_KIND_CNT		100

#define	NORMAL_PRIORITY			100
#define	URGENT_PRIORITY			150

#define RGV_LOADING_HS_1_CNT		10
#define RGV_LOADING_HS_2_CNT		9 

#define RGV_UNLOADING_HS_1_CNT		5 //3
#define RGV_UNLOADING_HS_2_CNT		6 //8

#define RGV_STO_LOADING_HS_1_CNT	11
#define RGV_STO_LOADING_HS_2_CNT	2 

#define RGV_RET_LOADING_HS_1_CNT	7
#define RGV_RET_LOADING_HS_2_CNT	1 

//IMS<->ECS Station Number
#define IMS_ECS_STO_STATION_100			100
#define IMS_ECS_STO_STATION_101			101
#define IMS_ECS_STO_STATION_102			102
#define IMS_ECS_STO_STATION_103			103
#define IMS_ECS_RET_STATION_200			200
#define IMS_ECS_RET_STATION_201			201
#define IMS_ECS_RET_STATION_202			202
#define IMS_ECS_RET_STATION_203			203
#define IMS_ECS_RET_STATION_204			204
#define IMS_ECS_RET_STATION_251			251
#define IMS_ECS_RET_STATION_255			255
#define IMS_ECS_RET_STATION_256			256
#define IMS_ECS_RET_STATION_257			257

//ECS<->PLC Station Number
#define CV_POS_HS_1						1
#define CV_POS_HS_2						2
#define CV_POS_HS_3						3
#define CV_POS_HS_4						4
#define CV_POS_HS_5						5
#define CV_POS_HS_6						6

#define CV_STO_STATION_1				1
#define CV_STO_STATION_2				2

#define CV_RET_STATION_4GROUP			1
#define CV_RET_STATION_5GROUP			2
#define CV_RET_STATION_6GROUP			3
#define CV_RET_STATION_2				7

#define	ECS_POS_HS_1					1
#define	ECS_POS_HS_2					2
#define	ECS_POS_HS_3					3
#define	ECS_POS_HS_4					4
#define	ECS_POS_HS_5					5
#define	ECS_POS_HS_6					6
#define	ECS_POS_HS_CNT					6



#define ECS_STO_POS_1					21
#define ECS_STO_POS_2					9
#define ECS_STO_POS_3					10
#define	ECS_STO_POS_CNT					2

#define ECS_RET_POS_1					31
#define ECS_RET_POS_2					32
#define	ECS_RET_POS_CNT					2

#define ECS_PICK_POS_1					41
#define	ECS_PICK_POS_CNT				0

#define	ECS_STO_STN_CNT					( ECS_STO_POS_CNT + ECS_PICK_POS_CNT )
#define	ECS_RET_STN_CNT					( ECS_RET_POS_CNT + ECS_PICK_POS_CNT )
#define	ECS_STN_CNT						( ECS_STO_POS_CNT + ECS_RET_POS_CNT + ECS_PICK_POS_CNT )
#define	ECS_RET_CHK_CNT					4

#define CNV_POS_HS_1					1
#define CNV_POS_HS_2					2
#define CNV_POS_HS_3					3
#define CNV_POS_HS_4					4
#define CNV_STO_POS_1					5
#define CNV_STO_POS_2					6
#define CNV_STO_POS_3					7
#define CNV_RET_POS_1					5
#define CNV_RET_POS_2					6
#define CNV_RET_POS_3					8
#define CNV_JOB_POS_CNT					9

#endif // __GLX_DEFINE_H__