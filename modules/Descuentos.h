#ifndef DESCUENTOS_H_INCLUDED
#define DESCUENTOS_H_INCLUDED

#define MAX_DESC 87
#define MAX_DESCLI 42

typedef struct {

    char Id_cod[11],                //Identificador del código promocional
         Descrip[51],               //Descripción del código promocional
         Tipo[8],                  //"codpro" (código promocional) o "cheqreg" (cheque regalo)
         Estado[9],                 //Estado del cheque ("acctivo" o "inactivo")
         Aplicable[7];              //"todos" (si es aplicable a todos los productos) o "esizon" (si sólo esaplicable a los gestionados por ESIZON)

    int  Importe;                   //Importe del descuento en euros

}Descuentos;

typedef struct {

    char Id_cod[11];                //Identificador del código promocional

    int  Id_cliente,                //Identificador del cliente poseedor del descuento
         dia_asig,                  //Día de la fecha de asignación
         mes_asig,                  //Mes de la fecha de asignación
         anio_asig,                 //Año de la fecha de asignación
         dia_cad,                   //Día de la fecha de caducidad
         mes_cad,                   //Mes de la fecha de caducidad
         anio_cad,                  //Año de la fecha de caducidad
         Estado;                    //El valor 0 indica que el cupón no ha sido aplicado y el valor 1 que si lo ha sido

}DescuentosClientes;

//Se han separado los campos de las fechas para facilitar el manejo posterior con funciones

typedef struct{

    int tam;                        //Tamaño del vector
    Descuentos *Desc;               //Vector de tipo Descuentos

}Vect_Desc;

typedef struct{

    int tam;                        //Tamaño del vector
    DescuentosClientes *DescCli;    //Vector de tipo DescuentosClientes

}Vect_DescCli;


//Precondición: El fichero Descuentos.txt debe estar relleno
//Postcondición: Devuelve una estructura con el vector de estructuras Desc y almacena su tamaño
void Cargar_Descuentos();


//Precondición: El fichero DescuentosClientes.txt debe estar relleno
//Postcondición: Devuelve una estructura con el vector de estructuras DescCli y almacena su tamaño
void Cargar_DescuentosClientes();



#endif // DESCUENTOS_H_INCLUDED
