#ifndef GRUPO_H
#define GRUPO_H

#include "Partido.h"

class Grupo {
private:
    char nombreGrupo;
    Equipo* equipos[4];
    int numEquiposActuales;

    Partido partidos[6];

    // Tabla de posiciones (arreglo simple)
    Equipo* tabla[4];
    int puntos[4];
    int golesFavor[4];
    int golesContra[4];

    // Métodos internos
    void inicializarTabla();
    void actualizarTablaConResultado(Partido& p);
    void ordenarTabla();

public:
    Grupo();
    ~Grupo();

    void setNombre(char letra);
    char getNombre() const;

    bool agregarEquipo(Equipo* e);
    void configurarEmparejamientos();
    Partido& getPartidoFaseGrupos(int index);

    void simularFaseGrupos();

    // GETTERS
    Equipo* getPrimerLugar() const;
    Equipo* getSegundoLugar() const;
    Equipo* getTercerLugar() const;

    int getPuntosTercerLugar() const;
    int getDiferenciaGolesTercerLugar() const;
    int getGolesFavorTercerLugar() const;



    Equipo* getEquipoRegistrado(int index) const {
        if (index >= 0 && index < numEquiposActuales) return equipos[index];
        return nullptr;
    }

    Equipo* getEquipoTabla(int index) const { return tabla[index]; }
    int getPuntosTabla(int index) const { return puntos[index]; }
    int getDiferenciaGolesTabla(int index) const { return golesFavor[index] - golesContra[index]; }
    int getGolesFavorTabla(int index) const { return golesFavor[index]; }
};

#endif