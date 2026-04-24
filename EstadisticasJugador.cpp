#include "EstadisticasJugador.h"

// Implementación del método para establecer todas las estadísticas de golpe
void EstadisticasJugador::establecer(int partidos, int g, int minutos, int asis,
                                     int amarillas, int rojas, int f) {
    partidosJugados = partidos;
    goles = g;
    minutosJugados = minutos;
    asistencias = asis;
    tarjetasAmarillas = amarillas;
    tarjetasRojas = rojas;
    faltas = f;
}

// Implementación del operador += (Suma las estadísticas de otro jugador)
EstadisticasJugador& EstadisticasJugador::operator+=(const EstadisticasJugador& otro) {
    partidosJugados += otro.partidosJugados;
    goles += otro.goles;
    minutosJugados += otro.minutosJugados;
    asistencias += otro.asistencias;
    tarjetasAmarillas += otro.tarjetasAmarillas;
    tarjetasRojas += otro.tarjetasRojas;
    faltas += otro.faltas;
    return *this;
}

// Implementación del operador == (Compara si dos estadísticas son idénticas)
bool EstadisticasJugador::operator==(const EstadisticasJugador& otro) const {
    return (partidosJugados == otro.partidosJugados &&
            goles == otro.goles &&
            minutosJugados == otro.minutosJugados &&
            asistencias == otro.asistencias &&
            tarjetasAmarillas == otro.tarjetasAmarillas &&
            tarjetasRojas == otro.tarjetasRojas &&
            faltas == otro.faltas);
}

// Implementación del método de impresión
void EstadisticasJugador::imprimir() const {
    std::cout << "Partidos Jugados: " << partidosJugados << "\n"
              << "Goles: " << goles << "\n"
              << "Minutos Jugados: " << minutosJugados << "\n"
              << "Asistencias: " << asistencias << "\n"
              << "Tarjetas Amarillas: " << tarjetasAmarillas << "\n"
              << "Tarjetas Rojas: " << tarjetasRojas << "\n"
              << "Faltas: " << faltas << "\n";
}