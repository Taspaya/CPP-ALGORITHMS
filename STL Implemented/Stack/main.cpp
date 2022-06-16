
#include <iostream>
using namespace std;

#include <cstdlib>   // rand

#include "Pila.h"

int main () {
   Pila pila;
   int i;

   for (i = 11; i < 100; i += 11) {
      cout << "Insertando " << i << ": Pila=";
      pila.apilar(i);
      pila.mostrar();
      cout << "\tTalla=" << pila.talla() << endl;
   }

   cout << endl;

   while ( ! pila.estaVacia()) {
      cout << "Eliminando " << pila.cima() << ": Pila=";
      pila.desapilar();
      pila.mostrar();
      cout << "\tTalla=" << pila.talla() << endl;

      int unDatoCualquiera = rand() % 100;
      cout << "Insertando " << unDatoCualquiera << ": Pila=";
      pila.apilar(unDatoCualquiera);
      pila.mostrar();
      cout << "\tTalla=" << pila.talla() << endl;

      cout << "Eliminando " << pila.cima() << ": Pila=";
      pila.desapilar();
      pila.mostrar();
      cout << "\tTalla=" << pila.talla() << endl;
   }

   try {
      cout << "Eliminando " << pila.cima() << ": Pila=";
   } catch (string mensaje) {
      cout << "Probando excepcion: " << mensaje << endl;
   }
  
   try {
      pila.desapilar();
   } catch (string mensaje) {
      cout << "Probando excepcion: " << mensaje << endl;
   }
  

}
