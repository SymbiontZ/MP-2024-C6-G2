#ifndef PRODUCTOS_H_
#define PRODUCTOS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct {
	int id_categ;		//Identificador de la categoría
	char descrip[51];	//Descripción de la categoría
}categorias;

typedef struct {
	categorias *categ;
	int num_cat;
}categ_vect;

typedef struct {
	int id_prod;		//Identificador del producto
	char nombre[16];	//Nombre del producto
	char descrip[51];	//Descripción del producto
	int id_categ;		//Id de la categoría a la que pertenece el producto
	int id_gestor;		//Id del gestor del producto
	int stock;			//Stock del producto
	int entrega;		//Fecha de compromiso de entrega en días
	int importe;		//Importe del producto en euros
}productos;

typedef struct {
	productos *produ;
	int num_prod;
}produ_vect;

//---> CATEGORIAS: <---
//PRECONDICIÓN:
//POSTCONDICIÓN:
categ_vect cargar_categorias ();

//PRECONDICIÓN:
//POSTCONDICIÓN:
void guardar_categorias (categ_vect);

//PRECONDICIÓN:
//POSTCONDICIÓN:
categ_vect agregar_categorias (categ_vect);

//PRECONDICIÓN:
//POSTCONDICIÓN:
int buscar_categorias (categ_vect);

//PRECONDICIÓN:
//POSTCONDICIÓN:
categ_vect modificar_categorias (categ_vect);

//PRECONDICIÓN:
//POSTCONDICIÓN:
categ_vect eliminar_categorias (categ_vect);

//PRECONDICIÓN:
//POSTCONDICIÓN:
categ_vect listar_categorias (categ_vect);

//PRECONDICIÓN:
//POSTCONDICIÓN:
void menu_categ (categ_vect);

//---> PRODUCTOS: <---
//PRECONDICIÓN:
//POSTCONDICIÓN:
produ_vect cargar_productos ();

//PRECONDICIÓN:
//POSTCONDICIÓN:
void guardar_productos (produ_vect);

//PRECONDICIÓN:
//POSTCONDICIÓN:
produ_vect agregar_productos (produ_vect);

//PRECONDICIÓN:
//POSTCONDICIÓN:
int buscar_productos (produ_vect);

//PRECONDICIÓN:
//POSTCONDICIÓN:
produ_vect modificar_productos (produ_vect);

//PRECONDICIÓN:
//POSTCONDICIÓN:
produ_vect eliminar_productos (produ_vect);

//PRECONDICIÓN:
//POSTCONDICIÓN:
void listar_productos (produ_vect);

//PRECONDICIÓN:
//POSTCONDICIÓN:
void menu_prod (produ_vect);

//PRECONDICIÓN:
//POSTCONDICIÓN:
int buscador_prodnombre ();

//PRECONDICIÓN:
//POSTCONDICIÓN:
int buscador_prodcateg ();

//PRECONDICIÓN:
//POSTCONDICIÓN:
produ_vect cambiar_stock (int, int);

//PRECONDICIÓN:
//POSTCONDICIÓN:
produ_vect modificar_prodgestor (produ_vect);

//PRECONDICIÓN:
//POSTCONDICIÓN:
produ_vect eliminar_prodgestor (produ_vect);

//PRECONDICIÓN:
//POSTCONDICIÓN:
produ_vect listar_prodgestor (produ_vect);

#endif