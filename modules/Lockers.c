#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lockers.h"
#include "complementos.h"

void Cargar_Lockers(){

    Vect_Lock vector_lock;
	FILE *f_lockers;
	char ruta[] = "..\\ESIZON-main\\data\\Lockers.txt";
	char linea[MAX_LOCK];
    int i = 0, m;

	if((f_lockers = fopen(ruta, "r+")) == NULL){
		printf("Error al abrir el fichero Lockers.txt.\n");
		exit(33);
	}

	vector_lock.tam = 0;
	while(fgets(linea, sizeof(linea), f_lockers) != NULL)
	    vector_lock.tam++;
	printf("Descuentos almacenados en Lockers.txt: %d \n", vector_lock.tam);
    vector_lock.Lock = malloc((vector_lock.tam + 1) * sizeof(Lockers));
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
	FILE *f_compartimentoslockers;
	char ruta[] = "..\\ESIZON-main\\data\\CompartimentosLockers.txt";
	char linea[MAX_COMPLOCK];
    int i = 0, m;

	if((f_compartimentoslockers = fopen(ruta, "r+")) == NULL){
		printf("Error al abrir el fichero CompartimentosLockers.txt.\n");
		exit(33);
	}

	vector_complock.tam = 0;
	while(fgets(linea, sizeof(linea), f_compartimentoslockers) != NULL)
	    vector_complock.tam++;
	printf("Descuentos almacenados en CompartimentosLockers.txt: %d \n", vector_complock.tam);
    vector_complock.CompLock = malloc((vector_complock.tam + 1) * sizeof(CompartimentosLockers));
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

    FILE *f_lockers;
	char ruta[] = "..\\ESIZON-main\\data\\Lockers.txt";
	char linea[MAX_LOCK];
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

    FILE *f_complockers;
	char ruta[] = "..\\ESIZON-main\\data\\CompartimentosLockers.txt";
	char linea[MAX_COMPLOCK];
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

void Gestionar_Lockers(Vect_Lock L){

    int op;

    printf("###¿Qué desea hacer?###\n\n");															// Menu de seleccion de funciones relacionadas a descuentos
    printf("1. Crear locker\n");
    printf("2. Eliminar locker\n");
    printf("3. Listar lockers\n");
    printf("0. Salir\n");

    scanf("%d", &op);

    switch(op){
        case 1:
            Alta_Lockers(L);
            break;

        case 2:
            Baja_Lockers(L);
            break;

        case 3:
            Listar_Lockers(L);
            break;

        default:
            break;

    }
}


Vect_Lock Alta_Lockers(Vect_Lock L){

    int tam = L.tam;

    L.Lock = realloc(L.Lock, L.tam+1*sizeof(Vect_Lock));											// Se amplia la longitud del vector para añadir un locker en la estructura
    if (L.Lock == NULL){
        printf("No se pudo asignar la estructura de lockers");
        getchar();
        exit(EXIT_FAILURE);
    }

    L = nuevo_idL(L, tam);															// Conjunto de funciones para recopilar datos del nuevo locker
    L = nueva_localidadL(L, tam);
    L = nueva_provinciaL(L, tam);
    L = nueva_ubicaL(L, tam);
    L = nuevo_numcompTL(L, tam);
    L = nuevo_numcompOkupL(L, tam);

    return L;

}

Vect_Lock nuevo_idL(Vect_Lock L, int pos){

    char new_Id_locker[11];															// Variable que guardara la id del nuevo locker

    do{

    printf("Ingrese el identificador: \n");

    fflush(stdin);
    fgets(new_Id_locker, sizeof(new_Id_locker), stdin);

    strcpy(L.Lock[pos].Id_locker, new_Id_locker);	                                        // Se escribe en la nueva posicion de la estructura la nueva id

    }while(strlen(new_Id_locker) == 0);

    return L;

}

Vect_Lock nueva_localidadL(Vect_Lock L, int pos){

    char new_Localidad[11];															// Variable que guardara la localidad del nuevo locker

    do{

    printf("Ingrese la localidad: \n");

    fflush(stdin);
    fgets(new_Localidad, sizeof(new_Localidad), stdin);

    strcpy(L.Lock[pos].Localidad, new_Localidad);	                                        // Se escribe en la nueva posicion de la estructura la nueva localidad

    }while(strlen(new_Localidad) == 0);

    return L;

}

Vect_Lock nueva_provinciaL(Vect_Lock L, int pos){

    char new_Provincia[11];															// Variable que guardara la provincia del nuevo locker

    do{

    printf("Ingrese la provincia: \n");

    fflush(stdin);
    fgets(new_Provincia, sizeof(new_Provincia), stdin);

    strcpy(L.Lock[pos].Provincia, new_Provincia);	                                        // Se escribe en la nueva posicion de la estructura la nueva provincia

    }while(strlen(new_Provincia) == 0);

    return L;

}

Vect_Lock nueva_ubicaL(Vect_Lock L, int pos){

    char new_Ubica[11];															// Variable que guardara la ubicacion del nuevo locker

    do{

    printf("Ingrese la ubicacion: \n");

    fflush(stdin);
    fgets(new_Ubica, sizeof(new_Ubica), stdin);

    strcpy(L.Lock[pos].Ubica, new_Ubica);	                                        // Se escribe en la nueva posicion de la estructura la nueva ubicacion

    }while(strlen(new_Ubica) == 0);

    return L;

}

Vect_Lock nuevo_numcompTL(Vect_Lock L, int pos){

    int new_Num_compT;															// Variable que guardara los compartimentos totales del nuevo locker

    printf("Ingrese los compartimentos totales: \n");
    scanf("%d", &new_Num_compT);

    L.Lock[pos].Num_compT = new_Num_compT;	                                        // Se escribe en la nueva posicion de la estructura los compartimentos totales

    return L;

}

Vect_Lock nuevo_numcompOkupL(Vect_Lock L, int pos){

    int new_NumcompOkup;															// Variable que guardara los compartimentos ocupados del nuevo locker

    printf("Ingrese los compartimentos ocupados: \n");
    scanf("%d", &new_NumcompOkup);

    L.Lock[pos].Num_compOkup = new_NumcompOkup;	                                        // Se escribe en la nueva posicion de la estructura los compartimentos ocupados

    return L;

}

Vect_Lock Baja_Lockers(Vect_Lock L){

    char Id_locker_busqueda[11];
    int i;

    printf("Introduzca la id del locker a eliminar: \n");
    scanf("%s", &Id_locker_busqueda);

    for(i=0; i<L.tam; i++){
        if(strcmp(Id_locker_busqueda, L.Lock[i].Id_locker) == 0){

        }

    }

    return L;

}

void Listar_Lockers(Vect_Lock L){

    int i;
    clear();
    printf("+---------------------------------+\n");
    printf("| LOCKERS EN EL SISTEMA           |\n");
    printf("+---------------------------------+\n");

    for(i=1;i<L.tam;i++){
            printf("| %s-%s-%s-%s-%d-%d |\n",L.Lock[L.tam].Id_locker, L.Lock[L.tam].Localidad, L.Lock[L.tam].Provincia, L.Lock[L.tam].Ubica, L.Lock[L.tam].Num_compT, L.Lock[L.tam].Num_compOkup);
    }

    printf("+------------------------------+\n");
    printf("Presione [ENTER] para volver...");
    getchar();

}

int Locker_Dispo(Vect_Lock L, int pos){

    int i = 0;
    clients c = cargar_clientes();

    while((i<=L.tam) && (L.Lock[i].Localidad != c.clients[pos].Localidad))
        i++;

    return i;

}
