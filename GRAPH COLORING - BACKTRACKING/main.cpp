
#include <iostream>
using namespace std;

#include "GrafoNoDirigido.h"


void probar(const char * nombreFichero) {

   try {
      GrafoNoDirigido miGrafo(nombreFichero); 
      //      miGrafo.mostrar();

      cout << endl << "Coloreando el grafo " << nombreFichero << endl;

      for (int colores = 2; colores <= 4; colores++) {
	 cout << endl << "\tCon " << colores << " colores:" << endl;
	 try {
	    vector<int> solucion = miGrafo.colorearGrafo(colores);
	    for (int v = 0; v < solucion.size(); v++)
	       cout << "\t\tcolor[" << v << "] = " << solucion[v] << endl;
	 } catch(string mensaje) {
	    cout << "\t\t" << mensaje << endl;
	 }
      }

   } catch(string error) {
      cerr << error << endl;
   }
}

int main () {

   probar("ejemploIslas.gr"); 
   probar("ejemploIslas2.gr"); 
   
}


