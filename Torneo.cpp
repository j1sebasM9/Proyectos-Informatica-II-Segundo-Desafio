#include "Torneo.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

Torneo::Torneo() {
    for (int i = 0; i < 32; i++) {
        clasificados[i] = nullptr;
    }
}

Torneo::~Torneo() {}

void Torneo::cargarDatos(const char* rutaEquipos, const char* rutaJugadores) {
    std::cout << "\n[1/6] Cargando base de datos FIFA..." << std::endl;
    gestor.extraerEquipos(rutaEquipos, equipos);

    for (int i = 0; i < equipos.getCantidad(); i++) {
        equipos.obtener(i)->repartirGolesHistoricos();
    }
    std::cout << "-> " << equipos.getCantidad() << " equipos listos para el mundial." << std::endl;
}

void Torneo::ordenarEquiposPorRanking() {
    int n = equipos.getCantidad();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (equipos.obtener(j)->getRankingFIFA() > equipos.obtener(j + 1)->getRankingFIFA()) {
                Equipo* temp = equipos.obtener(j);
                equipos.modificar(j, equipos.obtener(j + 1));
                equipos.modificar(j + 1, temp);
            }
        }
    }
}

bool Torneo::sePuedeAgregarAlGrupo(Grupo& grupo, Equipo* equipoNuevo) {
    int contadorUEFA = 0;
    const char* confedNueva = equipoNuevo->getConfederacion();

    for (int i = 0; i < 4; i++) {
        Equipo* eqExistente = grupo.getEquipoRegistrado(i);
        if (eqExistente != nullptr) {
            const char* confedExistente = eqExistente->getConfederacion();

            if (gestor.iguales(confedExistente, "UEFA") && gestor.iguales(confedNueva, "UEFA")) {
                contadorUEFA++;
                if (contadorUEFA >= 2) return false;
            }
            else if (gestor.iguales(confedExistente, confedNueva)) {
                return false;
            }
        }
    }
    return true;
}

void Torneo::conformarGrupos() {
    if (equipos.getCantidad() < 48) return;

    std::cout << "[2/6] Realizando sorteo oficial (Bombos 1-4)..." << std::endl;

    bool exito = false;

    while (!exito) {
        // Limpiar grupos
        for (int i = 0; i < 12; i++) {
            grupos[i].vaciar();
            grupos[i].setNombre('A' + i);
        }

        // Limpiar bombos
        for (int b = 0; b < 4; b++) {
            bombos[b].vaciar();
        }

        ordenarEquiposPorRanking();

        // Distribuir equipos en bombos
        int bActual = 0;

        for (int i = 0; i < 48; i++) {
            Equipo* eq = equipos.obtener(i);

            if (eq->coincidePais("EE. UU.")) {
                bombos[0].agregar(eq);
                continue;
            }

            if (bombos[bActual].getCantidad() == 12) {
                bActual++;
            }

            bombos[bActual].agregar(eq);
        }

        exito = true;

        // Asignar equipos a grupos
        for (int b = 0; b < 4 && exito; b++) {
            for (int g = 0; g < 12 && exito; g++) {
                bool asignado = false;
                int intentos = 0;

                while (!asignado && bombos[b].getCantidad() > 0 && intentos < 500) {
                    int rnd = std::rand() % bombos[b].getCantidad();
                    Equipo* candidato = bombos[b].obtener(rnd);

                    if (sePuedeAgregarAlGrupo(grupos[g], candidato)) {
                        grupos[g].agregarEquipo(candidato);
                        bombos[b].eliminar(rnd);
                        asignado = true;
                    }

                    intentos++;
                }

                if (!asignado) {
                    exito = false;
                }
            }
        }
    }

    std::cout << "-> Sorteo finalizado. Grupos A-L conformados correctamente." << std::endl;
}

