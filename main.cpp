#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Torneo.h"
#include "Vista.h"

int main() {

    // Inicializar semilla aleatoria
    std::srand(std::time(nullptr));

    // Verificar existencia del archivo de datos
    const char* rutaEquipos = "selecciones_clasificadas_mundial.csv";
    std::ifstream checkEquipos(rutaEquipos);
    if (!checkEquipos.is_open()) {
        std::cout << "ERROR: No se encontro el archivo " << rutaEquipos << "\n";
        return 1;
    }
    checkEquipos.close();

    // Encabezado del sistema
    std::cout << "                 SIMULADOR MUNDIAL FIFA 2026                 \n";
    std::cout << "                                                             \n";
    std::cout << " Jesus Sebatian Mendoza & Danna Isabela Ochoa              \n";
    std::cout << " Lenguaje: C++                                               \n";
    std::cout << " Requisitos: Estructuras dinamicas, Templates, POO           \n";

    // Instancias principales del sistema
    Torneo mundialista;
    Vista  visor;

    // Carga inicial de datos
    std::cout << "\n[INICIO] Cargando datos iniciales del Mundial 2026...\n";
    mundialista.cargarDatos(rutaEquipos, nullptr);

    int opcion           = 0;
    int iteracionesAntes = 0;

    do {
        visor.mostrarMenuPrincipal();

        // Lectura segura de opcion — evita bucle infinito por entrada invalida
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            opcion = -1;
        }

        // Foto de iteraciones antes de ejecutar la funcionalidad
        iteracionesAntes = mundialista.getIteraciones();

        if (opcion == 1) {
            std::cout << "\n[INFO] Conformando grupos...\n";
            mundialista.conformarGrupos();
            visor.mostrarGruposConformados(mundialista.getGrupos());
            visor.mostrarMetricas(mundialista.getIteraciones(),
                                  mundialista.getIteraciones() - iteracionesAntes,
                                  mundialista.getMemoriaBytes());

        } else if (opcion == 2) {
            std::cout << "\n[INFO] Generando calendario y simulando fase de grupos...\n";
            mundialista.generarCalendarioFaseGrupos();
            mundialista.simularFaseGrupos();
            visor.mostrarResultadosFaseGrupos(mundialista.getGrupos());
            visor.mostrarMetricas(mundialista.getIteraciones(),
                                  mundialista.getIteraciones() - iteracionesAntes,
                                  mundialista.getMemoriaBytes());

        } else if (opcion == 3) {
            std::cout << "\n[INFO] Procesando clasificados y armando llaves...\n";
            mundialista.transicionR16();
            visor.mostrarTablasYTransicion(mundialista.getGrupos(),
                                           mundialista.getPartidosR16());
            visor.mostrarMetricas(mundialista.getIteraciones(),
                                  mundialista.getIteraciones() - iteracionesAntes,
                                  mundialista.getMemoriaBytes());

        } else if (opcion == 4) {
            std::cout << "\n[INFO] Simulando etapas eliminatorias...\n";
            mundialista.simularEtapasEliminatorias();
            visor.mostrarResultadosEliminatorias(mundialista.getEliminatoria());
            visor.mostrarMetricas(mundialista.getIteraciones(),
                                  mundialista.getIteraciones() - iteracionesAntes,
                                  mundialista.getMemoriaBytes());

        } else if (opcion == 5) {
            std::cout << "\n[RESUMEN] Generando informe de estadisticas finales...\n";
            visor.mostrarResumenFinal(mundialista.getEquipos(),
                                      mundialista.getGrupos(),
                                      mundialista.getEliminatoria());
            mundialista.guardarResultados();
            visor.mostrarMetricas(mundialista.getIteraciones(),
                                  mundialista.getIteraciones() - iteracionesAntes,
                                  mundialista.getMemoriaBytes());

        } else if (opcion == 6) {
            std::cout << "\n                 GRACIAS POR USAR EL SIMULADOR                 \n";

        } else {
            std::cout << "\n[ERROR] Opcion no valida. Intente nuevamente.\n";
        }

    } while (opcion != 6);

    return 0;
}
