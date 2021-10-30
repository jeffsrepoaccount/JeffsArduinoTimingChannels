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

    _timer = timer_create_default();
}

bool TimedObject::turnOn() {
    digitalWrite(_outputPin, HIGH);
    _timer.in(_onTimeSecs * 1000, this.turnOff);
    return true;
}

bool TimedObject::turnOff() {
    digitalWrite(_outputPin, LOW);
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
    digitalWrite(_outputPin, LOW);
    pinMode(_outputPin, OUTPUT);
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
