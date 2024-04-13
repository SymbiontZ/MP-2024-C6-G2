#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "complementos.h"
#include "Productos.h"
#include "empresas.h"



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
		
		printf("\n	   EMPRESA: %s\n", provs.usuarios[pos].Nombre);
		
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
		
		printf("\n	   NOMBRE: %s\n", transports.transportistas[pos].Nombre);
		printf("\n	   EMPRESA: %s\n", transports.transportistas[pos].Nom_Emp);
		
		printf("\nBienvenido, %s - ¿Qué desea hacer hoy?\n\n <1> Ver perfil.\n <2> Ver repartos asignados.\n <3> Ver retornos.\n <0> Salir.\n Elija una opción: ", transports.transportistas[pos].email);
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
	menu_prod(prods);						//Accedemos al menú de gestión de productos
	guardar_productos(prods);				//Guardamos cambios
	Sleep(2000);
	
}



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
//Postcondición: El usuario habrá realizado las tareas de gestión de pedidos convenientes.
void ver_pedidos(admin_prov_vect provs, int pos){
	
}



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
//Postcondición: No devuelve nada. Se habrá cambiado el email del usuario guardado en el puntero.
void cambiar_email(admin_prov_vect provs, int pos){
	
	char nuevo_email[31];
	printf("\nIngrese el nuevo email: ");
	fflush(stdin);
	fgets(nuevo_email, sizeof(nuevo_email), stdin);
	terminador_cad(nuevo_email);
	strcpy(provs.usuarios[pos].email, nuevo_email);
	
}



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
//Postcondición: No devuelve nada. Se habrá cambiado la contraseña del usuario guardada en el puntero, o no.
void cambiar_contrasena(admin_prov_vect provs, int pos){
	
	char nueva_contra[21], contra_compr[21];									// Cadenas donde guardamos la contraseña nueva, y su repetición.
	int valido = 0;
	
	printf("\nIntroduzca la contrasena actual: ");
	fflush(stdin);
	fgets(contra_compr, sizeof(contra_compr), stdin);
	terminador_cad(contra_compr);
	if(strcmp(contra_compr, provs.usuarios[pos].Contrasena) == 0){							
		do{
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
		}while(valido == 0);
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
	printf("\nIngrese el nombre que debe figurar en el sistema: ");
	fflush(stdin);
	fgets(nuevo_nombre, sizeof(nuevo_nombre), stdin);
	fflush(stdin);
	terminador_cad(nuevo_nombre);
	strcpy(transports.transportistas[pos].Nombre, nuevo_nombre);
	
}



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
//Postcondición: No devuelve nada. Se habrá cambiado el email del usuario guardado en el puntero.
void cambiar_email_t(transport_vect transports, int pos){
	
	char nuevo_email[31];
	printf("\nIngrese el nuevo email: ");
	fflush(stdin);
	fgets(nuevo_email, sizeof(nuevo_email), stdin);
	fflush(stdin);
	terminador_cad(nuevo_email);
	strcpy(transports.transportistas[pos].email, nuevo_email);
	
}



//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
//Postcondición: No devuelve nada. Se habrá cambiado la contraseña del usuario guardada en el puntero, o no.
void cambiar_contrasena_t(transport_vect transports, int pos){
	
	char nueva_contra[21], contra_compr[21];									// Cadenas donde guardamos la contraseña nueva, y su repetición.
	int valido = 0;
	
	printf("\nIntroduzca la contrasena actual: ");
	fflush(stdin);
	fgets(contra_compr, sizeof(contra_compr), stdin);
	fflush(stdin);
	terminador_cad(contra_compr);
	if(strcmp(contra_compr, transports.transportistas[pos].Contrasena) == 0){							
		do{
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
		}while(valido == 0);
		strcpy(transports.transportistas[pos].Contrasena, nueva_contra);
		printf("\nContraseña cambiada satisfactoriamente.");
		Sleep(3000);															// Esperamos tres segundos antes de limpiar la pantalla para poder leer el mensaje anterior.
	}else{
		printf("\nContrasena errónea. Pruebe otra vez o contacte con un administrador.\n");
		Sleep(3000);															// Esperamos tres segundos antes de limpiar la pantalla para poder leer el mensaje anterior.		
	}
	
}



// FUNCIONES PARA LA GESTIÓN DE PROVEEDORES



void listar_prov(admin_prov_vect provs){
	
	clear();
	
	printf("	#########################################\n");
	printf("	# PROVEEDORES REGISTRADOS EN EL SISTEMA #\n");
	printf("	#########################################\n\n");
	
	printf("		    Empresa | Email");
	
	for(int i = 1; i < provs.tam; i++)
		printf("%s | %s", provs.usuarios[i].Nombre, provs.usuarios[i].email);
	
	printf("\n\n Presione cualquier tecla para continuar...");
	getchar();
}



int buscar_prov(admin_prov_vect provs){
}



admin_prov_vect alta_prov(admin_prov_vect provs){
}



admin_prov_vect baja_prov(admin_prov_vect provs){
}



admin_prov_vect modificar_prov(admin_prov_vect provs){
}



// FUNCIONES PARA LA GESTIÓN DE TRANSPORTISTAS



void listar_transport(transport_vect transports){
	
	clear();
	
	printf("	############################################\n");
	printf("	# TRANSPORTISTAS REGISTRADOS EN EL SISTEMA #\n");
	printf("	############################################\n\n");
	
	printf("	     Ciudad | Email | Nombre | Empresa  ");
	
	for(int i = 1; i < transports.tam; i++)
		printf("%s | %s | %s | %s ", transports.transportistas[i].Ciudad, transports.transportistas[i].email, transports.transportistas[i].Nombre, transports.transportistas[i].Nom_Emp);
	
	printf("\n\n Presione cualquier tecla para continuar...");
	getchar();

}



int buscar_transport(transport_vect transports){
}



transport_vect alta_transport(transport_vect transports){
}



transport_vect baja_transport(transport_vect transports){
}



transport_vect modificar_transport(transport_vect transports){
}



// FUNCIONES DE LECTURA DE FICHEROS



//Precondición: No recibe nada.
//Postcondición: Devuelve una variable de tipo admin_prov_vect con la información de cada usuario (proveedor o administrador) almacenados en AdminProv.txt.

admin_prov_vect cargar_adminprov(){
	
	admin_prov_vect adminprov_sistema;
	FILE *f_AdminProv;																							// Puntero al fichero a leer.
	char ruta[] = "..\\data\\AdminProv.txt";																		// Ruta del fichero a leer.
	char linea[LONG_MAX_ADMINPROV];																				// Línea actual del fichero. Longitud máxima de una línea 86 caracteres.
	char tipo_usuario[14];																						// Cadena auxiliar a convertir.
	int i = 0, m; 

	if((f_AdminProv = fopen(ruta, "w+")) == NULL){																// w+ permite leer y escribir, y crea el archivo si no existe.
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
	printf("\nCarga completada.\nUsuarios almacenados en AdminProv.txt: %d \n", adminprov_sistema.tam);
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
	char ruta[] = "../data/Transportistas.txt";																	// Ruta del fichero a leer.
	char linea[LONG_MAX_TRANSPORT];																				// Línea actual del fichero. Longitud máxima de una línea 113 caracteres.
	int i = 0, m;

	if((Transportistas = fopen(ruta, "w+")) == NULL){															// w+ permite leer y escribir, y crea el archivo si no existe.
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
    printf("\nCarga completada.\nTransportistas almacenados en Transportistas.txt: %d \n", transport_sistema.tam);
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
	char ruta[] = "..\\ESIZON-main\\data\\AdminProv.txt";														// Ruta del fichero a leer.
	char linea[LONG_MAX_ADMINPROV];																				// Línea actual del fichero. Longitud máxima de una línea 86 caracteres.
	char aux[14];
	
	AdminProv = fopen(ruta, "w");
	
	for(int i = 0; i < usuarios.tam; i++)
		fprintf(AdminProv, "%d-%20[^-]-%30[^-]-%15[^-]-%13[^\n]\n", usuarios.usuarios[i].Id_empresa, usuarios.usuarios[i].Nombre, usuarios.usuarios[i].email, usuarios.usuarios[i].Contrasena, usuarios.usuarios[i].Perfil_usuario);
	fclose(AdminProv);
}



//Precondición: Recibe una estructura de tipo transport con datos coherentes almacenados.
//Postcondición: Guarda en Transportistas.txt los datos del vector de estructuras recibido.

void guardar_transportista(transport_vect transportistas){
	
	FILE *Transportistas;																						// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\Transportistas.txt";													// Ruta del fichero a leer.
	char linea[LONG_MAX_TRANSPORT];																				// Línea actual del fichero. Longitud máxima de una línea 113 caracteres.

	Transportistas = fopen(ruta, "w");
	
	for(int i = 0; i < transportistas.tam; i++)
		fprintf(Transportistas, "%d-%20[^-]-%30[^-]-%15[^-]-%20[^-]-%20s\n", transportistas.transportistas[i].Id_transp, transportistas.transportistas[i].Nombre, transportistas.transportistas[i].email, transportistas.transportistas[i].Contrasena, transportistas.transportistas[i].Nom_Emp, transportistas.transportistas[i].Ciudad);
	fclose(Transportistas);
}



//	UTILIDADES VARIAS



//Precondición: No recibe nada.
//Postcondición: Devuelve el numero de lineas que contiene AdminProv.txt.

int longitud_vector_adminprov(){
	
	FILE *Admin_Prov_txt;	
	char aux[LONG_MAX_ADMINPROV];
	int i = 0;
	
	if((Admin_Prov_txt = fopen("..\\ESIZON-main\\data\\AdminProv.txt", "r")) == NULL){
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
