# B31DG Assignment 1

## Project Overview
This project is an **ESP32-based signal control system** designed to handle input interrupts and generate pulse waveforms. It utilizes GPIO for input buttons and output signals, with an efficient **interrupt-driven** approach to manage button presses and control LED signaling.

## About The Project
The project follows the requirements of B31DG Assignment 1. The system utilises GPIO pins on an ESP32-WROOM module, the system was first implemented in the Arduino ide in a .ino file and then was followed by implementing the system using the ESP-IDF extension with VSCode. The system generates a waveform utilising two GPIO pins for LEDs and a further two GPIO pins for input buttons. The signal timing parameters were defined by the calculations below. 

The alternate signal was a reversed waveform of the original signal.


| **Parameter**           | **Numerical Mapping**      | **Calculation**                     |
|------------------------|---------------------------|-------------------------------------|
| **a**                 | 'H' maps to 8             | 8 × 100µs = **800µs**               |
| **b**                 | 'O' maps to 12            | 12 × 100µs = **1200µs**             |
| **c**                 | 'L' maps to 12            | 12 + 4 = **16**                     |
| **d**                 | 'M' maps to 13            | 13 × 500µs = **6500µs**             |
| **Alternative Behaviour** | 'A' maps to 1        | (1 % 4) + 1 = **2**                 |
| **T<sub>ON(n)</sub>** | N/A                       | 800 + ((n - 1) × 50µs) for n ≥ 2   |



## Repository Structure

The repository is split mainly into doc and src files. The src files contain both the arduino .ino code and espressif .c and .h files for the working waveform. The doc files contain documents in relation to the assignment.

* [docs/](../docs)  # related documents
  * [B31DG - Assignment 1 - H00368728 - Fraser Holman.docx](../docs/B31DG%20-%20Assignment%201%20-%20H00368728%20-%20Fraser%20Holman.docx)  # assignment report
  * [alternateWaveform.PNG](../docs/alternateWaveform.PNG)  # alternate waveform png
  * [normalWaveform.PNG](../docs/normalWaveform.PNG)    # normal waveform png
  * [README.md](../docs/README.md)  # read me
* [src/](../src)    # source files
  * [arduino/](../src/arduino)
    * [main/](../src/arduino/main)
      * [main.ino/](../src/arduino/main/main.ino)   # arduino code
  * [espressifIDF/](../src/espressifIDF)
    * [main/](../src/espressifIDF/main) # ESP-IDF code
      * [main.c/](../src/espressifIDF/main/main.c)
      * [main.h/](../src/espressifIDF/main/main.h)


### **2️ Build & Flash**
```sh
idf.py set-target esp32
idf.py build
idf.py flash
idf.py monitor

