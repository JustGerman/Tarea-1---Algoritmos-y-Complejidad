#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función para realizar la multiplicación de matrices utilizando el algoritmo cúbico tradicional
vector<vector<int>> traditional(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2) {
    int rows1 = matrix1.size();          // Número de filas de la primera matriz
    int cols1 = matrix1[0].size();       // Número de columnas de la primera matriz (y número de filas de la segunda matriz)
    int cols2 = matrix2[0].size();       // Número de columnas de la segunda matriz
    
    // Inicialización de la matriz resultado con tamaño adecuado y valores iniciales de 0
    vector<vector<int>> result(rows1, vector<int>(cols2, 0));

    // Iteración cúbica para la multiplicación de matrices, adaptada para matrices no necesariamente cuadradas
    for (int i = 0; i < rows1; i++) {              // Recorre las filas de la primera matriz
        for (int j = 0; j < cols2; j++) {          // Recorre las columnas de la segunda matriz
            for (int k = 0; k < cols1; k++) {      // Recorre las columnas de la primera matriz (y filas de la segunda matriz)
                // Multiplica los elementos correspondientes de la primera y segunda matriz y acumula el resultado
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    // Retorna la matriz resultante de la multiplicación
    return result;
}


// Funcion para transponer una matriz
vector<vector<int>> transpose(vector<vector<int>>& matrix) {
    int rows = matrix.size();                // Numero de filas de la matriz original
    int cols = matrix[0].size();             // Numero de columnas de la matriz original
    // Inicializa una nueva matriz transpuesta con dimensiones invertidas
    vector<vector<int>> transposed(cols, vector<int>(rows)); 

    // Recorre cada elemento de la matriz original
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Asigna el valor transpuesto, intercambiando filas y columnas
            transposed[j][i] = matrix[i][j];  
        }
    }

    // Retorna la matriz transpuesta
    return transposed;
}

// Funcion para realizar la multiplicacion de matrices optimizada transponiendo la segunda matriz
vector<vector<int>> optimized(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2) {
    int rows1 = matrix1.size();              // Numero de filas de la primera matriz
    int cols1 = matrix1[0].size();           // Numero de columnas de la primera matriz (y numero de filas de la segunda matriz)
    int cols2 = matrix2[0].size();           // Numero de columnas de la segunda matriz

    // Transponer la segunda matriz para mejorar la localidad de los datos
    vector<vector<int>> matrix2T = transpose(matrix2);  

    // Inicializa la matriz resultado con el tamaño adecuado y valores iniciales de 0
    vector<vector<int>> result(rows1, vector<int>(cols2, 0));  

    // Iteracion cubica optimizada, utilizando la matriz transpuesta
    for (int i = 0; i < rows1; i++) {              // Recorre las filas de la primera matriz
        for (int j = 0; j < cols2; j++) {          // Recorre las columnas de la segunda matriz (transpuesta)
            for (int k = 0; k < cols1; k++) {      // Recorre las columnas de la primera matriz (y filas de la segunda matriz transpuesta)
                // Multiplica los elementos correspondientes y acumula el resultado
                result[i][j] += matrix1[i][k] * matrix2T[j][k];  
            }
        }
    }

    // Retorna la matriz resultante de la multiplicacion
    return result;
}


// Función para sumar matrices, utilizada en el algoritmo de Strassen
vector<vector<int>> add_matrix(vector<vector<int>>& matrix_A, vector<vector<int>>& matrix_B, int split_index, int multiplier = 1) {
    vector<vector<int>> result = matrix_A;  // Crear una copia de la matriz A
    for (int i = 0; i < split_index; i++) {
        for (int j = 0; j < split_index; j++) {
            result[i][j] += multiplier * matrix_B[i][j];
        }
    }
    return result;
}

// Funcion Strassen para multiplicar matrices
vector<vector<int>> Strassen(vector<vector<int>>& matrix_A, vector<vector<int>>& matrix_B) {
    int col_1 = matrix_A[0].size();      // Numero de columnas de la matriz A
    int row_1 = matrix_A.size();         // Numero de filas de la matriz A
    int col_2 = matrix_B[0].size();      // Numero de columnas de la matriz B
    int row_2 = matrix_B.size();         // Numero de filas de la matriz B

    // Verifica que las matrices sean cuadradas y que el número de columnas de A sea igual al número de filas de B
    if (col_1 != row_2 || row_1 != col_1 || col_2 != row_2) {
        cout << "\nAdvertencia: Strassen solo funciona para matrices cuadradas del mismo tamaño, se utilizará la multiplicación tradicional.\n";
        return traditional(matrix_A, matrix_B); // Usar multiplicación tradicional si no son cuadradas
    }
    
    // Verifica que el numero de columnas de A sea igual al numero de filas de B (condicion para multiplicacion de matrices)
    if (col_1 != row_2) {
        cout << "\nError: The number of columns in Matrix A must be equal to the number of rows in Matrix B\n";
        return {}; // Retorna un resultado vacio si las matrices no son multiplicables
    }

    // Inicializa la matriz resultante con el numero correcto de filas y columnas
    vector<int> result_matrix_row(col_2, 0);               // Fila de la matriz resultado con ceros
    vector<vector<int>> result_matrix(row_1, result_matrix_row); // Matriz de resultado

    // Caso base: si las matrices son de 1x1, multiplica los dos valores directamente
    if (col_1 == 1) {
        result_matrix[0][0] = matrix_A[0][0] * matrix_B[0][0];
    } else {
        // Caso recursivo: divide las matrices en 4 submatrices más pequeñas
        int split_index = col_1 / 2;                        // Punto de division de las matrices
        vector<int> row_vector(split_index, 0);             // Fila auxiliar con ceros para inicializar submatrices

        // Inicializacion de las submatrices A y B
        vector<vector<int>> a00(split_index, row_vector);
        vector<vector<int>> a01(split_index, row_vector);
        vector<vector<int>> a10(split_index, row_vector);
        vector<vector<int>> a11(split_index, row_vector);
        vector<vector<int>> b00(split_index, row_vector);
        vector<vector<int>> b01(split_index, row_vector);
        vector<vector<int>> b10(split_index, row_vector);
        vector<vector<int>> b11(split_index, row_vector);

        // Llena las submatrices A y B dividiendo las matrices originales
        for (int i = 0; i < split_index; i++) {
            for (int j = 0; j < split_index; j++) {
                a00[i][j] = matrix_A[i][j];                       // Parte superior izquierda de A
                a01[i][j] = matrix_A[i][j + split_index];         // Parte superior derecha de A
                a10[i][j] = matrix_A[split_index + i][j];         // Parte inferior izquierda de A
                a11[i][j] = matrix_A[i + split_index][j + split_index]; // Parte inferior derecha de A
                b00[i][j] = matrix_B[i][j];                       // Parte superior izquierda de B
                b01[i][j] = matrix_B[i][j + split_index];         // Parte superior derecha de B
                b10[i][j] = matrix_B[split_index + i][j];         // Parte inferior izquierda de B
                b11[i][j] = matrix_B[i + split_index][j + split_index]; // Parte inferior derecha de B
            }
        }

        // Evita pasar valores temporales directamente (Rvalues), almacena los resultados en variables intermedias
        
        // Calculo de las 7 multiplicaciones segun el algoritmo de Strassen
        vector<vector<int>> temp1 = add_matrix(b01, b11, split_index, -1); // b01 - b11
        vector<vector<int>> p = Strassen(a00, temp1);                      // p = a00 * (b01 - b11)

        vector<vector<int>> temp2 = add_matrix(a00, a01, split_index);     // a00 + a01
        vector<vector<int>> q = Strassen(temp2, b11);                      // q = (a00 + a01) * b11

        vector<vector<int>> temp3 = add_matrix(a10, a11, split_index);     // a10 + a11
        vector<vector<int>> r = Strassen(temp3, b00);                      // r = (a10 + a11) * b00

        vector<vector<int>> temp4 = add_matrix(b10, b00, split_index, -1); // b10 - b00
        vector<vector<int>> s = Strassen(a11, temp4);                      // s = a11 * (b10 - b00)

        vector<vector<int>> temp5a = add_matrix(a00, a11, split_index);    // a00 + a11
        vector<vector<int>> temp5b = add_matrix(b00, b11, split_index);    // b00 + b11
        vector<vector<int>> t = Strassen(temp5a, temp5b);                  // t = (a00 + a11) * (b00 + b11)

        vector<vector<int>> temp6a = add_matrix(a01, a11, split_index, -1); // a01 - a11
        vector<vector<int>> temp6b = add_matrix(b10, b11, split_index);    // b10 + b11
        vector<vector<int>> u = Strassen(temp6a, temp6b);                  // u = (a01 - a11) * (b10 + b11)

        vector<vector<int>> temp7a = add_matrix(a00, a10, split_index, -1); // a00 - a10
        vector<vector<int>> temp7b = add_matrix(b00, b01, split_index);    // b00 + b01
        vector<vector<int>> v = Strassen(temp7a, temp7b);                  // v = (a00 - a10) * (b00 + b01)

        // Combina los resultados de las 7 multiplicaciones para obtener las submatrices de la matriz resultante
        vector<vector<int>> temp8 = add_matrix(t, s, split_index);         // t + s
        vector<vector<int>> temp9 = add_matrix(temp8, u, split_index);     // (t + s) + u
        vector<vector<int>> result_matrix_00 = add_matrix(temp9, q, split_index, -1);  // result_matrix_00 = (t + s + u - q)

        vector<vector<int>> result_matrix_01 = add_matrix(p, q, split_index);           // result_matrix_01 = p + q

        vector<vector<int>> result_matrix_10 = add_matrix(r, s, split_index);           // result_matrix_10 = r + s

        vector<vector<int>> temp10 = add_matrix(t, p, split_index);         // t + p
        vector<vector<int>> temp11 = add_matrix(temp10, r, split_index, -1);// (t + p - r)
        vector<vector<int>> result_matrix_11 = add_matrix(temp11, v, split_index, -1); // result_matrix_11 = (t + p - r - v)

        // Reconstruccion de la matriz resultante desde las submatrices calculadas
        for (int i = 0; i < split_index; i++) {
            for (int j = 0; j < split_index; j++) {
                result_matrix[i][j] = result_matrix_00[i][j];               // Parte superior izquierda
                result_matrix[i][j + split_index] = result_matrix_01[i][j]; // Parte superior derecha
                result_matrix[split_index + i][j] = result_matrix_10[i][j]; // Parte inferior izquierda
                result_matrix[i + split_index][j + split_index] = result_matrix_11[i][j]; // Parte inferior derecha
            }
        }
    }
    return result_matrix;  // Retorna la matriz final resultante
}


// Función para leer una matriz desde un archivo
vector<vector<int>> read_matrix(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> matrix;
    
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<int> row;
            stringstream ss(line);
            int num;
            while (ss >> num) {
                row.push_back(num);
            }
            matrix.push_back(row);
        }
        file.close();
    } else {
        cout << "No se pudo abrir el archivo " << filename << endl;
    }
    
    return matrix;
}

