#include "sistema.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <string>
#include "consumorecursos.h"

using namespace std;
const int HUESPEDES = 100;
const int MANFITRIONES = 100;
const int ALOJAMIENTOS = 100;

bool iguales(const string& a, const string& b) {
    if (a.length() != b.length()) return false;
    for (size_t i = 0; i < a.length(); ++i) {
        consumorecursos::contarIteracion();
        if (tolower(static_cast<unsigned char>(a[i])) != tolower(static_cast<unsigned char>(b[i])))
            return false;
    }
    return true;
}


Sistema::Sistema() {
    cantidadAlojamientos = 0;
    alojamientos = new Alojamiento*[ALOJAMIENTOS];
    consumorecursos::sumarMemoria(sizeof(Alojamiento*) * ALOJAMIENTOS);
    for (int i = 0; i < ALOJAMIENTOS; ++i){
        consumorecursos::contarIteracion();
        alojamientos[i] = nullptr;
    }
    capacidadReservaciones = 100;
    cantidadReservaciones = 0;
    reservaciones = new Reservacion*[capacidadReservaciones];
    consumorecursos::sumarMemoria(sizeof(Reservacion*) * capacidadReservaciones);
    for (int i = 0; i < capacidadReservaciones; ++i){
        consumorecursos::contarIteracion();
        reservaciones[i] = nullptr;
    }
    ultimoCodigoReserva = 0;
    gestionarFechaCorte();

    anfitriones = new Anfitrion*[ANFITRIONES];
    consumorecursos::sumarMemoria(sizeof(Anfitrion*) * ANFITRIONES);
    for (int i = 0; i < ANFITRIONES; ++i){
        consumorecursos::contarIteracion();
        anfitriones[i] = nullptr;
    }
    cantidadAnfitriones = 0;

    cantidadHuespedes = 0;
    huespedes = new Huesped*[HUESPEDES];
    consumorecursos::sumarMemoria(sizeof(Huesped*) * HUESPEDES);
    for (int i = 0; i < HUESPEDES; ++i){
        consumorecursos::contarIteracion();
        huespedes[i] = nullptr;
    }
}
Sistema::~Sistema() {
    for (int i = 0; i < cantidadAlojamientos; i++) {
        consumorecursos::contarIteracion();
        if (alojamientos[i] != nullptr){
            delete alojamientos[i];
            alojamientos[i] = nullptr;
        }
    }
    delete[] alojamientos;
    alojamientos = nullptr;

    for (int i = 0; i < cantidadReservaciones; i++) {
        consumorecursos::contarIteracion();
        if (reservaciones[i] != nullptr) {
            delete reservaciones[i];
            reservaciones[i] = nullptr;
        }
    }
    delete[] reservaciones;
    reservaciones = nullptr;

    for (int i = 0; i < cantidadAnfitriones; i++) {
        consumorecursos::contarIteracion();
        if (anfitriones[i] != nullptr) {
            delete anfitriones[i];
            anfitriones[i] = nullptr;
        }
    }  
    delete[] anfitriones;
    anfitriones = nullptr;

    for (int i = 0; i < cantidadHuespedes; i++) {
        consumorecursos::contarIteracion();
        if (huespedes[i] != nullptr) {
            delete huespedes[i];
            huespedes[i] = nullptr;
        }
    }
    delete[] huespedes;
    huespedes = nullptr;
}

string extraerCampo(const string& linea, size_t& posicion) {
    size_t next = linea.find(':', posicion);
    string campo;
    if (next == string::npos) {
        campo = linea.substr(posicion);
        posicion = linea.length();
    } else {
        campo = linea.substr(posicion, next - posicion);
        posicion = next + 1;
    }
    return campo;
}

