#ifndef CATEGORIAS_H_
#define CATEGORIAS_H_

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

categ_vect cargar_categorias ();
void guardar_categorias (categ_vect);
categ_vect agregar_categorias (categ_vect);
int buscar_categorias (categ_vect);
categ_vect modificar_categorias (categ_vect);
categ_vect eliminar_categorias (categ_vect);
categ_vect listar_categorias (categ_vect);
void menu_categ (categ_vect);

#endif