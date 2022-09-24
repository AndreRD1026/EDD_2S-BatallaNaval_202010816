from os import system
from tkinter import*
import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox as MessageBox
from tkinter.font import families
import sys

def abrirArchvo1():
    global archivo, textoLeido, archivos_texto

    try:
        archivo = filedialog.askopenfilename(title="Seleccionar archivo", filetypes=[("json", "*.json")])
        archivos_texto = open(archivo, 'r')
        textoLeido = archivos_texto.read()
        print(textoLeido)
    except:
        MessageBox.showwarning("Alerta", "Debe cargar un archivo")
    
def registrarUsuarios():
    print("Btn Registrar")
    
def Login():
    ventanaLog = Tk()
    ventanaLog.title("Login")
    ventanaLog.resizable(0,0)
    ancho_ventana1 = 500
    alto_ventana1 = 500
    x_ventana1 = ventanaLog.winfo_screenwidth() // 2 - ancho_ventana1 // 2
    y_ventana1 = ventanaLog.winfo_screenheight() // 2 - alto_ventana1 // 2
    posicion1 = str(ancho_ventana1) + "x" + str(alto_ventana1) + "+" + str(x_ventana1) + "+" + str(y_ventana1)
    ventanaLog.geometry(posicion1)
    btnIniciar = Button(ventanaLog, height=2, width=15, text="Iniciar Sesion", command = "", background="#368807", font=("Verdana",10), fg="black")
    btnIniciar.place(x=180, y=400)
    labelLogin = Label (ventanaLog, text ="Login", font=("Verdana",16), background="#044D9A", fg="white")
    labelLogin.place(x=180, y=90)
    labelUser = Label (ventanaLog, text ="Ingrese Usuario", font=("Verdana",16), background="#044D9A", fg="white")
    labelUser.place(x=50, y=220)
    labelPass = Label (ventanaLog, text ="Ingrese Contraseña", font=("Verdana",16), background="#044D9A", fg="white")
    labelPass.place(x=50, y=280)

    textoUsuario = Text(ventanaLog, height=2, width=30, fg="white", font=("Consolas", 11)) 
    textoUsuario.place(x=230, y=210)
    textoPass = Entry(ventanaLog, fg="white", show="*", font=("Consolas", 11)) 
    textoPass.place(height=2, width=30, x=230, y=270)
    
    print("Btn Login")

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
btnCargarArchivo = Button(ventana, height=2, width=15, text="Cargar Usuarios", command = abrirArchvo1, background="#368807", font=("Verdana",10), fg="black")
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