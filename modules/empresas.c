#include "complementos.h"
#include "empresas.h"

//	MENÚS DE PROVEEDOR Y TRANSPORTISTA


//Precondición: Recibe una estructura de tipo admin_prov (en suma, recibe un proveedor).
//Postcondición: El usuario habrá realizado las tareas necesarias de gestión en la plataforma (ver y modificar perfil, gestionar productos, pedidos). No devuelve nada.
void menu_prov(admin_prov prov){
	
	int op = -1, i = 0;
	
	do{
		clear();
		
		printf("	#######################\n");
		printf("	## MENU DE PROVEEDOR ##\n");
		printf("	#######################\n");
		
		printf("\n	   EMPRESA: %s\n", prov.Nombre);
		
		printf("\nBienvenido, %s - ¿Qué desea hacer hoy?\n\n <1> Ver perfil.\n <2> Ver productos.\n <3> Administrar pedidos\n <0> Volver.\n Elija una opción: ", prov.email);
		if(scanf("%i",&op)!=1){
			fflush(stdin);
			printf("Error: introduzca una entrada válida.");
			op=-1;
		}
		else{
			switch(op){
				case 1: ver_perfil(prov); break;
				case 2: ver_productos(prov); break;
				case 3: ver_pedidos(prov); break;
				case 0: break;
				default: break;
			}
		}
	}while(op!=0);
	
}



//Precondición: Recibe una estructura de tipo transport (en suma, recibe un transportista).
//Postcondición: El usuario habrá realizado las tareas necesarias de gestión en la plataforma (ver y modificar perfil, repartos, retornos). No devuelve nada.
void menu_transport(transport transportista){
	
	int op = -1, i = 0;
	
	do{
		clear();
		
		printf("	###########################\n");
		printf("	## MENU DE TRANSPORTISTA ##\n");
		printf("	###########################\n");
		
		printf("\n	   NOMBRE: %s\n", transportista.Nombre);
		printf("\n	   EMPRESA: %s\n", transportista.Nom_Emp);
		
		printf("\nBienvenido, %s - ¿Qué desea hacer hoy?\n\n <1> Ver perfil.\n <2> Ver repartos asignados.\n <3> Ver retornos.\n <0> Volver.\n Elija una opción: ", transportista.email);
		if(scanf("%i",&op)!=1){
			fflush(stdin);
			printf("Error: introduzca una entrada válida.");
			op=-1;
		}
		else{
			switch(op){
				case 1: ver_perfil_t(transportista); break;
				case 2: break;
				case 3: break;
				case 0: break;
				default: break;
			}
		}
	}while(op!=0);
}



//	FUNCIONES PARA EL MENÚ DE PROVEEDOR



//Precondición: Recibe una estructura de tipo admin_prov (en suma, recibe un usuario, en este caso proveedor).
//Postcondición: El usuario habrá realizado las tareas necesarias de gestión de su cuenta en la plataforma. No devuelve nada.
void ver_perfil(admin_prov usu){

	int op = -1;
	
	do{
		clear();
		
		printf("	############\n");
		printf("	## PERFIL ##\n");
		printf("	############\n");
	
		printf("\nInformación de su perfil:\n ID DEL SISTEMA: %04d\n EMPRESA: %s\n EMAIL: %s\n PRIVILEGIOS: %s\n", usu.Id_empresa, usu.Nombre, usu.email, usu.Perfil_usuario);
		
		printf("\n¿Qué desea hacer?\n <1> Cambiar email.\n <2> Cambiar contraseña.\n <0> Volver.\n Elija una opción: ");
		if(scanf("%i",&op)!=1){
			fflush(stdin);
			printf("Error: introduzca una entrada válida.");
			op=-1;
		}
		else{
			switch(op){
				case 1: cambiar_email(&usu); break;
				case 2: cambiar_contrasena(&usu); break;
				case 0: break;
				default: break;
			}
		}
	}while(op!=0);
}



void ver_productos(admin_prov prov){
	
}



void ver_pedidos(admin_prov prov){
	
}



//Precondición: Recibe un puntero a una estructura de admin_prov.
//Postcondición: No devuelve nada. Se habrá cambiado el email del usuario guardado en el puntero.
void cambiar_email(admin_prov *usu){
	
	char nuevo_email[31];
	printf("\nIngrese el nuevo email: ");
	fflush(stdin);
	fgets(nuevo_email, sizeof(nuevo_email), stdin);
	acortar_cadena(nuevo_email);
	strcpy(usu->email, nuevo_email);
	
}



