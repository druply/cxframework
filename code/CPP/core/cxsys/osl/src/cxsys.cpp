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
#include <mutex>

#ifdef	_CX_CAN_
#include "cxcan.h"
#endif

#ifdef  _CX_DIO_
#include "cxdio.h"
#endif

#ifdef _CX_TMR_MEAS_
#include "cxtmr.h"
#endif

OsState_t sys_state = cxOS_INACTIVE;

std::mutex cxsys_mtx;           // mutex for critical section

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

    #ifdef _CX_TMR_MEAS_
        cxtmrInit();
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

	// lock mutex for critical section
	cxsys_mtx.lock();

	*state = sys_state;
	// unlock mutex
	cxsys_mtx.unlock();
}

/**
 * Initialize OS
 */
void cxsysDeInit(void) {
	sys_state = cxOS_INACTIVE;
	// deinitialize app
	//app_swc_deinit();
	//deiniliatize OS
	cxosDeInit();
}
