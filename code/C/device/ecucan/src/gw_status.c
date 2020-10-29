/*
 * gw_status.c
 *
 *  Created on: Sep 18, 2020
 *      Author: Rodolfo.Ortega
 */
#include "cxdtypes.h"
#include "cxcan_types.h"
#include "ecucan.h"
#include "gw_status.h"

#include "candrv.h"

Std_ReturnType gw_statusTxHandler(void) {
	union gw_status_U 	gw_status_MSG;
	Std_ReturnType res;
	cxcan_msg_t msg;
	int i;

	gw_status_MSG.msg.unused_0 = 0x00;
	gw_status_MSG.msg.unused_1 = 0x00;
	gw_status_MSG.msg.unused_2 = 0x00;
	gw_status_MSG.msg.unused_3 = 0x00;
	gw_status_MSG.msg.unused_4 = 0x00;
	gw_status_MSG.msg.unused_5 = 0x00;
	gw_status_MSG.msg.unused_6 = 0x00;
	gw_status_MSG.msg.unused_7 = 0x00;

	// configure message
	msg.id = (uint16_t)0x100;
	msg.dlc = (uint8_t)8;
	msg.hw_channel = (uint8_t)GW_STATUS_CHANNEL;

	// normalize data
	for(i=8; i>0; i--) {
		msg.data[i-1] = gw_status_MSG.data[i-1];
	}
	// send message and get response
	res = candrvSendMsg(&msg);
	return res;
}
