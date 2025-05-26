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
    static const int HUESPEDES = 100;
    static const int ANFITRIONES = 100;
    static const int ALOJAMIENTOS = 100;
    Alojamiento** alojamientos;
    int cantidadAlojamientos;


    Reservacion** reservaciones;
    int cantidadReservaciones;
    int capacidadReservaciones;
    int ultimoCodigoReserva;
    Fecha fechaCorteActual;

    Anfitrion** anfitriones;
    int cantidadAnfitriones;

    Huesped** huespedes;
    int cantidadHuespedes;

public:
    Sistema();
    ~Sistema();

    void gestionarFechaCorte();
    void cargarAlojamientos(const char* archivo);
    void cargarAnfitriones(const char* archivo);
    void cargarHuespedes(const char* archivo);
    void cargarReservacion(const char* archivo);
    void cargarDatos();
    void guardarDatos();
    bool Ingreso();
    void menuPrincipalAnfitrion(Anfitrion* a);
    void menuPrincipalHuesped(Huesped* h);
    Huesped* buscarHuesped(int documento) const;
    Anfitrion* buscarAnfitrion(int documento) const;
    Alojamiento* buscarAlojamiento(int codigo) const;
    Reservacion* buscarReservacion(int codigo) const;
    void guardarReservas(const char* archivo);
    void buscarAlojamientosDisponibles(const Fecha& inicio, int noches, const string& municipio, int costoMax, float puntuacionMin)const;
    bool registrarReservacionPorCodigo(Huesped* huesped, int codigoAlojamiento, Fecha fechaEntrada, int noches);
    bool registrarReservacionPorBusqueda(Huesped* huesped);
    void anularReservacion();
    void consultarReservacionesAnfitrion(Anfitrion* anfitrion, const Fecha& desde, const Fecha& hasta) const;
    void mostrarReservasDeHuesped(Huesped* h) const;
    int generarCodigoReserva();

    bool huespedTieneReservaEnRango(Huesped* huesped, const Fecha& inicio, int noches) const;
    bool alojamientoDisponible(Alojamiento* a, const Fecha& inicio, int noches) const;

    void agregarReservacion(Reservacion* reservacion);

    // Actualizar histórico (VI)
    void actualizarHistorico(const Fecha& fechaCorte);

    bool fechaValida(const Fecha& f) const;

    // Funcionalidad (VII)
    void mostrarRecursos();
};

#endif // SISTEMA_H
