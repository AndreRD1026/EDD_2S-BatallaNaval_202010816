#include "ListaTienda.h"
#include "SHA256.h"
#include <iostream>

using namespace std;

void ListaTienda::registro_articulos(int id,string categoria, string nombre, int precio , string SRCart){
	nodoTienda *actualArticulo = new nodoTienda();
	actualArticulo = primeroArticulo;
	bool encontrado = false;

	if(primeroArticulo != NULL){
		do{
			if(actualArticulo->id==id){
				cout<<"\n";
				//cout<<"No se puede agregar porque ya existe un ususario con ese Nick"<<endl;
				encontrado = true;				
			}
			actualArticulo = actualArticulo->siguienteArticulo;	
		}while(actualArticulo!=primeroArticulo && encontrado != true);
	}
	if(primeroArticulo!= NULL  && encontrado==false){
			if(actual->id!=id){
				nodoTienda *nuevoArticulo = new nodoTienda();
				nuevoArticulo->id = id;
				nuevoArticulo->categoria = categoria;
				nuevoArticulo->nombre = nombre;
				nuevoArticulo->precio = precio;
				nuevoArticulo->SRC = SRCart;

				if (primeroArticulo==NULL) {
					primeroArticulo=nuevoArticulo;
					ultimoArticulo=nuevoArticulo;
					primeroArticulo -> siguienteArticulo=primeroArticulo;
					primeroArticulo -> anteriorArticulo=ultimoArticulo;
				}else{
					ultimoArticulo-> siguienteArticulo=nuevoArticulo;
					nuevoArticulo-> anteriorArticulo=ultimoArticulo;
					nuevoArticulo-> siguienteArticulo=primeroArticulo;
					ultimoArticulo=nuevoArticulo;
					primeroArticulo-> anteriorArticulo=ultimoArticulo;
				}
				cout<<"\nArticulo registrado"<<endl;
			}
	}
		
	if(primeroArticulo == NULL){
		nodoTienda *nuevoArticulo = new nodoTienda();
        nuevoArticulo->id = id;
        nuevoArticulo->categoria = categoria;
        nuevoArticulo->nombre = nombre;
        nuevoArticulo->precio = precio;
        nuevoArticulo->SRC = SRCart;

		if (primeroArticulo==NULL) {
			primeroArticulo=nuevoArticulo;
			ultimoArticulo=nuevoArticulo;
			primeroArticulo -> siguienteArticulo=primeroArticulo;
			primeroArticulo -> anteriorArticulo=ultimoArticulo;
		}else{
			ultimoArticulo-> siguienteArticulo=nuevoArticulo;
			nuevoArticulo-> anteriorArticulo=ultimoArticulo;
			nuevoArticulo-> siguienteArticulo=primeroArticulo;
			ultimoArticulo=nuevoArticulo;
			primeroArticulo-> anteriorArticulo=ultimoArticulo;
		}
		cout<<"\nArticulo registrado"<<endl;
	}

}


void ListaTienda::lista_articulos() {
    nodoTienda *actualArticulo = new nodoTienda();
    actualArticulo = primeroArticulo;
    if (primeroArticulo!=NULL) {
        cout << "  "<< left << setw( 10 ) << "ID"<< " "<< left << setw( 20 ) << "Nombre"<< "   "<< left << setw( 12 ) << "Categoria"<< " "<< left << setw( 15 ) << "Precio"<< " "<<endl;
        do {
            cout << "  "<< left << setw( 10 ) <<actualArticulo->id<< " "<< left << setw( 20 ) << actualArticulo->categoria<< "   "<< left << setw( 12 ) << actualArticulo->nombre<< " "<< left << setw( 12 ) <<actualArticulo->precio<< " "<<endl;
            actualArticulo = actualArticulo -> siguienteArticulo;
        } while(actualArticulo!=primeroArticulo);
    }else{
        std::cout << "Lista vacia" << endl;
    }
}