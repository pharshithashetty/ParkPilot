#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servoEntry; // Servo for entry gate
Servo servoExit;  // Servo for exit gate

const int IR_Entry = 2;  // IR sensor for entry
const int IR_Exit = 4;   // IR sensor for exit

int Slot = 6;            // Total number of parking slots

int flagEntry = 0;
int flagExit = 0;

unsigned long lastTimeEntry = 0; // Variable to store the last time the entry gate was opened
unsigned long lastTimeExit = 0;  // Variable to store the last time the exit gate was opened
const unsigned long delayTime = 1000; // Time to wait before closing the gate

void setup() {
  pinMode(IR_Entry, INPUT);
  pinMode(IR_Exit, INPUT);

  servoEntry.attach(3); // Attach servo for entry gate to pin 3
  servoExit.attach(5);  // Attach servo for exit gate to pin 5

  servoEntry.write(100); // Initial position of the entry gate servo
  servoExit.write(100);  // Initial position of the exit gate servo

  Serial.begin(9600); // Initialize serial communication for debugging

  lcd.init();                      // Initialize the lcd
  lcd.backlight();                 // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Slots avail: ");
  lcd.setCursor(0, 1);
  lcd.print(Slot);                 // Display initial number of slots available
}

void loop() {
  int sensorEntry = digitalRead(IR_Entry);
  int sensorExit = digitalRead(IR_Exit);

  // Car entering
  if (sensorEntry == LOW && flagEntry == 0) {
    if (Slot > 0) {
      flagEntry = 1;
      servoEntry.write(0); // Open the entry gate
      Slot--;
      Serial.print("Car Entered. Slots available: ");
      Serial.println(Slot);
      updateLCD();
      lastTimeEntry = millis(); // Record the time the entry gate was opened
    } else {
      Serial.println("Parking is full.");
    }
  }

  // Car exiting
  if (sensorExit == LOW && flagExit == 0) {
    flagExit = 1;
    servoExit.write(0); // Open the exit gate
    Slot++;
    Serial.print("Car Exited. Slots available: ");
    Serial.println(Slot);
    updateLCD();
    lastTimeExit = millis(); // Record the time the exit gate was opened
  }

  // Close the entry gate after delay time
  if (millis() - lastTimeEntry >= delayTime && flagEntry == 1) {
    servoEntry.write(100); // Close the entry gate
    flagEntry = 0;
    Serial.println("Entry gate closed.");
  }

  // Close the exit gate after delay time
  if (millis() - lastTimeExit >= delayTime && flagExit == 1) {
    servoExit.write(100); // Close the exit gate
    flagExit = 0;
    Serial.println("Exit gate closed.");
  }
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Slots avail: ");
  lcd.setCursor(0, 1);
  lcd.print(Slot);
}
