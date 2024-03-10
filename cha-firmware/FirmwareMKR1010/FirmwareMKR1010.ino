#include <ArduinoBLE.h>

BLEService imuService("12345678-1234-1234-1234-123456789012"); // Custom service UUID for IMU data and LED control
BLEFloatCharacteristic imuDataCharacteristic("12345678-1234-1234-1234-123456789013", BLERead | BLENotify); // IMU data characteristic
BLEByteCharacteristic ledControlCharacteristic("12345678-1234-1234-1234-123456789014", BLEWrite | BLENotify); // LED control characteristic

const int ledPin = LED_BUILTIN;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("Arduino IMU");
  BLE.setAdvertisedService(imuService);

  imuService.addCharacteristic(imuDataCharacteristic);
  imuService.addCharacteristic(ledControlCharacteristic);

  BLE.addService(imuService);

  imuDataCharacteristic.writeValue(0.0); // Initial value
  ledControlCharacteristic.writeValue(0); // LED is off initially

  BLE.advertise();
  Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() {
  // Simulate IMU data (e.g., acceleration, gyro)
  float simulatedImuData = random(100) / 100.0; // Random value between 0.0 and 1.0
  imuDataCharacteristic.writeValue(simulatedImuData);

  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    while (central.connected()) {
      if (ledControlCharacteristic.written()) {
        if (ledControlCharacteristic.value() == 0x01) {
          digitalWrite(ledPin, HIGH);
          delay(500);
          digitalWrite(ledPin, LOW);
          ledControlCharacteristic.writeValue(0);
        } else if (ledControlCharacteristic.value() == 0x02) {
          digitalWrite(ledPin, HIGH);
          delay(500);
          digitalWrite(ledPin, LOW);
          delay(500);
          digitalWrite(ledPin, HIGH);
          delay(500);
          digitalWrite(ledPin, LOW);
          ledControlCharacteristic.writeValue(0);
        } else if (ledControlCharacteristic.value() == 0x03) {
          digitalWrite(ledPin, HIGH);
          delay(500);
          digitalWrite(ledPin, LOW);
          delay(500);
          digitalWrite(ledPin, HIGH);
          delay(500);
          digitalWrite(ledPin, LOW);
          delay(500);
          digitalWrite(ledPin, HIGH);
          delay(500);
          digitalWrite(ledPin, LOW);
          ledControlCharacteristic.writeValue(0);
        } else if (ledControlCharacteristic.value() == 0x04) {
          digitalWrite(ledPin, HIGH);
          delay(500);
          digitalWrite(ledPin, LOW);
          delay(500);
          digitalWrite(ledPin, HIGH);
          delay(500);
          digitalWrite(ledPin, LOW);
          delay(500);
          digitalWrite(ledPin, HIGH);
          delay(500);
          digitalWrite(ledPin, LOW);
          delay(500);
          digitalWrite(ledPin, HIGH);
          delay(500);
          digitalWrite(ledPin, LOW);
          ledControlCharacteristic.writeValue(0);
        } else { // Otherwise, turn the LED off
          digitalWrite(ledPin, LOW);
        }
      }
    }
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}
