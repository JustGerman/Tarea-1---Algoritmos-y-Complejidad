#include <bits/stdc++.h>
#include <chrono>  // Incluir la librería para medir el tiempo

using namespace std;

// Función merge que une dos subarreglos ordenados (left y right) en el arreglo original arr
void merge(vector<int>& left, vector<int>& right, vector<int>& arr) {
    int size_izq = left.size();  // Tamaño del subarreglo izquierdo
    int size_der = right.size(); // Tamaño del subarreglo derecho

    // Índices para recorrer left, right y arr
    int i = 0, izq = 0, der = 0;

    // Mientras queden elementos en ambos subarreglos
    while (izq < size_izq && der < size_der) {
        // Si el elemento de left es menor que el de right, se coloca en arr
        if (left[izq] < right[der]) {
            arr[i] = left[izq];
            izq++;  // Avanzamos en el subarreglo izquierdo
        } else {
            arr[i] = right[der];
            der++;  // Avanzamos en el subarreglo derecho
        }
        i++;  // Avanzamos en el arreglo combinado
    }

    // Si quedan elementos en el subarreglo izquierdo, se añaden a arr
    while (izq < size_izq) {
        arr[i] = left[izq];
        izq++;
        i++;
    }

    // Si quedan elementos en el subarreglo derecho, se añaden a arr
    while (der < size_der) {
        arr[i] = right[der];
        der++;
        i++;
    }
}

// Función mergesort que aplica el algoritmo de ordenamiento por mezcla
void mergesort(vector<int>& arr) {
    int size = arr.size();  // Tamaño del arreglo

    // Caso base: si el tamaño es 1 o menor, ya está ordenado
    if (size <= 1) return;

    int medio = size / 2;  // Dividimos el arreglo en dos mitades

    // Creamos los subarreglos para la izquierda y derecha
    vector<int> left(medio);  // Subarreglo izquierdo de tamaño 'medio'
    vector<int> right(size - medio);  // Subarreglo derecho con el resto

    // Llenamos los subarreglos con las correspondientes partes de arr
    for (int i = 0; i < medio; i++) left[i] = arr[i];  // Parte izquierda
    for (int i = medio; i < size; i++) right[i - medio] = arr[i];  // Parte derecha

    // Recursivamente aplicamos mergesort en ambos subarreglos
    mergesort(left);
    mergesort(right);

    // Combinamos ambos subarreglos ordenados en arr usando la función merge
    merge(left, right, arr);
}


int main() {
    vector<int> sizes = {0, 2000000, 4000000, 6000000, 8000000, 10000000,
                         12000000, 14000000, 16000000, 18000000, 20000000,
                         22000000, 24000000, 26000000, 28000000, 30000000,
                         32000000, 34000000, 36000000, 38000000, 40000000,
                         42000000, 44000000, 46000000, 48000000, 50000000,
                         52000000, 54000000, 56000000, 58000000, 60000000,
                         62000000, 64000000, 66000000, 68000000, 70000000,
                         72000000, 74000000, 76000000, 78000000, 80000000,
                         82000000, 84000000, 86000000, 88000000, 90000000,
                         92000000, 94000000, 96000000, 98000000, 100000000};

    for (int size : sizes) {
        string archivo = "semi_sorted_" + to_string(size) + ".txt";
        vector<int> numbers;
        ifstream infile(archivo);

        if (!infile) {
            cerr << "Error al abrir el archivo " << archivo << endl;
            continue;
        }

        int num;
        while (infile >> num) {
            numbers.push_back(num);
        }

        infile.close();

        // Iniciar la medición de tiempo
        auto start = chrono::high_resolution_clock::now();

        mergesort(numbers);

        // Finalizar la medición de tiempo
        auto end = chrono::high_resolution_clock::now();

        // Calcular la duración en milisegundos
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        // Imprimir la cantidad de datos y el tiempo de ejecución
        cout << duration.count() << endl;
    }

    return 0;
}

