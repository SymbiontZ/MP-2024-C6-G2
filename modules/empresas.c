#include "empresas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#include "complementos.h"
#include "Productos.h"
#include "pedidos.h"

// void listar_pedidos_prov(int id); void cambiar_estado_pedido(); void modificar_asig_transport();

//	FUNCIONES DE INICIO DE SESION



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
//Postcondición: El usuario habrá iniciado sesión como proveedor en el sistema, o se habrá cerrado la sesión por fallar la contraseña muchas veces. No devuelve nada.
void inicsesion_prov(admin_prov_vect provs, int pos){
	
	char validar_contra[16];
	int i = 3;
	
	clear();
	printf("\nIntroduzca su contrasena: ");
	scanf("%s", validar_contra);
	terminador_cad(validar_contra);
	do{
		if(strcmp(provs.usuarios[pos].Contrasena, validar_contra) == 0){
			menu_prov(provs, pos);
			i = -1;
		}
		else{
			printf("\nContrasena incorrecta, intentos restantes: %d\nVuelva a intentarlo: ", i);
			scanf("%s", validar_contra);
			terminador_cad(validar_contra);
			i--;
		}
	}while(i > 0);
	if(i == 0){
		printf("\nDemasiados intentos fallidos. Cerrando sesion...");
		exit(0);
	}
}



//Precondición: Recibe una estructura de tipo transport_vect (el vector de usuarios tipo transport), y la posición a utilizar en él.
//Postcondición: El usuario habrá iniciado sesión como transportista en el sistema, o se habrá cerrado la sesión por fallar la contraseña muchas veces. No devuelve nada.
void inicsesion_transport(transport_vect transports, int pos){
	
	char validar_contra[16];
	int i = 3;
	
	clear();
	printf("\nIntroduzca su contrasena: ");
	fflush(stdin);
	fgets(validar_contra, sizeof(validar_contra), stdin);
	terminador_cad(validar_contra);
	do{
		if(strcmp(transports.transportistas[pos].Contrasena, validar_contra) == 0){
			menu_transport(transports, pos);
			i = -1;
		}
		else{
			printf("\nContrasena incorrecta, intentos restantes: %d\nVuelva a intentarlo: ", i);
			scanf("%s", validar_contra);
			terminador_cad(validar_contra);
			i--;
		}
	}while(i > 0);
	if(i == 0){
		printf("\nDemasiados intentos fallidos. Cerrando sesion...");
		exit(0);
	}
}



//	MENÚS DE PROVEEDOR Y TRANSPORTISTA



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
//Postcondición: El usuario habrá realizado las tareas necesarias de gestión en la plataforma (ver y modificar perfil, gestionar productos, pedidos). No devuelve nada.
void menu_prov(admin_prov_vect provs, int pos){
	
	int op = -1;
	
	do{
		clear();
		
		printf("	#######################\n");
		printf("	## MENU DE PROVEEDOR ##\n");
		printf("	#######################\n");
		
		printf("\n	EMPRESA: %s\n", provs.usuarios[pos].Nombre);
		
		printf("\nBienvenido, %s - ¿Qué desea hacer hoy?\n\n <1> Ver perfil.\n <2> Ver productos.\n <3> Administrar pedidos\n <0> Volver.\n Elija una opción: ", provs.usuarios[pos].email);
		if(scanf("%i",&op)!=1){
			fflush(stdin);
			printf("\nError: introduzca una entrada válida.");
			Sleep(2000);
			op=-1;
		}
		else{
			switch(op){
				case 1: ver_perfil(provs, pos); break;
				case 2: ver_productos(provs, pos); break;
				case 3: ver_pedidos(provs, pos); break;
				case 0: break;
				default: break;
			}
		}
	}while(op!=0);
	
}



//Precondición: Recibe una estructura de tipo transport_vect (el vector de usuarios tipo transport), y la posición a utilizar en él.
//Postcondición: El usuario habrá realizado las tareas necesarias de gestión en la plataforma (ver y modificar perfil, repartos, retornos). No devuelve nada.
void menu_transport(transport_vect transports, int pos){
	
	int op = -1, i = 0;
	
	do{
		clear();
		
		printf("	###########################\n");
		printf("	## MENU DE TRANSPORTISTA ##\n");
		printf("	###########################\n");
		
		printf("\n	NOMBRE: %s\n", transports.transportistas[pos].Nombre);
		printf("\n	EMPRESA: %s\n", transports.transportistas[pos].Nom_Emp);
		
		printf("\nBienvenido, %s - ¿Qué desea hacer hoy?\n\n <1> Ver perfil.\n <2> Ver repartos asignados.\n <3> Retornos.\n <0> Salir.\n Elija una opción: ", transports.transportistas[pos].email);
		if(scanf("%i",&op)!=1){
			fflush(stdin);
			printf("\nError: introduzca una entrada válida.");
			Sleep(2000);
			op=-1;
		}
		else{
			switch(op){
				case 1: ver_perfil_t(transports, pos); break;
				case 2: break;
				case 3: break;
				case 0: break;
				default: break;
			}
		}
	}while(op!=0);
}



