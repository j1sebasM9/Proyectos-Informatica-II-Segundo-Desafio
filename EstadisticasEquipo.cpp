#include "EstadisticasEquipo.h"
#include <iostream>

// -------------------------------------------------------------
// UTILIDAD
// -------------------------------------------------------------
void EstadisticasEquipo::imprimir() const {
    // Usar "\n" en lugar de std::endl es más eficiente computacionalmente
    // porque no fuerza un vaciado (flush) innecesario del buffer de consola cada vez.
    std::cout << "--- Estadisticas ---\n"
              << "Partidos Jugados: " << getPartidosJugados() << "\n"
              << "Ganados: " << partidosGanados
              << " | Empatados: " << partidosEmpatados
              << " | Perdidos: " << partidosPerdidos << "\n"
              << "Goles a Favor: " << golesAFavor
              << " | En Contra: " << golesEnContra
              << " | Diferencia: " << getDiferenciaGoles() << "\n"
              << "Puntos Totales: " << getPuntos() << "\n"
              << "--------------------\n";
}