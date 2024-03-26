#include "./complementos.h"
#include "./useradmin.h"


clients cargar_clientes(){
    char filename[] = "../data/Clientes.txt";   
    int n_clients = 0;                          //Numero de clientes registrados
    int i = 0;                          
    char cad_linea[170];                        //Caracteres maximos que puede ocupar una linea en fichero
    int campo_cliente;                          //Entero que verifica no. campos de la estructura cliente.       

    FILE *f_clients;
    f_clients = fopen(filename, "r");
    if(f_clients == NULL){  
        f_clients = fopen(filename, "w");                                 //Excepcion si no encuentra fichero
        fclose(f_clients);
        printf("No se pudo abrir el archivo de clientes. Se ha creado un nuevo archivo.\n");
        getchar();
    }
    
    while(fgets(cad_linea, sizeof(cad_linea), f_clients)){      //Contador de clientes en el programa a partir de fichero 
        n_clients++;
    }
    rewind(f_clients);                                          //Necesario para volver a leer el fichero
    
    clients C;            
    C.n_clients = n_clients;
    C.clients = malloc(C.n_clients * sizeof(client));           //Asignacion de memoria dinamica "C.clients[n_clients]"
    
    if(C.clients == NULL){
        printf("No se ha podido asignar memoria a la estructura clientes");
        getchar();
        exit(EXIT_FAILURE);
    }



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
    int new_id = C.n_clients+1;         //IDENTIFICADOR DEL NUEVO CLIENTE
    int new_pos = new_id -1;            //POSICION DEL CLIENTE EN LA ESTRUCTURA

    C.clients = realloc(C.clients, new_id*sizeof(client));
    if (C.clients == NULL){
        printf("No se pudo asignar la estructura de clientes");
        getchar();
        exit(EXIT_FAILURE);
    }

    C.clients[new_pos].Id_cliente = new_id;
    C = cliente_nom(C, new_pos);
    C = cliente_contr(C, new_pos, 0);
    C = cliente_dir(C, new_pos , 0);
    C = cliente_email(C, new_pos, 0);
    C = cliente_cart(C, new_pos, 0);

    C.n_clients = new_id;

    guardar_clientes(C);

    printf("Se ha creado el cliente %s correctamente", C.clients[new_pos].Nom_cliente);
    getchar();

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
    printf("\n**Estructura guardada con %d clientes\n", C.n_clients);
}

void gestionar_cliente(clients C, int id){
    //CAMBIO DE INFORMACION//
    int opt = -1;

    while (opt < 0 || opt > 5){
        //MOSTRAR INFORMACION//
        clear();
        printf("\nNombre: %s\n", C.clients[id].Nom_cliente);
        printf("Direccion: %s, %s, %s\n", C.clients[id].Dir_cliente, C.clients[id].Localidad, C.clients[id].Provincia);
        printf("Email: %s\n", C.clients[id].email);
        printf("Cartera: %d\n", C.clients[id].Cartera);

        printf("\n### QUE DESEA MODIFICAR: ###\n");
        printf("1. Nombre\n2. Direccion\n3. Email\n4. Contrasena\n5. Cartera\n0. Salir\n############################\n");
        scanf("%d", &opt);
        switch (opt){
            case 1:
                C = cliente_nom(C, id);
                opt = -1;
                break;
            case 2:
                C = cliente_dir(C, id, 1);
                opt = -1;
                break;
            case 3:
                C = cliente_email(C, id, 1);
                opt = -1;
                break;

            case 4:
                C = cliente_contr(C, id, 1);
                opt = -1;
                break;
            case 5:
                C = cliente_cart(C, id, 1);
                opt = -1;
                break;
            case 0:         //CASO DE SALIDA
                break;
            default:
                printf("Seleccione una opcion valida: ");
                break;
        }
        guardar_clientes(C);
    }
    printf("Salio correctamente. %d\n", opt);
}

clients cliente_nom(clients C, int id){
    char cad_nom[21];
    int len;

    printf("Ingrese el nombre: ");
    
    fflush(stdin);
    fgets(cad_nom, sizeof(cad_nom), stdin);
    len = strlen(cad_nom);
        if (len > 0 && cad_nom[len - 1] == '\n') { cad_nom[len - 1] = '\0'; }
    strcpy(C.clients[id].Nom_cliente, cad_nom);

    return C;
}

