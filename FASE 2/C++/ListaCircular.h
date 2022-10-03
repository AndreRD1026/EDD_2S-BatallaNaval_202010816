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
    void registro_usuario(int id,string nombreuser, string contracifrada, int monedas ,int edad, string contra);
    void registro_usuarioJ(int id,string nombreuser, string contracifrada, int monedas ,int edad, string contra);
    void lista_usuarios();
    //void GraficoListaCDobleEnlace();
    void ordenarUsuarioASC();
    void ordenarUsuarioDESC();
    void ListaUsuarioASC(nodoUsuarios *cabeza);
    void ListaUsuarioDESC(nodoUsuarios *cabeza);
    void intercambioASC(nodoUsuarios *lado_izq, nodoUsuarios *lado_der);
    void intercambioDESC(nodoUsuarios *lado_izq, nodoUsuarios *lado_der);
    void HtmlASC(nodoUsuarios *cabeza);
    void HtmlDESC(nodoUsuarios *cabeza);
    void eliminarCuenta(string userbuscado);
    void modificarUsuario(string userb, string nuevouser, string contra, int edad, string cifrada);
    string BuscarUser(string nombreuser);
    string getUsers();
    string Comprobar(string nombreuser);
    string Comprobar1(string nombreuser);
    string verificarLog(string usuariob, string cifrada);
    string Buscar1(string username);
private:
};
#endif