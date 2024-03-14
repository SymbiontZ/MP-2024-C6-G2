#include <stdio.h>
#include "useradmin.h"

int main(){
    printf("###INTERFAZ INICIAL###\n");
    
    clients C = cargar_clientes();

    printf("%d", C.n_clients);
    return 0;
}