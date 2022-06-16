
#include <iostream>
using namespace std;

#include <cstdlib>   // rand

#include "Cola.h"

int main () {
   Cola cola;
   int i;

   for (i = 11; i < 100; i += 11) {
      cout << "Insertando " << i << ": Cola = ";
      cola.encolar(i);
      cola.mostrar();
      cout << endl;
   }

   cout << endl;

   while ( ! cola.estaVacia()) {
      cout << "Eliminando " << cola.consultarPrimero() << ": Cola = ";
      cola.desencolar();
      cola.mostrar();
      cout << endl;

      int unDatoCualquiera = rand() % 100;
      cout << "Insertando " << unDatoCualquiera << ": Cola = ";
      cola.encolar(unDatoCualquiera);
      cola.mostrar();
      cout << endl;

      cout << "Eliminando " << cola.consultarPrimero() << ": Cola = ";
      cola.desencolar();
      cola.mostrar();
      cout << endl;
   }

}
