
def leer_lista(lista):
    no_elem = int(input("Ingresa el número de elementos de la lista: "))
    
    for i in range(0, no_elem):
        elem_i = input("    Elemento " + str(i + 1) + ": ")
        lista.append(elem_i)


def concatenar(a, b):
    for i in range (0, len(b)):
        b[ i ] = a + b[ i ]
    return b


def intercalar(a, b):
    # caso base:
    if (len(a) == 0 or len(b) == 0):
        c = a + b
        resultado = [ c ]
        return resultado
    
    # obtener el primer elemento de cada lista:
    a0 = [ a[0] ]
    b0 = [ b[0] ]
    
    # obtener el sobrante de cada lista:
    lis1 = []
    lis2 = []
    for i in range(1, len(a)):
        lis1.append(a[ i ])
    for i in range(1, len(b)):
        lis2.append(b[ i ])
    
    # fórmula para intercalar dos listas:
    resultado = concatenar(a0, intercalar(lis1, b0 + lis2)) + concatenar(b0, intercalar(a0 + lis1, lis2))
   
    return resultado

 
def imprimir(lista):
    if (len(lista) == 1):
        print('\nLista A & Lista B = {', lista[0], '}')
        return
    
    print('\nLista A & Lista B = {', lista[0])
    for i in range(1, len(lista) - 1):
        print('                     ', lista[i])
    print('                     ', lista[-1], '}')
 
 
#Función principal:
print("CALCULADORA DE INTERCALADO ENTRE DOS LISTAS\n")

while (0 < 1):
    # inicialización de listas vacías a y b:
    a = []
    b = []
    
    # entrada de datos:
    print("\nLista A")
    leer_lista(a)
    print("\nLista B")
    leer_lista(b)
    
    # salida de datos:
    print("\n\nLista A =", a)
    print("\nLista B =", b)
    imprimir(intercalar(a, b)) # intercalado de listas
    
    
    opcion = int(input("\n\n¿Desea hacer otro cálculo (1-sí o 2-no)?: "))
    
    if (opcion == 2):
        break  # finalización del programa
