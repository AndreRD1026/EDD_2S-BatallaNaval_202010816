#ifndef NODOB_H
#define NODOB_H

#include <stddef.h>
#include <string>
#include <iostream>

using namespace std;

class NodoB {
public:
    int id;
    std::string nombreuser;
    //Apuntadores dentro de la rama
    NodoB* siguiente;
    NodoB* anterior;

    //apuntadores al inicio de otra rama
    NodoB* derecha;
    NodoB* izquierda;

    NodoB(int valor, string nombreuser1) {
        id = valor;
        nombreuser = nombreuser1;
        siguiente = NULL;
        anterior = NULL;
        derecha = NULL;
        izquierda = NULL;
    }
private:

};

#endif /* NODOB_H */