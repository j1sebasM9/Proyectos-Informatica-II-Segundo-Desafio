#include "Vista.h"
#include <iostream>


// UTILIDADES MANUALES DE CADENAS Y FORMATO

// Calcula la longitud de una cadena (reemplaza strlen)
int longitudCadena(const char* str) {
    int len = 0;
    if (str) {
        while (str[len] != '\0') len++;
    }
    return len;
}

// Compara dos cadenas caracter a caracter (reemplaza strcmp)
bool compararCadenas(const char* str1, const char* str2) {
    if (!str1 || !str2) return false;
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) return false;
        i++;
    }
    return str1[i] == str2[i];
}

// Imprime texto alineado a la izquierda con ancho fijo (reemplaza setw+left)
void imprimirTextoAlineado(const char* texto, int anchoTotal) {
    int len = longitudCadena(texto);
    if (texto) std::cout << texto;
    for (int i = len; i < anchoTotal; i++) std::cout << " ";
}

// Imprime número alineado a la derecha con ancho fijo (reemplaza setw+right)
void imprimirNumeroAlineado(int numero, int anchoTotal) {
    int len = 1;
    int temp = numero;
    if (temp < 0) { len++; temp = -temp; }
    while (temp >= 10) { len++; temp /= 10; }
    for (int i = len; i < anchoTotal; i++) std::cout << " ";
    std::cout << numero;
}


// CONSTRUCTOR Y DESTRUCTOR

Vista::Vista()  {}
Vista::~Vista() {}


// UTILIDADES PRIVADAS DE IMPRESIÓN

// Imprime una línea horizontal de separación
void Vista::imprimirLinea(int longitud) {
    for (int i = 0; i < longitud; i++) std::cout << "=";
    std::cout << "\n";
}

// Imprime un encabezado con título centrado entre líneas
void Vista::imprimirEncabezado(const char* titulo) {
    std::cout << "\n";
    imprimirLinea(70);
    std::cout << "  " << titulo << "\n";
    imprimirLinea(70);
}


// IMPRESIÓN INDIVIDUAL DE PARTIDO

void Vista::imprimirResultadoPartido(Partido& part) {
    if (!part.estaJugado()) {
        std::cout << "Partido no jugado aun.\n";
        return;
    }

    // Datos logísticos del partido
    const char* fecha = part.getFecha();
    const char* hora  = part.getHora();
    const char* sede  = part.getSede();
    const char* arb0  = part.getArbitro(0);
    const char* arb1  = part.getArbitro(1);
    const char* arb2  = part.getArbitro(2);

    std::cout << "[" << (fecha ? fecha : "N/A") << " | "
              << (hora  ? hora  : "N/A") << " | "
              << "Arbitros: "
              << (arb0  ? arb0  : "N/A") << ", "
              << (arb1  ? arb1  : "N/A") << ", "
              << (arb2  ? arb2  : "N/A") << " | "
              << (sede  ? sede  : "N/A") << " | Posesion: "
              << part.getPosesionLocal() << "% - "
              << part.getPosesionVisitante() << "%]\n";

    // Resultado del partido
    Equipo* local     = part.getLocal();
    Equipo* visitante = part.getVisitante();

    std::cout << (local     && local->getPais()     ? local->getPais()     : "Local")
              << " " << part.getGolesLocal()
              << " - " << part.getGolesVisitante() << " "
              << (visitante && visitante->getPais() ? visitante->getPais() : "Visitante");

    if (part.getFueProrroga()) std::cout << " (Definido en Prorroga)";
    std::cout << "\n";
}


