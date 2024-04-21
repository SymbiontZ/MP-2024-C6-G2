#include "Descuentos.h"

int main(){
    Descuentos D = Cargar_Descuentos();
    
    char cod[] = "black001";

    int i = desc_activo(cod);

    printf("%d", i);
    return 0;
}