#ifndef SISTEMA_H
#define SISTEMA_H
#include "Alojamiento.h"
#include "Reservacion.h"
#include "Fecha.h"
#include "Anfitrion.h"
#include "Huesped.h"
#include <string>

class Sistema
{
private:
    Alojamiento** alojamientos;
    int cantidadAlojamientos;


    Reservacion** reservaciones;
    int cantidadReservaciones;
    int capacidadReservaciones;
    int ultimoCodigoReserva;

    Anfitrion** anfitriones;
    int cantidadAnfitriones;

    Huesped** huespedes;
    int cantidadHuespedes;

public:
    Sistema();
    ~Sistema();

    void cargarAlojamientos(const char* archivo);
    void cargarAnfitriones(const char* archivo);
    void cargarHuespedes(const char* archivo);
    void cargarDatos();
    void guardarDatos();
    bool Ingreso();
    void menuPrincipal();
    Huesped* buscarHuesped(int documento) const;
    Anfitrion* buscarAnfitrion(int documento) const;
    Alojamiento* buscarAlojamiento(int codigo) const;
    Reservacion* buscarReservacion(int codigo) const;

    void buscarAlojamientosDisponibles(const Fecha& inicio, int noches, const string& municipio, int costoMax, float puntuacionMin)const;
    bool registrarReservacion();
    bool anularReservacion();
    void consultarReservacionesAnfitrion(Anfitrion* anfitrion, const Fecha& desde, const Fecha& hasta) const;

    int generarCodigoReserva();

    bool huespedTieneReservaEnRango(Huesped* huesped, const Fecha& inicio, int noches) const;
    bool alojamientoDisponible(Alojamiento* a, const Fecha& inicio, int noches) const;

    void agregarReservacion(Reservacion* reservacion);

    // Actualizar histórico (VI)
    void actualizarHistorico(const Fecha& fechaCorte);

    // Funcionalidad (VII)
    void mostrarRecursos();
};

#endif // SISTEMA_H
