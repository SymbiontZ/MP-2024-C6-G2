#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Descuentos.h"
#include "complementos.h"
#include "useradmin.h"



Descuentos Cargar_Descuentos(){

    Descuentos vector_desc;
	FILE *f_descuentos;																	// Puntero al fichero
	char ruta[] = "../data/Descuentos.txt";                                                  						// Ruta del fichero a leer
	char linea[MAX_DESC];													                                // Línea a leer
    int i = 0, m;

	if((f_descuentos = fopen(ruta, "a+")) == NULL){
		printf("Error al abrir el fichero Descuentos.txt.\n");
		exit(33);
	}



	vector_desc.tam = 0;
	while(fgets(linea, sizeof(linea), f_descuentos) != NULL)												// Contamos el número de líneas del fichero
	    vector_desc.tam++;
	printf("Descuentos almacenados en Descuentos.txt: %d \n", vector_desc.tam);
    vector_desc.Desc = malloc((vector_desc.tam + 1) * sizeof(Descuento));
    											// Se reserva memoria para el vector
	rewind(f_descuentos);


	while((fgets(linea, sizeof(linea), f_descuentos) != NULL) ){
		m = sscanf(linea, "%11[^-]-%51[^-]-%8[^-]-%9[^-]-%d-%7[^\n]\n",										// Se cargan los datos del fichero a la estructura
            vector_desc.Desc[i].Id_cod,
			vector_desc.Desc[i].Descrip,
			vector_desc.Desc[i].Tipo,
			vector_desc.Desc[i].Estado,
			&vector_desc.Desc[i].Importe,
			vector_desc.Desc[i].Aplicable);

			i++;
		if(m != 6){
			printf("Error leyendo datos del fichero Descuentos.txt. Linea: %d\n", i + 1);
            getchar();
			exit(EXIT_FAILURE);
		}
	}

	fclose(f_descuentos); 																	// Se cirra el fichero

    return vector_desc;
}


DescClientes Cargar_DescuentosClientes(){

    DescClientes vector_descClts;
	FILE *f_DescClientes;																	// Puntero al fichero a leer
	char ruta[] = "../data/DescuentosClientes.txt";                                                  					// Ruta del fichero a leer
	char linea[MAX_DESCLI];													                                // Linea a leer
    int i = 0, m;

	if((f_DescClientes = fopen(ruta, "a+")) == NULL){
		printf("Error al abrir el fichero DescuentosClientes.txt.\n");
        Sleep(2000);
	}

	vector_descClts.tam = 0;

    rewind(f_DescClientes);

	while(fgets(linea, sizeof(linea), f_DescClientes) != NULL)												// Contamos el numero de lineas del fichero
	    vector_descClts.tam++;

    vector_descClts.DescCliente = malloc((vector_descClts.tam) * sizeof(DescCliente));		    							// Se reserva memoria para el vector
	rewind(f_DescClientes);


	while((fgets(linea, sizeof(linea), f_DescClientes) != NULL) ){
		m = sscanf(linea, "%d-%11[^-]-%d/%d/%d-%d/%d/%d-%d\n",						// Se cargan los datos del fichero a la estructura
            &vector_descClts.DescCliente[i].Id_cliente,
            vector_descClts.DescCliente[i].Id_cod,
            &vector_descClts.DescCliente[i].dia_asig,
            &vector_descClts.DescCliente[i].mes_asig,
            &vector_descClts.DescCliente[i].anio_asig,
            &vector_descClts.DescCliente[i].dia_cad,
            &vector_descClts.DescCliente[i].mes_cad,
            &vector_descClts.DescCliente[i].anio_cad,
            &vector_descClts.DescCliente[i].Estado);

		if(m != 9){
			printf("Error leyendo datos del fichero DescuentosClientes.txt. Linea: %d %d\n", i,m);
            getchar();
			exit(EXIT_FAILURE);
		}
        i++;
	}

	fclose(f_DescClientes);
    																// Se cierra el fichero
    return vector_descClts;
}


