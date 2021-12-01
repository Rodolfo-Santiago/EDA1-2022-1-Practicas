// programa: blunnet_code
// fecha de inicio: 29/11/21 21:05
// última actualización: 9/12/21 12:03

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define p printf
#define s scanf


int CONTADOR_USUARIOS = 0;
int  matriz[1000][1000];
char arrusuarios[1000][50];
char USUARIO[50];

const char* admatriz = "adjacency_matrix.txt";
const char* usuarios = "users.txt";
const char* passwords = "passwords.txt";

// menú principal:
void imprimir_menu_principal();
void crear_cuenta();
void iniciar_sesion();


// menú de la cuenta:
void menu_cuenta();
void imprimir_menu_cuenta();
void menu_amistades();
void menu_publicaciones();
//void eliminar_cuenta();
 
 
// menú de amistades:
void imprimir_menu_amistades();
void ver_amigos();
void ver_amigos_amigos();
void ver_grupos();
void enviar_solicitud();
void aceptar_solicitud();
void ver_solicitudes();
void eliminar_amistad();

void guardar_matriz();

void imprimir_matriz();

/*
// menú de publicaciones:
void ver_mis_publicaciones();
void ver_publicaciones_amigos();
void escribir_publicacion();
void eliminar_publicacion();
*/

// menú principal:
int main ()
{
	int op;
	
	puts("Bienvenido a Blunnet");
	system("pause");
	system("cls");
	
	while (1)
	{
		imprimir_menu_principal();
	            
		if (s("%d", &op) != 1)
		{
	        p("\n Error..");
			exit(-1);
		} 
		
		switch (op)
		{
				case 1:
					crear_cuenta(); 
					break;
			
				case 2:
					iniciar_sesion();
					break;
				
				case 3:
					return 0;
					break;
					
				default:
					p("\n\a          Opcion invalida\n\n");
					break;
		   }
	}
	
	return 0;
}


void imprimir_menu_principal()
{
    puts("1. Crear cuenta\n2. Iniciar sesión\n3. Salir de Blunnet\nOpción: ");
}


void crear_cuenta()
{
	int i = 0;
	char caracter;
	char name[50], pas[30];
	char *NombreArchivo = NULL;
	FILE *ptrFile = NULL;
	
	FILE* a_usuarios = fopen(usuarios, "a");
	FILE* a_contrasenas = fopen(passwords, "a");
	
	if (a_usuarios == NULL || a_contrasenas == NULL )
	{
		perror("Error en la creacion del archivo\n\n");
	}
	else
	{
		p("Nombre:     ");
		s("%s", name);
		fprintf(a_usuarios,"%s\n", name);
		
		p("Password:   ");
	    scanf("%s", pas);
		fprintf(a_contrasenas, "%s\n", pas);	
    }
    
    fclose(a_usuarios);
    fclose(a_contrasenas);
    
    
    NombreArchivo = (char*) malloc (strlen(name) + 1);
    strcpy(NombreArchivo,name);
    strcat(NombreArchivo,".txt");
    
    if ((ptrFile = fopen(NombreArchivo,"wt")) != NULL)
    {
    	fclose(ptrFile);
	}else{
		perror("No se pudo crear el archivo");
	}
    
    free(NombreArchivo);
    NombreArchivo = NULL;
    
    for (i = 0; i < 50; i++)
    {
        name[i] = '\0';
    }
     
    fclose(ptrFile);
    


	FILE* auxptr = fopen(admatriz, "w");
	fclose(auxptr);
	
	FILE* ptr = fopen(admatriz, "r");

	if (ptr == NULL)
	{
		p("ERROR.. al abrir el archivo");	
	}
	else
	{		
		int i=0, j=0;
		
		if (fgetc(ptr) == '\0')
		{
			
			for ( i=0; i<CONTADOR_USUARIOS; i++)
			{
				for ( j=0; j<CONTADOR_USUARIOS; j++)
				{
					matriz[i][j] = 0;
				}
			}
			printf("si entro");
		}
		else
		{
			
			rewind(ptr);
			
			for ( i=0; i<CONTADOR_USUARIOS; i++)
			{
				for ( j=0; j<CONTADOR_USUARIOS; j++)
				{
					fscanf(ptr, "%i", &matriz[i][j]);
				}
			}
			printf("no entro");
		}
	}
	
	CONTADOR_USUARIOS++;
	for (i = 0; i < CONTADOR_USUARIOS; i++)
	{
		matriz[CONTADOR_USUARIOS][i] = 0;
		matriz[i][CONTADOR_USUARIOS] = 0;
	}

	fclose(ptr);
	guardar_matriz();
}


