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

#ifdef _CX_TMR_MEAS_
#include "cxtmr.h"
cxTmr_T tmr_appswc2 = tmr2;
#endif


// include your headers here!!


void app_swc2_init(void) {

}

void rte_input_swc2(void) {
	//bind rte  signals with swc input signals.

}

void rte_output_swc2(void) {
	//bind rte signals with swc output signals.

}

void app_swc2(void) {

	#ifdef _CX_TMR_MEAS_
		cxtmrStart(tmr_appswc2);
	#endif
	// read inputs from rte
	rte_input_swc2();

	//write outputs to rte
	rte_output_swc2();

	#ifdef _CX_TMR_MEAS_
		cxtmrStop(tmr_appswc2);
	#endif
	/**************************/
}


void app_swc2_deinit(void) {

}
