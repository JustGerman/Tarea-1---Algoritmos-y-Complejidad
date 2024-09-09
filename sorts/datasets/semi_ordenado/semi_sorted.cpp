#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>

void generate_semi_sorted_file(int elementos, double shuffle_fraction = 0.5) {
    // Generar el nombre del archivo basado en la cantidad de números
    std::string nombreArchivo = "semi_sorted_" + std::to_string(elementos) + ".txt";
    std::ofstream archivo(nombreArchivo);

    // Verificar que el archivo se abrió correctamente
    if (!archivo) {
        std::cerr << "Error al abrir el archivo " << nombreArchivo << "." << std::endl;
        return;
    }

    // Crear una secuencia ordenada de 0 a elementos-1
    std::vector<int> data(elementos);
    for (int i = 0; i < elementos; ++i) {
        data[i] = i;
    }

    // Determinar cuántos elementos desordenar
    int shuffle_count = static_cast<int>(elementos * shuffle_fraction);

    // Desordenar aleatoriamente una pequeña fracción de los elementos
    std::random_device rd;
    std::mt19937 g(rd());

    for (int i = 0; i < shuffle_count; ++i) {
        int idx1 = g() % elementos;
        int idx2 = g() % elementos;
        std::swap(data[idx1], data[idx2]);
    }

    // Utilizar un buffer grande para optimizar la escritura
    const int bufferSize = 1000000;  // Tamaño del buffer (1 millón de números)
    std::string buffer;
    buffer.reserve(bufferSize * 12);  // Reservar espacio para el buffer

    for (int j = 0; j < elementos; ++j) {
        buffer += std::to_string(data[j]) + '\n';

        // Escribir el buffer al archivo cuando esté lleno
        if (buffer.size() >= bufferSize * 12) {
            archivo << buffer;
            buffer.clear();  // Limpiar el buffer después de escribirlo
        }
    }

    // Escribir cualquier dato restante en el buffer al archivo
    if (!buffer.empty()) {
        archivo << buffer;
    }

    // Cerrar el archivo
    archivo.close();
    std::cout << "Dataset semiordenado generado correctamente en '" << nombreArchivo << "' con " << elementos << " números." << std::endl;
}

int main() {
    // Definir la secuencia de números: 0, 2000000, 4000000, ..., 100000000
    std::vector<int> numElementos;
    for (int i = 0; i <= 100000; i += 2000) {
        numElementos.push_back(i);
    }

    // Generar archivos secuencialmente
    for (int elementos : numElementos) {
        generate_semi_sorted_file(elementos);
    }

    return 0;
}
