#include "simulation.h"
#include "common.h"
#include "config.h"
#include "incident.h"
#include "log.h"
#include "map.h"
#include "unit.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
int exit=0;
void simulation_loop(){
    int turn=0;
    init_log();
    log_simulation_start();
    while (!exit){
        if(turn%10==0){
            process_user_input();
        }
        perform_turn_actions();
        turn++;
    }
    
}
void process_user_input(){
    printf("1. Enter a new incident\n2. Continue simulation\n3. Exit\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:{
        printf("Enter type (FIRE , MEDICAL , CRIME) :");
        char type[10];
        scanf("%s",type);
        printf("Enter priority (HIGH , MEDIUM , LOW) :");
        char priority[10];
        scanf("%s",priority);
        printf("Enter coordinate (x  y) :");
        int x,y;
        scanf("%d %d",&x,&y);
        Incident inc;
        inc.x=x;
        inc.y=y;
        inc.type=parse_department_type(type);
        inc.state=INCIDENT_WAITING;
        inc.priority=parse_priority(priority);
        inc.dispatched_count[0]=0;        
        inc.dispatched_count[1]=0;
        inc.dispatched_count[2]=0;
        log_incident_created(inc.type,inc.priority,inc.x,inc.y);
        ensure_incident_capacity();
        incidents[incident_count]=inc;
        incident_count++;
    }
        break;
    case 2:{
        return;
    }   
        break;
    case 3:{
        exit=1;
        return;
    }   
        break;
    default:
        break;
    }
}
void perform_turn_actions(){
    dispatch_units();
    update_units_movement();
    update_incidents();
    update_and_render();
}