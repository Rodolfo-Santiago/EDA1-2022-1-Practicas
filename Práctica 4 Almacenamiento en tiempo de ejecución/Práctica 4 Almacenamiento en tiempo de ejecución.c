#include <stdio.h>
#include <stdlib.h>

int filA;
int colA;
int filB;
int colB;

int** matrizA;
int** matrizB;

int i;
int j;

int** leerMatriz(int*, int*, int**);
void leerTamano(int*);
void imprimirMatriz(int**, int*, int*);
void multiplicacionMatrices();


int main()
{
	int opcion;
	
	while(1)
	{
		filB = 0;
	
		matrizA = leerMatriz(&filA, &colA, matrizA);
		matrizB = leerMatriz(&filB, &colB, matrizB);
	
		imprimirMatriz(matrizA, &filA, &colA);
		imprimirMatriz(matrizB, &filB, &colB);
	
		multiplicacionMatrices();
	
		printf("\nSi desea salir ingrese 0. Si no, cualquier otro entero.\n");
		scanf("%d", &opcion);
		
		if(opcion == 0)
		{
			free(matrizA);
			free(matrizB);
			return 0;
		}
	}
	
	return 0;
}


void leerTamano(int* dimension)
{
	scanf("%d", dimension);
	
	//Validación de datos
 	while(filB != 0 && filB != colA)  //Valida que el número de columnas de A sea el número de filas de B
  	{
    	printf("\tWarning: El número de columnas de A debe ser igual que el número de filas de B. Ingrese un valor válido.\n");
    	scanf("%d", &filB);
  	}
  	while(*dimension < 1)  //Valida que el entero ingresado sea positivo
  	{
    	printf("\tWarning: El valor debe ser un entero positivo.\n");
    	scanf("%d", dimension);
  	}
}


int** leerMatriz(int* filas, int* columnas, int** matrizprevia)
{
	leerTamano(filas);
	leerTamano(columnas);
	
	int** matriz = (int**)realloc(matrizprevia, (*filas)*sizeof(int*));
	for(i = 0; i < *filas; i ++)
	{
		*(matriz + i) = (int*)realloc(*(matriz + i), (*columnas)*sizeof(int));
	}

	for (i = 0; i < *filas; i ++)  //for que recorre las filas de la matriz
  	{
    	printf("\tIngrese los %d enteros de la fila %d:\n", *columnas, i + 1);
    	for (j = 0; j < *columnas; j ++)  //for que recorre las columnas de la matriz
    	{
      		printf("\t%d,%d: ", i + 1, j + 1);
      		scanf("\t\t%d", *(matriz + i) + j);  //Se almacena el valor en &matriz[i][j]
    	}
  	}
	
	return matriz;
}


void imprimirMatriz(int** matriz, int* filas, int* columnas)
{ 
  for (i = 0; i < *filas; i ++)  //for que recorre las filas de la matriz
  {
    printf("\t\t\t");
    for (j = 0; j < *columnas; j ++)  //for que recorre las columnas de la matriz
    {
      printf("%5d  ", *(*(matriz + i) + j));  //Se imprime matriz[i][j]. Nótese que *(*(matriz + i) + j) = matriz[i][j]
    }
    printf("\n");
  }
  printf("\n");
}


void multiplicacionMatrices()
{
  //Variables locales
  int r;  //Iterador
  int result;  //Variable que almacena cada elemento de la matriz producto
  
  puts("\n\tMatriz A x B:\n");
  
  for(i = 0; i < filA; i ++)  //for que recorre las filas de la matriz producto (filas de A)
  {
    printf("\t\t\t");
    for(j = 0; j < colB; j ++)  //for que recorre las columnas de la matriz producto (columnas de B)
    {
      for(result = 0, r = 0; r < colA; r ++)
      {
        result += (*(*(matrizA + i) + r)) * (*(*(matrizB + r) + j));  //Se almacena el resultado en result
      }
      printf("%5d  ", result);  //Se imprime result
    }
    printf("\n");
  }
  
  
}

