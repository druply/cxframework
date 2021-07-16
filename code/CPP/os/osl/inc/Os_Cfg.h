

// define services
//#define		_CX_COMM_
//#define		_CX_IO_
//#define		_CX_MEM_
//#define		_CX_SYSTEM_
//#define		_CX_DIAG_
#define        _CX_TMR_MEAS_
#define        _CX_TEST_


//define OS
//#define _CX_FREERTOS_
#define _CX_RTSIM_


//  enable services
#ifdef		_CX_COMM_
	//#define		_CX_CAN_
	//#define		_CX_SPI_
	//#define		_CX_I2C_
	//#define		_CX_ETH_
#endif


#ifdef      _CX_IO_
    #define       _CX_DIO_
    //#define       _CX_PWM_

#endif

#ifdef      _CX_ETH_
    #define     _CX_UDP_
    //#define     _CX_TCP_
#endif

// configure thread and sw component execution
#define		_CX_NUM_OF_THREADS_		1		// real time threads
#define		_CX_NUM_OF_NRT_THREADS_		0  // non real time threads
#define		_CX_NUM_OF_TMP_THREADS_		0  // non real time threads
#define		_CX_NUM_OF_SWC_			1		// sw components

// debug or production?
#define 	_DEBUG_
