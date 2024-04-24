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


//FUNCIONES PEDIDOS

//Cabecera: pedidos cargar_pedidos()
//Precondición: el fichero debe existir y la estructura de cada pedido
//Postcondición: guarda en un vector de tipo pedido cada pedido que hay en el fichero.
pedidos cargar_pedidos();

//Cabecera guardar_pedido(pedidos p, int pos)
//Precondición: estructura pedidos cargada con los datos del ultimo pedido realizado
//Postcondicion: se guarda en el fichero la estructura pedidos
void guardar_pedido(pedidos);

//Cabecera: void crear_pedido(int id_cliente, pedidos p)
//Precondicion: estrcutura pedidos cargada con datos del fichero Pedidos.txt y el id del cliente que ha realizado pedido, lo sabemos cuando ha iniciado sesión en la aplicación
//Postcondicion: se crea un nuevo pedido realizado por un cliente y se guarda en la estructura pedidos, ademas de escribirlo en el fichero Pedidos.txt
pedidos crear_pedido(pedidos, int);

//Cabecera: comprobar_descuento(char[], int)
//Precondicion: se le pasa un codigo de descuento a través de una cadena y la id del usuario
//Postcondicion: devuelve 1 si el codigo de descuento es incorrecto o devuelve 0 si es correcto
int comprobar_descuento(char[], int);

//Cabecera: listapedidos_cliente(prod_pedidos, pedidos, int)
//Precondicion: estructura prod_pedidos y pedidos cargada y se le pasa la id del cliente
//Postcondicion: muestra todos los pedidos del cliente indicado
void listapedidos_cliente(prod_pedidos, pedidos, int);

//Cabecera: eliminar_pedidos(prod_pedidos, pedidos, int)
//Precondicion: estructuras prod_pedidos, pedidos cargadas y se le pasa la posicion del pedido se desea eliminar
//Postcondicion: elimina el pedido 
void eliminar_pedidos(prod_pedidos, pedidos, int);

//Cabecera: menu_listadoped_estado()
//Precondicion
//Postcondicion: muestra los productos pedidos segun un estado seleccionado
void menu_listadoped_estado();

//Cabecera: listadoped_estado(prod_pedidos,char[]
//Precondicion: la estructura prod_pedidos tiene que estar cargada y se le pasa el estado 
//Postcondicion: muestra la lista de los productos pedidos que tienen el estado indicado
void listadoped_estado(prod_pedidos , char[]);

//Cabecera: listar_pedidos(pedidos)
//Precondicion: la estructura pedidos tiene que estar cargada
//Postcondicion: muestra todos los pedidos que tiene guardado el sistema
void listar_pedidos(pedidos);

//Cabecera: modificar_pedido(pedidos)
//Precondicion: la estructura pedidos tiene que estar cargada
//Postcondicion: modifica un pedido que ha seleccionado el cliente
pedidos modificar_pedido(pedidos);

//FUNCIONES PRODUCTOS PEDIDOS

//Cabecera: eliminar_productos_ped(prod_pedidos, int)
//Precondicion: la estructura prod_pedidos tiene que estar cargada y se le pasa la poscion del pedido del que se quieren eliminar los productos
//Postcondicion: elimina los productos que pertenecen al pedido indicado
void eliminar_productos_ped(prod_pedidos, int);

//Cabecera: prod_pedidos cargar_prod_pedidos()
//Precondicion:
//Postcondicion: carga en la estructura prod_pedidos los datos del fichero ProductosPedidos.txt
prod_pedidos cargar_prod_pedidos();


//Cabecera: guardar_producto_pedido()
//Precondicion:
//Postcondicion: rellena la estructura con un nuevo producto pedido y lo escribe en el fichero
void guardar_productos_pedidos(prod_pedidos );

//Cabecera: crear_producto_pedido(pedidos, int, int, prod_pedidos, int)
//Precondicion: se le pasa la estructura pedidos y prod_pedidos cargada y la id del producto, pedido y el numero de unidades
//Postcondicion: crea un nuevo producto pedido en la estructura
void crear_producto_pedido(pedidos, int, int, prod_pedidos, int);

//Cabecera: fecha_entrega(fecha, int)
//Precondicion: se le pasa una estructura fecha y los dias de entrega que tiene asignados el producto
//Postcondicion: devuelve la fecha de entrega de un producto segun los dias de entrega que tenga asignados
fecha fecha_entrega(fecha, int);

//FUNCIONES DEVOLUCIONES

//Cabecera: devoluciones cargar_devoluciones()
//Precondicion:
//Postcondicion: carga en la estructura devoluciones los datos que hay en el fichero Devoluciones.txt
devoluciones cargar_devoluciones();

//Cabecera: guardar_devoluciones(devoluciones)
//Precondicion: se le pasa la estructura devoluciones cargada
//Postcondicion: guarda en el fichero Devoluciones.txt la estructura devoluciones cargada
void guardar_devoluciones(devoluciones);

//Cabecera: devoluciones crear_devolucion(devoluciones, int, int)
//Precondicion: se le pasa la estructura devoluciones cargada, la id del pedido y la id del producto
//Postcondicion: crea una nueva devolucion en la estructura devoluciones con la id del pedido y del producto indicadas
devoluciones crear_devolucion(devoluciones, int, int);

//Cabecera: devoluciones nueva_devolucion(int, devoluciones)
//Precondicion: se le pasa la estructura devoluciones cargada y la id del cliente que quiere realizar la devolucion
//Postcondicion: el cliente selecciona un pedido para realizar la devolucion y se crea la devolucion de ese pedido en la estructura devoluciones
devoluciones nueva_devolucion_prod(int, devoluciones);

//Cabecera: void listar_devoluciones(devoluciones)
//Precondicion: se le pasa la estructura devoluciones cargada
//Postcondicion: muestra todas las devoluciones guardadas en el sistema
void listar_devoluciones(devoluciones);

//Cabecera: int buscar_devolucion(devoluciones)
//Precondicion: se le pasa la estructura devoluciones cargada
//Postcondicion: devuelve la posicion de la devolucion que el administrador desea modificar
int buscar_devolucion(devoluciones);

//Cabecera: void eliminar_devolucion(int, devoluciones)
//Precondicion: se le pasa la posicion de la devolucion a eliminar y la estructura devoluciones cargada
//Postcondicion: se elimina la devolucion correspondiente a la posicion indicada
void eliminar_devolucion(int, devoluciones);

//Cabecera: devoluciones modificar_devolucion(devoluciones, int)
//Precondicion: 
devoluciones modificar_devolucion(devoluciones, int);
void listar_dev_cliente(int, devoluciones);
devoluciones aceptar_dev(devoluciones);
void listar_dev_pendientes(devoluciones);


#endif