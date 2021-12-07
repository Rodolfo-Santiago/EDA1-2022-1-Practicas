// programa: blunnet-code
// fecha de inicio: 29/11/21 21:05
// última actualización: 8/12/21 13:05

// archivos de cabecera:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// definición de constantes simbólicas:
#define MAX_LONG   30
#define LONG_PUBL 140

// definición de estructuras:
struct Datos
{
	int cantidad_usuarios;
	char** usuarios;
	char** contrasenas;
	int** matriz;
	int mi_id;
	char usuario_actual[30];
};

// prototipos de funciones:
	// main:
void recopilar_datos(struct Datos**);
void obtener_cantidad_usuarios(int*);
void asignar_memoria_char(char***, int);
void asignar_memoria_int(int***, int);
void leer_listas(char**, char*, int);
void leer_matriz(int**, int);

	// menú principal:
void menu_principal(struct Datos*);
void imprimir_menu_principal();
void crear_cuenta(struct Datos*);
void iniciar_sesion(struct Datos*);
void guardar_datos(struct Datos*);

	// menú de la cuenta:
void menu_cuenta(struct Datos*);
void imprimir_menu_cuenta();
void menu_amistades(struct Datos*);
void menu_publicaciones(struct Datos*);
void eliminar_cuenta(struct Datos*);
 
	// menú de amistades:
void imprimir_menu_amistades();
int ver_amigos(struct Datos*);
void ver_amigos_amigos(struct Datos*);
void ver_personas_quizas_conozca(struct Datos*);
void ver_grupos();
void enviar_solicitud(struct Datos*);
void aceptar_solicitud(struct Datos*);
int ver_solicitudes(struct Datos*);
void eliminar_amistad(struct Datos*);

void imprimir_matriz(struct Datos*);

	// menú de publicaciones:
/*
void imprimir_menu_publicaciones();
void ver_mis_publicaciones(char*);
void ver_publicaciones_amigos();
void escribir_publicacion();
void eliminar_publicacion();
*/

// función principal:
int main()
{
	struct Datos* info;

	recopilar_datos(&info);
	
	printf("info3 = %p\n", info);

	menu_principal(info);

	return 0;
}

void recopilar_datos(struct Datos** info)
{
	*info = (struct Datos*) calloc(1, sizeof(struct Datos));

    obtener_cantidad_usuarios(&(**info).cantidad_usuarios);
	printf("cant = %d\n", (**info).cantidad_usuarios);

	if ((**info).cantidad_usuarios > 0)
	{
		asignar_memoria_char(&(**info).usuarios, (**info).cantidad_usuarios);
		asignar_memoria_char(&(**info).contrasenas, (**info).cantidad_usuarios);
		asignar_memoria_int(&(**info).matriz, (**info).cantidad_usuarios);

    	leer_listas((**info).usuarios, "lista_usuarios.txt", (**info).cantidad_usuarios);
		leer_listas((**info).contrasenas, "lista_contrasenas.txt", (**info).cantidad_usuarios);
    	leer_matriz((**info).matriz, (**info).cantidad_usuarios);
	}
}

void obtener_cantidad_usuarios(int* cantidad_usuarios)
{
    FILE* archivo_cantidad_usuarios;

    archivo_cantidad_usuarios = fopen("cantidad_usuarios.txt", "r");
    
    if (archivo_cantidad_usuarios == NULL) {*cantidad_usuarios = 0; return;}

    fscanf(archivo_cantidad_usuarios, "%d", cantidad_usuarios);
}

void asignar_memoria_char(char*** arreglo, int cantidad_usuarios)
{
	int i;
	*arreglo = (char**) calloc(cantidad_usuarios, sizeof(char*));

	for (i = 0; i < cantidad_usuarios; ++i)
	{
		*(*arreglo + i) = (char*) calloc(30, sizeof(char));
	}
}

void asignar_memoria_int(int*** matriz, int cantidad_usuarios)
{
	int i;
	*matriz = (int**) calloc(cantidad_usuarios, sizeof(int*));

	for (i = 0; i < cantidad_usuarios; ++i)
	{
		*(*matriz + i) = (int*) calloc(cantidad_usuarios, sizeof(int));
	}
}

