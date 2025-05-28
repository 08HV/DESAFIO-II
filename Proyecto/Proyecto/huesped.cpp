#include "huesped.h"
#include <iostream>
#include "consumorecursos.h"
using namespace std;

Huesped::Huesped() {
    documento = 0;
    antiguedad = 0;
    puntuacion = 0.0;
    codigosReservas = nullptr;
    cantidadReservas = 0;
    capacidadReservas = 0;
}
Huesped::Huesped(int documento, int antiguedad, float puntuacion) {
    this->documento = documento;
    this->antiguedad = antiguedad;
    this->puntuacion = puntuacion;
    this->codigosReservas = nullptr;
    this->cantidadReservas = 0;
    this->capacidadReservas = 0;
}
Huesped::Huesped(const Huesped& copia) {
    documento = copia.documento;
    antiguedad = copia.antiguedad;
    puntuacion = copia.puntuacion;
    cantidadReservas = copia.cantidadReservas;
    capacidadReservas = copia.capacidadReservas;
    if (copia.codigosReservas && capacidadReservas > 0) {
        codigosReservas = new int[capacidadReservas];
        consumorecursos::sumarMemoria(sizeof(int) * capacidadReservas);
        for (int i = 0; i < cantidadReservas; ++i){
            consumorecursos::contarIteracion();
            codigosReservas[i] = copia.codigosReservas[i];
        }
    } else {
        codigosReservas = nullptr;
    }
}
Huesped& Huesped::operator=(const Huesped& copia) {
    if (this != &copia) {
        delete[] codigosReservas;
        documento = copia.documento;
        antiguedad = copia.antiguedad;
        puntuacion = copia.puntuacion;
        cantidadReservas = copia.cantidadReservas;
        capacidadReservas = copia.capacidadReservas;
        if (copia.codigosReservas && capacidadReservas > 0) {
            codigosReservas = new int[capacidadReservas];
            consumorecursos::sumarMemoria(sizeof(int) * capacidadReservas);
            for (int i = 0; i < cantidadReservas; ++i){
                consumorecursos::contarIteracion();
                codigosReservas[i] = copia.codigosReservas[i];
            }
        } else {
            codigosReservas = nullptr;
        }
    }
    return *this;
}
Huesped::~Huesped() {
    delete[] codigosReservas;
}
//get
int Huesped::getDocumento() const {
    return documento;
}
int Huesped::getAntiguedad() const {
    return antiguedad;
}
float Huesped::getPuntuacion() const {
    return puntuacion;
}
int Huesped::getCantidadReservas() const {
    return cantidadReservas;
}
const int* Huesped::getCodigosReservas() const {
    return codigosReservas;
}
// Set
void Huesped::setDocumento(int doc) {
    documento = doc;
}
void Huesped::setAntiguedad(int ant) {
    antiguedad = ant;
}
void Huesped::setPuntuacion(float punt) {
    puntuacion = punt;
}

void Huesped::agregarCodigoReserva(int codigo) {
    if (capacidadReservas == 0) {
        capacidadReservas = 2;
        codigosReservas = new int[capacidadReservas];
        consumorecursos::sumarMemoria(sizeof(int) * capacidadReservas);
    }
    if (cantidadReservas == capacidadReservas) {
        int nuevaCapacidad = capacidadReservas * 2;
        int* nuevoArr = new int[nuevaCapacidad];
        consumorecursos::sumarMemoria(sizeof(int) * nuevaCapacidad);
        for (int i = 0; i < cantidadReservas; ++i){
            consumorecursos::contarIteracion();
            nuevoArr[i] = codigosReservas[i];
        }
        delete[] codigosReservas;
        codigosReservas = nuevoArr;
        capacidadReservas = nuevaCapacidad;
    }
    codigosReservas[cantidadReservas++] = codigo;
}
void Huesped::mostrarInfo() const {
    cout << "Documento: " << documento << endl;
    cout << "Antigüedad en la plataforma: " << antiguedad << endl;
    cout << "Puntuación: " << puntuacion << endl;
    cout << "Cantidad de reservas: " << cantidadReservas << endl;
    if (cantidadReservas > 0) {
        cout << "Códigos de reservas: ";
        for (int i = 0; i < cantidadReservas; ++i) {
            consumorecursos::contarIteracion();
            cout << codigosReservas[i];
            if (i < cantidadReservas - 1) cout << ", ";
        }
        cout << endl;
    }
}

