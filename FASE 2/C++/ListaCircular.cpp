#include "ListaCircular.h"
//#include "json/json.h"
//#include "jsoncpp.cpp"
#include "SHA256.h"
#include <iostream>

using namespace std;
std:: string userlogin;

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

void ListaCircular::login(){
    nodoUsuarios* actual = new nodoUsuarios();
    actual = primero;
    bool encontrado = false;
    string nodoBuscado;
    string usuariob, contrab;
    char caracter;
    cout << "Ingrese su usuario: "<<endl;
    cin >> usuariob;
    cout << "Ingrese su contraseña: "<<endl;
    cin >> contrab;
    string cifrada = SHA256::cifrar(contrab);
    //cout<<"El cifrado sha es : "<<cifrada<<endl;
    
    cout<<"\n";
    if(primero!=NULL){
        do{
            //cout<<"El cifrado sha a comparar es : "<<actual->contracifrada<<endl;
            if(actual->nombreuser==usuariob && actual->contracifrada==cifrada){
                encontrado = true;  
                cout<<"Inicio de sesión correctos"<<endl;
                userlogin = actual->nombreuser;
                sub_login(actual->nombreuser, actual->contra,actual-> edad, actual->monedas);
            }
            actual = actual->siguiente;
        }while(actual!=primero && encontrado != true);
        
        if(!encontrado){
            cout << "\nUsuario o contraseña incorrectos\n\n";
        }
        
    }else{
        cout << "\nNo existe el usuario en la lista\n\n";
    }
}


void ListaCircular::sub_login(string nombreuser, string contra,int edad, int monedas){
    int op1=0;
    char prueba;
    do {
    cout<<"************ Usuario ***********"<<endl;
    cout<<"* 1. Editar Informacion        *"<<endl;
    cout<<"* 2. Eliminar Cuenta           *"<<endl;
    cout<<"* 3. Ver tutorial              *"<<endl;
    cout<<"* 4. Ver articulos de tienda   *"<<endl;
    cout<<"* 5. Realizar movimientos      *"<<endl;
    cout<<"* 6. Cerrar sesión             *"<<endl;
    cout<<"********************************"<<endl;
    cin>>op1;
    cout<<"\n";
    switch(op1){
        case 1:
            cout<<"Datos del Usuario"<<endl;
            cout<<"Nick -> "<< nombreuser <<endl;
            cout<<"Edad -> "<< edad <<endl;
            cout<<"Contraseña -> "<< contra <<endl;
            cout<<"\n";
            editar_info(nombreuser, edad, contra);
            break;
        case 2:
            //cout<<"Eliminar cuenta\n";
            eliminarCuenta(nombreuser);
            break;
        case 3:
            cout<<"\nTutorial"<<endl;
            //verTutorial();
            break;
                        
        case 4:
			cout<<"Tienda\n";
            //Mostrar_Tienda(monedas);
            break;
        case 5:
            cout<<"Realizar Movimientos"<<endl;
            //movimientos(nombreuser);
            break;
        case 6:
            cout << "\nSe cerró la sesión\n";
            break;
        default:
            cout << "\nIngrese una opcion correcta\n\n";
        }   
    }while (op1!=6);
}

void ListaCircular::editar_info(string nombreuser, int edad, string contra){
    int opcio;
    cout<<"\n";
    cout<<"Elija lo que quiere editar: "<<endl;
    cout<<"1. Editar Nick"<<endl;
    cout<<"2. Editar Edad"<<endl;
    cout<<"3. Editar Contraseña"<<endl;
    cout<<"4. Regresar"<<endl;
    cin>>opcio;

    switch (opcio){
    case 1:
        cout<<"Opcion 1";
        modificarNick(nombreuser);
        break;
    case 2:
        cout<<"Opcion 2";
        modificarEdad(edad);
        break;
    case 3:
        cout<<"Opcion 3";
        modificarContra(contra);
        break;
    case 4:
        cout<<"\n";
        break;  
    default:
        cout << "\nIngrese una opcion correcta\n\n";
        break;
    }
}

void ListaCircular::modificarNick(string userb){
    nodoUsuarios* actual = new nodoUsuarios();
    actual = primero;
    bool encontrado = false;
    if(primero!=NULL){
        do{
            if(actual->nombreuser==userb){
                cout << "\n Ingrese el nuevo Nick: ";
                cin >> actual->nombreuser;
                cout << "\n Para efectuar los cambios debe cerrar sesión e iniciar con el nuevo usuario\n\n";
                encontrado = true;              
            }
            actual = actual->siguiente;
        }while(actual!=primero && encontrado != true);  
    }
}

void ListaCircular::modificarEdad(int edad){
    nodoUsuarios* actual = new nodoUsuarios();
    actual = primero;
    bool encontrado = false;
    if(primero!=NULL){
        do{
            if(actual->edad==edad){
                cout << "\n Ingrese la nueva Edad: ";
                cin >> actual->edad;
                cout << "\n Para efectuar los cambios debe volver a iniciar sesión\n\n";    
                encontrado = true;              
            }   
            actual = actual->siguiente;
        }while(actual!=primero && encontrado != true);  
    }
}

void ListaCircular::modificarContra(string contra){
    nodoUsuarios* actual = new nodoUsuarios();
    actual = primero;
    string cambiocontra;
    bool encontrado = false;
    if(primero!=NULL){
        do{
            if(actual->contra==contra){
                cout << "\n Ingrese la nueva Contraseña: ";
                cin>>cambiocontra;
                //cin >> actual->contra;
                string encriptado = SHA256::cifrar(cambiocontra);
                actual->contracifrada = encriptado;
                actual->contra = cambiocontra;
                cout << "\n Para efectuar los cambios debe cerrar sesión e iniciar con la nueva contraseña\n\n";
                encontrado = true;              
            }
            actual = actual->siguiente;
        }while(actual!=primero && encontrado != true);  
    }
}

void ListaCircular::eliminarCuenta(string userbuscado){
    nodoUsuarios* actual = new nodoUsuarios();
    actual = primero;
    nodoUsuarios* anterior = new nodoUsuarios();
    anterior = NULL;
    bool encontrado = false;
    string opc;
    cout<<"Desea eliminar su cuenta permanentemente [y/s] : " <<endl; 
    cin>>opc;
    if (opc == "y"){
        if(primero!=NULL){
        do{
            if(actual->nombreuser==userbuscado){                
                if(actual==primero){
                    primero = primero->siguiente;
                    primero->anterior = ultimo;
                    ultimo->siguiente = primero;
                }else if(actual==ultimo){
                    ultimo = anterior;
                    ultimo->siguiente = primero;
                    primero->anterior = ultimo;
                }else{
                    anterior->siguiente = actual->siguiente;
                    actual->siguiente->anterior = anterior;
                }
                cout << "\nLa cuenta ha sido eliminada\n\n";
                encontrado = true;      
            }
            anterior = actual;
            actual = actual->siguiente;
        }while(actual!=primero && encontrado != true);      
    }
    cout<<"Cerrando la sesión"<<endl;
    cout<<"\n";
    //MenuPrincipal();
    }
    if (opc == "s"){
        cout<<"\nRegresando\n"<<endl;
        return;
    }
    else{
        cout<<"Ingrese una opcion valida"<<endl;
    }
}