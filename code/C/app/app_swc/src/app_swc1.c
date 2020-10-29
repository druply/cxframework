/*
 * app_swc1.c
 *
 *  Created on: Aug 20, 2020
 *      Author: Rodolfo.Ortega
 */

#include "cxdtypes.h"
#include "app_swc.h"
#include "cxcan_types.h"
#include "rte_comm.h"

// include your headers here!!


void rte_input_swc1(void) {
	//bind rte  signals with swc input signals.



}

void rte_output_swc1(void) {
	//bind rte signals with swc output signals.

}

void app_swc1(void) {


	// read inputs from rte
	rte_input_swc1();


	//write outputs to rte
	rte_output_swc1();
	/**************************/
}
