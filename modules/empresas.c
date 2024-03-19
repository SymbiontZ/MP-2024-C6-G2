
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "empresas.h"

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
//Postcondición: Añade una nueva entrada en AdminProv.txt con los datos de la estructura recibida.

void agregar_adminprov(admin_prov usuario){
	
	FILE *AdminProv;																							// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\AdminProv.txt";														// Ruta del fichero a leer.
	char linea[LONG_MAX_ADMINPROV];																				// Línea actual del fichero. Longitud máxima de una línea 86 caracteres.
	char aux[14];
	
	if(usuario.Perfil_usuario == 1)
		strcpy(aux, "Administrador");
	else
		strcpy(aux, "Proveedor");
		
	if((AdminProv = fopen(ruta, "a+")) == NULL){
		printf("Error al abrir el fichero AdminProv.txt en cargar_adminprov.\n");
		exit(33);
	}
	else{
		fprintf(AdminProv, "%d-%20[^-]-%30[^-]-%15[^-]-%13[^\n]\n", usuario.Id_empresa, usuario.Nombre, usuario.email, usuario.Contrasena, aux);
	}
}


//Precondición: No recibe nada.
//Postcondición: Devuelve una variable de tipo trasnport_vect con la información de cada transportista almacenada en Transportistas.txt.

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
//Postcondición: Añade una nueva entrada en Transportistas.txt con los datos de la estructura recibida.

void agregar_transportista(transport transportista){
	
	FILE *Transportistas;																						// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\Transportistas.txt";													// Ruta del fichero a leer.
	char linea[LONG_MAX_TRANSPORT];																				// Línea actual del fichero. Longitud máxima de una línea 113 caracteres.

	if((Transportistas = fopen(ruta, "a+")) == NULL){
		printf("Error al abrir el fichero AdminProv.txt en cargar_adminprov.\n");
		exit(33);
	}
	else{
		fprintf(Transportistas, "%d-%20[^-]-%30[^-]-%15[^-]-%20[^-]-%20[^\n]\n", transportista.Id_transp, transportista.Nombre, transportista.email, transportista.Contrasena, transportista.Nom_Emp, transportista.Ciudad);
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


