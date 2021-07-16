/*
 * candrv.c
 *
 *  Created on: Sep 18, 2020
 *      Author: Rodolfo.Ortega
 */

#include "cxdtypes.h"
#include "cxcan_types.h"
#include "candrv.h"

#ifdef _DEBUG_
#include <stdio.h>
#endif
/**
 * Send CAN messages
 * to HW
 */
Std_ReturnType candrvSendMsg(cxcan_msg_t *msg) {

	Std_ReturnType res =E_OK;
	uint8_t res_drv;
	#ifdef _DEBUG_

	printf("hw channel: %x\n", msg->hw_channel);
	printf("msg id: %x\n", msg->id);
	printf("data 0: %x\n", msg->data[0]);
	printf("data 1: %x\n", msg->data[1]);
	printf("data 2: %x\n", msg->data[2]);
	printf("data 3: %x\n", msg->data[3]);


	#else
	res_drv = os_can_send_msg(msg->hw_channel, msg->id, 0, msg->dlc, msg->data[0], msg->data[1], msg->data[2], msg->data[3], msg->data[4], msg->data[5], msg->data[6], msg->data[7]);

	if(res_drv == 1) {
		res = E_OK;
	}
	else {
		res = E_NOT_OK;
	}
	#endif

	return res;
}


