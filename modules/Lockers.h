#ifndef LOCKERS_H_INCLUDED
#define LOCKERS_H_INCLUDED

#include "pedidos.h"
#include "useradmin.h"
#include "complementos.h"

#define MAX_LOCK 79
#define MAX_COMPLOCK 50

typedef struct{

    char Id_locker[11],                 //Identificador del Locker
         Localidad[21],                 //Población donde se encuentra el Locker
         Provincia[21],                 //Provincia donde se encuentra el Locker
         Ubica[21];                     //Ubicación del Locker

    int  Num_compT,                     //Número de compartimentos totales
         Num_compOkup;                  //Número de compartimentos ocupados actualmente

}Lockers;

typedef struct{

    char Id_locker[11],                 //Identificador del Locker
         Estado[8];                     //"ocupado" o "vacío"

    int Num_comp,                       //Número de compartimento
        Cod_locker,                     //Código del Locker
        dia_okup,                       //Dia de la fecha de Ocupación
        mes_okup,                       //Mes de la fecha de Ocupación
        anio_okup,                      //Año de la fecha de Ocupación
        dia_cad,                        //Dia de la fecha de Caducidad
        mes_cad,                        //Mes de la fecha de Caducidad
        anio_cad;                       //Año de la fecha de Caducidad

}CompartimentosLockers;

//Se han separado los campos de las fechas para facilitar el manejo posterior con funciones

typedef struct{

    int tam;                            //Tamaño del vector
    Lockers *Lock;                      //Vector de tipo Lockers

}Vect_Lock;

typedef struct{

    int tam;                            //Tamaño del vector
    CompartimentosLockers *CompLock;    //Vector de tipo CompartimentosLockers

}Vect_CompLock;

//Precondicion: El fichero Lockers.txt debe estar relleno
//Postcondicion: Devuelve una estructura con el vector de estructuras Desc y almacena su tama�o
Vect_Lock Cargar_Lockers();

//Precondici�n: El fichero CompartimentosLockers.txt debe estar relleno
//Postcondici�n: Devuelve una estructura con el vector de estructuras DescCli y almacena su tama�o
Vect_CompLock Cargar_CompartimentosLockers();

//Precondicion: Recibe una estructura de tipo Vect_Lock con datos coherentes almacenados.
//Postcondicion: Guarda en Lockers.txt los datos del vector de estructuras recibido
void Guardar_Lockers(Vect_Lock lockers);

//Precondicion: Recibe una estructura de tipo Vect_CompLock con datos coherentes almacenados.
//Postcondicion: Guarda en CompartimentosLockers.txt los datos del vector de estructuras recibido
void Guardar_CompartimentosLockers(Vect_CompLock compartimentoslockers);

//Precondición: Recibe 3 estructuras (Descuentos, DescClientes, clients)
//Postcondición: Muestra un menú con las funcionalidades referentes a los lockers
void Gestionar_Lockers(Vect_Lock);

//Precondición: Recibe la estructura Lockers
//Postcondición: Devuelve la estructura Lockers con un Locker eliminado
Vect_Lock Baja_Lockers(Vect_Lock);

//Precondición: Recibe la estructura Lockers
//Postcondición: Muestra todos los lockers del fichero
void Listar_Lockers(Vect_Lock);

//Precondición: Recibe la estructura Lockers y la posicion de la estructura pedidos del pedido que quiere asignarse en un locker
//Postcondición: Devuelve la posicion del primer locker coincidente con la ciudad deseada
int Locker_Dispo(Vect_Lock, int);

//Precondición: Recibe la estructura Lockers y la posicion del primer locker disponible
//Postcondición: Devuelve la posicion del primer compartimento disponible en el locker
int Comp_Dispo(Vect_Lock, Vect_CompLock, int);

//Precondición: Recibe las estructuras Lockers y CompartimentosLockers
//Postcondición: Devuelve la estructura CompartimentosLockers asignada al locker correspondiente
Vect_CompLock Asignar_Compartimentos(Vect_Lock, Vect_CompLock);

//Precondición: Recibe la estructura Lockers
//Postcondición: Devuelve la estructura Lockers con un Locker nuevo
Vect_Lock Alta_Lockers(Vect_Lock);

///------------------------------- FUNCIONES INTERNAS DE Alta_Lockers -------------------------------///

//Precondición: Recibe la estructura Lockers
//Postcondición: Devuelve la estructura Descuentos con el id del nuevo locker
Vect_Lock nuevo_idL(Vect_Lock, int);

//Precondición: Recibe la estructura Lockers
//Postcondición: Devuelve la estructura Descuentos con la localidad del nuevo locker
Vect_Lock nueva_localidadL(Vect_Lock, int);

//Precondición: Recibe la estructura Lockers
//Postcondición: Devuelve la estructura Descuentos con la provincia del nuevo locker
Vect_Lock nueva_provinciaL(Vect_Lock, int);

//Precondición: Recibe la estructura Lockers
//Postcondición: Devuelve la estructura Descuentos con la ubicación del nuevo locker
Vect_Lock nueva_ubicaL(Vect_Lock, int);

//Precondición: Recibe la estructura Lockers
//Postcondición: Devuelve la estructura Descuentos con los compartimentos totales del nuevo locker
Vect_Lock nuevo_numcompTL(Vect_Lock, int);

//Precondición: Recibe la estructura Lockers
//Postcondición: Devuelve la estructura Descuentos con los compartimentos ocupados del nuevo locker
Vect_Lock nuevo_numcompOkupL(Vect_Lock, int);


#endif // LOCKERS_H_INCLUDED
