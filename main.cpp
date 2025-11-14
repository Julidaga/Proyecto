#include <iostream>
#include <string>
#include "empleado.h"
#include "cliente.h"

using namespace std;
//este es para windows y para linux
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    vector<Auto> autos;
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
            menuEmpleado(autos);
            break;
        case 2:
            menuCliente(autos);
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
