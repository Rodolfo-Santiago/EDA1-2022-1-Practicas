// Estructuras de datos y algoritmos I
// Práctica 7 -> EDL: Lista simple y lista circular
// Equipo 7

// Última actualización: 18/10/21 23:19

/*****************Implementación de una lista ligada circular*****************/


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


#define   MAXIMO   30

#define   VIVO     1
#define   MUERTO   0


struct Elemento
{
	int estado;
	char nombre[MAXIMO];
	struct Elemento* siguiente;
};


int i;
int k;

struct Elemento* cabecera;

struct Elemento* temp1;
struct Elemento* temp2;

int numero_personas;


void agregar_persona( );
void quitar_persona( );
void ejecutar_juego( char* );
void mostrar_jugadores( );
void mostrar_jugadores_vivos( );
void resetear_juego( );

void descripcion_programa( );
void menu_acciones( );
void menu_acciones_2( );

void limpiar_bufer( );
void barra_de_carga( );
void leer_entero( int* );



int main( )
{
	int opcion;
	
	cabecera = NULL;
	temp1 = NULL;
	temp2 = NULL;
	
	numero_personas = 0;
	
	descripcion_programa( );
	
	while (1)
	{
		menu_acciones( );
		
		leer_entero( &opcion );
	
		switch (opcion)
		{
			case 1:
				agregar_persona( );
				break;
				
			case 2:
				quitar_persona( );
				break;
				
			case 3:
				if (cabecera == NULL)
				{
					printf("\n\nNo hay jugadores que mostrar.\n");
					break;
				}
				
				printf("\n\nEstos son los jugadores actualmente registrados:\n\n");
				
				mostrar_jugadores_vivos( );
				break;
				
			case 4:
				if (cabecera == NULL)
				{
					printf("\n\nNo se puede comenzar el juego sin tener jugadores registrados.\n");
					break;
				}
				
				if (cabecera == (*cabecera).siguiente)
				{
					printf("\n\nSolo hay una persona en el juego (%s). ", (*cabecera).nombre);
					printf("\nLe pedimos que agregue al menos a otra persona para poder jugar.");
	
					break;
				}
				
				menu_acciones_2( );
				
				leer_entero( &opcion );
				
				switch (opcion)
				{
					case 1:
						ejecutar_juego( "vivos y muertos" );
						break;
						
					case 2:
						ejecutar_juego( "solamente vivos" );
						break;
						
					default:
						printf("\nOpcion invalida. Vuelva a intentar.\n");
						break;
				}		
				break;
				
			case 5:
				printf("\nSeguro que desea salir:  0. Si \t1. No\nOpcion: ");
				if (leer_entero( &opcion ), opcion != 0) break;
				
				printf("\nJuego terminado.");
				return 0;
				
			default:
				printf("\nOpcion invalida. Vuelva a intentar.\n");
				break;
		}
		printf("\n");
	}
	
	return 0;	
}



void agregar_persona( )
{	
	int posicion_agregar;
	int var_auxiliar;
	
	
	temp1 = (struct Elemento*) calloc(1, sizeof(struct Elemento));
	
	(*temp1).estado = VIVO;
	
	printf("\n\nIngrese el nombre de la nueva persona: ");
	
	limpiar_bufer( );
	fgets((*temp1).nombre, MAXIMO, stdin);
	(*temp1).nombre[strlen((*temp1).nombre) - 1] = '\0'; 
	
	
	if (cabecera == NULL)
	{
		printf("\nAl ser la primera persona en el juego, %s sera colocada en la posicion 1.\n", (*temp1).nombre);
		
		cabecera = temp1;
		(*temp1).siguiente = cabecera;
		
		numero_personas++;
		i = -1;
		return;
	}
	
	printf("\nIngrese la posicion (1-%d) donde desee colocar a %s: ", numero_personas + 1, (*temp1).nombre);
	
	while (leer_entero( &var_auxiliar ), var_auxiliar < 1 || var_auxiliar > numero_personas + 1)
	{
		printf("No se puede colocar a la persona en esa posicion. Ingrese un valor valido.\n");
		printf("\nIngrese la posicion (1-%d) donde desee colocar a %s: ", numero_personas + 1, (*temp1).nombre);
	}
	
	if (var_auxiliar == 1) posicion_agregar = numero_personas + 1;
	else posicion_agregar = var_auxiliar;
	
	temp2 = cabecera;
	
	for (i = 1; i < posicion_agregar - 1; i++)
	{
		temp2 = (*temp2).siguiente;
	}
	
	(*temp1).siguiente = (*temp2).siguiente;
	
	(*temp2).siguiente = temp1;
	
	if (var_auxiliar == 1) cabecera = temp1;
	
	numero_personas++;
	i = -1;
}



