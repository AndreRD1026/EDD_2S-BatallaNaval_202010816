# Para estas clases, hay dos maneras principales de modelar. En general, al
#   programar en OOP, queremos que las clases sean lo más concisas posibles,
#   pero a veces necesitamos guardar información que no "debería pertenecerle".
# En este ejemplo, podría hacer que los objetos guarden una referencia al
#   tablero, pero creo que es innecesario para este problema y sería un poco
#   complicado para intro.


class Mina:
    def __init__(self):
        self.revelado = False

    def __str__(self):
        if self.revelado:
            return "X"
        return "?"


class Libre:
    def __init__(self):
        self.revelado = False
        self.minas = -1
        # inicialmente, la celda libre no sabe cuantas minas tiene alrededor.
        # sin embargo, no quiero recalcularla cada vez que se imprime, por lo
        #   que voy a guardarlo en una variable (que puedo ver facilmente si
        #   se ha calculado antes (es imposible tener -1))

        # obviamente, nunca debería pasar que revelado == True y minas == -1

    def __str__(self):
        if self.revelado:
            return str(self.minas)
        return "?"