// 💾 Archivo: src/main.cpp

#include "RoyalFamilyTree.h" // <-- ¡La única librería!

using namespace std;

void showMenu() {
    cout << "\n===== MENÚ DE SUCESIÓN REAL =====" << endl;
    cout << "1. Mostrar la Línea de Sucesión Actual" << endl;
    cout << "2. Asignar Nuevo Rey/Reina (por abdicación o muerte del actual)" << endl;
    cout << "3. Modificar Datos de un Descendiente (por ID)" << endl;
    cout << "4. Salir" << endl;
    cout << "Seleccione una opción: ";
}

int main() {
    RoyalFamilyTree tree; 
    
    // Pasamos la ruta como const char*
    tree.loadData("bin/family.csv"); 

    if (!tree.root) {
        return 1;
    }

    int choice;
    do {
        showMenu();
        if (!(cin >> choice)) {
            // Manejo de error de entrada
            cin.clear();
            
            // Limpieza de buffer con un bucle simple de I/O
            char dummy;
            while (cin.get(dummy) && dummy != '\n'); 
            
            choice = 0; 
        }

        switch (choice) {
            case 1: tree.showSuccessionLine(); break;
            case 2: {
                int kingId;
                cout << "Ingrese el ID del Monarca actual que muere/abdica: ";
                cin >> kingId;
                tree.assignNewKing(kingId);
                break;
            }
            case 3: {
                int nodeId;
                cout << "Ingrese el ID del descendiente a modificar: ";
                cin >> nodeId;
                tree.updateNodeData(nodeId);
                break;
            }
            case 4:
                cout << "Saliendo del sistema de sucesión. ¡Adiós!" << endl;
                break;
            default:
                cout << "Opción inválida. Por favor, intente de nuevo." << endl;
        }
    } while (choice != 4);

    return 0;
}
