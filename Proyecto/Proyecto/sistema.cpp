#include "sistema.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
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
    cantidadAlojamientos = 0;
    alojamientos = nullptr;

    capacidadReservaciones = 100;
    cantidadReservaciones = 0;
    reservaciones = new Reservacion*[capacidadReservaciones];
    ultimoCodigoReserva = 1000;

    anfitriones = nullptr;
    cantidadAnfitriones = 0;

    cantidadHuespedes = 0;
    huespedes = nullptr;
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
    for (int i = 0; i < cantidadAnfitriones; i++) {
        delete anfitriones[i];
    }
    delete[] anfitriones;
    for (int i = 0; i < cantidadHuespedes; i++) {
        delete huespedes[i];
    }
    delete[] huespedes;
}


void Sistema::cargarAlojamientos(const char* archivo){}
void Sistema::cargarAnfitriones(const char* archivo) {}
void Sistema::cargarHuespedes(const char* archivo) {}

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
Anfitrion* Sistema::buscarAnfitrion(int documento) const {
    for (int i = 0; i < cantidadAnfitriones; ++i) {
        if (anfitriones[i]->getDocumento() == documento) {
            return anfitriones[i];
        }
    }
    return nullptr;
}
Huesped* Sistema::buscarHuesped(int documento) const {
    for (int i = 0; i < cantidadHuespedes; ++i) {
        if (huespedes[i]->getDocumento() == documento) {
            return huespedes[i];
        }
    }
    return nullptr;
}

