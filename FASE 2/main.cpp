#include "./glove/glovehttpserver.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include<fstream>
#include "./glove/json.hpp"
#include "C++/jsoncpp.cpp"
#include "C++/ListaCircular.cpp"
#include "C++/ListaArticulos.cpp"
#include "C++/ListaTutorial.cpp"
#include "C++/ArbolB.cpp"
#include "C++/ListaPila.cpp"


int contadorusuarios = 0;
ListaCircular ListaUsuarios;
ListaArticulos ListaArt;
ListaTutorial ListTutorial;
ArbolB Arbol;
ListaPila Movimientos;


int atoi(std::string s)
{
    try
    {
        return std::stod(s);
    }
    catch (std::exception &e)
    {
        return 0;
    }
}

static std::string jsonkv(std::string k, std::string v)
{
    /* "k": "v" */
    return "\"" + k + "\": \"" + v + "\"";
}

class Servidor
{
public:
    Servidor()
    {
    string usuario = "EDD";
    string contra = "edd123";
    string encriptado = SHA256::cifrar(contra);
    ///cout<<"encripatdo: "<<encriptado<<"\n";

    ListaUsuarios.registro_usuario(contadorusuarios,usuario,encriptado,0,50,contra);
    Arbol.insertar(contadorusuarios,usuario);
    contadorusuarios++;
    }

    void get(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        string rut;
        response.contentType("text/json");
        rut = request.special["Ruta"];
        if (rut.empty())
            response << ListaUsuarios.getUsers();
                    
        else
        {
            response << "{ "
                << jsonkv("status", "ok tengo el get") << ",\n"
                " }";
        }
        
    }

    void post(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        ifstream archivo;
        string ruta;
        string pruebaa;
        string texto;
        string iduser,nombreuser,contra,monedas,edad;
        string idarticuloo, categoriarticulo,precioarticuloo,nombrearticulo,srcarticulo;
        string alt, anch, x1, y1;
        ruta = request.special["Ruta"];
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
            iduser = usuariosJ[i]["id"].asString();
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
            std ::string idi = iduser;
            std ::string edadi = edad;
            std ::string monedasi = monedas;
            int iddi = std::stoi(idi);
            int eddi = std::stoi(edadi);
            int monedi = std::stoi(monedasi);
            ListaUsuarios.registro_usuarioJ(iddi,nombreuser, encriptado, monedi, eddi, contra);
        }

        const Json::Value& articulosJ = obj["articulos"]; 
        for (int i = 0; i < articulosJ.size(); i++){
            //cout << "\nID: " << articulosJ[i]["id"].asString();
            idarticuloo = articulosJ[i]["id"].asString();
            //cout << "\nCategoria: " << articulosJ[i]["categoria"].asString();
            categoriarticulo = articulosJ[i]["categoria"].asString();
            //cout << "\nPrecio: " << articulosJ[i]["precio"].asString();
            precioarticuloo = articulosJ[i]["precio"].asString();
            //cout << "\nNombre: " << articulosJ[i]["nombre"].asString();
            nombrearticulo = articulosJ[i]["nombre"].asString();
            //cout << "\nSRC: " << articulosJ[i]["src"].asString();
            srcarticulo = articulosJ[i]["src"].asString();
            //std ::string iarticulo = idarticuloo;
            std ::string precioarticul = precioarticuloo;
            int precioarticulo = std::stoi(precioarticul);
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
        ListTutorial.registroTutorial(x,y);
        //cout<<"\nMovimientos: ";
        const Json::Value& movimientosJ = tutorialJ["movimientos"];
        for(int i = 0; i < movimientosJ.size(); i++){
            //cout << "\nX: " << movimientosJ[i]["x"].asString();
            x1 = movimientosJ[i]["x"].asString();
            //cout << " Y: " << movimientosJ[i]["y"].asString();
            y1 = movimientosJ[i]["y"].asString();
        int x = std::stoi(x1);
        int y = std::stoi(y1);
        ListTutorial.registroTutorial(x,y);
        }
        cout<<"\n";
        cout<<"\nArchivo cargado con exito\n"<<endl;
        break;
    }
    archivo.close();

    response << "{ "
                << jsonkv("status", "ok ha sido enviado") << ",\n"
                " }";
    return;
    }
};


class Servidor2{
    public:
    Servidor2()
    {
       //ListaUsuarios = Servidor
    
    }

    void get(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        string user, contr;
        response.contentType("text/json");
        user = request.special["Usuario"];
        contr = request.special["Contra"];
        string cifrada = SHA256::cifrar(contr);
        response << ListaUsuarios.verificarLog(user,cifrada);
        
    }
};

class Servidor3{
    public:
    Servidor3()
    {
       //ListaUsuarios = Servidor
    
    }
    
