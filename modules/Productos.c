#include "Productos.h"
#include "complementos.h"

produ_vect cargar_productos () {
	char filename[] = "../data/Productos.txt";   
    int num_prod = 0;                         //Numero de productos registrados
    int i = 0;                          		
    char cad_linea[250];                      //Caracteres maximos que puede ocupar una linea en fichero
    int campo_productos;                      //Entero que verifica nº campos de la estructura productos
    char default_prod[] = "0000000-defaultname-defaultdesc-0000-0000-0-0-0";	//Creacion de un producto estandar que ocupara la posicion 0 del fichero
	
	FILE *f_prod;
	
	f_prod = fopen (filename, "a+");
	
	if (f_prod == NULL) {

		printf ("No se pudo abrir el archivo de productos. Se ha creado un nuevo archivo\n");
		getchar ();
	}
	
	rewind (f_prod);						//Necesario para volver a leer el fichero
	
	if (fgetc(f_prod) == EOF) {				//Si fichero vacio, añadimos producto predeterminado

		fprintf (f_prod, default_prod);
	}
	
rewind (f_prod);
	while (fgets (cad_linea, sizeof(cad_linea), f_prod)) {			//Contador de productos en el programa a partir de fichero 
        num_prod++;
    }
	
	rewind (f_prod);
	
	produ_vect p;
	
  	p.num_prod = num_prod;
  	
  	p.produ = (productos*)malloc(p.num_prod*sizeof(productos));		//Asignacion de memoria dinamica "p.produ[num_prod]"
  	
  	if (p.produ == NULL) {
		printf ("No se ha podido reservar memoria suficiente\n");
		getchar ();
		exit (1);
	}
  	
  	//BUCLE PARA RELLENAR LA ESTRUCTURA DE PRODUCTOS//
    while (fgets(cad_linea, sizeof(cad_linea), f_prod) && i < num_prod) {
        campo_productos = sscanf (cad_linea, "%d-%16[^-]-%51[^-]-%d-%d-%d-%d-%d",
            &p.produ[i].id_prod,
            p.produ[i].nombre,
            p.produ[i].descrip,
            &p.produ[i].id_categ,
            &p.produ[i].id_gestor,
            &p.produ[i].stock,
            &p.produ[i].entrega,
            &p.produ[i].importe);

        if (campo_productos != 8){                               //Excepcion si fallo en dato de producto
            printf ("Se produjo un error con los datos de un producto. ID_producto: %d\n", i + 1);
            getchar();
            exit(EXIT_FAILURE);
        }
		i++;
    }
    
    fclose (f_prod);
    
    return p;
}

void guardar_productos (produ_vect p) {
	int i;
	
	FILE *f_prod;
<<<<<<< HEAD
	char filename[] = "Productos.txt";
=======
	char filename[] = "../data/Productos.txt";
>>>>>>> c37106f407833092b9bcde6971fefc5c5081f442
	f_prod = fopen (filename, "w");
	
	if (f_prod == NULL) {
		perror ("\nHa ocurrido un error, intentelo de nuevo");
		getchar ();
		exit (EXIT_FAILURE);
	}
	
	//PROCESO DE GUARDADO DE DATOS DE CADA PRODUCTO EN FICHERO//
	for (i = 0; i < p.num_prod; i++) {                          
        fprintf (f_prod, "%07d-%s-%s-%04d-%04d-%d-%d-%d\n",
                p.produ[i].id_prod,
                p.produ[i].nombre,
                p.produ[i].descrip,
                p.produ[i].id_categ,
                p.produ[i].id_gestor,
                p.produ[i].stock,
                p.produ[i].entrega,
                p.produ[i].importe);
    }
    
    fclose (f_prod);
    
    if (p.num_prod == 1) {
    	printf ("\n**Estructura guardada con 1 producto\n");
	}
	else {
		printf ("\n**Estructura guardada con %d productos\n", p.num_prod - 1);
	}
}

