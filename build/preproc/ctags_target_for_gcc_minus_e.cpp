# 1 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino"
# 2 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino" 2
# 3 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino" 2
# 4 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino" 2
# 5 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino" 2
# 6 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino" 2
# 7 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino" 2
# 8 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino" 2

int buttonPin = 2;
int servoPin = 3;
int recvPin = 4;
int ledRedPin = 9;
int ledGreenPin = 10;
int ledBluePin = 11;

Servo servo;
IRrecv irrecv(recvPin);
decode_results results;

int initialAngle = 30;
int lightOffAngle = 0;
int lightOnAngle = 60;

bool isLightOn = false;

bool isTimerMode = false;
bool isTimerSet = false;
char timerInput[3] = "\0";
unsigned long initialMillis;
unsigned long curMillis;
unsigned long remainMillis;
int milliSeconds;
int seconds;
int minutes;
int hours;

LiquidCrystal_I2C lcd(0x27, 16, 2);
char lightStatus[5];

void setup() {
    Serial.begin(9600);

    pinMode(buttonPin, 0x0);

    pinMode(ledRedPin, 0x1);
    pinMode(ledGreenPin, 0x1);
    pinMode(ledBluePin, 0x1);

    servo.attach(servoPin);
    servo.write(initialAngle);

    irrecv.enableIRIn();

    setLedColor("white");

    lcd.init();
    lcd.backlight();
}

