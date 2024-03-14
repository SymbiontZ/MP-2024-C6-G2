#ifndef LOCKERS_H_INCLUDED
#define LOCKERS_H_INCLUDED

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

#endif // LOCKERS_H_INCLUDED
