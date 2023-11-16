#ifndef GYM_H
#define GYM_H

#include "encabezados.h"
#include "cliente.h"
#include "asistencia.h"

enum addContact  { ErrAgrEspacio = -1,  ExitoAgregar = 1 };
enum srchClass { ErrSrchValue = -2,   ErrSrchIndex = -1, SuccessSearch = 1 };
enum bookClass { ErrMaxInscriptionsReachedInClass = -7,ErrNonNoSpaceInClass = -7,ErrNonExistentClass = -6,ErrClientAlreadySubscribed = -5 ,ErrClientSubscribedOtherClass = -4 ,ErrNonExistentClient = -3,ErrSpace = -2,   ErrNotFoundClass = -1, SuccessBook = 1 };

typedef enum addContact  eAddContact;
typedef enum srchClass eSrchClass;
typedef enum bookClass eBookClass;

struct clase{
    str idClass;

    str name;

    int maxCapacity;

    str room;

    str* schedules;
    int cantSchedules;

    int length;
};
typedef struct clase eClass;

struct book{
    uint idBook;
    str idClass;
    uint schedule;
    str* inscriptions;
    int countInscriptions;
};typedef struct book eBook;
const eBook nullBook = { 0,"",0,0,0};
const eClass nullClass = { "","",0,"",nullptr,0,0};

struct gym {
    eClient* clients;
    uint countClients;
    Asistencia* assistances;
    uint countAssistances;
    uint countMaxAssistances;
    eClass* clases;
    uint countClasses;
    time_t today;
    eBook* books;
    uint countBooks;
};typedef struct gym eGym;


eSrchClass searchClass(eClass* classes,int cant ,str name);
eCodFile readClasses(eClass *classes,eBook* books ,ifstream &file, int cant);
void printClasses(eClass* classes,int cant);
uint countClasses(ifstream &file,uint& realCantClasses);
eBookClass bookClassGym(eGym &gym, uint idBook, str idClient);
eBook findBook(eBook* books,uint cant, uint id);
bool existBook(eBook* books,uint cant, uint id);
bool isClientInBook(eBook* books,uint cant, uint schedule ,str idClient);
bool isClientInInscription(str* inscriptions, uint cant, str idClient);
bool isClientInSchedule(eBook *books, uint cant, uint schedule, str idClient);
eClass findClass(eClass *classes, uint cant, str idClass);

#endif // GYM_H
