#include "complementos.h"
#include "Productos.h"



int main(){

    produ_vect prods = cargar_productos(prods);

    
    int pos = buscar_productos(prods);

    printf("\n\nSe ha seleccionado la posicion producto: %d\n\n", pos);

    return 0;
}