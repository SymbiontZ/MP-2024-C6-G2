#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Descuentos.h"


void Cargar_Descuentos(){

    Descuentos vector_desc;
	FILE *f_descuentos;																						// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\Descuentos.txt";                                                  // Ruta del fichero a leer.
	char linea[MAX_DESC];													                                //Linea a leer
    int i = 0, m;

	if((f_descuentos = fopen(ruta, "r+")) == NULL){
		printf("Error al abrir el fichero Descuentos.txt.\n");
		exit(33);
	}

	vector_desc.tam = 0;
	while(fgets(linea, sizeof(linea), f_descuentos) != NULL)												// Contamos el n�mero de usuarios en el fichero...
	    vector_desc.tam++;
	printf("Descuentos almacenados en Descuentos.txt: %d \n", vector_desc.tam);
    vector_desc.Desc = malloc((vector_desc.tam + 1) * sizeof(Descuento));	// ... y reservamos memoria para el vector (m�s uno por si se necesita a�adir alg�n usuario).
	rewind(f_descuentos);

	while((fgets(linea, sizeof(linea), f_descuentos) != NULL) ){
		m = sscanf(linea, "%10[^-]-%50[^-]-%7[^-]-%8[^-]-%d[^-]-%6[^\n]\n",
            &vector_desc.Desc[i].Id_cod,
			vector_desc.Desc[i].Descrip,
			vector_desc.Desc[i].Tipo,
			vector_desc.Desc[i].Estado,
			vector_desc.Desc[i].Importe,
			vector_desc.Desc[i].Aplicable);

			i++;
		if(m != 6){
			printf("Error leyendo datos del fichero Descuentos.txt. Linea: %d\n", i + 1);
			exit(EXIT_FAILURE);
		}
	}
	fclose(f_descuentos);


}


void Cargar_DescuentosClientes(){

    DescClientes vector_descClts;
	FILE *f_DescClientes;																						// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\DescuentosClientes.txt";                                                  // Ruta del fichero a leer.
	char linea[MAX_DESCLI];													                                //Linea a leer
    int i = 0, m;

	if((f_DescClientes = fopen(ruta, "r+")) == NULL){
		printf("Error al abrir el fichero DescuentosClientes.txt.\n");
		exit(33);
	}
	vector_descClts.tam = 0;
	while(fgets(linea, sizeof(linea), f_DescClientes) != NULL)												// Contamos el n�mero de usuarios en el fichero...
	    vector_descClts.tam++;
	    printf("Descuentos almacenados en DescuentosClientes.txt: %d \n", vector_descClts.tam);
        vector_descClts.DescCliente = malloc((vector_descClts.tam + 1) * sizeof(DescClientes));	// ... y reservamos memoria para el vector (m�s uno por si se necesita a�adir alg�n usuario).
	 	rewind(f_DescClientes);

		while((fgets(linea, sizeof(linea), f_DescClientes) != NULL) ){
			if((m = sscanf(linea, "%d[^-]-%10[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^\n]\n",
                  &vector_descClts.DescCliente[i].Id_cliente,
                  vector_descClts.DescCliente[i].Id_cod,
                  vector_descClts.DescCliente[i].dia_asig,
                  vector_descClts.DescCliente[i].mes_asig,
                  vector_descClts.DescCliente[i].anio_asig,
                  vector_descClts.DescCliente[i].dia_cad,
                  vector_descClts.DescCliente[i].mes_cad,
                  vector_descClts.DescCliente[i].anio_cad)) == 6)
				i++;
			else{
				printf("Error leyendo datos del fichero DescuentosClientes.txt. L�nea: %d\n", i + 1);
				exit(33);
			}
		}

	fclose(f_DescClientes);


}


void Guardar_Descuentos(Descuentos descuentos){

    FILE *f_descuentos;																							// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\Descuentos.txt";														// Ruta del fichero a leer.
	char linea[MAX_DESC];																				// Línea actual del fichero. Longitud máxima de una línea 86 caracteres.
	char aux[14];

	if((f_descuentos = fopen(ruta, "a+")) == NULL){
		printf("\nError al abrir el fichero Descuentos.txt\n");
		f_descuentos = fopen(ruta, "w");
		Sleep(2000);
	}

	for(int i = 0; i < descuentos.tam; i++)
		fprintf(f_descuentos, "%10[^-]-%50[^-]-%7[^-]-%8[^-]-%d[^-]-%6[^\n]\n",
            descuentos.Desc[i].Id_cod,
            descuentos.Desc[i].Descrip,
			descuentos.Desc[i].Tipo,
			descuentos.Desc[i].Estado,
			descuentos.Desc[i].Importe,
			descuentos.Desc[i].Aplicable);


        fclose(f_descuentos);

}


void DescuentosClientes(DescClientes descuentosclientes){

    FILE *f_DescClientes;																							// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\DescuentosClientes.txt";														// Ruta del fichero a leer.
	char linea[MAX_DESCLI];																				// Línea actual del fichero. Longitud máxima de una línea 86 caracteres.
	char aux[14];

	if((f_DescClientes = fopen(ruta, "a+")) == NULL){
		printf("\nError al abrir el fichero DescuentosClientes.txt\n");
		f_DescClientes = fopen(ruta, "w");
		Sleep(2000);
	}

	for(int i = 0; i < descuentosclientes.tam; i++)
		fprintf(f_DescClientes, "%d[^-]-%10[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^\n]\n",
            descuentosclientes.DescCliente[i].Id_cliente,
            descuentosclientes.DescCliente[i].Id_cod,
            descuentosclientes.DescCliente[i].dia_asig,
            descuentosclientes.DescCliente[i].mes_asig,
            descuentosclientes.DescCliente[i].anio_asig,
            descuentosclientes.DescCliente[i].dia_cad,
            descuentosclientes.DescCliente[i].mes_cad,
            descuentosclientes.DescCliente[i].anio_cad);


        fclose(f_DescClientes);


}


Consultar_Descuentos(Descuentos descuentos, DescClientes descuentosclientes){

    FILE *f_DescClientes;																							// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\DescuentosClientes.txt";														// Ruta del fichero a leer.
	char linea[MAX_DESCLI];																				// Línea actual del fichero. Longitud máxima de una línea 86 caracteres.
	char aux[14];

	if((f_DescClientes = fopen(ruta, "a+")) == NULL){
		printf("\nError al abrir el fichero DescuentosClientes.txt\n");
		f_DescClientes = fopen(ruta, "w");
		Sleep(2000);
	}

	for(int i = 0; i < descuentosclientes.tam; i++){

	}


}

