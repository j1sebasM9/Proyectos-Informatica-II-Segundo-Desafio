#ifndef JUGADOR_H
#define JUGADOR_H

#include "EstadisticasJugador.h"

class Jugador {
private:
    int numeroCamiseta;
    char* nombre;
    char* apellido;
    EstadisticasJugador estadisticas;

    // Utilidades privadas para manejo de memoria
    char* copiarCadena(const char* origen) const;
    char* generarTexto(const char* prefijo, int numero);

public:
    Jugador();               // Constructor vacío
    Jugador(int camiseta);    // Constructor de autogeneración

    // Regla de los 3: Manejo seguro de memoria dinámica
    Jugador(const Jugador& otro);
    Jugador& operator=(const Jugador& otro);
    ~Jugador();


    int getNumeroCamiseta() const     { return numeroCamiseta; }
    const char* getNombre() const     { return nombre; }
    const char* getApellido() const   { return apellido; }
    EstadisticasJugador& getEstadisticas() { return estadisticas; }



    //  Medición de memoria
    int getMemoriaBytes() const;
};

#endif
