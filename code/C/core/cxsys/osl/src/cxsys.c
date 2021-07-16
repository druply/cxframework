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


#ifdef  _CX_DIO_
#include "cxdio.h"
#endif

OsState_t sys_state = cxOS_INACTIVE;

/**
 * Initialize OS
 */
void cxsysInit(void) {
	sys_state = cxOS_INIT;

	//initialize apps
	app_swc_init();

	cxosInit();

	#ifdef	_CX_CAN_
		cxcanInit();
	#endif

    #ifdef  _CX_IO_
        #ifdef  _CX_DIO_
		    cxdioInit();
        #endif
    #endif
}

/**
 * Start OS
 */
void cxsysStart(void) {
	sys_state = cxOS_RUNNING;
	// change OS state
	//sys_state = OS_RUNNING;

	// start OS
	cxosStart();
}

void cxsysGetState(OsState_t *state) {
	*state = sys_state;
}

/**
 * Initialize OS
 */
void cxsysDeInit(void) {
	sys_state = cxOS_INACTIVE;
	// deinitialize app
	app_swc_deinit();
	//deiniliatize OS
	cxosDeInit();
}
