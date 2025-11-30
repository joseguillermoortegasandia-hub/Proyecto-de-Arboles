
#include "RoyalFamilyTree.h" 

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
    
    // Ruta del archivo CSV
    tree.loadData("bin/family.csv"); 

    if (tree.getRoot() == nullptr) {
        return 1;
    }

    int choice;
    do {
        showMenu();
        if (!(cin >> choice)) {
            // Manejo de error de entrada
            cin.clear();
            char dummy;
            while (cin.get(dummy) && dummy != '\n'); // Limpieza manual de buffer
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
