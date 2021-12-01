//RED SOCIAL SISTEMA.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define p printf
#define s scanf

typedef struct publicacion{
	int ID;
	char publicacion[50];
	struct publicacion* next;
}Nodo;

Nodo *head;
Nodo *auxiliar;
 
int CONTADOR_USUARIOS = 0;
int  matriz[1000][1000];
char usuarios[1000][50];
char USUARIO[30];

const char* archivo_usuario = "E:\\Mis_Proyecto\\Red_social\\Archivos _txt\\INFO_USUARIOS\\";
const char* NombreArchivoUsuarios = "E:\\Mis_Proyecto\\Red_social\\Archivos _txt\\usuarios.txt";
const char* NombreArchivoPassword = "E:\\Mis_Proyecto\\Red_social\\Archivos _txt\\password.txt";

//Menu principal
void agregar_persona();
void iniciar_sesion();
void ver_usuarios();
void eliminar_cuenta();

//Matriz
void leer_matriz();
void imprimir_matriz();
void guardar_matriz();

//Menu
void menu();
 
//Menu Amistades
void agregar_amigo();
void ver_amigos();
void borrar_amigo();
void ver_solicitudes();
void aceptar_solicitudes();
void VerAmigosDeAmigos();
void MayoresGruposDeAmigos();

//Menu Publicaciones 
void agregar_publicaciones();
void borrar_publicaciones();
void ver_publicaciones();

//Visualisacion del monitor
void gotoxy(int x, int y);
void goy(int y);
void print_cursor();
void hide_cursor();

// Graficos del programa
void menu_menus();
void menu_principal();
void barra_carga_Principal();
void centrar_texto(char *, int );
void dibujarCuadro(int x1, int y1, int x2, int y2);

//---------------------------------- MENU PRINCIPAL ----------------------------------- //
int main (){
	
	int op;
//	system("start E:\\Mis_Proyecto\\Red_social\\BaseDatosUsuarios.xlsm");
	system("cls");
	system("TITLE = Red Social Sistema");
	system("color 0f");
	head = NULL;
	
	while (1)
	{
		dibujarCuadro(0,0,78,29);
		dibujarCuadro(2,2,76,4);
		centrar_texto("R E D   S O C I A L   S I S T E M A\n",3);
		
		menu_principal();
		print_cursor();
	            
		if(s("%d", &op) != 1)
		{
	        p("\n Error..");
			exit(-1);
		} 
		
		if(op == 1 || op == 2 ||op == 3 || op == 4) barra_carga_Principal();
		
		switch (op)
			{
				case 1:
					agregar_persona(); 
					break;
			
				case 2:
					iniciar_sesion();
					break;
				
				case 3: 
					ver_usuarios();
					break;
					
				case 4:
					eliminar_cuenta();
					break;
					
				case 5:
					system("taskkill /F /IM EXCEL.EXE /T>redireccionar_salida ");
					return 1;
					break;
					
				default:
					p("\n\a          Opcion invalida\n\n");
					system("pause>redireccionar_salida");
					system("cls");
					break;
		   }
	}
	return 0;
}

