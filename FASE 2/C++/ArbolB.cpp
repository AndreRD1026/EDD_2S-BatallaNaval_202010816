#include "ArbolB.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

void ArbolB::insertar(int id, string nombreuser) {
    NodoB* nodo = new NodoB(id, nombreuser);
    if (raiz == NULL) {
        raiz = nodo;
    } else {
        pair < NodoB*, pair<bool, bool>> ret = insertarCrearRama(nodo, raiz);
        NodoB* obj = ret.first;
        if ((ret.second.first or ret.second.second) and obj != NULL) {//si se divide la rama o se inserta al inicio, la raiz cambia
            cout << "se cambia de rama principal ID:" << obj->id << " nick: " << obj->nombreuser << "\n";
            raiz = obj;
        }
    }
}

void ArbolB::vaciar(){
    NodoB* prueba;
    prueba = raiz;
    raiz = NULL;
}

/**
 * Metodo recorre el arbol e inserta los valores nuevos, verifica si es necesario dividir ramas
 *
 * @param NodoB* nodo es el nodo a insertar
 * @param NodoB* rama es la rama en la cual se inicia la busqueda de la posicion donde insertarlo
 * 
 * @retun retorna un listado de elementos que nos permiten identificar lo siguiente:
 * 
 * NodoB*: nodo inicial de la rama donde se inserto un elemento
 * 
 * bool: true or false indicando si una rama se dividio en dos nuevas
 * 
 * bool: true or false indicando si el inicio de la rama cambio debio a un insert al inicio.
 */
pair<NodoB*, pair<bool, bool>> ArbolB::insertarCrearRama(NodoB* nodo, NodoB* rama) {
    pair < NodoB*, pair<bool, bool>> ResultadoRama;
    ResultadoRama.first = NULL; //nodo Inicial de la rama
    ResultadoRama.second.first = false; //indica si se dividio la rama
    ResultadoRama.second.second = false; //indica si se modifica el inicio de la rama
    if (esHoja(rama)) {//si el nodo es hoja se inseta directamente dentro de ella
        pair < NodoB*, bool> resultado = insertarEnRama(rama, nodo); //insertamos el nuevo elemento dentro de la rama actual
        ResultadoRama.first = resultado.first; //posee la rama con el valor ya insertado
        ResultadoRama.second.second = resultado.second; //posee el resultado de si se modifico el inicio en el insert anterior
        if (contador(resultado.first) == orden_arbol) {//si la rama posee mas elementos de los permitidos se divide
            cout << "La rama debe dividirse\n";
            ResultadoRama.first = dividir(resultado.first); //dividimos la rama y obtenemos una nueva rama con sus respectivos apuntadores
            ResultadoRama.second.first = true; //identificar que la rama se dividio
        }
    } else {//si el nodo es rama se debe buscar la posicion donde insertarlo
        NodoB*temp = rama;
        do {
            if (nodo->id == temp->id) {//valor ya insertado, no se permiten repeditos
                cout << "insertarCrearRama(), El ID " << nodo->id << " ya existe\n";
                return ResultadoRama;
            } else if (nodo->id < temp->id) {
                pair < NodoB*, pair<bool, bool>> ResultadoInsert = insertarCrearRama(nodo, temp->izquierda);
                if (ResultadoInsert.second.second and ResultadoInsert.first != NULL) {//si se modifico el inicio de la rama
                    ResultadoRama.second.second = true;
                    temp->izquierda = ResultadoInsert.first;
                }
                if (ResultadoInsert.second.first) {//se dividio la subrama
                    pair < NodoB*, bool> auxInsert = insertarEnRama(rama, ResultadoInsert.first);
                    rama = auxInsert.first;
                    if (auxInsert.second) {
                        ResultadoRama.first = rama;
                    }
                    if (contador(rama) == orden_arbol) {
                        ResultadoRama.first = dividir(rama);
                        ResultadoRama.second.first = true;
                    }
                }
                return ResultadoRama;
            } else if (temp->siguiente == NULL) {
                pair < NodoB*, pair<bool, bool>> ResultadoInsert = insertarCrearRama(nodo, temp->derecha);
                if (ResultadoInsert.second.second and ResultadoInsert.first != NULL) {//si se modifico el inicio de la rama
                    ResultadoRama.second.second = true;
                    temp->derecha = ResultadoInsert.first;
                }
                if (ResultadoInsert.second.first) {//se dividio la subrama
                    pair < NodoB*, bool> auxInsert = insertarEnRama(rama, ResultadoInsert.first);
                    rama = auxInsert.first;
                    if (auxInsert.second) {
                        ResultadoRama.first = rama;
                    }
                    if (contador(rama) == orden_arbol) {
                        ResultadoRama.first = dividir(rama);
                        ResultadoRama.second.first = true;
                    }
                }
                return ResultadoRama;
            }
            temp = temp->siguiente;
        } while (temp != NULL);
    }
    return ResultadoRama;
}

