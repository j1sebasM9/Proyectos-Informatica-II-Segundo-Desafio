#ifndef ARREGLO_DINAMICO_H
#define ARREGLO_DINAMICO_H

template <class T>
class ArregloDinamico {
private:
    T* elementos;  // Puntero principal
    int capacidad; // Tamaño total espacios (fijo en 48)
    int cantidad;  // Espacios ocupados actualmente

public:

    ArregloDinamico(int capacidad_fija = 48) {
        capacidad = capacidad_fija;
        cantidad = 0;
        elementos = new T[capacidad];
    }

    ~ArregloDinamico() {
        delete[] elementos;
    }

    void agregar(T e) {

        if (cantidad < capacidad) {
            elementos[cantidad] = e;
            cantidad++;
        }
    }

    T obtener(int indice) {
        return elementos[indice];
    }

    int getCantidad() {
        return cantidad;
    }
};

#endif