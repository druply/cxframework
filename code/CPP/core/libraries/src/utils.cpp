/*
 * utils.cpp
 *
 *  Created on: Apr 1, 2021
 *      Author: Rodolfo.Ortega
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <iostream>

#include "utils.h"

mutex cx_mtx;           // mutex for critical section


void cxprint(string str, double var) {

	cx_mtx.lock();
	thread::id this_id = this_thread::get_id();
    cout << "thread " << this_id << " says: "<< str << var << endl;;
    cx_mtx.unlock();

    this_thread::sleep_for(chrono::seconds(1));
}
