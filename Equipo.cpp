#include "Equipo.h"


char* Equipo::copiarCadena(const char* origen) const {
    if (!origen) return nullptr;
    int len = 0;
    while (origen[len] != '\0') len++;
    char* copia = new char[len + 1];
    for (int i = 0; i <= len; i++) copia[i] = origen[i];
    return copia;
}


Equipo::Equipo() : pais(nullptr), directorTecnico(nullptr),
    confederacion(nullptr), federacion(nullptr), rankingFIFA(0) {
    // Inicializamos los 26 jugadores con nombres genéricos ("Jugador 1", etc.)
    for (int i = 0; i < 26; i++) {
        plantilla[i] = Jugador(i + 1);
    }
}

Equipo::Equipo(const Equipo& otro) : rankingFIFA(otro.rankingFIFA), historial(otro.historial) {
    pais            = copiarCadena(otro.pais);
    directorTecnico = copiarCadena(otro.directorTecnico);
    confederacion   = copiarCadena(otro.confederacion);
    federacion      = copiarCadena(otro.federacion);
    for (int i = 0; i < 26; i++) {
        plantilla[i] = otro.plantilla[i];
    }
}

Equipo& Equipo::operator=(const Equipo& otro) {
    if (this != &otro) {
        rankingFIFA = otro.rankingFIFA;
        historial   = otro.historial;

        delete[] pais;
        delete[] directorTecnico;
        delete[] confederacion;
        delete[] federacion;

        pais            = copiarCadena(otro.pais);
        directorTecnico = copiarCadena(otro.directorTecnico);
        confederacion   = copiarCadena(otro.confederacion);
        federacion      = copiarCadena(otro.federacion);

        for (int i = 0; i < 26; i++) {
            plantilla[i] = otro.plantilla[i];
        }
    }
    return *this;
}

Equipo::~Equipo() {
    delete[] pais;
    delete[] directorTecnico;
    delete[] confederacion;
    delete[] federacion;
}


void Equipo::establecerDatosBasicos(const char* p_pais, const char* p_director,
                                    const char* p_confed, const char* p_fed, int ranking) {
    delete[] pais; delete[] directorTecnico; delete[] confederacion; delete[] federacion;

    pais            = copiarCadena(p_pais);
    directorTecnico = copiarCadena(p_director);
    confederacion   = copiarCadena(p_confed);
    federacion      = copiarCadena(p_fed);
    rankingFIFA     = ranking;
}

void Equipo::repartirGolesHistoricos() {
    int total = historial.getGolesAFavor();
    if (total <= 0) return;

    int porJugador = total / 26;
    int sobrantes  = total % 26;

    for (int i = 0; i < 26; i++) {
        int golesAsignar = porJugador + (sobrantes > 0 ? 1 : 0);
        if (sobrantes > 0) sobrantes--;

        for (int g = 0; g < golesAsignar; g++) {
            plantilla[i].getEstadisticas().sumarGol();
        }
    }
}


bool Equipo::coincidePais(const char* otroPais) const {
    if (!pais || !otroPais) return false;
    int i = 0;
    while (pais[i] != '\0' && otroPais[i] != '\0') {
        if (pais[i] != otroPais[i]) return false;
        i++;
    }
    return pais[i] == '\0' && otroPais[i] == '\0';
}

bool Equipo::operator<(const Equipo& otro) const {
    // Criterio de ordenación: Puntos -> Diferencia de Goles
    int misPuntos = historial.getPuntos();
    int otrosPuntos = otro.historial.getPuntos();
    if (misPuntos != otrosPuntos) return misPuntos < otrosPuntos;
    return historial.getDiferenciaGoles() < otro.historial.getDiferenciaGoles();
}

//Memoria
int Equipo::getMemoriaBytes() const {
    int mem = sizeof(*this); // Incluye punteros, ranking, historial y el tamaño BASE de los 26 jugadores

    // Sumar el contenido real de los char* (memoria dinámica del montón)
    if (pais) { int l=0; while(pais[l]) l++; mem += l+1; }
    if (directorTecnico) { int l=0; while(directorTecnico[l]) l++; mem += l+1; }
    if (confederacion)   { int l=0; while(confederacion[l]) l++; mem += l+1; }
    if (federacion)      { int l=0; while(federacion[l]) l++; mem += l+1; }

    // Sumar solo la memoria dinámica extra de los jugadores (nombres/apellidos)
    for (int i = 0; i < 26; i++) {
        mem += (plantilla[i].getMemoriaBytes() - sizeof(Jugador));
    }

    return mem;
}