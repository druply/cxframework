/*
 * gw_status.h
 *
 *  Created on: Sep 18, 2020
 *      Author: Rodolfo.Ortega
 */

#ifndef DEVICE_ECUCAN_INC_GW_STATUS_H_
#define DEVICE_ECUCAN_INC_GW_STATUS_H_

// define channel
#define GW_STATUS_CHANNEL	CANDRV_CAN0

struct gw_status_S
{
	uint8_t	unused_0;
    uint8_t unused_1;
    uint8_t	unused_2;
	uint8_t	unused_3;
    uint8_t unused_4;
	uint8_t	unused_5;
    uint8_t unused_6;
    uint8_t unused_7;
};

union gw_status_U
{
	struct gw_status_S msg;
	uint8_t data[8];
};

extern union gw_status_U 	gw_status_MSG;

Std_ReturnType gw_statusTxHandler(void);

#endif /* DEVICE_ECUCAN_INC_GW_STATUS_H_ */
