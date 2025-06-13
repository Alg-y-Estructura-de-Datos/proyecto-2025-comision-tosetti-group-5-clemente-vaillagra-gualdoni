#include <iostream>
#include <vector>
#include "venta.h"
#include<map>
#include<algorithm>
#include "Busqueda.h"

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
    if (!encontrado) cout<<"[INFO] No hay ventas para "<<ciudad<<".\n";
}

void listarVentasRangoFechas(const vector<Venta>& ventas) {
    string pais,fechaInicio,fechaFin;
    bool encontrado=false;
    cout<<"ingrese el pais donde desea buscar: ";
    cin>>pais;
    for (const auto& v : ventas) {
        if(v.pais==pais){
            encontrado=true;
            cout<<"Ingrese la fecha de inicio en el siguiente formato 2024-01-01: ";
            cin>>fechaInicio;
            cout<<"Ingrese la fecha final: ";
            cin>>fechaFin;
        }
        else{
            cout<<"No se puede localizar el pais";
            return;
        }
    }
    //Creamos un formato de clave para poder comparar las fechas
    auto parseFecha=[&](const string& f) {
        int d=stoi(f.substr(0, 2));
        int m=stoi(f.substr(3, 2));
        int y=stoi(f.substr(6, 4));
        return y * 10000 + m * 100 + d;
    };

    int ini=parseFecha(fechaInicio);
    int fin=parseFecha(fechaFin);
    cout<<"\n=== Ventas en "<<pais<<" entre "<<fechaInicio<<" y "<<fechaFin<<" ==="<<endl;
    encontrado=false;
    for (const auto& v : ventas) {
        if (v.pais==pais) {
            int fechaInt=parseFecha(v.fecha);
            if (fechaInt>=ini && fechaInt<=fin) {
                encontrado=true;
                cout<<v.idVenta<<" | "<<v.fecha<<" | "<<v.ciudad<<" | Producto="<<v.producto<<" | Monto="<<v.montoTotal<<endl;
            }
        }
    }
    if (!encontrado) cout<<" No hay ventas en ese rango.\n";
}

void comparacionPaises(const vector<Venta>& ventas) {
    double total1=0, total2=0;
    map<string, int> prod1, prod2;
    map<string, int> env1, env2;
    string pais1,pais2;
    bool encontrado=false;
    cout<<"ingrese el primer pais: ";
    cin>>pais1;
    for (const auto& v : ventas){
        if(v.pais==pais1){
            cout<<"ingrese el segundo: ";
            cin>>pais2;
            for (const auto& v : ventas) {
                if(v.pais==pais2){
                encontrado=true;
                break;
                }
            }
        }
        if(encontrado==true){
            break;
        }
    }
    if(!encontrado){
        cout<<"No se puede localizar el pais";
        return;
    }
    for (const auto& v : ventas) {
        if (v.pais == pais1) {
            total1 += v.montoTotal;
            prod1[v.producto]++;
            env1[v.medioEnvio]++;
        } 
        else if (v.pais == pais2) {
            total2 += v.montoTotal;
            prod2[v.producto]++;
            env2[v.medioEnvio]++;
        }
    }

    cout<<"\n=== Comparación: "<<pais1<<" vs "<<pais2<<" ==="<<endl;
    cout<<"1) Monto total: "<<pais1<<"=$"<<total1<<" | "<<pais2<<"=$"<<total2<<endl;

    auto topClave=[&](const map<string, int>& m) {
        return max_element(
            m.begin(), m.end(),
            [](auto& a, auto& b) { return a.second < b.second; }
        )->first;
    };

    if (!prod1.empty()){
        cout<<"2) Producto más vendido en "<<pais1<<": "<<topClave(prod1)<<endl;
    }
    if (!prod2.empty()){ 
        cout<<"   Producto más vendido en "<<pais2<<": "<<topClave(prod2)<<endl;
    }
    if (!env1.empty()){ 
        cout<<"3) Medio envío más usado en "<<pais1<<": "<<topClave(env1)<<endl;
    }
    if (!env2.empty()){
        cout<<"   Medio envío más usado en "<<pais2<<": "<<topClave(env2)<<endl;
    }
}

void comparacionProductos(const vector<Venta>& ventas){
    int c1=0, c2=0;
    double m1=0, m2=0;
    string p1,p2;
    bool encontrado=false;
    cout<<"ingrese el primer pais: ";
    cin>>p1;
    for (const auto& v : ventas){
        if(v.pais==p1){
            cout<<"ingrese el segundo: ";
            cin>>p2;
            for (const auto& v : ventas) {
                if(v.pais==p2){
                encontrado=true;
                break;
                }
            }
        }
        if(encontrado==true){
            break;
        }
    }
    if(!encontrado){
        cout<<"No se puede localizar el pais";
        return;
    }
    for (const auto& v : ventas) {
        if (v.producto==p1) {
            c1+=v.cantidad;
            m1+=v.montoTotal;
        } else if (v.producto==p2) {
            c2+=v.cantidad;
            m2+=v.montoTotal;
        }
    
    }
    cout<<"\n=== Comparación de productos: "<<p1<<" vs "<<p2<<" ==="<<endl;
    cout<<"a) Cantidad: "<<p1<<"="<<c1<<" | "<<p2<<"="<<c2<<endl;
    cout<<"b) Monto total: "<<p1<<"=$"<<m1<<" | "<<p2<<"=$"<<m2<<endl;
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


