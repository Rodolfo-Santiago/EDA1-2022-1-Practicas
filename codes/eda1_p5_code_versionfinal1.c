// Estructuras de datos y algoritmos I
// Práctica 5 -> EDL: Pila y cola
// Equipo 7

// Última actualización: 04/10/21 09:48


/*************Base de datos de canciones implementada en una EDL**************/

// Archivos de cabecera estándar
#include <stdio.h>
#include <stdlib.h>

// Estructuras de datos
struct Canciones      // Estructura para guardar las propiedades de una canción
{
	char nombre[100];
	char autor[50];
	char genero[50];
	float valoracion;
};

struct Nodo       // Estructura para modelar cada nodo de la pila que crearemos
{
	struct Canciones cancion;            // Estructura para almacenar los datos
	struct Nodo* siguiente; // Puntero para acceder a la dirección de otro nodo
};

//Variables globales
struct Nodo* cabecera;        // Puntero para acceder al primer nodo de la pila

// Funciones
void descripcion_programa( );            // Imprime la descripción del programa
void menu_acciones( );                           // Imprime el menú de acciones
void insertar_cancion( );      // Inserta una nueva canción en la base de datos
void insertar_datos_cancion(struct Nodo*);  // Inserta los datos de una canción
void borrar_cancion( );          // Borra la ultima canción de la base de datos
void imprimir_base_datos( ); // Imprime todas las canciones de la base de datos
void limpiar_bufer( );                                       // Limpia el búfer


// Funcion principal
int main( )
{
	int opcion;   // Variable de tipo entero para almacenar la opción que el usuario desea ejecutar
	
	cabecera = NULL;                   // Al iniciar el programa, el puntero cabecera apunta a NULL
	
	descripcion_programa( );                              // Se imprime la descripción del programa
	
	do       // Bucle que permite que el menú se siga imprimiendo hasta que el usuario decida salir
	{
		menu_acciones( );                                         // Se imprime el menú de acciones
		
		if (scanf("%d", &opcion) != 1)             // Se valida que el dato ingresado sea un entero
		{
			printf("\n\tError: El dato que ingreso es invalido.\n");
			return 0;
		}
		
		switch (opcion)    // switch que ejecuta diferentes tareas según el valor que tenga "opcion"
		{
			case 1:
				insertar_cancion( );                                // Se inserta una nueva canción
				break;
				
  	 		case 2:
   				borrar_cancion( );                        // Se elimina la última canción ingresada
   				break;
   				
  			case 3:
  				imprimir_base_datos( );                // Se imprimen todas la canciones ingresadas
  				break;
  				
  			case 4:
  				while(cabecera != NULL)          // Se eliminan todas las canciones usando un bucle
  				{
  					borrar_cancion( );
				}
				printf("\n\nBase de datos descartada y programa finalizado con exito.\n");
  				return 0;                                                // Se finaliza el programa
  				
  			default:
      			printf("\n\tOpcion invalida. Digite una de las cuatro opciones determinadas.\n\n");
      	}
	} while (1);
  
	return 0;
}



void descripcion_programa( )
{
	printf("BASE DE DATOS DE CANCIONES\n");
	printf("\nEn esta base de datos el usuario puede almacenar los datos de cualquier ");
	printf("cantidad de canciones. La base de datos esta vacia al comenzar el programa.");
	printf(" El usuario debe elegir que accion realizar dentro del siguiente menu.");
}



void menu_acciones( )
{
	printf("\n\nMenu de acciones:\n\t1. Registrar una nueva cancion en la base de datos");
	printf("\n\t2. Borrar la ultima cancion ingresada en la base de datos\n\t");
	printf("3. Imprimir todas las canciones almacenadas en la base de datos\n\t");
	printf("4. Salir de la base de datos\n\n\tElija la accion que desea ejecutar: ");
}



