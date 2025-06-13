#ifndef VENTA_H
#define VENTA_H
#include<iostream>
#include <string>
using namespace std;

//Crearemos un struct Venta para almacenar cada línea del archivo CSV.
struct Venta {
    string idVenta;
    string fecha;
    string pais;
    string ciudad;
    string cliente;
    string producto;
    string categoria;
    int cantidad;
    double precioUnitario;
    double montoTotal;
    string medioEnvio;
    string estadoEnvio;
};

#endif
