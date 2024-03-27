#ifndef COMPLEMTENTOS_H_
#define COMPLEMENTOS_H_

typedef struct{
    int dia;
    int mes;
    int anio;
}fecha;


void clear();
void titulo();

int dia_sist();
int mes_sist();
int anno_sist();

void terminador_cad(char []);

#endif