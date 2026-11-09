# System Design — Smart Study Room Occupancy Tracker

**CSE 1106 Final Project — Option 2**  
**Team Members:** James Grando and Dayton Crenshaw  
**Platform:** Raspberry Pi 4B | **Language:** C

## 1. Project Overview

The Smart Study Room Occupancy Tracker helps university library staff monitor how many students are inside a study room. Users can record students entering and exiting, view current occupancy, and change maximum capacity. The default capacity is five students. The program prevents negative occupancy and exceeding room capacity, saves activity to a CSV file, and activates an LED when the room is full.

## 2. System Architecture

The system follows this process:

**User Input to C Program to Occupancy Validation to Status Display, CSV Logging, and LED Control**

The program maintains two integer variables: occupancy and capacity. A switch statement processes the five menu options: student enters, student exits, show status, change capacity, and quit.

### Main Functions

- main() — Initializes the system and controls the menu.
- read_int() — Validates user input.
- how_status() — Displays occupancy and room availability.
- update_led() — Controls the LED using GPIO 17.
- log_event() — Records activity with timestamps in a CSV file.

## 3. Hardware Design

The system uses a Raspberry Pi 4B, an LED, a breadboard, jumper wires, and a 1,000-ohm resistor.

**Circuit:** GPIO 17 (physical pin 11) -> resistor -> LED positive leg -> LED negative leg ->  GND (physical pin 6).

The pigpio library controls the LED. When occupancy equals maximum capacity, the LED turns ON. Otherwise, it remains OFF.

## 4. Data Management

The program stores the current occupancy and maximum capacity in integer variables. Room activity is recorded in occupancy_log.csv, including timestamps, event types, occupancy, capacity, room status, and LED status. The log remains available after the program exits, although occupancy resets when restarted.

## 5. Testing and Validation

The system is designed to handle normal operations and prevent invalid actions. Important test cases include:

1. Enter five students — room full, LED ON.
2. Attempt a sixth entry — entry denied.
3. Attempt an exit from an empty room — exit denied.
4. Exit from a full room — LED OFF.
5. Change capacity to current occupancy — room full, LED ON.

Actual test results and physical LED verification are documented separately in the software testing report.

## 6. Conclusion

This project demonstrates C programming concepts including functions, loops, conditional statements, input validation, file handling, and Raspberry Pi GPIO integration. The system provides a simple way to monitor room capacity while preventing invalid occupancy counts.
