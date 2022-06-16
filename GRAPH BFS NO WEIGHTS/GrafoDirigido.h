
#include <vector>

using namespace std;

class GrafoDirigido {

   struct Arco {
      int vecino;
      float peso;
      Arco * siguiente;
      Arco(int, float, Arco *);
   };

   struct Vertice {
      Arco * primerArcoDeEntrada;
      Arco * primerArcoDeSalida;
      int gradoDeEntrada;
      int gradoDeSalida;
      Vertice();
   };

   vector<Vertice> vertices;
   
 public:

   GrafoDirigido(const char *);

   void mostrar() const;

   int cantidadDeVertices() const;

   vector<int> arbolDeCaminosOptimosSinPesos(int) const;

};

