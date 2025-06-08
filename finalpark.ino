#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

Servo servoEntry;
Servo servoExit;

const int IR_Entry = 2;
const int IR_Exit = 4;

const int totalSlots = 6;
int availableSlots = totalSlots;

int flagEntry = 0;
int flagExit = 0;

unsigned long lastTimeEntry = 0;
unsigned long lastTimeExit = 0;
const unsigned long delayTime = 1000;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(IR_Entry, INPUT);
  pinMode(IR_Exit, INPUT);

  servoEntry.attach(3);
  servoExit.attach(5);

  servoEntry.write(100);
  servoExit.write(100);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Parking Slots:");
  updateLCD();
}

void loop() {
  int sensorEntry = digitalRead(IR_Entry);
  int sensorExit = digitalRead(IR_Exit);

  if (sensorEntry == LOW && flagEntry == 0) {
    if (availableSlots > 0) {
      flagEntry = 1;
      servoEntry.write(0);
      availableSlots--;
      Serial.print("Car Entered. Slots available: ");
      Serial.println(availableSlots);
      updateLCD();
      lastTimeEntry = millis();
    } else {
      Serial.println("Parking is full.");
      displayFullMessage();
    }
  }

  if (sensorExit == LOW && flagExit == 0) {
    flagExit = 1;
    servoExit.write(0);
    availableSlots++;
    Serial.print("Car Exited. Slots available: ");
    Serial.println(availableSlots);
    updateLCD();
    lastTimeExit = millis();
  }

  if (millis() - lastTimeEntry >= delayTime && flagEntry == 1) {
    servoEntry.write(100);
    flagEntry = 0;
    Serial.println("Entry gate closed.");
  }

  if (millis() - lastTimeExit >= delayTime && flagExit == 1) {
    servoExit.write(100);
    flagExit = 0;
    Serial.println("Exit gate closed.");
  }
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Total Slots: ");
  lcd.print(totalSlots);
  
  lcd.setCursor(0, 1);
  lcd.print("Available: ");
  lcd.print(availableSlots);
  
  if (availableSlots == 0) {
    displayFullMessage();
  } else if (availableSlots == totalSlots) {
    displayEmptyMessage();
  }
}

void displayFullMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Parking Full!");
  lcd.setCursor(0, 1);
  lcd.print("Wait for exit.");
}

void displayEmptyMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Parking Empty!");
  lcd.setCursor(0, 1);
  lcd.print("Please Enter.");
}