void iniciar_sesion()
{
	int contador = 0, i=0;
	char nam[30];
	char pa[30];	
	char caracter;
	
	FILE *archivo  = fopen(usuarios,"r");
	FILE *archivo1 = fopen(passwords,"r");

    p("User:         ");
	s("%s", nam); 
	
	p("Password:     ");
	scanf("%s", pa);
	
	if(archivo == NULL || archivo1 == NULL)
	{
		perror("Error en la apertura del archivo\n\n");
		system("pause");
	}
	else
	{
		char Usuario_inicio[30];	
		char Password_inicio[30];
			
		while (feof(archivo) == 0)
		{
			fscanf(archivo,"%s", Usuario_inicio);	
			fscanf(archivo1,"%s", Password_inicio);

			if (strcmp(Usuario_inicio,nam)  == 0 && strcmp(Password_inicio,pa) == 0 && contador == 0)
			{	
				strcpy(USUARIO, nam);
				menu_cuenta();
				contador++;
		    }		
		}
		
		if (contador == 0)
		{
			p("  No se encontraron coincidencias.\n\n");
		}
		
		fclose(archivo);
		fclose(archivo1);
	}		
}


void ver_usuarios()
{	
	FILE *archivo = fopen(usuarios, "r");
	
	if(archivo == NULL)
	{
		perror("Error en la apertura del archivo\n\n");
		system("pause");
		
	}
	else
	{	
		fseek (archivo, 0, SEEK_END);
		int num_caracteres = ftell(archivo);
		rewind(archivo);
	
		char *cadena = (char*) calloc (sizeof (char),num_caracteres);
		
		if (cadena == NULL)
		{
			perror("Error en reserva de memoria");
			system("pause");		
		}else {
			
			int num_elementos_leidos = fread(cadena, sizeof(char),num_caracteres,archivo);
			
			p("Personas registradas:");
			p("%s\n",cadena);
			
			free(cadena);
			fclose(archivo);
		}
	}
}


void menu_cuenta()
{	
	int op;
	int a = 1, Menu;
	 
	while(a == 1)
	{
		imprimir_menu_cuenta();
		
		if(s("%d", &op) != 1)
		{
		    p("\n Error..");
			exit(-1);
		}
		
		switch (op)
		{
			case 1:
				menu_amistades();
				break;
				
			case 2:
				//menu_publicaciones();
				break;
				
			case 3:
				a++;
				break;
			
			case 4:
			    //eliminar_cuenta();
			    break;
			    
			default:
				p("\n\a          Opcion invalida\n\n");
				break;
		} 
	}			
}


void imprimir_menu_cuenta()
{
    puts("1. Amistades\n2. Publicaciones\n3. Cerrar sesión\n4. Eliminar mi cuenta\nOpción: ");
}


