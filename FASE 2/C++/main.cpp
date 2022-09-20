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
#include "ListaCircular.h"
//#include "ListaCircular.cpp"
#include <cstdlib>

using namespace std;


void MenuPrincipal();
void cargamasiva();
void registrousuario();
//void login();
//void sub_login(string nombreuser, string contra,int edad, int monedas);
//void reportes();
//void sub_reportes();
//void registro_usuario(string nombreuser, string contra,int monedas, int edad, string contracifrada);
//void registro_usuarioJ(string nombreuser, string contra,int monedas, int edad, string contracifrada);
//void registro_articulos(string categoriaarticulo, string nombrearticulo, int precioarticulo, string idarticulo, string srcarticulo);
//void registroTutorial(int x, int y);
//void insertarPila(int movx, int movy);
//void verTutorial();
//void lista_usuarios();
//void lista_usuariosordenada();
//void eliminarCuenta(string nombreuser);
//void editar_info(string nombreuser, int edad, string contra);
//void modificarNick(string nombreuser);
//void modificarEdad(int edad);
//void modificarContra(string contra);
//void GraficoListaCDobleEnlace();
//void GraficoTutorial();
//void movimientos(string nombreuser);
//void desplegarPila();
//void GraficoMovimientos(string nombreuser, string salida);
//void Mostrar_Tienda(int monedas);
//void ordenarPrecioASC();
//void ordenarPrecioDESC();
//void GraficoListadeListas();
//void vaciarPila();
//void SumaPuntosJugada(string nombreuser);
//void ordenarUsuarioASC();
//void ordenarUsuarioDESC();

//std:: string userlogin;
//std:: string nombrejugada;


/*struct nodo{
	string nombreuser, contra, contracifrada;
	int  monedas,edad; 
	nodo *anterior;
	nodo *siguiente;
} *primero=NULL, *ultimo=NULL; */

//ListaCircular Listausuarios;

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
			registrousuario();
            break;
		case 3:
			cout<<"\n";
			break;
        case 4:
			cout<<"\n";
            //reportes();
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
	ListaCircular Listausuarios;
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
	//registro_usuario(nombreuser,contra,monedas, edad,encriptado);
	//probando.registro_usuario(nombreuser,contra,monedas, edad,encriptado);
	Listausuarios.registro_usuario(nombreuser,contra,monedas,edad,encriptado);
	cout<<"\n";
}


void cargamasiva(){
	ListaCircular Listausuarios;
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
            Listausuarios.registro_usuarioJ(nombreuser,contra,monedi,eddi,encriptado);
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
        //registroTutorial(x,y);
        //cout<<"\nMovimientos: ";
        const Json::Value& movimientosJ = tutorialJ["movimientos"];
        for(int i = 0; i < movimientosJ.size(); i++){
            //cout << "\nX: " << movimientosJ[i]["x"].asString();
            x1 = movimientosJ[i]["x"].asString();
            //cout << " Y: " << movimientosJ[i]["y"].asString();
            y1 = movimientosJ[i]["y"].asString();
        int x = std::stoi(x1);
        int y = std::stoi(y1);
        //registroTutorial(x,y);
        }
        cout<<"\n";
        cout<<"\nArchivo cargado con exito\n"<<endl;
        break;
    }
    archivo.close();
    return;
}
