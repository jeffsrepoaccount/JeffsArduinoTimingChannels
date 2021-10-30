#include <Arduino.h>
#include <arduino-timer.h>
#include <JeffsArduinoTimingChannels.h>

TimedObject::TimedObject(
    int outputPin,
    int onTime,
    int offTime,
    bool initialState
) {
    _outputPin = outputPin;
    _onTime = onTime;
    _offTime = offTime;
    _initialState = initialState;

    _timer = timer_create_default();
}

void TimedObject::turnOn() {
    digitalWrite(_outputPin, HIGH);
    _timer.in(_onTimeSecs * 1000, this->turnChannelOff);
    return true;
}

void TimedObject::turnOff() {
    digitalWrite(_outputPin, LOW);
    _timer.in(_offTimeSecs * 1000, this->turnChannelOn);
    return true;
}

void TimedObject::start() {
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

TimerScheduler::TimerScheduler(){}

void TimerSchedule::setChannel(int channel, TimedObject object)
{
    channels[channel] = object;
}

void TimerSchedule::begin()
{
    for (int i = 0; i < numChannels(); i++) {
        channels[i].start();
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
        channels[i].stop();
    }
}

void TimerSchedule::endChannel(int channel)
{
    channels[i].end();
}
