#include<stdio.h>
#include"pedidos.h"
#include<stdlib.h>
#include<string.h>
#include"empresas.h"
#include"Productos.h"
#include"useradmin.h"
#include<time.h>



//Cabecera: pedidos cargar_pedidos()
//Precondición: el fichero debe existir y la estructura de cada pedido
//Postcondición: guarda en un vector de tipo pedido cada pedido que hay en el fichero.

pedidos cargar_pedidos(){
    
    int n_pedidos=0, i=0, campo_pedidos;
    char default_pedido[]="0-0/0/0-0-default-default-default";
    char cad_aux[150]; //cadena auxiliar en la que se guarda cada linea del fichero
    
    FILE * f_ped;
    f_ped=fopen("../data/Pedidos.txt", "r"); //abre el fichero Pedidos.txt
    if(f_ped==NULL){ //si no existe el fichero o esta vacio lo crea
        f_ped=fopen("../data/Pedidos.txt","w");
        fclose(f_ped);
        printf("ERROR");
    }

    rewind(f_ped);
    if(fgetc(f_ped)==EOF){
        f_ped=fopen("../data/Pedidos.txt", "w");
        fprintf(f_ped, default_pedido);
        fclose(f_ped);
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
            printf("error en estructura pedidos, i=%d", i);
        }

        i++;
        
    }

    printf("pedidos: %d\n", n_pedidos);

    return p;
}

