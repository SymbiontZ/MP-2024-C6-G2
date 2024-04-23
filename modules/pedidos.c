#include<stdio.h>
#include"pedidos.h"
#include"useradmin.h"
#include"Descuentos.h"

//Cabecera: pedidos cargar_pedidos()
//Precondición: el fichero debe existir y la estructura de cada pedido
//Postcondición: guarda en un vector de tipo pedido cada pedido que hay en el fichero.

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

//Cabecera: void crear_pedido(int id_cliente, pedidos p)
//Precondicion: estrcutura pedidos cargada con datos del fichero Pedidos.txt y el id del cliente que ha realizado pedido, lo sabemos cuando ha iniciado sesión en la aplicación
//Postcondicion: se crea un nuevo pedido realizado por un cliente y se guarda en la estructura pedidos, ademas de escribirlo en el fichero Pedidos.txt
int crear_pedido( pedidos p, int id_cliente, int modo){
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
        printf("id producto seleccionado: %d\n",id_producto);

        v_prod=(int*)realloc(v_prod, n_products*sizeof(int));//agrego la id del producto seleccionad al vector productos
        
        
        //SELECCIONAR UNIDADES DE CADA PRODUCTO
        v_uds=(int*)realloc(v_uds, n_products*sizeof(int));
        printf("Stock del producto: %d\n",productos.produ[id_producto].stock);
        printf("introduce el numero de unidades que desea del producto: \n");
        scanf("%d", &n_uds);

        //comprobar unidades del producto validas
        printf("unidades seleccionadas: %d\n", n_uds);
        while(n_uds>productos.produ[id_producto].stock || n_uds<1){
            printf("ERROR: ha introducido una opcion válida\n");
            printf("Introduzca una opcion válida\n");
            scanf("%d", &n_uds);
        }
        

        importe_uds=productos.produ[id_producto].importe*n_uds; //importe de cada producto
        printf("el importe es: %d\n", importe_uds);
        printf("el credito del cliente es: %d\n",credito_c);
        //Comprobamos importe del pedido es menor que credito del cliente
        
        if(importe_uds>=credito_c){ 
            printf("ERROR: el importe es superior al credito que tiene el cliente\n");
            printf("OPCIONES DISPONIBLES: \n"); //opciones que tiene el usuario cuando el importe supera su credito
            printf("1. Modificar unidades\n");
            printf("2. Cancelar compra\n");
            if(importe_uds==credito_c){ //opcion para cuando el importe es igual que el credito del cliente
                printf("3. Terminar compra\n");
            }
            printf("introduzca una opcion: \n");
            int resp;
            scanf("%d", &resp);

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
                        printf("no puede comprar ninguna unidad de este producto\n");
                    }
                    else{
                        printf("puede comprar %d unidades del producto\n", cantidad);
                        printf("desea añadir el producto [s/n]: \n");
                        fflush(stdin);
                        char aux=confirmacion();
                        if(aux=='s' || aux=='S'){
                            printf("cuantas unidades desea introducir: \n"); //preguntar al usuario cuantas unidades quiere del producto 
                            scanf("%d", &n_uds);
                            
                        }
                        else{
                            n_uds=0;
                        }
                    }
                break;

                case 2:
                    return -1;

                case 3:
                    compra=0;
                    printf("no desea agregar mas productos al pedido\n");
                    printf("continuamos con el pedido\n");
                    break;
                
            }

        }
        else{
            credito_c=credito_c-importe_uds; //le resto al credito del cliente el import
            printf("el importe es menor que el credito del cliente\n");

            
        }
        
        v_prod[n_products-1]=id_producto; //guardar en el vector dinamico el id del producto que ha seleccionado el cliente
        v_uds[n_products-1]=n_uds; //guardar numero de unidades de ese producto que ha seleccionado el usuario
        importe_total=importe_total + (productos.produ[id_producto].importe * n_uds); //cada vez que se incluye un producto en la lista se añade al importe total del pedido
        
        //Preguntar al cliente si desea añadir mas productos a un pedido
        
        fflush(stdin);
        printf("Desea agregar mas productos al pedido [s/n]: \n");
        op=confirmacion();
        if(op=='s'){
            n_products++;
            id_producto++;
        }
        else{
            compra=0; //para salir del bucle
            printf("\nno desea agregar mas productos al pedido\n");
            printf("\ncontinuamos con el pedido\n");
        }

    }while(compra != 0);
    //RESUMEN DE LOS PRODUCTOS QUE HA PEDIDO Y EL IMPORTE TOTAL
    
    printf("\n---RESUMEN DEL PEDIDO---\n");
    for(j=0;j<n_products;j++){ 
        id=v_prod[j];
        strcpy(nombre, productos.produ[id].nombre);
        printf("-nombre del producto: %s\n", nombre);
        printf("-unidades de ese producto: %d\n", v_uds[j]);
    }
    printf("-el numero de productos del pedido es: %d\n",n_products);
    printf("-el importe total del pedido es: %d\n", importe_total);
    
    printf("pos: %d", pos);
    //ALMACENAR EN LA ESTRUCTURA PEDIDO LOS DATOS DEL PEDIDO
    p.pedidos[pos].id_pedido=nueva_id;

    
    if(modo==0){
        printf("crear pedido como administrador\n");
        p.pedidos[pos].id_cliente=busqueda_cliente();
    }
    else{
        printf("crear pedido como cliente\n");
    }
    p.pedidos[pos].id_cliente=id_cliente;

    p.pedidos[pos].f_pedido.dia=dia_sist();
    p.pedidos[pos].f_pedido.mes=mes_sist();
    p.pedidos[pos].f_pedido.anio=anio_sist();


    /***LUGAR DE ENTREGA Y CHEQUES***/
    clear();
    printf("Selecciona un lugar de entrega: \n");
    printf("1. DOMICILIO\n");
    printf("2. LOCKER\n");
    printf("su opcion : ");
    scanf("%d", &lugar);
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

    clear();
    printf("Desea utilizar un cheque de descuento [s/n]: \n");
    cheque=confirmacion();
    int l,k, 
        conf=0;//variable para almacenar si el cliente tiene asociados codigos de descuento
    char cod_desc[11];
    if(cheque=='s' || cheque == 'S'){
        //listar descuentos de ese cliente
        do{
            printf("Introduce el codigo del descuento que deseas utilizar: ");
            fflush(stdin);
            fgets(cod_desc, 11, stdin);
            terminador_cad(cod_desc);
        
            conf = comprobar_descuento(cod_desc, id_cliente);
            if(conf==0){
                printf("el codigo de descuento introducido es correcto\n");
                strcpy(p.pedidos[pos].id_cod, cod_desc);
                cheque='n';
            }
            else{
                printf("el codigo de descuento introducido no es correcto\n");
                printf("desea introducir otro codigo de descuento [s/n]: ");
                cheque=confirmacion();
                if(cheque == 'n' || cheque == 'N'){
                    strcpy(p.pedidos[pos].id_cod, "nocod\0");
                }
                
            
            }  
            printf("%c", cheque);
            
        }while(conf!=0 || (cheque !='s' || cheque !='S'));
       
    }
    else{
        strcpy(p.pedidos[pos].id_cod, "nocod\0");
        
    }

    p.lon=p.lon+1; //actualiza el numero de pedidos que hay 

    guardar_pedido(p);

    printf("Se acaba de descontar %d euros de su cartera", importe_total);
    c.clients[id_cliente].Cartera -= importe_total;

    guardar_clientes(c);
    

    //CREAR PRODUCTO PEDIDO Y GUARDARLO EN LA ESTRUCTURA
   int id_pro, n_unidades;
    for(j=0;j<n_products+1;j++){
        prod_pedidos Prod_P=cargar_prod_pedidos();
        /*printf("productos pedidos: %d\n", n_products);
        printf("j: %d\n", j);
        printf("\npara llamar a la funcion crear producto pedido\n");*/
        id_pro=v_prod[j];
        
        //printf("id producto: %d\n",id_pro);
        n_unidades=v_uds[j];
        //printf("unidades de ese productos: %d\n", n_unidades);
        crear_producto_pedido(p, id_pro, nueva_id, Prod_P, n_unidades);

    }
    
    return 1;
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
    
    if(comp==1){
        printf("el codigo no ha caducado\n");
    }
    else{
        printf("el codigo esta caducado\n");
        return 1;
    }

    //SACAR LA POSICION 
    for(i=0;i<des.tam;i++){
        printf("cod descuento introducido: %s\n", cod_descuento);
        printf("cod descuento del fichero: %s\n", des_c.DescCliente[i].Id_cod);
        printf("%d",strcmp(cod_descuento, des.Desc[i].Id_cod));
        if(strcmp(cod_descuento, des.Desc[i].Id_cod)==0){
            printf("prueba1\n");
            printf("el codigo de descuento introducido existe\n");
            if(strcmp(des.Desc[i].Estado, "activo")==0){
                printf("el descuento esta activo");
                for(j=0;j<des_c.tam;j++){
                    if(id_cliente==des_c.DescCliente[j].Id_cliente){
                        printf("cliente tiene asociado descuento\n");
                        if(strcmp(cod_descuento, des_c.DescCliente[j].Id_cod)==0){
                            printf("el descuento pertenece al cliente\n");
                            if(des_c.DescCliente[j].Estado==0){
                                printf("el descuento no ha sido aplicado por tanto lo puede usar el cliente\n");
                                return 0;
                            }
                            else{
                                printf("el descuento no lo puede aplicar el cliente\n");
                            }
                                
                        }
                    }
                }
            }
        }
        
    }

    return 1;
    
    
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

