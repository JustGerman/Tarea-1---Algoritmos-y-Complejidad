#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>

int main() {
    // Establecer el generador de números aleatorios basado en Mersenne Twister
    std::mt19937 gen(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(0, 100000000); // Distribución uniforme entre 0 y 100 millones

    // Definir la secuencia de números: 0, 2000000, 4000000, ..., 100000000
    std::vector<int> numElementos;
    for (int i = 0; i <= 100000000; i += 2000000) {
        numElementos.push_back(i);
    }

    // Iterar sobre cada cantidad en la secuencia
    for (int elementos : numElementos) {
        // Generar el nombre del archivo basado en la cantidad de números
        std::string nombreArchivo = "random_" + std::to_string(elementos) + ".txt";
        std::ofstream archivo(nombreArchivo);

        // Verificar que el archivo se abrió correctamente
        if (!archivo) {
            std::cerr << "Error al abrir el archivo " << nombreArchivo << "." << std::endl;
            return 1;
        }

        // Utilizar un buffer para optimizar la escritura
        std::string buffer;
        buffer.reserve(elementos * 11); // Reservar espacio en el buffer

        // Generar números aleatorios y escribirlos en el buffer
        for (int j = 0; j < elementos; ++j) {
            buffer += std::to_string(dist(gen)) + '\n';
        }

        // Escribir el contenido del buffer en el archivo de una sola vez
        archivo << buffer;

        // Cerrar el archivo
        archivo.close();
        std::cout << "Dataset generado correctamente en '" << nombreArchivo << "' con " << elementos << " números." << std::endl;
    }

    return 0;
}
