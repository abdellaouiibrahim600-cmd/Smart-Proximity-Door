#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myServo;
#define SERVO_PIN 19

#define TRIG_PIN 5
#define ECHO_PIN 18

#define LED_GREEN 2
#define LED_RED   4
#define BUZZER    15

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH); 
  digitalWrite(BUZZER, LOW);

  myServo.attach(SERVO_PIN);
  myServo.write(0); 
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Proximity");
  lcd.setCursor(0, 1);
  lcd.print("Door Locked     ");
}

void loop() {
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

 
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < 20) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Granted! ");
    lcd.setCursor(0, 1);
    lcd.print("Welcome Home :) ");
    
    digitalWrite(LED_RED, LOW);  
    digitalWrite(LED_GREEN, HIGH); 
    myServo.write(90);          
    delay(4000);                 
    myServo.write(0);          
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH); 

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Smart Proximity");
    lcd.setCursor(0, 1);
    lcd.print("Door Locked     ");
  }

  delay(500);
}