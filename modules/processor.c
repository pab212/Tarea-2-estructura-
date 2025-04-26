#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processor.h"
#include "validator.h"

#define MAX_LINE 256

int process_csv(const char *filename, CityData **cities, int *num_cities) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    char line[256];
    *cities = NULL;
    *num_cities = 0;
    int capacity = 1000; // capacidad inicial 
    *cities = (CityData *)malloc(capacity * sizeof(CityData));
    if (!*cities) {
        fclose(file);
        return 0;
    }

    // Saltar el header
    if (!fgets(line, sizeof(line), file)) {
        free(*cities);
        fclose(file);
        return 0;
    }

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        CityData city;
        char *token = strtok(line, ",");
        if (!token) continue; // verifica lineas vacias
        strncpy(city.city_name, token, 49);
        city.city_name[49] = '\0';

        token = strtok(NULL, ",");
        if (!token || !validate_seismic_level(token, &city.seismic_level)) continue;

        token = strtok(NULL, ",");
        city.has_risk_percent = token && *token && validate_risk_percent(token, &city.risk_percent);

        if (*num_cities >= capacity) {
            capacity *= 2;
            CityData *temp = (CityData *)realloc(*cities, capacity * sizeof(CityData));
            if (!temp) {
                free(*cities);
                fclose(file);
                return 0;
            }
            *cities = temp;
        }

        (*cities)[*num_cities] = city;
        (*num_cities)++;
    }

    fclose(file);
    return 1;
}

int write_output(const char *filename, CityData *cities, int n_cities) {
    FILE *file = fopen(filename, "w");
    if (!file) return 0;

    fprintf(file, "city_name,seismic_level,risk_percent\n");

    for (int i = 0; i < n_cities; i++) {
        if (cities[i].has_risk_percent) {
            fprintf(file, "%s,%d,%.1f\n", cities[i].city_name, cities[i].seismic_level, cities[i].risk_percent);
        } else {
            fprintf(file, "%s,%d,\n", cities[i].city_name, cities[i].seismic_level);
        }
    }

    fclose(file);
    return 1;
}