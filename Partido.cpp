#include "Partido.h"
#include <iostream>
#include <cstdlib>



//Ecuación
 float Partido::potEntera(float base, int exp) {
    float res = 1.0;
    for (int i = 0; i < exp; i++) {
        totalIteraciones++;
        res *= base;
    }
    return res;
}

//Aproximación N-R
 float Partido::raizQuinta(float x) {
    if (x <= 0.0001) return 0.0;
    float y = 1.0;
    for (int i = 0; i < 15; i++) {
        totalIteraciones++;
        y = y - (potEntera(y, 5) - x) / (5.0 * potEntera(y, 4));
    }
    return y;
}

//Utilidad de memoria
char* Partido::copiarCadena(const char* origen) {
    if (!origen) return nullptr;
    int len = 0;
    while (origen[len] != '\0') {
        Partido::totalIteraciones++;
        len++;
    }
    char* copia = new char[len + 1];
    for (int i = 0; i <= len; i++) {
        Partido::totalIteraciones++;
        copia[i] = origen[i];
    }
    return copia;
}

//Constructores
Partido::Partido() : local(nullptr),
    visitante(nullptr),
    fecha(nullptr),
    hora(nullptr),
    sede(nullptr),
    golesLocal(0),
    golesVisitante(0),
    posesionLocal(0.0),
    posesionVisitante(0.0),
    jugado(false),
    esEliminatoria(false),
    fueProrroga(false) {

    totalIteraciones = 0;
    for (int i = 0; i < 3; i++) {
        totalIteraciones++;
        arbitros[i] = nullptr;
    }
    for (int i = 0; i < 11; i++) {
        totalIteraciones++;
        alineacionLocal[i] = nullptr;
        alineacionVisitante[i] = nullptr;
    }
    // Inicializar camisetas
    for (int i = 0; i < 50; i++) {
        totalIteraciones++;
        camisetasGolesLocal[i] = 0;
        camisetasGolesVisitante[i] = 0;
    }
}

Partido::Partido(const Partido& otro) : local(otro.local),
    visitante(otro.visitante),
    golesLocal(otro.golesLocal),
    golesVisitante(otro.golesVisitante),
    posesionLocal(otro.posesionLocal),
    posesionVisitante(otro.posesionVisitante),
    jugado(otro.jugado),
    esEliminatoria(otro.esEliminatoria),
    fueProrroga(otro.fueProrroga) {

    fecha = copiarCadena(otro.fecha);
    hora  = copiarCadena(otro.hora);
    sede  = copiarCadena(otro.sede);

    for (int i = 0; i < 3; i++) {
        totalIteraciones++;
        arbitros[i] = copiarCadena(otro.arbitros[i]);
    }
    for (int i = 0; i < 11; i++) {
        totalIteraciones++;
        alineacionLocal[i] = otro.alineacionLocal[i];
        alineacionVisitante[i] = otro.alineacionVisitante[i];
    }
    for (int i = 0; i < 50; i++) {
        totalIteraciones++;
        camisetasGolesLocal[i] = otro.camisetasGolesLocal[i];
        camisetasGolesVisitante[i] = otro.camisetasGolesVisitante[i];
    }
}

Partido& Partido::operator=(const Partido& otro) {
    if (this != &otro) {

        local = otro.local;
        visitante = otro.visitante;
        golesLocal = otro.golesLocal;
        golesVisitante = otro.golesVisitante;
        posesionLocal = otro.posesionLocal;
        posesionVisitante = otro.posesionVisitante;
        jugado = otro.jugado;
        esEliminatoria = otro.esEliminatoria;
        fueProrroga = otro.fueProrroga;

        delete[] fecha; delete[] hora; delete[] sede;
        for(int i=0; i<3; i++) {
            totalIteraciones++;
            delete[] arbitros[i];
        }

        fecha = copiarCadena(otro.fecha);
        hora  = copiarCadena(otro.hora);
        sede  = copiarCadena(otro.sede);
        for (int i = 0; i < 3; i++) {
            totalIteraciones++;
            arbitros[i] = copiarCadena(otro.arbitros[i]);
        }
        for (int i = 0; i < 11; i++) {
            totalIteraciones++;
            alineacionLocal[i] = otro.alineacionLocal[i];
            alineacionVisitante[i] = otro.alineacionVisitante[i];
        }
        for (int i = 0; i < 50; i++) {
            totalIteraciones++;
            camisetasGolesLocal[i] = otro.camisetasGolesLocal[i];
            camisetasGolesVisitante[i] = otro.camisetasGolesVisitante[i];
        }
    }
    return *this;
}

