#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class MetodoRadix {
private:
    int numeros[50];
    int numDatos;
    string preguntaIteracion;
    string preguntaSigno;

    void mostrarIteracion(int iteracion, int arreglo[]) const;

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

    cout << "Ingresa los datos separados por espacios: ";
    for (int i = 0; i < numDatos; ++i) {
        cin >> numeros[i];
    }

    cout << "Los valores son positivos?";
    cin >> preguntaSigno;

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

void MetodoRadix::mostrarIteracion(int iteracion, int arreglo[]) const {
    for (int i = 0; i < numDatos; ++i) {
        cout << arreglo[i] << " ";
    }
    cout << endl;
}

void MetodoRadix::Radix() {
    int i, maximoAbsoluto = abs(numeros[0]), exponente = 1;
    int arregloAuxiliar[50];

    // valor maximo en el arreglo
    for (i = 1; i < numDatos; i++) {
        if (abs(numeros[i]) > maximoAbsoluto) {
            maximoAbsoluto = abs(numeros[i]);
        }
    }

    while (maximoAbsoluto / exponente > 0) {
        int conteo[10] = { 0 };

        // cuenta la frecuencia de cada digito en la posicion actual
        for (i = 0; i < numDatos; i++) {
            int indice = abs(numeros[i]) / exponente % 10;
            conteo[indice]++;
        }

        for (i = 1; i < 10; i++) {
            conteo[i] += conteo[i - 1];
        }

        // ordena el arreglo en base al conteo de cada numero
        for (i = numDatos - 1; i >= 0; i--) {
            int indice = abs(numeros[i]) / exponente % 10;
            arregloAuxiliar[--conteo[indice]] = numeros[i];
        }

        // el arreglo ordenado se copia al arreglo original
        for (i = 0; i < numDatos; i++) {
            numeros[i] = arregloAuxiliar[i];
        }

        if (preguntaIteracion == "si") {
            mostrarIteracion(exponente / 10, numeros);
        }
        // ahora el exponente se mueve a la izquierda y asi hasta que no haya nada mas
        exponente *= 10;
    }

    if (preguntaSigno == "no") {
        for (int i = 0; i < numDatos; i++) {
            numeros[i] = abs(numeros[i]);
        }
    }
}

int main() {
    MetodoRadix ordenamiento;
    ordenamiento.ingresarDatos();
    ordenamiento.Radix();

    cout << endl;
    ordenamiento.imprimirArreglo();

    return 0;
}
