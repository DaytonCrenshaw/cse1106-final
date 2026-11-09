# Smart Study Room Occupancy Tracker
CSE 1106 Final Project — Option 2
Team: James Grando and Dayton Crenshaw
Raspberry Pi 4B | Language: C

The Smart Study Room Occupancy Tracker helps university library staff monitor the number of students in a study room. It records each student entering or leaving through a terminal menu. The program prevents the occupancy count from going below zero or above the room's maximum capacity, displays the room status, saves events to a CSV file, and turns on a physical LED when the room is full.
Features
- Record when a student enters or exits.
- Display the current occupancy as current / maximum.
- Prevent entry when the room is full.
- Prevent exits when the room is empty.
- Show SPACE AVAILABLE or ROOM FULL.
- Turn the warning LED ON when occupancy reaches maximum capacity, and OFF when space is available.
- Allow the maximum capacity to change, as long as it remains at least 1 and is not below current occupancy.
- Append events, timestamps, occupancy, capacity, status, and LED state to occupancy_log.csv.
- Reject invalid menu input without changing the occupancy count.
Note: Entries and exits are recorded manually through the terminal; this version does not use a motion sensor or automatically count people. Occupancy starts at zero each time the program runs. The CSV file is an event history, not an automatic restore file.

# Hardware Requirements
- Raspberry Pi 4B running Raspberry Pi OS
- Breadboard and jumper wires
- LED (red recommended)
- 1,000-ohm (1 kΩ) resistor