void leer_listas(char** lista, char* nombre_archivo, int cantidad_usuarios)
{
	int i;
	FILE* archivo;

	archivo = fopen(nombre_archivo, "r");

	for (i = 0; i < cantidad_usuarios; ++i)
		fscanf(archivo, "%s", *(lista + i));
}

void leer_matriz(int** matriz, int cantidad_usuarios)
{
	int i, j;
	FILE* archivo;

	archivo = fopen("matriz_adyacencia.txt", "r");

	for (i = 0; i < cantidad_usuarios; ++i)
		for (j = 0; j < cantidad_usuarios; ++j)
			fscanf(archivo, "%d", *(matriz + i) + j);
}

// menú principal:
void menu_principal(struct Datos* info)
{
    int opcion;
    
    puts("Bienvenido a Blunnet");
    printf("info4 = %p\n", info);
    while (1)
	{
		imprimir_menu_principal();
	
		scanf("%d", &opcion);

		switch (opcion)
		{
			case 1:
				crear_cuenta(info); 
				break;
			case 2:
				iniciar_sesion(info);
				break;
			case 3:
				guardar_datos(info);
				return;
			default:
				puts("\nOpción inválida");
				break;
		}
	}
}

void imprimir_menu_principal()
{
    printf("\n1. Crear una cuenta\n2. Iniciar sesión\n3. Salir de Blunnet\n   Opción: ");
}

void crear_cuenta(struct Datos* info)
{
    int i, j;
	char** usuarios_aux;
	char** contrasenas_aux;
	int** matriz_aux;

	// asignamos memoria a variables auxiliares
	asignar_memoria_char(&usuarios_aux, (*info).cantidad_usuarios + 1);
	asignar_memoria_char(&contrasenas_aux, (*info).cantidad_usuarios + 1);
	asignar_memoria_int(&matriz_aux, (*info).cantidad_usuarios + 1);

	// copiamos las listas a una mas grande
	for (i = 0; i < (*info).cantidad_usuarios; ++i)
	{
		strcpy(*(usuarios_aux + i), *((*info).usuarios + i));
		strcpy(*(contrasenas_aux + i), *((*info).contrasenas + i));
		for (j = 0; j < (*info).cantidad_usuarios; ++j)
		{
			*(*(matriz_aux + i) + j) = *(*((*info).matriz + i) + j);
		}
	}

	// liberamos las listas anteriores chicas
	if ((*info).cantidad_usuarios > 0)
	{
		for (j = 0; j < (*info).cantidad_usuarios; ++j)
		{
			free(*((*info).usuarios + j));
			free(*((*info).contrasenas + j));
			free(*((*info).matriz + j));
		}
		free((*info).usuarios);
		free((*info).contrasenas);
		free((*info).matriz);
	}

	// pasamos los nuevos datos a la estructura
	(*info).usuarios = usuarios_aux;
	(*info).contrasenas = contrasenas_aux;
	(*info).matriz = matriz_aux;

	// registramos al nuevo usuario
	puts("\nNueva cuenta");

	printf("\nIngrese un nombre de usuario para su nueva cuenta: ");
	scanf("%s", *((*info).usuarios + (*info).cantidad_usuarios));

	// comprobamos que no se repita el nombre de usuario
    if ((*info).cantidad_usuarios > 0)
    {
		for (i = 0; i < (*info).cantidad_usuarios; ++i)
		{
			if (strcmp(*((*info).usuarios + i), *((*info).usuarios + (*info).cantidad_usuarios)) == 0)
			{
				printf("   Error: ese nombre de usuario ya existe.\n");
				printf("\nIngrese un nombre de usuario para su nueva cuenta: ");
				scanf("%s", *((*info).usuarios + (*info).cantidad_usuarios));
				i = -1;
			}
		}
    }

	printf("Ingrese la contraseña para su nueva cuenta: ");
	scanf("%s", *((*info).contrasenas + (*info).cantidad_usuarios));

	(*info).cantidad_usuarios += 1;
}

