#include "GestionarArchivosCSV.h"



int GestionarArchivos::aEntero(const char* str) {
    int resultado = 0;
    int i = 0;
    while (str[i] == ' ') i++;
    while (str[i] >= '0' && str[i] <= '9') {
        resultado = resultado * 10 + (str[i] - '0');
        i++;
    }
    return resultado;
}

char* GestionarArchivos::copiarCadena(const char* origen) {
    int len = 0;
    while (origen[len] != '\0') len++;
    char* copia = new char[len + 1];
    for (int i = 0; i <= len; i++) copia[i] = origen[i];
    return copia;
}

bool GestionarArchivos::iguales(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}

char* GestionarArchivos::leerCampo(char*& cursor, char delimitador) {
    char* inicio = cursor;
    while (*cursor != delimitador && *cursor != '\0'
           && *cursor != '\n'    && *cursor != '\r') {
        cursor++;
    }
    if (*cursor == delimitador) {
        *cursor = '\0';
        cursor++;
    } else if (*cursor == '\r') {
        *cursor = '\0';
    }
    return copiarCadena(inicio);
}

int GestionarArchivos::leerEntero(char*& cursor, char delimitador) {
    char* campo = leerCampo(cursor, delimitador);
    int valor = aEntero(campo);
    delete[] campo;
    return valor;
}


void GestionarArchivos::extraerEquipos(const char* ruta, ArregloDinamico<Equipo*>& listaEquipos) {
    std::ifstream fin(ruta);
    if (!fin.is_open()) return;

    const int MAX_LINEA = 512;
    char linea[MAX_LINEA];

    fin.getline(linea, MAX_LINEA); // fila 1: título
    fin.getline(linea, MAX_LINEA); // fila 2: encabezados

    while (fin.getline(linea, MAX_LINEA)) {
        if (linea[0] == '\0' || linea[0] == '\r') continue;

        char* cursor = linea;

        int   ranking       = leerEntero(cursor, '\t');
        char* pais          = leerCampo (cursor, '\t');
        char* director      = leerCampo (cursor, '\t');
        char* federacion    = leerCampo (cursor, '\t');
        char* confederacion = leerCampo (cursor, '\t');
        int   golesFavor    = leerEntero (cursor, '\t');
        int   golesContra   = leerEntero (cursor, '\t');
        int   ganados       = leerEntero (cursor, '\t');
        int   empatados     = leerEntero (cursor, '\t');
        int   perdidos      = leerEntero (cursor, '\t');

        listaEquipos.agregar(new Equipo(
            ranking, pais, director, federacion, confederacion,
            golesFavor, golesContra, ganados, empatados, perdidos
            ));

        // Equipo copió internamente los char*  liberar los temporales
        delete[] pais;
        delete[] director;
        delete[] federacion;
        delete[] confederacion;
    }

    fin.close();
}

void GestionarArchivos::extraerJugadores(const char* ruta, ArregloDinamico<Equipo*>& listaEquipos) {
    std::ifstream fin(ruta);
    if (!fin.is_open()) return;

    const int MAX_LINEA = 512;
    char linea[MAX_LINEA];

    // Saltar encabezado
    fin.getline(linea, MAX_LINEA);

    while (fin.getline(linea, MAX_LINEA)) {
        if (linea[0] == '\0' || linea[0] == '\r') continue;

        char* cursor = linea;

        char* pais        = leerCampo (cursor, '\t');
        int   camiseta    = leerEntero (cursor, '\t');
        char* nombre      = leerCampo (cursor, '\t');
        char* apellido    = leerCampo (cursor, '\t');
        int   partidos    = leerEntero (cursor, '\t');
        int   goles       = leerEntero (cursor, '\t');
        int   minutos     = leerEntero (cursor, '\t');
        int   asistencias = leerEntero (cursor, '\t');
        int   amarillas   = leerEntero (cursor, '\t');
        int   rojas       = leerEntero (cursor, '\t');
        int   faltas      = leerEntero (cursor, '\t');

        // Buscar equipo por país y asignar jugador
        for (int i = 0; i < listaEquipos.getCantidad(); i++) {
            if (iguales(listaEquipos.obtener(i)->getPais(), pais)) {
                listaEquipos.obtener(i)->getJugador(camiseta - 1)->setEstadisticas(
                    partidos, goles, minutos, asistencias,
                    amarillas, rojas, faltas
                    );
                break;
            }
        }

        delete[] pais;
        delete[] nombre;
        delete[] apellido;
    }

    fin.close();
}

void GestionarArchivos::guardarJugadores(const char* ruta, ArregloDinamico<Equipo*>& listaEquipos) {
    std::ofstream fout(ruta);
    if (!fout.is_open()) return;

    fout << "pais\tcamiseta\tnombre\tapellido\tpartidos\tgoles\t"
         << "minutos\tasistencias\tamarillas\trojas\tfaltas\n";

    for (int i = 0; i < listaEquipos.getCantidad(); i++) {
        Equipo* equipo = listaEquipos.obtener(i);
        for (int j = 0; j < 26; j++) {
            Jugador* jugador = equipo->getJugador(j);
            fout << equipo->getPais()               << '\t'
                 << jugador->getNumeroCamiseta()    << '\t'
                 << jugador->getNombre()            << '\t'
                 << jugador->getApellido()          << '\t'
                 << jugador->getPartidosJugados()   << '\t'
                 << jugador->getGoles()             << '\t'
                 << jugador->getMinutosJugados()    << '\t'
                 << jugador->getAsistencias()       << '\t'
                 << jugador->getTarjetasAmarillas() << '\t'
                 << jugador->getTarjetasRojas()     << '\t'
                 << jugador->getFaltas()            << '\n';
        }
    }

    fout.close();
}