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
B31DGASSIG1/  
│── src/                # Source code directory  
│   ├── arduino/        # Arduino implementation  
│   │   ├── main/       # Required folder for Arduino `.ino` file  
│   │   │   ├── main.ino  
│   │   ├── other_files # Any supporting Arduino libraries or scripts  
│   │  
│   ├── c_code/         # ESP32 C implementation  
│   │   ├── main.c      # Main application  
│   │   ├── main.h      # Header files  
│   │   ├── other.c/.h  # Additional source files  
│  
│── bin/                # Compiled binaries and firmware  
│   ├── firmware.bin    # Flashable ESP32 binary  
│   ├── firmware.elf    # Executable firmware  
│  
│── build/              # Temporary build files (should be ignored by Git)  
│── docs/               # Documentation and project reports  
│── tools/              # Scripts for flashing or utilities  
│── .gitignore          # Specifies ignored files in the repository  
│── README.md           # Project documentation  
│── CMakeLists.txt      # Build system configuration for ESP32  



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

