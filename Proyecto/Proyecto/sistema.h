#ifndef SISTEMA_H
#define SISTEMA_H

#include <QtCore/qglobal.h>

class Sistema
{
private:
    Alojamiento** alojamientos;
    int cantidadAlojamientos;

    Reservacion** reservaciones;
    int cantidadReservaciones;

    Anfitrion** anfitriones;
    int cantidadAnfitriones;

    Huesped** huespedes;
    int cantidadHuespedes;

public:
    Sistema();

    void cargarDatos();
    void guardarDatos();
    bool Ingreso();
    void menuPrincipal();

    Huesped* buscarHuesped();
    Anfitrion* buscarAnfitrion();
    Alojamiento* buscarAlojamiento();
    Reservacion* buscarReservacion();

    void buscarAlojamientosDisponibles();
    bool registrarReservacion();
    bool anularReservacion();
    void consultarReservasAnfitrion();

    // Actualizar histórico (VI)
    void actualizarHistorico();

    // Funcionalidad (VII)
    void mostrarRecursos();
};

#endif // SISTEMA_H
