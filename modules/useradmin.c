#include "./useradmin.h"
#include <stdio.h>
#include <stdlib.h> 

void cargar_clientes();
void excepcion (int, char[]);

void cargar_clientes(){
    char filename[] = "../data/Clientes.txt";
    FILE *f_clients;
    int n_clients = 0;                          //Numero de clientes registrados
    char max_linea[170];                        //Caracteres maximos que puede ocupar una linea en fichero
    

    f_clients = fopen(filename, "r");

    if(f_clients == NULL)
    {
        perror("No se pudo abrir el archivo de clientes.\n");
        getchar();
        exit(EXIT_FAILURE);
    }
    while(fgets(max_linea, sizeof(max_linea), f_clients))
        n_clients++;

    printf("%d", n_clients);

    fclose(f_clients);

}




