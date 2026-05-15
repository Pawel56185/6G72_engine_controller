/*
 * timing.h
 *
 *  Created on: 4 maj 2026
 *      Author: Pmajc
 */

#ifndef INC_ENC_TIMING_H_
#define INC_ENC_TIMING_H_

#define E_TIM_NONE                         65535
#define E_TIM_TRUE                         1
#define E_TIM_FALSE                        0
#define E_TIM_WHICH_CYLINDER_UNKNOWN       0
#define E_TIM_DEGS_PAST_LAST_GMP_INI       65535
#define E_TIM_ABSOLUTE_POSITION_INIT       65535
#define E_TIM_RPM_INIT                     0
#define E_TIM_IGNITION_ACCELERATION_INIT   0
#define E_TIM_INJECTION_ACCELERATION_INIT  65535

#include "main.h"



typedef struct {
	uint16_t which_cylinder;
	uint16_t edges_past_last_gmp;
	uint16_t absolute_position;
	uint16_t rmp;
	uint16_t ignition_acceleration;
	uint16_t injection_acceleration;


}engine_position_and_timing;

void dense_encoder_callback(engine_position_and_timing* pos);
void sparse_encoder_callback(engine_position_and_timing* pos);
void TIM_InitPositionData(engine_position_and_timing *pos);




#endif /* INC_ENC_TIMING_H_ */
