/*
 * rtsim.c
 *
 *  Created on: Aug 22, 2020
 *      Author: Rodolfo.Ortega
 */
#include <time.h>
#include <thread>
#include <mutex>
#include <chrono>

#include "rtsim.h"
#include "Os.h"
#include "cxsys.h"
#include "cxos.h"

// test headers
#include <iostream>

struct timespec rt_loop, rt_loop1, rt_loop2, rt_loop3;

std::mutex rtsim_mtx, test_mx;           // mutex for critical section



void update_timer(struct timespec *tmr) {
	// lock mutex for critical section
	rtsim_mtx.lock();
	//std::thread::id this_id = std::this_thread::get_id();
	clock_gettime(CLOCK_MONOTONIC, tmr);
	//std::cout << "thread " << this_id << " tmr: "<< tmr << std::endl;;
	// unlock mutex
	rtsim_mtx.unlock();
}


void rtsim_init(void) {
	// init code

}

void rtsim_main() {

}

void rtsim_thread1(void) {
	double loop_time = 0.0;
	double previous_loop = 0.0;

	update_timer(&rt_loop1);
	previous_loop = (rt_loop1.tv_sec) * 1e9 + (rt_loop1.tv_nsec);
	OsState_t os_state = cxOS_RUNNING;
	cxsysGetState(&os_state);

	do {
		// get current clock timestamp
		update_timer(&rt_loop1);

		// get time difference betwee current timesampt and previous timestamp
		loop_time = (rt_loop1.tv_sec) * 1e9 + (rt_loop1.tv_nsec);
		loop_time = loop_time - previous_loop;

		// if difference is greater than 10ms then execute real time simulator
		if (loop_time >= MAIN_CYCLE_nS) {
			// call real time simulator
		  cxosThread1();
		  // get clock timestamp
		  update_timer(&rt_loop1);
		  //update previous loop time
	      previous_loop = (rt_loop1.tv_sec) * 1e9 + (rt_loop1.tv_nsec);

		 }

		cxsysGetState(&os_state);
	} while(os_state == cxOS_RUNNING);
}

void rtsim_thread2(void) {
	double loop_time = 0.0;
	double previous_loop = 0.0;

	update_timer(&rt_loop2);
	previous_loop = (rt_loop2.tv_sec) * 1e9 + (rt_loop2.tv_nsec);
	OsState_t os_state = cxOS_RUNNING;
	cxsysGetState(&os_state);

	do {
		// get current clock timestamp
		update_timer(&rt_loop2);

		// get time difference betwee current timesampt and previous timestamp
		loop_time = (rt_loop2.tv_sec) * 1e9 + (rt_loop2.tv_nsec);
		loop_time = loop_time - previous_loop;

		// if difference is greater than 10ms then execute real time simulator
		if (loop_time >= MAIN_CYCLE_nS) {
		  // call real time simulator
		  cxosThread2();
		  // get clock timestamp
		  update_timer(&rt_loop2);
		  //update previous loop time
	      previous_loop = (rt_loop2.tv_sec) * 1e9 + (rt_loop2.tv_nsec);

		 }

		cxsysGetState(&os_state);
	} while(os_state == cxOS_RUNNING);
}


void rtsim_thread3(void) {

	double loop_time = 0.0;
	double previous_loop = 0.0;

	update_timer(&rt_loop3);
	previous_loop = (rt_loop3.tv_sec) * 1e9 + (rt_loop3.tv_nsec);
	OsState_t os_state = cxOS_RUNNING;
	cxsysGetState(&os_state);

	do {
		// get current clock timestamp
		update_timer(&rt_loop3);

		// get time difference betwee current timesampt and previous timestamp
		loop_time = (rt_loop3.tv_sec) * 1e9 + (rt_loop3.tv_nsec);
		loop_time = loop_time - previous_loop;

		// if difference is greater than 10ms then execute real time simulator
		if (loop_time >= MAIN_CYCLE_nS) {
		  // call real time simulator
		  cxosThread3();
		  // get clock timestamp
		  update_timer(&rt_loop3);
		  //update previous loop time
	      previous_loop = (rt_loop3.tv_sec) * 1e9 + (rt_loop3.tv_nsec);

		 }

		cxsysGetState(&os_state);
	} while(os_state == cxOS_RUNNING);
}


void rtsim_nrt_thread0(void) {
	OsState_t os_state = cxOS_RUNNING;
	cxsysGetState(&os_state);

	do {
	  // call thread
		cxosThread_nrt0();

	  cxsysGetState(&os_state);
	} while(os_state == cxOS_RUNNING);
}


void rtsim_nrt_thread1(void) {
	OsState_t os_state = cxOS_RUNNING;
	cxsysGetState(&os_state);

	do {
	  // call thread
		cxosThread_nrt1();

	  cxsysGetState(&os_state);
	} while(os_state == cxOS_RUNNING);
}

void rtsim_tmp_thread0(void) {
	// call thread and finish
	cxosThread_tmp0();
}


void rtsim_tmp_thread1(void) {
	// call thread and finish
	cxosThread_tmp1();
}

void start_rtsim(void) {
	double loop_time = 0.0;
	double previous_loop = 0.0;

	update_timer(&rt_loop);
	previous_loop = (rt_loop.tv_sec) * 1e9 + (rt_loop.tv_nsec);
	OsState_t os_state = cxOS_RUNNING;
	cxsysGetState(&os_state);

	//start threads
	#if _CX_NUM_OF_THREADS_ > 1
	std::thread thread1(rtsim_thread1);
	thread1.detach();
	#endif

	#if _CX_NUM_OF_THREADS_ > 2
	std::thread thread2(rtsim_thread2);
	thread2.detach();
	#endif

	#if _CX_NUM_OF_THREADS_ > 3
	std::thread thread3(rtsim_thread3);
	thread3.detach();
	#endif


	#if _CX_NUM_OF_NRT_THREADS_ > 0
	std::thread thread10(rtsim_nrt_thread0);
	thread10.detach();
	#endif

	#if _CX_NUM_OF_NRT_THREADS_ > 1
	std::thread thread11(rtsim_nrt_thread1);
	thread11.detach();
	#endif

	#if _CX_NUM_OF_TMP_THREADS_ > 0
	std::thread thread20(rtsim_tmp_thread0);
	thread20.detach();
	#endif

	#if _CX_NUM_OF_TMP_THREADS_ > 1
	std::thread thread21(rtsim_tmp_thread1);
	thread21.detach();
	#endif

	do {
		// get current clock timestamp
		update_timer(&rt_loop);

		// get time difference betwee current timesampt and previous timestamp
		loop_time = (rt_loop.tv_sec) * 1e9 + (rt_loop.tv_nsec);
		loop_time = loop_time - previous_loop;

		// if difference is greater than 10ms then execute real time simulator
		if (loop_time>=MAIN_CYCLE_nS) {
		  // call real time simulator
		  cxosThread0();
		  // get clock timestamp
		  update_timer(&rt_loop);
		  //update previous loop time
	      previous_loop = (rt_loop.tv_sec) * 1e9 + (rt_loop.tv_nsec);

		 }
		cxsysGetState(&os_state);
	} while(os_state == cxOS_RUNNING);

}
