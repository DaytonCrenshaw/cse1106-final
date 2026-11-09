#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <pigpio.h>

#define LED_PIN 17
#define DEFAULT_CAPACITY 5
#define LOG_FILE "occupancy_log.csv"

/* Read a whole number safely without allowing letters or extra characters. */
int read_int(const char *prompt, int *value) {
    char line[128];
    char *end;
    long number;

    printf("%s", prompt);
    fflush(stdout);
    if (fgets(line, sizeof(line), stdin) == NULL) return 0;

    errno = 0;
    number = strtol(line, &end, 10);
    if (end == line || errno == ERANGE || number < INT_MIN || number > INT_MAX) {
        puts("Invalid input. Enter a whole number.");
        return -1;
    }
    while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r') end++;
    if (*end != '\0') {
        puts("Invalid input. Enter a whole number.");
        return -1;
    }
    *value = (int)number;
    return 1;
}

/* An illuminated LED means the room is at full capacity. */
void update_led(int occupancy, int capacity) {
    gpioWrite(LED_PIN, occupancy >= capacity ? 1 : 0);
}

void show_status(int occupancy, int capacity) {
    printf("\nCurrent occupancy: %d / %d\n", occupancy, capacity);
    printf("System status: %s\n", occupancy == capacity ? "ROOM FULL" : "SPACE AVAILABLE");
    printf("Full indicator LED: %s\n\n", occupancy == capacity ? "ON" : "OFF");
}

void log_event(const char *event, int occupancy, int capacity) {
    FILE *file = fopen(LOG_FILE, "a+");
    if (file == NULL) {
        perror("Could not open log file");
        return;
    }

    /* Write CSV column names only for a new/empty file. */
    if (fseek(file, 0, SEEK_END) == 0 && ftell(file) == 0) {
        fprintf(file, "timestamp,event,occupancy,capacity,status,led\n");
    }

    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char timestamp[32] = "unknown";
    if (local != NULL) strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", local);

    fprintf(file, "%s,%s,%d,%d,%s,%s\n", timestamp, event, occupancy, capacity,
            occupancy == capacity ? "ROOM FULL" : "SPACE AVAILABLE",
            occupancy == capacity ? "ON" : "OFF");
    fclose(file);
}

int main(void) {
    int occupancy = 0;
    int capacity = DEFAULT_CAPACITY;
    int choice, new_capacity, result;

    if (gpioInitialise() < 0) {
        fprintf(stderr, "GPIO setup failed. Run this on the Raspberry Pi with pigpio installed.\n");
        return 1;
    }
    gpioSetMode(LED_PIN, PI_OUTPUT);
    update_led(occupancy, capacity);

    puts("=== SMART STUDY ROOM OCCUPANCY TRACKER ===");
    printf("Starting capacity: %d students\n", capacity);
    log_event("START", occupancy, capacity);

    for (;;) {
        puts("1. Student enters");
        puts("2. Student exits");
        puts("3. Show room status");
        puts("4. Change maximum capacity");
        puts("5. Quit");

        result = read_int("Choose an option (1-5): ", &choice);
        if (result == 0) {
            puts("Input closed. Exiting.");
            break;
        }
        if (result < 0) continue;

        switch (choice) {
            case 1:
                if (occupancy >= capacity) {
                    puts("ENTRY DENIED: Room is full. Someone must exit first.");
                    log_event("ENTRY_DENIED_FULL", occupancy, capacity);
                } else {
                    occupancy++;
                    puts("Student entered successfully.");
                    log_event("ENTER", occupancy, capacity);
                }
                break;
            case 2:
                if (occupancy == 0) {
                    puts("EXIT DENIED: Room is already empty.");
                    log_event("EXIT_DENIED_EMPTY", occupancy, capacity);
                } else {
                    occupancy--;
                    puts("Student exited successfully.");
                    log_event("EXIT", occupancy, capacity);
                }
                break;
            case 3:
                show_status(occupancy, capacity);
                continue;
            case 4:
                result = read_int("Enter new maximum capacity: ", &new_capacity);
                if (result == 0) goto cleanup;
                if (result < 0) continue;
                if (new_capacity <= 0) {
                    puts("Capacity must be at least 1.");
                    continue;
                }
                if (new_capacity < occupancy) {
                    printf("Cannot set capacity below current occupancy (%d).\n", occupancy);
                    continue;
                }
                capacity = new_capacity;
                printf("Maximum capacity changed to %d.\n", capacity);
                log_event("CAPACITY_CHANGED", occupancy, capacity);
                break;
            case 5:
                goto cleanup;
            default:
                puts("Invalid option. Please choose 1-5.");
                continue;
        }

        update_led(occupancy, capacity);
        show_status(occupancy, capacity);
    }

cleanup:
    log_event("STOP", occupancy, capacity);
    gpioWrite(LED_PIN, 0);
    gpioTerminate();
    puts("Program closed. LED turned OFF.");
    return 0;
}
