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

├── docs                    # Documentation files
├── src                     # Source files (alternatively `lib` or `app`)
└── README.md


B31DGASSIG1/  
│── src/
│   ├── arduino/
│   │   ├── main/
│   │   │   ├── main.ino  
│   ├── espressifIDF/ 
│   │   ├── main.c      # Main application  
│   │   ├── main.h      # Header files  
│   │   ├── other.c/.h  # Additional source files  │  
│── docs/               # Documentation and project reports  

├── build                   # Compiled files (alternatively `dist`)
    ├── docs                    # Documentation files (alternatively `doc`)
    ├── src                     # Source files (alternatively `lib` or `app`)
    ├── test                    # Automated tests (alternatively `spec` or `tests`)
    ├── tools                   # Tools and utilities
    ├── LICENSE
    └── README.md



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

