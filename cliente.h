#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

extern void limpiarPantalla();
extern vector<string> gamasAuto;
extern vector<int> cilindrajesMoto;

struct Vehiculo;
struct Alquiler;

// Impuestos

double impuestoGama(string gama) {
    if (gama == "Toyota" || gama == "Chevrolet" || gama == "Renault" || gama == "Kia" || gama == "Hyundai")
        return 0.02;
    if (gama == "Audi" || gama == "BMW" || gama == "Mercedes-Benz" || gama == "Porsche" || gama == "Lexus")
        return 0.05;
    return 0.10; // Ultra lujo
}

double impuestoCilindraje(int c) {
    if (c >= 125 && c <= 250) return 0.02;
    if (c > 250 && c <= 400) return 0.05;
    if (c > 400 && c <= 600) return 0.08;
    return 0.12;
}

                    //Filtro para alquilar el vehiculo 

int elegirTipoVehiculo() {
    int op;
    cout << "¿Qué desea alquilar?\n1. Auto\n2. Moto\nOpción: ";
    cin >> op;
    return op;
}

int elegirFiltro(int tipo) {
    cout << "\n=== FILTROS ===\n";
    cout << "1. Ver todos\n";
    if (tipo == 1) cout << "2. Filtrar por gama\n";
    else cout << "2. Filtrar por cilindraje\n";
    cout << "Opción: ";

    int f;
    cin >> f;
    return f;
}

vector<int> filtrarVehiculos(const vector<Vehiculo>& v, int tipo, int filtro) {
    vector<int> indices;

    if (tipo == 1) {
        // Autos
        for (int i = 0; i < v.size(); i++)
            if (v[i].tipo == "AUTO" && !v[i].alquilado)
                indices.push_back(i);
    } else {
        // Motos
        for (int i = 0; i < v.size(); i++)
            if (v[i].tipo == "MOTO" && !v[i].alquilado)
                indices.push_back(i);
    }

    if (filtro == 1)
        return indices;

    // FILTRAR POR GAMA O CILINDRAJE
    vector<int> filtrados;
    
    if (tipo == 1) {
        cout << "\nSeleccione gama:\n";
        for (int i = 0; i < gamasAuto.size(); i++)
            cout << i + 1 << ". " << gamasAuto[i] << endl;

        int g;
        cout << "Opción: ";
        cin >> g;

        for (int idx : indices)
            if (v[idx].gama == gamasAuto[g - 1])
                filtrados.push_back(idx);
    }
    else {
        cout << "\nSeleccione cilindraje:\n";
        for (int i = 0; i < cilindrajesMoto.size(); i++)
            cout << i + 1 << ". " << cilindrajesMoto[i] << "cc\n";

        int c;
        cout << "Opción: ";
        cin >> c;

        for (int idx : indices)
            if (v[idx].cilindraje == cilindrajesMoto[c - 1])
                filtrados.push_back(idx);
    }

    return filtrados;
}

                    //Alquilar vehiculo 

void alquilarVehiculo(vector<Vehiculo>& v, vector<Alquiler>& hist) {
    if (v.empty()) {
        cout << "No hay vehículos registrados.\n";
        return;
    }

    int tipo = elegirTipoVehiculo();
    int filtro = elegirFiltro(tipo);

    vector<int> lista = filtrarVehiculos(v, tipo, filtro);

    if (lista.empty()) {
        cout << "No hay vehículos disponibles con esos filtros.\n";
        return;
    }

    cout << "\n=== VEHICULOS DISPONIBLES ===\n";

    for (int i = 0; i < lista.size(); i++) {
        int idx = lista[i];
        cout << i + 1 << ". " << v[idx].modelo;

        if (v[idx].tipo == "AUTO")
            cout << " | Gama: " << v[idx].gama;
        else
            cout << " | Cilindraje: " << v[idx].cilindraje << "cc";

        cout << " | Precio/hora: $" << v[idx].precioHora << "\n";
    }

    cout << "\nSeleccione vehículo: ";
    int op;
    cin >> op;
    op--;

    if (op < 0 || op >= lista.size()) {
        cout << "Opción inválida.\n";
        return;
    }

    Vehiculo& veh = v[lista[op]];

    cin.ignore();
    string nombre;
    cout << "Nombre completo: ";
    getline(cin, nombre);

    int horas;
    cout << "Horas de alquiler: ";
    cin >> horas;

    veh.horasAlquiladas = horas;

    double impuesto = (veh.tipo == "AUTO")
                        ? impuestoGama(veh.gama)
                        : impuestoCilindraje(veh.cilindraje);

    int total = horas * veh.precioHora;
    total += total * impuesto;

    veh.alquilado = true;

                //La fecha 
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    Alquiler reg = {nombre, veh.modelo, horas, total,
                    now->tm_mday, now->tm_mon + 1, now->tm_year + 1900};

    hist.push_back(reg);

    cout << "\nAlquiler completado. Total: $" << total << "\n";
}

                //Devolver el Vehiculo

void devolverVehiculo(vector<Vehiculo>& v) {
    vector<int> alquilados;

    for (int i = 0; i < v.size(); i++)
        if (v[i].alquilado)
            alquilados.push_back(i);

    if (alquilados.empty()) {
        cout << "No hay vehículos alquilados.\n";
        return;
    }

    cout << "=== VEHICULOS ALQUILADOS ===\n";

    for (int i = 0; i < alquilados.size(); i++) {
        int idx = alquilados[i];
        cout << i + 1 << ". " << v[idx].modelo << endl;
    }

    cout << "Seleccione vehículo a devolver: ";
    int op;
    cin >> op;
    op--;

    if (op < 0 || op >= alquilados.size()) {
        cout << "Opción inválida.\n";
        return;
    }

    Vehiculo& veh = v[alquilados[op]];

    int horas;
    cout << "¿Cuántas horas se utilizó?: ";
    cin >> horas;

    if (horas <= 1 || horas > veh.horasAlquiladas) {
        cout << "Error: La devolución debe ser más de 1 hora y menor a lo alquilado.\n";
        return;
    }

    veh.alquilado = false;

    cout << "\nDevolución registrada correctamente.\n";
}

                            //Menu

void menuCliente(vector<Vehiculo>& v, vector<Alquiler>& hist) {
    int op;

    do {
        cout << "=== MENU CLIENTE ===\n";
        cout << "1. Alquilar vehículo\n";
        cout << "2. Devolver vehículo\n";
        cout << "3. Ver vehículos disponibles\n";
        cout << "4. Volver\n";
        cout << "Opción: ";
        cin >> op;

        limpiarPantalla();

        switch (op) {
        case 1: alquilarVehiculo(v, hist); break;
        case 2: devolverVehiculo(v); break;
        case 3: alquilarVehiculo(v, hist); break;
        case 4: return;
        default: cout << "Opción inválida.\n";
        }

        string pausa;
        cout << "\nPresione ENTER para continuar...";
        cin.ignore();
        getline(cin, pausa);
        limpiarPantalla();

    } while (true);
}

#endif