    void post(GloveHttpRequest &request, GloveHttpResponse &response){
        string nombreuser, contra;
        int monedas, edad;
        nombreuser = request.special["nick"];
        contra = request.special["contra"];
        edad = atoi(request.special["edad"]);
        monedas = 0;
        string encriptado = SHA256::cifrar(contra);
        ListaUsuarios.Comprobar(nombreuser);
        ListaUsuarios.registro_usuario(contadorusuarios,nombreuser,encriptado,monedas,edad, contra);
        Arbol.insertar(contadorusuarios,nombreuser);
        contadorusuarios++;
        response << "{ "
            << jsonkv("status", "ok ha sido registrado") << ",\n"
            " }";
    }
    
};

class Servidor4{

    public:
    Servidor4()
    {
       //ListaUsuarios = Servidor
    
    }

    void get(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        string user, cont;
        response.contentType("text/json");
        user = request.special["Usuario"];
        cont = request.special["Contra"];
        //contr = request.special["Contra"];
        //string cifrada = SHA256::cifrar(contr);
        response << ListaUsuarios.Buscar1(user);
        
    }

};

class Servidor5{
    public:
    Servidor5()
    {
       //ListaUsuarios = Servidor
    
    }

    void post(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        Arbol.vaciar();
        nodoUsuarios *actual = new nodoUsuarios();
	    actual = ListaUsuarios.primero;

	    cout << "  "<< left << setw( 15 ) << "NICK"<< " "<< left << setw( 12 ) << "Monedas"<< "   "<< left << setw( 12 ) << "Edad"<< " "<< left << setw( 15 ) << "Contra"<< " "<<endl;	
	    while(actual)
	    {
		cout << "  "<< left << setw( 15 ) <<actual->nombreuser<< " "<< left << setw( 12 ) << actual->monedas<< "   "<< left << setw( 12 ) << actual->edad<< " "<< left << setw( 12 ) <<actual->contracifrada<< " "<<endl;
        Arbol.insertar(actual->id,actual->nombreuser);
		actual = actual->siguiente;
        
		if(actual == ListaUsuarios.primero){
			break;
		    }
	    }
	    cout<<"\n\n";

        Arbol.Grafo();        
        
        response << "{ "
                << jsonkv("status", "ok ha sido enviado") << ",\n"
                " }";
        return;

        
    }

};

class Servidor6{
    public:
    Servidor6()
    {
       //ListaUsuarios = Servidor
    
    }

    void post(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        ListaArt.GraficoListadeListas();
        response << "{ "
                << jsonkv("status", "ok ha sido enviado") << ",\n"
                " }";
        return;
    }

};



class Servidor7{
    public:
    Servidor7()
    {
       //ListaUsuarios = Servidor
    
    }

    void post(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        ListaUsuarios.ordenarUsuarioASC();
        response << "{ "
                 << jsonkv("status", "ok ha sido enviado") << ",\n"
                " }";
        return;

        
    }

};


class Servidor8{
    public:
    Servidor8()
    {
       //ListaUsuarios = Servidor
    
    }

    void post(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        ListaUsuarios.ordenarUsuarioDESC();
        response << "{ "
                << jsonkv("status", "ok ha sido enviado") << ",\n"
                " }";
        return;

    }

};

class Servidor9{
    public:
    Servidor9(){

    }

    void get(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        string user, contra, edad;
        response.contentType("text/json");
        user = request.special["nick"];
        contra = request.special["contra"];
        edad = atoi(request.special["edad"]);
        response << ListaUsuarios.Comprobar(user);
        
    }
};


class Servidor10{
    public:
    Servidor10(){

    }

    void get(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        string user, contra, edad;
        response.contentType("text/json");
        user = request.special["nick"];
        response << ListaUsuarios.BuscarUser(user);
        
    }
};

class Servidor11{
    public:
    Servidor11(){
        
    }

        void get(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        string user, idd;
        response.contentType("text/json");
        user = request.special["nick"];
        idd = request.special["id"];
        ListaUsuarios.eliminarCuenta(user);
        Arbol.eliminar(atoi(idd));
        response << "{ "
            << jsonkv("status", "ok ha sido eliminado") << ",\n"
            " }";
        
    }
};

class Servidor12{
    public:
    Servidor12(){
        
    }

        void get(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        string user,nuevouser, contranueva, edadnueva,idd;
        response.contentType("text/json");
        user = request.special["nick"];
        nuevouser = request.special["nuevoN"];
        contranueva = request.special["nuevoC"];
        string cifrado = SHA256::cifrar(contranueva);
        edadnueva = request.special["nuevoE"];
        idd = request.special["Id"];
        ListaUsuarios.modificarUsuario(user,nuevouser,contranueva,atoi(edadnueva),cifrado);
        //Arbol.modificar(atoi(idd),nuevouser);
        response << "{ "
            << jsonkv("status", "ok ha sido modificado") << ",\n"
            " }";
        
    }
};

