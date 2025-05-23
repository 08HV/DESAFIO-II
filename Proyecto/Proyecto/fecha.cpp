#include <iostream>
#include "fecha.h"
#include <string>
#include <limits>


Fecha::Fecha() {
        dia = 8;
        mes = 9;
        año = 2000;
}
Fecha::Fecha(int d, int m, int a) {
    setFecha(d, m, a);
}

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAño() const { return año; }

void Fecha::setFecha(int d, int m, int a) {
    if (a < 0) a = 2000;
    if (m<1 || m>=13)m=1;
    int dim = diasEnMes(m, a);
    if (d<1 || d>dim)d=1;
    dia = d;
    mes = m;
    año = a;
}

bool Fecha::operator==(const Fecha& comparar) const {
    return dia == comparar.dia && mes == comparar.mes && año == comparar.año;
}
bool Fecha::operator!=(const Fecha& comparar) const {
    return !(*this == comparar);
}
bool Fecha::operator<(const Fecha& comparar) const {
    if (año != comparar.año) return año < comparar.año;
    if (mes != comparar.mes) return mes < comparar.mes;
    return dia < comparar.dia;
}
bool Fecha::operator<=(const Fecha& comparar) const {
    return (*this < comparar) || (*this == comparar);
}
bool Fecha::operator>(const Fecha& comparar) const {
    return !(*this <= comparar);
}
bool Fecha::operator>=(const Fecha& comparar) const {
    return !(*this < comparar);
}

void Fecha::sumarDias(int dias) {
    while (dias > 0) {
        int dim = diasEnMes(mes, año);
        if (dia + dias <= dim) {
            dia += dias;
            return;
        } else {
            dias -= (dim - dia + 1);
            dia = 1;
            mes++;
            if (mes > 12) {
                mes = 1;
                año++;
            }
        }
    }
}

void Fecha::mostrarFecha(ostream& salida) const {
    if (dia < 10) salida << '0';
    salida << dia << '/';
    if (mes < 10) salida << '0';
    salida << mes << '/' << año;
}

bool Fecha::esBisiesto(int a) {
    return ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0));
}

int Fecha::diasEnMes(int m, int a) {
    static const int diasMes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (m == 2 && esBisiesto(a)) return 29;
    if (m >= 1 && m <= 12) return diasMes[m - 1];
    return 30;
}

string Fecha::nombreMes(int m) {
    static const string nombres[] = {
        "enero", "febrero", "marzo", "abril", "mayo", "junio", "julio",
        "agosto", "septiembre", "octubre", "noviembre", "diciembre"
    };
    if (m >= 1 && m <= 12) return nombres[m - 1];
    return "mes";
}

int Fecha::calcularDiaSemana(int d, int m, int a) {
    if (m < 3) {
        m += 12;
        a--;
    }
    int k = a % 100;
    int j = a / 100;
    int f = d + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j;
    return (f % 7);
}

string Fecha::nombreDiaSemana(int d, int m, int a) {
    static const string dias[] = { "sábado", "domingo", "lunes", "martes", "miércoles", "jueves", "viernes" };
    int i = calcularDiaSemana(d, m, a);
    return dias[i];
}


Fecha Fecha::fechaDeCorte() {
    cout << "Ingrese la fecha de corte (dd mm aaaa): ";
    int d, m, a;
    while (true) {
        cin >> d >> m >> a;
        if (a > 0 && m >= 1 && m <= 12 && d >= 1 && d <= diasEnMes(m, a))
            break;
        cout << "Fecha inválida. Intente de nuevo (dd mm aaaa): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return Fecha(d, m, a);
}
void Fecha::ingresarFecha() {
    int d, m, a;
    while (true) {
        cout << "Ingrese la fecha (dd mm aaaa): ";
        cin >> d >> m >> a;
        if (cin.fail() || a < 1 || m < 1 || m >= 13 || d < 1 || d > diasEnMes(m, a)) {
            cout << "Fecha inválida. Intente de nuevo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            setFecha(d, m, a);
            break;
        }
    }
}


