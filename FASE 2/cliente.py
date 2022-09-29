import requests##pip3 install request
import json
from tkinter import*
import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox as MessageBox
import sys
import os
from PIL import Image

pruebaa = None

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
        #print(archivo)
        prueba = os.path.split(archivo)
        #print(prueba)
        res = requests.post(f'{base_url}/Carga/' + f'{prueba[1]}')
        data = res.text#convertimos la respuesta en dict
        print(data)
        MessageBox.showinfo("Exito!", "Archivo Cargado con exito")
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
    btnRegistro = Button(ventanaReg, height=2, width=15, text="Registrar", command = lambda:[mandarRegistro(textoUsuario.get(1.0, tk.END+"-1c"),textoPass.get(1.0, tk.END+"-1c"),textoEdad.get(1.0, tk.END+"-1c")), ventanaReg.withdraw()], background="#368807", font=("Verdana",10), fg="black")
    btnRegistro.place(x=180, y=400)


def mandarRegistro(salida,salida2,salida3):
    res = requests.get(f'{base_url}/Registro/' + f'{salida}' + "/" + f'{salida2}' + "/" +  f'{salida3}')
    data = res.text#convertimos la respuesta en dict
    
    cerrandoRegistro()
    '''
    if (data == "falso"):
        MessageBox.showinfo("Advertencia!", "Ya existe un usuario con ese nick")
    if (data == "true"):
        MessageBox.showinfo("Exito!", "Usuario Registrado con exito")
        ventana.deiconify()
    if (data == "true2"):
        MessageBox.showinfo("Exito2!", "Usuario Registrado con exito")
        ventana.deiconify()
    '''
    
    print(data)

def cerrandoRegistro():
    print("llegando")
    MessageBox.showinfo("Exito!", "Usuario Registrado con exito")
    ventana.deiconify()

def mandarLogin(usuario, contra):
    print(usuario)
    print(contra)
    #pruebaa = usuario
    res = requests.get(f'{base_url}/Login/' + f'{usuario}' + "/" + f'{contra}')
    data = res.text#convertimos la respuesta en dict
    print(data)
    if (data == "admin"):
        ventanaLog.withdraw()
        MessageBox.showinfo("Exito!", "Inicio de sesion correcto")
        ventanaAdmin.deiconify()
    if (data == "correcto"):
        ventanaUser.withdraw()
        MessageBox.showinfo("Exito!", "Inicio de sesion correcto")
        ventanaUser.deiconify()
    if (data == "incorrecto"):
        MessageBox.showinfo("Error!", "Usuario o contraseña incorrectos")
        ventanaLog.deiconify()
    if (data == "inexistente"):
        MessageBox.showinfo("Inesperado!", "El usuario no existe")
        ventanaLog.deiconify()



def mandarDatos(usuario):
    global pruebaa
    res = requests.get(f'{base_url}/Log/' + f'{usuario}')
    data = res.text#convertimos la respuesta en dict
    pruebaa = data
    print(data)


def verusuario():
    print("usuarios")
    res = requests.get(f'{base_url}/Usuarios/')
    data = res.text#convertimos la respuesta en dict
    print(data)
    im = Image.open('Pruebas.png')
    im.show()

def verArticulos():
    print("articulos")
    res = requests.get(f'{base_url}/Articulos/')
    data = res.text#convertimos la respuesta en dict
    print(data)
    im = Image.open('ListadeListas.png')
    im.show()

def cerrar():
    MessageBox.showinfo("Adios", "Gracias por usar el programa")
    sys.exit()

#---------------------------------VENTANA PRINCIPAL ------------------------------

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

btnRegistrar = Button(ventana, height=2, width=15, text="Registrar Usuario", command=lambda:[ ventana.withdraw(),registrarUsuarios()], background="#10139E", font=("Verdana",10), fg="black")
btnRegistrar.place(x=180, y=210)

btnLogin = Button(ventana, height=2, width=15, text="Login",command=lambda:[ventana.withdraw(),ventanaLog.deiconify()], background="#8E8C08", font=("Verdana",10), fg="black")
btnLogin.place(x=180, y=270)

btnSalir = Button(ventana, height=2, width=15, text="Salir",command=cerrar, background="#B03314", font=("Verdana",10), fg="black")
btnSalir.place(x=180, y=330)


#Labels
labelEditor = Label (ventana, text ="BATALLA NAVAL", font=("Verdana",16), background="#044D9A", fg="white")
labelEditor.place(x=180, y=90)



#---------------------------------LOGIN ------------------------------

