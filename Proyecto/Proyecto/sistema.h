#ifndef SISTEMA_H
#define SISTEMA_H
#include "Alojamiento.h"

#include <QtCore/qglobal.h>

class Sistema
{
private:
    Alojamiento** alojamientos;
    int cantidadAlojamientos;
    int capacidadAlojamientos;

    Reservacion** reservaciones;
    int cantidadReservaciones;

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
    Reservacion* buscarReservacion();

    void buscarAlojamientosDisponibles(const Fecha& inicio, int noches, const char* municipio, int costoMax, float puntuacionMin)const;
    bool registrarReservacion();
    bool anularReservacion();
    void consultarReservasAnfitrion();

    // Actualizar histórico (VI)
    void actualizarHistorico();

    // Funcionalidad (VII)
    void mostrarRecursos();
};

#endif // SISTEMA_H
