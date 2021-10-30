
/*
 * jeffs_blink
 *
 * Blinks the built-in LED every second using the arduino-timer library.
 *
 */

#include <JeffsArduinoTimingChannels.h>

#define CHANNEL_OUTPUT_PIN      7
#define CHANNEL_INITIAL_STATE   true
#define CHANNEL_ON_SECONDS      1
#define CHANNEL_OFF_SECONDS     1

TimerSchedule scheduler;

void setup() {
    TimedObject channel1 (CHANNEL_OUTPUT_PIN, CHANNEL_ON_SECONDS, CHANNEL_OFF_SECONDS, CHANNEL_INITIAL_STATE);
    scheduler.setChannel(TIMER_CHANNEL_1, channel1);
    scheduler.begin();
}

void loop() {
    // Must call tickTimers() every loop.
    scheduler.tickTimers();
    delay(1000);
}
