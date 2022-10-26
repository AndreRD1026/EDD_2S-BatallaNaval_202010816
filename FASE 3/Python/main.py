import sys
import json
from tkinter import*
import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox as MessageBox
import matplotlib.pyplot as plt
import plotly.graph_objects as go 
import random
import os
import numpy as np
import pandas as pd
from PIL import Image, ImageTk
import requests
from usuario import Usuario
from articulos import Articulo
import hashlib
from MatrizDispersa import MatrizDispersa
from ListaAdyacente import ListaDG
from prettytable import PrettyTable

matrizD = MatrizDispersa(0)
matriz2 = MatrizDispersa(0)
matrizAct1 = MatrizDispersa(0)
matrizAct2 = MatrizDispersa(0)
matrizFinal1 = MatrizDispersa(0)
matrizFinal2 = MatrizDispersa(0)
ListaAdy = ListaDG()

ListaUsuarios = []
ListaArticulos = []
ListaCarrito = []

contauser = 1
contadorcarrito = 0
contadortotal = 0

base_url = "http://127.0.0.1:8080/"


admincifrado = hashlib.sha256("edd123".encode('utf-8')).hexdigest()
administrador =Usuario(0,"EDD","edd123",0,50,admincifrado)
ListaUsuarios.append(administrador)

#------------------------------FUNCIONES DEL PROGRAMA-------------------------------

def abrirArchivo1():
    try:
        global archivo
        archivo = filedialog.askopenfilename(title="Seleccionar archivo", filetypes=[("json", "*.json")])
        #print(archivo)
        otro = open(archivo)
        otro1 = otro.read()
        dicc = json.loads(otro1)
        for usser in dicc['usuarios'] :
            iduser = usser['id']
            nickuser = usser['nick']
            passnormal = usser['password']
            monedasuser = usser['monedas']
            edaduser = usser['edad']
            passcifrada=hashlib.sha256(passnormal.encode('utf-8')).hexdigest()
            nuevouser = Usuario(iduser,nickuser,passnormal,monedasuser,edaduser,passcifrada)
            ListaUsuarios.append(nuevouser)

        for arrt in dicc['articulos'] :
            idArticulo = arrt['id']
            catArticulo = arrt['categoria']
            precioArticulo = arrt['precio']
            nombreArticulo = arrt['nombre']
            SRCArticulo = arrt['src']
            nuevoArticulo = Articulo(idArticulo,catArticulo,precioArticulo,nombreArticulo,SRCArticulo)
            ListaArticulos.append(nuevoArticulo)
        MessageBox.showinfo("Exito!", "Archivo Cargado con exito")
    except:
        MessageBox.showwarning("Alerta", "Debe cargar un archivo")

def Comprobar(salida,salida2,salida3):

    for uss in ListaUsuarios:
        if salida == uss.nick:
            return True
    return False


def RegistroUser():
    validar = Comprobar(textoUsuario.get(1.0, tk.END+"-1c"),textoPass.get(1.0, tk.END+"-1c"),textoEdad.get(1.0, tk.END+"-1c"))
    if validar == False:
        iduser = 1
        nickuser = textoUsuario.get(1.0, tk.END+"-1c")
        passnormal = textoPass.get(1.0, tk.END+"-1c")
        monedasuser = 0
        eddaduser = textoEdad.get(1.0, tk.END+"-1c")
        passcifrada=hashlib.sha256(passnormal.encode('utf-8')).hexdigest()
        nuevoRegistro = Usuario(iduser,nickuser,passnormal,monedasuser,eddaduser,passcifrada)
        ListaUsuarios.append(nuevoRegistro)
        textoUsuario.delete(1.0, tk.END+"-1c")
        textoPass.delete(1.0, tk.END+"-1c")
        textoEdad.delete(1.0, tk.END+"-1c")
        ventanaReg.withdraw()
        cerrandoRegistro()
    if validar == True:
        MessageBox.showinfo("Problema", "Ya existe un usuario con este Nick")
    
def ComprobarCambio(salidaa,salidaa2,salidaa3):

    if usuariobusqueda == salidaa:
        res = requests.get(f'{base_url}/Modificando/' + f'{usuariobusqueda}' + "/" + f'{salidaa}' + "/" + f'{salidaa2}' + "/" + f'{salidaa3}')
        MessageBox.showinfo("Exito!", "Para actualizar los cambios debe volver a iniciar sesion")
        textoUsuarioC.delete(1.0, tk.END+"-1c")
        textoPassC.delete(1.0, tk.END+"-1c")
        textoEdadC.delete(1.0, tk.END+"-1c")
        ventanaEdit.withdraw()
        ventanaUser.deiconify()
        #print("No se cambio el usuario")
    else:
        res = requests.get(f'{base_url}/Verificar/' + f'{salidaa}' + "/" + f'{salidaa2}' + "/" +  f'{salidaa3}')
        data = res.text#convertimos la respuesta en dict

        datos_diccionario2 = json.loads(data)
        #idd1 = datos_diccionario2["Id"]
        est1 = datos_diccionario2["estado"]

        if est1 == "existe":
            MessageBox.showinfo("Problema", "El Nick ya esta en uso")
        if est1 == "no existe":
            res = requests.get(f'{base_url}/Eliminar/' + f'{usuariobusqueda}')
            data = res.text
            datos_diccionario3 = json.loads(data)
            idd2 = datos_diccionario3["Id"]
            #print("Sale? " + idd2)
            res = requests.get(f'{base_url}/Modificando/' + f'{usuariobusqueda}' + "/" + f'{salidaa}' + "/" + f'{salidaa2}' + "/" + f'{salidaa3}' "/" + f'{idd2}')
            MessageBox.showinfo("Exito!", "Para actualizar los cambios debe volver a iniciar sesion")
            textoUsuarioC.delete(1.0, tk.END+"-1c")
            textoPassC.delete(1.0, tk.END+"-1c")
            textoEdadC.delete(1.0, tk.END+"-1c")
            ventanaEdit.withdraw()
            ventanaUser.deiconify()

def mandarRegistro(salida,salida2,salida3):
    res = requests.get(f'{base_url}/Registro/' + f'{salida}' + "/" + f'{salida2}' + "/" +  f'{salida3}')
    data = res.text#convertimos la respuesta en dict
    cerrandoRegistro()    

def cerrandoRegistro():
    MessageBox.showinfo("Exito!", "Usuario Registrado con exito")
    ventana.deiconify()


def verificarLogin(usuario, contra):
    global usuariologin, contralogin,edadlogin,monedaslogin
    cifrada = hashlib.sha256(contra.encode('utf-8')).hexdigest()
    for uss in ListaUsuarios:
        if usuario == uss.nick and cifrada == uss.passcifrada:
            if usuario == "EDD":
                usuariologin = usuario
                contralogin = uss.passw
                edadlogin = uss.edad
                monedaslogin = uss.monedas
                return True
            else:
                usuariologin = usuario
                contralogin = uss.passw
                edadlogin = uss.edad
                monedaslogin = uss.monedas
                return "Normal"
    return False