//	FUNCIONES PARA EL MENÚ DE PROVEEDOR



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
//Postcondición: El usuario habrá realizado las tareas necesarias de gestión de su cuenta en la plataforma. No devuelve nada.
void ver_perfil(admin_prov_vect provs, int pos){
	
	int op = -1;
	
	do{
		clear();
		
		printf("	############\n");
		printf("	## PERFIL ##\n");
		printf("	############\n");
	
		printf("\nInformación de su perfil:\n ID DEL SISTEMA: %04d\n EMPRESA: %s\n EMAIL: %s\n PRIVILEGIOS: %s\n", provs.usuarios[pos].Id_empresa, provs.usuarios[pos].Nombre, provs.usuarios[pos].email, provs.usuarios[pos].Perfil_usuario);
		
		printf("\n¿Qué desea hacer?\n <1> Cambiar email.\n <2> Cambiar contraseña.\n <0> Volver.\n Elija una opción: ");
		if(scanf("%i",&op)!=1){
			fflush(stdin);
			printf("\nError: introduzca una entrada válida.");
			Sleep(2000);
			op = -1;
		}
		else{
			switch(op){
				case 1: cambiar_email(provs, pos); break;
				case 2: cambiar_contrasena(provs, pos); break;
				case 0: break;
				default: break;
			}
		}
	}while(op!=0);
}



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
//Postcondición: El usuario habrá realizado las tareas de gestión de productos convenientes.
void ver_productos(admin_prov_vect provs, int pos){
	
	produ_vect prods = cargar_productos();	//Creamos el vector de productos
	int op;
	
	do{
		clear();
		
		printf("	######################################\n");
		printf("	## SERVICIO DE GESTIÓN DE PRODUCTOS ##\n");
		printf("	######################################\n");
		
		printf("\n	EMPRESA: %s\n", provs.usuarios[pos].Nombre);
		
		printf("\nBienvenido al servicio de gestion de productos. Seleccione una opcion para continuar.\n\n <1> Ver mis productos.\n <2> Buscar un producto.\n <3> Modificar un producto\n <4> Añadir un producto al catalogo.\n <5> Retirar un producto del catalogo.\n Elija una opción: ", provs.usuarios[pos].email);
		if(scanf("%i",&op)!=1){
			fflush(stdin);
			printf("\nError: introduzca una entrada válida.");
			Sleep(2000);
			op=-1;
		}
		else{
			switch(op){
				case 1: break;
				case 2: break;
				case 3: break;
				case 4: break;
				case 5: break;
				case 0: break;
				default: break;
			}
		}
	}while(op!=0);
	
	guardar_productos(prods);				//Guardamos cambios
	Sleep(2000);
	
}



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
//Postcondición: El usuario habrá realizado las tareas de gestión de pedidos convenientes.
void ver_pedidos(admin_prov_vect provs, int pos){
	int op = -1;
	
	do{
		clear();
		
		printf("	####################################\n");
		printf("	## SERVICIO DE GESTION DE PEDIDOS ##\n");
		printf("	####################################\n");
		
		printf("\n	EMPRESA: %s\n", provs.usuarios[pos].Nombre);
		
		printf("\nBienvenido al servicio de gestion de peidos. Elija una opcion para continuar:\n\n <1> Ver pedidos asociados.\n <2> Cambiar estado de un pedido.\n <3> Modificar asignación de transportista.\n <4> Modificar asignación de locker. <0> Volver.\n Elija una opción: ", provs.usuarios[pos].email);
		if(scanf("%i",&op)!=1){
			fflush(stdin);
			printf("\nError: introduzca una entrada válida.");
			Sleep(2000);
			op=-1;
		}
		else{
			switch(op){
				case 1: listar_pedidos_prov(pos); break;
				case 2: cambiar_estado_pedido(); break;
				case 3: modificar_asig_transport(); break;
				case 4: break;
				case 0: break;
				default: break;
			}
		}
	}while(op!=0);
	
}



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
//Postcondición: No devuelve nada. Se habrá cambiado el email del usuario guardado en el puntero.
void cambiar_email(admin_prov_vect provs, int pos){
	
	char nuevo_email[31 - strlen(provs.usuarios[pos].Nombre) - 1];
	char prefijo[strlen(provs.usuarios[pos].Nombre) + 1];
	strcpy(prefijo, provs.usuarios[pos].Nombre);
	mayus_minus(prefijo);
	
	do{
		printf("Introduzca su nuevo email: nuevo_email@%s.com\n Nuevo email: ", prefijo);
		fflush(stdin);
		fgets(nuevo_email, sizeof(nuevo_email), stdin);
		terminador_cad(nuevo_email);
	}while(strlen(nuevo_email) == 0);
	
	sprintf(provs.usuarios[pos].email, "%s@%s.com", nuevo_email, prefijo);
	
}



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
//Postcondición: No devuelve nada. Se habrá cambiado la contraseña del usuario guardada en el puntero, o no.
void cambiar_contrasena(admin_prov_vect provs, int pos){
	
	char nueva_contra[21], contra_compr[21];									// Cadenas donde guardamos la contraseña nueva, y su repetición.
	int valido = 0, i = 0;
	
	printf("\nIntroduzca la contrasena actual: ");
	fflush(stdin);
	fgets(contra_compr, sizeof(contra_compr), stdin);
	terminador_cad(contra_compr);
	if(strcmp(contra_compr, provs.usuarios[pos].Contrasena) == 0){							
		do{
			if(i > 3)
				clear();
			printf("\nIndique la nueva contrasena: ");	
			fflush(stdin);					
			fgets(nueva_contra, sizeof(nueva_contra), stdin);
			fflush(stdin);
			terminador_cad(nueva_contra);
			printf("\nIndiquela de nuevo de nuevo: ");
			fflush(stdin);
			fgets(contra_compr, sizeof(contra_compr), stdin);	
			fflush(stdin);
			terminador_cad(contra_compr);
			if(strcmp(nueva_contra,contra_compr) == 0)							// Si las contraseñas son iguales (el usuario no se ha equivocado), salimos del bucle.
				valido = 1;
			else	
				printf("Contrasenas distintas, inténtelo de nuevo.");			// Solicitamos la nueva contraseña al usuario mientras no verifique que se repitan.
			i++;
		}while(valido == 0 || strlen(nueva_contra) == 0);
		printf("\nContraseña cambiada satisfactoriamente.");
		strcpy(provs.usuarios[pos].Contrasena, nueva_contra);
		Sleep(3000);															// Esperamos tres segundos antes de limpiar la pantalla para poder leer el mensaje anterior.
	}else{
		printf("\nContrasena errónea. Pruebe otra vez o contacte con un administrador.\n");
		Sleep(3000);															// Esperamos tres segundos antes de limpiar la pantalla para poder leer el mensaje anterior.		
	}
}



//	FUNCIONES PARA EL MENÚ DE TRANSPORTISTA



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
//Postcondición: El usuario habrá realizado las tareas necesarias de gestión de su cuenta en la plataforma. No devuelve nada.
void ver_perfil_t(transport_vect transports, int pos){

	int op = -1;
		
	do{
		clear();
		
		printf("	############\n");
		printf("	## PERFIL ##\n");
		printf("	############\n");
	
		printf("\nInformación de su perfil:\n ID DEL SISTEMA: %04d\n NOMBRE: %s\n EMAIL: %s\n EMPRESA: %s\n CIUDAD ASIGNADA: %s\n", transports.transportistas[pos].Id_transp, transports.transportistas[pos].Nombre, transports.transportistas[pos].email, transports.transportistas[pos].Nom_Emp, transports.transportistas[pos].Ciudad);
		
		printf("\n¿Qué desea hacer?\n <1> Cambiar nombre.\n <2> Cambiar email.\n <3> Cambiar contraseña.\n <0> Volver.\n Elija una opción: ");
		if(scanf("%i",&op)!=1){
			fflush(stdin);
			printf("\nError: introduzca una entrada válida.");
			Sleep(2000);
			op=-1;
		}
		else{
			switch(op){
				case 1: cambiar_nombre_t(transports, pos); break;
				case 2: cambiar_email_t(transports, pos); break;
				case 3: cambiar_contrasena_t(transports, pos); break;
				case 0: break;
				default: break;
			}
		}
	}while(op!=0);
}



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
//Postcondición: No devuelve nada. Se habrá cambiado el nombre del usuario guardado en el puntero.
void cambiar_nombre_t(transport_vect transports, int pos){
	
	char nuevo_nombre[21];
	int i = 0;
	do{
		if(i > 3)
			clear();
		printf("\nIngrese el nombre que debe figurar en el sistema: ");
		fflush(stdin);
		fgets(nuevo_nombre, sizeof(nuevo_nombre), stdin);
		fflush(stdin);
		terminador_cad(nuevo_nombre);
		strcpy(transports.transportistas[pos].Nombre, nuevo_nombre);
		i++;
	}while(strlen(nuevo_nombre) == 0);
}



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
//Postcondición: No devuelve nada. Se habrá cambiado el email del usuario guardado en el puntero.
void cambiar_email_t(transport_vect transports, int pos){
	
	char nuevo_email[31 - strlen(transports.transportistas[pos].Nom_Emp) - 1], prefijo[strlen(transports.transportistas[pos].Nom_Emp) + 1];
	strcpy(prefijo, transports.transportistas[pos].Nom_Emp);
	mayus_minus(prefijo);
	do{
		printf("\nIngrese el nuevo email: nuevo_email@%s.com\nnuevo_email: ", prefijo);
		fflush(stdin);
		fgets(nuevo_email, sizeof(nuevo_email), stdin);
		fflush(stdin);
		terminador_cad(nuevo_email);
	}while(strlen(nuevo_email) == 0);

	sprintf(transports.transportistas[pos].email, "%s@%s.com", nuevo_email, prefijo);
	
}



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
//Postcondición: No devuelve nada. Se habrá cambiado la contraseña del usuario guardada en el puntero, o no.
void cambiar_contrasena_t(transport_vect transports, int pos){
	
	char nueva_contra[21], contra_compr[21];									// Cadenas donde guardamos la contraseña nueva, y su repetición.
	int valido = 0, i = 0;
	
	printf("\nIntroduzca la contrasena actual: ");
	fflush(stdin);
	fgets(contra_compr, sizeof(contra_compr), stdin);
	fflush(stdin);
	terminador_cad(contra_compr);
	if(strcmp(contra_compr, transports.transportistas[pos].Contrasena) == 0){							
		do{
			if(i > 3)
				clear();
			printf("\nIndique la nueva contrasena: ");						
			fflush(stdin);
			fgets(nueva_contra, sizeof(nueva_contra), stdin);
			fflush(stdin);
			terminador_cad(nueva_contra);
			printf("\nIndiquela de nuevo de nuevo: ");
			fflush(stdin);
			fgets(contra_compr, sizeof(contra_compr), stdin);	
			fflush(stdin);
			terminador_cad(contra_compr);
			if(strcmp(nueva_contra,contra_compr) == 0)							// Si las contraseñas son iguales (el usuario no se ha equivocado), salimos del bucle.
				valido = 1;
			else	
				printf("\nContrasenas distintas, inténtelo de nuevo.");			// Solicitamos la nueva contraseña al usuario mientras no verifique que se repitan.
			i++;
		}while(valido == 0 || strlen(nueva_contra) == 0);
		strcpy(transports.transportistas[pos].Contrasena, nueva_contra);
		printf("\nContraseña cambiada satisfactoriamente.");
		Sleep(3000);															// Esperamos tres segundos antes de limpiar la pantalla para poder leer el mensaje anterior.
	}else{
		printf("\nContrasena errónea. Pruebe otra vez o contacte con un administrador.\n");
		Sleep(3000);															// Esperamos tres segundos antes de limpiar la pantalla para poder leer el mensaje anterior.		
	}
	
}



