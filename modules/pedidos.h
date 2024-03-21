
//ESTRUCTURAS
//Estructura pedidos.txt

typedef struct{
    int id_pedido;
    char f_pedido[10];
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
    char f_entrega[10];
    float importe;
    char estado[20];
    int id_transp;
    int id_locker;
    int cod_locker;
    char f_devolucion[10];
}prod_pedido;

typedef struct{
    prod_pedido *prod_pedidos;
    int lon;
}prod_pedidos;


typedef struct{
    int id_pedido;
    int id_prod;
    char f_devol[10];
    char motivo[50];
    char estado[10];
    char f_aceptacion[10];
    char f_caducidad[10];
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