void Sistema::buscarAlojamientosDisponibles(const Fecha& inicio, int noches, const string& municipio, int costoMax, float puntuacionMin) const {
    bool encontrado = false;
    for (int i = 0; i < cantidadAlojamientos; i++) {
        Alojamiento* al = alojamientos[i];

        if (!iguales(al->getMunicipio(), municipio))
            continue;

        if (costoMax >= 0 && al->getPrecio() > costoMax)
            continue;

        if (puntuacionMin >= 0 && al->getAnfitrion() && al->getAnfitrion()->getPuntuacion() < puntuacionMin)
            continue;

        if (!al->estaDisponible(inicio, noches))
            continue;

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

bool Sistema::alojamientoDisponible(Alojamiento* a, const Fecha& inicio, int noches) const {
    for (int i = 0; i < cantidadReservaciones; ++i) {
        Reservacion* r = reservaciones[i];
        if (r->getAlojamiento() == a && r->secruza(inicio, noches)) {
            return false;
        }
    }
    return true;
}

bool Sistema::registrarReservacion() {
    int docHuesped;
    cout << "Ingrese su documento: ";
    cin >> docHuesped;
    Huesped* huesped = buscarHuesped(docHuesped);
    if (!huesped) {
        cout << "Huésped no encontrado.\n";
        return false;
    }

    string municipio;
    cout << "Municipio: ";
    cin >> municipio;
    int noches;
    cout << "Cantidad de noches: ";
    cin >> noches;
    Fecha fechaEntrada;
    cout << "Fecha de entrada:\n";
    fechaEntrada.ingresarFecha();

    int costoMax = -1;
    float puntuacionMin = -1;
    cout << "¿Desea filtrar por costo máximo? (s/n): ";
    char resp;
    cin >> resp;
    if (resp == 's' || resp == 'S') {
        cout << "Costo máximo por noche: ";
        cin >> costoMax;
    }
    cout << "¿Desea filtrar por puntuación mínima de anfitrión? (s/n): ";
    cin >> resp;
    if (resp == 's' || resp == 'S') {
        cout << "Puntuación mínima: ";
        cin >> puntuacionMin;
    }

    buscarAlojamientosDisponibles(fechaEntrada, noches, municipio, costoMax, puntuacionMin);

    int codigoAlojamiento;
    cout << "Ingrese el código del alojamiento a reservar: ";
    cin >> codigoAlojamiento;
    Alojamiento* alojamiento = buscarAlojamiento(codigoAlojamiento);
    if (!alojamiento) {
        cout << "Alojamiento no encontrado.\n";
        return false;
    }

    if (!alojamientoDisponible(alojamiento, fechaEntrada, noches)) {
        cout << "El alojamiento no está disponible en esas fechas.\n";
        return false;
    }

    if (huespedTieneReservaEnRango(huesped, fechaEntrada, noches)) {
        cout << "Ya tiene una reserva en ese rango de fechas.\n";
        return false;
    }

    string metodoPago;
    cout << "Método de pago: ";
    cin >> metodoPago;
    Fecha fechaPago;
    cout << "Fecha de pago:\n";
    fechaPago.ingresarFecha(); // O usa la fecha actual si aplica
    float monto = alojamiento->getPrecio() * noches;
    char anotaciones[1001];
    cout << "¿Desea agregar anotaciones para el anfitrión? (Máx 1000 caracteres, vacío para omitir):\n";
    cin.ignore(); // Limpiar buffer
    cin.getline(anotaciones, 1001);

    int codigoReserva = generarCodigoReserva();
    Reservacion* reserva = new Reservacion(
        codigoReserva,
        alojamiento,
        huesped,
        fechaEntrada,
        noches,
        metodoPago,
        fechaPago,
        monto,
        anotaciones
        );

    agregarReservacion(reserva);

    reserva->mostrarComprobante();

    return true;
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

void Sistema::consultarReservacionesAnfitrion(Anfitrion* anfitrion, const Fecha& desde, const Fecha& hasta) const {
    bool encontrado = false;
    for (int i = 0; i < cantidadReservaciones; ++i) {
        Reservacion* r = reservaciones[i];
        Alojamiento* al = r->getAlojamiento();
        if (al->getAnfitrion() == anfitrion) {
            Fecha finReserva = r->getFechaEntrada();
            finReserva.sumarDias(r->getDuracion());
            if (!(finReserva < desde || r->getFechaEntrada() > hasta)) {
                cout << "Reserva #" << r->getCodigoReserva() << "\n";
                cout << "Alojamiento: " << al->getNombre() << " (Código: " << al->getCodigoID() << ")\n";
                cout << "Huésped: " << r->getHuesped()->getDocumento() << "\n";
                cout << "Desde: ";
                r->getFechaEntrada().mostrarFecha(cout); cout << "\n";
                cout << "Hasta: ";
                Fecha fechaFin = r->getFechaEntrada();
                fechaFin.sumarDias(r->getDuracion());
                fechaFin.mostrarFecha(cout); cout << "\n";
                cout << "------------------------\n";
                encontrado = true;
            }
        }
    }
    if (!encontrado) {
        cout << "No hay reservaciones activas para el anfitrión en el rango solicitado.\n";
    }
}

bool reservacionAntesDeCorte(const Reservacion* r, const Fecha& fechaCorte) {
    Fecha salida = r->getFechaEntrada();
    salida.sumarDias(r->getDuracion());
    return salida < fechaCorte;
}

void Sistema::actualizarHistorico(const Fecha& fechaCorte) {
    ofstream historico("historico_reservas.txt", ios::app); // Puedes cambiar el nombre del archivo

    int nuevoCount = 0;
    for (int i = 0; i < cantidadReservaciones; ++i) {
        Reservacion* r = reservaciones[i];
        if (reservacionAntesDeCorte(r, fechaCorte)) {
            historico << r->getCodigoReserva() << ' '
                      << r->getAlojamiento()->getCodigoID() << ' '
                      << r->getHuesped()->getDocumento() << ' '
                      << r->getFechaEntrada() << ' '
                      << r->getDuracion() << ' '
                      << r->getMetodoPago() << ' '
                      << r->getFechaPago() << ' '
                      << r->getMonto() << ' '
                      << r->getAnotaciones() << '\n';
            delete r;
        } else {
            reservaciones[nuevoCount++] = reservaciones[i];
        }
    }
    cantidadReservaciones = nuevoCount;
    historico.close();
    cout << "Reservaciones anteriores al ";
    fechaCorte.mostrarFecha(cout);
    cout << " movidas al histórico.\n";
}


