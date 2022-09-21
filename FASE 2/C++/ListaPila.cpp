#include "ListaPila.h"
#include <iostream>
using namespace std;


void ListaPila:: insertarPila(int x, int y){
	nodoPila* nuevoPila = new nodoPila();
	nuevoPila->x = x;
	nuevoPila->y = y;
		
	nuevoPila->siguientePila = primeroPila;
	primeroPila = nuevoPila;
	
}


void ListaPila:: GraficoMovimientos(string nombreuser,string nombresalida){
	nodoPila* actualPila = new nodoPila();
	actualPila = primeroPila;
	int contador1 = 0;
	string nombreNodo1, direccion1;

	if(actualPila==NULL){
		cout<<"No se puede graficar porque no existen datos en la pila"<<endl;
	}else{
	string dot = "";
	dot = dot + "digraph G {\n";
	dot = dot + "graph[nodesep=\"0.75\"]\n";
	dot = dot + "labelloc=\"t\"\n";
	dot = dot + "label=\"Lista de Pilas\" + \"\nListado de Jugadas\" + \"\nNick: "+ nombreuser + "\nNombre Jugada: " + nombresalida + "\"\n";
	dot = dot + "node[shape=box]" + "\n";
	if (primeroPila!=NULL) {
		do {
			nombreNodo1 = "nodo"+to_string(contador1);
			dot = dot + nombreNodo1 + "[label =\"X: "  + to_string(actualPila->x) + "\nY: " + to_string(actualPila->y) +"\" ""]" + "\n";
			if(actualPila->siguientePila!=NULL){
					int auxnum1 = contador1 +1;
					direccion1 += nombreNodo1 + "-> nodo" + std::to_string(auxnum1) + "[dir=back];\n";
				}		
			actualPila = actualPila->siguientePila;
			contador1++;
		} while(actualPila!=NULL);
	}
	dot += nombreNodo1 + "\n";
	dot +="{rank=same;\n" + direccion1 + "\n}";
	dot = dot + "\n}";	

	ofstream file;
	string nombredot = "ListadePilas_" + nombreuser + ".dot";
    file.open(nombredot);
    file << dot;
    file.close();
	string salida = "dot -Tpng " +nombredot+ " -o  GraficoMovimientos_"+nombreuser + ".png";
	system((salida.c_str()));
	vaciarPila();
	cout<<"\nReporte de Jugadas Generado\n"<<endl;
	}
}


void ListaPila:: vaciarPila(){
	nodoPila* actualPila = new nodoPila();
	actualPila = primeroPila;
	nodoPila* anteriorPila = new nodoPila();
	anteriorPila = NULL;
	bool encontrado = false;
	if(primeroPila!=NULL){
		while(actualPila!=NULL && encontrado != true){				
				if(actualPila == primeroPila){
					primeroPila = primeroPila->siguientePila;
				}else{
					anteriorPila->siguientePila = actualPila->siguientePila;
				}
			anteriorPila = actualPila;
			actualPila = actualPila->siguientePila;
		}
	}else{
		cout<<"\n";
	}	
}