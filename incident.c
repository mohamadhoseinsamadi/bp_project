
#include "incident.h"
#include "log.h"
#include "unit.h"
#include "map.h"
#include <stdio.h>
#include <string.h>

Incident *incidents = NULL;
int incident_count = 0;
int incident_capacity = 0;

//start
IncidentRequirements Incident_Requirement[3][3] =  { { {1,0,0,3}, {1,1,0,6}, {1,1,1,8} },
                                                     { {0,1,0,1} ,{0,1,0,3} ,{0,1,0,5} },
                                                     { {0,0,1,2} ,{0,1,1,4} ,{0,1,1,8} } };

// TODO: Initiate an array for storing incident requirements for different incident types and different priorities
// HINT: Use a 2d array of incident requirements like this:
// HINT:               Incident Requirement : {fire_units, medical_units, police_units, time_required}
//                         LOW      MEDIUM    HIGH
//            FIRE    [ {1,0,0,3} {1,1,0,6} {1,1,1,8}
//            MEDICAL   {0,1,0,1} {0,1,0,3} {0,1,0,5}
//            POLICE    {0,0,1,2} {0,1,1,4} {0,1,1,8} ]
//


void dispatch_units() {
//start
    ensure_incident_capacity();

    for(int i=0;i<incident_count;i++){
        Incident *Inc=&incidents[i];
        IncidentType type=Inc->type;
        Priority priority=Inc->priority;
        int t=(type==FIRE)?0:(type==MEDICAL)?1:2;
        int p=(priority==LOW)?0:(priority==MEDIUM)?1:2;
        IncidentRequirements needed=Incident_Requirement[t][p];

        if(Inc->dispatched_count[0] < needed.fire_unit_needed){
            //sorting ...
            int depfiresize=0;
            for(int d=0;d<department_count;d++){
                if(departments[d].type==FIRE){
                    depfiresize++;
                }
            }
            Department fire_dep[depfiresize];
            int index=0;
            for(int d=0;i,department_count;d++){
                if(departments[d].type==FIRE){
                    fire_dep[index++]=departments[d];
                }
            }
            for(int d=0;d<depfiresize;d++){
                int mindistance=manhattan_distance(fire_dep[d].x,fire_dep[d].y,Inc->x,Inc->y);
                int index=d;
                for(int f=d+1;f<depfiresize;f++){
                    if(manhattan_distance(fire_dep[f].x,fire_dep[f].y,Inc->x,Inc->y)<mindistance){
                        mindistance=manhattan_distance(fire_dep[f].x,fire_dep[f].y,Inc->x,Inc->y);
                        index=f;
                    }
                }
                Department* temp=&fire_dep[d];
                fire_dep[d]=fire_dep[index];
                fire_dep[index]=*temp;
            }
            //firedep sorted
            for (int j = 0; (j< depfiresize) && (Inc->dispatched_count[0] < needed.fire_unit_needed); j++) {
                Department *dep=&fire_dep[j];
                for(int k=0 ; (k < dep->unit_count)&&(Inc->dispatched_count[0] < needed.fire_unit_needed) ; k++){
                    Unit *u = &dep->units[k];
                    if(u->state==UNIT_WAITING){
                        Inc->dispatched_units[0][Inc->dispatched_count[0]]=u;
                        Inc->dispatched_count[0]++;
                        u->state=UNIT_DISPATCHED;
                        u->target_x=Inc->x;
                        u->target_y=Inc->y;
                    }
                }
                
            }
        }
        if(Inc->dispatched_count[1] < needed.medical_unit_needed){
            //sorting ...
            int depmedicalsize=0;
            for(int d=0;d<department_count;d++){
                if(departments[d].type==MEDICAL){
                    depmedicalsize++;
                }
            }
            Department medical_dep[depmedicalsize];
            int index=0;
            for(int d=0;i,department_count;d++){
                if(departments[d].type==MEDICAL){
                    medical_dep[index++]=departments[d];
                }
            }
            for(int d=0;d<depmedicalsize;d++){
                int mindistance=manhattan_distance(medical_dep[d].x,medical_dep[d].y,Inc->x,Inc->y);
                int index=d;
                for(int f=d+1;f<depmedicalsize;f++){
                    if(manhattan_distance(medical_dep[f].x,medical_dep[f].y,Inc->x,Inc->y)<mindistance){
                        mindistance=manhattan_distance(medical_dep[f].x,medical_dep[f].y,Inc->x,Inc->y);
                        index=f;
                    }
                }
                Department* temp=&medical_dep[d];
                medical_dep[d]=medical_dep[index];
                medical_dep[index]=*temp;
            }
            //medicaldep sorted
            for (int j = 0; (j< depmedicalsize) && (Inc->dispatched_count[1] < needed.medical_unit_needed); j++) {
                Department *dep=&medical_dep[j];
                for(int k=0 ; (k < dep->unit_count)&&(Inc->dispatched_count[1] < needed.medical_unit_needed) ; k++){
                    Unit *u = &dep->units[k];
                    if(u->state==UNIT_WAITING){
                        Inc->dispatched_units[1][Inc->dispatched_count[1]]=u;
                        Inc->dispatched_count[1]++;
                        u->state=UNIT_DISPATCHED;
                        u->target_x=Inc->x;
                        u->target_y=Inc->y;
                    }
                }
                
            }
        }
        if(Inc->dispatched_count[2] < needed.police_unit_needed){
            //sorting ...
            int deppolicesize=0;
            for(int d=0;d<department_count;d++){
                if(departments[d].type==POLICE){
                    deppolicesize++;
                }
            }
            Department police_dep[deppolicesize];
            int index=0;
            for(int d=0;i,department_count;d++){
                if(departments[d].type==POLICE){
                    police_dep[index++]=departments[d];
                }
            }
            for(int d=0;d<deppolicesize;d++){
                int mindistance=manhattan_distance(police_dep[d].x,police_dep[d].y,Inc->x,Inc->y);
                int index=d;
                for(int f=d+1;f<deppolicesize;f++){
                    if(manhattan_distance(police_dep[f].x,police_dep[f].y,Inc->x,Inc->y)<mindistance){
                        mindistance=manhattan_distance(police_dep[f].x,police_dep[f].y,Inc->x,Inc->y);
                        index=f;
                    }
                }
                Department* temp=&police_dep[d];
                police_dep[d]=police_dep[index];
                police_dep[index]=*temp;
            }
            //policedep sorted
            for (int j = 0; (j< deppolicesize) && (Inc->dispatched_count[2] < needed.police_unit_needed); j++) {
                Department *dep=&police_dep[j];
                for(int k=0 ; (k < dep->unit_count)&&(Inc->dispatched_count[2] < needed.police_unit_needed) ; k++){
                    Unit *u = &dep->units[k];
                    if(u->state==UNIT_WAITING){
                        Inc->dispatched_units[2][Inc->dispatched_count[2]]=u;
                        Inc->dispatched_count[2]++;
                        u->state=UNIT_DISPATCHED;
                        u->target_x=Inc->x;
                        u->target_y=Inc->y;
                    }
                }
                
            }
        }

        
    }
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
    //start
    if (incident_count >= incident_capacity) {
        if(incident_capacity==0){
            incident_capacity=1;
            incidents =(Incident *)malloc(1*sizeof(Incident));
        }
        else{
            incident_capacity*=2;
            incidents =(Incident *)realloc(incidents,incident_capacity*sizeof(Incident));
        }
    }
    // TODO: Implement memory reallocation logic if using dynamic memory for incidents.
    // If using static arrays, explain why this function is unnecessary.
}