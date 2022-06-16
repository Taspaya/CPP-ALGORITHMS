#include <iostream>
using namespace std;

#include "Conjunto.h"

Conjunto::Nodo::Nodo(int elDato) : dato{ elDato }, izquierdo{ nullptr }, derecho{ nullptr } {
}

Conjunto::Conjunto() : raiz{ nullptr } {
}

void Conjunto::insertar(int unDato) {
    insertar(unDato, raiz);
}

void Conjunto::insertar(int unDato, Nodo*& n) {
    if (n == nullptr)
        n = new Nodo(unDato);
    else if (unDato < n->dato)
        insertar(unDato, n->izquierdo);
    else if (unDato > n->dato)
        insertar(unDato, n->derecho);
    // No insertamos duplicados
}

int Conjunto::minimoEnSubarbol(Nodo* n) const { // Sabiendo que n != nullptr
    if (n->izquierdo == nullptr)
        return n->dato;
    return minimoEnSubarbol(n->izquierdo);
}

void Conjunto::eliminar(int unDato) {
    eliminar(unDato, raiz);
}

void Conjunto::eliminar(int unDato, Nodo*& n) {
    if (n == nullptr)
        return;
    if (unDato < n->dato)
        eliminar(unDato, n->izquierdo);
    else if (unDato > n->dato)
        eliminar(unDato, n->derecho);
    else if (n->izquierdo != nullptr && n->derecho != nullptr) {
        n->dato = minimoEnSubarbol(n->derecho);
        eliminar(n->dato, n->derecho);
    }
    else {
        Nodo* basura = n;
        if (n->izquierdo != nullptr)
            n = n->izquierdo;
        else
            n = n->derecho;
        delete basura;
    }
}

bool Conjunto::buscar(int unDato) const {
    Nodo* n = raiz;
    while (n != nullptr)
        if (unDato < n->dato)
            n = n->izquierdo;
        else if (unDato > n->dato)
            n = n->derecho;
        else
            return true;
    return false;
}



// ### RECURSIVITY ###
#pragma region RECURSIVITY
// Add all the values of the tree
int Conjunto::suma() const {
    if (raiz == nullptr) return 0;  //null check root
    return suma(raiz);
}

int Conjunto::suma(Nodo* n) const {

    if (n->izquierdo != nullptr && n->derecho != nullptr)       // base case
        return n->dato + suma(n->izquierdo) + suma(n->derecho);
    else if (n->izquierdo != nullptr)                           // add left
        return n->dato + suma(n->izquierdo);
    else if (n->derecho != nullptr)                             // add right
        return n->dato + suma(n->derecho);
    else return n->dato;
}


// Increase all
void Conjunto::incrementar(Nodo* n) const {

    if (n->izquierdo != nullptr) incrementar(n->izquierdo);     //increase left
    if (n->derecho != nullptr) incrementar(n->derecho);         //increase right

    n->dato++;                                                  //base case
}

void Conjunto::incrementarTodos() const{
    if (raiz != nullptr)                                        //null check root
        incrementar(raiz);                                      //increase from root
}

// Show Sorted
void Conjunto::mostrarOrdenados() const {
    if (raiz != nullptr)                                        //null check root
        mostrar(raiz);                                          //show from root
}

void Conjunto::mostrar(Nodo* n) const {
    if (n->izquierdo != nullptr) mostrar(n->izquierdo);         //show left
    std::cout << n->dato << std::endl;                          //print data
    if (n->derecho != nullptr) mostrar(n->derecho);             //show right
}

// Get Height

int Conjunto::altura() const {
    return altura(raiz);
}

int Conjunto::altura(Nodo* n) const {
    if (n == nullptr)
        return -1;
    return 1 + max(altura(n->izquierdo), altura(n->derecho));   //return the max between left and right
}

#pragma endregion


// ### ITERATIVE ###
#pragma region ITERATIVE
// show sorted
void Conjunto::mostrarIterativo() const
{
    if (raiz == nullptr) return;                                //null check root

                                                                // create an empty stack
    stack<Nodo*> stack;         
    Nodo* curr = raiz;                                          // start from the root node

    // if the current node is null and the stack is also empty, we are done
    while (!stack.empty() || curr != nullptr)
    {
        if (curr != nullptr)
        {
            stack.push(curr);
            curr = curr->izquierdo;                             //if curr exists, go full left
        }
        else {
            curr = stack.top();                                            
            stack.pop();                                        
            cout << curr->dato << " ";
            curr = curr->derecho;
        }
    }
}

// Increase all
void Conjunto::incrementarIterativo() const
{
    if (raiz == nullptr) return;
    int i = 0;
    // create an empty stack
    stack<Nodo*> stack;

    // start from the root node (set current node to the root node)
    Nodo* curr = raiz;

    // if the current node is null and the stack is also empty, we are done
    while (!stack.empty() || curr != nullptr)
    {
        // if the current node exists, push it into the stack (defer it)
        // and move to its left child
        if (curr != nullptr)
        {
            stack.push(curr);
            curr = curr->izquierdo;
        }
        else {
            // otherwise, if the current node is null, pop an element from the stack,
            // increase it, and finally set the current node to its right child
            curr = stack.top();
            stack.pop();
            curr->dato++;

            curr = curr->derecho;
        }
    }
}

bool Conjunto::BuscarIterativo(int n) const
{
    if (raiz == nullptr) return;
    int i = 0;
    // create an empty stack
    stack<Nodo*> stack;

    // start from the root node (set current node to the root node)
    Nodo* curr = raiz;

    // if the current node is null and the stack is also empty, we are done
    while (!stack.empty() || curr != nullptr)
    {
        // if the current node exists, push it into the stack (defer it)
        // and move to its left child
        if (curr != nullptr)
        {
            stack.push(curr);
            curr = curr->izquierdo;
        }
        else {
            // otherwise, if the current node is null, pop an element from the stack,
            // return the data if == n, else, the current node to its right child
            curr = stack.top();
            stack.pop();
            if (curr->dato == n)    return true;
            curr = curr->derecho;
        }
    }

    return false;
}
#pragma endregion