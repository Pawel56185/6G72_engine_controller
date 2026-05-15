/*
 * timing.c
 *
 *  Created on: 4 maj 2026
 *      Author: Pmajc
 */
#include "enc_timing.h"

void TIM_InitPositionData(engine_position_and_timing *pos){
    if (data == NULL) return;

    pos->which_cylinder = E_TIM_WHICH_CYLINDER_UNKNOWN;
    pos->edges_past_last_gmp = E_TIM_DEGS_PAST_LAST_GMP_INI;
    pos->absolute_position = E_TIM_ABSOLUTE_POSITION_INIT;
    pos->rmp = E_TIM_RPM_INIT;
    pos->ignition_acceleration = E_TIM_IGNITION_ACCELERATION_INIT;
    pos->injection_acceleration = E_TIM_INJECTION_ACCELERATION_INIT;
}