void loop() {
    curMillis = millis();
/* 

    if (isTimerSet && atoi(timerInput) != 0 && curMillis - initialMillis >= atoi(timerInput)*60000) {   //Timer Ended

        isLightOn = false;

        servoControl(false);



        isTimerMode = false;

        isTimerSet = false;



        remainMillis = 0;

        hours = 0;

        minutes = 0;

        seconds = 0;

        milliSeconds = 0;



        lcd.clear();



        setLedColor("blink");

    } */
# 81 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino"
    if (!isTimerMode) {
        if (!isLightOn) {
            strcpy(lightStatus, "OFF");
        } else if (isLightOn) {
            strcpy(lightStatus, "ON");
        }
        lcd.setCursor(0, 0);
        lcd.print("Light Switcher");
        lcd.setCursor(0, 1);
        lcd.print(String("Current: ") + lightStatus);
    } else if (isTimerMode && !isTimerSet) {
        lcd.setCursor(0, 0);
        lcd.print("Set Timer");
        lcd.setCursor(0, 1);
        lcd.print(String("Type: ") + atoi(timerInput) + String("minutes"));
    } else if (isTimerMode && isTimerSet) {
        remainMillis = atoi(timerInput)*60000 - (curMillis - initialMillis);
        hours = remainMillis / (1000ul * 60ul * 60ul);
        minutes = (remainMillis % (1000ul * 60ul * 60ul)) / (1000ul * 60ul);
        seconds = ((remainMillis % (1000ul * 60ul * 60ul)) % (1000ul * 60ul)) / 1000ul;
        milliSeconds = ((remainMillis % (1000ul * 60ul * 60ul)) % (1000ul * 60ul)) % 1000ul;
        lcd.setCursor(0, 0);
        lcd.print("Light off after");
        lcd.setCursor(0, 1);
        lcd.print(hours + String("h ") + minutes + String("m ") + seconds + String("s ") + milliSeconds + String("ms  "));
        if (remainMillis <= 100ul) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Light turned off");
            lcd.setCursor(0, 1);
            lcd.print(hours + String("h ") + minutes + String("m ") + seconds + String("s ") + 0 + String("ms"));

            isLightOn = false;
            servoControl(false);

            isTimerMode = false;
            isTimerSet = false;

            timerInput[0] = '\0';

            remainMillis = 0;
            hours = 0;
            minutes = 0;
            seconds = 0;
            milliSeconds = 0;

            delay(3000);
            lcd.clear();

            setLedColor("blink");
/*             exit(0); */
        }
    }

    if (irrecv.decode(&results)) {
        Serial.println(results.value, 16);

        switch (results.value) {
            case 0xFFE01F: //-
                isLightOn = false;
                servoControl(false);
                lcd.clear();
                break;

            case 0xFFA857: //+
                isLightOn = true;
                servoControl(true);
                lcd.clear();
                break;

            case 0xFFC23D: //Play/Pause
                if (!isTimerMode) { //Start Timer Setting Mode
                    isTimerMode = true;
                    setLedColor("yellow");
                    lcd.clear();
                } else if (isTimerMode) {
                    if (!isTimerSet) { //Set Timer
                        isTimerSet = true;
                        initialMillis = millis();
                        setLedColor("green");
                        lcd.clear();
                    } else if (isTimerSet) { //Reset Timer
                        timerInput[0] = '\0';
                        isTimerSet = false;
                        isTimerMode = false;
                        setLedColor("red");
                        lcd.clear();
                    }
                }
                break;

            case 0xFF6897: //0
                if (isTimerMode && !isTimerSet) {
                    strcat(timerInput, "0");
                }
                break;

            case 0xFF30CF: //1
                if (isTimerMode && !isTimerSet) {
                    strcat(timerInput, "1");
                }
                break;

            case 0xFF18E7: //2
                if (isTimerMode && !isTimerSet) {
                    strcat(timerInput, "2");
                }
                break;

            case 0xFF7A85: //3
                if (isTimerMode && !isTimerSet) {
                    strcat(timerInput, "3");
                }
                break;

            case 0xFF10EF: //4
                if (isTimerMode && !isTimerSet) {
                    strcat(timerInput, "4");
                }
                break;

            case 0xFF38C7: //5
                if (isTimerMode && !isTimerSet) {
                    strcat(timerInput, "5");
                }
                break;

            case 0xFF5AA5: //6
                if (isTimerMode && !isTimerSet) {
                    strcat(timerInput, "6");
                }
                break;

            case 0xFF42BD: //7
                if (isTimerMode && !isTimerSet) {
                    strcat(timerInput, "7");
                }
                break;

            case 0xFF4AB5: //8
                if (isTimerMode && !isTimerSet) {
                    strcat(timerInput, "8");
                }
                break;

            case 0xFF52AD: //9
                if (isTimerMode && !isTimerSet) {
                    strcat(timerInput, "9");
                }
                break;

            default:
                break;
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
    if (!onOff) {
        servo.write(lightOffAngle);
        delay(1000);
        servo.write(initialAngle);
    } else if (onOff) {
        servo.write(lightOnAngle);
        delay(1000);
        servo.write(initialAngle);
    }
}

void setLedColor(char color[10]) {
    if (color == "red") {
        analogWrite(ledRedPin, 255);
        analogWrite(ledGreenPin, 0);
        analogWrite(ledBluePin, 0);
        delay(1000);
        analogWrite(ledRedPin, 0);
        analogWrite(ledGreenPin, 0);
        analogWrite(ledBluePin, 0);
    } else if (color == "green") {
        analogWrite(ledRedPin, 0);
        analogWrite(ledGreenPin, 255);
        analogWrite(ledBluePin, 0);
        delay(1000);
        analogWrite(ledRedPin, 0);
        analogWrite(ledGreenPin, 0);
        analogWrite(ledBluePin, 0);
    } else if (color == "yellow") {
        analogWrite(ledRedPin, 255);
        analogWrite(ledGreenPin, 255);
        analogWrite(ledBluePin, 0);
        delay(1000);
        analogWrite(ledRedPin, 0);
        analogWrite(ledGreenPin, 0);
        analogWrite(ledBluePin, 0);
    } else if (color == "white") {
        analogWrite(ledRedPin, 255);
        analogWrite(ledGreenPin, 255);
        analogWrite(ledBluePin, 255);
        delay(1000);
        analogWrite(ledRedPin, 0);
        analogWrite(ledGreenPin, 0);
        analogWrite(ledBluePin, 0);
    } else if (color == "blink") {
        for (int i = 0; i < 2; i++) {
            analogWrite(ledRedPin, 255);
            analogWrite(ledGreenPin, 0);
            analogWrite(ledBluePin, 0);
            delay(500);
            analogWrite(ledRedPin, 0);
            analogWrite(ledGreenPin, 0);
            analogWrite(ledBluePin, 0);
            delay(500);
        }
    }
}
