#include <iostream>
#include "Sistema.h"
#include "consumorecursos.h"

using namespace std;

int main() {
    Sistema sistema;

    sistema.cargarDatos();

    bool continuar = true;
    while (continuar) {
        consumorecursos::contarIteracion();
        cout << "\n=== Sistema  ===\n";
        cout << "1. Ingresar al sistema\n";
        cout << "2. Salir\n";
        cout << "Seleccione una opción: ";
        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            sistema.Ingreso();
        } else if (opcion == 2) {
            continuar = false;
        } else {
            cout << "Opción no válida.\n";
        }
    }

    sistema.guardarDatos();
    consumorecursos::mostrar();

    return 0;
}
