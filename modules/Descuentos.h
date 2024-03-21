#ifndef DESCUENTOS_H_INCLUDED
#define DESCUENTOS_H_INCLUDED

typedef struct {

    char Id_cod[11],                //Identificador del c�digo promocional
         Descrip[51],               //Descripci�n del c�digo promocional
         Tipo[8],                  //"codpro" (c�digo promocional) o "cheqreg" (cheque regalo)
         Estado[9],                 //Estado del cheque ("acctivo" o "inactivo")
         Aplicable[7];              //"todos" (si es aplicable a todos los productos) o "esizon" (si s�lo esaplicable a los gestionados por ESIZON)

    int  Importe;                   //Importe del descuento en euros

}Descuentos;

typedef struct {

    char Id_cod[11];                //Identificador del c�digo promocional

    int  Id_cliente,                //Identificador del cliente poseedor del descuento
         dia_asig,                  //D�a de la fecha de asignaci�n
         mes_asig,                  //Mes de la fecha de asignaci�n
         anio_asig,                 //A�o de la fecha de asignaci�n
         dia_cad,                   //D�a de la fecha de caducidad
         mes_cad,                   //Mes de la fecha de caducidad
         anio_cad,                  //A�o de la fecha de caducidad
         Estado;                    //El valor 0 indica que el cup�n no ha sido aplicado y el valor 1 que si lo ha sido

}DescuentosClientes;

//Se han separado los campos de las fechas para facilitar el manejo posterior con funciones

typedef struct{

    int tam;                        //Tama�o del vector
    Descuentos *Desc;               //Vector de tipo Descuentos

}Vect_Desc;

typedef struct{

    int tam;                        //Tama�o del vector
    DescuentosClientes *DescCli;    //Vector de tipo DescuentosClientes

}Vect_DescCli;


Vect_Desc Cargar_Descuentos();      //Cabecera
                                    //Precondici�n: El fichero Descuentos.txt debe estar relleno
                                    //Postcondici�n: Devuelve una estructura con el vector de estructuras Desc y almacena su tama�o

#endif // DESCUENTOS_H_INCLUDED
