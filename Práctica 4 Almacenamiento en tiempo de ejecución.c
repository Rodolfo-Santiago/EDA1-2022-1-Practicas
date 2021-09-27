#include <stdio.h>
#include <stdlib.h>

int** matriz_A;
int filas_A;
int columnas_A;

int** matriz_B;
int filas_B;
int columnas_B;

int cont_x;
int cont_y;


int** creacion_de_una_matriz( int**, int*, int* );
void lectura_de_filas_columnas( int* );
int** asignacion_de_espacio_en_memoria( int**, int*, int* );
void insercion_de_numeros_dentro_de_matriz( int**, int*, int* );

void impresion_de_matriz( int**, int*, int* );

void multiplicacion_de_matrices(  );
void liberar_contenido_de_filas_de_matriz( int**, int* );


int main()
{	
	int opcion;
	while(1)
	{
		filas_B = 0;
	
		matriz_A = creacion_de_una_matriz( matriz_A, &filas_A, &columnas_A );
		matriz_B = creacion_de_una_matriz( matriz_B, &filas_B, &columnas_B );
		
		impresion_de_matriz( matriz_A, &filas_A, &columnas_A );
		impresion_de_matriz( matriz_B, &filas_B, &columnas_B );
	
		multiplicacion_de_matrices(   );
	
		/////////////////////////////////////////////////////////////////////////
		
		printf("\nSi desea salir ingrese 0. Si no, cualquier otro entero.\n");
		scanf("%d", &opcion);
		if(opcion == 0)
		{
			free(matriz_A);
			free(matriz_B);
			return 0;
		}
	}
	
	return 0;
}


int** creacion_de_una_matriz( int** matriz_previa, int* filas, int* columnas )
{
	lectura_de_filas_columnas( filas );
	lectura_de_filas_columnas( columnas );
	
	int** matriz = asignacion_de_espacio_en_memoria( matriz_previa, filas, columnas );
	
	insercion_de_numeros_dentro_de_matriz( matriz, filas, columnas );
	
	return matriz;
}

void lectura_de_filas_columnas ( int* dimension )
{
	scanf ( "%d", dimension ) ;
	
	//Validación de datos
 	while (filas_B != 0 && filas_B != columnas_A)  //Valida que el número de columnas de A sea el número de filas de B
  	{
    	printf ("\tWarning: El número de columnas de A debe ser igual que el número de filas de B. Ingrese un valor válido.\n");
    	scanf ( "%d", &filas_B );
  	}
  	while (*dimension < 1)  //Valida que el entero ingresado sea positivo
  	{
    	printf("\tWarning: El valor debe ser un entero positivo.\n");
    	scanf("%d", dimension);
  	}
}

int** asignacion_de_espacio_en_memoria( int** matriz_previa, int* filas, int* columnas )
{
	int** matriz_nueva = (int**)realloc(matriz_previa, (*filas)*sizeof(int*));
	for(cont_x = 0; cont_x < *filas; cont_x ++)
	{
		*(matriz_nueva + cont_x) = (int*)calloc(*columnas, sizeof(int));
	}
	
	return matriz_nueva;
}

void insercion_de_numeros_dentro_de_matriz( int** matriz, int* filas, int* columnas )
{
	for (cont_x = 0; cont_x < *filas; cont_x ++)  //for que recorre las filas de la matriz
  	{
    	printf("\tIngrese los %d enteros de la fila %d:\n", *columnas, cont_x + 1);
    	for (cont_y = 0; cont_y < *columnas; cont_y ++)  //for que recorre las columnas de la matriz
    	{
      		printf("\t%d,%d: ", cont_x + 1, cont_y + 1);
      		scanf("\t\t%d", *(matriz + cont_x) + cont_y);  //Se almacena el valor en &matriz[i][j]
    	}
  	}
}



void impresion_de_matriz( int** matriz, int* filas, int* columnas )
{ 
  for (cont_x = 0; cont_x < *filas; cont_x ++)  //for que recorre las filas de la matriz
  {
    printf("\t\t\t");
    for (cont_y = 0; cont_y < *columnas; cont_y ++)  //for que recorre las columnas de la matriz
    {
      printf("%5d  ", *(*(matriz + cont_x) + cont_y));  //Se imprime matriz[i][j]. Nótese que *(*(matriz + i) + j) = matriz[i][j]
    }
    printf("\n");
  }
  printf("\n");
}



void multiplicacion_de_matrices(   )
{
  //Variables locales
  int cont_z;  //Iterador
  int resultado;  //Variable que almacena cada elemento de la matriz producto
  
  puts("\n\tMatriz A x B:\n");
  
  for(cont_x = 0; cont_x < filas_A; cont_x ++)  //for que recorre las filas de la matriz producto (filas de A)
  {
    printf("\t\t\t");
    for(cont_y = 0; cont_y < columnas_B; cont_y ++)  //for que recorre las columnas de la matriz producto (columnas de B)
    {
      for(resultado = 0, cont_z = 0; cont_z < columnas_A; cont_z ++)
      {
        resultado += (*(*(matriz_A + cont_x) + cont_z)) * (*(*(matriz_B + cont_z) + cont_y));
      }
      printf("%5d  ", resultado);  //Se imprime result
    }
    printf("\n");
  }
  
	liberar_contenido_de_filas_de_matriz( matriz_A, &filas_A );
	liberar_contenido_de_filas_de_matriz( matriz_B, &filas_B );
}

void liberar_contenido_de_filas_de_matriz( int** matriz, int* filas )
{
	for(cont_x = 0; cont_x < *filas; cont_x ++)
	{
		free(*( matriz + cont_x ));
	}
}