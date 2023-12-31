#include "asistencia.h"
#include "cliente.h"
#include "gym.h"
#include <QThread>
#include <ctime>

int main() {

  ifstream fileClient("../../iriClientesGYM.csv");
  ifstream fileClasses("../../iriClasesGYM.csv");
  //ifstream fileAssistances("../../asistencias_1697673600000.dat", ios::binary);

  if (!fileClient.is_open()) {
    cout << "No pudimos abrir el archivo Clientes" << endl;
    return 0;
  }
  if (!fileClasses.is_open()) {
    cout << "No pudimos abrir el archivo Clases" << endl;
    return 0;
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
  uint cantClasses = countClasses(fileClasses, realCantClasses);
  eClass *classes = new eClass[cantClasses];
  eBook *books = new eBook[realCantClasses];
  eCodFile resClasses = readClasses(classes, books, fileClasses, cantClasses);

  /* Asistencias
  int cantAssistances = countAssistences(fileAssistances);
  cout << "assitencias" << cantAssistances << endl;
  Asistencia *assitances = new Asistencia[cantAssistances - 1];
  eCodFile resAssistances = readAssistances(fileAssistances, assitances);
*/

  // printClasses(classes,cantClasses);
  // printAssistances(assitances,cantAssistances);
  // printClients(clients,countClients);
  Asistencia *assitances = new Asistencia[DEFAULT_MAX_ASSITANCES_CAPACITY];
  uint countAssitances = 0;
  eGym *gymData = new eGym({clients, countClients, assitances, countAssitances,
                            DEFAULT_MAX_ASSITANCES_CAPACITY, classes,
                            cantClasses, time(0), books, realCantClasses});


  for (int i = 0; i < 10000; i++) {
    uint idBook = genRandomNumber(1, realCantClasses);
    uint idClient = genRandomNumber(1, countClients);
    cout<<"params: " << "idBook: " << idBook << " - idClient:" << idClient  <<endl;
    eBookClass res = bookClassGym(gymData, idBook, to_string(idClient));
    cout<< "RES NMR "<<i << " :" << res <<endl;
  }

  cout << "Cant clientes: " << gymData->countClients
       << " - Cant assitances: " << gymData->countAssistances
       << " - Cant classes: " << gymData->countClasses
       << " - Cant books: " << gymData->countBooks
       << " - Today: " << ctime(&gymData->today) << endl;

  printAssistances(gymData->assistances, gymData->countAssistances);

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
  fileClient.close();
  fileClasses.close();
  //fileAssistances.close();
  return 0;
}