void ejecutar_juego( char mostrar[15] )
{	
	int posicion_inicio;
	int numero_saltos;


	printf("\n\nEstos son los jugadores inscritos al juego:\n");
	mostrar_jugadores_vivos( );
	
	
	printf("\nIngrese la posicion (1-%d) donde empezaremos el juego: ", numero_personas);
	while (leer_entero( &posicion_inicio ), posicion_inicio < 1 || posicion_inicio > numero_personas)
	{
		printf("La posicion que ingreso no existe. Vuelva a intentar.\n");
		printf("\nIngrese la posicion (1-%d) donde empezaremos el juego: ", numero_personas);
	}
	
	
	printf("\nIngrese el numero de personas (1-%d) que \"saltaremos\" en cada eliminacion: ", numero_personas - 1);
	while (leer_entero( &numero_saltos ), numero_saltos < 1 || numero_saltos >= numero_personas)
	{
		printf("No se pueden saltar ese numero de personas en este juego. Vuelva a intentar.\n");
		printf("\nIngrese el numero de personas (1-%d) que \"saltaremos\" en cada eliminacion: ", numero_personas - 1);
	}
	
	
	temp1 = cabecera;
	for (i = 1; i < posicion_inicio; i++)
	{
		temp1 = (*temp1).siguiente;
	}
	
	printf("\n\nEstado inicial del juego (empezaremos a contar desde %s)\n", (*temp1).nombre);
	barra_de_carga( );
	i = -10;
	mostrar_jugadores_vivos( );
	
	
	for (i = 1; i < numero_personas; i++)
	{	
		k = 0;
		while (k < numero_saltos)
		{
			temp1 = (*temp1).siguiente;
			
			if ((*temp1).estado == VIVO) k++;
		}
		
		(*temp1).estado = MUERTO;
		
		printf("\nEliminiacion #%d:", i);
		barra_de_carga( );
		
		if (mostrar == "vivos y muertos") mostrar_jugadores( );
		else if (mostrar == "solamente vivos") mostrar_jugadores_vivos( );
	}
	
	temp1 = cabecera;
	while ((*temp1).estado != VIVO) temp1 = (*temp1).siguiente;
	
	printf("\n\t\t%s fue el ultimo sobreviviente y ha ganado el juego.", (*temp1).nombre);
	printf("\n\n\nEste juego ha terminado. Puede comenzar un nuevo juego con el siguiente menu:");
	
	resetear_juego( );
}



void mostrar_jugadores( )
{
	temp2 = cabecera;
	printf("\t\tPOSICION\t\tNOMBRE\t\t ESTADO\n");
	
	for (k = 1; k <= numero_personas; k++)
	{
		if ((*temp2).estado == MUERTO)
		{
			printf("\t%12d %25s      [Eliminado] X\n", k, (*temp2).nombre);
		}
		
		else if ((*temp2).estado == VIVO && i == numero_personas - 1)
		{
			printf("\t%12d %25s        [Ganador] !\n", k, (*temp2).nombre);
		}
		
		else if ((*temp2).estado == VIVO)
		{
			printf("\t%12d %25s       [En juego] +\n", k, (*temp2).nombre);
		}
		
		temp2 = (*temp2).siguiente;
	}
}



void mostrar_jugadores_vivos( )
{
	temp2 = cabecera;
	printf("\t\tPOSICION\t\tNOMBRE\t\t ESTADO\n");
	
	for (k = 1; k <= numero_personas; k++)
	{
		if ((*temp2).estado == VIVO && i == numero_personas - 1)
		{
			printf("\t%12d %25s        [Ganador] !\n", k, (*temp2).nombre);
		}
		
		else if ((*temp2).estado == VIVO)
		{
			printf("\t%12d %25s       [En juego] +\n", k, (*temp2).nombre);
		}
		
		temp2 = (*temp2).siguiente;
	}
}



void resetear_juego( )
{
	temp1 = cabecera;
	temp2 = cabecera;
	
	cabecera = NULL;
	
	for (i = 1; i < numero_personas; i++)
	{
		temp1 = (*temp1).siguiente;
		
		free(temp2);
		
		temp2 = temp1;
	}
	
	free(temp2);
	
	numero_personas = 0;
}



void quitar_persona( )
{
	int posicion_quitar;
	
	if (cabecera == NULL)
	{
		printf("\n\nNo hay personas que eliminar.\n");
		return;
	}
	
	if (cabecera == (*cabecera).siguiente)
	{
		printf("\n\n%s era la unica persona en el juego, por lo que ha sido eliminado.", (*cabecera).nombre);
		
		temp1 = cabecera;
		
		cabecera = NULL;
		
		free(temp1);
		
		numero_personas--;
		return;
	}

	printf("\n\nIngrese la posicion (1-%d) de la persona que desea sacar del juego: ", numero_personas);
	while (leer_entero( &posicion_quitar ), posicion_quitar < 1 || posicion_quitar > numero_personas)
	{
		printf("No se pueden saltar ese numero de personas en este juego. Vuelva a intentar.\n");
		printf("\nIngrese la posicion (1-%d) de la persona que desea sacar del juego: ", numero_personas);
	}
	
	if (posicion_quitar == 1) posicion_quitar = numero_personas + 1;
	
	temp1 = cabecera;
	for (i = 1; i < posicion_quitar - 1; i++)
	{
		temp1 = (*temp1).siguiente;
	}
	
	
	if ((*temp1).siguiente == cabecera)  cabecera = (*cabecera).siguiente;
	
	temp2 = (*temp1).siguiente;
	
	(*temp1).siguiente = (*temp2).siguiente;
	
	printf("\n%s ha sido sacado del juego.", (*temp2).nombre);
	
	free(temp2);
	
	numero_personas--;
}

	
	
