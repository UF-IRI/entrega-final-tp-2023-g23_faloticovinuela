#include "cliente.h"

eCodFile leerClientes(eClient* clients,ifstream& file){
    if(!file.is_open())
        return eCodFile::ErrorOpening;
    // reiniciar el file al inicio
    file.clear();
    file.seekg(0);

    str header;

    getline(file, header);
    // ELIMINO EL HEADER DE MIERDA DE LAS LINEAS A LEER
    eClient* aux = clients;
    str line;
    while (getline(file, line)) {
        char delimiter = ',';
        string idCliente, nombre, apellido, email, telefono, fechaNac, estado;
        std::istringstream iss(line);
        // IMPORTANTE QUE ESTE EN ESTE ORDEN
        getline(iss, idCliente, delimiter);
        getline(iss, nombre, delimiter);
        getline(iss, apellido, delimiter);
        getline(iss, email, delimiter);
        getline(iss, telefono, delimiter);
        getline(iss, fechaNac, delimiter);
        getline(iss, estado, delimiter);
        aux->idCliente = idCliente;
        aux->nombre  = nombre;
        aux->email  = email;
        aux->apellido  = apellido;
        aux->telefono  = telefono;
        aux->fechaNac  = fechaNac;
        aux->estado  = estado;
        aux++;
    }

    return eCodFile::SuccessOperation;
}

void printClients(eClient* clients,int cant)
{
    eClient* aux = clients,
        * last = (clients) + (cant  - 1);
    cout << "--------------Clients--------------"<< endl;
    if(cant == 0)
        return;

    while(true) {
        cout<<"id:" <<aux->nombre << endl;
        if (aux == last)
            break;
        aux++; // aux = aux + 1 o aux+= 1
    }
    cout << "---------------------------------------"<< endl;
}

eClient findClient(eClient* clients,uint cant, str id) {
    eClient* aux = clients,
        * ultimo = (clients) + cant - 1;
    while(true) {
        if (aux->idCliente == id ) {
            return *aux;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return nullClient;
}

bool existClient(eClient* clients,uint cant, str id){

    return findClient(clients,cant,id).idCliente != "" ;
}
