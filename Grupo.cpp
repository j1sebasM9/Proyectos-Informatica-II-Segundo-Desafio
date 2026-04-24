#include "Grupo.h"
#include <cstdlib>

Grupo::Grupo() : nombreGrupo('X'), numEquiposActuales(0) {
    for (int i = 0; i < 4; i++) {
        equipos[i] = nullptr;
        tabla[i] = nullptr;
        puntos[i] = 0;
        golesFavor[i] = 0;
        golesContra[i] = 0;
    }
}

Grupo::~Grupo() {}

void Grupo::setNombre(char letra) {
    nombreGrupo = letra;
}

char Grupo::getNombre() const {
    return nombreGrupo;
}

bool Grupo::agregarEquipo(Equipo* e) {
    if (numEquiposActuales < 4) {
        equipos[numEquiposActuales] = e;
        numEquiposActuales++;
        return true;
    }
    return false;
}

void Grupo::configurarEmparejamientos() {
    if (numEquiposActuales < 4) return;

    partidos[0].configurarEquipos(equipos[0], equipos[1], false);
    partidos[1].configurarEquipos(equipos[2], equipos[3], false);

    partidos[2].configurarEquipos(equipos[0], equipos[2], false);
    partidos[3].configurarEquipos(equipos[1], equipos[3], false);

    partidos[4].configurarEquipos(equipos[0], equipos[3], false);
    partidos[5].configurarEquipos(equipos[1], equipos[2], false);
}

Partido& Grupo::getPartidoFaseGrupos(int index) {
    return partidos[index];
}

void Grupo::inicializarTabla() {
    for (int i = 0; i < 4; i++) {
        tabla[i] = equipos[i];
        puntos[i] = 0;
        golesFavor[i] = 0;
        golesContra[i] = 0;
    }
}

void Grupo::actualizarTablaConResultado(Partido& p) {
    if (!p.estaJugado()) return;

    Equipo* local = p.getLocal();
    Equipo* visitante = p.getVisitante();
    int gLocal = p.getGolesLocal();
    int gVisitante = p.getGolesVisitante();

    int idxLocal = -1, idxVisitante = -1;
    for (int i = 0; i < 4; i++) {
        if (tabla[i] == local) idxLocal = i;
        if (tabla[i] == visitante) idxVisitante = i;
        if (idxLocal != -1 && idxVisitante != -1) break;  // ← Optimización
    }

    golesFavor[idxLocal] += gLocal;
    golesContra[idxLocal] += gVisitante;

    golesFavor[idxVisitante] += gVisitante;
    golesContra[idxVisitante] += gLocal;

    if (gLocal > gVisitante) {
        puntos[idxLocal] += 3;
    } else if (gVisitante > gLocal) {
        puntos[idxVisitante] += 3;
    } else {
        puntos[idxLocal] += 1;
        puntos[idxVisitante] += 1;
    }
}

void Grupo::ordenarTabla() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            int difJ = golesFavor[j] - golesContra[j];
            int difJ1 = golesFavor[j+1] - golesContra[j+1];

            bool intercambiar = false;

            if (puntos[j] < puntos[j+1]) {
                intercambiar = true;
            } else if (puntos[j] == puntos[j+1]) {
                if (difJ < difJ1) {
                    intercambiar = true;
                } else if (difJ == difJ1) {
                    if (golesFavor[j] < golesFavor[j+1]) {
                        intercambiar = true;
                    }
                }
            }

            if (intercambiar) {
                // Intercambiar
                Equipo* tempE = tabla[j];
                tabla[j] = tabla[j+1];
                tabla[j+1] = tempE;

                int tempP = puntos[j];
                puntos[j] = puntos[j+1];
                puntos[j+1] = tempP;

                int tempGF = golesFavor[j];
                golesFavor[j] = golesFavor[j+1];
                golesFavor[j+1] = tempGF;

                int tempGC = golesContra[j];
                golesContra[j] = golesContra[j+1];
                golesContra[j+1] = tempGC;
            }
        }
    }
}

void Grupo::simularFaseGrupos() {
    if (numEquiposActuales < 4) return;

    inicializarTabla();
    for (int i = 0; i < 6; i++) {
        partidos[i].simular();
        actualizarTablaConResultado(partidos[i]);
    }
    ordenarTabla();
}

Equipo* Grupo::getPrimerLugar() const {
    return tabla[0];
}

Equipo* Grupo::getSegundoLugar() const {
    return tabla[1];
}

Equipo* Grupo::getTercerLugar() const {
    return tabla[2];
}

int Grupo::getPuntosTercerLugar() const {
    return puntos[2];
}

int Grupo::getDiferenciaGolesTercerLugar() const {
    return golesFavor[2] - golesContra[2];
}

int Grupo::getGolesFavorTercerLugar() const {
    return golesFavor[2];
}