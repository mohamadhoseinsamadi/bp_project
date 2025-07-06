#include "incident.h"
#include "unit.h"
#include "map.h"
#include "log.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

Department departments[MAX_DEPARTMENTS];
int department_count = 0;

int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

void move_unit_one_step(Unit *u) {
    if( abs(u->target_x - u->x)>0 ){
        if(( u->target_x - u->x ) >0) {
            u->x++;
        }
        else {
            u->x--;
        }
    }
    else if( abs(u->target_y - u->y)>0 ){
        if(( u->target_y - u->y ) >0 ){
            u->y++ ;
        }
        else {
            u->y--;
        }
    }
  
}

void update_units_movement() {
    //start
    for (int i = 0; i < department_count; i++) {
        for (int j = 0; j < departments[i].unit_count; j++) {
            Unit *u = &departments[i].units[j];
            if(u->state==UNIT_DISPATCHED){
                move_unit_one_step(u);
                if(u->target_x==u->x&&u->target_y==u->y){
                    u->state=UNIT_OPERATING;
                    log_unit_state_change(u,UNIT_OPERATING);
                }
            }
            else if(u->state==UNIT_RETURNING){
                move_unit_one_step(u);
                if(u->target_x==u->x&&u->target_y==u->y){
                    u->state=UNIT_TIRED;
                    u->tired_time=2;
                    log_unit_state_change(u,UNIT_TIRED);
                }
            }
            else if(u->state==UNIT_TIRED){
                u->tired_time--;
                if(u->tired_time==0){
                    u->state=UNIT_WAITING;
                    log_unit_state_change(u,UNIT_WAITING);
                }
            }

        }
    }

}