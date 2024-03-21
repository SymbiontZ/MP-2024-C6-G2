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
			printf ("Que deseas hacer?\n");
			printf ("(1) Rellenar los datos de un nuevo producto\n");
			printf ("(2) Mostrar todos los productos ya existentes\n");
			printf ("(3) Salir del programa\n");
			scanf ("%i", &op);
			printf ("\n");
		}while (op < 1 || op > 3);
		
		switch (op) {
			case 1:
				rellenar_produ (prod);
			break;
			
			case 2:
				mostrar_produ (prod);
			break;
			
			case 3:
				exit(1);
				printf ("Gracias por su visita, vuelva pronto :)");
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

void crear_fichero () {
	int i;
	
	FILE *f;
	
	f = fopen ("Productos.txt", "a");
	
	if (f == NULL) {
		printf ("No se ha podido acceder al fichero, intentelo de nuevo");
		exit (1);
	}
}

void rellenar_produ (productos prod[]) {
	int i, n1, aux = 0;
	char cad[84];
	
	crear_fichero ();
	
	for (i = 0; i < N && aux == 0; i++) {
		printf ("Primero, escribe la id del producto: ");
		
		printf ("Segundo, haz una descripcion del producto (maximo 50 caracteres): ");
		fflush (stdin);
	}
}
	
	
	
	
	
	
	
	