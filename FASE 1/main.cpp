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

using namespace std;


void MenuPrincipal();
void cargamasiva();
void registrousuario();
void login();
void sub_login(string nombreuser, string contra,int edad, int monedas);
void reportes();
void sub_reportes();
void registro_usuario(string nombreuser, string contra,int monedas, int edad, string contracifrada);
void registro_usuarioJ(string nombreuser, string contra,int monedas, int edad, string contracifrada);
void registro_articulos(string categoriaarticulo, string nombrearticulo, int precioarticulo, string idarticulo, string srcarticulo);
void registroTutorial(int x, int y);
void insertarPila(int movx, int movy);
void verTutorial();
void lista_usuarios();
void lista_usuariosordenada();
void eliminarCuenta(string nombreuser);
void editar_info(string nombreuser, int edad, string contra);
void modificarNick(string nombreuser);
void modificarEdad(int edad);
void modificarContra(string contra);
void GraficoListaCDobleEnlace();
void GraficoTutorial();
void movimientos(string nombreuser);
void desplegarPila();
void GraficoMovimientos(string nombreuser, string salida);
void Mostrar_Tienda(int monedas);
void ordenarPrecioASC();
void ordenarPrecioDESC();
void GraficoListadeListas();
void vaciarPila();
void ordenarUsuarioASC();
void ordenarUsuarioDESC();

std:: string userlogin;
std:: string nombrejugada;


struct nodo{
	string nombreuser, contra, contracifrada;
	int  monedas,edad; 
	nodo *anterior;
	nodo *siguiente;
} *primero=NULL, *ultimo=NULL;

struct NodoArticulos{
	int precioArticulo;
    string idArticulo,nombreArticulo,SRCArticulo;    
    NodoArticulos* siguienteArtic;
}*primeroArticulos, *ultimoArticulos;

struct NodoCategoria{
    string categoria;
    int indice;
    NodoCategoria* siguienteCA;
    NodoArticulos* abajo;
}*primeroCategoria, *ultimoCategoria;

struct nodoCola{
	int  x,y; 
	nodoCola* siguienteCola;
} *primeroCola, *ultimoCola;

struct nodoPila{
	int x,y;
	nodoPila* siguientePila;
} *primeroPila;

bool CategoriaRepetida(string _categoria);

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
			cargamasiva();
            break;
		case 2:
			registrousuario();
            break;
		case 3:
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

void cargamasiva(){
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
			registro_usuarioJ(nombreuser,contra,monedi,eddi,encriptado);
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
			registro_articulos(categoriarticulo,nombrearticulo,precioarticulo,idarticuloo,srcarticulo);
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
		registroTutorial(x,y);
		//cout<<"\nMovimientos: ";
		const Json::Value& movimientosJ = tutorialJ["movimientos"];
		for(int i = 0; i < movimientosJ.size(); i++){
			//cout << "\nX: " << movimientosJ[i]["x"].asString();
			x1 = movimientosJ[i]["x"].asString();
			//cout << " Y: " << movimientosJ[i]["y"].asString();
			y1 = movimientosJ[i]["y"].asString();
		int x = std::stoi(x1);
		int y = std::stoi(y1);
		registroTutorial(x,y);
		}
		cout<<"\n";
		cout<<"\nArchivo cargado con exito\n"<<endl;
		break;
	}
	archivo.close();
	return;
}

void registrousuario(){
	
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
	registro_usuario(nombreuser,contra,monedas, edad,encriptado);
	cout<<"\n";
}

void login(){
	nodo* actual = new nodo();
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
			GraficoListaCDobleEnlace();
			break;
		case 2:
			GraficoListadeListas();
			break;
		case 3:
			GraficoTutorial();
			break;
		case 4:
			GraficoMovimientos(userlogin,nombrejugada);
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
			ordenarUsuarioASC();
			return;
			break;
			
		
		case 2:
			cout<<"lista usuarios de forma descendente\n"<<endl;
			ordenarUsuarioDESC();
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

void registro_usuarioJ(string nombreuser, string contra, int monedas ,int edad, string contracifrada){
	nodo *actual = new nodo();
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
				nodo *nuevo = new nodo();
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
		nodo *nuevo = new nodo();
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

};

void registro_usuario(string nombreuser, string contra, int monedas ,int edad, string contracifrada){
	nodo *actual = new nodo();
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
				nodo *nuevo = new nodo();
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
		nodo *nuevo = new nodo();
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
		//bubble_sort();
	}

};
  
