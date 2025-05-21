#ifndef HUESPED_H
#define HUESPED_H

#include <QtCore/qglobal.h>

class Huesped
{
private:
    int documento;
    int antiguedad;
    float puntuacion;
    int* codigosReservas;
    int cantidadReservas;
public:
    Huesped();
    void cargarDesdeArchivo();
    void guardarEnArchivo();
    bool reservarAlojamiento();
    bool anularReservacion();
    void agregarCodigoReserva(int codigoNuevo);
    bool tieneReservaEnFechas();
};

#endif // HUESPED_H
