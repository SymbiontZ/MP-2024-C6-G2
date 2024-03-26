#include<stdio.h>
#include<stdlib.h>
#include"empresas.h"
#include"useradmin.h"

int main(){
    iniciar_sesion();

    return 0;
}

void iniciar_sesion_email(){
    admin_prov_vect adminprov = cargar_adminprov();
    transport_vect transport = cargar_transportistas();
    clients client = cargar_clientes();

    char cad_email[MAX_EMAIL], cad_pasw[MAX_PSW];
    int len, i;
    int mode = 0;               //Modo de inicio sesion: | 1 CLIENTE | 2 ADMIN/PROVEEDOR | 3 TRANSPORTISTA
    int id;                 //Guarda la posicion relacionado con email

    //INTRDUCIR CORREO//
    printf("\nIntroduzca el correo: ");

    fgets(cad_email, MAX_EMAIL, stdin);
    len = strlen(cad_email);
    if (len > 0 && cad_email[len - 1] == '\n') { cad_email[len - 1] = '\0'; }

    //COMPROBAR EN USUARIOS
    for(i = 0; i < client.n_clients; i++){
        if(strcmp(cad_email, client.clients[i].email) == 0){
            id = i;
            mode = 1;

        }
    }
    for(i = 0; i < adminprov.tam; i++){
        if(strcmp(cad_email, adminprov.usuarios[i].email) == 0){
            id = 1;
            mode = 2;
        }
    }
    for(i = 0; i<transport.transportistas[i].email;i++){
        if(strcmp(cad_email, transport.transportistas[i].email) == 0){
            id = i;
            mode = 3;
        }
    }

    //AGREGAR USUARIO//
    char opt = ''
    if(mode == 0){
        printf("No se ha encontrado ese correo, desea registrarse como cliente[s/n]");

    }

    

}

void iniciar_sesion_psw(int id, int mode){
    if(mode == 1){

    }else if(mode == 2){

    }else if(mode == 3){

    }else{
        printf("Ha ocurrido un error a la hora de iniciar sesion [ERROR CONTRASENAS]");
        getchar();
        exit(EXIT_FAILURE);
    }

}