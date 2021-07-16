/*
 * app_swc.c
 *
 *  Created on: Aug 18, 2020
 *      Author: Rodolfo.Ortega
 */

#include "cxdtypes.h"
#include "cxcan_types.h"
#include "app_swc.h"
#include "rte_comm.h"
#include "Os.h"
#include "cxsys.h"

// hader files


void app_swc_init(void) {

	// add your init code here
	#if _CX_NUM_OF_SWC_ > 0
	app_swc1_init();
	#endif

	#if _CX_NUM_OF_SWC_ > 1
	app_swc2_init();
	#endif

	#if _CX_NUM_OF_SWC_ > 2
	app_swc3_init();
	#endif
	/**************************/
}



void app_swc_deinit(void) {

	// deinitialize sw components
	#if _CX_NUM_OF_SWC_ > 0
	app_swc1_deinit();
	#endif

	#if _CX_NUM_OF_SWC_ > 1
	app_swc2_deinit();
	#endif

	#if _CX_NUM_OF_SWC_ > 2
	app_swc3_deinit();
	#endif

	// deinitialize system
	cxsysDeInit();

	// add your deinit code here

	/**************************/
}
