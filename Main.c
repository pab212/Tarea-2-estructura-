#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modules/processor.h" 
#include "modules/sorter.h"
#include "modules/validator.h"
// types.h - Definición de la estructura CityData utilizada en todo el programa.

#define TYPES_H

typedef struct {
    char city_name[50];
    int seismic_level;
    float risk_percent; // -1.0 indica valor faltante
} CityData;

// Función principal del programa.
// Argumentos esperados: <input.csv> <N_CITIES> <output.txt>
// Realiza la carga, validación, ordenamiento y escritura del archivo de salida.
int main(int argc, char *argv[]) {
    // Validar número de argumentos
    if (argc != 4) {
        printf("Uso: %s <input.csv> <N_CITIES> <output.txt>\n", argv[0]);
        return 1;
    }

    char *input_file = argv[1];
    int n_cities = atoi(argv[2]);
    char *output_file = argv[3];

    // Cargar datos desde el archivo CSV
    int city_count = 0;
    CityData *cities = load_csv(input_file, &city_count);

    if (!cities) {
        fprintf(stderr, "Error al cargar el archivo.\n");
        return 1;
    }

    // Normalizar campos faltantes y asignar valores artificiales para ordenar
    validate_and_normalize(cities, city_count);

    // Ordenar ciudades usando quicksort personalizado
    quick_sort(cities, 0, city_count - 1);

    // Abrir archivo de salida para escritura
    FILE *fout = fopen(output_file, "w");
    if (!fout) {
        perror("No se pudo abrir el archivo de salida");
        free(cities);
        return 1;
    }

    // Escribir encabezado
    fprintf(fout, "city_name,seismic_level,risk_percent\n");

    // Escribir las N ciudades más prioritarias
    for (int i = 0; i < city_count && i < n_cities; i++) {
        // Si el campo fue normalizado, dejarlo vacío en la salida
        if (cities[i].risk_percent == -10.0 ||
            cities[i].risk_percent == 50.0 ||
            cities[i].risk_percent == 110.0)
        {
            fprintf(fout, "%s,%d,\n", cities[i].city_name, cities[i].seismic_level);
        }
        else
        {
            fprintf(fout, "%s,%d,%.1f\n", cities[i].city_name, cities[i].seismic_level, cities[i].risk_percent);
        }
    }

    // Cerrar archivo y liberar memoria
    fclose(fout);
    free(cities);

    return 0;
}