void agregar_persona(){

	int i = 0;
	char caracter;
	char name[30], pas[30];
	char *NombreArchivo = NULL;
	FILE *ptrFile = NULL;
	
	system("cls");
	print_cursor();
	
	FILE *archivo  = fopen(NombreArchivoUsuarios,"a");
	FILE *archivo1 = fopen(NombreArchivoPassword,"a");
	
	if(archivo == NULL || archivo1 == NULL )
	{
		perror("Error en la creacion del archivo\n\n");
		system("pause");
	
	} else{
		
		dibujarCuadro(0,0,78,29);
		dibujarCuadro(2,2,76,4);
		centrar_texto("R E G I S T R O\n",3);
		
		fflush(stdin);
		gotoxy(3,8);p("Nombre:     ");
		s("%[^\n]",&name);
		fprintf(archivo,"%s\n", name);
		
		fflush(stdin);
		gotoxy(3,10);p("Password:   ");
		
		while (caracter = getch())
		{
			if (caracter == 13)
			{
				pas[i] = '\0';
				break;	
				
			}else if (caracter == 8){
				if(i > 0 )
				{
					i--;
					p("\b \b");	
				}
				
			}else{
				p("*");
				pas[i] = caracter;
				i++;
			}
		}
		fprintf(archivo1,"%s\n", pas);	
    }
    
    NombreArchivo = (char*) malloc (strlen(archivo_usuario) + strlen(name) + 1);
    strcpy(NombreArchivo,archivo_usuario);
    strcat(NombreArchivo,name);
    strcat(NombreArchivo,".txt");
    
    if ((ptrFile = fopen(NombreArchivo,"wt")) != NULL)
    {
    	fclose(ptrFile);
	}else{
		perror("No se pudo crear el archivo");
	}
    
    free(NombreArchivo);
    NombreArchivo = NULL;
    strset(name,0);
     
    fclose(ptrFile);
    fclose(archivo);
    fclose(archivo1);
    barra_carga_Principal();
	system("cls");
	
//_---------------------------------------------------------------------------------
	const char *direccion = "E:\\Mis_Proyecto\\Red_social\\Archivos _txt\\Matriz.txt";
	FILE *ptr = fopen(direccion,"r");
	
	if (ptr == NULL)
	{
		p("ERROR.. al abrir el archivo");	
		system("pause");
	}else{
		
		int i=0, j=0;
		
		if(fgetc(ptr) == EOF)
		{
			
			for( i=0; i<CONTADOR_USUARIOS; i++)
			{
				for( j=0; j<CONTADOR_USUARIOS; j++)
				{
					matriz[i][j] = 0;
				}
			}
		}else{
			
			rewind(ptr);
			
			for( i=0; i<CONTADOR_USUARIOS; i++)
			{
				for( j=0; j<CONTADOR_USUARIOS; j++)
				{
					fscanf(ptr,"%i",&matriz[i][j]);
				}
			}
		}
	}
	
	CONTADOR_USUARIOS++;
	for( i=0; i<CONTADOR_USUARIOS; i++)
	{
		matriz[CONTADOR_USUARIOS][i] = 0;
		matriz[i][CONTADOR_USUARIOS] = 0;
	}

	fclose(ptr);
	guardar_matriz();
}

void iniciar_sesion(){
	
	system("cls");
	
	int contador = 0, i=0;
	char nam[30];
	char pa[30];	
	char caracter;
	
	FILE *archivo  = fopen(NombreArchivoUsuarios,"r");
	FILE *archivo1 = fopen(NombreArchivoPassword,"r");
	
	dibujarCuadro(0,0,78,29);
	dibujarCuadro(2,2,76,4);
	centrar_texto("B I E N B E N I D O\n",3);
	print_cursor();
	
	fflush(stdin);
	gotoxy(3,8);p("User:         ");
	s("%[^\n]",&nam); 
	
	fflush(stdin);
	gotoxy(3,11);p("Password:     ");
	while (caracter = getch())
	{
		if (caracter == 13)
		{
			pa[i] = '\0';
			break;	
			
		}else if (caracter == 8){
			if(i > 0 )
			{
				i--;
				p("\b \b");	
			}
			
		}else{
			p("*");
			pa[i] = caracter;
			i++;
		}
	}
	
	if(archivo == NULL || archivo1 == NULL)
	{
		perror("Error en la apertura del archivo\n\n");
		system("pause");
	}else{
		
		char Usuario_inicio[30];	
		char Password_inicio[30];
			
		while (feof(archivo) == 0)
		{
			fscanf(archivo,"%s",&Usuario_inicio);	
			fscanf(archivo1,"%s",&Password_inicio);
						
			if(strcmp(Usuario_inicio,nam)  == 0 && strcmp(Password_inicio,pa) == 0 && contador == 0)
			{	
				strcpy(USUARIO, nam);
				fclose(archivo);
				fclose(archivo1);		
				barra_carga_Principal();
				menu();
				contador++;
		    }		
		}
		
		if (contador == 0)
		{
			gotoxy(1,15);p("  No se encontraron coincidencias.\n\n");
			gotoxy(1,16);p("  Presione una tecla para continuar.");
			system ("pause>redireccionar_salida");
		}
		
		fclose(archivo);
		fclose(archivo1);
		
		hide_cursor();
		system("cls");
	}		
}