void Sistema::cargarAlojamientos(const char* archivo){
    ifstream in(archivo);
    if (!in) {
        cerr << "No se pudo abrir el archivo de alojamientos.\n";
        return;
    }
    string linea;
    while (getline(in, linea)) {
        consumorecursos::contarIteracion();
        if (linea.empty()) continue;
        size_t posicion = 0;
        int codigoID = stoi(extraerCampo(linea, posicion));
        string nombre = extraerCampo(linea, posicion);
        int documentoAnfitrion = stoi(extraerCampo(linea, posicion));
        string departamento = extraerCampo(linea, posicion);
        string municipio = extraerCampo(linea, posicion);
        string tipo = extraerCampo(linea, posicion);
        string direccion = extraerCampo(linea, posicion);
        int precio = stoi(extraerCampo(linea, posicion));
        string amenidades[10];
        for (int i = 0; i < 10; ++i) {
            consumorecursos::contarIteracion();
            amenidades[i] = extraerCampo(linea, posicion);
        }
        Anfitrion* anfitrion = buscarAnfitrion(documentoAnfitrion);
        alojamientos[cantidadAlojamientos++] = new Alojamiento(
            nombre, codigoID, anfitrion, departamento, municipio, tipo, direccion, precio, amenidades
            );
        consumorecursos::sumarMemoria(sizeof(Alojamiento));
    }
}

void Sistema::cargarAnfitriones(const char* archivo) {
    ifstream in(archivo);
    if (!in) {
        cerr << "No se pudo abrir el archivo de anfitriones.\n";
        return;
    }
    string linea;
    while (getline(in, linea)) {
        consumorecursos::contarIteracion();
        if (linea.empty()) continue;
        size_t posicion = 0;
        int documento = stoi(extraerCampo(linea, posicion));
        int antiguedad = stoi(extraerCampo(linea, posicion));
        float puntuacion = stof(extraerCampo(linea, posicion));
        Anfitrion* anfitrion = new Anfitrion(documento, antiguedad, puntuacion);
        consumorecursos::sumarMemoria(sizeof(Anfitrion));

        while (posicion < linea.size()) {
            consumorecursos::contarIteracion();
            string campo = extraerCampo(linea, posicion);
            if (!campo.empty())
                anfitrion->agregarCodigoAlojamiento(stoi(campo));
        }
        anfitriones[cantidadAnfitriones++] = anfitrion;
    }
}

void Sistema::cargarHuespedes(const char* archivo) {
    ifstream in(archivo);
    if (!in) {
        cerr << "No se pudo abrir el archivo de huespedes.\n";
        return;
    }
    string linea;
    while (getline(in, linea)) {
        consumorecursos::contarIteracion();
        if (linea.empty()) continue;
        size_t posicion = 0;
        int documento = stoi(extraerCampo(linea, posicion));
        int antiguedad = stoi(extraerCampo(linea, posicion));
        float puntuacion = stof(extraerCampo(linea, posicion));
        Huesped* huesped = new Huesped(documento, antiguedad, puntuacion);

        while (posicion < linea.size()) {
            consumorecursos::contarIteracion();
            string campo = extraerCampo(linea, posicion);
            if (!campo.empty())
                huesped->agregarCodigoReserva(stoi(campo));
        }
        huespedes[cantidadHuespedes++] = huesped;
    }
}

