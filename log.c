
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common.h"
#include "unit.h"
#include "utils.h"

FILE *log_file = NULL;

//start
void init_log(){
    time_t rawtime;
    struct tm * timeinfo;
    char filename[30];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(filename, sizeof(filename), "log_%Y%m%d_%H%M%S.txt", timeinfo);
    log_file = fopen(filename, "w");
    if (!log_file) {
        perror("error in opening file");
        return ;
    }
}
// TODO: Implement log initialization.
// Create a log file with a timestamped filename using strftime.
// Open the file in write mode and handle possible errors.
// Hint: Don't forget to check if fopen() returns NULL and handle it appropriately.


void log_simulation_start() {
    if (!log_file)
        return;
    fprintf(log_file,"Simulation Started\n");
    fflush(log_file);
}

void log_simulation_end() {
    if (!log_file) 
        return;
    fprintf(log_file,"Simulation Ended\n");
    fflush(log_file);
}

void log_incident_created(IncidentType type, Priority priority, int x, int y) {
    if (!log_file) 
        return;
    fprintf(log_file, "New Incident Created: Type=%s, Priority=%s, Location=(%d,%d)\n", getIncidentTypeStr(type), getPriorityStr(priority), x, y);
    fflush(log_file);
}

//start
void log_unit_dispatched(Unit *u, int target_x, int target_y){
    if (!log_file) 
        return;
    fprintf(log_file, "Unit Dispatched: type=%s, Dept=%d, Unit=%d, Target=(%d,%d)\n",getUnitTypeStr( u->type),u->departmentNumber,u->unitNumber,u->target_x,u->target_y);
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
            u->departmentNumber, u->unitNumber,getUnitStateStr(state) );
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
    fprintf(log_file, "Incident at (%d,%d) changed state to %d\n", x, y,getIncidentStateStr(state) );
    fflush(log_file);
}