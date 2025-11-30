
#ifndef ROYALFAMILYTREE_H
#define ROYALFAMILYTREE_H

#include <iostream>  
#include <cstdio>    

using namespace std;

// Implementación manual de la Clase String (Sustituye a std::string)
class CustomString {
public:
    char data[64]; // Longitud máxima fija
    int length;

    CustomString() {
        length = 0;
        data[0] = '\0';
    }

    void append(char c) {
        if (length < 63) {
            data[length++] = c;
            data[length] = '\0';
        }
    }

    void copy(const char* s) {
        length = 0;
        for (int i = 0; s[i] != '\0' && i < 63; ++i) {
            data[i] = s[i];
            length++;
        }
        data[length] = '\0';
    }

    // Funciones de I/O de cout (Amigas de iostream)
    friend ostream& operator<<(ostream& os, const CustomString& s) {
        os << s.data;
        return os;
    }
    
    // Operador de asignación manual
    CustomString& operator=(const CustomString& other) {
        if (this != &other) {
            length = other.length;
            for (int i = 0; i <= length; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // Simplificación de strncmp para comparación rápida
    bool startsWith(const char* prefix) const {
        for (int i = 0; prefix[i] != '\0'; ++i) {
            if (i >= length || data[i] != prefix[i]) return false;
        }
        return true;
    }
    
    // Implementación manual de conversión de cadena a entero (Sustituye stoi)
    int toInt() const {
        int result = 0;
        for (int i = 0; i < length; ++i) {
            if (data[i] >= '0' && data[i] <= '9') {
                result = result * 10 + (data[i] - '0');
            } else {
                return 0; 
            }
        }
        return result;
    }
    
    // Implementación manual de conversión de bool (Sustituye lógica de stdexcept)
    bool toBool() const {
        return (length == 1 && data[0] == '1');
    }
};

// --- ESTRUCTURA NODE ---
struct Node {
    int id;
    CustomString name;
    CustomString last_name;
    char gender; 
    int age;
    int id_father;
    bool is_dead;
    bool was_king;
    bool is_king;

    // Punteros del Árbol Binario y Lista Enlazada
    Node* child1; 
    Node* child2; 
    Node* parent; 
    Node* next; 

    Node(int _id, const CustomString& _name, const CustomString& _last_name, char _gender, int _age, int _id_father, bool _is_dead, bool _was_king, bool _is_king)
        : id(_id), gender(_gender), age(_age), id_father(_id_father),
          is_dead(_is_dead), was_king(_was_king), is_king(_is_king),
          child1(nullptr), child2(nullptr), parent(nullptr), next(nullptr) {
              name = _name;
              last_name = _last_name;
          }
};

// --- CLASE ROYALFAMILYTREE (Interfaz y Lógica) ---
class RoyalFamilyTree {
private:
    Node* root; 
    Node* allNodesHead; 
    
    // Implementación de Lectura Manual de Archivo (Sustituye fstream y getline)
    void _readFileLine(FILE* file, CustomString& result) {
        result.length = 0;
        char c;
        while ((c = fgetc(file)) != EOF && c != '\n' && c != '\r') {
            result.append(c);
        }
        if (c == '\r' && (c = fgetc(file)) != '\n') { 
            ungetc(c, file);
        }
    }

    // Implementación de Tokenización Manual (Sustituye sstream)
    void _tokenizeLine(const CustomString& line, CustomString data[], int max_tokens) {
        int token_index = 0;
        data[token_index] = CustomString(); 
        
        for (int i = 0; i < line.length; ++i) {
            char c = line.data[i];
            if (c == ',') {
                token_index++;
                if (token_index >= max_tokens) return;
                data[token_index] = CustomString(); 
            } else {
                data[token_index].append(c);
            }
        }
    }
    
    // Métodos Auxiliares
    void _destroyTree(Node* node) {
        if (node == nullptr) return;
        _destroyTree(node->child1);
        _destroyTree(node->child2);
        delete node;
    }

    Node* _findNodeById(int id) {
        Node* current = allNodesHead;
        while (current != nullptr) {
            if (current->id == id) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void _printNodeDetails(Node* n) {
        if (n == nullptr) return;
        CustomString status;
        
        if (n->is_king) status.copy(" (REY ACTUAL)");
        if (n->is_dead) {
            if (status.length > 0) status.append(' ');
            status.append('('); status.append('F'); status.append('A'); status.append('L'); status.append('L'); status.append('E'); status.append('C'); status.append('I'); status.append('D'); status.append('O'); status.append(')');
        }
        
        cout << "ID: " << n->id << ", Nombre: " << n->name << " " << n->last_name 
             << ", Edad: " << n->age << ", Género: " << n->gender << status << endl;
    }

    void _preOrderTraversal(Node* node) {
        if (node == nullptr) return;
                
        if (!node->is_dead && node->age < 70) {
            cout << "- "; _printNodeDetails(node);
        }

        _preOrderTraversal(node->child1);
        _preOrderTraversal(node->child2);
    }
    
    bool _isEligible(Node* node) {
        return node != nullptr && !node->is_dead && node->age < 70;
    }

    Node* _getSibling(Node* node) {
        if (!node || !node->parent) return nullptr;
        Node* parent = node->parent;

        if (parent->child1 == node && parent->child2 != nullptr) return parent->child2;
        if (parent->child2 == node && parent->child1 != nullptr) return parent->child1;
        return nullptr;
    }

    Node* _findAncestorWithTwoChildren(Node* startNode) {
        Node* current = startNode;
        while (current && current->parent) {
            Node* parent = current->parent;
            if (parent->child1 && parent->child2) {
                return parent;
            }
            current = current->parent;
        }
        return nullptr;
    }

    Node* _findEligibleMale(Node* startNode) {
        if (startNode == nullptr) return nullptr;

        if (_isEligible(startNode) && startNode->gender == 'H') {
            return startNode;
        }

        Node* result = _findEligibleMale(startNode->child1);
        if (result) return result;

        return _findEligibleMale(startNode->child2);
    }

    // --- Carga CSV (Implementación Completa) ---
    void _loadFromCsv(const char* filepath) {
        FILE* file = fopen(filepath, "r");
        if (file == NULL) {
            cerr << "Error: No se pudo abrir el archivo CSV." << endl;
            return;
        }

        CustomString line;
        _readFileLine(file, line); // Leer encabezado

        while (true) {
            _readFileLine(file, line);
            if (line.length == 0) break; 

            CustomString data[9]; 
            _tokenizeLine(line, data, 9);

            if (data[8].length > 0) { 
                try {
                    int id = data[0].toInt();
                    CustomString name = data[1];
                    CustomString last_name = data[2];
                    char gender = data[3].data[0];
                    int age = data[4].toInt();
                    int id_father = data[5].toInt();
                    bool is_dead = data[6].toBool();
                    bool was_king = data[7].toBool();
                    bool is_king = data[8].toBool();

                    Node* newNode = new Node(id, name, last_name, gender, age, id_father, is_dead, was_king, is_king);
                    
                    newNode->next = allNodesHead;
                    allNodesHead = newNode;

                    if (id_father == 0) {
                        root = newNode;
                    }
                } catch (...) {
                    cerr << "Error al procesar linea: datos invalidos." << endl;
                }
            }
        }
        fclose(file);

        // Conexión del Árbol
        Node* current = allNodesHead;
        while (current != nullptr) {
            if (current->id_father != 0) {
                Node* father = _findNodeById(current->id_father);
                if (father) {
                    current->parent = father;
                    
                    if (father->child1 == nullptr) {
                        father->child1 = current; 
                    } else if (father->child2 == nullptr) {
                        father->child2 = current; 
                    }
                }
            }
            current = current->next;
        }
    }

public:
    RoyalFamilyTree() : root(nullptr), allNodesHead(nullptr) {}
    ~RoyalFamilyTree() { _destroyTree(root); }

    void loadData(const char* filepath) { _loadFromCsv(filepath); }
    
    void showSuccessionLine() { 
        cout << "\n##  Línea de Sucesión Actual (Vivos < 70) ##" << endl;
        _preOrderTraversal(root);
        cout << "------------------------------------------" << endl;
    }

    // --- Función 3: Asignación de Rey (Implementación Completa) ---
    void assignNewKing(int deadKingId) {
        Node* currentKing = _findNodeById(deadKingId);
        if (!currentKing || !currentKing->is_king) {
            cout << "Error: El nodo ID " << deadKingId << " no es el rey actual o no existe." << endl;
            return;
        }

        currentKing->is_king = false;
        currentKing->was_king = true;

        if (currentKing->age >= 70) {
            cout << "\nEl monarca ID " << currentKing->id << " abdica por edad (" << currentKing->age << " años)." << endl;
        } else {
            currentKing->is_dead = true;
            cout << "\nEl monarca ID " << currentKing->id << " ha fallecido." << endl;
        }

        Node* newKing = nullptr;

        // Búsqueda de Sucesión
        newKing = _findEligibleMale(currentKing->child1); 
        
        if (!newKing) {
            Node* sibling = _getSibling(currentKing); 
            if (sibling) {
                newKing = _findEligibleMale(sibling);
                if (!newKing && _isEligible(sibling) && sibling->gender == 'H') newKing = sibling;
            }
        }
        
        if (!newKing && currentKing->parent) { 
            Node* uncle = _getSibling(currentKing->parent);
            if (uncle) {
                newKing = _findEligibleMale(uncle);
                if (!newKing && _isEligible(uncle) && uncle->gender == 'H' && uncle->child1 == nullptr && uncle->child2 == nullptr) {
                    newKing = uncle;
                }
            }
        }

        if (!newKing) { 
            Node* ancestor = _findAncestorWithTwoChildren(currentKing);
            Node* searchStart = ancestor ? ancestor : root;
            newKing = _findEligibleMale(searchStart);
        }

        // B. BÚSQUEDA DE MUJER 
        if (!newKing) {
            cout << "No se encontraron varones elegibles. Buscando Reina..." << endl;
            Node* current = allNodesHead;
            Node* youngestQueen = nullptr;

            while (current != nullptr) {
                if (_isEligible(current) && current->gender == 'M' && current->age >= 15) {
                    if (youngestQueen == nullptr || current->age < youngestQueen->age) {
                        youngestQueen = current;
                    }
                }
                current = current->next;
            }
            newKing = youngestQueen;
        }

        // C. ASIGNAR LA CORONA
        if (newKing) {
            newKing->is_king = true;
            cout << "\n¡NUEVO MONARCA ASIGNADO! " << endl;
            CustomString title;
            if (newKing->gender == 'H') title.copy("Rey"); else title.copy("Reina");
            
            cout << title << ": ID " << newKing->id << ", " << newKing->name << " " << newKing->last_name << endl;
        } else {
            cout << "\n ¡ADVERTENCIA! No se encontró ningún descendiente elegible para heredar el trono." << endl;
        }
        cout << "--------------------------------------------------" << endl;
    }

    // --- Función 4: Modificación de Datos (Implementación Completa) ---
    void updateNodeData(int nodeId) {
        Node* node = _findNodeById(nodeId);
        if (!node) {
            cout << "Error: Nodo con ID " << nodeId << " no encontrado." << endl;
            return;
        }

        cout << "\n##  Modificando: " << node->name << " " << node->last_name << endl;
        cout << "Ingrese el campo a modificar (name, last_name, gender, age, is_dead (0/1), was_king (0/1), is_king (0/1)): ";
        
        char key_input[64];
        if (!(cin >> key_input)) return;
        CustomString key; key.copy(key_input);
        
        if (key.startsWith("id") || key.startsWith("id_father")) {
            cout << "Advertencia: El campo es inmutable." << endl;
            return;
        }
        
        cout << "Ingrese el nuevo valor para " << key << ": ";
        char value_input[64];
        if (!(cin >> value_input)) return;
        CustomString value; value.copy(value_input);


        bool success = false;
        
        if (key.startsWith("name")) { node->name = value; success = true; }
        else if (key.startsWith("last_name")) { node->last_name = value; success = true; }
        else if (key.startsWith("gender") && (value.data[0] == 'H' || value.data[0] == 'M')) { node->gender = value.data[0]; success = true; }
        else if (key.startsWith("age")) { node->age = value.toInt(); success = true; }
        else if (key.startsWith("is_dead")) { node->is_dead = value.toBool(); success = true; }
        else if (key.startsWith("was_king")) { node->was_king = value.toBool(); success = true; }
        else if (key.startsWith("is_king")) { node->is_king = value.toBool(); success = true; }
        
        if (success) {
            cout << "  - '" << key << "' actualizado a: " << value << endl;
            cout << " Actualización completada." << endl;
        } else {
            cout << "Advertencia: Campo no reconocido o valor inválido." << endl;
        }
    }
};

#endif // ROYALFAMILYTREE_H