void Sistema::cargarReservacion(const char* archivo) {
    ifstream in(archivo);
    if (!in) {
        cerr << "No se pudo abrir el archivo de reservaciones.\n";
        return;
    }
    string linea;
    while (getline(in, linea)) {
        consumorecursos::contarIteracion();
        if (linea.empty()) continue;
        size_t posicion = 0;
        int codigoReserva = stoi(extraerCampo(linea, posicion));
        int codigoAlojamiento = stoi(extraerCampo(linea, posicion));
        int documentoHuesped = stoi(extraerCampo(linea, posicion));
        int diaEntrada = stoi(extraerCampo(linea, posicion));
        int mesEntrada = stoi(extraerCampo(linea, posicion));
        int añoEntrada = stoi(extraerCampo(linea, posicion));
        int duracion = stoi(extraerCampo(linea, posicion));
        string metodoPago = extraerCampo(linea, posicion);
        int diaPago = stoi(extraerCampo(linea, posicion));
        int mesPago = stoi(extraerCampo(linea, posicion));
        int añoPago = stoi(extraerCampo(linea, posicion));
        unsigned int monto = stof(extraerCampo(linea, posicion));
        string anotaciones = extraerCampo(linea, posicion);

        if (codigoReserva > ultimoCodigoReserva) {
            ultimoCodigoReserva = codigoReserva;
        }
        Alojamiento* alojamiento = buscarAlojamiento(codigoAlojamiento);
        Huesped* huesped = buscarHuesped(documentoHuesped);
        if (alojamiento == nullptr || huesped == nullptr){
            cerr<<"Error, reservacion no carga: codigo " <<codigoReserva;
            cerr<<"alojamiento o huesped no encontrado\n";
            continue;
        }
        Fecha fechaEntrada(diaEntrada, mesEntrada, añoEntrada);
        Fecha fechaPago(diaPago, mesPago, añoPago);

        reservaciones[cantidadReservaciones++] = new Reservacion(
            codigoReserva, alojamiento, huesped, fechaEntrada, duracion, metodoPago, fechaPago, monto, anotaciones.c_str()
        );
        consumorecursos::sumarMemoria(sizeof(Reservacion));
    }
}
void Sistema::guardarReservas(const char* archivo) {
    ofstream out(archivo);
    if (!out) {
        cout << "No se pudo abrir el archivo para guardar las reservas." << endl;
        return;
    }
    for (int i = 0; i < cantidadReservaciones; ++i) {
        consumorecursos::contarIteracion();
        Reservacion* r = reservaciones[i];

        if (r == nullptr) {
            cout << "[ERROR] reservaciones[" << i << "] es nullptr. No se guarda.\n";
            continue;
        }

        if (r->getAlojamiento() == nullptr || r->getHuesped() == nullptr) {
            cout << "[ERROR] Reservación " << r->getCodigoReserva() << " tiene alojamiento o huésped nulo.\n";
            continue;
        }

        out << r->getCodigoReserva() << ":"
            << r->getAlojamiento()->getCodigoID() << ":"
            << r->getHuesped()->getDocumento() << ":"
            << r->getFechaEntrada().getDia() << ":"
            << r->getFechaEntrada().getMes() << ":"
            << r->getFechaEntrada().getAño() << ":"
            << r->getDuracion() << ":"
            << r->getMetodoPago() << ":"
            << r->getFechaPago().getDia() << ":"
            << r->getFechaPago().getMes() << ":"
            << r->getFechaPago().getAño() << ":"
            << r->getMonto() << ":"
            << r->getAnotaciones() << endl;
    }
    out.close();
}
void Sistema::cargarDatos() {
    gestionarFechaCorte();
    cargarAnfitriones("ANFITRIONES.txt");
    cargarAlojamientos("ALOJAMIENTOS.txt");
    cargarHuespedes("HUESPEDES.txt");
    cargarReservacion("RESERVAS.txt");

}

void Sistema::guardarDatos() {
    guardarReservas("RESERVAS.txt");
}

bool Sistema::Ingreso() {
    int doc;
    int tipo;
    cout << "Seleccione tipo de usuario:\n 1) Huésped\n 2) Anfitrión\nOpción: ";
    cin >> tipo;

    if (tipo != 1 && tipo != 2) {
        cout << "Opción inválida.\n";
        return false;
    }

    cout << "Ingrese su número de documento: ";
    cin >> doc;
    if (tipo == 1) {
        Huesped* h = buscarHuesped(doc);
        if (h) {
            menuPrincipalHuesped(h);
            return true;
        }
    } else if (tipo == 2) {
        Anfitrion* a = buscarAnfitrion(doc);
        if (a) {
            menuPrincipalAnfitrion(a);
            return true;
        }
    }
    cout << "Credenciales inválidas.\n";
    return false;
}

void Sistema::mostrarReservasDeHuesped(Huesped* h) const {
    bool hay = false;
    for (int i = 0; i < cantidadReservaciones; ++i) {
        consumorecursos::contarIteracion();
        Reservacion* r = reservaciones[i];
        if (r->getHuesped() == h) {
            cout << "Reserva #" << r->getCodigoReserva() << endl;
            cout << "Alojamiento: " << r->getAlojamiento()->getNombre() << " (Código: " << r->getAlojamiento()->getCodigoID() << ")" << endl;
            cout << "Desde: "; r->getFechaEntrada().mostrarFecha(cout); cout << endl;
            cout << "Duración (noches): " << r->getDuracion() << endl;
            cout << "Método de pago: " << r->getMetodoPago() << endl;
            cout << "Monto: $" << r->getMonto() << endl;
            cout << "--------------------------" << endl;
            hay = true;
        }
    }
    if (!hay) {
        cout << "No tiene reservas activas.\n";
    }
}

