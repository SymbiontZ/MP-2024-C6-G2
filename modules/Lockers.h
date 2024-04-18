#ifndef LOCKERS_H_INCLUDED
#define LOCKERS_H_INCLUDED

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
void Cargar_Lockers();


//Precondici�n: El fichero CompartimentosLockers.txt debe estar relleno
//Postcondici�n: Devuelve una estructura con el vector de estructuras DescCli y almacena su tama�o
void Cargar_CompartimentosLockers();

//Precondicion: Recibe una estructura de tipo Vect_Lock con datos coherentes almacenados.
//Postcondicion: Guarda en Lockers.txt los datos del vector de estructuras recibido
void Guardar_Lockers(Vect_Lock lockers);

//Precondicion: Recibe una estructura de tipo Vect_CompLock con datos coherentes almacenados.
//Postcondicion: Guarda en CompartimentosLockers.txt los datos del vector de estructuras recibido
void Guardar_CompartimentosLockers(Vect_CompLock compartimentoslockers);

//Precondición: Recibe la estructura Lockers
//Postcondición: Devuelve la estructura Lockers con un Locker nuevo
Vect_Lock Alta_Lockers(Vect_Lock);

///------------------------------- FUNCIONES INTERNAS DE Alta_Lockers -------------------------------///

//Precondición: Recibe la estructura Lockers
//Postcondición: Devuelve la estructura Descuentos con el id del nuevo locker
Vect_Lock nuevo_id(Vect_Lock, int);

//Precondición: Recibe la estructura Lockers
//Postcondición: Devuelve la estructura Descuentos con la localidad del nuevo locker
Vect_Lock nueva_localidad(Vect_Lock, int);

//Precondición: Recibe la estructura Lockers
//Postcondición: Devuelve la estructura Descuentos con la provincia del nuevo locker
Vect_Lock nueva_provincia(Vect_Lock, int);

//Precondición: Recibe la estructura Lockers
//Postcondición: Devuelve la estructura Descuentos con la ubicación del nuevo locker
Vect_Lock nueva_ubica(Vect_Lock, int);

//Precondición: Recibe la estructura Lockers
//Postcondición: Devuelve la estructura Descuentos con los compartimentos totales del nuevo locker
Vect_Lock nuevo_numcompT(Vect_Lock, int);

//Precondición: Recibe la estructura Lockers
//Postcondición: Devuelve la estructura Descuentos con los compartimentos ocupados del nuevo locker
Vect_Lock nuevo_numcompOkup(Vect_Lock, int);
#endif // LOCKERS_H_INCLUDED
