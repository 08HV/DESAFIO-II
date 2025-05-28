#include "Anfitrion.h"
#include <iostream>
#include <cstring>
#include "consumorecursos.h"
using namespace std;
Anfitrion::Anfitrion() {
    documento = 0;
    antiguedad = 0;
    puntuacion = 0.0;
    codigosAlojamientos = nullptr;
    cantidadAlojamientos = 0;
    capacidadAlojamientos = 0;
}
Anfitrion::Anfitrion(int documento, int antiguedad, float puntuacion) {
    this->documento = documento;
    this->antiguedad = antiguedad;
    this->puntuacion = puntuacion;
    this->codigosAlojamientos = nullptr;
    this->cantidadAlojamientos = 0;
    this->capacidadAlojamientos = 0;
}

Anfitrion::Anfitrion(const Anfitrion& copia) {
    documento = copia.documento;
    antiguedad = copia.antiguedad;
    puntuacion = copia.puntuacion;
    cantidadAlojamientos = copia.cantidadAlojamientos;
    capacidadAlojamientos = copia.capacidadAlojamientos;
    if (copia.codigosAlojamientos && capacidadAlojamientos > 0) {
        codigosAlojamientos = new int[capacidadAlojamientos];
        consumorecursos::sumarMemoria(sizeof(int) * capacidadAlojamientos);
        for (int i = 0; i < cantidadAlojamientos; ++i){
            consumorecursos::contarIteracion();
            codigosAlojamientos[i] = copia.codigosAlojamientos[i];
        }
    } else {
        codigosAlojamientos = nullptr;
    }
}

Anfitrion& Anfitrion::operator=(const Anfitrion& copia) {
    if (this != &copia) {
        delete[] codigosAlojamientos;
        documento = copia.documento;
        antiguedad = copia.antiguedad;
        puntuacion = copia.puntuacion;
        cantidadAlojamientos = copia.cantidadAlojamientos;
        capacidadAlojamientos = copia.capacidadAlojamientos;
        if (copia.codigosAlojamientos && capacidadAlojamientos > 0) {
            codigosAlojamientos = new int[capacidadAlojamientos];
            consumorecursos::sumarMemoria(sizeof(int) * capacidadAlojamientos);
            for (int i = 0; i < cantidadAlojamientos; ++i){
                consumorecursos::contarIteracion();
                codigosAlojamientos[i] = copia.codigosAlojamientos[i];
            }
        } else {
            codigosAlojamientos = nullptr;
        }
    }
    return *this;
}


Anfitrion::~Anfitrion() {
    delete[] codigosAlojamientos;
}

int Anfitrion::getDocumento() const {
    return documento;
}
int Anfitrion::getAntiguedad() const {
    return antiguedad;
}
float Anfitrion::getPuntuacion() const {
    return puntuacion;
}
int Anfitrion::getCantidadAlojamientos() const {
    return cantidadAlojamientos;
}
const int* Anfitrion::getCodigosAlojamientos() const {
    return codigosAlojamientos;
}
void Anfitrion::setDocumento(int doc) {
    documento = doc;
}
void Anfitrion::setAntiguedad(int anti) {
    antiguedad = anti;
}
void Anfitrion::setPuntuacion(float punt) {
    puntuacion = punt;
}
void Anfitrion::agregarCodigoAlojamiento(int codigo) {
    if (capacidadAlojamientos == 0) {
        capacidadAlojamientos = 1;
        codigosAlojamientos = new int[capacidadAlojamientos];
        consumorecursos::sumarMemoria(sizeof(int) * capacidadAlojamientos);
    }
    if (cantidadAlojamientos == capacidadAlojamientos) {
        int nuevaCapacidad = capacidadAlojamientos * 2;
        int* nuevoArr = new int[nuevaCapacidad];
        consumorecursos::sumarMemoria(sizeof(int) * nuevaCapacidad);
        for (int i = 0; i < cantidadAlojamientos; ++i){
            consumorecursos::contarIteracion();
            nuevoArr[i] = codigosAlojamientos[i];
        }
        delete[] codigosAlojamientos;
        codigosAlojamientos = nuevoArr;
        capacidadAlojamientos = nuevaCapacidad;
    }
    codigosAlojamientos[cantidadAlojamientos++] = codigo;
}

void Anfitrion::mostrarInfo(ostream& salida) const {
salida << "Documento: " << documento << "\n"
       << "Antigüedad: " << antiguedad << " meses\n"
       << "Puntuación: " << puntuacion << "\n"
       << "Cantidad de alojamientos: " << cantidadAlojamientos << "\n";
    if (cantidadAlojamientos > 0) {
        salida << "Alojamientos: ";
        for (int i = 0; i < cantidadAlojamientos; ++i) {
            consumorecursos::contarIteracion();
            salida << codigosAlojamientos[i];
            if (i < cantidadAlojamientos - 1) salida << ", ";
        }
        salida << "\n";
    }
}

ostream& operator<<(ostream& salida, const Anfitrion& a) {
    a.mostrarInfo(salida);
    return salida;
}
