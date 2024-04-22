#include "Descuentos.h"

int main(){
    DescClientes dc = Cargar_DescuentosClientes();
    fecha fch_cad;
    fch_cad.dia = 21;
    fch_cad.mes = 4;
    fch_cad.anio = 2025;
    //marcar_aplicado(1, "black001");

    Asignar_Descuentos(dc, "black001", 2, fch_cad);
    return 0;
}