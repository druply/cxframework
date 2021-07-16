/*
 * cxcan_types.h
 *
 *  Created on: Sep 18, 2020
 *      Author: Rodolfo.Ortega
 */

#ifndef CORE_CXCOMM_CXCAN_INC_CXCAN_TYPES_H_
#define CORE_CXCOMM_CXCAN_INC_CXCAN_TYPES_H_


typedef uint16_t cxMsgId_t;

typedef struct {
	cxMsgId_t id;
	uint8_t hw_channel;
	uint8_t dlc;
	uint8_t crc;
	uint8_t data[8];
} cxcan_msg_t;

typedef struct {
	cxMsgId_t id;
	uint8_t hw_channel;
} cxcan_TxBuffer_t;

typedef struct {
	cxMsgId_t id;
	//uint8_t hw_channel;
	//uint8_t dlc;
	//uint8_t crc;
	//uint8_t to_flag;
	//uint8_t allow_tx;
	uint16_t to_ctr;
	uint16_t to_limit;
} cxcan_status_msg_t;

typedef enum {
	B_FULL = 0,
	B_EMPTY,
	B_NEMPTY
} cxBufferStatus_t;

typedef enum {
	T_ALLOW = 0,
	T_DONT_ALLOW
} cxAllowTx_t;

typedef uint16_t cxCrc_t;

typedef enum {
	CRC_OK=0,
	CRC_ERR
} cxCrcCheck_t;

typedef enum {
	RollCtr_OK=0,
	RollCtr_ERR
} cxRCCheck_t;

// ***** Buffer coniguration *************////

#endif /* CORE_CXCOMM_CXCAN_INC_CXCAN_TYPES_H_ */
