#pragma once
#include "stdint.h"
#include <time.h>

void animation_timer_set_startup_delay(int seconds);
void animation_timer_set_animation_duration_ms(uint32_t ms);
uint32_t animation_timer_get_animation_duration_ms();
void animation_timer_start();
void animation_timer_stop();
void animation_timer_reset();
uint32_t animation_timer_get_elapsed_time_ms();
uint64_t timespec_to_milliseconds(struct timespec* ts);
uint64_t timespec_to_nanoseconds(struct timespec* ts);

