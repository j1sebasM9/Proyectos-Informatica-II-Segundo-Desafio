#ifndef GESTIONAR_ARCHIVOS_H
#define GESTIONAR_ARCHIVOS_H

#include <fstream>
#include "ArregloDinamico.h"
#include "Equipo.h"

class GestionarArchivos {
private:
    // Funciones utilitarias internas (ocultas para el resto del programa)
    int aEntero(const char* str);
    char* copiarCadena(const char* origen);
    bool iguales(const char* a, const char* b);
    char* leerCampo(char*& cursor, char delimitador);
    int leerEntero(char*& cursor, char delimitador);

public:
    // Funciones principales (las que llamarás desde el main)
    void extraerEquipos(const char* ruta, ArregloDinamico<Equipo*>& listaEquipos);
    void extraerJugadores(const char* ruta, ArregloDinamico<Equipo*>& listaEquipos);
    void guardarJugadores(const char* ruta, ArregloDinamico<Equipo*>& listaEquipos);
};

#endif