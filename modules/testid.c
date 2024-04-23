#include <stdio.h>

// Función para eliminar un elemento de un array
void eliminarElemento(int array[], int *tam, int elemento) {
    int i, j;
    for (i = 0; i < *tam; i++) {
        if (array[i] == elemento) {
            // Desplazar los elementos restantes una posición hacia la izquierda
            for (j = i; j < *tam - 1; j++) {
                array[j] = array[j + 1];
            }
            (*tam)--; // Reducir el tamaño del array
            i--; // Compensar el desplazamiento
        }
    }
}

// Función para reajustar los números restantes en la secuencia
void reajustarSecuencia(int array[], int tam, int num_elim) {
    int i;
    for (i = 0; i < tam; i++) {
        if (array[i] > num_elim) {
            array[i]--; // Reducir el valor en 1
        }
    }
}

int main() {
    int secuencia[] = {1, 2, 3, 5, 5, 6, 6, 8, 8};
    int tam = sizeof(secuencia) / sizeof(secuencia[0]);
    int elemento_a_eliminar = 6;

    // Eliminar el elemento especificado
    eliminarElemento(secuencia, &tam, elemento_a_eliminar);

    // Reajustar los números restantes en la secuencia
    reajustarSecuencia(secuencia, tam, elemento_a_eliminar);

    // Imprimir la nueva secuencia
    printf("Secuencia resultante:\n");
    for (int i = 0; i < tam; i++) {
        printf("%d ", secuencia[i]);
    }
    printf("\n");

    return 0;
}