#ifndef FECHA_H
#define FECHA_H

#include <QtCore/qglobal.h>

class Fecha
{
private:
    int dia;
    int mes;
    int año;
public:
    Fecha();
    bool FechaIgual();
    bool FechaMenor();
    bool FechaRango();
    void mostrar();
};

#endif // FECHA_H
