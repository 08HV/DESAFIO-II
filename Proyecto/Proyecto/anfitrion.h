#ifndef ANFITRION_H
#define ANFITRION_H

#include <QtCore/qglobal.h>

class Anfitrion
{
private:
    int documento;
    int antiguedad;
    float puntuacion;
    int* codigosAlojamientos;
    int cantidadAlojamientos;
public:
    Anfitrion();
    void cargarDesdeArchivo();
    void guardarEnArchivo();
    void agregarAlojamiento();
    void consultarReservasActivas();
    void actualizarHistorico();

};

#endif // ANFITRION_H