def mandarLogin(usuario,contra):
    global usuariobusqueda, monedasusuario
    verificado = verificarLogin(usuario,contra)
    if verificado == True:
        ventanaLog.withdraw() 
        MessageBox.showinfo("Exito!", "Inicio de sesion correcto")
        ventanaAdmin.deiconify()
    if verificado == "Normal":
        ventanaLog.withdraw()
        MessageBox.showinfo("Exito!", "Inicio de sesion correcto")
        textoUsuarioC.insert(INSERT, usuariologin)
        textoPassC.insert(INSERT, contralogin)
        textoEdadC.insert(INSERT,edadlogin)
        usuariobusqueda = usuariologin
        monedasusuario = int(monedaslogin)
        ventanaUser.deiconify()
        print("Monedas usuario : ", monedaslogin)
    if verificado == False:
        MessageBox.showinfo("Error!", "Usuario o contraseña incorrectos")
        ventanaLog.deiconify()

def mandarDatos(usuario):
    res = requests.get(f'{base_url}/Log/' + f'{usuario}')
    data = res.text#convertimos la respuesta en dict
    print(data)

def verusuario():
    res = requests.get(f'{base_url}/Usuarios/')
    data = res.text#convertimos la respuesta en dict
    #print(data)
    im = Image.open('Arbol.png')
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
    res = requests.get(f'{base_url}/Eliminar/' + f'{usuariobusqueda}')
    data = res.text

    #print(data)
    datos_diccionario1 = json.loads(data)
    idd = datos_diccionario1["Id"]
    est = datos_diccionario1["estado"]
    if est == "encontrado":
        res = requests.get(f'{base_url}/Eliminando/' + f'{usuariobusqueda}' + "/" + f'{idd}')
        data = res.text
        mes = MessageBox.askquestion('Eliminar cuenta', '¿Esta seguro de eliminar esta cuenta?')
        if mes == 'yes':
            MessageBox.showinfo('Cerrando Sesion', 'La cuenta ha sido eliminada')
            ventanaUser.withdraw()
            ventanaLog.deiconify()
        else:
            MessageBox.showinfo('Regresar', 'Regresando al menu')

def Tutorial():
    res = requests.get(f'{base_url}/Tutorial/')
    data = res.text#convertimos la respuesta en dict
    im = Image.open('GraficoTutorial.png')
    im.show()
    print("Tutorial")


#--------------------------------Tienda--------------------------------
def MostrarTienda():
    #print("Tienda")
    print(monedasusuario)
    global ides
    res = requests.get(f'{base_url}/Tienda/')
    data = res.text#convertimos la respuesta en dict
    #print(data)
    articulos = json.loads(data)

    idAr = []
    nombresAr = []
    cateAr =[]
    precioAr = []
    for articulo in articulos:
        ides = articulo.get('Id')
        nombr = articulo.get('nombre')
        catt = articulo.get('categoria')
        prec = articulo.get('precio')
        #print(articulo.get('Id'))
        #print(articulo.get('categoria'))
        #print(articulo.get('precio'))
        #print(articulo.get('nombre'))
        
        idAr.append(ides)
        nombresAr.append(nombr)
        cateAr.append(catt)
        precioAr.append(prec)

    fig = go.Figure(data=[go.Table(
        
        header=dict(values=['ID','Nombre','Categoria','Precio']), 
        cells=dict(values=[idAr,nombresAr,cateAr,precioAr
                    ])) 
            ])
    fig.update_layout(title = "Tienda", title_x=0.5)
    fig.show()


def GraficoTienda():
    #definir figura y ejes
    fig, ax = plt.subplots()
    idAr1 = []
    nombresAr = []
    categArt = []
#crear valores para la tabla
    for art in ListaArticulos:
        print(art.idArticulo)
        ides = art.idArticulo
        cates = art.categoriaArticulo
        idAr1.append(ides)
        categArt.append(cates)
        table_data = [[idAr1, categArt]]
    columns = ("ID", "Categoria")


    
    
    '''table_data = [ ["Id", "Nombre"],
        ["Jugador 1", 30],
        ["Jugador 2", 20],
        ["Jugador 3", 33],
        ["Jugador 4", 25],
        ["Jugador 5", 12]
    ]'''

    #create table
    table = ax.table(cellText = table_data, loc = 'center')

    #modificar tabla de
    table.set_fontsize (14)
    table.scale(1,4)
    ax.axis('off')

    #plt.table(cellText=table_data, colLabels=columns, loc="bottom")

    #display table
    plt.show()
    print("hola")

def GraficoTiendaaa():
    global lblcontador, ventanaTiend, salida1
    salida1 = 0
    lblcontador = salida1
    ventanaTiend = Toplevel()
    ventanaTiend.title("Tienda")
    ancho_ventanaTienda = 1000
    alto_ventanaTienda = 800
    x_ventanaTienda = ventanaTiend.winfo_screenwidth() // 2 - ancho_ventanaTienda // 2
    y_ventanaTienda = ventanaTiend.winfo_screenheight() // 2 - alto_ventanaTienda // 2
    posicionTienda = str(ancho_ventanaTienda) + "x" + str(alto_ventanaTienda) + "+" + str(x_ventanaTienda) + "+" + str(y_ventanaTienda)
    ventanaTiend.geometry(posicionTienda)
    scrollbar = Scrollbar(ventanaTiend)
    scrollbar.pack( side = RIGHT, fill = Y )
    '''Imprime una tabla con los errores'''
    text = '\t'
    x = PrettyTable()
    x.field_names = ["ID","NOMBRE","CATEGORIA", "PRECIO"]

    for aart in ListaArticulos:
        idesArt = aart.idArticulo
        nombresArt = aart.nombreArticulo
        catesArt = aart.categoriaArticulo
        precArt = aart.precioArticulo
        x.add_row([idesArt, nombresArt, catesArt, precArt])
    text = x
    lbltabla = Label(ventanaTiend, text =text, font=("Verdana",16), background="white", fg="black")
    lbltabla.place(x=20, y=60)
    lblname = Label(ventanaTiend, text ="Usuario: " + usuariologin, font=("Verdana",16), background="white", fg="black")
    lblname.place(x=600, y=60)
    lbltok = Label(ventanaTiend, text ="Monedas: " + monedaslogin, font=("Verdana",16), background="white", fg="black")
    lbltok.place(x=600, y=100)
    lblcar = Label(ventanaTiend, text ="Carrito: " + str(contadorcarrito), font=("Verdana",16), background="red", fg="white")
    lblcar.place(x=750, y=60)
    lblcar = Label(ventanaTiend, text ="Total: " + str(lblcontador), font=("Verdana",16), background="red", fg="white")
    lblcar.place(x=750, y=100)
    btnbuscarid = Button(ventanaTiend, height=2, width=16, text="Elegir articulo", command = lambda:[elegir()], background="#368807", font=("Verdana",10), fg="black")
    btnbuscarid.place(x=600, y=150)


def elegir():
    global pruebaconta, contadortotal, salida1
    pruebaconta = 0
    pruebaconta += 1
    salida1 += 1
    contadortotal = pruebaconta
    print("Sale? ", salida1)
    ventanaTiend.destroy()
    GraficoTiendaaa()

    #contadortotal += 1

#-------------------------------GUARDANDO DATOS PARA VOLVER A JUGAR-------------------------

