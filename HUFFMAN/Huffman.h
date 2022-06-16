#include <string>
#include <vector>
#include <utility> // pair
#include <map>

using namespace std;

class Huffman {

    struct Nodo {
        char   caracter;
        float  frecuencia;
        Nodo* izquierdo;
        Nodo* derecho;
        Nodo* padre;
        char   bit;
        Nodo(char, float);
    };

    Nodo* raiz;
    map<char, Nodo*> hojas;

public:

    Huffman(const vector< pair<char, float> >&);
    string codificar(const string&) const;
    string decodificar(const string&) const;

};