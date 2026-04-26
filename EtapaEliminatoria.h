#ifndef ETAPAELIMINATORIA_H
#define ETAPAELIMINATORIA_H

#include "Equipo.h"
#include "Partido.h"

class EtapaEliminatoria {
private:
    Equipo* clasificados[32];

    Partido dieciseisavos[16];
    Partido octavos[8];
    Partido cuartos[4];
    Partido semifinales[2];
    Partido partidoTercerPuesto;
    Partido partidoFinal;

    Equipo* campeon;
    Equipo* subcampeon;
    Equipo* tercerLugar;
    Equipo* cuartoLugar;
    int totalIteraciones;

public:
    EtapaEliminatoria();

    void configurarClasificados(Equipo* equipos[32]);

    void simularDieciseisavos();
    void simularOctavos();
    void simularCuartos();
    void simularSemifinales();
    void simularFinales();
    void simularTodaLaEtapa();

    Equipo* getCampeon() const;
    Equipo* getSubcampeon() const;
    Equipo* getTercerLugar() const;
    Equipo* getCuartoLugar() const;


    Partido* getPartidosR16() { return dieciseisavos; }
    Partido* getPartidosR8() { return octavos; }
    Partido* getPartidosR4() { return cuartos; }
    Partido* getPartidosR2() { return semifinales; }
    Partido& getPartidoTercerPuesto() { return partidoTercerPuesto; }
    Partido& getPartidoFinal() { return partidoFinal; }



     int getIteraciones() { return totalIteraciones; }
     void reiniciarIteraciones() { totalIteraciones = 0; }


    // Medición de memoria
    int getMemoriaBytes();
};

#endif