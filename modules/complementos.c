
#include"complementos.h"

time_t tiempo_actual;
struct tm *fechasys;

void clear(){
    system("cls");
}

int dia_sist(){
    tiempo_actual = time(NULL);
    fechasys = localtime(&tiempo_actual);
    int dia = fechasys->tm_mday;    
    return  dia;
}

int mes_sist(){
    tiempo_actual = time(NULL);
    fechasys = localtime(&tiempo_actual);
    int mes = fechasys->tm_mon+1; 

    return  mes;
}

int anno_sist(){
    tiempo_actual = time(NULL);
    fechasys = localtime(&tiempo_actual);
    int anno = fechasys->tm_year+1900; 

    return  anno;
}

void titulo(){
    printf("### ESIZON ###\n");
}

void terminador_cad(char cad[]) {
    int i;
    int len = strlen(cad);

    for (i = 0; i < len; i++) {
        if (cad[i] == '\n') {
            cad[i] = '\0';
            len = i; // ACABA BUCLE SI CAMBIA EL SALTO DE LINEA POR TERMINADOR
        }
    }
}