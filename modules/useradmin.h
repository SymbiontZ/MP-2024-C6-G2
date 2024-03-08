#ifndef USERADMIN_H_
#define USERADMIN_H_

#define N 9999999
typedef struct
{
    int Id_cliente;
    char Nom_cliente[20];
    char Dir_cliente[50];
    char Localidad[20];
    char Provincia[20];
    char email[30]; //USADO COMO USUARIO
    char Contrasena[15];
    int Cartera;

}client;
typedef struct
{ 
    client *client;
    int n_clients;

}clients;


client cargar_clientes();


#endif 