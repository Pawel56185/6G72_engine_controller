/*
 * timing.h
 *
 * Created on: 4 maj 2026
 * Author: Pmajc
 */

#ifndef INC_ENC_TIMING_H_
#define INC_ENC_TIMING_H_

#define E_TIM_CYLINDER_UNKNOWN                  0
#define E_TIM_CYLINDER_WITH_SYNCH_HOLE          4
#define E_TIM_DEGS_BETWEEN_CYLINDERS            120
#define E_TIM_DEGS_IN_HIGH_SPARSE               64
#define E_TIM_DEGS_IN_LOW_SPARSE                56

#include "main.h"

typedef struct {
	volatile uint8_t which_cylinder;
	volatile uint8_t sparse_falling_occurred;
	volatile uint8_t sparse_rising_occurred;
	volatile uint8_t edges_past_sparse_falling;
	volatile uint8_t edges_past_sparse_rising;
	volatile uint8_t synch_detected;
	volatile uint16_t rpm;
	volatile uint32_t us_per_deg;     //estimated time between dense edges
	volatile uint32_t dwt_time_of_recent_falling;
	volatile uint8_t edge_start;
	volatile uint8_t edge_shoot;
}engine_position_and_timing;

void encoder_init(engine_position_and_timing* pos);
void dense_edge_callback(engine_position_and_timing* pos);
void sparse_edge_callback(engine_position_and_timing* pos);
void start_dwell(engine_position_and_timing* pos);

#endif /* INC_ENC_TIMING_H_ */
