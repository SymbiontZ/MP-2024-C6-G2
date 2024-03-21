#ifndef USERADMIN_H_
#define USERADMIN_H_

#define MAX_NAME 20
typedef struct
{
    int Id_cliente;
    char Nom_cliente[21];
    char Dir_cliente[51];
    char Localidad[21];
    char Provincia[21];
    char email[31]; //USADO COMO USUARIO
    char Contrasena[16];
    int Cartera;

}client;
typedef struct
{ 
    client *clients;
    int n_clients;

}clients;

clients cargar_clientes();
clients agregar_cliente(clients );
void guardar_clientes(clients );
void gestionar_cliente(clients, int);

#endif 