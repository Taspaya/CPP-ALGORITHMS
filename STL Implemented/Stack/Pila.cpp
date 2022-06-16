
#include <iostream>
#include <string>
using namespace std;

#include "Pila.h"

Pila::Nodo::Nodo(int d, Nodo * s) : dato{d}, siguiente{s} {
}

Pila::Pila() : laCima{nullptr}, laTalla{0} {

}
  
void Pila::apilar(int unDato) {
   laCima = new Nodo(unDato, laCima);
   laTalla++;
}

void Pila::desapilar() {
   if (laCima == nullptr)
      throw string("Intentando desapilar en una pila vacia");

   Nodo * basura = laCima;
   laCima = laCima->siguiente;
   delete basura;
   laTalla--;
}

int Pila::cima() const {
   if (laCima == nullptr)
      throw string("Intentando consultar la cima en una pila vacia");
   return laCima->dato;
}

void Pila::mostrar() const {
   cout << "[";
   for (Nodo * actual = laCima; actual != nullptr; actual = actual->siguiente) {
      cout << actual->dato;
      if (actual->siguiente != nullptr)
	 cout << ", ";
   }
   cout << "]";
}

int Pila::talla() const {
   return laTalla;
}

bool Pila::estaVacia() const {
   return laCima == nullptr;
}

