from tablero import Tablero

# comenzar leyendo tablero.py, luego celdas.py, luego lo que sigue.

ANCHO = 5
ALTO = 6
MINAS = 10
# valores arbitrarios, sientete libre de cambiarlos o la manera de obtenerlos
tablero = Tablero(ANCHO, ALTO, MINAS)
jugando = True

while jugando:
    x = int(input("x: "))
    y = int(input("y: "))
    jugando = tablero.jugar(x, y)
    print(tablero)

# Desafíos (en orden de dificultad):
# - Hacer que se muestren todas las minas al perder.
# - Agregar banderas
# - Hacer que si Libre.minas == 0, se revisa los vecinos, para acelerar el paso
#       del juego.