Partido::~Partido() {
    delete[] fecha;
    delete[] hora;
    delete[] sede;
    for (int i = 0; i < 3; i++) {
        totalIteraciones++;
        delete[] arbitros[i];
    }
}

//motor

void Partido::configurarEquipos(Equipo* equipoLocal, Equipo* equipoVisitante, bool eliminatoria) {
    local = equipoLocal;
    visitante = equipoVisitante;
    esEliminatoria = eliminatoria;
}

void Partido::configurarLogistica(const char* f, const char* h, const char* s,
                                  const char* arb1, const char* arb2, const char* arb3) {
    delete[] fecha; delete[] hora; delete[] sede;

    for(int i=0; i<3; i++) {
        totalIteraciones++;
        delete[] arbitros[i];
    }
    fecha = copiarCadena(f);
    hora = copiarCadena(h);
    sede = copiarCadena(s);
    arbitros[0] = copiarCadena(arb1);
    arbitros[1] = copiarCadena(arb2);
    arbitros[2] = copiarCadena(arb3);
}

bool Partido::probabilidad(float porcentaje)  {
    float randomVal = (std::rand() % 10000) / 100.0;
    return randomVal < porcentaje;
}

void Partido::seleccionarAlineacion(Equipo* equipo, Jugador* alineacion[11]) {
    int seleccionados[11];
    int contador = 0;
    while(contador < 11) {
        totalIteraciones++;
        int r = std::rand() % 26;
        bool repetido = false;
        for(int k = 0; k < contador; k++) {
            totalIteraciones++;
            if(seleccionados[k] == r) repetido = true;
        }
        if(!repetido) {
            seleccionados[contador] = r;
            alineacion[contador] = &(equipo->getJugador(r));
            contador++;
        }
    }
}

void Partido::simularEventosJugador(Jugador* jugador, int minutos) {
    jugador->getEstadisticas().sumarMinutos(minutos);

    if (probabilidad(6.0)) {
        jugador->getEstadisticas().sumarAmarilla();
        if (probabilidad(1.15)) {
            jugador->getEstadisticas().sumarAmarilla();
            jugador->getEstadisticas().sumarRoja();
        }
    }

    if (probabilidad(13.0)) {
        jugador->getEstadisticas().sumarFalta();
        if (probabilidad(2.75)) {
            jugador->getEstadisticas().sumarFalta();
            if (probabilidad(0.7)) jugador->getEstadisticas().sumarFalta();
        }
    }
}