ventanaLog = Toplevel()
ventanaLog.title("Login")
ventanaLog.resizable(0,0)
ancho_ventana1 = 500
alto_ventana1 = 500
x_ventana1 = ventanaLog.winfo_screenwidth() // 2 - ancho_ventana1 // 2
y_ventana1 = ventanaLog.winfo_screenheight() // 2 - alto_ventana1 // 2
posicion1 = str(ancho_ventana1) + "x" + str(alto_ventana1) + "+" + str(x_ventana1) + "+" + str(y_ventana1)
ventanaLog.geometry(posicion1)
bgL = PhotoImage(file="Python/user.png")
labelPhotoL = Label(ventanaLog, image=bgL)
labelPhotoL.place(x=150,y=30)
labelLogin = Label (ventanaLog, text ="Login", font=("Verdana",16), background="#044D9A", fg="white")
labelLogin.place(x=230, y=200)
labelUser = Label (ventanaLog, text ="Ingrese Usuario", font=("Verdana",16), background="#044D9A", fg="white")
labelUser.place(x=40, y=280)
labelPass = Label (ventanaLog, text ="Ingrese Contraseña", font=("Verdana",16), background="#044D9A", fg="white")
labelPass.place(x=40, y=340)
textoUsuarioL = Text(ventanaLog, height=2, width=30, fg="white", font=("Consolas", 12)) 
textoUsuarioL.place(x=220, y=270)
textoPassL = Entry(ventanaLog, fg="white", show="*", font=("Consolas", 12), width=30) 
textoPassL.place(x=220, y=340)

btnIniciar = Button(ventanaLog, height=2, width=15, text="Iniciar Sesion", command = lambda:[mandarLogin(textoUsuarioL.get(1.0, tk.END+"-1c"), textoPassL.get()), textoUsuarioL.delete(1.0, tk.END+"-1c"), textoPassL.delete(0, tk.END)], background="#368807", font=("Verdana",10), fg="black")
btnIniciar.place(x=180, y=400)
ventanaLog.withdraw()


#---------------------------------SUB LOGIN ------------------------------

ventanaSubLog = Tk()
ventanaSubLog.title("Sub_Login")
ventanaSubLog.resizable(0,0)
ancho_ventana1 = 500
alto_ventana1 = 500
x_ventana1 = ventanaSubLog.winfo_screenwidth() // 2 - ancho_ventana1 // 2
y_ventana1 = ventanaSubLog.winfo_screenheight() // 2 - alto_ventana1 // 2
posicion1 = str(ancho_ventana1) + "x" + str(alto_ventana1) + "+" + str(x_ventana1) + "+" + str(y_ventana1)
ventanaSubLog.geometry(posicion1)
btnIniciar = Button(ventanaSubLog, height=2, width=15, text="Editar Info", command = lambda: [ventanaSubLog.withdraw(), ventanaLog.deiconify()], background="#368807", font=("Verdana",10), fg="black")
btnIniciar.place(x=180, y=400)
labelLogin = Label (ventanaSubLog, text =pruebaa, font=("Verdana",16), background="#044D9A", fg="white")
labelLogin.place(x=180, y=90)
labelUser = Label (ventanaSubLog, text ="Usuario", font=("Verdana",16), background="#044D9A", fg="white")
labelUser.place(x=50, y=220)
labelPass = Label (ventanaSubLog, text ="Contraseña", font=("Verdana",16), background="#044D9A", fg="white")
labelPass.place(x=50, y=280)
textoUsuarioSL = Text(ventanaSubLog, height=2, width=30, fg="white", font=("Consolas", 11)) 
textoUsuarioSL.place(x=230, y=210)
textoPassSL = Entry(ventanaSubLog, fg="white", show="*", font=("Consolas", 11), width=30) 
textoPassSL.place(x=230, y=275)
ventanaSubLog.withdraw()


#--------------------------------- ADMIN ------------------------------

ventanaAdmin = Toplevel()
ventanaAdmin.title("ADMINISTRADOR")
ventanaAdmin.resizable(0,0)

