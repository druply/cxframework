#ifndef _IO_HANDLER_H_
#define _IO_HANDLER_H_

struct OUTPUTS_S
{
	uint8_t DC2DC_Enable;
    uint8_t MCS_ignition_output;
    uint8_t Warning_Lamp;
    uint8_t Fault_Switch_Control;
};

struct INPUTS_S
{       
	uint8_t DC2DC_1_status;
	uint8_t DC2DC_2_status;
    uint8_t veh_ignition_input;
    uint16_t MCS_battery_voltage;     
};

extern struct OUTPUTS_S outputs;
extern struct INPUTS_S inputs;

void discrete_input_init(void);
void discrete_output_init(void);

void discrete_input_handler(void);
void discrete_output_handler(void);

void discrete_inputs_on_wake(void);
void discrete_inputs_to_sleep(void);

void discrete_outputs_on_wake(void);
void discrete_outputs_to_sleep(void);

#endif // _IO_HANDLER_H_
