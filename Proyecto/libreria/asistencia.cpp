#include "asistencia.h"
#include <iostream>
using namespace std;
void resizeAssistances(Asistencia **miLista, uint tam, uint nuevoTam) {
  Asistencia *aux = new Asistencia[nuevoTam];
    Asistencia *auxLista = *miLista;
  if (aux == nullptr)
    return;

  uint longitud = (tam < nuevoTam) ? tam : nuevoTam;

  for (uint i = 0; i < longitud; i++){
    aux[i] = auxLista[i]; // **(miLista + i)
  }

  delete[] *miLista;
  *miLista = aux;
}

eCodFile readAssistances(ifstream &file, Asistencia *assistances,uint cant) {
  // SABIENDO QUE ESTA ORDENADO EL ARCHIVO CLASES
  if (!file.is_open())
    return eCodFile::ErrorOpening;
  // Setear inicio
  file.clear();
  file.seekg(0);

  Asistencia *aux = assistances;
  uint i=0;
  while (!file.eof()) {
    if(i == cant){
        break;
    }
    file.read((char *)&aux->idCliente, sizeof(uint));
    file.read((char *)&aux->cantInscriptos, sizeof(uint));

    Inscripcion *registered = new Inscripcion[aux->cantInscriptos];
    Inscripcion *auxInscriptions = registered;
    for (uint i = 0; i < aux->cantInscriptos; i++) {
      file.read((char *)auxInscriptions, sizeof(Inscripcion));
      auxInscriptions++;
    }
    aux->CursosInscriptos = registered;

    aux++;
    i++;
  }

  return eCodFile::SuccessOperation;
}

void printAssistances(Asistencia *assitances, int cant) {
  Asistencia *auxA = assitances, *lastA = (assitances) + (cant - 1);
  int i= 0;
  cout << "--------------Assistences--------------" << endl;
  if (cant == 0)
    return;
  while (true) {
    cout <<i << "-"<< "id:" << auxA->idCliente << endl;
    Inscripcion *auxH = auxA->CursosInscriptos,
                *lastAux =
                    (auxA->CursosInscriptos) + (auxA->cantInscriptos - 1);
    cout << "Incripciones:";
    while (true) {
      cout << auxH->idCurso << ",";
      if (auxH == lastAux)
        break;
      auxH++;
    }
    cout << endl;
    if (auxA == lastA)
      break;
    auxA++;
    i++;
  }
  cout << "---------------------------------------" << endl;
}

eAddAssistance addAssistance(Asistencia*& assistances,uint cant ,Asistencia assistance){
  if(assistances == nullptr){
    return eAddAssistance::ErrorSpace;
  }
  *(assistances + cant -1) = assistance;
  // miAgenda->*(misContactos + i )
  return eAddAssistance::SuccessAdd;
}

int countAssistences(ifstream &file) {
  if (!file.is_open()) {
    cout << "Error opening binary file" << endl;
    return 0;
  }
  // reiniciar el file al inicio
  file.clear();
  file.seekg(0);

  int cantAssistances = -1;
  uint auxReadAssitances;
  while (!file.eof()) {
    file.read((char *)&auxReadAssitances, sizeof(uint));
    file.read((char *)&auxReadAssitances, sizeof(uint));
    Inscripcion auxInscriptions;
    for (uint i = 0; i < auxReadAssitances; i++) {
      file.read((char *)&auxInscriptions, sizeof(Inscripcion));
    }
    cantAssistances++;
  }
  return cantAssistances;
}

eCodFile writeAssistances(Asistencia *assistances, uint cant, str today) {
  ofstream fileOutPut("../../asistencias_" + today,ios::binary);
  if (!fileOutPut.is_open()) {
    return eCodFile::ErrorOpening;
  }
  Asistencia *aux = assistances;
  if (fileOutPut.is_open()) {
    for (uint i = 0; i < cant; i++) {
      fileOutPut.write((char *)&aux[i].idCliente, sizeof(uint));
      fileOutPut.write((char *)&aux[i].cantInscriptos, sizeof(uint));
      for (uint j = 0; j < aux[i].cantInscriptos; j++) {
        fileOutPut.write((char *)&aux[i].CursosInscriptos[j],
                         sizeof(Inscripcion));
      }
    }
  }
  fileOutPut.close();
  return eCodFile::SuccessOperation;
}

Asistencia* findAssistances(Asistencia* assistances,uint cant ,str idClient) {
  Asistencia* aux = assistances,
      * ultimo = (assistances) +cant - 1;
  if(cant == 0 || assistances == nullptr){
    return nullptr;
  }
  while(true) {
    if (aux->idCliente == stoul(idClient)) {
      return aux;
    }
    if (aux == ultimo)
      break;
    aux++;
  }
  return nullptr;
}

eAddInscriptionInAssistance addInscriptionAssistance(Inscripcion*& inscriptions,uint cant,Inscripcion inscription){
  if(inscriptions == nullptr){
    return eAddInscriptionInAssistance::ErrorSpaceAssitance;
  }
  *(inscriptions + cant - 1) = inscription;
  return eAddInscriptionInAssistance::SuccessAddAssistance;
}
