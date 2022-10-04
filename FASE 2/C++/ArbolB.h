#ifndef ARBOLB_H
#define ARBOLB_H

#include <algorithm>

#include "NodoB.h"

class ArbolB {
public:
    int orden_arbol = 3;
    NodoB* raiz;

    ArbolB() {
        raiz = NULL;
    }
    void insertar(int id, string nombreuser);
    pair<NodoB*, pair<bool, bool>> insertarCrearRama(NodoB* nodo, NodoB* rama);
    NodoB* dividir(NodoB* rama);
    pair<NodoB*, bool>  insertarEnRama(NodoB* primero, NodoB* nuevo);
    bool esHoja(NodoB* primero);
    int contador(NodoB* primero);
    void eliminar(int id);
    void modificar(int id, string nuevouser);
    void Grafo();
    string GrafoArbolAbb(NodoB*rama);
    string GrafoRamas(NodoB*rama);
    string GrafoConexionRamas(NodoB*rama);
    void vaciar();
private:

};

#endif /* ARBOLB_H */