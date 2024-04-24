#include<stdio.h>
#include"pedidos.h"
#include"useradmin.h"
#include"Descuentos.h"



pedidos cargar_pedidos(){
    
    int n_pedidos=0, i=0, campo_pedidos;
    char default_pedido[]="0-0/0/0-0-default-default-default\0";
    char cad_aux[150]; //cadena auxiliar en la que se guarda cada linea del fichero
    
    FILE * f_ped;
    f_ped=fopen("../data/Pedidos.txt", "a+"); //abre el fichero Pedidos.txt
    if(f_ped==NULL){ //si no existe el fichero o esta vacio lo crea
        printf("ERROR se ha creado fichero");
        Sleep(2000);
    }

    rewind(f_ped);

    if(fgetc(f_ped)==EOF){
        fprintf(f_ped, default_pedido);
    }

    rewind(f_ped);
     
    while(fgets(cad_aux, sizeof(cad_aux), f_ped)){ //lee cada linea del fichero y la almacena en la variable cad_aux, para contar las lineas del fichero
        printf("%s", cad_aux);
        n_pedidos++; //numero de pedidos (numero de lineas del fichero)
    }
    rewind(f_ped);
    

    pedidos p; //p.pedidos es la variable de tipo pedido que esta dentro de la estructura pedidos. 

    p.lon=n_pedidos;
    p.pedidos=malloc(n_pedidos*sizeof(pedido)); //definimos un vector dinamico de tipo pedido, en cada posicion estara la estructura rellenada con los datos dela primera linea
    
    while(fgets(cad_aux, sizeof(cad_aux), f_ped) && i<n_pedidos){
        campo_pedidos=sscanf(cad_aux, "%d-%d/%d/%d-%d-%11[^-]-%11[^-]-%11[^\n]",
            &p.pedidos[i].id_pedido,
            &p.pedidos[i].f_pedido.dia,
            &p.pedidos[i].f_pedido.mes,
            &p.pedidos[i].f_pedido.anio,
            &p.pedidos[i].id_cliente,
            p.pedidos[i].lugar,
            p.pedidos[i].id_locker,
            p.pedidos[i].id_cod);

        if(campo_pedidos!=8){
            printf("error en estructura pedidos, i=%d", i);
        }

        i++;
        
    }
    printf("se ha cargado el fichero Pedidos.txt correctamente\n");
    printf("pedidos: %d\n", n_pedidos);
    
    return p;
}