void iniciar_sesion(struct Datos* info)
{
    int i;
	char usuario[30];
	char contrasena[30];
	// no hay nada
	if ((*info).cantidad_usuarios == 0)
	{
		puts("\nError: no hay cuentas registradas.");
		return;
	}

	puts("\nInicio de sesión");

	printf("\nIngrese su nombre de usuario: ");
	scanf("%s", usuario);
	// comparar usuarios
	for (i = 0; i < (*info).cantidad_usuarios; ++i)
	{
		if (strcmp(*((*info).usuarios + i), usuario) == 0)
		{
			(*info).mi_id = i;
			strcpy((*info).usuario_actual, usuario);
			break;
		}

		if (i == (*info).cantidad_usuarios - 1 && strcmp(*((*info).usuarios + i), usuario) != 0)
		{
			puts("   Error: no existe ninguna cuenta con ese nombre de usuario.");
			printf("Ingrese su nombre de usuario: ");
			scanf("%s", usuario);
			i = -1;
		}
	}

	printf("Ingrese su contraseña: ");
	scanf("%s", contrasena);
	// validar contraseña
	while (strcmp(*((*info).contrasenas + (*info).mi_id), contrasena) != 0)
	{
		puts("   Error: su contraseña es incorrecta.");
		printf("Ingrese su contraseña: ");
		scanf("%s", contrasena);
	}

	menu_cuenta(info);
}

// menú de la cuenta:
void menu_cuenta(struct Datos* info)
{ 
	int opcion;

	printf("\n¡Te damos la bienvenida a tu cuenta, %s!\n", (*info).usuario_actual);
		
	while(1)
	{
		imprimir_menu_cuenta();

		scanf("%d", &opcion);
				
		switch (opcion)
		{
			case 1:
				menu_amistades(info);
				break;
			case 2:
				//menu_publicaciones(info);
				break;
			case 3:
				return;
			case 4:
				eliminar_cuenta(info);
				return;
			default:
				printf("\n   Error: opción inválida.\n");
				break;
		} 
	} 
}

void imprimir_menu_cuenta()
{
    printf("\n1. Amistades\n2. Publicaciones\n3. Cerrar sesión\n4. Eliminar mi cuenta\n   Opción: ");
}

// menú de amistades:
void menu_amistades(struct Datos* info)
{ 
    int opcion;
    int i, j;

	while (1)
	{
		imprimir_menu_amistades();
				
		scanf("%d", &opcion);

		switch (opcion)
		{
			case 1:
				ver_amigos(info);
				break;
			case 2:
				ver_amigos_amigos(info);
				break;
			case 3:
				ver_grupos();
				break;
			case 4:
				enviar_solicitud(info);
				imprimir_matriz(info);
				break;
			case 5:
				aceptar_solicitud(info);
				imprimir_matriz(info);
				break;
			case 6: 
				eliminar_amistad(info);
				imprimir_matriz(info);
				break;
			case 7: 
				imprimir_matriz(info);
				return;
			case 8:
				imprimir_matriz(info);
				break;
			default:
				printf("Opción inválida\n");
				break;
		}
	}
}

void imprimir_menu_amistades()
{
    printf("\n1. Ver amigos\n2. Ver amigos de amigos\n3. Ver grupos\n4. Enviar solicitud\n5. Aceptar solicitud\n6. Eliminar amigo\n7. Regresar\n   Opción: ");
}

int ver_amigos(struct Datos* info)
{
    int i;
    
    for (i = 0; i < (*info).cantidad_usuarios; ++i)
	{
		if ((*info).matriz[(*info).mi_id][i] == 2) break;

        if (i == ((*info).cantidad_usuarios - 1) && (*info).matriz[(*info).mi_id][i] != 2)
        {
            puts("\nNo tienes amigos aún.");
            return 0;
        }
	}
    
    puts("\nMis amigos");

	for (i = 0; i < (*info).cantidad_usuarios; ++i)
	{ 
		if ((*info).matriz[(*info).mi_id][i] == 2)
		{
			printf("   %s\n", (*info).usuarios[i]);
		}
	}
	
	return 1;
}

