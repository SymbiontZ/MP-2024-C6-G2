#ifndef USERADMIN_H_
#define USERADMIN_H_

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "./complementos.h"
#include "empresas.h"

#define MAX_EMAIL 31            //Longitud de email + 1(terminador)
#define MAX_PSW 16              //Longitud de contrasena + 1(terminador)
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

    //PRECONDICION: Se le pasa una estructura tipo clients ya iniciada.
    //POSCONDICION: Almacena un nuevo cliente en la estructura y la guarda en el fichero.
    clients agregar_cliente(clients );

    //PRECONDICION: Se le pasa una estructura tipo clients.
    //POSCONDICION: Vuelca datos en el fichero pero no devuelve nada.
    void guardar_clientes(clients );

    //PRECONDICION: Se le pasa la estructura tipo clients cargada y la posicion del cliente en la estructura
    //POSCONDICION: Devuelve la estructura tipo clients actualizada con los nuevos cambios
    clients gestionar_cliente(clients, int);


    //### INTERFACES DEL USUARIO ###//

    //PRECONDICION
    void menu_cliente(clients ,int );

    //PRECONDICION: Se le pasa la posicion del cliente en la estructura y la misma estructura tipo clients
    //POSCONDICION: Ninguna  
    void inicsesion_cliente(clients ,int );

    //GESTION DATOS ESPECIFICOS USUARIOS//
    clients cliente_nom(clients , int );
    clients cliente_contr(clients , int , int );
    clients cliente_dir(clients , int ,int );
    clients cliente_email(clients , int , int );
    clients cliente_cart(clients , int , int );


///------------------------------- USUARIOS -------------------------------///
    void inicsesion_admin(admin_prov_vect, int);
    void menuadmin(admin_prov_vect , int );

#endif 