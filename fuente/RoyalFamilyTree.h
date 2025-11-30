
#ifndef ROYALFAMILYTREE_H
#define ROYALFAMILYTREE_H

// ÚNICAS LIBRERÍAS PERMITIDAS DENTRO DE TU .h:
#include <iostream>  // Para cout/cin
#include <cstdio>    // Para fopen/fgetc

using namespace std;

// --- Implementación manual de la Clase String (Sustituye a std::string y std::sstream) ---
class CustomString {
public:
    char data[64]; 
    int length;

    CustomString();
    void append(char c);
    void copy(const char* s);
    friend ostream& operator<<(ostream& os, const CustomString& s);
    CustomString& operator=(const CustomString& other);
    bool startsWith(const char* prefix) const;
    int toInt() const; // Sustituye stoi
    bool toBool() const;
};

// --- ESTRUCTURA NODE (Árbol y Lista Enlazada) ---
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

    Node* child1; 
    Node* child2; 
    Node* parent; 
    Node* next; 

    Node(int _id, const CustomString& _name, const CustomString& _last_name, char _gender, int _age, int _id_father, bool _is_dead, bool _was_king, bool _is_king);
};

// --- CLASE ROYALFAMILYTREE (Interfaz Pública) ---
class RoyalFamilyTree {
private:
    Node* root; 
    Node* allNodesHead; 
    
    // Métodos privados (Implementación manual de I/O y Lógica de Árbol)
    void _readFileLine(FILE* file, CustomString& result);
    void _tokenizeLine(const CustomString& line, CustomString data[], int max_tokens);
    void _destroyTree(Node* node);
    Node* _findNodeById(int id);
    void _printNodeDetails(Node* n);
    void _preOrderTraversal(Node* node);
    bool _isEligible(Node* node);
    Node* _getSibling(Node* node);
    Node* _findAncestorWithTwoChildren(Node* startNode);
    Node* _findEligibleMale(Node* startNode);
    void _loadFromCsv(const char* filepath); // Sustituye fstream
    
public:
    RoyalFamilyTree();
    ~RoyalFamilyTree();

    // Funciones del Menú
    void loadData(const char* filepath);
    void showSuccessionLine();
    void assignNewKing(int deadKingId);
    void updateNodeData(int nodeId);
    
    // Para main.cpp
    Node* getRoot() const { return root; }
};

#endif // ROYALFAMILYTREE_H