def GuardarConfiguracion():
    global nombrejugador2, dimensionestablero
    nombrejugador2 = textoNombre.get(1.0, tk.END+"-1c")
    dimensionestablero = textoDimension.get(1.0,tk.END+"-1c")

#---------------------------------CREACION DEL JUEGO 2.0 ------------------------------
def Partida():
    global Portaaviones, Submarino, Destructores, Buques, TotalBarcos, nuevocontador, nuevocontador2
    global totalmonedas,tokensjugador, totalmonedas2, tokensjugador2, jugador2
    global FILAS, COLUMNAS, MAR
    global BUQUE, DESTRUCTOR, SUBMARINO, DESTRUCTOR_VERTICAL, SUBMARINO_VERTICAL
    global PORTAAVIONES, PORTAAVIONES_VERTICAL, DISPARO_FALLADO, DISPARO_ACERTADO
    global JUGADOR_1, JUGADOR_2

    ventanaUser.withdraw()
    ListaAdy.crear(int(dimensionestablero))
    #jugador2 = textoNombre.get(1.0, tk.END+"-1c")
    for x in range(int(dimensionestablero)):
        ListaAdy.insertar(x,x)
        #print("X?", x)

    jugador2 = nombrejugador2
    
    MAR = " "
    BUQUE = "B"  # Ocupa una celda
    DESTRUCTOR = "D"  # Ocupa dos celdas
    SUBMARINO = "S" # Ocupa tres celdas
    DESTRUCTOR_VERTICAL = "A"  # Ocupa dos celdas
    SUBMARINO_VERTICAL = "C" # Ocupa tres celdas
    PORTAAVIONES = "P" # Ocupa cuatro celdas
    PORTAAVIONES_VERTICAL = "V" # Ocupa cuatro celdas
    DISPARO_FALLADO = "E"
    DISPARO_ACERTADO = "*"
    #CANTIDAD_BARCOS_INICIALES = 10
    JUGADOR_1 = usuariobusqueda
    JUGADOR_2 = jugador2
    Portaav = 1
    Subma = 2
    Destruc = 3
    Buq = 4
    # Formula para determinar la cantidad de barcos por tablero
    # B(m) = ((m-1)/10)+1
    #dimens = textoDimension.get(1.0,tk.END+"-1c")
    dimens = dimensionestablero
    dimen = int(dimens)
    if dimen<10:
        MessageBox.showerror("Advertencia", "El Numero minimo para el tablero es de 10")
    if dimen==10:
        FILAS = dimen
        COLUMNAS = dimen
        ventanaObtenerDimension.withdraw() 
        textoDimension.delete(1.0, tk.END+"-1c")
        textoNombre.delete(1.0, tk.END+"-1c")
        vidas = 3
        B = int(((dimen-1)/10))+1
        #print(B)
        Portaaviones = Portaav * B
        Submarino = Subma * B
        Destructores = Destruc * B
        Buques = Buq * B
        # print("Portaaviones: ", Portaaviones)
        # print("Submarinos : ", Submarino)
        # print("Destructores: ", Destructores)
        # print("Buques : " , Buques)
        TotalBarcos = Portaaviones + Submarino + Destructores + Buques
        otroB = TotalBarcos
        nuevocontador = otroB
        nuevocontador2 = otroB
        totalmonedas = monedasusuario
        pasarmoneda = totalmonedas
        tokensjugador = pasarmoneda
        totalmonedas2 = 0
        pasarmoneda2 = totalmonedas2
        tokensjugador2 = pasarmoneda2
        MessageBox.showinfo("Exito", "Tablero creado con exito")
        creartableros()
        pruebanueva()
    if dimen>10 and dimen <= 20:
        FILAS = dimen
        COLUMNAS = dimen
        ventanaObtenerDimension.withdraw() 
        textoDimension.delete(1.0, tk.END+"-1c")
        textoNombre.delete(1.0, tk.END+"-1c")
        vidas = 3
        B = int(((dimen-1)/10))+1
        #print(B)
        Portaaviones = Portaav * B
        Submarino = Subma * B
        Destructores = Destruc * B
        Buques = Buq * B
        # print("Portaaviones: ", Portaaviones)
        # print("Submarinos : ", Submarino)
        # print("Destructores: ", Destructores)
        # print("Buques : " , Buques)
        TotalBarcos = Portaaviones + Submarino + Destructores + Buques
        otroB = TotalBarcos
        nuevocontador = otroB
        nuevocontador2 = otroB
        totalmonedas = monedasusuario
        pasarmoneda = totalmonedas
        tokensjugador = pasarmoneda
        totalmonedas2 = 0
        pasarmoneda2 = totalmonedas2
        tokensjugador2 = pasarmoneda2
        MessageBox.showinfo("Exito", "Tablero creado con exito")
        creartableros()
        pruebanueva()
    if dimen>20:
        FILAS = dimen
        COLUMNAS = dimen
        ventanaObtenerDimension.withdraw() 
        textoDimension.delete(1.0, tk.END+"-1c")
        textoNombre.delete(1.0, tk.END+"-1c")
        vidas = 3
        B = int(((dimen-1)/10))+1
        #print(B)
        Portaaviones = Portaav * B
        Submarino = Subma * B
        Destructores = Destruc * B
        Buques = Buq * B
        # print("Portaaviones: ", Portaaviones)
        # print("Submarinos : ", Submarino)
        # print("Destructores: ", Destructores)
        # print("Buques : " , Buques)
        TotalBarcos = Portaaviones + Submarino + Destructores + Buques
        otroB = TotalBarcos
        nuevocontador = otroB
        nuevocontador2 = otroB
        totalmonedas = monedasusuario
        pasarmoneda = totalmonedas
        tokensjugador = pasarmoneda
        totalmonedas2 = 0
        pasarmoneda2 = totalmonedas2
        tokensjugador2 = pasarmoneda2
        MessageBox.showinfo("Exito", "Tablero creado con exito")
        creartableros()
        pruebanueva()


def obtener_matriz_inicial():
    matriz = []
    for y in range(FILAS):
        # Agregamos un arreglo a la matriz, que sería una fila básicamente
        matriz.append([])
        for x in range(COLUMNAS):
            # Y luego agregamos una celda a esa fila. Por defecto lleva "Mar"
            matriz[y].append(MAR)
    return matriz

# Indica si una coordenada de la matriz está vacía
def es_mar(x, y, matriz):
    return matriz[y][x] == MAR


def coordenada_en_rango(x, y):
    return x >= 0 and x <= COLUMNAS-1 and y >= 0 and y <= FILAS-1

