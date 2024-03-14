
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "empresas.h"


//Precondición: No recibe nada.
//Postcondición: Devuelve una variable de tipo admin_prov_vect con la información de cada usuario (proveedor o administrador).

admin_prov_vect cargar_adminprov(){
	
	admin_prov_vect usuarios;
	FILE *Admin_Prov_txt;
	
	usuarios.tam = 0;
	
	if((Admin_Prov_txt = fopen("AdminProv.txt","a+"))==NULL)
        	printf("Error al guardar la información");
	else{

		}
	fclose(Admin_Prov_txt);
	
}

//Precondición: No recibe nada.
//Postcondición: Devuelve una variable de tipo transport_vect con la información de cada transportista.

transport_vect cargar_transportistas(){
	
	transport_vect transportistas;
	FILE *Transportistas_txt;
	
		if((Transportistas_txt = fopen("Transportistas.txt","a+"))==NULL)
        	printf("Error al guardar la información");
	else{
			
		}
	fclose(Transportistas_txt);
	
}



