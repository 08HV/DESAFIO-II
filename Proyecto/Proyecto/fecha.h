#ifndef FECHA_H
#define FECHA_H
#include <string>
#include <iostream>
using namespace std;

class Fecha
{
private:
    int dia;
    int mes;
    int año;

    static string nombreDiaSemana(int d, int m, int a);
    static string nombreMes(int m);
    static int calcularDiaSemana(int d, int m, int a);

public:
    Fecha();
    Fecha(int d, int m, int a);
    int getDia() const;
    int getMes() const;
    int getAño() const;
    void setFecha(int d, int m, int a);
    bool operator==(const Fecha& comparar) const;
    bool operator!=(const Fecha& comparar) const;
    bool operator<(const Fecha& comparar) const;
    bool operator<=(const Fecha& comparar) const;
    bool operator>(const Fecha& comparar) const;
    bool operator>=(const Fecha& comparar) const;
    void sumarDias(int dias);
    static bool esBisiesto(int año);
    static int diasEnMes(int mes, int año);
    static Fecha fechaDeCorte();
    void ingresarFecha();
    void mostrarFecha(ostream& salida = cout) const;
    friend ostream& operator<<(ostream& out, const Fecha& f);
};

#endif // FECHA_H
