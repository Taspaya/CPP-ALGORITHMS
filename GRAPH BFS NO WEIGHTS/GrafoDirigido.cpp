
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
using namespace std;

#include "GrafoDirigido.h"

GrafoDirigido::Arco::Arco(int elVecino, float elPeso, Arco * elSiguiente)
  : vecino{elVecino}, peso{elPeso}, siguiente{elSiguiente} {

}

GrafoDirigido::Vertice::Vertice()
  : primerArcoDeEntrada{nullptr}, primerArcoDeSalida{nullptr}, gradoDeEntrada{0}, gradoDeSalida{0} {

}

void GrafoDirigido::mostrar() const {

   cout << "Arcos de salida para cada vertice: " << endl;
   for (int v = 0; v < vertices.size(); v++) {
      cout << "  vertice " << v << ":" << endl;
      for (Arco * arco = vertices[v].primerArcoDeSalida; arco != nullptr; arco = arco->siguiente)
	 cout << "    " << v << "-->" << arco->vecino << " (peso = " << arco->peso << ")" << endl;
      cout << endl;
   }
  
   cout << "Arcos de entrada para cada vertice: " << endl;
   for (int v = 0; v < vertices.size(); v++) {
      cout << "  vertice " << v << ":" << endl;
      for (Arco * arco = vertices[v].primerArcoDeEntrada; arco != nullptr; arco = arco->siguiente)
	 cout << "    " << arco->vecino << "-->" << v << " (peso = " << arco->peso << ")" << endl;
      cout << endl;
   }

}

GrafoDirigido::GrafoDirigido(const char * nombreFichero) {

   ifstream flujoFichero(nombreFichero);

   if (! flujoFichero.is_open() )
      throw string("ERROR: file not found ") +  nombreFichero;

   string linea;
   char tipoLinea;
   int cantidadVertices = -1, mayorVertice = -1;
  
   struct DatosArco {
      int origen, destino;
      float peso;
   } datosArco;

   vector<DatosArco> datos;

   while(getline(flujoFichero, linea)) {
      istringstream flujoLinea(linea);
      if (flujoLinea >> tipoLinea)
	 if (tipoLinea == 'n') {
	    if (!(flujoLinea >> cantidadVertices) || cantidadVertices <= 0)
	       throw string("ERROR: incorrect number of vertices in the file ") +  nombreFichero;
	 } else if (tipoLinea == 'a') {
	    if (!(flujoLinea >> datosArco.origen >> datosArco.destino >> datosArco.peso))
	       throw string("ERROR: incomplete arc in the file ") +  nombreFichero;
	    if (datosArco.origen < 0 || datosArco.destino < 0)
	       throw string("ERROR: negative vertex in the file ") +  nombreFichero;
	    datos.push_back(datosArco);
	    mayorVertice = max(mayorVertice, datosArco.origen);
	    mayorVertice = max(mayorVertice, datosArco.destino);
	 }
   }
  
   flujoFichero.close();

   if (cantidadVertices != -1) {
      if (mayorVertice >= cantidadVertices)
	 throw string("ERROR: vertex exceeds number of vertices declared in file ") +  nombreFichero;
   } else
      if (mayorVertice == -1)
	 throw string("ERROR: no vertices in the file ") +  nombreFichero;
      else
	 cantidadVertices = mayorVertice + 1;

   vertices.resize(cantidadVertices);

   for (const auto & datosArco : datos) {
      vertices[datosArco.origen].primerArcoDeSalida = new Arco(datosArco.destino,
							       datosArco.peso,
							       vertices[datosArco.origen].primerArcoDeSalida);
      vertices[datosArco.origen].gradoDeSalida++;
      vertices[datosArco.destino].primerArcoDeEntrada = new Arco(datosArco.origen,
								 datosArco.peso,
								 vertices[datosArco.destino].primerArcoDeEntrada);
      vertices[datosArco.destino].gradoDeEntrada++;
   }

}

int GrafoDirigido::cantidadDeVertices() const {

   return vertices.size();

}
   
vector<int> GrafoDirigido::arbolDeCaminosOptimosSinPesos(int origen) const {

   vector<bool> visitado(vertices.size(), false);
   vector<int> padre(vertices.size(), -1);

   queue<int> cola;

   padre[origen] = -2;
   visitado[origen] = true;
   cola.push(origen);

   while (! cola.empty()) {
      int v = cola.front();
      cola.pop();
      for (Arco * arco = vertices[v].primerArcoDeSalida; arco != nullptr; arco = arco->siguiente)
	 if (! visitado[arco->vecino]) {
	    padre[arco->vecino] = v;
	    visitado[arco->vecino] = true;
	    cola.push(arco->vecino);
	 }
   }

   return padre;

}

