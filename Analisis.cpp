#include "Analisis.h"
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

void mostrarTopCiudadesPorPais(const vector<Venta>& ventas) {
    // Mapa: pais -> ciudad -> monto total
    map<string, map<string, double>> ventasPorCiudadYPais;

    // Recorremos todas las ventas y agrupamos
    for (const auto& venta : ventas) {
        ventasPorCiudadYPais[venta.pais][venta.ciudad] += venta.montoTotal;
    }

    // Mostramos resultados
    for (const auto& [pais, ciudades] : ventasPorCiudadYPais) {
        cout<<"\nTop 5 ciudades con mayor monto total de ventas en "<<pais<< ":\n";

        // Convertir el mapa ciudad -> monto a vector para poder ordenarlo
        vector<pair<string, double>> ciudadMontos(ciudades.begin(), ciudades.end());

        // Ordenar de mayor a menor por monto
        sort(ciudadMontos.begin(), ciudadMontos.end(),
            [](const auto& a, const auto& b) {
                return a.second > b.second;
            });
    
        // Mostrar las primeras 5 o menos
        for (size_t i=0;i<min(size_t(5),ciudadMontos.size());++i) {
            cout<<i+1<< ". "<<ciudadMontos[i].first<< " - $"<<ciudadMontos[i].second<<endl;
        }
    }
}

void mostrarMontoTotalPorProductoPorPais(const vector<Venta>& ventas) {
    // Mapa: pais -> producto -> monto total
    map<string, map<string, double>> ventasPorProductoYPais;

    // Recorremos todas las ventas y agrupamos por país y producto
    for (const auto& venta : ventas) {
        ventasPorProductoYPais[venta.pais][venta.producto]+=venta.montoTotal;
    }

    // Mostramos resultados
    for (const auto& [pais,productos]:ventasPorProductoYPais) {
        cout<<"\nMonto total de ventas por producto en "<<pais<<":\n";

        // Convertir el mapa producto -> monto a vector para ordenarlo
        vector<pair<string, double>> productoMontos(productos.begin(), productos.end());

        // Ordenar de mayor a menor por monto
        sort(productoMontos.begin(), productoMontos.end(),
            [](const auto& a, const auto& b) {
                return a.second > b.second;
            });

        // Mostrar todos los productos
        for (size_t i=0;i<productoMontos.size();++i) {
            cout<<i+1<<". "<<productoMontos[i].first<<" - $"<<productoMontos[i].second<<endl;
        }
    }
}

void mostrarPromedioVentasPorCategoriaPorPais(const vector<Venta>& ventas) {
    // Mapa: pais -> categoria -> {monto total, conteo de ventas}
    map<string, map<string, pair<double, int>>> ventasPorCategoriaYPais;

    // Recorremos todas las ventas y agrupamos por país y categoría
    for (const auto& venta : ventas) {
        auto& categoriaData = ventasPorCategoriaYPais[venta.pais][venta.categoria];
        categoriaData.first += venta.montoTotal; // Sumar monto total
        categoriaData.second++; // Incrementar conteo
    }

    // Mostramos resultados
    for (const auto& [pais, categorias] : ventasPorCategoriaYPais) {
        cout << "\nPromedio de ventas por categoría en " << pais << ":\n";

        // Convertir el mapa categoría -> {monto, conteo} a vector para ordenarlo
        vector<pair<string, double>> categoriaPromedios;
        for (const auto& [categoria, data] : categorias) {
            double promedio = data.second > 0 ? data.first / data.second : 0.0;
            categoriaPromedios.emplace_back(categoria, promedio);
        }

        // Ordenar de mayor a menor por promedio
        sort(categoriaPromedios.begin(), categoriaPromedios.end(),
            [](const auto& a, const auto& b) {
                return a.second>b.second;
            });

        // Mostrar todas las categorías
        for (size_t i=0;i<categoriaPromedios.size();++i) {
            cout<<i+1<<". "<<categoriaPromedios[i].first<<" - $"<<categoriaPromedios[i].second<< " (promedio por venta)" << endl;
        }
    }
}

void mostrarMedioEnvioMasUtilizadoPorPais(const vector<Venta>& ventas) {
    // Mapa: pais -> medioEnvio -> conteo
    map<string, map<string, int>> conteoPorMedioEnvioYPais;

    // Recorremos todas las ventas y contamos por país y medio de envío
    for (const auto& venta : ventas) {
        conteoPorMedioEnvioYPais[venta.pais][venta.medioEnvio]++;
    }

    // Mostramos resultados
    for (const auto& [pais, medios] : conteoPorMedioEnvioYPais) {
        cout<<"\nMedio de envío más utilizado en "<<pais<<":\n";

        // Encontrar el medio de envío con mayor conteo
        string medioMasUtilizado;
        int maxConteo=0;
        for (const auto& [medio, conteo] : medios) {
            if (conteo > maxConteo || (conteo == maxConteo && medio < medioMasUtilizado)) {
                medioMasUtilizado = medio;
                maxConteo = conteo;
            }
        }

        cout<<"1."<<medioMasUtilizado<<" - "<<maxConteo<<" envíos"<<endl;
    }
}