ancho_ventana1 = 500
alto_ventana1 = 500
x_ventana1 = ventanaAdmin.winfo_screenwidth() // 2 - ancho_ventana1 // 2
y_ventana1 = ventanaAdmin.winfo_screenheight() // 2 - alto_ventana1 // 2
posicion1 = str(ancho_ventana1) + "x" + str(alto_ventana1) + "+" + str(x_ventana1) + "+" + str(y_ventana1)
ventanaAdmin.geometry(posicion1)
bg = PhotoImage(file="Python/admin.png")
labelPhoto = Label(ventanaAdmin, image=bg)
labelPhoto.place(x=150,y=30)
btnUser = Button(ventanaAdmin, height=2, width=22, text="Lista de usuarios", command = lambda: [verusuario()], background="#368807", font=("Verdana",10), fg="black")
btnUser.place(x=160, y=200)
btnArticulos = Button(ventanaAdmin, height=2, width=22, text="Lista de articulos", command = lambda: [verArticulos()], background="#368807", font=("Verdana",10), fg="black")
btnArticulos.place(x=160, y=250)
btnOrdenAsc = Button(ventanaAdmin, height=2, width=22, text="Usuarios ordenados ascendente", command = lambda: [ventanaAdmin.withdraw(), ventanaLog.deiconify()], background="#368807", font=("Verdana",10), fg="black")
btnOrdenAsc.place(x=160, y=300)
btnOrdenDesc = Button(ventanaAdmin, height=2, width=22, text="Usuarios ordenados descendente", command = lambda: [ventanaAdmin.withdraw(), ventanaLog.deiconify()], background="#368807", font=("Verdana",10), fg="black")
btnOrdenDesc.place(x=160, y=350)
btnTutorial = Button(ventanaAdmin, height=2, width=22, text="Tutorial del juego", command = lambda: [ventanaAdmin.withdraw(), ventanaLog.deiconify()], background="#368807", font=("Verdana",10), fg="black")
btnTutorial.place(x=160, y=400)
btnCerrarSesionAdmin = Button(ventanaAdmin, height=2, width=22, text="Cerrar Sesion", command = lambda: [ventanaLog.deiconify(),MessageBox.showinfo("Exito", "Sesion cerrada") , ventanaAdmin.withdraw()], background="#368807", font=("Verdana",10), fg="black")
btnCerrarSesionAdmin.place(x=160, y=450)


ventanaAdmin.withdraw()


#--------------------------------- USUARIOS ------------------------------

ventanaUser = Toplevel()
ventanaUser.title("Principal")
ventanaUser.resizable(0,0)
ancho_ventana1 = 500
alto_ventana1 = 500
x_ventana1 = ventanaUser.winfo_screenwidth() // 2 - ancho_ventana1 // 2
y_ventana1 = ventanaUser.winfo_screenheight() // 2 - alto_ventana1 // 2
posicion1 = str(ancho_ventana1) + "x" + str(alto_ventana1) + "+" + str(x_ventana1) + "+" + str(y_ventana1)
ventanaUser.geometry(posicion1)
bgUser = PhotoImage(file="Python/usuario.png")
labelPhotoUser = Label(ventanaUser, image=bgUser)
labelPhotoUser.place(x=150,y=30)
btnEditar = Button(ventanaUser, height=2, width=15, text="Editar Informacion", command = lambda: [ventanaUser.withdraw(), ventanaLog.deiconify()], background="#368807", font=("Verdana",10), fg="black")
btnEditar.place(x=180, y=200)
btnEliminarCuenta = Button(ventanaUser, height=2, width=15, text="Eliminar mi cuenta", command = lambda: [ventanaUser.withdraw(), ventanaLog.deiconify()], background="#368807", font=("Verdana",10), fg="black")
btnEliminarCuenta.place(x=180, y=250)
btnVerTutorial = Button(ventanaUser, height=2, width=15, text="Mostrar Tutorial", command = lambda: [ventanaUser.withdraw(), ventanaLog.deiconify()], background="#368807", font=("Verdana",10), fg="black")
btnVerTutorial.place(x=180, y=300)
btnVerTienda = Button(ventanaUser, height=2, width=15, text="Tienda", command = lambda: [ventanaUser.withdraw(), ventanaLog.deiconify()], background="#368807", font=("Verdana",10), fg="black")
btnVerTienda.place(x=180, y=350)
btnPartida = Button(ventanaUser, height=2, width=15, text="Iniciar Partida", command = lambda: [ventanaUser.withdraw(), ventanaLog.deiconify()], background="#368807", font=("Verdana",10), fg="black")
btnPartida.place(x=180, y=400)
btncerrarSesionUser = Button(ventanaUser, height=2, width=15, text="Cerrar Sesion", command = lambda: [ventanaUser.withdraw(), ventanaLog.deiconify()], background="#368807", font=("Verdana",10), fg="black")
btncerrarSesionUser.place(x=180, y=450)
'''
labelLogin = Label (ventanaUser, text = "Nick" , font=("Verdana",16), background="#044D9A", fg="white")
labelLogin.place(x=180, y=90)
labelUser = Label (ventanaUser, text ="Usuario", font=("Verdana",16), background="#044D9A", fg="white")
labelUser.place(x=50, y=220)
labelPass = Label (ventanaUser, text ="Contraseña", font=("Verdana",16), background="#044D9A", fg="white")
labelPass.place(x=50, y=280)
labelEdad = Label (ventanaUser, text ="Edad", font=("Verdana",16), background="#044D9A", fg="white")
labelEdad.place(x=50, y=340)
labelNick = Label(ventanaUser, height=2, width=30, fg="white", font=("Consolas", 11)) 
labelNick.place(x=230, y=210)
'''

ventanaUser.withdraw()


ventana.mainloop()