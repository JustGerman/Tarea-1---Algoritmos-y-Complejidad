#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void generate_sorted_file(int elementos) {
    // Generar el nombre del archivo basado en la cantidad de números
    std::string nombreArchivo = "sorted_" + std::to_string(elementos) + ".txt";
    std::ofstream archivo(nombreArchivo);

    // Verificar que el archivo se abrió correctamente
    if (!archivo) {
        std::cerr << "Error al abrir el archivo " << nombreArchivo << "." << std::endl;
        return;
    }

    // Utilizar un buffer grande para optimizar la escritura
    const int bufferSize = 1000000;  // Tamaño del buffer (1 millón de números)
    std::string buffer;
    buffer.reserve(bufferSize * 12);  // Reservar espacio para el buffer (12 es un tamaño aproximado para "int\n")

    for (int j = 0; j < elementos; ++j) {
        buffer += std::to_string(j) + '\n';

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
    std::cout << "Dataset generado correctamente en '" << nombreArchivo << "' con " << elementos << " números." << std::endl;
}

int main() {
    // Definir la secuencia de números: 0, 2000000, 4000000, ..., 100000000
    std::vector<int> numElementos;
    for (int i = 0; i <= 100000000; i += 2000000) {
        numElementos.push_back(i);
    }

    // Generar archivos secuencialmente
    for (int elementos : numElementos) {
        generate_sorted_file(elementos);
    }

    return 0;
}
