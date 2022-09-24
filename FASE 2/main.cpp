#include "./glove/glovehttpserver.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
//#include "C++/json/json.h"
//#include "C++/jsoncpp.cpp"
#include "./glove/json.hpp"
#include "C++/jsoncpp.cpp"
#include "C++/ListaCircular.cpp"

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
        //pruebas.lista_usuarios();
        //pruebas.InsertarEnOrden(100);
        //pruebas.registro_usuario("Hola","contra1",100,20,"salida");
       // pruebas.registro_usuario1("Primero");
    }

    void get(GloveHttpRequest &request, GloveHttpResponse &response)
    {
        response << pruebas.getUsers();
        //response << Servidor.
    }

    void post(GloveHttpRequest &request, GloveHttpResponse &response) {

        response.contentType("text/json");
        Json::Reader reader;
        Json::Value obj;
        reader.parse(obj);
        string nombreuser,contra,monedas,edad;
        const Json::Value& usuariosJ = obj["usuarios"]; 
        for (int i = 0; i < usuariosJ.size(); i++){
            //cout << "\nNick: " << usuariosJ[i]["nick"].asString();
            nombreuser = usuariosJ[i]["nick"].asString();
            contra = usuariosJ[i]["password"].asString();
            //string encriptado = SHA256::cifrar(contra);
            //cout<<"El cifrado sha es : "<<encriptado<<endl;
            //cout << "\nMonedas: " << usuariosJ[i]["monedas"].asString();
            monedas = usuariosJ[i]["monedas"].asString();
            //cout << "\nEdad: " << usuariosJ[i]["edad"].asString();
            edad = usuariosJ[i]["edad"].asString();
            std ::string edadi = edad;
            std ::string monedasi = monedas;
            int eddi = std::stoi(edadi);
            int monedi = std::stoi(monedasi);
            pruebas.registro_usuario1(nombreuser,contra,monedasi,edadi);
        }
        
        //auto jsonInput = nlohmann::json::parse(request.getData());
        //auto nick = jsonInput["nick"];
        //auto password = jsonInput["password"];
        //auto monedas = jsonInput["monedas"];
        //auto edad = jsonInput["edad"];

        //pruebas.registro_usuario1(nick,password,monedas,edad);
        //response << pruebas.lista_usuarios();
        //response << pruebas.lista_usuarios();
        response << pruebas.getUsers();
        /*response << "{ "
                 << jsonkv("status", "ok") << ",\n"
                 << jsonkv("Nuevo_usuario", nombreuser) << " }"; */
            //response << pruebas.getUsers();
    }

/*
        response.contentType("text/json");
        if (request.special["Id"].empty())
            response << pruebas.getDatos();
        else
        {
            response << "{ "
                     << jsonkv("status", "ok") << ",\n"
                     << jsonkv("Id_buscado", pruebas.Buscar(atoi(request.special["Id"]))) << " }";
        }
    }

    pruebas.InsertarEnOrden(atoi(request.special["Id"]));
        response << "{ "
                 << jsonkv("status", "ok") << ",\n"
                 << jsonkv("Id_nuevo", request.special["Id"]) << " }";


*/

        //std::string nombreuser;
        //Json::Value obj;
        //const Json::Value& usuariosJ = obj["usuarios"]; 
        //nombreuser = usuariosJ["nick"];
        //pruebas.registro_usuario1(request.special(nombreuser));
        //pruebas.registro_usuario1(nombreuser);
        
        
        //response << "{ "
        //         << jsonkv("status", "ok") << ",\n"
        //         << jsonkv("Usuario_agregado", request.special(nombreuser)) << " }";


    /*    auto jsonInput = nlohmann::json::parse(request.getData());
        auto nick = jsonInput["nick"];
        auto password = jsonInput["password"];
        auto monedas = jsonInput["monedas"];
        auto edad = jsonInput["edad"];
        if (nick.is_null())
            throw GloveApiException(1, "No nick give");
        if (password.is_null())
            throw GloveApiException(1, "No password give");
        if (monedas.is_null())
            throw GloveApiException(1, "No monedas give");
        if (edad.is_null())
            throw GloveApiException(1, "No edad give");

            unsigned id = pruebas.registro_usuario1(nick, password,monedas,edad);
            
        
        
        if (!id)
            throw GloveApiException(1,"Here has a problem");
        auto targetUri = request.getUri().servicehost()+"prueba"+std::to_string(id);
        response << "{"
                << jsonkv("status", "ok") << "\n"
                << jsonkv("target", targetUri) << " }";
    }

*/

    /*
    void post(GloveHttpRequest& request, GloveHttpResponse& response)
	{
		auto jsonInput = nlohmann::json::parse(request.getData());
		auto title = jsonInput["title"];
		auto director = jsonInput["director"];
		auto stars = jsonInput["stars"];
		auto duration = jsonInput["duration"];
		if (title.is_null())
			throw GloveApiException(1, "No title given");
		if (director.is_null())
			throw GloveApiException(1, "No director given");
		if (stars.is_null())
			throw GloveApiException(1, "No stars given");
		if (duration.is_null())
			throw GloveApiException(1, "No duration given");

		unsigned id = films.addFilm(title.get<std::string>(),
																director.get<std::string>(),
																stars.get<std::string>(),
																duration.get<uint32_t>());
		if (!id)
			throw GloveApiException(1, "There was a problem adding film");
		auto targetUri = request.getUri().servicehost()+"/films/"+std::to_string(id);
		response << "{ "
						 << jsonkv("status", "ok") << ",\n"
						 << jsonkv("target", targetUri) << " }";
	}

    void get(GloveHttpRequest &request, GloveHttpResponse& response)
	{
		response.contentType("text/json");
		if (request.special["filmId"].empty())
			response << films.getFilms();
		else
			{
				auto res = films.getFilm(atoi(request.special["filmId"]));
				if (res.empty())
					throw GloveApiException(3, "No films found");
				response << res;
			}
	}

	


    */

private:
    ListaCircular pruebas;
};

int main(int argc, char *argv[])
{
    Servidor cine;

    GloveHttpServer serv(8080, "", 2048);
    serv.compression("gzip, deflate");
    namespace ph = std::placeholders;
    serv.addRest("/Lista/$Nick", 1,
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