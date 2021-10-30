# Jeffs Arduino Timing Channels
---

Encapsulates separate output pins into different timed object channels that will oscillate between on and off states on different schedules. Built on top of [arduino-timer](https://github.com/contrem/arduino-timer) by Michael Contreras.

## Use Case

Any application that needs the ability to have different things in an ON state for a period of time followed by the OFF state for a period of time in a repeating fashion. This library currently does not assume a RTC module is available or offer support for one, and is inappropriate for any application requiring specific time of day activation or deactivation.

An approach to the setup of how long something can be on and off can be used, and that is to ensure that the sum of the two times add up to exactly 24 hours. The drawback to this approach would be you only get 1 activation/deactivation cycle per day, and, depending on how accurate you need to be, must initially power on the board only at a specific time of day.

## Usage

Single Channel Exaxmple

```
#include <JeffsArduinoTimingChannels.h>

#define CHANNEL_OUTPUT_PIN      7
#define CHANNEL_INITIAL_STATE   true

// Timing schedules
// No RTC module assumed - each channel will be in its initial state for a
// number of seconds followed by the other state for a number of seconds in
// a repeating fashion.
#define CHANNEL_ON_SECONDS      8 * 60 * 60     // 8 hrs
#define CHANNEL_OFF_SECONDS     16 * 60 * 60    // 16 hrs

TimerSchedule scheduler();

void setup() {
    TimedObject channel1 (CHANNEL_OUTPUT_PIN, CHANNEL_ON_SECONDS, CHANNEL_OFF_SECONDS, CHANNEL_INITIAL_STATE);
    scheduler.setChannel(TIMER_CHANNEL_1, channel1);

    // Must call begin() in setup, will set the channels to their initial state
    // and start their timers.
    scheduler.begin();
}

void loop() {
    // Must call tickTimers() every loop.
    scheduler.tickTimers();
    delay(1000);
}
```

Multiple Channel Exaxmple

```
#include <JeffsArduinoTimingChannels.h>

// A single light channel, initially on and running for 8 hours followed by 16 hours of being off.
#define CHANNEL1_OUTPUT_PIN     7
#define CHANNEL1_ON_SECONDS     8 * 60 * 60     // 8 hrs
#define CHANNEL1_OFF_SECONDS    16 * 60 * 60    // 16 hrs
#define CHANNEL1_INITIAL_STATE  true

// A water pump channel, initially off for 1 hour followed by 1 minute of running.
#define CHANNEL2_OUTPUT_PIN     6
#define CHANNEL2_ON_SECONDS     1 * 60          // 1 min
#define CHANNEL2_OFF_SECONDS    1 * 60 * 60     // 1 hr
#define CHANNEL2_INITIAL_STATE  false

TimerSchedule scheduler();

void setup() {
    TimedObject channel1 (CHANNEL1_OUTPUT_PIN, CHANNEL1_ON_SECONDS, CHANNEL1_OFF_SECONDS, CHANNEL1_INITIAL_STATE);
    TimedObject channel2 (CHANNEL2_OUTPUT_PIN, CHANNEL2_ON_SECONDS, CHANNEL2_OFF_SECONDS, CHANNEL2_INITIAL_STATE);

    scheduler.setChannel(TIMER_CHANNEL_1, channel1);
    scheduler.setChannel(TIMER_CHANNEL_2, channel2);

    scheduler.begin();
}

void loop() {
    scheduler.tickTimers();
    delay(1000);
}
```

## Available Scheduler Methods

**void setChannel(int channel, TimedObject object);** 
Adds an object and sets it into the specific channel.

**void begin();**
Should be called in setup(). Puts channels into their initial state and starts the timers.

**void tickTimers();**
Must be called once every loop.

**void end();**
Turns off all channels and stops the timers.

**void endChannel(int channel);**
Turns off a specific channel and stops its timer.
