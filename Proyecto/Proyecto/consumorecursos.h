#ifndef CONSUMORECURSOS_H
#define CONSUMORECURSOS_H
#include <cstddef>
#include <iostream>
using namespace std;

class consumorecursos {
private:
    static int iteraciones;
    static size_t totalmemoria;

public:
    static void contarIteracion(int cantidad = 1);
    static void sumarMemoria(size_t bytes);
    static void mostrar();
};

#endif // CONSUMORECURSOS_H
