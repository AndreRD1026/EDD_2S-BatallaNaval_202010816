#include "ListaArticulos.h"
#include <iostream>

using namespace std;

void ListaArticulos:: registro_articulos(string categoria, string nombre, int precio, string id, string srcarticulo){
    NodoCategoria* nodoCategoria = new NodoCategoria();
    nodoCategoria->categoria = categoria;
    NodoCategoria* aux = new NodoCategoria();

    NodoArticulos* nodoArticulos = new NodoArticulos();
    nodoArticulos->nombreArticulo = nombre;
    nodoArticulos->precioArticulo = precio;
    nodoArticulos->idArticulo= id;
	nodoArticulos->SRCArticulo = srcarticulo;

    aux = primeroCategoria;
	bool encontrado = false;

	if(primeroCategoria == NULL){
        nodoCategoria->indice++;
        primeroCategoria = nodoCategoria;
        ultimoCategoria = nodoCategoria;
        
            primeroCategoria->abajo = nodoArticulos;
            primeroArticulos = nodoArticulos;
            ultimoArticulos = nodoArticulos;
    }else{
        if(!CategoriaRepetida(nodoCategoria->categoria)){
        NodoCategoria* temp = new NodoCategoria();
        temp = primeroCategoria;
        int aux = 1;
            while (temp!=NULL)
            {
                aux++;
                temp = temp->siguienteCA;
            }
            nodoCategoria->indice = aux;
            
            ultimoCategoria->siguienteCA = nodoCategoria;
            ultimoCategoria = nodoCategoria;

            ultimoCategoria->abajo = nodoArticulos;
            primeroArticulos = nodoArticulos;
            ultimoArticulos = nodoArticulos;
        }else{
            ultimoArticulos->siguienteArtic = nodoArticulos;
            ultimoArticulos = nodoArticulos;
        }
    }
}

bool ListaArticulos:: CategoriaRepetida(string _categoria){
    NodoCategoria* actualCategoria = new NodoCategoria();
    bool repetido = false;
    actualCategoria = primeroCategoria;
    if(primeroCategoria!=NULL){
        while(actualCategoria!=NULL){
            if(_categoria==actualCategoria->categoria){
                repetido = true;
                break;
            }
            actualCategoria = actualCategoria->siguienteCA;
        }
    }
    return repetido;
}

void ListaArticulos:: Mostrar_Tienda(int monedas){
	NodoCategoria* aux1 = new NodoCategoria();
    aux1 = primeroCategoria;

    NodoArticulos* aux2 = new NodoArticulos();
    cout<<"\t\t\t\tTotal Tokens: "<<monedas<<endl;
	cout<<"Tienda"<<endl;
	cout << "  "<< left << setw( 10 ) << "ID"<< " "<< left << setw( 20 ) << "Nombre"<< "   "<< left << setw( 12 ) << "Categoria"<< " "<< left << setw( 15 ) << "Precio"<< " "<<endl;
    while(aux1!=NULL){		
        aux2 = aux1->abajo;
        while (aux2!=NULL)
        {
			cout << "  "<< left << setw( 10 ) <<aux2->idArticulo<< " "<< left << setw( 20 ) << aux2->nombreArticulo<< "   "<< left << setw( 12 ) << aux1->categoria<< " "<< left << setw( 12 ) <<aux2->precioArticulo<< " "<<endl;
            aux2 = aux2->siguienteArtic;
        }
        aux1 = aux1->siguienteCA;

    }
	cout<<"\n";
}