// menú de amistades:
void menu_amistades()
{	
    int a = 1;
    int op;
    int i;
    int j;
    
	char cadena[50];
	CONTADOR_USUARIOS = 0;
	
    FILE *ar  = fopen(usuarios,"r");
    while ( fscanf(ar,"%s", cadena) == 1 )
    {
    	CONTADOR_USUARIOS++;
	}
    fclose(ar);
    
	FILE* ptr = fopen(admatriz, "r");
	
	if (ptr == NULL)
	{
		p("ERROR.. al abrir el archivo");	
		system("pause");
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
	
	if(archivo == NULL)
	{
		perror("Error en la apertura del archivo\n\n");
		system("pause");	
	}
	else
	{	
		for (i = 0; i<CONTADOR_USUARIOS; i++)
		{
			fscanf(archivo, "%s", arrusuarios[i]);
		}
	}
    
	while (a == 1)
	{
		imprimir_menu_amistades();
	            
		if (s("%d", &op) != 1)
		{
	        p("\nError");
			exit(-1);
		} 
				
		switch (op)
		{
			case 1:
				imprimir_matriz();
				ver_amigos();
				imprimir_matriz();
				break;
			
			case 2:
				imprimir_matriz();
				ver_amigos_amigos();
				imprimir_matriz();
				break;
					
			case 3:
				ver_grupos();
				break;
					
			case 4: 
			    imprimir_matriz();
			    enviar_solicitud();
			    imprimir_matriz();
				break;
		    			
			case 5: 
			    imprimir_matriz();
			    aceptar_solicitud();
			    imprimir_matriz();
				break;
		       			
			case 6: 
			    imprimir_matriz();
			    eliminar_amistad();
			    imprimir_matriz();
				break;
								
			case 7:	
				imprimir_matriz();
				guardar_matriz();
				imprimir_matriz();
			    a++;
				break;
			
			case 8:
				imprimir_matriz();
				break;
									
			default:
				p("\n\a Opcion invalida\n\n");
				break;
		}
	}
}


void imprimir_menu_amistades()
{
    puts("1. Ver amigos\n2. Ver amigos de amigos\n3. Ver grupos\n4. Enviar solicitud\n5. Aceptar solicitud\n6. Eliminar amigo\n7. Regresar\nOpción: ");
}

void ver_amigos()
{
    
}



void ver_amigos_amigos()
{	
	int i, j, my_IDI;
		
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{
		if (strcmp(USUARIO, arrusuarios[i]) == 0)
		{
			my_IDI = i;
			break;
		}
	}
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{		
		if ( matriz[my_IDI][i] == 2)
		{
			p("\nAmigos de:  %s\n",usuarios[i]);
			
			for (j = 0; j<CONTADOR_USUARIOS; j++)
			{
				if ( matriz[i][j] == 2 && j != my_IDI ) p("  %s\n", arrusuarios[j]);
			}
			p("-----------------");
		}
	}
}


void ver_grupos()
{
    
}


void enviar_solicitud()
{
	int i, my_IDI;
	char nuevo_amigo[50];

	p(" \nPersona deseas mandarle la solucitud:\n");
	s("%s",&nuevo_amigo);
	
	if (strcmp(USUARIO,nuevo_amigo) == 0)
	{
		p("ERROR...\n");
		return;
	}
	
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{
		if (strcmp(USUARIO, arrusuarios[i]) == 0)
		{
			my_IDI = i;
			break;
		}
	}
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{		
		if (strcmp(nuevo_amigo, arrusuarios[i]) == 0)
		{
			matriz[i][my_IDI] = 1;
			break;
		}
	}
	
	if(i == CONTADOR_USUARIOS)
	{
		p("ERROR...\n No se encontaron coincidencias\n");
		return;
	}
}


void ver_solicitudes()
{
	int i, my_IDI;
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{
		if (strcmp(USUARIO, arrusuarios[i]) == 0)
		{
			my_IDI = i;
			break;
		}
	}

	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{
		if (matriz[my_IDI][i] == 1) p("%s\n",  arrusuarios[i]);
	}
	
	p("\n");
}


void aceptar_solicitud()
{
	int i, my_IDI;
	char aceptar_solicitud[50];
	
	ver_solicitudes();
	
	p("\n Escriba a quien acepta como amigo:\n");
	s("%s",&aceptar_solicitud);
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{
		if (strcmp(USUARIO, arrusuarios[i]) == 0)
		{
			my_IDI = i;
			break;
		}
	}
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{		
		if (strcmp(aceptar_solicitud, arrusuarios[i]) == 0  && matriz[my_IDI][i] == 1)
		{
			matriz[i][my_IDI] = 2;
			matriz[my_IDI][i] = 2;
			break;
		}
	}
	
	if(i == CONTADOR_USUARIOS)
	{
		p("ERROR...\n No se encontaron coincidencias\n");
		return;
	}
}


void eliminar_amistad()
{
	int i, my_IDI;
	char persona_eliminada[50];
	
	ver_amigos();
	 
	p(" Escriba la persona que dese eliminar:\n");
	s("%s", &persona_eliminada);
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{
		if (strcmp(USUARIO, arrusuarios[i]) == 0)
		{
			my_IDI = i;
			break;
		}
	}
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{		
		if (strcmp(persona_eliminada, arrusuarios[i]) == 0 && matriz[i][my_IDI] == 2)
		{
			matriz[i][my_IDI] = 0;
			matriz[my_IDI][i] = 0;
			break;
		}
	}
	
	if(i == CONTADOR_USUARIOS)
	{
		p("ERROR...\n No se encontaron coincidencias\n");
		return;
	}
}


void guardar_matriz()
{	
	FILE* ptr = fopen(admatriz, "w");
	
	if (ptr == NULL)
	{
		p("ERROR...\n ");
	}
	else
	{	
		for(int i = 0; i < CONTADOR_USUARIOS; i++)
		{
			for (int j = 0; j < CONTADOR_USUARIOS; j++)
			{
				fprintf(ptr, "%i ", matriz[i][j]);
			}
			fprintf(ptr, "\n");
		}
	}
	fclose(ptr);
}


void imprimir_matriz()
{
	for(int i = 0; i < CONTADOR_USUARIOS;i++)
	{
		for (int j = 0; j < CONTADOR_USUARIOS;j++)
		{
			p("%i ",matriz[i][j]);
		}
		p("\n");
	}
}




// menú de publicaciones:
/*
void MenuPublicaciones (){
	int op, a=1;
	
	while (a==1)
	{
		menu_Publicaciones();
		
		if(s("%d", &op) != 1)
		{
	        p("\nError..");
			exit(-1);
		} 
		
		switch (op)
		{
			case 1:
				agregar_publicaciones();
				break;
				
			case 2:
				borrar_publicaciones();
				break;
				
			case 3:
				ver_publicaciones();
				break;
			
			case 4:
			    a++;
			    break;
		}
	}
}

void agregar_publicaciones(){
	
	char comentario[50];
	char User_coment[30];
	char *NombreArchivo = NULL;
	FILE *ptrfile = NULL;

	system("cls");
	dibujarCuadro(2,2,76,4); 
	centrar_texto("N U E V A    P U B L I C A C I O N",3);
	
	NombreArchivo = (char*) malloc (strlen(archivo_usuario) + strlen(USUARIO) + 1);
    strcpy(NombreArchivo,archivo_usuario);
    strcat(NombreArchivo,USUARIO);
    strcat(NombreArchivo,".txt");
    
    if ((ptrfile = fopen(NombreArchivo,"a")) == NULL)
    {
    	p("ERROR...\n Al momento de abrir el archivo");
	}else {
		
		fflush(stdin);
		gotoxy(2,6);  p("----------------------------\n");
		gotoxy(2,7);  p("|  ESCRIBA SU PUBLICACION  |\n");
		gotoxy(2,8);  p("----------------------------\n\n");
		s("%[^\n]",&comentario);
		
		fprintf(ptrfile,"%s\n",comentario);			
	}
	
	
    free(NombreArchivo);
    fclose(ptrfile);
    NombreArchivo = NULL;
}

void borrar_publicaciones(){

	int contador = 0;	
	char publicacion_borrada[30];
	char cadena_linea[30];	
	char caracter;
	
	char *NameArchivo = NULL;
	FILE *ptrfile = NULL;

	system("cls");
	dibujarCuadro(0,0,74,2); 
	centrar_texto("M I S   P U B L I C A C I O N E S",1);
	
	gotoxy(2,4);  p("------------------------------");
	gotoxy(2,5);  p("|  PUBLICACIONES EXISTENTES  |");
	gotoxy(2,6);  p("------------------------------\n");
	
	NameArchivo = (char*) malloc (strlen(archivo_usuario) + strlen(USUARIO) + 1);
    strcpy(NameArchivo,archivo_usuario);
    strcat(NameArchivo,USUARIO);
    strcat(NameArchivo,".txt");
	
	if ((ptrfile = fopen(NameArchivo,"r")) == NULL)
    {
    	p("ERROR...\n Al momento de abrir el archivo");
	}else {
		
		fseek (ptrfile, 0, SEEK_END);
		int NumCaracteresPublicaciones = ftell(ptrfile);
		rewind(ptrfile);
		
		char *cadena_publicaciones = (char*) calloc (sizeof (char),NumCaracteresPublicaciones);
		
		if (cadena_publicaciones == NULL)
		{
			perror("Error en reserva de memoria");
			system("pause");		
		}else {
			
			int numelementosleidos = fread(cadena_publicaciones, sizeof(char),NumCaracteresPublicaciones,ptrfile);
			
			gotoxy(0,8);p("%s\n",cadena_publicaciones);
			
			free(cadena_publicaciones);
			fclose(ptrfile);
    	}
		
	}
	
	free(NameArchivo);
    fclose(ptrfile);
    NameArchivo = NULL;

	NameArchivo = (char*) malloc (strlen(archivo_usuario) + strlen(USUARIO) + 1);
    strcpy(NameArchivo,archivo_usuario);
    strcat(NameArchivo,USUARIO);
    strcat(NameArchivo,".txt");
    
    const char* archivoAux = "E:\\Mis_Proyecto\\Red_social\\Archivos _txt\\auxiliar.txt";
	
	FILE *fileAux = fopen(archivoAux,"w+");
    
	if ((ptrfile = fopen(NameArchivo,"r+")) == NULL || fileAux == NULL )
    {
    	p("ERROR...\n Al momento de abrir el archivo");
    	system("cls");
    	
	}else {
		
		fflush(stdin);
		p("Escriba la publicacion que desea borrar:\n");
		s("%[^\n]",&publicacion_borrada);
				
		while (feof(ptrfile) == 0)
		{
			
			fgets(cadena_linea,30,ptrfile);
			strtok(cadena_linea, "\n");
	
			if(strcmp(publicacion_borrada,cadena_linea)  == 0 )
			{				
				rewind(ptrfile);
					
				while (feof(ptrfile) == 0)
				{	
					fgets(cadena_linea,30,ptrfile);
					strtok(cadena_linea, "\n");
								
					if(strcmp(publicacion_borrada,cadena_linea)  != 0 )
					{
						fprintf(fileAux,"%s\n", cadena_linea);
						memset(cadena_linea,'\0',sizeof(cadena_linea));
						fprintf(fileAux,"%s",cadena_linea);				
					}		
				}
					
				fclose(ptrfile);
				fclose(fileAux);
				
				FILE *ptrfile = fopen(NameArchivo,"w");
				FILE *fileAux = fopen(archivoAux,"r");
				
				int data1 = 0;
				rewind(fileAux);
				
				while ((data1 = fgetc(fileAux)) != EOF)
				{
					fputc (data1,ptrfile);		
				}
				
				fclose(ptrfile);
				fclose(fileAux);
				
				contador++;
				break;
		   }
		}
		
		if (contador == 0)
		{
			p("\n No se encontraron coincidencias.\n");
			p(" Presione una tecla para continuar.");
			system ("pause>redireccionar_salida");
		}
				
	}	
}


//----------------------------------- NODOS -----------------

void crear_nodo(){
	
	char cadena[50];
	
	CONTADOR_USUARIOS = 0;
	Nodo* temp;
	
	FILE *ar  = fopen(NombreArchivoUsuarios,"r");
	
	if (ar == NULL)
	{
		perror("Error no se ha podido abrir el fichero");
		system("pause");
	}else{ 	
		
		while ( fscanf(ar,"%s", cadena) == 1 )
		{
			auxiliar = (Nodo*) calloc(1, sizeof(Nodo));
			strcpy(auxiliar->user, cadena);
			CONTADOR_USUARIOS++;
			
			if (head == NULL)
			{
				auxiliar->next = NULL;
				head = auxiliar;
				
			}else{
				
				temp= head;
			
				while (temp->next != NULL) temp=temp->next;
				
				temp->next = auxiliar;
				auxiliar->next=NULL;
			}
		}
		fclose(ar);
	}
}

int **leer_matriz(){
	
}

char **arreglo_usuarios(){
	

}

void EliminarTodosLosNodos(){
	
	Nodo* temp1;
	Nodo* temp2;
	
	temp1 = head;
	temp2 = temp1->next;
	
	while( temp2 != NULL )
	{
		free(temp1);
		
		temp1 = temp2;
		temp2 = temp2->next;	
	}
	
	free(temp1);
	head = NULL;
}




void eliminar_cuenta(){
	
	const char* ArchivoAuxiliar = "auxiliar.txt";
	const char* ArchivoAuxiliar2 = "auxiliar2.txt"
	
	FILE *archivo  = fopen(usuarios, "r+");
	FILE *archivoAux = fopen(ArchivoAuxiliar, "w+");
	
	FILE *archivo2  = fopen(passwords, "r+");
	FILE *archivoAux2 = fopen(ArchivoAuxiliar2,"w+");
	
	if(archivo == NULL || archivoAux == NULL || archivo2 == NULL || archivoAux2 == NULL )
	{
		perror("Error en la creacion del archivo\n\n");
		system("pause");
	
	}
	else
	{				
		int contador = 0, i =0;
		char cadena_linea[30];
		char cadena_line[30];
		char persona_borrada[30];
		char password_borrada[30];	
		char caracter;
		
		fflush(stdin);
		p("User:      ");
		s("%s", &persona_borrada);
		
		fflush(stdin);
		p("Password:  ");
		while (caracter = getch())
		{
			if (caracter == 13)
			{
				password_borrada[i] = '\0';
				break;	
				
			}else if (caracter == 8){
				if(i > 0 )
				{
					i--;
					p("\b \b");	
				}
				
			}else{
				p("*");
				password_borrada[i] = caracter;
				i++;
			}
		}

		while (feof(archivo) == 0)
		{
			fscanf(archivo,"%s",&cadena_linea);	
			fscanf(archivo2,"%s",&cadena_line);
						
			if(strcmp(persona_borrada,cadena_linea)  == 0 && strcmp(password_borrada,cadena_line) == 0 && contador == 0)
			{				
				rewind(archivo);
				rewind(archivo2);
					
				while (feof(archivo) == 0)
				{	
					fscanf(archivo,"%s",&cadena_linea);	
					fscanf(archivo2,"%s",&cadena_line);	
								
					if(strcmp(persona_borrada,cadena_linea)  != 0 )
					{
						fprintf(archivoAux,"%s\n", cadena_linea);
						memset(cadena_linea,'\0',sizeof(cadena_linea));
						fprintf(archivoAux,"%s",cadena_linea);
								
						fprintf(archivoAux2,"%s\n", cadena_line);
						memset(cadena_line,'\0',sizeof(cadena_line));
						fprintf(archivoAux2,"%s",cadena_line);					
					}		
				}
					
				fclose(archivo);
				fclose(archivoAux);
				
				fclose(archivo2);
				fclose(archivoAux2);
						
				int data1 = 0;
				int data2 = 0;
						
				FILE *archivo  = fopen(usuarios, "w");
				FILE *archivoAux = fopen(ArchivoAuxiliar, "r");
						
				FILE *archivo2  = fopen(passwords, "w");
				FILE *archivoAux2 = fopen(ArchivoAuxiliar2, "r");
						
				while ((data1 = fgetc(archivoAux)) != EOF) fputc(data1,archivo);

				
				while ((data2 = fgetc(archivoAux2)) != EOF) fputc(data2,archivo2);
				
				contador++;
							
				fclose(archivo);
				fclose(archivoAux);
				
				fclose(archivo2);
				fclose(archivoAux2);	
				
				break;	
		    }		
		}	
		
		if (contador == 0)
		{
			p("  No se encontraron coincidencias.\n\n")
		}
		
		fclose(archivo);
		fclose(archivoAux);
				
		fclose(archivo2);
		fclose(archivoAux2);						
		
		char *NombreArchivo = NULL;
		char *Namefile1 = NULL;
		char *Namefile2 = NULL;	
		
		NombreArchivo = (char*) malloc (strlen(persona_borrada) + 1);
	    strcpy(NombreArchivo,persona_borrada);
	    strcat(NombreArchivo,".txt");
		remove(NombreArchivo);
		
		Namefile1 = (char*) malloc (strlen(persona_borrada) + 1);
	    strcpy(NombreArchivo,persona_borrada);
		remove(NombreArchivo);
		
		NombreArchivo = (char*) malloc (strlen(persona_borrada) + 1);
	    strcpy(NombreArchivo,persona_borrada);
		remove(NombreArchivo);				
	}
}


*/	