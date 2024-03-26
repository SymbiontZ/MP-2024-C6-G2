#include <stdio.h>
#include "useradmin.h"

int main(){
    printf("###INTERFAZ INICIAL###\n");
    
    clients C = cargar_clientes();
    menu_cliente(C, 0);
    return 0;
}

