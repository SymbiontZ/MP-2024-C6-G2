#include<stdio.h>
#include<stdlib.h>

#include"empresas.h"
#include"admin.h"
#include"complementos.h"
#include"clientes.h"

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

    Sleep(1000);
    clear();
    titulo();

    char cad_email[MAX_EMAIL], cad_pasw[MAX_PSW];
    int i;
    int verif = 0;                  //Comprueba existe email | 0 -> NO EXISTE / 1 -> EXISTE
    int pos;                         //Guarda la posicion relacionado con email

    printf("--- INICIO DE SESION ---\n");
    //INTRDUCIR CORREO//
    printf("\nIntroduzca el correo: ");
    fgets(cad_email, MAX_EMAIL, stdin);
    terminador_cad(cad_email);

    //COMPROBAR EN USUARIOS
    for(i = 1; i < client.n_clients; i++){
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
                inicsesion_prov(adminprov, pos);    
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
    for(i = 1; i<transport.tam;i++){
        if(strcmp(cad_email, transport.transportistas[i].email) == 0){
            pos = i;
            inicsesion_transport(transport, pos);
            verif = 1;
        }
    }

    //AGREGAR USUARIO//
    char opt = '0';
    if(verif == 0){
        printf("No se ha encontrado ese correo, desea registrarse como cliente[s/n]: ");
        
        scanf(" %c", &opt);
        fflush(stdin);
        while(opt != 's' && opt != 'n'){
            printf("Elija opcion valida [s/n]: ");
            scanf(" %c", &opt);
            fflush(stdin);
        }
        if(opt == 's')
            client = agregar_cliente(client);

        main();
    }

}

//COMPILAR FLUJO PRINCIPAL VIA CMD
// >gcc -o maintest empresas.c useradmin.c Productos.c complementos.c main.c
// >.\maintest