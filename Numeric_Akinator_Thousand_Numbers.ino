// RESEARCH AND DEVELOPMENT (R&D) PROJECT
// Created by: Gabriel Correia
// Project Developed for Onda Elétrica

// Importing libraries (make sure it's compatible with the I2C LCD)
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C LCD address (adjust if necessary)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Button pins
const int buttonYesPin = 2;  // YES button (SIM)
const int buttonNoPin = 3;   // NO button (NO)

// LEDs (optional)
const int ledGreenPin = 11;  // Green LED pin
const int ledYellowPin = 12; // Yellow LED pin
const int ledRedPin = 13;    // Red LED pin

// Variables
int buttonYesState = 0;
int buttonNoState = 0;
int minNum = 1; // Start number
int maxNum = 999;
int guess;
int questionCount = 0;
const int maxQuestions = 10; // Maximum number of questions

void setup() {
  // Pin configuration
  pinMode(buttonYesPin, INPUT_PULLUP);
  pinMode(buttonNoPin, INPUT_PULLUP);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledYellowPin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);
  
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  // Initial message
  lcd.setCursor(0, 0);
  lcd.print("Think of a number");
  lcd.setCursor(0, 1);
  lcd.print("between 1 and 999");
  delay(3000);
  lcd.clear();
  
  // First guess
  guess = (minNum + maxNum) / 2;
  lcd.setCursor(0, 0);
  lcd.print("Is it strictly");
  lcd.setCursor(0, 1);
  lcd.print("greater than ");
  lcd.print(guess);
  lcd.print("?");
}

void loop() {
  // Read the state of the buttons
  buttonYesState = digitalRead(buttonYesPin);
  buttonNoState = digitalRead(buttonNoPin);
  digitalWrite(ledYellowPin, HIGH);

  if (questionCount < maxQuestions) {
    if (buttonYesState == LOW) {
      // YES button pressed
      minNum = guess + 1;
      questionCount++;
      nextGuess();
      delay(500); // Small delay to avoid multiple button readings
    } else if (buttonNoState == LOW) {
      // NO button pressed
      maxNum = guess; // Adjust to include the guess
      questionCount++;
      nextGuess();
      delay(500); // Small delay to avoid multiple button readings
    }
  } else {
    // After 10 questions, make the final statement
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("The number is ");
    lcd.print(guess);
    lcd.setCursor(0, 1);
    lcd.print("Did we guess?");
    digitalWrite(ledGreenPin, HIGH);
    digitalWrite(ledYellowPin, LOW);
    delay(5000);
    resetGame();
  }

  // Check if the limits have crossed
  if (minNum > maxNum) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error! Restart.");
    delay(3000);
    resetGame();
  }
}

void nextGuess() {
  guess = (minNum + maxNum) / 2;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Is it strictly");
  lcd.setCursor(0, 1);
  lcd.print("greater than ");
  lcd.print(guess);
  lcd.print("?");
}

void resetGame() {
  // Restart the game
  minNum = 1; // Reset to start number
  maxNum = 999;
  guess = (minNum + maxNum) / 2;
  questionCount = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("New game!");
  digitalWrite(ledGreenPin, LOW);
  digitalWrite(ledYellowPin, HIGH);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Think of a number");
  lcd.setCursor(0, 1);
  lcd.print("between 1 and 999");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Is it strictly");
  lcd.setCursor(0, 1);
  lcd.print("greater than ");
  lcd.print(guess);
  lcd.print("?");
}
