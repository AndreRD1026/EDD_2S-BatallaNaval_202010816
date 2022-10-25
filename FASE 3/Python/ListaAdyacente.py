import os

class ENodo():
    def __init__ (self, index):
        self.index = index
        self.siguiente = None

class VNodo():
    def _init_(self):
        self.dato = None
        self.inicio = None

    def insertar(self, index):
        nuevo = ENodo(index)
        if self.inicio == None:
            self.inicio = nuevo
        else:
            aux = self.inicio
            while True:
                if aux.siguiente == None:
                    aux.siguiente = nuevo
                    break
                aux = aux.siguiente
    
class ListaDG():
    def __init__(self):
        self.v = []

    def crear(self, tamanio):
        for i in range(tamanio):
            self.v.append(i)
            self.v[i] = VNodo()
    
    def insertar(self,dato,pos):
        if pos >= 0 and pos < len(self.v):
            self.v[pos].dato = dato
            self.v[pos].inicio = None

    
    def conexion(self,inicio,fin):
        if inicio >= 0 and inicio < len(self.v):
            self.v[inicio].insertar(fin)

    def GrafoLista(self):
        contenido = ''' digraph G {\n'''
        for sig in self.v:
            auxiliar = sig.inicio
            while auxiliar != None:
                contenido += str(sig.dato+1) + '->' + str(self.v[auxiliar.index].dato + 1) + ';\n'
                auxiliar = auxiliar.siguiente
        contenido += '}'

        dot = "Graficos/GrafoLista.dot"
        with open(dot, 'w') as f:
            f.write(contenido)
        result = "Salida/GrafoLista.png"
        os.system('dot -Tpng ' + dot +  ' -o' + result)
        


    def GraficoLista(self):
        contenido = ''' digraph G {\n
        graph [rankdir = LR ]\n
        node [ style=filled,shape = box, fillcolor="white"]\n
        '''
        rank = '{rank = same; '
        label = ''
        apuntarsiguiente = ''
        for sig in self.v:
            rank += "\"" + "nod" + str(sig.dato +1) + "nod\" "
            label += "\"" + "nod" + str(sig.dato +1) + "nod\" " + "[label = \"" + str(sig.dato +1) + "\"]\n"
            apuntarsiguiente += "\"" + "nod" + str(sig.dato +1) + "nod\" " + "->"
        contenido += rank + '};\n'
        contenido += label + '\n'
        apuntarsiguiente = apuntarsiguiente[:-2]
        contenido += apuntarsiguiente + '\n'
        for sig in self.v:
            aux = sig.inicio
            apuntarsiguiente = ''
            count = 0
            while aux != None:
                contenido += 'nod' + str(sig.dato +1) + 'nod' + str(self.v[aux.index].dato + 1) + ' [label = \"' + str(self.v[aux.index].dato + 1) + '\", fillcolor="white"];\n'
                apuntarsiguiente += 'nod' + str(sig.dato +1) + 'nod' + str(self.v[aux.index].dato + 1) + '->'
                aux = aux.siguiente
                count += 1
            
            if count > 0:
                apuntarsiguiente = apuntarsiguiente[:-2]
                contenido += 'nod' + str(sig.dato +1) + 'nod->' + apuntarsiguiente + '\n'
        contenido += '}'

        dot = "Graficos/ListaAdy1.dot"
        with open(dot, 'w') as f:
            f.write(contenido)
        result = "Salida/ListaAdy1.png"
        os.system('dot -Tpng ' + dot +  ' -o' + result)