pedidos crear_pedido( pedidos p, int id_cliente){
    //Cargar estructuras necesarias de otros modulos
    clients c = cargar_clientes();
    prod_pedidos Prod_P = cargar_prod_pedidos();
    produ_vect productos = cargar_productos();
    DescClientes desc_clients = Cargar_DescuentosClientes(); //cargar la estructura descuentos clientes para comprobar que el codigo introducido por el cliente es correcto

    int i=0, lugar, n_products=1, n_uds=0, compra=1, pos_product, j=0, id_producto, id;//n_products es la longitud de los vectores dinamicos

    //VARIABLES DE IMPORTE
    int importe_total=0, //importe total del pedido realizado por el cliente
        importe_uds=0, //importe por las unidades compradas de cada producto
        cantidad=0, //cantidad de unidades que puede comprar hasta que su credito sea menor que el importe
        importe_cant=0; //importe para comparar el credito del cliente con las cantidades que puede comprar

    char cod_cheque[10], //codigo de cheque que introduce el usuario y validar si es correcto
         nombre[16]; //para mostrar el nombre de los productos despues del que el producto haya terminado del pedido
    char op,cheque; //caracteres para que el usuario introduzca si si o no a una pregunta que realiza el sistema
    

    /***ASIGNACION DE ID, POS Y REASIGNACION DE LA ESTRUCTURA PEDIDOS***/
    int n_pedidos=p.lon+1;
    int nueva_id=n_pedidos-1; //id de un nuevo pedido, será el numero de pedidos que hay en el fichero +1
    int pos=nueva_id; //posicion del nuevo pedido es la id ya que la nueva id sera un nuevo pedido por tanto el numero de pedidos que hay
    p.pedidos=realloc(p.pedidos, (pos+1)*sizeof(pedido)); //reasignamos memoria dinámica, el tamaño sera la pos mas uno ya que la estructura tendra una posicion
    printf("\n%d(p.lon) %d, %d\n",p.lon, pos, nueva_id);
    
    if (pos == 0 || nueva_id == 0){ //No sustituir el pedido por defecto
        pos = 1;
        nueva_id = 1;
    }
    printf("\n%d, %d\n", pos, nueva_id);
    int *v_prod, //vector auxiliar para almacenar las id de los productos que ha seleccionado el usuario en un mismo pedido
        *v_uds; //vector auxiliar para almacenar las unidades de los productos que ha seleccionado el usuario
        //cada posicion es un producto, en un vector se almacena la id y en el otro vector las unidades de ese producto
    
    v_prod=(int*)malloc(n_products*sizeof(int)); //definimos de forma dinámica los vectores que hemos creado anteriormente
    v_uds=(int*)malloc(n_products*sizeof(int));

    int credito_c=c.clients[id_cliente].Cartera;


    //SELECCIONAR PRODUCTO
    
    do{ //bucle para seleccionar todos los productos y rellenar los vectores dinámicos
        clear();
        printf("---AGREGAR PRODUCTO AL PEDIDO---\n");
        n_uds=0;
        fflush(stdin);
        id_producto=buscar_productos(productos); //la posicion de un producto es la misma que su id

        v_prod=(int*)realloc(v_prod, n_products*sizeof(int));//agrego la id del producto seleccionad al vector productos
        
        
        //SELECCIONAR UNIDADES DE CADA PRODUCTO
        v_uds=(int*)realloc(v_uds, n_products*sizeof(int));
        printf("-- Stock disponible del producto [ %d ] --\n",productos.produ[id_producto].stock);
        printf("Introduce el numero de uds que desea del producto: \n");
        n_uds = input_int();

        //comprobar unidades del producto validas
        printf("Uds seleccionadas: %d\n", n_uds);
        while(n_uds>productos.produ[id_producto].stock || n_uds<1){
            printf("ERROR: ha introducido una opcion válida\n");
            printf("Introduzca una opcion válida\n");
            n_uds = input_int();
        }
        

        importe_uds=productos.produ[id_producto].importe*n_uds; //importe de cada producto
        printf("-- Credito que dispondria [ %d ] --\n",credito_c);
        printf("El importe del producto: %d\n", importe_uds);
        
        //Comprobamos importe del pedido es menor que credito del cliente
        
        if(importe_uds>=credito_c){ 
            printf("ERROR: el importe es superior al credito que tiene el cliente\n");
            printf("OPCIONES DISPONIBLES: \n"); //opciones que tiene el usuario cuando el importe supera su credito
            printf("1. Modificar unidades\n");
            printf("2. Cancelar compra\n");
            if(importe_uds==credito_c){ //opcion para cuando el importe es igual que el credito del cliente
                printf("3. Terminar compra\n");
            }
            int resp = input_int();

            switch(resp){
                case 1:
                    //numero de unidades que puede comprar el cliente hasta superar su credito
                    cantidad=0;
                    importe_cant=0;
                    while(importe_cant<credito_c-importe_cant){ //calcular la cantidad que puede comprar el cliente hasta que el importe sea superior al credito
                        importe_cant=cantidad*productos.produ[id_producto].importe;
                        cantidad++;
                    }
                    cantidad=cantidad-1;
                    if(cantidad==0){ //si la cantidad es 0 el cliente no puede comprar ese producto
                        printf("No puede comprar ninguna unidad de este producto\n");
                    }
                    else{
                        printf("Puede comprar %d unidades del producto\n", cantidad);
                        printf("Desea añadir el producto [s/n]: \n");
                        char aux=confirmacion();
                        if(aux=='s' || aux=='S'){
                            printf("cuantas unidades desea introducir: \n"); //preguntar al usuario cuantas unidades quiere del producto 
                            n_uds = input_int();
                            
                        }
                        else{
                            n_uds=0;
                        }
                    }
                break;

                case 2:
                    return p;

                case 3:
                    compra=0;
                    printf("Presione [enter] para continuar con el pedido...\n");
                    break;
                
            }

        }
        else{
            credito_c=credito_c-importe_uds; //le resto al credito del cliente el importe
        }
        
        v_prod[n_products-1]=id_producto; //guardar en el vector dinamico el id del producto que ha seleccionado el cliente
        v_uds[n_products-1]=n_uds; //guardar numero de unidades de ese producto que ha seleccionado el usuario
        importe_total=importe_total + (productos.produ[id_producto].importe * n_uds); //cada vez que se incluye un producto en la lista se añade al importe total del pedido
        
        //Preguntar al cliente si desea añadir mas productos a un pedido
        
        fflush(stdin);
        printf("Desea agregar mas productos al pedido [s/n]: \n");
        op=confirmacion();
        if(op=='s' || op == 'S'){
            n_products++;
            id_producto++;
        }
        else{
            compra=0; //para salir del bucle
            printf("\nno desea agregar mas productos al pedido\n");
            printf("\ncontinuamos con el pedido\n");
        }

    }while(compra != 0);
    
    //ALMACENAR EN LA ESTRUCTURA PEDIDO LOS DATOS DEL PEDIDO
    p.pedidos[pos].id_pedido=nueva_id;

    
    
    p.pedidos[pos].id_cliente=id_cliente;

    p.pedidos[pos].f_pedido.dia=dia_sist();
    p.pedidos[pos].f_pedido.mes=mes_sist();
    p.pedidos[pos].f_pedido.anio=anio_sist();

    getchar();
    /***LUGAR DE ENTREGA Y CHEQUES***/
    clear();
    printf("Selecciona un lugar de entrega: \n");
    printf("1. DOMICILIO\n");
    printf("2. LOCKER\n");
    printf("su opcion : ");
    lugar=input_int();
    switch(lugar){
        case 1:
            strcpy(p.pedidos[pos].lugar, "Domicilio");
            strcpy(p.pedidos[pos].id_locker, "noLocker");
            break;
        case 2:
            strcpy(p.pedidos[pos].lugar, "Locker");
            strcpy(p.pedidos[pos].id_locker, "pendLock"); //esta pendiente de asignación de locker
            break;
        default:
            break;
    }
    printf("Ha elegido como destino del pedido %s\n",p.pedidos[pos].lugar );
    printf("Presione [enter] para continuar con el pedido...");
    getchar();

    /*** CHEQUE Y CODIGO DE DESCUENTO ***/
    int l,k, 
        conf=0,//variable para almacenar si el cliente tiene asociados codigos de descuento
        cheque_ok = 0,
        imp_desc; //Importe descontado por codigo de descuento
    char cod_desc[11];

    clear();
    printf("Desea utilizar un cheque de descuento [s/n]: \n");
    cheque=confirmacion();

    if(cheque=='s' || cheque == 'S'){
        Consultar_desc_cliente(id_cliente, 1);
        do{
            printf("Introduce el codigo del descuento que deseas utilizar: ");
            fflush(stdin);
            fgets(cod_desc, 11, stdin);
            terminador_cad(cod_desc);

            conf = comprobar_descuento(cod_desc, id_cliente);
            if(conf==0){
                printf("El codigo de descuento introducido es valido.\n");
                strcpy(p.pedidos[pos].id_cod, cod_desc);
                
                imp_desc = importe_descuento(cod_desc);
                printf("Se va descontar %d euros del pedido.", imp_desc);
                importe_total -= imp_desc;
                Sleep(3000);
                
                cheque_ok = 1;
            }
            else{
                printf("El codigo de descuento introducido no es valido.\n");
                printf("Desea introducir otro codigo de descuento [s/n]: ");
                cheque=confirmacion();
                if(cheque == 'n' || cheque == 'N'){
                    strcpy(cod_desc, "nocod\0");
                    strcpy(p.pedidos[pos].id_cod, cod_desc); 
                    cheque_ok = 1;
                }   
            }
        }while(cheque_ok != 1);
       
    }
    else{
        strcpy(cod_desc, "nocod\0");
        strcpy(p.pedidos[pos].id_cod, cod_desc);  
    }
    printf("Presione [enter] para continuar con el pedido...");
    getchar();
    
    //RESUMEN DE LOS PRODUCTOS QUE HA PEDIDO Y EL IMPORTE TOTAL
    
    clear();
    printf("\n---RESUMEN DEL PEDIDO---\n");
    for(j=0;j<n_products;j++){ 
        id=v_prod[j];
        strcpy(nombre, productos.produ[id].nombre);
        printf(" <%d> Nombre del producto: %s\n", j+1, nombre);
        printf(" <%d> Numero de unidades del producto: %d\n", j+1, v_uds[j]);
    }
    printf(" TOTAL DE PRODUCTOS: %d\n",n_products);
    printf(" IMPORTE TOTAL: %d euros\n", importe_total);
    
    printf("Desea confirmar la compra? [s/n]: ");
    op = confirmacion();
    if (op == 'n' || op == 'N'){
        p = cargar_pedidos(); //Rechazo los cambios del nuevo pedido cargando la estructura previa 
        guardar_pedido(p);
        return p;
    }

    //CAMBIOS NECESARIOS SI REALIZA PEDIDO
        

    if(strcmp(cod_desc, "nocod\0") != 0)
        marcar_aplicado(id_cliente, cod_desc);

    p.lon=p.lon+1; //actualiza el numero de pedidos que hay 
    
    printf("Se acaba de descontar %d euros de su cartera", importe_total);
    c.clients[id_cliente].Cartera -= importe_total;

    guardar_clientes(c);

    //CREAR PRODUCTO PEDIDO Y GUARDARLO EN LA ESTRUCTURA
   int id_pro, n_unidades;
    for(j=0;j<n_products;j++){
        prod_pedidos Prod_P=cargar_prod_pedidos();
        id_pro=v_prod[j];
        n_unidades=v_uds[j];
        printf("%d, %d \n", id_pro, n_unidades);

        crear_producto_pedido(p, id_pro, nueva_id, Prod_P, n_unidades);

    }
    printf("Pedido completo realizado correctamente...");
    getchar();
    guardar_pedido(p);
    return p;
}
int comprobar_descuento(char cod_descuento[], int id_cliente){
    int i, j,
        comp; 

    
    DescClientes des_c = Cargar_DescuentosClientes();
    Descuentos des=Cargar_Descuentos();
    produ_vect pro=cargar_productos();

    fecha f_sist;
    fecha f_cad;

    //asignamos valores a las estructuras fechas
    f_sist.dia=dia_sist();
    f_sist.mes=mes_sist();
    f_sist.anio=anio_sist();

    for(i=0;i<des_c.tam;i++){
        if(strcmp(cod_descuento, des_c.DescCliente[i].Id_cod)==0){
            f_cad.dia=des_c.DescCliente[i].dia_cad;
            f_cad.mes=des_c.DescCliente[i].mes_cad;
            f_cad.anio=des_c.DescCliente[i].anio_cad;

        }
    }
    
    comp=comprobar_fecha(f_sist, f_cad);
    
    if(comp==0){
        printf("El codigo esta caducado\n");
        return 1;
    }

    //SACAR LA POSICION 
    for(i=0;i<des.tam;i++){
        if(strcmp(cod_descuento, des.Desc[i].Id_cod)==0){//Comprobacion si cod_desc existe

            if(strcmp(des.Desc[i].Estado, "activo")==0){   //Comprobacion si cod_desc esta activo

                for(j=0;j<des_c.tam;j++){
                    if(id_cliente==des_c.DescCliente[j].Id_cliente){    //Comprobacion si cod_desc esta asignado al cliente

                        if(strcmp(cod_descuento, des_c.DescCliente[j].Id_cod)==0){  

                            if(des_c.DescCliente[j].Estado==0){         //Comprobacion si cod_desc no ha sido aplicado antes

                                return 0;
                            }
     
                        }
                    }
                }
            }
        }
        
    }

    return 1;
    
    
}

