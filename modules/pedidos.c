#include<stdio.h>
#include"pedidos.h"
#include<stdlib.h>
#include<string.h>
#include"complementos.h"

pedidos cargar_pedidos();
prod_pedidos cargar_prod_pedidos();
devoluciones cargar_devoluciones();



//Cabecera: pedidos cargar_pedidos()
//Precondición: el fichero debe existir y la estructura de cada pedido
//Postcondición: guarda en un vector de tipo pedido cada pedido que hay en el fichero.

pedidos cargar_pedidos(){
    
    int n_pedidos=0, i=0, campo_pedidos;
    char cad_aux[150]; //cadena auxiliar en la que se guarda cada linea del fichero
    
    FILE * f_ped;
    f_ped=fopen("../data/Pedidos.txt", "r"); //abre el fichero Pedidos.txt
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
        campo_pedidos=sscanf(cad_aux, "%d-%d/%d/%d-%d-%10[^-]-%10[^-]-%10[^-]",
            &p.pedidos[i].id_pedido,
            &p.pedidos[i].f_pedido.dia,
            &p.pedidos[i].f_pedido.mes,
            &p.pedidos[i].f_pedido.anio,
            &p.pedidos[i].id_cliente,
            p.pedidos[i].lugar,
            p.pedidos[i].id_locker,
            p.pedidos[i].id_cod);

        if(campo_pedidos!=8){
            printf("error, i=%d", i);
        }

        i++;
        
    }
    return p;
}

//Cabecera: void crear_pedido(int id_cliente, pedidos p)
//Precondicion: estrcutura pedidos cargada con datos del fichero Pedidos.txt y el id del cliente que ha realizado pedido, lo sabemos cuando ha iniciado sesión en la aplicación
//Postcondicion: se crea un nuevo pedido realizado por un cliente y se guarda en la estructura pedidos, ademas de escribirlo en el fichero Pedidos.txt
void crear_pedido(int id_cliente, pedidos p){
    int n_pedidos=p.lon, i=0, nueva_id, pos, lugar, cheque;
    char cod_cheque[10];
    nueva_id=n_pedidos +1; //id de un nuevo pedido, será el numero de pedidos que hay en el fichero +1
    pos=nueva_id -1; //posicion del nuevo pedido en la estructura, es uno menos que el id ya que el vector empieza en la posicion 0
    p.pedidos=realloc(p.pedidos, nueva_id*sizeof(pedido)); //reasignamos memoria dinámica, el tamaño coincide con nueva_id ya que son los pedidos que habrá en la estructura
    
    p.pedidos[pos].id_pedido=nueva_id;
    p.pedidos[pos].id_cliente=id_cliente;

    p.pedidos[pos].f_pedido.dia=dia_sist();
    p.pedidos[pos].f_pedido.mes=mes_sist();
    p.pedidos[pos].f_pedido.anio=anno_sist();

    printf("Selecciona un lugar de entrega: \n");
    printf("1. DOMICILIO\n");
    printf("2. LOCKER\n");
    printf("su opcion : ");
    scanf("%d", &lugar);
    switch(lugar){
        case 1:
            strcpy(p.pedidos[pos].lugar, "Domicilio");
            strcpy(p.pedidos[pos].id_locker, "00000000");
            break;
        case 2:
            strcpy(p.pedidos[pos].lugar, "Locker");
            //añadir un id del locker y un codigo del locker
            //funciones modulo lockers para mirar locker libres
            break;
        default:
            printf("opcion no valida");
    }

    printf("Desea utilizar un cheque\n");
    printf("1. SI\n");
    printf("2. NO\n");
    printf("su opcion: ");
    scanf("%d", &cheque);
    switch(cheque){
        case 1:
            printf("introduce el codigo del cheque:");
            fflush(stdin);
            fgets(cod_cheque, 11, stdin);
            //if cod_cheque existe y es valido lo copia al fichero
            int len = strlen(cod_cheque);
            if (len > 0 && cod_cheque[len - 1] == '\n') {
                cod_cheque[len - 1] = '\0'; // Reemplazar el carácter de salto de linea con el carácter nulo
            }
            strcpy(p.pedidos[pos].id_cod, cod_cheque);
            break;
        case 2:
            strcpy(p.pedidos[pos].id_cod, "000000000");
            break;
        
        default:
            printf("opcion no valida");
    }

    p.lon=p.lon+1; //actualiza el numero de pedidos que hay 

    guardar_pedido(p);
    printf("Se han guardado los datos correctamente\n");
}


