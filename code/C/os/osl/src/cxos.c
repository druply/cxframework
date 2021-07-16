/*
 * cxos.c
 *
 *  Created on: Sep 2, 2020
 *      Author: Rodolfo.Ortega
 */
#include "cxdtypes.h"
#include "Os_Cfg.h"
#include "cxos.h"

#ifdef	_CX_CAN_
#include "cxcan_types.h"
#include "cxcan.h"
#include "ecucan.h"
#endif

#include "app_swc.h"

////// include your headers here


//variables

//declare threads/tasks here

void cxosInit(void){
	// add you code here
	// define threads here

    //xTaskCreate(bsp_main, "main", 200, (void*) 0, 0, 0);
    //xTaskCreate(bsp_write_outputs, "write", 200, (void*) 0, 0, 0);
}

void cxosStart(void) {
	// add your code here

	// start threads here
    #ifdef _CX_FREERTOS_
        cxFreeRtosStart();
    #endif
}


/**
 * Thread/Core 0 task
 * execute every 10ms to get a real time execution
 */

void cxosThread0(void) {


	static uint16_t cx_thread0ctr;

        // List 10ms calls here
        #ifdef	_CX_CAN_
        cxcanMain();
        ecucan10ms();
        #endif


        if ((cx_thread0ctr % 2) == 0) {
                // List 20ms task calls here
                // 20ms tasks will be called on the initial task loop with 10ms
        #ifdef	_CX_CAN_
            ecucan20ms();
        #endif
        }

        if (((cx_thread0ctr - 1) % 5) == 0)  {
                // List 50ms task calls here
                // 50ms tasks will initially be called 1 loop after the initial loop
            #ifdef	_CX_CAN_
                ecucan50ms();
            #endif

        }

        if (((cx_thread0ctr - 2) % 10) == 0)
        {
                // List 100ms task calls here
                // 100ms tasks will initially be called 2 loops after the initial loop
            #ifdef	_CX_CAN_
                ecucan100ms();
            #endif

        }

        if (((cx_thread0ctr - 3) % 100) == 0)
        {
                // List 1000ms task calls here
                // 1000ms tasks will initially be called 3 loops after the initial loop
            
            #ifdef	_CX_CAN_
                ecucan1000ms();
            #endif
        }


        // Initial loop executes when the TaskLoopCount is 0
        if (cx_thread0ctr >= 9999)
        {
            cx_thread0ctr = 0;
        }
        else
        {
            cx_thread0ctr++;
        }



}


/**
 * Thread/Core 1 task
 */
void cxosThread1(void) {

}

/**
 * Thread/Core 1 task
 */
void cxosThread2(void) {

}

void cxosDeInit(void) {
	// add you code here

}