void ver_usuarios(){
	
	system("cls");
	dibujarCuadro(2,2,76,4);
	centrar_texto("P E R S O N A S   R E G I S T R A D A S",3);
	
	FILE *archivo = fopen(NombreArchivoUsuarios,"r");
	
	if(archivo == NULL)
	{
		perror("Error en la apertura del archivo\n\n");
		system("pause");
		
	} else{
	 	
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
			
			gotoxy(0,7);p("Personas registradas:");
			gotoxy(0,9);p("%s\n",cadena);
			
			free(cadena);
			fclose(archivo);
			
			p("  Presione una tecla para continuar.");	
			system("pause>redireccionar_salida");
			system("cls");
		}
	}
}

void eliminar_cuenta(){
	
	const char* ArchivoAuxiliar = "E:\\Mis_Proyecto\\Red_social\\Archivos _txt\\auxiliar.txt";
	const char* ArchivoAuxiliar2 = "E:\\Mis_Proyecto\\Red_social\\Archivos _txt\\auxiliar2.txt";
	
	system("cls");
	dibujarCuadro(2,2,76,4);
	centrar_texto("E L I MI N A R  C U E N T A ",3);
	
	FILE *archivo  = fopen(NombreArchivoUsuarios,"r+");
	FILE *archivoAux = fopen(ArchivoAuxiliar,"w+");
	
	FILE *archivo2  = fopen(NombreArchivoPassword,"r+");
	FILE *archivoAux2 = fopen(ArchivoAuxiliar2,"w+");
	
	if(archivo == NULL || archivoAux == NULL || archivo2 == NULL || archivoAux2 == NULL )
	{
		perror("Error en la creacion del archivo\n\n");
		system("pause");
	
	} else{
				
		int contador = 0, i =0;
		char cadena_linea[30];
		char cadena_line[30];
		char persona_borrada[30];
		char password_borrada[30];	
		char caracter;
		
		fflush(stdin);
		gotoxy(5,9); p("User:      ");
		s("%[^\n]",&persona_borrada);
		
		fflush(stdin);
		gotoxy(5,12);p("Password:  ");
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
						
				FILE *archivo  = fopen(NombreArchivoUsuarios,"w");
				FILE *archivoAux = fopen(ArchivoAuxiliar,"r");
						
				FILE *archivo2  = fopen(NombreArchivoPassword,"w");
				FILE *archivoAux2 = fopen(ArchivoAuxiliar2,"r");
						
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
			gotoxy(1,15);p("  No se encontraron coincidencias.\n\n");
			gotoxy(1,16);p("  Presione una tecla para continuar.");
			system ("pause>redireccionar_salida");
		}	
	
		fclose(archivo);
		fclose(archivoAux);
				
		fclose(archivo2);
		fclose(archivoAux2);						
		
		char *NombreArchivo = NULL;
		char *Namefile1 = NULL;
		char *Namefile2 = NULL;
		
		
		NombreArchivo = (char*) malloc (strlen(archivo_usuario) + strlen(persona_borrada) + 1);
	    strcpy(NombreArchivo,archivo_usuario);
	    strcat(NombreArchivo,persona_borrada);
	    strcat(NombreArchivo,".txt");
		remove(NombreArchivo);
				
		barra_carga_Principal();
		system("cls");					
	}
}

