import matplotlib.pyplot as plt
from matplotlib.widgets import Button
import random
import math


class Casilla:
    def __init__(self):
        self.Visible = False
        self.TieneMina = False
        #self.TieneOtro = False
        #self.Prueba2 = False
        self.MinaMarcada = 0
        self.NumMinasAdyacentes = 0


class prueba:
    def __init__(self, tam, numMinas):
        self.Tamano = tam
        self.Tablero = []
        self.Pendientes = tam*tam
        self.Estado = ""
        self.XError = None
        self.YError = None
        for fila in range(tam):
            f = []
            for j in range(tam):
                f.append(Casilla())
            self.Tablero.append(f)
        num = 0
        #numF = numMinas + numMinas2
        while num < numMinas:
            rndx = random.randint(0,tam-1)
            rndy = random.randint(0,tam-1)
            if not self.Tablero[rndx][rndy].TieneMina:
                self.Tablero[rndx][rndy].TieneMina = True
                #self.Tablero[rndx][rndy].TieneOtro = True
                filaIni = max(rndx-1,1)
                filaFin = min(rndx+1,tam-1)
                colIni = max(rndy-1,0)
                colFin = min(rndy+1,tam-1)
                for i in range(filaIni, filaFin+1,1):
                    for j in range(colIni,colFin+1,1):
                        if i !=rndx or j != rndy:
                            self.Tablero[i][j].NumMinasAdyacentes += 1
                num += 1



    def Pintar(self):
        plt.figure(figsize=(6, 6))
        salida = 2
        plt.text(-2, self.Tamano + 2, "Portaaviones: " + str(salida) , fontdict=None)
        plt.text(8, self.Tamano + 2, "Submarinos: 4", fontdict=None )
        plt.text(20, self.Tamano + 2, "Destructores: 8", fontdict=None )
        plt.text(32, self.Tamano + 2, "Buques: 12", fontdict=None )
        for n in range(self.Tamano+1):
            plt.plot ([0,self.Tamano],[n,n], color="black", linewidth=1)
            plt.plot ([n,n],[0,self.Tamano], color="black", linewidth=1)
        for i in range(self.Tamano):
            for j in range(self.Tamano):
                px = j + 0.5
                py = self.Tamano - (i + 0.5)

                '''
                if self.Tablero[i][j].Visible:
                    if self.Tablero[i][j].TieneMina:
                        plt.plot([px], [py], linestyle='None', marker='.', markersize=8, color='red')
                    else:
                        if self.Tablero[i][j].NumMinasAdyacentes != 0:
                            plt.text(px,py, str(self.Tablero[i][j].NumMinasAdyacentes),horizontalalignment='center', verticalalignment='center',
                            color = 'green', fontsize=12)
                else: 
                    plt.plot([px], [py], linestyle='None', marker='.', markersize=4,color='black')
                '''
                if self.Tablero[j][i].TieneMina:
                    plt.plot([px], [py], linestyle='None', marker='^', markersize=8, color='red')
                #elif self.Tablero[j][i].TieneOtro:
                #    plt.plot([px], [py], linestyle='None', marker='.', markersize=8, color='blue')
                else:
                    plt.plot([px], [py], linestyle='None', marker='o', markersize=4, color='black')
                


    def on_click(self,event):
        y = math.floor(event.xdata)
        x = self.Tamano - math.floor(event.ydata) - 1
        if str(event.button) == "MouseButton.LEFT":
            if self.Tablero[x][y].TieneMina:
                #pass
                print("Mina")
            elif not self.Tablero[x][y].Visible:
                self.Tablero[x][y].Visible = True
        plt.clf()
        self.Pintar()
        plt.draw()

'''
Busca = prueba(10,2)
#plt.connect('button_press_event', Busca.on_click)
#plt.ion()
#print("ejecutados")
Busca.Pintar()
#plt.draw()
#plt.pause(100)
plt.show()

'''

fig, ax =plt.subplots()
data=[[1,2,3,4],
    [5,6,7,0],
    [8,9,10,11]]
column_labels=["ID", "Nombre", "Categoria", "Precio"]
ax.axis('tight')
ax.axis('off')
ax.table(cellText=data,colLabels=column_labels,loc="center")
axButn1 = plt.axes([0.1, 0.1, 0.1, 0.1])
btn2 = Button(axButn1, label="Prev", color='pink', hovercolor='tomato')

plt.show()