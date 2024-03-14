#ifndef LOCKERS_H_INCLUDED
#define LOCKERS_H_INCLUDED

typedef struct{

    char Id_locker[11],                 //Identificador del Locker
         Localidad[21],                 //Poblaci�n donde se encuentra el Locker
         Provincia[21],                 //Provincia donde se encuentra el Locker
         Ubica[21];                     //Ubicaci�n del Locker

    int  Num_compT,                     //N�mero de compartimentos totales
         Num_compOkup;                  //N�mero de compartimentos ocupados actualmente

}Lockers;

typedef struct{

    char Id_locker[11],                 //Identificador del Locker
         Estado[8];                     //"ocupado" o "vac�o"

    int Num_comp,                       //N�mero de compartimento
        Cod_locker,                     //C�digo del Locker
        dia_okup,                       //Dia de la fecha de Ocupaci�n
        mes_okup,                       //Mes de la fecha de Ocupaci�n
        anio_okup,                      //A�o de la fecha de Ocupaci�n
        dia_cad,                        //Dia de la fecha de Caducidad
        mes_cad,                        //Mes de la fecha de Caducidad
        anio_cad;                       //A�o de la fecha de Caducidad

}CompartimentosLockers;

//Se han separado los campos de las fechas para facilitar el manejo posterior con funciones

typedef struct{

    int tam;                            //Tama�o del vector
    Lockers *Lock;                      //Vector de tipo Lockers

}Vect_Lock;

typedef struct{

    int tam;                            //Tama�o del vector
    CompartimentosLockers *CompLock;    //Vector de tipo CompartimentosLockers

}Vect_CompLock;

#endif // LOCKERS_H_INCLUDED