produ_vect agregar_productos (produ_vect p) {
	int nueva_id = p.num_prod;		//IDENTIFICADOR DEL NUEVO PRODUCTO
	
	p.produ = (productos*)realloc(p.produ, (nueva_id + 1)*sizeof(productos));
	
	if (p.produ == NULL) {
		printf ("No se pudo reasignar la estructura de productos");
        getchar ();
        exit (EXIT_FAILURE);
	}
	
	p.produ[nueva_id].id_prod = nueva_id; //La id del producto se rellena automáticamente
	
	printf ("\nPrimero, escribe el nombre del producto: ");
	fgets (p.produ[nueva_id].nombre, 16, stdin);
	fflush (stdin);
	terminador_cad (p.produ[nueva_id].nombre);
	
	printf ("\nSengundo, escribe la descripcion del producto: ");
	fgets (p.produ[nueva_id].descrip, 51, stdin);
	fflush (stdin);
	terminador_cad (p.produ[nueva_id].descrip);
	
	printf ("\nTemporal, escribe el id de la categoria del producto: ");
	scanf ("%d", &p.produ[nueva_id].id_categ);
	fflush (stdin);
	
	printf ("\nTercero, escribe el id del gestor del producto: ");
	scanf ("%d", &p.produ[nueva_id].id_gestor);
	fflush (stdin);
	
	printf ("\nCuarto, escribe el stock del producto: ");
	scanf ("%d", &p.produ[nueva_id].stock);
	fflush (stdin);
	
	printf ("\nQuinto, escribe el compromiso de entrega en dias: ");
	scanf ("%d", &p.produ[nueva_id].entrega);
	fflush (stdin);
	
	printf ("\nPor ultimo, escribe el importe del producto en euros: ");
	scanf ("%d", &p.produ[nueva_id].importe);
	fflush (stdin);
	
	p.num_prod++;
	guardar_productos (p);
	
	printf ("Se ha registrado el producto %s correctamente", p.produ[nueva_id].nombre);
	getchar ();
	
	return p;
}

