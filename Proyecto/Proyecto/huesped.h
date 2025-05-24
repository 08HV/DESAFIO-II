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
    int* codigosReservas;
    int cantidadReservas;
    int capacidadReservas;
public:
    Huesped();
    Huesped(int documento, int antiguedad, float puntuacion);
    Huesped(const Huesped& copia);
    Huesped& operator=(const Huesped& copia);
    ~Huesped();
    //get
    int getDocumento() const;
    int getAntiguedad() const;
    float getPuntuacion() const;
    int getCantidadReservas() const;
    const int* getCodigosReservas() const;
    //set
    void setDocumento(int doc);
    void setAntiguedad(int ant);
    void setPuntuacion(float punt);

    void agregarCodigoReserva(int codigo);

    void mostrarInfo() const;
};

#endif // HUESPED_H
