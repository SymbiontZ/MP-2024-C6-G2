#include<stdio.h>
#include<stdlib.h>

#include"empresas.h"
#include"useradmin.h"

void inicsesion_email();

int main(){
    clear();
    inicsesion_email();

    return 0;
}

void inicsesion_email(){
    admin_prov_vect adminprov = cargar_adminprov();
    transport_vect transport = cargar_transportistas();
    clients client = cargar_clientes();

    char cad_email[MAX_EMAIL], cad_pasw[MAX_PSW];
    int len, i;
    int verif = 0;                  //Comprueba existe email | 0 -> NO EXISTE / 1 -> EXISTE
    int pos;                         //Guarda la posicion relacionado con email

    //INTRDUCIR CORREO//
    printf("\nIntroduzca el correo: ");
    fflush(stdin);
    fgets(cad_email, MAX_EMAIL, stdin);
    len = strlen(cad_email);
    if (len > 0 && cad_email[len - 1] == '\n') { cad_email[len - 1] = '\0'; }

    //COMPROBAR EN USUARIOS
    for(i = 0; i < client.n_clients; i++){
        if(strcmp(cad_email, client.clients[i].email) == 0){
            pos = i;
            verif = 1;
            inicsesion_cliente(client ,pos);
        }
    }
    //COMPROBAR EN ADMIN/PROV
    for(i = 0; i < adminprov.tam; i++){
        if(strcmp(cad_email, adminprov.usuarios[i].email) == 0){
            pos = i;
            
            if(strcmp(adminprov.usuarios[pos].Perfil_usuario, "proveedor") == 0)             //ES PROV
                printf("prov");
                //inicsesion_prov(adminprov, pos);    
            else if(strcmp(adminprov.usuarios[pos].Perfil_usuario, "administrador") == 0)    //ES ADMIN
                inicsesion_admin(adminprov, pos);
            else{
                printf("No se pudo encontrar prefil de usuario");
                getchar();
                exit(EXIT_FAILURE);
            }
            verif = 1;
        }
    }
    //COMPROBAR EN TRANSPORTISTAS
    for(i = 0; i<transport.tam;i++){
        if(strcmp(cad_email, transport.transportistas[i].email) == 0){
            pos = i;
            //inicsesion_transport(transport, pos);
            verif = 1;
        }
    }

    //AGREGAR USUARIO//
    char opt = '0';
    if(verif == 0){
        printf("No se ha encontrado ese correo, desea registrarse como cliente[s/n]: ");
        scanf(" %c", &opt);
        while(opt != 's' && opt != 'n'){
            printf("Elija opcion valida [s/n]: ");
            scanf(" %c", &opt);
        }
        if(opt == 's')
            client = agregar_cliente(client);

        main();
    }

}