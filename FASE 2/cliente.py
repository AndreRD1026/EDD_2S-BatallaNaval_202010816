import requests
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
    except:
        MessageBox.showwarning("Alerta", "Debe cargar un archivo")
    

def Comprobar(salida,salida2,salida3):
    res = requests.get(f'{base_url}/Verificar/' + f'{salida}' + "/" + f'{salida2}' + "/" +  f'{salida3}')
    data = res.text#convertimos la respuesta en dict
    #print(data)

    if (data == "existe"):
        MessageBox.showinfo("Problema", "Ya existe un usuario con este Nick")
    if (data == "no existe"):
        mandarRegistro(salida,salida2,salida3)
        textoUsuario.delete(1.0, tk.END+"-1c")
        textoPass.delete(1.0, tk.END+"-1c")
        textoEdad.delete(1.0, tk.END+"-1c")
        ventanaReg.withdraw()

def ComprobarCambio(salidaa,salidaa2,salidaa3):
    res = requests.get(f'{base_url}/Verificar/' + f'{salidaa}' + "/" + f'{salidaa2}' + "/" +  f'{salidaa3}')
    data = res.text#convertimos la respuesta en dict
    #print(data)

    if (data == "existe"):
        MessageBox.showinfo("Problema", "El Nick ya esta en uso")
    if (data == "no existe"):
        MessageBox.showinfo("Exito!", "Para actualizar los cambios debe volver a iniciar sesion")
        textoUsuarioC.delete(1.0, tk.END+"-1c")
        textoPassC.delete(1.0, tk.END+"-1c")
        textoEdadC.delete(1.0, tk.END+"-1c")
        ventanaEdit.withdraw()
        ventanaUser.deiconify()



def mandarRegistro(salida,salida2,salida3):
    res = requests.get(f'{base_url}/Registro/' + f'{salida}' + "/" + f'{salida2}' + "/" +  f'{salida3}')
    data = res.text#convertimos la respuesta en dict
    #print(data)
    cerrandoRegistro()    
    

def cerrandoRegistro():
    print("llegando")
    MessageBox.showinfo("Exito!", "Usuario Registrado con exito")
    ventana.deiconify()


def mandarLogin(usuario, contra):
    print(usuario)
    print(contra)
    res = requests.get(f'{base_url}/Login/' + f'{usuario}' + "/" + f'{contra}')
    data = res.text#convertimos la respuesta en dict
    print(data)
    if (data == "admin"):
        ventanaLog.withdraw()
        MessageBox.showinfo("Exito!", "Inicio de sesion correcto")
        ventanaAdmin.deiconify()
    if (data == "correcto"):
        ventanaLog.withdraw()
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
    res = requests.get(f'{base_url}/Usuarios/')
    data = res.text#convertimos la respuesta en dict
    #print(data)
    im = Image.open('Pruebas.png')
    im.show()

def verArticulos():
    print("articulos")
    res = requests.get(f'{base_url}/Articulos/')
    data = res.text#convertimos la respuesta en dict
    print(data)
    im = Image.open('ListadeListas.png')
    im.show()

def verusuarioASC():
    res = requests.get(f'{base_url}/UsuariosASC/')
    data = res.text#convertimos la respuesta en dict
    #print(data)

def verusuarioDESC():
    res = requests.get(f'{base_url}/UsuariosDESC/')
    data = res.text#convertimos la respuesta en dict
    #print(data)

def EliminarCuenta():
    res = MessageBox.askquestion('Eliminar cuenta', '¿Esta seguro de eliminar esta cuenta?')
    if res == 'yes':
        MessageBox.showinfo('Cerrando Sesion', 'La cuenta ha sido eliminada')
        ventanaUser.withdraw()
        ventanaLog.deiconify()
    else:
        MessageBox.showinfo('Regresar', 'Regresando al menu')


def Tutorial():
    print("Tutorial")


