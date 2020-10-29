/*
 * cxcan.c
 *
 *  Created on: Sep 18, 2020
 *      Author: Rodolfo.Ortega
 */
#include "cxdtypes.h"
//#include "cxcan_types.h"
#include "cxcan.h"
#include "ecucan.h"

uint32_t volatile TxPutI;// put next
uint32_t volatile TxGetI;// get next
cxcan_TxBuffer_t static TxFifo[TX_BUFFER_SIZE];



void cxcanInit(void) {
	// buffer init
	TxPutI = TxGetI = 0;  // Empty buffer
	ecucanInit();
}

void cxcanTxError(cxcan_TxBuffer_t *msg) {
	// store msg in buffer
	(void)cxcanTxBufferPut(msg);
}

void cxcanMain(void) {
	// monitor timeouts
	cxcanMonitor();
	// retransmit missed messages
	cxcanReTransmit();
}


Std_ReturnType  cxcanTxBufferPut(cxcan_TxBuffer_t *msg) {
	Std_ReturnType result;

	if(cxcanTxBufferStatus() == B_FULL) {
		result = E_NOT_OK;
	}
	else {
	// put in buffer
	  if((TxPutI-TxGetI) & ~(TX_BUFFER_SIZE-1)) {
		 result = E_NOT_OK;
	  }
	  else {
		  //TxFifo[TxPutI&(TX_BUFFER_SIZE-1)].allow_tx = msg_status->allow_tx; // put
		  //TxFifo[TxPutI&(TX_BUFFER_SIZE-1)].crc = msg_status->crc; // put
		  //TxFifo[TxPutI&(TX_BUFFER_SIZE-1)].dlc = msg_status->dlc; // put
		  //TxFifo[TxPutI&(TX_BUFFER_SIZE-1)].hw_channel = msg_status->hw_channel; // put
		  //TxFifo[TxPutI&(TX_BUFFER_SIZE-1)].id = msg_status->id; // put
		  //TxFifo[TxPutI&(TX_BUFFER_SIZE-1)].to_ctr = msg_status->to_ctr; // put
		  //TxFifo[TxPutI&(TX_BUFFER_SIZE-1)].to_flag = msg_status->to_flag; // put
		  //TxFifo[TxPutI&(TX_BUFFER_SIZE-1)].to_limit = msg_status->to_limit; // put
		  TxFifo[TxPutI&(TX_BUFFER_SIZE-1)].id = msg->id;
		  TxFifo[TxPutI&(TX_BUFFER_SIZE-1)].hw_channel = msg->hw_channel;
		  TxPutI++;  // Success, update
		  result = E_OK;
	  }
	}
	return result;
}

Std_ReturnType cxcanTxBufferGet(cxcan_TxBuffer_t *msg) {

	Std_ReturnType result;

	if(cxcanTxBufferStatus() == B_EMPTY) {
		// buffer is empty nothing to retrieve
		result = E_NOT_OK;
	}
	else {
		// get from buffer
		  if(TxPutI == TxGetI ) {
		    //return(TXFIFOFAIL); // Empty if TxPutI=TxGetI
			 result = E_NOT_OK;

		  }
		  else {
			  //msg_status->allow_tx = TxFifo[TxGetI&(TX_BUFFER_SIZE-1)].allow_tx;
			  //msg_status->crc = TxFifo[TxGetI&(TX_BUFFER_SIZE-1)].crc;
			  //msg_status->dlc = TxFifo[TxGetI&(TX_BUFFER_SIZE-1)].dlc;
			  //msg_status->hw_channel = TxFifo[TxGetI&(TX_BUFFER_SIZE-1)].hw_channel;
			  //msg_status->id = TxFifo[TxGetI&(TX_BUFFER_SIZE-1)].id;
			  //msg_status->to_ctr = TxFifo[TxGetI&(TX_BUFFER_SIZE-1)].to_ctr;
			  //msg_status->to_flag = TxFifo[TxGetI&(TX_BUFFER_SIZE-1)].to_flag;
			  //msg_status->to_limit = TxFifo[TxGetI&(TX_BUFFER_SIZE-1)].to_limit;
			  msg->id = TxFifo[TxGetI&(TX_BUFFER_SIZE-1)].id;
			  msg->hw_channel = TxFifo[TxGetI&(TX_BUFFER_SIZE-1)].hw_channel;

			  TxGetI++;  // Success, update
			  result = E_OK;
		  }
	}
	return result;
}

Std_ReturnType cxcanReTransmit(void) {

	Std_ReturnType result;
	//cxcan_status_msg_t msg;
	cxcan_TxBuffer_t msg;

	// check buffer status
	if((cxcanTxBufferStatus() == B_NEMPTY) || (cxcanTxBufferStatus() == B_FULL)) {
		// if not empty then get msg
		cxcanTxBufferGet(&msg);
		// send msg
		//CAN_Write(&msg);
		ecucanTxHandler(&msg);
	}
	result = E_OK;
	return result;
}

cxBufferStatus_t cxcanTxBufferStatus(void) {
	cxBufferStatus_t status = B_EMPTY;

	if((TxPutI-TxGetI) & ~(TX_BUFFER_SIZE-1)){
	    status = B_FULL; // fifo full
	}
	else if(TxPutI == TxGetI ){
		status = B_EMPTY; // Empty if TxPutI=TxGetI
	  }
	else {
		status = B_NEMPTY; // not empty nor full
	}
	// check buffer status
	return status;
}


void cxcanMonitor(void) {
	int idx;
	// time out handler
	for(idx = cxCAN_MSG_MAX; idx>0;idx--) {
		can_msg_tbl[idx - 1].to_ctr +=10; // incremente by 10ms
		if(can_msg_tbl[idx - 1].to_ctr > can_msg_tbl[idx - 1].to_limit) {
			// set to flag
			//can_msg_tbl[idx].to_flag = 1;
			 //ecucanSetTimeOut(can_msg_tbl[idx].id);
			ecucanSetTimeOut(idx-1);
		}
		// check if there is crc
		//if(can_msg_tbl[idx].crc == CRC_ERR) {
			// log error or report action
		//}
	}
}
