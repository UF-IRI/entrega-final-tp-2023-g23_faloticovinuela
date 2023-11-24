
#include "asistencia.h"
#include "gym.h"
#include <catch2/catch.hpp>


TEST_CASE("Is Client in Schedule") {
  eBook *books = new eBook[10];
  str *inscripciones = new str[5];
  str *inscripciones2 = new str[5];
  inscripciones[0] = "1";
  inscripciones2[0] = "12";
  eBook book = {1, "2", 4, inscripciones, 1};
  eBook book2 = {2, "2", 4, inscripciones2, 1};
  books[0] = book;
  books[1] = book;

  bool res = isClientInSchedule(books, 2, 4, "1");

  REQUIRE(res);

  delete[] books;
  delete[] inscripciones;
  delete[] inscripciones2;
}


TEST_CASE("Change of day when adding reservation") {
  ifstream fileClient("../../iriClientesGYM.csv");
  ifstream fileClasses("../../iriClasesGYM.csv");

  SECTION("FILES") {
    REQUIRE((fileClasses.is_open() && fileClient.is_open()));
  }
  string line;
  /* CLIENTS */
  uint countClients = 0;
  while (getline(fileClient, line))
    countClients++;
  countClients--;
  eClient *clients = new eClient[countClients];
  eCodFile resClients = leerClientes(clients, fileClient);

  /* CLASSES */
  uint realCantClasses;
  uint cantClasses = countClasses(fileClasses, realCantClasses);
  eClass *classes = new eClass[cantClasses];
  eBook *books = new eBook[realCantClasses];
  eCodFile resClasses = readClasses(classes, books, fileClasses, cantClasses);

  Asistencia *assitances = new Asistencia[DEFAULT_MAX_ASSITANCES_CAPACITY];
  uint countAssitances2 = 0;
  eGym *gymData = new eGym({clients, countClients, assitances, countAssitances2,
                            DEFAULT_MAX_ASSITANCES_CAPACITY, classes,
                            cantClasses, time(0), books, realCantClasses});

  int idBookToTest = 1;
  uint idClientToTest[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (int i = 0; i < 10; i++) {
    uint idBook = idBookToTest;
    uint idClient = idClientToTest[i];
    eBookClass res = bookClassGym(gymData, idBook, to_string(idClient));
    REQUIRE(res == eBookClass::SuccessBook);
  }

  SECTION("Effective day change") {
    gymData->today -= 25 * 60 * 60 * 1000;
    time_t prevDay = gymData->today;
    eBookClass res = bookClassGym(gymData, idBookToTest, to_string(11));

    SECTION("Correct data entry") {
      stringstream ss;
      str timeAsString;
      ss << prevDay << ',' << endl;
      getline(ss, timeAsString, ',');
      ifstream fileOutPut("../../asistencias_" + timeAsString, ios::binary);
      SECTION("FILE IN WRITE ASSISTANCES") { REQUIRE(fileOutPut.is_open()); }
      int cantAssistances = countAssistences(fileOutPut);
      Asistencia *assitances = new Asistencia[cantAssistances];
      eCodFile resAssistances = readAssistances(fileOutPut, assitances,cantAssistances);

      Asistencia *auxAssistances = assitances,
                 *lastAssistance = assitances + cantAssistances - 1;
      bool isEqual = true;
      int auxCheck = 0;
      while (true) {
        uint idClientToTest[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        if (auxAssistances->idCliente != idClientToTest[auxCheck] ||
            auxAssistances->cantInscriptos != 1 ||
            auxAssistances->CursosInscriptos[0].idCurso != 1) {
          isEqual = false;
        }
        if (!isEqual || auxAssistances == lastAssistance) {
          break;
        }
        auxAssistances++;auxCheck++;
      }
      REQUIRE(isEqual);
    }

    SECTION("Returns that the day was reset") {
      REQUIRE(res == eBookClass::ResetDay);
    }
    SECTION("the function resets the assistances") {
      REQUIRE(gymData->countAssistances == 0);
    }
    SECTION("Resets the books ") {
      bool aux = true;
      eBook *auxBook = gymData->books,
            *last = (gymData->books + gymData->countBooks - 1);
      int i = 0;
      while (true) {
        aux = (auxBook + i)->countInscriptions == 0;
        if (!aux || auxBook == last) {
          break;
        }
        auxBook++;
      }
      REQUIRE(aux);
    }
    SECTION("Change of day") { REQUIRE(gymData->today != prevDay); }
  }
  fileClasses.close();
  fileClient.close();
  delete[] clients;
  delete[] classes;
  Asistencia *auxLista = gymData->assistances;
  for(int i=0;i < gymData->countAssistances ; i++){
    delete[] (auxLista + i)->CursosInscriptos;
  }
  delete[] gymData->assistances;
  eBook *auxBooks = gymData->books;
  for(int i=0;i < gymData->countBooks ; i++){
    delete [] (auxBooks + i)->inscriptions;
  }
  delete[] books;
  delete gymData;
}
