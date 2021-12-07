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
void recopilar_datos(struct Datos*);
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
	FILE* archivo;

	archivo = fopen("lista_usuarios.txt", "a");
	fclose(archivo);
	archivo = fopen("lista_contrasenas.txt", "a");
	fclose(archivo);
	archivo = fopen("matriz_adyacencia.txt", "a");
	fclose(archivo);

	struct Datos* info;

	recopilar_datos(info);
	
	menu_principal(info);

	return 0;
}

void recopilar_datos(struct Datos* info)
{
	info = (struct Datos*) calloc(1, sizeof(struct Datos));

    obtener_cantidad_usuarios(&(*info).cantidad_usuarios);

	if ((*info).cantidad_usuarios > 0)
	{
		asignar_memoria_char(&(*info).usuarios, (*info).cantidad_usuarios);
		asignar_memoria_char(&(*info).contrasenas, (*info).cantidad_usuarios);
		asignar_memoria_int(&(*info).matriz, (*info).cantidad_usuarios);

    	leer_listas((*info).usuarios, "lista_usuarios.txt", (*info).cantidad_usuarios);
		leer_listas((*info).contrasenas, "lista_contrasenas.txt", (*info).cantidad_usuarios);
    	leer_matriz((*info).matriz, (*info).cantidad_usuarios);
	}
}

void obtener_cantidad_usuarios(int* cantidad_usuarios)
{
    FILE* archivo_cantidad_usuarios;

	archivo_cantidad_usuarios = fopen("cantidad_usuarios.txt", "a");
	fclose(archivo_cantidad_usuarios);

    archivo_cantidad_usuarios = fopen("cantidad_usuarios.txt", "r");
    
    if (fgetc(archivo_cantidad_usuarios) == EOF) {*cantidad_usuarios = 0; return;}

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
		for (j = 0; i < cantidad_usuarios; ++j)
			fscanf(archivo, "%d", *(matriz + i) + j);
}

