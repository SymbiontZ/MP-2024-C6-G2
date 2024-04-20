#ifndef PRODUCTOS_H_
#define PRODUCTOS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

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

produ_vect cargar_productos ();
void guardar_productos (produ_vect);
produ_vect agregar_productos (produ_vect);
int buscar_productos (produ_vect);
produ_vect modificar_productos (produ_vect);
produ_vect eliminar_productos (produ_vect);
produ_vect listar_productos (produ_vect);
produ_vect buscador_productos (produ_vect);
void menu_prod (produ_vect);

#endif