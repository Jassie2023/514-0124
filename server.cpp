#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <stdlib.h>
#include <NewPing.h>

BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
unsigned long previousMillis = 0;
const long interval = 1000;

#define TRIGGER_PIN D1
#define ECHO_PIN D0
#define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// TODO: add new global variables for your sensor readings and processed data
#define WINDOW_SIZE 10 // Size of the moving average window

unsigned int distanceReadings[WINDOW_SIZE]; // Array to store the last few readings
unsigned long sum = 0;                      // Sum of the readings in the window
unsigned int average = 0;                   // Average (filtered) value

// TODO: Change the UUID to your own (any specific one works, but make sure they're different from others'). You can generate one here: https://www.uuidgenerator.net/
#define SERVICE_UUID "cc74a6a2-20ce-4b2a-8c75-68fa063425ed"
#define CHARACTERISTIC_UUID "aec8b4db-965d-43b4-8a69-582d2573b3ad"

class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
  };

  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
  }
};

// TODO: add DSP algorithm functions here

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting BLE work!");
  memset(distanceReadings, 0, sizeof(distanceReadings)); // Initialize the array

  // TODO: add codes for handling your sensor setup (pinMode, etc.)
  // pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  // pinMode(echoPin, INPUT);  // Sets the echoPin as an Input

  // TODO: name your device to avoid conflictions
  BLEDevice::init("Group8Lab4");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
      CHARA