void ListaArticulos:: GraficoListadeListas(){
		NodoCategoria* actualCategoria = new NodoCategoria();
		NodoArticulos* templist = new NodoArticulos();
		actualCategoria = primeroCategoria;

		if(primeroCategoria==NULL){
			cout<<"No se puede graficar porque no existen datos en la lista"<<endl;
		}else{
		string dot = "";
		dot = dot + "digraph G{\n";
		dot = dot + "graph[nodesep=\"0.75\"]\n";
		dot = dot + "labelloc=\"t\"\n";
		dot = dot + "label=\"Lista de Listas\"\n";
		dot = dot + "node[shape=box];\n";
		dot = dot + "rankdir = \"LR\" ";
		string enlaces = "";
    	string conexionPrimero = "";
    	string nodos = "";
    	int numeronodo = 1;
		while (actualCategoria != NULL) {
			dot = dot +
			"\n    H" 
			+ to_string(actualCategoria->indice) +
			"[label = \"Categoria: " +
			actualCategoria->categoria +
			"\" "+  "  width = 2 , group = 1 ];\n";		
			templist = actualCategoria->abajo;		
			if (templist != NULL) {
				enlaces += "    H" + to_string(actualCategoria->indice) + " -> H" + to_string(actualCategoria->indice) + "C" + to_string(numeronodo);
				nodos += "\n    { rank = same; H" + to_string(actualCategoria->indice) + "; ";
		
				while (templist != NULL) {
					dot = dot +
						"    H" +
						to_string(actualCategoria->indice) +
						"C" +
						to_string(numeronodo) +
						"[label =\" " +
						"Id: " + templist->idArticulo +
						"\nNombre: "+templist->nombreArticulo+
						"\nPrecio: "+to_string(templist->precioArticulo)+
						"\"" +  " width = 2, group = 1 ];\n";
						nodos += "H" + to_string(actualCategoria->indice) + "C" + to_string(numeronodo) + ";";
						
						if (templist->siguienteArtic != NULL) {
							enlaces +=
							"    H" +
									to_string(actualCategoria->indice) +
									"C" +
									to_string(numeronodo) +
									" ->H" +
									to_string(actualCategoria->indice) +
									"C" +
									to_string((numeronodo+1)) +
									"\n";				
							}
							templist = templist->siguienteArtic;
							numeronodo++;
						}			
						nodos += "}";
						dot = dot + enlaces;
						dot = dot + nodos;
						enlaces = "";
						nodos = "";
					}
					if (actualCategoria->siguienteCA !=  NULL) {
						conexionPrimero +=
							"    H" + to_string(actualCategoria->indice) + " -> H" + to_string(actualCategoria->siguienteCA->indice) + "\n";
					}
					actualCategoria = actualCategoria->siguienteCA;
				}
				dot = dot + conexionPrimero;
				dot = dot + "\n}";
	ofstream file;
    file.open("ListadeListas.dot");
    file<<dot;
    file.close();
    system(("dot -Tpng ListadeListas.dot -o  ListadeListas.png"));
	cout<<"Reporte de Articulos Generado"<<endl;
	}

} 

string ListaArticulos :: getArticulos(){
    NodoCategoria* aux1 = new NodoCategoria();
	aux1 = primeroCategoria;
	NodoArticulos* aux2 = new NodoArticulos();
	/*
	NodoCategoria* aux1 = new NodoCategoria();
    aux1 = primeroCategoria;
    NodoArticulos* aux2 = new NodoArticulos();
	*/

	string datos = "";
	datos += "\"articulos\":[";
	while (aux1 != NULL){
		aux2 = aux1->abajo;
		while (aux2!=NULL)
		{
			datos+= "{";
			datos+= "\"id\":\"" + aux2->idArticulo;
			datos+= "\"categoria\":\"" + aux1->categoria;
			datos+= "\"precio\":\"" + to_string(aux2->precioArticulo);
			datos+= "\"nombre\":\"" + aux2->nombreArticulo;
			datos+= "\"src\":\"" + aux2->SRCArticulo;
			datos+= "}";
		}
		aux1 = aux1->siguienteCA;
	}
	datos += "]";
	return datos;
		
}

/* 
while(aux1!=NULL){		
        aux2 = aux1->abajo;
        while (aux2!=NULL)
        {
			cout << "  "<< left << setw( 10 ) <<aux2->idArticulo<< " "<< left << setw( 20 ) << aux2->nombreArticulo<< "   "<< left << setw( 12 ) << aux1->categoria<< " "<< left << setw( 12 ) <<aux2->precioArticulo<< " "<<endl;
            aux2 = aux2->siguienteArtic;
        }
        aux1 = aux1->siguienteCA;

    }

*/

