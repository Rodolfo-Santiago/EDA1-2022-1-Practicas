
def agregar_vuelo(): # función para registrar una ciudad y horario nuevos
    vuelo = list() # creamos una lista vacía para almacenar la ciudad y la hora
    
    var_aux = input("\nIngrese el nombre de la ciudad de destino: ") # leemos el nombre de la ciudad
    ciudad = var_aux.upper() # convertimos todas las letras de la cadena a mayúsculas
    
    while (0 < 1): # iniciamos un bucle infinito
        cont = 0 # inicializamos un contador en cero
        for caracter in ciudad: # recorremos cada caracter del nombre de la ciudad...
            if (caracter not in alfabeto) or (ciudad.index(caracter) == 0 and caracter == ' '):
                break # si el caracter no es letra, o si hay dos espacios seguidos... rompemos el ciclo for
            
            cont = cont + 1 # incrementamos el contador si el caracter que estamos evaluando si es aceptado
        
        if (cont == len(ciudad)): # si todos los caracteres del nombre fueron aceptados... salimos
            break # rompemos el ciclo while
        else: # si algún caracter no fue aceptado... volvemos a pedir otro nombre
            print("   Error. La ciudad que ingresó no tiene caracteres permitidos.")
            var_aux = input("Ingrese el nombre de la ciudad de destino: ")
            ciudad = var_aux.upper()
    
    ciudad = ciudad + "  " # añadimos dos espacios al final del nombre de la ciudad
    #                        para que: "abc  " esté antes que "abcxx  "
    #                        de otro modo el algoritmo pondría: "abcxx" antes que "abc"
    
    vuelo.append(ciudad) # agregamos el nombre la ciudad a nuestra lista de vuelo
    
    hora = int(input("Ingrese la hora: ")) # leemos la hora de salida
    while (hora < 0 or hora > 23): # validamos el dato
        hora = int(input("Error. Ingrese otra hora: "))
    vuelo.append(hora) # agregamos la hora a la lista de vuelo
    
    minuto = int(input("Ingrese los minutos: ")) # leemos el minuto de salida
    while (minuto < 0 or minuto > 59): # validamos el dato
        minuto = int(input("Error. Ingrese otros minutos: "))
    vuelo.append(minuto) # agregamos el minuto a la lista de vuelo
    
    segundo = int(input("Ingrese los segundos: ")) # leemos el segundo de salida
    while (segundo < 0 or segundo > 59): # validamos el dato
        segundo = int(input("Error. Ingrese otros segundos: "))
    vuelo.append(segundo) # agregamos el segundo a la lista de vuelo
    
    vuelos.append(vuelo) # añadimos toda la lista: [ciudad, hora, minuto, segundo] dentro de la lista de vuelos
    #                      la lista de vuelos se vería así:
    #                      {["ACAPULCO", 12, 30, 0], ["CANCÚN", 12, 0, 0], ["TOLUCA", 23, 59, 59]}
    
    
    
def mostrar_vuelos():
    print("\nLista de vuelos:\n")
    print ("{:<18} {:<25} Horario de salida".format('No. de vuelo','Ciudad de destino'))
    
    for vuelo in vuelos:
        hora = vuelo[1]
        minuto = vuelo[2]
        segundo = vuelo[3]
          
        if (vuelo[1] < 10):
            hora = "0" + str(vuelo[1])
 
        if (vuelo[2] < 10):
            minuto = "0" + str(vuelo[2])
           
        if (vuelo[3] < 10):
            segundo = "0" + str(vuelo[3])
            
        print("     {:<13} {:<25}   {:<2}:{:<2}:{:<2} hrs.".format(vuelos.index(vuelo) + 1, vuelo[0], hora, minuto, segundo))



def eliminar_vuelo():
    mostrar_vuelos()
    
    num_vuelo = int(input("\n¿Qué número de vuelo quieres eliminar?: "))
    while (num_vuelo < 1 or num_vuelo > len(vuelos)):
        num_vuelo = int(input("Error. ¿Qué número de vuelo quieres eliminar?: "))
    
    del(vuelos[num_vuelo - 1])
    
    print("\n¡Vuelo eliminado!")
    mostrar_vuelos()



def intercambiar(a, b):
    temporal = vuelos[a]
    vuelos[a] = vuelos[b]
    vuelos[b] = temporal



def segundos(num_vuelo):
    segundos = vuelos[num_vuelo][1] * 3600
    segundos += vuelos[num_vuelo][2] * 60
    segundos += vuelos[num_vuelo][3]
    
    return segundos



def posición(num_vuelo, letra):
    posición = alfabeto.index(vuelos[num_vuelo][0][letra])
    
    return posición
    


def elegir_pivote_al_azar(inicio, fin):
    índice_aleatorio = randint(inicio, fin)
    
    intercambiar(índice_aleatorio, fin)