void guardar_pedido(pedidos p){
    int i;

    FILE *f_ped;
    f_ped=fopen("../data/Pedidos.txt", "w");
    if(f_ped==NULL){
        printf("ERROR");
    }

    //Escribir en el fichero los pedidos que contiene la estructura pedidos 
    for(i=0;i<p.lon;i++){
        fprintf(f_ped,"%07d-%02d/%02d/%04d-%07d-%s-%s-%s\n", 
            p.pedidos[i].id_pedido,
            p.pedidos[i].f_pedido.dia,
            p.pedidos[i].f_pedido.mes,
            p.pedidos[i].f_pedido.anio,
            p.pedidos[i].id_cliente,
            p.pedidos[i].lugar,
            p.pedidos[i].id_locker,
            p.pedidos[i].id_cod);
    }
    
    printf("\nSe han guardado los pedidos correctamente\n");
    Sleep(2000);
    fclose(f_ped);
}


prod_pedidos cargar_prod_pedidos(){
    int n_prod_ped=0, i=0, campo_prod_ped;
    char cad_aux[200];
    char default_prod_ped[]="0-0-0-0/0/0-0-default-0-default-default-0/0/0\n";
    
    FILE * f_prod_ped;
    f_prod_ped=fopen("../data/ProductosPedidos.txt", "a+");
    if(f_prod_ped==NULL){
       printf("\nERROR se ha creado el fichero\n");
       Sleep(2000);
    }

    rewind(f_prod_ped);

    if(fgetc(f_prod_ped) == EOF){
        fprintf(f_prod_ped, default_prod_ped);
    }

    rewind(f_prod_ped);

    while(fgets(cad_aux, sizeof(cad_aux), f_prod_ped)){
        printf("%s", cad_aux);
        n_prod_ped++; //numero de productos pedidos
    }
    rewind(f_prod_ped);

    prod_pedidos prod_p;

    prod_p.lon=n_prod_ped;

    prod_p.prod_pedidos=malloc(n_prod_ped*sizeof(prod_pedido));
    
    while(fgets(cad_aux, sizeof(cad_aux), f_prod_ped) && i<n_prod_ped){
        campo_prod_ped=sscanf(cad_aux, "%d-%d-%d-%d/%d/%d-%d-%16[^-]-%d-%11[^-]-%11[^-]-%d/%d/%d",
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

        if(campo_prod_ped != 14){
            printf("error en la estructura productos pedidos, i=%d\n", i);
        }

        i++;
    }
    printf("\nse ha cargado el fichero ProductosPedidos.txt correctamente\n");

    
    return prod_p;
}


void guardar_productos_pedidos(prod_pedidos prod_p){
    int i;

    FILE*f_prod_ped;
    f_prod_ped=fopen("../data/ProductosPedidos.txt", "w");
    if(f_prod_ped==NULL){
        printf("ERROR");
    }

    for(i=0;i<prod_p.lon;i++){
        fprintf(f_prod_ped, "%d-%d-%d-%d/%d/%d-%d-%s-%d-%s-%s-%d/%d/%d\n",
            prod_p.prod_pedidos[i].id_pedido,
            prod_p.prod_pedidos[i].id_prod,
            prod_p.prod_pedidos[i].num_unid,
            prod_p.prod_pedidos[i].f_entrega.dia,
            prod_p.prod_pedidos[i].f_entrega.mes,
            prod_p.prod_pedidos[i].f_entrega.anio,
            prod_p.prod_pedidos[i].importe,
            prod_p.prod_pedidos[i].estado,
            prod_p.prod_pedidos[i].id_transp,
            prod_p.prod_pedidos[i].id_locker,
            prod_p.prod_pedidos[i].cod_locker,
            prod_p.prod_pedidos[i].f_devolucion.dia,
            prod_p.prod_pedidos[i].f_devolucion.mes,
            prod_p.prod_pedidos[i].f_devolucion.anio);
    }
    printf("\nSe han guardado los productos pedidos correctamente\n");
    Sleep(2000);

    fclose(f_prod_ped);
}

//Cabecera
//Precondición
//Postcondicion
void crear_producto_pedido(pedidos p, int product, int id_pedido, prod_pedidos prod_p, int uds){
    int pos, //variable para la posicion en la estructura productos pedidos
        i; //variable para recorrer la estructura

    produ_vect productos=cargar_productos(); //cargar la estructura del modulo productos


    pos=prod_p.lon;
    prod_p.prod_pedidos=realloc(prod_p.prod_pedidos, (pos+1)*sizeof(prod_pedido)); //reasignamos memoria dinamica al vector de la estructura productos pedidos
    
    //ALMACENAR DATOS EN LA ESTRUCTURA
    prod_p.prod_pedidos[pos].id_pedido=id_pedido;
    prod_p.prod_pedidos[pos].id_prod=product;
    prod_p.prod_pedidos[pos].num_unid=uds;

    //fecha de entrega
    int d_entrega=productos.produ[product].entrega;
    prod_p.prod_pedidos[pos].f_entrega=fecha_entrega(p.pedidos[id_pedido].f_pedido, d_entrega);

    prod_p.prod_pedidos[pos].importe=productos.produ[product].importe;

    strcpy(prod_p.prod_pedidos[pos].estado, "enPreparacion"); //por defecto el estado inicial del producto pedido es en Preparacion

    prod_p.prod_pedidos[pos].id_transp=0; //se le asignara un transportista en el modulo transportistas

    strcpy(prod_p.prod_pedidos[pos].id_locker, p.pedidos[id_pedido].id_locker); //locker asignado es el mismo que se le asigno al pedido
    strcpy(prod_p.prod_pedidos[pos].cod_locker, "pendcod");//codigo pendiente de asignacion

    prod_p.prod_pedidos[pos].f_devolucion.dia=0;
    prod_p.prod_pedidos[pos].f_devolucion.mes=0;
    prod_p.prod_pedidos[pos].f_devolucion.anio=0;

    
    prod_p.lon=prod_p.lon+1;

    printf("\nproductos pedidos: %d\n", prod_p.lon);
    
    guardar_productos_pedidos(prod_p);
    printf("El producto %s se ha pedido correctamente...\n",productos.produ[product].nombre);
    Sleep(2000);
}

void eliminar_pedidos(prod_pedidos prod_p, pedidos p){
    int i;
    char resp;
    int pos_ped=busqueda_pedidos(p);
    prod_pedidos prod_p = cargar_prod_pedidos();
    printf("Estas seguro de elimar el pedido? [s/n]: ");
    resp=confirmacion();
    if(resp =='S' || resp=='s'){
        for(i=pos_ped;i<p.lon-1;i++){
            printf("prueba2\n");
            p.pedidos[i]=p.pedidos[i+1];
            p.pedidos[i].id_pedido = i;

        }
        p.lon--;
        p.pedidos=realloc(p.pedidos, p.lon*sizeof(pedido));
        if(p.pedidos==NULL){
            printf("No se pudo reasignar la estructura pedidos\n");
            getchar();
            exit(EXIT_FAILURE);
        }

        guardar_pedido(p);
        printf("se ha eliminado el pedido correctamente\n");

        eliminar_productos_ped(prod_p, pos_ped);
    }
    else{
        printf("se ha cancelado la eliminacion del pedido indicado\n");
    }
}

void eliminar_productos_ped(prod_pedidos prod_p, int pos_ped){
    int i,j=0,
        n_ped=0; //variable que almacena el numero de productos que hay del pedido

    for(i=pos_ped;i<prod_p.lon-1;i++){
        if(prod_p.prod_pedidos[i].id_pedido==pos_ped){
            n_ped++;
        }
    }

    for(i=0;i<prod_p.lon;i++){
        if(prod_p.prod_pedidos[i].id_pedido==pos_ped){
            for(j=i;j<prod_p.lon-1;j++){
                prod_p.prod_pedidos[j]=prod_p.prod_pedidos[j+1];
            }
            prod_p.lon=prod_p.lon -1;
            i=i-1;
        }
    }

    for(i=0;i<prod_p.lon;i++){
        if(prod_p.prod_pedidos[i].id_pedido>pos_ped){
            prod_p.prod_pedidos[i].id_pedido=prod_p.prod_pedidos[i].id_pedido -1;
        }
    }

    //prod_p.lon=prod_p.lon-n_ped;
    prod_p.prod_pedidos=realloc(prod_p.prod_pedidos, prod_p.lon*sizeof(prod_pedido));
    if(prod_p.prod_pedidos==NULL){
        printf("No se pudo reasignar estructuras a productos pedidos\n");
    }

    

    guardar_productos_pedidos(prod_p);
    printf("se han eliminado los productos del pedido correctamente\n");

}
      


devoluciones cargar_devoluciones(){
    int n_dev=0, i=0, campo_devoluciones;
    char cad_aux[150];
    char default_dev[]="0-0-0/0/0-default-default-0/0/0-0/0/0\n";

    FILE * f_dev;
    f_dev=fopen("../data/Devoluciones.txt", "a+"); //Abrir fichero
    if(f_dev==NULL){
        printf("ERROR se ha creado el fichero");
        Sleep(2000);
    }

    rewind(f_dev);

    if(fgetc(f_dev) == EOF){
        fprintf(f_dev, default_dev);
    }
    
    rewind(f_dev);

    while(fgets(cad_aux, sizeof(cad_aux), f_dev)){
        n_dev++; //numero de devoluciones que hay, es decir, las líneas del fichero
    }
    rewind(f_dev);

    devoluciones dev;
    dev.devoluciones=malloc(1*sizeof(devolucion));
    dev.lon=n_dev;
    dev.devoluciones=realloc(dev.devoluciones,n_dev * sizeof(devolucion));

    while(fgets(cad_aux, sizeof(cad_aux), f_dev) && i<n_dev){
        campo_devoluciones=sscanf(cad_aux, "%d-%d-%d/%d/%d-%51[^-]-%11[^-]-%d/%d/%d-%d/%d/%d",
        &dev.devoluciones[i].id_pedido,
        &dev.devoluciones[i].id_prod,
        &dev.devoluciones[i].f_devol.dia,
        &dev.devoluciones[i].f_devol.mes,
        &dev.devoluciones[i].f_devol.anio,
        dev.devoluciones[i].motivo,
        dev.devoluciones[i].estado,
        &dev.devoluciones[i].f_aceptacion.dia,
        &dev.devoluciones[i].f_aceptacion.mes,
        &dev.devoluciones[i].f_aceptacion.anio,
        &dev.devoluciones[i].f_caducidad.dia,
        &dev.devoluciones[i].f_caducidad.mes,
        &dev.devoluciones[i].f_caducidad.anio);

        if(campo_devoluciones!=13){
            printf("error en estructura devoluciones, i=%d", i);
            getchar();
            exit(EXIT_FAILURE);
        }
    
    i++;
    }
    return dev;
}

void guardar_devoluciones(devoluciones d){
    int i;

    FILE*f_dev;
    f_dev=fopen("../data/Devoluciones.txt", "w");
    if(f_dev==NULL){
        printf("ERROR");
    }
    printf("%d",d.lon);
    getchar();

    for(i=0;i<d.lon;i++){
        printf("%s", d.devoluciones[i].motivo);
    }
    getchar();

    for(i=0;i<d.lon;i++){
        fprintf(f_dev,"%07d-%d-%d/%d/%d-%s-%s-%d/%d/%d-%d/%d/%d\n",
        d.devoluciones[i].id_pedido,
        d.devoluciones[i].id_prod,
        d.devoluciones[i].f_devol.dia,
        d.devoluciones[i].f_devol.mes,
        d.devoluciones[i].f_devol.anio,
        d.devoluciones[i].motivo,
        d.devoluciones[i].estado,
        d.devoluciones[i].f_aceptacion.dia,
        d.devoluciones[i].f_aceptacion.mes,
        d.devoluciones[i].f_aceptacion.anio,
        d.devoluciones[i].f_caducidad.dia,
        d.devoluciones[i].f_caducidad.mes,
        d.devoluciones[i].f_caducidad.anio);
    }
}

devoluciones crear_devolucion(devoluciones d, int id_pedido, int id_producto){
    int i, pos, id_ped, producto;
    char motivo[50]; //motivo que escribe el cliente para devolver el producto
    pos=d.lon;
    d.devoluciones=realloc(d.devoluciones, (pos+1)*sizeof(devolucion));

    d.devoluciones[pos].id_pedido=id_pedido;
    d.devoluciones[pos].id_prod=id_producto;
    
    d.devoluciones[pos].f_devol.dia=dia_sist(); //fecha en la que se realiza la solicitud de la devolucion, es la fecha del dia que se rellena la devolucion
    d.devoluciones[pos].f_devol.mes=mes_sist();
    d.devoluciones[pos].f_devol.anio=anio_sist();

    printf("Introduce el motivo de la devolucion: "); //usuario introduce el motivo de la devolucion
    fflush(stdin);
    fgets(motivo, 50, stdin);
    terminador_cad(motivo);
    strcpy(d.devoluciones[pos].motivo, motivo);

    strcpy(d.devoluciones[pos].estado, "pendiente");//estado original de la devolucion

    d.devoluciones[pos].f_aceptacion.dia=0;
    d.devoluciones[pos].f_aceptacion.mes=0;
    d.devoluciones[pos].f_aceptacion.anio=0;

    d.devoluciones[pos].f_caducidad.dia=0;
    d.devoluciones[pos].f_caducidad.mes=0;
    d.devoluciones[pos].f_caducidad.anio=0;

    d.lon=d.lon+1;
    printf("Se ha creado la devolucion correctamente\n");

    guardar_devoluciones(d);
    printf("Se han guardado los datos correctamente\n");

    return d;

}

fecha fecha_entrega(fecha f, int dia_ent){
    int d= f.dia + dia_ent, m= f.mes, y= f.anio;    //AUXILIARES PARA MANEJAR LA FECHA DE ENTREGA -> d(DIA)/m(mes)/y(anio)
    int ndias_mes[]={31,28,31,30,31,30,31,20,31,31,30,31};  //Vector para identificar los dias que tiene un mes

    if((y %4 == 0 && y %100 != 0) || (y % 400 == 0)) //COMPROBACION ANIO BISIESTO
        ndias_mes[1] = 29;
    
    if(d > ndias_mes[m-1]){
        d = d - ndias_mes[m-1];
        m++;
    }
    if(m > 12){
        m = m - 12;
        y++;
    }
    
    f.dia = d;
    f.mes = m;
    f.anio = y;

    return f;
}

void listapedidos_cliente(prod_pedidos prods_p,pedidos p, int id_cliente){
    int i,k,
        id_ped,
        id_produ,
        n_peds = 0;
    char nom_produ[16];
    produ_vect prods = cargar_productos();

    clear();
    printf("+---------------+\n");
    printf("|  TUS PEDIDOS  |\n");
    printf("+---------------+-----------------------------------------------------------------------+\n");

    for(i=1;i< p.lon; i++){
        if(id_cliente == p.pedidos[i].id_cliente){  //Mostrar pedidos solo del cliente
            printf("| <%d> FECHA: %d / %d / %d LUGAR:%-9s                                              |\n", i,
                                                                            p.pedidos[i].f_pedido.dia,
                                                                            p.pedidos[i].f_pedido.mes,
                                                                            p.pedidos[i].f_pedido.anio, 
                                                                            p.pedidos[i].lugar);
            id_ped = p.pedidos[i].id_pedido;        //Guardo temporalmente la id pedido para manejar mas facil
            n_peds++;
            for(k=1;k<prods_p.lon;k++){             //Mostrar productos de un pedido
                if(id_ped == prods_p.prod_pedidos[k].id_pedido){
                    id_produ = prods_p.prod_pedidos[k].id_prod;         //Guardo temporalmente la id producto para manejar mas facil
                    strcpy(nom_produ,prods.produ[id_produ].nombre);

                    printf("|  +-> ARTICULO: %-15s UDS: %-3d IMPORTE(euros): %-5d ESTADO :%-15s |\n",nom_produ,
                                                    prods_p.prod_pedidos[id_produ].num_unid,
                                                    prods_p.prod_pedidos[id_produ].importe,
                                                    prods_p.prod_pedidos[id_produ].estado);
                }       
            }
            printf("+---------------------------------------------------------------------------------------+\n");
        }
    }
    if(n_peds == 0){
        printf("| NO SE ENCONTRARON PEDIDOS                                                             |\n");
        printf("+---------------------------------------------------------------------------------------+\n");
    }
    printf("Pulse [enter] para salir");
    getchar();
}

devoluciones nueva_devolucion_prod(int id_cliente, devoluciones d){
    int i,j,k,
        id_prod,     //variable para almacenar los id de los productos que han sido entregados al cliente
        n_coinc = 0, //variable para almacenar el numero de coincidencias que hay
        op, //variable que almacena el producto que quiere devolver el cliente
        pos_prod,
        pos_ped;

    pedidos p = cargar_pedidos();
    prod_pedidos prod_p = cargar_prod_pedidos();
    int *v_prod, //vector auxiliar que almacena los productos que han sido entregados al cliente
        *v_ped; //vector auxiliar que almacena los pedidos a los que pertenecen los productos entregados del cliente
    
    v_prod=(int*)malloc(1*sizeof(int));
    v_ped=(int*)malloc(1*sizeof(int));
    
    produ_vect Prod=cargar_productos();
    for(i=1;i<p.lon;i++){
        //comprobar que el cliente tiene pedidos
        if(id_cliente==p.pedidos[i].id_cliente){ 
            int id_p=p.pedidos[i].id_pedido; //variable para almacenar las id de los pedido de ese cliente
            for(j=1;j<prod_p.lon;j++){
                //saber cuales son los productos que pertenecen a los pedidos de ese cliente
                if(id_p==prod_p.prod_pedidos[j].id_pedido){
                    //printf("los productos del cliente son: %d\n", prod_p.prod_pedidos[j].id_prod);
                    //comprobamos que los productos han sido entregados al cliente
                    if(strcmp(prod_p.prod_pedidos[j].estado, "entregado")==0){
                        //printf("pedido: %d\n", id_p);
                        //printf("el producto %d de ese pedido ha sido entregado al cliente\n", prod_p.prod_pedidos[j].id_prod);
                        id_prod=prod_p.prod_pedidos[j].id_prod; //asignamos la id de los productos del pedido a una variable auxiliar
                        for(k=0;k<Prod.num_prod;k++){
                            /*printf("numero de productos en el fichero: %d\n", Prod.num_prod);
                            printf("id productos del fichero: %d\n", Prod.produ[k].id_prod);
                            printf("id del producto del cliente: %d\n", id_prod);*/
                            //obtenemos los nombres de los productos cuya id es la que hemos almacenado anteriormente
                            if(id_prod==Prod.produ[k].id_prod){
                                printf("<%d> nombre:%s fecha:%d/%d/%d unidades:%d\n",n_coinc+1,
                                                                                    Prod.produ[k].nombre,
                                                                                    p.pedidos[i].f_pedido.dia, 
                                                                                    p.pedidos[i].f_pedido.mes,
                                                                                    p.pedidos[i].f_pedido.anio,
                                                                                    prod_p.prod_pedidos[j].num_unid);
                                n_coinc++;
                                v_prod=(int*)realloc(v_prod, n_coinc*sizeof(int));
                                v_prod[n_coinc-1]=id_prod;
                                v_ped=(int*)realloc(v_ped, n_coinc*sizeof(int));
                                v_ped[n_coinc-1]=id_p;
                            }
                        }

                    }
                }
            }
            
        }
        else{
            printf("ERROR: no hay pedidos de el cliente");
        }
    }

    printf("\nIntroduzca el numero <n> que desea seleccionar: ");
    op=input_int();
    fflush(stdin);
    pos_prod=v_prod[op-1];
    pos_ped=v_ped[op-1];
    

    
    d= crear_devolucion(d, pos_ped, pos_prod);
    return d;
    
}

void menu_listadoped_estado(){
    prod_pedidos prod_ped = cargar_prod_pedidos();

    int opt;

    
    do{
        clear();
        printf("+----------------------+\n");
        printf("| LISTADO PEDIDOS POR: |\n");
        printf("+----------------------+\n");
        printf("| <1> EN PREPARACION   |\n");
        printf("| <2> ENVIADO          |\n");
        printf("| <3> EN REPARTO       |\n");
        printf("| <4> EN LOCKER        |\n");
        printf("| <5> ENTREGADO        |\n");
        printf("| <6> DEVUELTO         |\n");
        printf("| <7> TRANSPORTISTA    |\n");
        printf("| <0> VOLVER           |\n");
        printf("+----------------------+\n");

        opt = input_int();

        switch (opt){
            case 1:
                listadoped_estado(prod_ped, "enPreparacion\0");
                break;
            case 2:
                listadoped_estado(prod_ped, "enviado\0");
                break;
            case 3:
                listadoped_estado(prod_ped, "enReparto\0");
                break;
            case 4:
                listadoped_estado(prod_ped, "enLocker\0");
                break;
            case 5:
                listadoped_estado(prod_ped, "entregado\0");
                break;
            case 6:
                listadoped_estado(prod_ped, "devuelto\0");
                break;
            case 7:
                listadoped_estado(prod_ped, "transportista\0");
                break;
            case 0:
                break;
            default:
                break;
            }

    } while (opt != 0);
    
}

void listadoped_estado(prod_pedidos prod_p, char estado[]){
    produ_vect prods = cargar_productos();
    pedidos P = cargar_pedidos();
    clients C = cargar_clientes();
    int i,j, npeds=0,
        id_cliente,
        id_prod,
        id_pedido;

    clear();
    printf("+------------------+\n");
    printf("| LISTA DE PEDIDOS |\n");
    printf("+------------------+---+----------------------------------------------------+----------+\n");
    printf("| Nombre del cliente   | Producto                                           | Cantidad |\n");
    printf("+----------------------+----------------------------------------------------+----------+\n");
    for(i=1; i< prod_p.lon;i++){
        if(strcmp(estado, prod_p.prod_pedidos[i].estado) == 0){
            id_pedido = prod_p.prod_pedidos[i].id_pedido;

            for(j=1;j<P.lon;j++){
                if(id_pedido == P.pedidos[j].id_pedido)
                    id_cliente = P.pedidos[j].id_cliente;
            }
            
            id_prod = prod_p.prod_pedidos[i].id_prod;

            printf("| %-20s | %-50s | %-8d |\n", 
                    C.clients[id_cliente].Nom_cliente,
                    prods.produ[id_prod].descrip,
                    prod_p.prod_pedidos[i].num_unid);
            npeds++;
        }
        
    }
    if(npeds == 0)
        printf("|                          NO EXISTEN PEDIDOS CON ESTE ESTADO!                         |\n");

    printf("+----------------------+----------------------------------------------------+----------+\n");
    printf("Pulse [enter] para volver...");
    getchar();
}


void listar_devoluciones( devoluciones d){
    int i, j,l,k,
        id_ped,
        id_prod,
        pos;
    char nom_cliente[21];
    char nom_prod[16];
    pedidos p = cargar_pedidos();
    prod_pedidos prod_p = cargar_prod_pedidos();
    printf("+--------------------------------------------------------------------------------------+\n");
    printf("| LISTA DE DEVOLUCIONES                                                                |\n");
    printf("+--------------------------------------------------------------------------------------+\n");
    printf("| <n> nombre cliente - nombre_producto - estado - fecha aceptacion - fehca caducidad   |\n");
    printf("+--------------------------------------------------------------------------------------+\n");
    produ_vect prod = cargar_productos();
    clients c = cargar_clientes();

    
    for(i=1;i<d.lon;i++){
       
        //obtener nombre del cliente
        id_ped=d.devoluciones[i].id_pedido;
       
        for(j=1;j<p.lon;j++){
           
            if(id_ped==p.pedidos[j].id_pedido){
                for(k=1;k<c.n_clients;k++){
                    if(p.pedidos[j].id_cliente==c.clients[k].Id_cliente){
                        
                        strcpy(nom_cliente, c.clients[k].Nom_cliente); //guardo el nombre del cliente que corresponde a esa devolucion
                        
                    }
                    
                }
                
            }
            
        }
        

        //obtener nombre del producto
        id_prod=d.devoluciones[i].id_prod;
        for(l=0;l<prod.num_prod;l++){
            if(id_prod==prod.produ[l].id_prod){
                strcpy(nom_prod, prod.produ[l].nombre); //guardo el nombre del producto que corresponde a esa devolucion
            }
        }

        printf("| <%d> %s - %s - %s - %d/%d/%d - %d/%d/%d\n", i,
                                                            nom_cliente,
                                                            nom_prod,
                                                            d.devoluciones[i].estado,
                                                            d.devoluciones[i].f_aceptacion.dia,
                                                            d.devoluciones[i].f_aceptacion.mes,
                                                            d.devoluciones[i].f_aceptacion.anio,
                                                            d.devoluciones[i].f_caducidad.dia,
                                                            d.devoluciones[i].f_caducidad.mes,
                                                            d.devoluciones[i].f_caducidad.anio);

    }
    


}

int buscar_devolucion(devoluciones d){
    int pos;
    listar_devoluciones(d);
    do{
        printf("introduce el numero n de la devolucion que desea modificar\n");
        pos=input_int();
        return pos;
    }while(pos<d.lon && pos>0);
    

}

void eliminar_devolucion(devoluciones d){
    int i; 
    char resp;
    int pos = buscar_devolucion(d);
    printf("Estas seguro de eliminar la devolucion? [s/n]: ");
    resp=confirmacion();
    if(resp=='s'||resp=='S'){
        for(i=pos;i<d.lon;i++){
            d.devoluciones[i]=d.devoluciones[i+1];
        }
        d.lon--;
        d.devoluciones=realloc(d.devoluciones, d.lon*sizeof(devolucion));
        if(d.devoluciones== NULL){
            printf("no se pudo reasignar la estructura pedidos\n");
            getchar();
            exit(EXIT_FAILURE);
        }
        guardar_devoluciones(d);
        printf("se ha eliminado la devolucion correctamente");
    }
}


devoluciones modificar_devolucion(devoluciones d){
    int i, resp, op;
    int pos=buscar_devolucion(d);
    
    char estado[11];

    printf("+----QUE DESEA MODIFICAR----+\n");
    printf("| 1) ESTADO                 |\n");
    printf("| 2) FECHA CADUCIDAD        |\n");
    printf("+---------------------------+\n");

    printf("introduce su opcion: ");
    scanf("%d", &resp);

    switch(resp){
        case 1: 
            printf("--ESTADOS POSIBLES--\n");
            printf("1. PENDIENTE\n");
            printf("2. ACEPTADO\n");
            printf("3. ENVIADO\n");
            printf("4. RECIBIDO");

            printf("introduce una opcion: ");
            op=input_int();
            switch(op){
                case 1: 
                    strcpy(d.devoluciones[pos].estado, "pendiente");
                    break;
                case 2:
                    strcpy(d.devoluciones[pos].estado, "aceptado");
                    break;
                case 3:
                    strcpy(d.devoluciones[pos].estado, "enviado");
                    break;
                case 4:
                    strcpy(d.devoluciones[pos].estado, "recibido");
                    break;
                default:
                    printf("opcion incorrecta\n");
            }

            break;
        case 2:
            d.devoluciones[pos].f_caducidad=crear_fechacad(d.devoluciones[pos].f_aceptacion);
            break;
        default:
            printf("opcion incorrecta\n");

    }

    return d;
}

void listar_dev_cliente(int id_cliente, devoluciones d){
    int i,j,k,
        id_ped,
        id_prod;
    char nom_prod[16];
    produ_vect prod = cargar_productos();
    prod_pedidos prod_p = cargar_prod_pedidos();
    pedidos p = cargar_pedidos();

    printf("+--------------------------------------------------------------------------------------+\n");
    printf("| LISTA DE DEVOLUCIONES                                                                |\n");
    printf("+--------------------------------------------------------------------------------------+\n");
    printf("| <n> nombre_producto - estado - fecha aceptacion - fehca caducidad   |\n");
    printf("+--------------------------------------------------------------------------------------+\n");
    
    for(i=1;i<d.lon;i++){
        for(j=1;j<p.lon;j++){
            //obtengo la id del pedido a la que pertenece el cliente
            if(id_cliente==p.pedidos[j].id_cliente && p.pedidos[j].id_pedido==d.devoluciones[i].id_pedido){
                printf("id cliente del pedido: %d\n", p.pedidos[j].id_cliente);
                
                id_ped=p.pedidos[j].id_pedido;
                printf("id ped: %d\n", id_ped);

                //obtener el nombre del producto de esa devolucion
                if(d.devoluciones[i].id_pedido==id_ped){
                    id_prod=d.devoluciones[i].id_prod;
                    for(k=1;k<prod.num_prod;k++){
                        if(id_prod==prod.produ[k].id_prod){
                            strcpy(nom_prod, prod.produ[k].nombre);
                        }
                    }
                }



                printf("| <%d>  %s - %s - %d/%d/%d - %d/%d/%d\n", i,
                                                            nom_prod,
                                                            d.devoluciones[i].estado,
                                                            d.devoluciones[i].f_aceptacion.dia,
                                                            d.devoluciones[i].f_aceptacion.mes,
                                                            d.devoluciones[i].f_aceptacion.anio,
                                                            d.devoluciones[i].f_caducidad.dia,
                                                            d.devoluciones[i].f_caducidad.mes,
                                                            d.devoluciones[i].f_caducidad.anio);
            }
        }
        
         
    

        
    }
}

void listar_pedidos(pedidos p){
    int i, j;
    char nom_client[21];

    clients c = cargar_clientes();

    printf("+--------------------------------------------------------+\n");
    printf("| LISTA DE TODOS LOS PEDIDOS                             |\n");
    printf("|--------------------------------------------------------+\n");
    printf("| <n> nombre cliente - fecha pedido - codigo promocional |\n");
    printf("+--------------------------------------------------------+\n");

    for(i=1;i<p.lon;i++){
        for(j=1;j<c.n_clients;j++){
            if(p.pedidos[i].id_cliente==c.clients[j].Id_cliente){
                strcpy(nom_client, c.clients[j].Nom_cliente);
            }

        }

        printf("| <%d> %s - %d/%d/%d - %s\n", i,
                                              nom_client,
                                              p.pedidos[i].f_pedido.dia,
                                              p.pedidos[i].f_pedido.mes,
                                              p.pedidos[i].f_pedido.anio,
                                              p.pedidos[i].id_cod);                                    
                                                            
    }

}

int busqueda_pedidos(pedidos p){
    int pos;
    listar_pedidos(p);
    do{
        printf("introduce el numero <n> del pedido que deseas modificar: \n");
        pos=input_int();
        return pos;
    }while(pos<p.lon && pos>1);
    
}

pedidos modificar_pedidos(pedidos p){
    int pos, //posicion del pedido que el usuario quiere modificar
        op, //opcion de lo que desea modificar el usuario
        lugar;//opcion del lugar donde entregar el pedido
    
    char locker[11];
    pos=busqueda_pedidos(p);

    printf("+-------- QUE DESEA MODIFICAR----------+\n");
    printf("| 1) LUGAR DE ENTREGA                  |\n");
    printf("| 2) LOCKER                            |\n");
    printf("+--------------------------------------+\n");

    printf("introduzca una opcion: ");
    op=input_int();

    switch(op){
        case 1:
            printf("Lugar de entrega actual: %s\n", p.pedidos[pos].lugar);
            printf("1. DOMICILIO\n");
            printf("2 .LOCKER\n");
            printf("introduzca una opcion: \n");
            lugar=input_int();
            switch(lugar){
                case 1:
                    strcpy(p.pedidos[pos].lugar, "Domicilio");
                    strcpy(p.pedidos[pos].id_locker, "noLocker");
                    break;
                case 2:
                    strcpy(p.pedidos[pos].lugar, "Locker");
                    strcpy(p.pedidos[pos].id_locker, "pendLock"); //esta pendiente de asignación de locker
                    //añadir un id del locker y un codigo del locker
                    //funciones modulo lockers para mirar locker libres
                    break;
                default:
                    printf("opcion no valida");
            }
            break;
        case 2:
            printf("Locker actual: %s\n", p.pedidos[pos].id_locker);
            printf("introduce el nuevo locker: ");
            fflush(stdin);
            fgets(locker, 11, stdin);
            strcpy(p.pedidos[pos].id_locker, locker);
            break;
        default:
            printf("opcion no valida\n");

    }
}

void listar_dev_pendientes(devoluciones d){

    printf("+-----------------------------------------------------------------+\n");
    printf("+----------- LISTA DEVOLUCIONES PENDIENTES DE ACEPTACION----------+\n");
    printf("+-----------------------------------------------------------------+\n");
    printf("| <n> nombre cliente - nombre producto - fecha realizo devolucion |\n");
    printf("+-----------------------------------------------------------------+\n");
    
    int i,j,k,l,
        id_ped,
        id_prod;

    char nom_cliente[21],
         nom_prod[16];

    clients c = cargar_clientes();
    produ_vect prod= cargar_productos();
    pedidos p = cargar_pedidos();


    for(i=1;i<d.lon;i++){
       
        //obtener nombre del cliente
        id_ped=d.devoluciones[i].id_pedido;
       
        for(j=1;j<p.lon;j++){
           
            if(id_ped==p.pedidos[j].id_pedido){
                for(k=1;k<c.n_clients;k++){
                    if(p.pedidos[j].id_cliente==c.clients[k].Id_cliente){
                        
                        strcpy(nom_cliente, c.clients[k].Nom_cliente); //guardo el nombre del cliente que corresponde a esa devolucion
                        
                    }
                    
                }
                
            }
            
        }
        //obtener nombre del producto
        id_prod=d.devoluciones[i].id_prod;
        for(l=1;l<prod.num_prod;l++){
            if(id_prod==prod.produ[l].id_prod){
                strcpy(nom_prod, prod.produ[l].nombre); //guardo el nombre del producto que corresponde a esa devolucion
            }
        }
        printf("%s\n",nom_prod );

        if(strcmp(d.devoluciones[i].estado, "pendiente")==0){
            printf("| <%d> %s - %s - %d/%d/%d\n", i,
                                                  nom_cliente,
                                                  nom_prod,
                                                  d.devoluciones[i].f_devol.dia,
                                                  d.devoluciones[i].f_devol.mes,
                                                  d.devoluciones[i].f_devol.anio);
        }

    }

}

devoluciones aceptar_dev(devoluciones d){
    int pos;
    listar_dev_pendientes(d);
    printf("introduce el numero <n> de la devolucion que deseas aceptar: ");
    pos=input_int();

    strcpy(d.devoluciones[pos].estado, "aceptada");

    d.devoluciones[pos].f_aceptacion.dia=dia_sist();
    d.devoluciones[pos].f_aceptacion.mes=mes_sist();
    d.devoluciones[pos].f_aceptacion.anio=anio_sist();

    d.devoluciones[pos].f_caducidad=crear_fechacad(d.devoluciones[pos].f_aceptacion);
    
}


//lockers
//terminar modificar devoluciones
//marcar aceptada parte administracion ¿en devoluciones?
    //seleccionar devolucion y automaticamente se pone como aceptada