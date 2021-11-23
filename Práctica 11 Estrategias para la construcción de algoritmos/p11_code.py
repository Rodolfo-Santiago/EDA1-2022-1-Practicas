def agregar_vuelo(vuelos): # función para registrar una ciudad y horario nuevos
    vuelo = list() # creamos una lista vacía para almacenar la ciudad y la hora
    
    alfabeto = [' ', 'A', 'Á', 'B', 'C', 'D', 'E', 'É', 'F', 'G', 'H', \
                'I', 'Í', 'J', 'K', 'L', 'M', 'N', 'Ñ', 'O', 'Ó', 'P', \
                'Q', 'R', 'S', 'T', 'U', 'Ú', 'V', 'W', 'X', 'Y', 'Z'] # creamos una lista con los caracteres aceptados
    
    var_aux = input("\nIngrese el nombre de la ciudad de destino: ") # leemos el nombre de la ciudad
    ciudad = var_aux.upper() # convertimos todas las letras de la cadena a mayúsculas
    
    while (0 < 1): # iniciamos un bucle infinito
        cont = 0 # inicializamos un contador en cero
        for caracter in ciudad: # recorremos cada caracter del nombre de la ciudad...
            if (caracter not in alfabeto) or (ciudad.index(caracter) == 0 and caracter == ' ') or (ciudad.index(caracter) < len(ciudad) - 1 and caracter == ' ' and ciudad[ciudad.index(caracter) + 1] == ' '):
                break # si el caracter no es letra, o si hay dos espacios seguidos... rompemos el ciclo for
            
            cont = cont + 1 # incrementamos el contador si el caracter que estamos evaluando si es aceptado
        
        if (cont == len(ciudad)): # si todos los caracteres del nombre fueron aceptados... salimos
            break # rompemos el ciclo while
        else: # si algún caracter no fue aceptado... volvemos a pedir otro nombre
            print("La ciudad que ingresó no tiene caracteres permitidos o incluyó muchos espacios.")
            var_aux = input("Ingrese el nombre de la ciudad de destino: ")
            ciudad = var_aux.upper()
    
    ciudad = ciudad + "  " # añadimos dos espacios al final del nombre de la ciudad
    #                        para que: "abc  " esté antes que "abcxx  "
    #                        de otro modo el algoritmo pondría: "abcxx" antes que "abc"
    
    vuelo.append(ciudad) # agregamos el nombre la ciudad a nuestra lista de vuelo
    
    hora = int(input("Ingrese la hora: ")) # leemos la hora de salida
    while (hora < 0 or hora > 23): # validamos el dato
        hora = int(input("Ingrese la hora: "))
    vuelo.append(hora) # agregamos la hora a la lista de vuelo
    
    minuto = int(input("Ingrese los minutos: ")) # leemos el minuto de salida
    while (minuto < 0 or minuto > 59): # validamos el dato
        minuto = int(input("Ingrese los minutos: "))
    vuelo.append(minuto) # agregamos el minuto a la lista de vuelo
    
    segundo = int(input("Ingrese los segundos: ")) # leemos el segundo de salida
    while (segundo < 0 or segundo > 59): # validamos el dato
        segundo = int(input("Ingrese los segundos: "))
    vuelo.append(segundo) # agregamos el segundo a la lista de vuelo
    
    vuelos.append(vuelo) # añadimos toda la lista: [ciudad, hora, minuto, segundo] dentro de la lista de vuelos
    #                      la lista de vuelos se vería así:
    #                      {["ACAPULCO", 12, 30, 0], ["CANCÚN", 12, 0, 0], ["TOLUCA", 23, 59, 59]}
    
    
def mostrar_vuelos(vuelos):
    print("\nLista de vuelos:\n")
    print ("{:<18} {:<25} Horario de salida".format('No. de vuelo','Ciudad de destino'))
    
    for vuelo in vuelos:
        if (vuelo[1] < 10):
            hora = "0" + str(vuelo[1])
        else:
            hora = vuelo[1]
        if (vuelo[2] < 10):
            minuto = "0" + str(vuelo[2])
        else:
            minuto = vuelo[2]
        if (vuelo[3] < 10):
            segundo = "0" + str(vuelo[3])
        else:
            segundo = vuelo[3]
            
        print("     {:<13} {:<25}   {:<2}:{:<2}:{:<2} hrs.".format(vuelos.index(vuelo) + 1, vuelo[0], hora, minuto, segundo))



def eliminar_vuelo(vuelos):
    mostrar_vuelos(vuelos)
    
    no_vuelo = int(input("\n¿Qué número de vuelo quieres eliminar?: "))
    while (no_vuelo < 1 or no_vuelo > len(vuelos)):
        no_vuelo = int(input("Error. ¿Qué número de vuelo quieres eliminar?: "))
    
    del(vuelos[no_vuelo - 1])
    
    print("\n¡Vuelo eliminado!")
    mostrar_vuelos(vuelos)



def intercambiar(lista, a, b):
    temporal = lista[a]
    lista[a] = lista[b]
    lista[b] = temporal


def segundos(vuelos, indice):
    segundos = vuelos[indice][1] * 3600
    segundos += vuelos[indice][2] * 60
    segundos += vuelos[indice][3]
    return segundos


def posicion(vuelos, indice, letra):
    alfabeto = [' ', 'A', 'Á', 'B', 'C', 'D', 'E', 'É', 'F', 'G', 'H', \
                'I', 'Í', 'J', 'K', 'L', 'M', 'N', 'Ñ', 'O', 'Ó', 'P', \
                'Q', 'R', 'S', 'T', 'U', 'Ú', 'V', 'W', 'X', 'Y', 'Z'] # creamos una lista con los caracteres aceptados
    
    posicion = alfabeto.index(vuelos[indice][0][letra])
    
    return posicion
    


