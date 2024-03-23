#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Descuentos.h"


void Cargar_Descuentos(){

    Vect_Desc vector_descuentos;
	FILE *Descuentos;																						// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\Descuentos.txt";                                                  // Ruta del fichero a leer.
	char linea[MAX_DESC];													                                //Linea a leer
    int i = 0, m;

	if((Descuentos = fopen(ruta, "r+")) == NULL){
		printf("Error al abrir el fichero Descuentos.txt.\n");
		exit(33);
	}
	else{
		vector_descuentos.tam = 0;
		while(fgets(linea, sizeof(linea), Descuentos) != NULL)												// Contamos el n�mero de usuarios en el fichero...
	    	vector_descuentos.tam++;
	    printf("Descuentos almacenados en Descuentos.txt: %d \n", vector_descuentos.tam);
        vector_descuentos.Desc = (Descuentos*)malloc((vector_descuentos.tam + 1) * sizeof(Descuentos));	// ... y reservamos memoria para el vector (m�s uno por si se necesita a�adir alg�n usuario).
	 	rewind(Descuentos);

		while((fgets(linea, sizeof(linea), Descuentos) != NULL) ){
			if((m = sscanf(linea, "%10[^-]-%50[^-]-%7[^-]-%8[^-]-%2[^-]-%d[^\n]\n", &vector_descuentos.Desc[i].Id_cod, vector_descuentos.Desc[i].Descrip, vector_descuentos.Desc[i].Tipo, vector_descuentos.Desc[i].Estado, vector_descuentos.Desc[i].Aplicable, vector_descuentos.Desc[i].Importe)) == 6)
				i++;
			else{
				printf("Error leyendo datos del fichero Descuentos.txt. L�nea: %d\n", i + 1);
				exit(33);
			}
		}
	}

	fclose(Descuentos);


}

void Cargar_DescuentosClientes(){

    Vect_DescCli vector_descuentosclientes;
	FILE *DescuentosClientes;																						// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\DescuentosClientes.txt";                                                  // Ruta del fichero a leer.
	char linea[MAX_DESCLI];													                                //Linea a leer
    int i = 0, m;

	if((DescuentosClientes = fopen(ruta, "r+")) == NULL){
		printf("Error al abrir el fichero DescuentosClientes.txt.\n");
		exit(33);
	}
	else{
		vector_descuentosclientes.tam = 0;
		while(fgets(linea, sizeof(linea), DescuentosClientes) != NULL)												// Contamos el n�mero de usuarios en el fichero...
	    	vector_descuentosclientes.tam++;
	    printf("Descuentos almacenados en DescuentosClientes.txt: %d \n", vector_descuentosclientes.tam);
        vector_descuentosclientes.DescCli = (DescuentosClientes*)malloc((vector_descuentosclientes.tam + 1) * sizeof(DescuentosClientes));	// ... y reservamos memoria para el vector (m�s uno por si se necesita a�adir alg�n usuario).
	 	rewind(DescuentosClientes);

		while((fgets(linea, sizeof(linea), DescuentosClientes) != NULL) ){
			if((m = sscanf(linea, "%7[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^\n]\n", &vector_descuentosclientes.DescCli[i].Id_cod, vector_descuentosclientes.DescCli[i].Id_cliente, vector_descuentosclientes.DescCli[i].dia_asig, vector_descuentosclientes.DescCli[i].mes_asig, vector_descuentosclientes.DescCli[i].anio_asig, vector_descuentosclientes.DescCli[i].dia_cad, vector_descuentosclientes.DescCli[i].mes_cad, vector_descuentosclientes.DescCli[i].anio_cad)) == 6)
				i++;
			else{
				printf("Error leyendo datos del fichero DescuentosClientes.txt. L�nea: %d\n", i + 1);
				exit(33);
			}
		}
	}

	fclose(DescuentosClientes);


}
