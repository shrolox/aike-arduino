#include <iostream>
#include <string>
#include <Arduino.h>
#include "bluetooth_manager.h"

BluetoothManager::BluetoothManager() {
}

void BluetoothManager::setup() {
    BLEDevice::init("AIKE");

    this->server = BLEDevice::createServer();
    this->service = this->server->createService(AIKE_SERVICE_UUID);
    
    this->setupCharacteristics();

    this->service->start();
    this->advertising = BLEDevice::getAdvertising();
    
    this->advertising->addServiceUUID(AIKE_SERVICE_UUID);
    this->advertising->setScanResponse(true);
    this->advertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    this->advertising->setMinPreferred(0x12);
    
    BLEDevice::startAdvertising();
}

void BluetoothManager::loop(Bike::BikeStatus status) {
    this->batteryCharacteristic->setValue("80");
    this->speedCharacteristic->setValue(std::to_string(status.speed));
    this->distanceCheckCharacteristic->setValue("0");
    this->distanceCharacteristic->setValue("0");

    this->speedCharacteristic->notify();
    delay(10);
}   

void BluetoothManager::setupCharacteristics() {
    this->batteryCharacteristic = this->service->createCharacteristic(
        BATTERY_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ
    );
    this->speedCharacteristic = this->service->createCharacteristic(
        SPEED_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ
    );
    this->distanceCheckCharacteristic = this->service->createCharacteristic(
        DISTANCE_CHECK_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ
    );
    this->distanceCharacteristic = this->service->createCharacteristic(
        DISTANCE_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ
    );
}