
#include "map.h"
#include "common.h"
#include "incident.h"
#include "unit.h"
#include <stdio.h>
#include <string.h>

MapCell map[MAP_MAX_HEIGHT][MAP_MAX_WIDTH];

void clear_map() {
    //start:
    for(int i=0;i<map_height;i++){
        for(int j=0 ; j<map_width;j++){
            sprintf(map[i][j].symbol," .  ");
        }
    }
    // TODO: Complete the loop to iterate over the entire map grid.
// For each cell, reset the symbol to " .  " to represent an empty cell.
// Hint: Use two nested loops to cover all rows and columns.

}

void render_map() {
    //start
    for(int i=0;i<map_height;i++){
        for(int j=0;j<map_width;j++){
            printf("%s",map[i][j].symbol);
        }
        printf("\n");
    }
    // TODO: Implement the logic to print the entire map.
// Hint: Use two nested loops to print each cell's symbol followed by a space.
// Don't forget to print a newline after each row and draw borders if necessary.

}

void place_departments() {
    for (int i = 0; i < department_count; i++) {
        char type_char = (departments[i].type == FIRE) ? 'F' :
                         (departments[i].type == MEDICAL) ? 'M' : 'P';
        sprintf(map[departments[i].y][departments[i].x].symbol, "_%c%d_", type_char, departments[i].number);
    }
}

void place_incidents() {
    //start
    for(int i=0 ; i< incident_count ; i++){
        if(incidents[i].state!=INCIDENT_FINISHED){
            char type= (incidents[i].type == FIRE) ? 'F' : (incidents[i].type == MEDICAL) ? 'M' : 'P';
            char priority=(incidents[i].priority==HIGH)?'H':(incidents[i].priority==MEDIUM)?'M':'L';
            sprintf( map[incidents[i].y][incidents[i].x].symbol, "!%c%c!" , type, priority );
        }
    }
    // TODO: Implement this function to place incidents on the map.
// Only incidents that are not finished should be placed.
// Determine the correct symbol based on incident type and priority.
// Hint: Use sprintf to format the symbol string and assign it to the correct map cell.

}

void place_units() {
    for (int i = 0; i < department_count; i++) {
        for (int j = 0; j < departments[i].unit_count; j++) {
            Unit *u = &departments[i].units[j];
            if (strcmp(map[u->y][u->x].symbol, " .  ") == 0) {
                char type_char = (u->type == FIRE) ? 'F' :
                                 (u->type == MEDICAL) ? 'M' : 'P';
                sprintf(map[u->y][u->x].symbol, "%c%d-%d", 
                        type_char, u->departmentNumber, u->unitNumber);
            }
        }
    }
}

void update_and_render() {

    //start
    clear_map();
    place_departments();
    place_incidents();
    place_units();
    render_map();
    // TODO: Determine the correct order of rendering the map.
// Call functions to clear the map, place departments, incidents, and units.
// Finally, call the function that renders the map to the console.

}