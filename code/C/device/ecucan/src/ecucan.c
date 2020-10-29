/*
 * ecucan.c
 *
 *  Created on: Sep 18, 2020
 *      Author: Rodolfo.Ortega
 */
#include "cxdtypes.h"
#include "cxcan_types.h"
#include "cxcan.h"
#include "ecucan.h"
#include "gw_status.h"

cxcan_status_msg_t  can_msg_tbl[cxCAN_MSG_MAX];

void ecucanInit() {

}

void ecucanTxHandler(cxMsgId_t msg_id) {
	// list your tx messages here
	switch(msg_id){
		case 0x10:
			if((/*TxAllowed*/1) && (gw_statusTxHandler() == E_NOT_OK)) {
				cxcanTxError(0x10);
			}
			break;
		default:
			break;

	};
}

void ecucanRxHandler(cxcan_msg_t *msg) {
	// handle
	if(msg->hw_channel == (uint8_t)GW_STATUS_CHANNEL) {
		// handle rx messages
		switch(msg->id){
			case environment_status_en:
				// acknowledge received
				//can_msg_tbl[environment_status_en].to_ctr = 0;
				// send message
				//ENV_CAN_RX_Status(msg);
				can_msg_tbl[environment_status_en].to_ctr = 0;
				break;
			default:
				break;

		};

	}
}

void ecucan10ms(void) {
	// pass the messages that will be transmitted every 10ms.
	ecucanTxHandler(0x10);

}

void ecucan20ms(void) {

}

void ecucan50ms(void) {

}

void ecucan100ms(void) {

}

void ecucan1000ms(void) {

}

void ecucanSetTimeOut(cxMsgId_t msg_id) {

	switch(msg_id){
		case 0x10:
			// Set timeout in rte
			break;
		default:
			break;

	};
}
