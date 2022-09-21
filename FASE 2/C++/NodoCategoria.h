#ifndef NODOCATEGORIA_H
#define NODOCATEGORIA_H
#include "NodoArticulos.h"
#include <stddef.h>
#include <string>

class NodoCategoria{
public:
    std::string categoria;
    int indice;
    NodoCategoria* siguienteCA;
    NodoArticulos* abajo;
    NodoCategoria(){
        abajo = NULL;
        siguienteCA = NULL;
        categoria = ' ';
        indice = 0;
    }
private:
};

#endif