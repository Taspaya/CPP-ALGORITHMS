
#include <vector>

using namespace std;

class GrafoNoDirigido {

   struct Arco {
      int vecino;
      float peso;
      Arco * siguiente;
      Arco(int, float, Arco *);
   };

   struct Vertice {
      Arco * primerArco;
      int grado;
      Vertice();
   };

   vector<Vertice> vertices;
   
   bool esColorValido(int, const vector<int> &) const;

   bool colorearGrafo(int, int, vector<int> &) const;

public:

   GrafoNoDirigido(const char *);

   void mostrar() const;

   int cantidadDeVertices() const;

   vector<int> colorearGrafo(int) const;

};
