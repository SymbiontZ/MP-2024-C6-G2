#include<stdio.h>
#include"pedidos.h"
#include<stdlib.h>

int main()
{
    /*pedidos P=cargar_pedidos();
    printf("se ha cargado el fichero correctamente\n");
    //crear_pedido(3,P);
    prod_pedidos Prod_P=cargar_prod_pedidos();
    guardar_productos_pedidos(Prod_P);
    crear_producto_pedido(P,12, 2,Prod_P);*/
    devoluciones D=cargar_devoluciones();
    guardar_devoluciones(D);
    return 0;
}