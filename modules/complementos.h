#ifndef COMPLEMENTOS_H_
#define COMPLEMENTOS_H_

#include<stdlib.h>
#include<string.h>
#include<stdio.h> 
#include<time.h>

typedef struct{
    int dia;
    int mes;
    int anio;
}fecha;


void clear();
void titulo();

int dia_sist();
int mes_sist();
int anio_sist();

//PRECONDICION: Se le pasa una cadena
//POSCONDICION: Se le cambia el caracter salto de linea por terminador
void terminador_cad(char []);

//PRECONDICION: Ninguna
//POSCONDICION: Devuelve un caracter para respuestas si/no
char confirmacion();

//PRECONDICION: Ninguna
//POSCONDICION: Devuelve un numero entero siempre
int input_int();


//PRECONDICION: Se le pasa dos estructuras tipo fecha, la fecha que quieres comparar y la fecha limite.
//POSCONDICION: Devuelve un 1 si no ha pasado la fecha limite y un 0 si no la ha pasado.
int comprobar_fecha(fecha fch_comp, fecha fch_lim);

//PRECONDICION: Se le pasa una estructura tipo fecha con valores asignados a comprobar.
//POSCONDICION: Devuelve una estructura tipo fecha para usarlo como fecha de caducidad.
fecha crear_fechacad(fecha fch_base);
#endif