//Cabecera guardar_pedido(pedidos p, int pos)
//Precondición: estructura pedidos cargada con los datos del ultimo pedido realizado
//Postcondicion: se guarda en el fichero la estructura pedidos
void guardar_pedido(pedidos p){
    int i;

    FILE *f_ped;
    f_ped=fopen("../data/Pedidos.txt", "w");
    if(f_ped==NULL){
        printf("ERROR");
    }
    
    for(i=0;i<p.lon;i++){
        fprintf(f_ped,"%d-%d/%d/%d-%d-%s-%s-%s\n", 
            p.pedidos[i].id_pedido,
            p.pedidos[i].f_pedido.dia,
            p.pedidos[i].f_pedido.mes,
            p.pedidos[i].f_pedido.anio,
            p.pedidos[i].id_cliente,
            p.pedidos[i].lugar,
            p.pedidos[i].id_locker,
            p.pedidos[i].id_cod);
    }
}

//Cabecera: prod_pedidos cargar_prod_pedidos()
//Precondicion:
//Postcondicion: carga en la estructura prod_pedidos los datos del fichero ProductosPedidos.txt
prod_pedidos cargar_prod_pedidos(){
    int n_prod_ped=0, i, campo_prod_ped;
    char cad_aux[200];
    
    FILE * f_prod_ped;
    f_prod_ped=fopen("../data/ProductosPedidos.txt", "r");
    if(f_prod_ped==NULL){
        printf("ERROR");
    }

    while(fgets(cad_aux, sizeof(cad_aux), f_prod_ped)){
        n_prod_ped++; //numero de productos pedidos
    }
    rewind(f_prod_ped);

    prod_pedidos prod_p;

    prod_p.lon=n_prod_ped;

    prod_p.prod_pedidos=malloc(n_prod_ped*sizeof(prod_pedido));
    
    while(fgets(cad_aux, sizeof(cad_aux), f_prod_ped) && i<n_prod_ped){
        campo_prod_ped=sscanf(cad_aux, "%d-%d-%d-%d/%d/%d-%d-%10[^-]-%d-%10[^-]-%10[^-]-%d/%d/%d",
            &prod_p.prod_pedidos[i].id_pedido,
            &prod_p.prod_pedidos[i].id_prod,
            &prod_p.prod_pedidos[i].num_unid,
            &prod_p.prod_pedidos[i].f_entrega.dia,
            &prod_p.prod_pedidos[i].f_entrega.mes,
            &prod_p.prod_pedidos[i].f_entrega.anio,
            &prod_p.prod_pedidos[i].importe,
            prod_p.prod_pedidos[i].estado,
            &prod_p.prod_pedidos[i].id_transp,
            prod_p.prod_pedidos[i].id_locker,
            prod_p.prod_pedidos[i].cod_locker,
            &prod_p.prod_pedidos[i].f_devolucion.dia,
            &prod_p.prod_pedidos[i].f_devolucion.mes,
            &prod_p.prod_pedidos[i].f_devolucion.anio);
        
        i++;
    }

    printf("productos pedidos: %d", n_prod_ped);
    for(i=0;i<n_prod_ped;i++){
        printf("%d-",prod_p.prod_pedidos[i].id_pedido);
        printf("%d-", prod_p.prod_pedidos[i].id_prod);
        printf("%d-",prod_p.prod_pedidos[i].num_unid);
        printf("%d",prod_p.prod_pedidos[i].f_entrega.dia);
        printf("%d",prod_p.prod_pedidos[i].f_entrega.mes);
        printf("%d-",prod_p.prod_pedidos[i].f_entrega.anio);
        printf("%d-",prod_p.prod_pedidos[i].importe);
        printf("%s-",prod_p.prod_pedidos[i].estado);
        printf("%d-",prod_p.prod_pedidos[i].id_transp);
        printf("%s-",prod_p.prod_pedidos[i].id_locker);
        printf("%s-",prod_p.prod_pedidos[i].cod_locker);
        printf("%d-",prod_p.prod_pedidos[i].f_devolucion.dia);
        printf("%d-",prod_p.prod_pedidos[i].f_devolucion.mes);
        printf("%d-",prod_p.prod_pedidos[i].f_devolucion.anio);
    }

    return prod_p;
}

//Cabecera: guardar_producto_pedido()
//Precondicion:
//Postcondicion: rellena la estructura con un nuevo producto pedido y lo escribe en el fichero
void guarda_producto_pedido(prod_pedidos prod_p){
    FILE*f_prod_pedidos;
    f_prod_pedidos=fopen("../data/ProductosPedidos.txt", "rw+");
    if(f_prod_pedidos==NULL){
        printf("ERROR");
    }
}

//Cabecera: devoluciones cargar_devoluciones()
//Precondicion:
//Postcondicion: carga en la estructura devoluciones los datos que hay en el fichero Devoluciones.txt

devoluciones cargar_devoluciones(){
    int n_dev=0, i, campo_devoluciones;
    char cad_aux[150];

    FILE * f_dev;
    f_dev=fopen("../data/Devoluciones.txt", "wr+"); //Abrir fichero
    if(f_dev==NULL){
        printf("ERROR");
    }

    while(fgets(cad_aux, sizeof(cad_aux), f_dev)){
        n_dev++; //numero de devoluciones que hay, es decir, las líneas del fichero
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