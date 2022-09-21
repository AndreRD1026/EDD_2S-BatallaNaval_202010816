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

private:
};
#endif