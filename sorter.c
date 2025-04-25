#include <string.h>
#include "sorter.h"

int compare(const CityData *a, const CityData *b) {
    if (a->seismic_level != b->seismic_level)
        return b->seismic_level - a->seismic_level;

    if (a->missing_risk && !b->missing_risk)
        return 1;
    if (!a->missing_risk && b->missing_risk)
        return -1;

    if (a->seismic_level == 3) {
        if (a->missing_risk && !b->missing_risk)
            return 1;
        if (!a->missing_risk && b->missing_risk)
            return -1;
    }

    if (!a->missing_risk && !b->missing_risk) {
        if (a->risk_percent != b->risk_percent)
            return (b->risk_percent > a->risk_percent) ? 1 : -1;
    }

    return strcmp(b->city_name, a->city_name);
}

void swap(CityData *a, CityData *b) {
    CityData temp = *a;
    *a = *b;
    *b = temp;
}

int partition(CityData *data, int low, int high) {
    CityData pivot = data[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compare(&data[j], &pivot) < 0) {
            i++;
            swap(&data[i], &data[j]);
        }
    }
    swap(&data[i + 1], &data[high]);
    return i + 1;
}

void quicksort(CityData *data, int low, int high) {
    if (low < high) {
        int pi = partition(data, low, high);
        quicksort(data, low, pi - 1);
        quicksort(data, pi + 1, high);
    }
}
