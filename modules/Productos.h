#ifndef PRODUCTOS_H_
#define PRODUCTOS_H_

#define N 100

typedef struct {
	int id_prod;		//Identificador del producto
	char descrip[51];	//Descripción del producto
	int id_categ;		//Id de la categoría a la que pertenece el producto
	int id_gestor;		//Id del gestor del producto
	int stock;			//Stock del producto
	int entrega;		//Fecha de compromiso de entrega en días
	int importe;		//Importe del producto en euros
	int lleno;			//Variable utilizada para diferenciar los productos con todos sus valores rellenados
}productos;

void vacio (productos []);
void cambio (char []);
void rellenar_produ (productos []);
void mostrar_produ (productos []);

#endif