
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common.h"
#include "unit.h"

FILE *log_file = NULL;

// TODO: Implement log initialization.
// Create a log file with a timestamped filename using strftime.
// Open the file in write mode and handle possible errors.
// Hint: Don't forget to check if fopen() returns NULL and handle it appropriately.


void log_simulation_start() {
    if (!log_file) return;
    // TODO: Write a simple message to the log indicating the simulation has started.
    // Remember to flush the log_file after writing.
}

void log_simulation_end() {
    if (!log_file) return;
    // TODO: Write a simple message to the log indicating the simulation has ended.
    // Remember to flush the log_file after writing.
}

void log_incident_created(IncidentType type, Priority priority, int x, int y) {
    if (!log_file) return;
    fprintf(log_file, "New Incident Created: Type=%d, Priority=%d, Location=(%d,%d)\n", type, priority, x, y);
    fflush(log_file);
}

// TODO: Implement the function to log when a unit is dispatched.
// Use fprintf to write a formatted message into the log_file.
// Remember to flush the file after writing.


void log_incident_finished(int x, int y) {
    if (!log_file) return;
    fprintf(log_file, "Incident Finished at Location=(%d,%d)\n", x, y);
    fflush(log_file);
}

void log_unit_state_change(Unit *u, UnitState state) {
    if (!log_file) return;
    fprintf(log_file, "Unit %d-%d changed state to %d\n",
            u->departmentNumber, u->unitNumber, state);
    fflush(log_file);
}

void log_unit_arrived(Unit *u, int incident_x, int incident_y) {
    if (!log_file) return;
    fprintf(log_file, "Unit %d-%d arrived at Incident (%d,%d)\n",
            u->departmentNumber, u->unitNumber, incident_x, incident_y);
    fflush(log_file);
}

void log_unit_returning(Unit *u, int base_x, int base_y) {
    if (!log_file) return;
    fprintf(log_file, "Unit %d-%d returning to base (%d,%d)\n",
            u->departmentNumber, u->unitNumber, base_x, base_y);
    fflush(log_file);
}

void log_incident_status_change(int x, int y, IncidentState state) {
    if (!log_file) return;
    fprintf(log_file, "Incident at (%d,%d) changed state to %d\n", x, y, state);
    fflush(log_file);
}