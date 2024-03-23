#include<stdio.h>
#include"pedidos.h"
#include<stdlib.h>

int main()
{
    pedidos P=cargar_pedidos();
    printf("se ha cargado el fichero correctamente\n");
    crear_pedido(3,P);
    
    return 0;
}