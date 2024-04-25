#ifndef ADMIN_H_
#define ADMIN_H_

#include "complementos.h"
#include "empresas.h"
#include "Productos.h"
#include "pedidos.h"

#include "Descuentos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <windows.h>

#define MAX_EMAIL 31            //Longitud de email + 1(terminador)
#define MAX_PSW 16              //Longitud de contrasena + 1(terminador)
#define MAX_NOM 21              //Longitud de nombre + 1(terminador)
#define MAX_LOC 21              //Longitud de localidad + 1(terminador)





///------------------------------- ADMINS -------------------------------///
    void inicsesion_admin(admin_prov_vect, int);
    void menuadmin(admin_prov_vect , int );
    void menuadmin_cliente();
    void menuadmin_admin(admin_prov_vect );
    void menuadmin_prov(admin_prov_vect );
    void menuadmin_prod();
    void menuadmin_cat();
    void menuadmin_ped();
    void menuadmin_transp();
    void menuadmin_desc();
    void menuadmin_devol();

    void listar_admin(admin_prov_vect );
    int buscar_admin(admin_prov_vect );

    admin_prov_vect agregar_admin(admin_prov_vect );
    admin_prov_vect eliminar_admin(admin_prov_vect , int );
    admin_prov_vect gestionar_admin (admin_prov_vect , int , int);

    admin_prov_vect admin_email(admin_prov_vect , int , int );
    admin_prov_vect admin_contr(admin_prov_vect , int , int );


#endif