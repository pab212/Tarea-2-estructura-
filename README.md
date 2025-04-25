# Tarea 2 - Reporte del Código

**Grupo 12:** Pablo Morales, Camilo Gaete, Santiago Hormazábal

## 📝 Descripción general

Este proyecto consiste en leer un archivo CSV generado aleatoriamente con parámetros de distintas ciudades de Chile, incluyendo:

- Grado de temblor  
- Porcentaje de riesgo  

El programa identifica las ciudades que experimentaron temblores y sus respectivos niveles de riesgo. Al finalizar, entrega como resultado las ciudades con:

- Los temblores de **mayor magnitud**  
- El **mayor porcentaje de riesgo**  

## 📁 Estructura del Código

- `main.c`: Función principal del programa
- `types.h`: Definición de la estructura `CityData`
- `Makefile`: Compilación automatizada
- `modules/`
  - `processor.c` y `processor.h`: Lectura del archivo CSV
  - `sorter.c` y `sorter.h`: Algoritmo QuickSort personalizado
  - `validator.c` y `validator.h`: Validación y normalización de datos

## ⚙️ Funcionalidades principales

1. Lectura línea por línea del archivo CSV  
2. Priorización de las ciudades con mayor magnitud de temblores y riesgo  
3. Uso de memoria dinámica con `malloc` y liberación con `free`  

---

¡Gracias por revisar nuestro trabajo!
