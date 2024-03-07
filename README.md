# Arduino Solar Tracker

## Project Overview
The Arduino Solar Tracker is designed to optimize solar energy absorption by automatically adjusting its position to follow the sun's path across the sky. Utilizing Light Dependent Resistors (LDRs) and servo motors, the system can also be manually controlled via serial commands from a phone for precise positioning.

## Team
- [AlinTcaci](https://github.com/AlinTcaci)
- [Radu-Maris](https://github.com/Radu-Maris)

## Features
- **Automatic Tracking Mode:** Adjusts the tracker's position based on LDR readings to maximize sunlight exposure.
- **Manual Control Mode:** Allows for manual adjustment of the tracker's position through serial commands.

## Hardware Requirements
- Arduino board
- 2 Servo Motors
- 4 LDRs (Light Dependent Resistors)
- Solar Panel
- Push Button
- LED
- Resistors, wires, and a breadboard

## Pin Configuration
- **Servo Motors:** Digital pins 5 (up-down) and 6 (left-right)
- **LDRs:** Analog pins A0 to A3
- **LED:** Digital built-in pin 13
- **Button:** Digital pin 2

## Getting Started
To set up your Arduino Solar Tracker, connect the components as outlined in the "Pin Configuration" section. The `SolarTracker.ino` file contains the source code to operate the tracker. Upload this code to your Arduino board using the Arduino IDE.

## Usage
- **Automatic Mode:** The tracker automatically adjusts its orientation to ensure optimal sunlight absorption.
- **Manual Mode:** Press the button to switch to manual mode, allowing you to adjust the tracker's position using serial commands ('u' for up, 'd' for down, followed by an angle).

## Conclusion
This project not only serves as an excellent learning tool for Arduino and its components but also has practical applications in small-scale solar projects or home solar setups.