def colocar_e_imprimir_barcos(matriz, cantidad_barcos, jugador):
    # Dividimos y redondeamos a entero hacia abajo (ya que no podemos colocar una parte no entera de un barco)
    salidadestructores = int((Destructores)/2)
    salidasubmarinos = int((Submarino)/2)
    salidaportaav = int((Portaaviones)/2)
    destructoresverticales = Destructores - salidadestructores
    submarinosverticales = Submarino - salidasubmarinos
    portaavionesvertical = Portaaviones - salidaportaav
    barcos_una_celda = Buques
    barcos_dos_celdas_verticales = destructoresverticales
    barcos_dos_celdas_horizontales = salidadestructores
    barcos_tres_celdas_verticales = submarinosverticales
    barcos_tres_celdas_horizontales = salidasubmarinos
    barcos_cuatro_celdas_horizontiles = portaavionesvertical
    barcos_cuatro_celdas_verticales = salidaportaav

    if jugador == JUGADOR_1:
        print("")
    else:
        print("")
    # Primero colocamos los de cuatro celdas para que se acomoden bien
    if barcos_cuatro_celdas_verticales == 0 :
        matriz = colocar_barcos_de_cuatro_celdas_horizontal(
            barcos_cuatro_celdas_horizontiles, PORTAAVIONES, matriz)
        #matriz = colocar_barcos_de_cuatro_celdas_vertical(
        #    barcos_cuatro_celdas_verticales, PORTAAVIONES_VERTICAL, matriz)
        matriz = colocar_barcos_de_tres_celdas_horizontal(
            barcos_tres_celdas_horizontales, SUBMARINO, matriz)
        matriz = colocar_barcos_de_tres_celdas_vertical(
            barcos_tres_celdas_verticales, SUBMARINO_VERTICAL, matriz)
        matriz = colocar_barcos_de_dos_celdas_horizontal(
            barcos_dos_celdas_horizontales, DESTRUCTOR, matriz)
        matriz = colocar_barcos_de_dos_celdas_vertical(
            barcos_dos_celdas_verticales, DESTRUCTOR_VERTICAL, matriz)
        matriz = colocar_barcos_de_una_celda(barcos_una_celda, BUQUE, matriz)
    else:
        matriz = colocar_barcos_de_cuatro_celdas_horizontal(
            barcos_cuatro_celdas_horizontiles, PORTAAVIONES, matriz)
        matriz = colocar_barcos_de_cuatro_celdas_vertical(
            barcos_cuatro_celdas_verticales, PORTAAVIONES_VERTICAL, matriz)
        matriz = colocar_barcos_de_tres_celdas_horizontal(
            barcos_tres_celdas_horizontales, SUBMARINO, matriz)
        matriz = colocar_barcos_de_tres_celdas_vertical(
            barcos_tres_celdas_verticales, SUBMARINO_VERTICAL, matriz)
        matriz = colocar_barcos_de_dos_celdas_horizontal(
            barcos_dos_celdas_horizontales, DESTRUCTOR, matriz)
        matriz = colocar_barcos_de_dos_celdas_vertical(
            barcos_dos_celdas_verticales, DESTRUCTOR_VERTICAL, matriz)
        matriz = colocar_barcos_de_una_celda(barcos_una_celda, BUQUE, matriz)
    return matriz

def obtener_x_aleatoria():
    return random.randint(0, COLUMNAS-1)


def obtener_y_aleatoria():
    return random.randint(0, FILAS-1)


def colocar_barcos_de_una_celda(cantidad, tipo_barco, matriz):
    barcos_colocados = 0
    while True:
        x = obtener_x_aleatoria()
        y = obtener_y_aleatoria()
        if es_mar(x, y, matriz):
            matriz[y][x] = tipo_barco
            barcos_colocados += 1
        if barcos_colocados >= cantidad:
            break
    return matriz


def colocar_barcos_de_dos_celdas_horizontal(cantidad, tipo_barco, matriz):
    barcos_colocados = 0
    while True:
        x = obtener_x_aleatoria()
        y = obtener_y_aleatoria()
        x2 = x+1
        if coordenada_en_rango(x, y) and coordenada_en_rango(x2, y) and es_mar(x, y, matriz) and es_mar(x2, y, matriz):
            matriz[y][x] = tipo_barco
            matriz[y][x2] = tipo_barco
            barcos_colocados += 1
        if barcos_colocados >= cantidad:
            break
    return matriz


def colocar_barcos_de_dos_celdas_vertical(cantidad, tipo_barco, matriz):
    barcos_colocados = 0
    while True:
        x = obtener_x_aleatoria()
        y = obtener_y_aleatoria()
        y2 = y+1
        if coordenada_en_rango(x, y) and coordenada_en_rango(x, y2) and es_mar(x, y, matriz) and es_mar(x, y2, matriz):
            matriz[y][x] = tipo_barco
            matriz[y2][x] = tipo_barco
            barcos_colocados += 1
        if barcos_colocados >= cantidad:
            break
    return matriz

def colocar_barcos_de_tres_celdas_horizontal(cantidad, tipo_barco, matriz):
    barcos_colocados = 0
    while True:
        x = obtener_x_aleatoria()
        y = obtener_y_aleatoria()
        x2 = x+1
        x3 = x+2
        if coordenada_en_rango(x, y) and coordenada_en_rango(x2, y) and coordenada_en_rango(x3, y) and es_mar(x, y, matriz) and es_mar(x2, y, matriz) and es_mar(x3, y, matriz):
            matriz[y][x] = tipo_barco
            matriz[y][x2] = tipo_barco
            matriz[y][x3] = tipo_barco
            barcos_colocados += 1
        if barcos_colocados >= cantidad:
            break
    return matriz

def colocar_barcos_de_tres_celdas_vertical(cantidad, tipo_barco, matriz):
    barcos_colocados = 0
    while True:
        x = obtener_x_aleatoria()
        y = obtener_y_aleatoria()
        y2 = y+1
        y3 = y+2
        if coordenada_en_rango(x, y) and coordenada_en_rango(x, y2) and coordenada_en_rango(x, y3) and es_mar(x, y, matriz) and es_mar(x, y2, matriz) and es_mar(x, y3, matriz):
            matriz[y][x] = tipo_barco
            matriz[y2][x] = tipo_barco
            matriz[y3][x] = tipo_barco
            barcos_colocados += 1
        if barcos_colocados >= cantidad:
            break
    return matriz

def colocar_barcos_de_cuatro_celdas_horizontal(cantidad, tipo_barco, matriz):
    barcos_colocados = 0
    while True:
        x = obtener_x_aleatoria()
        y = obtener_y_aleatoria()
        x2 = x+1
        x3 = x+2
        x4 = x+3
        if coordenada_en_rango(x, y) and coordenada_en_rango(x2, y) and coordenada_en_rango(x3, y) and coordenada_en_rango(x4, y) and es_mar(x, y, matriz) and es_mar(x2, y, matriz) and es_mar(x3, y, matriz) and es_mar(x4, y, matriz):
            matriz[y][x] = tipo_barco
            matriz[y][x2] = tipo_barco
            matriz[y][x3] = tipo_barco
            matriz[y][x4] = tipo_barco
            barcos_colocados += 1
        if barcos_colocados >= cantidad:
            break
    return matriz

def colocar_barcos_de_cuatro_celdas_vertical(cantidad, tipo_barco, matriz):
    barcos_colocados = 0
    while True:
        x = obtener_x_aleatoria()
        y = obtener_y_aleatoria()
        y2 = y+1
        y3 = y+2
        y4 = y+3
        if coordenada_en_rango(x, y) and coordenada_en_rango(x, y2) and coordenada_en_rango(x, y3) and coordenada_en_rango(x, y4) and es_mar(x, y, matriz) and es_mar(x, y2, matriz) and es_mar(x, y3, matriz) and es_mar(x, y4, matriz):
            matriz[y][x] = tipo_barco
            matriz[y2][x] = tipo_barco
            matriz[y3][x] = tipo_barco
            matriz[y4][x] = tipo_barco
            barcos_colocados += 1
        if barcos_colocados >= cantidad:
            break
    return matriz