//--------------------------------------- MENUS ----------------------------------------- //
void menu(){
	
	int op, a=1;
	char cadena[50];
	CONTADOR_USUARIOS = 0;
	
    FILE *ar  = fopen(NombreArchivoUsuarios,"r");
    while ( fscanf(ar,"%s", cadena) == 1 ) CONTADOR_USUARIOS++;
    fclose(ar);
    
    const char *direccion = "E:\\Mis_Proyecto\\Red_social\\Archivos _txt\\Matriz.txt";
	FILE *ptr = fopen(direccion,"r");
	
	if (ptr == NULL)
	{
		p("ERROR.. al abrir el archivo");	
		system("pause");
	}else{
		
		int i=0, j=0;
		
		if(fgetc(ptr) == EOF)
		{
			for( i=0; i<CONTADOR_USUARIOS; i++)
			{
				for( j=0; j<CONTADOR_USUARIOS; j++) matriz[i][j] = 0;
			}
		}else{
			
			rewind(ptr);
			
			for( i=0; i<CONTADOR_USUARIOS; i++)
			{
				for( j=0; j<CONTADOR_USUARIOS; j++) fscanf(ptr,"%i",&matriz[i][j]);
			}
		}
	}
	fclose(ptr);

	FILE *archivo = fopen(NombreArchivoUsuarios,"r");
	
	if(archivo == NULL)
	{
		perror("Error en la apertura del archivo\n\n");
		system("pause");
		
	} else{
		
		int i;
		for (i = 0; i<CONTADOR_USUARIOS; i++) fscanf(archivo,"%s",usuarios[i]);
	}
	
	while(a==1)
	{
		menu_menus();
		
		if(s("%d", &op) != 1)
		{
		    p("\n Error..");
			exit(-1);
		}
		
		if (op == 1 || op == 2 || op == 3 || op == 4 ) barra_carga_Principal();
		if (op == 5 || op == 6 || op == 7 || op == 8 ) barra_carga_Principal();
		if (op == 9 || op == 10) barra_carga_Principal();
		
		switch (op)
		{
			case 1:
				agregar_amigo();
				break;
				
			case 2:
				borrar_amigo();
				break;
				
			case 3:
				ver_amigos();
				system("pause");
				break;
			
			case 4:
				ver_solicitudes();
			    break;
			    
			case 5:
				aceptar_solicitudes();
				break;
			
			case 6:
				VerAmigosDeAmigos();
				break;
			
			case 7:
				MayoresGruposDeAmigos();
				break;
				
			case 8:
				agregar_publicaciones();
				break;
			
			case 9:
				borrar_publicaciones();
				break;
			
			case 10:
				ver_publicaciones();
				break;
			
			case 11:
				guardar_matriz();
				a++;
				break;
				
			case 12:
				imprimir_matriz();
				break;
					
			default:
				p("\n\a          Opcion invalida\n\n");
				system("pause>redireccionar_salida");
				system("cls");
		} 
	}			
}

//-------------------------------------- AMISTADES -------------------------------------- //
void guardar_matriz(){
	
	const char *direccion = "E:\\Mis_Proyecto\\Red_social\\Archivos _txt\\Matriz.txt";
	FILE *ptr = fopen(direccion,"w");
	
	if (ptr == NULL)
	{
		p("ERROR...\n ");
	}else{
		
		int i=0, j=0;
		
		for(i=0; i<CONTADOR_USUARIOS;i++)
		{
			for (j=0; j<CONTADOR_USUARIOS;j++) fprintf(ptr,"%i ",matriz[i][j]);
			fprintf(ptr,"\n");
		}
	}
	fclose(ptr);
}

void imprimir_matriz(){
	
	int i, j;
	
	for(i=0; i<CONTADOR_USUARIOS;i++)
	{
		for (j=0; j<CONTADOR_USUARIOS;j++) p("%i ",matriz[i][j]);
		p("\n");
	}
	system("pause");
}

