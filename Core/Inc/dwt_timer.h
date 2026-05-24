/*
 * dwt_timer.h
 *
 *  Created on: 17 maj 2026
 *      Author: Pmajc
 */

#ifndef DWT_TIMER_H_
#define DWT_TIMER_H_

#include "stm32f4xx_hal.h"

#define CPU_FREQ_MHZ 168

void DWT_Init(void);  //call in main to initialize


uint32_t DWT_GetMicros(void);


#endif /* DWT_TIMER_H_ */
