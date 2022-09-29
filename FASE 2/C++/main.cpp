#include<iostream>
#include <curses.h>
#include<fstream>
#include<string.h>
#include<string>
#include<stdlib.h>
#include <sstream>
#include "json/json.h"
#include "jsoncpp.cpp"
#include "SHA256.h"
#include "ListaCircular.cpp"
#include "ListaTutorial.cpp"
#include "ListaArticulos.cpp"
#include "ListaPila.cpp"
#include "ArbolB.cpp"
#include <cstdlib>

using namespace std;

void MenuPrincipal();
void cargamasiva();
void registrousuario();
void reportes();
void login();
void sub_login(string nombreuser, string contra,int edad, int monedas);
void editar_info(string nombreuser, int edad, string contra);
void modificarNick(string userb);
void modificarEdad(int edad);
void modificarContra(string contra);
void eliminarCuenta(string userbuscado);
void movimientos(string nombreuser);
void vaciarPila();
void SumaPuntosJugada(string user);


std:: string userlogin;
std:: string nombrejugada;
int contadorusuarios = 0;

ListaCircular Listausuarios;
ListaTutorial ListaCola;
ListaPila ListaMovimientos;
ListaArticulos ListaArt;
ArbolB pruebas;

int main(int argc, char** argv) {

	MenuPrincipal();
}


void MenuPrincipal(){
	    int op=0;
	do {
	cout<<"************* Menu *************"<<endl;
	cout<<"* 1. Carga Masiva              *"<<endl;
    cout<<"* 2. Registrar Usuario         *"<<endl;
    cout<<"* 3. Login                     *"<<endl;
    cout<<"* 4. Reportes                  *"<<endl;
    cout<<"* 5. Salir del juego           *"<<endl;
	cout<<"********************************"<<endl;
	cin>>op;
	switch(op){
		case 1:
			cout<<"\n";
			cargamasiva();
            break;
		case 2:
            cout<<"\n";
			registrousuario();
            break;
		case 3:
            //Listausuarios.login();
            login();
			break;
        case 4:
            reportes();
            break;
		case 5:
			cout << "\nFin del programa\n";
			break;
		default:
			cout << "\nIngrese una opcion correcta\n\n";
			break;
		}	
    }while (op!=5);
}

void registrousuario(){
	//ListaCircular Listausuarios;
	string nombreuser, contra;
	int monedas, edad;
	cout << "Ingresa el nombre de usuario: "<<endl;
	cin >> nombreuser;
	cout << "Ingresa la contraseña: "<<endl;
	cin >> contra;
	//cout << "Ingresa las monedas actual: "<<endl;
	//cin >> monedas;
	monedas = 0;
	cout << "Ingresa la edad: "<<endl;
	cin >> edad;
	string encriptado = SHA256::cifrar(contra);
	//cout<<"El cifrado sha es : "<<encriptado<<endl;
	Listausuarios.registro_usuario(contadorusuarios,nombreuser,encriptado,monedas,edad);
    pruebas.insertar(contadorusuarios, nombreuser);
    contadorusuarios++;
	cout<<"\n";
}


