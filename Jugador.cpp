#include "Jugador.h"



char* Jugador::copiarCadena(const char* origen) const {
    if (!origen) return nullptr;
    int len = 0;
    while (origen[len] != '\0') len++;
    char* copia = new char[len + 1];
    for (int i = 0; i <= len; i++) copia[i] = origen[i];
    return copia;
}

char* Jugador::generarTexto(const char* prefijo, int numero) {
    int lenPref = 0;
    while (prefijo[lenPref] != '\0') lenPref++;

    // Determinamos si el número tiene 1 o 2 dígitos (máximo 26 jugadores)
    int lenNum = (numero >= 10) ? 2 : 1;
    char* res = new char[lenPref + lenNum + 1];

    for (int i = 0; i < lenPref; i++) res[i] = prefijo[i];

    if (numero >= 10) {
        res[lenPref]     = (numero / 10) + '0';
        res[lenPref + 1] = (numero % 10) + '0';
        res[lenPref + 2] = '\0';
    } else {
        res[lenPref]     = numero + '0';
        res[lenPref + 1] = '\0';
    }
    return res;
}

// Constructores y Destructor

Jugador::Jugador() : numeroCamiseta(0), nombre(nullptr), apellido(nullptr) {}

Jugador::Jugador(int camiseta) : numeroCamiseta(camiseta) {
    // Genera automáticamente "nombreX" y "apellidoX"
    nombre   = generarTexto("nombre",   camiseta);
    apellido = generarTexto("apellido", camiseta);
}

Jugador::Jugador(const Jugador& otro) : numeroCamiseta(otro.numeroCamiseta), estadisticas(otro.estadisticas) {
    nombre   = copiarCadena(otro.nombre);
    apellido = copiarCadena(otro.apellido);
}

Jugador& Jugador::operator=(const Jugador& otro) {
    if (this != &otro) {
        numeroCamiseta = otro.numeroCamiseta;
        estadisticas   = otro.estadisticas;
        delete[] nombre;
        delete[] apellido;
        nombre   = copiarCadena(otro.nombre);
        apellido = copiarCadena(otro.apellido);
    }
    return *this;
}

Jugador::~Jugador() {
    delete[] nombre;
    delete[] apellido;
}

//Setters

void Jugador::setNombre(const char* n) {
    delete[] nombre;
    nombre = copiarCadena(n);
}

void Jugador::setApellido(const char* a) {
    delete[] apellido;
    apellido = copiarCadena(a);
}

//consumo de memoria

int Jugador::getMemoriaBytes() const {
    int memoria = sizeof(*this);
    if (nombre) {
        int len = 0; while (nombre[len] != '\0') len++;
        memoria += (len + 1);
    }
    if (apellido) {
        int len = 0; while (apellido[len] != '\0') len++;
        memoria += (len + 1);
    }
    return memoria;
}