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
    void registro_usuario(int id,string nombreuser, string contracifrada, int monedas ,int edad);
    void registro_usuarioJ(int id,string nombreuser, string contracifrada, int monedas ,int edad);
    void lista_usuarios();
    //void GraficoListaCDobleEnlace();
    void ordenarUsuarioASC();
    void ordenarUsuarioDESC();
    void ListaUsuarioASC(nodoUsuarios *cabeza);
    void ListaUsuarioDESC(nodoUsuarios *cabeza);
    void intercambioASC(nodoUsuarios *lado_izq, nodoUsuarios *lado_der);
    void intercambioDESC(nodoUsuarios *lado_izq, nodoUsuarios *lado_der);
    void registro_usuario1(int id,string nombreuser, string contra, int monedas, int edad);
    string getUsers();
    void Comprobar(string nombreuser);
    string verificarLog(string usuariob, string cifrada);
    //string Buscar(string usuario);
private:
};
#endif