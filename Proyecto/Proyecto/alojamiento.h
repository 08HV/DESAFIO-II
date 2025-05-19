#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include <QtCore/qglobal.h>

class Alojamiento
{
private:
    string Nombre;
    int CódigoID;
    Anfitrión* anfitrión;
    string Departamento;
    string Municipio;
    string Tipo;
    string Dirección;
    Int Precio;
    string* Amenidades;
    string* reservasFuturas;
public:
    Alojamiento();
    void estaDispo ();
    Void AgregarReserva();
    Void mostrar();
    Void filtros();
    Void EliminarReserva();

};

#endif // ALOJAMIENTO_H
