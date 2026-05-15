/*
 * silnik_krokowy.c
 *
 *  Created on: 29 kwi 2026
 *      Author: Pmajc
 */
#include "stepper_motor.h"
#include "main.h"


uint8_t current_stepper_position = 0;

GPIO_PinState state_winding_1[8] = {
    GPIO_PIN_SET,   GPIO_PIN_SET,   GPIO_PIN_RESET, GPIO_PIN_RESET,
    GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET
};
GPIO_PinState state_winding_4[8] = {
    GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET,
    GPIO_PIN_SET,   GPIO_PIN_SET,   GPIO_PIN_RESET, GPIO_PIN_RESET
};
GPIO_PinState state_winding_2[8] = {
    GPIO_PIN_RESET, GPIO_PIN_SET,   GPIO_PIN_SET,   GPIO_PIN_SET,
    GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET
};
GPIO_PinState state_winding_3[8] = {
    GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET,
    GPIO_PIN_RESET, GPIO_PIN_SET,   GPIO_PIN_SET,   GPIO_PIN_SET
};

void throttle_motor_step(int8_t dir) {
	if (dir == S_MOTOR_DIR_OPEN) {
		current_stepper_position = (current_stepper_position + 1) % 8;
	}
	else if (dir == S_MOTOR_DIR_CLOSE) {
		current_stepper_position = (current_stepper_position + 7) % 8;
	}
}

void update_stepper_control(void) {
	HAL_GPIO_WritePin(STEP_1_GPIO_Port, STEP_1_Pin, state_winding_1[current_stepper_position]);
	HAL_GPIO_WritePin(STEP_2_GPIO_Port, STEP_2_Pin, state_winding_2[current_stepper_position]);
	HAL_GPIO_WritePin(STEP_3_GPIO_Port, STEP_3_Pin, state_winding_3[current_stepper_position]);
	HAL_GPIO_WritePin(STEP_4_GPIO_Port, STEP_4_Pin, state_winding_4[current_stepper_position]);
}

void stepper_motor_controller_init(stepper_motor_t* motor_ins) {
    if (motor_ins == NULL) return;

    motor_ins->motor_idle = MOTOR_IDLE_INIT;
    motor_ins->motor_based = MOTOR_BASED_INIT;
    motor_ins->low_rpm_throttle_base = LOW_RPM_THROTTLE_BASE_INIT;
    motor_ins->homing_steps = HOMING_STEPS_INIT;
    motor_ins->requested_steps_left = REQUESTED_STEPS_LEFT_INIT;
    motor_ins->stepper_motor_occupied = STEPPER_MOTOR_OCCUPIED_INIT;
    motor_ins->requested_direction = REQUESTED_DIRECTION_INIT;
    motor_ins->basing_phase = S_MOTOR_BASING_PHASE_NONE;
}

void stepper_motor_request(uint16_t steps, int8_t dir, stepper_motor_t* motor_ins) {
    if (motor_ins == NULL) return;

	motor_ins->requested_steps_left = steps;
	motor_ins->requested_direction = dir;
	motor_ins->stepper_motor_occupied = S_MOTOR_TRUE;
	HAL_TIM_Base_Start_IT(&htim6);
}


void stepper_motor_controller_callback(stepper_motor_t* motor_ins) {
	if (motor_ins == NULL || motor_ins->stepper_motor_occupied == S_MOTOR_FALSE) return;

	throttle_motor_step(motor_ins->requested_direction);
	update_stepper_control();

    if (motor_ins->requested_steps_left > 0) {
	    motor_ins->requested_steps_left--;
    }

	if (motor_ins->requested_steps_left == 0) {
		if (motor_ins->basing_phase == S_MOTOR_BASING_PHASE_1) {
			motor_ins->requested_steps_left = motor_ins->low_rpm_throttle_base;
			motor_ins->requested_direction  = S_MOTOR_DIR_OPEN;
			motor_ins->basing_phase = S_MOTOR_BASING_PHASE_2;
		}
		else if (motor_ins->basing_phase == S_MOTOR_BASING_PHASE_2) {
			motor_ins->basing_phase = S_MOTOR_BASING_PHASE_NONE;
			motor_ins->motor_based = S_MOTOR_TRUE;
			motor_ins->stepper_motor_occupied = S_MOTOR_FALSE;
			HAL_TIM_Base_Stop_IT(&htim6);
		}
		else {
			motor_ins->requested_direction = REQUESTED_DIRECTION_INIT;
			motor_ins->stepper_motor_occupied = S_MOTOR_FALSE;
			HAL_TIM_Base_Stop_IT(&htim6);
		}
	}
}

void base_stepper_motor(stepper_motor_t* motor_ins){
    if (motor_ins == NULL) return;
	motor_ins->basing_phase = S_MOTOR_BASING_PHASE_1;
	stepper_motor_request(motor_ins->homing_steps, S_MOTOR_DIR_CLOSE, motor_ins);
}
