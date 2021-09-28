// Estructuras de datos y algoritmos I
// Práctica 4 -> Almacenamiento en tiempo de ejecución
// Equipo 7

/*     Programa que multiplica dos matrices de tamaño variable      */


// Archivos de cabecera estándar
#include <stdio.h>
#include <stdlib.h>

// Variables globales
int** matriz_A;	   	  // Punteros dobles de tipo entero para acceder a
int** matriz_B;    	 // los diferentes elementos de las matrices A y B   

int filas_A;	    	   			  // Variables de tipo entero para 						
int columnas_A;			// almacenar los tamaños de las matrices A y B
int filas_B;
int columnas_B;

int cont_x;					  // Contadores usados en varias funciones
int cont_y;

char letra_A = 'A';	// Caracteres 'A' y 'B' usados en varias funciones
char letra_B = 'B';


// Funciones
void descripcion_programa( ); 										// Imprime la descripcion del programa

int** creacion_de_una_matriz(int**, int*, int*, char*); 						  // Crea una matriz nueva
void lectura_de_filas_columnas(int*); 							  // Lee el tamaño de las filas o columnas
int** asignacion_de_espacio_en_memoria(int**, int*, int*); // Le asigna a una matriz un espacio en memoria
void insercion_de_numeros_dentro_de_matriz(int**, int*, int*); 	   // Inserta números dentro de una matriz

void impresion_de_matriz(int**, int*, int*, char*);									 // Imprime una matriz

void multiplicacion_de_matrices( ); 						   	// Calcula la matriz producto y la imprime
void liberar_filas_de_matriz(int**, int*); 		  // Libera el espacio que ocupaba cada fila de una matriz


// Función principal
int main()
{	
	int opcion;
	
	descripcion_programa( ); // Se describe el objetivo del programa antes de ingresar al bucle
	
	while (1)
	{
		filas_B = 0; 				 // Se inicializan las filas de B en cero en cada iteración
		
		// Se crean las dos matrices
		matriz_A = creacion_de_una_matriz( matriz_A, &filas_A, &columnas_A, &letra_A );
		matriz_B = creacion_de_una_matriz( matriz_B, &filas_B, &columnas_B, &letra_B );
		
		// Se imprimen ambas matrices
		impresion_de_matriz( matriz_A, &filas_A, &columnas_A, &letra_A );
		impresion_de_matriz( matriz_B, &filas_B, &columnas_B, &letra_B );
		
		// Se calcula el producto matricial y se imprime
		multiplicacion_de_matrices( );
	
	
		// Se pregunta al usuario si desea salir o repetir el programa
		printf("\n\nSi desea salir ingrese 0. Si no, cualquier otro entero.\n");
		scanf("%d", &opcion);
		
		if (opcion == 0) 						   // Si opcion es cero se finaliza el programa
		{
			free(matriz_A); 			  // Se liberan los espacios en memoria de las matrices
			free(matriz_B);
			
			return 0; 												 
		}
	}
	
	return 0;
}


// Imprime la descripción del programa
void descripcion_programa( )
{
  printf("PROGRAMA PARA CALCULAR EL PRODUCTO DE DOS MATRICES\n\n");
  printf("Este programa recibe como entrada dos matrices A y B de tamaño m x n y n x p");
  printf(" respectivamente (donde m, n, p son enteros positivos) cuyos elementos son ");
  printf("numeros enteros. El programa multiplica ambas matrices A y B.  Y como datos de");
  printf(" salida se imprimen las matrices factores y la matriz producto.\n");
}



// Crea una matriz nueva
int** creacion_de_una_matriz( int** matriz_previa, int* filas, int* columnas, char* caracter )
{
	int** matriz; 				 // Se crea un puntero doble para apuntar hacia la nueva matriz
	
	printf("\n\nIngrese el tamaño de la matriz %c:\n", *caracter);
	
	printf("\tNumero de filas: ");
	lectura_de_filas_columnas( filas ); 					  // Se leen las filas de la matriz
	printf ("\tNumero de columnas: ");
	lectura_de_filas_columnas( columnas ); 				   // Se leen las columnas de la matriz
	
	// Redimensionamos la matriz previa para crear una matriz nueva
	matriz = asignacion_de_espacio_en_memoria( matriz_previa, filas, columnas ); 
	
	// Insertamos valores dentro de la matriz nueva
	insercion_de_numeros_dentro_de_matriz( matriz, filas, columnas );
	
	return matriz; 				  // Devolvemos la matriz nueva que creamos a la función "main"
}