//Precondición: Recibe un puntero a una estructura de admin_prov.
//Postcondición: No devuelve nada. Se habrá cambiado la contraseña del usuario guardada en el puntero, o no.
void cambiar_contrasena(admin_prov *usu){
	
	char nueva_contra[21], contra_compr[21];									// Cadenas donde guardamos la contraseña nueva, y su repetición.
	int valido = 0;
	
	printf("\nIntroduzca la contrasena actual: ");
	fflush(stdin);
	fgets(contra_compr, sizeof(contra_compr), stdin);
	acortar_cadena(contra_compr);
	if(strcmp(contra_compr, usu->Contrasena) == 0){							
		do{
			printf("\nIndique la nueva contrasena: ");						
			fflush(stdin);
			fgets(nueva_contra, sizeof(nueva_contra), stdin);
			acortar_cadena(nueva_contra);
			printf("\nIndiquela de nuevo de nuevo: ");
			fflush(stdin);
			fgets(contra_compr, sizeof(contra_compr), stdin);	
			acortar_cadena(contra_compr);
			if(strcmp(nueva_contra,contra_compr) == 0)							// Si las contraseñas son iguales (el usuario no se ha equivocado), salimos del bucle.
				valido = 1;
			else	
				printf("Contrasenas distintas, inténtelo de nuevo.");			// Solicitamos la nueva contraseña al usuario mientras no verifique que se repitan.
		}while(valido == 0);
		printf("\nContraseña cambiada satisfactoriamente.");
		strcpy(usu->Contrasena, nueva_contra);
		Sleep(3000);															// Esperamos tres segundos antes de limpiar la pantalla para poder leer el mensaje anterior.
	}else{
		printf("\nContrasena errónea. Pruebe otra vez o contacte con un administrador.\n");
		Sleep(3000);															// Esperamos diez segundos antes de limpiar la pantalla para poder leer el mensaje anterior.		
	}
}



//	FUNCIONES PARA EL MENÚ DE TRANSPORTISTA



//Precondición: Recibe una estructura de tipo transport (en suma, recibe un usuario, en este caso transportista).
//Postcondición: El usuario habrá realizado las tareas necesarias de gestión de su cuenta en la plataforma. No devuelve nada.
void ver_perfil_t(transport usu){

	int op = -1;
		
	do{
		clear();
		
		printf("	############\n");
		printf("	## PERFIL ##\n");
		printf("	############\n");
	
		printf("\nInformación de su perfil:\n ID DEL SISTEMA: %04d\n NOMBRE: %s\n EMAIL: %s\n EMPRESA: %s\n CIUDAD ASIGNADA: %s\n", usu.Id_transp, usu.Nombre, usu.email, usu.Nom_Emp, usu.Ciudad);
		
		printf("\n¿Qué desea hacer?\n <1> Cambiar email.\n <2> Cambiar contraseña.\n <0> Volver.\n Elija una opción: ");
		if(scanf("%i",&op)!=1){
			fflush(stdin);
			printf("Error: introduzca una entrada válida.");
			op=-1;
		}
		else{
			switch(op){
				case 1: cambiar_email_t(&usu); break;
				case 2: cambiar_contrasena_t(&usu); break;
				case 0: break;
				default: break;
			}
		}
	}while(op!=0);
}

//Precondición: Recibe un puntero a una estructura de transport.
//Postcondición: No devuelve nada. Se habrá cambiado el email del usuario guardado en el puntero.
void cambiar_email_t(transport *usu){
	
	char nuevo_email[31];
	printf("\nIngrese el nuevo email: ");
	fflush(stdin);
	fgets(nuevo_email, sizeof(nuevo_email), stdin);
	acortar_cadena(nuevo_email);
	strcpy(usu->email, nuevo_email);
}

//Precondición: Recibe un puntero a una estructura de transport.
//Postcondición: No devuelve nada. Se habrá cambiado la contraseña del usuario guardada en el puntero, o no.
void cambiar_contrasena_t(transport *usu){
	
	char nueva_contra[21], contra_compr[21];									// Cadenas donde guardamos la contraseña nueva, y su repetición.
	int valido = 0;
	
	printf("\nIntroduzca la contrasena actual: ");
	fflush(stdin);
	fgets(contra_compr, sizeof(contra_compr), stdin);
	acortar_cadena(contra_compr);
	if(strcmp(contra_compr, usu->Contrasena) == 0){							
		do{
			printf("\nIndique la nueva contrasena: ");						
			fflush(stdin);
			fgets(nueva_contra, sizeof(nueva_contra), stdin);
			acortar_cadena(nueva_contra);
			printf("\nIndiquela de nuevo de nuevo: ");
			fflush(stdin);
			fgets(contra_compr, sizeof(contra_compr), stdin);	
			acortar_cadena(contra_compr);
			if(strcmp(nueva_contra,contra_compr) == 0)							// Si las contraseñas son iguales (el usuario no se ha equivocado), salimos del bucle.
				valido = 1;
			else	
				printf("Contrasenas distintas, inténtelo de nuevo.");			// Solicitamos la nueva contraseña al usuario mientras no verifique que se repitan.
		}while(valido == 0);
		strcpy_s(usu->Contrasena,sizeof(nueva_contra), nueva_contra);
		printf("\nContraseña cambiada satisfactoriamente.");
		Sleep(3000);															// Esperamos tres segundos antes de limpiar la pantalla para poder leer el mensaje anterior.
	}else{
		printf("\nContrasena errónea. Pruebe otra vez o contacte con un administrador.\n");
		Sleep(3000);															// Esperamos diez segundos antes de limpiar la pantalla para poder leer el mensaje anterior.		
	}
	
}