void barra_de_carga( )	
{
	int j;
	
	int numero_rayas;
	int espacio_disponible = 48;
	
	int milisegundos_limite;
	int milisegundos;
	
	printf("\nCargando        [");
	
	numero_rayas = rand() % espacio_disponible;
	espacio_disponible -= numero_rayas;
	milisegundos_limite = rand() % 900;
	milisegundos = rand() % milisegundos_limite;
	
	for (j = 0; j < numero_rayas; j++)
	{
        Sleep(milisegundos);
		printf("|");
	}
	
	if (espacio_disponible == 0) return;
	
	numero_rayas = rand() % espacio_disponible;
	espacio_disponible -= numero_rayas;
	milisegundos_limite = rand() % 900;
	milisegundos = rand() % milisegundos_limite;
	
	for (j = 0; j < numero_rayas; j++)
	{
        Sleep(milisegundos);
		printf("|");
	}

	if (espacio_disponible == 0) return;
	
	numero_rayas = rand() % espacio_disponible;
	espacio_disponible -= numero_rayas;
	milisegundos_limite = rand() % 900;
	milisegundos = rand() % milisegundos_limite;
	
	for (j = 0; j < numero_rayas; j++)
	{
        Sleep(milisegundos);
		printf("|");
	}
	
	if (espacio_disponible == 0) return;
	
	numero_rayas = rand() % espacio_disponible;
	espacio_disponible -= numero_rayas;
	milisegundos_limite = rand() % 900;
	milisegundos = rand() % milisegundos_limite;;;;
	
	for (j = 0; j < numero_rayas; j++)
	{
        Sleep(milisegundos);
		printf("|");
	}

	if (espacio_disponible == 0) return;
	
	numero_rayas = rand() % espacio_disponible;
	espacio_disponible -= numero_rayas;
	milisegundos_limite = rand() % 900;
	milisegundos = rand() % milisegundos_limite;
	
	for (j = 0; j < numero_rayas; j++)
	{
        Sleep(milisegundos);
		printf("|");
	}
	
	if (espacio_disponible == 0) return;
	
	numero_rayas = rand() % espacio_disponible;
	espacio_disponible -= numero_rayas;
	milisegundos_limite = rand() % 900;
	milisegundos = rand() % milisegundos_limite;
	
	for (j = 0; j < numero_rayas; j++)
	{
        Sleep(milisegundos);
		printf("|");
	}
	
	printf("]\n");
}



void leer_entero( int* entero )
{
	if (scanf("%d", entero) != 1)
	{
		printf("\nEl tipo de dato que ingreso no es un numero entero. Reinicie el juego.");
		exit(-1);
	}
}



void limpiar_bufer( )
{
	while (fgetc(stdin) != '\n')
		;
}



void descripcion_programa( )
{
	printf("BIENVENIDO AL JUEGO \"EL ULTIMO SOBREVIVIENTE\"\n");
	printf("\n\tDado un conjunto de personas ordenadas de forma circular, el juego consiste en, ");
	printf("comenzando en una cierta posicion del circulo, eliminar personas cada cierto periodo");
	printf(" hasta que solo quede una persona en juego: la sobrevieviente. Tanto la cantidad de ");
	printf("personas en el juego, como sus nombres, la posicion de inicio y el periodo son ");
	printf("proporcionados por el usuario. El menu de acciones disponibles es el siguiente.");
}



void menu_acciones( )
{
	printf("\n\nMenu de acciones:\n\t1. Agregar a una nueva persona al juego.\n\t2. Sacar a una ");
	printf("persona del juego.\n\t3. Mostrar a las personas que ya estan formadas.\n\t4. Comenza");
	printf("r el juego.\n\t5. Salir del juego.\n\n\tElija la opcion que desea ejecutar: ");
}



void menu_acciones_2( )
{
	printf("\n\nAntes de comenzar el juego, seleccione la forma en que quiere visualizar a los");
	printf(" jugadores despues de cada etapa del juego:\n\t1. Ver personas eliminadas y en ");
	printf("juego.\n\t2. Ver solo personas en juego.\n\n\tElige la opcion que desea ejecutar: ");
}
