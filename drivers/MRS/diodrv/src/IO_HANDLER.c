/*************************************************************************/
//	This file was generated using DBC Parser Version 4.3.29
/*************************************************************************/

/*************************************************************************/
//	Includes
/*************************************************************************/
#include "cxdtypes.h"
//#include "Os_Cfg.h"

#ifndef _DEBUG_
	#include "os_io_tables.h"
#endif
#include "IO_HANDLER.h"

/*************************************************************************/
//	Macros
/*************************************************************************/

/*************************************************************************/
//	Types
/*************************************************************************/

/*************************************************************************/
//	Variables
/*************************************************************************/

struct OUTPUTS_S outputs;
struct INPUTS_S inputs;

/*************************************************************************/
//	Prototypes
/*************************************************************************/

/*************************************************************************/
//	Implementation
/*************************************************************************/


void discrete_input_init(void)
{
	inputs.veh_ignition_input = 0;
	inputs.MCS_battery_voltage = 0x17F;
}

void discrete_output_init(void)
{
	outputs.MCS_ignition_output = 0;
	outputs.DC2DC_Enable = 0;
	outputs.Warning_Lamp = 0;
	outputs.Fault_Switch_Control = 0;
}

void discrete_input_handler(void)
{
#ifndef _DEBUG_
	inputs.veh_ignition_input = os_digin(DI_KL15);
	inputs.MCS_battery_voltage = os_algin_mv(AI_ANA0);
#endif
	    
    inputs.DC2DC_1_status = 1; //os_digin(D2DC_ON_STATUS1);
    inputs.DC2DC_2_status = 1; //os_pin_read(D2DC_ON_STATUS2);
}

void discrete_output_handler(void)
{
#ifndef _DEBUG_
	os_digout(DO_2, outputs.MCS_ignition_output);
    os_digout(DO_1, outputs.DC2DC_Enable);
	os_digout(DO_4, outputs.Warning_Lamp);
	os_digout(DO_3, outputs.Fault_Switch_Control);
#endif
}

void discrete_inputs_on_wake(void)
{
#ifndef _DEBUG_
	inputs.veh_ignition_input = os_digin(DI_KL15);
	inputs.MCS_battery_voltage = os_algin_mv(AI_ANA0);
#endif
}

void discrete_inputs_to_sleep(void)
{
	inputs.veh_ignition_input = 0;
	inputs.MCS_battery_voltage = 0x17F;
}

void discrete_outputs_on_wake(void)
{
	outputs.MCS_ignition_output = 0;
	outputs.DC2DC_Enable = 0;
	outputs.Warning_Lamp = 0;
	outputs.Fault_Switch_Control = 0;
#ifndef _DEBUG_
	os_digout(DO_2, outputs.MCS_ignition_output);
    os_digout(DO_1, outputs.DC2DC_Enable);
#endif
}
void discrete_outputs_to_sleep(void)
{
	outputs.MCS_ignition_output = 0;
	outputs.DC2DC_Enable = 0;
	outputs.Warning_Lamp = 0;
	outputs.Fault_Switch_Control = 0;
#ifndef _DEBUG_
	os_digout(DO_2, outputs.MCS_ignition_output);
    os_digout(DO_1, outputs.DC2DC_Enable);
#endif
}
