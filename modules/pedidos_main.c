#include<stdio.h>
#include<pedidos.h>

void cargar_pedidos()


int main()
{
    cargar_pedidos();
    return 0;
}


void cargar_pedidos(){
    FILE * f_ped;
    f_ped=fopen("pedidos.txt", "w+");
    if(f_ped==NULL){
        printf("ERROR");
    }
}