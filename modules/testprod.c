#include "complementos.h"
#include "Productos.h"
int main(){
    produ_vect prods = cargar_productos();

    prods = agregar_productos(prods);
    
    return 0;
}