#include "./productos.h"
#include "complementos.h"

produ_vect cargar_productos () {
	char filename[] = "Productos.txt";   		//Ruta del fichero
    int num_prod = 0;                           //Numero de productos registrados
    int i = 0;                          		
    char cad_linea[250];                        //Caracteres maximos que puede ocupar una linea en fichero
    int campo_productos;                        //Entero que verifica nº campos de la estructura productos
	
	FILE *f_prod;
	
	f_prod = fopen (filename, "r+");
	
	if (f_prod == NULL) {
		f_prod = fopen (filename, "w");			//Excepcion si no encuentra fichero
		perror ("No se pudo abrir el archivo de productos. Se ha creado un nuevo archivo.\n");
		getchar ();
	}
	
	while (fgets (cad_linea, sizeof(cad_linea), f_prod)){		//Contador de clientes en el programa a partir de fichero 
        num_prod++;
    }
	
	rewind (f_prod);											//Necesario para volver a leer el fichero
	
	produ_vect p;
	
  	p.num_prod = num_prod;
  	p.produ = malloc(p.num_prod*sizeof(productos));				//Asignacion de memoria dinamica "p.produ[num_prod]"
  	
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

        if (campo_productos != 8){                               //Excepcion si fallo en dato de cliente
            printf ("Se produjo un error con datos de un producto. ID_producto: %d\n", i+1);
            getchar();
            exit(EXIT_FAILURE);
        }
		i++;
    }
    
    fclose (f_prod);
    
    return p;
}

void cambio (char cad[]) {
	int i;
	int len = strlen(cad);
	
	for (i = 0; i < len; i++) {
		if (cad[i] == '\n') {
			cad[i] = '\0';
			len = i;	//ACABA BUCLE SI CAMBIA EL SALTO DE LINEA POR TERMINADOR
		}
	}
}

