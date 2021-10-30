/*
  JeffsArduinoTimingChannels.h
  Library for timing Arduino output pins in separately timed channels. Built on top of arduino-timer by Michael Contreras.
  Created by Jeff Lambert October 2021
  Released into the universe for it to do with as it pleases.
*/
#ifndef JeffsArduinoTimingChannels_h
#define JeffsArduinoTimingChannels_h

#define MAX_TIMING_CHANNELS     4
#define TIMER_CHANNEL_1         0
#define TIMER_CHANNEL_2         1
#define TIMER_CHANNEL_3         2
#define TIMER_CHANNEL_4         3

#include <Arduino.h>
#include <arduino-timer.h>

class TimedObject
{
    private:
        int _outputPin, _onTimeSecs, _offTimeSecs;
        bool _initialState, _switchesNormally;
        Timer<> _timer;
    public:
        TimedObject();
        TimedObject(
            int outputPin,
            int onTime,
            int offTime,
            bool initialState
        );
        TimedObject(
            int outputPin,
            int onTime,
            int offTime,
            bool initialState,
            bool switchesNormally
        );
        bool turnOn();
        bool turnOff();
        void begin();
        void end();
        void tickTimer();
};

class TimerSchedule
{
    TimedObject channels[MAX_TIMING_CHANNELS];

    public:
        TimerSchedule();
        /**
         * Adds an object and sets it into the specific channel.
         */
        void setChannel(int channel, TimedObject object);
        /**
         * Puts channels into their initial state and starts the timers.
         * Should be called in setup()
         */
        void begin();
        /**
         * Must be called once every loop
         */
        void tickTimers();
        /**
         * Turns off all channels and stops the timers
         */
        void end();
        /**
         * Turns off a specific channel and stops its timer
         */
        void endChannel(int channel);
    private:
        int numChannels();
};
#endif
