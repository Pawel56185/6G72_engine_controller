/*
 * dwt_timer.c
 *
 *  Created on: 17 maj 2026
 *      Author: Pmajc
 */

#include "dwt_timer.h"

void DWT_Init(void) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

uint32_t DWT_GetMicros(void) {
    return (DWT->CYCCNT / CPU_FREQ_MHZ);
}