void leer_matriz(){
	
	int i, my_IDI;
	gotoxy(2,6);p("------------------");
	gotoxy(2,7);p("|   SOLICITUDES  |");
	gotoxy(2,8);p("------------------\n");
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{
		if (strcmp(USUARIO,usuarios[i]) == 0)
		{
			my_IDI = i;
			break;
		}
	}

	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{
		if (matriz[my_IDI][i] == 1) p("%s\n", usuarios[i]);
	}
	p("\n");
	system("pause");
}

void agregar_amigo(){
	
	int i, my_IDI;
	char nuevo_amigo[50];
	
	system("cls");
	dibujarCuadro(2,2,76,4);
	centrar_texto("N U E V O   A M I G O",3);
	
	gotoxy(2,6);p("-------------------------------------");
	gotoxy(2,7);p("|   Personas que tal vez conozcas   |");
	gotoxy(2,8);p("-------------------------------------\n");
	p(" \nPersona deseas mandarle la solucitud:\n");
	s("%s",&nuevo_amigo);
	
	if (strcmp(USUARIO,nuevo_amigo) == 0)
	{
		p("ERROR...\n");
		return;
	}
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{
		if (strcmp(USUARIO,usuarios[i]) == 0)
		{
			my_IDI = i;
			break;
		}
	}
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{		
		if (strcmp(nuevo_amigo,usuarios[i]) == 0)
		{
			matriz[i][my_IDI] = 1;
			break;
		}
	}
	
	if(i == CONTADOR_USUARIOS)
	{
		p(" \nERROR...\n No se encontaron coincidencias\n");
		system("pause");
		return;
	}
}

void borrar_amigo(){
	
	int i, my_IDI;
	char persona_eliminada[50];
	
	system("cls");
	dibujarCuadro(2,2,76,4);
	centrar_texto("B O R R A R   A M I G O",3);
	
	gotoxy(2,6);p("-------------------------");
	gotoxy(2,7);p("|   TUS AMISTADES SON   |");
	gotoxy(2,8);p("-------------------------\n");
	 
	p(" Escriba la persona que dese eliminar:\n");
	s("%s",&persona_eliminada);
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{
		if (strcmp(USUARIO,usuarios[i]) == 0)
		{
			my_IDI = i;
			break;
		}
	}
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{		
		if (strcmp(persona_eliminada,usuarios[i]) == 0 && matriz[i][my_IDI] == 2)
		{
			matriz[i][my_IDI] = 0;
			matriz[my_IDI][i] = 0;
			break;
		}
	}
	
	if(i == CONTADOR_USUARIOS)
	{
		p(" \nERROR...\n No se encontaron coincidencias\n");
		system("pause");
		return;
	}
	system("pause");
}

void ver_amigos(){
	system("cls");
	int i, my_IDI;
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{
		if (strcmp(USUARIO,usuarios[i]) == 0)
		{
			my_IDI = i;
			break;
		}
	}
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{		
		if (matriz[my_IDI][i] == 2)
		{
			p("%s\n", usuarios[i]);
		}
	}
}

void ver_solicitudes(){

	system("cls");
	dibujarCuadro(2,2,76,4);
	centrar_texto("V E R   S O L I C I T U D E S",3);
	leer_matriz();
}

void aceptar_solicitudes(){
	
	int i, my_IDI;
	char aceptar_solicitud[50];
	
	system("cls");
	dibujarCuadro(2,2,76,4);
	centrar_texto("A C E P T A R   S O L U C I T U D E S",3);
	
	leer_matriz();
	p("\n Escriba a quien acepta como amigo:\n");
	s("%s",&aceptar_solicitud);
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{
		if (strcmp(USUARIO,usuarios[i]) == 0)
		{
			my_IDI = i;
			break;
		}
	}
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{		
		if (strcmp(aceptar_solicitud,usuarios[i]) == 0  && matriz[my_IDI][i] == 1)
		{
			matriz[i][my_IDI] = 2;
			matriz[my_IDI][i] = 2;
			break;
		}
	}
	
	if(i == CONTADOR_USUARIOS)
	{
		p(" \nERROR...\n No se encontaron coincidencias\n");
		system("pause");
		return;
	}
}

