#include <stdio.h>
#include "useradmin.h"

int main(){
    printf("###INTERFAZ INICIAL###\n");
    
    clients C = cargar_clientes();
    //C = agregar_cliente(C);
    //guardar_clientes(C);
    gestionar_cliente(C, C.n_clients-1);
    return 0;
}