void Sistema::menuPrincipalAnfitrion(Anfitrion* a) {
    int opcion = 0;
    while (opcion != 5) {
        consumorecursos::contarIteracion();
        cout << "\n--- MENÚ ANFITRIÓN ---" << endl;
        cout << "1. Mostrar mis alojamientos\n";
        cout << "2. Consultar reservaciones activas por rango de fecha\n";
        cout << "3. Anular una reservación\n";
        cout << "4. Actualizar histórico de reservaciones\n";
        cout << "5. Cerrar sesión para guardar cambios\n";
        cin >> opcion;

        if (opcion == 1) {
            // Mostrar alojamientos del anfitrión
            bool encontrado = false;
            for (int i = 0; i < cantidadAlojamientos; ++i) {
                consumorecursos::contarIteracion();
                if (alojamientos[i]->getAnfitrion() == a) {
                    alojamientos[i]->mostrarInfo();
                    cout << "-------------------------" << endl;
                    encontrado = true;
                }
            }
            if (!encontrado) {
                cout << "No tiene alojamientos registrados.\n";
            }
        }
        else if (opcion == 2) {
            Fecha desde, hasta;
            cout << "Ingrese fecha de inicio del rango:\n";
            desde.ingresarFecha();
            cout << "Ingrese fecha de fin del rango:\n";
            hasta.ingresarFecha();
            consultarReservacionesAnfitrion(a, desde, hasta);
        }
        else if (opcion == 3) {
            anularReservacion();
        }
        else if (opcion == 4) {
            Fecha fechaCorte;
            cout << "Ingrese la fecha de corte para actualizar el histórico:\n";
            fechaCorte.ingresarFecha();
            actualizarHistorico(fechaCorte);
        }
        else if (opcion == 5) {
            cout << "Sesión cerrada.\n";
        }
        else {
            cout << "Opción inválida.\n";
        }
    }
}

void Sistema::menuPrincipalHuesped(Huesped* h) {
    int opcion = 0;
    while (opcion != 5) {
        consumorecursos::contarIteracion();
        cout << "\n--- MENÚ HUÉSPED ---" << endl;
        cout << "1. Información de mis reservas\n";
        cout << "2. Buscar y reservar alojamiento (por filtros)\n";
        cout << "3. Buscar alojamiento por código y reservar\n";
        cout << "4. Anular reservación\n";
        cout << "5. Cerrar sesión para guardar reserva\n";
        cin >> opcion;

        if (opcion == 1) {
            mostrarReservasDeHuesped(h);
        }
        else if (opcion == 2) {
            registrarReservacionPorBusqueda(h);
        }
        else if (opcion == 3) {
            int codigoAloj;
            Fecha fechaEntrada;
            int noches;
            cout << "Ingrese el código del alojamiento: ";
            cin >> codigoAloj;
            cout << "Fecha de entrada:\n";
            fechaEntrada.ingresarFecha();
            cout << "Cantidad de noches: ";
            cin >> noches;
            if (!fechaValida(fechaEntrada)) {
                cout << "La fecha de entrada no es valida, no tenemos reservas habilitadas.\n";
            }else{
            registrarReservacionPorCodigo(h, codigoAloj, fechaEntrada, noches);
            }
        }
        else if (opcion == 4) {
            anularReservacion();
        }
        else if (opcion == 5) {
            cout << "Sesión cerrada.\n";
        }
        else {
            cout << "Opción inválida. Por favor, elija una opción válida.\n";
        }
    }
}


Alojamiento* Sistema::buscarAlojamiento(int codigo) const {
    for (int i = 0; i < cantidadAlojamientos; i++) {
        consumorecursos::contarIteracion();
        if (alojamientos[i]->getCodigoID() == codigo) {
            return alojamientos[i];
        }
    }
    return nullptr;
}

