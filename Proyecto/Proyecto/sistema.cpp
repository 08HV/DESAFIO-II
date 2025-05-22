#include "sistema.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

bool iguales(const string& a, const string& b) {
    if (a.length() != b.length()) return false;
    for (size_t i = 0; i < a.length(); ++i) {
        if (tolower(static_cast<unsigned char>(a[i])) != tolower(static_cast<unsigned char>(b[i])))
            return false;
    }
    return true;
}


Sistema::Sistema() {
    capacidadAlojamientos = 100;
    cantidadAlojamientos = 0;
    alojamientos = new Alojamiento*[capacidadAlojamientos];

    capacidadReservaciones = 100;
    cantidadReservaciones = 0;
    reservaciones = new Reservacion*[capacidadReservaciones];
    ultimoCodigoReserva = 1000;
}
Sistema::~Sistema() {
    for (int i = 0; i < cantidadAlojamientos; i++) {
        delete alojamientos[i];
    }
    delete[] alojamientos;

    for (int i = 0; i < cantidadReservaciones; i++) {
        delete reservaciones[i];
    }
    delete[] reservaciones;
}

void Sistema::cargarAlojamientos(const char* archivo){}

void Sistema::menuPrincipal() {
}

Alojamiento* Sistema::buscarAlojamiento(int codigo) const {
    for (int i = 0; i < cantidadAlojamientos; i++) {
        if (alojamientos[i]->getCodigoID() == codigo) {
            return alojamientos[i];
        }
    }
    return nullptr;
}

Reservacion* Sistema::buscarReservacion(int codigo) const {
    for (int i = 0; i < cantidadReservaciones; i++) {
        if (reservaciones[i]->getCodigoReserva() == codigo) {
            return reservaciones[i];
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
int Sistema::generarCodigoReserva() {
    return ultimoCodigoReserva++;
    }

bool Sistema::huespedTieneReservaEnRango(Huesped* h, const Fecha& inicio, int noches) const {
    for (int i = 0; i < cantidadReservaciones; ++i) {
        Reservacion* r = reservaciones[i];
        if (r->getHuesped() == h && r->secruza(inicio, noches)) {
            return true;
        }
    }
    return false;
}

void Sistema::agregarReservacion(Reservacion* reservacion) {
    if (cantidadReservaciones == capacidadReservaciones) {
        int nuevaCapacidad = capacidadReservaciones * 2;
        Reservacion** nuevo = new Reservacion*[nuevaCapacidad];
        for (int i = 0; i < cantidadReservaciones; ++i) {
            nuevo[i] = reservaciones[i];
        }
        delete[] reservaciones;
        reservaciones = nuevo;
        capacidadReservaciones = nuevaCapacidad;
    }
    reservaciones[cantidadReservaciones++] = reservacion;
}