NodoB* ArbolB::dividir(NodoB* rama) {
    int val = -999;
    string prueb;
    //int val2 = -999;
    NodoB*temp = NULL;
    NodoB*Nuevito = NULL;
    NodoB*aux = rama;

    NodoB*rderecha = NULL;
    NodoB*rizquierda = NULL;

    int cont = 0;
    while (aux != NULL) {
        cont++;
        //implementacion para dividir unicamente ramas de 4 nodos
        if (cont < 3) {
            val = aux->id;
            prueb = aux->nombreuser;
            temp = new NodoB(val,prueb);
            temp->izquierda = aux->izquierda;
            if (cont == 2) {
                temp->derecha = aux->siguiente->izquierda;
            } else {
                temp->derecha = aux->derecha;
            }
            rizquierda = insertarEnRama(rizquierda, temp).first;
        } else if (cont == 3) {
            val = aux->id;
            prueb = aux->nombreuser;
            Nuevito = new NodoB(val, prueb);
        } else {
            val = aux->id;
            prueb = aux->nombreuser;
            temp = new NodoB(val,prueb);
            temp->izquierda = aux->izquierda;
            temp->derecha = aux->derecha;
            rderecha = insertarEnRama(rderecha, temp).first;
        }
        aux = aux->siguiente;
    }
    Nuevito->derecha = rderecha;
    Nuevito->izquierda = rizquierda;
    return Nuevito;
}

pair<NodoB*, bool> ArbolB::insertarEnRama(NodoB* primero, NodoB* nuevo) {
    pair < NodoB*, bool> ret;
    ret.second = false;
    if (primero == NULL) {
        //primero en la lista
        ret.second = true;
        primero = nuevo;
    } else {
        //recorrer e insertar
        NodoB* aux = primero;
        while (aux != NULL) {
            if (aux->id == nuevo->id) {//------------->ya existe en el arbol
                cout << "insertarEnRama(), El ID " << nuevo->id << " ya existe\n";
                break;
            } else {
                if (aux->id > nuevo->id) {
                    if (aux == primero) {//------------->insertar al inicio
                        aux->anterior = nuevo;
                        nuevo->siguiente = aux;
                        //ramas del nodo
                        aux->izquierda = nuevo->derecha;
                        nuevo->derecha = NULL;
                        ret.second = true;
                        primero = nuevo;
                        break;
                    } else {//------------->insertar en medio;
                        nuevo->siguiente = aux;
                        //ramas del nodo
                        aux->izquierda = nuevo->derecha;
                        nuevo->derecha = NULL;

                        nuevo->anterior = aux->anterior;
                        aux->anterior->siguiente = nuevo;
                        aux->anterior = nuevo;
                        break;
                    }
                } else if (aux->siguiente == NULL) {//------------->insertar al final
                    aux->siguiente = nuevo;
                    nuevo->anterior = aux;
                    break;
                }
            }
            aux = aux->siguiente;
        }

    }
    ret.first = primero;

    return ret;
}

/*
 * Metodo para verificar si es hoja
 * Un nodo hoja no pose apuntadores a otros nodos hacia izquierda o derecha
 */
bool ArbolB::esHoja(NodoB* primero) {
    NodoB* aux = primero;
    while (aux != NULL) {
        cout << "[" << aux->id << "]->";
        if (aux->izquierda != NULL or aux->derecha != NULL) {
            return false;
        }
        aux = aux->siguiente;
    }
    cout << "Null\n";
    return true;
}

/*Metodo para contar los elementos de una rama*/
int ArbolB::contador(NodoB* primero) {
    int contador = 0;
    NodoB* aux = primero;
    while (aux != NULL) {
        contador++;
        aux = aux->siguiente;
    }
    return contador;
}


void ArbolB:: modificar(int id, string nuevouser){
    NodoB* aux = raiz;
    bool encontrado = false;

    if (aux!=NULL){
        do{
            if(aux->id == id){
                aux->nombreuser = nuevouser;
                encontrado = true;
            }
            aux = aux->siguiente;
        }while(aux->siguiente!=NULL && encontrado!=true);
    }

    /*
    nodoUsuarios* actual = new nodoUsuarios();
    actual = primero;
    bool encontrado = false;
    if(primero!=NULL){
        do{
            if(actual->nombreuser==userb){
				actual->nombreuser = nuevouser;
				actual->contra = contra;
				actual->contracifrada = cifrada;
				actual->edad = edad;
                encontrado = true;              
            }
            actual = actual->siguiente;
        }while(actual!=primero && encontrado != true);  
    }
    */

   /*
    while(aux!=NULL){
        if(aux->id == id){
            aux->nombreuser = nuevouser;
            cout<<"Nombre actual -> " <<aux->nombreuser<<"\n";
        }
        aux = aux->siguiente;
    }
    */
}