int buscar_productos (produ_vect p) {
	int i, op1, op2, len, naux, cont = 0, vaux[p.num_prod];	
	char saux[51];
	
	for (i = 0; i < p.num_prod; i++) {	//Inicializa todos los elementos del vector a 0
		vaux[i] = 0;
	}
	
	//Primero, busque el producto que desee modificar bajo uno de los siguientes criterios:
	//Primero, busque el producto que desee eliminar bajo uno de los siguientes criterios:
	
	do {
		printf ("\n\n1. Nombre\n2. Descripcion\n3. Stock del producto\n4. Dias de compromiso de entrega\n5. Importe en euros\n0. Salir\n############################\n");
		scanf ("%d", &op1);  
		fflush (stdin);
	}while (op1 < 0 || op1 > 5);
	
	switch (op1) {
		case 1:
			do {
				printf ("\nIntroduzca el nombre del producto que este buscando: ");
				fgets (saux, 16, stdin);
				fflush (stdin);
				terminador_cad (saux);
				len = strlen (saux);
			
				for (i = 1; i < p.num_prod; i++) {
					if (strncmp (saux, p.produ[i].nombre, len) == 0) {
						vaux[i] = i;
						cont++;
					}
				}
			
				if (cont != 0) {
					if (cont == 1) {
						printf ("Se encontro un producto con el nombre especificado:\n");				
						//Mostrar el producto encontrado
						for (i = 1; i < p.num_prod && vaux[i] != i; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %s-%s-%d-%d-%d", i, p.produ[vaux[i]].nombre, p.produ[vaux[i]].descrip, p.produ[vaux[i]].stock, p.produ[vaux[i]].entrega, p.produ[vaux[i]].importe);
							}
						}
						
						op2 = i;
					}
					else {
						printf ("\nSe encontraron %d productos con el nombre especificado:\n", cont);
						//Mostrar los productos encontrados
						for (i = 1; i < p.num_prod; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %s-%s-%d-%d-%d", i, p.produ[vaux[i]].nombre, p.produ[vaux[i]].descrip, p.produ[vaux[i]].stock, p.produ[vaux[i]].entrega, p.produ[vaux[i]].importe);
							}
						}
					
						do {
							//Permitir al usuario seleccionar un producto
							printf ("\n\nSeleccione el producto que este buscando escribiendo su respectivo indice: ");
							scanf ("%d", &op2);
							fflush (stdin);
							
							//Verificar si el indice ingresado es valido
    						if (op2 < 1 || op2 >= p.num_prod || vaux[op2] != op2) {
        						printf ("Indice invalido. Por favor, seleccione un indice valido\n");
        						op2 = -1;	//Reiniciar op2 para repetir el bucle
    						}
							else {
        						vaux[op2] = op2;
    						}
						}while (op2 == -1);		//Repetir mientras el indice sea invalido	
					}
				}
				else {
					printf ("No se encontro ningun producto con el nombre especificado, pruebe con un nombre distinto:\n\n");
				}
			}while (cont == 0);
		break;
		
		case 2:
			do {
				printf ("Itroduzca la descripcion del producto que este buscando: ");
				fgets (saux, 51, stdin);
				fflush (stdin);
				terminador_cad (saux);
				len = strlen (saux);
			
				for (i = 1; i < p.num_prod; i++) {
					if (strncmp (saux, p.produ[i].descrip, len) == 0) {
						vaux[i] = i;
						cont++;
					}
				}
			
				if (cont != 0) {
					if (cont == 1) {
						printf ("Se encontro un producto con la descripcion especificada:\n");				
						//Mostrar el producto encontrado
						for (i = 1; i < p.num_prod && vaux[i] != i; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %s-%s-%d-%d-%d", i, p.produ[vaux[i]].nombre, p.produ[vaux[i]].descrip, p.produ[vaux[i]].stock, p.produ[vaux[i]].entrega, p.produ[vaux[i]].importe);
							}
						}
						
						op2 = i;
					}
					else {
						printf ("\nSe encontraron %d productos con la descripcion especificada:\n", cont);
						//Mostrar los productos encontrados
						for (i = 1; i < p.num_prod; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %s-%s-%d-%d-%d", i, p.produ[vaux[i]].nombre, p.produ[vaux[i]].descrip, p.produ[vaux[i]].stock, p.produ[vaux[i]].entrega, p.produ[vaux[i]].importe);
							}
						}
					
						do {
							//Permitir al usuario seleccionar un producto
							printf ("\n\nSeleccione el producto que este buscando escribiendo su respectivo indice: ");
							scanf ("%d", &op2);
							fflush (stdin);
							
							//Verificar si el indice ingresado es valido
    						if (op2 < 1 || op2 >= p.num_prod || vaux[op2] != op2) {
        						printf ("Indice invalido. Por favor, seleccione un indice valido\n");
        						op2 = -1;	//Reiniciar op2 para repetir el bucle
    						}
							else {
        						vaux[op2] = op2;
    						}
						}while (op2 == -1);		//Repetir mientras el indice sea invalido	
					}
				}
				else {
					printf ("No se encontro ningun producto con la descripcion especificada, pruebe con una descripcion distinta:\n\n");
				}
			}while (cont == 0);
		break;
			
		case 3:
			do {
				printf ("Itroduzca el stock del producto que este buscando: ");
				scanf ("%d", &naux);
				fflush (stdin);
			
				for (i = 1; i < p.num_prod; i++) {
					if (naux == p.produ[i].stock) {
						vaux[i] = i;
						cont++;
					}
				}
			
				if (cont != 0) {
					if (cont == 1) {
						printf ("Se encontro un producto con el stock especificado:\n");				
						//Mostrar el producto encontrado
						for (i = 1; i < p.num_prod && vaux[i] != i; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %s-%s-%d-%d-%d", i, p.produ[vaux[i]].nombre, p.produ[vaux[i]].descrip, p.produ[vaux[i]].stock, p.produ[vaux[i]].entrega, p.produ[vaux[i]].importe);
							}
						}
						
						op2 = i;
					}
					else {
						printf ("\nSe encontraron %d productos con el stock especificado:\n", cont);
						//Mostrar los productos encontrados
						for (i = 1; i < p.num_prod; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %s-%s-%d-%d-%d", i, p.produ[vaux[i]].nombre, p.produ[vaux[i]].descrip, p.produ[vaux[i]].stock, p.produ[vaux[i]].entrega, p.produ[vaux[i]].importe);
							}
						}
					
						do {
							//Permitir al usuario seleccionar un producto
							printf ("\n\nSeleccione el producto que este buscando escribiendo su respectivo indice: ");
							scanf ("%d", &op2);
							fflush (stdin);
							
							//Verificar si el indice ingresado es valido
    						if (op2 < 1 || op2 >= p.num_prod || vaux[op2] != op2) {
        						printf ("Indice invalido. Por favor, seleccione un indice valido\n");
        						op2 = -1;	//Reiniciar op2 para repetir el bucle
    						}
							else {
        						vaux[op2] = op2;
    						}
						}while (op2 == -1);		//Repetir mientras el indice sea invalido	
					}
				}
				else {
					printf ("No se encontro ningun producto con el stock especificado, pruebe con un stock distinto:\n\n");
				}
			}while (cont == 0);
		break;
			
		case 4:
			do {
				printf ("Itroduzca los dias de compromiso de entrega del producto que este buscando: ");
				scanf ("%d", &naux);
				fflush (stdin);
			
				for (i = 1; i < p.num_prod; i++) {
					if (naux == p.produ[i].entrega) {
						vaux[i] = i;
						cont++;
					}
				}
			
				if (cont != 0) {
					if (cont == 1) {
						printf ("Se encontro un producto con los dias de compromiso de entrega especificados:\n");				
						//Mostrar el producto encontrado
						for (i = 1; i < p.num_prod && vaux[i] != i; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %s-%s-%d-%d-%d", i, p.produ[vaux[i]].nombre, p.produ[vaux[i]].descrip, p.produ[vaux[i]].stock, p.produ[vaux[i]].entrega, p.produ[vaux[i]].importe);
							}
						}
						
						op2 = i;
					}
					else {
						printf ("\nSe encontraron %d productos con los dias de compromiso de entrega especificados:\n", cont);
						//Mostrar los productos encontrados
						for (i = 1; i < p.num_prod; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %s-%s-%d-%d-%d", i, p.produ[vaux[i]].nombre, p.produ[vaux[i]].descrip, p.produ[vaux[i]].stock, p.produ[vaux[i]].entrega, p.produ[vaux[i]].importe);
							}
						}
					
						do {
							//Permitir al usuario seleccionar un producto
							printf ("\n\nSeleccione el producto que este buscando escribiendo su respectivo indice: ");
							scanf ("%d", &op2);
							fflush (stdin);
							
							//Verificar si el indice ingresado es valido
    						if (op2 < 1 || op2 >= p.num_prod || vaux[op2] != op2) {
        						printf ("Indice invalido. Por favor, seleccione un indice valido\n");
        						op2 = -1;	//Reiniciar op2 para repetir el bucle
    						}
							else {
        						vaux[op2] = op2;
    						}
						}while (op2 == -1);		//Repetir mientras el indice sea invalido	
					}
				}
				else {
					printf ("No se encontro ningun producto con los dias especificados, pruebe con una cantidad de dias distinta:\n\n");
				}
			}while (cont == 0);
		break;
		
		case 5:
			do {
				printf ("Itroduzca el importe en euros del producto que este buscando: ");
				scanf ("%d", &naux);
				fflush (stdin);
			
				for (i = 1; i < p.num_prod; i++) {
					if (naux == p.produ[i].importe) {
						vaux[i] = i;
						cont++;
					}
				}
			
				if (cont != 0) {
					if (cont == 1) {
						printf ("Se encontro un producto con el importe especificado:\n");				
						//Mostrar el producto encontrado
						for (i = 1; i < p.num_prod && vaux[i] != i; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %s-%s-%d-%d-%d", i, p.produ[vaux[i]].nombre, p.produ[vaux[i]].descrip, p.produ[vaux[i]].stock, p.produ[vaux[i]].entrega, p.produ[vaux[i]].importe);
							}
						}
						
						op2 = i;
					}
					else {
						printf ("\nSe encontraron %d productos con el importe especificado:\n", cont);
						//Mostrar los productos encontrados
						for (i = 1; i < p.num_prod; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %s-%s-%d-%d-%d", i, p.produ[vaux[i]].nombre, p.produ[vaux[i]].descrip, p.produ[vaux[i]].stock, p.produ[vaux[i]].entrega, p.produ[vaux[i]].importe);
							}
						}
					
						do {
							//Permitir al usuario seleccionar un producto
							printf ("\n\nSeleccione el producto que este buscando escribiendo su respectivo indice: ");
							scanf ("%d", &op2);
							fflush (stdin);
							vaux[op2] = op2;
							
							//Verificar si el indice ingresado es valido
    						if (op2 < 1 || op2 >= p.num_prod || vaux[op2] != op2) {
        						printf ("Indice invalido. Por favor, seleccione un indice valido\n");
        						op2 = -1;	//Reiniciar op2 para repetir el bucle
    						}
							else {
        						vaux[op2] = op2;
    						}
						}while (op2 == -1);		//Repetir mientras el indice sea invalido	
					}
				}
				else {
					printf ("No se encontro ningun producto con el importe especificado, pruebe con un importe distinto:\n\n");
				}
			}while (cont == 0);
		break;
		
		case 0:
			printf ("\nVolviendo al menu anterior...\n");
		break;
		
		default:
			printf ("Seleccione una opcion valida: ");
		break;
	}
	
	return op2;
}

