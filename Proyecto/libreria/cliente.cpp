#include "cliente.h"

eCodFile leerClientes(eClient *clients, ifstream &file) {
  if (!file.is_open())
    return eCodFile::ErrorOpening;
  // reiniciar el file al inicio
  file.clear();
  file.seekg(0);

  str header;

  getline(file, header);
  // ELIMINO EL HEADER DE MIERDA DE LAS LINEAS A LEER
  eClient *aux = clients;
  str line;
  while (getline(file, line)) {
    char delimiter = ',';
    string idCliente, nombre, apellido, email, telefono, fechaNac, estado;

    buscar_y_reemplazar_todos(line, "á", "a");
    buscar_y_reemplazar_todos(line, "é", "e");
    buscar_y_reemplazar_todos(line, "í", "i");
    buscar_y_reemplazar_todos(line, "ó", "o");
    buscar_y_reemplazar_todos(line, "ú", "u");
    buscar_y_reemplazar_todos(line, "ñ", "ni");
    buscar_y_reemplazar_todos(line, "Á", "A");
    buscar_y_reemplazar_todos(line, "É", "E");
    buscar_y_reemplazar_todos(line, "Í", "I");
    buscar_y_reemplazar_todos(line, "Ó", "O");
    buscar_y_reemplazar_todos(line, "Ú", "U");
    buscar_y_reemplazar_todos(line, "Ñ", "NI");
    buscar_y_reemplazar_todos(line, "¿", "");
    buscar_y_reemplazar_todos(line, "¡", "");
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
    aux->nombre = nombre;
    aux->email = email;
    aux->apellido = apellido;
    aux->telefono = telefono;
    aux->fechaNac = fechaNac;
    aux->estado = estado;
    aux++;
  }

  return eCodFile::SuccessOperation;
}

void printClients(eClient *clients, int cant) {
  eClient *aux = clients, *last = (clients) + (cant - 1);
  cout << "--------------Clients--------------" << endl;
  if (cant == 0)
    return;

  while (true) {
    cout << "id:" << aux->nombre << endl;
    if (aux == last)
      break;
    aux++; // aux = aux + 1 o aux+= 1
  }
  cout << "---------------------------------------" << endl;
}

eClient findClient(eClient *clients, uint cant, str id) {
  eClient *aux = clients, *ultimo = (clients) + cant - 1;
  while (true) {
    if (aux->idCliente == id) {
      return *aux;
    }
    if (aux == ultimo)
      break;
    aux++;
  }
  return nullClient;
}

bool existClient(eClient *clients, uint cant, str id) {

  return findClient(clients, cant, id).idCliente != "";
}

void buscar_y_reemplazar_todos(string &frase, string buscar,
                               string reemplazar) {
  int pos = frase.find(buscar);
  while (pos != string::npos) {
    frase.replace(pos, buscar.size(), reemplazar);
    pos = frase.find(buscar, pos + reemplazar.size());
  }
}
