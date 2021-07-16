//============================================================================
// Name        : main.cpp
// Author      : rodolfo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "cxdtypes.h"
#include "Os.h"
#include "cxsys.h"
#include "cxos.h"
#include "rtsim.h"

int main() {

	// initialize system
	cxsysInit();

	// if using rtsim execute start_rtsim(); once to start the system
	// if using your own OS then execute the function cxosThread0(); every 10ms	
	cxsysStart();

	return 0;
}
