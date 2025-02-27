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

* [.vscode/](./B31DGAssig1/.vscode)
  * [c_cpp_properties.json](./B31DGAssig1/.vscode/c_cpp_properties.json)
  * [settings.json](./B31DGAssig1/.vscode/settings.json)
* [docs/](./B31DGAssig1/docs)
  * [alternateWaveform.PNG](./B31DGAssig1/docs/alternateWaveform.PNG)
  * [B31DG - Assignment 1 - H00368728 - Fraser Holman.docx](./B31DGAssig1/docs/B31DG - Assignment 1 - H00368728 - Fraser Holman.docx)
  * [normalWaveform.PNG](./B31DGAssig1/docs/normalWaveform.PNG)
  * [README.md](./B31DGAssig1/docs/README.md)
* [src/](./B31DGAssig1/src)
  * [arduino/](./src/arduino)
    * [main/](./B31DGAssig1/src/arduino/main)
  * [espressifIDF/](./B31DGAssig1/src/espressifIDF)
    * [.vscode/](./B31DGAssig1/src/espressifIDF/.vscode)
    * [build/](./B31DGAssig1/src/espressifIDF/build)
    * [main/](./B31DGAssig1/src/espressifIDF/main)
    * [CMakeLists.txt](./B31DGAssig1/src/espressifIDF/CMakeLists.txt)
    * [sdkconfig](./B31DGAssig1/src/espressifIDF/sdkconfig)
    * [sdkconfig.old](./B31DGAssig1/src/espressifIDF/sdkconfig.old)
* [.gitignore](./B31DGAssig1/.gitignore)


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

