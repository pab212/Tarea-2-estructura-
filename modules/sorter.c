#include <string.h>
#include "sorter.h"

// compara dos ciudades según los criterios dados
int compare_cities(const CityData *a, const CityData *b) {
    if (a->seismic_level != b->seismic_level) {
        return b->seismic_level - a->seismic_level;
    }
    // compara risk_percent
    if (a->has_risk_percent && b->has_risk_percent) {
        if (a->risk_percent != b->risk_percent) {
            return (b->risk_percent > a->risk_percent) ? 1 : -1;
        }
    } else if (a->has_risk_percent && !b->has_risk_percent) {
        return -1;
    } else if (!a->has_risk_percent && b->has_risk_percent) {
        return 1;
    } else {
        // sin risk_percent
    }

    return strcmp(b->city_name, a->city_name);
}

void swap(CityData *a, CityData *b) {
    CityData temp = *a;
    *a = *b;
    *b = temp;
}

// partition del arreglo para el quicksort
int partition(CityData *cities, int low, int high) {
    CityData pivot = cities[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compare_cities(&cities[j], &pivot) <= 0) {
            i++;
            swap(&cities[i], &cities[j]);
        }
    }
    swap(&cities[i + 1], &cities[high]);
    return i + 1;
}

//  quicksort
void quicksort(CityData *cities, int low, int high) {
    if (low < high) {
        int pi = partition(cities, low, high);
        quicksort(cities, low, pi - 1);
        quicksort(cities, pi + 1, high);
    }
}