#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lockers.h"

void Cargar_Lockers(){

    Vect_Lock vector_lock;
	FILE *f_lockers;																						// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\Lockers.txt";                                                  // Ruta del fichero a leer.
	char linea[MAX_LOCK];													                                //Linea a leer
    int i = 0, m;

	if((f_lockers = fopen(ruta, "r+")) == NULL){
		printf("Error al abrir el fichero Lockers.txt.\n");
		exit(33);
	}

	vector_lock.tam = 0;
	while(fgets(linea, sizeof(linea), f_lockers) != NULL)												// Contamos el n�mero de usuarios en el fichero...
	    vector_lock.tam++;
	printf("Descuentos almacenados en Lockers.txt: %d \n", vector_lock.tam);
    vector_lock.Lock = malloc((vector_lock.tam + 1) * sizeof(Lockers));	// ... y reservamos memoria para el vector (m�s uno por si se necesita a�adir alg�n usuario).
	rewind(f_lockers);

	while((fgets(linea, sizeof(linea), f_lockers) != NULL) ){
		m = sscanf(linea, "%10[^-]-%20[^-]-%20[^-]-%20[^-]-%d[^-]-%d[^\n]\n",
			&vector_lock.Lock[i].Id_locker,
			vector_lock.Lock[i].Localidad,
			vector_lock.Lock[i].Provincia,
			vector_lock.Lock[i].Ubica,
			vector_lock.Lock[i].Num_compT,
			vector_lock.Lock[i].Num_compOkup);

			i++;
		if(m != 6){
			printf("Error leyendo datos del fichero Lockers.txt. Linea: %d\n", i + 1);
			exit(EXIT_FAILURE);
		}
	}
	fclose(f_lockers);


}

void Cargar_CompartimentosLockers(){

    Vect_CompLock vector_complock;
	FILE *f_compartimentoslockers;																						// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\CompartimentosLockers.txt";                                                  // Ruta del fichero a leer.
	char linea[MAX_COMPLOCK];													                                //Linea a leer
    int i = 0, m;

	if((f_compartimentoslockers = fopen(ruta, "r+")) == NULL){
		printf("Error al abrir el fichero CompartimentosLockers.txt.\n");
		exit(33);
	}

	vector_complock.tam = 0;
	while(fgets(linea, sizeof(linea), f_compartimentoslockers) != NULL)												// Contamos el n�mero de usuarios en el fichero...
	    vector_complock.tam++;
	printf("Descuentos almacenados en CompartimentosLockers.txt: %d \n", vector_complock.tam);
    vector_complock.CompLock = malloc((vector_complock.tam + 1) * sizeof(CompartimentosLockers));	// ... y reservamos memoria para el vector (m�s uno por si se necesita a�adir alg�n usuario).
	rewind(f_compartimentoslockers);

	while((fgets(linea, sizeof(linea), f_compartimentoslockers) != NULL) ){
		m = sscanf(linea, "%d[^-]-%d[^-]-%d[^-]-%7[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^\n]\n",
			&vector_complock.CompLock[i].Id_locker,
			vector_complock.CompLock[i].Num_comp,
			vector_complock.CompLock[i].Cod_locker,
			vector_complock.CompLock[i].Estado,
			vector_complock.CompLock[i].dia_okup,
			vector_complock.CompLock[i].mes_okup,
			vector_complock.CompLock[i].anio_okup,
			vector_complock.CompLock[i].dia_cad,
			vector_complock.CompLock[i].mes_cad,
			vector_complock.CompLock[i].anio_cad);

			i++;
		if(m != 6){
			printf("Error leyendo datos del fichero CompartimentosLockers.txt. Linea: %d\n", i + 1);
			exit(EXIT_FAILURE);
		}
	}
	fclose(f_compartimentoslockers);


}


void Guardar_Lockers(Vect_Lock lockers){

    FILE *f_lockers;																							// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\Lockers.txt";														// Ruta del fichero a leer.
	char linea[MAX_LOCK];																				// Línea actual del fichero. Longitud máxima de una línea 86 caracteres.
	char aux[14];

	if((f_lockers = fopen(ruta, "a+")) == NULL){
		printf("\nError al abrir el fichero Lockers.txt\n");
		f_lockers = fopen(ruta, "w");
		Sleep(2000);
	}

	for(int i = 0; i < lockers.tam; i++)
		fprintf(f_lockers, "%10[^-]-%20[^-]-%20[^-]-%20[^-]-%d[^-]-%d[^\n]\n",
            lockers.Lock[i].Id_locker,
			lockers.Lock[i].Localidad,
			lockers.Lock[i].Provincia,
			lockers.Lock[i].Ubica,
			lockers.Lock[i].Num_compT,
			lockers.Lock[i].Num_compOkup);

    fclose(f_lockers);

}


void Guardar_CompartimentosLockers(Vect_CompLock compartimentoslockers){

    FILE *f_complockers;																							// Puntero al fichero a leer.
	char ruta[] = "..\\ESIZON-main\\data\\CompartimentosLockers.txt";														// Ruta del fichero a leer.
	char linea[MAX_COMPLOCK];																				// Línea actual del fichero. Longitud máxima de una línea 86 caracteres.
	char aux[14];

	if((f_complockers = fopen(ruta, "a+")) == NULL){
		printf("\nError al abrir el fichero CompartimentosLockers.txt\n");
		f_complockers = fopen(ruta, "w");
		Sleep(2000);
	}

	for(int i = 0; i < compartimentoslockers.tam; i++)
		fprintf(f_complockers, "%d[^-]-%d[^-]-%d[^-]-%7[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^\n]\n",
            compartimentoslockers.CompLock[i].Id_locker,
			compartimentoslockers.CompLock[i].Num_comp,
			compartimentoslockers.CompLock[i].Cod_locker,
			compartimentoslockers.CompLock[i].Estado,
			compartimentoslockers.CompLock[i].dia_okup,
			compartimentoslockers.CompLock[i].mes_okup,
			compartimentoslockers.CompLock[i].anio_okup,
			compartimentoslockers.CompLock[i].dia_cad,
			compartimentoslockers.CompLock[i].mes_cad,
			compartimentoslockers.CompLock[i].anio_cad);

    fclose(f_complockers);

}

