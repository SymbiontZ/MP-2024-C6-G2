#include<stdio.h>
#include"Productos.h"

int main(){
    produ_vect pr = cargar_productos();
    printf("%s", pr.produ[0].nombre);
    return 0;
}