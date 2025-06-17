#ifndef CARGACSV_H
#define CARGACSV_H

#include<iostream>
#include <vector>
#include <string>
#include <fstream>
#include "venta.h"
using namespace std;

//Creamos una función que abra el archivo ventas_sudamerica.csv

vector<Venta> cargarVentasDesdeCSV(const string& nombreArchivo);

// Funcion para guardar los cambios en el csv
void guardarVentasEnCSV(const string& nombreArchivo, const vector<Venta>& ventas);

#endif
