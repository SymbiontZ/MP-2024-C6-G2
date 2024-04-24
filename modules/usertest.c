#include "useradmin.h"

int main(){
    clients C = cargar_clientes();
    admin_prov_vect adminprov = cargar_adminprov();
    //menuadmin(adminprov, 0);
    menucliente(C, 2);
    return 0;
}