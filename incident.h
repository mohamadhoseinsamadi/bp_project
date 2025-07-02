
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
// TODO: Define a struct representing IncidentRequirements. 
// This type should have number of fire, medical, and police units required for an incident alongside required time.
// Incidents must initiate the  operation_turns_remaining by reading the respective incident requirements


extern Incident *incidents;
extern int incident_count;
extern int incident_capacity;

//start
void dispatch_units();
void update_incidents();
// TODO: Declare the function responsible for dispatching units to incidents.
// TODO: Declare the function responsible for updating incident states.

void ensure_incident_capacity();

#endif // INCIDENT_H