void cargamasiva(){
    //int contador = 0;
    ifstream archivo;
    string ruta;
    string texto;
    string nombreuser,contra,monedas,edad;
    string idarticuloo, categoriarticulo,precioarticuloo,nombrearticulo,srcarticulo;
    string alt, anch, x1, y1;
    cout<<"Ingrese la ruta del archivo "<<endl;
    cin.ignore();
    getline(cin,ruta);
    //archivo.open("informacion.json", ios::in);
    archivo.open(ruta.c_str(), ios::in);
    if(archivo.fail()){
        cout<<"\nNo se pudo abrir el archivo\n"<<endl;
    }

    while (!archivo.eof())
    {
        Json::Reader reader;
        Json::Value obj;
        reader.parse(archivo, obj); 
        const Json::Value& usuariosJ = obj["usuarios"]; 
        for (int i = 0; i < usuariosJ.size(); i++){
            //cout << "\nNick: " << usuariosJ[i]["nick"].asString();
            nombreuser = usuariosJ[i]["nick"].asString();
            //cout << "\nPass: " << usuariosJ[i]["password"].asString();
            contra = usuariosJ[i]["password"].asString();
            string encriptado = SHA256::cifrar(contra);
            //cout<<"El cifrado sha es : "<<encriptado<<endl;
            //cout << "\nMonedas: " << usuariosJ[i]["monedas"].asString();
            monedas = usuariosJ[i]["monedas"].asString();
            //cout << "\nEdad: " << usuariosJ[i]["edad"].asString();
            edad = usuariosJ[i]["edad"].asString();
            std ::string edadi = edad;
            std ::string monedasi = monedas;
            int eddi = std::stoi(edadi);
            int monedi = std::stoi(monedasi);
            Listausuarios.registro_usuarioJ(contadorusuarios,nombreuser,encriptado,monedi,eddi);
            pruebas.insertar(contadorusuarios,nombreuser);
            contadorusuarios++;
        }

        const Json::Value& articulosJ = obj["articulos"]; 
        for (int i = 0; i < articulosJ.size(); i++){
            //cout << "\nID: " << articulosJ[i]["id"].asString();
            idarticuloo = articulosJ[i]["id"].asString();
            //cout << "\nCategoria: " << articulosJ[i]["categoria"].asString();
            categoriarticulo = articulosJ[i]["categoria"].asString();
            //cout << "\nPrecio: " << articulosJ[i]["precio"].asString();
            precioarticuloo = articulosJ[i]["precio"].asString();
            articulosJ[i]["precio"].asString();
            //cout << "\nNombre: " << articulosJ[i]["nombre"].asString();
            nombrearticulo = articulosJ[i]["nombre"].asString();
            //cout << "\nSRC: " << articulosJ[i]["src"].asString();
            srcarticulo = articulosJ[i]["src"].asString();
            //std ::string iarticulo = idarticuloo;
            std ::string precioarticul = precioarticuloo;
            int precioarticulo = std::stoi(precioarticul);
            //int idarticulo = std::stoi(iarticulo);
            //registro_articulos(categoriarticulo,nombrearticulo,precioarticulo,idarticuloo,srcarticulo);
            ListaArt.registro_articulos(categoriarticulo,nombrearticulo,precioarticulo,idarticuloo,srcarticulo);
            //cout << endl;
        }

        const Json::Value& tutorialJ = obj["tutorial"];
        //cout <<"\nAncho: "<<tutorialJ["ancho"].asString();
        anch = tutorialJ["ancho"].asString();
        //cout<<"\nAlto: "<<tutorialJ["alto"].asString();
        alt = tutorialJ["alto"].asString();
        std ::string ancho = anch;
        std ::string alto = alt;
        int x = std::stoi(ancho);
        int y = std::stoi(alto);
        ListaCola.registroTutorial(x,y);
        //cout<<"\nMovimientos: ";
        const Json::Value& movimientosJ = tutorialJ["movimientos"];
        for(int i = 0; i < movimientosJ.size(); i++){
            //cout << "\nX: " << movimientosJ[i]["x"].asString();
            x1 = movimientosJ[i]["x"].asString();
            //cout << " Y: " << movimientosJ[i]["y"].asString();
            y1 = movimientosJ[i]["y"].asString();
        int x = std::stoi(x1);
        int y = std::stoi(y1);
        ListaCola.registroTutorial(x,y);
        }
        cout<<"\n";
        cout<<"\nArchivo cargado con exito\n"<<endl;
        break;
    }
    archivo.close();
    return;
}