// menú principal:
void menu_principal(struct Datos* info)
{
    int opcion;
    
    puts("Bienvenido a Blunnet");
    
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
			free(*((*info).usuarios + j));
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
				break;
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


/*
void guardar_matriz()
{ 
	FILE* matriz_archivo;
		int i;
		int j;
		matriz_archivo = fopen(admatriz, "w");
	if (matriz_archivo == NULL)
	{
	printf("Error\n");
	}
	else
	{ 
	for(i = 0; i < CONTADOR_USUARIOS; i++)
	{
	for (j = 0; j < CONTADOR_USUARIOS; j++)
	{
					if (matriz[i][j] < 3)
	fprintf(matriz_archivo, "%i ", matriz[i][j]);
	}
				if (i == 0 && matriz[i][j - 1] == 4) continue;
	fprintf(matriz_archivo, "\n");
	}
	}
	fclose(matriz_archivo);
	}
}
*/

/*
// menú de publicaciones:
void menu_publicaciones()
{
int op;

    char nombre_archivo[strlen(USUARIO) + 4];
    FILE* archivo_usuario;
    strcpy(nombre_archivo, USUARIO);
    strcat(nombre_archivo, ".txt");
    
    archivo_usuario = fopen(nombre_archivo, "a");
    fclose(archivo_usuario);

    
    char nombre_archivo2[strlen(USUARIO) + 9];
    strcpy(nombre_archivo2, USUARIO);
    strcat(nombre_archivo2, "times.txt");
    
    archivo_usuario = fopen(nombre_archivo2, "a");
    fclose(archivo_usuario);
while (1)
{
imprimir_menu_publicaciones();
scanf("%d", &op);
switch (op)
{
case 1:
ver_mis_publicaciones(USUARIO);
break;
case 2:
ver_publicaciones_amigos();
break;
case 3:
escribir_publicacion();
break;

            case 4:
eliminar_publicacion();
break;
case 5:
   return;

            default:
                puts("\nOpción inválida");
                break;
}
}
}


void imprimir_menu_publicaciones()
{
    printf("\n1. Ver mis publicaciones\n2. Ver publicaciones de amigos\n3. Escribir publicación\n4. Eliminar publicación\n5. Regresar.\n   Opción: ");
}


void ver_mis_publicaciones(char* USUARIo)
{
    char publicacion[150];
    char hora[50];
char NombreArchivo[strlen(USUARIo) + 4];
    char times[strlen(USUARIo) + 9];
FILE *ptrfile;
    FILE* arch_times;

    strcpy(times, USUARIo);
    strcat(times, "times.txt");
    arch_times = fopen(times,"r");
    strcpy(NombreArchivo, USUARIo);
    strcat(NombreArchivo, ".txt");
ptrfile = fopen(NombreArchivo,"r");
    
    char c;
    if ((c = fgetc(ptrfile)) == EOF)
    {
        puts("\nEsta cuenta no tiene publicaciones registradas.\n");
        return;
    } 

    fgets(publicacion, 150, ptrfile);
    fgets(hora, 50, arch_times);
    printf("%s    %c%s\n", hora, c, publicacion);
    
    while (fgets(publicacion, 150, ptrfile))
    {
        fgets(hora, 50, arch_times);
        printf("%s    %s\n", hora, publicacion);
    }
    
    fclose(arch_times);
    fclose(ptrfile);
}


void ver_publicaciones_amigos()
{
    int i;
    int j;
    
char cadena[50];
CONTADOR_USUARIOS = 0;
    FILE *ar = fopen(usuarios, "r");
    while (fscanf(ar, "%s", cadena) == 1)
    {
    CONTADOR_USUARIOS++;
}
    fclose(ar);
    
FILE* ptr = fopen(admatriz, "r");
if (ptr == NULL)
{
printf("ERROR.. al abrir el archivo");
}
else
{ 
if (fgetc(ptr) == EOF)
{ 
for (i = 0; i < CONTADOR_USUARIOS; i++)
{
for (j = 0; j < CONTADOR_USUARIOS; j++)
{
matriz[i][j] = 0;
}
}
}
else
{ 
rewind(ptr);
for (i = 0; i < CONTADOR_USUARIOS; i++)
{
for (j = 0; j < CONTADOR_USUARIOS; j++)
{
fscanf(ptr, "%i", &matriz[i][j]);
}
}
}
}
fclose(ptr);

FILE* archivo = fopen(usuarios,"r");
if (archivo == NULL)
{
printf("Error en la apertura del archivo\n\n");
}
else
{ 
for (i = 0; i < CONTADOR_USUARIOS; i++)
{
fscanf(archivo, "%s", arrusuarios[i]);
}
}

    // publicaciones de amigos
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
            puts("\nNo tienes amigos aún.");
            return;
        }
}

    
    puts("\nPublicaciones de mis amigos:");
for (i = 0; i < CONTADOR_USUARIOS; i++)
{ 
if (matriz[mi_id][i] == 2)
{ 
printf("\n%s\n  ", arrusuarios[i]);
            ver_mis_publicaciones(arrusuarios[i]);
}
}
    
}


void escribir_publicacion()
{
char nombre_archivo[strlen(USUARIO) + 4];
    char times[strlen(USUARIO) + 9];
FILE* archivo;
    FILE* arch_times;

    strcpy(times, USUARIO);
    strcat(times, "times.txt");
    
    arch_times = fopen(times, "a");

    time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    fprintf(arch_times, "[%d/%d/%d a las %d:%d:%d hrs.]\n",timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour - 6, timeinfo->tm_min, timeinfo->tm_sec); 
    
    fclose(arch_times);


    strcpy(nombre_archivo, USUARIO);
    strcat(nombre_archivo, ".txt");
    
    archivo = fopen(nombre_archivo, "a");
    
    printf("\nEscribe tu publicación: ");

    char c;
    while ((c = getchar()) != '\n' && c != EOF) ;
    
    while ((c = getchar()) != '\n') fprintf(archivo, "%c", c);
fprintf(archivo, "\n"); 

    fclose(archivo);
}


void eliminar_publicacion()
{
    struct Publicacion
    {
   int id;
        char usuario[30];
        char hora[30];
      char publicacion[150];
   struct Publicacion* next;
    }
    
    struct Publicacion* head;
    struct Publicacion* auxiliar;
    struct Publicacion* temp;
    
int publicacion_borrada; 
char cadena[150];
    char hora[50];
FILE* ptrfile;


    char times[strlen(USUARIO) + 9];
FILE* arch_times = NULL;
    strcpy(times, USUARIO);
    strcat(times, "times.txt");
    
    arch_times = fopen(times, "r");
    
char NameArchivo[strlen(USUARIO) + 4];
    strcpy(NameArchivo, USUARIO);
    strcat(NameArchivo, ".txt");
ptrfile = fopen(NameArchivo,"r");
int id = 1;

    char c;
    if ((c = fgetc(ptrfile)) == EOF)
    {
        printf("Error: no hay publicaciones.");
        return;
    }
    
    rewind(ptrfile);
while (fgets(cadena, 150, ptrfile))
{
        fgets(hora, 50, arch_times);
       
printf("%d.- %s  %s", id, hora, cadena);
auxiliar = (struct Publicacion*) calloc(1, sizeof(struct Publicacion));
strcpy(auxiliar->publicacion, cadena);
        strcpy(auxiliar->hora, hora);
auxiliar->id = id;
if (head == NULL)
{
auxiliar->next = NULL;
head = auxiliar; 
}
        else
        { 
temp= head;
while (temp->next != NULL) temp=temp->next;
temp->next = auxiliar;
auxiliar->next = NULL;
}
        
id++;
}
fclose(ptrfile);
    fclose(arch_times);
printf("\nEscriba la publicación que desea borrar: ");
scanf("%d", &publicacion_borrada);

    while (publicacion_borrada >= id || publicacion_borrada <= 0)
    {
            printf("   Error: ese número de publicación no existe.\n");
            printf("Escriba la publicación que desea borrar: ");
            scanf("%d", &publicacion_borrada);
    }     
        
struct Publicacion* temp1 = head;
auxiliar = temp1->next;
    
if (publicacion_borrada == 1)
{
head = auxiliar;
free(temp1);
}
    else if (publicacion_borrada >= 1)
    {
while (auxiliar->id != publicacion_borrada)
{
auxiliar = auxiliar->next;
temp1 = (*temp1).next;
}
        
temp1->next = auxiliar->next;
free(auxiliar);
}
    
FILE* file;
    
    arch_times = fopen(times, "w");
file = fopen(NameArchivo, "w");
    
auxiliar = head;
while(auxiliar != NULL)
{
fprintf(file, "%s", auxiliar->publicacion);
        fprintf(arch_times, "%s", auxiliar->hora);
auxiliar = auxiliar->next;
}

fclose(arch_times);
fclose(file);
head =  NULL; 
} 

*/

void eliminar_cuenta(struct Datos* info)
{
	/*
	int opcion;
	int i, j;

	char archivo_usuario[strlen(USUARIO) + 4];
	char archivo_tiempos[strlen(USUARIO) + 9];

	printf("\n¿Estás seguro que deseas eliminar tu cuenta, %s? (0-sí  1-regresar): ", (*info).usuario_actual);
	scanf("%d", &opcion);
		
		
	if (opcion != 1)
	{

		for (i = 0; i < CONTADOR_USUARIOS; i++)
		{
			matriz[mi_id][i] = 4;
			matriz[i][mi_id] = 4;
		}
		
		strcpy(nombre_archivo, USUARIO);
		strcat(nombre_archivo, "_publicaciones.txt");
		
		remove(nombre_archivo);


		strcpy(times, USUARIO);
		strcat(times, "_tiempos.txt");
		
		remove(times);

		puts("\nLa cuenta ha sido eliminada exitosamente.\n");
	}
	*/
}
