#include <queue> // Para usar priority_queue

Huffman::Nodo::Nodo(char c, float f)
    : caracter{ c }, frecuencia{ f }, izquierdo{ nullptr }, derecho{ nullptr }, padre{ nullptr } {
}

Huffman::Huffman(const vector< pair<char, float> >& frecuencias) : raiz{ nullptr } {

    if (frecuencias.size() < 2)
        throw string("Necesitamos al menos dos caracteres con sus frecuencias.");

    class ComparadorNodos {
    public:
        bool operator() (Nodo* n1, Nodo* n2) const {
            return n1->frecuencia > n2->frecuencia;
            // Para que salgan de la cola de prioridad de menor a mayor
        }
    };

    priority_queue<Nodo*, vector<Nodo*>, ComparadorNodos> colaPrioridad;

    for (auto dato : frecuencias) {
        Nodo* hoja = new Nodo(dato.first, dato.second);
        colaPrioridad.push(hoja);
        hojas[dato.first] = hoja;
    }

    while (colaPrioridad.size() > 1) {
        Nodo* n = new Nodo(' ', 0);
        n->izquierdo = colaPrioridad.top();
        colaPrioridad.pop();
        n->derecho = colaPrioridad.top();
        colaPrioridad.pop();
        n->frecuencia = n->izquierdo->frecuencia + n->derecho->frecuencia;
        n->izquierdo->padre = n;
        n->izquierdo->bit = '0';
        n->derecho->padre = n;
        n->derecho->bit = '1';
        colaPrioridad.push(n);
    }
    raiz = colaPrioridad.top();

}