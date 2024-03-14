#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

struct Arco {
    string origen;
    string destino;
    int costo;

    Arco(string origen, string destino, int costo) : origen(origen), destino(destino), costo(costo) {}
};

class Grafo {
private:
    unordered_map<string, vector<Arco>> adjacencia;

public:
    Grafo() {}

    Grafo& insertarNodo(string nodo) {
        if (adjacencia.find(nodo) == adjacencia.end()) {
            adjacencia[nodo] = vector<Arco>();
        }
        return *this;
    }

    Grafo& insertarArco(string origen, string destino, int costo) {
        insertarNodo(origen).insertarNodo(destino);
        adjacencia[origen].push_back(Arco(origen, destino, costo));
        return *this;
    }

    bool esVacio() {
        return adjacencia.empty();
    }

    int costoTotalViaje(string origen, string destino) {
        if (adjacencia.find(origen) == adjacencia.end() || adjacencia.find(destino) == adjacencia.end())
            return -1; // No se encontró el nodo origen o destino

        unordered_map<string, int> costos;
        for (const auto& pair : adjacencia) {
            costos[pair.first] = INT_MAX;
        }

        costos[origen] = 0;

        queue<string> cola;
        cola.push(origen);

        while (!cola.empty()) {
            string actual = cola.front();
            cola.pop();

            for (const auto& arco : adjacencia[actual]) {
                if (costos[arco.destino] > costos[actual] + arco.costo) {
                    costos[arco.destino] = costos[actual] + arco.costo;
                    cola.push(arco.destino);
                }
            }
        }

        return costos[destino];
    }

    void mostrarViajesDisponibles() {
        cout << "Viajes Disponibles:\n";
        for (const auto& par : adjacencia) {
            const string& origen = par.first;
            for (const auto& arco : par.second) {
                cout << "Desde " << origen << " hasta " << arco.destino << ", Costo: " << arco.costo << endl;
            }
        }
    }
};

void flotaDeCamiones(Grafo& grafo, string origen, string destino) {
    int cantidadCamiones;
    int costoViajeCamion;

    cout << "Ingrese la cantidad de camiones que saldrán de " << origen << " a " << destino << ": ";
    cin >> cantidadCamiones;

    cout << "Ingrese el costo de viaje por camión: ";
    cin >> costoViajeCamion;

    int costoTotalViaje = grafo.costoTotalViaje(origen, destino);

    if (costoTotalViaje != -1) {
        int costoTotalFlota = cantidadCamiones * costoViajeCamion * costoTotalViaje;
        cout << "El costo total para la flota de camiones de " << origen << " a " << destino << " es: " << costoTotalFlota << endl;
    } else {
        cout << "No se encontró la ruta entre " << origen << " y " << destino << ". Por favor, verifique las ciudades ingresadas." << endl;
    }
}

int main() {
    Grafo g;
    g.insertarArco("Ciudad A", "Ciudad B", 10)
     .insertarArco("Ciudad B", "Ciudad C", 20)
     .insertarArco("Ciudad A", "Ciudad C", 30);

    int opcion;
    do {
        cout << "\nMenú:\n";
        cout << "1. Flota de Camiones\n";
        cout << "2. Mostrar Viajes Disponibles\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string origen, destino;
                cout << "Ingrese la ciudad de origen: ";
                cin >> origen;
                cout << "Ingrese la ciudad de destino: ";
                cin >> destino;
                flotaDeCamiones(g, origen, destino);
                break;
            }
            case 2:
                g.mostrarViajesDisponibles();
                break;
            case 0:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
                break;
        }
    } while (opcion != 0);

    return 0;
}

