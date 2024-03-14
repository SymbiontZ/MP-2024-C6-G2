#include "./useradmin.h"
#include <stdio.h>
#include <stdlib.h> 

clients cargar_clientes();
void excepcion (int, char[]);

clients cargar_clientes(){
    char filename[] = "../data/Clientes.txt";   //Nombre fichero
    int n_clients = 0;                          //Numero de clientes registrados
    int i = 0;                          
    char cad_linea[170];                        //Caracteres maximos que puede ocupar una linea en fichero
    int campo_cliente;                          //Entero que verifica no. campos de la estructura cliente.       

    
    FILE *f_clients;

    f_clients = fopen(filename, "r");
    if(f_clients == NULL){                                      //Excepcion si no encuentra fichero
        perror("No se pudo abrir el archivo de clientes.\n");
        getchar();
        exit(EXIT_FAILURE);
    }
    
    while(fgets(cad_linea, sizeof(cad_linea), f_clients)){
        n_clients++;
        //printf("%s", cad_linea);
    }
    rewind(f_clients);                                          //Necesario para volver a leer el fichero
    
    clients C; 
                         
    C.n_clients = n_clients;
    C.clients = malloc(C.n_clients * sizeof(client));


    //BUCLE PARA RELLENAR LA ESTRUCTURA DE CLIENTES//
    while(fgets(cad_linea, sizeof(cad_linea), f_clients) && i < n_clients){
        campo_cliente = sscanf(cad_linea, "%d-%19[^-]-%49[^-]-%19[^-]-%19[^-]-%29[^-]-%14[^-]-%d",
            &C.clients[i].Id_cliente,
            C.clients[i].Nom_cliente,
            C.clients[i].Dir_cliente,
            C.clients[i].Localidad,
            C.clients[i].Provincia,
            C.clients[i].email,
            C.clients[i].Contrasena,
            &C.clients[i].Cartera);

        if(campo_cliente != 8){                                     //Excepcion si fallo en dato de cliente
            printf("Se produjo un error con datos de un usario. ID_cliente: %d\n", i+1);
            getchar();
            exit(EXIT_FAILURE);
        }
        i++;
    }
    

    fclose(f_clients);
    return C;
}

clients agregar_cliente(){
    
}