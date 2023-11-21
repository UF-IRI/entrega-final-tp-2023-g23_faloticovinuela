#ifndef ASISTENCIA_H
#define ASISTENCIA_H


#include "encabezados.h"
//idCliente,cantInscriptos,{Inscripción(idCurso, fechaInscripción)}

typedef enum addAssistance{ErrorSpace=0,  SuccessAdd=1} eAddAssistance;
typedef enum addInscriptionInAssistance{ErrorSpaceAssitance=0,  SuccessAddAssistance=1} eAddInscriptionInAssistance;
typedef enum resetAssistance{ErrorResetAssistance=0,  SuccessResetAssistance=1} eResetAssistances;
typedef struct {
    uint idCurso;
    time_t fechaInscripcion;
} Inscripcion;

typedef struct {
    uint idCliente, cantInscriptos;
    Inscripcion* CursosInscriptos;
} Asistencia;
const Asistencia nullAsistencia = { 0, 0, nullptr};

eAddAssistance addAssistance(Asistencia*& assistances,uint cant ,Asistencia assistance);
bool hasSpace(Asistencia* assistances);
eCodFile readAssistances(ifstream& file,Asistencia* assistances);
void printAssistances(Asistencia* assitances,int cant);
eCodFile writeAssitance(ofstream& file,Asistencia* assistances,int cant);
int countAssistences(ifstream& file);
void resizeAssistances(Asistencia** miLista, uint tam, uint nuevoTam);
eCodFile writeAssistances(Asistencia* assistances,uint cant,str today);
Asistencia* findAssistances(Asistencia* assistances,uint cant ,str idClient);
eAddInscriptionInAssistance addInscriptionAssistance(Inscripcion*& inscriptions,uint cant,Inscripcion inscription);

#endif // ASISTENCIA_H
