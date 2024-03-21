#include "./complementos.h"
#include "./useradmin.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

clients cargar_clientes();
clients agregar_cliente(clients );
void guardar_clientes(clients );
void gestionar_cliente(clients, int);
clients cliente_nom(clients , int );
clients cliente_contr(clients C, int id, int mod);

clients cargar_clientes(){
    char filename[] = "../data/Clientes.txt";   
    int n_clients = 0;                          //Numero de clientes registrados
    int i = 0;                          
    char cad_linea[170];                        //Caracteres maximos que puede ocupar una linea en fichero
    int campo_cliente;                          //Entero que verifica no. campos de la estructura cliente.       

    FILE *f_clients;
    f_clients = fopen(filename, "r");
    if(f_clients == NULL){  
        f_clients = fopen(filename, "w+");                                    //Excepcion si no encuentra fichero
        perror("No se pudo abrir el archivo de clientes. Se ha creado un nuevo archivo.\n");
        getchar();
    }
    
    while(fgets(cad_linea, sizeof(cad_linea), f_clients)){      //Contador de clientes en el programa a partir de fichero 
        n_clients++;
    }
    rewind(f_clients);                                          //Necesario para volver a leer el fichero
    
    clients C;            
    C.n_clients = n_clients;
    C.clients = malloc(C.n_clients * sizeof(client));           //Asignacion de memoria dinamica "C.clients[n_clients]"


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

clients agregar_cliente(clients C){
    int new_id = C.n_clients+1;
    int new_pos = new_id -1;

    C.clients = realloc(C.clients, new_id*sizeof(client));
    if (C.clients == NULL){
        printf("No se pudo asignar la estructura de clientes");
        getchar();
        exit(EXIT_FAILURE);
    }

    C.clients[new_pos].Id_cliente = new_id;
    fflush(stdin);
    fgets(C.clients[new_pos].Nom_cliente, 20, stdin);
    printf("%s", C.clients[new_pos].Nom_cliente);
    printf("hola");

    strcpy(C.clients[new_pos].Dir_cliente, "Calle Roble 73");
    strcpy(C.clients[new_pos].Localidad, "Chiclana");
    strcpy(C.clients[new_pos].Provincia, "Cádiz");
    strcpy(C.clients[new_pos].email, "lgl512exam@uca.es");
    strcpy(C.clients[new_pos].Contrasena, "contra12345");
    C.clients[new_pos].Cartera = 1000;

    
    C.n_clients = new_id;
    guardar_clientes(C);
    return C;
}

void guardar_clientes(clients C){
    FILE* f_clients;
    char filename[] = "../data/Clientes.txt";
    int i;
    f_clients = fopen(filename,"w");
    //PROCESO DE GUARDADO DE DATOS DE CADA USUARIO EN FICHERO//
    for (i = 0; i < C.n_clients; i++){                          
        fprintf(f_clients, "%07d-%s-%s-%s-%s-%s-%s-%d\n",
                C.clients[i].Id_cliente,
                C.clients[i].Nom_cliente,
                C.clients[i].Dir_cliente,
                C.clients[i].Localidad,
                C.clients[i].Provincia,
                C.clients[i].email,
                C.clients[i].Contrasena,
                C.clients[i].Cartera);
    }
    fclose(f_clients);
}

void gestionar_cliente(clients C, int id){
    //MOSTRAR INFORMACION//
    clear();
    printf("\nNombre: %s\n", C.clients[id].Nom_cliente);
    printf("Direccion: %s, %s, %s\n", C.clients[id].Dir_cliente, C.clients[id].Localidad, C.clients[id].Provincia);
    printf("Email: %s\n", C.clients[id].email);
    printf("Cartera: %d\n", C.clients[id].Cartera);

    //CAMBIO DE INFORMACION//
    int opt;
    printf("\n### QUE DESEA MODIFICAR: ###\n");
    printf("1. Nombre\n2. Direccion\n3. Email\n4. Contrasena\n5. Cartera\n0. Salir\n############################\n");

    
    scanf("%d", &opt);
    while(opt < 0 || opt > 5) {
        printf("Opcion invalida. Por favor, seleccione una opcion valida: ");
        fflush(stdin);
        scanf("%d", &opt);
    }
    switch (opt)
    {
    case 1:
        C = cliente_nom(C, id);
        break;
    case 4:
        C = cliente_contr(C, id, 1);
    
    default:
        break;
    }
    
    guardar_clientes(C);
}

clients cliente_nom(clients C, int id){
    printf("Ingrese el nombre:\n");
    fgets(C.clients[id].Nom_cliente, 20, stdin);
    printf("%s",C.clients[id].Nom_cliente);
    return C;
}

clients cliente_contr(clients C, int id, int mod){
    char cad_contr[21];
    if(mod == 1){
        printf("%s", C.clients[id].Contrasena);
        printf("Para poder cambiar la contrasena es necesario verificar la anterior: ");
        fflush(stdin);
        fgets(cad_contr, 21, stdin);

        int len = strlen(cad_contr);
        if (len > 0 && cad_contr[len - 1] == '\n') {
            cad_contr[len - 1] = '\0'; // Reemplazar el carácter de salto de linea con el carácter nulo
        }
        
        if(strcmp(cad_contr, C.clients[id].Contrasena) == 0)
            printf("Iguales\n");
        else
            printf("No iguales\n");
        
    }

}