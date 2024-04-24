#include "useradmin.h"

/*** MANEJO CLIENTES ESTRUCTURA-FICHERO ***/

clients cargar_clientes(){
    char filename[] = "../data/Clientes.txt";
    char default_user[] = "0000000-userdefault-defaultdir-defaultloc-defaultprov-defaultemail-defpsw-0";    //Usuario por defecto
    int n_clients = 0;                          //Numero de clientes registrados
    int i = 0;                          
    char cad_linea[170];                        //Caracteres maximos que puede ocupar una linea en fichero
    int campo_cliente;                          //Entero que verifica no. campos de la estructura cliente.       

    FILE *f_clients;
    f_clients = fopen(filename, "a+");

    if(f_clients == NULL){                          //Excepcion si no encuentra fichero
        printf("No se pudo abrir el archivo de clientes. Se ha creado un nuevo archivo.\n");
        Sleep(2000);
    }

    rewind(f_clients);

    if(fgetc(f_clients) == EOF){                    //Si fichero vacio
        f_clients = fopen(filename, "w");
        fprintf(f_clients, default_user);           //Añadimos usuario predeterminado
        fclose(f_clients);
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
        campo_cliente = sscanf(cad_linea, "%d-%22[^-]-%52[^-]-%22[^-]-%22[^-]-%32[^-]-%17[^-]-%d",
            &C.clients[i].Id_cliente,
            C.clients[i].Nom_cliente,
            C.clients[i].Dir_cliente,
            C.clients[i].Localidad,
            C.clients[i].Provincia,
            C.clients[i].email,
            C.clients[i].Contrasena,
            &C.clients[i].Cartera);

        if(campo_cliente != 8){                                     //Excepcion si fallo en dato de cliente
            printf("Se produjo un error con datos de un usario. ID_cliente: %d\n", i);
            getchar();
            exit(EXIT_FAILURE);
        }
        i++;
    }

    //printf("\nCarga de clientes completada.\nClientes registrados: %d \n", C.n_clients-1);
    //Sleep(1500);

    fclose(f_clients);
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
    //printf("\n**Estructura guardada con %d clientes\n", C.n_clients -1);
}


/*** MENU CLIENTES ***/

void inicsesion_cliente(clients C, int pos){
    char psw_verif[MAX_PSW];            //Variable para almacenar la contrasena introducida por teclado

    printf("Ingrese la contrasena del correo: ", C.clients[pos].email);

    do{
        fflush(stdin);
        fgets(psw_verif, MAX_PSW, stdin);
        terminador_cad(psw_verif);

        
        if(strcmp(psw_verif, "exit") == 0)
            exit(EXIT_SUCCESS);
        else if(strcmp(psw_verif, C.clients[pos].Contrasena) != 0)
            printf("Vuelva a intentarlo, si quiere salir escriba [exit]: ");

    } while (strcmp(psw_verif, C.clients[pos].Contrasena) != 0); 
    
    menucliente(C, pos);
}

