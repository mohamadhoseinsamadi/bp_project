
#include "map.h"
#include "common.h"
#include "incident.h"
#include "unit.h"
#include <stdio.h>
#include <string.h>

MapCell map[MAP_MAX_HEIGHT][MAP_MAX_WIDTH];
int map_width = 20, map_height = 10;

void clear_map() {
    // TODO: Complete the loop to iterate over the entire map grid.
// For each cell, reset the symbol to " .  " to represent an empty cell.
// Hint: Use two nested loops to cover all rows and columns.

}

void render_map() {
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
    // TODO: Determine the correct order of rendering the map.
// Call functions to clear the map, place departments, incidents, and units.
// Finally, call the function that renders the map to the console.

}