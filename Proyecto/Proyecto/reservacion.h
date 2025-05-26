#ifndef RESERVACION_H
#define RESERVACION_H

#include "Fecha.h"
#include "Alojamiento.h"
#include "Huesped.h"
#include "string"
#include <algorithm>

using namespace std;
class Reservacion
{
private:
    Fecha fechaEntrada;
    int duracion;
    int codigoReserva;
    Alojamiento* alojamiento; // Relación con Alojamiento
    Huesped* huesped; // Relación con Huesped
    string metodoPago;
    Fecha fechaPago;
    unsigned int monto;
    char* anotaciones;
public:
    Reservacion();
    Reservacion(int codigoReserva, Alojamiento* alojamiento, Huesped* huesped,
    const Fecha& fechaEntrada, int duracion, const string& metodoPago,
    const Fecha& fechaPago,unsigned int monto, const char* anotaciones);
    Reservacion(const Reservacion& copia);
    Reservacion& operator=(const Reservacion& copia);
    ~Reservacion();

    // Get
    int getCodigoReserva() const;
    int getCodigoAlojamiento() const;
    int getDocHuesped() const;
    Alojamiento* getAlojamiento() const;
    Huesped* getHuesped() const;
    const Fecha& getFechaEntrada() const;
    int getDuracion() const;
    unsigned int getMonto() const;
    const string& getMetodoPago() const;
    const char* getAnotaciones() const;
    const Fecha& getFechaPago() const;
    // Set
    void setCodigoReserva(int codigo);
    void setAlojamiento(Alojamiento* alojamiento);
    void setHuesped(Huesped* huesped);
    void setFechaEntrada(const Fecha& fecha);
    void setDuracion(int duracion);
    void setMetodoPago(const string& metodo);
    void setFechaPago(const Fecha& fecha);
    void setMonto(unsigned int monto);
    void setAnotaciones(const char* anotaciones);

    bool estaActiva(const Fecha& fechaActual) const;
    void mostrarComprobante()const;
    bool secruza(const Fecha& inicio, int noches) const;
    Fecha getFechaFin() const;
};

#endif // RESERVACION_H