class Servidor13{
    public:
    Servidor13(){

    }

        void get(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        response << ListaArt.getArticulos();        
    }
};


class Servidor14{
    public:
    Servidor14()
    {
       //ListaUsuarios = Servidor
    
    }
    
    void post(GloveHttpRequest &request, GloveHttpResponse &response){
        string valX, valY;
        valX = request.special["X"];
        valY = request.special["Y"];
        Movimientos.insertarPila(atoi(valX),atoi(valY));
        response << "{ "
            << jsonkv("status", "ok ha sido registrado") << ",\n"
            " }";
    }
    
};


class Servidor15{
    public:
    Servidor15(){

    }
        /*
        void get(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        response << ListTutorial.getTutorial();        
    }
        */
        

        void post(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        ListTutorial.GraficoTutorial();
        response << "{ "
                << jsonkv("status", "ok ha sido enviado") << ",\n"
                " }";
        return;
    }
};

int main(int argc, char *argv[])
{
    Servidor cine;
    Servidor2 cine2;
    Servidor3 registroUser;
    Servidor4 mandarDatos;
    Servidor5 usuarios;
    Servidor6 Articulos;
    Servidor7 UsuariosAsc;
    Servidor8 UsuariosDesc;
    Servidor9 Verificador;
    Servidor10 Eliminar;
    Servidor11 Eliminado;
    Servidor12 Modificando;
    Servidor13 Tienda;
    Servidor14 Pila;
    Servidor15 Tuto;

    GloveHttpServer serv(8080, "", 2048);
    serv.compression("gzip, deflate");
    namespace ph = std::placeholders;
    serv.addRest("/Carga/$Ruta", 1,
                GloveHttpServer::jsonApiErrorCall,
                std::bind(&Servidor::get, &cine, ph::_1, ph::_2),
                std::bind(&Servidor::post, &cine, ph::_1, ph::_2));
                std::cout << "Servidor en Ejecucion :D" << std::endl;
    serv.addRest("/Login/$Usuario/$Contra", 1,
                GloveHttpServer::jsonApiErrorCall,
                std::bind(&Servidor2::get, &cine2, ph::_1, ph::_2));
    serv.addRest("/Registro/$nick/$contra/$edad", 1,
                GloveHttpServer::jsonApiErrorCall,
                std::bind(&Servidor3::post, &registroUser, ph::_1, ph::_2));
    serv.addRest("/Log/$Usuario/$Contra", 1,
                GloveHttpServer::jsonApiErrorCall,
                std::bind(&Servidor4::get, &mandarDatos, ph::_1, ph::_2));
    serv.addRest("/Usuarios/", 1,
                GloveHttpServer::jsonApiErrorCall,
                std::bind(&Servidor5::post, &usuarios, ph::_1, ph::_2));
    serv.addRest("/Articulos/", 1,
                GloveHttpServer::jsonApiErrorCall,
                std::bind(&Servidor6::post, &Articulos, ph::_1, ph::_2));
    serv.addRest("/UsuariosASC/", 1,
                GloveHttpServer::jsonApiErrorCall,
                std::bind(&Servidor7::post, &UsuariosAsc, ph::_1, ph::_2));
    serv.addRest("/UsuariosDESC/", 1,
                GloveHttpServer::jsonApiErrorCall,
                std::bind(&Servidor8::post, &UsuariosDesc, ph::_1, ph::_2));
    serv.addRest("/Verificar/$nick/$contra/$edad", 1,
                GloveHttpServer::jsonApiErrorCall,
                std::bind(&Servidor9::get, &Verificador, ph::_1, ph::_2));
    serv.addRest("/Eliminar/$nick", 1,
                GloveHttpServer::jsonApiErrorCall,
                std::bind(&Servidor10::get, &Eliminar, ph::_1, ph::_2));
    serv.addRest("/Eliminando/$nick/$id", 1,
                GloveHttpServer::jsonApiErrorCall,
                std::bind(&Servidor11::get, &Eliminado, ph::_1, ph::_2));
    serv.addRest("/Modificando/$nick/$nuevoN/$nuevoC/$nuevoE/$Id", 1,
                GloveHttpServer::jsonApiErrorCall,
                std::bind(&Servidor12::get, &Modificando, ph::_1, ph::_2));
    serv.addRest("/Tienda/", 1,
                GloveHttpServer::jsonApiErrorCall,
                std::bind(&Servidor13::get, &Tienda, ph::_1, ph::_2));
    serv.addRest("/Movimiento/$X/$Y", 1,
                GloveHttpServer::jsonApiErrorCall,
                std::bind(&Servidor14::post, &Pila, ph::_1, ph::_2));
    serv.addRest("/Tutorial/", 1,
                GloveHttpServer::jsonApiErrorCall,
                std::bind(&Servidor15::post, &Tuto, ph::_1, ph::_2));
    
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "TEST" << std::endl;
}