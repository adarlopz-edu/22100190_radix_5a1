#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class MetodoRadix {
private:
    int* numeros;
    int numDatos;
    string preguntaIteracion;
    string preguntaSigno;

    void mostrarIteracion(int iteracion, int* arreglo) const;

public:
    MetodoRadix();
    void ingresarDatos();
    void Radix();
    void imprimirArreglo() const;
};

MetodoRadix::MetodoRadix() {}

void MetodoRadix::ingresarDatos() {
    cout << "METODO DE ORDENACION POR RADIX" << endl;
    cout << "Ingresa cuantos datos quieres ordenar (entre 1 y 50): ";
    cin >> numDatos;

    if (numDatos < 1 || numDatos > 50) {
        cout << "La cantidad de datos debe estar entre 1 y 50." << endl;
        exit(1);
    }

    numeros = new int[numDatos];

    cout << "Ingresa los datos separados por espacios: ";
    for (int i = 0; i < numDatos; ++i) {
        cin >> numeros[i];
    }

    cout << "Los valores son positivos?";
    cin >> preguntaSigno;

    // convierte a minusculas
    for (char& c : preguntaSigno) {
        c = tolower(c);
    }

    cout << "Quieres ver cada iteracion?";
    cin >> preguntaIteracion;

    for (char& c : preguntaIteracion) {
        c = tolower(c);
    }
}

void MetodoRadix::imprimirArreglo() const {

    if (preguntaSigno == "no") {
        for (int i = numDatos - 1; i >= 0; --i) {
            cout << -numeros[i] << " ";
        }
    }
    else {
        for (int i = 0; i < numDatos; ++i) {
            cout << numeros[i] << " ";
        }
    }
}

void MetodoRadix::mostrarIteracion(int iteracion, int* arreglo) const {
    for (int i = 0; i < numDatos; ++i) {
        cout << arreglo[i] << " ";
    }
    cout << endl;
}

void MetodoRadix::Radix() {
    int i, maximoAbsoluto = abs(numeros[0]), exponente = 1;
    int* arregloAuxiliar = new int[numDatos];

    // encuentra el valor maximo en el arreglo
    for (i = 1; i < numDatos; i++)
        if (abs(numeros[i]) > maximoAbsoluto)
            maximoAbsoluto = abs(numeros[i]);

    while (maximoAbsoluto / exponente > 0) {
        // inicializa un arreglo para contar la frecuencia de cada digito
        int conteo[10] = { 0 };

        // cuenta la frecuencia de cada digito en la posicion actual
        for (i = 0; i < numDatos; i++) {
            int indice = abs(numeros[i]) / exponente % 10;
            conteo[indice]++;
        }

        // ajusta el conteo para tener la posicion correcta de cada digito en el arreglo ordenado
        for (i = 1; i < 10; i++)
            conteo[i] += conteo[i - 1];

        // construye el arreglo ordenado basado en el conteo de cada digito
        for (i = numDatos - 1; i >= 0; i--) {
            int indice = abs(numeros[i]) / exponente % 10;
            arregloAuxiliar[--conteo[indice]] = numeros[i];
        }

        // copia el arreglo ordenado de regreso al arreglo original
        for (i = 0; i < numDatos; i++)
            numeros[i] = arregloAuxiliar[i];

        if (preguntaIteracion == "si") {
            mostrarIteracion(exponente / 10, numeros);
        }

        // mover al siguiente digita hacia la izquierda
        exponente *= 10;
    }

    if (preguntaSigno == "no") {
        for (int i = 0; i < numDatos; i++) {
            numeros[i] = abs(numeros[i]); // restaura el signo original
        }
    }

    delete[] arregloAuxiliar;
}



int main() {
    MetodoRadix ordenamiento;
    ordenamiento.ingresarDatos();
    ordenamiento.Radix();

    cout << endl;
    ordenamiento.imprimirArreglo();

    return 0;
}
