
#include "incident.h"
#include "log.h"
#include "unit.h"
#include "map.h"
#include <stdio.h>
#include <string.h>

Incident *incidents = NULL;
int incident_count = 0;
int incident_capacity = 0;

// TODO: Initiate an array for storing incident requirements for different incident types and different priorities
// HINT: Use a 2d array of incident requirements like this:
// HINT:               Incident Requirement : {fire_units, medical_units, police_units, time_required}
//                         LOW      MEDIUM    HIGH
//            FIRE    [ {1,0,0,3} {1,1,0,6} {1,1,1,8}
//            MEDICAL   {0,1,0,1} {0,1,0,3} {0,1,0,5}
//            POLICE    {0,0,1,2} {0,1,1,4} {0,1,1,8} ]
//


void dispatch_units() {


// TODO: Implement the logic for dispatching units to incidents.
// For each incident, find the appropriate units based on required types and proximity.
// Select the nearest eligible unit and update its state to dispatched.
// Track dispatched units in the incident structure.
// Hint: Use loops and Manhattan distance to determine proximity.

                      
}

void update_incidents() {

// TODO: Implement logic for updating incidents over time.
// For each incident, check if all required units have arrived at the location.
// Update the state of the incident based on unit arrivals and remaining operation time.
// When an incident finishes, update the state of its dispatched units accordingly. 
// Also remember to reset the dispatch count after operation is finished.

}




void ensure_incident_capacity() {
    if (incident_count >= incident_capacity) {
        // TODO: Implement memory reallocation logic if using dynamic memory for incidents.
        // If using static arrays, explain why this function is unnecessary.
    }
}