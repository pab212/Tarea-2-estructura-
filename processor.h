#ifndef PROCESSOR_H
#define PROCESSOR_H

typedef struct {
    char city_name[50];
    int seismic_level;
    float risk_percent;
    int missing_risk;
} CityData;

CityData* read_csv(const char *filename, int *count);
void write_output(const char *filename, CityData *data, int n);

#endif
 
