#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

extern void limpiarPantalla();

// Estructura general para Autos y Motos

struct Vehiculo {
    string modelo;
    int año;
    string tipo;  
    
    string gama;

    int cilindraje;

    int precioHora;
    bool alquilado = false;

    int horasAlquiladas = 0;

        //Estadísticas
    int diaAlquilado = 0;
    int mesAlquilado = 0;
    int añoAlquilado = 0;
};

struct Alquiler {
    string cliente;
    string vehiculo;
    int horas;
    int total;
    int dia;
    int mes;
    int año;
};

vector<string> gamasAuto = {
    "Toyota", "Chevrolet", "Renault", "Kia", "Hyundai",
    "Audi", "BMW", "Mercedes-Benz", "Porsche", "Lexus",
    "Bentley", "Rolls-Royce", "Ferrari", "Lamborghini"
};

vector<int> cilindrajesMoto = {125, 150, 200, 250, 300, 400, 500, 600, 750, 1000};

                //Registrar el vehiculo 

void registrarVehiculo(vector<Vehiculo>& veh) {
    Vehiculo v;
    int op;

    cout << "¿Qué desea registrar?\n1. Auto\n2. Moto\nOpción: ";
    cin >> op;

    if (op == 1) {
        v.tipo = "AUTO";

        cout << "Modelo del auto: ";
        cin.ignore();
        getline(cin, v.modelo);

        cout << "Año: ";
        cin >> v.año;

        cout << "\nSeleccione una GAMA:\n";
        for (int i = 0; i < gamasAuto.size(); i++)
            cout << i + 1 << ". " << gamasAuto[i] << endl;

        cout << "Opción: ";
        int g;
        cin >> g;
        v.gama = gamasAuto[g - 1];

        v.cilindraje = 0; 

    } else {
        v.tipo = "MOTO";

        cout << "Modelo de la moto: ";
        cin.ignore();
        getline(cin, v.modelo);

        cout << "Año: ";
        cin >> v.año;

        cout << "\nSeleccione un CILINDRAJE:\n";
        for (int i = 0; i < cilindrajesMoto.size(); i++)
            cout << i + 1 << ". " << cilindrajesMoto[i] << "cc\n";

        int c;
        cout << "Opción: ";
        cin >> c;
        v.cilindraje = cilindrajesMoto[c - 1];

        v.gama = "";
    }

    cout << "Precio por hora: ";
    cin >> v.precioHora;

    veh.push_back(v);
    cout << "\nVehículo registrado exitosamente.\n";
}

                    //Lista de vehiculo 

void listarVehiculosEmpleado(const vector<Vehiculo>& v) {
    cout << "=== VEHICULOS REGISTRADOS ===\n\n";

    if (v.empty()) {
        cout << "No hay vehículos registrados.\n";
        return;
    }

    for (int i = 0; i < v.size(); i++) {
        cout << i + 1 << ". " << v[i].modelo
             << " | " << v[i].año
             << " | Tipo: " << v[i].tipo;

        if (v[i].tipo == "AUTO")
            cout << " | Gama: " << v[i].gama;
        else
            cout << " | Cilindraje: " << v[i].cilindraje << "cc";

        cout << " | Precio/hora: $" << v[i].precioHora
             << " | Estado: " << (v[i].alquilado ? "Alquilado" : "Disponible") << "\n";
    }
}

                        //Estadistica 

void verEstadisticas(const vector<Alquiler>& hist) {
    if (hist.empty()) {
        cout << "No hay alquileres registrados.\n";
        return;
    }

    time_t t = time(nullptr);
    tm* now = localtime(&t);

    int dia = now->tm_mday;
    int mes = now->tm_mon + 1;
    int año = now->tm_year + 1900;

    int totalDia = 0, totalMes = 0, totalAño = 0;
    int cantDia = 0, cantMes = 0, cantAño = 0;

    cout << "\n=== ESTADISTICAS ===\n\n";

    for (const Alquiler& a : hist) {
        if (a.dia == dia && a.mes == mes && a.año == año) {
            totalDia += a.total;
            cantDia++;
        }
        if (a.mes == mes && a.año == año) {
            totalMes += a.total;
            cantMes++;
        }
        if (a.año == año) {
            totalAño += a.total;
            cantAño++;
        }
    }

    cout << "Hoy se realizaron: " << cantDia << " alquileres.\n";
    cout << "Ganancia del día: $" << totalDia << "\n\n";

    cout << "Este mes: " << cantMes << " alquileres.\n";
    cout << "Ganancia mensual: $" << totalMes << "\n\n";

    cout << "Este año: " << cantAño << " alquileres.\n";
    cout << "Ganancia anual: $" << totalAño << "\n\n";
}

                        //Menu 

void menuEmpleado(vector<Vehiculo>& veh, vector<Alquiler>& hist) {
    int opcion;

    do {
        cout << "=== MENU EMPLEADO ===\n";
        cout << "1. Registrar vehículo\n";
        cout << "2. Listar vehículos\n";
        cout << "3. Ver estadísticas\n";
        cout << "4. Volver\n";
        cout << "Opción: ";
        cin >> opcion;

        limpiarPantalla();

        switch (opcion) {
        case 1: registrarVehiculo(veh); break;
        case 2: listarVehiculosEmpleado(veh); break;
        case 3: verEstadisticas(hist); break;
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
