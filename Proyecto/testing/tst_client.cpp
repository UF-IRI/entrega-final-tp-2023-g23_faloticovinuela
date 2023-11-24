#include <catch2/catch.hpp>
#include "cliente.h"


/*FIND CLIENT*/
TEST_CASE("FindClient returns the client with the specified ID") {
    eClient* clients = new eClient[3];
    clients[0] = {"1", "Juan", "Perez", "juan@perez.com", "12345678", "1980-01-01", "Activo"};
    clients[1] = {"2", "Maria", "Gonzalez", "maria@gonzalez.com", "87654321", "1990-02-02", "Activo"};
    clients[2] = {"3", "Pedro", "Sanchez", "pedro@sanchez.com", "98765432", "2000-03-03", "Activo"};

    eClient client = findClient(clients, 3, "2");

    REQUIRE(client.idCliente == "2");
    REQUIRE(client.nombre == "Maria");
    REQUIRE(client.apellido == "Gonzalez");
    REQUIRE(client.email == "maria@gonzalez.com");
    REQUIRE(client.telefono == "87654321");
    REQUIRE(client.fechaNac == "1990-02-02");
    REQUIRE(client.estado == "Activo");

    delete[] clients;
}

TEST_CASE("FindClient returns nullClient if the client with the specified ID is not found") {
    eClient* clients = new eClient[3];
    clients[0] = {"1", "Juan", "Perez", "juan@perez.com", "12345678", "1980-01-01", "Activo"};
    clients[1] = {"2", "Maria", "Gonzalez", "maria@gonzalez.com", "87654321", "1990-02-02", "Activo"};
    clients[2] = {"3", "Pedro", "Sanchez", "pedro@sanchez.com", "98765432", "2000-03-03", "Activo"};

    eClient client = findClient(clients, 3, "4");

    REQUIRE(client.idCliente == nullClient.idCliente);
    REQUIRE(client.nombre == nullClient.nombre);
    REQUIRE(client.apellido == nullClient.apellido);
    REQUIRE(client.email == nullClient.email);
    REQUIRE(client.telefono ==nullClient.telefono);
    REQUIRE(client.fechaNac == nullClient.fechaNac);
    REQUIRE(client.estado == nullClient.estado);;

    delete[] clients;
}


/*EXIST CLIENT*/
TEST_CASE("ExistClient returns true if the client with the specified ID exists") {
    eClient* clients = new eClient[3];
    clients[0] = {"1", "Juan", "Perez", "juan@perez.com", "12345678", "1980-01-01", "Activo"};
    clients[1] = {"2", "Maria", "Gonzalez", "maria@gonzalez.com", "87654321", "1990-02-02", "Activo"};
    clients[2] = {"3", "Pedro", "Sanchez", "pedro@sanchez.com", "98765432", "2000-03-03", "Activo"};

    bool exists = existClient(clients, 3, "2");

    REQUIRE(exists == true);

    delete[] clients;
}

TEST_CASE("ExistClient returns false if the client with the specified ID does not exist") {
    eClient* clients = new eClient[3];
    clients[0] = {"1", "Juan", "Perez", "juan@perez.com", "12345678", "1980-01-01", "Activo"};
    clients[1] = {"2", "Maria", "Gonzalez", "maria@gonzalez.com", "87654321", "1990-02-02", "Activo"};
    clients[2] = {"3", "Pedro", "Sanchez", "pedro@sanchez.com", "98765432", "2000-03-03", "Activo"};

    bool exists = existClient(clients, 3, "4");

    REQUIRE(exists == false);

    delete[] clients;
}
