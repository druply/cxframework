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
cxTmr_T tmr_appswc1 = tmr1;
#endif

#ifdef _CX_TEST_
#include "cxtest.h"
#include "cxtest_arr.h"
static int index_ctr = 0;
#endif

// include your headers here!!



void app_swc1_init(void) {

#ifdef _CX_TEST_

cxtestPrintHeaders();

#endif

}

void rte_input_swc1(void) {
	//bind rte  signals with swc input signals.
	//double input = BtS_ActivationState[index_ctr];
}

void rte_output_swc1(void) {
	//bind rte signals with swc output signals.
	//output1[index_ctr] = 5;
}

void app_swc1(void) {
	
    #ifdef _CX_TMR_MEAS_
        cxtmrStart(tmr_appswc1);
    #endif
    
    // read inputs from rte
	rte_input_swc1();

	//write outputs to rte
	rte_output_swc1();
    
    #ifdef _CX_TMR_MEAS_
        cxtmrStop(tmr_appswc1);
    #endif

	#ifdef _CX_TEST_
        index_ctr++;

        if(index_ctr >= max_outputs) {
			#ifdef _CX_TMR_MEAS_

        	double res = cxtmrGetTimeStamp(tmr_appswc1);

        	// printf("total time in ms: %f", res);

			#endif

        	cxtestPrintOutputs();
        	app_swc_deinit();
        }
    #endif
	/**************************/
}


void app_swc1_deinit(void) {


}
