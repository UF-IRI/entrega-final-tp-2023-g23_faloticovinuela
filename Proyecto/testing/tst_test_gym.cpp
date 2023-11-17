
#include <catch2/catch.hpp>
#include "gym.h"


TEST_CASE("Agenda Agregacion") {
    ifstream fileClient("../../iriClientesGYM.csv");
    ifstream fileClasses("../../iriClasesGYM.csv");
    ifstream fileAssistances("../../asistencias_1697673600000.dat", ios::binary);

    if (!fileClient.is_open()) {
        cout << "No pudimos abrir el archivo Clientes" << endl;

    }
    if (!fileClasses.is_open()) {
        cout << "No pudimos abrir el archivo Clases" << endl;

    }
    if (!fileAssistances.is_open()) {
        cout << "No pudimos abrir el archivo Asistencias" << endl;

    }

    SECTION("Chequeo Archivos "){
        REQUIRE((fileClient.is_open() && fileClasses.is_open() && fileAssistances.is_open()));
    }

    string line;
    /* CLIENTES */
    uint countClients = 0;
    while (getline(fileClient, line))
        countClients++;
    countClients--;
    eClient *clients = new eClient[countClients];
    eCodFile resClients = leerClientes(clients, fileClient);

    /* Clases */
    uint realCantClasses;
    uint cantClasses = countClasses(fileClasses,realCantClasses);
    eClass *classes = new eClass[cantClasses];
    eBook *books = new eBook[realCantClasses];
    eCodFile resClasses = readClasses(classes, books,fileClasses, cantClasses);

    Asistencia* assitances = new Asistencia[DEFAULT_MAX_ASSITANCES_CAPACITY];
    uint countAssitances = 0;
    eGym* gymData = new eGym({clients,countClients,assitances,countAssitances,DEFAULT_MAX_ASSITANCES_CAPACITY,classes,cantClasses,time(0),books,realCantClasses}) ;



    delete[] clients;
    delete[] classes;
    delete[] assitances;
    delete[] books;
    fileClient.close();
    fileClasses.close();
    fileAssistances.close();
}