produ_vect modificar_productos (produ_vect p) {
	int pos, op;
	char respuesta;
	
	//MOSTRAR INFORMACION//
	clear ();
	Sleep (1000);
	printf ("---> MODIFICADOR DE PRODUCTOS: <---\n\n");
	printf ("Primero, busque el producto que desee modificar bajo uno de los siguientes criterios:");
	
	Sleep (1000);	
	pos = buscar_productos (p);
	
	if (pos == -1) {
		return p;
	}
	
	printf ("\nEsta seguro que desea modificar el producto '%s-%s'? (S/N): ", p.produ[pos].nombre, p.produ[pos].descrip);
	scanf ("%c", &respuesta);
	fflush (stdin);
	
	if (respuesta == 'S' || respuesta == 's') {
		do {
			printf ("Seleccione que es lo que quiere modificar del producto:");
			printf ("\n\n1. Nombre\n2. Descripcion\n3. Stock del producto\n4. Dias de compromiso de entrega\n5. Importe en euros\n############################\n");	
			scanf ("%d", &op);
			fflush (stdin);
		}while (op < 1 || op > 5);
	
		switch (op) {
			case 1:
				printf ("\nNombre actual del producto: %s\n", p.produ[pos].nombre);
				printf ("Ingrese el nuevo nombre (maximo 15 caracteres): ");
				fgets (p.produ[pos].nombre, 16, stdin);
				fflush (stdin);
				terminador_cad (p.produ[pos].nombre);
			break;
		
			case 2:
				printf ("\nDescripcion actual del producto: %s\n", p.produ[pos].descrip);
				printf ("Ingrese la nueva descripcion (maximo 50 caracteres): ");
				fgets (p.produ[pos].descrip, 51, stdin);
				fflush (stdin);
				terminador_cad (p.produ[pos].descrip);
			break;
			
			case 3:
				printf ("\nStock actual del producto: %d\n", p.produ[pos].stock);
				printf ("Ingrese el nuevo stock: ");
				scanf ("%d", &p.produ[pos].stock);
				fflush (stdin);
			break;
			
			case 4:
				printf ("\nDias de compromiso de entrega actuales del producto: %d\n", p.produ[pos].entrega);
				printf ("Ingrese el nuevo numero de dias: ");
				scanf ("%d", &p.produ[pos].entrega);
				fflush (stdin);
			break;
		
			case 5:
				printf ("\nImporte actual en euros del producto: %d\n", p.produ[pos].importe);
				printf ("Ingrese el nuevo importe en euros: ");
				scanf ("%d", &p.produ[pos].importe);
				fflush (stdin);
			break;
			
			default:
				printf ("Seleccione una opcion valida: ");
			break;
		}	
			
		guardar_productos (p);
		
		printf ("\nProducto modificado correctamente\n");	
	}
	else {
		printf ("\nVolviendo al menu anterior...\n");
	}
			
	return p;
}