clients cliente_contr(clients C, int id, int mod){
    char cad_contr[21], verif_contr[21];
    int len;
    if(mod == 1){                               //SE DESEA CAMBIAR UNA CONTRASENA EXISTENTE
        printf("%s\n", C.clients[id].Contrasena);
        printf("Para poder cambiar la contrasena es necesario verificar la anterior: ");

        fflush(stdin);
        fgets(cad_contr, 21, stdin);

        len = strlen(cad_contr);
        if (len > 0 && cad_contr[len - 1] == '\n') {
            cad_contr[len - 1] = '\0'; // Reemplazar el carácter de salto de linea con el carácter nulo
        }
        
        while(strcmp(cad_contr, C.clients[id].Contrasena) != 0){
            printf("Por favor vuelva a intentarlo. Si desea salir escriba [exit]: ");
            fflush(stdin);
            fgets(cad_contr, 21, stdin);

            len = strlen(cad_contr);
            if (len > 0 && cad_contr[len - 1] == '\n') {
                cad_contr[len - 1] = '\0';
            }

            if(strcmp(cad_contr, "exit") == 0)  //Salir del bucle
                return C;
        }


    }
    printf("Escriba la contrasena a tener: ");

    fflush(stdin);
    fgets(cad_contr, 21, stdin);
    len = strlen(cad_contr);
    if (len > 0 && cad_contr[len - 1] == '\n') { cad_contr[len - 1] = '\0'; }


    while (strcmp(cad_contr, verif_contr) != 0){
        printf("Vuelva a introducir la nueva contrasena: ");

        fflush(stdin);
        fgets(verif_contr, 21, stdin);
        len = strlen(verif_contr);
        if (len > 0 && verif_contr[len - 1] == '\n') { verif_contr[len - 1] = '\0'; }
    }
    strcpy(C.clients[id].Contrasena, cad_contr);

    return C;
}

clients cliente_dir(clients C, int id, int mod){
    char cad_dir[51], cad_lugar[21];
    int len;
    
    if (mod == 1)
        printf("\nDireccion actual: %s\n", C.clients[id].Dir_cliente);
    printf("Ingrese la direccion del hogar (max 50 caracteres): ");
    
    fflush(stdin);
    fgets(cad_dir, sizeof(cad_dir), stdin);
    len = strlen(cad_dir);
        if (len > 0 && cad_dir[len - 1] == '\n') { cad_dir[len - 1] = '\0'; }
    strcpy(C.clients[id].Dir_cliente, cad_dir);

    if (mod == 1)
        printf("\nLocalidad actual: %s\n", C.clients[id].Localidad);
    printf("Introduzca la localidad: ");
    fflush(stdin);
    fgets(cad_lugar, sizeof(cad_lugar), stdin);
    len = strlen(cad_lugar);
        if (len > 0 && cad_lugar[len - 1] == '\n') { cad_lugar[len - 1] = '\0'; }
    strcpy(C.clients[id].Localidad, cad_lugar);

    if (mod == 1)
        printf("\nProvincia actual: %s\n", C.clients[id].Provincia);
    printf("Introduzca la provincia: ");
    fflush(stdin);
    fgets(cad_lugar, sizeof(cad_lugar), stdin);
    len = strlen(cad_lugar);
        if (len > 0 && cad_lugar[len - 1] == '\n') { cad_lugar[len - 1] = '\0'; }
    strcpy(C.clients[id].Provincia, cad_lugar);

    return C;
}

clients cliente_email(clients C, int id, int mod){
    char cad_email[31];
    int len;

    if(mod == 1)
        printf("\nEmail actual: %s\n", C.clients[id].email);
    printf("Ingrese el email: ");
    
    fflush(stdin);
    fgets(cad_email, sizeof(cad_email), stdin);
    len = strlen(cad_email);
        if (len > 0 && cad_email[len - 1] == '\n') { cad_email[len - 1] = '\0'; }
    strcpy(C.clients[id].email, cad_email);

    return C;
}

clients cliente_cart(clients C, int id, int mod){
    int cartera = 0;
    if(mod == 1){
        printf("Saldo de la cartera actual: %d\n", C.clients[id].Cartera);
    }
    printf("Introduzca el saldo disponible: ");
    scanf("%d", &cartera);

    while(cartera <= 0){
        printf("Saldo no valido, introduzcalo de nuevo: ");
        scanf("%d", &cartera);
    }
    C.clients[id].Cartera = cartera;

    return C;
}

void menu_cliente(clients C,int id){
    int opt = -1;    //AUXILIAR PARA MANEJO DE OPCIONES EN EL SWITCH

    while(opt<1 || opt>5){
        clear();
        titulo();
        
        printf("+Usuario: %s\n", C.clients[id].Nom_cliente);
        printf("1. Perfil\n");
        printf("2. Productos\n");
        printf("3. Descuentos\n");
        printf("4. Pedidos\n");
        printf("5. Devoluciones\n");
        printf("0. Salir del sistema\n");

        scanf("%d", &opt);

        switch (opt){
        case 1:
            gestionar_cliente(C ,id);
            opt = -1;
            break;
        case 2:
            opt = -1;
            break;
        case 3:
            opt = -1;
            break;
        case 4:
            opt = -1;
            break;
        case 5:
            opt = -1;
            break;
        case 0:
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    }
    
}

