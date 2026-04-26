#ifndef TORNEO_H
#define TORNEO_H

#include "ArregloDinamico.h"
#include "Equipo.h"
#include "Grupo.h"
#include "GestionarArchivosCSV.h"
#include "EtapaEliminatoria.h"

// Por si Partido no se incluye automáticamente a través de los otros headers
class Partido;

class Torneo {
private:
    ArregloDinamico<Equipo*> equipos;
    ArregloDinamico<Equipo*> bombos[4];

    Grupo grupos[12];
    Equipo* clasificados[32];

    EtapaEliminatoria eliminatoria;
    GestionarArchivosCSV gestor;

    // Métodos privados
    void ordenarEquiposPorRanking();
    bool sePuedeAgregarAlGrupo(Grupo& grupo, Equipo* equipoNuevo);

    // Medición de iteraciones
    int totalIteraciones;

public:
    Torneo();
    virtual ~Torneo();

    void cargarDatos(const char* rutaEquipos, const char* rutaJugadores);
    void conformarGrupos();
    void generarCalendarioFaseGrupos();
    void simularFaseGrupos();
    void transicionR16();
    void simularEtapasEliminatorias();
    void guardarResultados();

    // GETTERS PARA VISUALIZACIÓN
    ArregloDinamico<Equipo*>& getEquipos() { return equipos; }
    Grupo* getGrupos() { return grupos; }
    EtapaEliminatoria& getEliminatoria() { return eliminatoria; }


    Partido* getPartidosR16() {
        return eliminatoria.getPartidosR16();
    }



    int getIteraciones() { return totalIteraciones; }
    void reiniciarIteraciones() { totalIteraciones = 0; }

    // Medición de memoria
    int getMemoriaBytes() ;
};

#endif