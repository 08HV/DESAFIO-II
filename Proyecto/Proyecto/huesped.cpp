#include "huesped.h"
#include <iostream>
using namespace std;

Huesped::Huesped() {
    documento = 0;
    antiguedad = 0;
    puntuacion = 0.0;
}
Huesped::Huesped(int documento, int antiguedad, float puntuacion) {
    this->documento = documento;
    this->antiguedad = antiguedad;
    this->puntuacion = puntuacion;
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
// Método para mostrar información del huésped
void Huesped::mostrarInfo() const {
    cout << "Documento: " << documento << endl;
    cout << "Antigüedad en la plataforma: " << antiguedad << endl;
    cout << "Puntuación: " << puntuacion << endl;
}
