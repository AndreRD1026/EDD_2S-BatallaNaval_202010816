import requests##pip3 install request
import json
from tkinter import*
import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox as MessageBox
import sys
import os


base_url = "http://127.0.0.1:8080/"

'''
def abrirArchivo1():
    res = requests.post(f'{base_url}/Carga/otro.json')
    data = res.text#convertimos la respuesta en dict
    print(data)
'''
def abrirArchivo1():
    try:
        global archivo
        archivo = filedialog.askopenfilename(title="Seleccionar archivo", filetypes=[("json", "*.json")])
        prueba = os.path.split(archivo)
        #print(prueba)
        res = requests.post(f'{base_url}/Carga/' + f'{prueba[1]}')
        data = res.text#convertimos la respuesta en dict
        print(data)
        #MessageBox.showinfo("Exito!", "Archivo Cargado con exito")
        ventana.mainloop()
    except:
        MessageBox.showwarning("Alerta", "Debe cargar un archivo")
    

def registrarUsuarios():
    ventanaReg = Tk()
    ventanaReg.title("Registro Usuario")
    ventanaReg.resizable(0,0)
    ancho_ventana1 = 500
    alto_ventana1 = 500
    x_ventana1 = ventanaReg.winfo_screenwidth() // 2 - ancho_ventana1 // 2
    y_ventana1 = ventanaReg.winfo_screenheight() // 2 - alto_ventana1 // 2
    posicion1 = str(ancho_ventana1) + "x" + str(alto_ventana1) + "+" + str(x_ventana1) + "+" + str(y_ventana1)
    ventanaReg.geometry(posicion1)
    labelLogin = Label (ventanaReg, text ="Registro", font=("Verdana",16), background="#044D9A", fg="white")
    labelLogin.place(x=220, y=60)
    labelUser = Label (ventanaReg, text ="Ingrese Usuario", font=("Verdana",16), background="#044D9A", fg="white")
    labelUser.place(x=50, y=200)
    labelPass = Label (ventanaReg, text ="Ingrese Contraseña", font=("Verdana",16), background="#044D9A", fg="white")
    labelPass.place(x=50, y=260)
    labelEdad = Label (ventanaReg, text ="Ingrese Edad", font=("Verdana",16), background="#044D9A", fg="white")
    labelEdad.place(x=50, y=320)
    textoUsuario = Text(ventanaReg, height=2, width=30, fg="white", font=("Consolas", 11)) 
    textoUsuario.place(x=230, y=190)
    textoPass = Text(ventanaReg, height=2, width=30, fg="white", font=("Consolas", 11))
    textoPass.place(x=230, y=255)
    textoEdad = Text(ventanaReg, height=2, width=30, fg="white", font=("Consolas", 11))
    textoEdad.place(x=230,y=330)
    btnRegistro = Button(ventanaReg, height=2, width=15, text="Registrar", command = lambda:prueba(textoUsuario.get(1.0, tk.END+"-1c"),textoPass.get(1.0, tk.END+"-1c"),textoEdad.get(1.0, tk.END+"-1c")), background="#368807", font=("Verdana",10), fg="black")
    btnRegistro.place(x=180, y=400)
    print("Btn Registrar")


def prueba(salida,salida2,salida3):
    res = requests.get(f'{base_url}/Registro/' + f'{salida}' + "/" + f'{salida2}' + "/" +  f'{salida3}')
    data = res.text#convertimos la respuesta en dict
    print(data)



#Registro/$nick/$contra/$edad"

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

btnRegistrar = Button(ventana, height=2, width=15, text="Registrar Usuario", command=registrarUsuarios, background="#10139E", font=("Verdana",10), fg="black")
btnRegistrar.place(x=180, y=210)

btnLogin = Button(ventana, height=2, width=15, text="Login",command=Login, background="#8E8C08", font=("Verdana",10), fg="black")
btnLogin.place(x=180, y=270)

btnSalir = Button(ventana, height=2, width=15, text="Salir",command=cerrar, background="#B03314", font=("Verdana",10), fg="black")
btnSalir.place(x=180, y=330)


#Labels
labelEditor = Label (ventana, text ="BATALLA NAVAL", font=("Verdana",16), background="#044D9A", fg="white")
labelEditor.place(x=180, y=90)


ventana.mainloop()