def particion(vuelos, p, r, opcion):
    #indice_aleatorio = randint(0, len(vuelos) - 1)
    #intercambiar(vuelos, indice_aleatorio, r)
    
    if (opcion == 0):
        pivote = segundos(vuelos, r)
        
    i = p - 1
    
    for j in range(p, r):
        letra = 0
        while (opcion == 1 and posicion(vuelos, j, letra) == posicion(vuelos, r, letra) and letra < len(vuelos[j][0]) and letra < len(vuelos[r][0])):
                if (letra == len(vuelos[j][0]) - 1 or letra == len(vuelos[r][0]) - 1):
                    break
                letra = letra + 1
        
        if (opcion == 1 and posicion(vuelos, j, letra) > posicion(vuelos, r, letra)):
            continue
        
        if (opcion == 0 and segundos(vuelos, j) <= pivote) or (opcion == 1):
            i = i + 1
            intercambiar(vuelos, i, j)
    
    intercambiar(vuelos, i + 1, r)

    return i + 1



def ordenar(vuelos, p, r, opcion):
    if (p < r):
        q = particion(vuelos, p, r, opcion)
        
        ordenar(vuelos, p, q - 1, opcion)
        ordenar(vuelos, q + 1, r, opcion)
    
    
    
    
def encontrar_repetidos(vuelos, origen, fin):
    inicio = 0
    while inicio < len(vuelos) - 1:
        increm = 1
        while (origen == 0 and segundos(vuelos, inicio) == segundos(vuelos, inicio + increm)) or (origen == 1 and vuelos[inicio][0] == vuelos[inicio + increm][0]):
            increm = increm + 1
            if (inicio + increm == len(vuelos)):
                break
        
        if (increm > 1):
            final = inicio + increm - 1
            if (origen == 0):
                ordenar(vuelos, inicio, final, 1)
            elif (origen == 1):
                ordenar(vuelos, inicio, final, 0)
                
        inicio = inicio + increm



def menu_acciones():
    print("\nMenú de acciones:\n   1. Agregar vuelo.\n   2. Eliminar vuelo.\n   3. Ver vuelos.\
    \n   4. Ordenar por horario.\n   5. Ordenar por ciudad.\n   6. Ordenar por horario y ciudad.\
    \n   7. Ordenar por ciudad y horario.\n   8. Salir.\n")



# funcion principal:
#from random import randint

vuelos = list() # creamos una lista vacía para almacenar los datos de los vuelos
print("BASE DE DATOS DE VUELOS")

# vuelos= { ["ciudad", 23, 12, 45], ["ciudad2", 12, 23, 12], ["ciudad 3", 12, 12, 12] }


while (0 < 1):
    menu_acciones()
    
    opcion = int(input("   Elija la opción que desea ejecutar: ")) # leemos la elección del usuario
    
    if (opcion == 1):
        agregar_vuelo(vuelos) # registramos un nuevo vuelo
        
    elif (opcion == 2):
        if (len(vuelos) == 0): # si no hay vuelos registrados, no se puede eliminar
            print("\nNo hay vuelos en la base de datos.")
            continue
        
        eliminar_vuelo(vuelos) # eliminamos un vuelo
        
    elif (opcion == 3):
        if (len(vuelos) == 0): # si no hay vuelos, no se pueden mostrar
            print("\nNo hay vuelos en la base de datos.")
            continue
        
        mostrar_vuelos(vuelos) # imprimos los vuelos en el orden predeterminado
        
    elif (opcion == 4):
        if (len(vuelos) == 0): # si no hay vuelos, no se pueden ordenar
            print("\nNo hay vuelos en la base de datos.")
            continue
        
        ordenar(vuelos, 0, len(vuelos) - 1, 0) # se ejecuta el algoritmo "quicksort" en función del horario
        mostrar_vuelos(vuelos) # se muestran los vuelos ordenados
        
    elif (opcion == 5):
        if (len(vuelos) == 0):
            print("\nNo hay vuelos en la base de datos.")
            continue
        
        ordenar(vuelos, 0, len(vuelos) - 1, 1) # se ejecuta el algoritmo "quicksort" en función de la ciudad
        mostrar_vuelos(vuelos) # se muestran los vuelos ordenados
        
    elif (opcion == 6):
        if (len(vuelos) == 0):
            print("\nNo hay vuelos en la base de datos.")
            continue
        
        ordenar(vuelos, 0, len(vuelos) - 1, 0) # se ejecuta el algoritmo "quicksort" en función del horario primero
        encontrar_repetidos(vuelos, 0, 1) # se encuentran aquellos horarios repetidos... para después ordenarlos
        
        mostrar_vuelos(vuelos) # se muestran los vuelos ordenados
        
    elif (opcion == 7):
        if (len(vuelos) == 0):
            print("\nNo hay vuelos en la base de datos.")
            continue
        
        ordenar(vuelos, 0, len(vuelos) - 1, 1) # se ejecuta el algoritmo "quicksort" en función de la ciudad primero
        encontrar_repetidos(vuelos, 1, 0) # se encuentran aquellas ciudades repetidas... para después ordenarlas
        
        mostrar_vuelos(vuelos) # se muestran los vuelos ordenados
        
    elif (opcion == 8):
        break # se finaliza el programa
