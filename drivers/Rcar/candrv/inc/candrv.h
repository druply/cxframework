/*
 * candrv.h
 *
 *  Created on: Aug 22, 2020
 *      Author: Rodolfo.Ortega
 */

#ifndef CONEXCOMM_INC_CANDRV_H_
#define CONEXCOMM_INC_CANDRV_H_

#define   CAN0			0
#define   CAN1			1


Std_ReturnType candrvSendMsg(cxcan_msg_t *msg);
void receive_can_msg(cxcan_msg_t *msg);
void can_init(void);
void can_filter_init(uint16_t ids_tbl[]);
void receive_can(void);

#endif /* CONEXCOMM_INC_CANDRV_H_ */
