#include <stdio.h>
#include <string.h>
#define N 100

typedef struct {
	int Id_prod[7];		//Identificador del producto
	char Descrip[50];	//Descripción del producto
	int Id_categ[4];	//Id de la categoría a la que pertenece el producto
	int Id_gestor[4];	//Id del gestor del producto
	int Stock[4];		//Stock del producto
	int Entrega[3];		//Fecha de compromiso de entrega en días
	int Importe[4];		//Importe del producto en euros
	int lleno			//Variable utilizada para diferenciar los productos con todos sus valores rellenados
}productos;

void vacio (productos []);
void cambio (char []);
void rellenar_idprod (productos []);
void rellenar_descrip (productos []);
void rellenar_idcateg (productos []);
void rellenar_idgestor (productos []);
void rellenar_stock (productos []);
void rellenar_entrega (productos []);
void rellenar_importe (productos []);

int main () {
	productos prod[N];
	int op;
	char respuesta;
	
	do {
		do{
			printf ("Que deseas hacer?\n");
			printf ("(1) Identificador del producto\n");
			printf ("(2) Descripción del producto\n");
			printf ("(3) Id de la categoría a la que pertenece el producto\n");
			printf ("(4) Id del gestor del producto\n");
			printf ("(5) Stock del producto\n");
			printf ("(6) Fecha de compromiso de entrega en días\n");
			printf ("(7) Importe del producto en euros\n");
			scanf ("%i", &op);
			printf ("\n");
		}while (op < 1 || op > 7);
		
		switch (op) {
			case 1:
				rellenar_idprod (prod);
			break;
			
			case 2:
				rellenar_descrip (prod);
			break;
			
			case 3:
				rellenar_idcateg (prod);
			break;
			
			case 4:
				rellenar_idgesor (prod);
			break;
			
			case 5:
				rellenar_stock (prod);
			break;
			
			case 6:
				rellenar_entrega (prod);
			break;
			
			case 7:
				rellenar_importe (prod);
			break;
		}
		
		printf ("\nDeseas realizar algun cambio mas? (S/N): ");
		fflush (stdin);
		scanf ("%c", &respuesta);
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
	
	for (i = 0; i < N; i++) {
		if (cad[i] == '\n') {
			cad[i] = '\0';
		}
	}
}
	
void rellenar_idprod (productos prod[]) {
	int i;
}
	
	
	
	
	
	
	
	