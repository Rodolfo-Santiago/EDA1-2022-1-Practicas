// programa: blunnet-code
// fecha de inicio: 29/11/21 21:05
// última actualización: 8/12/21 13:05

// inclusión de archivos de cabecera:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// definición de estructuras:
struct Datos
{
	int cantidad_usuarios;
	char** usuarios;
	char** contrasenas;
	int** matriz;
	int mi_id;
	char usuario_actual[30];
	int cantidad_publicaciones;
};

struct Publicacion
{
    int tiempo[6];
    char publicacion[150];
   	struct Publicacion* next;
};

// declaración de prototipos de funciones:

// función principal:
	//recopilar datos:
void recopilar_datos(struct Datos**);
void obtener_cantidad_usuarios(int*);
void asignar_memoria_char(char***, int);
void asignar_memoria_int(int***, int);
void leer_listas(char**, char*, int);
void leer_matriz(int**, int);

	// menú principal:
void menu_principal(struct Datos*);
void imprimir_menu_principal();
		// crear cuenta:
void crear_cuenta(struct Datos*);
void crear_espacio_para_cuenta(struct Datos*);
void asignar_memoria_auxiliar(struct Datos*, struct Datos*);
void pasar_info_a_nueva_memoria(struct Datos*, struct Datos*);
void liberar_espacio_anterior(struct Datos*);

		// iniciar sesión:
void iniciar_sesion(struct Datos*);
void guardar_datos(struct Datos*);
			// menú de la cuenta:
void menu_cuenta(struct Datos*);
				// recopilar datos de publicaciones:
void recopilar_datos_publicaciones(struct Datos*, struct Publicacion**);
void obtener_cantidad_publicaciones(struct Datos*);
void formar_lista_publicaciones(struct Datos*, struct Publicacion**);
void abrir_archivo_publicaciones(struct Datos*, FILE**);
void formar_lista_ligada(struct Datos*, FILE**, struct Publicacion**);
void insertar_nodo_lista(struct Publicacion**, struct Publicacion*);

void imprimir_menu_cuenta();

				// menú de amistades:
void menu_amistades(struct Datos*);
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
void menu_publicaciones(struct Datos*, struct Publicacion**);
void imprimir_menu_publicaciones();
void ver_mis_publicaciones(struct Datos*, struct Publicacion*);
void ver_publicaciones_amigos(struct Datos*, struct Publicacion*);
void escribir_publicacion(struct Datos*, struct Publicacion**);
void eliminar_publicacion(struct Datos*, struct Publicacion**);
void guardar_cambios_publicaciones(struct Datos*, struct Publicacion*);

void eliminar_cuenta(struct Datos*);


// función principal:
int main()
{
	struct Datos* info;

	recopilar_datos(&info);

	menu_principal(info);

	return 0;
}

