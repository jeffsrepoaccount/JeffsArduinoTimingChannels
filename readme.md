# Jeff's Arduino Timing Channels

Encapsulates separate output pins into different timed object channels that will oscillate between on and off states on different schedules. Built on top of [arduino-timer](https://github.com/contrem/arduino-timer).

## Use Case

Any application that needs the ability to have different things in an ON state for a period of time followed by the OFF state for a period of time in a repeating fashion. This library currently does not assume an RTC module is available or offer support for one, and is inappropriate for any application requiring specific time of day activation or deactivation.

An approach to the setup of how long something can be on and off can be used, and that is to ensure that the sum of the two times add up to a value divisible into 24 hours. The drawback to this that you must power on the board at a specific time of day, which may be impossible depending on how accurate you need to be.

## Usage

Single Channel Exaxmple

```
#include <JeffsArduinoTimingChannels.h>

#define CHANNEL_OUTPUT_PIN      7
// true indicates a channel should initially be ON
// false indicates a channel should initially be OFF
#define CHANNEL_INITIAL_STATE   true

// Timing schedules
// No RTC module assumed - each channel will be in its initial state for a
// number of seconds followed by the other state for a number of seconds in
// a repeating fashion.
#define CHANNEL_ON_SECONDS      5
#define CHANNEL_OFF_SECONDS     10

TimerSchedule scheduler;

void setup() {
    // This constructor creates a channel that is ON when HIGH, useful for things such as LEDs.
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

Multi-Channel Example for Relays

```
#include <JeffsArduinoTimingChannels.h>

// A single light channel triggering a relay, initially on 
// and running for 8 hours followed by 16 hours of being off.
#define CHANNEL1_OUTPUT_PIN     7
#define CHANNEL1_ON_SECONDS     8 * 60 * 60     // 8 hrs
#define CHANNEL1_OFF_SECONDS    16 * 60 * 60    // 16 hrs
#define CHANNEL1_INITIAL_STATE  true
// Relays switching high voltage circuits activate on LOW
#define CHANNEL1_ON_IS_HIGH        false

// A water pump channel triggering a relay, initially off 
// for 3 hours followed by 1 minute of running.
#define CHANNEL2_OUTPUT_PIN         6
#define CHANNEL2_ON_SECONDS         1 * 60          // 1 min
#define CHANNEL2_OFF_SECONDS        3 * 60 * 60     // 3 hrs
#define CHANNEL2_INITIAL_STATE      false
// Another way to think of this parameter
#define CHANNEL2_SWITCHES_NORMALLY  false

TimerSchedule scheduler;

void setup() {
    TimedObject channel1 (
        CHANNEL1_OUTPUT_PIN,
        CHANNEL1_ON_SECONDS,
        CHANNEL1_OFF_SECONDS,
        CHANNEL1_INITIAL_STATE,
        CHANNEL1_ON_IS_HIGH
    );
    TimedObject channel2 (
        CHANNEL2_OUTPUT_PIN,
        CHANNEL2_ON_SECONDS,
        CHANNEL2_OFF_SECONDS,
        CHANNEL2_INITIAL_STATE,
        CHANNEL2_SWITCHES_NORMALLY
    );

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

Adds an object and sets it into the specific channel. Use predefined `TIMER_CHANNEL_N` constants where `N` can be channels `1-4`

**void begin();**

Puts channels into their initial state and starts the timers. Must be called in setup().

**void tickTimers();**

Advances timers. Must be called once every loop.

**void end();**

Turns off all channels and stops the timers.

**void endChannel(int channel);**

Turns off a specific channel and stops its timer.

## Timed Object Constructors

By default, we assume things are normal and when ON the output pin should be HIGH.

```

TimedObject(
    int outputPin,
    int onTimeSecs,
    int offTimeSecs,
    bool initialState
);
```

Some things, such as relays, may not work this way. When they are ON the output pin should be LOW.

```
TimedObject(
    int outputPin,
    int onTime,
    int offTime,
    bool initialState,
    bool switchesNormally
);
```

---

This is _my_ library for creating timing channels in my arduino projects. I put it out into the unvierse because it may find it useful, but the universe is big and I am small. If you find it useful send kudos to [arduino-timer](https://github.com/contrem/arduino-timer). No warranty given or implied, use at your own risk, always wear safety equipment, and always be wary of high voltage sources of electricity. Released under the [3-Clause BSD License](https://opensource.org/licenses/BSD-3-Clause).