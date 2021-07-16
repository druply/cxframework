/*
 * app_swc.h
 *
 *  Created on: Aug 18, 2020
 *      Author: Rodolfo.Ortega
 */

#ifndef APP_APP_SWC_INC_APP_SWC_H_
#define APP_APP_SWC_INC_APP_SWC_H_

#ifdef __cplusplus
extern "C" {
#endif

void app_swc_init(void);

void app_swc1_init(void);
void app_swc1(void);
void rte_input_swc1(void);
void rte_output_swc1(void);
void app_swc2(void);
void app_swc1_deinit(void);

void app_swc2_init(void);
void rte_input_swc2(void);
void rte_output_swc2(void);
void app_swc2(void);
void app_swc2_deinit(void);

void app_swc3_init(void);
void rte_input_swc3(void);
void rte_output_swc3(void);
void app_swc3(void);
void app_swc3_deinit(void);

void app_swc_deinit(void);

#ifdef __cplusplus
	}
#endif

#endif /* APP_APP_SWC_INC_APP_SWC_H_ */
