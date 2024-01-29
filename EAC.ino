#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int currentMenu = 1;
double freqChoice = 1;

const int increaseButtonPin = 2;
const int decreaseButtonPin = 3; 
const int setButtonPin = 4;
const int otherButtonPin = 5;

void setup() {
 lcd.begin();
 lcd.setBacklight(1);
 lcd.setCursor(0, 0);
 lcd.print("UXW-EAC");
 lcd.setCursor(0, 1);
 lcd.print("Version 0.0.1");
 delay(1000);
 lcd.clear();
 Serial.begin(9600);  // Initialize serial communication
 pinMode(keyerOutput, OUTPUT);  // Set LED pin as output
 pinMode(increaseButtonPin, INPUT_PULLUP);
 pinMode(decreaseButtonPin, INPUT_PULLUP);
 pinMode(setButtonPin, INPUT_PULLUP);
 pinMode(otherButtonPin, INPUT_PULLUP);
}

void loop() {
 if (currentMenu == 1){
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("A: FoM   0: CXC");
   lcd.setCursor(0, 1);
   lcd.print("V: AWG   O: NXT");
 } else if (currentMenu == 2) {
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("A: DIP   0: QWG");
   lcd.setCursor(0, 1);
   lcd.print("V: QWV   O: NXT");
 } else if (currentMenu == 3) {
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("A: N/A   0: 9:1 ");
   lcd.setCursor(0, 1);int numGroups = 5;
   lcd.print("V: JPL   O: NXT");
 } else if (currentMenu == 4) {
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("A: MAG   0: LLP");
   lcd.setCursor(0, 1);
   lcd.print("V: N/A   O: NXT");
 } else if (currentMenu == 5) {
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("A: CIL   0: SQW");
   lcd.setCursor(0, 1);
   lcd.print("V: N/A   O: NXT");
 }


 while (digitalRead(increaseButtonPin) == LOW && digitalRead(decreaseButtonPin) == LOW && digitalRead(setButtonPin) == LOW && digitalRead(otherButtonPin) == LOW) {
   // Wait for either button to be pressed
   delay(1);
 }

 if (currentMenu == 1){
   if (digitalRead(increaseButtonPin) == HIGH) {
     noMode();
   } else if (digitalRead(decreaseButtonPin) == HIGH) {
     noMode();
   } else if (digitalRead(setButtonPin) == HIGH) {
     noMode();
   } else if (digitalRead(otherButtonPin) == HIGH) {
     currentMenu += 1;
     delay(100);
   }
 } else if (currentMenu == 2) {
   if (digitalRead(increaseButtonPin) == HIGH) {
     noMode();
   } else if (digitalRead(decreaseButtonPin) == HIGH) {
     noMode();
   } else if (digitalRead(setButtonPin) == HIGH) {
     noMode();
   } else if (digitalRead(otherButtonPin) == HIGH) {
     currentMenu += 1;
     delay(100);
   }
 } else if (currentMenu == 3) {
   if (digitalRead(increaseButtonPin) == HIGH) {
     noMode(); //Set callsign.
   } else if (digitalRead(decreaseButtonPin) == HIGH) {
     noMode(); //Set grid.
   } else if (digitalRead(setButtonPin) == HIGH) {
     noMode(); //Clear EEPROM.
   } else if (digitalRead(otherButtonPin) == HIGH) {
     currentMenu += 1;
     delay(100);
   }
 } else if (currentMenu == 4) {
   if (digitalRead(increaseButtonPin) == HIGH) {
     noMode();
   } else if (digitalRead(decreaseButtonPin) == HIGH) {
     noMode();
   } else if (digitalRead(setButtonPin) == HIGH) {
     noMode();
   } else if (digitalRead(otherButtonPin) == HIGH) {
     currentMenu += 1;
     delay(100);
   }
 } else if (currentMenu == 5) {
   if (digitalRead(increaseButtonPin) == HIGH) {
     noMode();
   } else if (digitalRead(decreaseButtonPin) == HIGH) {
     noMode();
   } else if (digitalRead(setButtonPin) == HIGH) {
     noMode();
   } else if (digitalRead(otherButtonPin) == HIGH) {
     currentMenu = 1;
     delay(100);
   }
 }
}

void noMode() {
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("ERROR:");
 lcd.setCursor(0, 1);
 lcd.print("Mode N/A.");
 delay(500);
}

void dipoleCalc();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dipole");
  lcd.setCursor(0, 1);
  lcd.print("Calculator");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter");
  lcd.setCursor(0, 1);
  lcd.print("Frequency");
  
  while (digitalRead(setButtonPin) == LOW) {
   if (digitalRead(increaseButtonPin) == HIGH) {
     freqChoice += 0.1;
     if (freqChoice > 54) {
       freqChoice = 0.1;
     }
     displayFreq();
     delay(100);
   } else if (digitalRead(decreaseButtonPin) == HIGH) {
     freqChoice -= 0.1;
     if (freqChoice < 1) {
       freqChoice = 54;
     }
     
     delay(100);
   }
 }
}

displayFreq() {
  lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Freq: ");
     lcd.print(freqChoice);
     lcd.print(" MHz");
}
