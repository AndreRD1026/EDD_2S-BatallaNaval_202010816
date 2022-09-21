#ifndef LISTATUTORIAL_H
#define LISTATUTORIAL_H

#include "NodoTutorial.h"
#include <iostream>
using namespace std;

class ListaTutorial{
public:
    nodoCola*primeroCola;
    nodoCola*ultimoCola;

    ListaTutorial(){
        primeroCola = NULL;
        ultimoCola = NULL;
    }
    void registroTutorial(int x, int y);
    void verTutorial();
    void GraficoTutorial();
private:
};
#endif