void reportes(){
	int opreport;
	cout<<"\n";
	cout<<"************** Menu reportes **************"<<endl;
	cout<<"1. Estructuras Utilizadas"<<endl;
	cout<<"2. Listado de usuarios ordenados por edad"<<endl;
	cout<<"3. Listado de articulos ordenados por precio"<<endl;
	cout<<"4. Regresar al menu principal"<<endl;
	cout<<"*****************************************"<<endl;
	cin >> opreport;
	cout<<"\n";
	switch (opreport)
	{
	case 1:
	int opcestruct;
		cout<<"1. Lista Usuarios"<<endl;
		cout<<"2. Lista Articulos"<<endl;
		cout<<"3. Tutorial"<<endl;
		cout<<"4. Listado de Jugadas"<<endl;
		cout<<"5. Regresar al menu principal"<<endl;
		cin>> opcestruct;
		cout<<"\n";
		switch (opcestruct){
		case 1:
            cout<<"Hola";
            //Listausuarios.GraficoListaCDobleEnlace();
			break;
		case 2:
            cout<<"Lista de listas\n";
            ListaArt.GraficoListadeListas();
			break;
		case 3:
            ListaCola.GraficoTutorial();
			break;
		case 4:
            cout<<"Movimientos\n";
            ListaMovimientos.GraficoMovimientos(userlogin, nombrejugada);
			break;
		case 5:
			cout<<"\n";
			return;
			break;	
		default:
			cout<<"\nIngrese una opcion correcta\n"<<endl;
			break;
		}
		break;
	
	case 2:
	int ordenl;
		cout<<"1. Orden Ascendente"<<endl;
		cout<<"2. Orden Descendente"<<endl;
		cout<<"3. Regresar al menu principal"<<endl;
		cin>> ordenl;
		cout<<"\n";
		switch (ordenl)
		{
		case 1:
			cout<<"lista usuarios de forma ascendente\n"<<endl;
            Listausuarios.ordenarUsuarioASC();
			return;
			break;
			
		
		case 2:
			cout<<"lista usuarios de forma descendente\n"<<endl;
            Listausuarios.ordenarUsuarioDESC();
			return;
			break;

	
		case 3:
			cout<<"\n";
			return;
			break;
		default:
			cout<<"\nIngrese una opcion correcta\n";
			break;
		}
	
	case 3:
	int ordenp;
		cout<<"1. Orden Ascendente"<<endl;
		cout<<"2. Orden Descendente"<<endl;
		cout<<"3. Regresar al menu principal"<<endl;
		cin>> ordenp;

		switch (ordenp)
		{
		case 1:
    /*pruebas.insertar(10, "Pamela");
    pruebas.insertar(15, "Jose");
    pruebas.insertar(16, "Maria");
    pruebas.insertar(18, "Javier");
    pruebas.insertar(20, "Will");
    pruebas.insertar(25, "Andy");
    pruebas.insertar(30, "Michael");
    pruebas.insertar(40, "Juan");
    pruebas.insertar(50, "Walter");
    pruebas.insertar(70, "Pedro");
    pruebas.insertar(75, "Santiago");
    pruebas.insertar(80, "Orlando");
    pruebas.insertar(90, "Paula"); */
    pruebas.Grafo(); 
			cout<<"lista articulos de forma precio ascendente"<<endl;
			//ordenarPrecioASC();
			return;
			break;
		
		case 2:
			cout<<"lista usuarios de forma precio descendente"<<endl;
			return;
			break;
		case 3:
			cout<<"\n";
			return;
			break;
		default:
			cout<<"Ingrese una opcion correcta\n";
			break;
		}
	case 4:
		cout<<"\n";
		return;
		break;
	default:
		cout<<"\nIngrese una opcion correcta\n";
		break;
	}
	
	cout<<"\n";
}