void insertar_cancion( )
{
	// Paso 1: crear un puntero y crear un nuevo nodo, y hacer que el puntero apunte hacia el nodo
	struct Nodo* temp;
	temp = (struct Nodo*) calloc(1, sizeof(struct Nodo));
	
	// Paso 2: llenar el nodo con los datos de la nueva canción
	insertar_datos_cancion(temp);
	
	// Paso 3: hacer que el puntero del nodo apunte hacia donde apuntaba la "cabecera"
	(*temp).siguiente = cabecera;  
	
	// Paso 4: hacer que el puntero "cabecera" apunte hacia nuestro nuevo nodo
	cabecera = temp;  
}



void insertar_datos_cancion(struct Nodo* temp)
{
	printf("\n\nREGISTRO DE UNA NUEVA CANCION\n");
	
	limpiar_bufer( );
	printf("\n\tIntroduzca el nombre de la cancion: ");
	fgets((*temp).cancion.nombre, 100, stdin);                       // Se lee el nombre la canción
	
	printf("\tIntroduzca el autor: ");
	fgets((*temp).cancion.autor, 50, stdin);                       // Se lee el autor de la canción
	
	printf("\tIntroduzca el genero: ");
    fgets((*temp).cancion.genero, 50, stdin);                     // Se lee el género de la canción
    
    printf("\tIntroduzca la calificacion (0.0-10.0): ");
    if (scanf("%f", &(*temp).cancion.valoracion) != 1)          // Se lee la valoración y se valida
	{
		printf("\nError: El dato que ingreso es invalido.\n");
		exit(-1);
	}
    
    // Se valida que se haya ingresado un número real entre 0 y 10
    while ((*temp).cancion.valoracion < 0.0 || (*temp).cancion.valoracion > 10.0)
    {
    	printf("\tCalificacion inválida. Ingrese otra calificacion: ");
    	scanf("%f", &(*temp).cancion.valoracion);
	}
}



void borrar_cancion( )
{
	if (cabecera == NULL)                                      // Si no hay datos, no se borra nada
	{
		printf("\n\tError: La base de datos se encuentra vacia. No hay canciones que borrar.\n");
		return;
	}
	
	// Paso 1: crear un puntero temporal y hacer que apunte hacia donde apunta la "cabecera"
	struct Nodo* temp;
	temp = cabecera;
	
	// Paso 2: hacer que la cabecera apunte hacia donde apunta el primer elemento de la pila
	cabecera = (*cabecera).siguiente;
	
	// Paso 3: liberar el puntero temporal y así borrar al elemento que queríamos eliminar
	free(temp);
}



void imprimir_base_datos( )
{
	struct Nodo* auxiliar;
	
	if (cabecera == NULL)                                    // Si no hay datos, no se imprime nada
	{
		printf("\n\tError: La base de datos se encuentra vacia. No hay canciones que mostrar.\n");
		return;
	}
	
	printf("\n\nIMPRESION DE LAS CANCIONES EN LA BASE DE DATOS\n");
	printf("\nLa lista de todas las canciones es:");
	
	auxiliar = cabecera;    // Se comienza a recorrer la pila desde el principio (desde "cabecera")
	while (auxiliar != NULL)                       // Se recorre toda la base de datos con un bucle
	{
		// Se imprime cada canción y sus respectivos datos
		printf("\n\tNombre: %s", (*auxiliar).cancion.nombre);
		printf("\tAutor: %s", (*auxiliar).cancion.autor);
		printf("\tGenero: %s", (*auxiliar).cancion.genero);
		printf("\tValoracion: %.1f\n", (*auxiliar).cancion.valoracion);
		
		auxiliar = (*auxiliar).siguiente;   // El puntero "auxiliar" apunta hacia el siguiente nodo
	}
}



void limpiar_bufer( )
{
	// Se leen caracteres del búfer hasta encontrar un salto de línea (se limpia así el búfer)
	while (fgetc(stdin) != '\n') ; 
}
