#include "animation_timer.h"

static const uint32_t MAX_ANIMATION_DURATION_MS = 60 * 1000;

static uint32_t _animation_duration_ms = 0;
static uint64_t _animation_start_time_ms = 0;
static uint64_t _animation_stop_time_ms = 0;
// static uint64_t _current_time_ms = 0;

void animation_timer_set_startup_delay(int seconds) {

}

void animation_timer_set_animation_duration_ms(uint32_t ms) {
    if (ms > MAX_ANIMATION_DURATION_MS) _animation_duration_ms = MAX_ANIMATION_DURATION_MS;
    else {
        _animation_duration_ms = ms;
    }
}

uint32_t animation_timer_get_animation_duration_ms() {
    return _animation_duration_ms;
}

static uint64_t _get_current_realtime_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

void animation_timer_start() {
    _animation_start_time_ms = _get_current_realtime_ms();
}

void animation_timer_stop() {
    // _animation_stop_time_ms = _get_current_realtime_ms();
}

void animation_timer_reset() {
    _animation_start_time_ms = 0;
    // _current_time_ms = 0;
}

uint32_t animation_timer_get_elapsed_time_ms() {
    uint64_t current_time = _get_current_realtime_ms();
    return current_time - _animation_start_time_ms;
}

uint64_t timespec_to_milliseconds(struct timespec* ts) {
    return (uint64_t)ts->tv_sec * 1000 + (uint64_t)ts->tv_nsec / 1000000;
}

uint64_t timespec_to_nanoseconds(struct timespec* ts) {
    return (uint64_t)ts->tv_sec * 1000000000UL + (uint64_t)ts->tv_nsec;
}