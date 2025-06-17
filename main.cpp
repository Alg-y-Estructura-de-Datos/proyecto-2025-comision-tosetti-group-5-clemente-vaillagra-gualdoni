#include <iostream>
#include <vector>
#include "venta.h"
#include "Analisis.h"
#include "CargaCSV.h"
#include "Modificar.h"
#include "Busqueda.h"
#include <iostream>
using namespace std;

void Menu(int& op){
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
    int opcion=0;
    bool flag=false;
    cout<<"Elija qué opción desea visualizar: "<<endl;
    cout<<"1-->Top 5 de ciudades con mejores ventas por país\n2-->Monto total por producto por país\n"
    <<"3-->Promedio de ventas por categoría por país\n4-->Medio de envío más utilizado por país\n5-->Medio de envío más utilizado por categoría\n"
    <<"6-->Día con mayor ingreso por ventas\n7-->Estado de envío más frecuente por país\n8-->Producto más vendido por unidad\n"
    <<"9-->Producto menos vendido por unidad\nOpción: ";
    cin>>opcion;
    if(opcion==1){
        mostrarTopCiudadesPorPais(ventas);
    }
    if(opcion==2){
        mostrarMontoTotalPorProductoPorPais(ventas);
    }
    if(opcion==3){
        mostrarPromedioVentasPorCategoriaPorPais(ventas);
    }
    if(opcion==4){
        mostrarMedioEnvioMasUtilizadoPorPais(ventas);
    }
    if(opcion==5){
        mostrarMedioEnvioMasUtilizadoPorCategoria(ventas);
    }
    if(opcion==6){
        mostrarDiaMayorVentas(ventas);
    }
    if(opcion==7){
        mostrarEstadoEnvioMasFrecuentePorPais(ventas);
    }
    if(opcion==8){
        mostrarProductoMasVendidoPorCantidad(ventas);
    }
    if(opcion==9){
        mostrarProductoMenosVendidoPorCantidad(ventas);
    }
    cout<<"\n¿Desea regresar o ver más estadísticas? Ingrese R para regresar o A para reimprimir estadísticas: ";
    cin>>r;
    i=4;
    while(r<'1' && r>'9' && r!='a' && r!='A' && r!='r' && r!='R'){
        i-=1;
        cout<<"Término inválido reingrese nuevamente. quedan ["<<i<<"] intentos: ";
        cin>>r;
    if(i<2){
        Menu(i);
        }
    }
    if(r=='A' || r=='a'){
        Estadisticas(ventas, r, i);   
    }
    if(r=='r' || r=='R'){
        Menu(i);
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
            Menu(i);
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
        Menu(i);
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
            Menu(i);
        }
    }
    if(r=='1'){
        listarVentasCiudad(ventas);
    }
    if(r=='2'){
        listarVentasRangoFechas(ventas);
    }
    if(r=='3'){
        comparacionPaises(ventas);
    }
    if(r=='4'){
        comparacionProductos(ventas);
    }
    if(r=='5'){
        buscarProductosPorUmbral(ventas);
    }
    if(r=='r' || r=='R'){
        Menu(i);
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
        Menu(op);
        if (op==1){
            Estadisticas(ventas, r, i);     
        }
        if(op==2){
            Modificacion(ventas, r, i);
        }
        if(op==3){
            Analisis(ventas, r, i);
        }
        guardarVentasEnCSV(archivo,ventas);
        ventas=cargarVentasDesdeCSV(archivo);
        cout << "Se cargaron " << ventas.size() << " ventas desde el archivo." << endl;
        cout<<"¿Desea salir? Ingrese S, caso contrario N: ";
        cin>>r;
    }
    cout<<"END"<<endl;
    return 0;
}   
