
class Pila {

   struct Nodo {
      int dato;
      Nodo * siguiente;
      Nodo(int, Nodo *);
   };

   Nodo * laCima;
   int laTalla;

public:

   Pila();
  
   void apilar(int);

   void desapilar();

   int cima() const;

   void mostrar() const;

   int talla() const;

   bool estaVacia() const;

};