def partición(criterio, inicio, fin):
    elegir_pivote_al_azar(inicio, fin)
        
    i = inicio - 1
    
    for j in range(inicio, fin):
        if (criterio == "por horario"):
            if (segundos(j) > segundos(fin)):
                continue
        
        elif (criterio == "por ciudad"):
            letra = 0
            while (posición(j, letra) == posición(fin, letra) and letra < len(vuelos[j][0]) - 1 and letra < len(vuelos[fin][0]) - 1):
                    letra = letra + 1
            
            if (posición(j, letra) > posición(fin, letra)):
                continue
        
        i = i + 1
        intercambiar(i, j)
    
    intercambiar(i + 1, fin)

    return i + 1



def ordenar(criterio, inicio, fin): # algoritmo: "quicksort"
    if (inicio < fin):
        pivote = partición(criterio, inicio, fin)
        
        ordenar(criterio, inicio, pivote - 1)
        ordenar(criterio, pivote + 1, fin)
    
    
    
    
def encontrar_repetidos_y_luego_ordenar(criterio): # función que encuentra el rango en donde hay ciudades u horarios repetidos para luego ordenarlos
    inicio = 0
    
    while inicio < len(vuelos) - 1:
        increm = 1 # increm significa incremento
        
        while (criterio == "por ciudad" and segundos(inicio) == segundos(inicio + increm)) or (criterio == "por horario" and vuelos[inicio][0] == vuelos[inicio + increm][0]):
            increm = increm + 1
            if (inicio + increm == len(vuelos)):
                break
        
        if (increm > 1):
            fin = inicio + increm - 1 # f significa final
            
            ordenar(criterio, inicio, fin)
                
        inicio = inicio + increm



def menu_acciones(): # función que imprime el menú de acciones
    print("\nMenú de acciones:\n   1. Agregar vuelo.\n   2. Eliminar vuelo.\n   3. Ver vuelos.\
    \n   4. Ordenar por horario.\n   5. Ordenar por ciudad.\n   6. Ordenar por horario y ciudad.\
    \n   7. Ordenar por ciudad y horario.\n   8. Salir.\n")



# Función principal:

from random import randint # importamos la función randint

vuelos = list() # creamos una lista vacía para almacenar los datos de los vuelos, por ejemplo:
#                 vuelos = { ["ciudad 1", 23, 12, 45], ["ciudad 2", 12, 23, 12], ["ciudad 3", 12, 12, 12] }

alfabeto = [' ', 'A', 'Á', 'B', 'C', 'D', 'E', 'É', 'F', 'G', 'H', \
            'I', 'Í', 'J', 'K', 'L', 'M', 'N', 'Ñ', 'O', 'Ó', 'P', \
            'Q', 'R', 'S', 'T', 'U', 'Ú', 'V', 'W', 'X', 'Y', 'Z'] # creamos una lista con los caracteres aceptados

print("BASE DE DATOS DE VUELOS")

while (0 < 1): # bucle infinito
    menu_acciones()
    
    opción = int(input("   Elija la opción que desea ejecutar: ")) # leemos la elección del usuario
    
    if (opción == 1):
        agregar_vuelo() # registramos un nuevo vuelo
        
    elif (opción == 2):
        if (len(vuelos) == 0): # si no hay vuelos registrados, no se puede eliminar
            print("\nNo hay vuelos en la base de datos.")
            continue
        
        eliminar_vuelo() # eliminamos un vuelo
        
    elif (opción == 3):
        if (len(vuelos) == 0): # si no hay vuelos, no se pueden mostrar
            print("\nNo hay vuelos en la base de datos.")
            continue
        
        mostrar_vuelos() # imprimos los vuelos en el orden predeterminado
        
    elif (opción == 4):
        if (len(vuelos) == 0): # si no hay vuelos, no se pueden ordenar
            print("\nNo hay vuelos en la base de datos.")
            continue
        
        ordenar("por horario", 0, len(vuelos) - 1) # se ejecuta el algoritmo "quicksort" en función del horario
        mostrar_vuelos() # se muestran los vuelos ordenados
        
    elif (opción == 5):
        if (len(vuelos) == 0):
            print("\nNo hay vuelos en la base de datos.")
            continue
        
        ordenar("por ciudad", 0, len(vuelos) - 1) # se ejecuta el algoritmo "quicksort" en función de la ciudad
        mostrar_vuelos() # se muestran los vuelos ordenados
        
    elif (opción == 6):
        if (len(vuelos) == 0):
            print("\nNo hay vuelos en la base de datos.")
            continue
        
        ordenar("por horario", 0, len(vuelos) - 1) # se ejecuta el algoritmo "quicksort" en función del horario primero
        encontrar_repetidos_y_luego_ordenar("por ciudad") # se encuentran aquellos horarios repetidos... para después ordenarlos
        
        mostrar_vuelos() # se muestran los vuelos ordenados
        
    elif (opción == 7):
        if (len(vuelos) == 0):
            print("\nNo hay vuelos en la base de datos.")
            continue
        
        ordenar("por ciudad", 0, len(vuelos) - 1) # se ejecuta el algoritmo "quicksort" en función de la ciudad primero
        encontrar_repetidos_y_luego_ordenar("por horario") # se encuentran aquellas ciudades repetidas... para después ordenarlas
        
        mostrar_vuelos() # se muestran los vuelos ordenados
        
    elif (opción == 8):
        break # se finaliza el programa
    
    elif (opción < 1 or opción > 8):
        print("\nEsa opción no está contemplada.")
