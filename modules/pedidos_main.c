#include<stdio.h>
#include"pedidos.h"
#include<stdlib.h>

pedidos cargar_pedidos();
prod_pedidos cargar_prod_pedidos();

int main()
{
    cargar_pedidos();
    printf("se ha cargado el fichero correctamente");
    return 0;
}

//Cabecera: pedidos cargar_pedidos()
//Precondición: el fichero debe existir y la estructura de cada pedido
//Postcondición: guarda en un vector de tipo pedido cada pedido que hay en el fichero.

pedidos cargar_pedidos(){
    
    int n_pedidos=0, i, campo_pedidos;
    char cad_aux[150]; //cadena auxiliar en la que se guarda cada linea del fichero
    
    FILE * f_ped;
    f_ped=fopen("../data/Pedidos.txt", "rw+"); //abre el fichero Pedidos.txt
    if(f_ped==NULL){ //si no existe el fichero o esta vacio lo crea
        printf("ERROR");
    }

    while(fgets(cad_aux, sizeof(cad_aux), f_ped)){ //lee cada linea del fichero y la almacena en la variable cad_aux, para contar las lineas del fichero
        //printf("%s", cad_aux);
        n_pedidos++; //numero de pedidos (numero de lineas del fichero)
    }
    rewind(f_ped);

    pedidos p; //p.pedidos es la variable de tipo pedido que esta dentro de la estructura pedidos. 

    p.lon=n_pedidos;

    p.pedidos=malloc(n_pedidos*sizeof(pedido)); //definimos un vector dinamico de tipo pedido, en cada posicion estara la estructura rellenada con los datos dela primera linea
    while(fgets(cad_aux, sizeof(cad_aux), f_ped) && i<n_pedidos){
        //funcion sscanf(cadena, campos a separar):
        //campos a separar-> %tipo_campo  separardor
        //cuando es cadena %n_caracteres[hasta donde lee]
        campo_pedidos=sscanf(cad_aux, "%d-%10[^-]-%d-%10[^-]-%10[^-]-%10[^-]",
            &p.pedidos[i].id_pedido,
            p.pedidos[i].f_pedido,
            &p.pedidos[i].id_cliente,
            p.pedidos[i].lugar,
            p.pedidos[i].id_locker,
            p.pedidos[i].id_cod);
        i++;
    }


}

prod_pedidos cargar_prod_pedidos(){
    int n_prod_ped=0, i, campo_prod_ped;
    char cad_aux[150];
    
    FILE * f_prod_ped;
    f_prod_ped=fopen("../data/ProductosPedidos.txt", "rw+");
    if(f_prod_ped==NULL){
        printf("ERROR");
    }

    while(fgets(cad_aux, sizeof(cad_aux), f_prod_ped)){
        n_prod_ped++;
    }
    rewind(f_prod_ped);

    prod_pedidos prod;

    prod.lon=n_prod_ped;

    prod.prod_pedidos=malloc(n_prod_ped*sizeof(prod_pedido));
    while(fgets(cad_aux, sizeof(cad_aux), f_prod_ped) && i<n_prod_ped){
        campo_prod_ped=sscanf(cad_aux, "%d-%d-%d-%10[^-]-%d-%10[^-]-%f-%d-%d-%10[^-]",
            &prod.prod_pedidos[i].id_pedido,
            &prod.prod_pedidos[i].id_prod,
            &prod.prod_pedidos[i].num_unid,
            prod.prod_pedidos[i].f_entrega,
            &prod.prod_pedidos[i].importe,
            prod.prod_pedidos[i].estado,
            &prod.prod_pedidos[i].id_transp,
            &prod.prod_pedidos[i].id_locker,
            &prod.prod_pedidos[i].cod_locker,
            prod.prod_pedidos[i].f_devolucion);
        
        i++;
    }

}

devoluciones cargar_devoluciones(){
    int n_dev=0, i, campo_devoluciones;
    char cad_aux[150];

    FILE * f_dev;
    f_dev=fopen("../data/Devoluciones.txt", "wr+");
    if(f_dev==NULL){
        printf("ERROR");
    }

    while(fgets(cad_aux, sizeof(cad_aux), f_dev)){
        n_dev++;
    }
    rewind(f_dev);

    devoluciones dev;
    dev.lon=n_dev;

    dev.devoluciones=malloc(n_dev*sizeof(devolucion));
    while(fgets(cad_aux, sizeof(cad_aux), f_dev) && i<n_dev){
        campo_devoluciones=sscanf(cad_aux, "%d-%d-%10[^-]-%50[^-]-%10[^-]-%10[^-]-%10[^-]",
        &dev.devoluciones[i].id_pedido,
        &dev.devoluciones[i].id_prod,
        dev.devoluciones[i].f_devol,
        dev.devoluciones[i].estado,
        dev.devoluciones[i].f_aceptacion,
        dev.devoluciones[i].f_caducidad);
    
    i++;
    }
}