#include "EtapaEliminatoria.h"



EtapaEliminatoria::EtapaEliminatoria():
    campeon(nullptr),
    subcampeon(nullptr),
    tercerLugar(nullptr),
    cuartoLugar(nullptr) {

    totalIteraciones = 0;
    for (int i = 0; i < 32; i++) {
        clasificados[i] = nullptr;
        totalIteraciones++;
    }
}

void EtapaEliminatoria::configurarClasificados(Equipo* equipos[32]) {
    for (int i = 0; i < 32; i++) {
        clasificados[i] = equipos[i];
        totalIteraciones++;
    }

    for (int i = 0; i < 16; i++) {
        dieciseisavos[i].configurarEquipos(clasificados[i * 2], clasificados[i * 2 + 1], true);
        dieciseisavos[i].configurarLogistica("10/07/2026", "00:00", "nombreSede",
                                             "codArbitro1", "codArbitro2", "codArbitro3");
        totalIteraciones++;
    }
}

void EtapaEliminatoria::simularDieciseisavos() {
    for (int i = 0; i < 16; i++) {
        dieciseisavos[i].simular();
        totalIteraciones++;
    }

    for (int i = 0; i < 8; i++) {
        Equipo* ganador1 = dieciseisavos[i * 2].getGanador();
        Equipo* ganador2 = dieciseisavos[i * 2 + 1].getGanador();

        octavos[i].configurarEquipos(ganador1, ganador2, true);
        octavos[i].configurarLogistica("10/07/2026", "00:00", "nombreSede",
                                       "codArbitro1", "codArbitro2", "codArbitro3");
        totalIteraciones++;
    }
}

void EtapaEliminatoria::simularOctavos() {
    for (int i = 0; i < 8; i++) {
        octavos[i].simular();
        totalIteraciones++;
    }

    for (int i = 0; i < 4; i++) {
        Equipo* ganador1 = octavos[i * 2].getGanador();
        Equipo* ganador2 = octavos[i * 2 + 1].getGanador();

        cuartos[i].configurarEquipos(ganador1, ganador2, true);
        cuartos[i].configurarLogistica("10/07/2026", "00:00", "nombreSede",
                                       "codArbitro1", "codArbitro2", "codArbitro3");
        totalIteraciones++;
    }
}

void EtapaEliminatoria::simularCuartos() {
    for (int i = 0; i < 4; i++) {
        cuartos[i].simular();
        totalIteraciones++;
    }

    for (int i = 0; i < 2; i++) {
        Equipo* ganador1 = cuartos[i * 2].getGanador();
        Equipo* ganador2 = cuartos[i * 2 + 1].getGanador();

        semifinales[i].configurarEquipos(ganador1, ganador2, true);
        semifinales[i].configurarLogistica("10/07/2026", "00:00", "nombreSede",
                                           "codArbitro1", "codArbitro2", "codArbitro3");
        totalIteraciones++;
    }
}

void EtapaEliminatoria::simularSemifinales() {
    for (int i = 0; i < 2; i++) {
        semifinales[i].simular();
        totalIteraciones++;
    }

    Equipo* ganadorSemi1 = semifinales[0].getGanador();
    Equipo* perdedorSemi1 = (ganadorSemi1 == semifinales[0].getLocal()) ?
                                semifinales[0].getVisitante() : semifinales[0].getLocal();

    Equipo* ganadorSemi2 = semifinales[1].getGanador();
    Equipo* perdedorSemi2 = (ganadorSemi2 == semifinales[1].getLocal()) ?
                                semifinales[1].getVisitante() : semifinales[1].getLocal();

    partidoFinal.configurarEquipos(ganadorSemi1, ganadorSemi2, true);
    partidoFinal.configurarLogistica("10/07/2026", "00:00", "nombreSede",
                                     "codArbitro1", "codArbitro2", "codArbitro3");

    partidoTercerPuesto.configurarEquipos(perdedorSemi1, perdedorSemi2, true);
    partidoTercerPuesto.configurarLogistica("10/07/2026", "00:00", "nombreSede",
                                            "codArbitro1", "codArbitro2", "codArbitro3");
}

void EtapaEliminatoria::simularFinales() {
    partidoTercerPuesto.simular();
    tercerLugar = partidoTercerPuesto.getGanador();
    cuartoLugar = (tercerLugar == partidoTercerPuesto.getLocal()) ?
                      partidoTercerPuesto.getVisitante() : partidoTercerPuesto.getLocal();

    partidoFinal.simular();
    campeon = partidoFinal.getGanador();
    subcampeon = (campeon == partidoFinal.getLocal()) ?
                     partidoFinal.getVisitante() : partidoFinal.getLocal();
}

void EtapaEliminatoria::simularTodaLaEtapa() {
    simularDieciseisavos();
    simularOctavos();
    simularCuartos();
    simularSemifinales();
    simularFinales();
}

Equipo* EtapaEliminatoria::getCampeon() const { return campeon; }
Equipo* EtapaEliminatoria::getSubcampeon() const { return subcampeon; }
Equipo* EtapaEliminatoria::getTercerLugar() const { return tercerLugar; }
Equipo* EtapaEliminatoria::getCuartoLugar() const { return cuartoLugar; }

// Medición de memoria
int EtapaEliminatoria::getMemoriaBytes()  {
    // Memoria base: arreglos de Partido y punteros
    int mem = sizeof(*this);

    // Sumamos la memoria dinámica extra que puedan tener los partidos internamente
    for (int i = 0; i < 16; i++) {
        mem += (dieciseisavos[i].getMemoriaBytes() - sizeof(Partido));
        totalIteraciones++;
    }
    for (int i = 0; i < 8; i++) {
        mem += (octavos[i].getMemoriaBytes() - sizeof(Partido));
        totalIteraciones++;
    }
    for (int i = 0; i < 4; i++) {
        mem += (cuartos[i].getMemoriaBytes() - sizeof(Partido));
        totalIteraciones++;
    }
    for (int i = 0; i < 2; i++) {
        mem += (semifinales[i].getMemoriaBytes() - sizeof(Partido));
        totalIteraciones++;
    }

    mem += (partidoTercerPuesto.getMemoriaBytes() - sizeof(Partido));
    mem += (partidoFinal.getMemoriaBytes() - sizeof(Partido));


    return mem;
}