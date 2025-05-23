#ifndef HUESPED_H
#define HUESPED_H
#include <string>
using namespace std;

class Huesped
{
private:
    int documento;
    int antiguedad;
    float puntuacion;
public:
    Huesped();
    Huesped(int documento, int antiguedad, float puntuacion);
    //get
    int getDocumento() const;
    int getAntiguedad() const;
    float getPuntuacion() const;
    //set
    void setDocumento(int doc);
    void setAntiguedad(int ant);
    void setPuntuacion(float punt);

    void mostrarInfo() const;
};

#endif // HUESPED_H
