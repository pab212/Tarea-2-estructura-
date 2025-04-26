#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modules/processor.h" 
#include "modules/sorter.h"
#include "modules/validator.h"

// ./tarea2 input.csv n_ciudades output.txt

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <input> <N> <output>\n", argv[0]);
        return 1;
    }

    // lee el numero de ciudades seleccionadas
    int n_cities = atoi(argv[2]);
    if (n_cities <= 0) {
        printf("Error: N debe ser un número positivo\n");
        return 1;
    }

    // procesa el .CSV
    CityData *cities = NULL;
    int num_cities = 0;
    if (!process_csv(argv[1], &cities, &num_cities)) {
        printf("Error al procesar el archivo %s\n", argv[1]);
        return 1;
    }

    if (n_cities > num_cities) {
        printf("Error: N (%d) es mayor al número de ciudades (%d)\n", n_cities, num_cities);
        free(cities);
        return 1;
    }

    // ordenar las ciudades usando quicksort
    quicksort(cities, 0, num_cities - 1);

    if (!write_output(argv[3], cities, n_cities)) {
        printf("Error al escribir el archivo %s\n", argv[3]);
        free(cities);
        return 1;
    }

    //liberacion de memoria final
    free(cities);
    return 0;
}