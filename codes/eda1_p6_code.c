// Estructuras de datos y algoritmos I
// Práctica 6 -> EDL: Cola circular y cola doble
// Equipo 7

// Última actualización: 08/10/21 23:35


/**********Base de datos de canciones implementada en una cola doble**********/

// Archivos de cabecera estándar
#include <stdio.h>
#include <stdlib.h>


// Definición de constantes simbólicas
#define   MAXIMO     100       // Límite máximo para los arreglos que se usarán

#define   AL_INICIO  1           // Lugares donde insertaremos los nuevos nodos
#define   AL_FINAL   0


// Estructuras de datos
struct Propiedades    // Estructura para guardar las propiedades de una canción
{
	char nombre[MAXIMO];
	char autor[MAXIMO];
	char genero[MAXIMO];
	float valoracion;
};

struct Nodo       // Estructura para modelar cada nodo de la pila que crearemos
{
	struct Propiedades cancion;          // Estructura para almacenar los datos
	struct Nodo* siguiente;// Punteros para acceder a la dirección de otro nodo
	struct Nodo* anterior; 
};


//Variables globales
struct Nodo* inicio;   // Puntero para acceder al primer nodo añadido a la cola
struct Nodo* final;   // Puntero para acceder al último nodo añadido de la cola

struct Nodo* temp;       // Puntero auxiliar temporal usado en varias funciones


// Funciones
void descripcion_programa( );                                // Imprime la descripción del programa
void menu_acciones( );                                               // Imprime el menú de acciones

void insertar_cancion( struct Nodo**, int );       // Inserta una nueva canción en la base de datos
void insertar_datos_cancion();                                  // Inserta los datos de una canción

void borrar_cancion( struct Nodo**, int );           // Borra la ultima canción de la base de datos

void imprimir_base_datos( );                     // Imprime todas las canciones de la base de datos

void limpiar_bufer( );                                                           // Limpia el búfer


// Funcion principal
int main( )
{
	int opcion;   // Variable de tipo entero para almacenar la opción que el usuario desea ejecutar
	
	inicio = NULL;             // Al iniciar el programa, los puntero inicio y final apuntan a NULL
	final = NULL;
	
	descripcion_programa( );                              // Se imprime la descripción del programa
	
	do       // Bucle que permite que el menú se siga imprimiendo hasta que el usuario decida salir
	{
		menu_acciones( );                                         // Se imprime el menú de acciones
		
		if (scanf("%d", &opcion) != 1)             // Se valida que el dato ingresado sea un entero
		{
			printf("\n\tError: El dato ingresado es invalido.\n");
			exit(-1);
		}
		
		switch (opcion)    // switch que ejecuta diferentes tareas según el valor que tenga "opcion"
		{
			case 1:
				insertar_cancion( &inicio, AL_INICIO );                                
				break;
				
  	 		case 2:
   				insertar_cancion( &final, AL_FINAL );                        
   				break;
   				
  			case 3:
  				borrar_cancion( &inicio, AL_INICIO );                
  				break;
  				
  			case 4:
  				borrar_cancion( &final, AL_FINAL );              
  				break;
  			
  			case 5:
  				imprimir_base_datos( );                // Se imprimen todas la canciones ingresadas
  				break;
  			
  			case 6:
  				while (inicio != NULL)          // Se eliminan todas las canciones usando un bucle
  				{
  					borrar_cancion( &inicio, AL_INICIO );
				}
				
				printf("\n\nBase de datos descartada y programa finalizado con exito.\n");
  				return 0;                                                // Se finaliza el programa
  				
  			default:
      			printf("\n\tOpcion invalida. Digite una de las cuatro opciones determinadas.\n\n");
      	}
	} while (1);
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
	printf("\n\nMenu de acciones:\n\t1. Registrar una nueva cancion al inicio de la base de dato");
	printf("s\n\t2. Registrar una nueva cancion al final de la base de datos\n\t3. Borrar la ");
	printf("cancion situada al inicio de la base de datos\n\t4. Borrar la cancion situada al ");
	printf("final de la base de datos\n\t5. Imprimir todas las canciones almacenadas en la base");
	printf(" de datos\n\t6. Salir de la base de datos\n\n\tElija la accion que desea ejecutar: ");
}



