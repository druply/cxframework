/*
 * cxdio.c
 *
 *  Created on: Feb 26, 2021
 *      Author: Rodolfo.Ortega
 */


#include "cxdtypes.h"

#ifdef _CX_DIO_
#include "cxdio.h"
#include "diodrv.h"
#endif

#ifdef _CX_PWM_
#include "pwmdrv.h"
#endif


void cxdioInit(void) {
    #ifdef _CX_DIO_
    diodrvInit();
    #endif

    #ifdef _CX_PWM_
    pwmdrvInit();
    #endif
}