// FUNCIONES DE LECTURA DE FICHEROS



//Precondición: No recibe nada.
//Postcondición: Devuelve una variable de tipo admin_prov_vect con la información de cada usuario (proveedor o administrador) almacenados en AdminProv.txt.

admin_prov_vect cargar_adminprov(){
	
	admin_prov_vect adminprov_sistema;
	FILE *f_AdminProv;																							// Puntero al fichero a leer.
	char ruta[] = "..\\data\\AdminProv.txt";														// Ruta del fichero a leer.
	char linea[LONG_MAX_ADMINPROV];																				// Línea actual del fichero. Longitud máxima de una línea 86 caracteres.
	char tipo_usuario[14];																						// Cadena auxiliar a convertir.
	int i = 0, m;

	if((f_AdminProv = fopen(ruta, "r+")) == NULL){
		printf("Error al abrir el fichero AdminProv.txt en cargar_adminprov.\n");
		exit(33);
	}

	//COMPROBACION FICHERO VACIO//
	char verif = fgetc(f_AdminProv);
	if (verif == EOF){
		f_AdminProv = fopen(ruta, "w");
		printf("Se ha cargado nuevo fichero.\n");
		fprintf(f_AdminProv,"0000-ESIZON-adminadmin@esizon.com-admin000-administrador\n");
		fclose(f_AdminProv);

	}

	adminprov_sistema.tam = 0;
	while(fgets(linea, sizeof(linea), f_AdminProv) != NULL)													// Contamos el número de usuarios en el fichero...
		adminprov_sistema.tam++;
	printf("Usuarios almacenados en AdminProv.txt: %d \n", adminprov_sistema.tam);
	adminprov_sistema.usuarios = (admin_prov*)malloc((adminprov_sistema.tam + 1) * sizeof(admin_prov));		// ... y reservamos memoria para el vector (más uno por si se necesita añadir algún usuario).
	rewind(f_AdminProv);																							
	
	while((fgets(linea, sizeof(linea), f_AdminProv) != NULL) ){	
		if((m = sscanf(linea, "%d-%20[^-]-%30[^-]-%15[^-]-%13[^\n]\n", &adminprov_sistema.usuarios[i].Id_empresa, adminprov_sistema.usuarios[i].Nombre, adminprov_sistema.usuarios[i].email, adminprov_sistema.usuarios[i].Contrasena, adminprov_sistema.usuarios[i].Perfil_usuario)) == 5){
			i++;		
		}
		else{
			printf("Error leyendo datos del fichero AdminProv.txt en cargar_adminprov. Línea: %d", i + 1);	
			exit(33);				
		}
	}			
		                                    
	fclose(f_AdminProv);  
	
	return adminprov_sistema;                             	                            
}


//Precondición: No recibe nada.
//Postcondición: Devuelve una variable de tipo transport_vect con la información de cada transportista almacenada en Transportistas.txt.

transport_vect cargar_transportistas(){
	
	transport_vect transport_sistema;
	FILE *Transportistas;																						// Puntero al fichero a leer.
	char ruta[] = "../data/Transportistas.txt";													// Ruta del fichero a leer.
	char linea[LONG_MAX_TRANSPORT];																				// Línea actual del fichero. Longitud máxima de una línea 113 caracteres.
	int i = 0, m;

	if((Transportistas = fopen(ruta, "r+")) == NULL){
		printf("Error al abrir el fichero Transportistas.txt en cargar_transportistas.\n");
		exit(33);
	}
	else{
		transport_sistema.tam = 0;
		while(fgets(linea, sizeof(linea), Transportistas) != NULL)												// Contamos el número de usuarios en el fichero...
	    	transport_sistema.tam++;
	    printf("Transportistas almacenados en Transportistas.txt: %d \n", transport_sistema.tam);
	 	transport_sistema.transportistas = (transport*)malloc((transport_sistema.tam + 1) * sizeof(transport));	// ... y reservamos memoria para el vector (más uno por si se necesita añadir algún usuario).
	 	rewind(Transportistas);																							
	    
		while((fgets(linea, sizeof(linea), Transportistas) != NULL) ){	
			if((m = sscanf(linea, "%d-%20[^-]-%30[^-]-%15[^-]-%20[^-]-%20[^\n]\n", &transport_sistema.transportistas[i].Id_transp, transport_sistema.transportistas[i].Nombre, transport_sistema.transportistas[i].email, transport_sistema.transportistas[i].Contrasena, transport_sistema.transportistas[i].Nom_Emp, transport_sistema.transportistas[i].Ciudad)) == 6)
				i++;		
			else{
				printf("Error leyendo datos del fichero Transportistas.txt en cargar_transportistas. Línea: %d\n", i + 1);	
				exit(33);				
			}
		}			
	}
		                                    
	fclose(Transportistas); 
	return transport_sistema;  
	
}



