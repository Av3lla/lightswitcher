#include <Arduino.h>
#line 1 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino"
#include <Servo.h>
#include <IRremote.h>

int buttonPin = 2;
int servoPin = 3;
int recvPin = 4;

Servo servo;
IRrecv irrecv(recvPin);
decode_results results;

int initialAngle = 30;
int lightOffAngle = 0;
int lightOnAngle = 60;

bool isLightOn = false;

#line 18 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino"
void setup();
#line 28 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino"
void loop();
#line 55 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino"
void servoControl(bool onOff);
#line 18 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino"
void setup() {
    Serial.begin(9600);

    pinMode(buttonPin, INPUT);
    servo.attach(servoPin);
    servo.write(initialAngle);

    irrecv.enableIRIn();
}

void loop() {
    if (irrecv.decode(&results)) {
        Serial.println(results.value, HEX);

        if (results.value == 0xFF6897) {
            isLightOn = !isLightOn;
            servoControl(false);
        } else if (results.value == 0xFF30CF) {
            isLightOn = !isLightOn;
            servoControl(true);
        }

        delay(250);
        irrecv.resume();
    }

    if (digitalRead(buttonPin) == 1) {
        isLightOn = !isLightOn;
        if (isLightOn) {
            servoControl(true);
        } else {
            servoControl(false);
        }
        delay(250);
    }
}

void servoControl(bool onOff) {
    if (onOff == false) {
        servo.write(lightOffAngle);
        delay(1000);
        servo.write(initialAngle);
    } else if (onOff == true) {
        servo.write(lightOnAngle);
        delay(1000);
        servo.write(initialAngle);
    }
}