def Partida():
    print("Partida")

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
btnRegistrar = Button(ventana, height=2, width=15, text="Registrar Usuario", command=lambda:[ ventana.withdraw(),ventanaReg.deiconify()], background="#10139E", font=("Verdana",10), fg="black")
btnRegistrar.place(x=180, y=210)
btnLogin = Button(ventana, height=2, width=15, text="Login",command=lambda:[ventana.withdraw(),ventanaLog.deiconify()], background="#8E8C08", font=("Verdana",10), fg="black")
btnLogin.place(x=180, y=270)
btnSalir = Button(ventana, height=2, width=15, text="Salir",command=cerrar, background="#B03314", font=("Verdana",10), fg="black")
btnSalir.place(x=180, y=330)
#Labels
labelEditor = Label (ventana, text ="BATALLA NAVAL", font=("Verdana",16), background="#044D9A", fg="white")
labelEditor.place(x=180, y=90)

#---------------------------------REGISTRO ------------------------------

ventanaReg = Toplevel()
ventanaReg.title("Registro Usuario")
ventanaReg.resizable(0,0)
ancho_ventana1 = 500
alto_ventana1 = 500
x_ventana1 = ventanaReg.winfo_screenwidth() // 2 - ancho_ventana1 // 2
y_ventana1 = ventanaReg.winfo_screenheight() // 2 - alto_ventana1 // 2
posicion1 = str(ancho_ventana1) + "x" + str(alto_ventana1) + "+" + str(x_ventana1) + "+" + str(y_ventana1)
ventanaReg.geometry(posicion1)
labelLogin = Label (ventanaReg, text ="Registro", font=("Verdana",16), background="#044D9A", fg="white")
labelLogin.place(x=210, y=80)
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
btnRegistro = Button(ventanaReg, height=2, width=15, text="Registrar", command = lambda:[Comprobar(textoUsuario.get(1.0, tk.END+"-1c"),textoPass.get(1.0, tk.END+"-1c"),textoEdad.get(1.0, tk.END+"-1c"))], background="#368807", font=("Verdana",10), fg="black")
btnRegistro.place(x=180, y=400)
btnRegreso = Button(ventanaReg, height=2, width=8, text="Regresar", command = lambda:[textoUsuario.delete(1.0, tk.END+"-1c"),textoPass.delete(1.0, tk.END+"-1c"),textoEdad.delete(1.0, tk.END+"-1c"), ventanaReg.withdraw(), ventana.deiconify()], background="#368807", font=("Verdana",10), fg="black")
btnRegreso.place(x=405, y=5)
ventanaReg.withdraw()


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
btnIniciar.place(x=110, y=410)
btnRegresar = Button(ventanaLog, height=2, width=15, text="Regresar", command = lambda:[ventana.deiconify(), ventanaLog.withdraw()], background="#368807", font=("Verdana",10), fg="black")
btnRegresar.place(x=270, y=410)
ventanaLog.withdraw()

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
btnOrdenAsc = Button(ventanaAdmin, height=2, width=22, text="Usuarios ordenados ascendente", command = lambda: [verusuarioASC()], background="#368807", font=("Verdana",10), fg="black")
btnOrdenAsc.place(x=160, y=300)
btnOrdenDesc = Button(ventanaAdmin, height=2, width=22, text="Usuarios ordenados descendente", command = lambda: [verusuarioDESC()], background="#368807", font=("Verdana",10), fg="black")
btnOrdenDesc.place(x=160, y=350)
btnTutorial = Button(ventanaAdmin, height=2, width=22, text="Tutorial del juego", command = lambda: [Tutorial()], background="#368807", font=("Verdana",10), fg="black")
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
btnEditar = Button(ventanaUser, height=2, width=15, text="Editar Informacion", command = lambda: [ventanaUser.withdraw(), ventanaEdit.deiconify()], background="#368807", font=("Verdana",10), fg="black")
btnEditar.place(x=180, y=200)
btnEliminarCuenta = Button(ventanaUser, height=2, width=15, text="Eliminar mi cuenta", command = lambda: [EliminarCuenta()], background="#368807", font=("Verdana",10), fg="black")
btnEliminarCuenta.place(x=180, y=250)
btnVerTutorial = Button(ventanaUser, height=2, width=15, text="Mostrar Tutorial", command = lambda: [Tutorial()], background="#368807", font=("Verdana",10), fg="black")
btnVerTutorial.place(x=180, y=300)
btnVerTienda = Button(ventanaUser, height=2, width=15, text="Tienda", command = lambda: [verArticulos()], background="#368807", font=("Verdana",10), fg="black")
btnVerTienda.place(x=180, y=350)
btnPartida = Button(ventanaUser, height=2, width=15, text="Iniciar Partida", command = lambda: [Partida()], background="#368807", font=("Verdana",10), fg="black")
btnPartida.place(x=180, y=400)
btncerrarSesionUser = Button(ventanaUser, height=2, width=15, text="Cerrar Sesion", command = lambda: [ventanaUser.withdraw(),MessageBox.showinfo("Exito", "Sesion cerrada"), ventanaLog.deiconify()], background="#368807", font=("Verdana",10), fg="black")
btncerrarSesionUser.place(x=180, y=450)
ventanaUser.withdraw()

