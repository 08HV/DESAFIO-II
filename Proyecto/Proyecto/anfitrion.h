#ifndef ANFITRION_H
#define ANFITRION_H

#include <iostream>
using namespace std;
class Anfitrion
{
private:
    int documento;
    int antiguedad;
    float puntuacion;
    int* codigosAlojamientos;
    int cantidadAlojamientos;
    int capacidadAlojamientos;
public:
    Anfitrion();
    Anfitrion(int documento, int antiguedad, float puntuacion);
    Anfitrion(const Anfitrion& copia);
    Anfitrion& operator=(const Anfitrion& copia);
    ~Anfitrion();
    // Get
    int getDocumento() const;
    int getAntiguedad() const;
    float getPuntuacion() const;
    int getCantidadAlojamientos() const;
    const int* getCodigosAlojamientos() const;

    // Set
    void setDocumento(int doc);
    void setAntiguedad(int ant);
    void setPuntuacion(float punt);

    void mostrarInfo(ostream& salida = cout) const;

    friend ostream& operator<<(ostream& salida, const Anfitrion& a);
};

#endif // ANFITRION_H
