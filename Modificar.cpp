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
    cout<<"\n=== Agregar Nueva Venta ==="<<endl;
    cout<<"ID Venta: ";
    cin>>v.idVenta;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Fecha (dd/mm/aaaa): ";
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
    int a=4;
    char criterio;
    string valor;
    cout<<"\n=== Eliminar Venta ==="<<endl;
    cout<<"¿Eliminar por\n1-->Pais\n2-->Ciudad? :";
    cin>>criterio;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Ingrese "<<criterio<<": ";
    getline(cin, valor);
    vector<int> indices;
    for (size_t i = 0; i < ventas.size(); ++i) {
        if ((criterio == '1' && ventas[i].pais == valor) || (criterio == '2' && ventas[i].ciudad == valor)) {
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
    int opcion;
    cout<<"Selecciona el número de la venta a eliminar: ";
    cin>>opcion;
    while(opcion < 1 || opcion > static_cast<int>(indices.size())){
        a-=1;
        cout<<"Opción inválida. No se eliminó ninguna venta. reingrese nuevamente.\nQuedan ["<<a<<"intentos: ";
        cin>>opcion;
        if(a<1){
            return;
        }
    }
    ventas.erase(ventas.begin() + indices[opcion - 1]);
    cout<<"Venta eliminada correctamente!\n"<<endl;
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


