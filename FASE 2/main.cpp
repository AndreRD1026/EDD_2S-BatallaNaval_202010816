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


int contadorusuarios = 0;

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
       //pruebas = Servidor
        //pruebas.registro_usuario1("sale?","aaaa",10,21);
    }

    void get(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        string rut;
        response.contentType("text/json");
        rut = request.special["Ruta"];
        if (rut.empty())
            response << pruebas.getUsers();
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
            pruebas.registro_usuario1(contadorusuarios,nombreuser, encriptado, monedi, eddi);
            //Listausuarios.registro_usuario(nombreuser,contra,monedi,eddi,encriptado);
            //pruebas.insertar(contadorusuarios,nombreuser);
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
            //ListaArt.registro_articulos(categoriarticulo,nombrearticulo,precioarticulo,idarticuloo,srcarticulo);
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
        //ListaCola.registroTutorial(x,y);
        //cout<<"\nMovimientos: ";
        const Json::Value& movimientosJ = tutorialJ["movimientos"];
        for(int i = 0; i < movimientosJ.size(); i++){
            //cout << "\nX: " << movimientosJ[i]["x"].asString();
            x1 = movimientosJ[i]["x"].asString();
            //cout << " Y: " << movimientosJ[i]["y"].asString();
            y1 = movimientosJ[i]["y"].asString();
        int x = std::stoi(x1);
        int y = std::stoi(y1);
        //ListaCola.registroTutorial(x,y);
        }
        cout<<"\n";
        cout<<"\nArchivo cargado con exito\n"<<endl;
        break;
    }
    archivo.close();
    //return;

    response << "{ "
                 << jsonkv("status", "ok ha sido enviado") << ",\n"
                " }";


    return;
    }

private:
    ListaCircular pruebas;
};

int main(int argc, char *argv[])
{
    Servidor cine;

    GloveHttpServer serv(8080, "", 2048);
    serv.compression("gzip, deflate");
    namespace ph = std::placeholders;
    serv.addRest("/Carga/$Ruta", 1,
                 GloveHttpServer::jsonApiErrorCall,
                 std::bind(&Servidor::get, &cine, ph::_1, ph::_2),
                 std::bind(&Servidor::post, &cine, ph::_1, ph::_2));
    std::cout << "Servidor en Ejecucion" << std::endl;
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "TEST" << std::endl;
}