#--------------------------------- EDITAR USUARIO ------------------------------

ventanaEdit = Toplevel()
ventanaEdit.title("Actualizacion de Datos")
ventanaEdit.resizable(0,0)
ancho_ventana1 = 500
alto_ventana1 = 500
x_ventana1 = ventanaEdit.winfo_screenwidth() // 2 - ancho_ventana1 // 2
y_ventana1 = ventanaEdit.winfo_screenheight() // 2 - alto_ventana1 // 2
posicion1 = str(ancho_ventana1) + "x" + str(alto_ventana1) + "+" + str(x_ventana1) + "+" + str(y_ventana1)
ventanaEdit.geometry(posicion1)
bgc = PhotoImage(file="Python/usuario.png")
labelPhotoC = Label(ventanaEdit, image=bgc)
labelPhotoC.place(x=150,y=30)
labelUserC = Label (ventanaEdit, text ="NICK", font=("Verdana",16), background="#044D9A", fg="white")
labelUserC.place(x=100, y=215)
labelPassC = Label (ventanaEdit, text ="Contra", font=("Verdana",16), background="#044D9A", fg="white")
labelPassC.place(x=100, y=280)
labelEdadC = Label (ventanaEdit, text ="Edad", font=("Verdana",16), background="#044D9A", fg="white")
labelEdadC.place(x=100, y=345)
textoUsuarioC = Text(ventanaEdit, height=2, width=30 ,fg="white", font=("Consolas", 12)) 
textoUsuarioC.place(x=210, y=210)
textoPassC = Text(ventanaEdit, height=2, width=30, fg="white", font=("Consolas", 12)) 
textoPassC.place(x=210, y=270)
textoEdadC = Text(ventanaEdit, height=2, width=30 ,fg="white", font=("Consolas", 12)) 
textoEdadC.place(x=210, y=340)
btnGuardarC = Button(ventanaEdit, height=2, width=15, text="Guardar Cambios", command = lambda:[ComprobarCambio(textoUsuarioC.get(1.0, tk.END+"-1c"), textoPassC.get(1.0, tk.END+"-1c"), textoEdadC.get(1.0, tk.END+"-1c"))], background="#368807", font=("Verdana",10), fg="black")
btnGuardarC.place(x=110, y=420)
btnRegresarC = Button(ventanaEdit, height=2, width=15, text="Regresar", command = lambda:[ventanaUser.deiconify(), ventanaEdit.withdraw()], background="#368807", font=("Verdana",10), fg="black")
btnRegresarC.place(x=270, y=420)
ventanaEdit.withdraw()


#--------------------------------- INICIANDO INTERFAZ------------------------------
ventana.mainloop()