void ArbolB::eliminar(int id){
    NodoB*aux = raiz;
    NodoB*padre = NULL;
    while(aux != NULL){
        if(aux->id == id){
            if(aux->izquierda == NULL && aux->derecha == NULL){
                if(padre == NULL){
                    raiz = NULL;
                }else{
                    if(padre->izquierda == aux){
                        padre->izquierda = NULL;
                    }else{
                        padre->derecha = NULL;
                    }
                }
            }else if(aux->izquierda == NULL && aux->derecha != NULL){
                if(padre == NULL){
                    raiz = aux->derecha;
                }else{
                    if(padre->izquierda == aux){
                        padre->izquierda = aux->derecha;
                    }else{
                        padre->derecha = aux->derecha;
                    }
                }
            }else if(aux->izquierda != NULL && aux->derecha == NULL){
                if(padre == NULL){
                    raiz = aux->izquierda;
                }else{
                    if(padre->izquierda == aux){
                        padre->izquierda = aux->izquierda;
                    }else{
                        padre->derecha = aux->izquierda;
                    }
                }
            }else{
                NodoB*aux2 = aux->izquierda;
                NodoB*padre2 = aux;
                while(aux2->derecha != NULL){
                    padre2 = aux2;
                    aux2 = aux2->derecha;
                }
                aux->nombreuser = aux2->nombreuser;
                if(padre2->izquierda == aux2){
                    padre2->izquierda = aux2->izquierda;
                }else{
                    padre2->derecha = aux2->izquierda;
                }
            }
            break;
        }else if(aux->id > id){
            padre = aux;
            aux = aux->izquierda;
        }else{
            padre = aux;
            aux = aux->derecha;
        }
    }
}

//================================Grafo solo del arbol b=====================

void ArbolB::Grafo() {
    string dotFull = "";
    //escribir dot

    dotFull += "digraph G {\n";
    dotFull += "node[shape=record]\n";
    dotFull += "\t\t//Agregar Nodos Rama\n";
    dotFull += GrafoArbolAbb(raiz);
    //agregar conexiones de ramas
    dotFull += "\t\t//Agregar conexiones\n";
    dotFull += GrafoConexionRamas(raiz);

    dotFull += "}";

    //------->escribir archivo
    ofstream file;
    file.open("Arbol.dot");
    file << dotFull;
    file.close();

    //------->generar png
    system(("dot -Tpng Arbol.dot -o  Arbol.png"));

    //------>abrir archivo
    system(("Arbol.png"));

}

string ArbolB::GrafoArbolAbb(NodoB* rama) {
    string dot = "";
    if (rama != NULL) {
        //agrear rama actual
        dot += GrafoRamas(rama);
        //agregar las ramas siguientes recursivamente
        NodoB*aux = rama;
        while (aux != NULL) {
            if (aux->izquierda != NULL) {
                dot += GrafoArbolAbb(aux->izquierda);
            }
            if (aux->siguiente == NULL) {
                if (aux->derecha != NULL) {
                    dot += GrafoArbolAbb(aux->derecha);
                }
            }
            aux = aux->siguiente;
        }
    }
    return dot;
}

string ArbolB::GrafoRamas(NodoB*rama) {
    string dot = "";
    stringstream auxTXT;
    if (rama != NULL) {
        //============================================agregar rama=================================
        NodoB*aux = rama;
        auxTXT.str("");
        auxTXT << rama;
        dot = dot + "R" + auxTXT.str() + "[label=\"";
        int r = 1;
        while (aux != NULL) {
            if (aux->izquierda != NULL) {
                dot = dot + "<C" + to_string(r) + ">|";
                r++;
            }
            if (aux->siguiente != NULL) {
                dot = dot + "ID: " + to_string(aux->id) + "\\n Nick: " + aux->nombreuser + "|";
            } else {
                dot = dot + "ID: " + to_string(aux->id) + "\\n Nick: " +  aux->nombreuser;
                if (aux->derecha != NULL) {
                    dot = dot + "|<C" + to_string(r) + ">";
                }
            }
            aux = aux->siguiente;
        }
        dot = dot + "\"];\n";
    }
    return dot;
}

string ArbolB::GrafoConexionRamas(NodoB*rama) {
    string dot = "";
    stringstream auxTXT;
    if (rama != NULL) {
        //============================================agregar rama=================================
        NodoB*aux = rama;
        auxTXT << rama;
        string actual = "R" + auxTXT.str();
        int r = 1;
        while (aux != NULL) {
            if (aux->izquierda != NULL) {
                auxTXT.str("");
                auxTXT << aux->izquierda;
                dot += actual + ":C" + to_string(r) + "->" + "R" + auxTXT.str() + ";\n";
                r++;
                dot += GrafoConexionRamas(aux->izquierda);
            }
            if (aux->siguiente == NULL) {
                if (aux->derecha != NULL) {
                    auxTXT.str("");
                    auxTXT << aux->derecha;
                    dot += actual + ":C" + to_string(r) + "->" + "R" + auxTXT.str() + ";\n";
                    r++;
                    dot += GrafoConexionRamas(aux->derecha);
                }
            }
            aux = aux->siguiente;
        }
    }
    return dot;
}