// FUNCIONES PARA LA GESTIÓN DE PROVEEDORES



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov) ya rellena.
//Postcondición: No devuelve nada. Se habrá mostrado por pantalla todos los AdminProvs del sistema, menos el superusuario.
void listar_prov(admin_prov_vect provs){
	int i;
	clear();
	
	printf("+---------------------------------------+\n");
	printf("| PROVEEDORES REGISTRADOS EN EL SISTEMA |\n");
	printf("+----------------------+----------------+---------------+\n");
	printf("| EMPRESA              | CORREO                         |\n");
	printf("+----------------------+--------------------------------+\n");
	for(i = 1; i < provs.tam; i++)
		if(strcmp(provs.usuarios[i].Perfil_usuario, "proveedor")==0)
			printf("| %-20s | %-30s |\n", provs.usuarios[i].Nombre, provs.usuarios[i].email);
	printf("+----------------------+--------------------------------+\n");
	printf("Presione [enter] para volver...");
	getchar();
}



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios proveedores / administradores) ya rellena.
//Postcondición: Devuelve la ID del usuario buscado, o -1 si se cancela la búsqueda.
int buscar_prov(admin_prov_vect provs){
	int pos = -2, opt = -1;             // Elijo -2 como pos predeter. ya que -1 es para cancelar la busqueda
	clear();
    while (pos == -2){    				// Solo va a salir del bucle cuando se selecciona la posicion de un cliente valido
        clear();
        printf("Busqueda de proveedores. Seleccione un metodo de busqueda para continuar.\n");
        printf("¿Como desea buscar?\n");
        printf("1. Por nombre de la empresa asociada.\n");
        printf("2. Por email.\n");
        printf("0. Cancelar.\n");
        
        while(opt > 2 || opt < 0){
            if(scanf("%i",&opt) != 1){
				fflush(stdin);
				printf("\nError: introduzca una entrada válida.");
				Sleep(2000);
				opt = -1;
			}
			else{
	            switch (opt)
	            {
	            case 1:
	                pos = buscar_prov_tipo(provs, pos, 1);
	                break;
	            case 2:
	                pos = buscar_prov_tipo(provs, pos, 2);
	                break; 
	            case 0:
	                pos = -1;
	                printf("Se ha cancelado la busqueda.\n");
					break;
	            default:
	                printf("Introduzca una opcion valida: ");
	                break;
	            }
	    	}
        }
    }
	Sleep(2000);
    return pos;
}



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios provvedores / administradores) ya rellena y dos enteros (posición a tratar y
//tipo de búsqueda.
//Postcondición: Devuelve la ID del usuario buscado, o -1 si se cancela la búsqueda.
int buscar_prov_tipo(admin_prov_vect provs, int pos, int tipo){
	int len = 0, i, opt = -1;
    char cad_busq[35]; 
    int n_coinc = 0;                      				// Contador de coincidencias encontradas
    int *vect_coinc;                    				// Vector de guardado de IDs con coincidencias

    vect_coinc = (int*)malloc(1*sizeof(int));
	
	do{
		printf("Por favor, introduzca su busqueda: ");
	
	    fflush(stdin);
	    fgets(cad_busq, sizeof(cad_busq), stdin);         	// Cadena por la que se va a buscar al proveedor
	    fflush(stdin);
	    terminador_cad(cad_busq);
	}while(strlen(cad_busq) == 0); 
	
    len = strlen(cad_busq);
    if(tipo == 1){
        if(len > 21)
            len = 21;

        for(i = 1; i < provs.tam; i++){           		// Búsqueda por nombre de empresa asociada.
            if(strncmp(cad_busq, provs.usuarios[i].Nombre, len) == 0){
                printf("<%d> %s | %s\n", n_coinc+1,  provs.usuarios[i].Nombre, provs.usuarios[i].email);
                n_coinc++;
                vect_coinc = (int*)realloc(vect_coinc, n_coinc*sizeof(int));
                vect_coinc[n_coinc-1] = provs.usuarios[i].Id_empresa;
                }
        }
    }else if(tipo == 2){
        if(len > 31)
            len = 31;
        for(i = 1; i < provs.tam; i++){          		// Búsqueda por email.
            if(strncmp(cad_busq, provs.usuarios[i].email, len) == 0){
                printf("<%d> %s | %s\n",n_coinc+1,  provs.usuarios[i].Nombre, provs.usuarios[i].email);
                n_coinc++;
                vect_coinc = (int*)realloc(vect_coinc, n_coinc*sizeof(int));
                vect_coinc[n_coinc-1] = provs.usuarios[i].Id_empresa;
                }
        }
    }else{
        return -1;      								// Si hay fallo en el tipo, volvemos al menú anterior (buscar_prov).
    }
    

    if(n_coinc == 0){
        printf("No se ha encontrado ninguna coincidencia.\n");
        Sleep(2000);
        return -1;
    }

    printf("\nIntroduzca el usuario que desea seleccionar, o introduzca '0' para salir.\n");   //Elegir una opcion de coincidencia
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



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios proveedores / administradores) ya rellena.
//Postcondición: Devuelve la estructura de tipo admin_prov_vect con un nuevo proveedor dado de alta, y habiendo guardado el 
// cambio en AdminProv.txt
admin_prov_vect alta_prov(admin_prov_vect provs){
	int nueva_id;
	char empresa[21];
	
	clear();
    
    printf("\n	##################################\n");
    printf("	## SERVICIO DE ALTAS DE USUARIO ##\n");
    printf("	##################################\n");
    
    printf("\nIntroduzca los datos del nuevo usuario del sistema:\n\n");
    
	provs.usuarios = realloc(provs.usuarios, (provs.tam + 1) * sizeof(admin_prov));
	provs.tam++;
	
	if (provs.usuarios == NULL){
        printf("No se pudo asignar la estructura de proveedores/administradores.\n");
        getchar();
        exit(33);
    }
    
    prov_nombre(provs, provs.tam - 1);
    nueva_id = buscar_id_prov(provs, provs.usuarios[provs.tam - 1].Nombre);
    printf("%d", nueva_id);
    provs.usuarios[provs.tam - 1].Id_empresa = nueva_id;
    prov_email(provs, provs.tam - 1);    
    prov_contra(provs, provs.tam - 1);
    strcpy(provs.usuarios[provs.tam - 1].Perfil_usuario, "proveedor\0");
    
	guardar_adminprov(provs);
    
    printf("\nUsuario %04d dado de alta correctamente.\n", nueva_id);
    
    Sleep(2000);
    
	return provs;
}



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de proveedores / administradores) ya rellena, y la 
// ID del proveedor a eliminar.
//Postcondición: Devuelve la estructura de tipo admin_prov_vect sin el proveedor / administrador de identificador indicado, y habiendo  
// guardado el cambio en AdminProv.txt
admin_prov_vect baja_prov(admin_prov_vect provs, int id){
	char respuesta;
	
	if(strcmp(provs.usuarios[id].Perfil_usuario, "proveedor") == 0){
		printf("Esta a punto de eliminar al proveedor con email asociado %s del sistema. Desea continuar? [s/n]: ", provs.usuarios[id].email);
		fflush(stdin);
		scanf("%c", &respuesta);
		
		while (respuesta != 'S' && respuesta != 's' && respuesta != 'N' && respuesta != 'n'){
	        
			printf("Introduzca una respuesta valida: ");
	        fflush(stdin);
			scanf(" %c", &respuesta);
	    }
	    
		if(respuesta == 'S' || respuesta == 's'){
			for (int i = id; i < provs.tam - 1; i++) {				// Desplazamos la posicion de los usuarios en el vector
				provs.usuarios[i] = provs.usuarios[i + 1];
				provs.usuarios[i].Id_empresa = i;				// Reasignamos el identificador de cada usuario
			}
			
			provs.tam--;
			provs.usuarios = realloc(provs.usuarios, provs.tam * sizeof(admin_prov));
			
			if (provs.usuarios == NULL) {
				printf("\nError en la reasignación de datos.");
	        	getchar();
	        	exit(33);
			}
			
	        guardar_adminprov(provs);                        		// Guardamos el cambio en el fichero AdminProv.txt
	
	        printf("Operación realizada con éxito.\n");
		}
		else
			printf("Se ha cancelado la operación.\n");
	}
	else
		printf("Error: operación no permitida. Contacte con un administrador.\n");	
	
	Sleep(2000);
	
	return provs;
}



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de proveedores / administradores) ya rellena, y la 
// ID del proveedor a modificar.
//Postcondición: Devuelve la estructura de tipo admin_prov_vect con el proveedor / administrador de identificador indicado, habiendo  
// guardado el cambio en AdminProv.txt
admin_prov_vect modificar_prov(admin_prov_vect provs, int id){
	int op = -1;
	
	do{
		
		clear();
		
		printf("	############################\n");
		printf("	## INFORMACION DE USUARIO ##\n");
		printf("	############################\n");
		
		printf("\n	EMPRESA: %s\n", provs.usuarios[id].Nombre);
		printf("	EMAIL: %s\n", provs.usuarios[id].email);	
		printf("	PRIVILEGIOS: %s\n\n", provs.usuarios[id].Perfil_usuario);	
		
		printf("Desea hacer algun cambio?\n\n <1> Cambiar empresa asociada.\n <2> Cambiar email de usuario.\n <3> Cambiar contrasena.\n \n <0> Volver.\n Seleccione una opcion: ");
		if(scanf("%i",&op)!=1){
			fflush(stdin);
			printf("\nError: introduzca una entrada válida.");
			Sleep(2000);
			op=-1;
		}
		else{
			switch(op){
				case 1: prov_nombre(provs, id); break;
				case 2: prov_email(provs, id); break;
				case 3: prov_contra(provs, id); break;
				//case 4: prov_privi(provs, id); break;
				case 0: break;
				default: break;
			}
		}
	}while(op != 0);
		
	guardar_adminprov(provs);
	
	return provs;
}

