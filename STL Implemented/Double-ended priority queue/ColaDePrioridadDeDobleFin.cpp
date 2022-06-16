
#include <iostream>
#include <string>
using namespace std;

#include "ColaDePrioridadDeDobleFin.h"

ColaDePrioridadDeDobleFin::Nodo::Nodo(int laPrioridad, Nodo * elAnterior, Nodo * elSiguiente)
   : prioridad{laPrioridad}, anterior{elAnterior}, siguiente{elSiguiente} {
}

ColaDePrioridadDeDobleFin::ColaDePrioridadDeDobleFin() 
   : minimo{nullptr}, maximo{nullptr}, laTalla{0} {
}

void ColaDePrioridadDeDobleFin::insertar(int prioridad) {
   laTalla++;
   if (minimo == nullptr) {
      minimo = new Nodo(prioridad, nullptr, nullptr);
      maximo = minimo;
   } else if (prioridad <= minimo->prioridad) {
      minimo = new Nodo(prioridad, nullptr, minimo);
      minimo->siguiente->anterior = minimo;
   } else if (prioridad >= maximo->prioridad) {
      maximo = new Nodo(prioridad, maximo, nullptr);
      maximo->anterior->siguiente = maximo;
   } else {
      for (Nodo * actual = minimo; actual != nullptr; actual = actual->siguiente) {
	 if (actual->prioridad > prioridad) {
	    Nodo * nuevo = new Nodo(prioridad, actual->anterior, actual);
	    actual->anterior->siguiente = nuevo;
	    actual->anterior = nuevo;
	    return;
	 }
      }
   }
}
 
void ColaDePrioridadDeDobleFin::eliminar(int prioridad) {
   for (Nodo * actual = minimo; actual != nullptr && actual->prioridad <= prioridad; actual = actual->siguiente) {
      if (actual->prioridad == prioridad) {
	 if (minimo == maximo) {
	    minimo = maximo = nullptr;
	 } else if (actual == minimo) {
	    minimo = minimo->siguiente;
	    minimo->anterior = nullptr;
	 } else if (actual == maximo) {
	    maximo = maximo->anterior;
	    maximo->siguiente = nullptr;
	 } else {
	    actual->anterior->siguiente = actual->siguiente;
	    actual->siguiente->anterior = actual->anterior;
	 }
	 delete actual;
	 laTalla--;
	 return;
      }
   }
   throw string("Intentando eliminar un elemento que no esta");
}

void ColaDePrioridadDeDobleFin::eliminarMinimo() {
   if (minimo == nullptr)
      throw string("Intentando eliminar el minimo en un conjunto vacio");

   Nodo * basura = minimo;
   if (minimo == maximo) {
      minimo = maximo = nullptr;
   } else {
      minimo = minimo->siguiente;
      minimo->anterior = nullptr;
   }
   delete basura;
   laTalla--;
}

int ColaDePrioridadDeDobleFin::consultarMinimo() const {
   if (minimo == nullptr)
      throw string("Intentando consultar el minimo en un conjunto vacio");

   return minimo->prioridad;
}

void ColaDePrioridadDeDobleFin::eliminarMaximo() {
   if (maximo == nullptr)
      throw string("Intentando eliminar el maximo en un conjunto vacio");

   Nodo * basura = maximo;
   if (minimo == maximo) {
      minimo = maximo = nullptr;
   } else {
      maximo = maximo->anterior;
      maximo->siguiente = nullptr;
   }
   delete basura;
   laTalla--;
}

int ColaDePrioridadDeDobleFin::consultarMaximo() const {
   if (maximo == nullptr)
      throw string("Intentando consultar el maximo en un conjunto vacio");

   return maximo->prioridad;
}

void ColaDePrioridadDeDobleFin::mostrar() const {
   cout << "[";
   for (Nodo * actual = minimo; actual != nullptr; actual = actual->siguiente) {
      cout << actual->prioridad;
      if (actual != maximo)
	 cout << " < ";
   }
   cout << "] [";
   for (Nodo * actual = maximo; actual != nullptr; actual = actual->anterior) {
      cout << actual->prioridad;
      if (actual != minimo)
	 cout << " > ";
   }
   cout << "]" << endl;
}

int ColaDePrioridadDeDobleFin::talla() const {
   return laTalla;
}

