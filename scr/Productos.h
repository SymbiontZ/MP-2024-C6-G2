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
//PRECONDICIÓN: Ninguna
//POSTCONDICIÓN: Inicializa una estructura tipo categ_vect con datos almacenados de un fichero
categ_vect cargar_categorias ();

//PRECONDICIÓN: Se le pasa una estructura tipo categ_vect
//POSTCONDICIÓN: Vuelca datos en el fichero pero no devuelve nada
void guardar_categorias (categ_vect);

//PRECONDICIÓN: Se le pasa una estructura tipo categ_vect ya iniciada
//POSTCONDICIÓN: Almacena una nueva categoría en la estructura y la guarda en el fichero
categ_vect agregar_categorias (categ_vect);

//PRECONDICIÓN: Se le pasa una estructura tipo categ_vect
//POSTCONDICIÓN: Devuelve la posición de una categoría en la estructura
int buscar_categorias (categ_vect);

//PRECONDICIÓN: Se le pasa la estructura tipo categ_vect cargada y después recibe la posición de una categoría en la estructura
//POSTCONDICIÓN: Devuelve la estructura tipo categ_vect actualizada con los nuevos cambios
categ_vect modificar_categorias (categ_vect);

//PRECONDICIÓN: Se le pasa la estructura tipo categ_vect cargada y después recibe la posición de una categoría en la estructura
//POSTCONDICIÓN: Devuelve la estructura tipo categ_vect actualizada con los nuevos cambios
categ_vect eliminar_categorias (categ_vect);

//PRECONDICIÓN: Se le pasa una estructura tipo categ_vect ya iniciada
//POSTCONDICIÓN: No devuelve nada
void listar_categorias (categ_vect);

//PRECONDICIÓN: Se le pasa una estructura tipo categ_vect ya iniciada
//POSTCONDICIÓN: Accedemos a diversas funciones para la creación, modificación y eliminación de categorías
void menu_categ (categ_vect);


//---> PRODUCTOS: <---
//PRECONDICIÓN: Ninguna
//POSTCONDICIÓN: Inicializa una estructura tipo produ_vect con datos almacenados de un fichero
produ_vect cargar_productos ();

//PRECONDICIÓN: Se le pasa una estructura tipo produ_vect
//POSTCONDICIÓN: Vuelca datos en el fichero pero no devuelve nada
void guardar_productos (produ_vect);

//PRECONDICIÓN: Se le pasa tanto una estructura tipo produ_vect como una tipo categ_vect, además se le pasa el valor del id del producto que se está creando
//POSTCONDICIÓN: Devuelve la estructura tipo produ_vect actualizada con los nuevos cambios  
produ_vect seleccionar_categprod (produ_vect, categ_vect, int);

//PRECONDICIÓN: Se le pasa una estructura tipo produ_vect ya iniciada
//POSTCONDICIÓN: Almacena un nuevo producto en la estructura y lo guarda en el fichero
produ_vect agregar_productos (produ_vect, int);

//PRECONDICIÓN: Se le pasa una estructura tipo produ_vect ya iniciada
//POSTCONDICIÓN: Devuelve la posición de un producto en la estructura
int buscar_auxnom (produ_vect);

//PRECONDICIÓN: Se le pasa una estructura tipo produ_vect ya iniciada
//POSTCONDICIÓN: Devuelve la posición de un producto en la estructura
int buscar_auxdesc (produ_vect);

//PRECONDICIÓN: Se le pasa una estructura tipo produ_vect ya iniciada
//POSTCONDICIÓN: Devuelve la posición de un producto en la estructura
int buscar_auxstock (produ_vect);

//PRECONDICIÓN: Se le pasa una estructura tipo produ_vect ya iniciada
//POSTCONDICIÓN: Devuelve la posición de un producto en la estructura
int buscar_auxentrega (produ_vect);

//PRECONDICIÓN: Se le pasa una estructura tipo produ_vect ya iniciada
//POSTCONDICIÓN: Devuelve la posición de un producto en la estructura
int buscar_auximporte (produ_vect);

//PRECONDICIÓN: Se le pasa una estructura tipo produ_vect ya iniciada
//POSTCONDICIÓN: Devuelve la posición de un producto en la estructura
int buscar_productos (produ_vect);

//PRECONDICIÓN: Se le pasa la estructura tipo produ_vect cargada y después recibe la posición de un producto en la estructura
//POSTCONDICIÓN: Devuelve la estructura tipo produ_vect actualizada con los nuevos cambios
produ_vect modificar_productos (produ_vect);

//PRECONDICIÓN: Se le pasa la estructura tipo produ_vect cargada y después recibe la posición de un producto en la estructura
//POSTCONDICIÓN: Devuelve la estructura tipo produ_vect actualizada con los nuevos cambios
produ_vect eliminar_productos (produ_vect);

//PRECONDICIÓN: Se le pasa una estructura tipo produ_vect ya iniciada
//POSTCONDICIÓN: No devuelve nada
void listar_productos (produ_vect);

//PRECONDICIÓN: Se le pasa una estructura tipo produ_vect ya iniciada y el valor del id del gestor
//POSTCONDICIÓN: Accedemos a diversas funciones para la creación, modificación y eliminación de productos
void menu_prod (produ_vect, int);

//PRECONDICIÓN: Se le pasa una estructura tipo produ_vect ya iniciada
//POSTCONDICIÓN: Devuelve la posición de un producto en la estructura
int buscador_prodnombre ();

//PRECONDICIÓN: Se le pasa una estructura tipo produ_vect ya iniciada
//POSTCONDICIÓN: Devuelve la posición de un producto en la estructura
int buscador_prodcateg ();

//PRECONDICIÓN: Se le pasa el valor tanto del id del producto como del número de unidades que se le quiere asignar ahora a este
//POSTCONDICIÓN: Devuelve la estructura tipo produ_vect actualizada con los nuevos cambios
produ_vect cambiar_stock (int, int);

//PRECONDICIÓN: Se le pasa una estructura tipo produ_vect ya iniciada y un entero que funciona como id a comparar
//POSTCONDICIÓN: Devuelve la estructura tipo produ_vect actualizada con los nuevos cambios
produ_vect modificar_prodgestor (produ_vect, int);

//PRECONDICIÓN: Se le pasa una estructura tipo produ_vect ya iniciada y un entero que funciona como id a comparar
//POSTCONDICIÓN: Devuelve la estructura tipo produ_vect actualizada con los nuevos cambios
produ_vect eliminar_prodgestor (produ_vect, int);

//PRECONDICIÓN: Se le pasa una estructura tipo produ_vect ya iniciada y un entero que funciona como id a comparar
//POSTCONDICIÓN: No devuelve nada
void listar_prodgestor (produ_vect, int);

#endif