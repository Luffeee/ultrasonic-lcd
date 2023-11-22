#include <string>
#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

class UltrasonicSensor
{
public:
    UltrasonicSensor(int triggerPin, int echoPin);
    void initialize();
    long readDistance();
    std::string readDist();

private:
    int triggerPin;
    int echoPin;
    long duration, distance;
    void triggerPulse();
};
#endif