
#include <iostream>
#include <string>
using namespace std;

#include "Cola.h"

Cola::Nodo::Nodo(int d) : dato{d}, siguiente{nullptr} {
}

Cola::Cola() : primero{nullptr}, ultimo{nullptr} {
}
  
void Cola::encolar(int d) {
   Nodo * nuevo = new Nodo(d);

   if (primero == nullptr)
      primero = nuevo;
   else
      ultimo->siguiente = nuevo;
   ultimo = nuevo;
}

void Cola::desencolar() {
   if (primero == nullptr)
      throw string("Intentando desencolar en una cola vacia");

   Nodo * aux = primero;
   primero = primero->siguiente;
   delete aux;
   if (primero == nullptr)
      ultimo = nullptr;
}

int Cola::consultarPrimero() const {
   if (primero == nullptr)
      throw string("Intentando consultar el primero en una cola vacia");
   return primero->dato;
}

void Cola::mostrar() const {
   cout << "[";
   for (Nodo * aux = primero; aux != nullptr; aux = aux->siguiente) {
      cout << aux->dato;
      if (aux != ultimo)
	 cout << ", ";
   }
   cout << "]";
}

bool Cola::estaVacia() const {
   return primero == nullptr;
}

