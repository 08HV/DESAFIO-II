#include "consumorecursos.h"

int consumorecursos::iteraciones = 0;
size_t consumorecursos::totalmemoria = 0;

void consumorecursos::contarIteracion(int cantidad) {
    iteraciones += cantidad;
}

void consumorecursos::sumarMemoria(size_t bytes) {
    totalmemoria += bytes;
}

void consumorecursos::mostrar() {
    cout << "Consumo de recursos " << endl;
    cout << "Cantidas de iteraciones:  " << iteraciones << endl;
    cout << "Total de memoria consumida:  " << totalmemoria << " bytes" << endl;
}
