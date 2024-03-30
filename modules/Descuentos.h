#ifndef DESCUENTOS_H_INCLUDED
#define DESCUENTOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "useradmin.h"

#define MAX_DESC 87
#define MAX_DESCLI 42

typedef struct {

    char Id_cod[11],                //Identificador del codigo promocional
         Descrip[51],               //Descripcion del codigo promocional
         Tipo[8],                  //"codpro" (codigo promocional) o "cheqreg" (cheque regalo)
         Estado[9],                 //Estado del cheque ("acctivo" o "inactivo")
         Aplicable[7];              //"todos" (si es aplicable a todos los productos) o "esizon" (si solo esaplicable a los gestionados por ESIZON)

    int  Importe;                   //Importe del descuento en euros

}Descuento;

typedef struct {

    char Id_cod[11];                //Identificador del c�digo promocional

    int  Id_cliente,                //Identificador del cliente poseedor del descuento
         dia_asig,                  //Dia de la fecha de asignacion
         mes_asig,                  //Mes de la fecha de asignaci�n
         anio_asig,                 //A�o de la fecha de asignaci�n
         dia_cad,                   //D�a de la fecha de caducidad
         mes_cad,                   //Mes de la fecha de caducidad
         anio_cad,                  //A�o de la fecha de caducidad
         Estado;                    //El valor 0 indica que el cup�n no ha sido aplicado y el valor 1 que si lo ha sido

}DescCliente;

//Se han separado los campos de las fechas para facilitar el manejo posterior con funciones

typedef struct{

    int tam;                       //Tamano del vector
    Descuento *Desc;               //Vector de tipo Descuentos

}Descuentos;

typedef struct{

    int tam;                        //Tama�o del vector
    DescCliente *DescCliente;    //Vector de tipo DescuentosClientes

}DescClientes;


//Precondicion: El fichero Descuentos.txt debe estar relleno
//Postcondicion: Devuelve una estructura con el vector de estructuras Desc y almacena su tama�o
void Cargar_Descuentos();

//Precondici�n: El fichero DescuentosClientes.txt debe estar relleno
//Postcondici�n: Devuelve una estructura con el vector de estructuras DescCli y almacena su tama�o
void Cargar_DescuentosClientes();

//Precondicion: Recibe una estructura de tipo Descuentos con datos coherentes almacenados.
//Postcondicion: Guarda en Descuentos.txt los datos del vector de estructuras recibido
void Guardar_Descuentos(Descuentos);

//Precondicion: Recibe una estructura de tipo DescClientes con datos coherentes almacenados.
//Postcondicion: Guarda en DescuentosClientes.txt los datos del vector de estructuras recibido
void Guardar_DescuentosClientes(DescClientes);

//Precondición: Recibe las estructuras clients y DescClientes
//Postcondición: Lista los descuentos disponibles para el usuario en concreto
void Consultar_Descuentos(clients, DescClientes);

void Gestionar_Descuentos(Descuentos);

Descuentos Alta_Descuentos(Descuentos);

Descuentos Baja_Descuentos(Descuentos);

Descuentos Busqueda_Descuentos(Descuentos);

Descuentos Listar_Descuentos(Descuentos);

Descuentos Modificar_Descuentos(Descuentos);

Descuentos Asignar_Descuentos(Descuentos);

Descuentos nuevo_id(Descuentos, int);

Descuentos nueva_desc(Descuentos, int);

Descuentos nuevo_tipo(Descuentos, int);

Descuentos nuevo_est(Descuentos, int);

Descuentos nuevo_apl(Descuentos, int);

Descuentos nuevo_imp(Descuentos, int);
#endif // DESCUENTOS_H_INCLUDED