// ###################### SUBFUNCIONES DE GESTIÓN DE PROVEEDORES ######################

//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de proveedores / administradores) ya rellena, y la 
// ID del proveedor a registrar.
//Postcondición: No devuelve nada, pero modifica el proveedor con el identificador indicado, habiendo asignado el nombre de la empresa a su cuenta.
void prov_nombre(admin_prov_vect provs, int id){
	char empresa[21];
	
	do{
		printf("\n	<1> Empresa a la que pertenece: ");
		fflush(stdin);
		fgets(empresa, sizeof(empresa), stdin);
		terminador_cad(empresa);
	}while(strlen(empresa) == 0);
	
	strcpy(provs.usuarios[id].Nombre, empresa);

}

//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de proveedores / administradores) ya rellena, y la 
// ID del proveedor a registrar.
//Postcondición: No devuelve nada, pero modifica el proveedor con el identificador indicado, habiendo asignado el email de la empresa a su cuenta.
void prov_email(admin_prov_vect provs, int id){
	char email[31 - strlen(provs.usuarios[id].Nombre) - 1], prefijo[strlen(provs.usuarios[id].Nombre) + 1], email_final[31];
	strcpy(prefijo, provs.usuarios[id].Nombre);
	mayus_minus(prefijo);
	
	do{
		printf("\n	<2> Email de proveedor: nuevo_email@%s.com\n	    nuevo_email: ", prefijo);
		fflush(stdin);
		fgets(email, sizeof(email), stdin);
		terminador_cad(email);		
	}while(strlen(email) == 0);
	
	strcpy(email_final, email);
	strcat(email_final, "@");
	strcat(email_final, prefijo);
	strcat(email_final, ".com");
	
	strcpy(provs.usuarios[id].email, email_final);

}

//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de proveedores / administradores) ya rellena, y la 
// ID del proveedor a registrar.
//Postcondición: No devuelve nada, pero modifica el proveedor con el identificador indicado, habiendo asignado una contraseña a su cuenta.
void prov_contra(admin_prov_vect provs, int id){
	char contra[16], contra_rep[16];
	int contra_valida = 0;
	
	printf("\n	<3> Contraseña: ");
	fflush(stdin);
	fgets(contra, sizeof(contra), stdin);
	
	printf("\n	Repita la contraseña: ");
	fflush(stdin);
	fgets(contra_rep, sizeof(contra_rep), stdin);
	
	terminador_cad(contra);
	terminador_cad(contra_rep);
	
	if(strcmp(contra, contra_rep) == 0)
		contra_valida = 1;
	
	while(!contra_valida || strlen(contra) == 0){
		
		contra_valida = 0;
		
		printf("\n	Contrasenas dispares. Contrasena: ");
		fflush(stdin);
		fgets(contra, sizeof(contra), stdin);
	
		printf("\n	Repita la contraseña: ");
		fflush(stdin);
		fgets(contra_rep, sizeof(contra_rep), stdin);
	
		terminador_cad(contra);
		terminador_cad(contra_rep);
	
		if(strcmp(contra, contra_rep) == 0)
			contra_valida = 1;
	}
	
	strcpy(provs.usuarios[id].Contrasena, contra);
	
}

//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de proveedores / administradores) ya rellena, y la 
// ID del proveedor a registrar.
//Postcondición: No devuelve nada, pero guarda el proveedor de identificador indicado, habiendo  
// cambiado sus privilegios.
/*void prov_privi(admin_prov_vect provs, int id){
	char prov[] = "proveedor",
		 admin[] = "administrador";
	int op = -1;
	
	printf("\n <4> Indique los privilegios que desea dar al usuario:\n {1} Administrador.\n {2} Proveedor.\n Elija: ");
	
	do{
		if(scanf("%i",&op)!=1){
			fflush(stdin);
			printf("\nError: introduzca una entrada válida.");
			Sleep(2000);
			op=-1;
		}
		else{
			switch(op){
				case 1: strcpy(provs.usuarios[id].Perfil_usuario, admin); break;
				case 2: strcpy(provs.usuarios[id].Perfil_usuario, prov); break;
				case 0: break;
				default: break;
			}
		}
	}while(op != 0);
	
}*/

//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y una cadena a comparar.
//Postcondición: Devuelve la ID de empresa del proveedor dado de alta en la plataforma según la empresa a la que pertenezca.
int buscar_id_prov(admin_prov_vect provs, char* empresa){
	int i, id, val = 0;
	
	for(int i = 1; i < provs.tam; i++){
		if(strcmp(empresa, provs.usuarios[i].Nombre) == 0 && id < provs.usuarios[i].Id_empresa){
			id = provs.usuarios[i].Id_empresa;
			val = 1;
		}	
	}
	
	if(!val){
		for(int i = 1; i < provs.tam; i++){
			if(id < provs.usuarios[i].Id_empresa)
				id = provs.usuarios[i].Id_empresa;	
		}
	}
	id++;	
	return id;
}

