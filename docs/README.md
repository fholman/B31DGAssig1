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


# B31DGAssig1

* [.vscode/](../.vscode)
  * [c_cpp_properties.json](../.vscode/c_cpp_properties.json)
  * [settings.json](../.vscode/settings.json)
* [docs/](../docs)
  * [alternateWaveform.PNG](../docs/alternateWaveform.PNG)
  * [normalWaveform.PNG](../docs/normalWaveform.PNG)
  * [README.md](../docs/README.md)
* [src/](../src)
  * [arduino/](../src/arduino)
    * [main/](../src/arduino/main)
  * [espressifIDF/](../src/espressifIDF)
    * [.vscode/](../src/espressifIDF/.vscode)
    * [build/](../src/espressifIDF/build)
    * [main/](../src/espressifIDF/main)
    * [CMakeLists.txt](../src/espressifIDF/CMakeLists.txt)
    * [sdkconfig](../src/espressifIDF/sdkconfig)
    * [sdkconfig.old](../src/espressifIDF/sdkconfig.old)
* [.gitignore](../.gitignore)


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

