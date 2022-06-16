class Conjunto {

    struct Nodo {
        int dato;
        Nodo* izquierdo;
        Nodo* derecho;
        Nodo(int);
    };

    Nodo* raiz;

    void insertar(int, Nodo*&);
    void eliminar(int, Nodo*&);
    int  minimoEnSubarbol(Nodo*) const;
    int suma(Nodo*) const;
    int altura(Nodo* n) const;
    void incrementar(Nodo* n) const;
    void mostrar(Nodo* n) const;


public:

    Conjunto();
    void insertar(int);
    void eliminar(int);
    bool buscar(int) const;
    int suma() const;
    int altura() const;
    void incrementarTodos() const;
    void mostrarOrdenados() const;
};