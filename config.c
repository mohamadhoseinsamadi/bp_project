
#include "config.h"
#include "map.h"
#include "unit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_configuration(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open configuration file.\n");
        exit(1);
    }

    char line[128];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "MAP_SIZE", 8) == 0) {
            sscanf(line, "MAP_SIZE %d %d", &map_width, &map_height);
        } 
        // TODO: Parse "DEPARTMENT" lines from the configuration file.
        // Extract department type, index, coordinates, and unit count.
        // Initialize the department fields accordingly.
        // Then, initialize each unit for the department with appropriate values.
        // Hint: Use sscanf to parse values and a loop to initialize units.

    }

    fclose(file);
}

IncidentType parse_department_type(const char *str) {
    if (strcmp(str, "FIRE") == 0) return FIRE;
    if (strcmp(str, "MEDICAL") == 0) return MEDICAL;
    return POLICE;
}

Priority parse_priority(const char *str) {
    if (strcmp(str, "LOW") == 0) return LOW;
    if (strcmp(str, "MEDIUM") == 0) return MEDIUM;
    return HIGH;
}