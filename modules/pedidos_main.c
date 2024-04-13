#include<stdio.h>
#include"pedidos.h"
#include<stdlib.h>

int main()
{
    pedidos P=cargar_pedidos();
    printf("se ha cargado el fichero Pedidos.txt correctamente\n");
    //crear_pedido(3,P,1);
    prod_pedidos Prod_P=cargar_prod_pedidos();
    printf("Se ha cargado el fichero ProductosPedidos.txt correctamente\n");
    //guardar_productos_pedidos(Prod_P);
    //crear_producto_pedido(P,12, 2,Prod_P);*/
    devoluciones D=cargar_devoluciones();
    printf("se ha cargado el fichero Devoluciones.txt correctamente\n");
    crear_devolucion(D,P, Prod_P);
    return 0;
}