/*
 * silnik_krokowy.h
 *
 *  Created on: 29 kwi 2026
 *      Author: Pmajc
 */

#ifndef STEPPER_MOTOR_H_
#define STEPPER_MOTOR_H_

#include "stm32f4xx_hal.h"

#define INITIAL_WINDINGS_STATE      0
#define BASE_LOW_THROTTLE           (uint16_t)100
#define STEPS_FOR_HOMING            (uint16_t)500
#define MOTOR_IDLE_INIT             1
#define MOTOR_BASED_INIT            0
#define LOW_RPM_THROTTLE_BASE_INIT  200
#define HOMING_STEPS_INIT           370
#define REQUESTED_STEPS_LEFT_INIT   0
#define STEPPER_MOTOR_OCCUPIED_INIT 0
#define REQUESTED_DIRECTION_INIT    0

// state flags
#define S_MOTOR_TRUE                1
#define S_MOTOR_FALSE               0

// basing phases
#define S_MOTOR_BASING_PHASE_NONE   0
#define S_MOTOR_BASING_PHASE_1      1
#define S_MOTOR_BASING_PHASE_2      2

// motor directions
#define S_MOTOR_DIR_OPEN            1
#define S_MOTOR_DIR_CLOSE          -1

extern TIM_HandleTypeDef htim6;

typedef struct {
	uint8_t motor_idle;
	uint8_t motor_based;
	uint16_t low_rpm_throttle_base;
	uint16_t homing_steps;
	uint16_t requested_steps_left;
	uint8_t stepper_motor_occupied;
	int8_t requested_direction;
	uint8_t basing_phase;
} stepper_motor_t;

extern stepper_motor_t moj_silnik;

void throttle_motor_step(int8_t dir);
void update_stepper_control(void);
void stepper_motor_controller_init(stepper_motor_t* motor_ins);
void stepper_motor_request(uint16_t steps, int8_t dir, stepper_motor_t* motor_ins);
void stepper_motor_controller_callback(stepper_motor_t* motor_ins);
void base_stepper_motor(stepper_motor_t* motor_ins);

#endif /* STEPPER_MOTOR_H_ */
