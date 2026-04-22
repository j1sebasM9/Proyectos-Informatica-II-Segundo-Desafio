#ifndef ESTADISTICASEQUIPO_H
#define ESTADISTICASEQUIPO_H

class EstadisticasEquipo {
private:
    int golesAFavor;
    int golesEnContra;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;

public:
    // ELEGANCIA: Constructor con lista de inicialización
    EstadisticasEquipo() : golesAFavor(0), golesEnContra(0), partidosGanados(0),
        partidosEmpatados(0), partidosPerdidos(0) {}

    // Carga inicial INLINE
    void establecer(int favor, int contra, int ganados, int empatados, int perdidos) {
        golesAFavor = favor;
        golesEnContra = contra;
        partidosGanados = ganados;
        partidosEmpatados = empatados;
        partidosPerdidos = perdidos;
    }

    // Cálculos matemáticos al vuelo INLINE
    int getPuntos() const          { return (partidosGanados * 3) + partidosEmpatados; } // Empate * 1 es redundante
    int getDiferenciaGoles() const { return golesAFavor - golesEnContra; }
    int getPartidosJugados() const { return partidosGanados + partidosEmpatados + partidosPerdidos; }

    // Getters básicos INLINE
    int getGolesAFavor() const       { return golesAFavor; }
    int getGolesEnContra() const     { return golesEnContra; }
    int getPartidosGanados() const   { return partidosGanados; }
    int getPartidosEmpatados() const { return partidosEmpatados; }
    int getPartidosPerdidos() const  { return partidosPerdidos; }

    // Modificadores para el simulador INLINE
    void sumarVictoria()             { partidosGanados++; }
    void sumarEmpate()               { partidosEmpatados++; }
    void sumarDerrota()              { partidosPerdidos++; }
    void sumarGolFavor()             { golesAFavor++; }
    void sumarGolEnContra()          { golesEnContra++; }

    // REQUISITO V: Medición de RAM (5 enteros = 20 bytes fijos)
    int getMemoriaBytes() const      { return sizeof(*this); }

    // Utilidad (Se queda en el .cpp para no importar <iostream> en todos lados)
    void imprimir() const;
};

#endif