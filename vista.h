#ifndef VISTA_H
#define VISTA_H

#include "ArregloDinamico.h"
#include "Equipo.h"
#include "EtapaEliminatoria.h"
#include "Grupo.h"
#include "Partido.h"

class Vista {
private:


    // Clase interna para representar un goleador en el informe final
    class Goleador {
    public:
        const char* nombre;
        const char* apellido;
        const char* pais;
        int goles;

        Goleador() : nombre(nullptr), apellido(nullptr), pais(nullptr), goles(0) {}
    };

    // Utilidades de impresión
    void imprimirLinea(int longitud);
    void imprimirEncabezado(const char* titulo);

    // Utilidades de cálculo para el informe final
    Goleador* obtenerMayoresGoleadores(ArregloDinamico<Equipo*>& equipos, int cantidad);
    const char* obtenerConfederacionMayoritaria(Equipo* equipos[], int cantidad);

public:

    Vista();
    ~Vista();

    // Impresión individual de un partido
    void imprimirResultadoPartido(Partido& partido);


    void imprimirGoleadoresPartido(Partido& partido);

    // 1. Menu Principal
    void mostrarMenuPrincipal();

    // 2. Conformacion de los grupos
    void mostrarGruposConformados(Grupo grupos[12]);

    // 3. Resultados de la fase de grupos
    void mostrarResultadosFaseGrupos(Grupo grupos[12]);

    // 4. Tablas de clasificacion y cruces R16
    void mostrarTablasYTransicion(Grupo grupos[12], Partido partidosR16[16]);

    // 5. Fixture y resultados de etapas eliminatorias
    void mostrarResultadosEliminatorias(EtapaEliminatoria& eliminatoria);

    // 6. Informe de estadisticas finales
    void mostrarRanking(EtapaEliminatoria& eliminatoria);
    void mostrarMaximoGoleadorCampeon(EtapaEliminatoria& eliminatoria);
    void mostrarTresMayoresGoleadores(ArregloDinamico<Equipo*>& equipos);
    void mostrarEquipoMasGoles(ArregloDinamico<Equipo*>& equipos);
    void mostrarPresenciaConfederaciones(EtapaEliminatoria& eliminatoria);
    void mostrarResumenFinal(ArregloDinamico<Equipo*>& equipos, Grupo grupos[12],
                             EtapaEliminatoria& eliminatoria);

    // 7. Metricas de consumo de recursos
    void mostrarMetricas(int iteracionesAcumuladas, int iteracionesNuevas,
                         int memoriaConsumida);
};

#endif
