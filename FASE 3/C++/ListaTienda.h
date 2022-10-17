#ifndef LISTATIENDA_H
#define LISTATIENDA_H

#include "NodoTienda.h"
#include <iostream>
using namespace std;

class ListaTienda{
public:
    nodoTienda*primeroArticulo;
    nodoTienda*ultimoArticulo;
    ListaTienda(){
        primeroArticulo = NULL;
        ultimoArticulo = NULL;
    }
    void registro_articulos(int id,string categoria, string nombre, int precio, string srcarticulo);
    void lista_articulos();
    //void Mostrar_Tienda(int monedas);
    //void GraficoListadeListas();
    //string getArticulos();
    /*
    void registro_usuario(int id,string nombreuser, string contracifrada, int monedas ,int edad, string contra);
    void registro_usuarioJ(int id,string nombreuser, string contracifrada, int monedas ,int edad, string contra);
    void lista_usuarios();
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
    */
    
private:
};
#endif