void Vista::imprimirGoleadoresPartido(Partido& part) {
    std::cout << "   -> Goles Local (Camisetas): ";
    if (part.getGolesLocal() == 0) std::cout << "Ninguno";
    for (int k = 0; k < part.getGolesLocal(); k++)
        std::cout << part.getCamisetasGolesLocal()[k] << " ";
    std::cout << "\n";

    std::cout << "   -> Goles Visita (Camisetas): ";
    if (part.getGolesVisitante() == 0) std::cout << "Ninguno";
    for (int k = 0; k < part.getGolesVisitante(); k++)
        std::cout << part.getCamisetasGolesVisitante()[k] << " ";
    std::cout << "\n\n";
}

// 1. MENU PRINCIPAL

void Vista::mostrarMenuPrincipal() {
    imprimirEncabezado("SIMULADOR COPA MUNDIAL 2026 - MENU PRINCIPAL");
    std::cout << " 1. Conformar grupos y mostrar\n";
    std::cout << " 2. Simular fase de grupos (Resultados y goleadores)\n";
    std::cout << " 3. Mostrar tablas de clasificacion y cruces R16\n";
    std::cout << " 4. Simular eliminatorias (Fixture R16 hasta Final)\n";
    std::cout << " 5. Mostrar informe de estadisticas finales\n";
    std::cout << " 6. Salir\n";
    std::cout << "----------------------------------------------------------------------\n";
    std::cout << " Ingrese una opcion: ";
}


// 2. CONFORMACION DE GRUPOS

void Vista::mostrarGruposConformados(Grupo grupos[12]) {
    imprimirEncabezado("CONFORMACION DE GRUPOS (EQUIPOS Y CONFEDERACIONES)");
    for (int i = 0; i < 12; i++) {
        std::cout << "\n[ GRUPO " << grupos[i].getNombre() << " ]\n";
        for (int j = 0; j < 4; j++) {
            Equipo* eq = grupos[i].getEquipoRegistrado(j);
            if (eq) {
                std::cout << " - ";
                imprimirTextoAlineado(eq->getPais(), 20);
                std::cout << " | Conf: " << eq->getConfederacion() << "\n";
            }
        }
    }
}


// 3. RESULTADOS DE LA FASE DE GRUPOS

void Vista::mostrarResultadosFaseGrupos(Grupo grupos[12]) {
    imprimirEncabezado("RESULTADOS DE LA FASE DE GRUPOS");
    for (int i = 0; i < 12; i++) {
        std::cout << "\n--- PARTIDOS GRUPO " << grupos[i].getNombre() << " ---\n";
        for (int p = 0; p < 6; p++) {
            Partido& part = grupos[i].getPartidoFaseGrupos(p);
            if (part.estaJugado()) {
                imprimirResultadoPartido(part);
                imprimirGoleadoresPartido(part);

            }
        }
    }
}


// 4. TABLAS DE CLASIFICACION Y CRUCES R16

void Vista::mostrarTablasYTransicion(Grupo grupos[12], Partido partidosR16[16]) {
    imprimirEncabezado("TABLAS DE CLASIFICACION FINALES");

    for (int i = 0; i < 12; i++) {
        std::cout << "\n[ GRUPO " << grupos[i].getNombre() << " ]\n";
        std::cout << "Pos    Equipo                 Pts   PJ   GF   GC  DIF\n";
        std::cout << "------------------------------------------------------\n";

        for (int j = 0; j < 4; j++) {
            Equipo* eq = grupos[i].getEquipoTabla(j);
            if (eq) {
                int pts = grupos[i].getPuntosTabla(j);
                int gf  = grupos[i].getGolesFavorTabla(j);
                int dif = grupos[i].getDiferenciaGolesTabla(j);
                int gc  = gf - dif;

                std::cout << " ";
                imprimirNumeroAlineado(j + 1, 2);
                std::cout << ".   ";
                imprimirTextoAlineado(eq->getPais(), 20);
                imprimirNumeroAlineado(pts, 5);
                imprimirNumeroAlineado(3,   5);
                imprimirNumeroAlineado(gf,  5);
                imprimirNumeroAlineado(gc,  5);
                imprimirNumeroAlineado(dif, 5);
                std::cout << "\n";
            }
        }
    }

    // Cruces de dieciseisavos
    imprimirEncabezado("CRUCES DE DIECISEISAVOS DE FINAL (R32)");
    for (int i = 0; i < 16; i++) {
        std::cout << " Llave ";
        imprimirNumeroAlineado(i + 1, 2);
        std::cout << ": ";
        if (partidosR16[i].getLocal() && partidosR16[i].getVisitante()) {
            std::cout << partidosR16[i].getLocal()->getPais()
            << " vs "
            << partidosR16[i].getVisitante()->getPais() << "\n";
        } else {
            std::cout << "Por definir...\n";
        }
    }
}

