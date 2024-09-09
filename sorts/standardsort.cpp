#include <bits/stdc++.h>
#include <chrono>  // Incluir la librería para medir el tiempo

using namespace std;

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

        // Aplicar std::sort
        sort(numbers.begin(), numbers.end());

        // Finalizar la medición de tiempo
        auto end = chrono::high_resolution_clock::now();

        // Calcular la duración en milisegundos
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        // Imprimir la cantidad de datos y el tiempo de ejecución
        cout << duration.count() << endl;
    }

    return 0;
}