//	FUNCIONES DE VOLCADO EN FICHEROS



//Precondición: Recibe una estructura de tipo admin_prov con datos coherentes almacenados.
//Postcondición: Guarda en AdminProv.txt los datos del vector de estructuras recibido.

void guardar_adminprov(admin_prov_vect usuarios){
	
	FILE *AdminProv;																							// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\AdminProv.txt";														// Ruta del fichero a leer.
	char linea[LONG_MAX_ADMINPROV];																				// Línea actual del fichero. Longitud máxima de una línea 86 caracteres.
	char aux[14];
	
	if((AdminProv = fopen(ruta, "a+")) == NULL){
		printf("Error al abrir el fichero AdminProv.txt en cargar_adminprov.\n");
		exit(33);
	}
	else{
			for(int i = 0; i < usuarios.tam; i++)
				fprintf(AdminProv, "%d-%20[^-]-%30[^-]-%15[^-]-%13[^\n]\n", usuarios.usuarios[i].Id_empresa, usuarios.usuarios[i].Nombre, usuarios.usuarios[i].email, usuarios.usuarios[i].Contrasena, usuarios.usuarios[i].Perfil_usuario);
		}
}



//Precondición: Recibe una estructura de tipo transport con datos coherentes almacenados.
//Postcondición: Guarda en Transportistas.txt los datos del vector de estructuras recibido.

void guardar_transportista(transport_vect transportistas){
	
	FILE *Transportistas;																						// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\Transportistas.txt";													// Ruta del fichero a leer.
	char linea[LONG_MAX_TRANSPORT];																				// Línea actual del fichero. Longitud máxima de una línea 113 caracteres.

	if((Transportistas = fopen(ruta, "a+")) == NULL){
		printf("Error al abrir el fichero AdminProv.txt en cargar_adminprov.\n");
		exit(33);
	}
	else{
		for(int i = 0; i < transportistas.tam; i++)
			fprintf(Transportistas, "%d-%20[^-]-%30[^-]-%15[^-]-%20[^-]-%20s\n", transportistas.transportistas[i].Id_transp, transportistas.transportistas[i].Nombre, transportistas.transportistas[i].email, transportistas.transportistas[i].Contrasena, transportistas.transportistas[i].Nom_Emp, transportistas.transportistas[i].Ciudad);
	}
}



//	UTILIDADES VARIAS



//Precondición: No recibe nada.
//Postcondición: Devuelve el numero de lineas que contiene AdminProv.txt.

int longitud_vector_adminprov(){
	
	FILE *Admin_Prov_txt;	
	char aux[LONG_MAX_ADMINPROV];
	int i = 0;
	
	if((Admin_Prov_txt = fopen("..\\ESIZON-main\\data\\AdminProv.txt", "r")) == NULL)  
        printf("Error en la apertura de AdminProv.txt para longitud_vector_adminprov.\n");
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
	
	if((Transportistas_txt = fopen("..\\ESIZON-main\\data\\Transportistas.txt", "r+")) == NULL)  
        printf("Error en la apertura de Transportistas.txt para longitud_vector_transportistas.\n");
	else{
		while(fgets(aux, sizeof(aux), Transportistas_txt)){
        	i++;
    	}
	}
	
    fclose(Transportistas_txt);
    
    return i;	
}



//Precondición: Recibe una cadena que necesite ser acortada (no nula, con algún carácter ' ' al final de ella).
//Postcondición: No devuelve nada, sustituye el primer carácter ' ' que encuentre en la cadena por el carácter terminador '\0'.

void acortar_cadena(char cadena[]){
	int i, len = strlen(cadena);
	for(i = 0; i < len; i++){
    	if(cadena[i] == '\n')
    		cadena[i] = '\0';
	}
}
