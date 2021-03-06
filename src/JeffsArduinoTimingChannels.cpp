#include <Arduino.h>
#include <arduino-timer.h>
#include <JeffsArduinoTimingChannels.h>

TimedObject::TimedObject() {

}

TimedObject::TimedObject(
    int outputPin,
    int onTimeSecs,
    int offTimeSecs,
    bool initialState
) {
    _outputPin = outputPin;
    _onTimeSecs = onTimeSecs;
    _offTimeSecs = offTimeSecs;
    _initialState = initialState;

    _switchesNormally = true;

    _timer = timer_create_default();
}

TimedObject::TimedObject(
    int outputPin,
    int onTimeSecs,
    int offTimeSecs,
    bool initialState,
    bool switchesNormally = true
) {
    _outputPin = outputPin;
    _onTimeSecs = onTimeSecs;
    _offTimeSecs = offTimeSecs;
    _initialState = initialState;

    _switchesNormally = switchesNormally;

    _timer = timer_create_default();
}

bool TimedObject::turnOn() {
    if(_switchesNormally) {
        digitalWrite(_outputPin, HIGH);
    } else {
        digitalWrite(_outputPin, LOW);
    }

    // this line needs to be a callback to an instance method
    _timer.in(_onTimeSecs * 1000, this.turnOff);
    return true;
}

bool TimedObject::turnOff() {
    if(_switchesNormally) {
        digitalWrite(_outputPin, LOW);
    } else {
        digitalWrite(_outputPin, HIGH);
    }

    // this line needs to be a callback to an instance method
    _timer.in(_offTimeSecs * 1000, this.turnOn);
    return true;
}

void TimedObject::begin() {
    pinMode(_outputPin, OUTPUT);

    if(_initialState) {
      turnOn();
    } else {
      turnOff();
    }
}

void TimedObject::end() {
    turnOff();
    _timer.cancel();
}

void TimedObject::tickTimer() {
    _timer.tick();
}

TimerSchedule::TimerSchedule()
{
    TimedObject channels[MAX_TIMING_CHANNELS];
}

void TimerSchedule::setChannel(int channel, TimedObject object)
{
    channels[channel] = object;
}

void TimerSchedule::begin()
{
    for (int i = 0; i < numChannels(); i++) {
        channels[i].begin();
    }
}

void TimerSchedule::tickTimers()
{
    for (int i = 0; i < numChannels(); i++) {
        channels[i].tickTimer();
    }
}

int TimerSchedule::numChannels()
{
    return (int)(sizeof channels / sizeof channels[0]);
}

void TimerSchedule::end()
{
    for (int i = 0; i < numChannels(); i++) {
        channels[i].end();
    }
}

void TimerSchedule::endChannel(int channel)
{
    channels[channel].end();
}
