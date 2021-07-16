/*
 * cxos.h
 *
 *  Created on: Sep 2, 2020
 *      Author: Rodolfo.Ortega
 */

#ifndef OS_OSL_INC_CXOS_H_
#define OS_OSL_INC_CXOS_H_

#ifndef __cplusplus

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
void cxosDeInit(void);

#else

extern "C" void cxosInit(void);
extern "C" void cxosStart(void);
extern "C" void cxosThread0(void);
extern "C" void cxosThread1(void);
extern "C" void cxosThread2(void);
extern "C" void cxosDeInit(void);

#endif

#endif /* OS_OSL_INC_CXOS_H_ */
