import requests##pip3 install request
import json
from tkinter import*
import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox as MessageBox
import sys


base_url = "http://127.0.0.1:8080/"
'''
if __name__ == '__main__':
    res = requests.post(f'{base_url}/Carga/otro.json')
    data = res.text#convertimos la respuesta en dict
    print(data)

    #obtener listado
    res = requests.get(f'{base_url}/Carga/')
    data = res.text#convertimos la respuesta en dict
    print(data)
'''

def abrirArchivo1():
    res = requests.post(f'{base_url}/Carga/otro.json')
    data = res.text#convertimos la respuesta en dict
    print(data)

def Login():
    res = requests.get(f'{base_url}/Login/Login')
    data = res.text#convertimos la respuesta en dict
    print(data)


def cerrar():
    MessageBox.showinfo("Adios", "Gracias por usar el programa")
    sys.exit()

#---------------------------------INTERFAZ GRÁFICA ------------------------------

ventana = Tk()
ventana.title("Proyecto Fase 2 - 202010816")
ventana.resizable(0,0)
ancho_ventana = 500
alto_ventana = 500
x_ventana = ventana.winfo_screenwidth() // 2 - ancho_ventana // 2
y_ventana = ventana.winfo_screenheight() // 2 - alto_ventana // 2
posicion = str(ancho_ventana) + "x" + str(alto_ventana) + "+" + str(x_ventana) + "+" + str(y_ventana)
ventana.geometry(posicion)


#Botones
btnCargarArchivo = Button(ventana, height=2, width=15, text="Cargar Usuarios", command = abrirArchivo1, background="#368807", font=("Verdana",10), fg="black")
btnCargarArchivo.place(x=180, y=150)

btnRegistrar = Button(ventana, height=2, width=15, text="Registrar Usuario", command="registrarUsuarios", background="#10139E", font=("Verdana",10), fg="black")
btnRegistrar.place(x=180, y=210)

btnLogin = Button(ventana, height=2, width=15, text="Login",command=Login, background="#8E8C08", font=("Verdana",10), fg="black")
btnLogin.place(x=180, y=270)

btnSalir = Button(ventana, height=2, width=15, text="Salir",command=cerrar, background="#B03314", font=("Verdana",10), fg="black")
btnSalir.place(x=180, y=330)


#Labels
labelEditor = Label (ventana, text ="BATALLA NAVAL", font=("Verdana",16), background="#044D9A", fg="white")
labelEditor.place(x=180, y=90)


ventana.mainloop()