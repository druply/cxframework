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

#ifdef _CX_RTSIM_
#include "rtsim.h"
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

	#ifdef _CX_RTSIM_
        start_rtsim();
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

		#ifdef _CX_DIO_
        ecudio10ms();
		#endif

		#ifdef _CX_ETH_
		ecueth10ms();
		#endif

        app_swc1();

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

        if (((cx_thread0ctr - 2) % 10) == 0)  {
                // List 100ms task calls here
                // 100ms tasks will initially be called 2 loops after the initial loop
            #ifdef	_CX_CAN_
                ecucan100ms();
            #endif

        }

        if (((cx_thread0ctr - 3) % 100) == 0)  {
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

	static uint16_t cx_thread1ctr;

        // List 10ms calls here
    	app_swc2();

        if ((cx_thread1ctr % 2) == 0) {
                // List 20ms task calls here
                // 20ms tasks will be called on the initial task loop with 10ms

        }

        if (((cx_thread1ctr - 1) % 5) == 0)  {
                // List 50ms task calls here
                // 50ms tasks will initially be called 1 loop after the initial loop

        }

        if (((cx_thread1ctr - 2) % 10) == 0)
        {
                // List 100ms task calls here
                // 100ms tasks will initially be called 2 loops after the initial loop

        }

        if (((cx_thread1ctr - 3) % 100) == 0)
        {
                // List 1000ms task calls here
                // 1000ms tasks will initially be called 3 loops after the initial loop

        }


        // Initial loop executes when the TaskLoopCount is 0
        if (cx_thread1ctr >= 9999)
        {
        	cx_thread1ctr = 0;
        }
        else
        {
        	cx_thread1ctr++;
        }



}

/**
 * Thread/Core 2 task
 */
void cxosThread2(void) {

	static uint16_t cx_thread2ctr;

        // List 10ms calls here
		app_swc3();
        if ((cx_thread2ctr % 2) == 0) {
                // List 20ms task calls here
                // 20ms tasks will be called on the initial task loop with 10ms

        }

        if (((cx_thread2ctr - 1) % 5) == 0)  {
                // List 50ms task calls here
                // 50ms tasks will initially be called 1 loop after the initial loop

        }

        if (((cx_thread2ctr - 2) % 10) == 0)
        {
                // List 100ms task calls here
                // 100ms tasks will initially be called 2 loops after the initial loop

        }

        if (((cx_thread2ctr - 3) % 100) == 0)
        {
                // List 1000ms task calls here
                // 1000ms tasks will initially be called 3 loops after the initial loop

        }


        // Initial loop executes when the TaskLoopCount is 0
        if (cx_thread2ctr >= 9999)
        {
        	cx_thread2ctr = 0;
        }
        else
        {
        	cx_thread2ctr++;
        }

}


/**
 * Thread/Core 3 task
 */
void cxosThread3(void) {

	static uint16_t cx_thread3ctr;

        // List 10ms calls here

        if ((cx_thread3ctr % 2) == 0) {
                // List 20ms task calls here
                // 20ms tasks will be called on the initial task loop with 10ms
        }

        if (((cx_thread3ctr - 1) % 5) == 0)  {
                // List 50ms task calls here
                // 50ms tasks will initially be called 1 loop after the initial loop
        }

        if (((cx_thread3ctr - 2) % 10) == 0)
        {
                // List 100ms task calls here
                // 100ms tasks will initially be called 2 loops after the initial loop
        }

        if (((cx_thread3ctr - 3) % 100) == 0)
        {
                // List 1000ms task calls here
                // 1000ms tasks will initially be called 3 loops after the initial loop
        }


        // Initial loop executes when the TaskLoopCount is 0
        if (cx_thread3ctr >= 9999)
        {
        	cx_thread3ctr = 0;
        }
        else
        {
        	cx_thread3ctr++;
        }

}

/**
 * Thread/Core 4 task
 */
void cxosThread4(void) {

	static uint16_t cx_thread4ctr;

        // List 10ms calls here

        if ((cx_thread4ctr % 2) == 0) {
                // List 20ms task calls here
                // 20ms tasks will be called on the initial task loop with 10ms
        }

        if (((cx_thread4ctr - 1) % 5) == 0)  {
                // List 50ms task calls here
                // 50ms tasks will initially be called 1 loop after the initial loop
        }

        if (((cx_thread4ctr - 2) % 10) == 0)
        {
                // List 100ms task calls here
                // 100ms tasks will initially be called 2 loops after the initial loop
        }

        if (((cx_thread4ctr - 3) % 100) == 0)
        {
                // List 1000ms task calls here
                // 1000ms tasks will initially be called 3 loops after the initial loop
        }


        // Initial loop executes when the TaskLoopCount is 0
        if (cx_thread4ctr >= 9999)
        {
        	cx_thread4ctr = 0;
        }
        else
        {
        	cx_thread4ctr++;
        }

}


/**
 * non realtime Thread/Core 0 task
 */
void cxosThread_nrt0(void) {

}


/**
 * non realtime Thread/Core 1 task
 */
void cxosThread_nrt1(void) {

}


/**
 * non realtime temporary Thread/Core 0 task
 */
void cxosThread_tmp0(void) {
	// this thread is a one time execution thread, can be used to initialize drivers
}


/**
 * non realtime temporary Thread/Core 1 task
 */
void cxosThread_tmp1(void) {
	// this thread is a one time execution thread, can be used to initialize drivers
}

void cxosDeInit(void) {
	// add you code here
	#ifdef _CX_RTSIM_

	#endif
}
