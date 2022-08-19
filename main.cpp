#include<iostream>
#include <curses.h>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include "json/json.h"
#include "jsoncpp.cpp"

using namespace std;

void cargamasiva();
void registrousuario();
void login();
void sub_login();
void reportes();
void registro_usuario(string nombreuser, string contra,int monedas, int edad);
void ver_lista_PaU();

struct nodo
{
	string nombreuser, contra;
	int  monedas,edad; 
	nodo *anterior;
	nodo * siguiente;
} *primero=NULL, *ultimo=NULL;

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
	cout<<"Ingrese la ruta del archivo "<<endl;
	//getline(cin,ruta);
	//cin.ignore();
	archivo.open("informacion.json", ios::in);
	//archivo.open(ruta.c_str(), ios::in);

	if(archivo.fail()){
		cout<<" No se pudo abrir el archivo";
		exit(1);
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
			//cout << "\nMonedas: " << usuariosJ[i]["monedas"].asString();
			monedas = usuariosJ[i]["monedas"].asString();
        	//cout << "\nEdad: " << usuariosJ[i]["edad"].asString();
			edad = usuariosJ[i]["edad"].asString();
        	cout << endl;
			std ::string edadi = edad;
			std ::string monedasi = monedas;
			int eddi = std::stoi(edadi);
			int monedi = std::stoi(monedasi);
			registro_usuario(nombreuser,contra,monedi,eddi);
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
		const Json::Value& movimientosJ = obj["movimientos"];

		for(int i = 0; i < movimientosJ.size(); i++){
			cout << "\n X: " << movimientosJ[i]["x"].asString();
			cout << "\n Y: " << movimientosJ[i]["y"].asString();
		}

		break;
		//cout << "\n Ancho: " << tutorialJ["ancho"].asString();
		//cout << "\n Alto: " << tutorialJ["alto"].asString();
		//getline(archivo,texto);
		//archivo.close();

	}

	archivo.close();
	cout<<"Archivo cargado con exito"<<endl;
	return;
	
}

void registrousuario(){
	string nombreuser, contra;
	int monedas, edad;
	cout << "Ingresa el nombre de usuario: "<<endl;
	cin >> nombreuser;
	cout << "Ingresa la contraseña: "<<endl;
	cin >> contra;
	cout << "Ingresa las monedas actual: "<<endl;
	cin >> monedas;
	cout << "Ingresa la edad: "<<endl;
	cin >> edad;
	registro_usuario(nombreuser,contra,monedas, edad);
	cout << "Registro exitoso" << '\n';
	cout<<"\n";
}

void login(){
	nodo *temporal = primero;
	string usu, contrab;
	int posicion = 0;
	bool encontro = false;
	cout<<"Ingrese su nombre de usuario"<<endl;
	cin>> usu;
	cout<<"Ingrese su contraseña"<<endl;
	cin>>contrab;

    while(temporal != NULL){
        if(temporal->nombreuser == usu && temporal->contra == contrab){
			cout <<"Datos correctos"<<endl;
            encontro = true;
			sub_login();
            break;
        }
		if(temporal->nombreuser != usu && temporal->contra != contrab){
			cout <<"Usuario y contraseña incorrecto"<<endl;
            encontro = true;
            break;
		}
		if(temporal->nombreuser == usu && temporal->contra != contrab){
			cout <<"Contraseña incorrecta"<<endl;
            encontro = true;
            break;
		}
		if(temporal->nombreuser != usu && temporal->contra == contrab){
			cout <<"Usuario incorrecto"<<endl;
            encontro = true;
            break;
		}
		else{
            posicion += 1;
        }

        temporal = temporal -> siguiente;
    }
    if(encontro == false){
        cout  << "\n Usuario no encontrado en la Lista \n\n";
    }

}

void reportes(){
	cout<<"Opcion reportes"<<endl;
	ver_lista_PaU();
	cout<<"\n";
}

void registro_usuario(string nombreuser, string contra, int monedas ,int edad){
	nodo *nuevo = new nodo();
 
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

};

void insertar_nodo(){

}


void ver_lista_PaU() {
	nodo *actual = new nodo();
	actual = primero;
	if (primero!=NULL) {
		do {
			cout <<actual->nombreuser<<" "<<actual->contra<<" "<<actual->monedas<<" "<<actual->edad <<"->";
			actual = actual -> siguiente;
		} while(actual!=primero);
	}else{
		std::cout << "Lista vacia" << endl;
	}
 
}

void sub_login(){
	int op1=0;

	do {
		
	cout<<"************ Usuario ***********"<<endl;
	cout<<"* 1. Editar Informacion        *"<<endl;
    cout<<"* 2. Eliminar Cuenta           *"<<endl;
    cout<<"* 3. Ver tutorial              *"<<endl;
    cout<<"* 4. Ver articulos de tienda   *"<<endl;
    cout<<"* 5. Realizar movimientos      *"<<endl;
	cout<<"* 6. Salir al menu principal   *"<<endl;
	cout<<"********************************"<<endl;
	cin>>op1;
	switch(op1){
		case 1:
			cout<<"Editar Informacion"<<endl;
            break;
		case 2:
			cout<<"Eliminar"<<endl;
            break;
		case 3:
			cout<<"Ver tutorial"<<endl;
			break;
                        
        case 4:
            cout<<"Tienda"<<endl;
            break;
		case 5:
            cout<<"Movimientos"<<endl;
            break;
		case 6:
			cout << "\nFin del programa\n";
			break;
		default:
			cout << "\nIngrese una opcion correcta\n\n";
		}	
    }while (op1!=6);
}