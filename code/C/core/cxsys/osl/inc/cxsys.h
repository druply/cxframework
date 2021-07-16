/*
 * cxsys.h
 *
 *  Created on: Sep 18, 2020
 *      Author: Rodolfo.Ortega
 */

#ifndef CORE_CXSYS_OSL_INC_CXSYS_H_
#define CORE_CXSYS_OSL_INC_CXSYS_H_

#ifndef __cplusplus
void cxsysInit(void);
void cxsysStart(void);
void cxsysDeInit(void);
void cxsysGetState(OsState_t *state);

#else

extern "C" void cxsysInit(void);
extern "C" void cxsysStart(void);
extern "C" void cxsysDeInit(void);
extern "C" void cxsysGetState(OsState_t *state);
#endif

#endif /* CORE_CXSYS_OSL_INC_CXSYS_H_ */
