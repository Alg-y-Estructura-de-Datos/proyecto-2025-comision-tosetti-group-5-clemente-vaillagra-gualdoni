#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "venta.h"
#include <map>
#include "Modificar.h"
#include "CargaCSV.h"
using namespace std;

void agregarVenta(vector<Venta>& ventas) {
    Venta v;
    string input;
    bool duplicate = true;
    cout<<"\n=== Agregar Nueva Venta ==="<<endl;
    while (duplicate==true) {
        cout<<"ID Venta: ";
        cin>>v.idVenta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        for (const auto& venta : ventas) {
            if (venta.idVenta != v.idVenta) {
                duplicate = false;
            }
            else{
                duplicate = true;
                break;
            }
        }
        if (duplicate) {
            cout<<"Error: El ID '"<<v.idVenta<<"' ya existe.\n";
            cout<<"1-->Ingresar otro ID\n2-->Para abortar operación ingrese R\nOpción: ";
            if (input == "r" || input=="R") {
                cout<<"Operación abortada.\n"<<endl;
                return;
            }
            getline(cin, input);
            continue;
        }
        break;
    }

    cout<<"Fecha en el siguiente formato(2024-12-31): ";
    getline(cin, v.fecha);
    cout<<"País: ";
    getline(cin, v.pais);
    cout<<"Ciudad: ";
    getline(cin, v.ciudad);
    cout<<"Cliente: ";
    getline(cin, v.cliente);
    cout<<"Producto: ";
    getline(cin, v.producto);
    cout<<"Categoría: ";
    getline(cin, v.categoria);
    cout<<"Cantidad: ";
    cin>>v.cantidad;
    cout<<"Precio unitario: ";
    cin>>v.precioUnitario;
    cout<<"Monto total: ";
    cin>>v.montoTotal;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Medio de envío: ";
    getline(cin, v.medioEnvio);
    cout<<"Estado de envío: ";
    getline(cin, v.estadoEnvio);
    ventas.push_back(v);
    cout<<"\nVenta agregada correctamente!\n"<<endl;
}

void eliminarVenta(vector<Venta>& ventas) {
    int a=4, criterio;
    string valor, aux;
    cout<<"\n=== Eliminar Venta ==="<<endl;
    cout<<"¿Eliminar por\n1-->País\n2-->Ciudad\nOpción:";
    cin>>criterio;
    while(criterio != 1 && criterio != 2){
        cout<<"Término inválido. Reingrese nuevamente: ";
        cin>>criterio;
    }
    if(criterio == 1){
        aux = "país";
    }
    else{
        aux = "ciudad";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Ingrese "<<aux<<": ";
    getline(cin, valor);
    vector<int> indices;
    for (size_t i = 0; i < ventas.size(); ++i) {
        if ((criterio == 1 && ventas[i].pais == valor) || (criterio == 2 && ventas[i].ciudad == valor)) {
            indices.push_back(i);
            cout<<indices.size()<<". ID="<<ventas[i].idVenta
                <<" | "<<ventas[i].pais<<" / "<<ventas[i].ciudad
                <<" | Monto="<<ventas[i].montoTotal<<endl;
        }
    }
    if (indices.empty()){
        cout<<"No se encontraron ventas para '"<<valor<<"'.\n";
        return;
    }
    string idVentaEliminar;
    cout << "Selecciona el ID de la venta a eliminar: ";
    cin >> idVentaEliminar;

    bool eliminado = false;
    for (size_t i = 0; i < ventas.size(); ++i) {
        if (ventas[i].idVenta==idVentaEliminar){
            ventas.erase(ventas.begin() + i);
            cout << "Venta eliminada.\n";
            eliminado = true;
            break;
        }
    }
    if (!eliminado) {
        cout << "No se encontró la venta con ID " << idVentaEliminar << ".\n";
        return;
    }
}

void modificarVenta(vector<Venta>& ventas) {
    string id;
    cout<<"\n=== Modificar Venta ==="<<endl;
    cout<<"Ingrese ID de venta: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    bool encontrado=false;
    for (auto& v : ventas) {
        if (v.idVenta==id){
            encontrado=true;
            cout<<"Venta encontrada. Ingrese nuevos valores (deje vacío para mantener):"<<endl;
            string input;
            cout<<"Fecha ("<<v.fecha<<"): ";
            getline(cin, input);
            if (!input.empty()){
                v.fecha=input;
                }
            cout<<"País ("<<v.pais<<"): ";
            getline(cin, input);
            if (!input.empty()){
                v.pais=input;
                }
            cout<<"Ciudad ("<<v.ciudad<<"): ";
            getline(cin, input);
            if (!input.empty()){
                v.ciudad=input;
                }
            cout<<"Cliente ("<<v.cliente<<"): ";
            getline(cin, input);
            
            if (!input.empty()){
                v.cliente=input;
                }
            cout<<"Producto ("<<v.producto<<"): ";
            getline(cin, input);
            if (!input.empty()){
                v.producto=input;
                }
            cout<<"Categoría ("<<v.categoria<<"): ";
            getline(cin, input);
            if (!input.empty()){
                v.categoria=input;
            }
            cout<<"Cantidad ("<<v.cantidad<<"): ";
            getline(cin, input);
            if (!input.empty()){
                v.cantidad=stoi(input);
                }
            cout<<"Precio unitario ("<<v.precioUnitario<<"): ";
            getline(cin, input);
            if (!input.empty()){
                v.precioUnitario=stod(input);
            }
            cout<<"Monto total ("<<v.montoTotal<<"): ";
            getline(cin, input);
            if (!input.empty()){
                v.montoTotal = stod(input);
                }
            cout<<"Medio de envío ("<<v.medioEnvio<<"): ";
            getline(cin, input);
            if (!input.empty()){
                v.medioEnvio=input;
                }
            cout<<"Estado de envío ("<<v.estadoEnvio<<"): ";
            getline(cin, input);
            if (!input.empty()){
                v.estadoEnvio=input;
                }
            cout<<"\nVenta modificada correctamente!\n"<<endl;
            break;
        }
    }
    if (!encontrado) {
    cout<<"No se encontró ninguna venta con ID -->'"<<id<<"'.\n"<<endl;
    }
}