//Precondición: Recibe la ID del proveedor para asegurar que sólo ve sus pedidos.
//Postcondición: No devuelve nada. Muestra por pantalla todos los pedidos asociados a productos de su empresa.
void listar_pedidos_prov(int id){
	produ_vect prods = cargar_productos();
	pedidos pedidos = cargar_pedidos();
	prod_pedidos prods_pedidos = cargar_prod_pedidos();
	int i;
	
	printf("+-------------------+\n");
	printf("| PEDIDOS ASOCIADOS |\n");
	printf("+-------------------+--------------------+-----------+--------------------------------------+\n");
	printf("| PRODUCTO          | UNIDADES PEDIDAS   | IMPORTE   | ESTADO             | PEDIDO ASOCIADO |");
	for(i = 0; i < prods_pedidos.lon; i++){
		if(id == prods.produ[prods_pedidos.prod_pedidos[i].id_prod].id_gestor)
			printf("| %-20s | %-20d | %-11d | %-20s | %-20d |\n", prods.produ[ prods_pedidos.prod_pedidos[i].id_prod ].nombre, prods_pedidos.prod_pedidos[i].num_unid, prods_pedidos.prod_pedidos[i].importe, prods_pedidos.prod_pedidos[i].estado, prods_pedidos.prod_pedidos[i].id_pedido);
	}
	printf("+-------------------+--------------------+-----------+--------------------------------------+\n");	
	printf("Presione [enter] para volver...");
	getchar();
	
}

//Precondición: No recibe nada.
//Postcondición: No devuelve nada. Cambia el estado de un pedido elegido dentro de la propia función, y guarda los cambios.
void cambiar_estado_pedido(){
	int op = -1, id;
	pedidos pedidos = cargar_pedidos();
	prod_pedidos prods_pedidos = cargar_prod_pedidos();
	produ_vect prods = cargar_productos();
	
	do{
		printf("Indique la ID del pedido: ");
	}while(scanf("%i", &id) != 1);
	
	for(int i = 0; i < prods_pedidos.lon; i++){
		if(id == prods_pedidos.prod_pedidos[i].id_pedido){
			
			do{
				printf("\n\n Producto: %04d - %s.\nElija un estado para continuar:\n\n <1> En preparación.\n <2> Enviado.\n <0> Cancelar\n Elija una opción: ", prods_pedidos.prod_pedidos[i].id_prod, prods.produ[ prods_pedidos.prod_pedidos[i].id_prod ].nombre);
				if(scanf("%i",&op)!=1){
					fflush(stdin);
					printf("\nError: introduzca una entrada válida.");
					Sleep(2000);
					op=-1;
				}
				else{
					switch(op){
						case 1: strcpy(prods_pedidos.prod_pedidos[i].estado, "enPreparación\0"); break;
						case 2: strcpy(prods_pedidos.prod_pedidos[i].estado, "enviado\0"); break;
						case 0: break;
						default: break;
					}
				}
			}while(op!=0);
			
			i = pedidos.lon;
			id = -1;
		}		
	}
	if(id != -1)
		printf("\nNo se ha podido encontrar el pedido solicitado.");
	else
		printf("\nCambios realizados satisfactoriamente.");
	Sleep(2000);
}

//Precondición: No recibe nada.
//Postcondición: Devuelve 0 siempre por peculiaridades del código, que permite salir en cualquier momento.
int modificar_asig_transport(){
	pedidos pedidos = cargar_pedidos();
	prod_pedidos prods_pedidos = cargar_prod_pedidos();
	transport_vect transports = cargar_transportistas();
	produ_vect prods = cargar_productos();
	int id, id_p, id_t, encontrado_ped = 0, encontrado_prod = 0, encontrado_t = 0;
	
	do{
		printf("Indique la ID del pedido, o pulse 0 para volver: ");
	}while(scanf("%i", &id) != 1);
	
	if(id == 0)
		return 0;
		
	for(int i = 0; i < pedidos.lon; i++){																						// Buscamos el pedido...
		if(id == pedidos.pedidos[i].id_pedido){
			encontrado_ped = 1;				
			i = pedidos.lon;	
		}
	}
	
	if(!encontrado_ped)																											// Si no se encuentra el pedido...
		printf("\nNo se ha podido encontrar el pedido y/o el producto solicitado.");
	else{																														// Si se encuentra...	
		do{
			do{
				printf("\nAhora indique la ID del producto dentro del pedido, o pulse 0 si desea salir: ");
			}while(scanf("%i", &id_p) != 1);
			
			if(id_p == 0)
				return 0;
			for(int i = 0; i < prods_pedidos.lon; i++){	
				if(id_p == prods_pedidos.prod_pedidos[i].id_prod && id == pedidos.pedidos[i].id_pedido){								// Buscamos el producto dentro del pedido...
					encontrado_prod = 1;
					if(strcmp(prods_pedidos.prod_pedidos[i].estado, "enPreparación") == 0) 												// Si se encuentra en preparación...
						printf("\n{Pedido %d} El producto [%04d - %s] se encuentra en preparación, no es posible asignar un transportista todavia.", id, prods_pedidos.prod_pedidos[i].id_prod, prods.produ[ prods_pedidos.prod_pedidos[i].id_prod ].nombre);
					else{
						do{																												// Si no...
							do{
								printf("Indique la ID del transportista a asociar, o pulse 0 para salir: ");
							}while(scanf("%i", &id_t) != 1);
							
							if(id_t == 0)
								return 0;
								
							for(int j = 0; j < transports.tam; j++){																	// Buscamos al transportista en el vector.
								if(id == transports.transportistas[j].Id_transp){														// Si se encuentra...
									encontrado_t = 1;
									prods_pedidos.prod_pedidos[i].id_transp = id;														
								}
							}
							
							if(!encontrado_t)																							// Si no se encuentra...
								printf("\nNo se ha podido encontrar el transportista solicitado. Indique otro.");
							else
								printf("\nTransportista asignado.\n\n");
						}while(!encontrado_t);		
					}
				}
			}
			if(!encontrado_prod)
				printf("\nNo se ha podido encontrar el producto en el sistema de pedidos. Intentelo de nuevo.");
		}while(!encontrado_prod);
	}
	return 0;
}



// FUNCIONES PARA LA GESTIÓN DE TRANSPORTISTAS



//Precondición: Recibe una estructura de tipo transport_vect (el vector de transportistas) ya rellena.
//Postcondición: No devuelve nada. Se habrá mostrado por pantalla todos los transportistas del sistema, menos el por defecto.
void listar_transport(transport_vect transports){
	
	clear();
	
	printf("+------------------------------------------+\n");
	printf("| TRANSPORTISTAS REGISTRADOS EN EL SISTEMA |\n");
	printf("+----------------------+-------------------+------------+----------------------+-----------------------+\n");
	printf("| NOMBRE               | CORREO                         | EMPRESA              |  CIUDAD               |\n");
	printf("+----------------------+--------------------------------+----------------------+-----------------------+\n");
	for(int i = 1; i < transports.tam; i++)
		printf("| %-20s | %-30s | %-20s | %-21s |\n", transports.transportistas[i].Nombre, 
													  transports.transportistas[i].email, transports.transportistas[i].Nom_Emp, 
													  transports.transportistas[i].Ciudad);
	printf("+----------------------+--------------------------------+----------------------+-----------------------+\n");
	printf("Presione [enter] para volver...");
	getchar();

}



