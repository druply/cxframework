

// define services
//#define		_CX_COMM_
//#define		_CX_IO_
//#define		_CX_MEM_
//#define		_CX_SYSTEM_
//#define		_CX_DIAG_


//define OS
//#define _CX_FREERTOS_

#ifdef		_CX_COMM_
	//#define		_CX_CAN_
	//#define		_CX_SPI_
	//#define		_CX_I2C_
#endif


#ifdef      _CX_IO_
    #define       _CX_DIO_
    #define       _CX_PWM_

#endif

#define 	_DEBUG_