produ_vect eliminar_productos (produ_vect p) {
	int i, pos;
	char respuesta;
	
	//MOSTRAR INFORMACION//
	clear ();
	Sleep (1000);
	printf ("---> ELIMINADOR DE PRODUCTOS: <---\n\n");
	printf ("Primero, busque el producto que desee eliminar bajo uno de los siguientes criterios:");
	
	Sleep (1000);	
	pos = buscar_productos (p);
	
	if (pos == -1) {
		return p;
	}
	
	printf ("\nEsta seguro que desea eliminar el producto '%s-%s'? (S/N): ", p.produ[pos].nombre, p.produ[pos].descrip);
	scanf ("%c", &respuesta);
	fflush (stdin);
	
	if (respuesta == 'S' || respuesta == 's') {
		for (i = pos; i < p.num_prod - 1; i++) {
			p.produ[i] = p.produ[i + 1];			//Desplazar elementos hacia atras
			p.produ[i].id_prod = i;					//Reasignar las id de los productos
		}
	
		p.num_prod--;			//Reducir la variable del numero de productos
		
		p.produ = (productos*)realloc(p.produ, p.num_prod*sizeof(productos));	//Reasignar el tamaño del vector
	
		if (p.produ == NULL) {
			printf ("\nNo se pudo reasignar la estructura de productos");
        	getchar ();
        	exit (EXIT_FAILURE);
		}
		
		guardar_productos (p);
	
		printf ("\nProducto eliminado correctamente\n");
	}
	else {
		printf ("\nVolviendo al menu anterior...\n");
	}
	
	return p;
}