void guardar_productos (produ_vect p) {
	int i;
	
	FILE *f_prod;
	char filename[] = "Productos.txt";
	f_prod = fopen (filename, "a+");
	
	if (f_prod == NULL) {
		perror ("\nHa ocurrido un error, intentelo de nuevo");
		getchar ();
		exit (EXIT_FAILURE);
	}
	
	//PROCESO DE GUARDADO DE DATOS DE CADA PRODUCTO EN FICHERO//
	for (i = 0; i < p.num_prod; i++){                          
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
    printf ("\n**Estructura guardada con %d poductos\n", p.num_prod);
}

produ_vect agregar_productos (produ_vect p) {
	int nueva_id = p.num_prod + 1;		//IDENTIFICADOR DEL NUEVO PRODUCTO
	int nueva_pos = nueva_id - 1;		//POSICION DEL PRODUCTO EN LA ESTRUCTURA
	
	p.produ = realloc(p.produ, nueva_id*sizeof(productos));
	
	if (p.produ == NULL) {
		printf ("No se pudo asignar la estructura de productos");
        getchar ();
        exit (EXIT_FAILURE);
	}
	
	p.produ[nueva_pos].id_prod = nueva_id;
	
	printf ("\nPrimero, escribe el nombre del producto: ");
	fflush (stdin);
	fgets (p.produ[nueva_pos].nombre, 16, stdin);
	cambio (p.produ[nueva_pos].nombre);
	
	printf ("\nSengundo, escribe la descripcion del producto: ");
	fflush (stdin);
	fgets (p.produ[nueva_pos].descrip, 51, stdin);
	cambio (p.produ[nueva_pos].descrip);
	
	printf ("\nTercero, escribe el id de la categoria a la que pertenece: ");
	scanf ("%d", &p.produ[nueva_pos].id_categ);
	
	printf ("\nCuarto, escribe el id del gestor del producto: ");
	scanf ("%d", &p.produ[nueva_pos].id_gestor);
	
	printf ("\nQuinto, escribe el stock del producto: ");
	scanf ("%d", &p.produ[nueva_pos].stock);
	
	printf ("\nSexto, escribe el compromiso de entrega en dias: ");
	scanf ("%d", &p.produ[nueva_pos].entrega);
	
	printf ("\nPor ultimo, escribe el importe del producto en euros: ");
	scanf ("%d", &p.produ[nueva_pos].importe);
	
	p.num_prod = nueva_id;
	
	guardar_productos (p);
	
	printf ("Se ha registrado el producto %s correctamente", p.produ[nueva_pos].nombre);
	getchar ();
	
	return p;
}

produ_vect modificar_productos (produ_vect p, int pos) {
	//CAMBIO DE INFORMACION//
	int op = -1;
	
	do {
		//MOSTRAR INFORMACION//
		clear ();
		printf ("\n(1) Nombre: %s\n", p.produ[pos].nombre);
		printf ("(2) Descripcion: %s\n", p.produ[pos].descrip);
		printf ("(3) Id de la categoria: %d\n", p.produ[pos].id_categ);
		printf ("(4) Id del gestor: %d\n", p.produ[pos].id_gestor);
		printf ("(5) Stock del producto: %d\n", p.produ[pos].stock);
		printf ("(6) Dias de compromiso de entrega: %d\n", p.produ[pos].entrega);
		printf ("(7) Importe en euros: %d\n", p.produ[pos].importe);
		
		printf ("\n---> QUE DESEA MODIFICAR: <---\n\n");
		printf ("1. Nombre\n2. Descripcion\n3. Id de la categoria\n4. Id del gestor\n5. Stock del producto\n6. Dias de compromiso de entrega\n7. Importe en euros\n0. Salir\n############################\n");
		scanf ("%d", &op);
		
		switch (op) {
			case 1:
				printf ("\nNombre actual: %s\n", p.produ[pos].nombre);
				printf ("Ingrese el nuevo nombre (maximo 15 caracteres): ");
				fflush (stdin);
				fgets (p.produ[pos].nombre, 16, stdin);
				cambio (p.produ[pos].nombre);
			break;
			
			case 2:
				printf ("\nDescripcion actual: %s\n", p.produ[pos].descrip);
				printf ("Ingrese la nueva descripcion (maximo 50 caracteres): ");
				fflush (stdin);
				fgets (p.produ[pos].descrip, 51, stdin);
				cambio (p.produ[pos].descrip);
			break;
			
			case 3:
				printf ("\nId de la categoria actual: %d\n", p.produ[pos].id_categ);
				printf ("Ingrese la nueva id de la categoria (maximo 4 digitos): ");
				scanf ("%d", &p.produ[pos].id_categ);
			break;
			
			case 4:
				printf ("\nId del gestor actual: %d\n", p.produ[pos].id_gestor);
				printf ("Ingrese la nueva id del gestor (maximo 4 digitos): ");
				scanf ("%d", &p.produ[pos].id_gestor);
			break;
			
			case 5:
				printf ("\nStock actual: %d\n", p.produ[pos].stock);
				printf ("Ingrese la nueva cantidad de stock: ");
				scanf ("%d", &p.produ[pos].stock);
			break;
			
			case 6:
				printf ("\nDias hasta la entrega actuales: %d\n", p.produ[pos].entrega);
				printf ("Ingrese la nueva cantidad de dias hasta la entrega: ");
				scanf ("%d", &p.produ[pos].entrega);
			break;
			
			case 7:
				printf ("\nImporte en euros actual: %d\n", p.produ[pos].importe);
				printf ("Ingrese el nuevo importe en euros: ");
				scanf ("%d", &p.produ[pos].importe);
			break;
			
			case 0:		//Caso de salida	
			break;
			
			default:	//Caso de error al seleccionar
				printf ("Seleccione una opcion valida: ");
			break;
		}
		guardar_productos (p);
	}while (op < 0 || op > 7);
	
	printf ("Seleccion realizada correctamente (%d)", op);
	
	return p;
}

produ_vect eliminar_productos (produ_vect p, int pos) {
	int i, resp1, resp2;
	char respuesta;
	
	printf ("\nEstas seguro que deseas eliminar el producto (S/N)?");
	fflush (stdin);
	scanf ("%c", &respuesta);
	
	if (respuesta == 'S' || respuesta == 's') {
		for (i = pos; i < p.num_prod - 1; i++) {	//Desplazar elementos hacia atras
			p.produ[i] = p.produ[i + 1];
			p.produ[i].id_prod = i + 1;				//Reasignar las id de los productos
		}
	
		p.num_prod--;			//Reducir la variable del numero de productos
		
		p.produ = realloc(p.produ, p.num_prod*sizeof(productos));	//Reasignar el tamaño del vector
	
		if (p.produ == NULL) {
			printf ("\nNo se pudo asignar la estructura de productos");
        	getchar ();
        	exit (EXIT_FAILURE);
		}
	
		guardar_productos (p);
	
		printf ("\n\nProducto eliminado correctamente\n");
	}
	
	if (respuesta == 'N' || respuesta == 'n') {
		printf ("\n\nVolviendo al menu anterior...\n");
		getchar ();
	}
	
	return p;
}

produ_vect buscar_productos (produ_vect p) {
	int i, op1, op2, op3, naux, encontrado = 0, prod_encontrados = 0, indices[p.num_prod];	//Vector para almacenar los indices de los productos encontrados
	char saux[51];
	
	do {
		printf ("\n---> BIENVENIDO AL BUSCADOR DE PRODUCTOS: <---\n");
		printf ("\nQue criterio de busqueda desea utilizar?\n\n");
		printf ("1. Id del producto\n2. Nombre\n3. Descripcion\n4. Id de la categoria\n5. Id del gestor\n6. Stock del producto\n7. Dias de compromiso de entrega\n8. Importe en euros\n0. Salir\n############################\n");
		scanf ("%d", &op1);
		
		switch (op1) {
			case 1:
				printf ("\nEscriba el id del producto que desee buscar: ");
				scanf ("%d", &naux);
				
				for (i = 0; i < p.num_prod && encontrado == 0; i++) {
					if (naux == p.produ[i].id_prod) {
						encontrado = 1;
						
						do {
							printf ("\nUn producto ha sido encontrado bajo el id escrito, este se trata de un %s-%s", p.produ[i].nombre, p.produ[i].descrip);
							printf ("\n\nQue desea hacer con el producto?");
							printf ("\n(1) Modificar los datos del producto");
							printf ("\n(2) Eliminar el producto");
							printf ("\n(0) Salir\n\n");
							scanf ("%d", &op2);
							
							switch (op2) {
								case 1:
									modificar_productos (p, i);
								break;
							
								case 2:
									eliminar_productos (p, i);
								break;
							
								case 0:
								break;
							
								default:
									printf ("Seleccione una opcion valida: ");
								break;
							}
						}while (op2 < 0 || op2 > 2);
					}
				}
				
				if (encontrado == 0) {
					printf ("No se encontro ningun producto con el id especificado\n");
				}
			break;
			
			case 2:
				printf ("\nEscriba el nombre del producto que desee buscar (maximo 15 caracteres): ");
				fflush (stdin);
				fgets (saux, 16, stdin);
				cambio (saux);
				
				for (i = 0; i < p.num_prod; i++) {
					if (strcmp(saux, p.produ[i].nombre) == 0) {
						indices[prod_encontrados++] = i;
						encontrado = 1;
					}
				}
				
				if (encontrado == 1) {
					printf ("\nSe encontraron %d productos con el nombre especificado:\n", prod_encontrados);
					
					//Mostrar los productos encontrados
					for (i = 0; i < prod_encontrados; i++) {
						printf ("\n(%d) %s-%s", i + 1, p.produ[indices[i]].nombre, p.produ[indices[i]].descrip);
					}
					
					do {
						//Permitir al usuario seleccionar un producto para modificar o eliminar
						printf ("\n\nSeleccione el producto que desee modificar o eliminar (1-%d): ", prod_encontrados);
						scanf ("%d", &op3);
						
						do {
							printf ("\n\nQue desea hacer con el producto?");
							printf ("\n(1) Modificar los datos del producto");
							printf ("\n(2) Eliminar el producto");
							printf ("\n(0) Salir\n\n");
							scanf ("%d", &op2);
							
							switch (op2) {
								case 1:
									modificar_productos (p, indices[op3 - 1]);
								break;
															
								case 2:
									eliminar_productos (p, indices[op3 - 1]);
								break;
								
								case 0:
								break;
								
								default:
									printf ("Seleccione una opcion valida: ");
								break;
							}
						}while (op2 < 0 || op2 > 2);
					}while (op3 < 1 || op3 > prod_encontrados);
				}
				else {
					printf ("No se encontro ningun producto con el nombre especificado\n");
				}
			break;
			
			case 3:
				printf ("\nEscriba la descripcion del producto que desee buscar (maximo 50 caracteres): ");
				fflush (stdin);
				fgets (saux, 51, stdin);
				cambio (saux);
				
				for (i = 0; i < p.num_prod; i++) {
					if (strcmp(saux, p.produ[i].descrip) == 0) {
						indices[prod_encontrados++] = i;
						encontrado = 1;
					}
				}
				
				if (encontrado == 1) {
					printf ("\nSe encontraron %d productos con la descripcion especificada:\n", prod_encontrados);
					
					//Mostrar los productos encontrados
					for (i = 0; i < prod_encontrados; i++) {
						printf ("\n(%d) %s-%s", i + 1, p.produ[indices[i]].nombre, p.produ[indices[i]].descrip);
					}
					
					do {
						//Permitir al usuario seleccionar un producto para modificar o eliminar
						printf ("\n\nSeleccione el producto que desee modificar o eliminar (1-%d): ", prod_encontrados);
						scanf ("%d", &op3);
						
						do {
							printf ("\n\nQue desea hacer con el producto?");
							printf ("\n(1) Modificar los datos del producto");
							printf ("\n(2) Eliminar el producto");
							printf ("\n(0) Salir\n\n");
							scanf ("%d", &op2);
							
							switch (op2) {
								case 1:
									modificar_productos (p, indices[op3 - 1]);
								break;
															
								case 2:
									eliminar_productos (p, indices[op3 - 1]);
								break;
								
								case 0:
								break;
								
								default:
									printf ("Seleccione una opcion valida: ");
								break;
							}
						}while (op2 < 0 || op2 > 2);
					}while (op3 < 1 || op3 > prod_encontrados);
				}
				else {
					printf ("No se encontro ningun producto con la descripcion especificada\n");
				}
			break;
			
			case 4:
				printf ("\nEscriba la id de la categoria del producto que desee buscar: ");
				scanf ("%d", &naux);
				
				for (i = 0; i < p.num_prod; i++) {
					if (naux == p.produ[i].id_categ) {
						indices[prod_encontrados++] = i;
						encontrado = 1;
					}
				}
				
				if (encontrado == 1) {
					printf ("\nSe encontraron %d productos con la id de la categoria especificada:\n", prod_encontrados);
					
					//Mostrar los productos encontrados
					for (i = 0; i < prod_encontrados; i++) {
						printf ("\n(%d) %s-%s", i + 1, p.produ[indices[i]].nombre, p.produ[indices[i]].descrip);
					}
					
					do {
						//Permitir al usuario seleccionar un producto para modificar o eliminar
						printf ("\n\nSeleccione el producto que desee modificar o eliminar (1-%d): ", prod_encontrados);
						scanf ("%d", &op3);
						
						do {
							printf ("\n\nQue desea hacer con el producto?");
							printf ("\n(1) Modificar los datos del producto");
							printf ("\n(2) Eliminar el producto");
							printf ("\n(0) Salir\n\n");
							scanf ("%d", &op2);
							
							switch (op2) {
								case 1:
									modificar_productos (p, indices[op3 - 1]);
								break;
															
								case 2:
									eliminar_productos (p, indices[op3 - 1]);
								break;
								
								case 0:
								break;
								
								default:
									printf ("Seleccione una opcion valida: ");
								break;
							}
						}while (op2 < 0 || op2 > 2);
					}while (op3 < 1 || op3 > prod_encontrados);
				}
				else {
					printf ("No se encontro ningun producto con la id de la categoria especificada\n");
				}
			break;
			
			case 5:
				printf ("\nEscriba la id del gestor del producto que desee buscar: ");
				scanf ("%d", &naux);
				
				for (i = 0; i < p.num_prod; i++) {
					if (naux == p.produ[i].id_gestor) {
						indices[prod_encontrados++] = i;
						encontrado = 1;
					}
				}
				
				if (encontrado == 1) {
					printf ("\nSe encontraron %d productos con la id del gestor especificada:\n", prod_encontrados);
					
					//Mostrar los productos encontrados
					for (i = 0; i < prod_encontrados; i++) {
						printf ("\n(%d) %s-%s", i + 1, p.produ[indices[i]].nombre, p.produ[indices[i]].descrip);
					}
					
					do {
						//Permitir al usuario seleccionar un producto para modificar o eliminar
						printf ("\n\nSeleccione el producto que desee modificar o eliminar (1-%d): ", prod_encontrados);
						scanf ("%d", &op3);
						
						do {
							printf ("\n\nQue desea hacer con el producto?");
							printf ("\n(1) Modificar los datos del producto");
							printf ("\n(2) Eliminar el producto");
							printf ("\n(0) Salir\n\n");
							scanf ("%d", &op2);
							
							switch (op2) {
								case 1:
									modificar_productos (p, indices[op3 - 1]);
								break;
															
								case 2:
									eliminar_productos (p, indices[op3 - 1]);
								break;
								
								case 0:
								break;
								
								default:
									printf ("Seleccione una opcion valida: ");
								break;
							}
						}while (op2 < 0 || op2 > 2);
					}while (op3 < 1 || op3 > prod_encontrados);
				}
				else {
					printf ("No se encontro ningun producto con la id del gestor especificada\n");
				}
			break;
			
			case 6:
				printf ("\nEscriba el stock del producto que desee buscar: ");
				scanf ("%d", &naux);
				
				for (i = 0; i < p.num_prod; i++) {
					if (naux == p.produ[i].stock) {
						indices[prod_encontrados++] = i;
						encontrado = 1;
					}
				}
				
				if (encontrado == 1) {
					printf ("\nSe encontraron %d productos con el stock especificado:\n", prod_encontrados);
					
					//Mostrar los productos encontrados
					for (i = 0; i < prod_encontrados; i++) {
						printf ("\n(%d) %s-%s", i + 1, p.produ[indices[i]].nombre, p.produ[indices[i]].descrip);
					}
					
					do {
						//Permitir al usuario seleccionar un producto para modificar o eliminar
						printf ("\n\nSeleccione el producto que desee modificar o eliminar (1-%d): ", prod_encontrados);
						scanf ("%d", &op3);
						
						do {
							printf ("\n\nQue desea hacer con el producto?");
							printf ("\n(1) Modificar los datos del producto");
							printf ("\n(2) Eliminar el producto");
							printf ("\n(0) Salir\n\n");
							scanf ("%d", &op2);
							
							switch (op2) {
								case 1:
									modificar_productos (p, indices[op3 - 1]);
								break;
															
								case 2:
									eliminar_productos (p, indices[op3 - 1]);
								break;
								
								case 0:
								break;
								
								default:
									printf ("Seleccione una opcion valida: ");
								break;
							}
						}while (op2 < 0 || op2 > 2);
					}while (op3 < 1 || op3 > prod_encontrados);
				}
				else {
					printf ("No se encontro ningun producto con el stock especificado\n");
				}
			break;
			
			case 7:
				printf ("\nEscriba los dias de compromiso de entrega del producto que desee buscar: ");
				scanf ("%d", &naux);
				
				for (i = 0; i < p.num_prod; i++) {
					if (naux == p.produ[i].entrega) {
						indices[prod_encontrados++] = i;
						encontrado = 1;
					}
				}
				
				if (encontrado == 1) {
					printf ("\nSe encontraron %d productos con los dias de compromiso de entrega especificados:\n", prod_encontrados);
					
					//Mostrar los productos encontrados
					for (i = 0; i < prod_encontrados; i++) {
						printf ("\n(%d) %s-%s", i + 1, p.produ[indices[i]].nombre, p.produ[indices[i]].descrip);
					}
					
					do {
						//Permitir al usuario seleccionar un producto para modificar o eliminar
						printf ("\n\nSeleccione el producto que desee modificar o eliminar (1-%d): ", prod_encontrados);
						scanf ("%d", &op3);
						
						do {
							printf ("\n\nQue desea hacer con el producto?");
							printf ("\n(1) Modificar los datos del producto");
							printf ("\n(2) Eliminar el producto");
							printf ("\n(0) Salir\n\n");
							scanf ("%d", &op2);
							
							switch (op2) {
								case 1:
									modificar_productos (p, indices[op3 - 1]);
								break;
															
								case 2:
									eliminar_productos (p, indices[op3 - 1]);
								break;
								
								case 0:
								break;
								
								default:
									printf ("Seleccione una opcion valida: ");
								break;
							}
						}while (op2 < 0 || op2 > 2);
					}while (op3 < 1 || op3 > prod_encontrados);
				}
				else {
					printf ("No se encontro ningun producto con los dias de compromiso de entrega especificados\n");
				}
			break;
			
			case 8:
				printf ("\nEscriba el importe en euros del producto que desee buscar: ");
				scanf ("%d", &naux);
				
				for (i = 0; i < p.num_prod; i++) {
					if (naux == p.produ[i].importe) {
						indices[prod_encontrados++] = i;
						encontrado = 1;
					}
				}
				
				if (encontrado == 1) {
					printf ("\nSe encontraron %d productos con el importe en euros especificado:\n", prod_encontrados);
					
					//Mostrar los productos encontrados
					for (i = 0; i < prod_encontrados; i++) {
						printf ("\n(%d) %s-%s", i + 1, p.produ[indices[i]].nombre, p.produ[indices[i]].descrip);
					}
					
					do {
						//Permitir al usuario seleccionar un producto para modificar o eliminar
						printf ("\n\nSeleccione el producto que desee modificar o eliminar (1-%d): ", prod_encontrados);
						scanf ("%d", &op3);
						
						do {
							printf ("\n\nQue desea hacer con el producto?");
							printf ("\n(1) Modificar los datos del producto");
							printf ("\n(2) Eliminar el producto");
							printf ("\n(0) Salir\n\n");
							scanf ("%d", &op2);
							
							switch (op2) {
								case 1:
									modificar_productos (p, indices[op3 - 1]);
								break;
															
								case 2:
									eliminar_productos (p, indices[op3 - 1]);
								break;
								
								case 0:
								break;
								
								default:
									printf ("Seleccione una opcion valida: ");
								break;
							}
						}while (op2 < 0 || op2 > 2);
					}while (op3 < 1 || op3 > prod_encontrados);
				}
				else {
					printf ("No se encontro ningun producto con el importe en euros especificado\n");
				}
			break;
			
			case 0:		//Caso de salida	
			break;
			
			default:	//Caso de error al seleccionar
				printf ("Seleccione una opcion valida: ");
			break;
		}
	}while (op1 < 0 || op1 > 8);
}

void menu_prod (produ_vect p) {
	int op;
	char respuesta;
	
	do {
		do{
			printf ("Que desea hacer?\n\n");
			printf ("(1) Rellenar los datos de un nuevo producto\n");
			printf ("(2) Buscar un producto (modificar/eliminar)\n");
			printf ("(0) Salir del menu\n\n");
			scanf ("%d", &op);
		}while (op < 0 || op > 2);
		
		switch (op) {
			case 1:
				agregar_productos (p);
			break;
			
			case 2:
				buscar_productos (p);
			break;
			
			case 0:		//Caso de salida
			break;
			
			default:	//Caso de error al seleccionar
				printf ("Seleccione una opcion valida: ");
			break;
		}
		
		printf ("\nDeseas realizar algun cambio mas? (S/N): ");
		fflush (stdin);
		scanf ("%c", &respuesta);
		printf ("\n");
	}while (respuesta == 'S' || respuesta == 's');
	
	if (respuesta == 'N' || respuesta == 'n') {
		printf ("Gracias por su visita, vuelva pronto :)");
	}
}