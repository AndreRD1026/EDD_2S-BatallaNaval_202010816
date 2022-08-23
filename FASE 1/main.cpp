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

void cargamasiva();
void registrousuario();
void login();
void sub_login(string nombreuser, string contra,int edad);
void reportes();
void sub_reportes();
void registro_usuario(string nombreuser, string contra,int monedas, int edad, string contracifrada);
void registro_usuarioJ(string nombreuser, string contra,int monedas, int edad, string contracifrada);
void registroTutorial(int x, int y);
void verTutorial();
void lista_usuarios();
void lista_usuariosordenada();
void eliminarCuenta(string nombreuser);
void editar_info(string nombreuser, int edad, string contra);
void modificarNick(string nombreuser);
void modificarEdad(int edad);
void modificarContra(string contra);
void GenerarGrafo();
void GraficoListaCDobleEnlace();
void GraficoTutorial();
void graficaPrueba();

struct nodo{
	string nombreuser, contra, contracifrada;
	int  monedas,edad; 
	nodo *anterior;
	nodo * siguiente;
} *primero=NULL, *ultimo=NULL;


struct nodoCola{
	int  x,y; 
	nodoCola* siguienteCola;
} *primeroCola, *ultimoCola;



int main(int argc, char** argv) {
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
		}	
    }while (op!=5);
}

void cargamasiva(){
	ifstream archivo;
	string ruta;
	string texto;
	string nombreuser,contra,monedas,edad;
	string alt, anch, x1, y1;
	cout<<"Ingrese la ruta del archivo "<<endl;
	cin.ignore();
	getline(cin,ruta);
	archivo.open("informacion.json", ios::in);
	//archivo.open(ruta.c_str(), ios::in);
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
        	cout << "\nID: " << articulosJ[i]["id"].asString();
        	cout << "\nCategoria: " << articulosJ[i]["categoria"].asString();
			cout << "\nPrecio: " << articulosJ[i]["precio"].asString();
        	cout << "\nNombre: " << articulosJ[i]["nombre"].asString();
			cout << "\nSRC: " << articulosJ[i]["src"].asString();
        	cout << endl;
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
				cout<<" Datos correctos"<<endl;
				sub_login(actual->nombreuser, actual->contra,actual-> edad);
			}
			
			actual = actual->siguiente;
		}while(actual!=primero && encontrado != true);
		
		if(!encontrado){
			cout << "\n Usuario o contraseña incorrectos\n\n";
		}
		
	}else{
		cout << "\n No existe el usuario en la lista\n\n";
	}
}

void reportes(){
	int opreport;
	cout<<"\n";
	cout<<"Opcion reportes"<<endl;
	cout<<"1. Estructuras Utilizadas"<<endl;
	cout<<"2. Listado de usuarios ordenados por edad"<<endl;
	cout<<"3. Listado de articulos ordenados por precio"<<endl;
	cin >> opreport;

	switch (opreport)
	{
	case 1:
	int opcestruct;
		cout<<"1. Lista Usuarios"<<endl;
		cout<<"2. Lista Articulos"<<endl;
		cout<<"3. Tutorial"<<endl;
		cout<<"4. Listado de Jugadas"<<endl;
		cin>> opcestruct;

		switch (opcestruct){
		case 1:
			//lista_usuarios();
			cout<<"Grafica generada\n"<<endl;
			GraficoListaCDobleEnlace();
			break;
		case 2:
			cout<<"Reporte de Articulos"<<endl;
			break;
		case 3:
			cout<<"Reporte de Tutorial"<<endl;
			GraficoTutorial();
			break;
		case 4:
			cout<<"Reporte de Jugadas"<<endl;
			break;	
		
		default:
			cout<<"Reporte error"<<endl;
			break;
		}
		break;
	
	case 2:
	int ordenl;
		cout<<"1. Orden Ascendente"<<endl;
		cout<<"2. Orden Descendente"<<endl;
		cin>> ordenl;

		switch (ordenl)
		{
		case 1:
			cout<<"lista usuarios de forma ascendente"<<endl;
			//lista_usuariosordenada();
			graficaPrueba();
			//show();
			break;
		
		case 2:
			cout<<"lista usuarios de forma descendente"<<endl;
			break;
	
		default:
			cout<<"\n";
			break;
		}
	
	case 3:
	int ordenp;
		cout<<"1. Orden Ascendente"<<endl;
		cout<<"2. Orden Descendente"<<endl;
		cin>> ordenp;

		switch (ordenp)
		{
		case 1:
			cout<<"lista articulos de forma precio ascendente"<<endl;
			break;
		
		case 2:
			cout<<"lista usuarios de forma precio descendente"<<endl;
			break;
	
		default:
			cout<<"\n";
			break;
		}
	
	default:
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
	}

};

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
			//cout << endl << "Ancho: " << actualCola->ancho << " Alto: "<<actualCola->alto;
			
			cout<< "(" << actualCola->x<<","<<actualCola->y<< ")"<<"->";
			actualCola = actualCola->siguienteCola;
		}
		cout<<"\n";
	}else{
		cout << endl << " La cola se encuentra Vacia " << endl << endl;
	}
}

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

