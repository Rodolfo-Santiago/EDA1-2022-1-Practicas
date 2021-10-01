// Estructuras de datos y algoritmos I
// Práctica 5 -> EDL: Pila y cola
// Equipo 7

/*     Base de datos de canciones implementada en una EDL     */


// Archivos de cabecera estándar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructuras de datos
struct Canciones
{
	char nombre[100];
	char autor[50];
	char genero[50];
	float valoracion;
};

struct Nodo
{
	struct Canciones cancion;
	struct Nodo* siguiente;
};

//Variables globales
struct Nodo* cabecera;

// Funciones
void descripcion_programa( );
void insertar_cancion( );
void insertar_datos_cancion(struct Nodo*);
void borrar_cancion( );
void imprimir_base_datos( );
void limpiar_buffer( );

// Funcion principal
int main()
{
	int option;
	cabecera = NULL;  // Se apunta hacia NULL al principio
	
	descripcion_programa( );
	
	do
	{
		// Menú de opciones
		printf("\nMenu de acciones:\n\t1. Registrar una nueva cancion en la base de datos\n");
		printf("\t2. Borrar la ultima cancion ingresada en la base de datos.\n");
		printf("\t3. Imprimir todas las canciones almacenadas en la base de datos\n\t");
		printf("4. Salir de la base de datos\n\n\tElija la accion que desea ejecutar: ");
  		  
		if (scanf("%d", &option) != 1)
		{
			printf("\nError. Debió haber ingresado un entero.\n");
			return 0;
		}
		
		switch(option)
		{
			case 1:
				insertar_cancion( );
				printf("\n\t\t\tLos datos de la cancion fueron guardados exitosamente!\n\n");
				break;
  	 		case 2:
   				borrar_cancion( );
   				printf("\n\t\t\tLa ultima cancion ingresada ha sido eliminada exitosamente.\n\n");
   				break;
  			case 3:
  				imprimir_base_datos( );
  				printf("\n\t\t\tTodas la películas fueron impresas exitosamente!\n\n");
  				break;
  			case 4:
  				while(cabecera != NULL)
  				{
  					borrar_cancion( );
				}
				free(cabecera);
  				return 0;  // Salimos del programa
  			default:
      			printf("\nOpcion invalida. Digite una de las cuatro opciones determinadas.\n");
      	}
	} while(1);
  
	
	return 0;
}


void descripcion_programa()
{
	printf("BASE DE DATOS DE CANCIONES\n");
	printf("\nEn esta base de datos el usuario puede almacenar los datos de cualquier cantidad de ");
	printf("canciones. La base de datos esta vacia al comenzar el programa. ");
	printf("El usuario debe elegir que accion realizar dentro del siguiente menu.\n");
}



void insertar_cancion( )
{
	struct Nodo* temp = (struct Nodo*) calloc(1, sizeof(struct Nodo));
	
	insertar_datos_cancion(temp);


	(*temp).siguiente = cabecera;  
	cabecera = temp;  
}



void insertar_datos_cancion(struct Nodo* temp)
{
	printf("\nREGISTRO DE UNA NUEVA CANCION\n");
	
	limpiar_buffer();
	printf("\n\tIntroduzca el nombre de la cancion: ");
	fgets((*temp).cancion.nombre, 100, stdin);
	
	printf("\tIntroduzca el autor: ");
	fgets((*temp).cancion.autor, 50, stdin);  // Se lee el autor de la canción
	
	printf("\tIntroduzca el genero: ");
    fgets((*temp).cancion.genero, 50, stdin);  // Se lee el autor de la canción
    
    printf("\tIntroduzca la calificación (0.0-10.0): ");
    scanf("%f", &(*temp).cancion.valoracion);
    
    while( (*temp).cancion.valoracion < 0.0 || (*temp).cancion.valoracion > 10.0 )  // Se verifica que se ingrese algo válido
    {
    	printf("\tCalificación inválida. Ingrese otra calificación: ");
    	scanf("%f", &(*temp).cancion.valoracion);
	}
}



void borrar_cancion( )
{
	if (cabecera == NULL)
	{
		printf("Error: base de datos vacía\n");
		return;
	}
	
	struct Nodo* temp = cabecera;
	
	cabecera = (*cabecera).siguiente;
	
	free(temp);
}



void imprimir_base_datos( )
{
	printf("\n\nIMPRESION DE LAS CANCIONES EN LA BASE DE DATOS\n");
	
	struct Nodo* count = cabecera;
	
	if(count == NULL)  // Si no hay datos, no se imprime nada
	{
		printf("\n\tADVERTENCIA: La base de datos se encuentra vacia. No hay canciones para mostrar.\n");
		return;
	}

	printf("\nLa lista de todas las canciones es:");
	
	while(count != NULL)  // Se recorre toda la lista
	{
		//Se imprime cada película y sus respectivos datos
		printf("\n\tNombre: %s", (*count).cancion.nombre);
		printf("\tAutor: %s", (*count).cancion.autor);
		printf("\tGenero: %s", (*count).cancion.genero);
		printf("\tValoracion: %.1f\n", (*count).cancion.valoracion);
		count = (*count).siguiente;  // Se itera la variable count
	}
}


void limpiar_buffer()
{
	while(fgetc(stdin) != '\n') ;
}
