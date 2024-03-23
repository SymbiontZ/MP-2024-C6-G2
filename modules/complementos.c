#include<stdlib.h>
#include<stdio.h> 
#include<time.h>

time_t tiempo_actual;
struct tm *fecha;

void clear();

void clear(){
    system("cls");
}

int dia_sist(){
    tiempo_actual = time(NULL);
    fecha = localtime(&tiempo_actual);
    int dia = fecha->tm_mday;    
    return  dia;
}

int mes_sist(){
    tiempo_actual = time(NULL);
    fecha = localtime(&tiempo_actual);
    int mes = fecha->tm_mon; 

    return  mes;
}

int anno_sist(){
    tiempo_actual = time(NULL);
    fecha = localtime(&tiempo_actual);
    int anno = fecha->tm_year; 

    return  anno;
}