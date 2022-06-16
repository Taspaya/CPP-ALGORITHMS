
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "GrafoNoDirigido.h"

GrafoNoDirigido::Arco::Arco(int elVecino, float elPeso, Arco * elSiguiente)
  : vecino{elVecino}, peso{elPeso}, siguiente{elSiguiente} {

}

GrafoNoDirigido::Vertice::Vertice()
  : primerArco{nullptr}, grado{0} {

}

void GrafoNoDirigido::mostrar() const {

   cout << "Arcos para cada vertice: " << endl;
   for (int v = 0; v < vertices.size(); v++) {
      cout << "  vertice " << v << ":" << endl;
      for (Arco * arco = vertices[v].primerArco; arco != nullptr; arco = arco->siguiente)
	 cout << "    " << v << "---" << arco->vecino << " (peso = " << arco->peso << ")" << endl;
      cout << endl;
   }
  

}

GrafoNoDirigido::GrafoNoDirigido(const char * nombreFichero) {

   ifstream flujoFichero(nombreFichero);

   if (! flujoFichero.is_open() )
      throw string("ERROR: imposible abrir el fichero ") +  nombreFichero;

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
	       throw string("ERROR: cantidad de vertices incorrecta en el fichero ") +  nombreFichero;
	 } else if (tipoLinea == 'a') {
	    if (!(flujoLinea >> datosArco.origen >> datosArco.destino >> datosArco.peso))
	       throw string("ERROR: arco incompleto en el fichero ") +  nombreFichero;
	    if (datosArco.origen < 0 || datosArco.destino < 0)
	       throw string("ERROR: vertice negativo en el fichero ") +  nombreFichero;
	    datos.push_back(datosArco);
	    mayorVertice = max(mayorVertice, datosArco.origen);
	    mayorVertice = max(mayorVertice, datosArco.destino);
	 }
   }
  
   flujoFichero.close();

   if (cantidadVertices != -1) {
      if (mayorVertice >= cantidadVertices)
	 throw string("ERROR: vertice supera cantidad de vertices declarada en el fichero ") +  nombreFichero;
   } else
      if (mayorVertice == -1)
	 throw string("ERROR: no hay vertices en el fichero ") +  nombreFichero;
      else
	 cantidadVertices = mayorVertice + 1;

   vertices.resize(cantidadVertices);

   for (const auto & datosArco : datos) {
      vertices[datosArco.origen].primerArco = new Arco(datosArco.destino,
						       datosArco.peso,
						       vertices[datosArco.origen].primerArco);
      vertices[datosArco.origen].grado++;
      vertices[datosArco.destino].primerArco = new Arco(datosArco.origen,
							datosArco.peso,
							vertices[datosArco.destino].primerArco);
      vertices[datosArco.destino].grado++;
   }

}

int GrafoNoDirigido::cantidadDeVertices() const {

   return vertices.size();

}
   
bool GrafoNoDirigido::esColorValido(int vertice,
				    const vector<int> & coloreado) const {

   if (vertice == 0)
      return true;

   for (Arco * arco = vertices[vertice].primerArco; arco != nullptr; arco = arco->siguiente)
      if (coloreado[vertice] == coloreado[arco->vecino])
	 return false;

   return true;

}

bool GrafoNoDirigido::colorearGrafo(int vertice,
				    int cantidadDeColores,
				    vector<int> & coloreado) const {
   
   if (esColorValido(vertice - 1, coloreado)) {

      if (vertice == vertices.size())
	 return true;

      int coloresAProbar = (vertice == 0 ? 1 : cantidadDeColores);
      
      for (int c = 1; c <= coloresAProbar; c++) {
	 coloreado[vertice] = c;
	 if (colorearGrafo(vertice + 1, cantidadDeColores, coloreado))
	    return true;
      }
      coloreado[vertice] = -1;

   }

   return false;

}

vector<int> GrafoNoDirigido::colorearGrafo(int cantidadDeColores) const {

   vector<int> coloreado(vertices.size(), -1);

   if (colorearGrafo(0, cantidadDeColores, coloreado))
      return coloreado;
   else
      throw string("No hay solucion con ") + to_string(cantidadDeColores) + string(" colores");

}
