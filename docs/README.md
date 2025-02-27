# B31DG Assignment 1

## Project Overview
This project is an **ESP32-based signal control system** designed to handle input interrupts and generate pulse waveforms. It utilizes GPIO for input buttons and output signals, with an efficient **interrupt-driven** approach to manage button presses and control LED signaling.

## Features
- **ESP32-based** real-time signal processing
- **Button interrupt handling** with debounce logic
- **Configurable pulse generation** based on selection mode
- **ESP Logging support** for debugging and monitoring
- **Custom delay implementation** for precise waveform control

## Repository Structure


* [docs/](../docs)
  * [B31DG - Assignment 1 - H00368728 - Fraser Holman.docx](../docs/B31DG%20-%20Assignment%201%20-%20H00368728%20-%20Fraser%20Holman.docx)
  * [alternateWaveform.PNG](../docs/alternateWaveform.PNG)
  * [normalWaveform.PNG](../docs/normalWaveform.PNG)
  * [README.md](../docs/README.md)
* [src/](../src)
  * [arduino/](../src/arduino)
    * [main/](../src/arduino/main)
      * [main.ino/](../src/arduino/main/main.ino)
  * [espressifIDF/](../src/espressifIDF)
    * [main/](../src/espressifIDF/main)
      * [main.c/](../src/espressifIDF/main/main.c)
      * [main.h/](../src/espressifIDF/main/main.h)


## Setup Instructions
### **1️ Prerequisites**
- **ESP-IDF (Espressif IoT Development Framework)** installed  
- **Python 3.x** for ESP-IDF  
- **CMake & Ninja Build System**  
- **VS Code with ESP-IDF Plugin** (Recommended)  

### **2️ Build & Flash**
```sh
idf.py set-target esp32
idf.py build
idf.py flash
idf.py monitor

