#include <Arduino.h>
#include "../headers/Ultrasonic.h"
#include <string>

unsigned long pMbuz = 0;
bool buzzState = LOW;

void buzz(int buzzerPin, unsigned long currentMillis, unsigned long previousMillis, unsigned long interval)
{
    if (currentMillis - previousMillis >= interval)
    {
        pMbuz = currentMillis;
        buzzState = !buzzState;
        digitalWrite(buzzerPin, buzzState);
        digitalWrite(4, buzzState);
    }
}

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin)
{
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
}

void UltrasonicSensor::initialize()
{
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void UltrasonicSensor::triggerPulse()
{
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
}

long UltrasonicSensor::readDistance()
{
    triggerPulse();
    duration = pulseIn(echoPin, HIGH, 100000);
    distance = duration * 0.0343 / 2;
    return distance;
}

std::string UltrasonicSensor::readDist()
{
    if (distance <= 10 && distance > 6)
    {
        buzz(15, millis(), pMbuz, 600);
        return "Close";
    }
    else if (distance <= 6 && distance > 0)
    {
        buzz(15, millis(), pMbuz, 1);
        return "Too close";
    }
    else if (distance == 0)
    {
        digitalWrite(15, 0);
        digitalWrite(4, 0);
        return "Not Detected";
    }
    else
    {
        digitalWrite(15, 0);
        digitalWrite(4, 0);
        return "Far";
    }
}