#ifndef PRODUCTOS_H_
#define PRODUCTOS_H_

#define N 100

typedef struct {
	int Id_prod[7];		//Identificador del producto
	char Descrip[51];	//Descripción del producto
	int Id_categ[4];	//Id de la categoría a la que pertenece el producto
	int Id_gestor[4];	//Id del gestor del producto
	int Stock[4];		//Stock del producto
	int Entrega[3];		//Fecha de compromiso de entrega en días
	int Importe[4];		//Importe del producto en euros
	int lleno			//Variable utilizada para diferenciar los productos con todos sus valores rellenados
}productos;

void vacio (productos []);
void cambio (char []);
void crear_fichero ();
void rellenar_produ (productos []);
void mostrar_produ (productos []);

#endif