#include "./productos.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main () {
	productos prod[N];
	int op;
	char respuesta;
	
	do {
		do{
			printf ("Que deseas hacer?\n\n");
			printf ("(1) Rellenar los datos de un nuevo producto\n");
			printf ("(2) Mostrar todos los productos ya existentes\n");
			printf ("(3) Salir del programa\n\n");
			scanf ("%i", &op);
			printf ("\n");
		}while (op < 1 || op > 3);
		
		switch (op) {
			case 1:
				rellenar_produ (prod);
			break;
			
			case 2:
				//mostrar_produ (prod);
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
	
	return 0;
}

void vacio (productos prod[]) {
	int i;
	
	for (i = 0; i < N; i++) {
		prod[i].lleno = 0;
	}
}

void cambio (char cad[]) {
	int i;
	
	for (i = 0; i < strlen (cad); i++) {
		if (cad[i] == '\n') {
			cad[i] = '\0';
		}
	}
}

void rellenar_produ (productos prod[]) {
	int i, n1, n2, n3, n4, n5, n6, aux = 0;
	char cad[84];
	
	FILE *f;
	
	f = fopen ("Productos.txt", "a");
	
	if (f == NULL) {
		printf ("No se ha podido acceder al fichero, intentelo de nuevo");
		exit (1);
	}
	
	for (i = 0; i < N && aux == 0; i++) {
		if (prod[i].lleno == 0) {
			printf ("Producto %i/%i: ", i + 1, N);
			
			printf ("\n\nPrimero, escribe el id del producto: ");
			scanf ("%i", &n1);
		
			printf ("Segundo, haz una descripcion del producto (maximo 50 caracteres): ");
			fflush (stdin);
			fgets (prod[i].descrip, 51, stdin);
			cambio (prod[i].descrip);
		
			printf ("Tercero, escribe el id de la categoria: ");
			scanf ("%i", &n2);
		
			printf ("Cuarto, escribe el id del gestor del producto: ");
			scanf ("%i", &n3);
		
			printf ("Quinto, escribe la cantidad de stock del producto: ");
			scanf ("%i", &n4);
		
			printf ("Sexto, escribe el numero de dias de compromiso de entrega: ");
			scanf ("%i", &n5);
		
			printf ("Por ultimo, escribe el importe del producto en euros: ");
			scanf ("%i", &n6);
		
			fprintf (f, "%07d-%s-%04d-%04d-%i-%i-%i\n\n", n1, prod[i].descrip, n2, n3, n4, n5, n6);
		
			fclose (f);
			
			prod[i].lleno = 1;
			aux = 1;
		}
	}
	
	if (aux == 0) {
		printf ("\nTodos los productos han sido registrados");
	}
}	