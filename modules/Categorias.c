#include "Categorias.h"
#include "complementos.h"

categ_vect cargar_categorias () {
	char filename[] = "Categorias.txt";   
    int num_cat = 0;                          //Numero de categorias registradas
    int i = 0;                          		
    char cad_linea[250];                      //Caracteres maximos que puede ocupar una linea en fichero
    int campo_categorias;                     //Entero que verifica nº campos de la estructura categorias
    char default_cat[] = "0000-defaultdesc";  //Creacion de una categoria estandar que ocupara la posicion 0 del fichero
	
	FILE *f_cat;
	
	f_cat = fopen (filename, "r");
	
	if (f_cat == NULL) {
		f_cat = fopen (filename, "w");		 //Excepcion si no encuentra fichero
		fclose (f_cat);
		printf ("No se pudo abrir el archivo de categorias. Se ha creado un nuevo archivo\n");
		getchar ();
	}
	
	rewind (f_cat);						    //Necesario para volver a leer el fichero
	
	if (fgetc(f_cat) == EOF) {				//Si fichero vacio, añadimos categoria predeterminada
		f_cat = fopen (filename, "w");
		fprintf (f_cat, default_cat);
		fclose (f_cat);
	}
	
	while (fgets (cad_linea, sizeof(cad_linea), f_cat)) {			//Contador de categorias en el programa a partir de fichero 
        num_cat++;
    }
	
	rewind (f_cat);
	
	categ_vect c;
	
  	c.num_cat = num_cat;
  	
  	c.categ = (categorias*)malloc(c.num_cat*sizeof(categorias));    //Asignacion de memoria dinamica "c.categ[num_cat]"
  	
  	if (c.categ == NULL) {
		printf ("No se ha podido reservar memoria suficiente\n");
		getchar ();
		exit (1);
	}
  	
  	//BUCLE PARA RELLENAR LA ESTRUCTURA DE PRODUCTOS//
    while (fgets(cad_linea, sizeof(cad_linea), f_cat) && i < num_cat) {
        campo_categorias = sscanf (cad_linea, "%d-%51[^\n]",
            &c.categ[i].id_categ,
            c.categ[i].descrip);

        if (campo_categorias != 2){                                 //Excepcion si fallo en dato de categoria
            printf ("Se produjo un error con los datos de una categoria. ID_producto: %d\n", i + 1);
            getchar();
            exit(EXIT_FAILURE);
        }
		i++;
    }
    
    fclose (f_cat);
    
    return c;
}

void guardar_categorias (categ_vect c) {
	int i;
	
	FILE *f_cat;
	char filename[] = "Categorias.txt";
	f_cat = fopen (filename, "w");
	
	if (f_cat == NULL) {
		perror ("\nHa ocurrido un error, intentelo de nuevo");
		getchar ();
		exit (EXIT_FAILURE);
	}
	
	//PROCESO DE GUARDADO DE DATOS DE CADA CATEGORIA EN FICHERO//
	for (i = 0; i < c.num_cat; i++) {                          
        fprintf (f_cat, "%04d-%s\n",
                c.categ[i].id_categ,
                c.categ[i].descrip);
    }
    
    fclose (f_cat);
    
    if (c.num_cat == 1) {
    	printf ("\n**Estructura guardada con 1 categoria\n");
	}
	else {
		printf ("\n**Estructura guardada con %d categorias\n", c.num_cat - 1);
	}	
}

categ_vect agregar_categorias (categ_vect c) {
	int nueva_id = c.num_cat;		//IDENTIFICADOR DEL NUEVO PRODUCTO
	
	c.categ = (categorias*)realloc(c.categ, (nueva_id + 1)*sizeof(categorias));
	
	if (c.categ == NULL) {
		printf ("No se pudo reasignar la estructura de categorias");
        getchar ();
        exit (EXIT_FAILURE);
	}
	
	c.categ[nueva_id].id_categ = nueva_id;		//La id de la categoria se rellena automáticamente
	
	printf ("\nEscribe la descripcion de la categoria: ");
	fgets (c.categ[nueva_id].descrip, 51, stdin);
	fflush (stdin);
	terminador_cad (c.categ[nueva_id].descrip);
	
	c.num_cat++;
	guardar_categorias (c);
	
	printf ("Se ha registrado la categoria %04d correctamente", c.categ[nueva_id].id_categ);
	getchar ();
	
	return c;
}

