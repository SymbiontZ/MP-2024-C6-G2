
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "empresas.h"

void ver_perfil();

void admin_ver_clientes();

void admin_ver_proveedores();

void admin_ver_transportistas();

void admin_ver_productos();
 
void admin_ver_categorias();

void admin_ver_pedidos();

void admin_ver_descuentos();

void admin_ver_devoluciones();

//Precondición: No recibe nada.
//Postcondición: Devuelve una variable de tipo admin_prov_vect con la información de cada usuario (proveedor o administrador) almacenados en AdminProv.txt.

void cargar_adminprov(){
	
	admin_prov_vect adminprov_sistema;
	FILE *AdminProv;																							// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\AdminProv.txt";														// Ruta del fichero a leer.
	char linea[LONG_MAX_ADMINPROV];																				// Línea actual del fichero. Longitud máxima de una línea 86 caracteres.
	char tipo_usuario[14];																						// Cadena auxiliar a convertir.
	int i = 0, m;

	if((AdminProv = fopen(ruta, "r+")) == NULL){
		printf("Error al abrir el fichero AdminProv.txt en cargar_adminprov.\n");
		exit(33);
	}
	else{
		adminprov_sistema.tam = 0;
		while(fgets(linea, sizeof(linea), AdminProv) != NULL)													// Contamos el número de usuarios en el fichero...
	    	adminprov_sistema.tam++;
	    printf("Usuarios almacenados en AdminProv.txt: %d \n", adminprov_sistema.tam);
	 	adminprov_sistema.usuarios = (admin_prov*)malloc((adminprov_sistema.tam + 1) * sizeof(admin_prov));		// ... y reservamos memoria para el vector (más uno por si se necesita añadir algún usuario).
	 	rewind(AdminProv);																							
	    
		while((fgets(linea, sizeof(linea), AdminProv) != NULL) ){	
			if((m = sscanf(linea, "%d-%20[^-]-%30[^-]-%15[^-]-%13[^\n]\n", &adminprov_sistema.usuarios[i].Id_empresa, adminprov_sistema.usuarios[i].Nombre, adminprov_sistema.usuarios[i].email, adminprov_sistema.usuarios[i].Contrasena, tipo_usuario)) == 5){
				for(int j = 0; j < strlen(tipo_usuario); j++){
					if(tipo_usuario[j] == ' '){
						tipo_usuario[j] = '\0';  
						j = strlen(tipo_usuario) + 1;
					}
				}
				if(strcmp("administrador", tipo_usuario) == 0)
					adminprov_sistema.usuarios[adminprov_sistema.tam].Perfil_usuario = 1;
				else
					adminprov_sistema.usuarios[adminprov_sistema.tam].Perfil_usuario = 0;	
				i++;		
			}
			else{
				printf("Error leyendo datos del fichero AdminProv.txt en cargar_adminprov. Línea: %d", i + 1);	
				exit(33);				
			}
		}			
	}
		                                    
	fclose(AdminProv);                               	                            
}

//Precondición: Recibe una estructura de tipo admin_prov con datos coherentes almacenados.
//Postcondición: Guarda en AdminProv.txt los datos del vector de estructuras recibido.

void agregar_adminprov(admin_prov_vect usuarios){
	
	FILE *AdminProv;																							// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\AdminProv.txt";														// Ruta del fichero a leer.
	char linea[LONG_MAX_ADMINPROV];																				// Línea actual del fichero. Longitud máxima de una línea 86 caracteres.
	char aux[14];
	
	if((AdminProv = fopen(ruta, "a+")) == NULL){
		printf("Error al abrir el fichero AdminProv.txt en cargar_adminprov.\n");
		exit(33);
	}
	else{
		for(int i = 0; i < usuarios.tam; i++){
			if(usuarios.usuarios[i].Perfil_usuario == 1)
				strcpy(aux, "Administrador");
			else
				strcpy(aux, "Proveedor");
			fprintf(AdminProv, "%d-%20[^-]-%30[^-]-%15[^-]-%13[^\n]\n", usuarios.usuarios[i].Id_empresa, usuarios.usuarios[i].Nombre, usuarios.usuarios[i].email, usuarios.usuarios[i].Contrasena, aux);
		}
	}
}

//Precondición: No recibe nada.
//Postcondición: Devuelve una variable de tipo transport_vect con la información de cada transportista almacenada en Transportistas.txt.

void cargar_transportistas(){
	
	transport_vect transport_sistema;
	FILE *Transportistas;																						// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\Transportistas.txt";													// Ruta del fichero a leer.
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
	
}

//Precondición: Recibe una estructura de tipo transport con datos coherentes almacenados.
//Postcondición: Guarda en Transportistas.txt los datos del vector de estructuras recibido.

void agregar_transportista(transport_vect transportistas){
	
	FILE *Transportistas;																						// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\Transportistas.txt";													// Ruta del fichero a leer.
	char linea[LONG_MAX_TRANSPORT];																				// Línea actual del fichero. Longitud máxima de una línea 113 caracteres.

	if((Transportistas = fopen(ruta, "a+")) == NULL){
		printf("Error al abrir el fichero AdminProv.txt en cargar_adminprov.\n");
		exit(33);
	}
	else{
		for(int i = 0; i < transportistas.tam; i++){
			fprintf(Transportistas, "%d-%20[^-]-%30[^-]-%15[^-]-%20[^-]-%20[^\n]\n", transportistas.transportistas[i].Id_transp, transportistas.transportistas[i].Nombre, transportistas.transportistas[i].email, transportistas.transportistas[i].Contrasena, transportistas.transportistas[i].Nom_Emp, transportistas.transportistas[i].Ciudad);
		}
	}
}

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
	int i, len = (int) strlen(cadena);
	for(i=0; i<len; i++){
    	if(cadena[i]=='\n')
    		cadena[i]='\0';
	}
}

void menu_admin(admin_prov admin){
	
	int op = -1, i = 0;
	do{
		printf("\nBienvenido, %s - ¿Qué desea hacer hoy?\n <1> Ver perfil.\n <2> Administrar clientes.\n <3> Administrar proveedores\n <4> Administrar transportistas.\n <5> Administrar productos.\n <6> Ver categorías.\n <7> Ver pedidos.\n <8> Ver descuentos.\n <9> Ver devoluciones.\n <0> Volver.\n Elija una opción: ", admin.Nombre);
		if(scanf("%i",&op)!=1){
			fflush(stdin);
			printf("Error: introduzca una entrada válida.");
			op=-1;
		}
		else{
			switch(op){
				case 1: ver_perfil(); break;
				case 2: admin_ver_clientes(); break;
				case 3: admin_ver_proveedores; break;
				case 4: admin_ver_transportistas(); break;
				case 5: admin_ver_productos(); break;
				case 6: admin_ver_categorias(); break;
				case 7: admin_ver_pedidos(); break;
				case 8: admin_ver_descuentos(); break;
				case 9: admin_ver_devoluciones(); break;
				case 0: break;
				default: printf("Introduzca una entrada dentro de la lista dada."); i++; if(i>5) printf("\nVenga, que no es complicado: introduce 1, 2, 3 o 4 según lo que necesites.\n"); break;
			}
		}
	}while(op!=0);
	
}
	
	
	



