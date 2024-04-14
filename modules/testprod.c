#include "complementos.h"
#include "pedidos.h"



int main(){
    pedidos p = cargar_pedidos();
    prod_pedidos prods_p = cargar_prod_pedidos();
    int id_cliente = 1;

    listapedidos_cliente(prods_p,p,id_cliente);
    
    return 0;
}