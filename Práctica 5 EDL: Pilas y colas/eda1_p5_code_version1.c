// Estructuras de datos y algoritmos I

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructuras
struct Canciones
{
	char nombre[40];
	char autor[20];
	char genero[20];
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
void borrar_cancion( );
void imprimir_base_datos( );
void insertar_datos_cancion(struct Nodo**);
void limpiar_buffer( );

// Funcion principal
int main()
{
	descripcion_programa( );
	
	cabecera = NULL;  // Se apunta hacia NULL al principio
	
	int option;  
	
	do
	{
		// Menú de opciones
		printf("\nMenu de acciones:\n\t1. Registrar una nueva cancion en la base de datos\n");
		printf("\t2. Borrar la última canción ingresada en la base de datos.\n");
		printf("\t3. Imprimir todas las canciones almacenadas en la base de datos\n\t");
		printf("4. Salir de la base de datos\n\n\tElija la acción que desea ejecutar: ");
  		  
		scanf("%d",&option);
		
		switch(option)
		{
			case 1:
				insertar_cancion( );
				break;
  	 		case 2:
   				borrar_cancion( );
   				break;
  			case 3:
  				imprimir_base_datos( ); // Buscamos una película por su ID
  				break;
  			case 4:
  				return 0;  // Salimos del programa
  			default:
      			printf("\nOpción inválida. Digite una de las cuatro opciones determinadas.\n");
      	}
	} while(1);  //Un bucle infinito
  
	
	return 0;
}


void descripcion_programa()
{
	printf("BASE DE DATOS DE CANCIONES\n");
	printf("\nEn esta base de datos el usuario puede almacenar los datos de cualquier cantidad de ");
	printf("canciones. La base de datos está vacía al comenzar el programa");
	printf("El usuario debe elegir qué acción realizar dentro del siguiente menú.\n");
}



void insertar_cancion()
{
	struct Nodo* temp = (struct Nodo*) calloc(1, sizeof(struct Nodo));
	
	insertar_datos_cancion(&temp);


	(*temp).siguiente = cabecera;  
	cabecera = temp;  
	
	printf("\t\t\t¡Los datos de la película fueron guardados exitosamente!\n");
}


void insertar_datos_cancion(struct Nodo** temp)
{
	limpiar_buffer();
	printf("\n\tIntroduzca el nombre de la cancion: ");
	fgets((**temp).cancion.nombre, 40, stdin);  // Se lee el nombre de la película
	
	// Se toman en cuenta los espacios dentro del nombre de la película
	if (((**temp).cancion.nombre > 0) && ((**temp).cancion.nombre[strlen((**temp).cancion.nombre) - 1] == '\n'))
    {
        (**temp).cancion.nombre[strlen((**temp).cancion.nombre) - 1] = '\0'; 
	}
	
	//limpiar_buffer();
	printf("\tIntroduzca el autor: ");
	fgets((**temp).cancion.autor, 20, stdin);  // Se lee el nombre de la película
	
	// Se toman en cuenta los espacios dentro del nombre de la película
	if (((**temp).cancion.autor > 0) && ((**temp).cancion.autor[strlen((**temp).cancion.autor) - 1] == '\n'))
    {
        (**temp).cancion.autor[strlen((**temp).cancion.autor) - 1] = '\0'; 
	}
	
	printf("\tIntroduzca el genero: ");
    scanf("%s", &(**temp).cancion.genero);  // Se lee el género
    
    printf("\tIntroduzca la calificación (0.0-10.0): ");
    scanf("%f", &(**temp).cancion.valoracion);  // Se lee la calificación
    while( (**temp).cancion.valoracion < 0.0 || (**temp).cancion.valoracion > 10.0 )  // Se verifica que se ingrese algo válido
    {
    	printf("\tCalificación inválida. Ingrese otra calificación: ");
    	scanf("%f", &(**temp).cancion.valoracion);
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
	
	cabecera = (*temp).siguiente;
	
	free(temp);
	
	printf("\t\t\tLa ultima cancion ingresada ha sido eliminada exitosamente.\n");
}


void imprimir_base_datos( )
{
	printf("\n\nIMPRESIÓN DE LAS CANCIONES EN LA BASE DE DATOS\n");
	
	struct Nodo* count = cabecera;
	
	if(count == NULL)  // Si no hay datos, no se imprime nada
	{
		printf("\n\tADVERTENCIA: La base de datos se encuentra vacía. No hay películas para mostrar.\n");
		return;
	}

	printf("\nLa lista de todas las canciones es:");
	
	while(count != NULL)  // Se recorre toda la lista
	{
		//Se imprime cada película y sus respectivos datos
		printf("\n\tNombre: %s", (*count).cancion.nombre);
		printf("\n\tAutor: %s", (*count).cancion.autor);
		printf("\n\tGenero: %s", (*count).cancion.genero);
		printf("\n\tValoracion: %.1f\n", (*count).cancion.valoracion);
		count = (*count).siguiente;  // Se itera la variable count
	}
	
	printf("\t\t\t¡Todas la películas fueron impresas exitosamente!\n");
}

void limpiar_buffer()
{
	int ch;
	while((ch = fgetc(stdin)) != '\n') ;
}