void lista_usuarios() {
	nodo *actual = new nodo();
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

void registroTutorial(int x, int y){
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

void insertarPila(int movx, int movy){
	nodoPila* nuevoPila = new nodoPila();
	nuevoPila->x = movx;
	nuevoPila->y = movy;
		
	nuevoPila->siguientePila = primeroPila;
	primeroPila = nuevoPila;
	
}

void verTutorial(){
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

void lista_usuariosordenada() {
	//nodo *actual = new nodo();
	//actual = primero;

/*	if(actual!=NULL){
			nodo *auxiliar = actual->siguiente;
			while(auxiliar!=NULL){
				if(actual->edad > auxiliar->edad){
					int auxiliar2 = auxiliar->edad; 
					auxiliar->edad = actual->edad;
					auxiliar->edad = auxiliar2;
				}
				auxiliar = auxiliar->siguiente;
			}
			actual = actual->siguiente;
			//cout<<"Edad : "<<auxiliar->edad;
			//cout<<"ciclo";
	}else{
		cout << "Lista vacia" << endl;
	}
*/
/*	nodo *p = primero;
    while(p != NULL){
        nodo *j = p ->siguiente;
        while(j != NULL){
            if(p->edad > j->edad){
                int aux = j->edad;
                j->edad = p->edad;
                p->edad = aux;
            }
            j = j->siguiente;
        }
        p = p->siguiente;
    }

	cout<<"Listo"<<endl;
*/
/*	nodo *actual = new nodo();
	nodo *siguiente1;
	//actual = primero;

    //Nodo *actual, *siguiente;
	int n;
    if(actual != NULL)
    {
        actual = primero;
        do
        {
            siguiente1 = actual->siguiente;
            while(siguiente1 != actual)
            {
                if(actual->edad > siguiente1->edad)
                {
                    n = siguiente1->edad;
                    siguiente1->edad = actual->edad;
                    actual->edad = n;
                }
                siguiente1 = siguiente1->siguiente;
            }
            actual = actual->siguiente;
            siguiente1 = actual->siguiente;
        }
        while(siguiente1 != actual);
    }
*/

/*	while(primero!=NULL){
	nodo *otro = primero->siguiente;
		while(otro != NULL){
			if(primero->edad > otro->edad){
				int aux = otro->edad;
				otro->edad = primero->edad;
				otro->edad = aux;
			}
			otro = otro->siguiente;
		}
		primero = primero->siguiente;
	cout<<"Edad: "<<otro->edad<<endl;
	}
*/	
/*	if (primero!=NULL) {
		do {
			cout <<"| "<<"Nick: "<<actual->nombreuser<<" Contra: "<<actual->contra<<" Monedas: "<<actual->monedas<<" Edad: "<<actual->edad <<"| ";
			actual = actual -> siguiente;
		} while(actual!=primero);
	}else{
		std::cout << "Lista vacia" << endl;
	}
*/
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
			eliminarCuenta(nombreuser);
            break;
		case 3:
			cout<<"\nTutorial"<<endl;
			verTutorial();
			break;
                        
        case 4:
			Mostrar_Tienda(monedas);
            break;
		case 5:
            cout<<"Realizar Movimientos"<<endl;
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
	nodo* actual = new nodo();
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

void modificarEdad(int edad){
	nodo* actual = new nodo();
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


void modificarContra(string contra){
	nodo* actual = new nodo();
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

void eliminarCuenta(string userbuscado){
	nodo* actual = new nodo();
	actual = primero;
	nodo* anterior = new nodo();
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

void GraficoListaCDobleEnlace(){
	nodo* actual = new nodo();
	actual = primero;
	int contador = 0;
	int contador2 = 0;
	string nombreNodo, direccion;

	if(actual==NULL){
		cout<<"No se puede graficar porque no existen datos en la lista"<<endl;
	}else{
	string dot = "";
	dot = dot + "digraph G {\n";
	dot = dot + "graph[nodesep=\"0.75\"]\n";
	dot = dot + "labelloc=\"t\"\n";
	dot = dot + "label=\"Lista Circular doblemente enlazada\"\n";
	dot = dot + "node[shape=box]" + "\n";
	if (primero!=NULL) {
		do {
			nombreNodo = "nodo"+to_string(contador);
			dot = dot + nombreNodo + "[label =\"Nick: "  + (actual->nombreuser) + "\nContra: " +(actual->contracifrada) + "\nMonedas: " + to_string(actual->monedas) + "\nEdad: " + to_string(actual->edad) + "\" ""]" + "\n";
			if(actual->siguiente!=primero){
					int auxnum = contador +1;
					int prueba = contador2 -1;
					direccion += nombreNodo + "-> nodo" + std::to_string(auxnum) + "[dir=both];\n";
				}else{
					int auxnum = contador + 1;
					direccion += nombreNodo + ":n" + "-> nodo" + std::to_string(0) + ";\n";
					direccion += "nodo" +std::to_string(0) + ":s" + "->"  + nombreNodo + ";\n";
				}			
			actual = actual -> siguiente;
			contador++;
		} while(actual!=primero);
	}
	dot += nombreNodo + "\n";
	dot +="{rank=same;\n" + direccion + "\n}";
	dot = dot + "\n}";	

	ofstream file;
    file.open("ListaCircularDobleEnlazada.dot");
    file << dot;
    file.close();
    system(("dot -Tpng ListaCircularDobleEnlazada.dot -o  GraficoUsuarios.png"));
	cout<<"\nReporte Usuario Generado\n"<<endl;
	}
}

void GraficoTutorial(){
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

void movimientos(string nombreuser){
	int movx, movy;
	int resp;
	cout<<"Ingrese la coordenada X: ";
	cin>>movx;
	cout<<"Ingrese la coordenada Y: ";
	cin>>movy;
	insertarPila(movx,movy);

	cout<<"\nMovimiento - "<<movx<<","<<movy<<endl;

	cout<<"Desea realizar otro movimiento? "<<endl;
	cout<<"1. SI"<<endl;
	cout<<"2. NO"<<endl;
	cin>>resp;
	do{
		switch (resp)
	{
	case 1:
		cout<<"Ingrese la coordenada X: ";
		cin>>movx;
		cout<<"Ingrese la coordenada Y: ";
		cin>>movy;
		insertarPila(movx,movy);
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

void GraficoMovimientos(string nombreuser,string nombresalida){
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
	dot = dot + "label=\"Lista de Pilas\" + \"\nListado de Jugadas\" + \"\nNick: "+ userlogin + "\nNombre Jugada: " + nombresalida + "\"\n";
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

void vaciarPila(){
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

void desplegarPila(){
	nodoPila* actualPila = new nodoPila();
	actualPila = primeroPila;
	if(primeroPila!=NULL){
		while(actualPila!=NULL){
			cout<< "X:" << actualPila->x<<" Y:"<<actualPila->y<<endl; 
			actualPila = actualPila->siguientePila;
		}
	}else{
		cout << endl << " La Pila se encuentra vacia" << endl << endl;
	}
}

void registro_articulos(string categoria, string nombre, int precio, string id, string srcarticulo){
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

bool CategoriaRepetida(string _categoria){
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

void GraficoListadeListas(){
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

void Mostrar_Tienda(int monedas){
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

void ordenarPrecioASC(){
/*
	NodoArticulos *p = primeroArticulos;
    while(p != NULL){
        NodoArticulos *j = p ->siguienteArtic;
        while(j != NULL){
            if(p->precioArticulo > j->precioArticulo){
                int aux = j->precioArticulo;
                j->precioArticulo = p->precioArticulo;
                p->precioArticulo = aux;
				cout<<"Llega?";
				//cout<<"Salida : "<<p->precioArticulo;
            }
            j = j->siguienteArtic;
        }
        p = p->siguienteArtic;
    }
	cout<<"Listo"<<endl;
*/

	//NodoArticulos *actual = primeroArticulos;


	
	NodoArticulos *nodo1 = new NodoArticulos();
	NodoArticulos *actual, *siguiente;
    int n;
    if(nodo1 != NULL)
    {
        actual = nodo1;
        do
        {
            siguiente = actual->siguienteArtic;
            while(siguiente != nodo1)
            {
                if(actual->precioArticulo > siguiente->precioArticulo)
                {
                    n = siguiente->precioArticulo;
                    siguiente->precioArticulo = actual->precioArticulo;
                    actual->precioArticulo = n;
                }
                siguiente = siguiente->siguienteArtic;
            }
            actual = actual->siguienteArtic;
            siguiente = actual->siguienteArtic;
        }
        while(siguiente != nodo1);
    }
}

void ListaUsuarioASC(nodo *cabeza)
{
	nodo *inicio = cabeza;

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

void ListaUsuarioDESC(nodo *cabeza)
{
	nodo *inicio = cabeza;

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

void intercambioASC(nodo *lado_izq, nodo *lado_der){
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

void intercambioDESC(nodo *lado_izq, nodo *lado_der){
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

void ordenarUsuarioASC(){
	nodo* cabeza = new nodo();
	cabeza = primero;
	int cambiopos;

	nodo* lado_izq;
	nodo* lado_der;
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

void ordenarUsuarioDESC(){
	nodo* cabeza = new nodo();
	cabeza = primero;
	int cambiopos;

	nodo* lado_izq;
	nodo* lado_der;
	if(primero!=NULL){
		do{	
		cambiopos = 0;
		lado_izq = cabeza;
		while(lado_izq->siguiente != primero){

			if (lado_izq->edad < lado_izq->siguiente->edad){
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