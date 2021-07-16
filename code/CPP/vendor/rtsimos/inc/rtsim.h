/*
 * rtsim.h
 *
 *  Created on: Aug 22, 2020
 *      Author: Rodolfo.Ortega
 */

#ifndef RTSIMOS_INC_RTSIM_H_
#define RTSIMOS_INC_RTSIM_H_

//define step cycle execution time
//#define     MAIN_CYCLE_nS   5000000.00 // 5ms
#define     MAIN_CYCLE_nS   10000000.00  // 10ms

void rtsim_init(void);
void rtsim_main(void);
void start_rtsim(void);
void rtsim_thread1(void);
void rtsim_thread2(void);
void rtsim_thread3(void);

#endif /* RTSIMOS_INC_RTSIM_H_ */
