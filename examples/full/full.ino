
/*
 * jeffs_full
 *
 * Full example
 *
 */

#include <JeffsArduinoTimingChannels.h>

#define CHANNEL1_OUTPUT_PIN             7
#define CHANNEL1_INITIAL_STATE          true
#define CHANNEL1_ON_SECONDS             1
#define CHANNEL1_OFF_SECONDS            1

#define CHANNEL2_OUTPUT_PIN             6
#define CHANNEL2_INITIAL_STATE          false
#define CHANNEL2_ON_SECONDS             1
#define CHANNEL2_OFF_SECONDS            1

#define CHANNEL3_OUTPUT_PIN             5
#define CHANNEL3_INITIAL_STATE          true
#define CHANNEL3_ON_SECONDS             2
#define CHANNEL3_OFF_SECONDS            4

#define CHANNEL4_OUTPUT_PIN             8
#define CHANNEL4_INITIAL_STATE          false
#define CHANNEL4_SWITCHES_NORMALLY      false
#define CHANNEL4_ON_SECONDS             1
#define CHANNEL4_OFF_SECONDS            1

TimerSchedule scheduler;

void setup() {
    // These all "switch normally" (LEDs)
    TimedObject channel1 (CHANNEL1_OUTPUT_PIN, CHANNEL1_ON_SECONDS, CHANNEL1_OFF_SECONDS, CHANNEL1_INITIAL_STATE);
    TimedObject channel2 (CHANNEL2_OUTPUT_PIN, CHANNEL2_ON_SECONDS, CHANNEL2_OFF_SECONDS, CHANNEL2_INITIAL_STATE);
    TimedObject channel3 (CHANNEL3_OUTPUT_PIN, CHANNEL3_ON_SECONDS, CHANNEL3_OFF_SECONDS, CHANNEL3_INITIAL_STATE);
    // This channel will digitalWrite LOW when ON
    TimedObject channel4 (CHANNEL4_OUTPUT_PIN, CHANNEL4_ON_SECONDS, CHANNEL4_OFF_SECONDS, CHANNEL4_INITIAL_STATE, CHANNEL4_SWITCHES_NORMALLY);
    
    scheduler.setChannel(TIMER_CHANNEL_1, channel1);
    scheduler.setChannel(TIMER_CHANNEL_2, channel2);
    scheduler.setChannel(TIMER_CHANNEL_3, channel3);
    scheduler.setChannel(TIMER_CHANNEL_4, channel4);
    scheduler.begin();
}

void loop() {
    scheduler.tickTimers();
    delay(1000);
}
