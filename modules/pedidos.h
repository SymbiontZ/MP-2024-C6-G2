#ifndef PEDIDOS_H_
#define PEDIDOS_H_

#include "complementos.h"
#include "empresas.h"
#include "Productos.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

//ESTRUCTURAS
//Estructura pedidos.txt
typedef struct{
    int id_pedido;
    fecha f_pedido;
    int id_cliente;
    char lugar[11];
    char id_locker[11];
    char id_cod[11];   
}pedido;

typedef struct{
    pedido *pedidos;
    int lon;
}pedidos;

//Estructura ProductosPedidos.txt
typedef struct{
    int id_pedido;
    int id_prod;
    int num_unid;
    fecha f_entrega;
    int importe;
    char estado[21];
    int id_transp;
    char id_locker[11];
    char cod_locker[11];
    fecha f_devolucion;
}prod_pedido;

typedef struct{
    prod_pedido *prod_pedidos;
    int lon;
}prod_pedidos;


typedef struct{
    int id_pedido;
    int id_prod;
    fecha f_devol;
    char motivo[51];
    char estado[11];
    fecha f_aceptacion;
    fecha f_caducidad;
}devolucion;

typedef struct{
    devolucion *devoluciones;
    int lon;
}devoluciones;


//FUNCIONES
pedidos cargar_pedidos();
prod_pedidos cargar_prod_pedidos();
devoluciones cargar_devoluciones();
int crear_pedido(pedidos, int);
void guardar_pedido(pedidos);
void guardar_productos_pedidos(prod_pedidos );
void crear_producto_pedido(pedidos, int, int, prod_pedidos, int);
void guardar_devoluciones(devoluciones);
void crear_devolucion(devoluciones, pedidos, prod_pedidos);
void listapedidos_cliente(prod_pedidos, pedidos, int);
fecha fecha_entrega(fecha, int);

#endif