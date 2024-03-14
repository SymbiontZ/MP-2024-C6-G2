#include "./useradmin.h"
#include <stdio.h>
#include <stdlib.h> 

clients cargar_clientes();
void excepcion (int, char[]);

clients cargar_clientes(){
    char filename[] = "../data/Clientes.txt";
    int n_clients = 0;                          //Numero de clientes registrados
    char cad_linea[170];                        //Caracteres maximos que puede ocupar una linea en fichero

    clients C;
    FILE *f_clients;

    f_clients = fopen(filename, "r");

    if(f_clients == NULL){
        perror("No se pudo abrir el archivo de clientes.\n");
        getchar();
        exit(EXIT_FAILURE);
    }
    while(fgets(cad_linea, sizeof(cad_linea), f_clients)){
        //int campos = sscanf(cad_linea,"%[^-]/%[^-]/%s" );
        n_clients++;
    }
    C.n_clients = n_clients;
    

    fclose(f_clients);

    return C;

} 



