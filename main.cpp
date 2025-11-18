#include <iostream>
#include <string>
#include <vector>
#include "empleado.h"
#include "cliente.h"

using namespace std;

        //Limpia pantalla
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

        //Contraseña
bool validarContrasena() {
    string pass;
    int intentos = 3;

    while (intentos > 0) {
        cout << "Ingrese contraseña de empleado: ";
        cin >> pass;

        if (pass == "ABC123") {
            return true;
        }

        intentos--;
        cout << "Contraseña incorrecta. Intentos restantes: " << intentos << "\n\n";
    }

    return false;
}

int main() {
    vector<Vehiculo> vehiculos;
    vector<Alquiler> historial;

    int opcion;
    string pausa;

    limpiarPantalla();
    cout << "===========================================\n";
    cout << "        BIENVENIDOS AL ALQUILER DE AUTOS   \n";
    cout << "===========================================\n";
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    getline(cin, pausa);

    limpiarPantalla();

    do {
        cout << "===========================================\n";
        cout << "        ELIGE UNA OPCION PARA SEGUIR       \n";
        cout << "===========================================\n";
        cout << "INGRESAR COMO...\n";
        cout << "1. EMPLEADO\n";
        cout << "2. CLIENTE\n";
        cout << "3. SALIR\n";
        cout << "Opcion: ";
        cin >> opcion;

        limpiarPantalla();

        switch (opcion) {
        case 1:
            if (validarContrasena()) {
                menuEmpleado(vehiculos, historial);
            } else {
                cout << "Acceso denegado.\n";
            }
            break;

        case 2:
            menuCliente(vehiculos, historial);
            break;

        case 3:
            cout << "Saliendo del sistema...\n";
            break;

        default:
            cout << "Opcion invalida!\n";
        }

        if (opcion != 3) {
            cout << "\nPresione ENTER para continuar...";
            cin.ignore();
            getline(cin, pausa);
            limpiarPantalla();
        }

    } while (opcion != 3);

    return 0;
}
