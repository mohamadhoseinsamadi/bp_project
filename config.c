
#include "config.h"
#include "map.h"
#include "unit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_configuration(const char *filename) {
    FILE *file = fopen("C:\\Users\\Padidar\\Desktop\\basic\\basic\\sample_config.txtename", "r");
    if (!file) {
        printf("Failed to open configuration file.\n");
        exit(1);
    }

    char line[128];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "MAP_SIZE", 8) == 0) {
            sscanf(line, "MAP_SIZE %d %d", &map_width, &map_height);
        }
        //////start:
        else if( strncmp(line, "DEPARTMENT FIRE", 15) == 0){
            sscanf(line , "DEPARTMENT FIRE %d %d %d %d",
                   &departments[department_count].number,&departments[department_count].x,
                   &departments[department_count].y,&departments[department_count].unit_count);
            departments[department_count].type=FIRE;
            for(int i=0;i<departments[department_count].unit_count;i++){
                departments[department_count].units[i].x=departments[department_count].x;
                departments[department_count].units[i].y=departments[department_count].y;
                departments[department_count].units[i].type=FIRE;
                departments[department_count].units[i].departmentNumber=departments[department_count].number;
                departments[department_count].units[i].unitNumber=i+1;
                departments[department_count].units[i].state=UNIT_WAITING;
            }
            department_count++;
        }
        else if( strncmp(line, "DEPARTMENT MEDICAL", 18) == 0 ){
            sscanf(line , "DEPARTMENT MEDICAL %d %d %d %d",
                   &departments[department_count].number,&departments[department_count].x,
                   &departments[department_count].y,&departments[department_count].unit_count);
            departments[department_count].type=MEDICAL;
            for(int i=0;i<departments[department_count].unit_count;i++){
                departments[department_count].units[i].x=departments[department_count].x;
                departments[department_count].units[i].y=departments[department_count].y;
                departments[department_count].units[i].type=MEDICAL;
                departments[department_count].units[i].departmentNumber=departments[department_count].number;
                departments[department_count].units[i].unitNumber=i+1;
                departments[department_count].units[i].state=UNIT_WAITING;
            }
            department_count++;
        }
        else if( strncmp(line, "DEPARTMENT POLICE", 17) == 0 ){
            sscanf(line , "DEPARTMENT POLICE %d %d %d %d",
                   &departments[department_count].number,&departments[department_count].x,
                   &departments[department_count].y,&departments[department_count].unit_count);
            departments[department_count].type=POLICE;
            for(int i=0;i<departments[department_count].unit_count;i++){
                departments[department_count].units[i].x=departments[department_count].x;
                departments[department_count].units[i].y=departments[department_count].y;
                departments[department_count].units[i].type=POLICE;
                departments[department_count].units[i].departmentNumber=departments[department_count].number;
                departments[department_count].units[i].unitNumber=i+1;
                departments[department_count].units[i].state=UNIT_WAITING;
            }
            department_count++;
        }
        

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