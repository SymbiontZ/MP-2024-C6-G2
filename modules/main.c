#include<stdio.h>
#include<stdlib.h>
#include"empresas.h"

int main(){
    admin_prov_vect ap = cargar_adminprov();
    printf("%s", ap.usuarios[0].email);
    return 0;
}

void iniciar_sesion(){}