// Lee el tamaño de las filas o columnas
void lectura_de_filas_columnas( int* dimension )
{
	scanf("%d", dimension);  						 // Se leen las filas o las columnas según sea el caso
	
	// Validación de datos
 	while (filas_B != 0 && filas_B != columnas_A)  // Las filas de B y las columnas de A deben ser iguales
  	{
    	printf("\tAdvertencia: las filas de B deben ser iguales que las columnas de A.\n");
    	scanf("%d", &filas_B); 					  // Se vuelve a solicitar el valor hasta que sea correcto
  	}
  	
  	while (*dimension < 1)  									  // El entero ingresado debe ser positivo
  	{
    	printf("\tAdvertencia: el valor debe ser un entero positivo.\n");
    	scanf("%d", dimension);					  // Se vuelve a solicitar el valor hasta que sea correcto
  	}
}



// Le asigna a una matriz un espacio en memoria
int** asignacion_de_espacio_en_memoria( int** matriz_previa, int* filas, int* columnas )
{
	int** matriz_nueva; 		  // Declaramos un nuevo puntero doble de tipo entero para la matriz nueva
	
	// Se redimensiona una matriz previa y se transmforma en una nueva matriz
	matriz_nueva = (int**) realloc(matriz_previa, (*filas)*sizeof(int*) );
	
	for (cont_x = 0; cont_x < *filas; cont_x++)  			   // Se recorren las filas de la nueva matriz
	{
		// Se le asigna un nuevo espacio en memoria a cada fila de la matriz nueva
		*(matriz_nueva + cont_x) = (int*) calloc(*columnas, sizeof(int) );
	}
	
	return matriz_nueva; 	       // Se retorna la matriz nueva hacia la función "creacion_de_una_matriz"
}



// Inserta números dentro de una matriz
void insercion_de_numeros_dentro_de_matriz( int** matriz, int* filas, int* columnas )
{
	printf("\n\tIngrese los %d elementos de la matriz fila por fila.\n", (*filas) * (*columnas) );
	
	for (cont_x = 0; cont_x < *filas; cont_x++)  					 // Se recorren las filas de la matriz
  	{
    	printf("\tIngrese los %d enteros de la fila %d:\n", *columnas, cont_x + 1);
    	for (cont_y = 0; cont_y < *columnas; cont_y++)  		  // Se recorren las columnas de la matriz
    	{
      		printf("\t%d,%d: ", cont_x + 1, cont_y + 1);
      		scanf("%d", *(matriz + cont_x) + cont_y );  	  // Se almacena un entero dentro de la matriz
    	}
  	}
}



// Imprime una matriz
void impresion_de_matriz( int** matriz, int* filas, int* columnas, char* caracter )
{ 
	printf("\n\tMatriz %c:\n", *caracter);
	
  	for (cont_x = 0; cont_x < *filas; cont_x++)     				 // Se recorren las filas de la matriz
  	{
    	printf("\t\t\t");
    	for (cont_y = 0; cont_y < *columnas; cont_y++)  		  // Se recorren las columnas de la matriz
    	{
      		printf("%5d  ", *(*(matriz + cont_x) + cont_y) );  		  // Se imprime matriz[cont_x][cont_y]
    	}
    	printf("\n");
 	}
  	printf("\n");
}



// Calcula la matriz producto y la imprime
void multiplicacion_de_matrices( )
{
  	int cont_z;  
  	int resultado;  						  // Variable que almacena cada elemento de la matriz producto
  
  	printf("\n\tMatriz A x B:\n");
  
  	for (cont_x = 0; cont_x < filas_A; cont_x++)  			// Se recorren las filas de la matriz producto
  	{
    	printf("\t\t\t");
    	
    	for (cont_y = 0; cont_y < columnas_B; cont_y++)  // Se recorren las columnas de la matriz producto
    	{
      		for (resultado = 0, cont_z = 0; cont_z < columnas_A; cont_z++)// Se recorren las columnas de B
      		{
      			// Se va almacenando el resultado de las multiplicaciones dentro de "resultado"
        		resultado += ( *(*(matriz_A + cont_x) + cont_z) ) * ( *(*(matriz_B + cont_z) + cont_y) );
      		}
      		
      		printf("%5d  ", resultado);  	 // Se imprime "resultado" cuando el tercer "for" ha concluido
    	}
    	
    	printf("\n");
  	}
  	
  	// Se libera espacio en memoria al finalizar
	liberar_filas_de_matriz( matriz_A, &filas_A ); 	  		  
	liberar_filas_de_matriz( matriz_B, &filas_B );
}



// Libera el espacio que ocupaba cada fila de una matriz
void liberar_filas_de_matriz( int** matriz, int* filas )
{
	for (cont_x = 0; cont_x < *filas; cont_x++) 					 // Se recorren las filas de la matriz
	{
		free( *( matriz + cont_x ) );  		  // Por cada fila liberamos el espacio de memoria que ocupaba
	}
}