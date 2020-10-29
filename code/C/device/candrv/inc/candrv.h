/*
 * candrv.h
 *
 *  Created on: Sep 18, 2020
 *      Author: Rodolfo.Ortega
 */

#ifndef DEVICE_CANDRV_INC_CANDRV_H_
#define DEVICE_CANDRV_INC_CANDRV_H_

Std_ReturnType candrvSendMsg(cxcan_msg_t *msg);
void candrvReceiveMsg(cxcan_msg_t *msg);

#endif /* DEVICE_CANDRV_INC_CANDRV_H_ */
