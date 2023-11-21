
#include <catch2/catch.hpp>
#include "gym.h"
#include "asistencia.h"


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


TEST_CASE("Agregacion assitance") {
    Asistencia* assitances = new Asistencia[10];
    Asistencia asistencia =  {1,0,new Inscripcion[0]};
    Asistencia asistencia2 =  {2,0,new Inscripcion[0]};
    uint cant = 0;

    cant++;
    addAssistance(assitances,cant,asistencia);
    cant++;
    addAssistance(assitances,cant,asistencia2);
    REQUIRE(assitances[0].idCliente == 1);
    REQUIRE(assitances[1].idCliente == 2);
    delete [] assitances;

}

TEST_CASE("Is Client in Schedule") {
    eBook* books = new eBook[10];
    str* inscripciones = new str[5];
    str* inscripciones2 = new str[5];
    inscripciones[0] = "1";
    inscripciones2[0] = "12";
    eBook book = {1,"2",4,inscripciones,1};
    eBook book2 = {2,"2",4,inscripciones2,1};
    books[0] = book;
    books[1] = book;

    bool res = isClientInSchedule(books,2,4,"1");

    REQUIRE(res);

    delete [] books;
    delete [] inscripciones;
    delete [] inscripciones2;
}

TEST_CASE("check findAssistances") {
    Asistencia* assitances = new Asistencia[10];
    Asistencia asistencia =  {1,0,new Inscripcion[0]};
    Asistencia asistencia2 =  {2,0,new Inscripcion[0]};
    Asistencia asistencia3 =  {3,0,new Inscripcion[0]};
    Asistencia asistencia4 =  {4,0,new Inscripcion[0]};
    addAssistance(assitances,0,asistencia);
    addAssistance(assitances,2,asistencia2);
    addAssistance(assitances,3,asistencia3);
    addAssistance(assitances,4,asistencia4);

    Asistencia* assistance =
        findAssistances(assitances, 4, "4");

    REQUIRE(assistance != nullptr);
    assistance->idCliente = 5;

    REQUIRE(assitances[3].idCliente == 5 );

    delete [] assitances;
}

