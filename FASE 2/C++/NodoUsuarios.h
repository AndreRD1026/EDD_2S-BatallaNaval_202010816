#ifndef NODOUSUARIO_H
#define NODOUSUARIO_H
#include <stddef.h>
#include <string>

class nodoUsuarios{
public:
	std::string nombreuser;
    std::string contra;
    std::string contracifrada;
	int  monedas,edad; 
	nodoUsuarios *anterior;
	nodoUsuarios *siguiente;
    nodoUsuarios(){
        anterior = NULL;
        siguiente = NULL;
        nombreuser = ' ';
        contra = ' ';
        contracifrada = ' ';
        monedas = 0;
        edad = 0;
    }
private:
};

#endif