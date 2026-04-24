#ifndef ESTADISTICASJUGADOR_H
#define ESTADISTICASJUGADOR_H

#include <iostream>

class EstadisticasJugador {
private:
    int partidosJugados;
    int goles;
    int minutosJugados;
    int asistencias;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;

public:
    // Constructor por defecto
    EstadisticasJugador() : partidosJugados(0), goles(0), minutosJugados(0),
        asistencias(0), tarjetasAmarillas(0), tarjetasRojas(0), faltas(0) {}

    // Constructor de copia
    EstadisticasJugador(const EstadisticasJugador& otro)
        : partidosJugados(otro.partidosJugados), goles(otro.goles),
        minutosJugados(otro.minutosJugados), asistencias(otro.asistencias),
        tarjetasAmarillas(otro.tarjetasAmarillas), tarjetasRojas(otro.tarjetasRojas),
        faltas(otro.faltas) {}


    int getPartidosJugados()   const { return partidosJugados; }
    int getGoles()             const { return goles; }
    int getMinutosJugados()    const { return minutosJugados; }
    int getAsistencias()       const { return asistencias; }
    int getTarjetasAmarillas() const { return tarjetasAmarillas; }
    int getTarjetasRojas()     const { return tarjetasRojas; }
    int getFaltas()            const { return faltas; }


    void sumarPartido()        { partidosJugados++; }
    void sumarGol()            { goles++; }
    void sumarMinutos(int min) { minutosJugados += min; }
    void sumarAsistencia()     { asistencias++; }
    void sumarAmarilla()       { tarjetasAmarillas++; }
    void sumarRoja()           { tarjetasRojas++; }
    void sumarFalta()          { faltas++; }

    // Limpiar estadísticas
    void reset() {
        partidosJugados = goles = minutosJugados = asistencias = 0;
        tarjetasAmarillas = tarjetasRojas = faltas = 0;
    }

    //  Medición de memoria
    int getMemoriaBytes() const { return sizeof(*this); }


    void establecer(int partidos, int goles, int minutos, int asistencias,
                    int amarillas, int rojas, int faltas);

    // Operador +=
    EstadisticasJugador& operator+=(const EstadisticasJugador& otro);

    // Operador == (para comparaciones)
    bool operator==(const EstadisticasJugador& otro) const;

    // Impresión
    void imprimir() const;
};

#endif