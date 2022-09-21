#ifndef NODOARTICULOS_H
#define NODOARTICULOS_H
#include <stddef.h>
#include <string>

class NodoArticulos{
public:
	int precioArticulo;
    std::string idArticulo;
    std::string nombreArticulo;
    std::string SRCArticulo;
    NodoArticulos* siguienteArtic;
    NodoArticulos(){
        siguienteArtic = NULL;
        precioArticulo = 0;
        idArticulo = ' ';
        nombreArticulo = ' ';
        SRCArticulo = ' ';
    }
private:
};

#endif