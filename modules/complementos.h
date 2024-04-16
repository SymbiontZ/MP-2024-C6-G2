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


#endif