int buscar_categorias (categ_vect c) {
	int i, op1, op2, len, naux, cont = 0, vaux[c.num_cat];	
	char saux[51];
	
	for (i = 0; i < c.num_cat; i++) {	//Inicializa todos los elementos del vector a 0
		vaux[i] = 0;
	}
	
	//Primero, busque la categoria que desee modificar bajo uno de los siguientes criterios:
	//Primero, busque la categoria que desee eliminar bajo uno de los siguientes criterios:
	
	do {
		printf ("\n\n1. Id de la categoria\n2. Descripcion\n0. Salir\n############################\n");
		scanf ("%d", &op1);  
		fflush (stdin);
	}while (op1 < 0 || op1 > 2);
	
	switch (op1) {
		case 1:
			do {
				printf ("\nIntroduzca el id de la categoria que este buscando: ");
				scanf ("%d", &naux);
				fflush (stdin);
			
				for (i = 1; i < c.num_cat; i++) {
					if (naux == c.categ[i].id_categ) {
						vaux[i] = i;
						cont++;
					}
				}
			
				if (cont != 0) {
					if (cont == 1) {
						printf ("\nSe encontro una categoria con el id especificado:\n");				
						//Mostrar la categoria encontrada
						for (i = 1; i < c.num_cat; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %04d-%s\n", i, c.categ[vaux[i]].id_categ, c.categ[vaux[i]].descrip);
								op2 = i;
							}
						}
					}
					else {
						printf ("\nSe encontraron %d categorias con el id especificado:\n", cont);
						//Mostrar los productos encontrados
						for (i = 1; i < c.num_cat; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %04d-%s", i, c.categ[vaux[i]].id_categ, c.categ[vaux[i]].descrip);
							}
						}
					
						do {
							//Permitir al usuario seleccionar una categoria
							printf ("\n\nSeleccione la categoria que este buscando escribiendo su respectivo indice: ");
							scanf ("%d", &op2);
							fflush (stdin);
							
							//Verificar si el indice ingresado es valido
    						if (op2 < 1 || op2 >= c.num_cat || vaux[op2] != op2) {
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
					printf ("No se encontro ninguna categoria con el id especificado, pruebe con un id distinto:\n\n");
				}
			}while (cont == 0);
		break;
		
		case 2:
			do {
				printf ("\nIntroduzca la descripcion de la categoria que este buscando: ");
				fgets (saux, 51, stdin);
				fflush (stdin);
				terminador_cad (saux);
				len = strlen (saux);
			
				for (i = 1; i < c.num_cat; i++) {
					if (strncmp (saux, c.categ[i].descrip, len) == 0) {
						vaux[i] = i;
						cont++;
					}
				}
			
				if (cont != 0) {
					if (cont == 1) {
						printf ("\nSe encontro una categoria con la descripcion especificada:\n");				
						//Mostrar el producto encontrado
						for (i = 1; i < c.num_cat; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %04d-%s\n", i, c.categ[vaux[i]].id_categ, c.categ[vaux[i]].descrip);
								op2 = i;
							}
						}
					}
					else {
						printf ("\nSe encontraron %d categorias con la descripcion especificada:\n", cont);
						//Mostrar los productos encontrados
						for (i = 1; i < c.num_cat; i++) {
							if (vaux[i] == i) {
								printf ("\n%d. %04d-%s", i, c.categ[vaux[i]].id_categ, c.categ[vaux[i]].descrip);
							}
						}
					
						do {
							//Permitir al usuario seleccionar un producto
							printf ("\n\nSeleccione la categoria que este buscando escribiendo su respectivo indice: ");
							scanf ("%d", &op2);
							fflush (stdin);
							
							//Verificar si el indice ingresado es valido
    						if (op2 < 1 || op2 >= c.num_cat || vaux[op2] != op2) {
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
					printf ("No se encontro ninguna categoria con la descripcion especificada, pruebe con una descripcion distinta:\n\n");
				}
			}while (cont == 0);
		break;
		
		case 0:
			printf ("\nVolviendo al menu anterior...\n");
			op2 = -1;
		break;
		
		default:
			printf ("Seleccione una opcion valida: ");
		break;
	}
	
	return op2;
}

categ_vect modificar_categorias (categ_vect c) {
	int pos, op;
	char respuesta;
	
	//MOSTRAR INFORMACION//
	clear ();
	Sleep (1000);
	printf ("---> MODIFICADOR DE CATEGORIAS: <---\n\n");
	printf ("Primero, busque la categoria que desee modificar bajo uno de los siguientes criterios:");
	
	Sleep (1000);	
	pos = buscar_categorias (c);
	
	if (pos == -1) {
		return c;
	}
	
	printf ("\nEsta seguro que desea modificar la categoria '%04d-%s'? (S/N): ", c.categ[pos].id_categ, c.categ[pos].descrip);
	scanf ("%c", &respuesta);
	fflush (stdin);
	
	clear ();
	Sleep (1000);
	
	if (respuesta == 'S' || respuesta == 's') {
		printf ("\n\nDescripcion actual de la categoria: %s\n", c.categ[pos].descrip);
		printf ("Ingrese la nueva descripcion (maximo 50 caracteres): ");
		fgets (c.categ[pos].descrip, 51, stdin);
		fflush (stdin);
		terminador_cad (c.categ[pos].descrip);
		
		printf ("\nCategoria modificada correctamente\n");	
			
		guardar_categorias (c);
	}
	else {
		printf ("\nVolviendo al menu anterior...\n");
	}
			
	return c;
}

categ_vect eliminar_categorias (categ_vect c) {
	int i, pos;
	char respuesta;
	
	//MOSTRAR INFORMACION//
	clear ();
	Sleep (1000);
	printf ("---> ELIMINADOR DE CATEGORIAS: <---\n\n");
	printf ("Primero, busque la categoria que desee eliminar bajo uno de los siguientes criterios:");
	
	Sleep (1000);	
	pos = buscar_categorias (c);
	
	if (pos == -1) {
		return c;
	}
	
	printf ("\nEsta seguro que desea eliminar la categoria '%04d-%s'? (S/N): ", c.categ[pos].id_categ, c.categ[pos].descrip);
	scanf ("%c", &respuesta);
	fflush (stdin);
	
	if (respuesta == 'S' || respuesta == 's') {
		for (i = pos; i < c.num_cat - 1; i++) {
			c.categ[i] = c.categ[i + 1];			//Desplazar elementos hacia atras
			c.categ[i].id_categ = i;				//Reasignar las id de las categorias
		}
	
		c.num_cat--;			//Reducir la variable del numero de categorias
		
		c.categ = (categorias*)realloc(c.categ, c.num_cat*sizeof(categorias));	//Reasignar el tamaño del vector
	
		if (c.categ == NULL) {
			printf ("\nNo se pudo reasignar la estructura de categorias");
        	getchar ();
        	exit (EXIT_FAILURE);
		}
		
		guardar_categorias (c);
	
		printf ("\nCategoria eliminada correctamente\n");
	}
	else {
		printf ("\nVolviendo al menu anterior...\n");
	}
	
	return c;
}

categ_vect listar_categorias (categ_vect c) {
	int i;
	
	clear ();
	Sleep (1000);
	printf ("---> LISTA DE CATEGORIAS: <---\n\n");
	
	for (i = 1; i < c.num_cat; i++) {
		printf ("(%i) %04d-%s\n", i, c.categ[i].id_categ, c.categ[i].descrip);
	}
	
	return c;
}

void menu_categ (categ_vect c) {
	int op;
	char respuesta;
	
	do {
		do{
			printf ("Que desea hacer?\n\n");
			Sleep (1000);
			printf ("(1) Rellenar los datos de una nueva categoria\n");
			printf ("(2) Modificar los datos de una categoria existente\n");
			printf ("(3) Eliminar los datos de una categoria existente\n");
			printf ("(4) Listar las categorias existentes\n");
			printf ("(0) Salir del menu\n\n");
			scanf ("%d", &op);
			fflush (stdin);
		}while (op < 0 || op > 4);
		
		switch (op) {
			case 1:
				c = agregar_categorias (c);
			break;
			
			case 2:
				c = modificar_categorias (c);
			break;
			
			case 3:
				c = eliminar_categorias (c);
			break;
			
			case 4:
				listar_categorias (c);
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