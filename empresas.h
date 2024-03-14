#ifndef EMPRESAS_H
#define EMPRESAS_H

#define LONG_MAX_ADMINPROV 88;

// Estructura asociada a AdminProv.txt

typedef struct{
	int Id_empresa,					// Identificador de la empresa administradora o proveedora (Id_empresa), 4 dígitos.
		Perfil_usuario;				// Perfil del usuario (Perfil_usuario): «administrador» o «proveedor».
	char Nombre[21],				// Nombre de la empresa (Nombre), sería ESIZON si es administrador, 20 caracteres máximo.
		 email[31],					// Email (email), 30 caracteres máximo, será usado como nombre de usuario para el acceso a la plataforma.
		Contrasena[16];				// Contraseña para acceder al sistema (Contraseña), con 15 caracteres máximo.
} admin_prov;

// Estructura asociada a Transportistas.txt

typedef struct{
	int Id_transp;					// Identificador del transportista (Id_transp), 4 dígitos.
	char Nombre[21],				// Nombre del transportista (Nombre), 20 caracteres má
		 email[31],					// Email (email), 30 caracteres máximo, será usado como nombre de usuario para el acceso a la plataforma.
		 Contrasena[16],			// Contraseña para acceder al sistema (Contraseña), con 15 caracteres máximo.
		 Nom_Emp[21],				// Nombre de la empresa (Nombre), 20 caracteres máximo.
		 Ciudad[21];				// Ciudad de reparto (Ciudad), 20 caracteres máximo.
	
} transport;

// Estructura para el vector de estructuras de tipo admin_prov.

typedef struct{
	
	int tam;
	admin_prov *usuarios;
	
} admin_prov_vect;

// Estructura para el vector de estructuras de tipo transport.

typedef struct{
	
	int tam;
	transport *transportistas;
	
} transport_vect;

admin_prov_vect cargar_adminprov();
transport_vect cargar_transportistas();

int contar_admin_prov();


#endif