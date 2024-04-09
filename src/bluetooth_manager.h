#ifndef BLUETOOTH_MANAGER_H
#define BLUETOOTH_MANAGER_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "bike.h"

#define AIKE_DEVICE_NAME          "AIKE"

#define AIKE_SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define SPEED_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define DISTANCE_CHECK_CHARACTERISTIC_UUID "0ac82d02-002b-4ccb-b96c-1c7839cbc4c0"
#define DISTANCE_CHARACTERISTIC_UUID "878663eb-e875-47ae-93b7-42226602074c"
#define BATTERY_CHARACTERISTIC_UUID "0b5d50b0-58c5-48ad-864e-fda4699f53e6"

class BluetoothManager {
    public:
        BluetoothManager();

        void setup();
        void loop(Bike::BikeStatus status);

    private:
        BLEServer *server;
        BLEService *service;
        BLEAdvertising *advertising;

        BLECharacteristic *speedCharacteristic;
        BLECharacteristic *distanceCheckCharacteristic;
        BLECharacteristic *distanceCharacteristic;
        BLECharacteristic *batteryCharacteristic;

        void setupCharacteristics();
};

#endif