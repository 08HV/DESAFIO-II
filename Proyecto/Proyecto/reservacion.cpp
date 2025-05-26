#include "Reservacion.h"
#include "iostream"
#include <cstring>
#include <algorithm>

Reservacion::Reservacion() {
    fechaEntrada = Fecha();
    duracion = 0;
    codigoReserva = 0;
    alojamiento = nullptr;
    huesped = nullptr;
    metodoPago = "";
    fechaPago = Fecha();
    monto = 0;
    anotaciones = nullptr;
    setAnotaciones("");
    }
Reservacion::Reservacion(int codigoReserva, Alojamiento* alojamiento, Huesped* huesped,
const Fecha& fechaEntrada, int duracion, const string& metodoPago,
const Fecha& fechaPago,unsigned int monto, const char* anotaciones)
{
    this->fechaEntrada = fechaEntrada;
    this->duracion = duracion;
    this->codigoReserva = codigoReserva;
    this->alojamiento = alojamiento;
    this->huesped = huesped;
    this->metodoPago = metodoPago;
    this->fechaPago = fechaPago;
    this->monto = monto;
    this->anotaciones = nullptr;
    setAnotaciones(anotaciones);
}
Reservacion::Reservacion(const Reservacion& copia) {
    fechaEntrada = copia.fechaEntrada;
    duracion = copia.duracion;
    codigoReserva = copia.codigoReserva;
    alojamiento = copia.alojamiento;
    huesped = copia.huesped;
    metodoPago = copia.metodoPago;
    fechaPago = copia.fechaPago;
    monto = copia.monto;
    anotaciones = nullptr;
    setAnotaciones(copia.anotaciones);
}

Reservacion& Reservacion::operator=(const Reservacion& copia) {
    if (this != &copia) {
        fechaEntrada = copia.fechaEntrada;
        duracion = copia.duracion;
        codigoReserva = copia.codigoReserva;
        alojamiento = copia.alojamiento;
        huesped = copia.huesped;
        metodoPago = copia.metodoPago;
        fechaPago = copia.fechaPago;
        monto = copia.monto;
        setAnotaciones(copia.anotaciones);
    }
    return *this;
}
Reservacion::~Reservacion() {
    delete[] anotaciones;
}

// Get
int Reservacion::getCodigoReserva() const {
    return codigoReserva;
}
int Reservacion::getCodigoAlojamiento() const {
    return (alojamiento ? alojamiento->getCodigoID() : 0);
}
int Reservacion::getDocHuesped() const {
    return (huesped ? huesped->getDocumento() : 0);
}
Alojamiento* Reservacion::getAlojamiento() const {
    return alojamiento;
}
Huesped* Reservacion::getHuesped() const {
    return huesped;
}
const Fecha& Reservacion::getFechaEntrada() const {
    return fechaEntrada;
}
int Reservacion::getDuracion() const {
    return duracion;
}
unsigned int Reservacion::getMonto() const {
    return monto;
}
const string& Reservacion::getMetodoPago() const {
    return metodoPago;
}
const char* Reservacion::getAnotaciones() const {
    return anotaciones ? anotaciones : "";
}
const Fecha& Reservacion::getFechaPago() const {
    return fechaPago;
}
// Set
void Reservacion::setCodigoReserva(int codigo) {
    codigoReserva = codigo;
}
void Reservacion::setAlojamiento(Alojamiento* a) {
    alojamiento = a;
}
void Reservacion::setHuesped(Huesped* h) {
    huesped = h;
}
void Reservacion::setFechaEntrada(const Fecha& fecha) {
    fechaEntrada = fecha;
}
void Reservacion::setDuracion(int d) {
    duracion = d;
}
void Reservacion::setMetodoPago(const string& metodo) {
    metodoPago = metodo;
}
void Reservacion::setFechaPago(const Fecha& fecha) {
    fechaPago = fecha;
}
void Reservacion::setMonto(unsigned int m) {
    monto = m;
}
void Reservacion::setAnotaciones(const char* anota) {
    delete[] anotaciones;
    if (anota) {
        size_t len = min(strlen(anota), size_t(1000));
        anotaciones = new char[len + 1];
        strncpy(anotaciones, anota, len);
        anotaciones[len] = '\0';
    } else {
        anotaciones = new char[1];
        anotaciones[0] = '\0';
    }
}

bool Reservacion::estaActiva(const Fecha& fechaActual) const {
    Fecha fin = getFechaFin();
    return (fechaActual >= fechaEntrada) && (fechaActual < fin);
}

Fecha Reservacion::getFechaFin() const {
    Fecha fin = fechaEntrada;
    fin.sumarDias(duracion);
    return fin;
}

// Muestra comprobante de la reserva
void Reservacion::mostrarComprobante() const {
    cout << "----- Comprobante de Reservacion -----\n";
    cout << "Codigo de reserva: " << codigoReserva << "\n";
    if (huesped)
        cout << "Documento huesped: " << huesped->getDocumento() << "\n";
    if (alojamiento)
        cout << "Codigo alojamiento: " << alojamiento->getCodigoID() << "\n";
    cout << "Fecha de inicio: ";
    fechaEntrada.mostrarFechaBonita(cout); // Debe mostrar en formato "nombreDía, día de nombreMes del año"
    cout << "\n";
    cout << "Fecha de fin: ";
    getFechaFin().mostrarFechaBonita(cout);
    cout << "\n";
    cout << "--------------------------------------\n";
}

bool Reservacion::secruza(const Fecha& inicio, int noches) const {
    Fecha finReserva = getFechaFin();

    Fecha finConsulta = inicio;
    finConsulta.sumarDias(noches);

    return !(finReserva <= inicio || fechaEntrada >= finConsulta);
}
