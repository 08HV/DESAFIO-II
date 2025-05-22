#ifndef SISTEMA_H
#define SISTEMA_H
#include "Alojamiento.h"
#include "Reservacion.h"

#include <QtCore/qglobal.h>

class Sistema
{
private:
    Alojamiento** alojamientos;
    int cantidadAlojamientos;
    int capacidadAlojamientos;

    Reservacion** reservaciones;
    int cantidadReservaciones;
    int capacidadReservaciones;

    Anfitrion** anfitriones;
    int cantidadAnfitriones;

    Huesped** huespedes;
    int cantidadHuespedes;

public:
    Sistema();
    ~Sistema();

    void cargarAlojamientos(const char* archivo);
    void cargarDatos();
    void guardarDatos();
    bool Ingreso();
    void menuPrincipal();

    Huesped* buscarHuesped();
    Anfitrion* buscarAnfitrion();
    Alojamiento* buscarAlojamiento(int codigo) const;
    Reservacion* buscarReservacion(int codigo) const;

    void buscarAlojamientosDisponibles(const Fecha& inicio, int noches, const char* municipio, int costoMax, float puntuacionMin)const;
    bool registrarReservacion();
    bool anularReservacion();
    void consultarReservasAnfitrion();

    int generarCodigoReserva();

    bool huespedTieneReservaEnRango(Huesped* huesped, const Fecha& inicio, int noches) const;
    bool alojamientoDisponible(Alojamiento* alojamiento, const Fecha& inicio, int noches) const;

    void agregarReservacion(Reservacion* reservacion);

    // Actualizar histórico (VI)
    void actualizarHistorico();

    // Funcionalidad (VII)
    void mostrarRecursos();
};

#endif // SISTEMA_H
