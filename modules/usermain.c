#include <stdio.h>
#include "useradmin.h"

int main(){
    printf("###INTERFAZ INICIAL###\n");
    
    clients C = cargar_clientes();
    //C = agregar_cliente(C);
    //guardar_clientes(C);
    
    return 0;
}