def imprimir_matriz(matriz, deberia_mostrar_barcos, jugador):
    doc = open("Jugador1.txt", "w")
    letra = 1
    for y in range(FILAS):
        for x in range(COLUMNAS):
            celda = matriz[y][x]
            valor_real = celda
            if not deberia_mostrar_barcos and valor_real != MAR and valor_real != DISPARO_FALLADO and valor_real != DISPARO_ACERTADO:
                if valor_real == BUQUE:
                    valor_real = "B"
                elif valor_real == SUBMARINO:
                    valor_real = "S"
                elif valor_real == DESTRUCTOR:
                    valor_real = "D"
                elif valor_real == DESTRUCTOR_VERTICAL:
                    valor_real == "A"
                elif valor_real == SUBMARINO_VERTICAL:
                    valor_real == "C"
                elif valor_real == PORTAAVIONES:
                    valor_real == "P"
                elif valor_real == PORTAAVIONES_VERTICAL:
                    valor_real == "V"
                else:
                    valor_real = "X"
            doc.write(f"{valor_real}")
            
        letra+=1
        doc.write("\n",)
    doc.close()
    with open('Jugador1.txt') as archivo:
        l = 0
        c = 0
        lineas = archivo.readlines()
        for linea in lineas:
            columnas = linea
            l += 1
            for col in columnas:
                if col != '\n':
                    c += 1
                    matrizD.insert(l, c, col)
            c = 0
            matrizD.graficarNeato2('Jugador1')


def imprimir_matriz2(matriz, deberia_mostrar_barcos, jugador):
    doc = open("Jugador2.txt", "w")
    letra = 1
    for y in range(FILAS):
        for x in range(COLUMNAS):
            celda = matriz[y][x]
            valor_real = celda
            if not deberia_mostrar_barcos and valor_real != MAR and valor_real != DISPARO_FALLADO and valor_real != DISPARO_ACERTADO:
                if valor_real == BUQUE:
                    valor_real = "B"
                elif valor_real == SUBMARINO:
                    valor_real = "S"
                elif valor_real == DESTRUCTOR:
                    valor_real = "D"
                elif valor_real == DESTRUCTOR_VERTICAL:
                    valor_real == "A"
                elif valor_real == SUBMARINO_VERTICAL:
                    valor_real == "C"
                elif valor_real == PORTAAVIONES:
                    valor_real == "P"
                elif valor_real == PORTAAVIONES_VERTICAL:
                    valor_real == "V"
                else:
                    valor_real = "X"
            doc.write(f"{valor_real}")
            
        letra+=1
        doc.write("\n",)
    doc.close()
    with open('Jugador2.txt') as archivo1:
        l1 = 0
        c1 = 0
        lineas1 = archivo1.readlines()
        for linea1 in lineas1:
            columnas1 = linea1
            l1 += 1
            for col1 in columnas1:
                if col1 != '\n':
                    c1 += 1
                    matriz2.insert(l1, c1, col1)
            c1 = 0
            matriz2.graficarNeato2('Jugador2')

def solicitando_coordenadas():
    global XDisparo, YDisparo

    y = None
    x = None

    while True:
        try:
            y = ataqueY
            y2 = ataqueY
            if coordenada_en_rango(y-1, 0):
                y = y-1
                YDisparo = y
                
                break
            else:
                print("Fila invalida")
        except:
            print("Ingrese una coordenada valida")
    while True:
        try:
            x = ataqueX
            x2 = ataqueX
            if coordenada_en_rango(x-1,0):
                x = x-1
                XDisparo = x
                break
            else:
                print("Columna invalida")
        except:
            print("Ingrese una coordenada valida")
    ListaAdy.conexion(XDisparo, YDisparo)
    disparar()

def solicitando_coordenadas2():
    global XDisparo2, YDisparo2

    y = None
    x = None

    while True:
        try:
            y = ataqueY2
            if coordenada_en_rango(y-1, 0):
                y = y-1
                YDisparo2 = y
                break
            else:
                print("Fila invalida")
        except:
            print("Ingrese una coordenada valida")
    while True:
        try:
            x = ataqueX2
            if coordenada_en_rango(x-1,0):
                x = x-1
                XDisparo2 = x
                break
            else:
                print("Columna invalida")
        except:
            print("Ingrese una coordenada valida")
    disparar2()

def abrirventana():
    global ventanaNueva, lbltokens
    lblbarcoos = nuevocontador
    lbltokens = tokensjugador
    ventanaNueva = Toplevel()
    ventanaNueva.title("Tablero Jugador 1")
    ventanaNueva.resizable(0,0)
    ancho_ventanaN = 1100
    alto_ventanaN = 800
    x_ventanaN = ventanaNueva.winfo_screenwidth() // 2 - ancho_ventanaN // 2
    y_ventanaN = ventanaNueva.winfo_screenheight() // 2 - alto_ventanaN // 2
    posicionN = str(ancho_ventanaN) + "x" + str(alto_ventanaN) + "+" + str(x_ventanaN) + "+" + str(y_ventanaN)
    ventanaNueva.geometry(posicionN)
    image = Image.open("Salida/matriz_Jugador1.png")
    resize_image = image.resize((700, 700))
    img = ImageTk.PhotoImage(resize_image)
    labelPhotoN = Label(ventanaNueva, image=img)
    labelPhotoN.image = img
    labelPhotoN.place(x=250,y=30)
    #labelPhotoN.pack()
    labelusuarioactual = Label (ventanaNueva, text ="Turno de : " + JUGADOR_1, font=("Verdana",16), background="#044D9A", fg="white")
    labelusuarioactual.place(x=550, y=0)
    labelAtacando = Label (ventanaNueva, text ="Atacando a : " + JUGADOR_2, font=("Verdana",16), background="#044D9A", fg="white")
    labelAtacando.place(x=20, y=100)
    labelPuntos = Label (ventanaNueva, text ="Tokens: " + str(lbltokens), font=("Verdana",16), background="#044D9A", fg="white")
    labelPuntos.place(x=20, y=130)
    labelBarcos = Label (ventanaNueva, text ="Barcos Restantes: " + str(lblbarcoos), font=("Verdana",16), background="#044D9A", fg="white")
    labelBarcos.place(x=20, y=160)
    labelBuques = Label (ventanaNueva, text ="Buques: " + str(Buques), font=("Verdana",16), background="#044D9A", fg="white")
    labelBuques.place(x=20, y=190)
    labelDestructor = Label (ventanaNueva, text ="Destructores: " + str(Destructores), font=("Verdana",16), background="#044D9A", fg="white")
    labelDestructor.place(x=20, y=220)
    labelSubmarinos = Label (ventanaNueva, text ="Submarinos: " + str(Submarino), font=("Verdana",16), background="#044D9A", fg="white")
    labelSubmarinos.place(x=20, y=250)
    labelPortaa = Label (ventanaNueva, text ="Portaaviones: " + str(Portaaviones), font=("Verdana",16), background="#044D9A", fg="white")
    labelPortaa.place(x=20, y=280)
    labelPoosX = Label (ventanaNueva, text ="Pos X", font=("Verdana",16), background="#044D9A", fg="white")
    labelPoosX.place(x=1000, y=90)
    labelPoosY = Label (ventanaNueva, text ="Pos Y", font=("Verdana",16), background="#044D9A", fg="white")
    labelPoosY.place(x=1000, y=200)
    textoPoosX = Text(ventanaNueva, height=2, width=8, fg="white", font=("Consolas", 12)) 
    textoPoosX.place(x=1000, y=140)
    textoPoosY = Text(ventanaNueva, height=2, width=8, fg="white", font=("Consolas", 12)) 
    textoPoosY.place(x=1000, y=240)
    btnAbandonar = Button(ventanaNueva, height=2, width=8, text="Abandonar",command=lambda:[abandonarpartida()] , background="#B03314", font=("Verdana",10), fg="black")
    btnAbandonar.place(x=20, y=320)
    btnAtaque = Button(ventanaNueva, height=2, width=8, text="Atacar",command=lambda:[sacarcoordenadas(textoPoosX.get(1.0, tk.END+"-1c"),textoPoosY.get(1.0, tk.END+"-1c")), ventanaNueva.destroy(), pruebanueva1()] , background="#B03314", font=("Verdana",10), fg="black")
    btnAtaque.place(x=990, y=320)

