#include "gym.h"
#include <ctime>

eSrchClass searchClass(eClass *classes, int cant, str name) {
  eClass *aux = classes, *last = (classes) + cant - 1;
  while (true) {
    if (aux->name == name) {
      return eSrchClass::SuccessSearch;
    }
    if (aux == last)
      break;
    aux++;
  }
  return eSrchClass::ErrSrchIndex;
}
eCodFile readClasses(eClass *classes, eBook *books, ifstream &file, int cant) {
  // SABIENDO QUE ESTA ORDENADO EL ARCHIVO CLASES
  if (!file.is_open())
    return eCodFile::ErrorOpening;
  // Setear inicio
  file.clear();
  file.seekg(0);

  str header;
  getline(file, header);
  eClass *aux = classes;
  eBook *auxBooks = books;
  str *contSchedule;
  bool firstLine = true;
  str line;
  while (getline(file, line)) {
    char delimiter = ',';
    string idClass, name, schedule;
    str field;
    std::istringstream iss(line);
    getline(iss, idClass, delimiter);
    getline(iss, name, delimiter);
    getline(iss, schedule, delimiter);

    eSrchClass res = searchClass(classes, cant, name);

    if (res == eSrchClass::SuccessSearch && name != "Musculacion") {
      *contSchedule = schedule;
      contSchedule++;
      aux->cantSchedules += 1;

      // Init Book
      auxBooks->idBook = stoul(idClass);
      auxBooks->countInscriptions = 0;
      auxBooks->inscriptions = new string[aux->maxCapacity];
      auxBooks->idClass = aux->idClass;
      auxBooks->schedule = stoul(schedule);

    } else if (name != "Musculacion" && name != aux->name) {
      if (!firstLine) {
        aux++;
      } else {
        firstLine = false;
      }
      aux->idClass = idClass;
      aux->name = name;
      aux->length = 60;
      aux->maxCapacity = 45;
      aux->room = "Salita";
      aux->schedules = new str[10];
      aux->cantSchedules = 0;
      contSchedule = aux->schedules;

      // Init Book
      auxBooks->idBook = stoul(idClass);
      auxBooks->countInscriptions = 0;
      auxBooks->inscriptions = new str[aux->maxCapacity];
      auxBooks->idClass = aux->idClass;
      auxBooks->schedule = stoul(schedule);
    }
    auxBooks++;
  }

  return eCodFile::SuccessOperation;
}

void printClasses(eClass *classes, int cant) {
  eClass *aux = classes, *last = (classes) + (cant - 1);
  cout << "--------------Classes--------------" << endl;
  while (true) {
    cout << "Name:" << aux->name << endl;
    str *auxH = aux->schedules,
        *lastAux = (aux->schedules) + (aux->cantSchedules - 1);
    cout << "Horarios:";
    while (true) {
      cout << *auxH << ",";
      if (auxH == lastAux)
        break;
      auxH++;
    }
    cout << endl;
    if (aux == last)
      break;
    aux++;
  }
  cout << "---------------------------------------" << endl;
}

uint countClasses(ifstream &file, uint &realCantClasses) {

  if (!file.is_open()) {
    cout << "Error opening binary file" << endl;
    return 0;
  }
  if (realCantClasses != 0) {
    realCantClasses = 0;
  }
  // reiniciar el file al inicio
  file.clear();
  file.seekg(0);

  str line;
  int cantClasses = 0;
  str names = "";
  str auxName;
  getline(file, line); // get header
  while (getline(file, line)) {
    std::istringstream iss(line);
    getline(iss, auxName, ',');
    getline(iss, auxName, ',');
    size_t pos = 0;
    str token;
    str nameToSplit = names;
    bool finded = false;
    if (nameToSplit.length() != 0) {
      while ((pos = nameToSplit.find(',')) != std::string::npos) {
        token = nameToSplit.substr(0, pos);
        nameToSplit.erase(0, pos + 1);
        if (token == auxName) {
          finded = true;
        }
      }
      if (!finded && auxName.compare("Musculacion") != 0 &&
          auxName.compare("") != 0) {
        names += auxName + ',';
        cantClasses++;
      }
    } else {
      names = auxName + ',';
      cantClasses++;
    }
    if(auxName.compare("Musculacion") != 0){
      realCantClasses++;
    }
  }

  return cantClasses;
}

