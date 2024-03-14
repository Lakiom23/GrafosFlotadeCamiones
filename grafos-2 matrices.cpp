#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Arco {
    string origen;
    string destino;
    int costo;

    Arco(string origen, string destino, int costo) : origen(origen), destino(destino), costo(costo) {}
};

class Grafo {
private:
    vector<vector<int>> matrizCostos;
    vector<string> ciudades;

public:
    Grafo(int n, int m) : matrizCostos(n, vector<int>(m, -1)) {}

    void insertarCiudad(string ciudad) {
        ciudades.push_back(ciudad);
    }

    void insertarArco(string origen, string destino, int costo) {
        int indiceOrigen = obtenerIndiceCiudad(origen);
        int indiceDestino = obtenerIndiceCiudad(destino);
        if (indiceOrigen != -1 && indiceDestino != -1) {
            matrizCostos[indiceOrigen][indiceDestino] = costo;
        }
    }

    int obtenerIndiceCiudad(string ciudad) {
        for (int i = 0; i < ciudades.size(); ++i) {
            if (ciudades[i] == ciudad) {
                return i;
            }
        }
        return -1;
    }

    int costoTotalViaje(string origen, string destino) {
        int indiceOrigen = obtenerIndiceCiudad(origen);
        int indiceDestino = obtenerIndiceCiudad(destino);
        if (indiceOrigen != -1 && indiceDestino != -1) {
            return matrizCostos[indiceOrigen][indiceDestino];
        }
        return -1;
    }

    void mostrarViajesDisponibles() {
        cout << "Viajes Disponibles:\n";
        for (int i = 0; i < ciudades.size(); ++i) {
            for (int j = 0; j < ciudades.size(); ++j) {
                if (matrizCostos[i][j] != -1) {
                    cout << "Desde " << ciudades[i] << " hasta " << ciudades[j] << ", Costo: " << matrizCostos[i][j] << endl;
                }
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
    Grafo g(3, 3); // Por ejemplo, una matriz 3x3
    g.insertarCiudad("Ciudad A");
    g.insertarCiudad("Ciudad B");
    g.insertarCiudad("Ciudad C");

    g.insertarArco("Ciudad A", "Ciudad B", 10);
    g.insertarArco("Ciudad B", "Ciudad C", 20);
    g.insertarArco("Ciudad A", "Ciudad C", 30);

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
