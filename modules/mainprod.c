#include "complementos.h"
#include "Productos.h"

int main(){
    produ_vect pr = cargar_productos();

    menu_prod(pr);
    return 0;
}