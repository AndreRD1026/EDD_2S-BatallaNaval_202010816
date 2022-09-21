#ifndef NODOTUTORIAL_H
#define NODOTUTORIAL_H
#include <stddef.h>
#include <string>

class nodoCola{
public:
	int x;
    int y;
	nodoCola *siguienteCola;
    nodoCola(){
        siguienteCola = NULL;
        x = 0;
        y = 0;
    }
private:
};

#endif