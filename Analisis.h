#ifndef ANALISIS_H
#define ANALISIS_H

#include<iostream>
#include <vector>
#include "venta.h"

using namespace std;
void mostrarTopCiudadesPorPais(const vector<Venta>& ventas);
void mostrarMontoTotalPorProductoPorPais(const vector<Venta>& ventas);
void mostrarPromedioVentasPorCategoriaPorPais(const vector<Venta>& ventas);
void mostrarMedioEnvioMasUtilizadoPorPais(const vector<Venta>& ventas);
void mostrarMedioEnvioMasUtilizadoPorCategoria(const vector<Venta>& ventas);
void mostrarDiaMayorVentas(const vector<Venta>& ventas);
void mostrarEstadoEnvioMasFrecuentePorPais(const vector<Venta>& ventas);
void mostrarProductoMasVendidoPorCantidad(const vector<Venta>& ventas);
void mostrarProductoMenosVendidoPorCantidad(const vector<Venta>& ventas);


#endif
