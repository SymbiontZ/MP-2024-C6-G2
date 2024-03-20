#ifndef EMPRESAS_H
#define EMPRESAS_H

#define LONG_MAX_ADMINPROV 86
#define LONG_MAX_TRANSPORT 113

// Estructura asociada a cada usuario en AdminProv.txt

typedef struct{
	int Id_empresa,					// Identificador de la empresa administradora o proveedora (Id_empresa), 4 dígitos.
		Perfil_usuario;				// Perfil del usuario: 1 para administrador y 0 para proveedor.
	char Nombre[21],				// Nombre de la empresa (Nombre), sería ESIZON si es administrador, 20 caracteres máximo.
		 email[31],					// Email (email), 30 caracteres máximo, será usado como nombre de usuario para el acceso a la plataforma.
		Contrasena[16];				// Contraseña para acceder al sistema (Contraseña), con 15 caracteres máximo.
} admin_prov;

// Estructura asociada a cada transportista en Transportistas.txt

typedef struct{
	int Id_transp;					// Identificador del transportista (Id_transp), 4 dígitos.
	char Nombre[21],				// Nombre del transportista (Nombre), 20 caracteres má
		 email[31],					// Email (email), 30 caracteres máximo, será usado como nombre de usuario para el acceso a la plataforma.
		 Contrasena[16],			// Contraseña para acceder al sistema (Contraseña), con 15 caracteres máximo.
		 Nom_Emp[21],				// Nombre de la empresa (Nombre), 20 caracteres máximo.
		 Ciudad[21];				// Ciudad de reparto (Ciudad), 20 caracteres máximo.
	
} transport;

// Estructura para la lectura del fichero AdminProv.txt.

typedef struct{
	
	int tam;						// Tamaño del vector dinámico admin_prov *usuarios.
	admin_prov *usuarios;			// Vector de almacenamiento de administradores y proveedores.
	
} admin_prov_vect;					

// Estructura para la lectura del fichero Transportistas.txt.

typedef struct{
	
	int tam;						// Tamaño del vector dinámico transport *transportistas.
	transport *transportistas;		// Vector de almacenamiento de transportistas dados de alta.
	
} transport_vect;

//Precondición: No recibe nada.
//Postcondición: Devuelve una variable de tipo admin_prov_vect con la información de cada usuario (proveedor o administrador) almacenados en AdminProv.txt.
void cargar_adminprov();			// Carga en una estructura de tipo admin_prov_vect todos lo usuarios almacenados en AdminProv.txt

//Precondición: Recibe una estructura de tipo admin_prov con datos coherentes almacenados.
//Postcondición: Añade una nueva entrada en AdminProv.txt con los datos de la estructura recibida.
void agregar_adminprov(admin_prov usuario);

//Precondición: No recibe nada.
//Postcondición: Devuelve una variable de tipo trasnport_vect con la información de cada transportista almacenada en Transportistas.txt.
void cargar_transportistas();		// Carga en una estructura de tipo transport_vect todos lo usuarios almacenados en Transportistas.txt

//Precondición: Recibe una estructura de tipo transport con datos coherentes almacenados.
//Postcondición: Añade una nueva entrada en Transportistas.txt con los datos de la estructura recibida.
void agregar_transportista(transport transportista);

//Precondición: No recibe nada.
//Postcondición: Devuelve el numero de lineas que contiene AdminProv.txt.
int longitud_vector_adminprov();

//Precondición: No recibe nada.
//Postcondición: Devuelve el numero de lineas que contiene Transportistas.txt.
int longitud_vector_transportistas();

//Precondición: Recibe una cadena que necesite ser acortada (no nula, con algún carácter ' ' al final de ella).
//Postcondición: No devuelve nada, sustituye el primer carácter ' ' que encuentre en la cadena por el carácter terminador '\0'.
void acortar_cadena(char cad[]);	// Se emplea en casos en los que el espacio desperdiciado es mínimo.

#endif