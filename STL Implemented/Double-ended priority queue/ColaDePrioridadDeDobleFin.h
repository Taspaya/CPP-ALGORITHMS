
class ColaDePrioridadDeDobleFin {

   struct Nodo {
      int prioridad;
      Nodo * anterior;
      Nodo * siguiente;
      Nodo(int, Nodo *, Nodo *);
   };

   Nodo * minimo;
   Nodo * maximo;
   int    laTalla;

 public:

   ColaDePrioridadDeDobleFin(); // O(1)

   void insertar(int); // O(n)
 
   void eliminar(int); // O(n)

   void eliminarMinimo(); // O(1) 

   int consultarMinimo() const; // O(1) 

   void eliminarMaximo(); // O(1) 

   int consultarMaximo() const; // O(1)

   int talla() const; // O(1)

   void mostrar() const; // O(n)

};
