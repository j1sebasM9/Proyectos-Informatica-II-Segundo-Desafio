#ifndef EQUIPO_H
#define EQUIPO_H

#include "Jugador.h"
#include "EstadisticasEquipo.h"

class Equipo {
private:
    char* pais;
    char* directorTecnico;
    char* confederacion;
    char* federacion;
    int rankingFIFA;

    //Arreglo fijo de 26 ya que el cupo mundialista es invariable.
    Jugador plantilla[26];
    EstadisticasEquipo historial;

    char* copiarCadena(const char* origen) const;

public:
    Equipo();


    Equipo(const Equipo& otro);
    Equipo& operator=(const Equipo& otro);
    ~Equipo();

    void establecerDatosBasicos(const char* p_pais, const char* p_director,
                                const char* p_confed, const char* p_fed, int ranking);
    void repartirGolesHistoricos();


    const char* getPais() const             { return pais; }
    const char* getDirectorTecnico() const  { return directorTecnico; }
    const char* getConfederacion() const    { return confederacion; }
    const char* getFederacion() const       { return federacion; }
    int getRankingFIFA() const              { return rankingFIFA; }

    // Promedios para la Ecuación Matemática
    double getPromedioGolesFavor() const {
        int pj = historial.getPartidosJugados();
        return (pj == 0) ? 0.0 : (double)historial.getGolesAFavor() / pj;
    }

    double getPromedioGolesContra() const {
        int pj = historial.getPartidosJugados();
        return (pj == 0) ? 0.0 : (double)historial.getGolesEnContra() / pj;
    }

    // ACCESOS
    Jugador& getJugador(int indice)             { return plantilla[indice]; }
    const Jugador& getJugador(int indice) const { return plantilla[indice]; }
    int getNumJugadores() const                 { return 26; }

    EstadisticasEquipo& getEstadisticas()             { return historial; }
    const EstadisticasEquipo& getEstadisticas() const { return historial; }

    //inline
    bool coincidePais(const char* otroPais) const;
    bool operator==(const Equipo& otro) const { return coincidePais(otro.pais); }
    bool operator!=(const Equipo& otro) const { return !(*this == otro); }
    bool operator<(const Equipo& otro) const;

    //  Medición exacta de memoria
    int getMemoriaBytes() const;
};

#endif