#ifndef RESERVACION_H
#define RESERVACION_H

#include <QtCore/qglobal.h>

class Reservacion
{
private:
    char fecha[32];
    int duracion;
    int codigoReserva;
    int codigoAlojamiento; // Relación con Alojamiento
    int docHuesped; // Relación con Huesped
    char metodoPago[20];
    char fechaPago[32];
    float monto;
    char anotaciones[1000];
public:
    Reservacion();
    void cargarDesdeArchivo();
    void guardarEnArchivo();
    bool estaActiva();
    void mostrarComprobante();
    bool secruza();
};

#endif // RESERVACION_H
