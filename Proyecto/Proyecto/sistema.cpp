#include "sistema.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

bool iguales(const char* a, const char* b) {
    if (!a || !b) return false;
    while (*a && *b) {
        if (tolower(static_cast<unsigned char>(*a)) != tolower(static_cast<unsigned char>(*b)))
            return false;
        ++a;
        ++b;
    }
    return *a == *b;
}


Sistema::Sistema() {
    capacidadAlojamientos = 100;
    cantidadAlojamientos = 0;
    alojamientos = new Alojamiento*[capacidadAlojamientos];
}
Sistema::~Sistema() {
    for (int i = 0; i < cantidadAlojamientos; i++) {
        delete alojamientos[i];
    }
    delete[] alojamientos;
}

void Sistema::cargarAlojamientos(const char* archivo){}

Alojamiento* Sistema::buscarAlojamiento(int codigo) const {
    for (int i = 0; i < cantidadAlojamientos; i++) {
        if (alojamientos[i]->getCodigoID() == codigo) {
            return alojamientos[i];
        }
    }
    return nullptr;
}

void Sistema::buscarAlojamientosDisponibles(const Fecha& inicio, int noches, const char* municipio, int costoMax, float puntuacionMin) const {
    bool encontrado = false;
    for (int i = 0; i < cantidadAlojamientos; i++) {
        Alojamiento* al = alojamientos[i];

        // Filtro por municipio
        if (!iguales(al->getMunicipio(), municipio))
            continue;

        // Filtro por costo máximo
        if (costoMax >= 0 && al->getPrecio() > costoMax)
            continue;

        // Filtro por puntuación mínima del anfitrión
        if (puntuacionMin >= 0 && al->getAnfitrion() && al->getAnfitrion()->getPuntuacion() < puntuacionMin)
            continue;

        // Verifica disponibilidad para el rango solicitado
        if (!al->estaDisponible(inicio, noches))
            continue;

        // Si pasó todos los filtros
        al->mostrarInfo();
        cout << "-------------------------" << endl;
        encontrado = true;
    }

    if (!encontrado) {
        cout << "No se encontraron alojamientos que cumplan con lo solicitado." << endl;
    }
}
