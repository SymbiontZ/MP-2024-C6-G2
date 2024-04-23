
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

int anio_sist(){
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

char confirmacion(){
    char resp = '0';

    fflush(stdin);
    scanf("%c", &resp);
    fflush(stdin);
    while(resp != 'S' && resp != 's' && resp != 'N' && resp != 'n'){
        printf("Seleccione una opcion valida: ");
        scanf("%c", &resp);
        fflush(stdin);
    }

    return resp;
}

int input_int(){
    int verif_int, //Verifica que se haya introducido numero entero
        num;

    fflush(stdin);
    do{
        verif_int = scanf("%d", &num);
        fflush(stdin);
        if (verif_int != 1)
            printf("Introduca un numero entero: ");
    } while (verif_int != 1);
    
    return num;
}

int comprobar_fecha(fecha fch_comp, fecha fch_limite){
    if (fch_comp.anio > fch_limite.anio) //Si sobrepasa el anio
        return 0;
    else if(fch_comp.anio == fch_limite.anio){
        if(fch_comp.mes > fch_limite.mes)
            return 0;
        else if(fch_comp.mes == fch_limite.mes){
            if(fch_comp.dia > fch_limite.dia)
                return 0;
            else
                return 1;
        }else
            return 1;
    }else
        return 1;
}


fecha crear_fechacad(fecha fch_base){
    fecha fch_cad;
    int fch_ok;     //Variable para comprobar la fecha es valida
    do{
        printf("FECHA ACTUAL: %02d / %02d / %04d\n", fch_base.dia, fch_base.mes, fch_base.anio);
        printf("Introduzca el dia que caduca: ");
        fch_cad.dia = input_int();
        printf("Introduzca el mes que caduca: ");
        fch_cad.mes = input_int();
        printf("Introduzca el anio que caduca: ");
        fch_cad.anio = input_int();

        fch_ok = comprobar_fecha(fch_base, fch_cad);
        if (fch_ok != 1){
            printf("La fecha indicada no es valida. Vuelva a intentarlo.\n");
        }
        
    } while (fch_ok != 1);

    return fch_cad;
}