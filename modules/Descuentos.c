#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Descuentos.h"
#include "complementos.h"
#include "useradmin.h"



Descuentos Cargar_Descuentos(){

    Descuentos vector_desc;
	FILE *f_descuentos;																	// Puntero al fichero
	char ruta[] = "..\\data\\Descuentos.txt";                                                  						// Ruta del fichero a leer
	char linea[MAX_DESC];													                                // Línea a leer
    int i = 0, m;

	if((f_descuentos = fopen(ruta, "r+")) == NULL){
		printf("Error al abrir el fichero Descuentos.txt.\n");
		exit(33);
	}

	vector_desc.tam = 0;
	while(fgets(linea, sizeof(linea), f_descuentos) != NULL)												// Contamos el número de líneas del fichero
	    vector_desc.tam++;
	printf("Descuentos almacenados en Descuentos.txt: %d \n", vector_desc.tam);
    vector_desc.Desc = malloc((vector_desc.tam + 1) * sizeof(Descuento));											// Se reserva memoria para el vector
	rewind(f_descuentos);

	while((fgets(linea, sizeof(linea), f_descuentos) != NULL) ){
		m = sscanf(linea, "%10[^-]-%50[^-]-%7[^-]-%8[^-]-%d-%6[^\n]\n",										// Se cargan los datos del fichero a la estructura
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
	fclose(f_descuentos); 																	// Se cirra el fichero

    return vector_desc;
}


DescClientes Cargar_DescuentosClientes(){

    DescClientes vector_descClts;
	FILE *f_DescClientes;																	// Puntero al fichero a leer
	char ruta[] = "..\\ESIZON-main\\data\\DescuentosClientes.txt";                                                  					// Ruta del fichero a leer
	char linea[MAX_DESCLI];													                                // Linea a leer
    int i = 0, m;

	if((f_DescClientes = fopen(ruta, "r+")) == NULL){
		printf("Error al abrir el fichero DescuentosClientes.txt.\n");
		exit(33);
	}
	vector_descClts.tam = 0;
	while(fgets(linea, sizeof(linea), f_DescClientes) != NULL)												// Contamos el numero de lineas del fichero
	    vector_descClts.tam++;
	    printf("Descuentos almacenados en DescuentosClientes.txt: %d \n", vector_descClts.tam);
        vector_descClts.DescCliente = malloc((vector_descClts.tam + 1) * sizeof(DescClientes));									// Se reserva memoria para el vector
	 	rewind(f_DescClientes);

		while((fgets(linea, sizeof(linea), f_DescClientes) != NULL) ){
			if((m = sscanf(linea, "%d-%10[^-]-%d-%d-%d-%d-%d-%d-%d\n",						// Se cargan los datos del fichero a la estructura
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

	fclose(f_DescClientes);																	// Se cierra el fichero

    return vector_descClts;
}


void Guardar_Descuentos(Descuentos descuentos){

    FILE *f_descuentos;																		// Puntero al fichero a leer
	char ruta[] = "..\\ESIZON-main\\data\\Descuentos.txt";													// Ruta del fichero a leer
	char linea[MAX_DESC];																	// Línea actual del fichero
	char aux[14];

	if((f_descuentos = fopen(ruta, "a+")) == NULL){
		printf("\nError al abrir el fichero Descuentos.txt\n");
		f_descuentos = fopen(ruta, "w");
		Sleep(2000);
	}

	for(int i = 0; i < descuentos.tam; i++)
		fprintf(f_descuentos, "%10[^-]-%50[^-]-%7[^-]-%8[^-]-%d-%6[^\n]\n",										// Se escribe el contenido de la estructura en el fichero
            descuentos.Desc[i].Id_cod,
            descuentos.Desc[i].Descrip,
			descuentos.Desc[i].Tipo,
			descuentos.Desc[i].Estado,
			descuentos.Desc[i].Importe,
			descuentos.Desc[i].Aplicable);


        fclose(f_descuentos);																	// Se cierra el fichero

}


void Guardar_DescuentosClientes(DescClientes descuentosclientes){

    FILE *f_DescClientes;																	// Puntero al fichero
	char ruta[] = "..\\ESIZON-main\\data\\DescuentosClientes.txt";												// Ruta del fichero
	char linea[MAX_DESCLI];																	// Línea actual del fichero
	char aux[14];

	if((f_DescClientes = fopen(ruta, "a+")) == NULL){
		printf("\nError al abrir el fichero DescuentosClientes.txt\n");
		f_DescClientes = fopen(ruta, "w");
		Sleep(2000);
	}

	for(int i = 0; i < descuentosclientes.tam; i++)
		fprintf(f_DescClientes, "%d-%10[^-]-%d-%d-%d-%d-%d-%d-%d\n",							// Se escribe el contenido de la estructura en el fichero
            descuentosclientes.DescCliente[i].Id_cliente,
            descuentosclientes.DescCliente[i].Id_cod,
            descuentosclientes.DescCliente[i].dia_asig,
            descuentosclientes.DescCliente[i].mes_asig,
            descuentosclientes.DescCliente[i].anio_asig,
            descuentosclientes.DescCliente[i].dia_cad,
            descuentosclientes.DescCliente[i].mes_cad,
            descuentosclientes.DescCliente[i].anio_cad);


        fclose(f_DescClientes);																	// Se cierra el fichero


}


void Consultar_Descuentos(DescClientes descuentosclientes){

    int i,j;
    clients cliente = cargar_clientes();

	for(i = 0; i < cliente.n_clients; i++){
          for(j = 0; j < descuentosclientes.tam; j++){
            if ((descuentosclientes.DescCliente[j].Id_cliente == cliente.clients[i].Id_cliente) && descuentosclientes.DescCliente[j].Estado == 0)		// Se comprueba que el identificador del cliente buscado esta asociado con algun descuento
                printf("Descuento disponible: %s \n", &descuentosclientes.DescCliente[j].Id_cod);								// Lista los descuentos disponibles para el usuario en concreto

        }

	}

}

void Consultar_desc_cliente(int pos){

    clients Cliente = cargar_clientes();
    DescClientes desccl = Cargar_DescuentosClientes();
    int i,
        n_desc=0;
    clear();
    printf("+---------------------------+");
    printf("|    TUS DESCUENTOS         |");
    printf("+---------------------------+");
    for(i=1;i<desccl.tam;i++){
        if(Cliente.clients[pos].Id_cliente == desccl.DescCliente[i].Id_cliente){
            if(desccl.DescCliente[i].Estado == 0)
                printf("| CODIGO: %-10s ASIGNADO: %d/%d/%d CADUCADO: %d/%d/%d --> Disponible |\n", desccl.DescCliente[i].Id_cod,
                                                                                                    desccl.DescCliente[i].dia_asig,
                                                                                                    desccl.DescCliente[i].mes_asig,
                                                                                                    desccl.DescCliente[i].anio_asig,
                                                                                                    desccl.DescCliente[i].dia_cad,
                                                                                                    desccl.DescCliente[i].mes_cad,
                                                                                                    desccl.DescCliente[i].anio_cad);
            else
                printf("| CODIGO: %-10s ASIGNADO: %d/%d/%d CADUCADO: %d/%d/%d --> No disponible |\n", desccl.DescCliente[i].Id_cod,
                                                                                                    desccl.DescCliente[i].dia_asig,
                                                                                                    desccl.DescCliente[i].mes_asig,
                                                                                                    desccl.DescCliente[i].anio_asig,
                                                                                                    desccl.DescCliente[i].dia_cad,
                                                                                                    desccl.DescCliente[i].mes_cad,
                                                                                                    desccl.DescCliente[i].anio_cad);
        n_desc++;
        }
    }
    if(n_desc == 0){
        printf("| NO TIENES CUPONES DISPONIBLES |\n");
        printf("+---------------------------+");
    }
}


void Gestionar_Descuentos(Descuentos D, DescClientes dc){

    int op;
    clients cliente = cargar_clientes();

    printf("###¿Qué desea hacer?###\n\n");															// Menu de seleccion de funciones relacionadas a descuentos
    printf("1. Dar de alta\n");
    printf("2. Dar de baja\n");
    printf("3. Realizar búsqueda\n");
    printf("4. Listar descuentos\n");
    printf("5. Modificar descuentos\n");
    printf("6. Asignar descuentos\n");
    printf("0. Salir\n");

    scanf("%d", &op);

    switch(op){
        case 1:
            Alta_Descuentos(D);
            break;
        case 2:
            Baja_Descuentos(D);
            break;
        case 3:
            Busqueda_Descuentos(D);
            break;
        case 4:
            Listar_Descuentos(D);
            break;
        case 5:
            Modificar_Descuentos(D);
            break;
        case 6:
            Asignar_Descuentos(D,dc);
            break;
        default:
            break;

    }
}


Descuentos Alta_Descuentos(Descuentos D){

    int tam = D.tam;

    D.Desc = realloc(D.Desc, D.tam+1*sizeof(Descuento));											// Se amplia la longitud del vector para añadir un descuento en la estructura
    if (D.Desc == NULL){
        printf("No se pudo asignar la estructura de descuentos");
        getchar();
        exit(EXIT_FAILURE);
    }

    D = nuevo_id(D, tam);															// Conjunto de funciones para recopilar datos del nuevo descuento
    D = nueva_desc(D, tam);
    D = nuevo_tipo(D, tam);
    D = nuevo_est(D, tam);
    D = nuevo_apl(D, tam);
    D = nuevo_imp(D, tam);

    return D;

}

Descuentos nuevo_id(Descuentos D, int pos){
    char new_Id_cod[11];															// Variable que guardara la id del nuevo descuento

    do{

    printf("Ingrese el identificador: \n");

    fflush(stdin);
    fgets(new_Id_cod, sizeof(new_Id_cod), stdin);

    strcpy(D.Desc[pos].Id_cod, new_Id_cod);	                                        // Se escribe en la nueva posicion de la estructura la nueva id

    }while(strlen(new_Id_cod) == 0);

    return D;
}


Descuentos nueva_desc(Descuentos D, int pos){
    char new_Descrip[11];															// Variable que guardara la descripcion del nuevo descuento

    do{

    printf("Ingrese la descripción: \n");

    fflush(stdin);
    fgets(new_Descrip, sizeof(new_Descrip), stdin);

    strcpy(D.Desc[pos].Descrip, new_Descrip);													// Se escribe en la nueva posicion de la estructura la nueva descripcion

    }while(strlen(new_Descrip) == 0);

    return D;
}



Descuentos nuevo_tipo(Descuentos D, int pos){

    int op = 0;

    while(op != 1 || op != 2){
        printf("Elija el tipo de descuento: \n");
        printf("1. Código promocional\n");
        printf("2. Cheque regalo\n");
        scanf("%d", &op);

        switch(op){

            case 1:
                strcpy(D.Desc[pos].Tipo, "codpro");												// Se escribe en la nueva posicion de la estructura el tipo "codpro"
                break;

            case 2:
                strcpy(D.Desc[pos].Tipo, "cheqreg");												// Se escribe en la nueva posicion de la estructura el tipo "cheqreg"
                break;

            default:
                break;

        }
    }

    return D;
}


Descuentos nuevo_est(Descuentos D, int pos){

    int op = 0;

    while(op != 1 || op != 2){
        printf("Seleccione el estado: \n");
        printf("1. Activo\n");
        printf("2. Inactivo\n");
        scanf("%d", &op);

        switch(op){

            case 1:
                strcpy(D.Desc[pos].Estado, "activo");												// Se escribe en la nueva posicion de la estructura el estado "activo"
                break;

            case 2:
                strcpy(D.Desc[pos].Estado, "inactivo");												// Se escribe en la nueva posicion de la estructura el estado "inactivo"
                break;

            default:
                break;

        }
    }

    return D;
}


Descuentos nuevo_apl(Descuentos D, int pos){

    int op = 0;

    while(op != 1 || op != 2){
        printf("Seleccione la aplicabilidad: \n");
        printf("1. Aplicable solo para productos gestionados por ESIZON\n");
        printf("2. Aplicable para todos los productos\n");
        scanf("%d", &op);

        switch(op){

            case 1:
                strcpy(D.Desc[pos].Aplicable, "esizon");											// Se escribe en la nueva posicion de la estructura la aplicabilidad "esizon"
                break;

            case 2:
                strcpy(D.Desc[pos].Aplicable, "todos");											// Se escribe en la nueva posicion de la estructura la aplicabilidad "todos"
                break;

            default:
                break;

        }
    }

    return D;
}


Descuentos nuevo_imp(Descuentos D, int pos){

    int new_Importe = 0;															// Variable que guardara el importe del nuevo descuentos

    printf("Introduzca el importe: \n");
    scanf("%d", &new_Importe);

        D.Desc[pos].Importe = new_Importe;													// Se escribe en la nueva posicion de la estructura el importe introducido

    return D;
}


Descuentos Baja_Descuentos(Descuentos D){
    int tam = D.tam, i;
    char Id_cod_busqueda[11];			                    								// Variables que serviran como filtro a la hora de buscar el descuento que se dara de baja

    printf("Introduzca el identificador del descuento que quiere dar de baja\n");
    scanf("%s", &Id_cod_busqueda);

    for(i=0; i<tam; i++){
        if(strcmp(Id_cod_busqueda, D.Desc[i].Id_cod) == 0)
            strcpy(D.Desc[i].Estado, "inactivo");												// Se actualiza el del descuento encontrado, dejandolo "inactivo" en caso de querer darlo de alta en el futuro
    }

    return D;
}


Descuentos Busqueda_Descuentos(Descuentos D){

    int tam = D.tam, i;
    char Id_cod_busqueda[11];															// Variable que servira como filtro a la hora de buscar el descuento deseado

    printf("Introduzca el identificador del descuento que quiere buscar\n");
    scanf("%s", &Id_cod_busqueda);

    for(i=0; i<tam; i++){
        if(strcmp(Id_cod_busqueda, D.Desc[i].Id_cod) == 0)
            printf("Descuento encontrado %i: %s\n", &i, &Id_cod_busqueda);									// Se muestra el descuento(s) encontrado
    }

    return D;
}



Descuentos Listar_Descuentos(Descuentos D){

    int tam = D.tam, i;																// Variables para controlar el bucle
    for(i=0; i<tam; i++){
        printf("Código de descuento %i: %s\n", &i, &D.Desc[i].Id_cod);										// Se muestra en cada iteracion el contenido de cada linea del fichero
    }

    return D;
}


Descuentos Modificar_Descuentos(Descuentos D){
    int tam = D.tam, i, op;
    char Id_cod_busqueda[11];															// Variable en la que se almacena el codigo del descuento a modificar

    printf("Introduzca el identificador del descuento que quiere modificar\n");
    scanf("%s", &Id_cod_busqueda);

    for(i=0; i<tam; i++){
        if(strcmp(Id_cod_busqueda, D.Desc[i].Id_cod) == 0){											// Cuando exista una coincidencia se despliega un menu con las distintas opciones de modificacion

            printf("Indique que quiere modificar:\n\n");
            printf("1. ID\n");
            printf("2. Descripcion\n");
            printf("3. Tipo\n");
            printf("4. Estado\n");
            printf("5. Aplicabilidad\n");
            printf("6. Importe\n");
            printf("0. Cancelar");
            scanf("%i", &op);

            switch(op){
                case 1:
                    D = nuevo_id(D, tam);
                    break;
                case 2:
                    D = nueva_desc(D, tam);
                    break;
                case 3:
                    D = nuevo_tipo(D, tam);
                    break;
                case 4:
                    D = nuevo_est(D, tam);
                    break;
                case 5:
                    D = nuevo_apl(D, tam);
                    break;
                case 6:
                    D = nuevo_imp(D, tam);
                    break;
                default:
                    break;
            }
        }
    }

    return D;
}

Descuentos Asignar_Descuentos(Descuentos D, DescClientes dc){

    clients cliente = cargar_clientes();
    int tamD = D.tam, tamC = cliente.n_clients, i, j, Id_cli_busqueda, n_dia_a, n_mes_a, n_anio_a, n_dia_c, n_mes_c, n_anio_c;
    char Id_cod_busqueda[11];                                                                                                       // Variable en la que se almacena el codigo del descuento a asignar

    dc.DescCliente = realloc(dc.DescCliente, dc.tam+1*sizeof(DescCliente));											                // Se amplia la longitud del vector para añadir un descuento en la estructura
    if (dc.DescCliente == NULL){
        printf("No se pudo asignar la estructura de descuentosclientes");
        getchar();
        exit(EXIT_FAILURE);
    }

    printf("Introduzca el ID del cliente al que quiere asignar el descuento\n");
    scanf("%i", &Id_cli_busqueda);

    for(i=0; i<tamC; i++){
        if(Id_cli_busqueda == cliente.clients[i].Id_cliente){

            printf("Introduzca el codigo del descuento que quiere asignarle\n");
            scanf("%s", &Id_cod_busqueda);

            for(j=0; j>tamD; j++){
                if(strcmp(Id_cod_busqueda, dc.DescCliente[i].Id_cod) == 0){

                    printf("Introduzca el dia de hoy\n");
                    scanf("%i",&n_dia_a);
                    printf("Introduzca el mes de hoy\n");
                    scanf("%i",&n_mes_a);
                    printf("Introduzca el año de hoy\n");
                    scanf("%i",&n_anio_a);
                    printf("Introduzca el dia de caducidad\n");
                    scanf("%i",&n_dia_c);
                    printf("Introduzca el mes de caducidad\n");
                    scanf("%i",&n_mes_c);
                    printf("Introduzca el año de caducidad\n");
                    scanf("%i",&n_anio_c);


                    strcpy(dc.DescCliente[tamC].Id_cod, Id_cod_busqueda);
                    dc.DescCliente[tamC].Id_cliente = Id_cli_busqueda;
                    dc.DescCliente[tamC].dia_asig = n_dia_a;
                    dc.DescCliente[tamC].mes_asig = n_mes_a;
                    dc.DescCliente[tamC].anio_asig = n_anio_a;
                    dc.DescCliente[tamC].dia_cad = n_dia_c;
                    dc.DescCliente[tamC].mes_cad = n_mes_c;
                    dc.DescCliente[tamC].anio_cad = n_anio_c;
                    dc.DescCliente[tamC].Estado = 0;

                }

            }

        }

    }
}