void Partido::simular() {
    if (jugado || !local || !visitante) return;

    //Crear plantilla de jugadores
    seleccionarAlineacion(local, alineacionLocal);
    seleccionarAlineacion(visitante, alineacionVisitante);

    //Posesión del balón
    int rankLocal = local->getRankingFIFA();
    int rankVisitante = visitante->getRankingFIFA();
    posesionLocal = ((float)rankVisitante / (rankLocal + rankVisitante)) * 100.0;
    posesionVisitante = 100.0 - posesionLocal;

    //Ecuación de goles
    float mu = 1.35;
    float gfLocal = local->getPromedioGolesFavor();
    float gcLocal = local->getPromedioGolesContra();
    float gfVisitante = visitante->getPromedioGolesFavor();
    float gcVisitante = visitante->getPromedioGolesContra();

    float baseAlphaLoc = gfLocal / mu;
    float baseBetaLoc = gcVisitante / mu;
    float lambdaLocal = mu * raizQuinta(potEntera(baseAlphaLoc, 3)) * raizQuinta(potEntera(baseBetaLoc, 2));

    float baseAlphaVis = gfVisitante / mu;
    float baseBetaVis = gcLocal / mu;
    float lambdaVisitante = mu * raizQuinta(potEntera(baseAlphaVis, 3)) * raizQuinta(potEntera(baseBetaVis, 2));


    //Redondeo de goles
    int golesEsperadosLocal = (int)lambdaLocal;
    float restoLocal = lambdaLocal - golesEsperadosLocal;

    if (probabilidad(restoLocal * 100.0)) {
        golesEsperadosLocal++;
    }

    int golesEsperadosVisitante = (int)lambdaVisitante;
    float restoVisitante = lambdaVisitante - golesEsperadosVisitante;

    if (probabilidad(restoVisitante * 100.0)) {
        golesEsperadosVisitante++;
    }

    // Asignación de goles Local y guardado de camisetas
    golesLocal = 0;
    while (golesLocal < golesEsperadosLocal) {
        totalIteraciones++;
        for (int i = 0; i < 11 && golesLocal < golesEsperadosLocal; i++) {
            totalIteraciones++;
            if (probabilidad(4.0)) {
                alineacionLocal[i]->getEstadisticas().sumarGol();
                if (golesLocal < 50) camisetasGolesLocal[golesLocal] = alineacionLocal[i]->getNumeroCamiseta();
                golesLocal++;
            }
        }
    }

    // Asignación de goles Visitante y guardado de camisetas
    golesVisitante = 0;
    while (golesVisitante < golesEsperadosVisitante) {
        totalIteraciones++;
        for (int i = 0; i < 11 && golesVisitante < golesEsperadosVisitante; i++) {
            totalIteraciones++;
            if (probabilidad(4.0)) {
                alineacionVisitante[i]->getEstadisticas().sumarGol();
                if (golesVisitante < 50) camisetasGolesVisitante[golesVisitante] = alineacionVisitante[i]->getNumeroCamiseta();
                golesVisitante++;
            }
        }
    }

    // Prórroga
    int minutosPartido = 90;
    if (esEliminatoria && golesLocal == golesVisitante) {
        fueProrroga = true;
        minutosPartido = 120;
        if (probabilidad(posesionLocal)) {
            int idx = std::rand() % 11;
            alineacionLocal[idx]->getEstadisticas().sumarGol();
            if (golesLocal < 50) camisetasGolesLocal[golesLocal] = alineacionLocal[idx]->getNumeroCamiseta();
            golesLocal++;
        } else {
            int idx = std::rand() % 11;
            alineacionVisitante[idx]->getEstadisticas().sumarGol();
            if (golesVisitante < 50) camisetasGolesVisitante[golesVisitante] = alineacionVisitante[idx]->getNumeroCamiseta();
            golesVisitante++;
        }
    }


    //Actualización base de datos

    for (int i = 0; i < 11; i++) {
        totalIteraciones++;
        simularEventosJugador(alineacionLocal[i], minutosPartido);
        simularEventosJugador(alineacionVisitante[i], minutosPartido);
    }

    for(int i = 0; i < golesLocal; i++) {
        totalIteraciones++;
        local->getEstadisticas().sumarGolFavor();
        visitante->getEstadisticas().sumarGolEnContra();
    }
    for(int i = 0; i < golesVisitante; i++) {
        totalIteraciones++;
        visitante->getEstadisticas().sumarGolFavor();
        local->getEstadisticas().sumarGolEnContra();
    }

    if (golesLocal > golesVisitante) {
        local->getEstadisticas().sumarVictoria();
        visitante->getEstadisticas().sumarDerrota();
    } else if (golesVisitante > golesLocal) {
        visitante->getEstadisticas().sumarVictoria();
        local->getEstadisticas().sumarDerrota();
    } else {
        local->getEstadisticas().sumarEmpate();
        visitante->getEstadisticas().sumarEmpate();
    }

    jugado = true;
}

Equipo* Partido::getGanador() const {
    if (!jugado) return nullptr;
    if (golesLocal > golesVisitante) return local;
    if (golesVisitante > golesLocal) return visitante;
    return nullptr;
}

int Partido::getMemoriaBytes()  {
    int mem = sizeof(*this);
    if (fecha) { int l=0; while(fecha[l]) { totalIteraciones++; l++; } mem += l+1; }
    if (hora)  { int l=0; while(hora[l]) { totalIteraciones++; l++; } mem += l+1; }
    if (sede)  { int l=0; while(sede[l]) { totalIteraciones++; l++; } mem += l+1; }
    for(int i=0; i<3; i++) {
        totalIteraciones++;
        if (arbitros[i]) { int l=0; while(arbitros[i][l]) { totalIteraciones++; l++; } mem += l+1; }
    }
    return mem;
}