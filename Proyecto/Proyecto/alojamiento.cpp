#include "alojamiento.h"
#include <cstring>
#include <iostream>

using namespace std;
Alojamiento(){
    nombre = nullptr;
    codigoID = 0;
    anfitrion = nullptr;
    departamento = nullptr;
    municipio = nullptr;
    tipo = nullptr;
    direccion = nullptr;
    precio = 0;
    for (int i = 0; i < 10; ++i) {
        amenidades[i][0] = '\0';
    }
    for (int i = 0; i < 365; ++i) {
        reservasFuturas[i] = '\0';
    }
    cantidadReservasFutu = 0;
}
Alojamiento::Alojamiento(const char* nombre, int codigoID, Anfitrion* anfitrion, const char* departamento, const char* municipio, const char* tipo, const char* direccion, int precio, char amenidades[10][25])
    {
    this->codigoID = codigoID;

    // Atributos dinámicos
    this->nombre = new char[strlen(nombre) + 1];
    strcpy(this->nombre, nombre);

    this->anfitrion = anfitrion;

    this->departamento = new char[strlen(departamento) + 1];
    strcpy(this->departamento, departamento);

    this->municipio = new char[strlen(municipio) + 1];
    strcpy(this->municipio, municipio);

    this->tipo = new char[strlen(tipo) + 1];
    strcpy(this->tipo, tipo);

    this->direccion = new char[strlen(direccion) + 1];
    strcpy(this->direccion, direccion);

    this->precio = precio;

    // atributo estático
    for (int i = 0; i < 10; i++) {
        strcpy(this->amenidades[i], amenidades[i]);
    }
    // Inicialización de reservas futuras
    for (int i = 0; i < 365; i++) {
        reservasFuturas[i] = '\0';
    }
    cantidadReservasFutu = 0;
}
    Alojamiento::~Alojamiento() {
        delete[] nombre;
        delete[] departamento;
        delete[] municipio;
        delete[] tipo;
        delete[] direccion;
    }
    // Get
    int Alojamiento::getCodigoID() const {
        return codigoID;
    }
    const char* Alojamiento::getNombre() const {
        return nombre;
    }
    Anfitrion* Alojamiento::getAnfitrion() const {
        return anfitrion;
    }
    const char* Alojamiento::getDepartamento() const {
        return departamento;
    }
    const char* Alojamiento::getMunicipio() const {
        return municipio;
    }
    const char* Alojamiento::getTipo() const {
        return tipo;
    }
    const char* Alojamiento::getDireccion() const {
        return direccion;
    }
    int Alojamiento::getPrecio() const {
        return precio;
    }
    const char* Alojamiento::getAmenidad(int i) const {
        if (i >= 0 && i < 10) return amenidades[i];
        return nullptr;
    }
    int Alojamiento::getCantidadReservasFutu() const {
        return cantidadReservasFutu;
    }
    const char* Alojamiento::getReservaFutura(int i) const {
        if (i >= 0 && i < cantidadReservasFutu) return &reservasFuturas[i];
        return nullptr;
    }

    // Set
    void Alojamiento::setNombre(const char* nombre) {
        delete[] this->nombre;
        this->nombre = new char[strlen(nombre) + 1];
        strcpy(this->nombre, nombre);
    }
    void Alojamiento::setAnfitrion(Anfitrion* anfitrion) {
        this->anfitrion = anfitrion;
    }
    void Alojamiento::setDepartamento(const char* departamento) {
        delete[] this->departamento;
        this->departamento = new char[strlen(departamento) + 1];
        strcpy(this->departamento, departamento);
    }
    void Alojamiento::setMunicipio(const char* municipio) {
        delete[] this->municipio;
        this->municipio = new char[strlen(municipio) + 1];
        strcpy(this->municipio, municipio);
    }
    void Alojamiento::setTipo(const char* tipo) {
        delete[] this->tipo;
        this->tipo = new char[strlen(tipo) + 1];
        strcpy(this->tipo, tipo);
    }
    void Alojamiento::setDireccion(const char* direccion) {
        delete[] this->direccion;
        this->direccion = new char[strlen(direccion) + 1];
        strcpy(this->direccion, direccion);
    }
    void Alojamiento::setPrecio(int precio) {
        this->precio = precio;
    }

    // Set para atributos estáticos
    void Alojamiento::setAmenidad(int i, const char* amenidad) {
        if (i >= 0 && i < 10) {
            strncpy(this->amenidades[i], amenidad, 24);
            this->amenidades[i][24] = '\0';
        }
    }

    // Agrega una reservacion a futura
    void Alojamiento::agregarReservaFutura(char reserva) {
        if (cantidadReservasFutu < 365) {
            reservasFuturas[cantidadReservasFutu++] = reserva;
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
        for (int i = 0; i < 10; i++) {
            if (amenidades[i][0] != '\0') {
                cout << amenidades[i];
                if (i < 9 && amenidades[i + 1][0] != '\0') cout << ", ";
            }
        }
        cout << endl;
        cout << "Cantidad de reservas futuras: " << cantidadReservasFutu << endl;
    }

    bool Alojamiento::estaDisponible(const char* fechaInicio, const char* fechaFin) const {
         // Falta implementar esta funcionalidad para verificar disponibilidad
    }


