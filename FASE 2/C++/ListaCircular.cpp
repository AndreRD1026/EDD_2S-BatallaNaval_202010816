#include "ListaCircular.h"
#include "SHA256.h"
#include <iostream>

using namespace std;


void ListaCircular::registro_usuario(string nombreuser, string contra, int monedas ,int edad, string contracifrada){
	nodoUsuarios *actual = new nodoUsuarios();
	actual = primero;
	bool encontrado = false;

	if(primero != NULL){
		do{
			if(actual->nombreuser==nombreuser){
				cout<<"\n";
				cout<<"No se puede agregar porque ya existe un ususario con ese Nick"<<endl;
				encontrado = true;				
			}
			actual = actual->siguiente;	
		}while(actual!=primero && encontrado != true);
	}
	if(primero!= NULL  && encontrado==false){
			if(actual->nombreuser!=nombreuser){
				nodoUsuarios *nuevo = new nodoUsuarios();
				nuevo->nombreuser = nombreuser;
				nuevo->contra = contra;
				nuevo->monedas = monedas;
				nuevo->edad = edad;
				nuevo->contracifrada = contracifrada;

				if (primero==NULL) {
					primero=nuevo;
					ultimo=nuevo;
					primero -> siguiente=primero;
					primero -> anterior=ultimo;
				}else{
					ultimo-> siguiente=nuevo;
					nuevo-> anterior=ultimo;
					nuevo-> siguiente=primero;
					ultimo=nuevo;
					primero-> anterior=ultimo;
				}
				cout<<"\nUsuario registrado"<<endl;
			}
	}
		
	if(primero == NULL){
		nodoUsuarios *nuevo = new nodoUsuarios();
		nuevo->nombreuser = nombreuser;
		nuevo->contra = contra;
		nuevo->monedas = monedas;
		nuevo->edad = edad;
		nuevo->contracifrada = contracifrada;

		if (primero==NULL) {
			primero=nuevo;
			ultimo=nuevo;
			primero -> siguiente=primero;
			primero -> anterior=ultimo;
		}else{
			ultimo-> siguiente=nuevo;
			nuevo-> anterior=ultimo;
			nuevo-> siguiente=primero;
			ultimo=nuevo;
			primero-> anterior=ultimo;
		}
		cout<<"\nUsuario registrado"<<endl;
	}

}

void ListaCircular::registro_usuarioJ(string nombreuser, string contra, int monedas ,int edad, string contracifrada){
    nodoUsuarios *actual = new nodoUsuarios();
    actual = primero;
    bool encontrado = false;

    if(primero != NULL){
        do{
            if(actual->nombreuser==nombreuser){
                encontrado = true;              
            }
            actual = actual->siguiente; 
        }while(actual!=primero && encontrado != true);
    }
    if(primero!= NULL  && encontrado==false){
            if(actual->nombreuser!=nombreuser){
                nodoUsuarios *nuevo = new nodoUsuarios();
                nuevo->nombreuser = nombreuser;
                nuevo->contra = contra;
                nuevo->monedas = monedas;
                nuevo->edad = edad;
                nuevo->contracifrada = contracifrada;

                if (primero==NULL) {
                    primero=nuevo;
                    ultimo=nuevo;
                    primero -> siguiente=primero;
                    primero -> anterior=ultimo;
                }else{
                    ultimo-> siguiente=nuevo;
                    nuevo-> anterior=ultimo;
                    nuevo-> siguiente=primero;
                    ultimo=nuevo;
                    primero-> anterior=ultimo;
                }
            }
    }   
    if(primero == NULL){
        nodoUsuarios *nuevo = new nodoUsuarios();
        nuevo->nombreuser = nombreuser;
        nuevo->contra = contra;
        nuevo->monedas = monedas;
        nuevo->edad = edad;
        nuevo->contracifrada = contracifrada;

        if (primero==NULL) {
            primero=nuevo;
            ultimo=nuevo;
            primero -> siguiente=primero;
            primero -> anterior=ultimo;
        }else{
            ultimo-> siguiente=nuevo;
            nuevo-> anterior=ultimo;
            nuevo-> siguiente=primero;
            ultimo=nuevo;
            primero-> anterior=ultimo;
        }
        //cout<<"\nUsuario registrado"<<endl;
    }

}

