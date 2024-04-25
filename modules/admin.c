#include "admin.h"



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
        titulo();
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
        titulo();
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
        titulo();
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
                    Produ = agregar_productos(Produ, 0);
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
        titulo();
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
        titulo();
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
                listar_pedidos(Ped);
                break;
            case 2:
                menu_listadoped_estado();
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
                printf("Para poder eliminar un pedido es necesario seleccionar el cliente.\n");
                Sleep(3000);
                Ped = eliminar_pedidos(Prod_P, Ped);
            case 5:
                Ped = modificar_pedidos(Ped);
                break;
            case 6:
                modificar_asig_transport_admin();
                break;
            case 7:

            case 0:         //CASO DE SALIDA
                break;
            default:
                break;
        }
        guardar_pedido(Ped);
        guardar_productos_pedidos(Prod_P);
    }while (opt != 0);
    free(Ped.pedidos);
    free(Prod_P.prod_pedidos);
}

void menuadmin_transp(){
    transport_vect T = cargar_transportistas();
    int opt;
    char resp;
    int pos;          //Posicion del proveedor al que se le realizan los cambios.

    do{
        clear();
        titulo();
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
        titulo();
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
    int pos, ped;          //Posicion del cliente al que se le realizan los cambios.

    do{
        clear();
        titulo();
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
                listar_devoluciones(Dev);
                break;
            case 2:
                printf("Para hacer una devolucion tiene que elegir un cliente.");
                Sleep(2000);
                pos = busqueda_cliente();
                    if (pos != -1){
                        printf("Ahora tienes que seleccionar un pedido.\n");
                        Sleep(2000);
                        //BUSCAR PEDIDO
                        Dev = nueva_devolucion_prod(pos, Dev);
                    }
                break;
            case 3:
                
                Dev = eliminar_devolucion(,Dev);
                break;
            case 4:
                Dev = modificar_devolucion(Dev);
                break;
            case 5:
                aceptar_dev(Dev);
            case 6:
                
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
    titulo();
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
    titulo();
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
        titulo();
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