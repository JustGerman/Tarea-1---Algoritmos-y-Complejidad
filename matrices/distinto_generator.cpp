#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

// Función para generar una matriz de tamaño rows x cols con valores consecutivos
vector<vector<int>> generate_matrix(int rows, int cols) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = value++;
        }
    }
    return matrix;
}

// Función para guardar una matriz en un archivo
void save_matrix_to_file(const vector<vector<int>>& matrix, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
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

// Función para generar 20 casos de prueba de matrices A y B multiplicables entre sí
void generate_test_cases(int num_cases, int max_dim) {
    for (int case_num = 1; case_num <= num_cases; case_num++) {
        // Generar dimensiones aleatorias o incrementales para A y B
        int rowsA = (case_num * 50) % max_dim;  // Número de filas de A, con un valor máximo de 1000
        int colsA = (case_num * 40) % max_dim;  // Número de columnas de A (y filas de B)
        int colsB = (case_num * 30) % max_dim;  // Número de columnas de B

        // Si alguna dimensión es 0, se le asigna el valor máximo permitido
        if (rowsA == 0) rowsA = max_dim;
        if (colsA == 0) colsA = max_dim;
        if (colsB == 0) colsB = max_dim;

        // Generar matrices A y B
        vector<vector<int>> matrixA = generate_matrix(rowsA, colsA);
        vector<vector<int>> matrixB = generate_matrix(colsA, colsB); // Aseguramos que colsA == rowsB

        // Guardar matrices en archivos
        string filenameA = "matrizA" + to_string(case_num) + "_" + to_string(rowsA) + "x" + to_string(colsA) + ".txt";
        string filenameB = "matrizB" + to_string(case_num) + "_" + to_string(colsA) + "x" + to_string(colsB) + ".txt";

        save_matrix_to_file(matrixA, filenameA);
        save_matrix_to_file(matrixB, filenameB);
    }
}

int main() {
    int max_dim = 1000;  // Máxima dimensión permitida para las matrices (1000)
    int num_cases = 20;  // Número de casos de prueba

    // Generar 20 casos de prueba con matrices multiplicables
    generate_test_cases(num_cases, max_dim);

    return 0;
}