void ListaCircular::lista_usuarios() {
    nodoUsuarios *actual = new nodoUsuarios();
    actual = primero;
    if (primero!=NULL) {
        do {
            cout <<"| "<<"Nick: "<<actual->nombreuser<<" Contra: "<<actual->contra<<" Monedas: "<<actual->monedas<<" Edad: "<<actual->edad <<"| ";
            actual = actual -> siguiente;
        } while(actual!=primero);
    }else{
        std::cout << "Lista vacia" << endl;
    }
 
}

void ListaCircular::ordenarUsuarioASC(){
	nodoUsuarios* cabeza = new nodoUsuarios();
	cabeza = primero;
	int cambiopos;

	nodoUsuarios* lado_izq;
	nodoUsuarios* lado_der;
	if(primero!=NULL){
		do{	
		cambiopos = 0;
		lado_izq = cabeza;
		while(lado_izq->siguiente != primero){

			if (lado_izq->edad > lado_izq->siguiente->edad){
				intercambioASC(lado_izq, lado_izq->siguiente); 
                cambiopos = 1; 
			}
			lado_izq = lado_izq->siguiente;
			lado_der = lado_izq;
		}
	}while(cambiopos);
		ListaUsuarioASC(cabeza);
	}
}

void ListaCircular:: intercambioASC(nodoUsuarios *lado_izq, nodoUsuarios *lado_der){
	string nombreus = lado_izq->nombreuser;
	string contraa = lado_izq->contra;
	string contraci = lado_izq->contracifrada;
	int temp = lado_izq->edad;
	int mone = lado_izq->monedas;
	lado_izq->edad = lado_der -> edad;
	lado_izq->nombreuser = lado_der -> nombreuser;
	lado_izq->contra = lado_der -> contra;
	lado_izq->contracifrada = lado_der -> contracifrada;
	lado_izq->monedas = lado_der -> monedas;
	lado_der -> edad = temp;
	lado_der -> nombreuser = nombreus;
	lado_der -> contra = contraa;
	lado_der -> contracifrada = contraci;
	lado_der -> monedas = mone;
}

void ListaCircular:: ListaUsuarioASC(nodoUsuarios *cabeza) {
	nodoUsuarios *inicio = cabeza;

	cout << "  "<< left << setw( 15 ) << "NICK"<< " "<< left << setw( 12 ) << "Monedas"<< "   "<< left << setw( 12 ) << "Edad"<< " "<< left << setw( 15 ) << "Contra"<< " "<<endl;	
	while(inicio)
	{
		cout << "  "<< left << setw( 15 ) <<inicio->nombreuser<< " "<< left << setw( 12 ) << inicio->monedas<< "   "<< left << setw( 12 ) << inicio->edad<< " "<< left << setw( 12 ) <<inicio->contracifrada<< " "<<endl;
		inicio = inicio->siguiente;
		if(inicio == primero){
			break;
		}
	}
	cout<<"\n\n";
}


void ListaCircular:: ordenarUsuarioDESC(){
	nodoUsuarios* cabeza = new nodoUsuarios();
	cabeza = primero;
	int cambiopos;

	nodoUsuarios* lado_izq;
	nodoUsuarios* lado_der;
	if(primero!=NULL){
		do{	
		cambiopos = 0;
		lado_izq = cabeza;
		while(lado_izq->siguiente != primero){

			if (lado_izq->edad < lado_izq->siguiente->edad){
				intercambioDESC(lado_izq, lado_izq->siguiente); 
                cambiopos = 1; 
			}
			lado_izq = lado_izq->siguiente;
			lado_der = lado_izq;
		}
	}while(cambiopos);
		ListaUsuarioDESC(cabeza);
	}
}

