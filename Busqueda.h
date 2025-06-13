
#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include<iostream>
#include <vector>
#include <string>
#include "venta.h"
#include "CargaCSV.h"

using namespace std;

void listarVentasCiudad(const vector<Venta>& ventas);
void listarVentasRangoFechas(const vector<Venta>& ventas);
void comparacionPaises(const vector<Venta>& ventas);
void comparacionProductos(const vector<Venta>& ventas);
void buscarProductosPorUmbral(const vector<Venta>& ventas);

#endif

