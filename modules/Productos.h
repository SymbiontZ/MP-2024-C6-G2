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
//POSCONDICIÓN:
categ_vect cargar_categorias ();

//PRECONDICIÓN:
//POSCONDICIÓN:
void guardar_categorias (categ_vect);

//PRECONDICIÓN:
//POSCONDICIÓN:
categ_vect agregar_categorias (categ_vect);

//PRECONDICIÓN:
//POSCONDICIÓN:
int buscar_categorias (categ_vect);

//PRECONDICIÓN:
//POSCONDICIÓN:
categ_vect modificar_categorias (categ_vect);

//PRECONDICIÓN:
//POSCONDICIÓN:
categ_vect eliminar_categorias (categ_vect);

//PRECONDICIÓN:
//POSCONDICIÓN:
void listar_categorias (categ_vect);

//PRECONDICIÓN:
//POSCONDICIÓN:
void menu_categ (categ_vect);

//---> PRODUCTOS: <---
//PRECONDICIÓN:
//POSCONDICIÓN:
produ_vect cargar_productos ();

//PRECONDICIÓN:
//POSCONDICIÓN:
void guardar_productos (produ_vect);

//PRECONDICIÓN:
//POSCONDICIÓN:
produ_vect agregar_productos (produ_vect);

//PRECONDICIÓN:
//POSCONDICIÓN:
int buscar_productos (produ_vect);

//PRECONDICIÓN:
//POSCONDICIÓN:
produ_vect modificar_productos (produ_vect);

//PRECONDICIÓN:
//POSCONDICIÓN:
produ_vect eliminar_productos (produ_vect);

//PRECONDICIÓN:
//POSCONDICIÓN:
void listar_productos (produ_vect);

//PRECONDICIÓN:
//POSCONDICIÓN:
produ_vect buscador_productos (produ_vect);

//PRECONDICIÓN:
//POSCONDICIÓN:
int buscador_prodidcateg ();

#endif