eBookClass bookClassGym(eGym &gym, uint idBook, str idClient) {

  eBook bookClass = findBook(gym.books, gym.countBooks, idBook);
  eClass realClass = findClass(gym.clases, gym.countClasses, bookClass.idClass);
  cout << "VAR:" << idBook << "-" << idClient << endl;
  // comprobar que la clase existe
  if (bookClass.idClass == "") {
    return eBookClass::ErrNonExistentClass;

    // comprobar que la clase tenga espacio
  } else if (bookClass.countInscriptions >= realClass.maxCapacity) {
    return eBookClass::ErrNonNoSpaceInClass;
  }

  // comprobar que existe el cliente
  if (!existClient(gym.clients, gym.countClients, idClient)) {
    return eBookClass::ErrNonExistentClient;

    /* Comprobar que el cliente no este inscripto en otra clase en el mismo
       horario, a su vez chequea que no este en ya inscripto en esta clase */
  } else if (isClientInSchedule(gym.books, gym.countBooks, bookClass.schedule,
                                idClient)) {
    return eBookClass::ErrClientSubscribedOtherClass;
  }

  // revisar si sigue siendo hoy, sino reiniciar asistencias
  time_t now = time(0);
  uint diff = difftime(now, gym.today) / 60 / 60 / 24;
  if (diff >= 1) {
    // siguiente dia
    gym.today = now;
    // Guardo las asistencias en mi archivo
    stringstream ss;
    str timeAsString;
    ss << now << ',' << endl;
    getline(ss, timeAsString, ',');
    writeAssistances(gym.assistances, gym.countAssistances, timeAsString);

    // Reinicio las asistencias y paso de dia

    resizeAssistences(&gym.assistances, gym.countAssistances, 0);
    gym.countAssistances = 0;
  } else {

    Inscripcion newInscription = {idBook,time(0)};
    // CHEQUEAR QUE HAYA ESPACIO
    if (gym.countAssistances < gym.countMaxAssistances) {
      // guardar asistencia
      Asistencia* assistance =
          findAssistances(gym.assistances, gym.countAssistances, idClient);

      // chequear si existe
      if (assistance == nullptr) {
        // crearla y agregar
        Asistencia newAssistance = {stoul(idClient),1,new Inscripcion[DEFAULT_MAX_INSCRIPTIONS_ASSITANCES_CAPACITY]};
        *newAssistance.CursosInscriptos = newInscription;
        gym.countAssistances++;
        addAssistance(gym.assistances,gym.countAssistances,newAssistance);
      } else {
        // agregar
        if(assistance->cantInscriptos < DEFAULT_MAX_INSCRIPTIONS_ASSITANCES_CAPACITY){
          assistance->cantInscriptos++;
          addInscriptionAssistance(assistance->CursosInscriptos,assistance->cantInscriptos,newInscription);

        } else {
          return eBookClass::ErrMaxInscriptionsReachedInClass;
        }
      }
    } else {
      printAssistances(gym.assistances,gym.countAssistances);
      resizeAssistences(&gym.assistances, gym.countAssistances,
                        gym.countMaxAssistances * 2);
      gym.countAssistances = gym.countMaxAssistances * 2;
      if (gym.assistances == nullptr) {
        return eBookClass::ErrSpace;
      }
      bookClassGym(gym,idBook,idClient);
    }
  }
  return eBookClass::SuccessBook;
}

bool isClientInInscription(str *inscriptions, uint cant, str idClient) {
  str *auxInscriptions = (inscriptions),
      *auxLastInscriptions = (inscriptions) + cant - 1;
  if(cant == 0){
    return false;
  }
  while (true) {
    if ( idClient.compare(*auxInscriptions) == 0) {
      return true;
    }
    if (auxInscriptions == auxLastInscriptions)
      break;
    auxInscriptions++;
  }
  return false;
}

bool isClientInSchedule(eBook *books, uint cant, uint schedule, str idClient) {
  eBook *aux = books, *ultimo = (books) + cant - 1;

  while (true) {

    if (aux->schedule == schedule) {
      if (isClientInInscription(aux->inscriptions, aux->countInscriptions,
                                idClient)) {
        return true;
      }
    }

    if (aux == ultimo)
      break;
    aux++;
  }
  return false;
}

eBook findBook(eBook *books, uint cant, uint id) {
  eBook *aux = books, *ultimo = (books) + cant - 1;
  while (true) {
    if (aux->idBook == id) {
      return *aux;
    }
    if (aux == ultimo)
      break;
    aux++;
  }
  return nullBook;
}

bool existBook(eBook *books, uint cant, uint id) {

  return findBook(books, cant, id).idClass != "";
}

eClass findClass(eClass *classes, uint cant, str idClass) {
  eClass *aux = classes, *ultimo = (classes) + cant - 1;
  while (true) {
    if (aux->idClass == idClass) {
      return *aux;
    }
    if (aux == ultimo)
      break;
    aux++;
  }
  return nullClass;
}

void printBooks(eBook* books,uint cant){
  eBook *aux = books, *last = (books) + (cant - 1);
  cout << "--------------Books--------------" << endl;
  while (true) {
    cout << "Name:" << aux->idBook << endl;
    cout << "Cant inscriptions:" << aux->countInscriptions << endl;
    if(aux->countInscriptions){
      str *auxH = aux->inscriptions,
          *lastAux = (aux->inscriptions) + (aux->countInscriptions - 1);
      cout << "Inscriptiones:";
      while (true) {
        cout << *auxH << ",";
        if (auxH == lastAux)
          break;
        auxH++;
      }
      cout << endl;
    }

    if (aux == last)
      break;

    aux++;
  }
  cout << "---------------------------------------" << endl;
}

uint genRandomNumber(uint min,uint max){

   uint randomNumber;
   randomNumber = (rand() % max) + min;
   return randomNumber;
}