void login(){
    nodoUsuarios* actual = new nodoUsuarios();
    actual = Listausuarios.primero;
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
    if(Listausuarios.primero!=NULL){
        do{
            //cout<<"El cifrado sha a comparar es : "<<actual->contracifrada<<endl;
            if(actual->nombreuser==usuariob && actual->contracifrada==cifrada){
                encontrado = true;  
                cout<<"Inicio de sesión correctos"<<endl;
                userlogin = actual->nombreuser;
                sub_login(actual->nombreuser, actual->contra,actual-> edad, actual->monedas);
            }
            actual = actual->siguiente;
        }while(actual!=Listausuarios.primero && encontrado != true);
        
        if(!encontrado){
            cout << "\nUsuario o contraseña incorrectos\n\n";
        }
        
    }else{
        cout << "\nNo existe el usuario en la lista\n\n";
    }
}


void sub_login(string nombreuser, string contra,int edad, int monedas){
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
            cout<<"Eliminar\n";
            eliminarCuenta(nombreuser);
            break;
        case 3:
            cout<<"\nTutorial"<<endl;
            ListaCola.verTutorial();
            break;
                        
        case 4:
            cout<<"Tienda\n";
            ListaArt.Mostrar_Tienda(monedas);
            break;
        case 5:
            cout<<"Realizar Movimientos"<<endl;
            userlogin = nombreuser;
            movimientos(nombreuser);
            break;
        case 6:
            cout << "\nSe cerró la sesión\n";
            break;
        default:
            cout << "\nIngrese una opcion correcta\n\n";
        }   
    }while (op1!=6);
}

