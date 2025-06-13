#include <iostream>
#include <vector>
#include "venta.h"
#include "Analisis.h"
#include "CargaCSV.h"
#include "Modificar.h"
#include "Busqueda.h"
#include <iostream>
using namespace std;

void Menu(vector<Venta>& ventas, int& op){
    op=0;
    cout<<"Usuario, Elija que tipo de operaciones desea realizar ingresando numéricamente cada una de las opciones:"<<endl;
    cout<<"1-->Estadísticas básicas\n2-->Modificar datos\n3-->Análisis dinámico (usted pone los parámetros)\n0-->Para volver\nOpción: ";
    cin>>op;
    while(op<0 || op>3 ){
        cout<<"Término inválido reingrese nuevamente: ";
        cin>>op;
    }
}

void Estadisticas(vector<Venta>& ventas, char& r, int& i){
    mostrarTopCiudadesPorPais(ventas);
    mostrarMontoTotalPorProductoPorPais(ventas);
    mostrarPromedioVentasPorCategoriaPorPais(ventas);
    mostrarMedioEnvioMasUtilizadoPorPais(ventas);
    mostrarMedioEnvioMasUtilizadoPorCategoria(ventas);
    mostrarDiaMayorVentas(ventas);
    mostrarEstadoEnvioMasFrecuentePorPais(ventas);
    mostrarProductoMasVendidoPorCantidad(ventas);
    mostrarProductoMenosVendidoPorCantidad(ventas);
    cout<<"¿Desea regresar o reimprimir? Ingrese R para regresar y A para imprimir: ";
    cin>>r;
    i=4;
    while(r=='A' && r=='a'&& r!='r' && r!='R'){
        i-=1;
        cout<<"Término inválido reingrese nuevamente. quedan ["<<i<<"] intentos: ";
        cin>>r;
    if(i<2){
        Menu(ventas,i);
        }
    }
    if(r=='A' || r=='a'){
        Estadisticas(ventas, r, i);   
    }
    if(r=='r' || r=='R'){
        Menu(ventas, i);
    }
}
void Modificacion(vector<Venta>& ventas, char& r, int& i){
    cout<<"Elija qué modificación desea realizar o ingrese R para regresar: "<<endl;
    cout<<"1-->Agregar una venta"<<endl;
    cout<<"2-->Borrar una venta"<<endl;
    cout<<"3-->Buscar y modificar datos de una venta\nOpción:";
    cin>>r;
    i=4;
    while((r<'1' || r>'5') && r!='r' && r!='R' ){
        i-=1;
        cout<<"Término inválido reingrese nuevamente. quedan ["<<i<<"] intentos: ";
        cin>>r;
        if(i<2){
            Menu(ventas,i);
        }
    }
    if(r=='1'){
        agregarVenta(ventas);
        Estadisticas(ventas,r,i);
    }
    if(r=='2'){
        eliminarVenta(ventas);
        Estadisticas(ventas,r,i);
    }
    if(r=='3'){
        modificarVenta(ventas);
        Estadisticas(ventas,r,i);
    }
    if(r=='r' || r=='R'){
        Menu(ventas, i);
    }
}

void Analisis(vector<Venta>& ventas, char& r, int& i){
    cout<<"Elija qué estadística desea consultar o ingrese R para regresar: "<<endl;
    cout<<"1-->Listado de ventas en una ciudad específica"<<endl;
    cout<<"2-->Listado de ventas realizadas en un rango de fechas por país"<<endl;
    cout<<"3-->Comparación de ventas, productos más vendidos y medio de envío más usado entre dos países"<<endl;
    cout<<"4-->Comparación entre dos países del total de ventas e ingresos de dos productos"<<endl;
    cout<<"5-->Buscar productos vendidos en promedio por debajo de un umbral y por país\nOpción:";
    cin>>r;
    i=4;
    while((r<'1' || r>'5') && r!='r' && r!='R' ){
        i-=1;
        cout<<"Término inválido reingrese nuevamente. quedan ["<<i<<"] intentos: ";
        cin>>r;
        if(i<2){
            Menu(ventas,i);
        }
    }
    if(r=='1'){
        listarVentasCiudad(ventas);
    }
    if(r=='2'){
        listarVentasRangoFechas(ventas);
    }
    if(r=='3'){
        comparacionProductos(ventas);
    }
    if(r=='4'){
        comparacionPaises(ventas);
    }
    if(r=='5'){
        buscarProductosPorUmbral(ventas);
    }
    if(r=='r' || r=='R'){
        Menu(ventas, i);
    }
}

int main() {
    int op=0;
    int i=0;
    char r;
    string archivo = "ventas_sudamerica.csv";
    vector<Venta> ventas = cargarVentasDesdeCSV(archivo);
    cout << "Se cargaron " << ventas.size() << " ventas desde el archivo." << endl;
    while(r!='s' && r!='S'){
        Menu(ventas, op);
        if (op==1){
            Estadisticas(ventas, r, i);     
        }
        if(op==2){
            Modificacion(ventas, r, i);
        }
        if(op==3){
            Analisis(ventas, r, i);
        }
        cout<<"¿Desea salir? Ingrese S, caso contrario N: ";
        cin>>r;
    }
    cout<<"END"<<endl;
    return 0;
}   
