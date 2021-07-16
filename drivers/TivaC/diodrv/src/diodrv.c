/*
 * diodrv.c
 *
 *  Created on: Feb 9, 2021
 *      Author: Rodolfo.Ortega
 */

#include "cxdtypes.h"

#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "diodrv.h"


void diodrvInit(void) {
    volatile uint32_t ui32Loop;

    // PLL = 200Mhz   div = 3   clock = 200Mhz/3 = 66.66Mhz
    SysCtlClockSet(SYSCTL_SYSDIV_3 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);

    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    //
    // Enable the GPIO pin for the LED (PF3).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
}

void Dio_WriteChannel(Dio_ChannelType ChannelId,Dio_LevelType Level) {


}

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId) {
    Dio_LevelType res = 0;

    return res;
}


void Dio_WritePin(Dio_PortType PortId, Dio_PinType Pin, Dio_PinLevelType Level) {

    switch(PortId) {
        case GPIO_PORTA:
            GPIOPinWrite(GPIO_PORTA_BASE, CX_PIN(Pin), (Level << Pin));
            break;
        case GPIO_PORTB:
             GPIOPinWrite(GPIO_PORTB_BASE, CX_PIN(Pin), (Level << Pin));
             break;
        case GPIO_PORTC:
             GPIOPinWrite(GPIO_PORTC_BASE, CX_PIN(Pin), (Level << Pin));
             break;
        case GPIO_PORTD:
             GPIOPinWrite(GPIO_PORTD_BASE, CX_PIN(Pin), (Level << Pin));
             break;
        case GPIO_PORTE:
             GPIOPinWrite(GPIO_PORTE_BASE, CX_PIN(Pin), (Level << Pin));
             break;
        case  GPIO_PORTF:
            GPIOPinWrite(GPIO_PORTF_BASE, CX_PIN(Pin), (Level << Pin));
            break;
        default:
            break;
    };
}


Dio_PinLevelType Dio_ReadPin(Dio_PortType PortId, Dio_PinType Pin) {

    Dio_PinLevelType value;

    switch(PortId) {
        case GPIO_PORTA:
            break;
        case  GPIO_PORTF:
            value = GPIOPinRead(GPIO_PORTF_BASE, CX_PIN(Pin));
            break;
        default:
            break;
    };
    return value;
}
