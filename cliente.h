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

// ==================== IMPUESTOS ====================

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

// ==================== FILTROS ====================

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
        for (int i = 0; i < v.size(); i++)
            if (v[i].tipo == "AUTO" && !v[i].alquilado)
                indices.push_back(i);
    } else {
        for (int i = 0; i < v.size(); i++)
            if (v[i].tipo == "MOTO" && !v[i].alquilado)
                indices.push_back(i);
    }

    if (filtro == 1)
        return indices;

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

// ==================== ALQUILAR VEHICULO ====================

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

    // HORAS DECIMALES + VALIDACIÓN
    double horas;
    cout << "Horas de alquiler (positivas y en decimales): ";

    while (true) {
        cin >> horas;

        if (cin.fail() || horas <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Valor inválido. Ingrese un número positivo: ";
        } else {
            break;
        }
    }

    veh.horasAlquiladas = horas;

    double impuesto = (veh.tipo == "AUTO")
                        ? impuestoGama(veh.gama)
                        : impuestoCilindraje(veh.cilindraje);

    double total = horas * veh.precioHora;
    total += total * impuesto;

    veh.alquilado = true;

    // FECHA
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    Alquiler reg = {nombre, veh.modelo, (int)horas, (int)total,
                    now->tm_mday, now->tm_mon + 1, now->tm_year + 1900};

    hist.push_back(reg);

    cout << "\nAlquiler completado. Total: $" << total << "\n";

    // ==================== FACTURA ALQUILER ====================
    ofstream factura("factura_alquiler.txt");

    factura << "========== FACTURA DE ALQUILER ==========\n";
    factura << "Cliente: " << nombre << "\n";
    factura << "Vehículo: " << veh.modelo << "\n";
    factura << "Horas alquiladas: " << horas << "\n";
    factura << "Precio/hora: $" << veh.precioHora << "\n";
    factura << "Impuesto aplicado: " << (impuesto * 100) << "%\n";
    factura << "TOTAL A PAGAR: $" << total << "\n";
    factura << "Fecha: " << now->tm_mday << "/" 
            << now->tm_mon + 1 << "/" 
            << now->tm_year + 1900 << "\n";
    factura << "=========================================\n";

    factura.close();

    cout << "Factura generada: factura_alquiler.txt\n";
}

// ==================== DEVOLVER VEHICULO ====================

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

    double horas;
    cout << "¿Cuántas horas se utilizó?: ";

    while (true) {
        cin >> horas;

        if (cin.fail() || horas <= 1 || horas > veh.horasAlquiladas) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error. Ingrese un valor entre 1 y " << veh.horasAlquiladas << ": ";
        } else {
            break;
        }
    }

    veh.alquilado = false;

    cout << "\nDevolución registrada correctamente.\n";

    // ==================== FACTURA DEVOLUCIÓN ====================
    ofstream factura("factura_devolucion.txt");

    factura << "========== FACTURA DE DEVOLUCIÓN ==========\n";
    factura << "Vehículo devuelto: " << veh.modelo << "\n";
    factura << "Horas utilizadas: " << horas << "\n";
    factura << "Horas pagadas originalmente: " << veh.horasAlquiladas << "\n";
    factura << "Estado: Devuelto correctamente\n";
    factura << "===========================================\n";

    factura.close();

    cout << "Factura generada: factura_devolucion.txt\n";
}

// ==================== MENU CLIENTE ====================

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