void recopilar_datos(struct Datos** info)
{
	*info = (struct Datos*) calloc(1, sizeof(struct Datos));

    obtener_cantidad_usuarios(&(**info).cantidad_usuarios);

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

	crear_espacio_para_cuenta(info);

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

void crear_espacio_para_cuenta(struct Datos* info)
{
	struct Datos auxiliares;

	// asignamos memoria a variables auxiliares
	asignar_memoria_auxiliar(info, &auxiliares);

	// copiamos las listas a una mas grande
	pasar_info_a_nueva_memoria(info, &auxiliares);

	// liberamos las listas anteriores chicas
	liberar_espacio_anterior(info);

	// pasamos los nuevos datos a la estructura original
	(*info).usuarios = auxiliares.usuarios;
	(*info).contrasenas = auxiliares.contrasenas;
	(*info).matriz = auxiliares.matriz;
}

void asignar_memoria_auxiliar(struct Datos* info, struct Datos* auxiliares)
{
	asignar_memoria_char(&(*auxiliares).usuarios, (*info).cantidad_usuarios + 1);
	asignar_memoria_char(&(*auxiliares).contrasenas, (*info).cantidad_usuarios + 1);
	asignar_memoria_int(&(*auxiliares).matriz, (*info).cantidad_usuarios + 1);
}

void pasar_info_a_nueva_memoria(struct Datos* info, struct Datos* aux)
{
	int i, j;

	for (i = 0; i < (*info).cantidad_usuarios; ++i)
	{
		strcpy(*((*aux).usuarios + i), *((*info).usuarios + i));
		strcpy(*((*aux).contrasenas + i), *((*info).contrasenas + i));
		for (j = 0; j < (*info).cantidad_usuarios; ++j)
		{
			*(*((*aux).matriz + i) + j) = *(*((*info).matriz + i) + j);
		}
	}
}

void liberar_espacio_anterior(struct Datos* info)
{
	int j;
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
	struct Publicacion* head;
	
	recopilar_datos_publicaciones(info, &head);

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
				menu_publicaciones(info, &head);
				break;
			case 3:
				guardar_cambios_publicaciones(info, head);
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

void recopilar_datos_publicaciones(struct Datos* info, struct Publicacion** head)
{
	*head = NULL;
	
	obtener_cantidad_publicaciones(info);

	if ((*info).cantidad_publicaciones > 0)
	{
		formar_lista_publicaciones(info, head);
	}
}

void obtener_cantidad_publicaciones(struct Datos* info)
{
    FILE* archivo_cant_pub;
	char nombre_archivo[strlen((*info).usuario_actual) + 27];

	strcpy(nombre_archivo, (*info).usuario_actual);
	strcat(nombre_archivo, "_cantidad_publicaciones.txt");

    archivo_cant_pub = fopen(nombre_archivo, "r");
    
    if (archivo_cant_pub == NULL) {(*info).cantidad_publicaciones = 0; return;}

    fscanf(archivo_cant_pub, "%d", &(*info).cantidad_publicaciones);
}

void formar_lista_publicaciones(struct Datos* info, struct Publicacion** head)
{
	FILE* archivo;
	
	abrir_archivo_publicaciones(info, &archivo);

	formar_lista_ligada(info, &archivo, head);

	fclose(archivo);
}

void abrir_archivo_publicaciones(struct Datos* info, FILE** archivo)
{
	char nombre_archivo[strlen((*info).usuario_actual) + 18];

	strcpy(nombre_archivo, (*info).usuario_actual);
	strcat(nombre_archivo, "_publicaciones.txt");

	*archivo = fopen(nombre_archivo, "r");
}

void formar_lista_ligada(struct Datos* info, FILE** archivo, struct Publicacion** head)
{
	char c;
	int i, j;
	struct Publicacion* publicacion_n;

	for (i = 0; i < (*info).cantidad_publicaciones; ++i)
	{
			publicacion_n = (struct Publicacion*) calloc(1, sizeof(struct Publicacion));

			for (j = 0; j < 6; ++j) fscanf(*archivo, "%d ", &(*publicacion_n).tiempo[j]);
			fgets((*publicacion_n).publicacion, 150, *archivo);

			insertar_nodo_lista(head, publicacion_n);
	}
}

void insertar_nodo_lista(struct Publicacion** head, struct Publicacion* publicacion_n)
{
	struct Publicacion* temporal;

	if (*head == NULL)
	{
		(*publicacion_n).next = NULL;
		*head = publicacion_n; 
	}
	else
	{ 
		temporal = *head;
		while ((*temporal).next != NULL) temporal = (*temporal).next;
		(*temporal).next = publicacion_n;
		(*publicacion_n).next = NULL;
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
				return;
			case 8:
				imprimir_matriz(info);
				break;
			default:
				puts("\nOpción inválida");
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

void ver_personas_quizas_conozca(struct Datos* info)
{
	int i, j, k;
	char ya_salieron[(*info).cantidad_usuarios * (*info).cantidad_usuarios][30];
	int posicion;
	int contador_amigos;
	int contador_amigos_amigos;

	for (i = 0; i < (*info).cantidad_usuarios; ++i)
	{
		if ((*info).matriz[(*info).mi_id][i] == 2) break;

        if (i == (*info).cantidad_usuarios - 1)
        {
            puts("\nNo sabemos qué personas puedas conocer porque aún no tienes amigos.");
            return;
        }
	}

	// checar si no tienes amigos o si tus amigos tienen más amigos que no sean amigos tuyos ni que les hayas mandado solicitud o que ellos te hayan mandado solicitud 
	for (i = 0, contador_amigos = 0; i < (*info).cantidad_usuarios; ++i)
	{ 
		if ((*info).matriz[(*info).mi_id][i] == 2)
		{
			contador_amigos += 1;

			for (j = 0, contador_amigos_amigos = 0; j < (*info).cantidad_usuarios; ++j)
			{
				if ((*info).matriz[i][j] == 2 && j != (*info).mi_id && (*info).matriz[(*info).mi_id][j] == 0 && (*info).matriz[j][(*info).mi_id] == 0)
				{
					contador_amigos_amigos += 1;
					break;
				}
			}
		}

		if (contador_amigos_amigos != 0) break;

		if (i == (*info).cantidad_usuarios - 1 && contador_amigos == 0)
        {
            puts("\nNo sabemos qué personas puedas conocer porque aún no tienes amigos.");
            return;
        }

		if (i == ((*info).cantidad_usuarios - 1) && contador_amigos_amigos == 0)
        {
            puts("\nNo sabemos qué personas puedas conocer porque tus amigos no tienen amigos aparte de ti.");
            return;
		}
	}


	puts("\nPersonas que tal vez conozcas");
	for (i = 0, posicion = 0; i < (*info).cantidad_usuarios; ++i)
	{ 
		if ((*info).matriz[(*info).mi_id][i] == 2)
		{
			for (j = 0; j < (*info).cantidad_usuarios; ++j)
			{
				if ((*info).matriz[i][j] == 2 && j != (*info).mi_id && (*info).matriz[(*info).mi_id][j] == 0 && (*info).matriz[j][(*info).mi_id] == 0)
				{
					for (k = 0; k < ((*info).cantidad_usuarios * (*info).cantidad_usuarios); ++k)
					{
						if (strcmp((*info).usuarios[j], ya_salieron[k]) == 0) break;
					}

					if (k == (*info).cantidad_usuarios * (*info).cantidad_usuarios)
					{
						printf("   %s (amigo de tu amigo %s)\n", (*info).usuarios[j], (*info).usuarios[i]);
						strcpy(ya_salieron[posicion], (*info).usuarios[j]);
						posicion += 1;
					}
				}
			}
		}
	}
}

void ver_grupos()
{}

void enviar_solicitud(struct Datos* info)
{
	int i;
	char nuevo_amigo[30];

	ver_personas_quizas_conozca(info);
	
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

// menú de publicaciones:
void menu_publicaciones(struct Datos* info, struct Publicacion** head)
{		
	int opcion;

	while (1)
	{
		imprimir_menu_publicaciones();

		scanf("%d", &opcion);

		switch (opcion)
		{
			case 1:
				ver_mis_publicaciones(info, *head);
				break;
			case 2:
				ver_publicaciones_amigos(info, *head);
				break;
			case 3:
				escribir_publicacion(info, head);
				break;
			case 4:
				eliminar_publicacion(info, head);
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

void ver_mis_publicaciones(struct Datos* info, struct Publicacion* head)
{
    int i, j;
	struct Publicacion* aux;

    if ((*info).cantidad_publicaciones == 0)
	{
		puts("\nEsta cuenta no tiene publicaciones aún.");
		return;
	}

	puts("\nMis publicaciones\n");
    
    for (i = 0, aux = head; i < (*info).cantidad_publicaciones; ++i, aux = (*aux).next)
    {
        printf("[%d/%d/%d a las %d:%d:%d hrs.]\n   %s", (*aux).tiempo[0], (*aux).tiempo[1], (*aux).tiempo[2], (*aux).tiempo[3], (*aux).tiempo[4], (*aux).tiempo[5] , (*aux).publicacion);
    }
}

void ver_publicaciones_amigos(struct Datos* info, struct Publicacion* head)
{
    /*int i;
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
		*/
}

void escribir_publicacion(struct Datos* info, struct Publicacion** head)
{
	int i;
	char c;
	struct Publicacion* nueva_publicacion;
	struct Publicacion* temporal;
	int hora_cdmx;

	// asignamos memoria a la nueva publicacion
	nueva_publicacion = (struct Publicacion*) calloc(1, sizeof(struct Publicacion));
	
	// metemos la publicacion en la lista hasta el final
	if (*head == NULL)
	{
		(*nueva_publicacion).next = NULL;
		*head = nueva_publicacion; 
	}
	else
	{ 
		temporal = *head;
		while ((*temporal).next != NULL) temporal = (*temporal).next;
		(*temporal).next = nueva_publicacion;
		(*nueva_publicacion).next = NULL;
	}
	
	
	// aumentamos el contador de publicaciones
	(*info).cantidad_publicaciones += 1;

	//(*nueva_publicacion).id = (*info).cantidad_publicaciones;

	// obtener la hora y la fecha
    time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    (*nueva_publicacion).tiempo[0] = timeinfo->tm_mday;
	(*nueva_publicacion).tiempo[1] = timeinfo->tm_mon + 1;
	(*nueva_publicacion).tiempo[2] = timeinfo->tm_year + 1900;
	
	hora_cdmx = timeinfo->tm_hour - 6;
	if (hora_cdmx < 0) hora_cdmx = 24 + hora_cdmx;

	(*nueva_publicacion).tiempo[3] = hora_cdmx;
	(*nueva_publicacion).tiempo[4] = timeinfo->tm_min;
	(*nueva_publicacion).tiempo[5] = timeinfo->tm_sec; 


    printf("\nEscribe tu publicación: ");

    while ((c = getchar()) != '\n' && c != EOF) ;
    
    for (i = 0; (c = getchar()) != '\n'; ++i)
		(*nueva_publicacion).publicacion[i] = c;
	(*nueva_publicacion).publicacion[i] = '\n';
}

void eliminar_publicacion(struct Datos* info, struct Publicacion** head)
{
    int i, j;
	int pub_borrada;
	struct Publicacion* aux;

    if ((*info).cantidad_publicaciones == 0)
	{
		puts("\nEsta cuenta no tiene publicaciones aún.");
		return;
	}

	puts("\nMis publicaciones\n");
    
    for (i = 0, aux = *head; i < (*info).cantidad_publicaciones; ++i, aux = (*aux).next)
    {
        printf("%d - [%d/%d/%d a las %d:%d:%d hrs.]\n   %s\n", i + 1, (*aux).tiempo[0], (*aux).tiempo[1], (*aux).tiempo[2], (*aux).tiempo[3], (*aux).tiempo[4], (*aux).tiempo[5] , (*aux).publicacion);
    }

	printf("\nEscriba la publicación que desea borrar: ");
	scanf("%d", &pub_borrada);

    while (pub_borrada > (*info).cantidad_publicaciones || pub_borrada <= 0)
    {
            printf("   Error: ese número de publicación no existe.\n");
            printf("Escriba la publicación que desea borrar: ");
            scanf("%d", &pub_borrada);
    }     
    
	struct Publicacion* auxiliar;
	struct Publicacion* temp1;

	temp1 = *head;
	auxiliar = temp1->next;
		
	if (pub_borrada == 1)
	{
		*head = auxiliar;
		free(temp1);
	}
	else if (pub_borrada > 1)
	{
		for (i = 2; i < pub_borrada; ++i)
		{
			auxiliar = auxiliar->next;
			temp1 = (*temp1).next;
		}
					
		temp1->next = auxiliar->next;
		free(auxiliar);
	}

	(*info).cantidad_publicaciones -= 1;
} 

void guardar_cambios_publicaciones(struct Datos* info, struct Publicacion* head)
{
	int i, j;
	char nombre_archivo_cants[strlen((*info).usuario_actual) + 27];
	char nombre_archivo[strlen((*info).usuario_actual) + 18];
	struct Publicacion* aux;
	FILE* archivo;
	
	strcpy(nombre_archivo_cants, (*info).usuario_actual);
	strcat(nombre_archivo_cants, "_cantidad_publicaciones.txt");

	archivo = fopen(nombre_archivo_cants, "w");
	fprintf(archivo, "%d", (*info).cantidad_publicaciones);
	fclose(archivo);

	strcpy(nombre_archivo, (*info).usuario_actual);
	strcat(nombre_archivo, "_publicaciones.txt");

	archivo = fopen(nombre_archivo, "w");
	

	aux = head;
	while (aux != NULL)
    {
        fprintf(archivo, "%d %d %d %d %d %d %s", (*aux).tiempo[0], (*aux).tiempo[1], (*aux).tiempo[2], (*aux).tiempo[3], (*aux).tiempo[4], (*aux).tiempo[5] , (*aux).publicacion);
		aux = aux->next;
    }
	
	fclose(archivo);
	
	
	struct Publicacion* temp1;
	struct Publicacion* temp2;

	if ((*info).cantidad_publicaciones == 0)
	{
		head = NULL;
		return;
	}
 
	temp1 = head;
	temp2 = (*head).next;

	while (temp2 != NULL)
	{
		free(temp1);
		temp1 = temp2;
		temp2 = (*temp1).next;
	}

	free(temp1);
	head =  NULL;
}


void eliminar_cuenta(struct Datos* info)
{
	int i, j;
	int x, y;
	char** usuarios_aux;
	char** contrasenas_aux;
	int** matriz_aux;
	char nombre_archivo_cants[strlen((*info).usuario_actual) + 27];
	char nombre_archivo[strlen((*info).usuario_actual) + 18];
	int opcion;


	printf("\n¿Estás seguro que deseas eliminar tu cuenta, %s? (0-sí 1-regresar): ", (*info).usuario_actual);
	scanf("%d", &opcion);
		
	if (opcion == 0)
	{
		// asignamos memoria a variables auxiliares
		asignar_memoria_char(&usuarios_aux, (*info).cantidad_usuarios - 1);
		asignar_memoria_char(&contrasenas_aux, (*info).cantidad_usuarios - 1);
		asignar_memoria_int(&matriz_aux, (*info).cantidad_usuarios - 1);

		// copiamos las listas a la pequeña
		for (i = 0, x = 0; i < (*info).cantidad_usuarios; ++i, ++x)
		{
			if (i == (*info).mi_id) {x = i - 1; continue;}
			strcpy(*(usuarios_aux + x), *((*info).usuarios + i));
			strcpy(*(contrasenas_aux + x), *((*info).contrasenas + i));

			for (j = 0, y = 0; j < (*info).cantidad_usuarios; ++j, ++y)
			{
				if (j == (*info).mi_id) {y = j - 1; continue;}
				*(*(matriz_aux + x) + y) = *(*((*info).matriz + i) + j);
			}
		}

		// liberamos las listas anteriores grandes
		for (j = 0; j < (*info).cantidad_usuarios; ++j)
		{
			free(*((*info).usuarios + j));
			free(*((*info).contrasenas + j));
			free(*((*info).matriz + j));
		}
		free((*info).usuarios);
		free((*info).contrasenas);
		free((*info).matriz);

		// pasamos los nuevos datos a la estructura
		(*info).usuarios = usuarios_aux;
		(*info).contrasenas = contrasenas_aux;
		(*info).matriz = matriz_aux;

		// disminuimos la cantidad de usuarios
		(*info).cantidad_usuarios -= 1;

		// eliminamos los archivos de publicaciones
		strcpy(nombre_archivo, (*info).usuario_actual);
		strcat(nombre_archivo, "_publicaciones.txt");
		remove(nombre_archivo);

		strcpy(nombre_archivo_cants, (*info).usuario_actual);
		strcat(nombre_archivo_cants, "_cantidad_publicaciones.txt");
		remove(nombre_archivo_cants);

		puts("\nLa cuenta ha sido eliminada exitosamente.");
	}
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
