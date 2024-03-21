#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Descuentos.h"


void Cargar_Descuentos(){

    Vect_Desc vector_descuentos;
	FILE *Descuentos;																						// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\Descuentos.txt";                                                  // Ruta del fichero a leer.
	char linea[MAX_DESC];													// Ruta del fichero a leer.
    int i = 0, m;

	if((Descuentos = fopen(ruta, "r+")) == NULL){
		printf("Error al abrir el fichero Descuentos.txt.\n");
		exit(33);
	}
	else{
		vector_descuentos.tam = 0;
		while(fgets(linea, sizeof(linea), Descuentos) != NULL)												// Contamos el número de usuarios en el fichero...
	    	vector_descuentos.tam++;
	    printf("Descuentos almacenados en Descuentos.txt: %d \n", vector_descuentos.tam);
        vector_descuentos.Desc = (Descuentos*)malloc((vector_descuentos.tam + 1) * sizeof(Descuentos));	// ... y reservamos memoria para el vector (más uno por si se necesita añadir algún usuario).
	 	rewind(Descuentos);

		while((fgets(linea, sizeof(linea), Descuentos) != NULL) ){
			if((m = sscanf(linea, "%10[^-]-%50[^-]-%7[^-]-%8[^-]-%2[^-]-%d[^\n]\n", &vector_descuentos.Desc[i].Id_cod, vector_descuentos.Desc[i].Descrip, vector_descuentos.Desc[i].Tipo, vector_descuentos.Desc[i].Estado, vector_descuentos.Desc[i].Aplicable, vector_descuentos.Desc[i].Importe)) == 6)
				i++;
			else{
				printf("Error leyendo datos del fichero Descuentos.txt. Línea: %d\n", i + 1);
				exit(33);
			}
		}
	}

	fclose(Descuentos);


}
