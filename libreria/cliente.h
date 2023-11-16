#ifndef CLIENTE_H
#define CLIENTE_H

#include "encabezados.h"


struct cliente{
    str idCliente,nombre,apellido,email,telefono,fechaNac,estado;
};typedef struct cliente eClient;

const eClient nullClient = { "", "", "", "", "","",""};

eCodFile leerClientes(eClient* clientes,ifstream& archivo);
eClient findClient(eClient* clients,uint cant, str id);
void printClients(eClient* clients,int cant);
bool existClient(eClient* clients,uint cant, str id);
#endif // CLIENTE_H
