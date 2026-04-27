#ifndef PARTIDO_H
#define PARTIDO_H

#include "Equipo.h"

class Partido {
private:
    // Punteros a los equipos (Partido NO crea a los equipos, solo los referencia)
    Equipo* local;
    Equipo* visitante;

    // Cadenas dinámicas propias del partido
    char* fecha;
    char* hora;
    char* sede;
    char* arbitros[3];

    int golesLocal;
    int golesVisitante;
    float posesionLocal;
    float posesionVisitante;

    // Arreglos de punteros para los 11 titulares elegidos para este partido
    Jugador* alineacionLocal[11];
    Jugador* alineacionVisitante[11];

    bool jugado;
    bool esEliminatoria;
    bool fueProrroga;

    //Arreglos estáticos para guardar las camisetas de los goleadores
    int camisetasGolesLocal[50];
    int camisetasGolesVisitante[50];

    char* copiarCadena(const char* origen);

    // Utilidades privadas
    bool probabilidad(float porcentaje);
    void seleccionarAlineacion(Equipo* equipo, Jugador* alineacion[11]);
    void simularEventosJugador(Jugador* jugador, int minutosJugados);




    float potEntera(float base, int exp);
    float raizQuinta(float x);


    int totalIteraciones;

public:
    Partido();


    Partido(const Partido& otro);
    Partido& operator=(const Partido& otro);
    ~Partido();

    void configurarEquipos(Equipo* equipoLocal, Equipo* equipoVisitante, bool eliminatoria);
    void configurarLogistica(const char* f, const char* h, const char* s,
                             const char* arb1, const char* arb2, const char* arb3);

    void simular();


    bool estaJugado() const                { return jugado; }
    Equipo* getLocal() const               { return local; }
    Equipo* getVisitante() const           { return visitante; }
    int getGolesLocal() const              { return golesLocal; }
    int getGolesVisitante() const          { return golesVisitante; }
    Equipo* getGanador() const;


    const int* getCamisetasGolesLocal() const { return camisetasGolesLocal; }
    const int* getCamisetasGolesVisitante() const { return camisetasGolesVisitante; }


    // Getters de Logística
    const char* getFecha() const { return fecha; }
    const char* getHora() const { return hora; }
    const char* getSede() const { return sede; }
    const char* getArbitro(int idx) const { return (idx >= 0 && idx < 3) ? arbitros[idx] : nullptr; }

    // Getters de detalles del juego
    float getPosesionLocal() const { return posesionLocal; }
    float getPosesionVisitante() const { return posesionVisitante; }
    bool getFueProrroga() const { return fueProrroga; }





     int getIteraciones() { return totalIteraciones; }
     void reiniciarIteraciones() { totalIteraciones = 0; }

    //  Medición de Memoria
    int getMemoriaBytes() ;
};

#endif