/*
 * timing.c
 *
 * Created on: 4 maj 2026
 * Author: Pmajc
 */
#include "enc_timing.h"
#include "dwt_timer.h"
#include "stm32f4xx_hal.h"

const uint8_t ign_map[31] = {
    5, 5, 5, 6, 7,      // 0 - 800 RPM
    8, 9, 10, 11, 12,   // 1000 - 1800 RPM
    13, 14, 15, 17, 18, // 2000 - 2800 RPM
    20, 22, 24, 26, 27, // 3000 - 3800 RPM
    29, 30, 31, 32, 33, // 4000 - 4800 RPM
    34, 34, 35, 35, 35, // 5000 - 5800 RPM
    35                  // 6000 RPM
};
uint8_t get_ignition_advance(uint16_t rpm);
uint32_t calculate_us_per_deg(uint32_t us, uint8_t degs_qt);
uint16_t us_per_deg_to_rpm(uint32_t us_per_deg);
uint16_t get_dwell_angle(uint32_t us_per_deg);
void start_spark_timer(uint32_t us);
void order_spark_event(engine_position_and_timing* pos);

void encoder_init(engine_position_and_timing* pos){
	pos->which_cylinder = E_TIM_CYLINDER_UNKNOWN;
	pos->sparse_falling_occurred = FALSE;
	pos->sparse_rising_occurred = FALSE;
	pos->edges_past_sparse_falling = 0;
	pos->edges_past_sparse_rising = 0;
	pos->synch_detected = FALSE;
	pos->us_per_deg = INF32;
	pos->rpm = 0;
	pos->dwt_time_of_recent_falling = INF32;
	pos->edge_start = INF8;
	pos->edge_shoot = INF8;
}

void sparse_edge_callback(engine_position_and_timing* pos){
	if (ENC_SPARSE_GPIO_Port->IDR & ENC_SPARSE_Pin){
		if (pos->synch_detected){
			pos->which_cylinder = E_TIM_CYLINDER_WITH_SYNCH_HOLE+1;
			pos->synch_detected = FALSE;
		}
		else if (pos->which_cylinder > 0 && pos->which_cylinder < 7){
			pos->which_cylinder = pos->which_cylinder%6 + 1;
		}
		if (pos->sparse_falling_occurred){
			pos->us_per_deg = calculate_us_per_deg((DWT_GetMicros()-pos->dwt_time_of_recent_falling),
					pos->edges_past_sparse_falling);
			pos->rpm = us_per_deg_to_rpm(pos->us_per_deg);
			order_spark_event(pos);
		}
		pos->sparse_rising_occurred = TRUE;
		pos->edges_past_sparse_rising = 0;
	}
	else{
		if (pos->edges_past_sparse_rising > 30 && pos->edges_past_sparse_rising < 50){
			pos->synch_detected = TRUE;
		}
		pos->dwt_time_of_recent_falling = DWT_GetMicros();
		pos->sparse_falling_occurred = TRUE;
		pos->edges_past_sparse_falling = 0;
	}
}

void dense_edge_callback(engine_position_and_timing* pos){
	if (ENC_SPARSE_GPIO_Port->IDR & ENC_SPARSE_Pin){
		if (pos->sparse_rising_occurred){
			pos->edges_past_sparse_rising++;
		}
	}
	else{
		if (pos->sparse_falling_occurred){
			pos->edges_past_sparse_falling++;
		}
		if (pos->edges_past_sparse_falling == pos->edge_start){
				    start_dwell(pos);
		}
		if (pos->edges_past_sparse_falling == pos->edge_shoot){
			COIL_1_4_GPIO_Port->BSRR = COIL_1_4_Pin | COIL_2_5_Pin | COIL_3_6_Pin;
		}
	}
}

void order_spark_event(engine_position_and_timing* pos){
	uint8_t advance = get_ignition_advance(pos->rpm);
	uint8_t advance_plus_dwell = get_dwell_angle(pos->us_per_deg) + advance;
	if (advance_plus_dwell <= advance) {
		advance_plus_dwell = advance + 1;
	}
	pos->edge_shoot = E_TIM_DEGS_BETWEEN_CYLINDERS-advance-E_TIM_DEGS_IN_HIGH_SPARSE;
	if (advance_plus_dwell > 52){
		start_spark_timer(pos->us_per_deg * (E_TIM_DEGS_BETWEEN_CYLINDERS - advance_plus_dwell));
		pos->edge_start = INF8;
	}
	else {
		pos->edge_start = E_TIM_DEGS_BETWEEN_CYLINDERS-advance_plus_dwell-E_TIM_DEGS_IN_HIGH_SPARSE;
	}
}

uint8_t get_ignition_advance(uint16_t rpm) {
    if (rpm >= 6000) {
        return 35;
    }

    return ign_map[rpm / 200];
}

uint32_t calculate_us_per_deg(uint32_t us, uint8_t degs_qt){
	if (degs_qt == 0) return INF32;
	return us/degs_qt;
}

uint16_t us_per_deg_to_rpm(uint32_t us_per_deg) {
    if (us_per_deg == 0) return 0;
    return 500000 / (3 * us_per_deg);
}

uint16_t get_dwell_angle(uint32_t us_per_deg) {
    if (us_per_deg == 0) return 0;
    return 1500 / us_per_deg;
}

void start_dwell(engine_position_and_timing* pos){
	if     (pos->which_cylinder == 1 || pos->which_cylinder == 4){
		COIL_1_4_GPIO_Port->BSRR = (COIL_1_4_Pin << 16);
	}
	else if(pos->which_cylinder == 2 || pos->which_cylinder == 5){
		COIL_2_5_GPIO_Port->BSRR = (COIL_2_5_Pin << 16);
	}
	else if(pos->which_cylinder == 3 || pos->which_cylinder == 6){
		COIL_3_6_GPIO_Port->BSRR = (COIL_3_6_Pin << 16);
	}
	else{}
}

void start_spark_timer(uint32_t us){
	TIM7->ARR = us;
	TIM7->CNT = 0;
	TIM7->DIER |= TIM_DIER_UIE;
	TIM7->CR1 |= TIM_CR1_CEN;
}
