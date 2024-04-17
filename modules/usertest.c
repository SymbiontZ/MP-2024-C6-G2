#include "useradmin.h"

int main(){
    clients C = cargar_clientes();
    admin_prov_vect adminprov = cargar_adminprov();
    printf("Hola");
    menuadmin(adminprov, 0);
    return 0;
}