void insertar_cancion( struct Nodo** puntero, int lugar )
{
	// crear un nuevo nodo, y hacer que un puntero auxiliar apunte hacia el nodo
	temp = (struct Nodo*) calloc(1, sizeof(struct Nodo));
	
	// llenar el nuevo nodo con los datos de la nueva canción
	insertar_datos_cancion( );
	
	if (inicio == NULL && final == NULL) // Si la base de datos está vacía...
	{
		inicio = temp;
		final = temp;
		return;
	}
	
	if (lugar == AL_INICIO) // Si queremos insertar el nodo al inicio...
	{
		(*inicio).anterior = temp;
		(*temp).siguiente = inicio;
	}
	
	else if (lugar == AL_FINAL) // Si queremos insertar el nodo al final...
	{
		(*final).siguiente = temp;
		(*temp).anterior = final;
	}
	
	*puntero = temp;
}



void insertar_datos_cancion()
{
	printf("\n\nREGISTRO DE UNA NUEVA CANCION\n");
	
	limpiar_bufer( );
	printf("\n\tIntroduzca el nombre de la cancion: ");
	fgets((*temp).cancion.nombre, MAXIMO, stdin);                    // Se lee el nombre la canción
	
	printf("\tIntroduzca el autor: ");
	fgets((*temp).cancion.autor, MAXIMO, stdin);                   // Se lee el autor de la canción
	
	printf("\tIntroduzca el genero: ");
    fgets((*temp).cancion.genero, MAXIMO, stdin);                 // Se lee el género de la canción
    
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



void borrar_cancion( struct Nodo** puntero, int lugar )
{
	if (inicio == NULL && final == NULL) // Si no hay datos, no se borra nada
	{
		printf("\n\tError: La base de datos se encuentra vacia. No hay canciones que borrar.\n");
		return;
	}
	
	if (inicio == final) // Si solamente queda un nodo en la cola
	{
		final = inicio = NULL;
		return;
	}
	
	temp = *puntero;
	
	if (lugar == AL_INICIO) // Si queremos borrar el nodo que está al principio
	{
		inicio = (*inicio).siguiente;
	}
	
	else if (lugar == AL_FINAL) // Si queremos borrar el nodo que está al final
	{
		final = (*final).anterior;
	}
	
	// liberar el puntero temporal y así borrar al elemento que queríamos eliminar
	free(temp);
}



void imprimir_base_datos( )
{
	if (inicio == NULL && final == NULL) // Si no hay datos, no se imprime nada
	{
		printf("\n\tError: La base de datos se encuentra vacia. No hay canciones que mostrar.\n");
		return;
	}
	
	printf("\n\nIMPRESION DE LAS CANCIONES EN LA BASE DE DATOS\n");
	printf("\nLa lista de todas las canciones es:");
	
	temp = inicio; // Se comienza a recorrer la pila desde el principio
	while (1) // Se crea un bucle infinito
	{
		// Se imprime cada canción y sus respectivos datos
		printf("\n\tNombre: %s", (*temp).cancion.nombre);
		printf("\tAutor: %s", (*temp).cancion.autor);
		printf("\tGenero: %s", (*temp).cancion.genero);
		printf("\tValoracion: %.1f\n", (*temp).cancion.valoracion);
		
		if (temp == final) break; // El bucle infinito se detiene si se cumple esta condición
		
		temp = (*temp).siguiente;   // El puntero "temp" apunta hacia el siguiente nodo
	}
}


void limpiar_bufer( )
{
	// Se leen caracteres del búfer hasta encontrar un salto de línea (se limpia así el búfer)
	while (fgetc(stdin) != '\n')
		; 
}
