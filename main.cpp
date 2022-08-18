#include<iostream>
#include <curses.h>
#include<fstream>
#include "json/json.h"
#include "jsoncpp.cpp"

using namespace std;

void cargamasiva();
void registrousuario();
void login();
void reportes();

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
	string ruta;
	string texto;
	cout<<"Ingrese la ruta del archivo"<<endl;
	//cin>>ruta;
	//cout<<"Es : "<<ruta<<endl;
	ifstream archivo;
	archivo.open("informacion.json", ios::in);

	if(archivo.fail()){
		cout<<" No se pudo abrir el archivo";
		exit(1);
	}

	while (!archivo.eof())
	{
		getline(archivo,texto);
		cout<<texto<<endl;
	}

	archivo.close();
	
}

void registrousuario(){
	cout<<"Opcion registro usuarios"<<endl;
}

void login(){
	cout<<"Opcion login"<<endl;
}

void reportes(){
	cout<<"Opcion reportes"<<endl;
}