#ifndef LISTAPILA_H
#define LISTAPILA_H

#include "NodoMovimientos.h"
#include <iostream>
using namespace std;

class ListaPila{
public:
    nodoPila*primeroPila;

    ListaPila(){
        primeroPila = NULL;
    }
    void insertarPila(int x, int y);
    void  GraficoMovimientos(string nombreuser,string nombresalida);
    void vaciarPila();
private:
};
#endif