//Cabecera: prod_pedidos cargar_prod_pedidos()
//Precondicion:
//Postcondicion: carga en la estructura prod_pedidos los datos del fichero ProductosPedidos.txt
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

//Cabecera: guardar_producto_pedido()
//Precondicion:
//Postcondicion: rellena la estructura con un nuevo producto pedido y lo escribe en el fichero
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
}

void eliminar_pedidos_productos(prod_pedidos prod_p, pedidos p, int pos_ped){
    int i;
    char resp;
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
      

//Cabecera: devoluciones cargar_devoluciones()
//Precondicion:
//Postcondicion: carga en la estructura devoluciones los datos que hay en el fichero Devoluciones.txt

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
        fclose(f_dev);
    }
    
    rewind(f_dev);

    while(fgets(cad_aux, sizeof(cad_aux), f_dev)){
        n_dev++; //numero de devoluciones que hay, es decir, las líneas del fichero
    }
    rewind(f_dev);

    devoluciones dev;

    dev.lon=n_dev;
    dev.devoluciones=malloc(n_dev*sizeof(devolucion));

    while(fgets(cad_aux, sizeof(cad_aux), f_dev) && i<n_dev){
        campo_devoluciones=sscanf(cad_aux, "%d-%d-%d/%d/%d-%50[^-]-%10[^-]-%d/%d/%d-%d/%d/%d",
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

    printf("devoluciones: %d\n", n_dev);
    return dev;

}

void guardar_devoluciones(devoluciones d){
    int i;

    FILE*f_dev;
    f_dev=fopen("../data/Devoluciones.txt", "w");
    if(f_dev==NULL){
        printf("ERROR");
    }

    for(i=0;i<d.lon;i++){
        fprintf(f_dev,"%d-%d-%d/%d/%d-%s-%s-%d/%d/%d-%d/%d/%d\n",
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

void crear_devolucion(devoluciones d, int id_pedido, int id_producto){
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
            printf("| <%d> FECHA: %d / %d / %d LUGAR:%-9s                                               |\n", i,
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

void listar_prod_clientes(int id_cliente, pedidos p, prod_pedidos prod_p){
    int i,j,k,
        id_prod,     //variable para almacenar los id de los productos que han sido entregados al cliente
        n_coinc = 0, //variable para almacenar el numero de coincidencias que hay
        op, //variable que almacena el producto que quiere devolver el cliente
        pos_prod,
        pos_ped;

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
    scanf("%d", &op);
    fflush(stdin);
    pos_prod=v_prod[op-1];
    pos_ped=v_ped[op-1];
    

    devoluciones d =cargar_devoluciones();
    crear_devolucion(d, pos_ped, pos_prod);
    
}


void listar_devoluciones(pedidos p, prod_pedidos prod_p, devoluciones d){
    int i, j,k,
        id_pedido,
        id_prod;
    printf("+---------------------+\n");
    printf("| DEVOLUCIONES        |\n");
    printf("+---------------------+\n");

    produ_vect prod = cargar_productos();
    clients c =cargar_clientes();

    for(i=1;i<d.lon;i++){
        id_pedido=d.devoluciones[i].id_pedido;
        
        for(j=0;j<p.lon;j++){
            if(id_pedido==p.pedidos[j].id_pedido){
                for(k=0;k<c.n_clients;k++){
                    if(p.pedidos[j].id_cliente==c.clients[k].Id_cliente){
                        printf("nombre del cliente: %s", c.clients[k].Nom_cliente);
                    }
                }
            }
            
        }
        id_prod=d.devoluciones[i].id_prod;
        for(j=0;prod.num_prod;j++){
            if(id_prod==prod.produ[j].id_prod){
                printf("nombre del producto: %s", prod.produ[j].nombre);
            }
        }

        printf("estado de la devolucion: %s", d.devoluciones[i].estado);

        printf("fecha aceptacion: %d/%d/%d",  d.devoluciones[i].f_aceptacion.dia,
                                              d.devoluciones[i].f_aceptacion.mes,
                                              d.devoluciones[i].f_aceptacion.anio);

        printf("fecha caducidad: %d/%d/%d",   d.devoluciones[i].f_caducidad.dia,
                                              d.devoluciones[i].f_caducidad.mes,
                                              d.devoluciones[i].f_caducidad.anio);
    }

}

