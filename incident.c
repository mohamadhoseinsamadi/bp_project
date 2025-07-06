#include "utils.h"
#include "incident.h"
#include "log.h"
#include "unit.h"
#include "map.h"
#include <stdio.h>
#include "simulation.h"
#include <string.h>

Incident *incidents = NULL;
int incident_count = 0;
int incident_capacity = 0;

IncidentRequirements Incident_Requirement[3][3] =  { { {1,0,0,3}, {1,1,0,6}, {1,1,1,8} },
                                                     { {0,1,0,1} ,{0,1,0,3} ,{0,1,0,5} },
                                                     { {0,0,1,2} ,{0,1,1,4} ,{0,1,1,8} } };

void dispatch_units() {
    ensure_incident_capacity();

    for(int i=0;i<incident_count;i++){
        Incident *Inc=&incidents[i];
        IncidentType type=Inc->type;
        Priority priority=Inc->priority;
        int t=(type==FIRE)?0:(type==MEDICAL)?1:2;
        int p=(priority==LOW)?0:(priority==MEDIUM)?1:2;
        IncidentRequirements needed=Incident_Requirement[t][p];
        if(Inc->state==INCIDENT_FINISHED||Inc->state==INCIDENT_OPERATION){
            continue;
        }
        if(Inc->dispatched_count[0] < needed.fire_unit_needed){
            //sorting ...
            int depfiresize=0;
            for(int d=0;d<department_count;d++){
                if(departments[d].type==FIRE){
                    depfiresize++;
                }
            }
            Department* fire_dep[depfiresize];
            int s=0;
            for(int d=0;d<department_count;d++){
                if(departments[d].type==FIRE){
                    fire_dep[s++]=&departments[d];
                }
            }
            for(int d=0;d<depfiresize;d++){
                int mindistance=manhattan_distance(fire_dep[d]->x,fire_dep[d]->y,Inc->x,Inc->y);
                int index=d;
                for(int f=d+1;f<depfiresize;f++){
                    if(manhattan_distance(fire_dep[f]->x,fire_dep[f]->y,Inc->x,Inc->y)<mindistance){
                        mindistance=manhattan_distance(fire_dep[f]->x,fire_dep[f]->y,Inc->x,Inc->y);
                        index=f;
                    }
                }
                Department* temp=fire_dep[d];
                fire_dep[d]=fire_dep[index];
                fire_dep[index]=temp;
            }
            //firedep sorted
            for (int j = 0; (j< depfiresize) && (Inc->dispatched_count[0] < needed.fire_unit_needed); j++) {
                Department* dep=fire_dep[j];
                for(int k=0 ; (k < dep->unit_count)&&(Inc->dispatched_count[0] < needed.fire_unit_needed) ; k++){
                    Unit *u = &dep->units[k];
                    if(u->state==UNIT_WAITING){
                        u->state=UNIT_DISPATCHED;
                        u->target_x=Inc->x;
                        u->target_y=Inc->y;
                        Inc->dispatched_units[0][Inc->dispatched_count[0]]=u;
                        Inc->dispatched_count[0]++;
                        log_unit_dispatched(u,u->target_x,u->target_y);
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
            Department* medical_dep[depmedicalsize];
            int s=0;
            for(int d=0;d<department_count;d++){
                if(departments[d].type==MEDICAL){
                    medical_dep[s++]=&departments[d];
                }
            }
            for(int d=0;d<depmedicalsize;d++){
                int mindistance=manhattan_distance(medical_dep[d]->x,medical_dep[d]->y,Inc->x,Inc->y);
                int index=d;
                for(int f=d+1;f<depmedicalsize;f++){
                    if(manhattan_distance(medical_dep[f]->x,medical_dep[f]->y,Inc->x,Inc->y)<mindistance){
                        mindistance=manhattan_distance(medical_dep[f]->x,medical_dep[f]->y,Inc->x,Inc->y);
                        index=f;
                    }
                }
                Department* temp=medical_dep[d];
                medical_dep[d]=medical_dep[index];
                medical_dep[index]=temp;
            }
            //medicaldep sorted
            for (int j = 0; (j< depmedicalsize) && (Inc->dispatched_count[1] < needed.medical_unit_needed); j++) {
                Department *dep=medical_dep[j];
                for(int k=0 ; (k < dep->unit_count)&&(Inc->dispatched_count[1] < needed.medical_unit_needed) ; k++){
                    Unit *u = &dep->units[k];
                    if(u->state==UNIT_WAITING){
                        u->state=UNIT_DISPATCHED;
                        u->target_x=Inc->x;
                        u->target_y=Inc->y;
                        Inc->dispatched_units[1][Inc->dispatched_count[1]]=u;
                        Inc->dispatched_count[1]++;
                        log_unit_dispatched(u,u->target_x,u->target_y);
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
            Department* police_dep[deppolicesize];
            int s=0;
            for(int d=0;d<department_count;d++){
                if(departments[d].type==POLICE){
                    police_dep[s++]=&departments[d];
                }
            }
            for(int d=0;d<deppolicesize;d++){
                int mindistance=manhattan_distance(police_dep[d]->x,police_dep[d]->y,Inc->x,Inc->y);
                int index=d;
                for(int f=d+1;f<deppolicesize;f++){
                    if(manhattan_distance(police_dep[f]->x,police_dep[f]->y,Inc->x,Inc->y)<mindistance){
                        mindistance=manhattan_distance(police_dep[f]->x,police_dep[f]->y,Inc->x,Inc->y);
                        index=f;
                    }
                }
                Department* temp=police_dep[d];
                police_dep[d]=police_dep[index];
                police_dep[index]=temp;
            }
            //policedep sorted
            for (int j = 0; (j< deppolicesize) && (Inc->dispatched_count[2] < needed.police_unit_needed); j++) {
                Department *dep=police_dep[j];
                for(int k=0 ; (k < dep->unit_count)&&(Inc->dispatched_count[2] < needed.police_unit_needed) ; k++){
                    Unit *u = &dep->units[k];
                    if(u->state==UNIT_WAITING){
                        u->state=UNIT_DISPATCHED;
                        u->target_x=Inc->x;
                        u->target_y=Inc->y;
                        Inc->dispatched_units[2][Inc->dispatched_count[2]]=u;
                        Inc->dispatched_count[2]++;

                        log_unit_dispatched(u,u->target_x,u->target_y);
                    }
                }

            }
        }


    }

}

void update_incidents() {
    for(int i=0;i<incident_count;i++){
        Incident *Inc=&incidents[i];
        IncidentType type=Inc->type;
        Priority priority=Inc->priority;
        int t=(type==FIRE)?0:(type==MEDICAL)?1:2;
        int pr=(priority==LOW)?0:(priority==MEDIUM)?1:2;
        IncidentRequirements needed=Incident_Requirement[t][pr];
        if(Inc->state==INCIDENT_FINISHED){
            continue;
        }
        if(Inc->state==INCIDENT_OPERATION){
            Inc->operation_turns_remaining--;
            if(Inc->operation_turns_remaining==0){
                Inc->state=INCIDENT_FINISHED;
                finish_time[i]=turn;
                solved++;
                log_incident_finished(Inc->type,Inc->x,Inc->y);
                for(int f=0;f<Inc->dispatched_count[0];f++){
                    Unit *u = Inc->dispatched_units[0][f];
                    u->target_x=u->first_x;
                    u->target_y=u->first_y;
                    u->state=UNIT_RETURNING;
                    log_unit_returning(u,u->first_x,u->first_y);
                }
                for(int m=0;m<Inc->dispatched_count[1];m++){
                    Unit *u = Inc->dispatched_units[1][m];
                    u->target_x=u->first_x;
                    u->target_y=u->first_y;
                    u->state=UNIT_RETURNING;
                    log_unit_returning(u,u->first_x,u->first_y);
                }
                for(int p=0;p<Inc->dispatched_count[2];p++){
                    Unit *u = Inc->dispatched_units[2][p];
                    u->target_x=u->first_x;
                    u->target_y=u->first_y;
                    u->state=UNIT_RETURNING;
                    log_unit_returning(u,u->first_x,u->first_y);
                }
            }
        }
        if(Inc->state==INCIDENT_WAITING){
            if( (Inc->dispatched_count[0] == needed.fire_unit_needed)&&(Inc->dispatched_count[1] == needed.medical_unit_needed)&&(Inc->dispatched_count[2] == needed.police_unit_needed) ){
                int allarive=1;
                for(int f=0;f<Inc->dispatched_count[0];f++){
                    Unit *u = Inc->dispatched_units[0][f];
                    if(u->state!=UNIT_OPERATING){
                        allarive=0;
                        break;
                    }
                }
                for(int m=0;m<Inc->dispatched_count[1];m++){
                    Unit *u = Inc->dispatched_units[1][m];
                    if(u->state!=UNIT_OPERATING){
                        allarive=0;
                        break;
                    }
                }
                for(int p=0;p<Inc->dispatched_count[2];p++){
                    Unit *u = Inc->dispatched_units[2][p];
                    if(u->state!=UNIT_OPERATING){
                        allarive=0;
                        break;
                    }
                }
                if(allarive==1){
                    Inc->state=INCIDENT_OPERATION;
                    Inc->operation_turns_remaining=needed.required_time;
                    log_incident_status_change(Inc->x,Inc->y,Inc->state,Inc->type);
                }
            }
        }




    }

}




void ensure_incident_capacity() {
    if (incident_count >= incident_capacity) {
        if(incident_capacity==0){
            incident_capacity=1;
            incidents =(Incident *)malloc(1*sizeof(Incident));
            create_time=(int*)malloc(1*sizeof(int));
            finish_time=(int*)malloc(1*sizeof(int));
        }
        else{
            incident_capacity*=2;
            incidents =(Incident *)realloc(incidents,incident_capacity*sizeof(Incident));
            create_time=(int*)realloc(create_time,incident_capacity*sizeof(int));
            finish_time=(int*)realloc(finish_time,incident_capacity*sizeof(int));
        }
    }
   
}