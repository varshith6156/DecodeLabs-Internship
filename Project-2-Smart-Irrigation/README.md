# Project 2 – Automated Irrigation Controller 

## Overview

This project is an **Automated Irrigation Controller** developed as part of the **DecodeLabs IoT Industrial Training Program**.

The main idea is pretty simple — the system checks the **soil moisture level** and automatically decides whether the plants need water or not.

A **soil moisture sensor** sends an analog value to the **ESP32**. The ESP32 processes this value using its ADC and checks it with a predefined threshold. If the soil is too dry, the ESP32 activates a **relay**, which simulates turning ON a water pump.

So basically, the system works automatically without needing someone to manually check and water the soil.

## Objective

The main objective of this project is to build a simple automatic irrigation system that can:

* Read the soil moisture level using a sensor.
* Process the analog sensor value using the ESP32 ADC.
* Check whether the soil is dry or wet using threshold logic.
* Control a relay based on the moisture level.
* Automatically simulate a water pump.
* Display the system status using an OLED and LED.

## Components Used

* ESP32
* Soil Moisture Sensor
* 5V Relay Module
* Water Pump (Simulated)
* OLED Display
* LED
* Jumper Wires

## Software and Tools

* Arduino IDE
* C/C++
* Wokwi
* Blynk IoT

## How It Works

The working of the project is straightforward:

1. The **soil moisture sensor** detects the moisture level in the soil.
2. The sensor sends an **analog signal** to the ESP32.
3. The ESP32 reads the signal using its **ADC**.
4. The moisture value is compared with a predefined **threshold**.
5. If the soil is **too dry**, the ESP32 turns ON the relay.
6. The relay activates the **simulated water pump**.
7. When the soil has enough moisture, the relay is turned OFF.

### Working Flow

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
  Water Pump 💧
```

## Project Concept

This project is basically a **closed-loop IoT automation system**. The sensor continuously provides information about the environment, and the ESP32 takes the required action based on that information.

It shows how IoT can be used to make irrigation **automatic, simple, and more efficient**, while reducing unnecessary water usage.
