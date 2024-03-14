#include "./useradmin.h"
#include <stdio.h>
#include <stdlib.h> 

clients cargar_clientes();
void excepcion (int, char[]);

clients cargar_clientes(){
    char filename[] = "../data/Clientes.txt";
    int n_clients = 0,i;                          //Numero de clientes registrados
    char cad_linea[170]; 
    int campo_cliente;                      //Caracteres maximos que puede ocupar una linea en fichero

    
    FILE *f_clients;

    f_clients = fopen(filename, "r");
    if(f_clients == NULL){
        perror("No se pudo abrir el archivo de clientes.\n");
        getchar();
        exit(EXIT_FAILURE);
    }
    
    while(fgets(cad_linea, sizeof(cad_linea), f_clients)){
        n_clients++;
        printf("%s", cad_linea);
    }
    rewind(f_clients);                                          //Necesario para volver a leer el fichero
    
    clients C; 
                         
    C.n_clients = n_clients;
    C.clients = malloc(n_clients * sizeof(client));
    
    //BUCLE PARA RELLENAR LA ESTRUCTURA DE CLIENTES//
    for (i = 0; i < n_clients; i++) {
        while(fgets(cad_linea, sizeof(cad_linea), f_clients)){
            campo_cliente = sscanf(cad_linea, "%d");
        }
        
    }
    printf("%s", C.clients[0].email);

    fclose(f_clients);
    return C;
}



