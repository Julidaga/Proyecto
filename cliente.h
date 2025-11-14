#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

extern void limpiarPantalla();

void abrirFactura(string archivo) {
#ifdef _WIN32
    string cmd = "start " + archivo;
#else
    string cmd = "xdg-open " + archivo;
#endif
    system(cmd.c_str());
}

void listarAutosCliente(const vector<Auto>& autos) {
    cout << "=== AUTOS DISPONIBLES ===\n";

    for (int i = 0; i < autos.size(); i++) {
        if (!autos[i].alquilado)
            cout << i + 1 << ". " << autos[i].modelo << endl;
    }

    cout << endl;
}

void alquilarAuto(vector<Auto>& autos) {
    if (autos.empty()) {
        cout << "No hay autos registrados.\n";
        return;
    }

    listarAutosCliente(autos);

    int opcion;
    cout << "Elige un auto: ";
    cin >> opcion;

    if (opcion < 1 || opcion > autos.size()) {
        cout << "Opcion invalida.\n";
        return;
    }

    Auto& a = autos[opcion - 1];

    if (a.alquilado) {
        cout << "Este auto ya esta alquilado.\n";
        return;
    }

    limpiarPantalla();
    cout << "=== INFORMACION DEL AUTO ===\n";
    cout << "Modelo: " << a.modelo << endl;
    cout << "Año: " << a.año << endl;
    cout << "Gama: " << a.gama << endl;
    cout << "Precio por hora: $" << a.precioHora << endl;

    int op2;
    cout << "\n1. Alquilar auto\n2. Volver\nOpcion: ";
    cin >> op2;

    if (op2 != 1) return;

    string nombre;
    int doc, cel, horas;

    cin.ignore();
    cout << "Nombre completo: ";
    getline(cin, nombre);

    cout << "Documento: ";
    cin >> doc;

    cout << "Telefono: ";
    cin >> cel;

    cout << "Horas de alquiler: ";
    cin >> horas;

    int total = horas * a.precioHora;
    a.alquilado = true;

    string archivo = "Factura_" + a.modelo + ".txt";
    ofstream x(archivo);

    x << "========= FACTURA DE ALQUILER =========\n";
    x << "Cliente: " << nombre << endl;
    x << "Documento: " << doc << endl;
    x << "Auto: " << a.modelo << endl;
    x << "Horas: " << horas << endl;
    x << "Total a pagar: $" << total << endl;

    x.close();

    cout << "\nAlquiler realizado.\n";
    cout << "Factura generada: " << archivo << endl;

    abrirFactura(archivo);
}

void devolverAuto(vector<Auto>& autos) {
    cout << "=== DEVOLVER AUTO ===\n";

    vector<int> indices;
    for (int i = 0; i < autos.size(); i++) {
        if (autos[i].alquilado) {
            cout << i + 1 << ". " << autos[i].modelo << endl;
            indices.push_back(i);
        }
    }

    if (indices.empty()) {
        cout << "No hay autos alquilados.\n";
        return;
    }

    int opcion;
    cout << "Elige un auto para devolver: ";
    cin >> opcion;

    Auto& a = autos[opcion - 1];

    int horas;
    cout << "Cuantas horas se utilizo?: ";
    cin >> horas;

    int total = horas * a.precioHora;

    string archivo = "Devolucion_" + a.modelo + ".txt";
    ofstream x(archivo);

    x << "========= FACTURA DE DEVOLUCION =========\n";
    x << "Auto: " << a.modelo << endl;
    x << "Horas utilizadas: " << horas << endl;
    x << "Total a pagar: $" << total << endl;

    x.close();

    a.alquilado = false;

    cout << "\nDevolucion registrada.\n";
    abrirFactura(archivo);
}

void menuCliente(vector<Auto>& autos) {
    int opcion;

    do {
        cout << "=== MENU CLIENTE ===\n";
        cout << "1. Alquilar auto\n";
        cout << "2. Devolver auto\n";
        cout << "3. Ver precios\n";
        cout << "4. Volver\n";
        cout << "Opcion: ";
        cin >> opcion;

        limpiarPantalla();

        switch (opcion) {
        case 1:
            alquilarAuto(autos);
            break;
        case 2:
            devolverAuto(autos);
            break;
        case 3:
            listarAutosCliente(autos);
            break;
        case 4:
            return;
        default:
            cout << "Opcion invalida.\n";
        }

        string pausa;
        cout << "\nPresione ENTER para continuar...";
        cin.ignore();
        getline(cin, pausa);
        limpiarPantalla();

    } while (true);
}

#endif
