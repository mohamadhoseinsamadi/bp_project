
#include "unit.h"
#include "map.h"
#include "log.h"
#include <stdlib.h>
#include <stdio.h>

Department departments[MAX_DEPARTMENTS];
int department_count = 0;

int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

void move_unit_one_step(Unit *u) {
    // Just for debugging purposes. Remove after complete implementation.
    printf("Moving Unit %d-%d\n", u->departmentNumber, u->unitNumber);

    // TODO: Implement logic to move the unit one step toward its target.
    // Only move along one axis per function call. Prioritize X direction.
    // Hint: Use simple conditionals to decide whether to increment or decrement X or Y.

}

void update_units_movement() {
    // TODO: Iterate through all departments and units.
    // For each unit in DISPATCHED or RETURNING state, move it one step toward its target.
    // If the unit reaches its target, update its state accordingly.
    // Don't forget to log the state changes using the appropriate logging function.

}