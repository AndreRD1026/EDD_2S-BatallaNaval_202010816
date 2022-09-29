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


int contadorusuarios = 0;

ListaCircular ListaUsuarios;
ListaArticulos ListaArt;
ListaTutorial ListTutorial;
ArbolB Arbol;



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

    ListaUsuarios.registro_usuario(contadorusuarios,usuario,encriptado,0,50);
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
        string nombreuser,contra,monedas,edad;
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
            ListaUsuarios.registro_usuarioJ(contadorusuarios,nombreuser, encriptado, monedi, eddi);
            Arbol.insertar(contadorusuarios,nombreuser);
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
    //Arbol.Grafo();
    //return;

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


    /* 
    void post(GloveHttpRequest &request, GloveHttpResponse &response){
        string nombreuser, contra;
        int monedas, edad;
        nombreuser = request.special["nick"];
        contra = request.special["contra"];
        edad = atoi(request.special["edad"]);
        monedas = 0;
        string encriptado = SHA256::cifrar(contra);
        //ListaUsuarios.Comprobar(nombreuser);
        //ListaUsuarios.registro_usuario(contadorusuarios,nombreuser,encriptado,monedas,edad);
        //Arbol.insertar(contadorusuarios,nombreuser);
        //contadorusuarios++;
        response << "{ "
            << jsonkv("status", "ok ha sido registrado") << ",\n"
            " }"; 

        response << ListaUsuarios.registro_usuario1(contadorusuarios,nombreuser,encriptado,monedas,edad);
        contadorusuarios++;
        }
    */
    
    void post(GloveHttpRequest &request, GloveHttpResponse &response){
        string nombreuser, contra;
        int monedas, edad;
        nombreuser = request.special["nick"];
        contra = request.special["contra"];
        edad = atoi(request.special["edad"]);
        monedas = 0;
        string encriptado = SHA256::cifrar(contra);
        ListaUsuarios.Comprobar(nombreuser);
        ListaUsuarios.registro_usuario(contadorusuarios,nombreuser,encriptado,monedas,edad);
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
        string user;
        response.contentType("text/json");
        user = request.special["Usuario"];
        //contr = request.special["Contra"];
        //string cifrada = SHA256::cifrar(contr);
        response << ListaUsuarios.Buscar(user);
        
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
        //string user;
        //response.contentType("text/json");
        Arbol.Grafo();
        response << "{ "
                 << jsonkv("status", "ok ha sido enviado") << ",\n"
                " }";
        return;
        //user = request.special[""];
        //contr = request.special["Contra"];
        //string cifrada = SHA256::cifrar(contr);
        //response << ListaUsuarios.Buscar(user);
        
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


int main(int argc, char *argv[])
{
    Servidor cine;
    Servidor2 cine2;
    Servidor3 registroUser;
    Servidor4 mandarDatos;
    Servidor5 usuarios;
    Servidor6 Articulos;

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
    serv.addRest("/Log/$Usuario", 1,
                 GloveHttpServer::jsonApiErrorCall,
                 std::bind(&Servidor4::get, &mandarDatos, ph::_1, ph::_2));
    serv.addRest("/Usuarios/", 1,
                 GloveHttpServer::jsonApiErrorCall,
                 std::bind(&Servidor5::post, &usuarios, ph::_1, ph::_2));
    serv.addRest("/Articulos/", 1,
                 GloveHttpServer::jsonApiErrorCall,
                 std::bind(&Servidor6::post, &Articulos, ph::_1, ph::_2));
    
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "TEST" << std::endl;
}