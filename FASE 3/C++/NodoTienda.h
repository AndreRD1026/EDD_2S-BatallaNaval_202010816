#ifndef NODOTIENDA_H
#define NODOTIENDA_H
#include <stddef.h>
#include <string>

class nodoTienda{
public:
    int id;
    std::string categoria;
    int precio;
    std::string nombre;
    std::string SRC;
	nodoTienda *anteriorArticulo;
	nodoTienda *siguienteArticulo;
    nodoTienda(){
        anteriorArticulo = NULL;
        siguienteArticulo = NULL;
        id = 0;
        categoria = ' ';
        precio = 0;
        nombre = ' ';
        SRC = ' ';
    }
private:
};
#endif