// Resto del código para las funciones de multiplicación...

int main() {
    // Nombres de los archivos de las matrices A y B que se leerán
    vector<string> filesA = {
        "matrizA1_50x40.txt", "matrizA2_100x80.txt", "matrizA3_150x120.txt", "matrizA4_200x160.txt",
        "matrizA5_250x200.txt", "matrizA6_300x240.txt", "matrizA7_350x280.txt", "matrizA8_400x320.txt",
        "matrizA9_450x360.txt", "matrizA10_500x400.txt", "matrizA11_550x440.txt", "matrizA12_600x480.txt",
        "matrizA13_650x520.txt", "matrizA14_700x560.txt", "matrizA15_750x600.txt", "matrizA16_800x640.txt",
        "matrizA17_850x680.txt", "matrizA18_900x720.txt", "matrizA19_950x760.txt", "matrizA20_1000x800.txt"
    };

    vector<string> filesB = {
        "matrizB1_40x30.txt", "matrizB2_80x60.txt", "matrizB3_120x90.txt", "matrizB4_160x120.txt",
        "matrizB5_200x150.txt", "matrizB6_240x180.txt", "matrizB7_280x210.txt", "matrizB8_320x240.txt",
        "matrizB9_360x270.txt", "matrizB10_400x300.txt", "matrizB11_440x330.txt", "matrizB12_480x360.txt",
        "matrizB13_520x390.txt", "matrizB14_560x420.txt", "matrizB15_600x450.txt", "matrizB16_640x480.txt",
        "matrizB17_680x510.txt", "matrizB18_720x540.txt", "matrizB19_760x570.txt", "matrizB20_800x600.txt"
    };

    for (size_t i = 0; i < filesA.size(); i++) {
        // Leer las matrices desde los archivos correspondientes
        vector<vector<int>> matrix1 = read_matrix(filesA[i]);
        vector<vector<int>> matrix2 = read_matrix(filesB[i]);

        if (matrix1.empty() || matrix2.empty()) continue;

        // Obtener las dimensiones de las matrices
        int filasA = matrix1.size();
        int columnasA = matrix1[0].size();
        int filasB = matrix2.size();
        int columnasB = matrix2[0].size();

        // Mostrar las dimensiones de las matrices procesadas
        cout << "Procesando " << filesA[i] << " (" << filasA << "x" << columnasA << ") y " 
             << filesB[i] << " (" << filasB << "x" << columnasB << ")" << endl;

        // Medir tiempo de ejecución para la multiplicación tradicional
        auto start_traditional = high_resolution_clock::now();
        vector<vector<int>> result_traditional = traditional(matrix1, matrix2);
        auto end_traditional = high_resolution_clock::now();
        auto duration_traditional = duration_cast<milliseconds>(end_traditional - start_traditional);
        cout << "Tiempo de ejecución (Traditional): " << duration_traditional.count() << " ms" << endl;

        // Medir tiempo de ejecución para la multiplicación optimizada
        auto start_optimized = high_resolution_clock::now();
        vector<vector<int>> result_optimized = optimized(matrix1, matrix2);
        auto end_optimized = high_resolution_clock::now();
        auto duration_optimized = duration_cast<milliseconds>(end_optimized - start_optimized);
        cout << "Tiempo de ejecución (Optimized): " << duration_optimized.count() << " ms" << endl;

        // Medir tiempo de ejecución para la multiplicación con Strassen
        auto start_strassen = high_resolution_clock::now();
        vector<vector<int>> result_strassen = Strassen(matrix1, matrix2);
        auto end_strassen = high_resolution_clock::now();
        auto duration_strassen = duration_cast<milliseconds>(end_strassen - start_strassen);
        cout << "Tiempo de ejecución (Strassen): " << duration_strassen.count() << " ms" << endl;

        cout << "-------------------------------------" << endl;
    }

    return 0;
}
