#ifndef PROCESSOR_H
#define PROCESSOR_H

typedef struct {
    char city_name[50];
    int seismic_level;
    float risk_percent;
    int has_risk_percent;
} CityData;

int process_csv(const char *filename, CityData **cities, int *num_cities);
int write_output(const char *filename, CityData *cities, int n_cities);

#endif
 
