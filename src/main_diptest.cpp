#include <Arduino.h>
#include <Servo.h>
#include <DMXSerial.h>

const int DmxTimeoutMs = 		1000;
const int DmxDipPins[9] = 		{ 2,3,4,5,6,7,8,9,10 };

Servo Servo1; 
const int Servo1CtrlPin = 		1;
const int Servo1DefaultPos =	0;
const int Servo1MinPos = 		0;
const int Servo1MaxPos = 		200;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i = 0; i<9; i++){
    pinMode(DmxDipPins[i], INPUT_PULLUP);      // set the digital pins (defined above) as input
    // digitalWrite(DmxDipPins[i], HIGH);  // set internal pullup resistor on
  }
}

// cannot use uint8 as DMX uses 9 bits
uint16_t getDipAddress(){
  int i,address=0;
  for(i=1; i<=9; i++){
	  // build address number by left shifting by 1, then merge next bit by OR operation
    address = (address << 1) | !digitalRead(DmxDipPins[9-i]);
  }
  return address;
}

// Caution: bitOffset starts from 0!
bool getBit(byte data, int bitOffset = 0)
{
	// Create a mask by shifting (<<) "1" bit to the left.
	// then use AND (&) to check if the bit exists in both values.
    return (data & (1<<bitOffset)) != 0;
}

void printDipValues() {
  Serial.print(digitalRead(DmxDipPins[0]));
  Serial.print(digitalRead(DmxDipPins[1]));
  Serial.print(digitalRead(DmxDipPins[2]));
  Serial.print(digitalRead(DmxDipPins[3]));
  Serial.print(digitalRead(DmxDipPins[4]));
  Serial.print(digitalRead(DmxDipPins[5]));
  Serial.print(digitalRead(DmxDipPins[6]));
  Serial.print(digitalRead(DmxDipPins[7]));
  Serial.print(digitalRead(DmxDipPins[8]));
  Serial.print(" (");
  Serial.print(getDipAddress());
  Serial.print(")");
  Serial.print("\r\n");
}

void loop() {
  // // Calculate how long no data packet was received
//   unsigned long lastPacket = DMXSerial.noDataSince();
  uint16_t DmxAddress = getDipAddress();
  printDipValues();
//   bool hasBit = getBit(DmxAddress, 7);
  
//   if (hasBit) {
//     digitalWrite(LED_BUILTIN, HIGH);
//   } else {
//     digitalWrite(LED_BUILTIN, LOW);
//   }
  
}