void Guardar_Descuentos(Descuentos descuentos){

    FILE *f_descuentos;																		// Puntero al fichero a leer
	char ruta[] = "..\\data\\Descuentos.txt";													// Ruta del fichero a leer
	char linea[MAX_DESC];																	// Línea actual del fichero
	char aux[14];

	f_descuentos = fopen(ruta, "w");

	for(int i = 0; i < descuentos.tam; i++)
		fprintf(f_descuentos, "%s-%s-%s-%s-%d-%s\n",										// Se escribe el contenido de la estructura en el fichero
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
	char ruta[] = "..\\data\\DescuentosClientes.txt";												// Ruta del fichero
	char linea[MAX_DESCLI];																	// Línea actual del fichero
	char aux[14];

	f_DescClientes = fopen(ruta, "w");


	for(int i = 0; i < descuentosclientes.tam; i++)
		fprintf(f_DescClientes, "%07d-%s-%02d/%02d/%04d-%02d/%02d/%04d-%d\n",							// Se escribe el contenido de la estructura en el fichero
            descuentosclientes.DescCliente[i].Id_cliente,
            descuentosclientes.DescCliente[i].Id_cod,
            descuentosclientes.DescCliente[i].dia_asig,
            descuentosclientes.DescCliente[i].mes_asig,
            descuentosclientes.DescCliente[i].anio_asig,
            descuentosclientes.DescCliente[i].dia_cad,
            descuentosclientes.DescCliente[i].mes_cad,
            descuentosclientes.DescCliente[i].anio_cad,
            descuentosclientes.DescCliente[i].Estado);


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

void Consultar_desc_cliente(int pos, int mode){
    clients Cliente = cargar_clientes();
    DescClientes desccl = Cargar_DescuentosClientes();

    int i,
        n_desc=0,
        activo;
    clear();


    if(mode == 0){
        printf("+---------------------------+\n");
        printf("|    TUS DESCUENTOS         |\n");
        printf("+---------------------------+\n");
        for(i=1;i<desccl.tam;i++){
            if(Cliente.clients[pos].Id_cliente == desccl.DescCliente[i].Id_cliente){
                if(desccl.DescCliente[i].Estado == 0)
                    printf("| CODIGO: %-10s ASIGNADO: %02d/%02d/%04d CADUCADO: %02d/%02d/%04d --> No aplicado |\n", desccl.DescCliente[i].Id_cod,
                                                                                                        desccl.DescCliente[i].dia_asig,
                                                                                                        desccl.DescCliente[i].mes_asig,
                                                                                                        desccl.DescCliente[i].anio_asig,
                                                                                                        desccl.DescCliente[i].dia_cad,
                                                                                                        desccl.DescCliente[i].mes_cad,
                                                                                                        desccl.DescCliente[i].anio_cad);
                else
                    printf("| CODIGO: %-10s ASIGNADO: %02d/%02d/%04d CADUCADO: %02d/%02d/%04d --> Aplicado |\n", desccl.DescCliente[i].Id_cod,
                                                                                                        desccl.DescCliente[i].dia_asig,
                                                                                                        desccl.DescCliente[i].mes_asig,
                                                                                                        desccl.DescCliente[i].anio_asig,
                                                                                                        desccl.DescCliente[i].dia_cad,
                                                                                                        desccl.DescCliente[i].mes_cad,
                                                                                                        desccl.DescCliente[i].anio_cad);
            n_desc++;
            }
        }
    }else{
        for(i=1;i<desccl.tam;i++){
            if(Cliente.clients[pos].Id_cliente == desccl.DescCliente[i].Id_cliente){
                if(desccl.DescCliente[i].Estado == 0 && desc_activo(desccl.DescCliente[i].Id_cod) == 1)
                    printf("| CODIGO: %-10s |\n", desccl.DescCliente[i].Id_cod);
            n_desc++;
            }
        }
    }

    if(n_desc == 0){
        printf("| NO TIENES CUPONES DISPONIBLES |\n");
        printf("+-------------------------------+");
    }

}

void marcar_aplicado(int id_cliente, char cod[]){
    DescClientes DescC = Cargar_DescuentosClientes();
    int i,pos = -1;

    for(i=1; i< DescC.tam ; i++){
        if(DescC.DescCliente[i].Id_cliente == id_cliente && strcmp(DescC.DescCliente[i].Id_cod, cod) == 0)
            pos = i;
    }

    if(pos != -1){
        DescC.DescCliente[pos].Estado = 1;
    }else{
        printf("No se pudo marcar el descuento como aplicado.\n");
        getchar();
    }

    Guardar_DescuentosClientes(DescC);
    free(DescC.DescCliente);
}


int desc_activo(char cod[]){
    Descuentos D = Cargar_Descuentos();
    int i, pos = -1;

    for(i=0; i< D.tam; i++){
        if(strcmp(D.Desc[i].Id_cod, cod)== 0)
            pos = i;
    }

    if (pos == -1){
        printf("No se pudo encontrar el codigo del descuento [%s] (COMPROBACION DISPONIBILIDAD GENERAL)", cod);
        getchar();
        return 0;

    }
    if(strcmp(D.Desc[pos].Estado, "activo") == 0)
        return 1;
    else
        return 0;
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
    fgets(new_Id_cod, sizeof(new_Id_cod)+1, stdin);
    terminador_cad(new_Id_cod);

    strcpy(D.Desc[pos].Id_cod, new_Id_cod);	                                        // Se escribe en la nueva posicion de la estructura la nueva id

    }while(strlen(new_Id_cod) == 0);

    return D;
}


Descuentos nueva_desc(Descuentos D, int pos){
    char new_Descrip[11];															// Variable que guardara la descripcion del nuevo descuento

    do{

    printf("Ingrese la descripción: \n");

    fflush(stdin);
    fgets(new_Descrip, sizeof(new_Descrip)+1, stdin);
    terminador_cad(new_Descrip);

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
    char Id_cod_busqueda[11];
    int i, pos = -1;

    printf("Introduzca la id del descuento a eliminar: \n");

                                                                                            //Se guarda la id del descuento que se quiere eliminar en la variable de busqueda
    fflush(stdin);
    fgets(Id_cod_busqueda, sizeof(Id_cod_busqueda)+1, stdin);
    terminador_cad(Id_cod_busqueda);

    for(i=0; i<D.tam; i++){

        if(strcmp(Id_cod_busqueda, D.Desc[i].Id_cod) == 0){                                 //Una vez se encuentra una coincidencia de la id de busqueda en la estructura

            for(pos = i; pos<D.tam; pos++){

                D.Desc[pos] = D.Desc[pos+1];                                              //Se asignan los descuentos en la posicion anterior a partir de la instancia del descuento

            }

            D.Desc = realloc(D.Desc, (D.tam - 1)*sizeof(Descuentos));                       //Se reajusta la memoria asignada al vector de estructuras

            if (D.Desc == NULL){
                printf("No se pudo asignar la estructura de descuentosclientes");
                getchar();
                exit(EXIT_FAILURE);
            }

            D.tam = D.tam - 1;                                                            //Se reduce el tamaño total del vector de estructuras
            break;
        }
    }



    return D;

}


Descuentos Busqueda_Descuentos(Descuentos D){

    int tam = D.tam, i;
    char Id_cod_busqueda[11];															// Variable que servira como filtro a la hora de buscar el descuento deseado

    printf("Introduzca el identificador del descuento que quiere buscar\n");

    fflush(stdin);
    fgets(Id_cod_busqueda, sizeof(Id_cod_busqueda)+1, stdin);
    terminador_cad(Id_cod_busqueda);

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

    fflush(stdin);
    fgets(Id_cod_busqueda, sizeof(Id_cod_busqueda)+1, stdin);
    terminador_cad(Id_cod_busqueda);

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

void Asignar_Descuentos(DescClientes dc, int id_cliente, fecha fch_cad){
    Descuentos D = Cargar_Descuentos();
    char cod_desc[11];
    int i,cod_ok = 0;
    int new_pos = dc.tam;
    dc.DescCliente = realloc(dc.DescCliente, (dc.tam+1)*sizeof(DescCliente));											                // Se amplia la longitud del vector para añadir un descuento en la estructura
    if (dc.DescCliente == NULL){
        printf("No se pudo asignar la estructura de descuentosclientes");
        getchar();
        exit(EXIT_FAILURE);
    }

    do
    {
        printf("Introduzca el codigo de descuento a asignar:");
        fflush(stdin);
        fgets(cod_desc, 11, stdin);
        terminador_cad(cod_desc);

        for(i=1;i<D.tam;i++){
            if(strcmp(cod_desc, D.Desc[i].Id_cod)==0)
                cod_ok = 1;
        }

        if (cod_ok != 1){
            printf("Codigo de descuento no valido. Vuelva a intentarlo.\n");
        }

    } while (cod_ok != 1);
    
    dc.DescCliente[new_pos].Id_cliente = id_cliente;

    strcpy(dc.DescCliente[new_pos].Id_cod, cod_desc);

    //FECHA DE ASIGNACION
    fecha fch_sist;
    fch_sist.dia = dia_sist();
    fch_sist.mes = mes_sist();
    fch_sist.anio = anio_sist();

    dc.DescCliente[new_pos].dia_asig = fch_sist.dia;
    dc.DescCliente[new_pos].mes_asig = fch_sist.mes;
    dc.DescCliente[new_pos].anio_asig = fch_sist.anio;

    //FECHA DE CADUCIDAD
    int fch_ok;
    do{
        fch_ok = comprobar_fecha(fch_sist, fch_cad);
        printf(" comp: %d ", fch_ok);
        if(fch_ok != 1){
            printf("Fecha de caducidad no valida. Genera una valida.\n");
            fch_cad = crear_fechacad(fch_sist);
        }
    } while (fch_ok != 1);


    dc.DescCliente[new_pos].dia_cad = fch_cad.dia;
    dc.DescCliente[new_pos].mes_cad = fch_cad.mes;
    dc.DescCliente[new_pos].anio_cad = fch_cad.anio;

    dc.DescCliente[new_pos].Estado = 0;

    dc.tam++;

    Guardar_DescuentosClientes(dc);
}


DescClientes Asignar_codpro(DescClientes dc){

    int i;
    char cod_desc[11];

    fecha fch_sist;
    fch_sist.dia = dia_sist();
    fch_sist.mes = mes_sist();
    fch_sist.anio = anio_sist();

    fecha fch_cad = crear_fechacad(fch_sist);
    clients c = cargar_clientes();


    strcpy(cod_desc, "codpro");

    for(i=0; i<c.n_clients; i++){
        Asignar_Descuentos(dc, c.clients[i].Id_cliente, fch_cad);
    }

    return dc;
}

void Listar_Descuentos_Asignados(DescClientes dc){

    int i, j;
    char Id_cod_busqueda[11];
    clients c = cargar_clientes();

    printf("Introduzca el identificador del descuento que quiera saber los clientes asignados\n");

    fflush(stdin);
    fgets(Id_cod_busqueda, sizeof(Id_cod_busqueda)+1, stdin);
    terminador_cad(Id_cod_busqueda);

    for(i = 0; i<dc.tam; i++){
        if(strcpy(Id_cod_busqueda, dc.DescCliente[i].Id_cod ) == 0){
            for(j = 0; j<c.n_clients; j++){
                if(dc.DescCliente[i].Id_cliente == c.clients[j].Id_cliente){
                    printf("Nombre del cliente: %s. Fecha de caducidad: %d/%d/%d \n", &c.clients[j].Nom_cliente, &dc.DescCliente[i].dia_cad, &dc.DescCliente[i].mes_cad, &dc.DescCliente[i].anio_cad);
                }
            }
        }
    }
}

void Listar_Descuentos_Aplicados(DescClientes dc){

    int i, j;
    clients c = cargar_clientes();

    for(i = 0; i<dc.tam; i++){
        if(dc.DescCliente[i].Estado != 0){
            for(j = 0; j<c.n_clients; j++){
                if(dc.DescCliente[i].Id_cliente == c.clients[j].Id_cliente){
                    printf("Nombre del cliente: %s. Código del descuento: %s \n", &c.clients[j].Nom_cliente, &dc.DescCliente[i].Id_cod);
                }
            }
        }
    }
}