produ_vect listar_productos (produ_vect p) {
	int i;
	
	clear ();
	Sleep (1000);
	printf ("---> LISTA DE PRODUCTOS: <---\n\n");
	
	for (i = 1; i < p.num_prod; i++) {
		printf ("(%i) %07d-%s-%s-%04d-%04d-%d-%d-%d\n", i, p.produ[i].id_prod, p.produ[i].nombre, p.produ[i].descrip, p.produ[i].id_categ, p.produ[i].id_gestor, p.produ[i].stock, p.produ[i].entrega, p.produ[i].importe);
	}
	
	return p;
}

produ_vect buscador_productos (produ_vect p) {
	int i, op, naux, len, cont = 0, vaux[p.num_prod];
	char saux [16];
	
	for (i = 0; i < p.num_prod; i++) {	//Inicializa todos los elementos del vector a 0
		vaux[i] = 0;
	}
	
	printf ("---> BUSCADOR DE PRODUCTOS: <---\n\n");
	
	do {
		printf ("Primero, elija el criterio que desee para buscar el producto:");
		printf ("\n\n1. Nombre\n2. Id de la categoria del producto\n0. Salir\n############################\n");
		scanf ("%d", &op);
		fflush (stdin);
	}while (op < 0 || op > 2);
	
	switch (op) {
		case 1:
			do {
				printf ("\nIntroduzca el nombre del producto que este buscando: ");
				fgets (saux, 16, stdin);
				fflush (stdin);
				terminador_cad (saux);
				len = strlen (saux);
			
				for (i = 1; i < p.num_prod; i++) {
					if (strncmp (saux, p.produ[i].nombre, len) == 0) {
						vaux[i] = i;
						cont++;
					}
				}
			
				if (cont != 0) {
					if (cont == 1) {
						printf ("Se encontro un producto con el nombre especificado:\n");				
						//Mostrar el producto encontrado
						for (i = 1; i < p.num_prod && vaux[i] != i; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %s-%s-%d-%d-%d", i, p.produ[vaux[i]].nombre, p.produ[vaux[i]].descrip, p.produ[vaux[i]].stock, p.produ[vaux[i]].entrega, p.produ[vaux[i]].importe);
							}
						}
					}
					else {
						printf ("\nSe encontraron %d productos con el nombre especificado:\n", cont);
						//Mostrar los productos encontrados
						for (i = 1; i < p.num_prod; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %s-%s-%d-%d-%d", i, p.produ[vaux[i]].nombre, p.produ[vaux[i]].descrip, p.produ[vaux[i]].stock, p.produ[vaux[i]].entrega, p.produ[vaux[i]].importe);
							}
						}
					}
				}
				else {
					printf ("No se encontro ningun producto con el importe especificado, pruebe con un importe distinto:\n\n");
				}
			}while (cont == 0);		
		break;
		
		case 2:
			do {
				printf ("\nIntroduzca la id de la categoria del producto que este buscando: ");
				scanf ("%d", &naux);
				fflush (stdin);
			
				for (i = 1; i < p.num_prod; i++) {
					if (naux == p.produ[i].id_categ) {
						vaux[i] = i;
						cont++;
					}
				}
			
				if (cont != 0) {
					if (cont == 1) {
						printf ("Se encontro un producto con la id de la categoria especificada:\n");				
						//Mostrar el producto encontrado
						for (i = 1; i < p.num_prod && vaux[i] != i; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %s-%s-%d-%d-%d", i, p.produ[vaux[i]].nombre, p.produ[vaux[i]].descrip, p.produ[vaux[i]].stock, p.produ[vaux[i]].entrega, p.produ[vaux[i]].importe);
							}
						}
					}
					else {
						printf ("\nSe encontraron %d productos con la id de la categoria especificada:\n", cont);
						//Mostrar los productos encontrados
						for (i = 1; i < p.num_prod; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %s-%s-%d-%d-%d", i, p.produ[vaux[i]].nombre, p.produ[vaux[i]].descrip, p.produ[vaux[i]].stock, p.produ[vaux[i]].entrega, p.produ[vaux[i]].importe);
							}
						}
					}
				}
				else {
					printf ("No se encontro ningun producto con la id de la categoria especificada, pruebe con una id distinta:\n\n");
				}
			}while (cont == 0);	
		break;
		
		case 0:
		break;
		
		default:
			printf ("Seleccione una opcion valida: ");
		break;
	}
	
	return p;
}

void menu_prod (produ_vect p) {
	int op;
	char respuesta;
	
	do {
		do{
			printf ("Que desea hacer?\n\n");
			Sleep (1000);
			printf ("(1) Rellenar los datos de un nuevo producto\n");
			printf ("(2) Modificar los datos de un producto existente\n");
			printf ("(3) Eliminar los datos de un producto existente\n");
			printf ("(4) Listar los productos existentes\n");
			printf ("(0) Salir del menu\n\n");
			scanf ("%d", &op);
			fflush (stdin);
		}while (op < 0 || op > 4);
		
		switch (op) {
			case 1:
				p = agregar_productos (p);
			break;
			
			case 2:
				p = modificar_productos (p);
			break;
			
			case 3:
				p = eliminar_productos (p);
			break;
			
			case 4:
				listar_productos (p);
			break;
			
			case 0:		//Caso de salida
				respuesta = 'N';
			break;
			
			default:	//Caso de error al seleccionar
				printf ("Seleccione una opcion valida: ");
			break;
		}
		
		if (op != 0) {
			printf ("\nDesea realizar algun cambio mas? (S/N): ");
			scanf ("%c", &respuesta);
			fflush (stdin);
			clear ();
		}
	}while (respuesta == 'S' || respuesta == 's');
}