void mostrarMedioEnvioMasUtilizadoPorCategoria(const vector<Venta>& ventas) {
    // Mapa: pais -> categoria -> medioEnvio -> conteo
    map<string, map<string, map<string, int>>> conteoPorMedioEnvioCategoriaYPais;

    // Recorremos todas las ventas y contamos por país, categoría y medio de envío
    for (const auto& venta : ventas) {
        conteoPorMedioEnvioCategoriaYPais[venta.pais][venta.categoria][venta.medioEnvio]++;
    }

    // Mostramos resultados
    for (const auto& [pais, categorias] : conteoPorMedioEnvioCategoriaYPais) {
        cout << "\nMedio de envío más utilizado por categoría en " << pais << ":\n";

        for (const auto& [categoria, medios] : categorias) {
            cout << "  Categoría: " << categoria << ":\n";

            // Encontrar el medio de envío con mayor conteo
            string medioMasUtilizado;
            int maxConteo = 0;
            for (const auto& [medio, conteo] : medios) {
                if (conteo > maxConteo || (conteo == maxConteo && medio < medioMasUtilizado)) {
                    medioMasUtilizado = medio;
                    maxConteo = conteo;
                }
            }

            cout << "    1. " << medioMasUtilizado << " - " << maxConteo << " envíos\n";
        }
    }
}

void mostrarDiaMayorVentas(const vector<Venta>& ventas) {
    // Mapa: fecha -> monto total
    map<string, double> montoPorDia;

    // Recorremos todas las ventas y sumamos el monto total por fecha
    for (const auto& venta : ventas) {
        montoPorDia[venta.fecha] += venta.montoTotal;
    }

    // Encontrar el día con mayor monto
    string diaMayorVentas;
    double maxMonto = 0.0;
    for (const auto& [fecha, monto] : montoPorDia) {
        if (monto > maxMonto) {
            maxMonto = monto;
            diaMayorVentas = fecha;
        }
    }

    // Mostrar resultado
    cout << "\nDía con mayor cantidad de ventas (por monto de dinero) en toda la base de datos:\n";
    cout << "1. " << diaMayorVentas << " - $" << fixed << setprecision(2) << maxMonto << endl;
}

void mostrarEstadoEnvioMasFrecuentePorPais(const std::vector<Venta>& ventas) {
    // Mapa: pais -> estadoEnvio -> conteo
    std::map<std::string, std::map<std::string, int>> conteoPorEstadoEnvioYPais;

    // Recorremos todas las ventas y contamos por país y estado de envío
    for (const auto& venta : ventas) {
        conteoPorEstadoEnvioYPais[venta.pais][venta.estadoEnvio]++;
    }

    // Mostramos resultados
    for (const auto& [pais, estados] : conteoPorEstadoEnvioYPais) {
        std::cout << "\nEstado de envío más frecuente en " << pais << ":\n";

        // Encontrar el estado de envío con mayor conteo
        std::string estadoMasFrecuente;
        int maxConteo = 0;
        for (const auto& [estado, conteo] : estados) {
            if (conteo > maxConteo || (conteo == maxConteo && estado < estadoMasFrecuente)) {
                estadoMasFrecuente = estado;
                maxConteo = conteo;
            }
        }

        std::cout << "1. " << estadoMasFrecuente << " - " << maxConteo << " envíos" << std::endl;
    }
}

void mostrarProductoMasVendidoPorCantidad(const vector<Venta>& ventas) {
    // Mapa: producto -> cantidad total
    map<string, int> cantidadPorProducto;
    
    // Sumar la cantidad vendida por cada producto
    for (const auto& venta : ventas) {
        cantidadPorProducto[venta.producto] += venta.cantidad;
    }

    // Encontrar el producto con mayor cantidad vendida
    string productoMasVendido;
    int maxCantidad = 0;
    for (const auto& [producto, cantidad] : cantidadPorProducto) {
        if (cantidad > maxCantidad || (cantidad == maxCantidad && producto < productoMasVendido)) {
            productoMasVendido = producto;
            maxCantidad = cantidad;
        }
    }

    // Mostrar resultado
    cout << "\nProducto más vendido por cantidad total en toda la base de datos:\n";
    cout << "1. " << productoMasVendido << " - " << maxCantidad << " unidades vendidas" << endl;
}

void mostrarProductoMenosVendidoPorCantidad(const vector<Venta>& ventas) {
    // Mapa: producto -> cantidad total
    map<string, int> cantidadPorProducto;
    
    // Sumar la cantidad vendida por cada producto
    for (const auto& venta : ventas) {
        cantidadPorProducto[venta.producto] += venta.cantidad;
    }

    // Encontrar el producto con menor cantidad vendida
    string productoMenosVendido;
    int minCantidad = numeric_limits<int>::max(); // Initialize to maximum possible integer
    for (const auto& [producto, cantidad] : cantidadPorProducto) {
        if (cantidad < minCantidad || (cantidad == minCantidad && producto < productoMenosVendido)) {
            productoMenosVendido = producto;
            minCantidad = cantidad;
        }
    }

    // Mostrar resultado
    cout << "\nProducto menos vendido por cantidad total en toda la base de datos:\n";
    cout << "1. " << productoMenosVendido << " - " << minCantidad << " unidades vendidas" << endl;
}

