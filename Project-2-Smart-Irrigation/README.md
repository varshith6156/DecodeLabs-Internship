# Project 2 – Automated Irrigation Controller

## Overview

This project is an automated irrigation controller developed as part of the DecodeLabs Internet of Things (IoT) Industrial Training Program.

The system reads an analog signal from a soil moisture sensor, processes the reading using the ESP32's ADC, and uses threshold-based logic to control a relay module that simulates a water pump.

The project demonstrates a closed-loop automation system where real-time environmental data is used to control an actuator.

## Objective

The objective of this project is to build an automated system that:

- Reads analog data from a soil moisture sensor.
- Processes the sensor reading using an ADC.
- Determines whether the soil is too dry using threshold logic.
- Controls a relay module through a digital output.
- Simulates automatic control of a water pump.

## Components Used

- ESP32
- Soil Moisture Sensor
- 5V Relay Module
- Water Pump (simulated)
- OLED Display
- LED
- Jumper Wires

## Software and Tools

- Arduino IDE
- C/C++
- Wokwi
- Blynk IoT

## Working Principle

The soil moisture sensor provides an analog value to the ESP32.

The ESP32 reads this value and calculates the soil moisture level. The programmed threshold logic then determines whether irrigation is required.

```text
Soil Moisture Sensor
        ↓
      ESP32
        ↓
   ADC Processing
        ↓
 Threshold Decision
        ↓
   Relay Control
        ↓
 Water Pump
