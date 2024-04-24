#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lockers.h"
#include "complementos.h"

Vect_Lock Cargar_Lockers(){

    Vect_Lock vector_lock;
	FILE *f_lockers;                                                                                                        // Puntero al fichero
	char ruta[] = "..\\ESIZON-main\\data\\Lockers.txt";                                                                     // Ruta del fichero a leer
	char linea[MAX_LOCK];                                                                                                   // Línea a leer
    int i = 0, m;

	if((f_lockers = fopen(ruta, "r+")) == NULL){
		printf("Error al abrir el fichero Lockers.txt.\n");
		exit(33);
	}

	vector_lock.tam = 0;
	while(fgets(linea, sizeof(linea), f_lockers) != NULL)                                                                   // Contamos el número de líneas del fichero
	    vector_lock.tam++;
	printf("Descuentos almacenados en Lockers.txt: %d \n", vector_lock.tam);
    vector_lock.Lock = malloc((vector_lock.tam + 1) * sizeof(Lockers));
	rewind(f_lockers);

	while((fgets(linea, sizeof(linea), f_lockers) != NULL) ){
		m = sscanf(linea, "%10[^-]-%20[^-]-%20[^-]-%20[^-]-%d[^-]-%d[^\n]\n",                                               // Se cargan los datos del fichero a la estructura
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
	fclose(f_lockers);                                                                                                      // Se cirra el fichero

    return vector_lock;
}

Vect_CompLock Cargar_CompartimentosLockers(){

    Vect_CompLock vector_complock;
	FILE *f_compartimentoslockers;                                                                                          // Puntero al fichero
	char ruta[] = "..\\ESIZON-main\\data\\CompartimentosLockers.txt";                                                       // Ruta del fichero a leer
	char linea[MAX_COMPLOCK];                                                                                               // Línea a leer
    int i = 0, m;

	if((f_compartimentoslockers = fopen(ruta, "r+")) == NULL){
		printf("Error al abrir el fichero CompartimentosLockers.txt.\n");
		exit(33);
	}

	vector_complock.tam = 0;
	while(fgets(linea, sizeof(linea), f_compartimentoslockers) != NULL)                                                     // Contamos el número de líneas del fichero
	    vector_complock.tam++;
	printf("Descuentos almacenados en CompartimentosLockers.txt: %d \n", vector_complock.tam);
    vector_complock.CompLock = malloc((vector_complock.tam + 1) * sizeof(CompartimentosLockers));
	rewind(f_compartimentoslockers);

	while((fgets(linea, sizeof(linea), f_compartimentoslockers) != NULL) ){
		m = sscanf(linea, "%d[^-]-%d[^-]-%d[^-]-%7[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^\n]\n",                       // Se cargan los datos del fichero a la estructura
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
	fclose(f_compartimentoslockers);                                                                                        // Se cirra el fichero

    return vector_complock;

}


void Guardar_Lockers(Vect_Lock lockers){

    FILE *f_lockers;                                                                                                        // Puntero al fichero a leer
	char ruta[] = "..\\ESIZON-main\\data\\Lockers.txt";                                                                     // Ruta del fichero a leer
	char linea[MAX_LOCK];                                                                                                   // Línea actual del fichero
	char aux[14];

	if((f_lockers = fopen(ruta, "a+")) == NULL){
		printf("\nError al abrir el fichero Lockers.txt\n");
		f_lockers = fopen(ruta, "w");
		Sleep(2000);
	}

	for(int i = 0; i < lockers.tam; i++)
		fprintf(f_lockers, "%10[^-]-%20[^-]-%20[^-]-%20[^-]-%d[^-]-%d[^\n]\n",                                              // Se escribe el contenido de la estructura en el fichero
            lockers.Lock[i].Id_locker,
			lockers.Lock[i].Localidad,
			lockers.Lock[i].Provincia,
			lockers.Lock[i].Ubica,
			lockers.Lock[i].Num_compT,
			lockers.Lock[i].Num_compOkup);

    fclose(f_lockers);                                                                                                      // Se cierra el fichero

}


void Guardar_CompartimentosLockers(Vect_CompLock compartimentoslockers){

    FILE *f_complockers;                                                                                                    // Puntero al fichero a leer
	char ruta[] = "..\\ESIZON-main\\data\\CompartimentosLockers.txt";                                                       // Ruta del fichero a leer
	char linea[MAX_COMPLOCK];                                                                                               // Línea actual del fichero
	char aux[14];

	if((f_complockers = fopen(ruta, "a+")) == NULL){
		printf("\nError al abrir el fichero CompartimentosLockers.txt\n");
		f_complockers = fopen(ruta, "w");
		Sleep(2000);
	}

	for(int i = 0; i < compartimentoslockers.tam; i++)
		fprintf(f_complockers, "%d[^-]-%d[^-]-%d[^-]-%7[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^-]-%d[^\n]\n",                  // Se escribe el contenido de la estructura en el fichero
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

    fclose(f_complockers);                                                                                                  // Se cierra el fichero

}

void Gestionar_Lockers(Vect_Lock L){

    int op;

    printf("###¿Qué desea hacer?###\n\n");															// Menu de seleccion de funciones relacionadas a lockers
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

    L.Lock[pos].Num_compOkup = 0;	                                        // Se escribe en la nueva posicion de la estructura los compartimentos ocupados (0)

    return L;

}

Vect_Lock Baja_Lockers(Vect_Lock L){

    char Id_locker_busqueda[11];
    int i, pos = -1;

    printf("Introduzca la id del locker a eliminar: \n");
    scanf("%s", &Id_locker_busqueda);                                                     //Se guarda la id del locker que se quiere eliminar en la variable de busqueda

    for(i=0; i<L.tam; i++){

        if(strcmp(Id_locker_busqueda, L.Lock[i].Id_locker) == 0){                         //Una vez se encuentra una coincidencia de la id de busqueda en la estructura

            for(pos = i; pos<L.tam; pos++){

                L.Lock[pos] = L.Lock[pos+1];                                              //Se asignan los lockers en la posicion anterior a partir de la instancia del locker

            }

            L.Lock = realloc(L.Lock, (L.tam - 1)*sizeof(Lockers));                       //Se reajusta la memoria asignada al vector de estructuras

            if (L.Lock == NULL){
                printf("No se pudo asignar la estructura de descuentosclientes");
                getchar();
                exit(EXIT_FAILURE);
            }

            L.tam = L.tam - 1;                                                            //Se reduce el tamaño total del vector de estructuras
            break;
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

    int i = 0, res = -1;

    clients c = cargar_clientes();                                                                                              //Se carga la estructura clientes

    while((i<=L.tam) && (L.Lock[i].Localidad != c.clients[pos].Localidad) && (L.Lock[i].Num_compOkup < L.Lock[i].Num_compT))
        i++;

    if(L.Lock[i].Localidad == c.clients[pos].Localidad)                                                                         //Se busca una coincidencia de localidades
        res = i;

    else
        printf("No existe ningún locker disponible en tu localidad \n");

    return res;

}


int Comp_Dispo(Vect_Lock L, Vect_CompLock C, int cli){

    int i = 0, pos;
    pos = Locker_Dispo(L, cli);                                                                                                 //Se busca la primera posicion del vector de lockers con un locker disponible

    while((i<=C.tam) && (C.CompLock[i].Id_locker != L.Lock[pos].Id_locker) && (C.CompLock[i].Estado != "ocupado"))
        i++;

    strcpy(C.CompLock[i].Estado, "ocupado");                                                                                    //Se actualiza el estado del locker

    return i;                                                                                                                   //Devuelve la posicion del primer vector de compartimentos lockers disponible

}


Vect_CompLock Asignar_Compartimentos(Vect_Lock L, Vect_CompLock C){

    int i, j, cont = 0, n_comp = 0;
    char Id_locker_busqueda[11];


    printf("Indique la ID del locker al que quiere asignarle los compartimentos \n");
    scanf("%s", &Id_locker_busqueda);                                                                                                       //Se guarda la id del locker que se quiere eliminar en la variable de busqueda

    for(i=0; i<L.tam; i++){

            if(strcmp(Id_locker_busqueda, L.Lock[i].Id_locker) == 0){                                                                       //Una vez se encuentra una coincidencia de la id de busqueda en la estructura

                    C.CompLock = realloc(C.CompLock, (L.Lock[i].Num_compT - L.Lock[i].Num_compOkup)*sizeof(CompartimentosLockers));	        //Se reasigna la memoria reservada para el vector de compartimentos lockers
                    if (C.CompLock == NULL){
                        printf("No se pudo asignar la estructura de descuentosclientes");
                        getchar();
                        exit(EXIT_FAILURE);
                    }

                    cont = C.tam - (L.Lock[i].Num_compT - L.Lock[i].Num_compOkup);                                                          //Se ajustan los parametros de los contadores para recorrer la estructura y para saber el numero del compartimento correspondiente
                    n_comp = L.Lock[i].Num_compOkup  + 1;
                    do{

                        strcpy(C.CompLock[cont].Id_locker, Id_locker_busqueda);
                        strcpy(C.CompLock[cont].Estado, "vacío");
                        C.CompLock[cont].Num_comp = n_comp;
                        C.CompLock[cont].dia_okup = 0;
                        C.CompLock[cont].mes_okup = 0;
                        C.CompLock[cont].anio_okup = 0;
                        C.CompLock[cont].dia_cad = 0;
                        C.CompLock[cont].mes_cad = 0;
                        C.CompLock[cont].anio_cad = 0;

                        n_comp++;
                        cont++;
                    }while(cont != C.tam);

            }

        }

        return C;
}

Vect_CompLock Recogida_Locker(Vect_CompLock cl, int pos, int n_comp){

    int cont = 0, i, Cod_locker_check, fch;

    fecha fch_comprobar;
    fch_comprobar.dia = cl.CompLock[i].dia_cad;
    fch_comprobar.mes = cl.CompLock[i].mes_cad;
    fch_comprobar.anio = cl.CompLock[i].anio_cad;

    fecha fch_sist;
    fch_sist.dia = dia_sist();
    fch_sist.mes = mes_sist();
    fch_sist.anio = anio_sist();

    fch = comprobar_fecha(fch_sist, fch_comprobar);                                                                                 //Se comprueba que la fecha de caducidad no se haya sobrepasado

    pedidos p = cargar_pedidos();                                                                                                   //Se carga la estructuta CompartimentosLockers

    for(i = 0; i<cl.tam; i++){
        if((strcpy(p.pedidos[pos].id_locker, cl.CompLock[i].Id_locker) == 0) && cl.CompLock[i].Num_comp == n_comp && fch == 1){     //Se comprueba que exista el compartimento deseado

            do{
                printf("Introduzca el código de seguridad del locker: \n");                                                         //Se introduce el código de seguridad
                scanf("%d", &Cod_locker_check);

                if(Cod_locker_check == cl.CompLock[i].Cod_locker){                                                                  //Se comprueba el código de seguridad
                    printf("Código introducido correctamente \n");
                    printf("Se ha abierto el compartimento número %d \n", &n_comp);
                    strcpy(cl.CompLock[i].Estado, "vacío");

                }
                else{
                    printf("Código incorrecto, inténtelo nuevamente: \n \n");
                }
                cont++;
            }while(cont < 3);

            if(cont == 3)
                printf("Se ha quedado sin intentos, cancelando operación... \n");                                                   //En caso de fallar el código 3 veces el sistema cancela la operación

        }
    }

    return cl;

}


