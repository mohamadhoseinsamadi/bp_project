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
int ex=0;

void simulation_loop(){
    init_log();
    log_simulation_start();
    load_configuration("C:\\Users\\Padidar\\CLionProjects\\untitled5\\sample_config.txt");
    while (!ex){
        if(turn%10==0){
            process_user_input();
        }
        if(ex==1){
            log_simulation_end();
            int total_time_solved=0;
            for(int i=0;i<incident_count;i++){
                if(finish_time[i]!=-1){
                    total_time_solved+=finish_time[i]-create_time[i];
                }
            }
            printf("\nsolved: %d   unsolved:%d\n",solved,incident_count-solved);
            if(solved!=0){
                printf("average time: %d\n",total_time_solved/solved);
            }
            break;
        }
        printf("===City Map===\n");
        perform_turn_actions();
        turn++;
        printf("===============\n");
        printf(" ...Turn %d...\n",turn);
        if(turn%10!=0) {
            printf("Press Enter to continue...\n");
            fflush(stdin);
            getchar();
        }

    }
    
}
void process_user_input(){
    printf("1. Enter a new incident\n2. Continue simulation\n3. Exit\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d",&choice);
    while (choice==1){
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
        create_time[incident_count]=turn;
        finish_time[incident_count]=-1;
        incident_count++;
        printf("1. Enter a new incident\n2. Continue simulation\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
    }
    if(choice==2) {
        return;
    }
    else if(choice==3){
        ex=1;
        return;
    }
}
void perform_turn_actions(){
    dispatch_units();
    update_units_movement();
    update_incidents();
    update_and_render();
}