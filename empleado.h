#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

extern void limpiarPantalla();

struct Auto {
    string modelo;
    int año;
    string gama;
    int precioHora;
    bool alquilado = false;
};

void agregarAuto(vector<Auto>& autos) {
    Auto a;

    cout << "=== REGISTRO DE AUTO NUEVO ===\n";
    cout << "Modelo del auto: ";
    cin.ignore();
    getline(cin, a.modelo);

    cout << "Año del auto: ";
    cin >> a.año;

    cout << "Gama del auto: ";
    cin.ignore();
    getline(cin, a.gama);

    cout << "Precio por hora: ";
    cin >> a.precioHora;

    autos.push_back(a);

    cout << "\nAuto registrado con exito!\n";
}

void listarAutosEmpleado(const vector<Auto>& autos) {
    cout << "=== AUTOS REGISTRADOS ===\n";

    if (autos.empty()) {
        cout << "No hay autos registrados.\n";
        return;
    }

    for (int i = 0; i < autos.size(); i++) {
        cout << i + 1 << ". " << autos[i].modelo
            << " | " << autos[i].año
            << " | Gama: " << autos[i].gama
            << " | Precio/hora: " << autos[i].precioHora
            << " | Estado: " << (autos[i].alquilado ? "Alquilado" : "Disponible") << "\n";
    }

    cout << endl;
}

void menuEmpleado(vector<Auto>& autos) {
    int opcion;
    do {
        cout << "=== MENU EMPLEADO ===\n";
        cout << "1. Registrar auto\n";
        cout << "2. Listar autos\n";
        cout << "3. Volver\n";
        cout << "Opcion: ";
        cin >> opcion;

        limpiarPantalla();

        switch (opcion) {
        case 1:
            agregarAuto(autos);
            break;
        case 2:
            listarAutosEmpleado(autos);
            break;
        case 3:
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