void VerAmigosDeAmigos(){
	
	int i,j, my_IDI;
	
	system("cls");
	dibujarCuadro(2,2,76,4);
	centrar_texto("V E R   A M I G O S   D E   A M I G O S",3);
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{
		if (strcmp(USUARIO,usuarios[i]) == 0)
		{
			my_IDI = i;
			break;
		}
	}
	
	for (i = 0; i<CONTADOR_USUARIOS; i++)
	{		
		if ( matriz[my_IDI][i] == 2)
		{
			p("\n\n Amigos de: %s\n",usuarios[i]);
			
			for (j = 0; j<CONTADOR_USUARIOS; j++)
			{
				if ( matriz[i][j] == 2 && j != my_IDI ) p("  %s\n",usuarios[j]);
			}
			p(" -----------------\n");
		}
	}
	system("pause");
}

void MayoresGruposDeAmigos(){

	system("cls");
	dibujarCuadro(2,2,76,4);
	centrar_texto("M A Y O R E S   G R U P O S   D E   A M I G O S",3);	
	
	
	system("pause");
}
//------------------------------------- PUBLICACIONES ------------------------------------- //
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

	int publicacion_borrada;	
	char cadena[50];	
	Nodo *temp;
	
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
		
		int id = 1;
		
		while ( fgets(cadena,50,ptrfile ))
		{
			p("%d.- %s",id, cadena);
			
			auxiliar = (Nodo*) calloc(1, sizeof(Nodo));
			strcpy(auxiliar->publicacion, cadena);
			auxiliar->ID = id;
			
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
			id++;
		}
		fclose(ptrfile);
		
		p("\n Escriba la publicacion que desea borrar:\n");
		s("%i",&publicacion_borrada);
		
		Nodo* temp1 = head;
		auxiliar = temp1->next;
		p("hola");
		if(publicacion_borrada == 1)
		{
			head = auxiliar;
			free(temp1);
		}else{
			
			while(auxiliar->ID != publicacion_borrada)
			{
				auxiliar = auxiliar->next;
				temp1 = temp1->next;
			} 
			temp1 = auxiliar->next;
			free(auxiliar);
		}
		FILE *file = NULL;
		
		if ((file = fopen(NameArchivo,"w")) == NULL)
	    {
	    	p("ERROR...\n Al momento de abrir el archivo");
		}else {
			
			auxiliar = head;
			while(auxiliar != NULL)
			{
				fprintf(file,"%s",auxiliar->publicacion);
				auxiliar = auxiliar->next;
			}
		}
		
		fclose(file);
		head =  NULL;
	}	
}	

void ver_publicaciones(){
	
	char *NombreArchivo = NULL;
	FILE *ptrfile = NULL;

	system("cls");
	dibujarCuadro(0,0,74,2); 
	centrar_texto("M I S   P U B L I C A C I O N E S",1);
	
	NombreArchivo = (char*) malloc (strlen(archivo_usuario) + strlen(USUARIO) + 1);
    strcpy(NombreArchivo,archivo_usuario);
    strcat(NombreArchivo,USUARIO);
    strcat(NombreArchivo,".txt");
	
	if ((ptrfile = fopen(NombreArchivo,"r")) == NULL)
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
			
			gotoxy(2,4);p("--------------------------\n");
			gotoxy(2,5);p("|     PUBLICACIONES.     |\n");
			gotoxy(2,6);p("--------------------------\n");
			gotoxy(0,8);p("%s\n",cadena_publicaciones);
			
			free(cadena_publicaciones);
			fclose(ptrfile);
			
			p("  \nPresione una tecla para salir.");	
			system("pause>redireccionar_salida");
			system("cls");	
    	}
	}
	free(NombreArchivo);
    fclose(ptrfile);
    NombreArchivo = NULL;
}

//------------------------------ VISUALISACION DE CONSOLA -------------------------------- //
void gotoxy(int x, int y){
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}

