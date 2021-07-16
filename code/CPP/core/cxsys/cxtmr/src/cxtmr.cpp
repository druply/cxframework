#include "cxdtypes.h"


#ifdef 	 _CX_TMR_MEAS_

#include "cxtmr.h"
#include <time.h>
#include <mutex>

struct timespec start1, stop1, start2, stop2, start3, stop3, start4, stop4, start5, stop5;
static double result_tmr1, result_tmr2, result_tmr3, result_tmr4, result_tmr5;
static double result_tmr1_tmp, result_tmr2_tmp, result_tmr3_tmp, result_tmr4_tmp, result_tmr5_tmp;

std::mutex cxtmr_mtx1, cxtmr_mtx2;

void cxtmrInit(void) {
    result_tmr1 = 0;
    result_tmr2 = 0;
    result_tmr3 = 0;
    result_tmr4 = 0;
    result_tmr5 = 0;

    result_tmr1_tmp = 0;
    result_tmr2_tmp = 0;
    result_tmr3_tmp = 0;
    result_tmr4_tmp = 0;
    result_tmr5_tmp = 0;
}


void cxtmrStart(cxTmr_T timer) {

	// lock mutex for critical section
	cxtmr_mtx1.lock();

    if(timer == tmr1) {
        clock_gettime(CLOCK_MONOTONIC, &start1);
    }
    if(timer == tmr2) {
        clock_gettime(CLOCK_MONOTONIC, &start2);
    }

	// unlock mutex
    cxtmr_mtx1.unlock();
}

void cxtmrStop(cxTmr_T timer) {

	// lock mutex for critical section
	cxtmr_mtx2.lock();

	if(timer == tmr1) {
        clock_gettime(CLOCK_MONOTONIC, &stop1);
        result_tmr1_tmp = (stop1.tv_sec - start1.tv_sec) * 1e9 + (stop1.tv_nsec - start1.tv_nsec);
        result_tmr1_tmp /= 1000000; // convert to milliseconds

        if(result_tmr1_tmp > result_tmr1) {
        	result_tmr1 = result_tmr1_tmp;
        }
    }

    if(timer == tmr2) {
        clock_gettime(CLOCK_MONOTONIC, &stop2);
        result_tmr2_tmp = (stop2.tv_sec - start2.tv_sec) * 1e9 + (stop2.tv_nsec - start2.tv_nsec);
        result_tmr2_tmp /= 1000000; // convert to milliseconds

        if(result_tmr2_tmp > result_tmr2) {
        	result_tmr2 = result_tmr2_tmp;
        }
    }

	// unlock mutex
    cxtmr_mtx2.unlock();
}

double cxtmrGetTimeStamp(cxTmr_T timer) {

    if(timer == tmr1) {
        return result_tmr1;
    }
    if(timer == tmr2) {
        return result_tmr2;
    }
}

void cxtmrDeInit(void) {

}


#endif
