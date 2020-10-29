/*
 * cxsys.c
 *
 *  Created on: Sep 18, 2020
 *      Author: Rodolfo.Ortega
 */

#include "cxdtypes.h"
#include "Os.h"
#include "cxsys.h"
#include "cxos.h"
#include "app_swc.h"

#ifdef	_CX_CAN_
#include "cxcan.h"
#endif
//OsState_t sys_state;

/**
 * Initialize OS
 */
void cxsysInit(void) {
	//initialize apps
	app_swc_init();

	cxosInit();

	#ifdef	_CX_CAN_
		cxcanInit();
	#endif

}


/**
 * Start OS
 */
void cxsysStart(void) {
	// execute threads

	// change OS state
	//sys_state = OS_RUNNING;

	// start OS
	cxosStart();
}