void ver_amigos_amigos(struct Datos* info)
{ 
	int i, j;
	int contador;

	for (i = 0; i < (*info).cantidad_usuarios; ++i)
	{
		if ((*info).matriz[(*info).mi_id][i] == 2) break;

        if (i == ((*info).cantidad_usuarios - 1) && (*info).matriz[(*info).mi_id][i] != 2)
        {
            puts("\nNo tienes amigos aún.");
            return;
        }
	}
	
    puts("\nAmigos de mis amigos");

	for (i = 0; i < (*info).cantidad_usuarios; ++i)
	{ 
		if ((*info).matriz[(*info).mi_id][i] == 2)
		{
			printf("\nAmigos de %s\n", (*info).usuarios[i]);

			for (j = 0, contador = 0; j < (*info).cantidad_usuarios; ++j)
			{
				if ((*info).matriz[i][j] == 2 && j != (*info).mi_id)
				{
					printf("   %s\n", (*info).usuarios[j]);
					contador += 1;
				}
					
				if (j == ((*info).cantidad_usuarios - 1) && contador == 0)
				{
					puts("\n   No tiene más amigos aparte de ti.");   
				}
			}
		}
	}
}

/*
void ver_personas_quizas_conozca()
{
		int i;
		int j;
		int mi_id;
		int contador;
	for (i = 0; i < CONTADOR_USUARIOS; i++)
	{
	if (strcmp(USUARIO, arrusuarios[i]) == 0)
	{
	mi_id = i;
	break;
	}
	}

		for (i = 0, contador = 0; i < CONTADOR_USUARIOS; i++)
	{ 
	if (matriz[mi_id][i] != 2)
	{
				contador++;
			}
			
			if (i == (CONTADOR_USUARIOS - 1) && i == contador - 1)
			{
				puts("\nNo sabemos qué personas puedas conocer.");
				return;
			}
	}

		int k;
		char ya_salieron[CONTADOR_USUARIOS*CONTADOR_USUARIOS][50];
		int posicion = 0;
		int contador2 = 0;
		int contador3 = 0;
		puts("\nPersonas que tal vez conozcas:");
	for (i = 0; i < CONTADOR_USUARIOS; i++)
	{ 
	if (matriz[mi_id][i] == 2)
	{
				contador3++;
	for (j = 0, contador = 1; j < CONTADOR_USUARIOS; j++)
	{
	if ((matriz[i][j] == 2 && matriz[j][i] == 2) && j != mi_id && (matriz[mi_id][j] != 2 && matriz[j][mi_id] != 2))
					{
						for (k = 0; k < (CONTADOR_USUARIOS*CONTADOR_USUARIOS); k++)
						{
							if (strcmp(arrusuarios[j], ya_salieron[k]) == 0) break;
						}
						if (k >= CONTADOR_USUARIOS*CONTADOR_USUARIOS)
						{
							printf("   %s (amigo de tu amigo %s)\n", arrusuarios[j], arrusuarios[i]);
							strcpy(ya_salieron[posicion], arrusuarios[j]);
							posicion++;
						}
					}
						
					
					if (matriz[i][j] != 2 && j != mi_id)
		{
						contador++;
					}
			
					if (j == (CONTADOR_USUARIOS - 1) && j == contador - 1)
					{
						contador2++;
					}
	}
	}
	}
		if (contador2 == contador3)
		{
			printf("\n   No encontramos a alguien que tal vez conozcas.\n");
		}
}
*/

void ver_grupos()
{
    
}

void enviar_solicitud(struct Datos* info)
{
	int i;
	char nuevo_amigo[30];

	//ver_personas_quizas_conozca();
	
	printf("\nIngresa el usuario al que deseas mandarle una solucitud: ");
	scanf("%s", nuevo_amigo);

	while (strcmp((*info).usuario_actual, nuevo_amigo) == 0)
	{
		puts("   Error: no puedes enviar una solicitud a tu misma cuenta.");
		printf("Ingresa el usuario al que deseas mandarle una solucitud: ");
		scanf("%s", nuevo_amigo);
	}

	for (i = 0; i < (*info).cantidad_usuarios; ++i)
	{ 
		if (strcmp((*info).usuarios[i], nuevo_amigo) == 0)
		{
			if ((*info).matriz[i][(*info).mi_id] == 1)
			{
				printf("   Error: Ya le enviaste antes una solicitud a %s.\n", (*info).usuarios[i]);
				break;
			}
			else if ((*info).matriz[(*info).mi_id][i] == 1)
			{
				printf("   Error: %s ya te ha enviado una solicitud a ti, acéptala.\n", (*info).usuarios[i]);
				break;
			}
			else if ((*info).matriz[(*info).mi_id][i] == 2)
			{
				printf("   Error: %s ya tiene una amistad contigo.\n", (*info).usuarios[i]);
				break;
			}
			else
			{
				(*info).matriz[i][(*info).mi_id] = 1;
				break;
			}
		}
	}

	if (i == (*info).cantidad_usuarios)
	{
		puts("   Error: no tenemos a nadie registrado con ese nombre.");
	}
}

