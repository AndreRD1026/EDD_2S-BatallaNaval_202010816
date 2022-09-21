#ifndef LISTAARTICULOS_H
#define LISTAARTICULOS_H

#include "NodoArticulos.h"
#include "NodoCategoria.h"
#include <iostream>
using namespace std;

class ListaArticulos{
public:
    NodoArticulos* primeroArticulos;
    NodoArticulos* ultimoArticulos;
    NodoCategoria* primeroCategoria;
    NodoCategoria* ultimoCategoria;

    ListaArticulos(){
        primeroArticulos = NULL;
        ultimoArticulos = NULL;
        primeroCategoria = NULL;
        ultimoCategoria = NULL;
    }
    void registro_articulos(string categoria, string nombre, int precio, string id, string srcarticulo);
    bool CategoriaRepetida(string _categoria);
    void Mostrar_Tienda(int monedas);
    void GraficoListadeListas();
    //void registro_usuario(string nombreuser, string contra, int monedas ,int edad, string contracifrada);
    //void registro_usuarioJ(string nombreuser, string contra, int monedas ,int edad, string contracifrada);

private:
};
#endif

/*

struct NodoCategoria{
    string categoria;
    int indice;
    NodoCategoria* siguienteCA;
    NodoArticulos* abajo;
}*primeroCategoria, *ultimoCategoria;

*/

/* 

struct NodoArticulos{
	int precioArticulo;
    string idArticulo,nombreArticulo,SRCArticulo;    
    NodoArticulos* siguienteArtic;
}*primeroArticulos, *ultimoArticulos;

*/