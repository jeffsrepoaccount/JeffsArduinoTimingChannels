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
        int _outputPin, _onTime, _offTime;
        bool _initialState;
        Timer<> _timer;
    public:
        TimedObject(
            int outputPin,
            int onTime,
            int offTime,
            bool initialState
        );
        void turnOn();
        void turnOff();
        void start();
        void stop();
        void tickTimer();
};

class TimerSchedule
{
    TimedObject channels[MAX_TIMING_CHANNELS];

    public:
        TimerScheduler();
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
        void stopChannels();
        /**
         * Turns off a specific channel and stops its timer
         */
        void stopChannel(int channel);
    private:
        int numChannels();
};
#endif