void Torneo::generarCalendarioFaseGrupos() {
    std::cout << "[3/6] Programando calendario (Limite: 4 partidos/dia)..." << std::endl;

    int diaTorneo = 1;
    int partidosHoy = 0;

    for (int jornada = 0; jornada < 3; jornada++) {
        for (int g = 0; g < 12; g++) {
            grupos[g].configurarEmparejamientos();

            for (int p = 0; p < 2; p++) {
                int idPartido = (jornada * 2) + p;
                Partido& part = grupos[g].getPartidoFaseGrupos(idPartido);

                int dia = 20 + (diaTorneo - 1);
                int mes = 6;

                while (dia > 30) {
                    dia -= 30;
                    mes++;
                }

                char fechaStr[30];
                std::sprintf(fechaStr, "%02d/%02d/2026", dia, mes);

                part.configurarLogistica( fechaStr, "00:00","nombreSede","codArbitro1", "codArbitro2","codArbitro3"  );

                partidosHoy++;

                if (partidosHoy >= 4) {
                    partidosHoy = 0;
                    diaTorneo++;
                }
            }
        }
    }
    std::cout << "-> Calendario listo. Duracion fase grupos: " << diaTorneo << " dias." << std::endl;
}

void Torneo::simularFaseGrupos() {
    std::cout << "[4/6] Simulando 72 encuentros de fase de grupos..." << std::endl;
    for (int i = 0; i < 12; i++) {
        grupos[i].simularFaseGrupos();
    }
}

void Torneo::transicionR16() {
    std::cout << "[5/6] Analizando tablas para Dieciseisavos de Final..." << std::endl;

    int totalClasificados = 0;

    // 1. Guardar los primeros y segundos de cada grupo
    for (int g = 0; g < 12; g++) {
        clasificados[totalClasificados++] = grupos[g].getPrimerLugar();
        clasificados[totalClasificados++] = grupos[g].getSegundoLugar();
    }


    Equipo* tercerosE[12];
    int tercerosPts[12];
    int tercerosDg[12];
    int tercerosGf[12];

    for (int g = 0; g < 12; g++) {
        tercerosE[g]   = grupos[g].getTercerLugar();
        tercerosPts[g] = grupos[g].getPuntosTercerLugar();
        tercerosDg[g]  = grupos[g].getDiferenciaGolesTercerLugar();
        tercerosGf[g]  = grupos[g].getGolesFavorTercerLugar();
    }

    // 2. Ordenar a los mejores terceros (Método Burbuja)
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11 - i; j++) {
            bool swap = false;

            // Criterios de desempate
            if (tercerosPts[j] < tercerosPts[j+1]) {
                swap = true;
            } else if (tercerosPts[j] == tercerosPts[j+1]) {
                if (tercerosDg[j] < tercerosDg[j+1]) {
                    swap = true;
                } else if (tercerosDg[j] == tercerosDg[j+1] && tercerosGf[j] < tercerosGf[j+1]) {
                    swap = true;
                }
            }

            // Si hay que cambiar, intercambiamos en todos los arreglos a la vez
            if (swap) {
                Equipo* auxE = tercerosE[j];
                tercerosE[j] = tercerosE[j+1];
                tercerosE[j+1] = auxE;

                int auxPts = tercerosPts[j];
                tercerosPts[j] = tercerosPts[j+1];
                tercerosPts[j+1] = auxPts;

                int auxDg = tercerosDg[j];
                tercerosDg[j] = tercerosDg[j+1];
                tercerosDg[j+1] = auxDg;

                int auxGf = tercerosGf[j];
                tercerosGf[j] = tercerosGf[j+1];
                tercerosGf[j+1] = auxGf;
            }
        }
    }

    // 3. Agregar a los 8 mejores terceros al arreglo final
    for (int i = 0; i < 8; i++) {
        clasificados[totalClasificados++] = tercerosE[i];
    }

    // 4. Configurar los partidos de la eliminatoria para que la Opción 3 los pueda mostrar
    eliminatoria.configurarClasificados(clasificados);

    std::cout << "-> Cruces de eliminacion directa definidos." << std::endl;
}

void Torneo::simularEtapasEliminatorias() {
    std::cout << "[6/6] Iniciando Fase Eliminatoria (32 equipos)..." << std::endl;
    // La configuración ya se hizo en transicionR16(), solo falta simular
    eliminatoria.simularTodaLaEtapa();
}

void Torneo::guardarResultados() {
    std::cout << "\n[GUARDANDO] Exportando estadisticas de jugadores por equipo...\n";
    gestor.guardarJugadores(equipos);
    std::cout << "-> Archivos de jugadores guardados exitosamente.\n";
}
