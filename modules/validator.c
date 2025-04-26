#include <stdlib.h>
#include <ctype.h>
#include "validator.h"

int validate_seismic_level(const char *str, int *seismic_level) {
    char *endptr;
    long value = strtol(str, &endptr, 10);
    if (*endptr != '\0' || str[0] == '\0') return 0;
    if (value < 1 || value > 5) return 0; 
    *seismic_level = (int)value;
    return 1;
}

int validate_risk_percent(const char *str, float *risk_percent) {
    if (!str || str[0] == '\0') return 0;
    char *endptr;
    float value = strtof(str, &endptr);
    if (*endptr != '\0') return 0; 
    *risk_percent = value;
    return 1;
}