// 5. FIXTURE Y RESULTADOS DE ETAPAS ELIMINATORIAS

void Vista::mostrarResultadosEliminatorias(EtapaEliminatoria& eliminatoria) {
    imprimirEncabezado("FIXTURE Y RESULTADOS - ETAPAS ELIMINATORIAS");
    // Dieciseisavos
    std::cout << "\n--- DIECISEISAVOS DE FINAL (R32) ---\n";
    Partido* r16 = eliminatoria.getPartidosR16();
    for (int i = 0; i < 16; i++) {
        if (r16[i].estaJugado()) {
            imprimirResultadoPartido(r16[i]);
            imprimirGoleadoresPartido(r16[i]);
        }
    }

    // Octavos
    std::cout << "\n--- OCTAVOS DE FINAL (R16) ---\n";
    Partido* r8 = eliminatoria.getPartidosR8();
    for (int i = 0; i < 8; i++) {
        if (r8[i].estaJugado()) {
            imprimirResultadoPartido(r8[i]);
            imprimirGoleadoresPartido(r8[i]);
        }
    }

    // Cuartos
    std::cout << "\n--- CUARTOS DE FINAL (R8) ---\n";
    Partido* r4 = eliminatoria.getPartidosR4();
    for (int i = 0; i < 4; i++) {
        if (r4[i].estaJugado()) {
            imprimirResultadoPartido(r4[i]);
            imprimirGoleadoresPartido(r4[i]);
        }
    }

    // Semifinales
    std::cout << "\n--- SEMIFINALES (R4) ---\n";
    Partido* r2 = eliminatoria.getPartidosR2();
    for (int i = 0; i < 2; i++) {
        if (r2[i].estaJugado()) {
            imprimirResultadoPartido(r2[i]);
            imprimirGoleadoresPartido(r2[i]);
        }
    }

    // Tercer puesto
    std::cout << "\n--- PARTIDO POR EL TERCER PUESTO ---\n";
    if (eliminatoria.getPartidoTercerPuesto().estaJugado()) {
        imprimirResultadoPartido(eliminatoria.getPartidoTercerPuesto());
        imprimirGoleadoresPartido(eliminatoria.getPartidoTercerPuesto());
    }

    // Gran final
    std::cout << "\n--- GRAN FINAL ---\n";
    if (eliminatoria.getPartidoFinal().estaJugado()) {
        imprimirResultadoPartido(eliminatoria.getPartidoFinal());
        imprimirGoleadoresPartido(eliminatoria.getPartidoFinal());
    }
}


// 6. INFORME DE ESTADISTICAS FINALES

// Ranking de los 4 primeros lugares
void Vista::mostrarRanking(EtapaEliminatoria& eliminatoria) {
    std::cout << "\n--- 1. RANKING DE LOS 4 PRIMEROS ---\n";
    Equipo* campeon  = eliminatoria.getCampeon();
    Equipo* sub      = eliminatoria.getSubcampeon();
    Equipo* tercero  = eliminatoria.getTercerLugar();
    Equipo* cuarto   = eliminatoria.getCuartoLugar();

    if (campeon)  std::cout << " 1. CAMPEON:      " << campeon->getPais()  << "\n";
    if (sub)      std::cout << " 2. SUBCAMPEON:   " << sub->getPais()      << "\n";
    if (tercero)  std::cout << " 3. TERCER LUGAR: " << tercero->getPais()  << "\n";
    if (cuarto)   std::cout << " 4. CUARTO LUGAR: " << cuarto->getPais()   << "\n";
}

