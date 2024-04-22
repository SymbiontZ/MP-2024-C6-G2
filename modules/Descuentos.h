#ifndef DESCUENTOS_H_INCLUDED
#define DESCUENTOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "useradmin.h"

#define MAX_DESC 87
#define MAX_DESCLI 50

//ESTRUCTTURA DE DESCUENTOS
typedef struct {

    char Id_cod[11],                //Identificador del codigo promocional
         Descrip[51],               //Descripcion del codigo promocional
         Tipo[8],                  //"codpro" (codigo promocional) o "cheqreg" (cheque regalo)
         Estado[9],                 //Estado del cheque ("activo" o "inactivo")
         Aplicable[7];              //"todos" (si es aplicable a todos los productos) o "esizon" (si solo esaplicable a los gestionados por ESIZON)

    int  Importe;                   //Importe del descuento en euros

}Descuento;

//ESTRUCTURA DE DESCUENTOSCLIENTES
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

//ESTRUCTURA DE VECTOR DE DESCUENTOS Y NUM DE DESCUENTOS(TAM VECTOR)
typedef struct{

    int tam;                       //Tamano del vector
    Descuento *Desc;               //Vector de tipo Descuentos

}Descuentos;

//ESTRUCTURA DE VECTOR DE DESCUENTOSCLIENTES Y NUM DE DESCUENTOSCLIENTES(TAM VECTOR)
typedef struct{

    int tam;                        //Tama�o del vector
    DescCliente *DescCliente;    //Vector de tipo DescuentosClientes

}DescClientes;


//Precondicion: El fichero Descuentos.txt debe estar relleno
//Postcondicion: Devuelve una estructura con el vector de estructuras Desc y almacena su tama�o
Descuentos Cargar_Descuentos();

//Precondici�n: El fichero DescuentosClientes.txt debe estar relleno
//Postcondici�n: Devuelve una estructura con el vector de estructuras DescCli y almacena su tama�o
DescClientes Cargar_DescuentosClientes();

//Precondicion: Recibe una estructura de tipo Descuentos con datos coherentes almacenados.
//Postcondicion: Guarda en Descuentos.txt los datos del vector de estructuras recibido
void Guardar_Descuentos(Descuentos);

//Precondicion: Recibe una estructura de tipo DescClientes con datos coherentes almacenados.
//Postcondicion: Guarda en DescuentosClientes.txt los datos del vector de estructuras recibido
void Guardar_DescuentosClientes(DescClientes);

//Precondición: Recibe la estructura DescClientes
//Postcondición: Lista los descuentos disponibles para el usuario en concreto
void Consultar_Descuentos(DescClientes);

//Precondición: Recibe valor entero (posicion de cliente en la estructura) y el modo que muestra(0: TODOS, 1: DISPONIBLES PARA ASIGNAR)
//Postcondición: Muestra un listado con los descuentos asignados al cliente
void Consultar_desc_cliente(int, int);

//Precondición: Recibe 2 estructuras (Descuentos, DescClientes)
//Postcondición: Muestra un menú con las funcionalidades referentes a los descuentos
void Gestionar_Descuentos(Descuentos, DescClientes);

int desc_activo(char[] );

void marcar_aplicado(int, char[]);
//Precondición: Recibe la estructura Descuentos
//Postcondición: Devuelve la estructura Descuentos con el descuento seleccionado eliminado
Descuentos Baja_Descuentos(Descuentos);

//Precondición: Recibe la estructura Descuentos
//Postcondición: Devuelve la estructura Descuentos y muestra el descuento/descuentos coincidentes con la búsqueda
Descuentos Busqueda_Descuentos(Descuentos);

//Precondición: Recibe la estructura Descuentos
//Postcondición: Devuelve la estructura Descuentos y lista todos los descuentos contenidos en la estructura
Descuentos Listar_Descuentos(Descuentos);

//Precondición: Recibe la estructura Descuentos
//Postcondición: Devuelve la estructura Descuentos con las modificaciones realizadas
Descuentos Modificar_Descuentos(Descuentos);

//Precondición: Recibe 2 estructuras (Descuentos, DescClientes)
//Postcondición: Devuelve la estructura Descuentos con el descuento asignado al cliente indicado
Descuentos Asignar_Descuentos(Descuentos, DescClientes);

//Precondición: Recibe la estructura Descuentos
//Postcondición: Devuelve la estructura Descuentos con un nuevo descuento
Descuentos Alta_Descuentos(Descuentos);

///------------------------------- FUNCIONES INTERNAS DE Alta_Descuentos -------------------------------///

//Precondición: Recibe la estructura Descuentos
//Postcondición: Devuelve la estructura Descuentos con el id del nuevo descuento
Descuentos nuevo_id(Descuentos, int);

//Precondición: Recibe la estructura Descuentos
//Postcondición: Devuelve la estructura Descuentos con la descripción del nuevo descuento
Descuentos nueva_desc(Descuentos, int);

//Precondición: Recibe la estructura Descuentos
//Postcondición: Devuelve la estructura Descuentos con el tipo del nuevo descuento
Descuentos nuevo_tipo(Descuentos, int);

//Precondición: Recibe la estructura Descuentos
//Postcondición: Devuelve la estructura Descuentos con el estado del nuevo descuento
Descuentos nuevo_est(Descuentos, int);

//Precondición: Recibe la estructura Descuentos
//Postcondición: Devuelve la estructura Descuentos con la aplicabilidad del nuevo descuento
Descuentos nuevo_apl(Descuentos, int);

//Precondición: Recibe la estructura Descuentos
//Postcondición: Devuelve la estructura Descuentos con el importe del nuevo descuento
Descuentos nuevo_imp(Descuentos, int);

#endif // DESCUENTOS_H_INCLUDED
