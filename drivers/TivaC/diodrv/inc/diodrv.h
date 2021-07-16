/*
 * diodrv.h
 *
 *  Created on: Feb 9, 2021
 *      Author: Rodolfo.Ortega
 */

#ifndef DEVICE_DIODRV_INC_DIODRV_H_
#define DEVICE_DIODRV_INC_DIODRV_H_

enum Ports_En {
    GPIO_PORTA       =  0,  // GPIO Port A
    GPIO_PORTB           ,// GPIO Port B
    GPIO_PORTC           ,// GPIO Port C
    GPIO_PORTD           ,// GPIO Port D
    GPIO_PORTE           ,// GPIO Port E
    GPIO_PORTF           ,// GPIO Port F
    GPIO_PORTG           ,// GPIO Port G
    GPIO_PORTH           ,// GPIO Port H
};

#define  CX_PIN(X)       (1 << X)
#define  CX_GPIO_PIN_1    GPIO_PIN_1       // GPIO pin 1
#define  CX_GPIO_PIN_2    GPIO_PIN_2       // GPIO pin 2
#define  CX_GPIO_PIN_3    GPIO_PIN_3       // GPIO pin 3
/*
GPIO_PIN_4              0x00000010  // GPIO pin 4
    GPIO_PIN_5              0x00000020  // GPIO pin 5
    GPIO_PIN_6              0x00000040  // GPIO pin 6
    GPIO_PIN_7              0x00000080  // GPIO pin 7
*/

typedef uint8_t Dio_LevelType;
typedef enum Ports_En Dio_PortType;
typedef uint8_t Dio_ChannelType;
typedef uint8_t Dio_PortLevelType;
//typedef uint32_t Dio_PinLevelType;
typedef uint8_t Dio_PinLevelType;
typedef uint8_t Dio_PinType;



void Dio_WritePin(Dio_PortType PortId, Dio_PinType Pin, Dio_PinLevelType Level);
Dio_PinLevelType Dio_ReadPin(Dio_PortType PortId, Dio_PinType Pin);
void diodrvInit(void);

#endif /* DEVICE_DIODRV_INC_DIODRV_H_ */