//Cabecera: void crear_pedido(int id_cliente, pedidos p)
//Precondicion: estrcutura pedidos cargada con datos del fichero Pedidos.txt y el id del cliente que ha realizado pedido, lo sabemos cuando ha iniciado sesión en la aplicación
//Postcondicion: se crea un nuevo pedido realizado por un cliente y se guarda en la estructura pedidos, ademas de escribirlo en el fichero Pedidos.txt
int crear_pedido(int id_cliente, pedidos p){
    int n_pedidos=p.lon-1, i=0, nueva_id, pos, lugar, n_products=1, n_uds=0, compra=1, pos_product, j=0, id_producto, importe_total=0,id, importe_uds=0,cantidad=0,importe_cant=0; //n_products es la longitud de los vectores dinamicos
    char cod_cheque[10],nombre[16];
    char op,cheque;
    int *v_prod, *v_uds;//vectores auxiliares con los id de los productos que realiza el cliente ese pedido y las unidades de cada producto
    
    v_prod=malloc(n_products*sizeof(int)); 
    v_uds=malloc(n_products*sizeof(int));

    nueva_id=n_pedidos +1; //id de un nuevo pedido, será el numero de pedidos que hay en el fichero +1
    pos=nueva_id; //posicion del nuevo pedido es la id ya que la nueva id sera un nuevo pedido por tanto el numero de pedidos que hay
    p.pedidos=realloc(p.pedidos, (pos+1)*sizeof(pedido)); //reasignamos memoria dinámica, el tamaño sera la pos mas uno ya que la estructura tendra una posicion
    
    produ_vect productos;
    productos=cargar_productos();
    clients c;
    c=cargar_clientes();
    int credito_c=c.clients[id_cliente].Cartera;

    //SELECCIONAR PRODUCTO
    id_producto=1;
    while(compra==1){ //bucle para seleccionar todos los productos y rellenar los vectores dinámicos
        printf("AGREGAR PRODUCTO AL PEDIDO\n");
        n_uds=0;
        fflush(stdin);
        //id_producto=buscar_productos(productos); //la posicion de un producto es la misma que su id
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
            printf("OPCIONES DISPONIBLES: \n");
            printf("1. Modificar unidades\n");
            printf("2. Cancelar compra\n");
            if(importe_uds==credito_c){
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
                while(importe_cant<credito_c-importe_cant){
                    importe_cant=cantidad*productos.produ[id_producto].importe;
                    cantidad++;
                }
                cantidad=cantidad-1;
                if(cantidad==0){
                    printf("no puede comprar ninguna unidad de este producto\n");
                }
                else{
                    printf("puede comprar %d unidades del producto\n", cantidad);
                    printf("desea añadir el producto [s/n]: \n");
                    fflush(stdin);
                    char aux=confirmacion();
                    if(aux=='s' || aux=='S'){
                        v_prod[n_products-1]=id_producto;
                        printf("cuantas unidades desea introducir: \n");
                        scanf("%d", &n_uds);
                        v_uds[n_products-1]=n_uds;
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
                
            }

        }
        else{
            credito_c=credito_c-importe_uds; //le resto al credito del cliente el import
            printf("el importe es menor que el credito del cliente\n");

            
        }

        importe_total=importe_total + (productos.produ[id_producto].importe * n_uds); //cada vez que se incluye un producto en la lista se añade al importe total del pedido
        printf("el importe total del pedido es: %d\n", importe_total);

        fflush(stdin);
        printf("Desea agregar mas productos al pedido [s/n]: \n");
        op=confirmacion();
        if(op=='s'){
            n_products++;
            id_producto++;
        }
        else{
            compra=0; //para salir del bucle
            printf("no desea agregar mas productos al pedido\n");
            printf("continuamos con el pedido\n");
        }
        

        
        
    }
    //RESUMEN DE LOS PRODUCTOS QUE HA PEDIDO Y EL IMPORTE TOTAL
    
    for(j=0;j<n_products;j++){
        id=v_prod[j];
        strcpy(nombre, productos.produ[id].nombre);
        printf("nombre del producto: %s\n", nombre);
        printf("unidades de ese producto: %d\n", v_uds[j]);
    }
    
    

    p.pedidos[pos].id_pedido=nueva_id;
    p.pedidos[pos].id_cliente=id_cliente;

    p.pedidos[pos].f_pedido.dia=dia_sist();
    p.pedidos[pos].f_pedido.mes=mes_sist();
    p.pedidos[pos].f_pedido.anio=anio_sist();

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

    printf("Desea utilizar un cheque de descuento [s/n]: \n");
    cheque=confirmacion();
    if(cheque=='s' || cheque == 'S'){
        printf("introduce el codigo del cheque:");
        fflush(stdin);
        fgets(cod_cheque, 11, stdin);
        //if cod_cheque existe y es valido lo copia al fichero
        terminador_cad(cod_cheque);
        strcpy(p.pedidos[pos].id_cod, cod_cheque);
    }   
    else{
        strcpy(p.pedidos[pos].id_cod,"000000000");
        
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
    int n_prod_ped=0, i=0, campo_prod_ped;
    char cad_aux[200];
    char default_prod_ped[]="0-0-0-0/0/0-0-default-0-default-default-0/0/0\n";
    
    FILE * f_prod_ped;
    f_prod_ped=fopen("../data/ProductosPedidos.txt", "r");
    if(f_prod_ped==NULL){
        f_prod_ped = fopen("../data/ProductosPedidos.txt", "w");
        fclose(f_prod_ped);
        printf("ERROR");
    }

    rewind(f_prod_ped);

    if(fgetc(f_prod_ped) == EOF){
        f_prod_ped=fopen("../data/ProductosPedidos.txt", "w");
        fprintf(f_prod_ped, default_prod_ped);
        fclose(f_prod_ped);
    }
    while(fgets(cad_aux, sizeof(cad_aux), f_prod_ped)){
        n_prod_ped++; //numero de productos pedidos
    }
    rewind(f_prod_ped);

    prod_pedidos prod_p;

    prod_p.lon=n_prod_ped;

    prod_p.prod_pedidos=malloc(n_prod_ped*sizeof(prod_pedido));
    
    while(fgets(cad_aux, sizeof(cad_aux), f_prod_ped) && i<n_prod_ped){
        campo_prod_ped=sscanf(cad_aux, "%d-%d-%d-%d/%d/%d-%f-%10[^-]-%d-%10[^-]-%10[^-]-%d/%d/%d",
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
            printf("error en la estructura productos pedidos, i=%d", i);
        }

        i++;
    }

    printf("productos pedidos: %d\n", n_prod_ped);
    
    return prod_p;
}

//Cabecera: guardar_producto_pedido()
//Precondicion:
//Postcondicion: rellena la estructura con un nuevo producto pedido y lo escribe en el fichero
void guardar_productos_pedidos(prod_pedidos prod_p){
    int i;

    FILE*f_prod_ped;
    f_prod_ped=fopen("../data/ProductosPedidos.txt", "rw+");
    if(f_prod_ped==NULL){
        printf("ERROR");
    }

    for(i=0;i<prod_p.lon;i++){
        fprintf(f_prod_ped, "%d-%d-%d-%d/%d/%d-%f-%s-%d-%s-%s-%d/%d/%d\n",
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
}

//Cabecera
//Precondición
//Postcondicion
void crear_producto_pedido(pedidos p, int pos_product, int id_pedido, prod_pedidos prod_p){
    int i, pos, nuevo_prod_p, ud,j,k, ocupado=0, id_t, m=0, numero;
    int disponibles[2]; //vector con los transportistas que pueden encargarse de un producto
    char ciudad[50]; //variable auxiliar para almacenar la ciudad del cliente

    transport_vect t; //variable de tipo transportistas 
    t=cargar_transportistas(); //carga la estructura transportistas con los datos que hay en el fichero
    clients c;
    c=cargar_clientes();
    produ_vect productos;
    productos=cargar_productos();

    prod_p.prod_pedidos=realloc(prod_p.prod_pedidos,(prod_p.lon+1)*sizeof(prod_pedido));
    pos=prod_p.lon; //la posicion en el vector de la estructura de producto pedido
    prod_p.prod_pedidos[pos].id_prod=productos.produ[pos_product].id_prod; //la id del producto que ha seleccionado el cliente
    prod_p.prod_pedidos[pos].id_pedido=id_pedido; //la id del pedido que se ha creado cuando el cliente decide comprar el producto
    

    for(i=0;i<p.lon;i++){
        if(id_pedido==p.pedidos[i].id_pedido){
            printf("el pedido existe");
            
            //UNIDADES DEL PRODUCTO
            printf("Cuantas unidades desea del producto: ");
            scanf("%d",&ud);
            if(ud<productos.produ[pos_product].stock && ud>0){
                prod_p.prod_pedidos[pos].num_unid=ud;
            }
            else{
                printf("ERROR");
                printf("ha introducido un numero de unidades incorrecto");
            }

            //FECHA DE ENTREGA
            

            //IMPORTE
            prod_p.prod_pedidos[pos].importe=productos.produ[pos_product].importe; 
            
            //ESTADO
            strcpy(prod_p.prod_pedidos[pos].estado, "En preparacion");
            //ID TRANSPORTISTA
            for(j=0;j<c.n_clients;j++){ //bucle para recorrer la estructura cliente
                if(p.pedidos[i].id_cliente==c.clients[j].Id_cliente){ //buscar en el fichero de clientes, el cliente que ha realizado este pedido
                    strcpy(ciudad, c.clients[j].Localidad); //en una cadena auxiliar guardo la ciudad del cliente
                }
            }
            for(k=0;k<t.tam;k++){ //bucle para recorrer la estructura transportistas
                if(strcmp(ciudad, t.transportistas[k].Ciudad)==0){//buscar transportista de la misma ciudad del cliente
                    printf("id transportista %d\n", t.transportistas[k].Id_transp);
                    disponibles[m]=t.transportistas[k].Id_transp; //rellena el vector con los transportistas de esa ciudad
                    m++;
                }
            }
            srand (time(NULL));
            numero=rand() % (m+1); //numero aleatorio para asignar un transportista de los que hay en esa ciudad
            prod_p.prod_pedidos[pos].id_transp=disponibles[numero];
            //añadir excepcion si no hay transportistas en esa ciudad

            //LOCKERS
            //igual que con asignar un transportista
        }
    }
}
        

//Cabecera: devoluciones cargar_devoluciones()
//Precondicion:
//Postcondicion: carga en la estructura devoluciones los datos que hay en el fichero Devoluciones.txt

devoluciones cargar_devoluciones(){
    int n_dev=0, i=0, campo_devoluciones;
    char cad_aux[150];
    char default_dev[]="0-0-0/0/0-default-default-0/0/0-0/0/0\n";

    FILE * f_dev;
    f_dev=fopen("../data/Devoluciones.txt", "r"); //Abrir fichero
    if(f_dev==NULL){
        f_dev=fopen("../data/Devoluciones.txt", "w");
        fclose(f_dev);
        printf("ERROR");
    }

    rewind(f_dev);

    if(fgetc(f_dev) == EOF){
        f_dev=fopen("../data/Devoluciones.txt", "w");
        fprintf(f_dev, default_dev);
        fclose(f_dev);
    }
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

void crear_devolucion(devoluciones d, pedidos p, prod_pedidos prod_p){
    int i, pos, id_ped, producto;
    char motivo[50];
    pos=d.lon;
    d.devoluciones=realloc(d.devoluciones, (pos+1)*sizeof(devolucion));

    fflush(stdin);

    printf("Introduce el id del pedido que desea devolver: ");
    scanf("%d", &id_ped);
    fflush(stdin);
    d.devoluciones[pos].id_pedido=id_ped; 
    
    for(i=0;i<p.lon;i++){//bucle para buscar el producto que corresponde a ese pedido que desea devolver el cliente
        if(id_ped==prod_p.prod_pedidos[i].id_pedido){
            producto=prod_p.prod_pedidos[i].id_prod; //saca el producto al que corresponde el pedido
        }
    }
    d.devoluciones[pos].id_prod=producto;
    printf("el producto que corresponde a ese pedido es: %d\n", producto);
    
    d.devoluciones[pos].f_devol.dia=dia_sist(); //fecha en la que se realiza la solicitud de la devolucion, es la fecha del dia que se rellena la devolucion
    d.devoluciones[pos].f_devol.mes=mes_sist();
    d.devoluciones[pos].f_devol.anio=anio_sist();

    printf("Introduce el motivo de la devolución: "); //usuario introduce el motivo de la devolucion
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
