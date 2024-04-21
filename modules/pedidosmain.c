#include"pedidos.h"
#include"useradmin.h"

#include<stdio.h>
#include<stdlib.h>

int main()
{
    pedidos P=cargar_pedidos();
    prod_pedidos Prod_P=cargar_prod_pedidos();
    int confirmacion=crear_pedido(P, 1);
    if(confirmacion==-1){
        printf("se ha cancelado la compra\n");
    }
    else{
        printf("se ha realizado el pedido correctamente\n");
    }
    /*devoluciones D=cargar_devoluciones();
    printf("se ha cargado el fichero Devoluciones.txt correctamente\n");*/
   
    //listar_prod_clientes(1, P, Prod_P);
    return 0;
}