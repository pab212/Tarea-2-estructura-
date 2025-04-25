#include <stdlib.h>
#include <ctype.h>
#include "validator.h"

int is_valid_seismic_level(const char *value) {
    int num = atoi(value);
    return num >= 1 && num <= 5;
}

int is_valid_risk_percent(const char *value) {
    for (int i = 0; value[i]; i++) {
        if (!(isdigit(value[i]) || value[i] == '.'))
            return 0;
    }
    float num = atof(value);
    return num >= 0.0 && num <= 100.0;
} 
