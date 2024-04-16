#include "useradmin.h"

int main(){
    clients C = cargar_clientes();

    menucliente(C, 2);
    return 0;
}