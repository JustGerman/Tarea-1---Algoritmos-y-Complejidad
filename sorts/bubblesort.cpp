#include <bits/stdc++.h>
#include <chrono>  // Incluir la librería para medir el tiempo

using namespace std;

// Versión optimizada bubblesort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    int i, j;               // Variables i and j are used for iteration
    bool swapped;            // A flag to check if any swapping happened

    // Outer loop to iterate over the entire array n-1 times
    for (i = 0; i < n - 1; i++) {
        swapped = false;     // Reset the swapped flag to false for each pass

        // Inner loop to perform the comparison and swap adjacent elements
        // As the largest elements "bubble up" to the end, we reduce the range by 'i'
        for (j = 0; j < n - i - 1; j++) {
            // Compare adjacent elements
            if (arr[j] > arr[j + 1]) {
                // Swap them if they are in the wrong order
                swap(arr[j], arr[j + 1]);
                swapped = true; // Set swapped to true if any swapping occurred
            }
        }

        // If no two elements were swapped in the current pass,
        // the array is already sorted, and we can break early
        if (swapped == false)
            break; // Exit the loop early since the array is sorted
    }
}

int main() {
 /*
    vector<int> sizes = {0, 2000, 4000, 6000, 8000, 10000, 12000, 14000, 16000, 
                         18000, 20000, 22000, 24000, 26000, 28000, 30000, 
                         32000, 34000, 36000, 38000, 40000, 42000, 44000, 
                         46000, 48000, 50000, 52000, 54000, 56000, 58000, 
                         60000, 62000, 64000, 66000, 68000, 70000, 72000, 
                         74000, 76000, 78000, 80000, 82000, 84000, 86000, 
                         88000, 90000, 92000, 94000, 96000, 98000, 100000};
*/
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
        string archivo = "sorted_" + to_string(size) + ".txt";
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

        bubbleSort(numbers);

        // Finalizar la medición de tiempo
        auto end = chrono::high_resolution_clock::now();

        // Calcular la duración en milisegundos
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        // Imprimir la cantidad de datos y el tiempo de ejecución
        cout << duration.count() << endl;
    }

    return 0;
}
