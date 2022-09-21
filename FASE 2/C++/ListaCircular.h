#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H

#include "NodoUsuarios.h"
#include <iostream>
using namespace std;

class ListaCircular{
public:
    nodoUsuarios*primero;
    nodoUsuarios*ultimo;

    ListaCircular(){
        primero = NULL;
        ultimo = NULL;
    }
    void registro_usuario(string nombreuser, string contra, int monedas ,int edad, string contracifrada);
    void registro_usuarioJ(string nombreuser, string contra, int monedas ,int edad, string contracifrada);
    void lista_usuarios();
    void login();
    void sub_login(string nombreuser, string contra,int edad, int monedas);
    void editar_info(string nombreuser, int edad, string contra);
    void modificarNick(string userb);
    void modificarEdad(int edad);
    void modificarContra(string contra);
    void eliminarCuenta(string userbuscado);
private:
};
#endif