void editar_info(string nombreuser, int edad, string contra){
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

void modificarNick(string userb){
    nodoUsuarios* actual = new nodoUsuarios();
    actual = Listausuarios.primero;
    bool encontrado = false;
    if(Listausuarios.primero!=NULL){
        do{
            if(actual->nombreuser==userb){
                cout << "\n Ingrese el nuevo Nick: ";
                cin >> actual->nombreuser;
                cout << "\n Para efectuar los cambios debe cerrar sesión e iniciar con el nuevo usuario\n\n";
                encontrado = true;              
            }
            actual = actual->siguiente;
        }while(actual!=Listausuarios.primero && encontrado != true);  
    }
}

void modificarEdad(int edad){
    nodoUsuarios* actual = new nodoUsuarios();
    actual = Listausuarios.primero;
    bool encontrado = false;
    if(Listausuarios.primero!=NULL){
        do{
            if(actual->edad==edad){
                cout << "\n Ingrese la nueva Edad: ";
                cin >> actual->edad;
                cout << "\n Para efectuar los cambios debe volver a iniciar sesión\n\n";    
                encontrado = true;              
            }   
            actual = actual->siguiente;
        }while(actual!=Listausuarios.primero && encontrado != true);  
    }
}

void modificarContra(string contra){
    nodoUsuarios* actual = new nodoUsuarios();
    actual = Listausuarios.primero;
    string cambiocontra;
    bool encontrado = false;
    if(Listausuarios.primero!=NULL){
        do{
            if(actual->contra==contra){
                cout << "\n Ingrese la nueva Contraseña: ";
                cin>>cambiocontra;
                string encriptado = SHA256::cifrar(cambiocontra);
                actual->contracifrada = encriptado;
                actual->contra = cambiocontra;
                cout << "\n Para efectuar los cambios debe cerrar sesión e iniciar con la nueva contraseña\n\n";
                encontrado = true;              
            }
            actual = actual->siguiente;
        }while(actual!=Listausuarios.primero && encontrado != true);  
    }
}

void eliminarCuenta(string userbuscado){
    nodoUsuarios* actual = new nodoUsuarios();
    actual = Listausuarios.primero;
    nodoUsuarios* anterior = new nodoUsuarios();
    anterior = NULL;
    bool encontrado = false;
    string opc;
    cout<<"Desea eliminar su cuenta permanentemente [y/s] : " <<endl; 
    cin>>opc;
    if (opc == "y"){
        if(Listausuarios.primero!=NULL){
        do{
            if(actual->nombreuser==userbuscado){                
                if(actual==Listausuarios.primero){
                    Listausuarios.primero = Listausuarios.primero->siguiente;
                    Listausuarios.primero->anterior = Listausuarios.ultimo;
                    Listausuarios.ultimo->siguiente = Listausuarios.primero;
                }else if(actual==Listausuarios.ultimo){
                    Listausuarios.ultimo = anterior;
                    Listausuarios.ultimo->siguiente = Listausuarios.primero;
                    Listausuarios.primero->anterior = Listausuarios.ultimo;
                }else{
                    anterior->siguiente = actual->siguiente;
                    actual->siguiente->anterior = anterior;
                }
                cout << "\nLa cuenta ha sido eliminada\n\n";
                encontrado = true;      
            }
            anterior = actual;
            actual = actual->siguiente;
        }while(actual!=Listausuarios.primero && encontrado != true);      
    }
    cout<<"Cerrando la sesión"<<endl;
    cout<<"\n";
    MenuPrincipal();
    }
    if (opc == "s"){
        cout<<"\nRegresando\n"<<endl;
        return;
    }
    else{
        cout<<"Ingrese una opcion valida"<<endl;
    }
}


void movimientos(string nombreuser){
	int movx, movy;
	int contadormov = 0;
	int resp;
	cout<<"\t\t\nTokens: "<<contadormov<<endl;
	cout<<"Realizar movimientos\n";
	cout<<"Ingrese la coordenada X: ";
	cin>>movx;
	cout<<"Ingrese la coordenada Y: ";
	cin>>movy;
	ListaMovimientos.insertarPila(movx,movy);
	SumaPuntosJugada(nombreuser);

	cout<<"\nMovimiento - "<<movx<<","<<movy<<endl;

	cout<<"Desea realizar otro movimiento? "<<endl;
	cout<<"1. SI"<<endl;
	cout<<"2. NO"<<endl;
	cin>>resp;
	do{
		switch (resp)
	{
	case 1:
		contadormov +=1;
		cout<<"\t\t\nTokens: +"<<contadormov<<endl;
		cout<<"Realizar movimientos\n";
		cout<<"Ingrese la coordenada X: ";
		cin>>movx;
		cout<<"Ingrese la coordenada Y: ";
		cin>>movy;
		ListaMovimientos.insertarPila(movx,movy);
		SumaPuntosJugada(nombreuser);
		cout<<"Desea realizar otro movimiento? "<<endl;
		cout<<"1. SI"<<endl;
		cout<<"2. NO"<<endl;
		cin>>resp;
		if(resp==2){
		string nombremov;
		cout<<"Nombre para guardar movimientos: ";
		cin>>nombremov;
		nombrejugada = nombremov;
		cout<<"Se ha guardado la jugada\n";
		}
		break;
	case 2:
		string nombremov;
		cout<<"Nombre para guardar movimientos: ";
		cin>>nombremov;
		nombrejugada = nombremov;
		cout<<"Se ha guardado la jugada\n";
	}
	}while(resp!=2);
	
}

void vaciarPila(){
	nodoPila* actualPila = new nodoPila();
	actualPila = ListaMovimientos.primeroPila;
	nodoPila* anteriorPila = new nodoPila();
	anteriorPila = NULL;
	bool encontrado = false;
	if(ListaMovimientos.primeroPila!=NULL){
		while(actualPila!=NULL && encontrado != true){				
				if(actualPila == ListaMovimientos.primeroPila){
					ListaMovimientos.primeroPila = ListaMovimientos.primeroPila->siguientePila;
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


void SumaPuntosJugada(string user){
	nodoUsuarios* actualJugada = new nodoUsuarios();
	bool encontrado = false;
	int jugada = 1;
	actualJugada = Listausuarios.primero;
	if(Listausuarios.primero!=NULL){
		do{
			if(actualJugada->nombreuser==user){
				encontrado = true;
				actualJugada->monedas = actualJugada->monedas + jugada;
				break;
			}else{
				encontrado = false;
			}
			actualJugada = actualJugada->siguiente;
			}while(actualJugada!=Listausuarios.primero && encontrado!=true);
		}else{
			cout<<"No encontrado\n";
		}
	}