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
void sub_login(string nombreuser, string contra,int edad);
void reportes();
void sub_reportes();
void registro_usuario(string nombreuser, string contra,int monedas, int edad);
void lista_usuarios();
void eliminarCuenta(string nombreuser);
void editar_info(string nombreuser, int edad, string contra);
void modificarNick(string nombreuser);
void modificarEdad(int edad);
void modificarContra(string contra);

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
	nodo* actual = new nodo();
	actual = primero;
	bool encontrado = false;
	string nodoBuscado;
	string usuariob, contrab;
	cout << " Ingrese su usuario: "<<endl;
	cin >> usuariob;
	cout << "Ingrese su contraseña: "<<endl;
	cin >> contrab;
	if(primero!=NULL){
		do{
			
			if(actual->nombreuser==usuariob && actual->contra==contrab ){
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
			lista_usuarios();
			break;
		case 2:
			cout<<"Reporte de Articulos"<<endl;
			break;
		case 3:
			cout<<"Reporte de Tutorial"<<endl;
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

void sub_login(string nombreuser, string contra,int edad){
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
			cout << "\nRegresando\n";
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
	char opc;
	cout<<"Desea eliminar su cuenta permanentemente [y/s] : " <<endl; 
	cin>>opc;
	if (opc == 'y'){
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
				cout << "\n La cuenta ha sido eliminada\n\n";
				encontrado = true;	
				//break;			
			}
			anterior = actual;
			actual = actual->siguiente;
		}while(actual!=primero && encontrado != true);		
	}
	}
	if (opc == 's'){
		cout<<"Salida"<<endl;
		return;
	}
	else{
		cout<<"Ingrese una opcion valida"<<endl;
	}
	
}