// Maximo goleador del equipo campeon
void Vista::mostrarMaximoGoleadorCampeon(EtapaEliminatoria& eliminatoria) {
    std::cout << "\n--- 2. MAXIMO GOLEADOR DEL CAMPEON ---\n";
    Equipo* campeon = eliminatoria.getCampeon();
    if (!campeon) return;

    Jugador* mejor  = nullptr;
    int maxGoles    = -1;

    for (int i = 0; i < 26; i++) {
        Jugador& j = campeon->getJugador(i);
        if (j.getEstadisticas().getGoles() > maxGoles) {
            maxGoles = j.getEstadisticas().getGoles();
            mejor    = &j;
        }
    }

    if (mejor && maxGoles > 0) {
        std::cout << " " << mejor->getNombre() << " " << mejor->getApellido()
        << " - " << maxGoles << " goles"
        << " (Camiseta: " << mejor->getNumeroCamiseta() << ")\n";
    } else {
        std::cout << " Sin goleadores registrados.\n";
    }
}

// Calcula los N mayores goleadores del torneo
Vista::Goleador* Vista::obtenerMayoresGoleadores(ArregloDinamico<Equipo*>& equipos, int cantidad) {
    Goleador* goleadores = new Goleador[cantidad];

    for (int e = 0; e < equipos.getCantidad(); e++) {
        Equipo* eq = equipos[e];
        for (int j = 0; j < 26; j++) {
            Jugador& jug = eq->getJugador(j);
            int goles    = jug.getEstadisticas().getGoles();
            if (goles > 0) {
                for (int k = 0; k < cantidad; k++) {
                    if (goles > goleadores[k].goles) {
                        // Desplazar hacia abajo para insertar
                        for (int m = cantidad - 1; m > k; m--)
                            goleadores[m] = goleadores[m - 1];
                        goleadores[k].nombre   = jug.getNombre();
                        goleadores[k].apellido = jug.getApellido();
                        goleadores[k].pais     = eq->getPais();
                        goleadores[k].goles    = goles;
                        break;
                    }
                }
            }
        }
    }
    return goleadores;
}

// Top 3 goleadores del mundial
void Vista::mostrarTresMayoresGoleadores(ArregloDinamico<Equipo*>& equipos) {
    std::cout << "\n--- 3. TOP 3 GOLEADORES DEL MUNDIAL ---\n";
    Goleador* top3 = obtenerMayoresGoleadores(equipos, 3);
    for (int i = 0; i < 3; i++) {
        if (top3[i].goles > 0) {
            std::cout << " " << (i + 1) << ". "
                      << top3[i].nombre   << " "
                      << top3[i].apellido << " ("
                      << top3[i].pais     << ") - "
                      << top3[i].goles    << " goles\n";
        }
    }
    delete[] top3;
}

// Equipo con mas goles historicos
void Vista::mostrarEquipoMasGoles(ArregloDinamico<Equipo*>& equipos) {
    std::cout << "\n--- 4. EQUIPO CON MAS GOLES HISTORICOS ---\n";
    Equipo* mejor = nullptr;
    int maxGoles  = -1;

    for (int i = 0; i < equipos.getCantidad(); i++) {
        Equipo* eq = equipos[i];
        if (eq->getEstadisticas().getGolesAFavor() > maxGoles) {
            maxGoles = eq->getEstadisticas().getGolesAFavor();
            mejor    = eq;
        }
    }
    if (mejor)
        std::cout << " " << mejor->getPais() << " con " << maxGoles << " goles totales.\n";
}

