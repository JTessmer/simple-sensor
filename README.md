# Simple Sensor

## What is this?
The Simple Sensor project is a small codebase intended for use on IoT microcontrollers. It is built with the NodeMCU v2 (ESP8266) in mind, but could in theory be adapted to other boards, such as the Arduino.

This is primarily intended for personal use, but I am sharing it publicly in case it happens to be useful for others.

## Usage

This project was built with PlatformIO's IDE. All dependencies are listed within the platformio.ini file.

For simplicity's sake, configuration options are stored in ```/src/util/Const.h```. Because this file contains sensitive information, it is not included in the repository. An example file has been provided at ```/src/util/Const.h.blank```. Make sure to rename this file and fill in the details prior to building.
