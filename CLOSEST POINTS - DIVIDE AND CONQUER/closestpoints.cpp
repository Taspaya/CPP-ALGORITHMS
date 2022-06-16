#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;

typedef pair<float, float> Punto;

void ver(const vector<Punto>& puntos) {

    for (const auto& p : puntos)
        cout << "( " << p.first << " , " << p.second << " )";

}

int main() {

    cout << "First try, defined points" << endl;
    cout << "===================================" << endl;

    vector<Punto> puntos = { Punto(2, 3), Punto(5,7), Punto(3, 4), Punto(4, 4), Punto(4, 4), Punto(5,7) };

    while (puntos.size() >= 2) {
        cout << "Points : ";
        ver(puntos);
        cout << " ---> minium Distance: " << distanciaMinima(puntos) << endl;
        puntos.pop_back();
    }


    cout << endl;
    cout << "Second try: random generated points" << endl;
    cout << "===================================================" << endl;

    default_random_engine default_random;
    uniform_real_distribution<float> generadorAleatorio(-1000.0, 1000.0);

    for (int talla = 2, tallaMax = 10; tallaMax <= 100000; tallaMax *= 10)

        for (; talla < tallaMax; talla += tallaMax / 10) {

            while (puntos.size() < talla)
                puntos.push_back(Punto(generadorAleatorio(default_random), generadorAleatorio(default_random)));

            float distancia = distanciaMinima(puntos);

            cout << "n points: " << talla << " ---> minium distance: " << distancia << endl;
        }

}

float distanciaAlCuadrado(const Punto& p1, const Punto& p2) { //square distance

    float a = p2.first - p1.first;
    float b = p2.second - p1.second;
    return a * a + b * b;

}

bool compararY(const Punto& p1, const Punto& p2) { // Y compare

    return p1.second < p2.second;

}


// minimun saquare distance
float distanciaAlCuadradoMinima(const vector<Punto>& puntosPorX, 
    const vector<Punto>& puntosPorY) {

    // Si estamos en el caso base de la recursion, terminamos

    int talla = puntosPorX.size();

    if (talla == 2)
        return distanciaAlCuadrado(puntosPorX[0], puntosPorX[1]);

    if (talla == 3)
        return min({ distanciaAlCuadrado(puntosPorX[0], puntosPorX[1]),
            distanciaAlCuadrado(puntosPorX[0], puntosPorX[2]),
            distanciaAlCuadrado(puntosPorX[1], puntosPorX[2]) });

    // Dividimos los puntos ordenados por X entre la mitad izquierda y la mitad derecha sin perder esa ordenacion

    int tallaIzquierda = talla / 2;

    vector<Punto> puntosIzquierdaPorX(puntosPorX.begin(), puntosPorX.begin() + tallaIzquierda),
        puntosDerechaPorX(puntosPorX.begin() + tallaIzquierda, puntosPorX.end());

    // Repartimos los puntos ordenados por Y entre la mitad izquierda y la mitad derecha sin perder esa ordenacion

    vector<Punto> puntosIzquierdaPorY(tallaIzquierda),
        puntosDerechaPorY(talla - tallaIzquierda);

    for (int i = 0, j = 0, k = 0; i < talla; i++)
        if (puntosPorY[i] < puntosDerechaPorX[0]) // A igual X mira Y; no pueden coincidir X e Y
            puntosIzquierdaPorY[j++] = puntosPorY[i];
        else
            puntosDerechaPorY[k++] = puntosPorY[i];

    // Llamamos a la funcion recursiva pasandole los puntos de la mitad izquierda ordenados por X y ordenados por Y

    float minimaIzquierda = distanciaAlCuadradoMinima(puntosIzquierdaPorX, puntosIzquierdaPorY);

    // Llamamos a la funcion recursiva pasandole los puntos de la mitad derecha ordenados por X y ordenados por Y

    float minimaDerecha = distanciaAlCuadradoMinima(puntosDerechaPorX, puntosDerechaPorY);

    // Creamos un vector con los puntos en la franja central ordenados por Y

    float minima = min(minimaIzquierda, minimaDerecha);
    vector<Punto> puntosCentralesPorY;
    float frontera = puntosIzquierdaPorX[tallaIzquierda - 1].first;
    for (auto p : puntosPorY)
        if (abs(frontera - p.first) < minima)
            puntosCentralesPorY.push_back(p);

    // Calculamos distancias entre puntos de la franja central con criterio de parada por distancia vertical

    for (int i = 0; i < puntosCentralesPorY.size() - 1; i++)
        for (int j = i + 1;
            j < puntosCentralesPorY.size() && puntosCentralesPorY[j].second - puntosCentralesPorY[i].second < minima;
            j++)
            minima = min(minima,
                distanciaAlCuadrado(puntosCentralesPorY[i], puntosCentralesPorY[j]));

    return minima;

}


// minimum distance 
float distanciaMinima(const vector<Punto>& puntos) {

    if (puntos.size() < 2)
        throw string("Necesitamos al menos dos puntos.");

    // We create a copy of the vector of points ordered by X and, in case of a tie in X, by Y

    vector<Punto> puntosPorX(puntos);

    // We use pair operator to sort by X and, in case of a tie, by Y
    sort(puntosPorX.begin(), puntosPorX.end()); 
    
    // We detect duplicates and terminate if there are duplicates.
    // Thanks to the previous order, if there are two consecutive equal points we return 0,
    // and if there are not, we know that there is no pair of equal points.

    for (int i = 0; i < puntosPorX.size() - 1; i++)
        if (puntosPorX[i] == puntosPorX[i + 1])
            return 0;

    // We create a copy of the vector of points ordered by Y

    vector<Punto> puntosPorY(puntos);

    sort(puntosPorY.begin(), puntosPorY.end(), compararY); // sort by Y

    // We call the recursive function passing the two ordered copies to it

    return sqrt(distanciaAlCuadradoMinima(puntosPorX, puntosPorY));

}