void menucliente(clients C,int pos){
    int opt;    //AUXILIAR PARA MANEJO DE OPCIONES EN EL SWITCH

    do{
        clear();
        titulo();
        printf("+------------------------------+\n");
        printf("| Usuario: %-20s|\n", C.clients[pos].Nom_cliente);
        printf("+------------------------------+\n");
        printf("| <1> Perfil                   |\n");
        printf("| <2> Productos                |\n");
        printf("| <3> Descuentos               |\n");
        printf("| <4> Pedidos                  |\n");
        printf("| <5> Devoluciones             |\n");
        printf("| <0> Salir del sistema        |\n");
        printf("+------------------------------+\n");

        scanf("%d", &opt);
        fflush(stdin);

        switch (opt){
        case 1:
            C = gestionar_cliente(C ,pos, 1);
            break;
        case 2:
            menucliente_prod();
            break;
        case 3:
            Consultar_desc_cliente(pos, 0);
            break;
        case 4:
            menucliente_ped(pos);
            break;
        case 5:
            menucliente_dev(pos);
            break;
        case 0:
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    }while(opt != 0);

}

void menucliente_prod(){
    int opt;
    do{
        clear();
        titulo();
        printf("+-------------------------------+\n");
        printf("| Como desea buscar el producto |\n");
        printf("+-------------------------------+\n");
        printf("| <1> Por nombre                |\n");
        printf("| <2> Por categoria             |\n");
        printf("| <0> Volver                    |\n");
        printf("+-------------------------------+\n");

        scanf("%d", &opt);
        fflush(stdin);

        switch (opt){
            case 1:
                buscador_prodnombre();
                break;
            case 2:
                buscador_prodidcateg();
                break;
            case 0:
                //CASO DE VUELTA AL MENU ANTERIOR
                break;
            default:
                break;
        }
    } while (opt != 0);
}

void menucliente_ped(int pos){
    pedidos p = cargar_pedidos();
    prod_pedidos prods_p = cargar_prod_pedidos();
    int opt;
    do{
        clear();
        titulo();
        printf("+-------------------------------+\n");
        printf("|        QUE DESEA HACER        |\n");
        printf("+-------------------------------+\n");
        printf("| <1> Realizar pedido           |\n");
        printf("| <2> Consultar mis productos   |\n");
        printf("| <3> Recoger pedido locker     |\n");
        printf("| <0> Volver                    |\n");
        printf("+-------------------------------+\n");

        scanf("%d", &opt);
        fflush(stdin);

        switch (opt){
            case 1:
                p = crear_pedido(p, pos);
                break;
            case 2:
                listapedidos_cliente(prods_p, p, pos);
                break;
            case 3:

                break;
            case 0:
                
                //CASO DE VUELTA AL MENU ANTERIOR
                break;
            default:
                break;
        }
        guardar_pedido(p);
    } while (opt != 0);

    free(prods_p.prod_pedidos);
    free(p.pedidos);
}

void menucliente_dev(int pos){
    devoluciones Dev = cargar_devoluciones();
    int opt;
    do{
        clear();
        titulo();
        printf("+---------------------------------------+\n");
        printf("|        QUE DESEA HACER                |\n");
        printf("+---------------------------------------+\n");
        printf("| <1> Realizar devolucion               |\n");
        printf("| <2> Seguimiento devoluciones          |\n");
        printf("| <3> Consultar devoluciones pendientes |\n");
        printf("| <0> Volver                            |\n");
        printf("+---------------------------------------+\n");

        opt = input_int();
        fflush(stdin);

        switch (opt){
        case 1:
            /* code */
            break;
        case 2:

            break;
        case 3:
            listar_devolpend(Dev,pos);
            break;    
        case 0:
            //CASO DE VUELTA AL MENU ANTERIOR
            break;
        default:
            break;
        }
        
    } while (opt != 0);
    guardar_devoluciones(Dev);

}

/*** MENU ADMIN ***/

void inicsesion_admin(admin_prov_vect adminprov, int pos){
    char psw_verif[MAX_PSW];            //Variable para almacenar la contrasena introducida por teclado

    printf("Ingrese la contrasena del correo: ", adminprov.usuarios[pos].email);

    do{
        fflush(stdin);
        fgets(psw_verif, MAX_PSW, stdin);
        terminador_cad(psw_verif);

        
        if(strcmp(psw_verif, "exit") == 0)
            exit(EXIT_SUCCESS);
        else if(strcmp(psw_verif, adminprov.usuarios[pos].Contrasena) != 0)
            printf("Vuelva a intentarlo, si quiere salir escriba [exit]: ");

    } while (strcmp(psw_verif, adminprov.usuarios[pos].Contrasena) != 0); 
        
    menuadmin(adminprov, pos);
}

void menuadmin(admin_prov_vect admin, int pos){
    int opt;    //AUXILIAR PARA MANEJO DE OPCIONES EN EL SWITCH

    do{
        clear();
        titulo();
        printf("+------------------------+\n");

        if (pos == 0)
            printf("| Superadministrador     |\n");
        else
            printf("| Administrador          |\n");

        printf("+------------------------+\n");
        printf("| <1> Perfil             |\n");
        printf("| <2> Clientes           |\n");
        printf("| <3> Proveedores        |\n");
        printf("| <4> Productos          |\n");
        printf("| <5> Categorias         |\n");
        printf("| <6> Pedidos            |\n");
        printf("| <7> Transportistas     |\n");
        printf("| <8> Descuentos         |\n");
        printf("| <9> Devoluciones       |\n");
        if (pos == 0)
            printf("| <10> Administradores   |\n");
        printf("| <0> Salir del sistema  |\n");
        printf("+------------------------+\n");

        opt = input_int();

        switch (opt){
        case 1:
            admin = gestionar_admin(admin, pos, 1);
            break;
        case 2:
            menuadmin_cliente();
            break;
        case 3:
            menuadmin_prov(admin);
            break;
        case 4:
            menuadmin_prod();
            break;
        case 5:
            menuadmin_cat();
            break;
        case 6:
            menuadmin_ped();
            break;
        case 7:
            menuadmin_transp();
            break;
        case 8:
            menuadmin_desc();
            break;
        case 9:
            menuadmin_devol();
            break;
        case 10:
            if(pos == 0)
                menuadmin_admin(admin);
            break;
        case 0:
            free(admin.usuarios);
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    }while(opt != 0);
}


void menuadmin_cliente(){
    clients C = cargar_clientes();
    int opt;
    char resp = '0';
    int pos;                            //Posicion del cliente al que se le realizan los cambios. 

    do{
        //MOSTRAR INFORMACION//
        clear();
        printf("+-----------------------------+\n");
        printf("| QUE DESEA REALIZAR:         |\n");
        printf("+-----------------------------+\n");
        printf("| <1> Listado de clientes     |\n");
        printf("| <2> Dar de alta cliente     |\n");
        printf("| <3> Dar de baja cliente     |\n");
        printf("| <4> Modificar cliente       |\n");
        printf("| <0> Volver                  |\n");
        printf("+-----------------------------+\n");
        opt = input_int();
        fflush(stdin);
        switch (opt){
            case 1:
                mostrar_clientes(C);
                break;
            case 2:
                printf("Seguro que quiere agregar un cliente [s/n]: ");
                resp = confirmacion();
                if(resp == 'S'|| resp == 's')
                    C = agregar_cliente(C);
                break;
            case 3:
                pos = busqueda_cliente();
                if (pos != -1)
                    C = eliminar_cliente(C, pos);
                break;
            case 4:
                pos = busqueda_cliente();
                if (pos != -1)
                    C = gestionar_cliente(C, pos, 0);
                break;
            case 0:        
                 //CASO DE SALIDA
                break;
            default:
                break;
        }
        guardar_clientes(C);
    }while(opt != 0);

    free(C.clients);
}

void menuadmin_admin(admin_prov_vect admin){
    int opt;
    char resp;
    int pos;                            //Posicion del admin al que se le realizan los cambios.

    do{
        clear();
        printf("+----------------------------+\n");
        printf("| QUE DESEA REALIZAR:        |\n");
        printf("+----------------------------+\n");
        printf("| <1> Mostrar listado admin  |\n");
        printf("| <2> Dar de alta admin      |\n");
        printf("| <3> Dar de baja admin      |\n");
        printf("| <4> Modificar admin        |\n");
        printf("| <0> Salir                  |\n");
        printf("+----------------------------+\n");

        opt = input_int();

        switch (opt){
            case 1:
                listar_admin(admin);
                break;
            case 2:
                printf("Seguro que quiere agregar un administrador [s/n]: ");
                resp = confirmacion();
                if(resp == 'S'|| resp == 's')
                    admin = agregar_admin(admin);
                break;
            case 3:
                pos = buscar_admin(admin);
                if (pos != -1)
                    admin = eliminar_admin(admin, pos);
                break;
            case 4:
                pos = buscar_admin(admin);
                if (pos != -1)
                    admin = gestionar_admin(admin, pos, 0);
                break;
            
            case 0:         //CASO DE SALIDA
                break;
            default:
                break;
        }
        guardar_adminprov(admin);
    }while (opt != 0);
    
}

void menuadmin_prov(admin_prov_vect admin){
    int opt;
    char resp;
    int pos;          //Posicion del proveedor al que se le realizan los cambios.

    do{
        clear();
        printf("+--------------------------------+\n");
        printf("| QUE DESEA REALIZAR:            |\n");
        printf("+--------------------------------+\n");
        printf("| <1> Mostrar listado proveedor  |\n");
        printf("| <2> Dar de alta proveedor      |\n");
        printf("| <3> Dar de baja proveedor      |\n");
        printf("| <4> Modificar proveedor        |\n");
        printf("| <0> Volver                     |\n");
        printf("+--------------------------------+\n");
 
        opt = input_int();
        fflush(stdin);
        switch (opt){
            case 1:
                listar_prov(admin);
                break;
            case 2:
                printf("Seguro que quiere agregar un proveedor [s/n]: ");
                resp = confirmacion();
                if(resp == 'S'|| resp == 's')
                    admin = alta_prov(admin);
                break;
            case 3:
                pos = buscar_prov(admin);
                if (pos != -1)
                    admin = baja_prov(admin, pos);
                break;
            case 4:
                pos = buscar_prov(admin);
                if (pos != -1)
                    admin = modificar_prov(admin, pos);
                break;
            
            case 0:         //CASO DE SALIDA
                break;
            default:
                break;
        }
        guardar_adminprov(admin);
    }while (opt != 0);
}

void menuadmin_prod(){
    produ_vect Produ = cargar_productos();
    int opt;
    char resp;
    int pos;          //Posicion del proveedor al que se le realizan los cambios.

    do{
        clear();
        printf("+--------------------------------+\n");
        printf("| QUE DESEA REALIZAR:            |\n");
        printf("+--------------------------------+\n");
        printf("| <1> Mostrar listado productos  |\n");
        printf("| <2> Dar de alta productos      |\n");
        printf("| <3> Dar de baja productos      |\n");
        printf("| <4> Modificar producto         |\n");
        printf("| <0> Volver                     |\n");
        printf("+--------------------------------+\n");
 
        scanf("%d", &opt);
        fflush(stdin);
        switch (opt){
            case 1:
                listar_productos(Produ);   
                break;
            case 2:
                printf("Seguro que quiere agregar un producto [s/n]: ");
                resp = confirmacion();
                if(resp == 'S'|| resp == 's')
                    agregar_productos(Produ);
                break;
            case 3:
                
                if (pos != -1)
                
                break;
            case 4:

                if (pos != -1)
                    
                break;
            
            case 0:         //CASO DE SALIDA
                break;
            default:
                break;
        }
        guardar_productos(Produ);
    }while (opt != 0);
}

void menuadmin_cat(){
    categ_vect Cat = cargar_categorias();
    int opt;
    char resp;
    int pos;          //Posicion del proveedor al que se le realizan los cambios.

    do{
        clear();
        printf("+---------------------------------+\n");
        printf("| QUE DESEA REALIZAR:             |\n");
        printf("+---------------------------------+\n");
        printf("| <1> Mostrar listado categorias  |\n");
        printf("| <2> Dar de alta categorias      |\n");
        printf("| <3> Dar de baja categorias      |\n");
        printf("| <4> Modificar categorias        |\n");
        printf("| <0> Volver                      |\n");
        printf("+---------------------------------+\n");
 
        opt = input_int();
        fflush(stdin);
        switch (opt){
            case 1:
                listar_categorias(Cat);
                break;
            case 2:
                printf("Seguro que quiere agregar una categoria [s/n]: ");
                resp = confirmacion();
                if(resp == 'S'|| resp == 's')
                    Cat = agregar_categorias(Cat);
                break;
            case 3:
                Cat = eliminar_categorias(Cat);
                break;
            case 4:
                Cat = modificar_categorias(Cat);
                break;
            
            case 0:         //CASO DE SALIDA
                break;
            default:
                break;
        }
        guardar_categorias(Cat);
    }while (opt != 0);
    free(Cat.categ);
}

void menuadmin_ped(){
    pedidos Ped = cargar_pedidos();
    prod_pedidos Prod_P = cargar_prod_pedidos();
    int opt;
    char resp;
    int pos;          //Posicion del cliente al que se le realizan los cambios.

    do{
        clear();
        printf("+----------------------------------+\n");
        printf("| QUE DESEA REALIZAR:              |\n");
        printf("+----------------------------------+\n");
        printf("| <1> Lista completa de pedidos    |\n");
        printf("| <2> Lista estado de pedidos      |\n");
        printf("| <3> Realizar pedido              |\n");
        printf("| <4> Eliminar pedido              |\n");
        printf("| <5> Modificar pedido             |\n");
        printf("| <6> Asignar transportista pedido |\n");
        printf("| <7> Asignar locker pedido        |\n");
        printf("| <0> Volver                       |\n");
        printf("+----------------------------------+\n");
 
        opt = input_int();
        fflush(stdin);
        switch (opt){
            case 1:

                break;
            case 2:
                printf("Seguro que quiere agregar un pedido [s/n]: ");
                resp = confirmacion();
                if(resp == 'S'|| resp == 's')
                break;
            case 3:
                printf("Para poder realizar un pedido es necesario seleccionar el cliente.\n");
                Sleep(3000);
                pos = busqueda_cliente();
                if(pos!= -1)
                    Ped = crear_pedido(Ped, pos);
                break;
            case 4:

                if (pos != -1)
                    
                break;
            
            case 0:         //CASO DE SALIDA
                break;
            default:
                break;
        }
        guardar_pedido(Ped);
    }while (opt != 0);
    free(Ped.pedidos);
}

void menuadmin_transp(){
    transport_vect T = cargar_transportistas();
    int opt;
    char resp;
    int pos;          //Posicion del proveedor al que se le realizan los cambios.

    do{
        clear();
        printf("+---------------------------------+\n");
        printf("| QUE DESEA REALIZAR:             |\n");
        printf("+---------------------------------+\n");
        printf("| <1> Listado transportista       |\n");
        printf("| <2> Dar de alta transportista   |\n");
        printf("| <3> Dar de baja transportista   |\n");
        printf("| <4> Modificar transportista     |\n");
        printf("| <0> Volver                      |\n");
        printf("+---------------------------------+\n");
 
        opt = input_int();
        fflush(stdin);
        switch (opt){
            case 1:
                listar_transport(T);
                break;
            case 2:
                printf("Seguro que quiere agregar un transportista [s/n]: ");
                resp = confirmacion();
                if(resp == 'S'|| resp == 's')
                    T = alta_transport(T);
                break;
            case 3:
                pos = buscar_transport(T);
                if(pos != -1)
                    T= baja_transport(T, pos);
                break;
            case 4:
                pos = buscar_transport(T);
                if (pos != -1)
                    T = modificar_transport(T,pos);
                break;
            
            case 0:         //CASO DE SALIDA
                break;
            default:
                break;
        }
        guardar_transportista(T);
    }while (opt != 0);
    free(T.transportistas);
}

void menuadmin_desc(){
    DescClientes Dc = Cargar_DescuentosClientes();
    Descuentos D = Cargar_Descuentos();
    clients C = cargar_clientes();

    fecha fch_cad;
    fecha fch_act;
    fch_act.dia = dia_sist();
    fch_act.mes = mes_sist();
    fch_act.anio = anio_sist();

    int opt;
    char resp;
    int pos;          //Posicion del proveedor al que se le realizan los cambios.

    do{
        clear();
        printf("+------------------------------------+\n");
        printf("| QUE DESEA REALIZAR:                |\n");
        printf("+------------------------------------+\n");
        printf("| <1> Listado de descuentos          |\n");
        printf("| <2> Dar de alta descuento          |\n");
        printf("| <3> Dar de baja descuento          |\n");
        printf("| <4> Modificar categorias           |\n");
        printf("| <5> Lista clientes descuento       |\n");
        printf("| <6> Lista clientes descuento usado |\n");
        printf("| <7> Asignar cliente descuento      |\n");
        printf("| <0> Volver                         |\n");
        printf("+------------------------------------+\n");
 
        opt = input_int();
        fflush(stdin);
        switch (opt){
            case 1:
                Listar_Descuentos(D);
                break;
            case 2:
                printf("Seguro que quiere agregar un descuento [s/n]: ");
                resp = confirmacion();
                if(resp == 'S'|| resp == 's')
                    D = Alta_Descuentos(D);
                break;
            case 3:
                    D = Baja_Descuentos(D);
                break;
            case 4:
                    D = Modificar_Descuentos(D);
            case 5:

                break;
            case 6:
                    
                break;
            case 7:
                printf("Se va a proceder a buscar un cliente para asignar un codigo");
                Sleep(2000);
                pos = busqueda_cliente();
                if(pos != -1){
                    fch_cad = crear_fechacad(fch_act);
                    Asignar_Descuentos(Dc, pos, fch_cad);
                }
                break;
            
            case 0:         //CASO DE SALIDA
                break;
            default:
                break;
        }
        Guardar_Descuentos(D);
        Guardar_DescuentosClientes(Dc);
    }while (opt != 0);
    free(D.Desc);
    free(Dc.DescCliente);
    free(C.clients);
}

void menuadmin_devol(){
    devoluciones Dev = cargar_devoluciones();
    int opt;
    char resp;
    int pos, ped;          //Posicion del proveedor al que se le realizan los cambios.

    do{
        clear();
        printf("+---------------------------------+\n");
        printf("| QUE DESEA REALIZAR:             |\n");
        printf("+---------------------------------+\n");
        printf("| <1> Listado devoluciones        |\n");
        printf("| <2> Dar de alta devolucion      |\n");
        printf("| <3> Dar de baja devolucion      |\n");
        printf("| <4> Modificar devolucion        |\n");
        printf("| <5> Aceptar devolucion          |\n");
        printf("| <6> Marcar devolucion recibida  |\n");
        printf("| <0> Volver                      |\n");
        printf("+---------------------------------+\n");
 
        opt = input_int();
        fflush(stdin);
        switch (opt){
            case 1:
                
                break;
            case 2:
                printf("Para hacer una devolucion tiene que elegir un cliente.");
                Sleep(2000);
                pos = busqueda_cliente();
                    if (pos != -1){
                        printf("Ahora tienes que seleccionar un pedido.\n");
                        Sleep(2000);
                        //BUSCAR PEDIDO
                        crear_devolucion(Dev, ped, pos);
                    }
                break;
            case 3:

                break;
            case 4:
                break;
            
            case 0:         //CASO DE SALIDA
                break;
            default:
                break;
        }
       
    }while (opt != 0);
}

void listar_admin(admin_prov_vect admin){
    int i;
    clear();
    printf("+------------------------------+\n");
    printf("| ADMINS REGISTRADOS           |\n");
    printf("+------------------------------+\n");

    for(i=1;i<admin.tam;i++){
        if(strcmp(admin.usuarios[i].Perfil_usuario, "administrador") == 0)
            printf("| %-30s |\n",admin.usuarios[i].email);
    }
    printf("+------------------------------+\n");
    printf("Presione [ENTER] para volver...");
    getchar();
}


/*** GESTIONAR ADMIN ***/

int buscar_admin(admin_prov_vect admin){
    int len = 0, i, opt = -1, pos;
    char cad_busq[MAX_EMAIL]; 
    int n_coinc = 0;                      //Contador de coincidencias encontradas
    int *vect_coinc;                    //Vector que contiene las ids de las coincidencias

    vect_coinc = (int*)malloc(1*sizeof(int)); 
    printf("Introduzca su busqueda de correo: ");

    fflush(stdin);
    fgets(cad_busq, MAX_EMAIL, stdin);         //Cadena por la que se va a buscar el nombre
    fflush(stdin);
    terminador_cad(cad_busq);

    len = strlen(cad_busq);
    for(i=1; i<admin.tam; i++){           //Busqueda de coincidencias nombre.
        if(strncasecmp(cad_busq, admin.usuarios[i].email, len) == 0){
            printf("<%d> %s\n",n_coinc+1, admin.usuarios[i].email);
            n_coinc++;
            vect_coinc = (int*)realloc(vect_coinc, n_coinc*sizeof(int));
            vect_coinc[n_coinc-1] = admin.usuarios[i].Id_empresa;
        }
    }
    if(n_coinc == 0){
        printf("No se ha encontrado ninguna coincidencia.\nSe cancela la accion deseada, disculpe las molestias.");
        getchar();
        return(-1);
    }

    printf("\nPor favor introduzca el numero <n> del que desea seleccionar o introduzca '0' para salir.\n");   //Elegir una opcion de coincidencia
    scanf(" %d", &opt);
    if(opt == 0){
        return -1;
    }
    
    while(opt < 0 || opt > n_coinc){
        printf("Introduzca una opcion valida: ");
        scanf(" %d", &opt);
    }
    fflush(stdin);
    pos = vect_coinc[opt-1];
    free(vect_coinc);

    return pos;
}

admin_prov_vect agregar_admin(admin_prov_vect admin){
    /***DEBIDO AL USUARIO POR DEFECTO LA ID Y LA POSICION EN LA ESTRUCTURA DEL CLIENTE ES LA MISMA***/
    int new_id = admin.tam;           //IDENTIFICADOR DEL NUEVO CLIENTE   

    admin.usuarios = realloc(admin.usuarios, (new_id+1)*sizeof(client));  //Reasignar numero de clientes
    if (admin.usuarios == NULL){
        printf("No se pudo asignar la estructura de clientes");
        getchar();
        exit(EXIT_FAILURE);
    }

    admin.usuarios[new_id].Id_empresa = 0;
    strcpy(admin.usuarios[new_id].Nombre, "ESIZON");
    admin = admin_email(admin, new_id, 0);
    admin = admin_contr(admin, new_id, 0);
    strcpy(admin.usuarios[new_id].Perfil_usuario, "administrador");

    admin.tam++;

    guardar_adminprov(admin);

    printf("Se ha creado un administrador correctamente");
    Sleep(2000);

    
    return admin;
}

admin_prov_vect eliminar_admin(admin_prov_vect admin, int pos){
    int i;
    char resp;      //Variable para responder preguntas si/no.
    clear();
    printf("Estas seguro de eliminar al cliente [ %s ]? [s/n]: ", admin.usuarios[pos].email);
    resp = confirmacion();

    if (resp == 'S' || resp == 's'){
        for (i = pos; i < admin.tam - 1; i++) {	//Desplazar la posicion de la estructura admin(admin_prov_vect)
			admin.usuarios[i] = admin.usuarios[i + 1];
		}

        admin.tam --;

        admin.usuarios = realloc(admin.usuarios, admin.tam*sizeof(admin_prov));
        if (admin.usuarios == NULL) {
			printf ("\nNo se pudo reasignar estructuras clientes.");
        	getchar ();
        	exit (EXIT_FAILURE);
		}

        guardar_adminprov(admin);                        //Volcado de datos a fichero

        printf("Se ha eliminado al usuario correctamente");
    }else{
        printf("Se cancelo la eliminacion del cliente.");
    }
    Sleep(2000);
    return admin;
}

admin_prov_vect gestionar_admin (admin_prov_vect admin, int pos, int mod){
    //CAMBIO DE INFORMACION//
    int opt = -1;

    do{
        //MOSTRAR INFORMACION//
        clear();
        printf("+------------ TU INFORMACION ------------+\n");
        printf("| Email: %-31s |\n", admin.usuarios[pos].email);
        printf("+----------------------+-----------------+\n");
        printf("| QUE DESEA MODIFICAR: |\n");
        printf("+----------------------+\n");
        printf("| <1> Email            |\n");
        printf("| <2> Contrasena       |\n");
        printf("| <0> Volver           |\n");
        printf("+----------------------+\n");

        scanf("%d", &opt);
        switch (opt){
            case 1:
                admin = admin_email(admin, pos, mod);
                
                break;
            case 2:
                admin = admin_contr(admin, pos, mod);
                break;
            case 0:      
                //CASO DE SALIDA
                break;
            default:
                break;
        }
        guardar_adminprov(admin);
    }while(opt != 0);
    return admin;
}

admin_prov_vect admin_email(admin_prov_vect admin, int pos, int mod){
    
    char sufijo[] = "@esizon.com";
    int i,
        lensuf = strlen(sufijo),             //Longitud del sufijo '@esizon.com'
        emailvalid = 0;                     //Variable para verificar si correo es valido
    
    char cad_email[MAX_EMAIL];
    

    if(mod == 1)
        printf("\nEmail actual: < %s >\n", admin.usuarios[pos].email);
    printf("Ingrese el {usuario} de su correo '{usuario}@esizon.com' [ MAX 19 CARACTERES ]: ");
    
    do{
        emailvalid = 1;
        fflush(stdin);
        fgets(cad_email, MAX_EMAIL-lensuf, stdin);
        terminador_cad(cad_email);

        if(strlen(cad_email) == 0){     //Si email esta vacio no es valido
            emailvalid = 0;         
        }else{
            strcat(cad_email, sufijo);

            for(i=1;i<admin.tam;i++){
                if(strcmp(cad_email, admin.usuarios[i].email) == 0){    //Si email en uso no es valido
                    printf("Se ha encontrado un admin usando ese correo.\n");
                    printf("Vuelva a introducir el identificador: ");
                    emailvalid = 0;
                }
            }
        }

    }while(emailvalid != 1);

    strcpy(admin.usuarios[pos].email, cad_email);
    fflush(stdin);
    return admin;
}

admin_prov_vect admin_contr(admin_prov_vect admin, int pos, int mod){
    char cad_contr[MAX_PSW], verif_contr[MAX_PSW];

    /***COMPROBAR CONTRASENA SI CLIENTE EXISTE Y LO MODIFICA EL MISMO***/

    if(mod == 1){
        printf("\nPara poder cambiar la contrasena es necesario verificar la anterior: ");

        do{
            fflush(stdin);
            fgets(cad_contr, MAX_PSW, stdin);
            terminador_cad(cad_contr);

            

            if(strcmp(cad_contr, "exit") == 0)  //Salir del bucle
                return admin;
            else if(strcmp(cad_contr, admin.usuarios[pos].Contrasena))
                printf("Por favor vuelva a intentarlo. Si desea salir escriba [exit]: ");

        } while(strcmp(cad_contr, admin.usuarios[pos].Contrasena));
    }

    do{
        printf("Escriba la nueva contrasena: ");
        
        fgets(cad_contr, MAX_PSW, stdin);
        terminador_cad(cad_contr);
        fflush(stdin);

        if(strcmp(cad_contr, "exit") == 0)                         //SALIR DE CAMBIO DE CONTRASENA
            return admin;
        else if(strcmp(cad_contr, admin.usuarios[pos].Contrasena) == 0)      //COMPROBAR SI NUEVA CONTRASENA IGUAL A LA ENTERIOR
            printf("La contrasena tiene que ser diferente a la anterior, si quiere salir escriba [exit].\n");
        if(strlen(cad_contr) > 15)
            printf("La contrasena tiene como maximo 15 caracteres. Vueva a intentarlo\n");
         
    } while (strcmp(cad_contr, admin.usuarios[pos].Contrasena) == 0 || strlen(cad_contr) == 0 || strlen(cad_contr) > 15);

    do{
        printf("Vuelva a introducir la nueva contrasena: ");

        fflush(stdin);
        fgets(verif_contr, MAX_PSW, stdin);
        terminador_cad(verif_contr);
    } while (strcmp(cad_contr, verif_contr) != 0);

    strcpy(admin.usuarios[pos].Contrasena, cad_contr);

    fflush(stdin);
    return admin;
}


/*** GESTIONAR CLIENTE ***/

int busqueda_cliente(){
    clients C = cargar_clientes();

    int pos = -2, opt;             //Elijo -2 como pos predeter. ya que -1 es para cancelar la busqueda
    while (pos == -2){    //Solo va a salir del bucle cuando se selecciona la posicion de un cliente valido
        clear();
        printf("Para poder realizar esta accion tiene que seleccionar un cliente.\n");
        printf("Como quieres buscar\n");
        printf("1. Por nombre.\n");
        printf("2. Por localidad.\n");
        printf("3. Por email.\n");
        printf("0. Cancelar.\n");
        
        do{ //Selecciona un filtro valido
            opt = input_int();
            switch (opt)
            {
            case 1:
                pos = busqueda_clientetipo(C, pos, 1);  //Por nombre
                opt = 0;
                break;
            case 2:
                pos = busqueda_clientetipo(C, pos, 2);  //Por localidad
                opt = 0;
                break;  
            case 3:
                pos = busqueda_clientetipo(C, pos, 3);  //Por email
                opt =0;
                break;
            case 0:
                pos = -1;
                printf("Se ha cancelado la busqueda.\n");
                Sleep(2000);
            default:
                break;
            }
        }while(opt!=0);

    }
    return pos;
}

int busqueda_clientetipo(clients C, int pos, int tipo){
    int len = 0, i, opt = -1;
    char cad_busq[35]; 
    int n_coinc = 0;                      //Contador de coincidencias encontradas
    int *vect_coinc;                    //Vector que contiene las ids de las coincidencias

    vect_coinc = (int*)malloc(1*sizeof(int)); 
    printf("Introduzca su busqueda: ");

    fflush(stdin);
    fgets(cad_busq, sizeof(cad_busq), stdin);         //Cadena por la que se va a buscar el nombre
    fflush(stdin);
    terminador_cad(cad_busq);

    len = strlen(cad_busq);
    if(tipo == 1){
        if(len > MAX_NOM)
            len = MAX_NOM;

        for(i=1; i<C.n_clients; i++){           //Busqueda de coincidencias nombre.
            if(strncasecmp(cad_busq, C.clients[i].Nom_cliente, len) == 0){
                printf("<%d> %s - %s - %s\n",n_coinc+1,  C.clients[i].Nom_cliente, C.clients[i].email, C.clients[i].Localidad);
                n_coinc++;
                vect_coinc = (int*)realloc(vect_coinc, n_coinc*sizeof(int));
                vect_coinc[n_coinc-1] = C.clients[i].Id_cliente;
                }
        }
    }else if(tipo == 2){
        if(len > MAX_LOC)
            len = MAX_LOC;
        for(i=1; i<C.n_clients; i++){           //Busqueda de coincidencias localidad.
            if(strncasecmp(cad_busq, C.clients[i].Localidad, len) == 0){
                printf("<%d> %s - %s - %s\n",n_coinc+1,  C.clients[i].Nom_cliente, C.clients[i].email, C.clients[i].Localidad);
                n_coinc++;
                vect_coinc = (int*)realloc(vect_coinc, n_coinc*sizeof(int));
                vect_coinc[n_coinc-1] = C.clients[i].Id_cliente;
                }
        }
    }else if(tipo == 3){
        if(len > MAX_EMAIL)
            len = MAX_EMAIL;
        for(i=1; i<C.n_clients; i++){           //Busqueda de coincidencias email.
            if(strncasecmp(cad_busq, C.clients[i].email, len) == 0){
                printf("<%d> %s - %s - %s\n",n_coinc+1,  C.clients[i].Nom_cliente, C.clients[i].email, C.clients[i].Localidad);
                n_coinc++;
                vect_coinc = (int*)realloc(vect_coinc, n_coinc*sizeof(int));
                vect_coinc[n_coinc-1] = C.clients[i].Id_cliente;
                }
        }
    }else{
        return -1;      //SI FALLO EN TIPO VOLVER AL MENU ANTERIOR
    }
    

    if(n_coinc == 0){
        printf("No se ha encontrado ninguna coincidencia.\nSe cancela la accion deseada, disculpe las molestias.");
        getchar();
        return(-1);
    }

    printf("\nPor favor introduzca el numero <n> del que desea seleccionar o introduzca '0' para salir.\n");   //Elegir una opcion de coincidencia
    do
    {
        opt = input_int();
        if(opt == 0){
            printf("Se cancelo la busqueda.");
            Sleep(2000);
            return -1;
        }
        if(opt < 0 || opt > n_coinc)
            printf("Introduzca una opcion valida: ");
    } while (opt < 0 || opt > n_coinc);
    
    
    
    fflush(stdin);
    pos = vect_coinc[opt-1];
    free(vect_coinc);

    return pos;
}

void mostrar_clientes(clients C){
    int i;
    clear();
    printf("+---------------------+\n");
    printf("| LISTADO DE CLIENTES |\n");
    printf("+---------------------+---------------------+-------------------------------+\n");
    printf("| Nombre              | Localidad           | Email                         |\n");
    printf("+---------------------+---------------------+-------------------------------+\n");
    for(i=1;i<C.n_clients;i++){
        printf("| %-20s| %-20s| %-30s|\n",C.clients[i].Nom_cliente, C.clients[i].Localidad, C.clients[i].email);
    }
    printf("+---------------------+---------------------+-------------------------------+\n");
    printf("Presione enter para salir");
    getchar();
}

clients agregar_cliente(clients C){
    /***DEBIDO AL USUARIO POR DEFECTO LA ID Y LA POSICION EN LA ESTRUCTURA DEL CLIENTE ES LA MISMA***/
    int new_id = C.n_clients;           //IDENTIFICADOR DEL NUEVO CLIENTE   

    C.clients = realloc(C.clients, (new_id+1)*sizeof(client));  //Reasignar numero de clientes
    if (C.clients == NULL){
        printf("No se pudo asignar la estructura de clientes");
        getchar();
        exit(EXIT_FAILURE);
    }

    C.clients[new_id].Id_cliente = new_id;
    C = cliente_nom(C, new_id);                 //Crear nombre
    C = cliente_email(C, new_id, 0);            //      correo      
    C = cliente_contr(C, new_id, 0);            //      contrasena
    C = cliente_dir(C, new_id , 0);             //      direccion
    C = cliente_cart(C, new_id, 0);             //      cartera

    C.n_clients++;

    guardar_clientes(C);

    printf("Se ha creado el cliente %s correctamente", C.clients[new_id].Nom_cliente);
    Sleep(3000);

    return C;
}

clients eliminar_cliente(clients C, int pos){
    int i;
    char resp;      //Variable para responder preguntas si/no.
    clear();
    printf("Estas seguro de eliminar al usuario [ %s ]? [s/n]: ", C.clients[pos].Nom_cliente);
    
    resp = confirmacion();

    if (resp == 'S' || resp == 's'){
        for (i = pos; i < C.n_clients - 1; i++) {	//Desplazar la posicion de los clientes
			C.clients[i] = C.clients[i + 1];
			C.clients[i].Id_cliente = i + 1;				//Reasignar id clientes
		}

        C.n_clients --;

        C.clients = realloc(C.clients, C.n_clients*sizeof(client));
        if (C.clients == NULL) {
			printf ("\nNo se pudo reasignar estructuras clientes.");
        	getchar ();
        	exit (EXIT_FAILURE);
		}

        guardar_clientes(C);                        //Volcado de datos a fichero

        printf("Se ha eliminado al usuario correctamente");
    }else{
        printf("Se cancelo la eliminacion del cliente.");
    }
    Sleep(2000);
    return C;
}

clients gestionar_cliente(clients C, int pos, int mode){
    //CAMBIO DE INFORMACION//
    int opt;
    char cad_loc[44] = "";
    strcat(cad_loc, C.clients[pos].Localidad);
    strcat(cad_loc, ", ");
    strcat(cad_loc, C.clients[pos].Provincia);
    do{
        //MOSTRAR INFORMACION//
        clear();
        printf("\n+----------------- INFORMACION PERSONAL -----------------+\n");
        printf("| Nombre: %-47s|\n", C.clients[pos].Nom_cliente);
        printf("| Dir: %-50s|\n", C.clients[pos].Dir_cliente);
        printf("| Localidad: %-44s|\n", cad_loc);
        printf("| Email: %-48s|\n", C.clients[pos].email);
        printf("| Cartera: %-46d|\n", C.clients[pos].Cartera);
        printf("+-------------------------------------+------------------+\n");

        printf("+-------- QUE DESEA MODIFICAR --------+\n");
        printf("| <1> Nombre                          |\n");
        printf("| <2> Direccion                       |\n");
        printf("| <3> Email                           |\n");
        printf("| <4> Contrasena                      |\n");
        printf("| <5> Cartera                         |\n");
        printf("| <0> Salir                           |\n");
        printf("+-------------------------------------+\n");
        scanf("%d", &opt);
        fflush(stdin);
        switch (opt){
            case 1:
                C = cliente_nom(C, pos);
                break;
            case 2:
                C = cliente_dir(C, pos, mode);
                break;
            case 3:
                C = cliente_email(C, pos, mode);
                break;

            case 4:
                C = cliente_contr(C, pos, mode);
                break;
            case 5:
                C = cliente_cart(C, pos, mode); 
                break;
            case 0:         //CASO DE SALIDA
                break;
            default:
                printf("Seleccione una opcion valida: ");
                break;
        }
        guardar_clientes(C);
    }while(opt!=0);
    
    return C;
}

clients cliente_nom(clients C, int pos){
    char cad_nom[MAX_NOM];
    fflush(stdin);

    do{
        printf("Ingrese el nombre: ");
        
        fgets(cad_nom, MAX_NOM, stdin);
        terminador_cad(cad_nom);
        fflush(stdin);

    } while (strlen(cad_nom) == 0);     //LIMITAR NOMBRE NO VACIO

    strcpy(C.clients[pos].Nom_cliente, cad_nom);

    return C;
}

clients cliente_contr(clients C, int pos, int mod){
    char cad_contr[MAX_PSW], verif_contr[MAX_PSW];

    /***COMPROBAR CONTRASENA SI CLIENTE EXISTE Y LO MODIFICA EL MISMO***/
    
    if(mod == 1){
        printf("Para poder cambiar la contrasena es necesario verificar la anterior: ");
        
        fgets(cad_contr, MAX_PSW, stdin);
        terminador_cad(cad_contr);
        fflush(stdin);
        
        while(strcmp(cad_contr, C.clients[pos].Contrasena) != 0){
            printf("Por favor vuelva a intentarlo. Si desea salir escriba [exit]: ");
            
            fgets(cad_contr, MAX_PSW, stdin);
            terminador_cad(cad_contr);
            fflush(stdin);

            if(strcmp(cad_contr, "exit") == 0)  //Salir del bucle
                return C;
        }
    }

    /***MODIFICAR LA CONTRASENA ACTUAL***/
    
    do{
        printf("Escriba la contrasena a tener: ");
        fgets(cad_contr, MAX_PSW+5, stdin);
        terminador_cad(cad_contr);
        fflush(stdin);

        if(strcmp(cad_contr, "exit") == 0)                 //SALIR DE CAMBIO DE CONTRASENA
            return C;
        if(strcmp(cad_contr, C.clients[pos].Contrasena) == 0 && strlen(cad_contr) != 0)   //COMPROBAR SI NUEVA CONTRASENA IGUAL A LA ENTERIOR
            printf("La contrasena tiene que ser diferente a la anterior, si quiere salir escriba [exit].\n");
        if(strlen(cad_contr) > 15)
            printf("La contrasena tiene como maximo 15 caracteres. Vueva a intentarlo\n");

    } while (strcmp(cad_contr, C.clients[pos].Contrasena) == 0 || strlen(cad_contr) == 0 || strlen(cad_contr) > 15);
    
    do{
        fflush(stdin);
        printf("Vuelva a introducir la nueva contrasena: ");
        
        fgets(verif_contr, MAX_PSW+5, stdin);
        terminador_cad(verif_contr);
        fflush(stdin);
    }while (strcmp(cad_contr, verif_contr) != 0);
    strcpy(C.clients[pos].Contrasena, cad_contr);

    return C;
}

clients cliente_dir(clients C, int pos, int mod){
    char cad_dir[51], cad_lugar[MAX_LOC];
    
    if (mod == 1)
        printf("\nDireccion actual: %s\n", C.clients[pos].Dir_cliente);
    
    do{   
        printf("Ingrese la direccion del hogar (max 50 caracteres): ");
        fgets(cad_dir, sizeof(cad_dir), stdin);
        terminador_cad(cad_dir);
        fflush(stdin);
        
    } while (strlen(cad_dir) == 0);
    strcpy(C.clients[pos].Dir_cliente, cad_dir);

    if (mod == 1)
        printf("\nLocalidad actual: %s\n", C.clients[pos].Localidad);
    
    do{
        printf("Introduzca la localidad: ");
        fgets(cad_lugar, sizeof(cad_lugar), stdin);
        terminador_cad(cad_lugar);
        fflush(stdin);
        
    } while (strlen(cad_lugar) == 0);

    strcpy(C.clients[pos].Localidad, cad_lugar);

    if (mod == 1)
        printf("\nProvincia actual: %s\n", C.clients[pos].Provincia);
    
    do{   
        printf("Introduzca la provincia: ");
        fgets(cad_lugar, sizeof(cad_lugar), stdin);
        terminador_cad(cad_lugar);
        fflush(stdin);
        
    } while (strlen(cad_lugar) == 0);
    strcpy(C.clients[pos].Provincia, cad_lugar);

    return C;
}

clients cliente_email(clients C, int pos, int mod){
    char cad_email[MAX_EMAIL];
    char org[12];
    int opt,i;

    if(mod == 1)
        printf("\nEmail actual: < %s >\n", C.clients[pos].email);

    printf("+----------------------------+\n");
    printf("| ELIJA PROVEEDOR DEL CORREO |\n");
    printf("+----------------------------+\n");
    printf("| <1> GMAIL (@gmail.com)     |\n");
    printf("| <2> OUTLOOK (@outlook.es)  |\n");
    printf("| <3> YAHOO (@yahoo.com)     |\n");

    if(mod == 1)
    printf("| <4> CANCELAR               |\n");

    printf("+----------------------------+\n");
    do{
    opt = input_int();
    switch (opt)
    {
    case 1:
        strcpy(org, "@gmail.com");
        break;
    case 2:
        strcpy(org, "@outlook.es");
        break;
    case 3:
        strcpy(org, "@yahoo.com");
        break;
    case 4:
        if(mod == 1){
            printf("Se ha cancelado cambio de correo");
            Sleep(2000);
            return C;
        }
        break;

    default:
        break;
    }
    } while (opt < 1 || opt > 3);

    int tam_email = (MAX_EMAIL- strlen(org));
    int emailvalid = 0;
    
    do{
        emailvalid = 1;
        printf("Ingrese el usuario del correo (Sin la terminacion del correo): ");

        fflush(stdin);
        fgets(cad_email, MAX_EMAIL, stdin);
        terminador_cad(cad_email);
        fflush(stdin);

        if(strlen(cad_email) > tam_email){
            printf("Ha sobrepasado el limite de caracteres que es %d\n", tam_email);
            emailvalid = 0;
        }else if(strlen(cad_email) == 0){
            emailvalid = 0;
        }else{
            for(i=1;i<C.n_clients;i++){
                if(strncmp(C.clients[i].email, cad_email, strlen(cad_email)) == 0){
                    emailvalid = 0;
                    printf("Ese usuario del mail ya ha sido introducido.\n");
                }
            }
        }
    }while (emailvalid != 1);

    strcat(cad_email, org);
    
    strcpy(C.clients[pos].email, cad_email);

    return C;
}

clients cliente_cart(clients C, int pos, int mod){
    int cartera = 0,
        verif;
    if(mod == 1){
        printf("Saldo de la cartera actual: %d\n", C.clients[pos].Cartera);
    }
    printf("Introduzca el saldo disponible: ");
    do{

        cartera = input_int();
        if(cartera < 0)
            printf("Introduce un saldo positivo: ");

    } while (cartera < 0);
    
    C.clients[pos].Cartera = cartera;

    return C;
}

