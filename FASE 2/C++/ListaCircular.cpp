#include "ListaCircular.h"
#include "SHA256.h"
#include <iostream>

using namespace std;


void ListaCircular::registro_usuario(int id,string nombreuser, string contracifrada, int monedas ,int edad){
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
				nuevo->id = id;
				nuevo->nombreuser = nombreuser;
				//nuevo->contra = contra;
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
		nuevo->id = id;
		nuevo->nombreuser = nombreuser;
		//nuevo->contra = contra;
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

void ListaCircular::registro_usuarioJ(int id,string nombreuser, string contracifrada, int monedas ,int edad){
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
				nuevo-> id = id;
                nuevo->nombreuser = nombreuser;
                //nuevo->contra = contra;
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
		nuevo-> id = id;
        nuevo->nombreuser = nombreuser;
        //nuevo->contra = contra;
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

string ListaCircular::getUsers() {
    nodoUsuarios*aux = primero;
	string datos = "";
	datos += "\"usuario\":[";
	while (aux != NULL){
		datos += "{";
		datos+= "\"id\":\"" + to_string(aux->id) + "\",";
		datos+= "\"nick\":\"" + aux->nombreuser + "\",";
		datos+= "\"password\":\"" + aux->contracifrada + "\",";
		datos+= "\"monedas\":\"" + to_string(aux->monedas) + "\",";
		datos+= "\"edad\":\"" + to_string(aux->edad) + "\"";
		datos += "}"; 

	aux = aux->siguiente;
	if(aux!=primero){
		datos+= ",";
	}
	if(aux == primero){
		break;
	}

	}
	datos += "]";
	return datos;	
}


void ListaCircular::Comprobar(string nombreuser) {

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
    
}

string ListaCircular:: verificarLog(string usuariob, string cifrada){
	string dato = "";
	bool encontrado = false;
	nodoUsuarios *actual;
	actual = primero;
	if(primero!=NULL){
		/*if (usuariob == "EDD" && cifrada == "857aba7c59662e1c306cf59c0c2199ec1d2ce895a928fb62b54f034760ebe8a6"){
				encontrado = true;
				dato += "admin";
				return dato;
		} */
        do{
			string contr = "edd123";
			string uss = "EDD";
			string nuevocif = SHA256::cifrar(contr);
            //cout<<"El cifrado sha a comparar es : "<<actual->contracifrada<<endl;
            if(actual->nombreuser==usuariob && actual->contracifrada==cifrada){
				if (actual->nombreuser == uss && actual->contracifrada == nuevocif){
					encontrado = true;
					dato += "admin";
					return dato;
				}
				else{
				encontrado = true;
				//Buscar(usuariob); 
                cout<<"Inicio de sesión correctos"<<endl;
				//dato += actual->nombreuser;
				dato += "correcto";
				return dato;
				}
                
            }
            actual = actual->siguiente;
        }while(actual!=primero && encontrado != true);
        
        if(!encontrado){
            cout << "\nUsuario o contraseña incorrectos\n\n";
			dato += "incorrecto";
			return dato;
        }
    }else{
        cout << "\nNo existe el usuario en la lista\n\n";
		dato += "inexistente";
		return dato;
    }
}


string ListaCircular::registro_usuario1(int id,string nombreuser, string contracifrada, int monedas ,int edad){
	string datos = "";
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
				nuevo->id = id;
				nuevo->nombreuser = nombreuser;
				//nuevo->contra = contra;
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
			datos += "true";
			return datos;
	}
		
	if(primero == NULL){
		nodoUsuarios *nuevo = new nodoUsuarios();
		nuevo->id = id;
		nuevo->nombreuser = nombreuser;
		//nuevo->contra = contra;
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
		datos += "true2";
		return datos;
		cout<<"\nUsuario registrado"<<endl;
	}
}


string ListaCircular::Buscar(string user)
{
	string salida = "";
	string salida2= "";
    if (primero == NULL)
        return "El valor no se encuentra en la lista";

    string out = "";
    int contador = 0;
    nodoUsuarios *actual = primero;

	bool encontrado = false;
	if(primero != NULL){
		do{
			if(actual->nombreuser==user){
				cout<<"\n";
				cout<<"Ha sido encontrado"<<endl;
				cout<<" "<< actual->edad<<"\n";
				cout<<" "<< actual->monedas<<"\n";
				salida += actual->nombreuser;
				salida2 += actual-> edad;
				encontrado = true;			
				return salida, salida2;	
			}
			actual = actual->siguiente;	
		}while(actual!=primero && encontrado != true);
	}

}