void ListaCircular:: intercambioDESC(nodoUsuarios *lado_izq, nodoUsuarios *lado_der){
	string nombreus = lado_izq->nombreuser;
	string contraa = lado_izq->contra;
	string contraci = lado_izq->contracifrada;
	int temp = lado_izq->edad;
	int mone = lado_izq->monedas;
	lado_izq->edad = lado_der -> edad;
	lado_izq->nombreuser = lado_der -> nombreuser;
	lado_izq->contra = lado_der -> contra;
	lado_izq->contracifrada = lado_der -> contracifrada;
	lado_izq->monedas = lado_der -> monedas;
	lado_der -> edad = temp;
	lado_der -> nombreuser = nombreus;
	lado_der -> contra = contraa;
	lado_der -> contracifrada = contraci;
	lado_der -> monedas = mone;
}

void ListaCircular:: ListaUsuarioDESC(nodoUsuarios *cabeza)
{
	nodoUsuarios *inicio = cabeza;

	cout << "  "<< left << setw( 15 ) << "NICK"<< " "<< left << setw( 12 ) << "Monedas"<< "   "<< left << setw( 12 ) << "Edad"<< " "<< left << setw( 15 ) << "Contra"<< " "<<endl;	
	while(inicio)
	{
		cout << "  "<< left << setw( 15 ) <<inicio->nombreuser<< " "<< left << setw( 12 ) << inicio->monedas<< "   "<< left << setw( 12 ) << inicio->edad<< " "<< left << setw( 12 ) <<inicio->contracifrada<< " "<<endl;
		inicio = inicio->siguiente;
		if(inicio == primero){
			break;
		}
	}
	cout<<"\n\n";
}


unsigned ListaCircular:: registro_usuario1(string nombreuser, string contra, int monedas, int edad){
	nodoUsuarios *actual = new nodoUsuarios();
	actual = primero;
	bool encontrado = false;

	if(primero != NULL){
		do{
			if(actual->nombreuser==nombreuser){
				cout<<"\n";
				cout<<"No se puede agregar porque ya existe un ususario con ese Nick"<<endl;
				encontrado = true;				
			}
			actual = actual->siguiente;	
		}while(actual!=primero && encontrado != true);
	}
	if(primero!= NULL  && encontrado==false){
			if(actual->nombreuser!=nombreuser){
				nodoUsuarios *nuevo = new nodoUsuarios();
				nuevo->nombreuser = nombreuser;
				nuevo->contra = contra;
				nuevo->monedas = monedas;
				nuevo->edad = edad;

				if (primero==NULL) {
					primero=nuevo;
					ultimo=nuevo;
					primero -> siguiente=primero;
					primero -> anterior=ultimo;
				}else{
					ultimo-> siguiente=nuevo;
					nuevo-> anterior=ultimo;
					nuevo-> siguiente=primero;
					ultimo=nuevo;
					primero-> anterior=ultimo;
				}
				cout<<"\nUsuario registrado"<<endl;
			}
	}
		
	if(primero == NULL){
		nodoUsuarios *nuevo = new nodoUsuarios();
		nuevo->nombreuser = nombreuser;
		nuevo->contra = contra;
		nuevo->monedas = monedas;
		nuevo->edad = edad;

		if (primero==NULL) {
			primero=nuevo;
			ultimo=nuevo;
			primero -> siguiente=primero;
			primero -> anterior=ultimo;
		}else{
			ultimo-> siguiente=nuevo;
			nuevo-> anterior=ultimo;
			nuevo-> siguiente=primero;
			ultimo=nuevo;
			primero-> anterior=ultimo;
		}
		cout<<"\nUsuario registrado"<<endl;
	}
	return true;
}



string ListaCircular::getUsers() {


    if (primero == NULL)
        return "[\n]";

    string out = "";
    nodoUsuarios *aux = primero;
    while (aux != NULL)
    {

        out += "{\"Nick\": \"" + (aux->nombreuser) + "\"}";
        aux = aux->siguiente;
        if (aux != NULL)
        {
            out += ",";
        }
    }
    return "[\n " + out + "\n]";
}


/*
string ListaCircular::Buscar(string usuario)
{
    if (primero == NULL)
        return "El valor no se encuentra en la lista";

    string out = "";
    int contador = 0;
    nodoUsuarios *aux = primero;
    while (aux != NULL)
    {

        if (aux->nombreuser == usuario)
        {
            return "El id se encuntra en la posicion " + to_string(contador);
        }
        aux = aux->siguiente;
        contador++;
    }
    return "El valor no se encuentra en la lista";
}

*/