/*
 * cxcan.h
 *
 *  Created on: Sep 18, 2020
 *      Author: Rodolfo.Ortega
 */

#ifndef CORE_CXCOMM_CXCAN_INC_CXCAN_H_
#define CORE_CXCOMM_CXCAN_INC_CXCAN_H_

#include "cxcan_types.h"

void cxcanInit(void);
void cxcanMain(void);
Std_ReturnType cxcanReTransmit(void);
void cxcanMonitor(void);
void cxcanTxError(cxcan_TxBuffer_t *msg);
Std_ReturnType  cxcanTxBufferPut(cxcan_TxBuffer_t *msg);
Std_ReturnType cxcanTxBufferGet(cxcan_TxBuffer_t *msg);
cxBufferStatus_t cxcanTxBufferStatus(void);
/*
typedef struct {
	can_status_msg_t data[1];
} TxBuffer_t;
*/


#define TX_BUFFER_SIZE 16 // must be a power of 2

#endif /* CORE_CXCOMM_CXCAN_INC_CXCAN_H_ */