def abrirventana2():
    global ventanaNueva2
    lblbarcoos2 = nuevocontador2
    lbltokens2 = tokensjugador2
    ventanaNueva2 = Toplevel()
    ventanaNueva2.title("Tablero Jugador 2")
    ventanaNueva2.resizable(0,0)
    ancho_ventanaN = 1100
    alto_ventanaN = 800
    x_ventanaN = ventanaNueva2.winfo_screenwidth() // 2 - ancho_ventanaN // 2
    y_ventanaN = ventanaNueva2.winfo_screenheight() // 2 - alto_ventanaN // 2
    posicionN = str(ancho_ventanaN) + "x" + str(alto_ventanaN) + "+" + str(x_ventanaN) + "+" + str(y_ventanaN)
    ventanaNueva2.geometry(posicionN)
    image = Image.open("Salida/matriz_Jugador2.png")
    resize_image = image.resize((700, 700))
    img = ImageTk.PhotoImage(resize_image)
    labelPhotoN = Label(ventanaNueva2, image=img)
    labelPhotoN.image = img
    labelPhotoN.place(x=250,y=30)
    #labelPhotoN.pack()
    labelusuarioactual = Label (ventanaNueva2, text ="Turno del jugador : " + JUGADOR_2, font=("Verdana",16), background="#044D9A", fg="white")
    labelusuarioactual.place(x=550, y=0)
    labelAtacando = Label (ventanaNueva2, text ="Atacando a: " + JUGADOR_1, font=("Verdana",16), background="#044D9A", fg="white")
    labelAtacando.place(x=20, y=90)
    labelPuntos = Label (ventanaNueva2, text ="Tokens: " + str(lbltokens2), font=("Verdana",16), background="#044D9A", fg="white")
    labelPuntos.place(x=20, y=120)
    labelBarcos = Label (ventanaNueva2, text ="Barcos Restantes: " + str(lblbarcoos2), font=("Verdana",16), background="#044D9A", fg="white")
    labelBarcos.place(x=20, y=150)
    labelBuques = Label (ventanaNueva2, text ="Buques: " + str(Buques), font=("Verdana",16), background="#044D9A", fg="white")
    labelBuques.place(x=20, y=190)
    labelDestructor = Label (ventanaNueva2, text ="Destructores: " + str(Destructores), font=("Verdana",16), background="#044D9A", fg="white")
    labelDestructor.place(x=20, y=220)
    labelSubmarinos = Label (ventanaNueva2, text ="Submarinos: " + str(Submarino), font=("Verdana",16), background="#044D9A", fg="white")
    labelSubmarinos.place(x=20, y=250)
    labelPortaa = Label (ventanaNueva2, text ="Portaaviones: " + str(Portaaviones), font=("Verdana",16), background="#044D9A", fg="white")
    labelPortaa.place(x=20, y=280)
    labelPoosX = Label (ventanaNueva2, text ="Pos X", font=("Verdana",16), background="#044D9A", fg="white")
    labelPoosX.place(x=1000, y=90)
    labelPoosY = Label (ventanaNueva2, text ="Pos Y", font=("Verdana",16), background="#044D9A", fg="white")
    labelPoosY.place(x=1000, y=200)
    textoPoosX = Text(ventanaNueva2, height=2, width=8, fg="white", font=("Consolas", 12)) 
    textoPoosX.place(x=1000, y=140)
    textoPoosY = Text(ventanaNueva2, height=2, width=8, fg="white", font=("Consolas", 12)) 
    textoPoosY.place(x=1000, y=240)
    btnAtaque = Button(ventanaNueva2, height=2, width=8, text="Atacar",command=lambda:[sacarcoordenadas2(textoPoosX.get(1.0, tk.END+"-1c"),textoPoosY.get(1.0, tk.END+"-1c")), ventanaNueva2.destroy(), pruebanueva()] , background="#B03314", font=("Verdana",10), fg="black")
    btnAtaque.place(x=1000, y=320)


def sacarcoordenadas(nuevoX, nuevoY):
    global ataqueX, ataqueY
    ataqueX = int(nuevoX)
    ataqueY = int(nuevoY)
    solicitando_coordenadas()

def sacarcoordenadas2(nuevoX, nuevoY):
    global ataqueX2, ataqueY2
    ataqueX2 = int(nuevoX)
    ataqueY2 = int(nuevoY)
    solicitando_coordenadas2()
    

def disparar() -> bool:
    global nuevocontador, tokensjugador, barcosdestruidos, tokensganados, disparosfalladosj1
    disparosfalladosj1 = 0
    barcosdestruidos = 0
    tokensganados = 0
    x = int(YDisparo)
    y = int(XDisparo)
    matriz = MatrizActual
    if es_mar(x, y, matriz):
        matriz[y][x] = DISPARO_FALLADO
        #print("Fallado")
        MessageBox.showinfo("Fallo", "Disparo fallado")
        disparosfalladosj1 += 1
        imprimir_matriz(MatrizActual, False,
                    oponente_de_jugador(turno_actual1))
        return False
    # Si ya había disparado antes, se le cuenta como falla igualmente
    elif matriz[y][x] == DISPARO_FALLADO or matriz[y][x] == DISPARO_ACERTADO:
        #print("De nuevo")
        #MessageBox.showinfo("Fallo", "El disparo ya ha sido fallado")
        disparosfalladosj1 += 1
        imprimir_matriz(MatrizActual, False,
                    oponente_de_jugador(turno_actual1))
        return False
    else:
        matriz[y][x] = DISPARO_ACERTADO
        MessageBox.showinfo("Exito", "El disparo ha impactado en un barco")
        nuevocontador -= 1
        tokensjugador += 20
        barcosdestruidos += 1
        tokensganados += 20
        #print("Acertado")
        imprimir_matriz(MatrizActual, False,
                    oponente_de_jugador(turno_actual1))
        return True

