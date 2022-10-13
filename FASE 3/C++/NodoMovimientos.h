#ifndef NODOMOVIMIENTOS_H
#define NODOMOVIMIENTOS_H
#include <stddef.h>
#include <string>

class nodoPila{
public:
	int x;
    int y;
	nodoPila *siguientePila;
    nodoPila(){
        siguientePila = NULL;
        x = 0;
        y = 0;
    }
private:
};

#endif