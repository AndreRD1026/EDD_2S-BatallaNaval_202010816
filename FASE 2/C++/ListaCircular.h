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
    void GraficoListaCDobleEnlace();
    void ordenarUsuarioASC();
    void ordenarUsuarioDESC();
    void ListaUsuarioASC(nodoUsuarios *cabeza);
    void ListaUsuarioDESC(nodoUsuarios *cabeza);
    void intercambioASC(nodoUsuarios *lado_izq, nodoUsuarios *lado_der);
    void intercambioDESC(nodoUsuarios *lado_izq, nodoUsuarios *lado_der);
private:
};
#endif