def disparar2() -> bool:
    global nuevocontador2, tokensjugador2, barcosdestruidos2, tokensganados2, disparosfalladosj2
    disparosfalladosj2 = 0
    barcosdestruidos2 = 0
    tokensganados2 = 0
    x = int(YDisparo2)
    y = int(XDisparo2)
    matriz = MatrizActual2
    if es_mar(x, y, matriz):
        matriz[y][x] = DISPARO_FALLADO
        #print("Fallado")
        MessageBox.showinfo("Fallo", "Disparo fallado")
        disparosfalladosj2 += 1
        imprimir_matriz2(MatrizActual2, False,
                    oponente_de_jugador(turno_actual1))
        
        return False
    elif matriz[y][x] == DISPARO_FALLADO or matriz[y][x] == DISPARO_ACERTADO:
        disparosfalladosj2 += 1
        imprimir_matriz2(MatrizActual2, False,
                    oponente_de_jugador(turno_actual1))
        return False
    else:
        matriz[y][x] = DISPARO_ACERTADO
        MessageBox.showinfo("Exito", "El disparo ha impactado en un barco")
        nuevocontador2 -= 1
        tokensjugador2 += 20
        barcosdestruidos2 += 1
        tokensganados2 += 20
        imprimir_matriz2(MatrizActual2, False,
                    oponente_de_jugador(turno_actual1))
        return True

def oponente_de_jugador(jugador):
    if jugador == JUGADOR_1:
        return JUGADOR_2
    else:
        return JUGADOR_1

def creartableros():
    global matriz_j1, matriz_j2
    cantidad_barcos = TotalBarcos
    matriz_j1, matriz_j2 = obtener_matriz_inicial(), obtener_matriz_inicial()
    matriz_j1 = colocar_e_imprimir_barcos(
        matriz_j1, cantidad_barcos, JUGADOR_1)
    matriz_j2 = colocar_e_imprimir_barcos(
        matriz_j2, cantidad_barcos, JUGADOR_2)


def pruebanueva():
    global MatrizActual, turno_actual1, jugadorganador1, tokensganador1, barcosganador1, falladosj1
    DERROTADO = FALSE
    turno_actual1 = JUGADOR_1
    while DERROTADO == False:
        if turno_actual1:
            matriz_oponente = matriz_j1
            imprimir_matriz(matriz_oponente, False,
                        oponente_de_jugador(turno_actual1))
            MatrizActual = matriz_oponente
            abrirventana()
            if nuevocontador == 0 :
                jugadorganador1 = turno_actual1
                tokensganador1 =  tokensganados
                barcosganador1 = barcosdestruidos
                falladosj1 = disparosfalladosj1
                MessageBox.showinfo("Exito", "El jugador " + jugadorganador1 +  " ha ganado")
                agregarpuntos()
                resultadojugador1()
                tablerofinal1()
                ventanaNueva.destroy()
                mostrarjugador1()
                break
            DERROTADO = TRUE


def tablerofinal1():
    with open('Jugador1.txt') as archivo:
        l = 0
        c = 0
        lineas = archivo.readlines()
        for linea in lineas:
            columnas = linea
            l += 1
            for col in columnas:
                if col != '\n':
                    c += 1
                    matrizFinal1.insert(l, c, col)
            c = 0
            matrizFinal1.graficarNeato2('TableroFinal1')

def tablerofinal2():
    with open('Jugador2.txt') as archivo:
        l = 0
        c = 0
        lineas = archivo.readlines()
        for linea in lineas:
            columnas = linea
            l += 1
            for col in columnas:
                if col != '\n':
                    c += 1
                    matrizFinal1.insert(l, c, col)
            c = 0
            matrizFinal1.graficarNeato2('TableroFinal2')

def resultadojugador1():
    ListaAdy.GraficoLista()
    ListaAdy.GrafoLista()

def resultadojugador2():
    pass


def pruebanueva1():
    global  MatrizActual2, jugadorganador2, tokensganador2, barcosganador2, falladosj2
    #ventanaNueva.destroy()
    DERROTADO = FALSE
    turno_actual2 = JUGADOR_2
    while DERROTADO == False:
        #print("Turno de: ", turno_actual2)
        if turno_actual2:
            #print("jugador dos")
            matriz_oponente = matriz_j2
            imprimir_matriz2(matriz_oponente, False,
                        oponente_de_jugador(turno_actual2))
            MatrizActual2 = matriz_oponente
            abrirventana2()
            if nuevocontador2 == 0 :
                jugadorganador2 = turno_actual2
                tokensganador2 =  tokensganados2
                barcosganador2 = barcosdestruidos2
                falladosj2 = disparosfalladosj2
                MessageBox.showinfo("Exito", "El jugador " + jugadorganador2 +  " ha ganado")
                resultadojugador1()
                tablerofinal1()
                ventanaNueva2.destroy()
                mostrarjugador1()
                #resultadojugador2()
                break
            DERROTADO = TRUE

def abandonarpartida():
    global quitartokens, finaltokens
    quitartokens = 0
    mes = MessageBox.askquestion('Abandonar', '¿Esta seguro de abandonar esta partida? Perderá 20 tokens')
    if mes == 'yes':
        quitartokens -= 20
        finaltokens = lbltokens + quitartokens
        quitarpuntos()
        MessageBox.showinfo('Cerrando', 'Ha terminado la partida')
        ventanaNueva.destroy()
        ventanaUser.deiconify()
    else:
        MessageBox.showinfo('Regresar', 'Regresando al juego')

def mostrarjugador1():
    ventanaGanador = Toplevel()
    ventanaGanador.title("Jugador Logeado")
    ventanaGanador.resizable(0,0)
    ancho_ventanaGanador = 400
    alto_ventanaGanador = 400
    x_ventanaGanador = ventanaGanador.winfo_screenwidth() // 2 - ancho_ventanaGanador // 2
    y_ventanaGanador = ventanaGanador.winfo_screenheight() // 2 - alto_ventanaGanador // 2
    posicionNombre = str(ancho_ventanaGanador) + "x" + str(alto_ventanaGanador) + "+" + str(x_ventanaGanador) + "+" + str(y_ventanaGanador)
    ventanaGanador.geometry(posicionNombre)
    labelNombreGanador= Label (ventanaGanador, text ="Resultados del usuario : " + usuariobusqueda, font=("Verdana",16), background="#044D9A", fg="white")
    labelNombreGanador.place(x=75, y=30)
    labelDestruidos = Label (ventanaGanador, text ="Barcos Destruidos : " + str(barcosdestruidos), font=("Verdana",16), background="#044D9A", fg="white")
    labelDestruidos.place(x=50, y=90)
    labeLTokensG = Label (ventanaGanador, text ="Tokens Ganados : " + str(tokensganados), font=("Verdana",16), background="#044D9A", fg="white")
    labeLTokensG.place(x=50, y=120)
    btnDisparos = Button(ventanaGanador, height=2, width=12, text="Ver tablero", command = lambda:[abrirtablerofinal1()], background="#368807", font=("Verdana",10), fg="black")
    btnDisparos.place(x=50, y=200)
    btnListaA = Button(ventanaGanador, height=2, width=12, text="Lista de Jugadas", command = lambda:[abrirlistaadyacencia1()], background="#368807", font=("Verdana",10), fg="black")
    btnListaA.place(x=200, y=200)
    btnGrafo = Button(ventanaGanador, height=2, width=12, text="Grafo de Jugadas", command = lambda:[abrirgrafoLista()], background="#368807", font=("Verdana",10), fg="black")
    btnGrafo.place(x=50, y=250)
    btnVolverJuego = Button(ventanaGanador, height=2, width=12, text="Volver a jugar", command = lambda:[Partida()], background="#368807", font=("Verdana",10), fg="black")
    btnVolverJuego.place(x=50, y=300)
    btnEstadisticas = Button(ventanaGanador, height=2, width=16, text="Estadisiticas del Ganador", command = lambda:[estadisticasganador()], background="#368807", font=("Verdana",10), fg="black")
    btnEstadisticas.place(x=200, y=250)
    btnRegresarM = Button(ventanaGanador, height=2, width=12, text="Regresar al menu", command = lambda:[ventanaGanador.withdraw(), ventanaUser.deiconify()], background="#368807", font=("Verdana",10), fg="black")
    btnRegresarM.place(x=200, y=300)


