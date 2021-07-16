/*
 * freertos.c
 *
 *  Created on: Jan 28, 2021
 *      Author: Rodolfo.Ortega
 */
#include "cxdtypes.h"
#include "Os_Cfg.h"
#include "cxos.h"

#ifdef _CX_FREERTOS_
#include "FreeRTOS.h"
#include "task.h"
#include "app_swc.h"
//#include "queue.h"
//#include "semphr.h"


void cxTask0(void *pvParameters) {

	while(1) {
        cxosThread0();
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}


void cxFreeRtosStart(void) {
	// create tasks
    xTaskCreate(cxTask0, "thread0", 200, "task", 1, 0);
    vTaskStartScheduler();
}


#endif
