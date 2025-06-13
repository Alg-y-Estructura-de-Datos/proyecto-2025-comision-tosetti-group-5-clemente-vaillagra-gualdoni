#include "CargaCSV.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include<iostream>
#include <algorithm>
using namespace std;

//Creamos una función que abra el archivo ventas_sudamerica.csv, lo lea línea por línea y almacene las ventas en un vector<Venta>

vector<Venta> cargarVentasDesdeCSV(const string& nombreArchivo) {
    vector<Venta> ventas;
    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open()) {
        cerr<<"No se pudo abrir el archivo: "<<nombreArchivo<<endl;
        return ventas;
    }

    getline(archivo, linea); // Saltar encabezado

    while (getline(archivo, linea)) {
    stringstream ss(linea);
    string campo;
    Venta venta;

    getline(ss, venta.idVenta, ';');
    getline(ss, venta.fecha, ';');
    getline(ss, venta.pais, ';');
    getline(ss, venta.ciudad, ';');
    getline(ss, venta.cliente, ';');
    getline(ss, venta.producto, ';');
    getline(ss, venta.categoria, ';');

    // cantidad
    getline(ss, campo, ';');
    campo.erase(remove(campo.begin(), campo.end(), '"'), campo.end()); // quitar comillas
    if (campo.empty()) {
        venta.cantidad = 0;
    } else {
        try {
            venta.cantidad = stoi(campo);
        } catch (const std::exception& e) {
            cerr<<"Error en 'cantidad': '"<<campo<<"' - "<<e.what()<<endl;
            continue;
        }
    }

    // precioUnitario
    getline(ss, campo, ';');
    campo.erase(remove(campo.begin(), campo.end(), '"'), campo.end()); // quitar comillas
    if (campo.empty()) {
        venta.precioUnitario = 0;
    } else {
        try {
            venta.precioUnitario = stod(campo);
        } catch (const std::exception& e) {
            cerr<<"Error en 'precioUnitario': '"<<campo<<"' - "<<e.what()<<endl;
            continue;
        }
    }

    // montoTotal
   getline(ss, campo, ';');
    campo.erase(remove(campo.begin(), campo.end(), '"'), campo.end()); // quitar comillas
    if (campo.empty()) {
        venta.montoTotal = 0;
    } else {
        try {
            venta.montoTotal = stod(campo);
        } catch (const std::exception& e) {
            cerr<<"Error en 'montoTotal': '"<<campo<<"' - "<<e.what()<<endl;
            continue;
        }
    }
    getline(ss, venta.medioEnvio, ';');
    getline(ss, venta.estadoEnvio, ';');

    ventas.push_back(venta);
}


    archivo.close();
    return ventas;
}