def estadisticasganador():
    if nuevocontador == 9 :
        #definir figura y ejes
        fig, ax = plt.subplots()
        
        table_data = [ ["Puntos Ganados", "Barcos destruidos"],
            [tokensganador1, barcosganador1]
        ]

        #create table
        table = ax.table(cellText = table_data, loc = 'center')

        #modificar tabla de
        table.set_fontsize (14)
        table.scale(1,4)
        ax.axis('off')

        #display table
        plt.title("Jugador Ganador : " + jugadorganador1)
        plt.show()
    else:
        #definir figura y ejes
        fig, ax = plt.subplots()
        
        table_data = [ ["Puntos Ganados", "Barcos destruidos"],
            [tokensganador2, barcosganador2]
        ]
        #create table
        table = ax.table(cellText = table_data, loc = 'center')

        #modificar tabla de
        table.set_fontsize (14)
        table.scale(1,4)
        ax.axis('off')

        #display table
        plt.title("Jugador Ganador : " + jugadorganador2)
        plt.show()


def abrirtablerofinal1():
    im = Image.open('Salida/matriz_TableroFinal1.png')
    im.show()

def abrirlistaadyacencia1():
    im = Image.open('Salida/ListaAdy1.png')
    im.show()

def abrirgrafoLista():
    im = Image.open('Salida/GrafoLista.png')
    im.show()

def agregarpuntos():
    for uss in ListaUsuarios:
        if usuariobusqueda == uss.nick:
            uss.monedas = lbltokens

def quitarpuntos():
    for uss in ListaUsuarios:
        if usuariobusqueda == uss.nick:
            uss.monedas = finaltokens

#---------------------------------CERRANDO ------------------------------

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
#btnRegistrar = Button(ventana, height=2, width=15, text="Registrar Usuario", command=lambda:[verusuarios()], background="#10139E", font=("Verdana",10), fg="black")
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
btnVerTienda = Button(ventanaUser, height=2, width=15, text="Tienda", command = lambda: [GraficoTiendaaa()], background="#368807", font=("Verdana",10), fg="black")
#btnVerTienda = Button(ventanaUser, height=2, width=15, text="Tienda", command = lambda: [MostrarTienda()], background="#368807", font=("Verdana",10), fg="black")
btnVerTienda.place(x=180, y=350)
btnPartida = Button(ventanaUser, height=2, width=15, text="Iniciar Partida", command = lambda: [ventanaNombre.deiconify()], background="#368807", font=("Verdana",10), fg="black")
btnPartida.place(x=180, y=400)
btncerrarSesionUser = Button(ventanaUser, height=2, width=15, text="Cerrar Sesion", command = lambda: [ventanaUser.withdraw(),textoUsuarioC.delete(1.0, tk.END+"-1c"),textoPassC.delete(1.0, tk.END+"-1c"),textoEdadC.delete(1.0, tk.END+"-1c"),MessageBox.showinfo("Exito", "Sesion cerrada"), ventanaLog.deiconify()], background="#368807", font=("Verdana",10), fg="black")
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


#--------------------------------- CREANDO TABLERO DE JUEGO ------------------------------
ventanaObtenerDimension = Toplevel()
ventanaObtenerDimension.title("Dimensiones del Tablero")
ventanaObtenerDimension.resizable(0,0)
ancho_ventana2 = 300
alto_ventana2 = 250
x_ventana2 = ventanaObtenerDimension.winfo_screenwidth() // 2 - ancho_ventana2 // 2
y_ventana2 = ventanaObtenerDimension.winfo_screenheight() // 2 - alto_ventana2 // 2
posicion2 = str(ancho_ventana2) + "x" + str(alto_ventana2) + "+" + str(x_ventana2) + "+" + str(y_ventana2)
ventanaObtenerDimension.geometry(posicion2)
labelDimension = Label (ventanaObtenerDimension, text ="Dimensiones del Tablero", font=("Verdana",16), background="#044D9A", fg="white")
labelDimension.place(x=50, y=45)
labelNum = Label (ventanaObtenerDimension, text ="Numero", font=("Verdana",16), background="#044D9A", fg="white")
labelNum.place(x=50, y=115)
textoDimension = Text(ventanaObtenerDimension, height=2, width=12 ,fg="white", font=("Consolas", 12)) 
textoDimension.place(x=150, y=110)
btnCrearT = Button(ventanaObtenerDimension, height=2, width=15, text="Crear", command = lambda:[GuardarConfiguracion(),Partida()], background="#368807", font=("Verdana",10), fg="black")
btnCrearT.place(x=80, y=190)
ventanaObtenerDimension.withdraw()

#---------------------------------- NOMBRE JUGADOR 2 -----------------------------------
ventanaNombre = Toplevel()
ventanaNombre.title("Jugador Invitado")
ventanaNombre.resizable(0,0)
ancho_ventanaNombre = 250
alto_ventanaNombre = 250
x_ventanaNombre = ventanaNombre.winfo_screenwidth() // 2 - ancho_ventanaNombre // 2
y_ventanaNombre = ventanaNombre.winfo_screenheight() // 2 - alto_ventanaNombre // 2
posicionNombre = str(ancho_ventanaNombre) + "x" + str(alto_ventanaNombre) + "+" + str(x_ventanaNombre) + "+" + str(y_ventanaNombre)
ventanaNombre.geometry(posicionNombre)
labelNombre = Label (ventanaNombre, text ="Jugador 2", font=("Verdana",16), background="#044D9A", fg="white")
labelNombre.place(x=75, y=30)
labelJugador = Label (ventanaNombre, text ="Nombre del jugador", font=("Verdana",16), background="#044D9A", fg="white")
labelJugador.place(x=50, y=90)
textoNombre = Text(ventanaNombre, height=2, width=12, fg="white", font=("Consolas", 12)) 
textoNombre.place(x=80, y=130)
btnAgregar = Button(ventanaNombre, height=2, width=16, text="Agregar", command = lambda:[ventanaObtenerDimension.deiconify(), ventanaNombre.withdraw()], background="#368807", font=("Verdana",10), fg="black")
btnAgregar.place(x=65, y=200)
ventanaNombre.withdraw()

#--------------------------------- INICIANDO INTERFAZ------------------------------
ventana.mainloop()