int ver_solicitudes(struct Datos* info)
{
	int i;

	for (i = 0; i < (*info).cantidad_usuarios; ++i)
	{
		if ((*info).matriz[(*info).mi_id][i] == 1) break;

        if (i == ((*info).cantidad_usuarios - 1) && (*info).matriz[(*info).mi_id][i] != 1)
        {
            puts("\nNo tienes solicitudes de amistad aún.");
            return 0;
        }
	}

	puts("\nSolicitudes de amistad recibidas");
	for (i = 0; i < (*info).cantidad_usuarios; ++i)
	{
		if ((*info).matriz[(*info).mi_id][i] == 1) printf("   %s\n",  (*info).usuarios[i]);
	}
	
	return 1;
}

void aceptar_solicitud(struct Datos* info)
{
	int i, j;
	char nuevo_amigo[30];

	if (ver_solicitudes(info) != 1) return;

	printf("\nIngrese el nombre de usuario de la presona que aceptará como amigo: ");
	scanf("%s", nuevo_amigo);

	for (i = 0; i < (*info).cantidad_usuarios; ++i)
	{ 
		if (strcmp((*info).usuarios[i], nuevo_amigo) == 0 && (*info).matriz[(*info).mi_id][i] == 1)
		{
			(*info).matriz[i][(*info).mi_id] = 2;
			(*info).matriz[(*info).mi_id][i] = 2;
			break;
		}
	}
	
	if (i == (*info).cantidad_usuarios)
	{
		puts("   Error: no tenemos ninguna solicitud procedente de esa cuenta.");
	}
}

void eliminar_amistad(struct Datos* info)
{
	int i, j;
	char amigo_eliminado[30];

	if (ver_amigos(info) != 1) return;
	
	printf("\nIngrese el nombre del amigo que desea eliminar: ");
	scanf("%s", amigo_eliminado);

	for (i = 0; i < (*info).cantidad_usuarios; ++i)
	{ 
		if (strcmp((*info).usuarios[i], amigo_eliminado) == 0 && (*info).matriz[i][(*info).mi_id] == 2)
		{
			(*info).matriz[i][(*info).mi_id] = 0;
			(*info).matriz[(*info).mi_id][i] = 0;
			break;
		}
	}

	if (i == (*info).cantidad_usuarios)
	{
		puts("   Error: el nombre de usuario que ingresó no era amigo suyo o no existe.");
	}
}


void imprimir_matriz(struct Datos* info)
{
	for (int i = 0; i < (*info).cantidad_usuarios; i++)
	{
		printf("       ");
		for (int j = 0; j < (*info).cantidad_usuarios; j++)
		{
			printf("%d ", (*info).matriz[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void eliminar_cuenta(struct Datos* info)
{
	
}

void guardar_datos(struct Datos* info)
{
	int i, j;
	FILE* archivo;

	archivo = fopen("cantidad_usuarios.txt", "w");
	fprintf(archivo, "%d", (*info).cantidad_usuarios);
	fclose(archivo);

	archivo = fopen("lista_usuarios.txt", "w");
	for (i = 0; i < (*info).cantidad_usuarios; ++i)
		fprintf(archivo, "%s\n", (*info).usuarios[i]);
	fclose(archivo);

	archivo = fopen("lista_contrasenas.txt", "w");
	for (i = 0; i < (*info).cantidad_usuarios; ++i)
		fprintf(archivo, "%s\n", (*info).contrasenas[i]);
	fclose(archivo);

	archivo = fopen("matriz_adyacencia.txt", "w");
	for (i = 0; i < (*info).cantidad_usuarios; ++i)
	{
		for (j = 0; j < (*info).cantidad_usuarios; ++j)
			fprintf(archivo, "%d ", (*info).matriz[i][j]);
		
		fprintf(archivo, "\n");
	}
	fclose(archivo);
}
