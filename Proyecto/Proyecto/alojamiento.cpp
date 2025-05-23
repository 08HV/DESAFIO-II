#include "alojamiento.h"
#include <cstring>
#include <iostream>


using namespace std;
Alojamiento::Alojamiento(){
    nombre = "";
    codigoID = 0;
    anfitrion = nullptr;
    departamento = "";
    municipio = "";
    tipo = "";
    direccion = "";
    precio = 0;
    for (int i = 0; i < 10; ++i) {
        amenidades[i] = "";
    }
    cantidadReservasFutu = 0;
}
Alojamiento::Alojamiento(const string& nombre, int codigoID, Anfitrion* anfitrion, const string& departamento, const string& municipio, const string& tipo, const string& direccion, int precio, string amenidades[10])
    {
    this->codigoID = codigoID;

    this->nombre = nombre;

    this->anfitrion = anfitrion;

    this->nombre = nombre;

    this->municipio = municipio;

    this->tipo = tipo;

    this->direccion = direccion;

    this->precio = precio;

    // atributo estático
    for (int i = 0; i < 10; i++) {
        this->amenidades[i] = amenidades[i];
    }
    cantidadReservasFutu = 0;
}
    // Get
    int Alojamiento::getCodigoID() const {
        return codigoID;
    }
    const string& Alojamiento::getNombre() const {
        return nombre;
    }
    Anfitrion* Alojamiento::getAnfitrion() const {
        return anfitrion;
    }
    const string& Alojamiento::getDepartamento() const {
        return departamento;
    }
    const string& Alojamiento::getMunicipio() const {
        return municipio;
    }
    const string& Alojamiento::getTipo() const {
        return tipo;
    }
    const string& Alojamiento::getDireccion() const {
        return direccion;
    }
    int Alojamiento::getPrecio() const {
        return precio;
    }
    const string& Alojamiento::getAmenidad(int i) const {
        if (i >= 0 && i < 10) return amenidades[i];
        static const string empty = "";
        return empty;
    }
    int Alojamiento::getCantidadReservasFutu() const {
        return cantidadReservasFutu;
    }
    const Fecha& Alojamiento::getReservaFutura(int i) const {
        if (i >= 0 && i < cantidadReservasFutu) return reservasFuturas[i];
        static Fecha vacia;
        return vacia;
    }

    // Set
    void Alojamiento::setNombre(const string& nombre) {
        this->nombre = nombre;
    }
    void Alojamiento::setAnfitrion(Anfitrion* anfitrion) {
        this->anfitrion = anfitrion;
    }
    void Alojamiento::setDepartamento(const string& departamento) {
        this->departamento = departamento;
    }
    void Alojamiento::setMunicipio(const string& municipio) {
        this->municipio = municipio;
    }
    void Alojamiento::setTipo(const string& tipo) {
        this->tipo = tipo;
    }
    void Alojamiento::setDireccion(const string& direccion) {
        this->direccion = direccion;
    }
    void Alojamiento::setPrecio(int precio) {
        this->precio = precio;
    }
    void Alojamiento::setAmenidad(int i, const string& amenidad) {
        if (i >= 0 && i < 10) {
            this->amenidades[i] = amenidad;
        }
    }

 // Agrega una reservacion a futuro
void Alojamiento::agregarReservaFutura(const Fecha& fechaReserva) {
    if (cantidadReservasFutu < 365) {
        reservasFuturas[cantidadReservasFutu++] = fechaReserva;
    }
}

// Muestra la información completa del alojamiento
void Alojamiento::mostrarInfo() const {
    cout << "Nombre: " << nombre << endl;
    cout << "Codigo: " << codigoID << endl;
    cout << "Departamento: " << departamento << endl;
    cout << "Municipio: " << municipio << endl;
    cout << "Tipo: " << tipo << endl;
    cout << "Direccion: " << direccion << endl;
    cout << "Precio por noche: $" << precio << endl;
    cout << "Amenidades: ";
    bool eso=true;
    for (int i = 0; i < 10; i++) {
        if (!amenidades[i].empty()) {
            if (!eso) cout << ", ";
            cout << amenidades[i];
            eso = false;
        }
    }
    cout << endl;
    cout << "Cantidad de reservas futuras: " << cantidadReservasFutu << endl;
    if (cantidadReservasFutu > 0) {
        cout << "Fechas reservadas: ";
        for (int i = 0; i < cantidadReservasFutu; ++i) {
            reservasFuturas[i].mostrarFecha(cout);
            if (i != cantidadReservasFutu - 1) cout << ", ";
        }
        cout << endl;
    }
}

bool Alojamiento::estaDisponible(const Fecha& nicio, int noches) const {
    Fecha dia = inicio;
    for (int n = 0; n < noches; ++n) {
        for (int r = 0; r < cantidadReservasFutu; ++r) {
            if (reservasFuturas[r] == dia) {
                return false; // Día ya reservado
            }
        }
        dia.sumarDias(1);
    }
    return true;
}



