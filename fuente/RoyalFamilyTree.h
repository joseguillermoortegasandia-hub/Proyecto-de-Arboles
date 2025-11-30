#ifndef ROYALFAMILYTREE_H
#define ROYALFAMILYTREE_H

#include <iostream>  
#include <cstdio>    

using namespace std;

// --- CustomString (Declaraciones) ---
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
    int toInt() const; 
    bool toBool() const;
};

// --- ESTRUCTURA NODE (Definición y Constructor) ---
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

    // Implementación del constructor aquí (es una buena práctica para clases pequeñas)
    Node(int _id, const CustomString& _name, const CustomString& _last_name, char _gender, int _age, int _id_father, bool _is_dead, bool _was_king, bool _is_king)
        : id(_id), gender(_gender), age(_age), id_father(_id_father),
          is_dead(_is_dead), was_king(_was_king), is_king(_is_king),
          child1(nullptr), child2(nullptr), parent(nullptr), next(nullptr) {
              name = _name;
              last_name = _last_name;
          }
};

// --- CLASE ROYALFAMILYTREE (Interfaz Pública y Privada) ---
class RoyalFamilyTree {
private:
    Node* root; 
    Node* allNodesHead; 
    
    // Métodos privados
    void _readFileLine(FILE* file, CustomString& result);
    void _tokenizeLine(const CustomString& line, CustomString data[], int max_tokens);
    void _destroyTree(Node* node); // REVISADA
    Node* _findNodeById(int id);
    void _printNodeDetails(Node* n);
    void _preOrderTraversal(Node* node);
    bool _isEligible(Node* node);
    Node* _getSibling(Node* node); // REVISADA
    Node* _findAncestorWithTwoChildren(Node* startNode); // REVISADA
    Node* _findEligibleMale(Node* startNode);
    void _loadFromCsv(const char* filepath); 
    
public:
    RoyalFamilyTree();
    ~RoyalFamilyTree();

    void loadData(const char* filepath);
    void showSuccessionLine();
    void assignNewKing(int deadKingId);
    void updateNodeData(int nodeId);
    
    Node* getRoot() const { return root; }
};

#endif // ROYALFAMILYTREE_H
