from random import random
from celdas import Libre, Mina


def abs(x):
    # funcion de valor absoluto
    if (x < 0):
        return -1 * x
    return x


class Tablero():  # () no es relevante en intro, y es opcional en Python.
    # definicion de la clase Tablero. Convención es usar CamelCase.

    def __init__(self, ancho, alto, minas):
        # metodo inicializador. Define que argumentos necesitas y que pasará al
        #   inicializar un objeto de esta clase.
        # Siempre se llama __init__, y se utiliza (afuera de la clase) como
        #   Tablero(5, 5), por ejemplo.

        # self es un keyword que se refiere al objeto dueño.
        # SIEMPRE es el primer argumento (la palabra self es convención)

        self.ancho = ancho
        self.alto = alto
        self.minas = minas

        # aquí guardamos las variables de función ancho y alto en los atributos
        #   del objeto tablero, para poder accederlos después.

        prob = minas / (ancho * alto)

        # en cambio, prob no se guardará luego de terminar __init__.

        self.tablero = []
        # Aqui se construye una lista de listas de objetos creados
        #   dinámicamente, es decir, sin nombrarlos con una variable global.
        for fila in range(alto):
            nueva_fila = []
            for col in range(ancho):
                if (random() < prob):
                    # prob * 100% de mina
                    nueva_fila.append(Mina())
                else:
                    nueva_fila.append(Libre())
            self.tablero.append(nueva_fila)

        # Cómo se guardan los objetos? Así, supongamos de 3x3
        # tablero = [
        # [Mina(),    Libre(),  Libre()],
        # [Libre(),   Mina(),   Libre()],
        # [Mina(),    Libre(),  Libre()]
        #           ]
        # Si te fijas, los indices tablero[i] son filas, y dado un fila[i], un
        #   fila[i][j] sería una posición.
        # Con ésta manera de hacerlo (hay alternativas), para acceder a una
        #   posición (x,y) se haría tablero[y][x]

    def margen(self, a, b):
        # revisa que a y b esten en el tablero
        if 0 <= a < self.ancho and 0 <= b < self.alto:
            # que esté contenido en el tablero
            return True
        return False

    def calcular_minas(self, x, y):
        # Calcula las minas vecinas de una celda
        # se supone que x, y es libre
        obj = self.tablero[y][x]
        if obj.minas >= 0:  # si ya fue calculado
            return obj.minas

        minas = 0
        for i in range(-1, 2):
            new_y = y + i # y a revisar
            for j in range(-1, 2):
                new_x = x + j # x a revisar

                if self.margen(new_x, new_y) and (x != new_x and y != new_y):

                    vecino = self.tablero[new_y][new_x]

                    if type(vecino) == Mina:
                        # type(obj) indica la clase de un objeto
                        minas += 1
        obj.minas = minas
        # guardo el valor en el objeto, para no tener que recalcularlo.
        return obj.minas

    def jugar(self, x, y):
        # hacer una jugada dado una posicion x, y
        obj = self.tablero[y][x]
        obj.revelado = True
        if type(obj) == Mina:
            # Game Over!
            return False
        self.calcular_minas(x, y)
        return True

    def __str__(self):
        # __str__ es metodo interno que solo toma self como argumento y retorna
        #   un string. Define que se hace cuando, en este caso, se hace
        #   str(Tablero(...))
        # en este caso queremos imprimir el tablero. ? para no vistos, x para
        #   minas, un int para vecinos.
        string = ""
        for fila in range(self.alto):
            for col in range(self.ancho):
                obj = self.tablero[fila][col]
                string += str(obj) + " "
                # str(obj) definido por el __str__ de la clase de obj
            string += "\n"
        return string