void sub_login(string nombreuser, string contra,int edad){
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
			cout<<"Contraseña -> "<< contra <<endl;
			cout<<"Edad -> "<< edad <<endl;
			cout<<"\n";
			editar_info(nombreuser, edad, contra);
            break;
		case 2:
			eliminarCuenta(nombreuser);
			//return;
            break;
		case 3:
			cout<<"\nTutorial"<<endl;
			verTutorial();
			break;
                        
        case 4:
            cout<<"Tienda"<<endl;
            break;
		case 5:
            cout<<"Movimientos"<<endl;
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


/* 
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
*/


void modificarNick(string userb){
	nodo* actual = new nodo();
	string nuevouser;
	actual = primero;
	bool encontrado = false;
	//if(primero!=NULL){
		cout<<"\nIngrese el nuevo Nick: ";
		cin >> nuevouser;
		do{
			//if(actual->nombreuser==userb){
				if(actual->nombreuser==nuevouser){
					cout<<"Nick repetido\n";
					encontrado=true;
					break;
				}
				//cout << "\n Ingrese el nuevo Nick: ";
				//cin >> actual->nombreuser;
				//cout << "\n Para efectuar los cambios debe cerrar sesión e iniciar con el nuevo usuario\n\n";
				//encontrado = true;				
			//}
			actual = actual->siguiente;
		}while(actual!=primero && encontrado != true);

	//actual->nombreuser = userb;
	//userb = nuevouser;
	//actual->nombreuser = nuevouser;

	//}

/*		do{
			
			if(actual->nombreuser==nuevouser){
				cout<<"El nick ingresado ya existe\n";
				encontrado = true;
				return;
			}
			if(actual->nombreuser!=nuevouser){
				//cout<<"Llega\n";
				actual->nombreuser = nuevouser;
				encontrado = false;
			}
		actual = actual->siguiente;	
		}while(actual!=primero && encontrado != true);	
		
	} */
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
	bool encontrado = false;
	if(primero!=NULL){
		do{
			if(actual->contra==contra){
				cout << "\n Ingrese la nueva Contraseña: ";
				cin >> actual->contra;
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
	return;
	}
	if (opc == "s"){
		cout<<"Salida"<<endl;
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
	string dot = "";
	dot = dot + "digraph G {\n";
	dot = dot + "graph[nodesep=\"0.75\"]\n";
	dot = dot + "labelloc=\"t\"\n";
	dot = dot + "label=\"Lista Circular doblemente enlazada\"\n";
	dot = dot + "node[shape=box]" + "\n";
	//dot = dot + "nodo1[label =\"Nick: "  + (actual->nombreuser) + "\nContra: " +(actual->contra) + "\nMonedas: " + to_string(actual->monedas) + "\nEdad: " + to_string(actual->edad) + "\" ""]"; Este es el bueno
	if (primero!=NULL) {
		do {
			nombreNodo = "nodo"+to_string(contador);
			dot = dot + nombreNodo + "[label =\"Nick: "  + (actual->nombreuser) + "\nContra: " +(actual->contra) + "\nMonedas: " + to_string(actual->monedas) + "\nEdad: " + to_string(actual->edad) + "\" ""]" + "\n";
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

    //------->generar png
    system(("dot -Tpng ListaCircularDobleEnlazada.dot -o  ListaCircularDobleEnlazada.png"));

    //------>abrir archivo
    //system(("ListaCircularDobleEnlazada.png"));
}


void GraficoTutorial(){
	nodoCola* actualCola = new nodoCola();
	actualCola = primeroCola->siguienteCola;
	int contador1 = 0;
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
					direccion1 += nombreNodo1 + "-> nodo" + std::to_string(auxnum1) + "[dir=right];\n";
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

    //------->generar png
    system(("dot -Tpng ColadeMovimientos.dot -o  ColadeMovimientos.png"));

    //------>abrir archivo
    //system(("ListaCircularDobleEnlazada.png"));
}


void GenerarGrafo() {
	nodo* actual = new nodo();
	actual = primero;
    string dot = "";
    dot = dot + "digraph G {\n";
    dot = dot + "label=\"ListaDeImagenes\";\n";
    dot = dot + "node [shape=box];\n";
	//cout <<"| "<<"Nick: "<<actual->nombreuser<<" Contra: "<<actual->contra<<" Monedas: "<<actual->monedas<<" Edad: "<<actual->edad <<"| ";
	//actual = actual -> siguiente;


    dot = dot + "//agregar nodos\n";
    while (actual != NULL) {
        dot = dot + "N" + to_string(actual->monedas) + "[label=\"" + to_string(actual->edad) + "\"];\n";
        actual = actual->siguiente;
    }
    dot = dot + "//Enlazar imagenes\n";
    dot = dot + "{rank=same;\n";
    actual = primero;
    while (actual != NULL) {

        dot = dot + "N" + to_string(actual->edad);
        if (actual->siguiente != NULL) {
            dot = dot + "->";
        }
        actual = actual->siguiente;
    }

    dot = dot + "}\n";
    dot = dot + "}\n";

    cout << dot;
    
     //------->escribir archivo
    ofstream file;
    file.open("Pruebas.dot");
    file << dot;
    file.close();

    //------->generar png
    system(("dot -Tpng Pruebas.dot -o  Pruebas.png"));

    //------>abrir archivo
    system(("Pruebas.png"));
    
}

void graficaPrueba(){

	nodo* actual = new nodo();
	actual = primero;
	int auxi,auxi2;

	if(primero!=NULL){
		do{
			nodo* aux = actual->siguiente;
			while(aux!=NULL){
				if(actual->edad > aux->edad){
					auxi = aux->edad;
					aux->edad = actual->edad;
					actual->edad = auxi;
					cout<<"Edad1: " <<auxi<<endl;
				}else{
					auxi2 = aux->edad;
					aux->edad = actual->edad;
					aux = actual->siguiente;
					actual->edad = auxi2;
					cout<<"Edad2: "<<auxi2<<endl;
					//break;
				}
					
			aux = aux->siguiente;
		actual = actual->siguiente;
		//cout<<"Edad: "<<aux->siguiente<<endl;
					//break;
					
			}
			//aux = aux->siguiente;
		}while(actual->siguiente!=primero);
	}

/*	while(p != NULL){
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
*/
}