#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H
#include <iostream>
#include <string>
#include "Anfitrion.h"

using namespace std;

class Alojamiento
{
private:
    string nombre;
    int codigoID;
    Anfitrion* anfitrion; // Relación con Anfitrion
    string departamento;
    string municipio;
    string tipo;
    string direccion;
    int precio;
    string amenidades[10];
    char reservasFuturas[365];
    int cantidadReservasFutu;
public:
    Alojamiento();
    Alojamiento(const string& nombre, int codigoID, Anfitrion* anfitrion, const string& departamento, const string& municipio, const string& tipo, const string& direccion,  int precio, string amenidades[10]);

    const string& getNombre() const;
    int getCodigoID() const;
    Anfitrion* getAnfitrion() const;
    const string& getDepartamento() const;
    const string& getMunicipio() const;
    const string& getTipo() const;
    const string& getDireccion() const;
    int getPrecio() const;
    const string& getAmenidad(int i) const;
    int getCantidadReservasFutu() const;
    const char* getReservaFutura(int i) const;

    void setNombre(const string& nombre);
    void setAnfitrion(Anfitrion* anfitrion);
    void setDepartamento(const string& departamento);
    void setMunicipio(const string& municipio);
    void setTipo(const string& Tipo);
    void setDireccion(const string& direccion);
    void setPrecio(int precio);
    void setAmenidad(int i, const string& amenidad);

    void agregarReservaFutura(char reserva);
    void estaDisponible(const char* fechaInicio, const char* fechaFin) const;
    void mostrarInfo()const;

};

#endif // ALOJAMIENTO_H
