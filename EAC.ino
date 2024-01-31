#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int currentMenu = 1;

//Universal Variables
float chartOfAWG[30] = {324.9 ,289.3, 257.6, 229.4, 204.3, 181.9, 162, 144.3, 128.5, 114.4, 101.9, 90.7, 80.8, 72, 64.1, 57.1, 50.8, 45.3, 40.3, 35.9, 32, 28.5, 25.3, 22.6, 20.1, 17.9, 15.9, 14.2, 12.6, 11.3, 10}; //Added the AWG 1/10 as the value of 0 here in this array. Data from https://www.lapptannehill.com/resources/technical-information/solid-conductor-awg-dimensions-chart.
float wireAWG = chartOfAWG[30];
float inputPower = 100; // Measured in Watts.
float freqChoice = 14;
float antennaLength = 0;

//Magnetic Loop Antenna Variables
float loopDiameter = 0;
float magloopVoltage = 0; // Voltage across the capacitor during TX.
float radiationResistance = 0; // Measured in Ohms.
float efficiency = 0; // Measured in decimal: 0.0 = 0% and 1.0 = 100%
float inductance = 0; // Meaured in Henries.
float tuningCapacitance = 0; // Measured in Farads.
float inductiveReactance = 0; // Measured in Ohms.
float Q = 0; // Quality Factor.
float bandwidth = 0; // Bandwidth over which the performance is acceptable and measured in Hertz.
float distributedCapacitance = 0; // Measured in Picofarads.

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
   lcd.print("A: AWG   0: N/A");
   lcd.setCursor(0, 1);
   lcd.print("V: PWR   O: NXT");
 } else if (currentMenu == 2) {
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("A: DIP   0: INV");
   lcd.setCursor(0, 1);
   lcd.print("V: 9:1   O: NXT");
 } else if (currentMenu == 3) {
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("A: JPL   0: N/A");
   lcd.setCursor(0, 1);int numGroups = 5;
   lcd.print("V: N/A   O: NXT");
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
     dipoleCalc();
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

void setFreq() {
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
     if (freqChoice < 0.1) {
       freqChoice = 54;
     }
     displayFreq();
     delay(100);
   }
}

void setAWG() {
  while (digitalRead(setButtonPin) == LOW) {
   if (digitalRead(increaseButtonPin) == HIGH) {
     freqChoice -= 1;
     if (freqChoice < 1) {
       freqChoice = 30;
     }
     displayAWG();
     delay(100);
   } else if (digitalRead(decreaseButtonPin) == HIGH) {
     freqChoice += 1;
     if (freqChoice > 30) {
       freqChoice = 1;
     }
     displayAWG();
     delay(100);
   }
}

void showLength() {
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Wire Length:");
   lcd.setCursor(0, 1);
   lcd.print(antennaLength);
   lcd.print("'");
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

  setFreq();
  
   antennaLength = (467 / freqChoice);
   antennaLength = round(10 * antennaLength) / 10;
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Dipole for");
   lcd.setCursor(0, 1);
   lcd.print(freqChoice);
   lcd.print(" MHz.");
   delay(500);
   showLength();
   while (digitalRead(setButtonPin) == LOW) {
     delay(10);
   }
}

displayFreq() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Freq: ");
  lcd.print(freqChoice);
  lcd.print(" MHz");
}

displayAWG() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AWG ");
  lcd.print(wireAWG);
}
