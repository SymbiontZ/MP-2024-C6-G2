#include<stdio.h>
#include"pedidos.h"

pedidos cargar_pedidos();


int main()
{
    cargar_pedidos();
    printf("se ha cargado el fichero correctamente");
    return 0;
}


pedidos cargar_pedidos(){
    FILE * f_ped;
    int n_pedidos=0, i;
    f_ped=fopen("../data/Pedidos.txt", "rw+");
    char cad_aux[150]; //cadena auxiliar en la que se guarda cada linea del fichero
    if(f_ped==NULL){
        printf("ERROR");
    }
    while(fgets(cad_aux, sizeof(cad_aux), f_ped)){ //lee cada linea del fichero y la almacena en la variable cad_aux, para contar las lineas del fichero
        printf("%s", cad_aux);
        n_pedidos++;
    }

    pedidos p;
    p.pedidos=(pedido*)malloc(n_pedidos*sizeof(pedido)); //definimos un vector dinamico de tipo pedido, en cada posicion estara la estructura rellenada con los datos dela primera linea
    for (i=0;i<n_pedidos;i++){
        
    }
}