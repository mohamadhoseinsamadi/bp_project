
#ifndef INCIDENT_H
#define INCIDENT_H

#include "common.h"
#include "unit.h"
#include "stdlib.h"

typedef struct {
    int x, y;
    IncidentType type;
    Priority priority;
    IncidentState state;
    int operation_turns_remaining;
    Unit *dispatched_units[3][MAX_REQUIRED_UNITS_PER_TYPE];
    int dispatched_count[3];
} Incident;

//start 
typedef struct{
    int fire_unit_needed;
    int medical_unit_needed;
    int police_unit_needed;
    int required_time;
}IncidentRequirements;

extern Incident *incidents;
extern int incident_count;
extern int incident_capacity;

void dispatch_units();
void update_incidents();
void ensure_incident_capacity();

#endif // INCIDENT_H