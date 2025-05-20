#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H
#include <iostream>
#include <QtCore/qglobal.h>

using namespace std;

class Alojamiento
{
private:
    char Nombre[20];
    int CódigoID;
    Anfitrión* anfitrión; // Relación con Anfitrion
    char Departamento[20];
    char Municipio[10];
    char Tipo[12];
    char Dirección[25];
    int Precio;
    char Amenidades[10][25];
    char reservasFuturas[365];
    int cantidadReservasFutu;
public:
    Alojamiento();
    void estaDispo ();
    void AgregarReserva();
    void mostrar();
    void filtros();
    void EliminarReserva();

};

#endif // ALOJAMIENTO_H