//Precondición: Recibe una estructura de tipo transport_vect (el vector de transportistas) ya rellena.
//Postcondición: Devuelve la ID del usuario buscado, o -1 si se cancela la búsqueda.
int buscar_transport(transport_vect transports){
	int pos = -2, opt = -1;             // Elijo -2 como pos predeter. ya que -1 es para cancelar la busqueda
	
	clear();
    
	while (pos == -2){    				// Solo va a salir del bucle cuando se selecciona la posicion de un cliente valido
        clear();
        printf("Busqueda de transportistas. Seleccione un metodo de busqueda para continuar.\n");
        printf("¿Como desea buscar?\n");
        printf("1. Por nombre.\n");
        printf("2. Por email.\n");
        printf("3. Por ciudad de reparto.\n");
        printf("0. Cancelar.\n");
        
        while(opt > 3 || opt < 0){
            if(scanf("%i",&opt) != 1){
				fflush(stdin);
				printf("\nError: introduzca una entrada válida.");
				Sleep(2000);
				opt=-1;
			}
			else{
					switch (opt)
	            {
	            case 1:
	                pos = buscar_transport_tipo(transports, pos, 1);
	                break;
	            case 2:
	                pos = buscar_transport_tipo(transports, pos, 2);
	                break; 
	            case 3:
	            	pos = buscar_transport_tipo(transports, pos, 3);
	            	break;
	            case 0:
	                pos = -1;
	                printf("Se ha cancelado la busqueda.\n");
					break;
	            default:
	                printf("Introduzca una opcion valida: ");
	                break;
	            }
			}
        }
    }
	Sleep(2000);
    return pos;
}