void hide_cursor(){
    HANDLE consoleHandle;
    consoleHandle= GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void print_cursor(){
	HANDLE consoleHandle;
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = TRUE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void centrar_texto(char *texto, int y){
	int lon;
	lon = strlen(texto);
	gotoxy(40-(lon/2),y);printf(texto);
}

void dibujarCuadro(int x1, int y1, int x2, int y2){

	int i;
    for (i=x1; i<x2; i++)
	{
		gotoxy(i,y1); p("%c",196);
		gotoxy(i,y2); p("%c",196);
    }
    
    for (i=y1; i<y2; i++)
	{
		gotoxy(x1,i); p("%c",179);
    	gotoxy(x2,i); p("%c",179);
	}
    gotoxy(x1,y1); p("%c",04);
    gotoxy(x1,y2); p("%c",04);
    gotoxy(x2,y1); p("%c",04);
    gotoxy(x2,y2); p("%c",04);
}

////-------------------------------------- GRAFICOS --------------------------------------- //
void menu_principal(){
	gotoxy (3,6);  p("------------------------------------------");
	gotoxy (3,7);  p("| 1.- Agregar Cuenta.                    |"); 
	gotoxy (3,8);  p("------------------------------------------");
	gotoxy (3,9);  p("------------------------------------------");
	gotoxy (3,10); p("| 2.- Iniciar Sesion.                    |");
	gotoxy (3,11); p("------------------------------------------");
	gotoxy (3,12); p("------------------------------------------");
	gotoxy (3,13); p("| 3.- Ver personas que usan el sistema.  |");
	gotoxy (3,14); p("------------------------------------------");
	gotoxy (3,15); p("------------------------------------------");
	gotoxy (3,16); p("| 4.- Eliminar Cuenta.                   |");
	gotoxy (3,17); p("------------------------------------------");
	gotoxy (3,18); p("------------------------------------------");
	gotoxy (3,19); p("| 5.- Salir.                             |");
	gotoxy (3,20); p("------------------------------------------");
	gotoxy (3,22); p("                                Elige: ");
}

void menu_menus(){
	system("cls");
//	system("");
	print_cursor();
	dibujarCuadro(0,0,78,13);
	gotoxy (1,1); p("                                               DONDE QUIERE ACCESAR                                              ");
	gotoxy (1,2); p("-----------------------------------------------------------------------------------------------------------------");
	gotoxy (1,3); p("            AMISTADES.                |           SOLICITUDES               |           PUBLICACIONES.           ");
	gotoxy (1,4); p("-----------------------------------------------------------------------------------------------------------------");
	gotoxy (1,5); p(" 1.- Agregar amigo.                   | 4.- Ver solicitudes                 | 7.- Agregar Publicaciones.         ");	
	gotoxy (1,6); p(" 2.- Borrar amigo.                    | 5.- Ver amigos de amigos.           | 8.- Borrar Publicaciones.          ");
	gotoxy (1,7); p(" 3.- Ver amigo                        | 6.- Ver mayores grupos de amigos.   | 9.- Ver Publicaciones.             ");
	gotoxy (1,8); p("                                      | 7.- Ver mayores grupos de amigos.   |                                    ");
	gotoxy (1,9); p("-----------------------------------------------------------------------------------------------------------------");
	gotoxy (1,10);p(" 10.- SALIR                           |                                     |                                    ");
	gotoxy (1,10);p("     |                                     |                                    ");
	gotoxy (1,11);p("-----------------------------------------------------------------------------------------------------------------");	
	gotoxy (1,12);p("                                                          Elige: ");
}

void barra_carga_Principal(){
	int j;
	hide_cursor();
	centrar_texto("Cargando ...\n",25);

	for (j=10;j<70;j++)
	{
		gotoxy(j,27);p("%c",177);
	}

	for (j=10;j<70;j++)
	{
        Sleep(20);
		gotoxy(j,27);p("%c",219);
	}
	print_cursor();
}
