/*
 * cxos.h
 *
 *  Created on: Sep 2, 2020
 *      Author: Rodolfo.Ortega
 */

#ifndef OS_OSL_INC_CXOS_H_
#define OS_OSL_INC_CXOS_H_


void cxosInit(void);
void cxosStart(void);

#ifdef _CX_FREERTOS_
void cxFreeRtosStart(void);
void cxosThread0(void);
#else
void cxosThread0(void);
#endif

void cxosThread1(void);
void cxosThread2(void);
void cxosThread3(void);
void cxosThread4(void);


void cxosThread_nrt0(void);
void cxosThread_nrt1(void);
void cxosThread_tmp0(void);
void cxosThread_tmp1(void);

void cxosDeInit(void);


#endif /* OS_OSL_INC_CXOS_H_ */
