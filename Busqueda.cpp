#include <iostream>
#include <vector>
#include "venta.h"
#include<map>
#include <iomanip>
#include <set>
#include<algorithm>
#include "Busqueda.h"
#include <set>

using namespace std;

void listarVentasCiudad(const vector<Venta>& ventas) {
    string ciudad;
    cout<<"ingrese la ciudad donde desea buscar: ";
    cin>>ciudad;
    cout<<"\n=== Ventas en ciudad: "<<ciudad<<" ==="<<endl;
    bool encontrado=false;
    for (const auto& v : ventas) {
        if (v.ciudad==ciudad) {
            encontrado=true;
            cout<<v.idVenta<<" | "<<v.fecha<<" | "<<v.pais<<" | "<<v.cliente<<" | "<<v.producto<<" | Cantidad="<<v.cantidad<<" x Precio="<<v.precioUnitario<<"=Monto="<<v.montoTotal<<" | Envío="<<v.medioEnvio<<" | Estado="<<v.estadoEnvio<<endl;
        }
    }
    if (!encontrado) cout<<"No hay ventas para "<<ciudad<<".\n";
}

void listarVentasRangoFechas(const vector<Venta>& ventas) {
    string fechaInicioStr, fechaFinStr;
    cout << "Ingrese la fecha de inicio (YYYY-MM-DD): ";
    cin >> fechaInicioStr;
    cout << "Ingrese la fecha de fin (YYYY-MM-DD): ";
    cin >> fechaFinStr;

    auto convertirFecha = [](const string& fechaStr) -> int {
        int anio, mes, dia;
        if (sscanf(fechaStr.c_str(), "%d-%d-%d", &anio, &mes, &dia) != 3) return -1;
        return anio * 10000 + mes * 100 + dia;
    };

    int inicio = convertirFecha(fechaInicioStr);
    int fin = convertirFecha(fechaFinStr);
    if (inicio == -1 || fin == -1) {
        cout << "Formato de fecha inválido.\n";
        return;
    }

    bool encontrado = false;
    for (const auto& v : ventas) {
        int fechaVenta = convertirFecha(v.fecha);
        if (fechaVenta >= inicio && fechaVenta <= fin) {
            cout << v.idVenta << " | " << v.fecha << " | " << v.pais << " | "
                 << v.cliente << " | " << v.producto << " | Cant=" << v.cantidad
                 << " x $" << v.precioUnitario << " = $" << v.montoTotal
                 << " | Envío=" << v.medioEnvio << " | Estado=" << v.estadoEnvio << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron ventas en el rango especificado.\n";
    }
}



void comparacionPaises(const vector<Venta>& ventas) {
    string pais1, pais2;
    cout << "Ingrese el primer país: ";
    cin >> pais1;
    cout << "Ingrese el segundo país: ";
    cin >> pais2;

    double total1 = 0, total2 = 0;
    map<string, int> prod1, prod2;
    map<string, int> env1, env2;

    for (const auto& v : ventas) {
        if (v.pais == pais1) {
            total1 += v.montoTotal;
            prod1[v.producto]++;
            env1[v.medioEnvio]++;
        } else if (v.pais == pais2) {
            total2 += v.montoTotal;
            prod2[v.producto]++;
            env2[v.medioEnvio]++;
        }
    }

    if (total1 == 0 && total2 == 0) {
        cout << "No se encontraron ventas en esos países.\n";
        return;
    }

    cout << "\n=== Comparación: " << pais1 << " vs " << pais2 << " ===" << endl;
    cout << "1) Monto total: " << pais1 << "=$" << total1 << " | " << pais2 << "=$" << total2 << endl;

    auto topClave = [](const map<string, int>& m) {
        return max_element(m.begin(), m.end(),
                           [](const auto& a, const auto& b) { return a.second < b.second; })->first;
    };

    if (!prod1.empty()) cout << "2) Producto más vendido en " << pais1 << ": " << topClave(prod1) << endl;
    if (!prod2.empty()) cout << "   Producto más vendido en " << pais2 << ": " << topClave(prod2) << endl;
    if (!env1.empty())  cout << "3) Medio de envío más usado en " << pais1 << ": " << topClave(env1) << endl;
    if (!env2.empty())  cout << "   Medio de envío más usado en " << pais2 << ": " << topClave(env2) << endl;
}




void comparacionProductos(const vector<Venta>& ventas) {
    string pais1, pais2, producto1, producto2;
    set<string> paisesDisponibles;
    set<string> productosDisponibles;

    // Crear sets con todos los países y productos válidos
    for (const auto& venta : ventas) {
        paisesDisponibles.insert(venta.pais);
        productosDisponibles.insert(venta.producto);
    }

    cout << "\n=== Comparación de productos entre dos países ===" << endl;

    // Ingreso y validación del primer país
    do {
        cout << "Ingrese el primer país: ";
        getline(cin >> ws, pais1);
        if (paisesDisponibles.find(pais1) == paisesDisponibles.end()) {
            cout << " País no encontrado. Intente de nuevo." << endl;
        }
    } while (paisesDisponibles.find(pais1) == paisesDisponibles.end());

    // Ingreso y validación del segundo país
    do {
        cout << "Ingrese el segundo país: ";
        getline(cin >> ws, pais2);
        if (paisesDisponibles.find(pais2) == paisesDisponibles.end()) {
            cout << " País no encontrado. Intente de nuevo." << endl;
        }
    } while (paisesDisponibles.find(pais2) == paisesDisponibles.end());

    // Ingreso y validación del primer producto
    do {
        cout << "Ingrese el nombre del primer producto: ";
        getline(cin >> ws, producto1);
        if (productosDisponibles.find(producto1) == productosDisponibles.end()) {
            cout << " Producto no encontrado. Intente de nuevo." << endl;
        }
    } while (productosDisponibles.find(producto1) == productosDisponibles.end());

    // Ingreso y validación del segundo producto
    do {
        cout << "Ingrese el nombre del segundo producto: ";
        getline(cin >> ws, producto2);
        if (productosDisponibles.find(producto2) == productosDisponibles.end()) {
            cout << " Producto no encontrado. Intente de nuevo." << endl;
        }
    } while (productosDisponibles.find(producto2) == productosDisponibles.end());

    // Variables de acumulación
    int cantidadPais1P1 = 0, cantidadPais1P2 = 0;
    double montoPais1P1 = 0, montoPais1P2 = 0;
    int cantidadPais2P1 = 0, cantidadPais2P2 = 0;
    double montoPais2P1 = 0, montoPais2P2 = 0;

    // Recorrido y comparación
    for (const auto& venta : ventas) {
        string pais = venta.pais;
        string producto = venta.producto;

        if ((pais == pais1 || pais == pais2)) {
            if (producto == producto1) {
                if (pais == pais1) {
                    cantidadPais1P1 += venta.cantidad;
                    montoPais1P1 += venta.montoTotal;
                } else {
                    cantidadPais2P1 += venta.cantidad;
                    montoPais2P1 += venta.montoTotal;
                }
            } else if (producto == producto2) {
                if (pais == pais1) {
                    cantidadPais1P2 += venta.cantidad;
                    montoPais1P2 += venta.montoTotal;
                } else {
                    cantidadPais2P2 += venta.cantidad;
                    montoPais2P2 += venta.montoTotal;
                }
            }
        }
    }

    // Mostrar resultados
    cout << "\nProducto: " << producto1 << endl;
    cout << pais1 << " -> Cantidad: " << cantidadPais1P1 << ", Monto total: $" << montoPais1P1 << endl;
    cout << pais2 << " -> Cantidad: " << cantidadPais2P1 << ", Monto total: $" << montoPais2P1 << endl;

    cout << "\nProducto: " << producto2 << endl;
    cout << pais1 << " -> Cantidad: " << cantidadPais1P2 << ", Monto total: $" << montoPais1P2 << endl;
    cout << pais2 << " -> Cantidad: " << cantidadPais2P2 << ", Monto total: $" << montoPais2P2 << endl;

}


void buscarProductosPorUmbral(const vector<Venta>& ventas){
    bool mayor,encontrado=false;
    string pais;
    double umbral;
    map<string, int> totCant;
    map<string, double> totMonto;
    cout<<"ingrese el pais donde desea buscar: ";
    cin>>pais;
    for (const auto& v : ventas) {
        if(v.pais==pais){
            cout<<"Ingrese el umbral (monto por el cual desea buscar por debajo): ";
            cin>>umbral;
            break;
        }
        else{
            cout<<"No se puede localizar el pais";
            return;
        }
    }
    for (const auto& v : ventas) {
        if (v.pais==pais) {
            totCant[v.producto]+=v.cantidad;
            totMonto[v.producto]+=v.montoTotal;
        }
    }
    cout<<"\n=== Productos con monto promedio "<<(mayor?"mayor" : "menor")<<" a $"<<umbral<<" en "<<pais<<" ==="<<endl;
    encontrado=false;
    for (const auto& p : totCant) {
        double avg=p.second > 0
                     ? totMonto[p.first] / p.second
                     : 0;
        if ((mayor && avg > umbral) || (!mayor && avg < umbral)) {
            cout<<p.first<<" (avg=$"<<avg<<")"<<endl;
            encontrado=true;
        }
    }
    if (!encontrado){
        cout<<"No se encontraron productos.\n";
    }
}


