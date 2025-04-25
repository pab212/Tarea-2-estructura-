#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processor.h"
#include "validator.h"

#define MAX_LINE 256

CityData* read_csv(const char *filename, int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    char line[MAX_LINE];
    fgets(line, MAX_LINE, file); // skip header

    int capacity = 1000;
    *count = 0;
    CityData *data = malloc(sizeof(CityData) * capacity);

    while (fgets(line, MAX_LINE, file)) {
        if (*count >= capacity) {
            capacity *= 2;
            data = realloc(data, sizeof(CityData) * capacity);
        }

        CityData city;
        city.missing_risk = 0;

        char *token = strtok(line, " \t\n");
        if (!token) continue;
        strcpy(city.city_name, token);

        token = strtok(NULL, " \t\n");
        if (!token || !is_valid_seismic_level(token)) continue;
        city.seismic_level = atoi(token);

        token = strtok(NULL, " \t\n");
        if (token && is_valid_risk_percent(token)) {
            city.risk_percent = atof(token);
        } else {
            city.risk_percent = 0.0;
            city.missing_risk = 1;
        }

        data[(*count)++] = city;
    }

    fclose(file);
    return data;
}

void write_output(const char *filename, CityData *data, int n) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < n; i++) {
        if (data[i].missing_risk)
            fprintf(file, "%s %d\n", data[i].city_name, data[i].seismic_level);
        else
            fprintf(file, "%s %d %.1f\n", data[i].city_name, data[i].seismic_level, data[i].risk_percent);
    }
    fclose(file);
}
