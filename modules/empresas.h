#ifndef EMPRESAS_H
#define EMPRESAS_H

#define LONG_MAX_ADMINPROV 86
#define LONG_MAX_TRANSPORT 113


// --------------- ESTRUCTURAS DE DATOS ---------------


// Estructura asociada a cada usuario en AdminProv.txt

typedef struct{
	int Id_empresa;					// Identificador de la empresa administradora o proveedora (Id_empresa), 4 dígitos.
	char Nombre[21],				// Nombre de la empresa (Nombre), sería ESIZON si es administrador, 20 caracteres máximo.
		 email[31],					// Email (email), 30 caracteres máximo, será usado como nombre de usuario para el acceso a la plataforma.
		Contrasena[16],				// Contraseña para acceder al sistema (Contraseña), con 15 caracteres máximo.
		Perfil_usuario[14];			// Tipo de usuario: administrador o proveedor.
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

// --------------- FUNCIONES DE INICIO DE SESION ---------------


 //Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
 //Postcondición: El usuario habrá iniciado sesión como proveedor en el sistema, o se habrá cerrado la sesión por fallar la contraseña muchas veces. No devuelve nada.
 void inicsesion_prov(admin_prov_vect provs, int pos);

 //Precondición: Recibe una estructura de tipo transport_vect (el vector de usuarios tipo transport), y la posición a utilizar en él.
 //Postcondición: El usuario habrá iniciado sesión como transportista en el sistema, o se habrá cerrado la sesión por fallar la contraseña muchas veces. No devuelve nada.
 void inicsesion_transport(transport_vect transports, int pos);


// --------------- MENUS DE PROVEEDOR Y TRANSPORTISTA ---------------


 //Precondición: Recibe una estructura de tipo admin_prov (en suma, recibe un proveedor).
 //Postcondición: El usuario habrá realizado las tareas necesarias de gestión en la plataforma (ver y modificar perfil, gestionar productos, pedidos). No devuelve nada.
 void menu_prov(admin_prov_vect provs, int pos);

 //Precondición: Recibe una estructura de tipo transport (en suma, recibe un transportista).
 //Postcondición: El usuario habrá realizado las tareas necesarias de gestión en la plataforma (ver y modificar perfil, repartos, retornos). No devuelve nada.
 void menu_transport(transport_vect transports, int pos);


// --------------- FUNCIONES PARA EL MENU DE PROVEEDOR ---------------


 //Precondición: Recibe una estructura de tipo admin_prov (en suma, recibe un usuario, en este caso proveedor).
 //Postcondición: El usuario habrá realizado las tareas necesarias de gestión de su cuenta en la plataforma. No devuelve nada.
 void ver_perfil(admin_prov_vect provs, int pos);

 //Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
 //Postcondición: El usuario habrá realizado las tareas de gestión de productos convenientes.
 void ver_productos(admin_prov_vect provs, int pos);



 void ver_pedidos(admin_prov_vect provs, int pos);

 //Precondición: Recibe un puntero a una estructura de admin_prov.
 //Postcondición: No devuelve nada. Se habrá cambiado el email del usuario guardado en el puntero.
 void cambiar_email(admin_prov_vect provs, int pos);

 //Precondición: Recibe un puntero a una estructura de admin_prov.
 //Postcondición: No devuelve nada. Se habrá cambiado la contraseña del usuario guardada en el puntero, o no.
 void cambiar_contrasena(admin_prov_vect provs, int pos);


// --------------- FUNCIONES PARA EL MENU DE TRANSPORTISTA ---------------


 //Precondición: Recibe una estructura de tipo transport (en suma, recibe un usuario, en este caso transportista).
 //Postcondición: El usuario habrá realizado las tareas necesarias de gestión de su cuenta en la plataforma. No devuelve nada.
 void ver_perfil_t(transport_vect transports, int pos);

 //Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov), y la posición a utilizar en él.
 //Postcondición: No devuelve nada. Se habrá cambiado el nombre del usuario guardado en el puntero.
 void cambiar_nombre_t(transport_vect transports, int pos);
 
 //Precondición: Recibe un puntero a una estructura de transport.
 //Postcondición: No devuelve nada. Se habrá cambiado el email del usuario guardado en el puntero.
 void cambiar_email_t(transport_vect transports, int pos);

 //Precondición: Recibe un puntero a una estructura de transport.
 //Postcondición: No devuelve nada. Se habrá cambiado la contraseña del usuario guardada en el puntero, o no.
 void cambiar_contrasena_t(transport_vect transports, int pos);


// --------------- FUNCIONES PARA LA GESTIÓN DE PROVEEDORES ---------------


//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios tipo adminprov) ya rellena.
//Postcondición: No devuelve nada. Se habrá mostrado por pantalla todos los AdminProvs del sistema, menos el superusuario.
void listar_prov(admin_prov_vect provs);

//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios proveedores / administradores) ya rellena.
//Postcondición: Devuelve la ID del usuario buscado, o -1 si se cancela la búsqueda.
int buscar_prov(admin_prov_vect provs);

//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios provvedores / administradores) ya rellena y dos enteros (posición a tratar y
//tipo de búsqueda.
//Postcondición: Devuelve la ID del usuario buscado, o -1 si se cancela la búsqueda.
int buscar_prov_tipo(admin_prov_vect provs, int pos, int tipo);

//Precondición: Recibe una estructura de tipo admin_prov_vect (el vector de usuarios provvedores / administradores) ya rellena.
//Postcondición: Devuelve la estructura de tipo admin_prov_vect con un nuevo proveedor dado de alta, y habiendo guardado el 
// cambio en AdminProv.txt
admin_prov_vect alta_prov(admin_prov_vect provs);

admin_prov_vect baja_prov(admin_prov_vect provs);

admin_prov_vect modificar_prov(admin_prov_vect provs, int pos);

// ###################### SUBFUNCIONES DE GESTIÓN DE PROVEEDORES ######################

admin_prov_vect prov_nombre(admin_prov_vect provs, int id);

admin_prov_vect prov_email(admin_prov_vect provs, int id);

admin_prov_vect prov_contra(admin_prov_vect provs, int id);


// --------------- FUNCIONES PARA LA GESTIÓN DE TRANSPORTISTAS ---------------


//Precondición: Recibe una estructura de tipo transport_vect (el vector de transportistas) ya rellena.
//Postcondición: No devuelve nada. Se habrá mostrado por pantalla todos los transportistas del sistema, menos el por defecto.
void listar_transport(transport_vect transports);

//Precondición: Recibe una estructura de tipo transport_vect (el vector de transportistas) ya rellena.
//Postcondición: Devuelve la ID del usuario buscado, o -1 si se cancela la búsqueda.
int buscar_transport(transport_vect transports);

//Precondición: Recibe una estructura de tipo transport_vect (el vector de transportistas) ya rellena y dos enteros (posición a tratar y
//tipo de búsqueda.
//Postcondición: Devuelve la ID del usuario buscado, o -1 si se cancela la búsqueda.
int buscar_transport_tipo(transport_vect transports, int pos, int tipo);

//Precondición: Recibe una estructura de tipo transport_vect (el vector de transportistas) ya rellena.
//Postcondición: Devuelve la estructura de tipo transport_vect con un nuevo transportista dado de alta, y habiendo guardado el 
// cambio en Transportistas.txt
transport_vect alta_transport(transport_vect transports);

transport_vect baja_transport(transport_vect transports);

transport_vect modificar_transport(transport_vect transports);

// ###################### SUBFUNCIONES DE GESTIÓN DE TRANSPORTISTAS ######################

transport_vect t_nombre(transport_vect transports, int id);

transport_vect t_email(transport_vect transports, int id);

transport_vect t_contra(transport_vect transports, int id);

transport_vect t_empresa(transport_vect transports, int id);

transport_vect t_ciudad(transport_vect transports, int id);

// --------------- FUNCIONES DE LECTURA DE FICHEROS ---------------


 //Precondición: No recibe nada.
 //Postcondición: Devuelve una variable de tipo admin_prov_vect con la información de cada usuario (proveedor o administrador) almacenados en AdminProv.txt.
 admin_prov_vect cargar_adminprov();			// Carga en una estructura de tipo admin_prov_vect todos lo usuarios almacenados en AdminProv.txt

 //Precondición: No recibe nada.
 //Postcondición: Devuelve una variable de tipo transport_vect con la información de cada transportista almacenada en Transportistas.txt.
 transport_vect cargar_transportistas();		// Carga en una estructura de tipo transport_vect todos lo usuarios almacenados en Transportistas.txt


// --------------- FUNCIONES DE VOLCADO EN FICHEROS ---------------


 //Precondición: Recibe una estructura de tipo transport con datos coherentes almacenados.
 //Postcondición: Guarda en Transportistas.txt los datos del vector de estructuras recibido.
 void guardar_transportista(transport_vect transportistas);

 //Precondición: Recibe una estructura de tipo admin_prov con datos coherentes almacenados.
 //Postcondición: Guarda en AdminProv.txt los datos del vector de estructuras recibido.
 void guardar_adminprov(admin_prov_vect usuarios);


// --------------- UTILIDADES VARIAS ---------------


 //Precondición: No recibe nada.
 //Postcondición: Devuelve el numero de lineas que contiene AdminProv.txt.
 int longitud_vector_adminprov();

 //Precondición: No recibe nada.
 //Postcondición: Devuelve el numero de lineas que contiene Transportistas.txt.
 int longitud_vector_transportistas();
 /*
 //Precondición: Recibe una cadena que necesite ser acortada (no nula, con algún carácter ' ' al final de ella).
 //Postcondición: No devuelve nada, sustituye el primer carácter ' ' que encuentre en la cadena por el carácter terminador '\0'.
 void acortar_cadena(char cad[]);	// Se emplea en casos en los que el espacio desperdiciado es mínimo.
 */
#endif