
#include <iostream>
using namespace std;

#include "GrafoDirigido.h"

int main () {

   try {
      GrafoDirigido miGrafo("noReachable.gr"); 
      //      miGrafo.mostrar();

      int origen = 3;
                                    
      vector<int> arbolDeCaminos = miGrafo.arbolDeCaminosOptimosSinPesos(origen);
      cout << "Arches on the optimal road tree without weights from " << origen << ":" << endl;
      for (int i = 0; i < arbolDeCaminos.size(); i++)
	 if (arbolDeCaminos[i] >= 0)
	    cout << "  " << arbolDeCaminos[i] << " --> " << i << endl;
      cout << "Parents vector: ";
      for (int i = 0; i < arbolDeCaminos.size(); i++)
	 cout << " " << arbolDeCaminos[i];
      cout << endl;
      
   } catch(string error) {
      cerr << error << endl;
   }

}
