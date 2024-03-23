
//ESTRUCTURAS
//Estructura pedidos.txt

typedef struct{
    int dia;
    int mes;
    int anio;
}fecha;
typedef struct{
    int id_pedido;
    fecha f_pedido;
    int id_cliente;
    char lugar[10];
    char id_locker[10];
    char id_cod[10];   
}pedido;

typedef struct{
    pedido *pedidos;
    int lon;
}pedidos;

//Estructura ProductosPedidos.txt
typedef struct{
    int id_pedido;
    int id_prod;
    int num_unid;
    fecha f_entrega;
    float importe;
    char estado[20];
    int id_transp;
    int id_locker;
    int cod_locker;
    fecha f_devolucion;
}prod_pedido;

typedef struct{
    prod_pedido *prod_pedidos;
    int lon;
}prod_pedidos;


typedef struct{
    int id_pedido;
    int id_prod;
    fecha f_devol;
    char motivo[50];
    char estado[10];
    fecha f_aceptacion;
    fecha f_caducidad;
}devolucion;

typedef struct{
    devolucion *devoluciones;
    int lon;
}devoluciones;


//FUNCIONES
pedidos cargar_pedidos();
prod_pedidos cargar_prod_pedidos();
devoluciones cargar_devoluciones();
void crear_pedido(int, pedidos);
void guardar_pedido(pedidos);
void guardar_productos_pedidos(prod_pedidos prod_p);