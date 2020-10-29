/*
 * ecucan.h
 *
 *  Created on: Sep 18, 2020
 *      Author: Rodolfo.Ortega
 */

#ifndef DEVICE_ECUCAN_INC_ECUCAN_H_
#define DEVICE_ECUCAN_INC_ECUCAN_H_

#ifdef _DEBUG_
#define   CANDRV_CAN0			0
#define   CANDRV_CAN1			1

#else

#define   CANDRV_CAN0			CAN_BUS_0
#define   CANDRV_CAN1			CAN_BUS_1

#endif

/// Define rx messages
typedef enum
{
	environment_status_en  = 0,
	environment_control_en,
    cxCAN_MSG_MAX
} can_msg_list_t;

void ecucanInit(void);
void ecucanTxHandler(cxMsgId_t msg_id);
void ecucan10ms(void);
void ecucan20ms(void);
void ecucan50ms(void);
void ecucan100ms(void);
void ecucan1000ms(void);
void ecucanSetTimeOut(cxMsgId_t msg_id) ;

extern cxcan_status_msg_t  can_msg_tbl[cxCAN_MSG_MAX];

#endif /* DEVICE_ECUCAN_INC_ECUCAN_H_ */
