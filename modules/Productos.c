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
		f_prod = fopen (filename, "w");		//Excepcion si no encuentra fichero
		perror ("No se pudo abrir el archivo de productos. Se ha creado un nuevo archivo.\n");
		getchar ();
	}
	
	while (fgets (cad_linea, sizeof(cad_linea), f_prod)){		//Contador de clientes en el programa a partir de fichero 
        num_prod++;
    }
	
	rewind (f_prod);											//Necesario para volver a leer el fichero
	
	produ_vect p;
	
  	p.num_prod = num_prod;
  	p.produ = malloc(p.num_prod*sizeof(productos));					//Asignacion de memoria dinamica "p.produ[num_prod]"
  	
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

        if (campo_productos != 8){                                 //Excepcion si fallo en dato de cliente
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
	
	for (i = 0; i < strlen (cad); i++) {
		if (cad[i] == '\n') {
			cad[i] = '\0';
		}
	}
}

void menu_prod () {
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
				
			break;
			
			case 2:
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

/*void rellenar_produ (productos *prod) {
	int i, aux = 0;
	
	FILE *f;
	
	f = fopen ("Productos.txt", "a");
	
	if (f == NULL) {
		printf ("No se ha podido acceder al fichero, intentelo de nuevo");
		exit (1);
	}
	
	for (i = 0; i < N && aux == 0; i++) {
		if (prod[i].lleno == 0) {
			prod = (productos*)realloc(prod, (i + 1)*sizeof(productos));
			
			if (prod == NULL) {
				printf ("No se ha podido reservar la memoria suficiente\n");
				exit (1);
			}
			
			printf ("Producto %i:", i + 1);
			
			printf ("\n\nPrimero, escribe el id del producto: ");
			scanf ("%i", &prod[i].id_prod);
			
			printf ("Segundo, escribe el nombre del producto (maximo 15 caracteres): ");
			fflush (stdin);
			fgets (prod[i].nombre, 16, stdin);
			cambio (prod[i].nombre);
			
			printf ("Tercero, haz una descripcion del producto (maximo 50 caracteres): ");
			fflush (stdin);
			fgets (prod[i].descrip, 51, stdin);
			cambio (prod[i].descrip);
		
			printf ("Cuarto, escribe el id de la categoria: ");
			scanf ("%i", &prod[i].id_categ);
			
			printf ("Quinto, escribe el id del gestor del producto: ");
			scanf ("%i", &prod[i].id_gestor);
			
			printf ("Sexto, escribe la cantidad de stock del producto: ");
			scanf ("%i", &prod[i].stock);
		
			printf ("Septimo, escribe el numero de dias de compromiso de entrega: ");
			scanf ("%i", &prod[i].entrega);
		
			printf ("Por ultimo, escribe el importe del producto en euros: ");
			scanf ("%i", &prod[i].importe);
			
			fprintf (f, "%07d-%s-%s-%04d-%04d-%i-%i-%i\n\n", prod[i].id_prod, prod[i].nombre, prod[i].descrip, prod[i].id_categ, prod[i].id_gestor, prod[i].stock, prod[i].entrega, prod[i].importe);
			
			fclose (f);
			
			prod[i].lleno = 1;
			aux = 1;
		}
	}
		
	if (aux == 0) {
		printf ("\nTodos los productos han sido registrados");
	}
}

void mostrar_produ (productos *prod) {
	char aux[10000];
	
	FILE *f;
	
	f = fopen ("Productos.txt", "r");
	
	if (f == NULL) {
		printf ("No se ha podido acceder al fichero, intentelo de nuevo");
		exit (1);
	}
	
	while (!feof(f)) {
		fgets (cad, 10000, f);
		printf ("%s", cad);
	}
	
	printf ("\n");
	
	fclose (f);
}	*/