Reservacion* Sistema::buscarReservacion(int codigo) const {
    for (int i = 0; i < cantidadReservaciones; i++) {
        consumorecursos::contarIteracion();
        if (reservaciones[i]->getCodigoReserva() == codigo) {
            return reservaciones[i];
        }
    }
    return nullptr;
}
Anfitrion* Sistema::buscarAnfitrion(int documento) const {
    for (int i = 0; i < cantidadAnfitriones; ++i) {
        consumorecursos::contarIteracion();
        if (anfitriones[i]->getDocumento() == documento) {
            return anfitriones[i];
        }
    }
    return nullptr;
}
Huesped* Sistema::buscarHuesped(int documento) const {
    for (int i = 0; i < cantidadHuespedes; ++i) {
        consumorecursos::contarIteracion();
        if (huespedes[i]->getDocumento() == documento) {
            return huespedes[i];
        }
    }
    return nullptr;
}

void Sistema::buscarAlojamientosDisponibles(const Fecha& inicio, int noches, const string& municipio, int costoMax, float puntuacionMin) const {
    bool encontrado = false;
    for (int i = 0; i < cantidadAlojamientos; i++) {
        consumorecursos::contarIteracion();
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
    return ++ultimoCodigoReserva;
}

bool Sistema::huespedTieneReservaEnRango(Huesped* h, const Fecha& inicio, int noches) const {
    for (int i = 0; i < cantidadReservaciones; ++i) {
        consumorecursos::contarIteracion();
        Reservacion* r = reservaciones[i];
        if (r->getHuesped() == h && r->secruza(inicio, noches)) {
            return true;
        }
    }
    return false;
}

bool Sistema::alojamientoDisponible(Alojamiento* a, const Fecha& inicio, int noches) const {
    for (int i = 0; i < cantidadReservaciones; ++i) {
        consumorecursos::contarIteracion();
        Reservacion* r = reservaciones[i];
        if (r->getAlojamiento() == a && r->secruza(inicio, noches)) {
            return false;
        }
    }
    return true;
}

bool Sistema::registrarReservacionPorCodigo(Huesped* huesped, int codigoAlojamiento, Fecha fechaEntrada, int noches) {
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
    fechaPago.ingresarFecha();
    unsigned int monto = alojamiento->getPrecio() * noches;
    char anotaciones[1000];
    cout << "¿Desea agregar anotaciones para el anfitrión? (Máx 1000 caracteres, enter para omitir):\n";
    cin.ignore();
    cin.getline(anotaciones, 1000);

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
    consumorecursos::sumarMemoria(sizeof(Reservacion));
    agregarReservacion(reserva);
    reserva->mostrarComprobante();
    return true;
}

bool Sistema::registrarReservacionPorBusqueda(Huesped* huesped) {
    string municipio;
    Fecha fechaEntrada;
    int noches;
    int costoMax = -1;
    float puntuacionMin = -1;

    cout << "Municipio: ";
    cin >> municipio;
    cout << "Fecha de entrada:\n";
    fechaEntrada.ingresarFecha();
    cout << "Cantidad de noches: ";
    cin >> noches;
    if (!fechaValida(fechaEntrada)) {
        cout << "La fecha de entrada no es valida, no tenemos reservas habilitadas.\n";
    }else{
        string respu;
        while (true) {
            consumorecursos::contarIteracion();
            cout << "¿Desea filtrar por costo máximo por noche? (si/no): ";
            cin >> respu;
            for (auto &c : respu) c = tolower(c);

            if (respu == "si") {
                cout << "Costo máximo por noche: ";
                cin >> costoMax;
                break;
            } else if (respu == "no") {
                break;
            } else {
                cout << "Respuesta inválida. Por favor escriba 'si' o 'no'.\n";
            }
        }
        while (true) {
            consumorecursos::contarIteracion();
            cout << "¿Desea filtrar por puntuación mínima de anfitrión? (si/no): ";
            cin >> respu;
            for (auto &c : respu) c = tolower(c);

            if (respu == "si") {
                cout << "Puntuación mínima: ";
                cin >> puntuacionMin;
                break;
            } else if (respu == "no") {

                break;
            } else {
                cout << "Respuesta inválida. Por favor escriba 'si' o 'no'.\n";
            }
        }

        const int resultados = 100;
        Alojamiento* disponibles[resultados];
        int totalDisponibles = 0;

        for (int i = 0; i < cantidadAlojamientos; ++i) {
            consumorecursos::contarIteracion();
            if (alojamientos[i]->esDelMunicipio(municipio) &&
                alojamientos[i]->estaDisponible(fechaEntrada, noches) &&
                (costoMax < 0 || alojamientos[i]->getCostoPorNoche() <= costoMax) &&
                (puntuacionMin < 0 || alojamientos[i]->getAnfitrion()->getPuntuacion() >= puntuacionMin)) {
                disponibles[totalDisponibles++] = alojamientos[i];
            }
        }
        if (totalDisponibles == 0) {
            cout << "No hay alojamientos disponibles con esos criterios.\n";
            return false;
        }
        cout << "\nAlojamientos disponibles:\n";
        for (int i = 0; i < totalDisponibles; ++i) {
            consumorecursos::contarIteracion();
            cout << "Código: " << disponibles[i]->getCodigo() << endl;
            disponibles[i]->mostrarInfo();
            cout << "----------------------\n";
        }
        while (true) {
            consumorecursos::contarIteracion();
            cout << "¿Desea registrar una reservación? (si/no): ";
            cin >> respu;

            for (auto &c : respu) c = tolower(c);

            if (respu == "si") {
                break;
            } else if (respu == "no") {
                return false;
            } else {
                cout << "Respuesta inválida. Por favor escriba 'si' o 'no'.\n";
            }
        }
        int codigoAlojamiento;
        cout << "Ingrese el código del alojamiento a reservar: ";
        cin >> codigoAlojamiento;
        bool encontrado = false;
        for (int i = 0; i < totalDisponibles; ++i) {
            consumorecursos::contarIteracion();
            if (disponibles[i]->getCodigo() == codigoAlojamiento) {
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            cout << "Código de alojamiento inválido.\n";
            return false;
        }
        return registrarReservacionPorCodigo(huesped, codigoAlojamiento, fechaEntrada, noches);
    }
}
void Sistema::anularReservacion() {
    int codigo;
    cout << "Ingrese el código de la reservación a anular: ";
    cin >> codigo;
    int indice = -1;
    for (int i = 0; i < cantidadReservaciones; ++i) {
        consumorecursos::contarIteracion();
        if (reservaciones[i]->getCodigoReserva() == codigo) {
            indice = i;
            break;
        }
    }
    if (indice == -1) {
        cout << "No existe una reservación con ese código.\n";
        return;
    }
    delete reservaciones[indice];

    for (int j = indice; j < cantidadReservaciones - 1; ++j) {
        consumorecursos::contarIteracion();
        reservaciones[j] = reservaciones[j + 1];
    }
    reservaciones[cantidadReservaciones - 1] = nullptr;
    cantidadReservaciones--;
    cout << "Reservación anulada y eliminada exitosamente.\n";
}

void Sistema::agregarReservacion(Reservacion* reservacion) {
    if (cantidadReservaciones == capacidadReservaciones) {
        int nuevaCapacidad = capacidadReservaciones * 2;
        Reservacion** nuevo = new Reservacion*[nuevaCapacidad];
        consumorecursos::sumarMemoria(sizeof(Reservacion*) * nuevaCapacidad);
        for (int i = 0; i < cantidadReservaciones; ++i) {
            consumorecursos::contarIteracion();
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
        consumorecursos::contarIteracion();
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
    fechaCorteActual = fechaCorte;
    ofstream historico("historico_reservas.txt", ios::app);

    int nuevoCount = 0;
    for (int i = 0; i < cantidadReservaciones; ++i) {
        consumorecursos::contarIteracion();
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
    ofstream out("fechacorte.txt");
    if (out)
        out << fechaCorteActual.getDia() << ' '
            << fechaCorteActual.getMes() << ' '
            << fechaCorteActual.getAño();
    cout << "Reservaciones anteriores al ";
    fechaCorte.mostrarFecha(cout);
    cout << " movidas al histórico.\n";
}
void Sistema::gestionarFechaCorte() {
    ifstream in("fechacorte.txt");
    int d, m, a;
    if (in >> d >> m >> a) {
        fechaCorteActual.setFecha(d, m, a);
    }
}

bool Sistema::fechaValida(const Fecha& f) const {
    Fecha limiteSuperior = fechaCorteActual;
    limiteSuperior.sumarDias(365);
    return f >= fechaCorteActual && f <= limiteSuperior;
}
