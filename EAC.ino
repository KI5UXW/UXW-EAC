#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int currentMenu = 1;

//Universal Variables
float chartOfAWG[30] = {324.9 ,289.3, 257.6, 229.4, 204.3, 181.9, 162, 144.3, 128.5, 114.4, 101.9, 90.7, 80.8, 72, 64.1, 57.1, 50.8, 45.3, 40.3, 35.9, 32, 28.5, 25.3, 22.6, 20.1, 17.9, 15.9, 14.2, 12.6, 11.3, 10}; //Added the AWG 1/10 as the value of 0 here in this array. Data from https://www.lapptannehill.com/resources/technical-information/solid-conductor-awg-dimensions-chart.
float wireAWG = 30;
float wireDiameter= (chartOfAWG[30] / 1000); //Measured in Inches.
string coaxTypes[93] = {"RG-4/U", "RG-5/U", "RG-5A/B/U", "RG-6/U", "RG-6A/U", "RG-8/U", "9914/U", "RG-8A/U", "RG-8X/U", "RG-9/U", "RG-9A/U", "RG-9B/U", "RG-10/U", "RG-10A/U", "RG-11/U", "RG-11A/U", "RG-12/U", "RG-12A/U", "RG-17A/U", "RG-17A/U", "RG-22/U", "RG-22A/B/U", "RG-23/A/U", "RG-24/A/U", "RG-34/U", "RG-34A/U", "RG-35/U", "RG-35A/B/U", "RG-55B/U", "RG-58/U", "RG-58A/U", "RG-58B/U", "RG-58C/U", "RG-59/A/U", "RG-59B/U", "RG-62/A/B/U", "RG-63/A/B/U", "RG-65/A/U", "RG-71/A/B/U", "RG-79/A/B/U", "RG-83/U", "RG-88U", "RG-108/A/U", "RG-111/A/U", "RG-114/A/U", "RG-119/U", "RG-120/U", "RG-122/U", "RG-130/U", "RG-131/U", "RG-133/A/U", "RG-141/A/U", "RG-142/A/B/U", "RG-144/U", "RG-164/U", "RG-165/U", "RG-166/U", "RG-174/U", "RG-177/U", "RG-178/A/B/U", "RG-179/U", "RG-179A/B/U", "RG-180/U", "RG-180/A/B/U", "RG-210/U", "RG-211/A/U", "RG-212/U", "RG-213/U", "RG-214/U", "RG-215/U", "RG-216/U", "RG-217/U", "RG-218/U", "RG-219/U", "RG-223/U", "RG-302/U", "RG-303/U", "RG-304/U", "RG-307/A/U", "RG-316/U", "RG-391/U", "RG-392/U", "RG-393/U", "RG-400/U", "RG-401/U", "RG-402/U", "RG-403/U", "RG-405/U", "LMR-100", "LMR-195", "LMR-240", "LMR-400", "LMR-600"} // Sourced from: https://www.everythingrf.com/tech-resources/rf-cable-specifications
float coaxTypesDiameters[93] = {0.226, 0.332, 0.328, 0.332, 0.332, 0.405, 0.403, 0.405, 0.242, 0.420, 0.420, 0.420, 0.463, 0.463, 0.405, 0.405, 0.463, 0.463, 0.870, 0.405, 0.405, 0.650, 0.708, 0.625, 0.630, 0.928, 0.928, 0.200, 0.195, 0.195, 0.195, 0.195, 0.242, 0.242, 0.242, 0.405, 0.405, 0.245, 0.436, 0.405, 0.515, 0.235, 0.478, 0.405, 0.465, 0.523, 0.160, 0.625, 0.683, 0.405, 0.190, 0.195, 0.410, 0.460, 0.110, 0.895, 0.072, 0.100, 0.100, 0.140, 0.140, 0.242, 0.730, 0.332, 0.405, 0.425, 0.463, 0.425, 0.545, 0.870, 0.928, 0.211, 0.201, 0.170, 0.280, 0.270, 0.102, 0.402, 0.475, 0.390, 0.195, 0.250, 0.141, 0.116, 0.086, 0.110, 0.195, 0.240, 0.400, 0.590} //Measured in Inches.
float coaxTypeChoice = 0;
float inputPower = 100; // Measured in Watts.
float freqChoice = 14; // Measured in MHz.
float antennaLength = 0;
float universalCounter = 0;

//Magnetic Loop Antenna Variables
//Formulas from https://www.aa5tb.com/loop.html
float loopDiameter = 0;
float conductorDiameter = 0;
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
   lcd.print("A: AWG   0: FRQ");
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

void setCoax() {
  while (digitalRead(setButtonPin) == LOW) {
   if (digitalRead(increaseButtonPin) == HIGH) {
     wireAWG -= 1;
     if (wireAWG < 1) {
       wireAWG = 30;
     }
     displayAWG();
     delay(100);
   } else if (digitalRead(decreaseButtonPin) == HIGH) {
     wireAWG += 1;
     if (wireAWG > 30) {
       wireAWG = 1;
     }
     displayAWG();
     delay(100);
   }
   wireDiameter = (chartOfAWG[wireAWG] / 1000)
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("You've chosen AWG ");
   lcd.print(wireAWG);
   lcd.setCursor(0, 1);
   lcd.print(wireDiameter);
   lcd.print("'")
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

void showLength() {
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Wire Length:");
   lcd.setCursor(0, 1);
   lcd.print(antennaLength);
   lcd.print("'");
}
 
void dipoleCalc() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dipole");
  lcd.setCursor(0, 1);
  lcd.print("Calculator");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Chosen Freq.");
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

void magloopCalc() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Magloop");
  lcd.setCursor(0, 1);
  lcd.print("Calculator");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select Wire");
  lcd.setCursor(0, 1);
  lcd.print("Diameter");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AWG: A ");
  lcd.setCursor(0, 1);
  lcd.print("Other: V");
  while (digitalRead(increaseButtonPin) == LOW && digitalRead(decreaseButtonPin) == LOW {
   // Wait for either button to be pressed
   delay(1);
 }
 if (digitalRead(increaseButtonPin) == HIGH) {
     loopDiameter = wireDiameter;
   } else if (digitalRead(decreaseButtonPin) == HIGH) {
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Custom Diam.: A");
     lcd.setCursor(0, 1);
     lcd.print("Coax: V");
}

void displayFreq() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Freq: ");
  lcd.print(freqChoice);
  lcd.print(" MHz");
}

void displayAWG() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AWG ");
  lcd.print(wireAWG);
}
