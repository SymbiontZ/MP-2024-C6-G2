#include<stdio.h>
#include"pedidos.h"
#include<stdlib.h>

int main()
{
    pedidos P=cargar_pedidos();
    
    int confirmacion=crear_pedido(3,P);
    if(confirmacion==-1){
        printf("se ha cancelado la compra\n");
    }
    else{
        printf("se ha realizado el pedido correctamente\n");
    }
    /*devoluciones D=cargar_devoluciones();
    printf("se ha cargado el fichero Devoluciones.txt correctamente\n");
    crear_devolucion(D,P, Prod_P);*/
    return 0;
}