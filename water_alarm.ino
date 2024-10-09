#include "Arduino.h"
#include "uRTCLib.h"

#include <Servo.h>

Servo myservo;

int hour = 0;
int minute = 0;
int buzzer = 7;
bool alarm = false;

// uRTCLib rtc;
uRTCLib rtc(0x68);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  Serial.begin(9600);
  delay(1000); // wait for console opening
  pinMode(buzzer, OUTPUT);

  URTCLIB_WIRE.begin();
  // rtc.set(0, 37, 17, 2, 7, 10, 24); // set only the first time
  // rtc.set(second, minute, hour, dayOfWeek, dayOfMonth, month, year)

  myservo.attach(2);
  myservo.write(90);
}

void loop() {
  rtc.refresh();
  hour = rtc.hour();
  minute = rtc.minute();

  Serial.print("hour: ");
  Serial.print(hour);
  Serial.print(" minute: ");
  Serial.print(minute);
  Serial.println("");

  if(hour==4){
    alarm = true;
  }

  if(hour==5 && minute<=5 && alarm==true){
    myservo.write(180);
    delay(3000);
    myservo.write(90);

    delay(4000);

    myservo.write(0);
    delay(2750); // less than 3000 because the weight is with the direction so it speeds it up when going back
    myservo.write(90);

    alarm = false;
  }

  if(hour==5 && minute<=15){
    tone(buzzer, 700);
    delay(400);
    noTone(buzzer);
    delay(400);
  }

}
