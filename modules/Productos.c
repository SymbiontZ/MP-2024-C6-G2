#include "./productos.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

produ_vect cargar_productos () {
	char filename[] = "../data/Productos.txt";   
    int num_prod = 0;                           //Numero de productos registrados
    int i = 0;                          		
    char cad_linea[250];                        //Caracteres maximos que puede ocupar una linea en fichero
    int campo_productos;                        //Entero que verifica nº campos de la estructura productos
	
	FILE *f_prod;
	
	f_prod = fopen (filename, "r");
	
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
        campo_productos = sscanf (cad_linea, "%d-%16[^-]-%21[^-]-%d-%d-%i-%i-%i",
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
	
	for (i = 0; i < strlen(cad); i++) {
		if (cad[i] == '\n') {
			cad[i] = '\0';
		}
	}
}

void guardar_productos (produ_vect p) {
	int i;
	
	FILE *f_prod;
	char filename[] = "Productos.txt";
	f_prod = fopen (filename, "w");
	
	if (f_prod == NULL) {
		perror ("\nHa ocurrido un error, intentelo de nuevo");
		getchar ();
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
    fclose(f_prod);
    printf("\n**Estructura guardada con %d poductos\n", p.num_prod);
}

produ_vect agregar_productos (produ_vect p) {
	int nuevo_id = p.num_prod + 1;		//IDENTIFICADOR DEL NUEVO PRODUCTO
	int nueva_pos = nuevo_id - 1;		//POSICION DEL PRODUCTO EN LA ESTRUCTURA
	
	p.produ = realloc(p.produ, nuevo_id*sizeof(productos));
	
	if (p.produ == NULL) {
		printf ("No se pudo asignar la estructura de productos");
        getchar ();
        exit (EXIT_FAILURE);
	}
	
	p.produ[nueva_pos].id_prod = nuevo_id;
	
	printf ("Primero, escribe el nombre del producto: ");
	fflush (stdin);
	fgets (p.produ[nueva_pos].nombre, 16, stdin);
	cambio (p.produ[nueva_pos].nombre);
	
	printf ("\nSengundo, escribe la descripcion del producto: ");
	fflush (stdin);
	fgets (p.produ[nueva_pos].descrip, 51, stdin);
	cambio (p.produ[nueva_pos].descrip);
	
	printf ("\nTercero, escribe el id de la categoria a la que pertenece: ");
	scanf ("%i", &p.produ[nueva_pos].id_categ);
	
	printf ("\nCuarto, escribe el id del gestor del producto: ");
	scanf ("%i", &p.produ[nueva_pos].id_gestor);
	
	printf ("\nQuinto, escribe el stock del producto: ");
	scanf ("%i", &p.produ[nueva_pos].stock);
	
	printf ("\nSexto, escribe el compromiso de entrega en dias: ");
	scanf ("%i", &p.produ[nueva_pos].entrega);
	
	printf ("\nPor ultimo, escribe el importe del producto en euros: ");
	scanf ("%i", &p.produ[nueva_pos].importe);
	
	p.num_prod = nuevo_id;
	
	guardar_productos (p);
	
	printf ("Se ha registrado el producto %s correctamente", p.produ[nueva_pos].nombre);
	getchar ();
	
	return p;
}

void menu_prod (produ_vect p) {
	int op;
	char respuesta;
	
	do {
		do{
			printf ("Que deseas hacer?\n\n");
			printf ("(1) Rellenar los datos de un nuevo producto\n");
			printf ("(2) Mostrar todos los productos ya existentes");
			printf ("\n(3) Salir del programa\n\n");
			scanf ("%i", &op);
			printf ("\n");
		}while (op < 1 || op > 3);
		
		switch (op) {
			case 1:
				agregar_productos (p);
			break;
			
			case 2:
				//Hola :);
			break;
			
			case 3:
				printf ("Gracias por su visita, vuelva pronto :)");
				exit(1);
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