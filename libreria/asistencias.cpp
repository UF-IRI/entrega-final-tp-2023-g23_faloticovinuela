#include "asistencias.h"


Asistencia* resizeAsistencia(Asistencia* miLista, uint tam, uint nuevoTam) {
    Asistencia* aux = new Asistencia[nuevoTam];

    uint longitud = (tam <  nuevoTam) ? tam : nuevoTam;

    if(aux != nullptr) {

        for(uint i = 0; i < longitud; i++)
            aux[i] = miLista[i]; // *(miLista + i)

        delete[] miLista;
        return aux;
    }

    return nullptr;
}


eCodArchivos readAssistances(ifstream& file,Asistencia* assistances){
    // SABIENDO QUE ESTA ORDENADO EL ARCHIVO CLASES
    if(!file.is_open())
        return eCodArchivos::ErrorApertura;
    //Setear inicio
    file.clear();
    file.seekg(0);


    // read data as a block:
    while (file.good()) {
        file.read((char *)&assistances, sizeof(Asistencia));
    }



    return eCodArchivos::ExitoOperacion;
}



/*eAddAssistance addAssistance(Asistencia* assistances, Asistencia assistance) {
    if (!hayEspacio(asistencias)) {

    }

    miAgenda->CantContactos++;
    miAgenda->misContactos[miAgenda->CantContactos - 1] = miContacto;
    // miAgenda->*(misContactos + i )
    return eAgrContacto::ExitoAgregar;
}*/
