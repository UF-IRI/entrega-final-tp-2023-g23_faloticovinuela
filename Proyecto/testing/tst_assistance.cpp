
#include "asistencia.h"
#include <catch2/catch.hpp>


/*ADD ASSISTANCES*/
TEST_CASE("Add assistance to an empty array") {
  Asistencia assistance;
  assistance.idCliente = 123;
  assistance.cantInscriptos = 1;
  Inscripcion inscripcion;
  inscripcion.idCurso = 456;
  inscripcion.fechaInscripcion = 1674467200;
  assistance.CursosInscriptos = &inscripcion;

  Asistencia *assistances = nullptr;
  uint cant = 0;

  eAddAssistance result = addAssistance(assistances, cant, assistance);

  REQUIRE(result == eAddAssistance::ErrorSpace);
  delete[] assistances;
}

TEST_CASE("Add assistance to a non-empty array") {
  Asistencia assistance1;
  assistance1.idCliente = 123;
  assistance1.cantInscriptos = 1;
  Inscripcion inscripcion1;
  inscripcion1.idCurso = 456;
  inscripcion1.fechaInscripcion = 1674467200;
  assistance1.CursosInscriptos = &inscripcion1;

  Asistencia assistance2;
  assistance2.idCliente = 789;
  assistance2.cantInscriptos = 2;
  Inscripcion inscripcion2;
  inscripcion2.idCurso = 987;
  inscripcion2.fechaInscripcion = 1674468000;
  assistance2.CursosInscriptos = &inscripcion2;

  Asistencia *assistances = new Asistencia[2];
  assistances[0] = assistance1;
  uint cant = 2;
  eAddAssistance result = addAssistance(assistances, cant, assistance2);

  REQUIRE(result == eAddAssistance::SuccessAdd);
  CHECK(assistances[0].idCliente == 123);
  CHECK(assistances[0].cantInscriptos == 1);
  CHECK(assistances[0].CursosInscriptos->idCurso == 456);
  CHECK(assistances[0].CursosInscriptos->fechaInscripcion == 1674467200);
  CHECK(assistances[1].idCliente == 789);
  CHECK(assistances[1].cantInscriptos == 2);
  CHECK(assistances[1].CursosInscriptos->idCurso == 987);
  CHECK(assistances[1].CursosInscriptos->fechaInscripcion == 1674468000);

  delete[] assistances;
}



/*FIND ASSISTANCES*/
TEST_CASE("Find assistance entries in an empty array") {
  Asistencia *assistances = nullptr;
  uint cant = 100;
  str idClient = "123";

  Asistencia *result = findAssistances(assistances, cant, idClient);
  REQUIRE(result == nullptr);
}

TEST_CASE("Find assistance entry for a client in a non-empty array") {
  Asistencia assistance1;
  assistance1.idCliente = 123;
  assistance1.cantInscriptos = 1;
  Inscripcion inscripcion1;
  inscripcion1.idCurso = 456;
  inscripcion1.fechaInscripcion = 1674467200;
  assistance1.CursosInscriptos = new Inscripcion[1];
  assistance1.CursosInscriptos[0] = inscripcion1;

  Asistencia assistance2;
  assistance2.idCliente = 789;
  assistance2.cantInscriptos = 2;
  Inscripcion inscripcion2;
  inscripcion2.idCurso = 987;
  inscripcion2.fechaInscripcion = 1674468000;
  assistance2.CursosInscriptos = new Inscripcion[1];
  assistance2.CursosInscriptos[0] = inscripcion2;
  Asistencia *assistances = new Asistencia[2];
  assistances[0] = assistance1;
  assistances[1] = assistance2;
  uint cant = 2;
  str idClient = "123";

  Asistencia *result = findAssistances(assistances, cant, idClient);
  REQUIRE(result != nullptr);

  REQUIRE(result->idCliente == 123);
  REQUIRE(result->cantInscriptos == 1);
  REQUIRE(result->CursosInscriptos->idCurso == 456);
  REQUIRE(result->CursosInscriptos->fechaInscripcion == 1674467200);

  delete[] assistances;
}

TEST_CASE("Fail to find assistance entry for a non-existent client in a "
          "non-empty array") {
  Asistencia assistance1;
  assistance1.idCliente = 123;
  assistance1.cantInscriptos = 1;
  Inscripcion inscripcion1;
  inscripcion1.idCurso = 456;
  inscripcion1.fechaInscripcion = 1674467200;
  assistance1.CursosInscriptos = new Inscripcion[1];
  assistance1.CursosInscriptos[0] = inscripcion1;
  Asistencia assistance2;
  assistance2.idCliente = 789;
  assistance2.cantInscriptos = 2;
  Inscripcion inscripcion2;
  inscripcion2.idCurso = 987;
  inscripcion2.fechaInscripcion = 1674468000;
  assistance2.CursosInscriptos = new Inscripcion[1];
  assistance2.CursosInscriptos[0] = inscripcion2;
  Asistencia *assistances = new Asistencia[2];
  assistances[0] = assistance1;
  assistances[1] = assistance2;
  uint cant = 2;
  str idClient = "999";

  Asistencia *result = findAssistances(assistances, cant, idClient);
  REQUIRE(result == nullptr);

  delete[] assistances;
}


/*INSCRIPTIONS*/

TEST_CASE("AddInscriptionAssistance adds an inscription to an empty array") {
  Inscripcion* inscriptions = new Inscripcion[1];
  Inscripcion inscription = {1, 1675267200};
  eAddInscriptionInAssistance result = addInscriptionAssistance(inscriptions, 1, inscription);

  REQUIRE(result == eAddInscriptionInAssistance::SuccessAddAssistance);
  REQUIRE(inscriptions[0].idCurso == inscription.idCurso);
  REQUIRE(inscriptions[0].fechaInscripcion == inscription.fechaInscripcion);
  delete [] inscriptions;
}

TEST_CASE("AddInscriptionAssistance adds an inscription to an array with elements") {
  Inscripcion* inscriptions = new Inscripcion[2];
  inscriptions[0] = {1, 1675267200};
  Inscripcion inscription = {2, 1675267800};
  eAddInscriptionInAssistance result = addInscriptionAssistance(inscriptions, 2, inscription);

  REQUIRE(result == eAddInscriptionInAssistance::SuccessAddAssistance);
  REQUIRE(inscriptions[1].idCurso == inscription.idCurso);
  REQUIRE(inscriptions[1].fechaInscripcion == inscription.fechaInscripcion);
  delete [] inscriptions;
}

TEST_CASE("Add Inscription to an empty array") {
  Inscripcion inscription = {1, 1675267200};
  Inscripcion *inscriptions = nullptr;
  eAddInscriptionInAssistance result = addInscriptionAssistance(inscriptions,12, inscription);

  REQUIRE(result == eAddInscriptionInAssistance::ErrorSpaceAssitance);
  delete [] inscriptions;
}
