/*
 * cxsys.h
 *
 *  Created on: Sep 18, 2020
 *      Author: Rodolfo.Ortega
 */

#ifndef CORE_CXSYS_OSL_INC_CXSYS_H_
#define CORE_CXSYS_OSL_INC_CXSYS_H_

void cxsysInit(void);
void cxsysStart(void);
void cxsysDeInit(void);
void cxsysGetState(OsState_t *state);

#endif /* CORE_CXSYS_OSL_INC_CXSYS_H_ */
