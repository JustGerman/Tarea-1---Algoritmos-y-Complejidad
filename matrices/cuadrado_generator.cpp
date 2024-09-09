#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

void generate_cuadrados(int max_size, int step) {
    for (int size = 0; size <= max_size; size += step) {
        // Crear la matriz de tamaño 'size x size'
        vector<vector<int>> matrix(size, vector<int>(size));

        // Llenar la matriz con valores ordenados
        int value = 1;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] = value++;
            }
        }

        // Crear el nombre del archivo de salida
        string filename = "matriz" + to_string(size) + ".txt";
        ofstream file(filename);

        if (file.is_open()) {
            // Escribir la matriz en el archivo
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    file << setw(5) << matrix[i][j] << " ";
                }
                file << endl;
            }
            file.close();
            cout << "Archivo " << filename << " generado correctamente." << endl;
        } else {
            cout << "No se pudo abrir el archivo " << filename << endl;
        }
    }
}

int main() {

    generate_cuadrados(1000, 100);

    return 0;
}