//Precondición: Recibe una estructura de tipo transport_vect (el vector de transportistas) ya rellena y dos enteros (posición a tratar y
//tipo de búsqueda.
//Postcondición: Devuelve la ID del usuario buscado, o -1 si se cancela la búsqueda.
int buscar_transport_tipo(transport_vect transports, int pos, int tipo){
	int len = 0, i, opt = -1;
    char cad_busq[35]; 
    int n_coinc = 0;                      				// Contador de coincidencias encontradas
    int *vect_coinc;                    				// Vector de guardado de IDs con coincidencias
	
	clear();
	
    vect_coinc = (int*)malloc(1*sizeof(int)); 
    do{
    	printf("Por favor, introduzca su busqueda: ");
	    fflush(stdin);
	    fgets(cad_busq, sizeof(cad_busq), stdin);         	// Cadena por la que se va a buscar al proveedor
	    fflush(stdin);
	    terminador_cad(cad_busq);    	
	}while(strlen(cad_busq) == 0);
	
    len = strlen(cad_busq);
    if(tipo == 1){
        if(len > 21)
            len = 21;

        for(i = 1; i < transports.tam; i++){           		// Búsqueda por nombre de empresa asociada.
            if(strncmp(cad_busq, transports.transportistas[i].Nombre, len) == 0){
                printf("<%d> %s | %s | %s | %s\n", n_coinc + 1,  transports.transportistas[i].Nombre, transports.transportistas[i].email, transports.transportistas[i].Nom_Emp, transports.transportistas[i].Ciudad);
                n_coinc++;
                vect_coinc = (int*)realloc(vect_coinc, n_coinc*sizeof(int));
                vect_coinc[n_coinc-1] = transports.transportistas[i].Id_transp;
                }
        }
    }else if(tipo == 2){
        if(len > 31)
            len = 31;
        for(i = 1; i < transports.tam; i++){          		// Búsqueda por email.
            if(strncmp(cad_busq, transports.transportistas[i].email, len) == 0){
                printf("<%d> %s | %s | %s | %s\n",n_coinc+1, transports.transportistas[i].Nombre, transports.transportistas[i].email, transports.transportistas[i].Nom_Emp, transports.transportistas[i].Ciudad);
                n_coinc++;
                vect_coinc = (int*)realloc(vect_coinc, n_coinc*sizeof(int));
                vect_coinc[n_coinc-1] = transports.transportistas[i].Id_transp;
                }
        }
    }else if(tipo == 3){
        if(len > 21)
            len = 21;
        for(i = 1; i < transports.tam; i++){          		// Búsqueda por ciudad de reparto.
            if(strncmp(cad_busq, transports.transportistas[i].Ciudad, len) == 0){
                printf("<%d> %s | %s | %s | %s\n",n_coinc+1, transports.transportistas[i].Nombre, transports.transportistas[i].email, transports.transportistas[i].Nom_Emp, transports.transportistas[i].Ciudad);
                n_coinc++;
                vect_coinc = (int*)realloc(vect_coinc, n_coinc*sizeof(int));
                vect_coinc[n_coinc-1] = transports.transportistas[i].Id_transp;
                }
        }
    }else{
        return -1;      									// Si hay fallo en el tipo, volvemos al menú anterior (buscar_prov).
    }
    

    if(n_coinc == 0){
        printf("No se ha encontrado ninguna coincidencia.\n");
        Sleep(2000);
        return -1;
    }

    printf("\nIntroduzca el usuario que desea seleccionar, o introduzca '0' para salir.\n");   //Elegir una opcion de coincidencia
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



//Precondición: Recibe una estructura de tipo transport_vect (el vector de transportistas) ya rellena.
//Postcondición: Devuelve la estructura de tipo transport_vect con un nuevo transportista dado de alta, y habiendo guardado el 
// cambio en Transportistas.txt
transport_vect alta_transport(transport_vect transports){
	int nueva_id = transports.tam;
	
	clear();
	
	printf("\n	##################################\n");
    printf("	## SERVICIO DE ALTAS DE USUARIO ##\n");
    printf("	##################################\n");
    
    printf("\nIntroduzca los datos del nuevo usuario del sistema:\n\n");
	
	transports.transportistas = realloc(transports.transportistas, (nueva_id + 1) * sizeof(transport));
	transports.tam++;
	
	if (transports.transportistas == NULL){
        printf("No se pudo asignar la estructura de transportistas.\n");
        getchar();
        exit(33);
    }
    
    transports.transportistas[nueva_id].Id_transp = nueva_id;
    
    t_nombre(transports, nueva_id);
    t_empresa(transports, nueva_id);
    t_email(transports, nueva_id);    
    t_ciudad(transports, nueva_id);
    t_contra(transports, nueva_id);
    
	guardar_transportista(transports);
    
    printf("\nTransportista %04d dado de alta correctamente.\n", nueva_id);
    
    Sleep(2000);
    
	return transports;
}



//Precondición: Recibe una estructura de tipo transport_vect (el vector de transportistas) ya rellena, y la ID del transportista a eliminar.
//Postcondición: Devuelve la estructura de tipo transport_vect sin el transportista de identificador indicado, y habiendo guardado el 
// cambio en Transportistas.txt
transport_vect baja_transport(transport_vect transports, int id){
	char respuesta;
	
	printf("Esta a punto de eliminar al transportista %s del sistema. Desea continuar? [s/n]: ", transports.transportistas[id].Nombre);
	fflush(stdin);
	scanf("%c", &respuesta);
	
	while (respuesta != 'S' && respuesta != 's' && respuesta != 'N' && respuesta != 'n'){
        
		printf("Introduzca una respuesta valida: ");
        fflush(stdin);
		scanf(" %c", &respuesta);
    }
    
	if(respuesta == 'S' || respuesta == 's'){
		for (int i = id; i < transports.tam - 1; i++) {							// Desplazamos la posicion de los usuarios en el vector
			transports.transportistas[i] = transports.transportistas[i + 1];
			transports.transportistas[i].Id_transp = i;						// Reasignamos el identificador de cada usuario
		}
		
		transports.tam--;
		transports.transportistas = realloc(transports.transportistas, transports.tam * sizeof(transport));
		
		if (transports.transportistas == NULL) {
			printf("\nError en la reasignación de datos.");
        	getchar();
        	exit(33);
		}
		
        guardar_transportista(transports);                        				// Guardamos el cambio en el fichero Transportistas.txt

        printf("Operación realizada con éxito.\n");
	}
	else
		printf("Se ha cancelado la operación.\n");
	
	Sleep(2000);
	
	return transports;
}



//Precondición: Recibe una estructura de tipo transport_vect (el vector de transportistas) ya rellena, y la ID del transportista a modificar.
//Postcondición: Devuelve la estructura de tipo transport_vect con el transportista de identificador indicado, habiendo guardado cualquier 
// cambio en su cuenta.
transport_vect modificar_transport(transport_vect transports, int id){
	int op = -1;
	
	do{
		
		clear();
		
		printf("	############################\n");
		printf("	## INFORMACION DE USUARIO ##\n");
		printf("	############################\n");
		
		printf("\n	NOMBRE: %s\n",transports.transportistas[id].Nombre);
		printf("	EMPRESA: %s\n", transports.transportistas[id].Nom_Emp);
		printf("	EMAIL: %s\n", transports.transportistas[id].email);	
		printf("	CIUDAD: %s\n\n", transports.transportistas[id].Ciudad);	
		
		printf("Desea hacer algun cambio?\n\n <1> Cambiar nombre.\n <2> Cambiar empresa asociada.\n <3> Cambiar email de usuario.\n <4> Cambiar contrasena.\n <5> Cambiar ciudad de reparto.\n <0> Volver.\n Seleccione una opcion: ");
		if(scanf("%i",&op)!=1){
			fflush(stdin);
			printf("\nError: introduzca una entrada válida.");
			Sleep(2000);
			op=-1;
		}
		else{
			switch(op){
				case 1: t_nombre(transports, id); break;
				case 2: t_empresa(transports, id); break;
				case 3: t_email(transports, id); break;
				case 4: t_contra(transports, id); break;
				case 5: t_ciudad(transports, id); break;
				case 0: break;
				default: break;
			}
		}
	}while(op != 0);
	
	guardar_transportista(transports);
	
	return transports;
}

// ###################### SUBFUNCIONES DE GESTIÓN DE TRANSPORTISTAS ######################

//Precondición: Recibe una estructura de tipo transport_vect (el vector de transportistas) ya rellena, y la ID del transportista a registrar.
//Postcondición: No devuelve nada, pero modifica el transportista con el identificador indicado, habiendo asignado un nombre a su cuenta.
void t_nombre(transport_vect transports, int id){
	char nombre[21];
	
	do{	
		printf("\n	<1> Nombre completo: ");
		fflush(stdin);
		fgets(nombre, sizeof(nombre), stdin);
		terminador_cad(nombre);
	}while(strlen(nombre) == 0);
	
	strcpy(transports.transportistas[id].Nombre, nombre);

}

//Precondición: Recibe una estructura de tipo transport_vect (el vector de transportistas) ya rellena, y la ID del transportista a registrar.
//Postcondición: No devuelve nada, pero modifica el transportista con el identificador indicado, habiendo asignado un email a su cuenta.
void t_email(transport_vect transports, int id){

	char email[31 - strlen(transports.transportistas[id].Nom_Emp) - 1], prefijo[strlen(transports.transportistas[id].Nom_Emp) + 1];
	strcpy(prefijo, transports.transportistas[id].Nom_Emp);
	mayus_minus(prefijo);
	
	do{
		printf("\n	<2> Email de transportista: nuevo_email@%s.com\n	    nuevo_email: ", prefijo);
		fflush(stdin);
		fgets(email, sizeof(email), stdin);
		terminador_cad(email);		
	}while(strlen(email) == 0);

	sprintf(transports.transportistas[id].email, "%s@%s.com", email, prefijo);

}

//Precondición: Recibe una estructura de tipo transport_vect (el vector de transportistas) ya rellena, y la ID del transportista a registrar.
//Postcondición: No devuelve nada, pero modifica el transportista con el identificador indicado, habiendo asignado una contraseña a su cuenta.
void t_contra(transport_vect transports, int id){
	char contra[16], contra_rep[16];
	int contra_valida = 0;
	
	do{
		printf("\n	<5> Contraseña: ");
		fflush(stdin);
		fgets(contra, sizeof(contra), stdin);
		
		printf("\n	Repita la contraseña: ");
		fflush(stdin);
		fgets(contra_rep, sizeof(contra_rep), stdin);
		
		terminador_cad(contra);
		terminador_cad(contra_rep);
		
		if(strcmp(contra, contra_rep) == 0)
			contra_valida = 1;
		
		while(!contra_valida){
			
			contra_valida = 0;
			
			printf("\n	Contrasenas dispares. Contrasena: ");
			fflush(stdin);
			fgets(contra, sizeof(contra), stdin);
		
			printf("\n	Repita la contraseña: ");
			fflush(stdin);
			fgets(contra_rep, sizeof(contra_rep), stdin);
		
			terminador_cad(contra);
			terminador_cad(contra_rep);
		
			if(strcmp(contra, contra_rep) == 0)
				contra_valida = 1;
		}
	}while(strlen(contra) ==  0);
	
	strcpy(transports.transportistas[id].Contrasena, contra);

}

//Precondición: Recibe una estructura de tipo transport_vect (el vector de transportistas) ya rellena, y la ID del transportista a registrar.
//Postcondición: No devuelve nada, pero modifica el transportista con el identificador indicado, habiendo asignado una empresa a su cuenta.
void t_empresa(transport_vect transports, int id){
	char empresa[21];
	
	do{
		printf("\n	<3> Empresa a la que pertenece: ");
		fflush(stdin);
		fgets(empresa, sizeof(empresa), stdin);
		terminador_cad(empresa);
	}while(strlen(empresa) == 0);
	
	strcpy(transports.transportistas[id].Nom_Emp, empresa);
	
}

//Precondición: Recibe una estructura de tipo transport_vect (el vector de transportistas) ya rellena, y la ID del transportista a registrar.
//Postcondición: No devuelve nada, pero modifica el transportista con identificador indicado, habiendo asignado una ciudad a su cuenta.
void t_ciudad(transport_vect transports, int id){
	char ciudad[21];
	
	do{
		printf("\n	<4> Ciudad en la que trabaja: ");
		fflush(stdin);
		fgets(ciudad, sizeof(ciudad), stdin);
		terminador_cad(ciudad);
	}while(strlen(ciudad) == 0);
	
	strcpy(transports.transportistas[id].Ciudad, ciudad);
	
}



// FUNCIONES DE LECTURA DE FICHEROS



//Precondición: No recibe nada.
//Postcondición: Devuelve una variable de tipo admin_prov_vect con la información de cada usuario (proveedor o administrador) almacenados 
// en AdminProv.txt.
admin_prov_vect cargar_adminprov(){
	
	admin_prov_vect adminprov_sistema;
	FILE *f_AdminProv;																							// Puntero al fichero a leer.
	char ruta[] = ".\\data\\AdminProv.txt";																		// Ruta del fichero a leer.
	char linea[LONG_MAX_ADMINPROV];																				// Línea actual del fichero. Longitud máxima de una línea 86 caracteres.
	char tipo_usuario[14];																						// Cadena auxiliar a convertir.
	int i = 0, m; 

	if((f_AdminProv = fopen(ruta, "a+")) == NULL){																// w+ permite leer y escribir, y crea el archivo si no existe.
		printf("\nError al abrir el fichero AdminProv.txt en cargar_adminprov. Creando uno nuevo...\n");
		getchar();                     	
	}	

	//COMPROBACION FICHERO VACIO//
	char verif = fgetc(f_AdminProv);
	if (verif == EOF){
		fprintf(f_AdminProv,"0000-ESIZON-adminadmin@esizon.com-admin000-administrador\n");
	}

	rewind(f_AdminProv);																								
	adminprov_sistema.tam = 0;
	while(fgets(linea, sizeof(linea), f_AdminProv) != NULL)														// Contamos el número de usuarios en el fichero...
		adminprov_sistema.tam++;
//	printf("\nCarga completada.\nUsuarios almacenados en AdminProv.txt: %d \n", adminprov_sistema.tam);
	adminprov_sistema.usuarios = (admin_prov*)malloc((adminprov_sistema.tam + 1) * sizeof(admin_prov));			// ... y reservamos memoria para el vector (más uno por si se necesita añadir algún usuario).
	rewind(f_AdminProv);																								
	
	while((fgets(linea, sizeof(linea), f_AdminProv) != NULL) ){	
		if((m = sscanf(linea, "%d-%20[^-]-%30[^-]-%15[^-]-%13[^\n]\n", &adminprov_sistema.usuarios[i].Id_empresa, adminprov_sistema.usuarios[i].Nombre, adminprov_sistema.usuarios[i].email, adminprov_sistema.usuarios[i].Contrasena, adminprov_sistema.usuarios[i].Perfil_usuario)) == 5){
			i++;		
		}
		else{
			printf("\nError leyendo datos del fichero AdminProv.txt en cargar_adminprov. Línea: %d", i + 1);
			getchar();	
			exit(33);				
		}
	}			
		                                    
	fclose(f_AdminProv);  
	Sleep(2000);
	return adminprov_sistema;                             	                            
}



//Precondición: No recibe nada.
//Postcondición: Devuelve una variable de tipo transport_vect con la información de cada transportista almacenada en Transportistas.txt.
transport_vect cargar_transportistas(){
	
	transport_vect transport_sistema;
	FILE *Transportistas;																						// Puntero al fichero a leer.
	char ruta[] = "./data/Transportistas.txt";																	// Ruta del fichero a leer.
	char linea[LONG_MAX_TRANSPORT];																				// Línea actual del fichero. Longitud máxima de una línea 113 caracteres.
	int i = 0, m;

	if((Transportistas = fopen(ruta, "a+")) == NULL){															// w+ permite leer y escribir, y crea el archivo si no existe.
		printf("\nError al abrir el fichero Transportistas.txt en cargar_transportistas. Creando uno nuevo...\n");
		getchar();
	}
	//COMPROBACION FICHERO VACIO//
	char verif = fgetc(Transportistas);
	if (verif == EOF){
		fprintf(Transportistas, "0000-defaultnombre-defaultemail-defaultcontra-defaultempresa-defaultciudad\n");
	}                                                                                                        
	
	rewind(Transportistas);
	transport_sistema.tam = 0;
	while(fgets(linea, sizeof(linea), Transportistas) != NULL)													// Contamos el número de usuarios en el fichero...
    	transport_sistema.tam++;
//  printf("\nCarga completada.\nTransportistas almacenados en Transportistas.txt: %d \n", transport_sistema.tam);
 	transport_sistema.transportistas = (transport*)malloc((transport_sistema.tam + 1) * sizeof(transport));		// ... y reservamos memoria para el vector (más uno por si se necesita añadir algún usuario).
 	rewind(Transportistas);																							
    
	while(fgets(linea, sizeof(linea), Transportistas) != NULL){	
		if((m = sscanf(linea, "%d-%20[^-]-%30[^-]-%15[^-]-%20[^-]-%20[^\n]\n", &transport_sistema.transportistas[i].Id_transp, transport_sistema.transportistas[i].Nombre, transport_sistema.transportistas[i].email, transport_sistema.transportistas[i].Contrasena, transport_sistema.transportistas[i].Nom_Emp, transport_sistema.transportistas[i].Ciudad)) == 6)
			i++;		
		else{
			printf("\nError leyendo datos del fichero Transportistas.txt en cargar_transportistas. Línea: %d\n", i);
			getchar();	
			exit(33);				
		}		
	}	
		                                    
	fclose(Transportistas);
	Sleep(2000); 
	return transport_sistema;  
}



//	FUNCIONES DE VOLCADO EN FICHEROS



//Precondición: Recibe una estructura de tipo admin_prov con datos coherentes almacenados.
//Postcondición: Guarda en AdminProv.txt los datos del vector de estructuras recibido.
void guardar_adminprov(admin_prov_vect usuarios){
	
	FILE *AdminProv;																							// Puntero al fichero a leer.
	char ruta[] = ".\\data\\AdminProv.txt";																		// Ruta del fichero a leer.
	char linea[LONG_MAX_ADMINPROV];																				// Línea actual del fichero. Longitud máxima de una línea 86 caracteres.
	char aux[14];
	
	AdminProv = fopen(ruta, "w");
	
	for(int i = 0; i < usuarios.tam; i++)
		fprintf(AdminProv, "%04d-%s-%s-%s-%s\n", usuarios.usuarios[i].Id_empresa, usuarios.usuarios[i].Nombre, usuarios.usuarios[i].email, usuarios.usuarios[i].Contrasena, usuarios.usuarios[i].Perfil_usuario);
	fclose(AdminProv);
}



//Precondición: Recibe una estructura de tipo transport con datos coherentes almacenados.
//Postcondición: Guarda en Transportistas.txt los datos del vector de estructuras recibido.
void guardar_transportista(transport_vect transportistas){
	
	FILE *Transportistas;																						// Puntero al fichero a leer.
	char ruta[] = ".\\data\\Transportistas.txt";																// Ruta del fichero a leer.
	char linea[LONG_MAX_TRANSPORT];																				// Línea actual del fichero. Longitud máxima de una línea 113 caracteres.

	Transportistas = fopen(ruta, "w");
	
	for(int i = 0; i < transportistas.tam; i++)
		fprintf(Transportistas, "%04d-%s-%s-%s-%s-%s\n", transportistas.transportistas[i].Id_transp, transportistas.transportistas[i].Nombre, transportistas.transportistas[i].email, transportistas.transportistas[i].Contrasena, transportistas.transportistas[i].Nom_Emp, transportistas.transportistas[i].Ciudad);
	fclose(Transportistas);
}



//	UTILIDADES VARIAS



//Precondición: No recibe nada.
//Postcondición: Devuelve el numero de lineas que contiene AdminProv.txt.
int longitud_vector_adminprov(){
	
	FILE *Admin_Prov_txt;	
	char aux[LONG_MAX_ADMINPROV];
	int i = 0;
	
	if((Admin_Prov_txt = fopen("..\\data\\AdminProv.txt", "r")) == NULL){
        printf("\nError en la apertura de AdminProv.txt para longitud_vector_adminprov.\n");
        Sleep(2000);
	}  
	else{
		while(fgets(aux, sizeof(aux), Admin_Prov_txt)){
        	i++;
    	}
	}
	
    fclose(Admin_Prov_txt);
    
    return i;
}



//Precondición: No recibe nada.
//Postcondición: Devuelve el numero de lineas que contiene Transportistas.txt.
int longitud_vector_transportistas(){
	
	FILE *Transportistas_txt;	
	char aux[LONG_MAX_TRANSPORT];
	int i = 0;
	
	if((Transportistas_txt = fopen("..\\ESIZON-main\\data\\Transportistas.txt", "r+")) == NULL) {
		printf("\nError en la apertura de Transportistas.txt para longitud_vector_transportistas.\n");
		Sleep(2000);
	}  
	else{
		while(fgets(aux, sizeof(aux), Transportistas_txt)){
        	i++;
    	}
	}
	
    fclose(Transportistas_txt);
    
    return i;	
}



//Precondición: Recibe una cadena de caracteres, en principio con caracteres en mayúsculas.
//Postcondición: Devuelve la misma cadena dada, pero con todas las letras en minúscula.
char* mayus_minus(char* cad){
	for(int i = 0; i < strlen(cad); i++)
		cad[i] = tolower(cad[i]);
	return cad;
}

/*

//Precondición: Recibe una cadena que necesite ser acortada (no nula, con algún carácter ' ' al final de ella).
//Postcondición: No devuelve nada, sustituye el primer carácter ' ' que encuentre en la cadena por el carácter terminador '\0'.
void terminador_cad(char cadena[]){
	int i, len = strlen(cadena);
	for(i = 0; i < len; i++){
    	if(cadena[i] == '\n'){
     		cadena[i] = '\0';
			i = len;   		
		}
	}
}
*/