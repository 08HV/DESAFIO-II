#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H
#include <iostream>
#include "Anfitrion.h"

using namespace std;

class Alojamiento
{
private:
    char* nombre;
    int codigoID;
    Anfitrion* anfitrion; // Relación con Anfitrion
    char* departamento;
    char* municipio;
    char* tipo;
    char* direccion;
    int precio;
    char amenidades[10][25];
    char reservasFuturas[365];
    int cantidadReservasFutu;
public:
    Alojamiento();
    Alojamiento(const char* nombre, int codigoID, Anfitrion* anfitrion, const char* departamento, const char* municipio, const char* tipo, const char* direccion,  int precio, char amenidades[10][25]);
    ~Alojamiento();

    const char* getNombre() const;
    int getCodigoID() const;
    Anfitrion* getAnfitrion() const;
    const char* getDepartamento() const;
    const char* getMunicipio() const;
    const char* getTipo() const;
    const char* getDireccion() const;
    int getPrecio() const;
    const char* getAmenidad(int i) const;
    int getCantidadReservasFutu() const;
    const char* getReservaFutura(int i) const;

    void setNombre(const char* nombre);
    void setAnfitrion(Anfitrion* anfitrion);
    void setDepartamento(const char* departamento);
    void setMunicipio(const char* municipio);
    void setTipo(const char* Tipo);
    void setDireccion(const char* direccion);
    void setPrecio(int precio);
    void setAmenidad(int idx, const char* amenidad);
    void agregarReservaFutura(char reserva);


    void estaDisponible(const char* fechaInicio, const char* fechaFin) const;
    void mostrarInfo();

};

#endif // ALOJAMIENTO_H
