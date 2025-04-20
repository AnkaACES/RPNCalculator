// PROJECT  :RPN Calculator
// PURPOSE  :Understand Object-Oriented Programming and stacks
// COURSE   :ICS3U-E1
// AUTHOR   :Anka Shen
// DATE     :April 21 2025
// MCU      :328P
// STATUS   :Working
// Reference:http://darcy.rsgc.on.ca/ACES/TEI3M/Tasks.html#RPN

// include the libraries
#include "Stack.h"
#include <LiquidCrystal.h>

// set up the LCD
uint8_t RS = 9, EN = 8, D4 = 7, D5 = 6, D6 = 5, D7 = 4;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// define the input pin from the keypad
#define KEYPAD A5

// delay after reading key
uint16_t DURATION = 300;

// map the characters to their voltage values using arrays
uint16_t thresholds[] = {55, 58, 62, 66, 76, 81, 88, 97, 116, 132, 152, 179, 255, 341, 512, 1024};
char keys[] = {'+', 'E', '.', '0', '-', '3', '2', '1', '*', '6', '5', '4', '/', '9', '8', '7'};

// create an object of the Stack class called stack
Stack stack;

void setup() {
  lcd.begin(LCD_COLUMNS, LCD_ROWS);           // set up the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  pinMode(KEYPAD, INPUT);                     // set the input pin from the keypad to input mode
}

char getKey() {                               // gets the key from presses
  uint16_t value = 0;
  while ((value = analogRead(KEYPAD)) == 0);  // wait until a key is pressed
  delay(DURATION);                            // wait a bit after a key is pressed
  uint8_t i = 0;
  while (value > thresholds[i]) {             // matching the keys to their voltage values...
    i++;
  }
  return keys[i];                             // return the correct key
}

void printExpression(char op, float a, float b) {   // prints the expression
  lcd.setCursor(0, 0);
  lcd.print(a);
  lcd.print(op);
  lcd.print(b);
}

void printResult(float result) {        // prints the result of calculations
  char buffer[16];                      // create a buffer array to put the characters in
  dtostrf(result, 16, 4, buffer);       // turn the result from a float to a formatted string
  lcd.setCursor(0, 1);
  lcd.print(buffer);                    // print the result on the bottom line of the LCD
}

void add() {                        // adds the top two numbers on the stack
  float b = stack.pop();            // gets the top two numbers on the stack
  float a = stack.pop();
  float result = a + b;             // adding
  stack.push(result);               // push the result onto the stack
  printExpression('+', a, b);
  printResult(result);
}

void subtract() {                   // subtracts the top two numbers on the stack, same logic as add
  float b = stack.pop();
  float a = stack.pop();
  float result = a - b;
  stack.push(result);
  printExpression('-', a, b);
  printResult(result);
}

void multiply() {                   // subtracts the top two numbers on the stack, same logic as add
  float b = stack.pop();
  float a = stack.pop();
  float result = a * b;
  stack.push(result);
  printExpression('*', a, b);
  printResult(result);
}

void divide() {                     // subtracts the top two numbers on the stack, same logic as add
  float b = stack.pop();
  float a = stack.pop();
  float result = a / b;
  stack.push(result);
  printExpression('/', a, b);
  printResult(result);
}

// variables for the runCalculator function
float num = 0;
float mult = 0.1;
bool isDecimal = false;
bool isDisplayingResult = false;

void runCalculator() {                    // runs the calculator
  char ch;
  lcd.setCursor(0, 0);
  while (true) {                          // loop for entering numbers and decimals
    ch = getKey();                        // get the key that is pressed
    lcd.print(ch);
    if (ch == 'E') {                      // if enter key is pressed
      stack.push(num);                    // push the number onto the stack
      lcd.clear();                        // clear LCD
      num = 0;                            // reset all the variables
      mult = 0.1;
      isDecimal = false;
      break;
    } else if (ch == '+') {               // if + key is pressed
      add();                              // add
      isDisplayingResult = true;          // the LCD is displaying the result
      break;
    } else if (ch == '-') {               // if - key is pressed, same logic as +
      subtract();
      isDisplayingResult = true;
      break;
    } else if (ch == '*') {               // if - key is pressed, same logic as +
      multiply();
      isDisplayingResult = true;
      break;
    } else if (ch == '/') {               // if - key is pressed, same logic as +
      divide();
      isDisplayingResult = true;
      break;
    } else if (ch == '.') {               // turns on decimal mode
      isDecimal = true;
    } else if (ch >= '0' && ch <= '9') {  // if a digit key is pressed
      if (isDisplayingResult) {           // resets LCD if it was displaying the result
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(ch);                    // print the new input
        isDisplayingResult = false;       // not displaying the result anymore
      }
      if (!isDecimal) {                   // if decimal mode is not on
        num = num * 10 + (ch - '0');
      } else {                            // if decimal mode is on
        num = num + mult * (ch - '0');
        mult = mult * 0.1;
      }
    }
  }
}

void loop() {
  runCalculator();    // run the calculator repeatedly
}