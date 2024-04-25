#ifndef CLIENTES_H_
#define CLIENTES_H_

#include "complementos.h"
#include "empresas.h"
#include "Productos.h"
#include "pedidos.h"
#include "Descuentos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <windows.h>

#define MAX_EMAIL 31            //Longitud de email + 1(terminador)
#define MAX_PSW 16              //Longitud de contrasena + 1(terminador)
#define MAX_NOM 21              //Longitud de nombre + 1(terminador)
#define MAX_LOC 21              //Longitud de localidad + 1(terminador)

//ESTRUCTURA DE INFORMACION DE UN CLIENTE
typedef struct
{
    int Id_cliente;
    char Nom_cliente[21];
    char Dir_cliente[51];
    char Localidad[21];
    char Provincia[21];
    char email[31];             //Usado para iniciar sesion
    char Contrasena[16];
    int Cartera;

}client;

//ESTRUCTURA VECTOR DE CLIENTE Y NUMERO DE CLIENTES(TAM VECTOR)
typedef struct
{ 
    client *clients;
    int n_clients;

}clients;

///------------------------------- USUARIOS -------------------------------///

    //### GESTION DE USUARIOS ###//

    //PRECONDICION: Ninguna
    //POSCONDICION: Inicializa una estructura tipo clients con datos almacenados de un fichero.
    clients cargar_clientes();          

    //PRECONDICION: Se le pasa una estructura tipo clients.
    //POSCONDICION: Vuelca datos en el fichero pero no devuelve nada.
    void guardar_clientes(clients );

    //PRECONDICION:
    //POSCONDICION:
    int busqueda_cliente();

    //PRECONDICION:
    //POSCONDICION:
    int busqueda_clientetipo(clients , int ,int );

    //PRECONDICION: Se le pasa la estructura tipo clients cargada y la posicion del cliente en la estructura
    //POSCONDICION: Devuelve la estructura tipo clients actualizada con los nuevos cambios
    clients gestionar_cliente(clients, int, int);

    //PRECONDICION: Se le pasa una estructura tipo clients ya iniciada.
    //POSCONDICION: Almacena un nuevo cliente en la estructura y la guarda en el fichero.
    clients agregar_cliente(clients );

    //PRECONDICION:
    //POSCONDICION:
    clients eliminar_cliente(clients , int );

    
    //### INTERFACES DEL USUARIO ###//

    //PRECONDICION: Se le pasa la posicion del cliente en la estructura y la misma estructura tipo clients
    //POSCONDICION: Ninguna  
    void inicsesion_cliente(clients ,int );

    //PRECONDICION: Se le pasa la posicion del cliente en la estructura y la estructura tipo clients cargada
    //POSCONDICION: Ninguna
    void menucliente(clients ,int );

    //PRECONDICION:Ninguna
    //POSCONDICION:Ninguna
    //FUNCION:Acceder a listas de productos segun el nombre o la categoria
    void menucliente_prod();

    //PRECONDICION:Le paso la id del cliente
    //POSCONDICION:Accedemos a diversas funciones para 
    void menucliente_ped(int );

    //PRECONDICION:
    //POSCONDICION:
    void menucliente_dev(int );

    //GESTION DATOS ESPECIFICOS USUARIOS//
    clients cliente_nom(clients , int );
    clients cliente_contr(clients , int , int );
    clients cliente_dir(clients , int ,int );
    clients cliente_email(clients , int , int );
    clients cliente_cart(clients , int , int );

    void mostrar_clientes(clients );




#endif  


/*
CAMBIOS PENDIENTES

> cambiar interfaces
*/