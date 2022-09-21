#include "ListaTutorial.h"
#include <iostream>
using namespace std;

void ListaTutorial:: registroTutorial(int x, int y){
	nodoCola* nuevoCola = new nodoCola();
	nuevoCola->x = x;
	nuevoCola->y = y;
	if(primeroCola==NULL){
		primeroCola = nuevoCola;
		primeroCola->siguienteCola = NULL;
		ultimoCola = primeroCola;
	}else{
		ultimoCola->siguienteCola = nuevoCola;
		nuevoCola->siguienteCola = NULL;
		ultimoCola = nuevoCola;
	}
}

void ListaTutorial:: verTutorial(){
	nodoCola* actualCola = new nodoCola();
	cout<<"   Tablero\n";
	actualCola = primeroCola->siguienteCola;
	if(primeroCola!=NULL){
		cout<<"\tAncho: " << primeroCola->x<<"\n"; 
		cout<<"\tAlto: "<<primeroCola->y<<"\n";
		cout<<"   Movimientos: "<<endl;
		cout<<"\t";
		while(actualCola!=NULL){
			if(actualCola!= ultimoCola){
				cout<< "(" << actualCola->x<<","<<actualCola->y<< ")<-";
			}
			else if(actualCola == ultimoCola){
				cout<< "(" << actualCola->x<<","<<actualCola->y<< ")";
			}			
			
			actualCola = actualCola->siguienteCola;
		}
		cout<<"\n\n";
	}else{
		cout << endl << " La cola se encuentra Vacia " << endl << endl;
	}
}

void ListaTutorial:: GraficoTutorial(){
	nodoCola* actualCola = new nodoCola();
	if(primeroCola==NULL){
		cout<<"No se puede graficar porque no existen datos en la cola"<<endl;
	}else{
	int contador1 = 0;
	actualCola = primeroCola->siguienteCola;
	string nombreNodo1, direccion1;
	string dot = "";
	dot = dot + "digraph G {\n";
	dot = dot + "graph[nodesep=\"0.75\"]\n";
	dot = dot + "labelloc=\"t\"\n";
	dot = dot + "label=\"Cola de Movimientos\" + \"\nDimensiones del Tablero\" + \"\nANCHO: " +to_string(primeroCola->x)+ "\nLARGO: " + to_string(primeroCola->y)+ "\"\n";
	dot = dot + "node[shape=box]" + "\n";
	if (primeroCola!=NULL) {
		do {
			nombreNodo1 = "nodo"+to_string(contador1);
			dot = dot + nombreNodo1 + "[label =\"X: "  + to_string(actualCola->x) + "\nY: " + to_string(actualCola->y) +"\" ""]" + "\n";
			if(actualCola->siguienteCola!=NULL){
					int auxnum1 = contador1 +1;
					direccion1 += nombreNodo1 + "-> nodo" + std::to_string(auxnum1) + "[dir=back];\n";
				}		
			actualCola = actualCola->siguienteCola;
			contador1++;
		} while(actualCola!=NULL);
	}
	dot += nombreNodo1 + "\n";
	dot +="{rank=same;\n" + direccion1 + "\n}";
	dot = dot + "\n}";	

	ofstream file;
    file.open("ColadeMovimientos.dot");
    file << dot;
    file.close();

    system(("dot -Tpng ColadeMovimientos.dot -o  GraficoTutorial.png"));
	cout<<"\nReporte de Tutorial Generado\n"<<endl;
	}
}
