/*
 * app_swc1.c
 *
 *  Created on: Aug 20, 2020
 *      Author: Rodolfo.Ortega
 */

#include "cxdtypes.h"
#include "app_swc.h"
#include "cxcan_types.h"
#include "rte_comm.h"

// include your headers here!!
#ifdef _CX_TMR_MEAS_
#include "cxtmr.h"
cxTmr_T tmr_appswc3 = tmr3;
#endif
void app_swc3_init(void) {

}

void rte_input_swc3(void) {
	//bind rte  signals with swc input signals.

}

void rte_output_swc3(void) {
	//bind rte signals with swc output signals.

}

void app_swc3(void) {
	#ifdef _CX_TMR_MEAS_
		cxtmrStart(tmr_appswc3);
	#endif
	// read inputs from rte
	rte_input_swc3();

	//write outputs to rte
	rte_output_swc3();

	#ifdef _CX_TMR_MEAS_
		cxtmrStop(tmr_appswc3);
	#endif
	/**************************/
}


void app_swc3_deinit(void) {

}
