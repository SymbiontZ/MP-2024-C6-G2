typedef struct{
    int dia;
    int mes;
    int año;
}fecha;

typedef struct{
    int id_pedido;
    fecha f_pedido;
    int id_cliente;
    char lugar[10];
    int id_locker;
    int id_cod;   
}pedido;

typedef struct{
    pedido *pedidos;
    int lon;
}pedidos;

typedef struct{
    int id_pedido;
    int id_prod;
    int num_unid;
    fecha f_entrega;
    float importe;
    char estado[20];
    int id_transp;
    int cod_locker;
    fecha f_devolucion;
}prod_pedido;

typedef struct{
    prod_pedido *prod_pedidos;
    int lon
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