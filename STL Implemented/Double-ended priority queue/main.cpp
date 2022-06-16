
#include <iostream>
#include <vector>
using namespace std;

#include <cstdlib>   // rand

#include "ColaDePrioridadDeDobleFin.h"

int main () {
   ColaDePrioridadDeDobleFin cola;
   int datoAleatorio;

   for (int i = 0; i < 10; i ++) {
    
      datoAleatorio = rand() % 10;
      cout << "Insertando " << datoAleatorio << ": Cola = ";
      cola.insertar(datoAleatorio);
      cola.mostrar();
    
   }

   while (cola.talla() > 0) {
  
      cout << "Eliminando minimo " << cola.consultarMinimo() << endl;
      cola.eliminarMinimo();

   }
  
   for (int i = 0; i < 10; i ++) {
    
      datoAleatorio = rand() % 10;
      cout << "Insertando " << datoAleatorio << ": Cola = ";
      cola.insertar(datoAleatorio);
      cola.mostrar();
    
   }

   while (cola.talla() > 0) {
  
      cout << "Eliminando maximo " << cola.consultarMaximo() << endl;;
      cola.eliminarMaximo();

   }

}