// Determina la confederacion con mayor presencia en una lista de equipos
const char* Vista::obtenerConfederacionMayoritaria(Equipo* equipos[], int cantidad) {
    const char* confederaciones[] = {"UEFA", "CONMEBOL", "CAF", "AFC", "CONCACAF", "OFC"};
    int contadores[6] = {0};

    for (int i = 0; i < cantidad; i++) {
        if (equipos[i] && equipos[i]->getConfederacion()) {
            for (int j = 0; j < 6; j++) {
                if (compararCadenas(equipos[i]->getConfederacion(), confederaciones[j])) {
                    contadores[j]++;
                    break;
                }
            }
        }
    }

    int maxIdx = 0;
    for (int i = 1; i < 6; i++)
        if (contadores[i] > contadores[maxIdx]) maxIdx = i;

    return confederaciones[maxIdx];
}

// Confederacion dominante por etapa eliminatoria
void Vista::mostrarPresenciaConfederaciones(EtapaEliminatoria& eliminatoria) {
    std::cout << "\n--- 5. CONFEDERACION CON MAYOR PRESENCIA ---\n";

    // Recolectamos equipos de R16, R8 y R4 (32 + 16 + 8 = 56 cupos)
    Equipo* equiposFasesFinales[56];
    int indice = 0;

    Partido* pR16 = eliminatoria.getPartidosR16();
    for (int i = 0; i < 16; i++) {
        equiposFasesFinales[indice++] = pR16[i].getLocal();
        equiposFasesFinales[indice++] = pR16[i].getVisitante();
    }

    Partido* pR8 = eliminatoria.getPartidosR8();
    for (int i = 0; i < 8; i++) {
        equiposFasesFinales[indice++] = pR8[i].getLocal();
        equiposFasesFinales[indice++] = pR8[i].getVisitante();
    }

    Partido* pR4 = eliminatoria.getPartidosR4();
    for (int i = 0; i < 4; i++) {
        equiposFasesFinales[indice++] = pR4[i].getLocal();
        equiposFasesFinales[indice++] = pR4[i].getVisitante();
    }

    const char* confedGanadora = obtenerConfederacionMayoritaria(equiposFasesFinales, 56);
    std::cout << " " << confedGanadora << " fue la confederacion dominante en las eliminatorias.\n";
}

// Resumen completo del torneo
void Vista::mostrarResumenFinal(ArregloDinamico<Equipo*>& equipos, Grupo grupos[12],
                                EtapaEliminatoria& eliminatoria) {
    imprimirEncabezado("INFORME DE ESTADISTICAS FINALES DEL TORNEO");
    mostrarRanking(eliminatoria);
    mostrarMaximoGoleadorCampeon(eliminatoria);
    mostrarTresMayoresGoleadores(equipos);
    mostrarEquipoMasGoles(equipos);
    mostrarPresenciaConfederaciones(eliminatoria);
}


// 7. METRICAS DE CONSUMO DE RECURSOS

void Vista::mostrarMetricas(int iteracionesAcumuladas, int iteracionesNuevas,
                            int memoriaConsumida) {
    std::cout << "\n";
    imprimirLinea(70);
    std::cout << "  METRICAS DE EJECUCION\n";
    imprimirLinea(70);

    std::cout << " - Iteraciones de este proceso: " << iteracionesNuevas     << "\n";
    std::cout << " - Iteraciones acumuladas:      " << iteracionesAcumuladas << "\n";

    // Conversion manual a KB para evitar uso de setprecision
    int kbEntero  = memoriaConsumida / 1024;
    int kbDecimal = ((memoriaConsumida % 1024) * 100) / 1024;

    std::cout << " - Memoria total del sistema:   " << memoriaConsumida
              << " bytes (" << kbEntero << ".";
    if (kbDecimal < 10) std::cout << "0";
    std::cout << kbDecimal << " KB)\n";

    imprimirLinea(70);
    std::cout << "\n";
}
