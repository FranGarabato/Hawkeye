#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 16, TXPin = 17;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  Serial.begin(115200);
  ss.begin(GPSBaud);

}

void loop() {
  // put your main code here, to run repeatedly:

}
